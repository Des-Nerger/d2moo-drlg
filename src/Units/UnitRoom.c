#include "Units/UnitRoom.h"

#include "D2Dungeon.h"
#include "D2StatList.h"
#include "Units/Units.h"
#include "Path/Path.h"


//TODO: Find names (used by Path Functions)
int dword_6FDD2580;
int dword_6FDD2584;

//D2Common.0x6FDBCF10 (#11279)
int __stdcall UNITROOM_AddUnitToRoomEx(struct D2Unit* pUnit, struct D2ActiveRoom* pRoom, int nUnused)
{
	D2_MAYBE_UNUSED(nUnused);

	D2_ASSERT(pUnit);
	D2_ASSERT(pRoom);

	//Note: tRoomCoord is unused but filled in the original code
	//struct D2DrlgCoords tRoomCoord = {};
	//DUNGEON_GetRoomCoordinates(pRoom, &tRoomCoord);

	struct D2Coord tCoord = {};
	UNITS_GetCoords(pUnit, &tCoord);
	D2_ASSERT(DungeonTestRoomGame(pRoom, tCoord.nX, tCoord.nY));

	for (struct D2Unit* i = pRoom->pUnitFirst; i; i = i->pRoomNext)
	{
		D2_ASSERTM(pUnit != i, "Unit being added to a room it is already in");
	}

	struct D2Unit** ppUnitFirst = DUNGEON_GetUnitListFromRoom(pRoom);
	D2_ASSERT(ppUnitFirst);
	pUnit->pRoomNext = *ppUnitFirst;
	*ppUnitFirst = pUnit;

	UNITROOM_RefreshUnit(pUnit);

	if (pUnit->dwUnitType == UNIT_PLAYER || (pUnit->dwUnitType == UNIT_MONSTER && STATLIST_GetUnitAlignment(pUnit) == UNIT_ALIGNMENT_GOOD))
	{
		DUNGEON_IncreaseAlliedCountOfRoom(pRoom);
	}

	return 1;
}

//D2Common.0x6FDBD100 (#10384)
int __stdcall UNITROOM_AddUnitToRoom(struct D2Unit* pUnit, struct D2ActiveRoom* pRoom)
{
	return UNITROOM_AddUnitToRoomEx(pUnit, pRoom, 1);
}

//D2Common.0x6FDBD120 (#10385)
void __stdcall UNITROOM_RefreshUnit(struct D2Unit* pUnit)
{

	D2_ASSERT(pUnit);

	struct D2ActiveRoom* pRoom = UNITS_GetRoom(pUnit);
	if (pRoom && !D2Common_10084(pRoom) && !(pUnit->dwFlags & UNITFLAG_ISLINKREFRESHMSG))
	{
		pUnit->dwFlags |= UNITFLAG_ISLINKREFRESHMSG;

		struct D2Unit** ppUnitFirst = DUNGEON_GetUnitUpdateListFromRoom(pRoom, TRUE);
		D2_ASSERT(ppUnitFirst);

		pUnit->pChangeNextUnit = *ppUnitFirst;
		*ppUnitFirst = pUnit;
	}
}

//D2Common.0x6FDBD1B0 (#10388)
void __stdcall UNITROOM_SortUnitListByTargetY(struct D2ActiveRoom* pRoom)
{
	struct D2Unit** ppUnitFirst = NULL;
	struct D2Unit** ppUnit = NULL;
	struct D2Unit* pPreviousUnit = NULL;
	struct D2Unit* pNextUnit = NULL;
	struct D2Unit* pUnit = NULL;
	bool bContinue = false;

	ppUnit = DUNGEON_GetUnitListFromRoom(pRoom);
	pUnit = *ppUnit;
	ppUnitFirst = ppUnit;

	if (pUnit)
	{
		pNextUnit = pUnit->pRoomNext;
		do
		{
			bContinue = false;

			while (pNextUnit)
			{
				if (UNITS_GetClientCoordY(pUnit) <= UNITS_GetClientCoordY(pNextUnit))
				{
					pPreviousUnit = pUnit;
					pUnit = pNextUnit;
					pNextUnit = pNextUnit->pRoomNext;
				}
				else
				{
					if (pPreviousUnit)
					{
						pPreviousUnit->pRoomNext = pNextUnit;
					}
					else
					{
						*ppUnitFirst = pNextUnit;
					}

					pPreviousUnit = pNextUnit;
					pUnit->pRoomNext = pNextUnit->pRoomNext;
					pNextUnit->pRoomNext = pUnit;
					pNextUnit = pUnit->pRoomNext;
					bContinue = true;
				}
			}
		}
		while (bContinue);
	}
}

//1.00:  D2Common.0x1006D1E0 (#10385)
//1.10f: D2Common.0x6FDBD250 (#10390)
void __stdcall UNITROOM_UpdatePath(struct D2Unit* pUnit)
{
	D2_ASSERT(pUnit);

	switch (pUnit->dwUnitType)
	{
	case UNIT_PLAYER:
	case UNIT_MONSTER:
	case UNIT_MISSILE:
		pUnit->pDynamicPath->tGameCoords.dwPrecisionX = dword_6FDD2580;
		pUnit->pDynamicPath->tGameCoords.dwPrecisionY = dword_6FDD2584;

		pUnit->pDynamicPath->dwClientCoordX = dword_6FDD2580;
		pUnit->pDynamicPath->dwClientCoordY = dword_6FDD2584;

		pUnit->pDynamicPath->dwPathPoints = 0;
		
		if (pUnit->pDynamicPath->pRoom)
		{
			pUnit->pDynamicPath->pPreviousRoom = pUnit->pDynamicPath->pRoom;
			UNITROOM_RemoveUnitFromRoom(pUnit->pDynamicPath->pUnit);
			pUnit->pDynamicPath->dwFlags |= PATH_CURRENT_ROOM_INVALID;
		}
		break;

	case UNIT_OBJECT:
	case UNIT_ITEM:
	case UNIT_TILE:
		if (pUnit->pStaticPath->pRoom)
		{
			UNITROOM_RemoveUnitFromRoom(pUnit);
			pUnit->pStaticPath->pRoom = NULL;
		}
		break;
	default:
		break;
	}
}

//D2Common.0x6FDBD2B0 (#10391)
void __stdcall UNITROOM_ClearUpdateQueue(struct D2ActiveRoom* pRoom)
{
	struct D2Unit** ppChangeUnit = NULL;
	struct D2Unit* pNextChangeUnit = NULL;

	ppChangeUnit = DUNGEON_GetUnitUpdateListFromRoom(pRoom, FALSE);
	while (*ppChangeUnit)
	{
		pNextChangeUnit = (*ppChangeUnit)->pChangeNextUnit;
		(*ppChangeUnit)->dwFlags &= ~UNITFLAG_ISLINKREFRESHMSG;
		(*ppChangeUnit)->pChangeNextUnit = NULL;
		*ppChangeUnit = pNextChangeUnit;
	}

	*ppChangeUnit = NULL;
}

//D2Common.0x6FDBD300 (#10386)
void __stdcall UNITROOM_RemoveUnitFromRoom(struct D2Unit* pUnit)
{
	struct D2Unit** ppRoomUnit = NULL;
	struct D2Unit* pPreviousUnit = NULL;
	struct D2Unit* pRoomUnit = NULL;
	struct D2ActiveRoom* pRoom = NULL;
	bool bReset = false;

	D2_ASSERT(pUnit);

	pRoom = UNITS_GetRoom(pUnit);
	if (pRoom)
	{
		ppRoomUnit = DUNGEON_GetUnitListFromRoom(pRoom);
		pRoomUnit = *ppRoomUnit;

		if (pRoomUnit)
		{
			while (pRoomUnit != pUnit)
			{
				pPreviousUnit = pRoomUnit;
				pRoomUnit = pRoomUnit->pRoomNext;
				if (!pRoomUnit)
				{
					break;
				}
			}

			if (pRoomUnit)
			{
				bReset = true;
				if (pPreviousUnit)
				{
					pPreviousUnit->pRoomNext = pRoomUnit->pRoomNext;
				}
				else
				{
					*ppRoomUnit = pRoomUnit->pRoomNext;
				}

				pRoomUnit->pRoomNext = NULL;

				if (pUnit->dwUnitType == UNIT_PLAYER || pUnit->dwUnitType == UNIT_MONSTER && STATLIST_GetUnitAlignment(pUnit) == UNIT_ALIGNMENT_GOOD)
				{
					DUNGEON_DecreaseAlliedCountOfRoom(pRoom);
				}
			}
		}

		UNITROOM_RemoveUnitFromUpdateQueue(pUnit);
		pUnit->dwFlags &= ~UNITFLAG_ISLINKREFRESHMSG;
		if (bReset)
		{
			UNITS_ResetRoom(pUnit);
		}
	}
	D2_ASSERT(!pUnit->pRoomNext);
}

//D2Common.0x6FDBD400 (#10387)
void __stdcall UNITROOM_RemoveUnitFromUpdateQueue(struct D2Unit* pUnit)
{
	struct D2Unit** ppChangeUnit = NULL;
	struct D2Unit* pPreviousChangeUnit = NULL;
	struct D2Unit* pChangeUnit = NULL;
	struct D2ActiveRoom* pRoom = NULL;

	D2_ASSERT(pUnit);

	pRoom = UNITS_GetRoom(pUnit);
	if (pRoom)
	{
		ppChangeUnit = DUNGEON_GetUnitUpdateListFromRoom(pRoom, FALSE);
		pChangeUnit = *ppChangeUnit;

		if (pChangeUnit)
		{
			while (pChangeUnit != pUnit)
			{
				pPreviousChangeUnit = pChangeUnit;
				pChangeUnit = pChangeUnit->pChangeNextUnit;
				if (!pChangeUnit)
				{
					return;
				}
			}

			if (pChangeUnit)
			{
				if (pPreviousChangeUnit)
				{
					pPreviousChangeUnit->pChangeNextUnit = pChangeUnit->pChangeNextUnit;
					pChangeUnit->pChangeNextUnit = NULL;
				}
				else
				{
					*ppChangeUnit = pChangeUnit->pChangeNextUnit;
					pChangeUnit->pChangeNextUnit = NULL;
				}
			}
		}
	}
	D2_ASSERT(!pUnit->pChangeNextUnit);
}

//D2Common.0x6FDBD4C0 (#10389)
BOOL __stdcall UNITROOM_IsUnitInRoom(struct D2ActiveRoom* pRoom, struct D2Unit* pUnit)
{
	struct D2Unit* pRoomUnit = NULL;

	D2_ASSERT(pUnit);

	if (!pRoom)
	{
		return FALSE;
	}

	pRoomUnit = *DUNGEON_GetUnitListFromRoom(pRoom);
	if (pRoomUnit != pUnit)
	{
		while (pRoomUnit)
		{
			pRoomUnit = pRoomUnit->pRoomNext;

			if (pRoomUnit == pUnit)
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	return TRUE;
}
