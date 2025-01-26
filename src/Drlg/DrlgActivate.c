#include "Drlg/D2DrlgActivate.h"

#include "Drlg/D2DrlgDrlg.h"
#include "Drlg/D2DrlgDrlgRoom.h"
#include "Drlg/D2DrlgPreset.h"
#include "Drlg/D2DrlgRoomTile.h"
#include <DataTbls/LevelsIds.h>

static int gStatsClientFreedRooms;
static int gStatsClientAllocatedRooms;
static int gStatsFreedRooms;
static int gStatsAllocatedRooms;

// D2Common.0x6FDE07B0
static void (__cdecl* gRoomExSetStatus[ROOMSTATUS_COUNT])(struct D2DrlgRoom*) =
{
	DRLGACTIVATE_RoomExSetStatus_ClientInRoom,
	DRLGACTIVATE_RoomExSetStatus_ClientInSight,
	DRLGACTIVATE_RoomExSetStatus_ClientOutOfSight,
	DRLGACTIVATE_RoomExSetStatus_Untile
};

// D2Common.0x6FDE07C0
static void (__cdecl* gRoomExUnsetStatus[ROOMSTATUS_COUNT])(struct D2DrlgRoom*) =
{
	DRLGACTIVATE_RoomExIdentifyRealStatus,
	DRLGACTIVATE_RoomExIdentifyRealStatus,
	DRLGACTIVATE_RoomExIdentifyRealStatus,
	DRLGACTIVATE_RoomExStatusUnset_Untile
};

//Helper functions
static void DRLGACTIVATE_RoomExStatuslink(struct D2DrlgRoom* pStatusRoomsListHead, struct D2DrlgRoom* pDrlgRoom)
{
	pDrlgRoom->pStatusNext = pStatusRoomsListHead;
	pDrlgRoom->pStatusPrev = pStatusRoomsListHead->pStatusPrev;

	pStatusRoomsListHead->pStatusPrev->pStatusNext = pDrlgRoom;
	pStatusRoomsListHead->pStatusPrev = pDrlgRoom;
}
static void DRLGACTIVATE_RoomExStatusUnlink(struct D2DrlgRoom* pDrlgRoom)
{
	if (pDrlgRoom->pStatusPrev && pDrlgRoom->pStatusNext)
	{
		pDrlgRoom->pStatusPrev->pStatusNext = pDrlgRoom->pStatusNext;
		pDrlgRoom->pStatusNext->pStatusPrev = pDrlgRoom->pStatusPrev;
		pDrlgRoom->pStatusPrev = nullptr;
		pDrlgRoom->pStatusNext = nullptr;
	}
}
// Returns true if status changed
static bool DRLGACTIVATE_UpdateRoomExStatusImpl(struct D2DrlgRoom* pDrlgRoom, enum D2DrlgRoomStatus nStatus)
{
	// Note: Lower value has priority over others
	if (pDrlgRoom->fRoomStatus > nStatus)
	{
		DRLGACTIVATE_RoomExStatusUnlink(pDrlgRoom);
		if (nStatus < ROOMSTATUS_COUNT)
		{
			DRLGACTIVATE_RoomExStatuslink(&pDrlgRoom->pLevel->pDrlg->tStatusRoomsLists[nStatus], pDrlgRoom);
		}
		pDrlgRoom->fRoomStatus = nStatus;
		return true;
	}
	return false;
}
static enum D2DrlgRoomStatus DRLGACTIVATE_RoomExFindFirstStatusWithRefCount(struct D2DrlgRoom* pDrlgRoom, enum D2DrlgRoomStatus nMaxStatus)
{
	for (int nFirstNonEmptyListStatus = 0; nFirstNonEmptyListStatus <= nMaxStatus && nFirstNonEmptyListStatus < ROOMSTATUS_COUNT; nFirstNonEmptyListStatus++)
	{
		if (pDrlgRoom->wRoomsInList[nFirstNonEmptyListStatus] != 0)
		{
			return (enum D2DrlgRoomStatus)nFirstNonEmptyListStatus;
		}
	}
	return nMaxStatus;
}

//D2Common.0x6FD733D0
void __cdecl DRLGACTIVATE_RoomExSetStatus_ClientInRoom(struct D2DrlgRoom* pDrlgRoom)
{
	DRLGACTIVATE_UpdateRoomExStatusImpl(pDrlgRoom, ROOMSTATUS_CLIENT_IN_ROOM);
}

//Helper function
static void DRLGACTIVATE_InitRoomsInitTimeout(struct D2Drlg* pDrlg)
{
	pDrlg->nRoomsInitTimeout = 2 * (DRLG_IsOnClient(pDrlg) == 0) + 5;
}
void DRLGACTIVATE_RoomEx_EnsureHasRoom(struct D2DrlgRoom* pDrlgRoom, bool bInitTimeoutCounter)
{
	if (pDrlgRoom->pRoom == nullptr && !(pDrlgRoom->dwFlags & DRLGROOMFLAG_HAS_ROOM))
	{
		struct D2Drlg* pDrlg = pDrlgRoom->pLevel->pDrlg;
		if (!pDrlgRoom->nRoomsNear)
		{
			sub_6FD77BB0(pDrlg->pMempool, pDrlgRoom);
		}

		DRLGROOMTILE_InitRoomGrids(pDrlgRoom);
		DRLGROOMTILE_AddRoomMapTiles(pDrlgRoom);
		DRLG_CreateRoomForRoomEx(pDrlg, pDrlgRoom);
		++pDrlg->nRoomsInitSinceLastUpdate;
		++pDrlg->nAllocatedRooms;
		if (bInitTimeoutCounter)
		{
			DRLGACTIVATE_InitRoomsInitTimeout(pDrlg);
		}
	}
}

//D2Common.0x6FD73450
void __cdecl DRLGACTIVATE_RoomExSetStatus_ClientInSight(struct D2DrlgRoom* pDrlgRoom)
{
	DRLGACTIVATE_RoomEx_EnsureHasRoom(pDrlgRoom, true);
	DRLGACTIVATE_UpdateRoomExStatusImpl(pDrlgRoom, ROOMSTATUS_CLIENT_IN_SIGHT);
}

//D2Common.0x6FD73550
void __cdecl DRLGACTIVATE_RoomExSetStatus_ClientOutOfSight(struct D2DrlgRoom* pDrlgRoom)
{
	if (pDrlgRoom->dwFlags & DRLGROOMFLAG_TILELIB_LOADED 
		&& (pDrlgRoom->nType != DRLGTYPE_PRESET || (pDrlgRoom->dwFlags & DRLGROOMFLAG_PRESET_UNITS_ADDED) != 0))
	{

		if (DRLGACTIVATE_UpdateRoomExStatusImpl(pDrlgRoom, ROOMSTATUS_CLIENT_OUT_OF_SIGHT)
			&& pDrlgRoom->wRoomsInList[ROOMSTATUS_CLIENT_IN_SIGHT] != 0)
		{
			DRLGACTIVATE_RoomExSetStatus_ClientInSight(pDrlgRoom);
		}
	}
}

//D2Common.0x6FD736F0
void __cdecl DRLGACTIVATE_RoomExSetStatus_Untile(struct D2DrlgRoom* pDrlgRoom)
{
	if (!(pDrlgRoom->dwFlags & DRLGROOMFLAG_TILELIB_LOADED))
	{
		DRLGROOMTILE_LoadDT1FilesForRoom(pDrlgRoom);
	}

	if (pDrlgRoom->nType == DRLGTYPE_PRESET && !(pDrlgRoom->dwFlags & DRLGROOMFLAG_PRESET_UNITS_ADDED))
	{
		DRLGPRESET_SpawnHardcodedPresetUnits(pDrlgRoom);
	}
	DRLGACTIVATE_UpdateRoomExStatusImpl(pDrlgRoom, ROOMSTATUS_UNTILE);
}

//D2Common.0x6FD73790
void __cdecl DRLGACTIVATE_RoomExIdentifyRealStatus(struct D2DrlgRoom* pDrlgRoom)
{
	if (pDrlgRoom->fRoomStatus >= ROOMSTATUS_COUNT || pDrlgRoom->wRoomsInList[pDrlgRoom->fRoomStatus] == 0)
	{
		const enum D2DrlgRoomStatus nFirstStatusWithRefCount = DRLGACTIVATE_RoomExFindFirstStatusWithRefCount(pDrlgRoom, ROOMSTATUS_COUNT);
		if (pDrlgRoom->fRoomStatus != nFirstStatusWithRefCount)
		{
			DRLGACTIVATE_UpdateRoomExStatusImpl(pDrlgRoom, nFirstStatusWithRefCount);
		}
	}
}

//D2Common.0x6FD73880
void __cdecl DRLGACTIVATE_RoomExStatusUnset_Untile(struct D2DrlgRoom* pDrlgRoom)
{
	if (pDrlgRoom->fRoomStatus != ROOMSTATUS_COUNT)
	{
		DRLGACTIVATE_RoomExIdentifyRealStatus(pDrlgRoom);
		
		// We may unload the room if no status is now set
		if (pDrlgRoom->fRoomStatus == ROOMSTATUS_COUNT)
		{
			if (DRLG_IsOnClient(pDrlgRoom->pLevel->pDrlg))
			{
				DRLGROOMTILE_FreeRoom(pDrlgRoom, false);
			}
		}
	}
}

//D2Common.0x6FD73A30
void __cdecl DRLGACTIVATE_RoomExPropagateSetStatus(void* pMemPool, struct D2DrlgRoom* pDrlgRoom, uint8_t nStatus)
{
	if (pDrlgRoom->nRoomsNear == 0)
	{
		sub_6FD77BB0(pMemPool, pDrlgRoom);
	}

	for (int i = 0; i < pDrlgRoom->nRoomsNear; ++i)
	{
		struct D2DrlgRoom* pNearRoom = pDrlgRoom->ppRoomsNear[i];
		if (nStatus + 1 < ROOMSTATUS_COUNT)
		{
			DRLGACTIVATE_RoomExPropagateSetStatus(pMemPool, pNearRoom, nStatus + 1);
		}

		if (pNearRoom->fRoomStatus >= nStatus)
		{
			const enum D2DrlgRoomStatus nFirstStatusWithRefCount = DRLGACTIVATE_RoomExFindFirstStatusWithRefCount(pNearRoom, (enum D2DrlgRoomStatus)(nStatus));
			if (nFirstStatusWithRefCount == nStatus)
			{
				gRoomExSetStatus[nStatus](pNearRoom);
			}
		}
		++pNearRoom->wRoomsInList[nStatus];
	}
}

//D2Common.0x6FD73BE0
void __cdecl DRLGACTIVATE_RoomExPropagateUnsetStatus(struct D2DrlgRoom* pDrlgRoom, uint8_t nStatus)
{
	for (int i = 0; i < pDrlgRoom->nRoomsNear; ++i)
	{
		if (pDrlgRoom->ppRoomsNear[i])
		{
			--pDrlgRoom->ppRoomsNear[i]->wRoomsInList[nStatus];

			gRoomExUnsetStatus[nStatus](pDrlgRoom->ppRoomsNear[i]);

			if (nStatus + 1 < ROOMSTATUS_COUNT)
			{
				DRLGACTIVATE_RoomExPropagateUnsetStatus(pDrlgRoom->ppRoomsNear[i], nStatus + 1);
			}
		}
	}
}

// Helper functions
static void DRLGACTIVATE_RoomSetAndPropagateStatus(struct D2DrlgRoom* pDrlgRoom, enum D2DrlgRoomStatus nStatus)
{
	DRLGACTIVATE_RoomExPropagateSetStatus(pDrlgRoom->pLevel->pDrlg->pMempool, pDrlgRoom, nStatus + 1);
	if (pDrlgRoom->fRoomStatus >= nStatus)
	{
		const enum D2DrlgRoomStatus nFirstStatusWithRefCount = DRLGACTIVATE_RoomExFindFirstStatusWithRefCount(pDrlgRoom, nStatus);
		if (nFirstStatusWithRefCount == nStatus)
		{
			gRoomExSetStatus[nStatus](pDrlgRoom);
		}
	}
	++pDrlgRoom->wRoomsInList[nStatus];
}

static void DRLGACTIVATE_RoomUnsetAndPropagateStatus(struct D2DrlgRoom* pDrlgRoom, enum D2DrlgRoomStatus nStatus)
{
	if (pDrlgRoom->wRoomsInList[nStatus] != 0)
	{
		--pDrlgRoom->wRoomsInList[nStatus];

		gRoomExUnsetStatus[nStatus](pDrlgRoom);

		for (int i = 0; i < pDrlgRoom->nRoomsNear; ++i)
		{
			struct D2DrlgRoom * pNearRoom = pDrlgRoom->ppRoomsNear[i];
			if (pNearRoom)
			{
				--pNearRoom->wRoomsInList[nStatus + 1];
				gRoomExUnsetStatus[nStatus + 1](pNearRoom);
				DRLGACTIVATE_RoomExPropagateUnsetStatus(pNearRoom, nStatus + 2);
			}
		}
	}
}

//D2Common.0x6FD739A0
void __cdecl DRLGACTIVATE_SetClientIsInSight(struct D2Drlg* pDrlg, int nLevelId, int nX, int nY, struct D2DrlgRoom* pDrlgRoomHint)
{
	struct D2DrlgLevel* pLevel = DRLG_GetLevel(pDrlg, nLevelId);
	if (pDrlgRoomHint && pDrlgRoomHint->pLevel->nLevelId != nLevelId)
	{
		pDrlgRoomHint = nullptr;
	}
	struct D2DrlgRoom* pDrlgRoom = DRLG_GetRoomExFromCoordinates(nX, nY, pDrlg, pDrlgRoomHint, pLevel);

	if (pDrlgRoom->wRoomsInList[ROOMSTATUS_CLIENT_IN_SIGHT] == 0)
	{
		DRLGACTIVATE_RoomSetAndPropagateStatus(pDrlgRoom, ROOMSTATUS_CLIENT_IN_SIGHT);
	}
}

//D2Common.0x6FD73B40
void __cdecl DRLGACTIVATE_UnsetClientIsInSight(struct D2Drlg* pDrlg, int nLevelId, int nX, int nY, struct D2DrlgRoom* pDrlgRoomHint)
{
	struct D2DrlgLevel* pLevel = DRLG_GetLevel(pDrlg, nLevelId);
	if (pDrlgRoomHint && pDrlgRoomHint->pLevel->nLevelId != nLevelId)
	{
		pDrlgRoomHint = nullptr;
	}

	struct D2DrlgRoom* pDrlgRoom = DRLG_GetRoomExFromCoordinates(nX, nY, pDrlg, pDrlgRoomHint, pLevel);
	if (pDrlgRoom)
	{
		DRLGACTIVATE_RoomUnsetAndPropagateStatus(pDrlgRoom, ROOMSTATUS_CLIENT_IN_SIGHT);
	}
}


//D2Common.0x6FD73C40
void __cdecl DRLGACTIVATE_ChangeClientRoom(struct D2DrlgRoom* pPreviousRoom, struct D2DrlgRoom* pNewRoom)
{
	if (pPreviousRoom == pNewRoom)
	{
		return;
	}

	if (pNewRoom)
	{
		DRLGACTIVATE_RoomSetAndPropagateStatus(pNewRoom, ROOMSTATUS_CLIENT_IN_ROOM);
	}

	if (pPreviousRoom)
	{
		DRLGACTIVATE_RoomUnsetAndPropagateStatus(pPreviousRoom, ROOMSTATUS_CLIENT_IN_ROOM);
	}
}

//D2Common.0x6FD73CF0
void __cdecl DRLGACTIVATE_InitializeRoomEx(struct D2DrlgRoom* pDrlgRoom)
{
	if (!(pDrlgRoom->dwFlags & DRLGROOMFLAG_TILELIB_LOADED))
	{
		DRLGROOMTILE_LoadDT1FilesForRoom(pDrlgRoom);
	}

	if (!(pDrlgRoom->dwFlags & DRLGROOMFLAG_PRESET_UNITS_ADDED) && (pDrlgRoom->nType == DRLGTYPE_PRESET))
	{
		DRLGPRESET_SpawnHardcodedPresetUnits(pDrlgRoom);
	}

	DRLGACTIVATE_RoomEx_EnsureHasRoom(pDrlgRoom, false);
}

//D2Common.0x6FD73D80
struct D2ActiveRoom* __cdecl DRLGACTIVATE_StreamRoomAtCoords(struct D2Drlg* pDrlg, int nX, int nY)
{
	struct D2DrlgRoom* pDrlgRoom = DRLG_GetRoomExFromCoordinates(nX, nY, pDrlg, 0, 0);
	if (pDrlgRoom)
	{
		DRLGACTIVATE_InitializeRoomEx(pDrlgRoom);
		return pDrlgRoom->pRoom;
	}
	return nullptr;
}

//D2Common.0x6FD73E30
void __cdecl DRLGACTIVATE_InitializeRoomExStatusLists(struct D2Drlg* pDrlg)
{
	for (int nStatus = 0; nStatus < ROOMSTATUS_COUNT; ++nStatus)
	{
		struct D2DrlgRoom* pDrlgRoomStatusList = &pDrlg->tStatusRoomsLists[nStatus];
		pDrlgRoomStatusList->fRoomStatus = nStatus;
		pDrlgRoomStatusList->pStatusNext = pDrlgRoomStatusList;
		pDrlgRoomStatusList->pStatusPrev = pDrlgRoomStatusList;
	}
}

//Helper function
static struct D2DrlgRoom* DRLGACTIVATE_RoomExStatusList_GetFirst(struct D2Drlg* pDrlg, enum D2DrlgRoomStatus nStatus)
{
	const struct D2DrlgRoom* pStatusListHead = &pDrlg->tStatusRoomsLists[nStatus];
	if (pStatusListHead != pStatusListHead->pStatusNext) // If not empty
	{
		return pStatusListHead->pStatusNext;
	}
	return nullptr;
}

//D2Common.0x6FD73E60
struct D2ActiveRoom* __cdecl DRLGACTIVATE_GetARoomInClientSight(struct D2Drlg* pDrlg)
{
	struct D2DrlgRoom* pDrlgRoom = DRLGACTIVATE_RoomExStatusList_GetFirst(pDrlg, ROOMSTATUS_CLIENT_IN_ROOM);
	if (pDrlgRoom)
	{
		return pDrlgRoom->pRoom;
	}
	pDrlgRoom = DRLGACTIVATE_RoomExStatusList_GetFirst(pDrlg, ROOMSTATUS_CLIENT_IN_SIGHT);
	if (pDrlgRoom)
	{
		return pDrlgRoom->pRoom;
	}
	return nullptr;
}

//D2Common.0x6FD73E90
struct D2ActiveRoom* __cdecl DRLGACTIVATE_GetARoomInSightButWithoutClient(struct D2Drlg* pDrlg, struct D2DrlgRoom* pDrlgRoom)
{
	struct D2DrlgRoom* pNextStatusRoom = pDrlgRoom->pStatusNext;
	if (pNextStatusRoom)
	{
		if (pDrlgRoom->fRoomStatus != ROOMSTATUS_CLIENT_IN_ROOM || pNextStatusRoom != &pDrlg->tStatusRoomsLists[ROOMSTATUS_CLIENT_IN_ROOM])
		{
			return pNextStatusRoom->pRoom;
		}

		struct D2DrlgRoom* pFirstRoomInSight = DRLGACTIVATE_RoomExStatusList_GetFirst(pDrlg, ROOMSTATUS_CLIENT_IN_SIGHT);
		if (pFirstRoomInSight)
		{
			return pFirstRoomInSight->pRoom;
		}
	}

	return nullptr;
}

//D2Common.0x6FD73EF0 (#10015)
void __cdecl DRLGACTIVATE_GetRoomsAllocationStats(int* pOutStatsClientAllocatedRooms, int* pOutStatsClientFreedRooms, int* pOutStatsAllocatedRooms, int* pOutStatsFreedRooms)
{
	*pOutStatsClientAllocatedRooms = gStatsClientAllocatedRooms;
	*pOutStatsClientFreedRooms = gStatsClientFreedRooms;
	*pOutStatsAllocatedRooms = gStatsAllocatedRooms;
	*pOutStatsFreedRooms = gStatsFreedRooms;
}

//D2Common.0x6FD73F20 (#10003)
void __cdecl DRLGACTIVATE_Update(struct D2Drlg* pDrlg)
{
	if (DRLG_IsOnClient(pDrlg))
	{
		gStatsClientAllocatedRooms = pDrlg->nAllocatedRooms;
		gStatsClientFreedRooms = pDrlg->nFreedRooms;
	}
	else
	{
		gStatsAllocatedRooms = pDrlg->nAllocatedRooms;
		gStatsFreedRooms = pDrlg->nFreedRooms;
	}

	if (pDrlg->nRoomsInitSinceLastUpdate > 1)
	{
		pDrlg->nRoomsInitSinceLastUpdate = 0;
		return;
	}

	--pDrlg->nRoomsInitTimeout;

	if (pDrlg->nRoomsInitTimeout == 0)
	{
		DRLGACTIVATE_InitRoomsInitTimeout(pDrlg);

		if (!pDrlg->pDrlgRoom || pDrlg->pDrlgRoom->fRoomStatus != ROOMSTATUS_CLIENT_OUT_OF_SIGHT)
		{
			pDrlg->pDrlgRoom = pDrlg->tStatusRoomsLists[ROOMSTATUS_CLIENT_OUT_OF_SIGHT].pStatusNext;
		}


		struct D2DrlgRoom* pDrlgRoomExListHead = pDrlg->pDrlgRoom;
		if (pDrlgRoomExListHead)
		{
			struct D2DrlgRoom* pCurRoomEx;
			for (pCurRoomEx = pDrlgRoomExListHead ; pCurRoomEx != pDrlgRoomExListHead ; pCurRoomEx = pCurRoomEx->pStatusNext)
			{
				if (pCurRoomEx != &pDrlg->tStatusRoomsLists[ROOMSTATUS_CLIENT_OUT_OF_SIGHT])
				{
					DRLGACTIVATE_RoomEx_EnsureHasRoom(pCurRoomEx, false);
				}
				if (pDrlg->nRoomsInitSinceLastUpdate != 0)
				{
					break;
				}
			}

			pDrlg->pDrlgRoom = pCurRoomEx;
			pDrlg->nRoomsInitSinceLastUpdate = 0;
		}
	}
}

//D2Common.0x6FD74060
BOOL __cdecl DRLGACTIVATE_TestRoomCanUnTile(struct D2DrlgRoom* pDrlgRoom)
{
	if (pDrlgRoom->dwFlags & DRLGROOMFLAG_HASPORTAL)
	{
		return FALSE;
	}

	D2_ASSERT(!DRLG_IsOnClient(DRLGROOM_GetDrlgFromRoomEx(pDrlgRoom)));

	if (pDrlgRoom->fRoomStatus <= 1)
	{
		return FALSE;
	}

	if (DRLG_IsTownLevel(pDrlgRoom->pLevel->nLevelId) || pDrlgRoom->pLevel->nLevelId == LEVEL_ROCKYSUMMIT)
	{
		for (struct D2DrlgRoom* pCurrentRoomEx = pDrlgRoom->pLevel->pFirstRoomEx; pCurrentRoomEx; pCurrentRoomEx = pCurrentRoomEx->pDrlgRoomNext)
		{
			if (pCurrentRoomEx->fRoomStatus <= 1)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

//D2Common.0x6FD740F0
void __cdecl DRLGACTIVATE_ToggleHasPortalFlag(struct D2DrlgRoom* pDrlgRoom, BOOL bReset)
{
	if (bReset)
	{
		pDrlgRoom->dwFlags &= ~DRLGROOMFLAG_HASPORTAL;
	}
	else
	{
		pDrlgRoom->dwFlags |= DRLGROOMFLAG_HASPORTAL;
	}
}

//D2Common.0x6FD74110
uint8_t __cdecl DRLGACTIVATE_GetRoomStatusFlags(struct D2DrlgRoom* pDrlgRoom)
{
	return pDrlgRoom->fRoomStatus;
}
