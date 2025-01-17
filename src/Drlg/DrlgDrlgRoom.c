#include "Drlg/D2DrlgDrlgRoom.h"

#include "D2DataTbls.h"
#include "Drlg/D2DrlgDrlg.h"
#include "Drlg/D2DrlgDrlgLogic.h"
#include "Drlg/D2DrlgDrlgWarp.h"
#include "Drlg/D2DrlgOutRoom.h"
#include "Drlg/D2DrlgPreset.h"
#include "Drlg/D2DrlgRoomTile.h"
#include "D2Dungeon.h"
#include "D2Seed.h"


//D2Common.0x6FD771C0
struct D2DrlgRoom* __fastcall DRLGROOM_AllocRoomEx(struct D2DrlgLevel* pLevel, int nType)
{
	struct D2DrlgRoom* pDrlgRoom = D2_CALLOC_STRC_POOL(pLevel->pDrlg->pMempool, struct D2DrlgRoom);

	pDrlgRoom->pLevel = pLevel;
	pDrlgRoom->nType = nType;
	pDrlgRoom->fRoomStatus = 4;
	SEED_InitLowSeed(&pDrlgRoom->pSeed, (int)SEED_RollRandomNumber(&pLevel->pSeed));
	pDrlgRoom->dwInitSeed = (unsigned int)SEED_RollRandomNumber(&pDrlgRoom->pSeed);

	if (pLevel->dwFlags & DRLGLEVELFLAG_AUTOMAP_REVEAL)
	{
		pDrlgRoom->dwFlags |= DRLGROOMFLAG_AUTOMAP_REVEAL;
	}

	if (nType == DRLGTYPE_MAZE)
	{
		DRLGOUTROOM_AllocDrlgOutdoorRoom(pDrlgRoom);
	}
	else if (nType == DRLGTYPE_PRESET)
	{
		DRLGPRESET_AllocPresetRoomData(pDrlgRoom);
	}

	return pDrlgRoom;
}

//D2Common.0x6FD77280
void __fastcall sub_6FD77280(struct D2DrlgRoom* pDrlgRoom, BOOL bClient, uint32_t nFlags)
{
	pDrlgRoom->pRoom = NULL;

	pDrlgRoom->dwOtherFlags = nFlags & 1;

	if (pDrlgRoom->dwFlags & DRLGROOMFLAG_HAS_ROOM)
	{
		DRLGROOMTILE_FreeRoom(pDrlgRoom, bClient == 0);
	}
}

//D2Common.0x6FD772B0
void __fastcall DRLGROOM_FreeRoomTiles(void* pMemPool, struct D2DrlgRoom* pDrlgRoom)
{
	struct D2RoomTile* pRoomTile = NULL;
	struct D2RoomTile* pNext = NULL;

	pRoomTile = pDrlgRoom->pRoomTiles;
	while (pRoomTile)
	{
		pNext = pRoomTile->pNext;
		D2_FREE_POOL(pMemPool, pRoomTile);
		pRoomTile = pNext;
	}
	pDrlgRoom->pRoomTiles = NULL;
}

//D2Common.0x6FD772F0
void __fastcall DRLGROOM_FreeRoomEx(struct D2DrlgRoom* pDrlgRoom)
{
	struct D2PresetUnit* pNextPresetUnit = NULL;
	struct D2DrlgRoom* pCurrentRoomEx = NULL;
	struct D2DrlgRoom* pNextRoomEx = NULL;
	struct D2DrlgOrth* pNextDrlgOrth = NULL;
	struct D2DrlgOrth* pNextOrth = NULL;
	struct D2DrlgOrth* pOrth = NULL;
	void* pMemPool = NULL;

	pMemPool = pDrlgRoom->pLevel->pDrlg->pMempool;

	DRLGROOM_FreeRoomTiles(pMemPool, pDrlgRoom);

	if (pDrlgRoom->ppRoomsNear)
	{
		D2_FREE_POOL(pMemPool, pDrlgRoom->ppRoomsNear);
		pDrlgRoom->nRoomsNear = 0;
		pDrlgRoom->ppRoomsNear = NULL;
	}

	if (pDrlgRoom->nType == DRLGTYPE_MAZE)
	{
		DRLGOUTROOM_FreeDrlgOutdoorRoom(pDrlgRoom);
	}
	else if (pDrlgRoom->nType == DRLGTYPE_PRESET)
	{
		DRLGPRESET_FreePresetRoomData(pDrlgRoom);
	}

	
	for (struct D2PresetUnit* pPresetUnit = pDrlgRoom->pPresetUnits; pPresetUnit; pPresetUnit = pNextPresetUnit)
	{
		pNextPresetUnit = pPresetUnit->pNext;
		DRLGPRESET_FreePresetUnit(pMemPool, pPresetUnit);
	}

	for (struct D2DrlgOrth* pDrlgOrth = pDrlgRoom->pDrlgOrth; pDrlgOrth; pDrlgOrth = pNextDrlgOrth)
	{
		pNextDrlgOrth = pDrlgOrth->pNext;
		if (pDrlgOrth->bInit == 1)
		{
			pCurrentRoomEx = pDrlgOrth->pDrlgRoom;
			pOrth = pDrlgRoom->pDrlgOrth;
			pNextOrth = pOrth->pNext;

			if (pOrth->bInit == 1 && pOrth->pDrlgRoom == pCurrentRoomEx)
			{
				pDrlgRoom->pDrlgOrth = pNextOrth;
				pNextOrth = pOrth;

				D2_FREE_POOL(pMemPool, pNextOrth);
			}
			else
			{
				while (pNextOrth)
				{
					if (pNextOrth->bInit == 1 && pNextOrth->pDrlgRoom == pCurrentRoomEx)
					{
						pOrth->pNext = pNextOrth->pNext;
						D2_FREE_POOL(pMemPool, pNextOrth);
						break;
					}

					pOrth = pNextOrth;
					pNextOrth = pNextOrth->pNext;
				}
			}

			pOrth = pCurrentRoomEx->pDrlgOrth;
			pNextOrth = pOrth->pNext;
			if (pOrth->bInit == 1 && pOrth->pDrlgRoom == pDrlgRoom)
			{
				pCurrentRoomEx->pDrlgOrth = pNextOrth;
				pNextOrth = pOrth;
				D2_FREE_POOL(pMemPool, pNextOrth);
			}
			else
			{
				while (pNextOrth)
				{
					if (pNextOrth->bInit == 1 && pNextOrth->pDrlgRoom == pDrlgRoom)
					{
						pOrth->pNext = pNextOrth->pNext;
						D2_FREE_POOL(pMemPool, pNextOrth);
						break;
					}

					pOrth = pNextOrth;
					pNextOrth = pNextOrth->pNext;
				}
			}
		}
	}

	for (struct D2DrlgOrth* pDrlgOrth = pDrlgRoom->pDrlgOrth; pDrlgOrth; pDrlgOrth = pNextDrlgOrth)
	{
		pNextDrlgOrth = pDrlgOrth->pNext;
		D2_FREE_POOL(pMemPool, pDrlgOrth);
	}

	pCurrentRoomEx = pDrlgRoom->pLevel->pFirstRoomEx;
	if (pCurrentRoomEx == pDrlgRoom)
	{
		pDrlgRoom->pLevel->pFirstRoomEx = pDrlgRoom->pDrlgRoomNext;
		--pDrlgRoom->pLevel->nRooms;
	}
	else
	{
		pNextRoomEx = pCurrentRoomEx->pDrlgRoomNext;
		while (pNextRoomEx)
		{
			if (pNextRoomEx == pDrlgRoom)
			{
				pCurrentRoomEx->pDrlgRoomNext = pDrlgRoom->pDrlgRoomNext;
				--pDrlgRoom->pLevel->nRooms;
				break;
			}

			pCurrentRoomEx = pNextRoomEx;
			pNextRoomEx = pCurrentRoomEx->pDrlgRoomNext;
		}
	}

	DRLGROOMTILE_FreeTileGrid(pDrlgRoom);
	DRLGLOGIC_FreeDrlgCoordList(pDrlgRoom);
	D2_FREE_POOL(pMemPool, pDrlgRoom);
}

//D2Common.0x6FD774F0
void __fastcall DRLGROOM_FreeRoomData(void* pMemPool, struct D2DrlgOrth* pDrlgRoomData)
{
	struct D2DrlgOrth* pNext = NULL;
	
	for (struct D2DrlgOrth* pRoomData = pDrlgRoomData; pRoomData; pRoomData = pNext)
	{
		pNext = pRoomData->pNext;
		D2_FREE_POOL(pMemPool, pRoomData);
	}
}

//D2Common.0x6FD77520
void __fastcall DRLGROOM_AllocDrlgOrthsForRooms(struct D2DrlgRoom* pDrlgRoom1, struct D2DrlgRoom* pDrlgRoom2, int nDirection)
{
	struct D2DrlgOrth* pDrlgOrth = NULL;
	struct D2DrlgOrth* pNew = NULL;

	pDrlgOrth = pDrlgRoom1->pDrlgOrth;
	while (pDrlgOrth)
	{
		if (pDrlgOrth->pDrlgRoom == pDrlgRoom2)
		{
			break;
		}
		pDrlgOrth = pDrlgOrth->pNext;
	}

	if (!pDrlgOrth)
	{
		pNew = D2_CALLOC_STRC_POOL(pDrlgRoom1->pLevel->pDrlg->pMempool, struct D2DrlgOrth);
		pNew->pNext = pDrlgRoom1->pDrlgOrth;
		pDrlgRoom1->pDrlgOrth = pNew;
		pNew->pDrlgRoom = pDrlgRoom2;
		pNew->nDirection = nDirection;
		pNew->bInit = 1;
		pNew->pBox = &pDrlgRoom2->pDrlgCoord;
	}

	pDrlgOrth = pDrlgRoom2->pDrlgOrth;
	while (pDrlgOrth)
	{
		if (pDrlgOrth->pDrlgRoom == pDrlgRoom1)
		{
			break;
		}
		pDrlgOrth = pDrlgOrth->pNext;
	}

	if (!pDrlgOrth)
	{
		pNew = D2_CALLOC_STRC_POOL(pDrlgRoom2->pLevel->pDrlg->pMempool, struct D2DrlgOrth);
		pNew->pNext = pDrlgRoom2->pDrlgOrth;
		pDrlgRoom2->pDrlgOrth = pNew;
		pNew->pDrlgRoom = pDrlgRoom1;
		pNew->nDirection = ((uint8_t)nDirection - 2) & 3;
		pNew->bInit = 1;
		pNew->pBox = &pDrlgRoom1->pDrlgCoord;
	}
}

//D2Common.0x6FD77600
void __fastcall DRLGROOM_AddOrth(struct D2DrlgOrth** ppDrlgOrth, struct D2DrlgLevel* pLevel, int nDirection, BOOL bIsPreset)
{
	struct D2DrlgOrth* pPrevious = NULL;
	struct D2DrlgOrth* pNext = NULL;
	struct D2DrlgOrth* pNew = NULL;

	pNew = D2_CALLOC_STRC_POOL(pLevel->pDrlg->pMempool, struct D2DrlgOrth);

	pNew->pLevel = pLevel;
	pNew->nDirection = nDirection;
	pNew->bPreset = bIsPreset;
	pNew->bInit = 0;
	pNew->pBox = &pLevel->pLevelCoords;

	if (!*ppDrlgOrth)
	{
		*ppDrlgOrth = pNew;
	}
	else
	{
		pNext = (*ppDrlgOrth)->pNext;
		pPrevious = *ppDrlgOrth;
		if (pNext)
		{
			do
			{
				if (sub_6FD776B0(pNext, pNew))
				{
					break;
				}

				pPrevious = pNext;
				pNext = pNext->pNext;
			}
			while (pNext);
		}
		else
		{
			if (sub_6FD776B0(*ppDrlgOrth, pNew))
			{
				pNew->pNext = *ppDrlgOrth;
				*ppDrlgOrth = pNew;
				return;
			}
		}

		pNew->pNext = pNext;
		pPrevious->pNext = pNew;
	}
}

//D2Common.0x6FD776B0
BOOL __fastcall sub_6FD776B0(struct D2DrlgOrth* pDrlgOrth1, struct D2DrlgOrth* pDrlgOrth2)
{
	if (pDrlgOrth1->nDirection <= pDrlgOrth2->nDirection)
	{
		if (pDrlgOrth1->nDirection == pDrlgOrth2->nDirection)
		{
			switch (pDrlgOrth2->nDirection)
			{
			case 0:
				if (pDrlgOrth1->pBox->nPosY <= pDrlgOrth2->pBox->nPosY)
				{
					return FALSE;
				}
				break;

			case 1:
				if (pDrlgOrth1->pBox->nPosX >= pDrlgOrth2->pBox->nPosX)
				{
					return FALSE;
				}
				break;

			case 2:
				if (pDrlgOrth1->pBox->nPosY >= pDrlgOrth2->pBox->nPosY)
				{
					return FALSE;
				}
				break;

			case 3:
				if (pDrlgOrth1->pBox->nPosX <= pDrlgOrth2->pBox->nPosX)
				{
					return FALSE;
				}
				break;

			default:
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}

	return TRUE;
}

// Helper function
void DRLG_ComputeManhattanDistance(struct D2DrlgCoord* pDrlgCoord1, struct D2DrlgCoord* pDrlgCoord2, int* pDistanceX, int* pDistanceY)
{
	// Negative distance means we are "inside" the other rectangle
	if (pDrlgCoord1->nPosX >= pDrlgCoord2->nPosX)
	{
		*pDistanceX = pDrlgCoord1->nPosX - pDrlgCoord2->nWidth - pDrlgCoord2->nPosX;
	}
	else
	{
		*pDistanceX = pDrlgCoord2->nPosX - pDrlgCoord1->nWidth - pDrlgCoord1->nPosX;
	}

	if (pDrlgCoord1->nPosY >= pDrlgCoord2->nPosY)
	{
		*pDistanceY = pDrlgCoord1->nPosY - pDrlgCoord2->nHeight - pDrlgCoord2->nPosY;
	}
	else
	{
		*pDistanceY = pDrlgCoord2->nPosY - pDrlgCoord1->nHeight - pDrlgCoord1->nPosY;
	}
}


//D2Common.0x6FD77740
// Compute manhattan distance between rectangles and returns true if distance is greater or equal than nMargin
BOOL __fastcall DRLG_GetRectanglesManhattanDistanceAndCheckNotOverlapping(struct D2DrlgCoord* pDrlgCoord1, struct D2DrlgCoord* pDrlgCoord2, int nMaxDistance, int* pDistanceX, int* pDistanceY)
{
	DRLG_ComputeManhattanDistance(pDrlgCoord1, pDrlgCoord2, pDistanceX, pDistanceY);
	return *pDistanceX >= nMaxDistance || *pDistanceY >= nMaxDistance;
}

//D2Common.0x6FD777B0
// Compute manhattan distance between rectangles and returns true if distance is greater or equal than nMargin
BOOL __fastcall DRLG_CheckNotOverlappingUsingManhattanDistance(struct D2DrlgCoord* pDrlgCoord1, struct D2DrlgCoord* pDrlgCoord2, int nMaxDistanceToAssumeCollision)
{
	int nSignedDistanceX = 0;
	int nSignedDistanceY = 0;
	return DRLG_GetRectanglesManhattanDistanceAndCheckNotOverlapping(pDrlgCoord1, pDrlgCoord2, nMaxDistanceToAssumeCollision, &nSignedDistanceX, &nSignedDistanceY);
}

//D2Common.0x6FD77800
BOOL __fastcall DRLG_CheckOverlappingWithOrthogonalMargin(struct D2DrlgCoord* pDrlgCoord1, struct D2DrlgCoord* pDrlgCoord2, int nOrthogonalDistanceMax)
{
	int nSignedDistanceX = 0;
	int nSignedDistanceY = 0;
	DRLG_ComputeManhattanDistance(pDrlgCoord1, pDrlgCoord2, &nSignedDistanceX, &nSignedDistanceY);

	if (nOrthogonalDistanceMax)
	{
		if (nSignedDistanceX == 0 && nSignedDistanceY <= nOrthogonalDistanceMax)
		{
			return TRUE;
		}

		if (nSignedDistanceY == 0 && nSignedDistanceX <= nOrthogonalDistanceMax)
		{
			return TRUE;
		}
	}
	else
	{
		if (nSignedDistanceX <= 0 && nSignedDistanceY <= 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}

//D2Common.0x6FD77890
BOOL __fastcall DRLGMAZE_CheckRoomNotOverlaping(struct D2DrlgLevel* pLevel, struct D2DrlgRoom* pDrlgRoom1, struct D2DrlgRoom* pIgnoredRoom, int nMargin)
{
	for (struct D2DrlgRoom* pCurrentRoomEx = pLevel->pFirstRoomEx; pCurrentRoomEx; pCurrentRoomEx = pCurrentRoomEx->pDrlgRoomNext)
	{
		if (pCurrentRoomEx != pDrlgRoom1 && pCurrentRoomEx != pIgnoredRoom)
		{
			if (!DRLG_CheckNotOverlappingUsingManhattanDistance(&pDrlgRoom1->pDrlgCoord, &pCurrentRoomEx->pDrlgCoord, nMargin))
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

//D2Common.0x6FD77910
void __fastcall DRLGROOM_AddRoomExToLevel(struct D2DrlgLevel* pLevel, struct D2DrlgRoom* pDrlgRoom)
{
	pDrlgRoom->pDrlgRoomNext = pLevel->pFirstRoomEx;
	pLevel->pFirstRoomEx = pDrlgRoom;
	++pLevel->nRooms;
}

//D2Common.0x6FD77930
BOOL __fastcall DRLGROOM_AreXYInsideCoordinates(struct D2DrlgCoord* pDrlgCoord, int nX, int nY)
{
	if (nX >= pDrlgCoord->nPosX && nY >= pDrlgCoord->nPosY && nX < pDrlgCoord->nPosX + pDrlgCoord->nWidth && nY < pDrlgCoord->nPosY + pDrlgCoord->nHeight)
	{
		return TRUE;
	}

	return FALSE;
}

//D2Common.0x6FD77980
BOOL __fastcall DRLGROOM_AreXYInsideCoordinatesOrOnBorder(struct D2DrlgCoord* pDrlgCoord, int nX, int nY)
{
	if (nX >= pDrlgCoord->nPosX && nY >= pDrlgCoord->nPosY && nX <= pDrlgCoord->nPosX + pDrlgCoord->nWidth && nY <= pDrlgCoord->nPosY + pDrlgCoord->nHeight)
	{
		return TRUE;
	}

	return FALSE;
}

//D2Common.0x6FD779D0
BOOL __fastcall DRLGROOM_CheckLOSDraw(struct D2DrlgRoom* pDrlgRoom)
{
	if (pDrlgRoom->nType == DRLGTYPE_MAZE)
	{
		return TRUE;
	}
	else if (pDrlgRoom->nType == DRLGTYPE_PRESET)
	{
		return pDrlgRoom->dwFlags & DRLGROOMFLAG_NO_LOS_DRAW;
	}
		
	return FALSE;
}

//D2Common.0x6FD779F0
int __fastcall sub_6FD779F0(struct D2DrlgRoom* pDrlgRoom)
{
	if (pDrlgRoom->nType == DRLGTYPE_MAZE)
	{
		return pDrlgRoom->pOutdoor->dwFlags & 0x80;
	}

	return 0;
}

//D2Common.0x6FD77A00
int __fastcall DRLGROOM_CheckWaypointFlags(struct D2DrlgRoom* pDrlgRoom)
{
	return pDrlgRoom->dwFlags & (DRLGROOMFLAG_HAS_WAYPOINT | DRLGROOMFLAG_HAS_WAYPOINT_SMALL);
}

//D2Common.0x6FD77A10
int __fastcall DRLGROOM_GetLevelId(struct D2DrlgRoom* pDrlgRoom)
{
	return pDrlgRoom->pLevel->nLevelId;
}

//D2Common.0x6FD77A20
int __fastcall DRLGROOM_GetWarpDestinationLevel(struct D2DrlgRoom* pDrlgRoom, int nSourceLevel)
{
	int nDestinationLevel = 0;
	struct D2LvlWarpTxt* pLvlWarpTxtRecord = nullptr;
	struct D2ActiveRoom* pRoom = DRLGWARP_GetDestinationRoom(pDrlgRoom, nSourceLevel, &nDestinationLevel, &pLvlWarpTxtRecord);
	D2_ASSERT(pRoom);
	
	pDrlgRoom = DUNGEON_GetRoomExFromRoom(pRoom);
	D2_ASSERT(pDrlgRoom);
	
	D2_ASSERT(pDrlgRoom->pLevel);
	return pDrlgRoom->pLevel->nLevelId;
}

//D2Common.0x6FD77AB0
int __fastcall DRLGROOM_GetLevelIdFromPopulatedRoom(struct D2DrlgRoom* pDrlgRoom)
{
	if (!pDrlgRoom)
	{
		FOG_DisplayWarning("ptRoom", __FILE__, __LINE__);
	}

	if (pDrlgRoom->dwFlags & DRLGROOMFLAG_POPULATION_ZERO)
	{
		return 0;
	}
	else
	{
		return pDrlgRoom->pLevel->nLevelId;
	}
}

//D2Common.0x6FD77AF0
BOOL __fastcall DRLGROOM_HasWaypoint(struct D2DrlgRoom* pDrlgRoom)
{
	if (!pDrlgRoom)
	{
		FOG_DisplayWarning("ptRoom", __FILE__, __LINE__);
	}

	return DRLGROOM_CheckWaypointFlags(pDrlgRoom) != 0;
}

//D2Common.0x6FD77B20
const char* __fastcall DRLGROOM_GetPickedLevelPrestFilePathFromRoomEx(struct D2DrlgRoom* pDrlgRoom)
{
	if (pDrlgRoom->nType == DRLGTYPE_PRESET)
	{
		return DRLGPRESET_GetPickedLevelPrestFilePathFromRoomEx(pDrlgRoom);
	}
	else
	{
		return "None";
	}
}

//D2Common.0x6FD77B50
int __fastcall DRLGROOM_ReorderNearRoomList(struct D2DrlgRoom* pDrlgRoom, struct D2ActiveRoom** ppRoomList)
{
	int nRooms = 0;

	for (int i = 0; i < pDrlgRoom->nRoomsNear; ++i)
	{
		if (pDrlgRoom->ppRoomsNear[i]->pRoom)
		{
			ppRoomList[nRooms] = pDrlgRoom->ppRoomsNear[i]->pRoom;
			++nRooms;
		}
	}

	for (int i = nRooms; i < pDrlgRoom->nRoomsNear; ++i)
	{
		ppRoomList[i] = NULL;
	}

	return nRooms;
}

//D2Common.0x6FD77BB0
void __fastcall sub_6FD77BB0(void* pMemPool, struct D2DrlgRoom* pDrlgRoom)
{
	struct D2DrlgRoom* ppNearRooms[30] = {};
	struct D2DrlgLevel* pLevel = NULL;
	int* pDestinationVisArray = 0;
	int* pSourceVisArray = 0;
	int nWarpDestination = 0;
	int nDestinationVisCount = 0;
	int nSourceVisCount = 0;
	int nFlags = 0;
	int nX = 0;
	int nY = 0;
	BOOL bSkip = FALSE;
	uint8_t nWarpId = 0;

	pDrlgRoom->nRoomsNear = 0;

	for (struct D2DrlgRoom* pCurrentRoomEx = pDrlgRoom->pLevel->pFirstRoomEx; pCurrentRoomEx; pCurrentRoomEx = pCurrentRoomEx->pDrlgRoomNext)
	{
		if (pDrlgRoom->nTileXPos >= pCurrentRoomEx->nTileXPos)
		{
			nX = pDrlgRoom->nTileXPos - pCurrentRoomEx->nTileWidth - pCurrentRoomEx->nTileXPos;
		}
		else
		{
			nX = pCurrentRoomEx->nTileXPos - pDrlgRoom->nTileWidth - pDrlgRoom->nTileXPos;
		}

		if (pDrlgRoom->nTileYPos >= pCurrentRoomEx->nTileYPos)
		{
			nY = pDrlgRoom->nTileYPos - pCurrentRoomEx->nTileHeight - pCurrentRoomEx->nTileYPos;
		}
		else
		{
			nY = pCurrentRoomEx->nTileYPos - pDrlgRoom->nTileHeight - pDrlgRoom->nTileYPos;
		}

		if (nX < 6 && nY < 6)
		{
			ppNearRooms[pDrlgRoom->nRoomsNear] = pCurrentRoomEx;
			++pDrlgRoom->nRoomsNear;
		}
	}

	DRLGROOM_SortRoomListByPosition(ppNearRooms, pDrlgRoom->nRoomsNear);

	pDrlgRoom->ppRoomsNear = (struct D2DrlgRoom**)D2_ALLOC_POOL(pMemPool, sizeof(struct D2DrlgRoom*) * pDrlgRoom->nRoomsNear);

	for (int i = 0; i < pDrlgRoom->nRoomsNear; ++i)
	{
		pDrlgRoom->ppRoomsNear[i] = ppNearRooms[i];
	}

	if (pDrlgRoom->dwFlags & DRLGROOMFLAG_HAS_WARP_MASK)
	{
		nFlags = DRLGROOMFLAG_HAS_WARP_0;
		nWarpId = 0;

		do
		{
			if (nFlags & pDrlgRoom->dwFlags)
			{
				if (nWarpId >= 8)
				{
					FOG_DisplayWarning("ptRoom1 && bExit1 < LEVEL_VIS_MAX", __FILE__, __LINE__);
				}

				pSourceVisArray = DRLGROOM_GetVisArrayFromLevelId(pDrlgRoom->pLevel->pDrlg, pDrlgRoom->pLevel->nLevelId);

				pLevel = DRLG_GetLevel(pDrlgRoom->pLevel->pDrlg, pSourceVisArray[nWarpId]);

				pDestinationVisArray = DRLGROOM_GetVisArrayFromLevelId(pDrlgRoom->pLevel->pDrlg, pSourceVisArray[nWarpId]);
				nWarpDestination = DRLGWARP_GetWarpDestinationFromArray(pDrlgRoom->pLevel, nWarpId);

				if (!pLevel->pFirstRoomEx)
				{
					DRLG_InitLevel(pLevel);
				}

				if (nWarpDestination != -1)
				{
					nSourceVisCount = 0;
					nDestinationVisCount = 0;
					for (int i = 0; i < nWarpId; ++i)
					{
						if (pSourceVisArray[i] == pSourceVisArray[nWarpId])
						{
							++nSourceVisCount;
						}
					}

					for (int i = 0; i < 8; ++i)
					{
						if (pDestinationVisArray[i] == pDrlgRoom->pLevel->nLevelId)
						{
							if (nSourceVisCount == nDestinationVisCount)
							{
								if (sub_6FD77F00(pMemPool, pDrlgRoom, nWarpId, pLevel->pFirstRoomEx, i, nWarpDestination))
								{
									bSkip = TRUE;
								}
								break;
							}

							++nDestinationVisCount;
						}
					}
				}

				if (!bSkip)
				{
					for (int i = 0; i < 8; ++i)
					{
						if (pDestinationVisArray[i] == pDrlgRoom->pLevel->nLevelId && sub_6FD77F00(pMemPool, pDrlgRoom, nWarpId, pLevel->pFirstRoomEx, i, nWarpDestination))
						{
							break;
						}
					}
				}
			}

			nFlags <<= 1;

			++nWarpId;
		}
		while (nFlags & DRLGROOMFLAG_HAS_WARP_MASK);
	}

	if (!DRLG_IsTownLevel(pDrlgRoom->pLevel->nLevelId))
	{
		for (int i = 0; i < pDrlgRoom->nRoomsNear; ++i)
		{
			if (DRLG_IsTownLevel(pDrlgRoom->ppRoomsNear[i]->pLevel->nLevelId))
			{
				pDrlgRoom->dwFlags |= DRLGROOMFLAG_POPULATION_ZERO;
				return;
			}
		}
	}
}

//D2Common.0x6FD77EB0
void __fastcall DRLGROOM_SortRoomListByPosition(struct D2DrlgRoom** ppRoomList, int nListSize)
{
	struct D2DrlgRoom* pDrlgRoom1 = NULL;
	struct D2DrlgRoom* pDrlgRoom2 = NULL;

	for (int j = nListSize - 1; j > 0; --j)
	{
		for (int i = 0; i < nListSize - 1; ++i)
		{
			pDrlgRoom1 = ppRoomList[i + 1];
			pDrlgRoom2 = ppRoomList[i];

			if (pDrlgRoom2->nTileXPos >= pDrlgRoom1->nTileXPos + pDrlgRoom1->nTileWidth || pDrlgRoom2->nTileYPos >= pDrlgRoom1->nTileYPos + pDrlgRoom1->nTileHeight)
			{
				ppRoomList[i] = pDrlgRoom1;
				ppRoomList[i + 1] = pDrlgRoom2;
			}
		}
	}
}

//D2Common.0x6FD77F00
BOOL __fastcall sub_6FD77F00(void* pMemPool, struct D2DrlgRoom* pDrlgRoom1, uint8_t nWarpId, struct D2DrlgRoom* pDrlgRoom2, char nWarpFlag, int nDirection)
{
	struct D2RoomTile* pRoomTile = NULL;
	int nX = 0;
	int nY = 0;
	BOOL bResult = FALSE;

	while (pDrlgRoom2)
	{
		if (((1 << (nWarpFlag + 4)) & pDrlgRoom2->dwFlags))
		{
			if (nDirection == -1)
			{
				if (pDrlgRoom1->nTileXPos >= pDrlgRoom2->nTileXPos)
				{
					nX = pDrlgRoom1->nTileXPos - pDrlgRoom2->nTileWidth - pDrlgRoom2->nTileXPos;
				}
				else
				{
					nX = pDrlgRoom2->nTileXPos - pDrlgRoom1->nTileWidth - pDrlgRoom1->nTileXPos;
				}

				if (pDrlgRoom1->nTileYPos >= pDrlgRoom2->nTileYPos)
				{
					nY = pDrlgRoom1->nTileYPos - pDrlgRoom2->nTileHeight - pDrlgRoom2->nTileYPos;
				}
				else
				{
					nY = pDrlgRoom2->nTileYPos - pDrlgRoom1->nTileHeight - pDrlgRoom1->nTileYPos;
				}

				if (nX < 6 && nY < 6)
				{
					++pDrlgRoom1->nRoomsNear;
					pDrlgRoom1->ppRoomsNear = (struct D2DrlgRoom**)D2_REALLOC_POOL(pMemPool, pDrlgRoom1->ppRoomsNear, sizeof(struct D2DrlgRoom*) * pDrlgRoom1->nRoomsNear);

					D2_ASSERT(pDrlgRoom1->ppRoomsNear);

					pDrlgRoom1->ppRoomsNear[pDrlgRoom1->nRoomsNear - 1] = pDrlgRoom2;
					DRLGROOM_SortRoomListByPosition(pDrlgRoom1->ppRoomsNear, pDrlgRoom1->nRoomsNear);

					bResult = TRUE;
				}
			}
			else
			{
				++pDrlgRoom1->nRoomsNear;
				pDrlgRoom1->ppRoomsNear = (struct D2DrlgRoom**)D2_REALLOC_POOL(pMemPool, pDrlgRoom1->ppRoomsNear, sizeof(struct D2DrlgRoom*) * pDrlgRoom1->nRoomsNear);

				D2_ASSERT(pDrlgRoom1->ppRoomsNear);
				pDrlgRoom1->ppRoomsNear[pDrlgRoom1->nRoomsNear - 1] = pDrlgRoom2;
				DRLGROOM_SortRoomListByPosition(pDrlgRoom1->ppRoomsNear, pDrlgRoom1->nRoomsNear);

				pRoomTile = D2_CALLOC_STRC_POOL(pDrlgRoom1->pLevel->pDrlg->pMempool, struct D2RoomTile);
				pRoomTile->pDrlgRoom = pDrlgRoom2;
				pRoomTile->pLvlWarpTxtRecord = DRLGWARP_GetLvlWarpTxtRecordFromWarpIdAndDirection(pDrlgRoom1->pLevel, nWarpId, 'b');
				pRoomTile->bEnabled = 1;
				pRoomTile->pNext = pDrlgRoom1->pRoomTiles;
				pDrlgRoom1->pRoomTiles = pRoomTile;

				return TRUE;
			}
		}

		pDrlgRoom2 = pDrlgRoom2->pDrlgRoomNext;
	}

	return bResult;
}

//D2Common.0x6FD780E0
struct D2PresetUnit* __fastcall DRLGROOM_AllocPresetUnit(struct D2DrlgRoom* pDrlgRoom, void* pMemPool, int nUnitType, int nIndex, int nMode, int nX, int nY)
{
	struct D2PresetUnit* pPresetUnit = D2_CALLOC_STRC_POOL(pMemPool, struct D2PresetUnit);

	pPresetUnit->nUnitType = nUnitType;
	pPresetUnit->nMode = nMode;
	pPresetUnit->nIndex = nIndex;
	pPresetUnit->nYpos = nY;
	pPresetUnit->nXpos = nX;

	if (pDrlgRoom)
	{
		pPresetUnit->pNext = pDrlgRoom->pPresetUnits;
		pDrlgRoom->pPresetUnits = pPresetUnit;
	}
	else
	{
		pPresetUnit->pNext = NULL;
	}

	return pPresetUnit;
}

//D2Common.0x6FD78160
struct D2PresetUnit* __fastcall DRLGROOM_GetPresetUnits(struct D2DrlgRoom* pDrlgRoom)
{
	if (!(pDrlgRoom->dwFlags & DRLGROOMFLAG_AUTOMAP_REVEAL))
	{
		if (pDrlgRoom->dwFlags & DRLGROOMFLAG_PRESET_UNITS_SPAWNED)
		{
			return NULL;
		}

		pDrlgRoom->dwFlags |= DRLGROOMFLAG_PRESET_UNITS_SPAWNED;
	}

	return pDrlgRoom->pPresetUnits;
}

//D2Common.0x6FD78190
void __fastcall DRLGROOM_SetRoom(struct D2DrlgRoom* pDrlgRoom, struct D2ActiveRoom* pRoom)
{
	pDrlgRoom->pRoom = pRoom;
}

//D2Common.0x6FD781A0
void __fastcall DRLGROOM_GetRGB_IntensityFromRoomEx(struct D2DrlgRoom* pDrlgRoom, uint8_t* pIntensity, uint8_t* pRed, uint8_t* pGreen, uint8_t* pBlue)
{
	struct D2LevelDefBin* pLevelDefRecord = DATATBLS_GetLevelDefRecord(pDrlgRoom->pLevel->nLevelId);

	*pIntensity = pLevelDefRecord->nIntensity;
	*pRed = pLevelDefRecord->nRed;
	*pGreen = pLevelDefRecord->nGreen;
	*pBlue = pLevelDefRecord->nBlue;
}

//D2Common.0x6FD781E0
int* __fastcall DRLGROOM_GetVisArrayFromLevelId(struct D2Drlg* pDrlg, int nLevelId)
{
	struct D2DrlgWarp* pDrlgWarp = pDrlg->pWarp;

	while (pDrlgWarp)
	{
		if (!pDrlgWarp->nLevel)
		{
			FOG_DisplayWarning("ptVisInfo->eLevelId != LEVEL_ID_NONE", __FILE__, __LINE__);
		}

		if (nLevelId == pDrlgWarp->nLevel)
		{
			return pDrlgWarp->nVis;
		}

		pDrlgWarp = pDrlgWarp->pNext;
	}

	return DATATBLS_GetLevelDefRecord(nLevelId)->dwVis;
}

//D2Common.0x6FD78230
struct D2Drlg* __fastcall DRLGROOM_GetDrlgFromRoomEx(struct D2DrlgRoom* pRoom)
{
	D2_ASSERT(pRoom);
	D2_ASSERT(pRoom->pLevel);
	D2_ASSERT(pRoom->pLevel->pDrlg);
	return pRoom->pLevel->pDrlg;
}
