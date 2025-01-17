#include "D2StatList.h"

#include <D2BitManip.h>
#include "D2DataTbls.h"
#include "D2Environment.h"
#include "D2ItemMods.h"
#include "D2Items.h"
#include "D2States.h"
#include "Units/Units.h"
//TODO: Find names


//D2Common.0x6FDB57C0 (#10563)
BOOL __stdcall STATLIST_AreUnitsAligned(struct D2Unit* pUnit1, struct D2Unit* pUnit2)
{
	if (pUnit1 && pUnit2)
	{
		if (pUnit1 == pUnit2)
		{
			return TRUE;
		}

		int nAlignment1 = STATLIST_GetUnitAlignment(pUnit1);
		int nAlignment2 = STATLIST_GetUnitAlignment(pUnit2);

		if (nAlignment1 == UNIT_ALIGNMENT_EVIL && nAlignment2 == UNIT_ALIGNMENT_EVIL
			|| nAlignment1 == UNIT_ALIGNMENT_GOOD && nAlignment2 == UNIT_ALIGNMENT_GOOD)
		{
			return TRUE;
		}
	}

	return FALSE;
}

#define IMPLEMENT_StatArray_FUNCTIONS_ON(T, StatType) \
/* Helper function */ \
static int __fastcall T##_FindInsertionIndex(const struct T* pStatsArray, D2SLayerStatId_PackedType nLayer_StatId, bool* pAlreadyInArray) \
{ \
	if (pAlreadyInArray) \
	{ \
		*pAlreadyInArray = false; \
	} \
	/* Find by dichotomic search, stats are sorted by nPackedValue */ \
	int nMin = 0; \
	int nMax = pStatsArray->nStatCount; \
 \
	while (nMin < nMax) \
	{ \
		const int nMidPoint = nMin + (nMax - nMin) / 2; \
 \
		if (nLayer_StatId < pStatsArray->pStat[nMidPoint].nPackedValue) \
		{ \
			nMax = nMin + (nMax - nMin) / 2; \
		} \
		else if (nLayer_StatId > pStatsArray->pStat[nMidPoint].nPackedValue) \
		{ \
			nMin = nMidPoint + 1; \
		} \
		else /* found it */ \
		{ \
			if (pAlreadyInArray) \
			{ \
				*pAlreadyInArray = true; \
			} \
			return nMidPoint; \
		} \
	} \
 \
	return nMin; \
} \
 \
int T##_DichotomicSearch(const struct T* pStatArray, D2SLayerStatId_PackedType nLayer_StatId) \
{ \
	bool alreadyInArray = false; \
	int insertionIdx = T##_FindInsertionIndex(pStatArray, nLayer_StatId, &alreadyInArray); \
	if (alreadyInArray) \
		return insertionIdx; \
	return -1; \
} \
 \
/* Helper function */ \
struct StatType* __fastcall T##_InsertStat(void* pMemPool, struct T* pStatsArray, D2SLayerStatId_PackedType nLayer_StatId, int insertionIdx) \
{ \
	if (pStatsArray->nStatCount >= pStatsArray->nCapacity) \
	{ \
		pStatsArray->nCapacity += T##_nGrowthAmount; \
		pStatsArray->pStat = (struct StatType *)D2_REALLOC_POOL(pMemPool, pStatsArray->pStat, pStatsArray->nCapacity * sizeof(*pStatsArray->pStat)); \
	} \
 \
	if (insertionIdx < pStatsArray->nStatCount) \
	{ \
		/* Move memory by 1 slot so that we can insert our stat */ \
		memmove(&pStatsArray->pStat[insertionIdx + 1], &pStatsArray->pStat[insertionIdx], (pStatsArray->nStatCount - insertionIdx) * sizeof(struct D2Stat)); \
	} \
 \
	pStatsArray->pStat[insertionIdx] = (struct StatType){}; /* Default init to 0 */ \
	pStatsArray->pStat[insertionIdx].nPackedValue = nLayer_StatId; \
	++pStatsArray->nStatCount; \
 \
	return &pStatsArray->pStat[insertionIdx]; \
}
IMPLEMENT_StatArray_FUNCTIONS_ON(D2ModStatsArray, D2SLayerStatId)
IMPLEMENT_StatArray_FUNCTIONS_ON(D2StatsArray, D2Stat)

// Helper function
static struct D2Stat* __fastcall STATLIST_GetOrInsertStat(void* pMemPool, struct D2StatsArray* pStatsArray, D2SLayerStatId_PackedType nLayer_StatId)
{
	bool bFoundStatInArray = false;
	const int insertionIdx = D2StatsArray_FindInsertionIndex(pStatsArray, nLayer_StatId, &bFoundStatInArray);

	if (bFoundStatInArray)
	{
		return &pStatsArray->pStat[insertionIdx];
	}
	else
	{
		return D2StatsArray_InsertStat(pMemPool, pStatsArray, nLayer_StatId, insertionIdx);
	}
}

// Helper function
static void STATLIST_NotifyUnitOfStatValueChange(struct D2ItemStatCostTxt* pItemStatCostTxtRecord, struct D2StatListEx* pStatListEx, struct D2Unit* pUnit, D2SLayerStatId_PackedType nLayer_StatId, int nPreviousValue, int nNewValue)
{
	if (pStatListEx->pfOnValueChanged && (pItemStatCostTxtRecord->dwItemStatFlags & gdwBitMasks[ITEMSTATCOSTFLAGINDEX_FCALLBACK]))
	{
		pStatListEx->pfOnValueChanged(pStatListEx->pGame, pStatListEx->pOwner, pUnit, nLayer_StatId, nPreviousValue, nNewValue);
	}
}

//Helper function
static void STATLIST_SetUnitStatNewValue(struct D2StatListEx* pStatListEx, struct D2StatsArray* pStatsArray, struct D2Stat* pStat, D2SLayerStatId_PackedType nLayer_StatId, int nNewValue, struct D2ItemStatCostTxt* pItemStatCostTxtRecord, struct D2Unit* pUnit)
{
	int nPreviousValue = pStat->nValue;
	if (nNewValue != 0 || pItemStatCostTxtRecord->nKeepZero)
	{
		pStat->nValue = nNewValue;
		if (pItemStatCostTxtRecord->bHasOpApplyingToItem)
		{
			pStatListEx->dwFlags |= STATLIST_PERMANENT;
		}
	}
	else // We do not need to keep a value of 0, it's the default if not found
	{
		STATLIST_RemoveStat_6FDB6A30(pStatListEx->pMemPool, pStatsArray, pStat);
	}

	if (nPreviousValue != nNewValue)
	{
		STATLIST_NotifyUnitOfStatValueChange(pItemStatCostTxtRecord, pStatListEx, pUnit, nLayer_StatId, nPreviousValue, nNewValue);
	}
}

// Helper function
static int ComputeStatPercentage(int nValue, struct D2StatListEx* pStatListEx, uint16_t opStatId)
{
	int nOpStatValue = sub_6FDB5830(pStatListEx, D2SLayerStatId_MakeFromStatId(opStatId).nPackedValue);
	if (nOpStatValue)
	{
		return nValue * (nOpStatValue / 100.0);
	}
	return 0;
}

//D2Common.0x6FDB5830
int __fastcall sub_6FDB5830(struct D2StatListEx* pStatListEx, D2SLayerStatId_PackedType nLayer_StatId)
{
	int nAccumulatedValue = 0;

	const uint16_t nStatId = D2SLayerStatId_FromPackedType(nLayer_StatId).nStat;

	struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nStatId);
	if (!pItemStatCostTxtRecord)
	{
		return 0;
	}

	nAccumulatedValue = STATLIST_GetBaseStat_6FDB6340((struct D2StatList *)pStatListEx, nLayer_StatId, 0);

	if (STATLIST_IsExtended((struct D2StatList *)pStatListEx))
	{
		for (struct D2StatList* i = pStatListEx->pMyLastList; i; i = i->pPrevLink)
		{
			if (!(pItemStatCostTxtRecord->dwItemStatFlags & gdwBitMasks[ITEMSTATCOSTFLAGINDEX_DAMAGERELATED]) || !(i->dwFlags & 0x40000000))
			{
				nAccumulatedValue += STATLIST_GetTotalStat_6FDB63E0(i, nLayer_StatId, 0);
			}
		}
	}

	if (!pItemStatCostTxtRecord->bHasOpStatData)
	{
		return nAccumulatedValue;
	}

	int nPreviousOpStatValue = nAccumulatedValue;

	for (int i = 0; i < ARRAY_SIZE(pItemStatCostTxtRecord->pOpStatData); ++i)
	{
		struct D2OpStatData* pOpStatData = &pItemStatCostTxtRecord->pOpStatData[i];
		switch (pOpStatData->nOp)
		{
		case 0:
			return nAccumulatedValue;

		case 1:

			if (pStatListEx->pOwner)
			{
				if (pStatListEx->pOwner->dwUnitType == UNIT_ITEM)
				{
					nPreviousOpStatValue = 0;
					if (pItemStatCostTxtRecord && pStatListEx->pOwner->pStatListEx)
					{
						nPreviousOpStatValue = STATLIST_GetBaseStat_6FDB6340((struct D2StatList *)pStatListEx->pOwner->pStatListEx, D2SLayerStatId_MakeFromStatId(nStatId).nPackedValue, pItemStatCostTxtRecord);
					}
				}

				if (nPreviousOpStatValue)
				{
					nAccumulatedValue += ComputeStatPercentage(nPreviousOpStatValue, pStatListEx, pOpStatData->nStat);
				}
			}
			break;

		case 2:
			if (pStatListEx->dwOwnerType == UNIT_PLAYER || pStatListEx->dwOwnerType == UNIT_MONSTER)
			{
				uint16_t nOpBase = pOpStatData->nOpBase;
				if (nOpBase != 0xFFFF)
				{
					struct D2ItemStatCostTxt* pOpBaseItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nOpBase);
					if (pOpBaseItemStatCostTxtRecord)
					{
						struct D2StatsArray* pStatsArray = STATLIST_IsExtended((struct D2StatList *)pStatListEx) ? &pStatListEx->FullStats : &pStatListEx->Stats;
						
						struct D2Stat* pStat = STATLIST_FindStat_6FDB6920(pStatsArray, D2SLayerStatId_MakeFromStatId(nOpBase).nPackedValue);
						if (pStat)
						{
							int nShiftedVal = pStat->nValue >> pOpBaseItemStatCostTxtRecord->nValShift;
							if (nShiftedVal > 0)
							{
								int nRecursiveValue = sub_6FDB5830(pStatListEx, D2SLayerStatId_MakeFromStatId(pOpStatData->nStat).nPackedValue);
								if (nRecursiveValue)
								{
									nAccumulatedValue += (nShiftedVal * nRecursiveValue) >> pOpStatData->nOpParam;
								}
							}
						}
					}
				}
			}
			break;

		case 3:
			if (pStatListEx->dwOwnerType == UNIT_PLAYER || pStatListEx->dwOwnerType == UNIT_MONSTER)
			{
				uint16_t nOpBase = pOpStatData->nOpBase;
				if (nOpBase != 0xFFFF)
				{
					struct D2ItemStatCostTxt* pOpBaseItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nOpBase);
					if (pOpBaseItemStatCostTxtRecord)
					{
						struct D2StatsArray* pStatsArray = STATLIST_IsExtended((struct D2StatList *)pStatListEx) ? &pStatListEx->FullStats : &pStatListEx->Stats;

						struct D2Stat* pStat = STATLIST_FindStat_6FDB6920(pStatsArray, D2SLayerStatId_MakeFromStatId(nOpBase).nPackedValue);
						if (pStat)
						{
							int nShiftedVal = pStat->nValue >> pOpBaseItemStatCostTxtRecord->nValShift;
							if (nShiftedVal > 0)
							{
								int nRecursiveValue = sub_6FDB5830(pStatListEx, D2SLayerStatId_MakeFromStatId(pOpStatData->nStat).nPackedValue);
								if (nRecursiveValue)
								{
									int nTemp = (nShiftedVal * nRecursiveValue) >> pOpStatData->nOpParam;
									nAccumulatedValue += nTemp * nPreviousOpStatValue / 100.0;
								}
							}
						}
					}
				}
			}
			break;

		case 4:
			if (pStatListEx->pUnit && (pStatListEx->pUnit->dwUnitType == UNIT_PLAYER || pStatListEx->pUnit->dwUnitType == UNIT_MONSTER))
			{
				uint16_t nOpBase = pOpStatData->nOpBase;
				if (nOpBase != 0xFFFF)
				{
					struct D2ItemStatCostTxt* pOpBaseItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nOpBase);
					if (pOpBaseItemStatCostTxtRecord && pStatListEx->pUnit->pStatListEx)
					{
						int nTmp = STATLIST_GetTotalStat_6FDB63E0((struct D2StatList *)pStatListEx->pUnit->pStatListEx, D2SLayerStatId_MakeFromStatId(nOpBase).nPackedValue, pOpBaseItemStatCostTxtRecord) >> pOpBaseItemStatCostTxtRecord->nValShift;
						if (nTmp > 0)
						{
							int nRecursiveValue = sub_6FDB5830(pStatListEx, D2SLayerStatId_MakeFromStatId(pOpStatData->nStat).nPackedValue);
							if (nRecursiveValue)
							{
								nAccumulatedValue += (nTmp * nRecursiveValue) >> pOpStatData->nOpParam;
							}
						}
					}
				}
			}
			break;

		case 5:
			if (pStatListEx->pUnit && (pStatListEx->pUnit->dwUnitType == UNIT_PLAYER || pStatListEx->pUnit->dwUnitType == UNIT_MONSTER))
			{
				uint16_t nOpBase = pOpStatData->nOpBase;
				if (nOpBase != 0xFFFF)
				{
					struct D2ItemStatCostTxt* pOpBaseItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nOpBase);
					if (pOpBaseItemStatCostTxtRecord && pStatListEx->pUnit->pStatListEx)
					{
						int nTmp = STATLIST_GetTotalStat_6FDB63E0((struct D2StatList *)pStatListEx->pUnit->pStatListEx, D2SLayerStatId_MakeFromStatId(nOpBase).nPackedValue, pOpBaseItemStatCostTxtRecord) >> pOpBaseItemStatCostTxtRecord->nValShift;
						if (nTmp > 0)
						{
							int nRecursiveValue = sub_6FDB5830(pStatListEx, D2SLayerStatId_MakeFromStatId(pOpStatData->nStat).nPackedValue);
							if (nRecursiveValue)
							{
								int nTemp = (nTmp * nRecursiveValue) >> pOpStatData->nOpParam;
								nAccumulatedValue += nPreviousOpStatValue * nTemp / 100.0;
							}
						}
					}
				}
			}
			break;

		case 6:
			if (pStatListEx->pOwner && pStatListEx->pOwner->pDrlgAct)
			{
				int nTmp = sub_6FDB5830(pStatListEx, D2SLayerStatId_MakeFromStatId(pOpStatData->nStat).nPackedValue);
				if (nTmp)
				{
					int nBaseTime = 0;
					int nPeriodOfDay = ENVIRONMENT_GetPeriodOfDayFromAct(pStatListEx->pOwner->pDrlgAct, &nBaseTime);
					nAccumulatedValue += ITEMMODS_GetByTimeAdjustment(nTmp, nPeriodOfDay, nBaseTime, NULL, NULL, NULL);
				}
			}
			break;

		case 7:
			if (pStatListEx->pOwner && pStatListEx->pOwner->pDrlgAct)
			{
				int nTmp = sub_6FDB5830(pStatListEx, D2SLayerStatId_MakeFromStatId(pOpStatData->nStat).nPackedValue);
				if (nTmp)
				{
					int nBaseTime = 0;
					int nPeriodOfDay = ENVIRONMENT_GetPeriodOfDayFromAct(pStatListEx->pOwner->pDrlgAct, &nBaseTime);
					nAccumulatedValue += nAccumulatedValue * ITEMMODS_GetByTimeAdjustment(nTmp, nPeriodOfDay, nBaseTime, NULL, NULL, NULL) / 100.0;
				}
			}
			break;

		case 8:
			if (pStatListEx->pOwner && pStatListEx->pOwner->dwUnitType == UNIT_PLAYER)
			{
				struct D2CharStatsTxt* pCharStatsTxtRecord = UNITS_GetCharStatsTxtRecord(pStatListEx->pOwner->dwClassId);
				if (pCharStatsTxtRecord)
				{
					int nTemp = 0;
					struct D2Stat* pStat = STATLIST_FindStat_6FDB6920(&pStatListEx->Stats, D2SLayerStatId_MakeFromStatId(pOpStatData->nStat).nPackedValue);
					if (pStat)
					{
						nTemp = pStat->nValue;
					}

					int nBaseValue = sub_6FDB5830(pStatListEx, D2SLayerStatId_MakeFromStatId(pOpStatData->nStat).nPackedValue) - nTemp;
					if (nBaseValue)
					{
						nAccumulatedValue += nBaseValue * pCharStatsTxtRecord->nManaPerMagic << 6;
					}
				}
			}
			break;

		case 9:
			if (pStatListEx->pOwner && pStatListEx->pOwner->dwUnitType == UNIT_PLAYER)
			{
				struct D2CharStatsTxt* pCharStatsTxtRecord = UNITS_GetCharStatsTxtRecord(pStatListEx->pOwner->dwClassId);
				if (pCharStatsTxtRecord)
				{
					int nBaseStatValue = 0;
					struct D2Stat* pStat = STATLIST_FindStat_6FDB6920(&pStatListEx->Stats, D2SLayerStatId_MakeFromStatId(pOpStatData->nStat).nPackedValue);
					if (pStat)
					{
						nBaseStatValue = pStat->nValue;
					}
					
					int nBonusValue = sub_6FDB5830(pStatListEx, D2SLayerStatId_MakeFromStatId(pOpStatData->nStat).nPackedValue) - nBaseStatValue;
					if (nBonusValue)
					{
						if (nStatId == STAT_MAXSTAMINA)
						{
							nAccumulatedValue += nBonusValue * pCharStatsTxtRecord->nStaminaPerVitality << 6;
						}
						else
						{
							nAccumulatedValue += nBonusValue * pCharStatsTxtRecord->nLifePerVitality << 6;
						}
					}
				}
			}
			break;

		case 11:
			if (nPreviousOpStatValue)
			{
				if (pStatListEx->pOwner && (pStatListEx->pOwner->dwUnitType == UNIT_PLAYER || pStatListEx->pOwner->dwUnitType == UNIT_MONSTER))
				{
					nAccumulatedValue += ComputeStatPercentage(nPreviousOpStatValue, pStatListEx, pOpStatData->nStat);
				}
			}
			break;

		case 13:
			if (pStatListEx->pOwner && pStatListEx->pOwner->dwUnitType == UNIT_ITEM)
			{
				nPreviousOpStatValue = 0;
				if (pStatListEx->pOwner->pStatListEx)
				{
					nPreviousOpStatValue = STATLIST_GetBaseStat_6FDB6340((struct D2StatList *)pStatListEx->pOwner->pStatListEx, D2SLayerStatId_MakeFromStatId(nStatId).nPackedValue, pItemStatCostTxtRecord);
					
					if (nPreviousOpStatValue)
					{
						nAccumulatedValue += ComputeStatPercentage(nPreviousOpStatValue, pStatListEx, pOpStatData->nStat);
					}
				}
			}
			break;

		default:
			break;
		}
	}

	return nAccumulatedValue;
}


//D2Common.0x6FDB6300
int __fastcall STATLIST_FindStatIndex_6FDB6300(struct D2StatsArray* pStatArray, D2SLayerStatId_PackedType nLayer_StatId)
{
	return D2StatsArray_DichotomicSearch(pStatArray, nLayer_StatId);
}

// Helper function
static int STATLIST_ApplyMinValue(int nValue, struct D2ItemStatCostTxt* pItemStatCostTxtRecord, struct D2StatListEx* pStatListEx)
{
	if (pItemStatCostTxtRecord && pItemStatCostTxtRecord->dwItemStatFlags & gdwBitMasks[ITEMSTATCOSTFLAGINDEX_FMIN])
	{
		if (pStatListEx && pStatListEx->pOwner && (pStatListEx->pOwner->dwUnitType == UNIT_PLAYER || pStatListEx->pOwner->dwUnitType == UNIT_MONSTER))
		{
			// Note: looks wrong but this is what the game acutally does.
			if (nValue < pItemStatCostTxtRecord->dwMinAccr)
			{
				nValue = pItemStatCostTxtRecord->dwMinAccr << pItemStatCostTxtRecord->nValShift;
			}
		}
	}
	return nValue;
}

//D2Common.0x6FDB6340
int __fastcall STATLIST_GetBaseStat_6FDB6340(struct D2StatList* pStatList, D2SLayerStatId_PackedType nLayer_StatId, struct D2ItemStatCostTxt* pItemStatCostTxtRecord)
{
	struct D2Stat* pStat = STATLIST_FindStat_6FDB6920(&pStatList->Stats, nLayer_StatId);
	if (pStat)
	{
		return STATLIST_ApplyMinValue(pStat->nValue, pItemStatCostTxtRecord, STATLIST_StatListExCast(pStatList));
	}
	return 0;
}

//D2Common.0x6FDB63E0
int __fastcall STATLIST_GetTotalStat_6FDB63E0(struct D2StatList* pStatList, D2SLayerStatId_PackedType nLayer_StatId, struct D2ItemStatCostTxt* pItemStatCostTxtRecord)
{
	D2_VERIFY(pStatList != nullptr);
	struct D2StatListEx* pStatListEx = STATLIST_StatListExCast(pStatList);
	struct D2StatsArray* pStatArray = pStatListEx ? &pStatListEx->FullStats : &pStatList->Stats;

	struct D2Stat* pStat = STATLIST_FindStat_6FDB6920(pStatArray, nLayer_StatId);
	if (pStat)
	{
		return STATLIST_ApplyMinValue(pStat->nValue, pItemStatCostTxtRecord, pStatListEx);
	}
	return 0;
}

//D2Common.0x6FDB64A0
int __fastcall sub_6FDB64A0(struct D2StatListEx* pStatListEx, D2SLayerStatId_PackedType nLayer_StatId, struct D2ItemStatCostTxt* pItemStatCostTxtRecord, struct D2Unit* pUnit)
{
	int nNewValue = sub_6FDB5830(pStatListEx, nLayer_StatId);

	if (pItemStatCostTxtRecord->bIsBaseOfOtherStatOp)
	{
		if (nNewValue == 0)
		{
			struct D2Stat* pStat = STATLIST_FindStat_6FDB6920(&pStatListEx->FullStats, nLayer_StatId);
			if (pStat)
			{
				STATLIST_SetUnitStatNewValue(pStatListEx, &pStatListEx->FullStats, pStat, nLayer_StatId, nNewValue, pItemStatCostTxtRecord, pUnit);
			}
		}

		bool bUpdate = TRUE;
		
		for (int nCounter = 0; nCounter < 3; ++nCounter)
		{
			if (pItemStatCostTxtRecord->wOpStat[nCounter] == (uint16_t)(-1))
			{
				break;
			}

			const int nOpStat = pItemStatCostTxtRecord->wOpStat[nCounter];
			const struct D2OpStatData* pOpStatData = &pItemStatCostTxtRecord->pOpStatData[nCounter];
			const struct D2SLayerStatId nOpStatLayer_StatId = D2SLayerStatId_MakeFromStatId(nOpStat);
			struct D2ItemStatCostTxt* pOpItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nOpStat);
			struct D2StatsArray* pStatsArray = &pStatListEx->FullStats;
			int nOpStatNewValue = sub_6FDB64A0(pStatListEx, nOpStatLayer_StatId.nPackedValue, pOpItemStatCostTxtRecord, pUnit);
			
			struct D2Stat* pStat = STATLIST_FindStat_6FDB6920(pStatsArray, nOpStatLayer_StatId.nPackedValue);
			if (pStat == nullptr && nOpStatNewValue != 0)
			{
				pStat = STATLIST_InsertStatOrFail_6FDB6970(pStatListEx->pMemPool, pStatsArray, nOpStatLayer_StatId.nPackedValue);
			}

			if (pStat == nullptr)
				continue;

			STATLIST_SetUnitStatNewValue(pStatListEx, pStatsArray, pStat, nOpStatLayer_StatId.nPackedValue, nOpStatNewValue, pOpItemStatCostTxtRecord, pUnit);

			if (nOpStatNewValue)
			{
				switch (pItemStatCostTxtRecord->nOp)
				{
				case 2: // FALLTHROUGH
				case 3:
					if ((pStatListEx->dwOwnerType == UNIT_PLAYER || pStatListEx->dwOwnerType == UNIT_MONSTER) 
						&& pOpStatData->nOpBase != (uint16_t)(-1))
					{
						if (!STATLIST_IsExtended((struct D2StatList *)pStatListEx))
						{
							pStatsArray = &pStatListEx->Stats;
						}

						const struct D2Stat* pOpBaseStat = STATLIST_FindStat_6FDB6920(pStatsArray, D2SLayerStatId_MakeFromStatId(pOpStatData->nOpBase).nPackedValue);
						if (pOpBaseStat && pOpBaseStat->nValue > 0)
						{
							bUpdate = FALSE;
						}
					}
					break;

				case STAT_OP_APPLY_TO_ITEM: // FALLTHROUGH
				case STAT_OP_APPLY_TO_ITEM_PCT:
					if (pStatListEx->pUnit && (pStatListEx->pUnit->dwUnitType == UNIT_PLAYER || pStatListEx->pUnit->dwUnitType == UNIT_MONSTER))
					{
						int nOpBase = pOpStatData->nOpBase;
						if (nOpBase != (uint16_t)(-1))
						{
							struct D2ItemStatCostTxt* pOpItemStatCost = ITEMS_GetItemStatCostTxtRecord(nOpBase);
							if (pOpItemStatCost)
							{
								int nOpStatValue = STATLIST_GetTotalStat_6FDB63E0((struct D2StatList *)pStatListEx->pUnit->pStatListEx, D2SLayerStatId_MakeFromStatId(nOpBase).nPackedValue, pOpItemStatCost);
								bUpdate = nOpStatValue <= 0;
							}
						}
					}
					break;

				case STAT_OP_BY_TIME: // FALLTHROUGH
				case STAT_OP_BY_TIME_PCT:
					if (pStatListEx->dwOwnerType == UNIT_PLAYER || pStatListEx->dwOwnerType == UNIT_MONSTER)
					{
						bUpdate = FALSE;
					}
					break;

				case STAT_OP_ADD_ITEM_STAT_PCT:
					if (pStatListEx->dwOwnerType == UNIT_ITEM)
					{
						bUpdate = FALSE;
					}
					break;

				default:
					bUpdate = FALSE;
					break;

				case 0:
				case 8:
				case 9:
				case 10:
				case 11:
					break;
				}
			}
		}

		if (bUpdate && nNewValue)
		{
			STATLIST_UpdateUnitStat_6FDB6AB0(pStatListEx, nLayer_StatId, nNewValue, pItemStatCostTxtRecord, pUnit);

			for (int i = 0; i < ARRAY_SIZE(pItemStatCostTxtRecord->unk0x5E); ++i)
			{
				const int nStatId = pItemStatCostTxtRecord->unk0x5E[i];

				if (nStatId == (uint16_t)(-1))
				{
					break;
				}

				struct D2ItemStatCostTxt* pLayerStatCostRecord = ITEMS_GetItemStatCostTxtRecord(nStatId);
				const struct D2SLayerStatId layerStatId = D2SLayerStatId_MakeFromStatId(nStatId);
				const int nLayerStatNewValue = sub_6FDB64A0(pStatListEx, layerStatId.nPackedValue, pLayerStatCostRecord, pUnit);
				STATLIST_UpdateUnitStat_6FDB6AB0(pStatListEx, layerStatId.nPackedValue, nLayerStatNewValue, pLayerStatCostRecord, pUnit);
			}
		}
		return nNewValue;
	}

	struct D2Stat* pStat = STATLIST_FindStat_6FDB6920(&pStatListEx->FullStats, nLayer_StatId);
	if (pStat == nullptr)
	{
		if (nNewValue != 0)
		{
			pStat = STATLIST_InsertStatOrFail_6FDB6970(pStatListEx->pMemPool, &pStatListEx->FullStats, nLayer_StatId);
		}
		else
		{
			return 0;
		}
	}

	STATLIST_SetUnitStatNewValue(pStatListEx, &pStatListEx->FullStats, pStat, nLayer_StatId, nNewValue, pItemStatCostTxtRecord, pUnit);

	return nNewValue;
}

//D2Common.0x6FDB6920
struct D2Stat* __fastcall STATLIST_FindStat_6FDB6920(struct D2StatsArray* pStatArray, D2SLayerStatId_PackedType nLayer_StatId)
{
	const int nStatIndex = STATLIST_FindStatIndex_6FDB6300(pStatArray, nLayer_StatId);
	return (nStatIndex >= 0) ? &pStatArray->pStat[nStatIndex] : nullptr;
}

//D2Common.0x6FDB6970
struct D2Stat* __fastcall STATLIST_InsertStatOrFail_6FDB6970(void* pMemPool, struct D2StatsArray* pStatsArray, D2SLayerStatId_PackedType nLayer_StatId)
{
	bool bFoundStatInArray = false;
	int insertionIdx = D2StatsArray_FindInsertionIndex(pStatsArray, nLayer_StatId, &bFoundStatInArray);
	if (bFoundStatInArray)
	{
		return nullptr;
	}
	return D2StatsArray_InsertStat(pMemPool, pStatsArray, nLayer_StatId, insertionIdx);
}

//D2Common.0x6FDB6A30
void __fastcall STATLIST_RemoveStat_6FDB6A30(void* pMemPool, struct D2StatsArray* pStatEx, struct D2Stat* pStat)
{
	int nIndex = pStat - pStatEx->pStat;

	if (nIndex < pStatEx->nStatCount)
	{
		if (nIndex < pStatEx->nStatCount - 1)
		{
			memmove(pStat, pStat + 1, (pStatEx->nStatCount - (nIndex + 1)) * sizeof(struct D2Stat));
		}

		--pStatEx->nStatCount;
		
		D2_ASSERT(pStatEx->nCapacity >= pStatEx->nStatCount);
		if ((pStatEx->nCapacity - pStatEx->nStatCount) > D2StatsArray_nShrinkThreshold)
		{
			pStatEx->nCapacity -= D2StatsArray_nGrowthAmount;
			pStatEx->pStat = (struct D2Stat*)D2_REALLOC_POOL(pMemPool, pStatEx->pStat, pStatEx->nCapacity * sizeof(struct D2Stat));
		}
	}
}

//D2Common.0x6FDB6AB0
void __fastcall STATLIST_UpdateUnitStat_6FDB6AB0(struct D2StatListEx* pStatListEx, D2SLayerStatId_PackedType nLayer_StatId, int nNewValue, struct D2ItemStatCostTxt* pItemStatCostTxtRecord, struct D2Unit* pUnit)
{
	struct D2StatsArray* pStatsArray = &pStatListEx->FullStats;
	bool bFoundStatInArray = false;
	const int insertionIdx = D2StatsArray_FindInsertionIndex(pStatsArray, nLayer_StatId, &bFoundStatInArray);

	struct D2Stat* pStat = nullptr;
	if (bFoundStatInArray)
	{
		pStat = &pStatsArray->pStat[insertionIdx];
	}
	else if (nNewValue != 0)
	{
		pStat = D2StatsArray_InsertStat(pStatListEx->pMemPool, pStatsArray, nLayer_StatId, insertionIdx);
	}

	if (pStat == nullptr)
	{
		return;
	}
	STATLIST_SetUnitStatNewValue(pStatListEx, pStatsArray, pStat, nLayer_StatId, nNewValue, pItemStatCostTxtRecord, pUnit);
}

//D2Common.0x6FDB6C10
void __fastcall sub_6FDB6C10(struct D2StatListEx* pStatListEx, D2SLayerStatId_PackedType nLayer_StatId, int nValue, struct D2Unit* pUnit)
{
	if (!nValue)
	{
		return;
	}

	const uint16_t nStatId = D2SLayerStatId_FromPackedType(nLayer_StatId).nStat;
	struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nStatId);
	if (!pItemStatCostTxtRecord || (pStatListEx->dwFlags & STATLIST_SET))
	{
		return;
	}
	const bool bStatIsDamageRelated = (pItemStatCostTxtRecord->dwItemStatFlags & gdwBitMasks[ITEMSTATCOSTFLAGINDEX_DAMAGERELATED]);

	struct D2StatListEx* pParentStatList = nullptr;
	if (!STATLIST_IsExtended((struct D2StatList *)pStatListEx))
	{
		pParentStatList = (struct D2StatListEx*)(pStatListEx->pParent);
	}
	else
	{
		pParentStatList = pStatListEx;
	}

	while (pParentStatList)
	{
		if (pItemStatCostTxtRecord->bIsBaseOfOtherStatOp || pItemStatCostTxtRecord->bHasOpStatData)
		{
			sub_6FDB64A0(pParentStatList, nLayer_StatId, pItemStatCostTxtRecord, pUnit);
		}
		else
		{
			struct D2Stat* pStat = STATLIST_GetOrInsertStat(pParentStatList->pMemPool, &pParentStatList->FullStats, nLayer_StatId);

			int nNewValue = pStat->nValue + nValue;
			D2_ASSERTM(!(nNewValue < 0 && pItemStatCostTxtRecord->bHasOpApplyingToItem), 
				"Original game does not set STATLIST_PERMANENT if (nNewValue <= 0), while we do when (nNewValue != 0).");
			STATLIST_SetUnitStatNewValue(pParentStatList, &pParentStatList->FullStats, pStat, nLayer_StatId, nNewValue, pItemStatCostTxtRecord, pUnit);
		}
		if ((pParentStatList->dwFlags & STATLIST_SET) || (bStatIsDamageRelated && (pParentStatList->dwFlags & STATLIST_DYNAMIC)))
		{
			break;
		}

		pParentStatList = (struct D2StatListEx*)pParentStatList->pParent;
	}
}

//D2Common.0x6FDB6E30
void __stdcall D2Common_ExpireStatList_6FDB6E30(struct D2StatList* pStatList)
{
	if (!pStatList)
	{
		return;
	}
	struct D2StatList* pParentStatList = pStatList->pParent;
	if (pParentStatList)
	{
		struct D2StatListEx* pParentStatListEx = STATLIST_StatListExCast(pParentStatList);
		if (pParentStatListEx)
		{
			// Unlink the stat from the parent list
			if (pParentStatListEx->pMyLastList == pStatList)
			{
				pParentStatListEx->pMyLastList = pStatList->pPrevLink;
			}

			if (pParentStatListEx->pMyStats == pStatList)
			{
				pParentStatListEx->pMyStats = pStatList->pPrevLink;
			}
		}

		pStatList->pParent = NULL;
	}

	// Unlink the stat from the list
	if (pStatList->pNextLink)
	{
		pStatList->pNextLink->pPrevLink = pStatList->pPrevLink;
	}

	if (pStatList->pPrevLink)
	{
		pStatList->pPrevLink->pNextLink = pStatList->pNextLink;
	}

	pStatList->pPrevLink = NULL;
	pStatList->pNextLink = NULL;

	struct D2Unit* pUnit = pStatList->pUnit;
	pStatList->pUnit = NULL;

	if (!(pStatList->dwFlags & STATLIST_SET))
	{
		struct D2StatListEx* pStatListEx = STATLIST_StatListExCast(pStatList);
		struct D2Unit* pOwner = pStatListEx ? pStatListEx->pOwner : nullptr;
			
		if (pStatListEx && pStatList->dwFlags & STATLIST_PERMANENT)
		{
			struct D2SLayerStatId nLayer_StatIds[16] = {};
			int nCounter = 0;
			for (struct D2Stat* i = pStatListEx->FullStats.pStat; i < &pStatListEx->FullStats.pStat[pStatListEx->FullStats.nStatCount]; ++i)
			{
				struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(i->nStat);
				if (pItemStatCostTxtRecord && pItemStatCostTxtRecord->bHasOpApplyingToItem)
				{
					nLayer_StatIds[nCounter] = *(struct D2SLayerStatId *)i;
					++nCounter;
				}
			}

			for (int i = 0; i < nCounter; ++i)
			{
				struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nLayer_StatIds[i].nStat);
				if (pItemStatCostTxtRecord)
				{
					sub_6FDB64A0(pStatListEx, nLayer_StatIds[i].nPackedValue, pItemStatCostTxtRecord, 0);
				}
			}
		}

		if (pParentStatList)
		{
			struct D2StatsArray* pStatsArray = STATLIST_IsExtended(pStatList) ? &pStatListEx->FullStats : &pStatList->Stats;

			struct D2StatListEx* pParentStatListEx = STATLIST_StatListExCast(pParentStatList);
			// Something looks wrong, seems like some checks were eluded in D2Common.0x6FDB6C10
			// Or inversely, the check above is useless as pParentStatListEx is in fact always an extended statlist
			// if it exists or when STATLIST_SET is set on the current statlist ?
			// In any case, we add an assert here
			D2_ASSERT(pParentStatListEx);

			if (pStatList->dwFlags & STATLIST_DYNAMIC)
			{
				for (struct D2Stat* i = pStatsArray->pStat; i < &pStatsArray->pStat[pStatsArray->nStatCount]; ++i)
				{
					struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(i->nStat);
					if (pItemStatCostTxtRecord && !(pItemStatCostTxtRecord->dwItemStatFlags & gdwBitMasks[ITEMSTATCOSTFLAGINDEX_DAMAGERELATED]))
					{
						sub_6FDB6C10(pParentStatListEx, i->nPackedValue, -i->nValue, pOwner);
					}
				}
			}
			else
			{
				for (struct D2Stat* i = pStatsArray->pStat; i < &pStatsArray->pStat[pStatsArray->nStatCount]; ++i)
				{
					sub_6FDB6C10(pParentStatListEx, i->nPackedValue, -i->nValue, pOwner);
				}
			}
		}

		if (pUnit && pStatList->fpStatRemove)
		{
			pStatList->fpStatRemove(pUnit, pStatList->dwStateNo, pStatList);
		}
	}
}

//D2Common.0x6FDB7030 (#10485)
void __stdcall STATLIST_FreeStatList(struct D2StatList* pStatList)
{
	if (pStatList && !STATLIST_IsExtended(pStatList))
	{
		D2Common_STATLIST_FreeStatListImpl_6FDB7050(pStatList);
	}
}

//D2Common.0x6FDB7050
void __fastcall D2Common_STATLIST_FreeStatListImpl_6FDB7050(struct D2StatList* pStatList)
{

	D2Common_ExpireStatList_6FDB6E30(pStatList);

	if (pStatList->Stats.pStat)
	{
		D2_FREE_POOL(pStatList->pMemPool, pStatList->Stats.pStat);
	}

	struct D2StatListEx* pStatListEx = STATLIST_StatListExCast(pStatList);
	if (pStatListEx)
	{
		struct D2StatList* pPrevious;
		for (struct D2StatList* pCurrent = pStatListEx->pMyLastList; pCurrent != nullptr; pCurrent = pPrevious)
		{
			pPrevious = pCurrent->pPrevLink;
			pCurrent->pParent = nullptr;
			pCurrent->pUnit = nullptr;
			if (STATLIST_IsExtended(pCurrent))
			{
				continue;
			}

			if (pStatListEx->pMyLastList == pCurrent)
			{
				pStatListEx->pMyLastList = pPrevious;
			}

			D2Common_STATLIST_FreeStatListImpl_6FDB7050(pCurrent);

			pPrevious = pStatListEx->pMyLastList;
		}

		if (pStatListEx->FullStats.pStat)
		{
			D2_FREE_POOL(pStatListEx->pMemPool, pStatListEx->FullStats.pStat);
		}

		if (pStatListEx->ModStats.pStat)
		{
			D2_FREE_POOL(pStatListEx->pMemPool, pStatListEx->ModStats.pStat);
		}

		D2_FREE_POOL(pStatListEx->pMemPool, pStatListEx->StatFlags);
	}

	D2_FREE_POOL(pStatList->pMemPool, pStatList);
}

//D2Common.0x6FDB7110 (#10527)
void __stdcall STATLIST_FreeStatListEx(struct D2Unit* pUnit)
{
	if (pUnit->pStatListEx)
	{
		if (STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx))
		{
			D2Common_STATLIST_FreeStatListImpl_6FDB7050((struct D2StatList *)pUnit->pStatListEx);
		}

		pUnit->pStatListEx = NULL;
	}
}

//D2Common.0x6FDB7140 (#10470)
struct D2StatList* __stdcall STATLIST_AllocStatList(void* pMemPool, uint32_t fFilter, uint32_t dwTimeout, int nUnitType, D2UnitGUID nUnitGUID)
{
	struct D2StatList* pStatList = D2_CALLOC_STRC_POOL(pMemPool, struct D2StatList);

	pStatList->dwOwnerType = nUnitType;
	pStatList->dwOwnerId = nUnitGUID;
	pStatList->pMemPool = pMemPool;
	pStatList->dwFlags = fFilter;
	pStatList->dwExpireFrame = dwTimeout;

	return pStatList;
}

//D2Common.0x6FDB7190 (#10526)
void __stdcall STATLIST_AllocStatListEx(struct D2Unit* pUnit, char nFlags, StatListValueChangeFunc pfOnValueChanged, struct D2Game* pGame)
{
	STATLIST_FreeStatListEx(pUnit);

	struct D2StatListEx* pStatListEx = D2_CALLOC_STRC_POOL(pUnit->pMemoryPool, struct D2StatListEx);

	pStatListEx->pMemPool = pUnit->pMemoryPool;
	pStatListEx->dwOwnerType = pUnit->dwUnitType;
	pStatListEx->dwOwnerId = pUnit->dwUnitId;
	pStatListEx->pOwner = pUnit;
	pStatListEx->pfOnValueChanged = pfOnValueChanged;
	pStatListEx->pGame = pGame;
	pStatListEx->dwFlags = (nFlags & STATLIST_BASIC) | STATLIST_EXTENDED;
	pStatListEx->StatFlags = (uint32_t*)D2_CALLOC_POOL(pUnit->pMemoryPool, 2 * sizeof(uint32_t) * (sgptDataTables->nStatesTxtRecordCount + 31) / 32);

	pUnit->pStatListEx = pStatListEx;
}

//D2Common.0x6FDB7260 (#10471)
int __stdcall STATLIST_GetOwnerType(struct D2StatList* pStatList)
{
	if (pStatList)
	{
		return pStatList->dwOwnerType;
	}

	return 6;
}

//D2Common.0x6FD912D0 (#10472)
D2UnitGUID __stdcall STATLIST_GetOwnerGUID(struct D2StatList* pStatList)
{
	if (pStatList)
	{
		return pStatList->dwOwnerId;
	}

	REMOVE_LATER_Trace("STATLIST_GetOwnerGUID: NULL pointer");
	return 0;
}

//D2Common.0x6FDB7280 (#11304)
int __stdcall STATLIST_GetBaseStatsCount(struct D2StatList* pStatList)
{
	if (pStatList)
	{
		return pStatList->Stats.nStatCount;
	}

	return 0;
}

//D2Common.0x6FDB72A0 (#11305)
int __stdcall STATLIST_GetFullStatsCountFromUnit(struct D2Unit* pUnit)
{
	if (pUnit && pUnit->pStatListEx)
	{
		return pUnit->pStatListEx->FullStats.nStatCount;
	}

	return 0;
}

//D2Common.0x6FDB72C0 (#10478)
void __stdcall STATLIST_SetState(struct D2StatList* pStatList, int nState)
{
	if (pStatList)
	{
		pStatList->dwStateNo = nState;
	}
}

//D2Common.0x6FDB72E0 (#10479)
int __stdcall STATLIST_GetState(struct D2StatList* pStatList)
{
	if (pStatList)
	{
		return pStatList->dwStateNo;
	}

	return 0;
}

//D2Common.0x6FDB7300 (#10528)
void __stdcall STATLIST_SetExpireFrame(struct D2StatList* pStatList, int nExpireFrame)
{
	if (pStatList)
	{
		if (nExpireFrame > 0)
		{
			pStatList->dwFlags |= STATLIST_NEWLENGTH;
		}

		pStatList->dwExpireFrame = nExpireFrame;
	}
}

//D2Common.0x6FDB7320 (#10529)
int __stdcall STATLIST_GetExpireFrame(struct D2StatList* pStatList)
{
	if (pStatList)
	{
		return pStatList->dwExpireFrame;
	}

	REMOVE_LATER_Trace("STATLIST_GetExpireFrame: NULL pointer");
	return 0;
}

//D2Common.0x6FDB7340 (#10475)
void __stdcall D2COMMON_10475_PostStatToStatList(struct D2Unit* pUnit, struct D2StatList* pStatList, BOOL bResetFlag)
{
	struct D2StatListEx* pUnitStatListEx = STATLIST_StatListExCast((struct D2StatList *)pUnit->pStatListEx);
	if (pUnitStatListEx)
	{
		D2Common_ExpireStatList_6FDB6E30(pStatList);
		struct D2StatListEx* pCurrentStatList = pUnitStatListEx;

		while (pCurrentStatList && (pStatList != (struct D2StatList *)pCurrentStatList))
		{
			pCurrentStatList = (struct D2StatListEx*)pCurrentStatList->pParent;
		}
		if (pCurrentStatList)
		{
			// pCurStatList already present, skip
			return;
		}


		struct D2StatListEx* pStatListEx = STATLIST_StatListExCast(pStatList);
		if (pStatList->dwFlags & STATLIST_TEMPONLY)
		{
			pUnit->pStatListEx->dwFlags |= STATLIST_NEWLENGTH;
		}

		if (pStatList->dwFlags & STATLIST_SET)
		{
			pStatList->pPrevLink = pUnit->pStatListEx->pMyStats;

			if (pUnit->pStatListEx->pMyStats)
			{
				pUnit->pStatListEx->pMyStats->pNextLink = pStatList;
			}

			pStatList->pNextLink = NULL;
			pUnit->pStatListEx->pMyStats = pStatList;
			pStatList->pParent = (struct D2StatList*)pUnit->pStatListEx;
			pStatList->pUnit = pUnit;
		}
		else
		{
			pStatList->pPrevLink = pUnit->pStatListEx->pMyLastList;
			if (pUnit->pStatListEx->pMyLastList)
			{
				pUnit->pStatListEx->pMyLastList->pNextLink = pStatList;
			}

			pStatList->pParent = (struct D2StatList*)pUnit->pStatListEx;
			pUnit->pStatListEx->pMyLastList = pStatList;
			pStatList->pUnit = pUnit;

			struct D2Unit* pOwner = nullptr;

			if (pStatListEx)
			{
				pOwner = pStatListEx->pOwner;

				int nCounter = 0;
				struct D2SLayerStatId nLayer_StatIds[16] = {};
				for (struct D2Stat* pCurStat = pStatListEx->FullStats.pStat; pCurStat < &pStatListEx->FullStats.pStat[pStatListEx->FullStats.nStatCount]; ++pCurStat)
				{
					struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(pCurStat->nStat);
					if (pItemStatCostTxtRecord && pItemStatCostTxtRecord->bHasOpApplyingToItem)
					{
						nLayer_StatIds[nCounter] = *(struct D2SLayerStatId *)pCurStat;
						++nCounter;
					}
				}

				for (int i = 0; i < nCounter; ++i)
				{
					struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nLayer_StatIds[i].nStat);
					if (pItemStatCostTxtRecord)
					{
						sub_6FDB64A0(pStatListEx, nLayer_StatIds[i].nPackedValue, pItemStatCostTxtRecord, 0);
					}
				}
			}

			struct D2StatsArray* pStatsArray = pStatListEx ? &pStatListEx->FullStats : &pStatList->Stats;
			if (bResetFlag)
			{
				pStatList->dwFlags &= ~STATLIST_DYNAMIC;

				for (struct D2Stat* i = pStatsArray->pStat; i < &pStatsArray->pStat[pStatsArray->nStatCount]; ++i)
				{
					sub_6FDB6C10(pUnitStatListEx, i->nPackedValue, i->nValue, pOwner);
				}
			}
			else
			{
				pStatList->dwFlags |= STATLIST_DYNAMIC;

				for (struct D2Stat* i = pStatsArray->pStat; i < &pStatsArray->pStat[pStatsArray->nStatCount]; ++i)
				{
					struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(i->nStat);
					if (pItemStatCostTxtRecord && !(pItemStatCostTxtRecord->dwItemStatFlags & gdwBitMasks[ITEMSTATCOSTFLAGINDEX_DAMAGERELATED]))
					{
						sub_6FDB6C10(pUnitStatListEx, i->nPackedValue, i->nValue, pOwner);
					}
				}
			}
		}
	}
}

//D2Common.0x6FDB7560 (#10464)
void __stdcall STATLIST_AddStat(struct D2StatList* pStatList, int nStatId, int nValue, uint16_t nLayer)
{
	if (!pStatList || !nValue)
	{
		return;
	}

	struct D2StatsArray* pStatsArray = &pStatList->Stats;

	struct D2Stat* pStat = STATLIST_FindStat_6FDB6920(pStatsArray, D2SLayerStatId_Make(nLayer, nStatId).nPackedValue);

	if (!pStat)
	{
		pStat = STATLIST_InsertStatOrFail_6FDB6970(pStatList->pMemPool, pStatsArray, D2SLayerStatId_Make(nLayer, nStatId).nPackedValue);
	}

	pStat->nValue += nValue;

	if (pStat->nValue == 0)
	{
		STATLIST_RemoveStat_6FDB6A30(pStatList->pMemPool, pStatsArray, pStat);
	}

	sub_6FDB6C10((struct D2StatListEx*)pStatList, D2SLayerStatId_Make(nLayer, nStatId).nPackedValue, nValue, 0);
	struct D2StatListEx* pStatListEx = STATLIST_StatListExCast(pStatList);
	if (pStatListEx)
	{
		if (pStatList->dwOwnerType == UNIT_PLAYER)
		{
			STATLIST_InsertStatModOrFail_6FDB7690((struct D2StatList *)pStatListEx, D2SLayerStatId_Make(nLayer,nStatId).nPackedValue);
		}
	}
}

//D2Common.0x6FDB7690
void __fastcall STATLIST_InsertStatModOrFail_6FDB7690(struct D2StatList* pStatList, D2SLayerStatId_PackedType nLayer_StatId)
{
	struct D2StatListEx* pStatListEx = STATLIST_StatListExCast(pStatList);
	if (pStatListEx)
	{
		uint16_t nStatId = D2SLayerStatId_FromPackedType(nLayer_StatId).nStat;

		switch (nStatId)
		{
		case STAT_HITPOINTS:
		case STAT_MANA:
		case STAT_STAMINA:
		case STAT_EXPERIENCE:
		case STAT_GOLD:
			return;
		default:
			break;
		}

		struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nStatId);
		if (pItemStatCostTxtRecord && pItemStatCostTxtRecord->dwItemStatFlags & gdwBitMasks[ITEMSTATCOSTFLAGINDEX_SAVED])
		{
			bool alreadyInArray = false;
			int insertIdx = D2ModStatsArray_FindInsertionIndex(&pStatListEx->ModStats, nLayer_StatId, &alreadyInArray);
			if (!alreadyInArray)
				D2ModStatsArray_InsertStat(pStatListEx->pMemPool, &pStatListEx->ModStats, nLayer_StatId, insertIdx);
		}
	}
}

//D2Common.0x6FDB77B0 (#10463)
BOOL __stdcall STATLIST_SetStat(struct D2StatList* pStatList, int nStatId, int nValue, uint16_t nLayer)
{
	return STATLIST_SetBaseStat(pStatList, nStatId, nValue, nLayer, NULL);
}

//D2Common.0x6FDB7910 (#10465)
void __stdcall STATLIST_SetStatIfListIsValid(struct D2StatList* pStatList, int nStatId, int nValue, uint16_t nLayer)
{
	if (pStatList)
	{
		STATLIST_SetStat(pStatList, nStatId, nValue, nLayer);
	}
}

//D2Common.0x6FDB7930 (#11294)
BOOL __stdcall STATLIST_SetBaseStat(struct D2StatList* pStatList, int nStatId, int nValue, uint16_t nLayer, struct D2Unit* pUnit)
{
	if (!pStatList)
	{
		return FALSE;
	}

	const struct D2SLayerStatId nLayer_StatId = D2SLayerStatId_Make(nLayer, nStatId);
	struct D2StatsArray* pBaseStatsArray = &pStatList->Stats;
	bool bFoundStatInArray = false;
	const int insertionIdx = D2StatsArray_FindInsertionIndex(pBaseStatsArray, nLayer_StatId.nPackedValue, &bFoundStatInArray);
	if (!bFoundStatInArray)
	{
		if (nValue == 0) // Early exit, we do not keep stats with a value of 0
		{
			return FALSE;
		}
		D2StatsArray_InsertStat(pStatList->pMemPool, pBaseStatsArray, nLayer_StatId.nPackedValue, insertionIdx);
	}
	struct D2Stat* pStat = &pBaseStatsArray->pStat[insertionIdx];

	const int nDiffValue = nValue - pStat->nValue;
	if (nDiffValue == 0)
	{
		return FALSE;
	}

	if (nValue != 0)
	{
		pStat->nValue = nValue;
	}
	else
	{
		STATLIST_RemoveStat_6FDB6A30(pStatList->pMemPool, pBaseStatsArray, pStat);
	}

	sub_6FDB6C10((struct D2StatListEx*)pStatList, nLayer_StatId.nPackedValue, nDiffValue, pUnit);
	struct D2StatListEx* pStatListEx = STATLIST_StatListExCast(pStatList);
	if (pStatListEx)
	{
		if (pStatList->dwOwnerType == UNIT_PLAYER)
		{
			STATLIST_InsertStatModOrFail_6FDB7690((struct D2StatList *)pStatListEx, nLayer_StatId.nPackedValue);
		}
	}

	return TRUE;

}

//D2Common.0x6FDB7A90 (#11295)
void __stdcall STATLIST_SetBaseStat2(struct D2StatList* pStatList, int nStatId, int nValue, uint16_t nLayer, struct D2Unit* pUnit)
{
	if (pStatList)
	{
		STATLIST_SetBaseStat(pStatList, nStatId, nValue, nLayer, pUnit);
	}
}

//D2Common.0x6FDB7AB0 (#10517)
void __stdcall STATLIST_SetUnitStat(struct D2Unit* pUnit, int nStatId, int nValue, uint16_t nLayer)
{
	if (STATLIST_SetStat((struct D2StatList *)pUnit->pStatListEx, nStatId, nValue, nLayer))
	{
		if (pUnit->dwUnitType == UNIT_PLAYER)
		{
			STATLIST_InsertStatModOrFail_6FDB7690((struct D2StatList *)pUnit->pStatListEx, D2SLayerStatId_Make(nLayer, nStatId).nPackedValue);
		}
	}
}

//D2Common.0x6FDB7B00 (#10518)
void __stdcall STATLIST_AddUnitStat(struct D2Unit* pUnit, int nStatId, int nValue, uint16_t nLayer)
{
	if (nValue)
	{
		STATLIST_AddStat((struct D2StatList *)pUnit->pStatListEx, nStatId, nValue, nLayer);
	}
}

//D2Common.0x6FDB7B30 (#10521)
int __stdcall STATLIST_GetUnitBaseStat(struct D2Unit* pUnit, int nStatId, uint16_t nLayer)
{
	if (!pUnit || !pUnit->pStatListEx)
	{
		return 0;
	}
	struct D2StatList* pStatList = (struct D2StatList *)pUnit->pStatListEx;

	struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nStatId);
	if (!pItemStatCostTxtRecord)
	{
		return 0;
	}

	return STATLIST_GetBaseStat_6FDB6340(pStatList, D2SLayerStatId_Make(nLayer, nStatId).nPackedValue, pItemStatCostTxtRecord);
}

// Helper function
// Different than STATLIST_GetStatValue in that it may use FullStats
static int32_t __stdcall STATLIST_GetTotalStatValue(struct D2StatList* pStatList, int nStatId, uint16_t nLayer)
{
	if (!pStatList)
	{
		return 0;
	}

	struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nStatId);
	if (!pItemStatCostTxtRecord)
	{
		return 0;
	}
	return STATLIST_GetTotalStat_6FDB63E0(pStatList, D2SLayerStatId_Make(nLayer, nStatId).nPackedValue, pItemStatCostTxtRecord);
}

//D2Common.0x6FDB7C30 (#10519)
int32_t __stdcall STATLIST_UnitGetStatValue(const struct D2Unit* pUnit, int nStatId, uint16_t nLayer)
{
	return STATLIST_GetTotalStatValue((struct D2StatList *)pUnit->pStatListEx, nStatId, nLayer);
}

//D2Common.0x6FDB7E30 (#10520)
// A little history for those wondering why it returns the exact same thing as STATLIST_UnitGetStatValue
// There have been a few reworks of the stat system over the different versions of the game.
// In the versions 1.08 and below, the "base" stats and "item/skill" stats were in two seperate lists.
// Then in 1.09, both lists were merged into the same system, resulting in both functions doing the same thing.
// This can easily be tracked by checking the function responsible for computing the defense rate and its usage of both functions.
// - 1.00 to 1.05 : UNITS_GetDefenseRate#10426. STATLIST_UnitGetStatValue#10497. STATLIST_UnitGetItemStatOrSkillStatValue#10498.
// - 1.08 to 1.10f: UNITS_GetDefenseRate#10431. STATLIST_UnitGetStatValue#10519. STATLIST_UnitGetItemStatOrSkillStatValue#10520.
int32_t __stdcall STATLIST_UnitGetItemStatOrSkillStatValue(struct D2Unit* pUnit, int nStatId, uint16_t nLayer)
{
	return STATLIST_UnitGetStatValue(pUnit, nStatId, nLayer);
}


//D2Common.0x6FDB7D40 (#10466)
int __stdcall STATLIST_GetStatValue(struct D2StatList* pStatList, int nStatId, uint16_t nLayer)
{
	if (!pStatList)
	{
		return 0;
	}

	struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nStatId);
	if (!pItemStatCostTxtRecord)
	{
		return 0;
	}

	struct D2Stat* pStat = STATLIST_FindStat_6FDB6920(&pStatList->Stats, D2SLayerStatId_Make(nLayer, nStatId).nPackedValue);
	if (pStat)
	{
		return STATLIST_ApplyMinValue(pStat->nValue, pItemStatCostTxtRecord, STATLIST_StatListExCast(pStatList));
	}

	return 0;
}


//D2Common.0x6FDB7F40 (#10522)
int __stdcall STATLIST_GetUnitStatBonus(struct D2Unit* pUnit, int nStatId, uint16_t nLayer)
{


	if (!pUnit->pStatListEx)
	{
		return 0;
	}
	struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nStatId);

	if (!pItemStatCostTxtRecord)
	{
		return 0;
	}

	struct D2StatList* pStatList = (struct D2StatList*)pUnit->pStatListEx;
	struct D2StatListEx* pStatListEx = STATLIST_StatListExCast(pStatList);

	int nValue = 0;
	struct D2StatsArray* pStatsArray = pStatListEx ? &pStatListEx->FullStats : &pStatList->Stats;
	{
		const struct D2Stat* pStat = STATLIST_FindStat_6FDB6920(pStatsArray, D2SLayerStatId_Make(nLayer, nStatId).nPackedValue);
		if (pStat)
		{
			nValue = STATLIST_ApplyMinValue(pStat->nValue, pItemStatCostTxtRecord, pStatListEx);
		}
	}

	struct D2StatsArray* pBaseStatsArray = &pStatList->Stats;
	{
		const struct D2Stat* pStat = STATLIST_FindStat_6FDB6920(pBaseStatsArray, D2SLayerStatId_Make(nLayer, nStatId).nPackedValue);
		if (pStat)
		{
			int nBaseValue = STATLIST_ApplyMinValue(pStat->nValue, pItemStatCostTxtRecord, pStatListEx);
			return nValue - nBaseValue;
		}
	}

	return nValue;
}

//D2Common.0x6FDB80C0 (#10515)
void __stdcall STATLIST_DeactivateTemporaryStates(struct D2Unit* pUnit)
{
	if (pUnit->pStatListEx == nullptr || !(pUnit->pStatListEx->dwFlags & STATLIST_NEWLENGTH))
	{
		return;
	}

	struct D2StatList* pPrevious;
	for (struct D2StatList* pCurrent = pUnit->pStatListEx->pMyLastList; pCurrent != nullptr; pCurrent = pPrevious)
	{
		pPrevious = pCurrent->pPrevLink;
		if (!(pCurrent->dwFlags & STATLIST_TEMPONLY))
		{
			continue;
		}

		if (pCurrent->dwStateNo)
		{
			STATES_ToggleState(pUnit, pCurrent->dwStateNo, FALSE);
		}

		if (!STATLIST_IsExtended(pCurrent))
		{
			D2Common_STATLIST_FreeStatListImpl_6FDB7050(pCurrent);
		}

		pPrevious = pUnit->pStatListEx->pMyLastList;
	}

	pUnit->pStatListEx->dwFlags &= ~STATLIST_NEWLENGTH;
}

//D2Common.0x6FDB8120 (#10467)
int __stdcall D2Common_10467(struct D2StatList* pStatList, int nStat)
{
	if (pStatList && nStat < pStatList->Stats.nStatCount)
	{
		return pStatList->Stats.pStat[nStat].nValue;
	}

	return 0;
}

//D2Common.0x6FDB8150 (#10468)
void __stdcall STATLIST_RemoveAllStats(struct D2StatList* pStatList)
{
	if (pStatList == nullptr)
	{
		return;
	}

	while (pStatList->Stats.nStatCount > 0)
	{
		STATLIST_SetStat(pStatList, pStatList->Stats.pStat->nStat, 0, pStatList->Stats.pStat->nLayer);
	}
}

//D2Common.0x6FDB8190
struct D2StatList* __stdcall D2Common_GetStateFromStatListEx_6FDB8190(struct D2StatListEx* pStatListEx, int nStateId)
{
	if (pStatListEx && nStateId)
	{
		struct D2StatList* pStatList = STATLIST_IsExtended((struct D2StatList *)pStatListEx) ? pStatListEx->pMyLastList : nullptr;
		while (pStatList && pStatList->dwStateNo != nStateId)
		{
			pStatList = pStatList->pPrevLink;
		}

		if (pStatList)
		{
			return pStatList;
		}

		pStatList = pStatListEx->pMyStats;
		while (pStatList && pStatList->dwStateNo != nStateId)
		{
			pStatList = pStatList->pPrevLink;
		}
		return pStatList;
	}

	return NULL;
}

//D2Common.0x6FDB81E0 (#10480)
struct D2StatList* __stdcall STATLIST_GetStatListFromUnitAndState(struct D2Unit* pUnit, int nState)
{
	if (pUnit->pStatListEx && STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx))
	{
		return D2Common_GetStateFromStatListEx_6FDB8190(pUnit->pStatListEx, nState);
	}

	return nullptr;
}

//D2Common.0x6FDB8200 (#10482)
struct D2StatList* __stdcall STATLIST_GetStatListFromFlag(struct D2StatList* pStatList, int nFlag)
{
	if (!pStatList)
	{
		return nullptr;
	}

	pStatList = pStatList->pPrevLink;
	while (pStatList && !(nFlag & pStatList->dwFlags))
	{
		pStatList = pStatList->pPrevLink;
	}
	return pStatList;
}

//D2Common.0x6FDB8230 (#10481)
struct D2StatList* __stdcall STATLIST_GetStatListFromUnitAndFlag(struct D2Unit* pUnit, int nFlag)
{
	if (pUnit->pStatListEx && STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx))
	{
		struct D2StatList* pStatList = pStatList = nFlag & STATLIST_SET ? pUnit->pStatListEx->pMyStats : pUnit->pStatListEx->pMyLastList;
		nFlag &= ~STATLIST_SET;

		while (pStatList && !(nFlag & pStatList->dwFlags))
		{
			pStatList = pStatList->pPrevLink;
		}

		return pStatList;
	}

	return NULL;
}

//D2Common.0x6FDB8270 (#10483)
struct D2StatList* __stdcall STATLIST_GetStatListFromUnitStateOrFlag(struct D2Unit* pUnit, int nState, int nFlag)
{
	if (pUnit->pStatListEx && STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx))
	{
		if (nState)
		{
			return D2Common_GetStateFromStatListEx_6FDB8190(pUnit->pStatListEx, nState);
		}

		return STATLIST_GetStatListFromUnitAndFlag(pUnit, nFlag);
	}

	return NULL;
}

//D2Common.0x6FDB82C0 (#10484)
struct D2StatList* __stdcall STATLIST_GetStatListFromUnitStateAndFlag(struct D2Unit* pUnit, int nState, int nFlag)
{
	if (pUnit->pStatListEx && STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx))
	{
		struct D2StatList* pStatList = nFlag & STATLIST_SET ? pUnit->pStatListEx->pMyStats : pUnit->pStatListEx->pMyLastList;
		nFlag &= ~STATLIST_SET;
		while (pStatList && (pStatList->dwStateNo != nState || nFlag && !(nFlag & pStatList->dwFlags)))
		{
			pStatList = pStatList->pPrevLink;
		}

		return pStatList;
	}

	return NULL;
}

//D2Common.0x6FDB8310 (#10523)
void __stdcall STATLIST_MergeStatLists(struct D2Unit* pTarget, struct D2Unit* pUnit, BOOL bType)
{
	if (pTarget && pUnit && pUnit->pStatListEx)
	{
		if (pUnit->dwUnitType == UNIT_ITEM && (ITEMS_GetBodyLocation(pUnit) == BODYLOC_SWRARM || ITEMS_GetBodyLocation(pUnit) == BODYLOC_SWLARM))
		{
			D2Common_ExpireStatList_6FDB6E30((struct D2StatList *)pUnit->pStatListEx);
		}
		else if (pUnit->pStatListEx->pUnit == pTarget)
		{
			if (bType && (pUnit->pStatListEx->dwFlags & STATLIST_DYNAMIC))
			{
				D2Common_11274(pTarget, pUnit);
			}
			else if (!bType && !(pUnit->pStatListEx->dwFlags & STATLIST_DYNAMIC))
			{
				D2Common_11275(pTarget, pUnit);
			}
		}
		else
		{
			D2COMMON_10475_PostStatToStatList(pTarget, (struct D2StatList *)pUnit->pStatListEx, bType);
			pUnit->pStatListEx->pUnit = pTarget;
		}
	}
}


//D2Common.0x6FDB83A0 (#10535)
struct D2Unit* __stdcall STATLIST_GetOwner(struct D2Unit* pUnit, BOOL* pStatNotDynamic)
{
	if (!pUnit || !pUnit->pStatListEx || !pUnit->pStatListEx->pParent || !STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx->pParent))
	{
		if (pStatNotDynamic)
		{
			*pStatNotDynamic = FALSE;
		}
		return NULL;
	}

	if (pStatNotDynamic)
	{
		*pStatNotDynamic = !(pUnit->pStatListEx->dwFlags & STATLIST_DYNAMIC);
	}
	return ((struct D2StatListEx*)pUnit->pStatListEx->pParent)->pOwner;
}

//D2Common.0x6FDB8420 (#10512)
void __stdcall D2Common_10512(struct D2Unit* pUnit1, struct D2Unit* pUnit2, int nStatId, void (__fastcall* pfCallback)(struct D2Unit*, int, int, struct D2Unit*))
{
	if (!pUnit1 || !pUnit1->pStatListEx || !STATLIST_IsExtended((struct D2StatList *)pUnit1->pStatListEx))
	{
		return;
	}

	const struct D2SLayerStatId nLayerId = D2SLayerStatId_MakeFromStatId(nStatId);

	if (D2ModStatsArray_DichotomicSearch(&pUnit1->pStatListEx->ModStats, nLayerId.nPackedValue) < 0)
	{
		return;
	}

	struct D2Stat* pBaseStat = STATLIST_FindStat_6FDB6920(&pUnit1->pStatListEx->Stats, nLayerId.nPackedValue);
	if (pBaseStat)
	{
		pfCallback(pUnit1, nStatId, pBaseStat->nValue, pUnit2);
	}
}

//D2Common.0x6FDB84E0 (#10513)
void __stdcall D2Common_10513(struct D2Unit* pUnit1, struct D2Unit* pUnit2, void (__fastcall* pfCallback)(struct D2Unit*, int, int, struct D2Unit*))
{
	if (!pUnit1 || (!pUnit2 && pfCallback) || !pUnit1->pStatListEx || !STATLIST_IsExtended((struct D2StatList *)pUnit1->pStatListEx))
	{
		return;
	}
	struct D2StatListEx* pUnit1StatList = pUnit1->pStatListEx;
	for (int i = 0; i < pUnit1StatList->ModStats.nStatCount; ++i)
	{
		const struct D2SLayerStatId* pModStat = &pUnit1StatList->ModStats.pStat[i];
		int nBaseStatValue = 0;
		struct D2Stat* pBaseStat = STATLIST_FindStat_6FDB6920(&pUnit1StatList->Stats, pModStat->nPackedValue);
		if (pBaseStat)
		{
			nBaseStatValue = pBaseStat->nValue;
		}

		pfCallback(pUnit1, pModStat->nStat, nBaseStatValue, pUnit2);
	}
}

//D2Common.0x6FDB85D0 (#10511)
void __stdcall STATLIST_FreeModStats(struct D2Unit* pUnit)
{
	if (pUnit && pUnit->pStatListEx && STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx))
	{
		if (pUnit->pStatListEx->ModStats.pStat)
		{
			D2_FREE_POOL(pUnit->pStatListEx->pMemPool, pUnit->pStatListEx->ModStats.pStat);
			pUnit->pStatListEx->ModStats.pStat = NULL;
		}

		pUnit->pStatListEx->ModStats.nCapacity = 0;
		pUnit->pStatListEx->ModStats.nStatCount = 0;
	}
}

//D2Common.0x6FDB8620 (#10562)
int __stdcall STATLIST_GetUnitAlignment(struct D2Unit* pUnit)
{
	if (!pUnit || !pUnit->pStatListEx)
	{
		return UNIT_ALIGNMENT_EVIL;
	}

	if (pUnit->dwUnitType != UNIT_PLAYER && pUnit->dwUnitType != UNIT_MONSTER)
	{
		return UNIT_ALIGNMENT_GOOD;
	}

	struct D2StatListEx* pStatListEx = STATLIST_StatListExCast((struct D2StatList *)pUnit->pStatListEx);
	if (pStatListEx)
	{
		struct D2StatList* pAlignmentStateList = D2Common_GetStateFromStatListEx_6FDB8190(pUnit->pStatListEx, STATE_ALIGNMENT);
		if (pAlignmentStateList)
		{
			return STATLIST_GetTotalStatValue_Layer0(pAlignmentStateList, STAT_ALIGNMENT);
		}
	}

	return UNIT_ALIGNMENT_EVIL;
}

//D2Common.0x6FDB8750 (#10534)
void __stdcall D2Common_10534(struct D2Unit* pUnit)
{
	if (pUnit && pUnit->pStatListEx)
	{
		pUnit->pStatListEx->dwFlags |= STATLIST_UNK_0x100;
	}
}

//D2Common.0x6FDB8770 (#10530)
BOOL __stdcall D2COMMON_10530_D2CheckStatlistFlagDMGRed(struct D2Unit* pUnit)
{
	if (pUnit && pUnit->pStatListEx)
	{
		return pUnit->pStatListEx->dwFlags & STATLIST_UNK_0x100;
	}

	return FALSE;
}

//D2Common.0x6FDB87A0 (#10532)
int __stdcall STATLIST_GetTotalStatValue_Layer0(struct D2StatList* pStatListEx, int nStatId)
{
	return STATLIST_GetTotalStatValue((struct D2StatList *)pStatListEx, nStatId, 0);
}

//D2Common.0x6FDB8890 (#10533)
void __stdcall STATLIST_RemoveAllStatsFromOverlay(struct D2Unit* pUnit)
{

	if (pUnit && pUnit->pStatListEx)
	{
		pUnit->pStatListEx->dwFlags &= ~STATLIST_UNK_0x100;

		struct D2StatListEx* pStatListEx = STATLIST_StatListExCast((struct D2StatList *)pUnit->pStatListEx);
		if (pStatListEx)
		{
			struct D2StatList* pCurStatList = pStatListEx->pMyLastList;
			while (pCurStatList && !(pCurStatList->dwFlags & STATLIST_OVERLAY))
			{
				pCurStatList = pCurStatList->pPrevLink;
			}
			if(pCurStatList)
			{
				STATLIST_RemoveAllStats(pCurStatList);
			}
		}
	}
}

//D2Common.0x6FDB8900
void __stdcall D2Common_STATES_ToggleState_6FDB8900(struct D2Unit* pUnit, int nState, BOOL bSet)
{
	
	if (pUnit && pUnit->pStatListEx && STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx))
	{
		const uint32_t dwStateBitMask = gdwBitMasks[nState % 32];
		const bool bStateBitChanged = BITMANIP_SetBitsValueForMask_uint32_t(&pUnit->pStatListEx->StatFlags[nState / 32], dwStateBitMask, bSet);
		if (!bStateBitChanged)
		{
			return;
		}
		const size_t states2Offset = (sgptDataTables->nStatesTxtRecordCount + 31) / 32;
		pUnit->pStatListEx->StatFlags[nState / 32 + states2Offset] |= dwStateBitMask;

		struct D2StatesTxt* pStatesTxtRecord = DATATBLS_GetStatesTxtRecord(nState);
		if (pStatesTxtRecord)
		{
			bool bStateMaskDisguise = pStatesTxtRecord->dwStateFlags & gdwBitMasks[STATEMASK_DISGUISE];
			if (bSet && bStateMaskDisguise)
			{
				pUnit->dwFlagEx |= UNITFLAGEX_ISSHAPESHIFTED;
			}
			else if (bStateMaskDisguise  && !STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_DISGUISE))
			{
				pUnit->dwFlagEx &= ~UNITFLAGEX_ISSHAPESHIFTED;
			}
		}
	}
}

//D2Common.0x6FDB8A90
uint32_t* __stdcall D2COMMON_STATES_GetStatFlags_6FDB8A90(struct D2Unit* pUnit)
{
	if (pUnit && pUnit->pStatListEx && STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx))
	{
		return pUnit->pStatListEx->StatFlags;
	}

	return NULL;
}

//D2Common.0x6FDB8AC0
uint32_t* __stdcall D2COMMON_STATES_GetListGfxFlags_6FDB8AC0(struct D2Unit* pUnit)
{
	if (pUnit && pUnit->pStatListEx && STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx))
	{
		return &pUnit->pStatListEx->StatFlags[(sgptDataTables->nStatesTxtRecordCount + 31) / 32];
	}

	return NULL;
}

//D2Common.0x6FDB8B10 (#10516)
void __stdcall STATLIST_UpdateStatListsExpiration(struct D2Unit* pUnit, int nFrame)
{
	if (pUnit == nullptr || pUnit->pStatListEx == nullptr || !STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx))
	{
		return;
	}

	struct D2StatList* pPrevious;
	for (struct D2StatList* pCurrent = pUnit->pStatListEx->pMyLastList; pCurrent != nullptr; pCurrent = pPrevious)
	{
		pPrevious = pCurrent->pPrevLink;
		if (!(pCurrent->dwFlags & STATLIST_NEWLENGTH))
		{
			continue;
		}

		if (nFrame == 0)  // Client, the server only syncs
		{
			pCurrent->dwExpireFrame--;
		}

		if (pCurrent->dwExpireFrame <= nFrame)
		{
			if (!STATLIST_IsExtended(pCurrent))
			{
				D2Common_STATLIST_FreeStatListImpl_6FDB7050(pCurrent);
			}

			pPrevious = pUnit->pStatListEx->pMyLastList;
		}
	}
}


// Helper function
int __stdcall STATLIST_CopyStatsData(struct D2StatsArray* pStatsArray, struct D2Stat* pOutStatBuffer, int nBufferSize)
{
	int nStatCount = pStatsArray->nStatCount;
	if (nStatCount >= nBufferSize)
	{
		nStatCount = nBufferSize;
	}

	for(int nCounter = 0; nCounter < nStatCount; ++nCounter)
	{
		pOutStatBuffer[nCounter].nLayer = pStatsArray->pStat[nCounter].nLayer;
		pOutStatBuffer[nCounter].nStat  = pStatsArray->pStat[nCounter].nStat;
		pOutStatBuffer[nCounter].nValue = pStatsArray->pStat[nCounter].nValue;
	}

	return nStatCount;
}

//D2Common.0x6FDB8BA0 (#11268)
int __stdcall STATLIST_GetFullStatsDataFromUnit(struct D2Unit* pUnit, struct D2Stat* pOutStatBuffer, int nBufferSize)
{
	if (pUnit && pUnit->pStatListEx && STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx))
	{
		return STATLIST_CopyStatsData(&pUnit->pStatListEx->FullStats, pOutStatBuffer, nBufferSize);
	}
	return 0;
}

//D2Common.0x6FDB8C00 (#11243)
int __stdcall STATLIST_GetBaseStatsData(struct D2StatList* pStatListEx, struct D2Stat* pOutStatBuffer, int nBufferSize)
{
	if (pStatListEx)
	{
		return STATLIST_CopyStatsData(&pStatListEx->Stats, pOutStatBuffer, nBufferSize);
	}
	return 0;
}

//D2Common.0x6FDB8C50 (#10573)
void __stdcall STATLIST_MergeBaseStats(struct D2StatList* pTargetStatList, struct D2StatList* pSourceStatlist)
{
	if (pTargetStatList && pSourceStatlist)
	{
		for (struct D2Stat* i = pSourceStatlist->Stats.pStat; i < &pSourceStatlist->Stats.pStat[pSourceStatlist->Stats.nStatCount]; ++i)
		{
			STATLIST_AddStat(pTargetStatList, i->nStat, i->nValue, i->nLayer);
		}
	}
}

//D2Common.0x6FDB8CA0 (#10477)
void __stdcall STATLIST_SetStatRemoveCallback(struct D2StatList* pStatList, StatListRemoveCallback pfStatRemove)
{
	if (pStatList)
	{
		pStatList->fpStatRemove = pfStatRemove;
	}
}

//D2Common.0x6FDB8CC0 (#10469)
void __stdcall D2Common_10469(struct D2Unit* pUnit)
{
	if (pUnit && pUnit->pStatListEx && STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx))
	{
		struct D2StatList* pStatListEx = pUnit->pStatListEx->pMyLastList;
		if (pStatListEx)
		{
			struct D2StatList* pPrevious = NULL;
			do
			{
				pPrevious = pStatListEx->pPrevLink;
				if (pStatListEx->dwOwnerType != UNIT_ITEM 
					&& !(pStatListEx->dwFlags & (STATLIST_BASIC|STATLIST_OVERLAY|STATLIST_UNK_0x100)) 
					&& !STATES_CheckStateMaskStayDeathOnUnitByStateId(pUnit, pStatListEx->dwStateNo))
				{
					if (!STATLIST_IsExtended((struct D2StatList *)pStatListEx))
					{
						D2Common_STATLIST_FreeStatListImpl_6FDB7050((struct D2StatList *)pStatListEx);
					}

					pPrevious = pUnit->pStatListEx->pMyLastList;
				}
				pStatListEx = pPrevious;
			}
			while (pPrevious);
		}
	}
}

// Helper function
static void STATLIST_ClampStat(struct D2StatListEx* pStatListEx, int nStatId)
{
	int nCurrentValue = 0;
	{
		struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nStatId);
		if (pItemStatCostTxtRecord)
		{
			nCurrentValue = STATLIST_GetTotalStat_6FDB63E0((struct D2StatList *)pStatListEx, D2SLayerStatId_MakeFromStatId(nStatId).nPackedValue, pItemStatCostTxtRecord);
		}
	}

	const int nMaxStatId = nStatId + 1; // Assumes the Max of the input stat is the next stat, for example STAT_MANA = 8 and STAT_MAXMANA = 9
	int nMaxValue = 0;
	{
		struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(nMaxStatId);
		if (pItemStatCostTxtRecord)
		{
			nMaxValue = STATLIST_GetTotalStat_6FDB63E0((struct D2StatList *)pStatListEx, D2SLayerStatId_MakeFromStatId(nMaxStatId).nPackedValue, pItemStatCostTxtRecord);
		}
	}

	if (nCurrentValue > nMaxValue)
	{
		STATLIST_AddStat((struct D2StatList *)pStatListEx, nStatId, nMaxValue - nCurrentValue, 0);
	}
}

//D2Common.0x6FDB8D30 (#10514)
void __stdcall STATLIST_ClampStaminaManaHP(struct D2Unit* pUnit)
{
	if (pUnit && pUnit->pStatListEx)
	{
		STATLIST_ClampStat(pUnit->pStatListEx, STAT_STAMINA);
		STATLIST_ClampStat(pUnit->pStatListEx, STAT_MANA);
		STATLIST_ClampStat(pUnit->pStatListEx, STAT_HITPOINTS);
	}
}

//D2Common.0x6FDB8EB0 (#10574)
BOOL __stdcall D2Common_10574(struct D2Unit* pUnit, int nStateId, BOOL bSet)
{

	if (nStateId && pUnit->pStatListEx && STATLIST_IsExtended((struct D2StatList *)pUnit->pStatListEx))
	{
		struct D2StatList* pStatList = D2Common_GetStateFromStatListEx_6FDB8190(pUnit->pStatListEx, nStateId);
		if (pStatList)
		{
			if (bSet)
			{
				if (!(pStatList->dwFlags & STATLIST_SET))
				{
					D2Common_ExpireStatList_6FDB6E30(pStatList);
					pStatList->dwFlags |= STATLIST_SET;
					D2COMMON_10475_PostStatToStatList(pUnit, pStatList, TRUE);
				}
			}
			else
			{
				if (pStatList->dwFlags & STATLIST_SET)
				{
					D2Common_ExpireStatList_6FDB6E30(pStatList);
					pStatList->dwFlags &= ~STATLIST_SET;
					D2COMMON_10475_PostStatToStatList(pUnit, pStatList, TRUE);
				}
			}

			return TRUE;
		}
	}

	return FALSE;
}

//D2Common.0x6FDB8F30 (#10525)
void __stdcall D2Common_10525(struct D2Unit* pUnit1, struct D2Unit* pUnit2)
{
	if (!pUnit1 || !pUnit2 || !(pUnit1->dwUnitType == UNIT_PLAYER || pUnit1->dwUnitType == UNIT_MONSTER))
	{
		return;
	}
	struct D2StatListEx* pStatListEx2 = pUnit2->pStatListEx ? STATLIST_StatListExCast((struct D2StatList *)pUnit2->pStatListEx) : nullptr;
	if (!pStatListEx2)
	{
		return;
	}

	for (struct D2Stat* j = pStatListEx2->FullStats.pStat; j < &pStatListEx2->FullStats.pStat[pStatListEx2->FullStats.nStatCount]; ++j)
	{
		struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(j->nStat);
		if (pItemStatCostTxtRecord && pItemStatCostTxtRecord->nOp >= 6 && pItemStatCostTxtRecord->nOp <= 7)
		{
			for (int i = 0; i < ARRAY_SIZE(pItemStatCostTxtRecord->wOpStat); i++)
			{
				const uint16_t wOpStat = pItemStatCostTxtRecord->wOpStat[i];
				if (wOpStat == (uint16_t)(-1))
				{
					break;
				}

				struct D2SLayerStatId nOpLayer_StatId = D2SLayerStatId_MakeFromStatId(wOpStat);
				struct D2StatListEx* pUnit1StatListEx = pUnit1->pStatListEx;
				int nOpStatValue = sub_6FDB5830(pUnit1StatListEx, nOpLayer_StatId.nPackedValue);

				struct D2Stat* pUnit1Stat = STATLIST_FindStat_6FDB6920(&pUnit1StatListEx->FullStats, nOpLayer_StatId.nPackedValue);
				if (!pUnit1Stat && nOpStatValue != 0)
				{
					pUnit1Stat = STATLIST_InsertStatOrFail_6FDB6970(pUnit1StatListEx->pMemPool, &pUnit1StatListEx->FullStats, nOpLayer_StatId.nPackedValue);
				}
				if (pUnit1Stat)
				{
					STATLIST_SetUnitStatNewValue(pUnit1StatListEx, &pUnit1StatListEx->FullStats, pUnit1Stat, nOpLayer_StatId.nPackedValue, nOpStatValue, ITEMS_GetItemStatCostTxtRecord(wOpStat), pUnit1);
				}
			}
		}
	}
}

//D2Common.0x6FDB91C0 (#10474)
void __stdcall D2Common_10474(struct D2Unit* pUnused, struct D2StatList* pStatList)
{
	D2_MAYBE_UNUSED(pUnused);
	D2Common_ExpireStatList_6FDB6E30(pStatList);
}

//D2Common.0x6FDB91D0 (#10564)
int __stdcall STATLIST_GetMaxLifeFromUnit(struct D2Unit* pUnit)
{
	return D2Common_11248(NULL, pUnit, STAT_MAXHP);
}

//D2Common.0x6FDB92C0 (#10565)
int __stdcall STATLIST_GetMaxManaFromUnit(struct D2Unit* pUnit)
{
	return D2Common_11248(NULL, pUnit, STAT_MAXMANA);
}

//D2Common.0x6FDB93B0 (#10566)
int __stdcall STATLIST_GetMaxStaminaFromUnit(struct D2Unit* pUnit)
{
	return D2Common_11248(NULL, pUnit, STAT_MAXSTAMINA);
}

//D2Common.0x6FDB94A0 (#10567)
int __stdcall STATLIST_GetMaxDurabilityFromUnit(struct D2Unit* pUnit)
{
	return D2Common_11248(NULL, pUnit, STAT_MAXDURABILITY);
}

//D2Common.0x6FDB95D0 (#10568)
int __stdcall STATLIST_GetMaxDamageFromUnit(struct D2Unit* pUnit, BOOL b2Handed)
{
	if (b2Handed)
	{
		return D2Common_11248(NULL, pUnit, STAT_SECONDARY_MAXDAMAGE);
	}
	else
	{
		return D2Common_11248(NULL, pUnit, STAT_MAXDAMAGE);
	}
}

//D2Common.0x6FDB96F0 (#10569)
int __stdcall STATLIST_GetMinDamageFromUnit(struct D2Unit* pUnit, BOOL b2Handed)
{
	if (b2Handed)
	{
		return D2Common_11248(NULL, pUnit, STAT_SECONDARY_MINDAMAGE);
	}
	else
	{
		return D2Common_11248(NULL, pUnit, STAT_MINDAMAGE);
	}
}

//D2Common.0x6FDB9810 (#10570)
int __stdcall STATLIST_GetMaxThrowDamageFromUnit(struct D2Unit* pUnit)
{
	return D2Common_11248(NULL, pUnit, STAT_ITEM_THROW_MAXDAMAGE);
}

//D2Common.0x6FDB9900 (#10571)
int __stdcall STATLIST_GetMinThrowDamageFromUnit(struct D2Unit* pUnit)
{
	return D2Common_11248(NULL, pUnit, STAT_ITEM_THROW_MINDAMAGE);
}

//D2Common.0x6FDB99F0 (#10572)
int __stdcall STATLIST_GetDefenseFromUnit(struct D2Unit* pUnit)
{
	return D2Common_11248(NULL, pUnit, STAT_ARMORCLASS);
}

//D2Common.0x6FDB9AE0 (#10524)
void __stdcall STATLIST_ExpireUnitStatlist(struct D2Unit* pUnused, struct D2Unit* pUnit)
{
	D2_MAYBE_UNUSED(pUnused);
	if (pUnit && pUnit->pStatListEx)
	{
		D2Common_ExpireStatList_6FDB6E30((struct D2StatList *)pUnit->pStatListEx);
	}
}

//D2Common.0x6FDB9B00 (#10531)
int __stdcall D2Common_10531_SetStatInStatListLayer0(struct D2StatList* pStatList, int nStatId, int nValue, int nUnused)
{
	D2_MAYBE_UNUSED(nUnused);
	return STATLIST_SetStat(pStatList, nStatId, nValue, 0);
}

//D2Common.0x6FDB9B10 (#11248)
int __stdcall D2Common_11248(struct D2Unit* pUnused, struct D2Unit* pUnit, int nStatId)
{
	D2_MAYBE_UNUSED(pUnused);
	if (pUnit)
	{
		return STATLIST_GetTotalStatValue_Layer0((struct D2StatList *)pUnit->pStatListEx, nStatId);
	}

	return 0;
}

//D2Common.0x6FDA9E60 (#11264)
void __stdcall STATLIST_SetSkillId(struct D2StatList* pStatList, int nSkillId)
{
	pStatList->dwSkillNo = nSkillId;
}

//D2Common.0x6FDB9C10 (#11265)
int __stdcall STATLIST_GetSkillId(struct D2StatList* pStatList)
{
	if (pStatList)
	{
		return pStatList->dwSkillNo;
	}

	REMOVE_LATER_Trace("STATLIST_GetSkillId: NULL pointer");
	return 0;
}

//D2Common.0x6FDB9C20 (#11266)
void __stdcall STATLIST_SetSkillLevel(struct D2StatList* pStatList, int nSkillLevel)
{
	if (pStatList)
	{
		pStatList->dwSLvl = nSkillLevel;
		return;
	}

	REMOVE_LATER_Trace("STATLIST_SetSkillLevel: NULL pointer");
}

//D2Common.0x6FDA9E70 (#11267)
int __stdcall STATLIST_GetSkillLevel(struct D2StatList* pStatList)
{
	if (pStatList)
	{
		return pStatList->dwSLvl;
	}

	REMOVE_LATER_Trace("STATLIST_GetSkillLevel: NULL pointer");
	return 0;
}

//D2Common.0x6FDB9C30 (#11269)
int __stdcall D2COMMON_11269_CopyStats(struct D2StatListEx* pStatListEx, int nStatId, struct D2Stat* pBuffer, int nBufferSize)
{
	return D2Common_CopyStats_6FDB9C50((struct D2StatList *)pStatListEx, nStatId, pBuffer, nBufferSize);
}

//D2Common.0x6FDB9C50
int __fastcall D2Common_CopyStats_6FDB9C50(struct D2StatList* pStatList, int nStatId, struct D2Stat* pBuffer, int nBufferSize)
{
	if (!pStatList)
	{
		return 0;
	}

	struct D2StatListEx* pStatListEx = STATLIST_StatListExCast(pStatList);
	struct D2StatsArray* pStatArray = pStatListEx ? &pStatListEx->FullStats : &pStatList->Stats;
	int nStatIndex = D2StatsArray_FindInsertionIndex(pStatArray, D2SLayerStatId_MakeFromStatId(nStatId).nPackedValue, nullptr);
	if (nStatIndex < 0)
	{
		return 0;
	}

	int nCopiedStats = 0;
	while (nStatIndex < pStatArray->nStatCount
		&& pStatArray->pStat[nStatIndex].nStat == nStatId
		&& nCopiedStats < nBufferSize
		)
	{
		pBuffer[nCopiedStats].nPackedValue = pStatArray->pStat[nStatIndex].nPackedValue;
		pBuffer[nCopiedStats].nValue = pStatArray->pStat[nStatIndex].nValue;

		++nCopiedStats;
		++nStatIndex;
	}

	return nCopiedStats;
}

//D2Common.0x6FDB9D20 (#11270)
int __stdcall STATLIST_CopyStats(struct D2Unit* pUnit, int nStatId, struct D2Stat* pBuffer, int nBufferSize)
{
	struct D2StatListEx* pStatListEx = STATLIST_StatListExCast((struct D2StatList *)pUnit->pStatListEx);
	if (pStatListEx)
	{
		return D2Common_CopyStats_6FDB9C50((struct D2StatList *)pStatListEx, nStatId, pBuffer, nBufferSize);
	}
	return 0;
}

//D2Common.0x6FDB9D60 (#11273)
int __stdcall D2Common_11273(struct D2Unit* pUnit, int nStatId)
{
	struct D2StatListEx* pStatListEx = STATLIST_StatListExCast((struct D2StatList *)pUnit->pStatListEx);
	if (pStatListEx)
	{
		return sub_6FDB5830(pStatListEx, D2SLayerStatId_MakeFromStatId(nStatId).nPackedValue);
	}
	return 0;
}


// Helper function
BOOL __stdcall D2Common_11274_11275_Impl(struct D2Unit* pTarget, struct D2Unit* pUnit, bool addOrSubstract)
{

	if (!pTarget || !pUnit || !pUnit->pStatListEx)
	{
		return FALSE;
	}

	if (pUnit->pStatListEx->pUnit != pTarget)
	{
		STATLIST_MergeStatLists(pTarget, pUnit, addOrSubstract);
		return FALSE;
	}

	if (!(pTarget->pStatListEx && STATLIST_IsExtended((struct D2StatList *)pTarget->pStatListEx)))
	{
		return FALSE;
	}

	bool bDynamicBitChanged = BITMANIP_SetBitsValueForMask_uint32_t(&pUnit->pStatListEx->dwFlags, STATLIST_DYNAMIC, !addOrSubstract);
	if (!bDynamicBitChanged)
	{
		return FALSE;
	}

	struct D2StatListEx* pUnitStatListEx = STATLIST_StatListExCast((struct D2StatList *)pUnit->pStatListEx);
	struct D2StatsArray* pStatsArray = pUnitStatListEx ? &pUnitStatListEx->FullStats : &pUnit->pStatListEx->Stats;

	for (struct D2Stat* i = pStatsArray->pStat; i < &pStatsArray->pStat[pStatsArray->nStatCount]; ++i)
	{
		struct D2ItemStatCostTxt* pItemStatCostTxtRecord = ITEMS_GetItemStatCostTxtRecord(i->nStat);
		if (pItemStatCostTxtRecord && (pItemStatCostTxtRecord->dwItemStatFlags & gdwBitMasks[ITEMSTATCOSTFLAGINDEX_DAMAGERELATED]))
		{
			const int nValue = addOrSubstract ? i->nValue : -i->nValue;
			sub_6FDB6C10(pTarget->pStatListEx, i->nPackedValue, nValue, pUnit);
		}
	}

	return TRUE;
}

//D2Common.0x6FDB9D90 (#11274)
BOOL __stdcall D2Common_11274(struct D2Unit* pTarget, struct D2Unit* pUnit)
{
	return D2Common_11274_11275_Impl(pTarget, pUnit, true);
}

//D2Common.0x6FDB9E60 (#11275)
BOOL __stdcall D2Common_11275(struct D2Unit* pTarget, struct D2Unit* pUnit)
{
	return D2Common_11274_11275_Impl(pTarget, pUnit, false);
}
