#include "D2States.h"

#include "D2DataTbls.h"
#include "D2StatList.h"
#include "Units/UnitRoom.h"
#include "Units/Units.h"
#include <D2BitManip.h>

//Used in some of the following functions
__forceinline BOOL __cdecl STATES_CheckStateMaskByStateId(int nState, int nStateMask)
{
	if (nState >= 0 && nState < sgptDataTables->nStatesTxtRecordCount)
	{
		return sgptDataTables->fStateMasks[nStateMask][nState >> 5] & gdwBitMasks[nState & 31];
	}

	return FALSE;
}


//D2Common.0x6FDB4560 (#10486)
void __cdecl STATES_ToggleState(struct D2Unit* pUnit, int nState, BOOL bSet)
{
	if (nState >= 0 && nState < sgptDataTables->nStatesTxtRecordCount)
	{
		D2Common_STATES_ToggleState_6FDB8900(pUnit, nState, bSet);
		UNITROOM_RefreshUnit(pUnit);
	}
}

//D2Common.0x6FDB45A0 (#10487)
BOOL __cdecl STATES_CheckState(struct D2Unit* pUnit, int nState)
{
	if (pUnit && (pUnit->dwUnitType == UNIT_PLAYER || pUnit->dwUnitType == UNIT_MONSTER || pUnit->dwUnitType == UNIT_MISSILE) && nState >= 0 && nState < sgptDataTables->nStatesTxtRecordCount)
	{
		if (pUnit->pStatListEx && STATLIST_IsExtended(pUnit->pStatListEx))
		{
			return pUnit->pStatListEx->StatFlags[nState >> 5] & gdwBitMasks[nState & 31];
		}
	}

	return FALSE;
}

//D2Common.0x6FDB45F0 (#10488)
void __cdecl STATES_ToggleGfxStateFlag(struct D2Unit* pUnit, int nState, BOOL bSet)
{
	uint32_t* pGfxFlags = D2COMMON_STATES_GetListGfxFlags_6FDB8AC0(pUnit);

	if (pGfxFlags && nState >= 0 && nState < sgptDataTables->nStatesTxtRecordCount)
	{
		if (bSet)
		{
			pGfxFlags[nState >> 5] |= gdwBitMasks[nState & 31];
		}
		else
		{
			pGfxFlags[nState >> 5] &= gdwInvBitMasks[nState & 31];
		}

		UNITROOM_RefreshUnit(pUnit);
	}
}

//D2Common.0x6FDB4670 (#10489)
BOOL __cdecl STATES_CheckGfxStateFlag(struct D2Unit* pUnit, int nState)
{
	uint32_t* pGfxFlags = NULL;

	if (nState >= 0 && nState < sgptDataTables->nStatesTxtRecordCount)
	{
		pGfxFlags = D2COMMON_STATES_GetListGfxFlags_6FDB8AC0(pUnit);
		if (pGfxFlags)
		{
			return pGfxFlags[nState >> 5] & gdwBitMasks[nState & 31];
		}
	}

	return FALSE;
}

//D2Common.0x6FDB46C0 (#10491)
void __cdecl STATES_ClearGfxStateFlags(struct D2Unit* pUnit)
{
	uint32_t* pGfxFlags = D2COMMON_STATES_GetListGfxFlags_6FDB8AC0(pUnit);

	if (pGfxFlags)
	{
		memset(pGfxFlags, 0x00, sizeof(uint32_t) * (sgptDataTables->nStatesTxtRecordCount + 31) / 32);
	}
}

//D2Common.0x6FDB4710 (#10490)
BOOL __cdecl STATES_IsAnyGfxStateFlagSet(struct D2Unit* pUnit)
{
	uint32_t* pGfxFlags = NULL;
	int nCounter = 0;

	pGfxFlags = D2COMMON_STATES_GetListGfxFlags_6FDB8AC0(pUnit);
	if (pGfxFlags && (sgptDataTables->nStatesTxtRecordCount + 31) / 32 > 0)
	{
		while (!pGfxFlags[nCounter])
		{
			++nCounter;
			if (nCounter >= (sgptDataTables->nStatesTxtRecordCount + 31) / 32)
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	return FALSE;
}

//D2Common.0x6FDB4760 (#10492)
uint32_t* __cdecl STATES_GetGfxStateFlags(struct D2Unit* pUnit)
{
	D2_ASSERT(pUnit);

	return D2COMMON_STATES_GetListGfxFlags_6FDB8AC0(pUnit);
}

//D2Common.0x6FDB4790 (#10493)
void __cdecl STATES_UpdateStayDeathFlags(struct D2Unit* pUnit, BOOL bIsBoss)
{
	uint32_t* pStatFlags = NULL;
	uint32_t* pGfxFlags = NULL;

	pGfxFlags = D2COMMON_STATES_GetListGfxFlags_6FDB8AC0(pUnit);
	pStatFlags = D2COMMON_STATES_GetStatFlags_6FDB8A90(pUnit);

	if (pGfxFlags && pStatFlags)
	{
		if (bIsBoss)
		{
			for (int i = 0; i < (sgptDataTables->nStatesTxtRecordCount + 31) / 32; ++i)
			{
				pGfxFlags[i] |= pStatFlags[i] & ~sgptDataTables->fStateMasks[STATEMASK_BOSSSTAYDEATH][i];
				pStatFlags[i] &= sgptDataTables->fStateMasks[STATEMASK_BOSSSTAYDEATH][i];
			}
		}
		else if (!pUnit || pUnit->dwUnitType != UNIT_PLAYER)
		{
			for (int i = 0; i < (sgptDataTables->nStatesTxtRecordCount + 31) / 32; ++i)
			{
				pGfxFlags[i] |= pStatFlags[i] & ~sgptDataTables->fStateMasks[STATEMASK_MONSTAYDEATH][i];
				pStatFlags[i] &= sgptDataTables->fStateMasks[STATEMASK_MONSTAYDEATH][i];
			}
		}
		else
		{
			for (int i = 0; i < (sgptDataTables->nStatesTxtRecordCount + 31) / 32; ++i)
			{
				pGfxFlags[i] |= pStatFlags[i] & ~sgptDataTables->fStateMasks[STATEMASK_PLRSTAYDEATH][i];
				pStatFlags[i] &= sgptDataTables->fStateMasks[STATEMASK_PLRSTAYDEATH][i];
			}
		}

		UNITROOM_RefreshUnit(pUnit);
	}
}

//D2Common.0x6FDB48F0 (#10494)
uint32_t* __cdecl D2COMMON_10494_STATES_GetStatFlags(struct D2Unit* pUnit)
{
	return D2COMMON_STATES_GetStatFlags_6FDB8A90(pUnit);
}

//D2Common.0x6FDB4900 (#10495)
int __cdecl STATES_GetNumberOfStateFlags()
{
	return (sgptDataTables->nStatesTxtRecordCount + 31) / 32;
}

//D2Common.0x6FDB4920 (#10496)
BOOL __cdecl STATES_CheckStateMaskAuraByStateId(int nState)
{
	return STATES_CheckStateMaskByStateId(nState, STATEMASK_AURA);
}

//D2Common.0x6FDB4960 (#10503)
BOOL __cdecl STATES_CheckStateMaskAuraOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_AURA);
}

//D2Common.0x6FDB49D0 (#10500)
BOOL __cdecl STATES_CheckStateMaskPgsvByStateId(int nState)
{
	return STATES_CheckStateMaskByStateId(nState, STATEMASK_PGSV);
}

//D2Common.0x6FDB4A10 (#11234)
BOOL __cdecl STATES_CheckStateMaskPgsvOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_PGSV);
}

//D2Common.0x6FDB4A80 (#10501)
void __cdecl STATES_UpdatePgsvFlags(struct D2Unit* pUnit)
{
	uint32_t* pStatFlags = NULL;
	uint32_t* pGfxFlags = NULL;

	pGfxFlags = D2COMMON_STATES_GetListGfxFlags_6FDB8AC0(pUnit);
	pStatFlags = D2COMMON_STATES_GetStatFlags_6FDB8A90(pUnit);

	if (pGfxFlags && pStatFlags)
	{
		for (int i = 0; i < (sgptDataTables->nStatesTxtRecordCount + 31) / 32; ++i)
		{
			pGfxFlags[i] |= pStatFlags[i] & sgptDataTables->fStateMasks[STATEMASK_PGSV][i];
			pStatFlags[i] &= ~sgptDataTables->fStateMasks[STATEMASK_PGSV][i];
		}

		UNITROOM_RefreshUnit(pUnit);
	}
}

//D2Common.0x6FDB4B20 (#10558)
BOOL __cdecl STATES_CheckStateMaskHideByStateId(int nState)
{
	return STATES_CheckStateMaskByStateId(nState, STATEMASK_HIDE);
}

//D2Common.0x6FDB4B50 (#10557)
BOOL __cdecl STATES_CheckStateMaskHideOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_HIDE);
}

//D2Common.0x6FDB4BC0 (#10502)
BOOL __cdecl STATES_CheckStateMaskActiveOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_ACTIVE);
}

//D2Common.0x6FDB4C30 (#11272)
BOOL __cdecl STATES_CheckStateMaskRemHitOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_REMHIT);
}

//D2Common.0x6FDB4CA0 (#10538)
BOOL __cdecl STATES_CheckStateMaskDamBlueOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_DAMBLUE);
}

//D2Common.0x6FDB4D10 (#10545)
BOOL __cdecl STATES_CheckStateMaskDamRedOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_DAMRED);
}

//D2Common.0x6FDB4D80 (#10537)
BOOL __cdecl STATES_CheckStateMaskAttBlueOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_ATTBLUE);
}

//D2Common.0x6FDB4DF0 (#10544)
BOOL __cdecl STATES_CheckStateMaskAttRedOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_ATTRED);
}

//D2Common.0x6FDB4E60 (#10551)
BOOL __cdecl STATES_IsUnitShapeShifted(struct D2Unit* pUnit)
{
	if (pUnit)
	{
		return pUnit->dwFlagEx & UNITFLAGEX_ISSHAPESHIFTED;
	}

	return FALSE;
}

//D2Common.0x6FDB4E80 (#10497)
BOOL __cdecl STATES_CheckStateMaskCurseByStateId(int nState)
{
	if (nState >= 0 && nState < sgptDataTables->nStatesTxtRecordCount)
	{
		return sgptDataTables->fStateMasks[11][nState >> 5] & gdwBitMasks[nState & 31];
	}

	return STATES_CheckStateMaskByStateId(nState, STATEMASK_CURSE);
}

//D2Common.0x6FDB4EC0 (#10498)
BOOL __cdecl STATES_CheckStateMaskCurableByStateId(int nState)
{
	return STATES_CheckStateMaskByStateId(nState, STATEMASK_CURABLE);
}

//D2Common.0x6FDB4F00 (#10554)
BOOL __cdecl STATES_CheckStateMaskStayDeathOnUnitByStateId(struct D2Unit* pUnit, int nState)
{
	if (nState >= 0 && nState < sgptDataTables->nStatesTxtRecordCount)
	{
		if (pUnit && pUnit->dwUnitType == UNIT_MONSTER)
		{
			return sgptDataTables->fStateMasks[STATEMASK_MONSTAYDEATH][nState >> 5] & gdwBitMasks[nState & 31];
		}
		else
		{
			return sgptDataTables->fStateMasks[STATEMASK_PLRSTAYDEATH][nState >> 5] & gdwBitMasks[nState & 31];
		}
	}

	return FALSE;
}

//D2Common.0x6FDB4F60
BOOL __cdecl STATES_CheckStateMaskRestrictOnUnit(struct D2Unit* pUnit, struct D2Skill* pSkill)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_RESTRICT);
}

//D2Common.0x6FDB4FC0 (#10536)
BOOL __cdecl STATES_CheckStateMaskBlueOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_BLUE);
}

//D2Common.0x6FDB5030 (#10539)
BOOL __cdecl STATES_CheckStateMaskArmBlueOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_ARMBLUE);
}

//D2Common.0x6FDB50A0 (#10540)
BOOL __cdecl STATES_CheckStateMaskRFBlueOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_RFBLUE);
}

//D2Common.0x6FDB5110 (#10541)
BOOL __cdecl STATES_CheckStateMaskRCBlueOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_RCBLUE);
}

//D2Common.0x6FDB5180 (#10542)
BOOL __cdecl STATES_CheckStateMaskRLBlueOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_RLBLUE);
}

//D2Common.0x6FDB51F0 (#10543)
BOOL __cdecl STATES_CheckStateMaskRPBlueOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_RPBLUE);
}

//D2Common.0x6FDB5260 (#10546)
BOOL __cdecl STATES_CheckStateMaskArmRedOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_ARMRED);
}

//D2Common.0x6FDB52D0 (#10547)
BOOL __cdecl STATES_CheckStateMaskRFRedOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_RFRED);
}

//D2Common.0x6FDB5340 (#10548)
BOOL __cdecl STATES_CheckStateMaskRCRedOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_RCRED);
}

//D2Common.0x6FDB53B0 (#10549)
BOOL __cdecl STATES_CheckStateMaskRLRedOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_RLRED);
}

//D2Common.0x6FDB5420 (#10550)
BOOL __cdecl STATES_CheckStateMaskRPRedOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_RPRED);
}

//D2Common.0x6FDB5490 (#10552)
BOOL __cdecl STATES_CheckStateMaskExpOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_EXP);
}

//D2Common.0x6FDB5500 (#10553)
BOOL __cdecl STATES_CheckStateMaskExpByStateId(int nState)
{
	return STATES_CheckStateMaskByStateId(nState, STATEMASK_EXP);
}

//D2Common.0x6FDB5540 (#10555)
BOOL __cdecl STATES_CheckStateMaskShatterOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_SHATTER);
}

//D2Common.0x6FDB55B0 (#10556)
BOOL __cdecl STATES_CheckStateMaskShatterByStateId(int nState)
{
	return STATES_CheckStateMaskByStateId(nState, STATEMASK_SHATTER);
}

//D2Common.0x6FDB55F0 (#10559)
BOOL __cdecl STATES_CheckStateMaskLifeOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_LIFE);
}

//D2Common.0x6FDB5660 (#10560)
BOOL __cdecl STATES_CheckStateMaskUdeadOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_UDEAD);
}

//D2Common.0x6FDB56D0 (#10561)
BOOL __cdecl STATES_CheckStateMaskGreenOnUnit(struct D2Unit* pUnit)
{
	return STATES_CheckStateMaskOnUnit(pUnit, STATEMASK_GREEN);
}

//D2Common.0x6FDB5740 (#11303)
BOOL __cdecl STATES_CheckStateMaskOnUnit(struct D2Unit* pUnit, int nStateMask)
{

	if (pUnit && nStateMask >= 0 && nStateMask < 40)
	{
		uint32_t* pStatFlags = D2COMMON_STATES_GetStatFlags_6FDB8A90(pUnit);

		if (pStatFlags)
		{
			for (int i = 0; i < (sgptDataTables->nStatesTxtRecordCount + 31) / 32; ++i)
			{
				if (pStatFlags[i] & sgptDataTables->fStateMasks[nStateMask][i])
				{
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}
