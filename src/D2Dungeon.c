#include "D2Dungeon.h"

#include "D2Collision.h"
#include "D2DataTbls.h"
#include <DataTbls/LevelsIds.h>
#include "Drlg/D2DrlgActivate.h"
#include "Drlg/D2DrlgDrlg.h"
#include "Drlg/D2DrlgDrlgAnim.h"
#include "Drlg/D2DrlgDrlgLogic.h"
#include "Drlg/D2DrlgDrlgRoom.h"
#include "Drlg/D2DrlgDrlgWarp.h"
#include "Drlg/D2DrlgPreset.h"
#include "D2Environment.h"
#include "Units/UnitRoom.h"
#include "Units/Units.h"
#include "D2Seed.h"


//D2Common.0x6FD8B8A0 (#10038)
struct D2DrlgAct* __stdcall DUNGEON_AllocAct(uint8_t nAct, uint32_t nInitSeed, BOOL bClient, struct D2Game* pGame, uint8_t nDifficulty, void* pMemPool, int nTownLevelId, AUTOMAPFN pfAutoMap, TOWNAUTOMAPFN pfTownAutoMap)
{
	struct D2DrlgAct* pAct = D2_CALLOC_STRC_POOL(pMemPool, struct D2DrlgAct);

	pAct->dwInitSeed = nInitSeed;
	pAct->bClient = bClient;
	pAct->nAct = nAct;
	pAct->pMemPool = pMemPool;

	if (!bClient)
	{
		pAct->nTownId = nTownLevelId;
	}

	pAct->pDrlg = DRLG_AllocDrlg(pAct, nAct, 0, nInitSeed, (bClient ? LEVEL_NONE : nTownLevelId), (bClient ? DRLGFLAG_ONCLIENT : 0), pGame, nDifficulty, pfAutoMap, pfTownAutoMap);
	pAct->pEnvironment = ENVIRONMENT_AllocDrlgEnvironment(pMemPool);

	DRLGANIM_InitCache(pAct->pDrlg, &pAct->pTileData);

	return pAct;
}

//D2Common.0x6FD8B950 (#10039)
void __stdcall DUNGEON_FreeAct(struct D2DrlgAct* pAct)
{
	struct D2ActiveRoom* pRoom = NULL;
	struct D2ActiveRoom* pNext = NULL;

	D2_ASSERT(pAct);

	if (pAct->pDrlg)
	{
		DRLG_FreeDrlg(pAct->pDrlg);
		pAct->pDrlg = NULL;
	}

	pRoom = pAct->pRoom;
	while (pRoom)
	{
		pNext = pRoom->pRoomNext;
		DUNGEON_FreeRoom(pAct->pMemPool, pRoom);
		pRoom = pNext;
	}

	if (pAct->pEnvironment)
	{
		ENVIRONMENT_FreeDrlgEnvironment(pAct->pMemPool, pAct->pEnvironment);
		pAct->pEnvironment = NULL;
	}

	D2_FREE_POOL(pAct->pMemPool, pAct);
}

//D2Common.0x6FD8B9D0
void* __fastcall DUNGEON_GetMemPoolFromAct(struct D2DrlgAct* pAct)
{
	return pAct->pMemPool;
}

//D2Common.0x6FD8B9E0 (#10026)
void __stdcall DUNGEON_ToggleRoomTilesEnableFlag(struct D2ActiveRoom* pRoom, BOOL bEnabled)
{
	D2_ASSERT(pRoom);

	DRLGWARP_ToggleRoomTilesEnableFlag(pRoom->pDrlgRoom, bEnabled);
}

//D2Common.0x6FD8BA20 (#10027)
struct D2Unit* __stdcall DUNGEON_GetWarpTileFromRoomAndSourceLevelId(struct D2ActiveRoom* pRoom, int nSourceLevel, struct D2LvlWarpTxt** ppLvlWarpTxtRecord)
{
	D2_ASSERT(pRoom);

	int nDestinationLevel = 0;
	struct D2ActiveRoom* pDestRoom = DRLGWARP_GetDestinationRoom(pRoom->pDrlgRoom, nSourceLevel, &nDestinationLevel, ppLvlWarpTxtRecord);
	D2_ASSERT(pDestRoom);

	for (struct D2Unit* pTile = pDestRoom->pUnitFirst; pTile; pTile = pTile->pRoomNext)
	{
		if (pTile->dwUnitType == UNIT_TILE && pTile->dwClassId == nDestinationLevel)
		{
			return pTile;
		}
	}

	return nullptr;
}

//D2Common.0x6FD8BAB0 (#10028)
struct D2LvlWarpTxt* __stdcall DUNGEON_GetLvlWarpTxtRecordFromRoomAndUnit(struct D2ActiveRoom* pRoom, struct D2Unit* pUnit)
{
	D2_ASSERT(pRoom);

	return DRLGWARP_GetLvlWarpTxtRecordFromUnit(pRoom->pDrlgRoom, pUnit);
}

//D2Common.0x6FD8BAF0 (#10030)
struct D2DrlgTileData* __stdcall DUNGEON_GetFloorTilesFromRoom(struct D2ActiveRoom* pRoom, int* pFloorCount)
{
	if (pRoom && pRoom->pRoomTiles)
	{
		*pFloorCount = pRoom->pRoomTiles->nFloors;
		return pRoom->pRoomTiles->pFloorTiles;
	}

	*pFloorCount = 0;
	return NULL;
}

//D2Common.0x6FD8BB20 (#10031)
struct D2DrlgTileData* __stdcall DUNGEON_GetWallTilesFromRoom(struct D2ActiveRoom* pRoom, int* pWallCount)
{
	D2_ASSERT(pRoom);

	*pWallCount = pRoom->pRoomTiles->nWalls;
	return pRoom->pRoomTiles->pWallTiles;
}

//D2Common.0x6FD8BB60 (#10032)
struct D2DrlgTileData* __stdcall DUNGEON_GetRoofTilesFromRoom(struct D2ActiveRoom* pRoom, int* pRoofCount)
{
	D2_ASSERT(pRoom);

	*pRoofCount = pRoom->pRoomTiles->nRoofs;
	return pRoom->pRoomTiles->pRoofTiles;
}

//D2Common.0x6FD8BBA0 (#10033)
struct D2DrlgTileData* __stdcall DUNGEON_GetTileDataFromAct(struct D2DrlgAct* pAct)
{
	return &pAct->pTileData;
}

//D2Common.0x6FD8BBB0 (#10034)
void __stdcall DUNGEON_GetRoomCoordinates(struct D2ActiveRoom* pRoom, struct D2DrlgCoords* pCoords)
{
	D2_ASSERT(pCoords);

	if (pRoom)
	{
		memcpy(pCoords, &pRoom->tCoords, sizeof(struct D2DrlgCoords));
	}
	else
	{
		FOG_Trace(" ----- RJS NOTE: Would have crashed, see code");
		memset(pCoords, 0x00, sizeof(struct D2DrlgCoords));
	}
}

//D2Common.0x6FD8BC10 (#10035)
void __stdcall DUNGEON_GetAdjacentRoomsListFromRoom(struct D2ActiveRoom* pRoom, struct D2ActiveRoom*** pppRoomList, int* pNumRooms)
{
	D2_ASSERT(pRoom);

	*pNumRooms = pRoom->nNumRooms;
	*pppRoomList = pRoom->ppRoomList;
}

//D2Common.0x6FD8BC50
struct D2ActiveRoom* __fastcall DUNGEON_AllocRoom(struct D2DrlgAct* pAct, struct D2DrlgRoom* pDrlgRoom, struct D2DrlgCoords* pDrlgCoords, struct D2DrlgRoomTiles* pRoomTiles, int nLowSeed, uint32_t dwFlags)
{
	D2_ASSERT(pAct);

	struct D2ActiveRoom* pRoom = D2_CALLOC_STRC_POOL(pAct->pMemPool, struct D2ActiveRoom);

	pRoom->dwFlags = dwFlags;

	SEED_InitLowSeed(&pRoom->pSeed, nLowSeed);

	pRoom->pDrlgRoom = pDrlgRoom;
	memcpy(&pRoom->tCoords, pDrlgCoords, sizeof(struct D2DrlgCoords));
	pRoom->pRoomTiles = pRoomTiles;
	pRoom->pRoomNext = pAct->pRoom;
	pAct->pRoom = pRoom;
	pAct->bHasPendingRoomsUpdates = TRUE;
	pRoom->pAct = pAct;

	DRLGROOM_SetRoom(pDrlgRoom, pRoom);

	pRoom->ppRoomList = (struct D2ActiveRoom**)D2_ALLOC_POOL(pAct->pMemPool, sizeof(struct D2ActiveRoom*) * pRoom->pDrlgRoom->nRoomsNear);
	pRoom->nNumRooms = DRLGROOM_ReorderNearRoomList(pRoom->pDrlgRoom, pRoom->ppRoomList);

	for (int i = 0; i < pRoom->nNumRooms; ++i)
	{
		struct D2ActiveRoom* pAdjacentRoom = pAdjacentRoom = pRoom->ppRoomList[i];
		D2_ASSERT(pAdjacentRoom);

		if (pAdjacentRoom != pRoom)
		{
			pAdjacentRoom->nNumRooms = DRLGROOM_ReorderNearRoomList(pAdjacentRoom->pDrlgRoom, pAdjacentRoom->ppRoomList);
		}
	}

	COLLISION_AllocRoomCollisionGrid(pAct->pMemPool, pRoom);

	if (pAct->pfnActCallBack)
	{
		pAct->pfnActCallBack(pRoom);
	}

	return pRoom;
}

//D2Common.0x6FD8BD90 (#10040)
BOOL __stdcall DUNGEON_DoRoomsTouchOrOverlap(struct D2ActiveRoom* ptFirst, struct D2ActiveRoom* ptSecond)
{
	D2_ASSERT(ptFirst);
	D2_ASSERT(ptSecond);

	return ptFirst->tCoords.nTileXPos <= ptSecond->tCoords.nTileXPos + ptSecond->tCoords.nTileWidth
		&& ptFirst->tCoords.nTileXPos + ptFirst->tCoords.nTileWidth >= ptSecond->tCoords.nTileXPos
		&& ptFirst->tCoords.nTileYPos <= ptSecond->tCoords.nTileYPos + ptSecond->tCoords.nTileHeight
		&& ptFirst->tCoords.nTileYPos + ptFirst->tCoords.nTileHeight >= ptSecond->tCoords.nTileYPos;
}

//D2Common.0x6FD8BE30 (#10043)
BOOL __stdcall DUNGEON_AreTileCoordinatesInsideRoom(struct D2ActiveRoom* pRoom, int nX, int nY)
{
	D2_ASSERT(pRoom);

	return nX >= pRoom->tCoords.nTileXPos && nX < pRoom->tCoords.nTileXPos + pRoom->tCoords.nTileWidth
		&& nY >= pRoom->tCoords.nTileYPos && nY < pRoom->tCoords.nTileYPos + pRoom->tCoords.nTileHeight;
}

//D2Common.0x6FD8BE90 (#10048)
int __stdcall DUNGEON_CheckRoomsOverlapping_BROKEN(struct D2ActiveRoom* pPrimary, struct D2ActiveRoom* pSecondary)
{
	//This was probably meant to check if 2 rooms are overlaping / adjacent, but pSecondary is unused.
	//In the end, this always returns 4 unless width or height is 0
	//Probably why this is not used since it's broken.
	D2_MAYBE_UNUSED(pSecondary);
	D2_ASSERT(pPrimary); // pRoom is pPrimary in original code

	if (pPrimary->tCoords.nTileWidth + pPrimary->tCoords.nTileXPos >= pPrimary->tCoords.nTileXPos
		&& pPrimary->tCoords.nTileYPos + pPrimary->tCoords.nTileHeight >= pPrimary->tCoords.nTileYPos)
	{
		if (pPrimary->tCoords.nTileXPos == pPrimary->tCoords.nTileWidth + pPrimary->tCoords.nTileXPos)
		{
			return 1;
		}
		else if (pPrimary->tCoords.nTileYPos == pPrimary->tCoords.nTileYPos + pPrimary->tCoords.nTileHeight)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}

	return 0;
}

//D2Commmon.0x6FD8BF00 (#10051)
struct D2ActiveRoom* __stdcall DUNGEON_FindRoomByTileCoordinates(struct D2DrlgAct* pAct, int nX, int nY)
{
	for (struct D2ActiveRoom* pRoom = pAct->pRoom; pRoom; pRoom = pRoom->pRoomNext)
	{
		if(DUNGEON_AreTileCoordinatesInsideRoom(pRoom, nX, nY))
		{
			return pRoom;
		}
	}
	return nullptr;
}

//D2Common.0x6FD8BF50 (#10050)
struct D2ActiveRoom* __stdcall DUNGEON_GetAdjacentRoomByTileCoordinates(struct D2ActiveRoom* pRoom, int nX, int nY)
{
	struct D2ActiveRoom* pTemp = NULL;

	D2_ASSERT(pRoom);

	for (int i = 0; i < pRoom->nNumRooms; ++i)
	{
		pTemp = pRoom->ppRoomList[i];
		D2_ASSERT(pTemp);
		if (DUNGEON_AreTileCoordinatesInsideRoom(pTemp, nX, nY))
		{
			return pTemp;
		}
	}

	return NULL;
}

//D2Common.0x6FD8BFF0 (#10049)
void __stdcall DUNGEON_CallRoomCallback(struct D2ActiveRoom* pRoom, ROOMCALLBACKFN pfnRoomCallback, void* pArgs)
{
	D2_ASSERT(pRoom);

	D2_ASSERT(!IsBadCodePtr((FARPROC)pfnRoomCallback));

	for (int i = 0; i < pRoom->nNumRooms; ++i)
	{
		if (!pfnRoomCallback(pRoom->ppRoomList[i], pArgs))
		{
			break;
		}
	}
}

//D2Common.0x6FD8C080 (#10052)
void __stdcall D2Common_10052(struct D2ActiveRoom* pRoom, RECT* pRect)
{
	int nTemp = 0;

	D2_ASSERT(pRoom);

	DUNGEON_GameToClientTileDrawPositionCoords(pRoom->tCoords.nTileXPos                            , pRoom->tCoords.nTileYPos                             , &nTemp             , (int*)&pRect->top);
	DUNGEON_GameToClientTileDrawPositionCoords(pRoom->tCoords.nTileXPos                            , pRoom->tCoords.nTileHeight + pRoom->tCoords.nTileYPos, (int*)&pRect->left , &nTemp);
	DUNGEON_GameToClientTileDrawPositionCoords(pRoom->tCoords.nTileXPos + pRoom->tCoords.nTileWidth, pRoom->tCoords.nTileYPos                             , (int*)&pRect->right, &nTemp);
	DUNGEON_GameToClientTileDrawPositionCoords(pRoom->tCoords.nTileXPos + pRoom->tCoords.nTileWidth, pRoom->tCoords.nTileHeight + pRoom->tCoords.nTileYPos, &nTemp             , (int*)&pRect->bottom);

	D2_ASSERT(pRect->top <= pRect->bottom);
	D2_ASSERT(pRect->left <= pRect->right);
}

//D2Common.0x6FD8C170 (#10053)
void __stdcall DUNGEON_GetSubtileRect(struct D2ActiveRoom* pRoom, RECT* pRect)
{
	D2_ASSERT(pRoom);

	pRect->top = pRoom->tCoords.nSubtileY;
	pRect->bottom = pRoom->tCoords.nSubtileY + pRoom->tCoords.nSubtileHeight;
	pRect->left = pRoom->tCoords.nSubtileX;
	pRect->right = pRoom->tCoords.nSubtileWidth + pRoom->tCoords.nSubtileX;

	D2_ASSERT(pRect->top <= pRect->bottom);
	D2_ASSERT(pRect->left <= pRect->right);
}

//D2Common.0x6FD8C210 (#10054)
void __stdcall DUNGEON_GetRGB_IntensityFromRoom(struct D2ActiveRoom* pRoom, uint8_t* pIntensity, uint8_t* pRed, uint8_t* pGreen, uint8_t* pBlue)
{
	return DRLGROOM_GetRGB_IntensityFromRoomEx(pRoom->pDrlgRoom, pIntensity, pRed, pGreen, pBlue);
}

//D2Common.0x6FD8C240 (#10041)
struct D2ActiveRoom* __stdcall DUNGEON_FindRoomBySubtileCoordinates(struct D2DrlgAct* pAct, int nX, int nY)
{
	if (pAct)
	{
		for (struct D2ActiveRoom* pRoom = pAct->pRoom; pRoom; pRoom = pRoom->pRoomNext)
		{
			if (DungeonTestRoomGame(pRoom, nX, nY))
			{
				return pRoom;
			}
		}
	}

	return NULL;
}

//D2Common.0x6FD8C290
BOOL __fastcall DUNGEON_AreSubtileCoordinatesInsideRoom(struct D2DrlgCoords* pDrlgCoords, int nX, int nY)
{
	D2_ASSERT(pDrlgCoords);

	return nX >= pDrlgCoords->nSubtileX && nX < pDrlgCoords->nSubtileX + pDrlgCoords->nSubtileWidth && nY >= pDrlgCoords->nSubtileY && nY < pDrlgCoords->nSubtileY + pDrlgCoords->nSubtileHeight;
}

//D2Common.0x6FD8C2F0 (#10046)
struct D2ActiveRoom* __stdcall DUNGEON_FindActSpawnLocation(struct D2DrlgAct* pAct, int nLevelId, int nTileIndex, int* pX, int* pY)
{
	D2_ASSERT(pAct);

	return sub_6FD788D0(pAct->pDrlg, nLevelId, nTileIndex, pX, pY);
}

//D2Common.0x6FD8C340 (#10045)
struct D2ActiveRoom* __stdcall DUNGEON_FindActSpawnLocationEx(struct D2DrlgAct* pAct, int nLevelId, int nTileIndex, int* pX, int* pY, int nUnitSize)
{
	struct D2ActiveRoom* pNearRoom = NULL;
	struct D2ActiveRoom* pRoom = NULL;
	struct D2Coord pCoord = {};
	int nX = 0;
	int nY = 0;

	D2_ASSERT(pAct);

	pRoom = sub_6FD788D0(pAct->pDrlg, nLevelId, nTileIndex, &nX, &nY);
	if (pRoom)
	{
		DUNGEON_GameTileToSubtileCoords(&nX, &nY);

		pCoord.nX = nX + 3;
		pCoord.nY = nY + 3;

		if (!COLLISION_GetFreeCoordinates(pRoom, &pCoord, nUnitSize, 0x1C09, 0))
		{
			FOG_DisplayAssert("Unable to find spawn location for act start", __FILE__, __LINE__);
			exit(-1);
		}

		*pX = pCoord.nX;
		*pY = pCoord.nY;

		if (DungeonTestRoomGame(pRoom, *pX, *pY))
		{
			return pRoom;
		}

		for (int i = 0; i < pRoom->nNumRooms; ++i)
		{
			pNearRoom = pRoom->ppRoomList[i];
			if (DungeonTestRoomGame(pNearRoom, *pX, *pY))
			{
				return pNearRoom;
			}
		}
	}

	return NULL;
}

//D2Common.0x6FD8C4A0 (#10029)
struct D2Unit* __stdcall DUNGEON_GetFirstUnitInRoom(struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pRoom);

	UNITROOM_SortUnitListByTargetY(pRoom);

	return pRoom->pUnitFirst;
}

//D2Common.0x6FD8C4E0 (#10100)
void __stdcall DUNGEON_IncreaseAlliedCountOfRoom(struct D2ActiveRoom* pRoom)
{
	if (pRoom)
	{
		++pRoom->nAllies;
	}
}

//D2Comon.0x6FD8C4F0 (#10036)
int __stdcall DUNGEON_GetAlliedCountFromRoom(struct D2ActiveRoom* pRoom)
{
	if (pRoom)
	{
		return pRoom->nAllies;
	}

	return 0;
}

//D2Common.0x6FD8C510 (#10101)
void __stdcall DUNGEON_DecreaseAlliedCountOfRoom(struct D2ActiveRoom* pRoom)
{
	if (pRoom)
	{
		D2_ASSERT(pRoom->nAllies > 0);

		--pRoom->nAllies;
	}
}

//D2Common.0x6FD8C550
struct D2Unit** __fastcall DUNGEON_GetUnitListFromRoom(struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pRoom);

	return &pRoom->pUnitFirst;
}

//D2Common.0x6FD8C580
struct D2Unit** __fastcall DUNGEON_GetUnitUpdateListFromRoom(struct D2ActiveRoom* pRoom, BOOL bUpdate)
{
	D2_ASSERT(pRoom);

	if (bUpdate)
	{
		pRoom->pAct->bHasPendingUnitListUpdates = TRUE;
	}

	return &pRoom->pUnitUpdate;
}

//D2Common.0x6FD8C5C0 (#10055)
struct D2PresetUnit* __stdcall DUNGEON_GetPresetUnitsFromRoom(struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pRoom);

	return DRLGROOM_GetPresetUnits(pRoom->pDrlgRoom);
}

//D2Common.0x6FD8C600
struct D2RoomCollisionGrid* __fastcall DUNGEON_GetCollisionGridFromRoom(struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pRoom);

	return pRoom->pCollisionGrid;
}

//D2Common.0x6FD8C630
void __fastcall DUNGEON_SetCollisionGridInRoom(struct D2ActiveRoom* pRoom, struct D2RoomCollisionGrid* pCollisionGrid)
{
	D2_ASSERT(pRoom);

	pRoom->pCollisionGrid = pCollisionGrid;
}

//D2Common.0x6FD8C660 (#10063)
void __stdcall DUNGEON_SetClientIsInSight(struct D2DrlgAct* pAct, int nLevelId, int nX, int nY, struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pAct);

	DRLGACTIVATE_SetClientIsInSight(pAct->pDrlg, nLevelId, nX, nY, pRoom ? pRoom->pDrlgRoom : nullptr);
}

//D2Common.0x6FD8C6B0 (#10064)
void __stdcall DUNGEON_UnsetClientIsInSight(struct D2DrlgAct* pAct, int nLevelId, int nX, int nY, struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pAct);

	DRLGACTIVATE_UnsetClientIsInSight(pAct->pDrlg, nLevelId, nX, nY, pRoom ? pRoom->pDrlgRoom : nullptr);
}

//D2Common.0x6FD8C700 (#10062)
void __stdcall DUNGEON_ChangeClientRoom(struct D2ActiveRoom* pRoom1, struct D2ActiveRoom* pRoom2)
{
	DRLGACTIVATE_ChangeClientRoom(pRoom1 ? pRoom1->pDrlgRoom : nullptr, pRoom2 ? pRoom2->pDrlgRoom : nullptr);
}

//D2Common.0x6FD8C730 (#10065)
struct D2ActiveRoom* __stdcall DUNGEON_StreamRoomAtCoords(struct D2DrlgAct* pAct, int nX, int nY)
{
	D2_ASSERT(pAct);

	return DRLGACTIVATE_StreamRoomAtCoords(pAct->pDrlg, nX, nY);
}

//D2Common.0x6FD8C770 (#10056)
struct D2ActiveRoom* __stdcall DUNGEON_GetRoomFromAct(struct D2DrlgAct* pAct)
{
	D2_ASSERT(pAct);

	return pAct->pRoom;
}

//D2Common.0x6FD8C7A0 (#10057)
int __stdcall DUNGEON_GetLevelIdFromRoom(struct D2ActiveRoom* pRoom)
{
	if (pRoom)
	{
		return DRLGROOM_GetLevelId(pRoom->pDrlgRoom);
	}

	return 0;
}

//D2Common.0x6FD8C7C0 (#10058)
int __stdcall DUNGEON_GetWarpDestinationLevel(struct D2ActiveRoom* pRoom, int nSourceLevel)
{
	if (pRoom)
	{
		return DRLGROOM_GetWarpDestinationLevel(pRoom->pDrlgRoom, nSourceLevel);
	}

	return 0;
}

//D2Common.0x6FD8C7E0 (#10059)
int __stdcall DUNGEON_GetLevelIdFromPopulatedRoom(struct D2ActiveRoom* pRoom)
{
	if (pRoom)
	{
		return DRLGROOM_GetLevelIdFromPopulatedRoom(pRoom->pDrlgRoom);
	}

	return 0;
}

//D2Common.0x6FD8C800 (#10060)
BOOL __stdcall DUNGEON_HasWaypoint(struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pRoom);

	return DRLGROOM_HasWaypoint(pRoom->pDrlgRoom);
}

//D2Common.0x6FD8C840 (#10061)
const char* __stdcall DUNGEON_GetPickedLevelPrestFilePathFromRoom(struct D2ActiveRoom* pRoom)
{
	if (pRoom)
	{
		return DRLGROOM_GetPickedLevelPrestFilePathFromRoomEx(pRoom->pDrlgRoom);
	}

	return NULL;
}

//D2Common.0x6FD8C860 (#10066)
void __stdcall DUNGEON_AllocDrlgDelete(struct D2ActiveRoom* pRoom, int nUnitType, D2UnitGUID nUnitGUID)
{
	struct D2DrlgDelete* pDrlgDelete = NULL;

	if (pRoom)
	{
		pDrlgDelete = D2_ALLOC_STRC_POOL(pRoom->pAct->pMemPool, struct D2DrlgDelete);
		pDrlgDelete->nUnitType = nUnitType;
		pDrlgDelete->nUnitGUID = nUnitGUID;
		pDrlgDelete->pNext = pRoom->pDrlgDelete;
		pRoom->pDrlgDelete = pDrlgDelete;
		pRoom->pAct->bHasPendingRoomDeletions = TRUE;
	}
}

//D2Common.0x6FD8C8B0 (#10067)
void __stdcall DUNGEON_FreeDrlgDelete(struct D2ActiveRoom* pRoom)
{
	struct D2DrlgDelete* pNext = NULL;

	D2_ASSERT(pRoom);

	for (struct D2DrlgDelete* pDrlgDelete = pRoom->pDrlgDelete; pDrlgDelete; pDrlgDelete = pNext)
	{
		pNext = pDrlgDelete->pNext;
		D2_FREE_POOL(pRoom->pAct->pMemPool, pDrlgDelete);
	}

	pRoom->pDrlgDelete = NULL;
}

//D2Common.0x6FD8C910 (#10068)
struct D2DrlgDelete* __stdcall DUNGEON_GetDrlgDeleteFromRoom(struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pRoom);

	return pRoom->pDrlgDelete;
}

//D2Common.0x6FD8C940 (#10069)
struct D2ActiveRoom* __stdcall DUNGEON_GetARoomInClientSight(struct D2DrlgAct* pAct)
{
	D2_ASSERT(pAct);

	return DRLGACTIVATE_GetARoomInClientSight(pAct->pDrlg);
}

//D2Common.0x6FD8C980 (#10070)
struct D2ActiveRoom* __stdcall DUNGEON_GetARoomInSightButWithoutClient(struct D2DrlgAct* pAct, struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pAct);

	D2_ASSERT(pRoom);

	return DRLGACTIVATE_GetARoomInSightButWithoutClient(pAct->pDrlg, pRoom->pDrlgRoom);
}

//D2Common.0x6FD8C9E0 (#10071)
BOOL __stdcall DUNGEON_TestRoomCanUnTile(struct D2DrlgAct* pAct, struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pAct);
	D2_ASSERTM(!pAct->bClient, "Only servers should use DungeonTestRoomCanUnTile.");
	D2_ASSERT(pRoom);

	return DRLGACTIVATE_TestRoomCanUnTile(pRoom->pDrlgRoom);
}

//D2Common.0x6FD8CA60 (#10072)
bool __stdcall DUNGEON_GetRoomStatusFlags(struct D2ActiveRoom* pRoom)
{
	return DRLGACTIVATE_GetRoomStatusFlags(pRoom->pDrlgRoom) >= 3;
}

//D2Common.0x6FD8CA80 (#10073)
BOOL __stdcall D2Common_10073(struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pRoom);

	if (pRoom->nNumRooms == pRoom->pDrlgRoom->nRoomsNear)
	{
		for (int i = 0; i < pRoom->nNumRooms; ++i)
		{
			if (!(pRoom->ppRoomList[i]->dwFlags & 1))
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	return FALSE;
}

//D2Common.0x6FD8CAE0 (#10074)
BOOL __stdcall D2Common_10074(struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pRoom);

	return pRoom->dwFlags & 2;
}

//D2Common.0x6FD8CB10 (#10075)
void __stdcall D2Common_10075(struct D2ActiveRoom* pRoom, BOOL bSet)
{
	D2_ASSERT(pRoom);

	if (bSet)
	{
		pRoom->dwFlags |= 2;
	}
	else
	{
		pRoom->dwFlags &= 0xFFFFFFFD;
	}
}

//D2Common.0x6FD8CB60 (#10079)
void __stdcall DUNGEON_AddClientToRoom(struct D2ActiveRoom* pRoom, struct D2Client* pClient)
{
	D2_ASSERT(pRoom);

	D2_ASSERT(pClient);

	for (int i = 0; i < pRoom->nNumClients; ++i)
	{
		D2_ASSERT(pRoom->ppClients[i]);
	}

	D2_ASSERT(pRoom->nNumClients <= pRoom->nMaxClients);

	if (pRoom->nNumClients == pRoom->nMaxClients)
	{
		pRoom->nMaxClients += 4;
		pRoom->ppClients = (struct D2Client**)D2_REALLOC_POOL(pRoom->pAct->pMemPool, pRoom->ppClients, sizeof(struct D2Client*) * pRoom->nMaxClients);
	}

	pRoom->ppClients[pRoom->nNumClients] = pClient;
	++pRoom->nNumClients;

	DUNGEON_UpdateClientListOfRoom(pRoom);
}

//D2Common.0x6FD8CC50
void __fastcall DUNGEON_UpdateClientListOfRoom(struct D2ActiveRoom* pRoom)
{
	struct D2Client* pClient1 = NULL;
	struct D2Client* pClient2 = NULL;
	BOOL bContinue = FALSE;

	for (int i = 0; i < pRoom->nNumClients; ++i)
	{
		D2_ASSERT(pRoom->ppClients[i]);
	}

	for (int nClients = pRoom->nNumClients - 1; nClients > 0; --nClients)
	{
		bContinue = FALSE;

		for (int i = 0; i < nClients; ++i)
		{
			pClient1 = pRoom->ppClients[i];
			pClient2 = pRoom->ppClients[i + 1];

			if (pClient1 > pClient2)
			{
				pRoom->ppClients[i] = pClient2;
				pRoom->ppClients[i + 1] = pClient1;
				bContinue = TRUE;
			}
		}

		if (!bContinue)
		{
			return;
		}
	}

	for (int i = 0; i < pRoom->nNumClients; ++i)
	{
		D2_ASSERT(pRoom->ppClients[i]);
	}
}

//D2Common.0x6FD8CD10 (#10080)
void __stdcall DUNGEON_RemoveClientFromRoom(struct D2ActiveRoom* pRoom, struct D2Client* pClient)
{
	int i = 0;

	D2_ASSERT(pRoom);

	D2_ASSERT(pClient);

	for (i = 0; i < pRoom->nNumClients; ++i)
	{
		D2_ASSERT(pRoom->ppClients[i]);
	}

	for (i = 0; i < pRoom->nNumClients; ++i)
	{
		if (pRoom->ppClients[i] == pClient)
		{
			break;
		}
	}

	D2_ASSERT(i < pRoom->nNumClients);

	--pRoom->nNumClients;
	pRoom->ppClients[i] = pRoom->ppClients[pRoom->nNumClients];

	DUNGEON_UpdateClientListOfRoom(pRoom);
}

//D2Common.0x6FD8CDF0 (#10081)
int __stdcall D2Common_10081_GetTileCountFromRoom(struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pRoom);

	if (pRoom->nNumClients)
	{
		pRoom->nTileCount = 0;
		return 0;
	}
	else
	{
		++pRoom->nTileCount;
		return pRoom->nTileCount;
	}
}

//D2Common.0x6FD8CE40
void __fastcall DUNGEON_FreeRoom(void* pMemPool, struct D2ActiveRoom* pRoom)
{
	for (struct D2Unit* i = pRoom->pUnitFirst; i; i = pRoom->pUnitFirst)
	{
		if (!(i->dwFlags & UNITFLAG_ISCLIENTUNIT))
		{
			i->dwFlagEx |= 0x20;
		}

		i->dwFlags |= 0x800000;
		UNITROOM_UpdatePath(i);
	}

	COLLISION_FreeRoomCollisionGrid(pMemPool, pRoom);

	DUNGEON_FreeDrlgDelete(pRoom);

	if (pRoom->ppClients)
	{
		D2_FREE_POOL(pRoom->pAct->pMemPool, pRoom->ppClients);
	}

	D2_FREE_POOL(pMemPool, pRoom->ppRoomList);
	D2_FREE_POOL(pMemPool, pRoom);
}

//D2Common.0x6FD8CF10 (#10076)
void __stdcall DUNGEON_RemoveRoomFromAct(struct D2DrlgAct* pAct, struct D2ActiveRoom* pRoom)
{
	struct D2ActiveRoom* pPreviousRoom = NULL;
	struct D2ActiveRoom* pCurrentRoom = NULL;
	struct D2ActiveRoom* pNearRoom = NULL;
	int nCounter = 0;

	D2_ASSERT(pRoom);
	D2_ASSERT(pAct->pRoom);

	pCurrentRoom = pAct->pRoom;
	while (pCurrentRoom != pRoom)
	{
		pPreviousRoom = pCurrentRoom;
		pCurrentRoom = pCurrentRoom->pRoomNext;
		if (!pCurrentRoom)
		{
			break;
		}
	}

	D2_ASSERT(pCurrentRoom);

	if (pPreviousRoom)
	{
		pPreviousRoom->pRoomNext = pCurrentRoom->pRoomNext;
	}
	else
	{
		pAct->pRoom = pCurrentRoom->pRoomNext;
	}

	for (int i = 0; i < pRoom->nNumRooms; ++i)
	{
		pNearRoom = pRoom->ppRoomList[i];
		if (pNearRoom != pRoom)
		{
			nCounter = 0;

			while (nCounter < pNearRoom->nNumRooms && pNearRoom->ppRoomList[nCounter] != pRoom)
			{
				++nCounter;
			}

			if (nCounter < pNearRoom->nNumRooms)
			{
				--pNearRoom->nNumRooms;
				pNearRoom->ppRoomList[nCounter] = pNearRoom->ppRoomList[pNearRoom->nNumRooms];
			}
		}
	}

	sub_6FD77280(pRoom->pDrlgRoom, pAct->bClient, pRoom->dwFlags);
	DUNGEON_FreeRoom(pAct->pMemPool, pRoom);
}

//D2Common.0x6FD8D000 (#10077)
void __stdcall D2Common_10077(struct D2ActiveRoom* pRoom1, struct D2ActiveRoom* pRoom2)
{
	sub_6FD745C0(pRoom1 ? pRoom1->pDrlgRoom : NULL, pRoom2 ? pRoom2->pDrlgRoom : NULL);
}

//D2Common.0x6FD8D030 (#10078)
void __stdcall DUNGEON_UpdateAndFreeInactiveRooms(struct D2DrlgAct* pAct)
{
	DRLG_UpdateAndFreeInactiveRooms(pAct->pDrlg);
}

//D2Common.0x6FD8D040 (#10044)
int __stdcall DUNGEON_CheckLOSDraw(struct D2ActiveRoom* pRoom)
{
	if (pRoom)
	{
		return DRLGROOM_CheckLOSDraw(pRoom->pDrlgRoom);
	}

	return 0;
}

//D2Common.0x6FD8D060
struct D2DrlgEnvironment* __fastcall DUNGEON_GetEnvironmentFromAct(struct D2DrlgAct* pAct)
{
	D2_ASSERT(pAct);

	return pAct->pEnvironment;
}

//D2Common.0x6FD8D090 (#10088)
struct D2Drlg* __stdcall DUNGEON_GetDrlgFromAct(struct D2DrlgAct* pAct)
{
	D2_ASSERT(pAct);

	return pAct->pDrlg;
}

//D2Common.0x6FD912D0 (#10089)
int __stdcall DUNGEON_GetInitSeedFromAct(struct D2DrlgAct* pAct)
{
	if (pAct)
	{
		return pAct->dwInitSeed;
	}

	return 0;
}

//D2Common.0x6FD8D0C0 (#10007)
struct D2DrlgRoom* __fastcall DUNGEON_GetRoomExFromRoom(struct D2ActiveRoom* pRoom)
{
	return pRoom->pDrlgRoom;
}

//D2Common.0x6FD8D0D0 (#10086)
BOOL __stdcall DUNGEON_IsTownLevelId(int nLevelId)
{
	return DRLG_IsTownLevel(nLevelId);
}

//D2Common.0x6FD8D0E0 (#10082)
BOOL __stdcall DUNGEON_IsRoomInTown(struct D2ActiveRoom* pRoom)
{
	if (pRoom)
	{
		return DRLG_IsTownLevel(DRLGROOM_GetLevelId(pRoom->pDrlgRoom));
	}

	return FALSE;
}

//D2Common.0x6FD8D100 (#10083)
int __stdcall D2COMMON_10083_Return0(struct D2ActiveRoom* pRoom)
{
	//if (pRoom)
	//{
	//	DRLGROOM_GetLevelId(pRoom->pDrlgRoom);
	//}

	//return D2COMMON_10018_Return0();

	return 0;
}

//D2Common.0x6FD8D130 (#10084)
int __stdcall D2Common_10084(struct D2ActiveRoom* pRoom)
{
	return pRoom->dwFlags & 4;
}

//D2Common.0x6FD8D140 (#10085)
int __stdcall DUNGEON_GetTownLevelIdFromActNo(uint8_t nAct)
{
	static const int gnTownLevelIds[] = { LEVEL_ROGUEENCAMPMENT, LEVEL_LUTGHOLEIN, LEVEL_KURASTDOCKTOWN, LEVEL_THEPANDEMONIUMFORTRESS, LEVEL_HARROGATH };

	D2_ASSERT(nAct < ARRAY_SIZE(gnTownLevelIds));

	return gnTownLevelIds[nAct];
}

//D2Common.0x6FD8D180 (#10087)
int __stdcall D2Common_10087(struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pRoom);

	return sub_6FD779F0(pRoom->pDrlgRoom);
}

//D2Common.0x6FD8D1C0 (#10090)
int __stdcall DUNGEON_GetNumberOfPopulatedRoomsInLevel(struct D2DrlgAct* pAct, int nLevelId)
{
	return DRLG_GetNumberOfPopulatedRoomsInLevel(pAct->pDrlg, nLevelId);
}

//D2Common.0x6FD8D1E0 (#10025)
int* __stdcall DUNGEON_GetWarpCoordinatesFromRoom(struct D2ActiveRoom* pRoom)
{
	D2_ASSERT(pRoom);

	return DRLG_GetRoomCenterX_RoomWarpXFromRoom(pRoom->pDrlgRoom);
}

//D2Common.0x6FD8D220 (#10091)
void __stdcall DUNGEON_UpdateWarpRoomSelect(struct D2ActiveRoom* pRoom, int nLevelId)
{
	D2_ASSERT(pRoom);

	DRLGWARP_UpdateWarpRoomSelect(pRoom->pDrlgRoom, nLevelId);
}

//D2Common.0x6FD8D260 (#10092)
void __stdcall DUNGEON_UpdateWarpRoomDeselect(struct D2ActiveRoom* pRoom, int nLevelId)
{
	D2_ASSERT(pRoom);

	DRLGWARP_UpdateWarpRoomDeselect(pRoom->pDrlgRoom, nLevelId);
}

//D2Common.0x6FD8D2A0 (#10093)
void __stdcall DUNGEON_UpdatePops(struct D2ActiveRoom* pRoom, int nX, int nY, BOOL bOtherRoom)
{
	D2_ASSERT(pRoom);

	DRLGPRESET_UpdatePops(pRoom->pDrlgRoom, nX, nY, bOtherRoom);
}

//D2Common.0x6FD8D2E0 (#10094)
void __stdcall DUNGEON_GetTombStoneTileCoords(struct D2ActiveRoom* pRoom, struct D2Coord** ppTombStoneTiles, int* pnTombStoneTiles)
{
	return DRLGPRESET_GetTombStoneTileCoords(pRoom->pDrlgRoom, ppTombStoneTiles, pnTombStoneTiles);
}

//D2Common.0x6FD8D300 (#10095)
int __stdcall D2Common_10095(struct D2ActiveRoom* pRoom, int nX, int nY)
{
	struct D2ActiveRoom* pNearRoom = NULL;

	if (!pRoom)
	{
		return 0;
	}

	if (DungeonTestRoomGame(pRoom, nX, nY))
	{
		return DRLGLOGIC_GetRoomCoordListIndex(pRoom->pDrlgRoom, nX, nY);
	}

	for (int i = 0; i < pRoom->nNumRooms; ++i)
	{
		pNearRoom = pRoom->ppRoomList[i];
		if (DungeonTestRoomGame(pNearRoom, nX, nY))
		{
			return DRLGLOGIC_GetRoomCoordListIndex(pNearRoom->pDrlgRoom, nX, nY);
		}
	}

	return 0;
}

//D2Common.0x6FD8D3A0 (#10096)
struct D2RoomCoordList* __stdcall D2Common_10096(struct D2ActiveRoom* pRoom, int nX, int nY)
{
	return sub_6FD77110(pRoom->pDrlgRoom, nX, nY);
}

//D2Common.0x6FD8D3C0 (#10097)
struct D2RoomCoordList* __stdcall DUNGEON_GetRoomCoordList(struct D2ActiveRoom* pRoom)
{
	return DRLGLOGIC_GetRoomCoordList(pRoom->pDrlgRoom);
}

//D2Common.0x6FD8D3D0 (#10098)
void __stdcall DUNGEON_GetPortalLevelArrayFromPortalFlags(void* pMemPool, int nFlags, int** ppLevels, int* pnLevels)
{
	int* pPortalLevels = NULL;
	int nPortalLevels = 0;
	int nCurrentFlag = 0;
	int pLevels[32] = {};

	nCurrentFlag = 1;

	pPortalLevels = DATATBLS_GetPortalLevels(&nPortalLevels);
	D2_ASSERT(nPortalLevels <= ARRAY_SIZE(pLevels));

	*ppLevels = NULL;
	*pnLevels = 0;

	for (int i = 0; i < nPortalLevels; ++i)
	{
		if (nFlags & nCurrentFlag)
		{
			pLevels[*pnLevels] = pPortalLevels[i];
			++*pnLevels;
		}

		nCurrentFlag <<= 1;
	}		
	
	if (*pnLevels)
	{
		*ppLevels = (int*)D2_ALLOC_POOL(pMemPool, sizeof(int) * *pnLevels);
		memcpy(*ppLevels, pLevels, sizeof(int) * *pnLevels);
	}
}

//D2Common.0x6FD8D4B0 (#10099)
int __stdcall DUNGEON_GetPortalFlagFromLevelId(int nPortalLevelId)
{
	int* pPortalLevels = NULL;
	int nPortalLevels = 0;

	pPortalLevels = DATATBLS_GetPortalLevels(&nPortalLevels);

	for (int i = 0; i < nPortalLevels; ++i)
	{
		if (nPortalLevelId == pPortalLevels[i])
		{
			return 1 << i;
		}
	}

	return 0;
}

//D2Common.0x6FD8D4F0 (#10037)
int __stdcall DUNGEON_GetTownLevelIdFromAct(struct D2DrlgAct* pAct)
{
	D2_ASSERT(pAct);

	return pAct->nTownId;
}

//D2Common.0x6FD8D520 (#10047)
int __stdcall DUNGEON_GetHoradricStaffTombLevelId(struct D2DrlgAct* pAct)
{
	if (pAct)
	{
		return DRLG_GetHoradricStaffTombLevelId(pAct->pDrlg);
	}

	return 0;
}

//D2Common.0x6FD8D540 (#10102)
void __stdcall DUNGEON_ToggleHasPortalFlag(struct D2ActiveRoom* pRoom, BOOL bReset)
{
	if (pRoom)
	{
		DRLGACTIVATE_ToggleHasPortalFlag(pRoom->pDrlgRoom, bReset);
	}
}

//D2Common.0x6FD8D560 (#10104)
void __stdcall DUNGEON_AnimateTiles(struct D2ActiveRoom* pRoom)
{
	if (pRoom)
	{
		DRLGANIM_AnimateTiles(pRoom->pDrlgRoom);
	}
}

//D2Common.0x6FD8D580 (#10105)
void __stdcall DUNGEON_InitRoomTileAnimation(struct D2DrlgAct* pAct, struct D2ActiveRoom* pRoom1, struct D2ActiveRoom* pRoom2)
{
	struct D2DrlgRoom* pDrlgRoom1 = NULL;
	struct D2ActiveRoom* pRoom = NULL;

	if (pRoom1)
	{
		pRoom = pAct->pRoom;
		if (pRoom)
		{
			while (pRoom != pRoom1)
			{
				pRoom = pRoom->pRoomNext;
				if (!pRoom)
				{
					DRLGANIM_UpdateFrameInAdjacentRooms(NULL, pRoom2 ? pRoom2->pDrlgRoom : NULL);
					return;
				}
			}

			pDrlgRoom1 = pRoom1->pDrlgRoom;
		}
	}

	DRLGANIM_UpdateFrameInAdjacentRooms(pDrlgRoom1, pRoom2 ? pRoom2->pDrlgRoom : NULL);
}

//D2Common.0x6FD8D5C0 (#10103)
void __stdcall DUNGEON_SetActCallbackFunc(struct D2DrlgAct* pAct, ACTCALLBACKFN pActCallbackFunction)
{
	if (pAct)
	{
		pAct->pfnActCallBack = pActCallbackFunction;
	}
	else
	{
		FOG_DisplayWarning("ptAct", __FILE__, __LINE__);
	}
}

//D2Common.0x6FD8D600 (#10106)
void __stdcall DUNGEON_SaveKilledUnitGUID(struct D2ActiveRoom* pRoom, D2UnitGUID nUnitGUID)
{
	if (pRoom)
	{
		pRoom->nLastDeadGUIDs[pRoom->nCurrentDeathIndex] = nUnitGUID;
		pRoom->nCurrentDeathIndex = (pRoom->nCurrentDeathIndex + 1) & 3;
	}
}

//D2Common.0x6FD8D690 (#10107)
void __stdcall DUNGEON_ClientToGameTileCoords(int* pX, int* pY)
{
	const int nOutX = (2 * *pY + *pX) / 160;
	const int nOutY = (2 * *pY - *pX) / 160;

	*pX = nOutX;
	*pY = nOutY;
}

//D2Common.0x6FD8D870 (#10108)
void __stdcall DUNGEON_ClientToGameSubtileCoords(int* pX, int* pY)
{
	const int nOutX = (2 * *pY + *pX) / 32;
	const int nOutY = (2 * *pY - *pX) / 32;

	*pX = nOutX;
	*pY = nOutY;
}

//D2Common.0x6FD8D8A0 (#10109)
void __stdcall DUNGEON_ClientToGameCoords(int* pX, int* pY)
{
	int nX = 2 * *pY + *pX;
	int nY = 2 * *pY - *pX;

	*pX = nX;
	*pY = nY;
}

//D2Common.0x6FD8D6E0 (#10110)
void __stdcall DUNGEON_GameTileToClientCoords(int* pX, int* pY)
{
	int nX = *pX;
	int nY = *pY;

	*pX = 80 * (nX - nY);
	*pY = (80 * (nX + nY)) / 2;
}

//D2Common.0x6FD8D630 (#10111)
void __stdcall DUNGEON_GameSubtileToClientCoords(int* pX, int* pY)
{
	const int nOutX = 16 * (*pX - *pY);
	const int nOutY =  8 * (*pX + *pY);

	*pX = nOutX;
	*pY = nOutY;
}

//D2Common.0x6FD8D660 (#10112)
void __stdcall DUNGEON_GameToClientCoords(int* pX, int* pY)
{
	const int nOutX = (*pX - *pY) / 2;
	const int nOutY = (*pX + *pY) / 4;

	*pX = nOutX;
	*pY = nOutY;
}

//D2Common.0x6FD8D8C0 (#10113)
void __stdcall DUNGEON_GameTileToSubtileCoords(int* pX, int* pY)
{
	*pX *= 5;
	*pY *= 5;
}

//D2Common.0x6FD8D710 (#10114)
void __stdcall DUNGEON_ClientTileDrawPositionToGameCoords(int nX, int nY, int* pX, int* pY)
{
	*pX = 2 * nY + nX;
	*pY = 2 * nY - nX;

	if (*pX >= 0)
	{
		*pX /= 160;
	}
	else
	{
		*pX = *pX / 160 - 1;
	}

	if (*pY >= 0)
	{
		*pY /= 160;
	}
	else
	{
		*pY = *pY / 160 - 1;
	}
}

//D2Common.0x6FD8D790 (#10115)
void __stdcall DUNGEON_GameToClientTileDrawPositionCoords(int nX, int nY, int* pX, int* pY)
{
	*pX = 80 * (nX - nY);
	*pY = 40 * (nX + nY);
	*pX -= 80;
	*pY += 80;
}

//D2Common.0x6FD8D7D0 (#10116)
void __stdcall DUNGEON_ClientSubileDrawPositionToGameCoords(int nX, int nY, int* pX, int* pY)
{
	*pX = 2 * nY + nX;
	*pY = 2 * nY - nX;

	if (*pX >= 0)
	{
		*pX /= 32;
	}
	else
	{
		*pX = (*pX / 32) - 1;
	}

	if (*pY >= 0)
	{
		*pY /= 32;
	}
	else
	{
		*pY = (*pY / 32) - 1;
	}
}

//D2Common.0x6FD8D830 (#10117)
void __stdcall DUNGEON_GameToClientSubtileDrawPositionCoords(int nX, int nY, int* pX, int* pY)
{
	*pX = 16 * (nX - nY);
	*pY = 8 * (nX + nY);
	*pX -= 16;
	*pY += 16;
}

// Helper function
struct D2ActiveRoom* __fastcall DUNGEON_GetRoomAtPosition(struct D2ActiveRoom* pRoom, int32_t nSubtileX, int32_t nSubtileY)
{
    if (!pRoom)
    {
        return nullptr;
    }

    if (DungeonTestRoomGame(pRoom, nSubtileX , nSubtileY))
    {
        return pRoom;
    }

    struct D2ActiveRoom** ppRoomList = nullptr;
    int32_t nNumRooms = 0;
    DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, &ppRoomList, &nNumRooms);

    for (int32_t i = 0; i < nNumRooms; ++i)
    {
        struct D2ActiveRoom* pAdjacentRoom = ppRoomList[i];
        if (pAdjacentRoom && DungeonTestRoomGame(pAdjacentRoom, nSubtileX, nSubtileY))
        {
            return pAdjacentRoom;
        }
    }

    return nullptr;
}