#include "Drlg/D2DrlgDrlgAnim.h"

#include "D2DataTbls.h"
#include "Drlg/D2DrlgDrlg.h"
#include "Drlg/D2DrlgDrlgGrid.h"
#include "Drlg/D2DrlgRoomTile.h"
#include <D2CMP.h>



//TODO: Variable names


//D2Common.0x6FD75480
void __cdecl DRLGANIM_InitCache(struct D2Drlg* pDrlg, struct D2DrlgTileData* pTileData)
{
	struct D2TileLibraryEntry* ppTileLibraryEntry[40] = {};
	int nSequence = 0;
	int nStyle = 0;

	D2_ASSERT(pDrlg);
	D2_ASSERT(pTileData);

	memset(pTileData, 0x00, sizeof(struct D2DrlgTileData));

	if (pDrlg->nAct != ACT_I)
	{
		if (pDrlg->nAct == ACT_II)
		{
			nSequence = 1;
		}
		else if (pDrlg->nAct == ACT_III)
		{
			nStyle = 29;
			nSequence = 12;
		}
		else
		{
			return;
		}
	}

	const int nSize = D2CMP_10088_GetTiles(pDrlg->pTiles, 0, nStyle, nSequence, ppTileLibraryEntry, ARRAY_SIZE(ppTileLibraryEntry));
	D2_ASSERT(nSize);
	DRLGROOMTILE_InitTileData(NULL, pTileData, 0, 0, 0, ppTileLibraryEntry[0]);
}

//D2Common.0x6FD75560
void __cdecl DRLGANIM_TestLoadAnimatedRoomTiles(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgGrid* pDrlgGrid, struct D2DrlgGrid* pTileTypeGrid, int nTileType, int nTileX, int nTileY)
{
	struct D2TileLibraryEntry* ppTileLibraryEntry[40] = {};

	for (int nY = 0; nY < pDrlgRoom->nTileHeight + (nTileY == 0); ++nY)
	{
		for (int nX = 0; nX < pDrlgRoom->nTileWidth + (nTileX == 0); ++nX)
		{
			const uint32_t nGridEntry = DRLGGRID_GetGridEntry(pDrlgGrid, nX, nY);
			const union D2C_PackedTileInformation nTileInfo = { nGridEntry };
			if (nTileInfo.bShadow || nTileInfo.bIsWall || nTileInfo.bIsFloor)
			{
				if (pTileTypeGrid)
				{
					nTileType = DRLGGRID_GetGridEntry(pTileTypeGrid, nX, nY);
				}

				const uint8_t nStyle = nTileInfo.nTileStyle;
				const uint8_t nSequence = nTileInfo.nTileSequence;

				const int nTilesCount = D2CMP_10088_GetTiles(pDrlgRoom->pTiles, nTileType, nStyle, nSequence, ppTileLibraryEntry, ARRAY_SIZE(ppTileLibraryEntry));
				if (nTilesCount && D2CMP_10079_GetTileFlags(ppTileLibraryEntry[0]) & TILE_FLAGS_LAVA)
				{
					if (nTileInfo.bIsFloor)
					{
						pDrlgRoom->pTileGrid->pTiles.nFloors += (nTilesCount - 1);
					}
					else if (nTileInfo.bIsWall)
					{
						pDrlgRoom->pTileGrid->pTiles.nWalls += (nTilesCount - 1);
					}
					else
					{
						pDrlgRoom->pTileGrid->pTiles.nRoofs += (nTilesCount - 1);
					}

					pDrlgRoom->dwFlags |= DRLGROOMFLAG_ANIMATED_FLOOR;
				}
			}
		}
	}
}

// Helper functions
static int AnimationFrameFixedPointToInteger(int nFixedPointFrame)
{
	return nFixedPointFrame >> 8;
}

static int AnimationFrameIntegerToFixedPoint(int nIntegerPart)
{
	return nIntegerPart << 8;
}

//D2Common.0x6FD756B0
void __cdecl DRLGANIM_AnimateTiles(struct D2DrlgRoom* pDrlgRoom)
{

	for (int i = 0; i < pDrlgRoom->nRoomsNear; ++i)
	{
		struct D2DrlgRoom* pCurrentRoomEx = pDrlgRoom->ppRoomsNear[i];

		if (pCurrentRoomEx->dwFlags & DRLGROOMFLAG_ANIMATED_FLOOR && pCurrentRoomEx->pTileGrid)
		{
			for (struct D2DrlgAnimTileGrid* j = pCurrentRoomEx->pTileGrid->pAnimTiles; j; j = j->pNext)
			{
				struct D2DrlgTileData* pTileData = j->ppMapTileData[AnimationFrameFixedPointToInteger(j->nCurrentFrame)];
				if (pTileData)
				{
					pTileData->dwFlags |= MAPTILE_HIDDEN;
				}

				j->nCurrentFrame = (j->nCurrentFrame + j->nAnimationSpeed) % AnimationFrameIntegerToFixedPoint(j->nFrames);

				pTileData = j->ppMapTileData[AnimationFrameFixedPointToInteger(j->nCurrentFrame)];
				if (pTileData)
				{
					pTileData->dwFlags &= ~MAPTILE_HIDDEN;
				}
			}
		}
	}
}

//D2Common.0x6FD75740
void __cdecl DRLGANIM_AllocAnimationTileGrids(struct D2DrlgRoom* pDrlgRoom, int nAnimationSpeed, struct D2DrlgGrid* pWallGrid, int nWalls, struct D2DrlgGrid* pFloorGrid, int nFloors, struct D2DrlgGrid* pShadowGrid)
{
	DRLGANIM_AllocAnimationTileGrid(pDrlgRoom, nAnimationSpeed, pDrlgRoom->pTileGrid->pTiles.pWallTiles, pDrlgRoom->pTileGrid->nWalls, pWallGrid, nWalls);
	DRLGANIM_AllocAnimationTileGrid(pDrlgRoom, nAnimationSpeed, pDrlgRoom->pTileGrid->pTiles.pFloorTiles, pDrlgRoom->pTileGrid->nFloors, pFloorGrid, nFloors);
	DRLGANIM_AllocAnimationTileGrid(pDrlgRoom, nAnimationSpeed, pDrlgRoom->pTileGrid->pTiles.pRoofTiles, pDrlgRoom->pTileGrid->nShadows, pShadowGrid, 1);
}

// Helper function
struct D2TileLibraryEntry* DRLGANIM_FindAnimatedTileFrame(struct D2TileLibraryEntry** pTileLibraryEntries, int nbTileEntries, int nRarity, int nStyle, int nSeq)
{
	for (int nEntryIndex = 0; nEntryIndex < nbTileEntries; nEntryIndex++)
	{
		if (D2CMP_10081_GetTileRarity(pTileLibraryEntries[nEntryIndex]) == nRarity)
		{
			return pTileLibraryEntries[nEntryIndex];
		}
	}
	char szBuffer[100] = { sgptDataTables->szDefaultString };
	FOG_DisplayWarning(FOG_csprintf(szBuffer, "Animating tiles missing Rarity %d Tile - Style %d Seq %d", nRarity, nStyle, nSeq), __FILE__, __LINE__);
	// Return first tile if nothing found.
	return pTileLibraryEntries[0];
}

//D2Common.0x6FD757B0
void __cdecl DRLGANIM_AllocAnimationTileGrid(struct D2DrlgRoom* pDrlgRoom, int nAnimationSpeed, struct D2DrlgTileData* pTiles, int nTiles, struct D2DrlgGrid* pDrlgGrid, int nUnused)
{
	D2_MAYBE_UNUSED(nUnused);
	if (!pTiles)
	{
		return;
	}
	if (nAnimationSpeed == 0)
	{
		nAnimationSpeed = 80;
	}

	struct D2TileLibraryEntry* pTileLibraryEntries[40] = {};

	for (int i = 0; i < nTiles; ++i)
	{
		struct D2DrlgTileData* pCurrentTileData = &pTiles[i];
		if (pCurrentTileData->pTile && D2CMP_10079_GetTileFlags(pCurrentTileData->pTile) & TILE_FLAGS_LAVA)
		{

			const int32_t nGridIdx = GetMapTileLayer(pCurrentTileData->dwFlags);
			const uint32_t nGridEntry = DRLGGRID_GetGridEntry(&pDrlgGrid[nGridIdx], pCurrentTileData->nPosX, pCurrentTileData->nPosY);
			const union D2C_PackedTileInformation nPackedTileInformation = { nGridEntry };

			const uint8_t nStyle = nPackedTileInformation.nTileStyle;
			const uint8_t nSeq = nPackedTileInformation.nTileSequence;

			int nFrames = D2CMP_10088_GetTiles(pDrlgRoom->pTiles, pCurrentTileData->nTileType, nStyle, nSeq, pTileLibraryEntries, ARRAY_SIZE(pTileLibraryEntries));

			struct D2DrlgAnimTileGrid* pDrlgAnimTileGrid = D2_CALLOC_STRC_POOL(pDrlgRoom->pLevel->pDrlg->pMempool, struct D2DrlgAnimTileGrid);

			pDrlgAnimTileGrid->ppMapTileData = (struct D2DrlgTileData**)D2_CALLOC_POOL(pDrlgRoom->pLevel->pDrlg->pMempool, sizeof(struct D2DrlgTileData*) * nFrames);

			pDrlgAnimTileGrid->nFrames = nFrames;
			pDrlgAnimTileGrid->nAnimationSpeed = nAnimationSpeed;
			pDrlgAnimTileGrid->pNext = pDrlgRoom->pTileGrid->pAnimTiles;

			pDrlgRoom->pTileGrid->pAnimTiles = pDrlgAnimTileGrid;

			// Animated tiles use rarity as frame index
			pCurrentTileData->pTile = DRLGANIM_FindAnimatedTileFrame(pTileLibraryEntries, nFrames, 0, nStyle, nSeq);
			pDrlgAnimTileGrid->ppMapTileData[0] = pCurrentTileData;

			int nX = pCurrentTileData->nPosX + pDrlgRoom->nTileXPos;
			int nY = pCurrentTileData->nPosY + pDrlgRoom->nTileYPos;

			for (unsigned int nRarity = 1; nRarity < nFrames; ++nRarity)
			{
				struct D2TileLibraryEntry* pTileEntry = DRLGANIM_FindAnimatedTileFrame(pTileLibraryEntries, nFrames, nRarity, nStyle, nSeq);

				if (pCurrentTileData->nTileType == TILETYPE_FLOOR)
				{
					pDrlgAnimTileGrid->ppMapTileData[nRarity] = DRLGROOMTILE_InitFloorTileData(pDrlgRoom, nullptr, nX, nY, nPackedTileInformation.nPackedValue, pTileEntry);
				}
				else if (pCurrentTileData->nTileType == TILETYPE_SHADOW)
				{
					pDrlgAnimTileGrid->ppMapTileData[nRarity] = DRLGROOMTILE_InitShadowTileData(pDrlgRoom, nullptr, nX, nY, nPackedTileInformation.nPackedValue, pTileEntry);
				}
				else
				{
					pDrlgAnimTileGrid->ppMapTileData[nRarity] = DRLGROOMTILE_InitWallTileData(pDrlgRoom, nullptr, nX, nY, nPackedTileInformation.nPackedValue, pTileEntry, pCurrentTileData->nTileType);
				}
				// We start by displaying the first frame, hide all other frames tiles.
				pDrlgAnimTileGrid->ppMapTileData[nRarity]->dwFlags |= MAPTILE_HIDDEN;
			}
		}
	}
}

//D2Common.0x6FD75B00
void __cdecl DRLGANIM_UpdateFrameInAdjacentRooms(struct D2DrlgRoom* pDrlgRoom1, struct D2DrlgRoom* pDrlgRoom2)
{
	if (!pDrlgRoom2)
	{
		return;
	}
	int nCurrentFrame = 0;
	if (pDrlgRoom1)
	{
		for (int i = 0; i < pDrlgRoom1->nRoomsNear; ++i)
		{
			if (pDrlgRoom1->ppRoomsNear[i]->pTileGrid && pDrlgRoom1->ppRoomsNear[i]->pTileGrid->pAnimTiles)
			{
				nCurrentFrame = pDrlgRoom1->ppRoomsNear[i]->pTileGrid->pAnimTiles->nCurrentFrame;
				break;
			}
		}
	}

	for (int i = 0; i < pDrlgRoom2->nRoomsNear; ++i)
	{
		struct D2DrlgTileGrid* pAdjacentRoomTileGrid = pDrlgRoom2->ppRoomsNear[i]->pTileGrid;
		if (pAdjacentRoomTileGrid)
		{
			for (struct D2DrlgAnimTileGrid* pAdjacentRoomAnimData = pAdjacentRoomTileGrid->pAnimTiles; pAdjacentRoomAnimData; pAdjacentRoomAnimData = pAdjacentRoomAnimData->pNext)
			{
				pAdjacentRoomAnimData->nCurrentFrame = nCurrentFrame;
			}
		}
	}

}
