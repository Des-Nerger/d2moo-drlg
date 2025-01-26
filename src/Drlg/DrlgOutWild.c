#include "Drlg/D2DrlgOutWild.h"

#include "Drlg/D2DrlgDrlg.h"
#include "Drlg/D2DrlgDrlgGrid.h"
#include "Drlg/D2DrlgOutdoors.h"
#include "Drlg/D2DrlgOutPlace.h"
#include "Drlg/D2DrlgMaze.h"
#include "D2Seed.h"
#include <DataTbls/LevelsIds.h>

//D2Common.0x6FD84CA0
void __cdecl DRLGOUTWILD_GetBridgeCoords(struct D2DrlgLevel* pLevel, int* pX, int* pY)
{
	int nX = pLevel->pOutdoors->nGridWidth / 2 - 1;

	for (int nY = 1; nY < pLevel->pOutdoors->nGridWidth - 1; ++nY)
	{
		if (DRLGGRID_GetGridEntry(&pLevel->pOutdoors->pGrid[0], nX, nY) == 28 
			&& DRLGOUTDOORS_GetPackedGrid2Info(pLevel->pOutdoors, nX, nY).nPickedFile == 1)
		{
			*pX = nX;
			*pY = nY;
			return;
		}
	}

	*pX = -1;
	*pY = -1;
}

//D2Common.0x6FD84D30
//TODO: Check v21, v22
void __cdecl DRLGOUTWILD_InitAct1OutdoorLevel(struct D2DrlgLevel* pLevel)
{
	int nX = 0;
	int nY = 0;
	BOOL bAdded = FALSE;
	BOOL bBreak = FALSE;

	int v21 = 0;
	bool v22; // zf@53

	if (pLevel->nLevelId != LEVEL_BLOODMOOR && pLevel->nLevelId != LEVEL_COLDPLAINS && pLevel->nLevelId != LEVEL_BURIALGROUNDS)
	{
		struct D2DrlgVertex* pVertex = pLevel->pOutdoors->pVertex;
		struct D2DrlgVertex* pPreviousVertex = pVertex;

		for (struct D2DrlgVertex* i = pVertex->pNext; i != pVertex; i = i->pNext)
		{
			pPreviousVertex = i;
		}

		bBreak = FALSE;
		do
		{
			struct D2DrlgVertex* pNextVertex = pVertex->pNext;
			if (pVertex->nPosX < pNextVertex->nPosX && pPreviousVertex->nPosY > pVertex->nPosY && !(pVertex->dwFlags & 1)
				&& !(pPreviousVertex->dwFlags & 1) || pVertex->nPosY > pNextVertex->nPosY 
				&& pPreviousVertex->nPosX > pVertex->nPosX && !(pVertex->dwFlags & 1) && !(pPreviousVertex->dwFlags & 1))
			{
				struct D2DrlgVertex* pFirstVertex = pVertex;
				struct D2DrlgVertex* pSpecialVertex = NULL;
				do
				{
					if (pVertex == pLevel->pOutdoors->pVertex)
					{
						bBreak = TRUE;
					}

					if (sub_6FD85350(pVertex))
					{
						break;
					}

					if (sub_6FD85300(pVertex))
					{
						pSpecialVertex = pVertex;
					}

					pVertex = pVertex->pNext;
				}
				while (pVertex != pFirstVertex);

				if (pSpecialVertex)
				{
					for (struct D2DrlgVertex* j = pFirstVertex; j != pSpecialVertex; j = j->pNext)
					{
						j->nDirection = 1;
					}

					pSpecialVertex->nDirection = 1;

					pLevel->pOutdoors->dwFlags |= 0x20;
				}
			}

			pPreviousVertex = pVertex;
			pVertex = pVertex->pNext;
		}
		while (!bBreak && pVertex != pLevel->pOutdoors->pVertex);
	}

	DRLGOUTPLACE_SetOutGridLinkFlags(pLevel);
	DRLGOUTPLACE_PlaceAct1245OutdoorBorders(pLevel);

	if (pLevel->nLevelId >= LEVEL_BLOODMOOR && pLevel->nLevelId <= LEVEL_TAMOEHIGHLAND)
	{
		DRLGOUTDOORS_AddAct124SecondaryBorder(pLevel, LVLSUB_ACT1_BORDER_CLIFFS, LVLPREST_ACT1_WILD_BORDER_1);

		if (pLevel->nLevelId != LEVEL_MOOMOOFARM)
		{
			if (pLevel->pOutdoors->dwFlags & 0xC)
			{
				if (DRLGOUTWILD_TestSpawnRiver(pLevel, pLevel->pOutdoors->nGridWidth - 2))
				{
					DRLGOUTWILD_SpawnRiver(pLevel, pLevel->pOutdoors->nGridWidth - 2);
				}
			}

			if (pLevel->pOutdoors->dwFlags & 0x20 && !(pLevel->pOutdoors->dwFlags & 0x40))
			{
				bAdded = FALSE;

				if (!(SEED_RollRandomNumber(&pLevel->pSeed) & 1))
				{
					for (int j = 0; j < pLevel->pOutdoors->nGridHeight; ++j)
					{
						if (bAdded)
						{
							break;
						}

						for (int i = 0; i < pLevel->pOutdoors->nGridWidth; ++i)
						{
							if (bAdded)
							{
								break;
							}

							bAdded = DRLGOUTWILD_SpawnCliffCaves(pLevel, i, j);
						}
					}

					if (!bAdded)
					{
						FOG_DisplayWarning("fAdded", __FILE__, __LINE__);
					}
				}
				else
				{
					for (int j = 0; j < pLevel->pOutdoors->nGridHeight; ++j)
					{
						if (bAdded)
						{
							break;
						}

						for (int i = 0; i < pLevel->pOutdoors->nGridWidth; ++i)
						{
							if (bAdded)
							{
								break;
							}

							bAdded = DRLGOUTWILD_SpawnCliffCaves(pLevel, j, i);
						}
					}

					if (!bAdded)
					{
						FOG_DisplayWarning("fAdded", __FILE__, __LINE__);
					}
				}
			}

			if (pLevel->pOutdoors->dwFlags & 0x1C && !(pLevel->pOutdoors->dwFlags & 0x40))
			{
				nY = pLevel->pOutdoors->nGridHeight - 4;
				nX = pLevel->pOutdoors->nGridWidth - ((~(uint8_t)pLevel->pOutdoors->dwFlags & 0x10 | 0x40) >> 4);

				v21 = SEED_RollRandomNumber(&pLevel->pSeed) & 3;
				if ((v21 % 2) != 0)
				{
					nX = 3;
				}

				if (v21 / 2)
				{
					nY = 3;
				}

				DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, nX, nY, (pLevel->nLevelId == LEVEL_BLOODMOOR) + 51, -1, 0);
				pLevel->pOutdoors->dwFlags |= 0x40;
			}
		}

		DRLGOUTDOORS_AddAct124SecondaryBorder(pLevel, LVLSUB_ACT1_BORDER_MIDDLE, LVLPREST_ACT1_WILD_BORDER_1);
		DRLGOUTDOORS_AddAct124SecondaryBorder(pLevel, LVLSUB_ACT1_BORDER_CORNER, LVLPREST_ACT1_WILD_BORDER_1);
		DRLGOUTWILD_SpawnTownTransitionsAndCaves(pLevel);
		DRLGOUTDOORS_AddAct124SecondaryBorder(pLevel, LVLSUB_ACT1_BORDER_BORDER, LVLPREST_ACT1_WILD_BORDER_1);
		DRLGOUTDOORS_SpawnAct1DirtPaths(pLevel);
	}

	if (pLevel->nLevelId == LEVEL_MOOMOOFARM)
	{
		DRLGOUTDOORS_AddAct124SecondaryBorder(pLevel, LVLSUB_ACT1_BORDER_CLIFFS, LVLPREST_ACT1_WILD_BORDER_1);
		DRLGOUTDOORS_AddAct124SecondaryBorder(pLevel, LVLSUB_ACT1_BORDER_MIDDLE, LVLPREST_ACT1_WILD_BORDER_1);
		DRLGOUTDOORS_AddAct124SecondaryBorder(pLevel, LVLSUB_ACT1_BORDER_CORNER, LVLPREST_ACT1_WILD_BORDER_1);
		DRLGOUTDOORS_AddAct124SecondaryBorder(pLevel, LVLSUB_ACT1_BORDER_BORDER, LVLPREST_ACT1_WILD_BORDER_1);
	}

	if (pLevel->nLevelId >= LEVEL_COLDPLAINS && pLevel->nLevelId <= LEVEL_BLACKMARSH)
	{
		DRLGOUTDOORS_SpawnAct12Waypoint(pLevel);
	}

	if (pLevel->nLevelId >= LEVEL_BLOODMOOR && pLevel->nLevelId <= LEVEL_TAMOEHIGHLAND)
	{
		DRLGOUTDOORS_SpawnAct12Shrines(pLevel, 5);
	}

	DRLGOUTWILD_SpawnSpecialPresets(pLevel);
}

//D2Common.0x6FD85060
BOOL __cdecl DRLGOUTWILD_TestSpawnRiver(struct D2DrlgLevel* pLevel, int nX)
{
	for (int nY = 0; nY < pLevel->pOutdoors->nGridHeight; ++nY)
	{
		if (DRLGOUTDOORS_GetPackedGrid2Info(pLevel->pOutdoors, nX, nY).bHasDirection 
			|| DRLGOUTDOORS_GetPackedGrid2Info(pLevel->pOutdoors, nX + 1, nY).bHasDirection)
		{
			return FALSE;
		}
	}

	return TRUE;
}

//1.10f: Inlined
void DRLGOUTWILD_SpawnRiverPreset(struct D2DrlgLevel* pLevel, int nX, int nY, bool bLowerRiver)
{
	static const struct {
		int nUpperFile;
		int nLowerFile;
	} stru_6FDD0CA0[] =
	{
		{ 2, 2 },
		{ 0, 3 },
		{ 1, 1 },
		{ 3, 0 },
		{ 0, 2 },
		{ 0, 1 },
		{ 1, 0 },
		{ 2, 0 },
		{ 2, 3 },
		{ 1, 3 },
		{ 3, 1 },
		{ 3, 2 }
	};
	int nPickedFile = 0;

	union D2DrlgOutdoorPackedGrid2Info tPackedInfo = DRLGOUTDOORS_GetPackedGrid2Info(pLevel->pOutdoors, nX + (int)(bLowerRiver), nY);
	int nFlags2 = DRLGGRID_GetGridEntry(&pLevel->pOutdoors->pGrid[0], nX + (int)(bLowerRiver), nY);
	if (nFlags2)
	{
		if (nFlags2 != LVLPREST_ACT1_WILD_BORDER_4 || tPackedInfo.nPickedFile != 3)
		{

			const int nIdx = nFlags2 - LVLPREST_ACT1_WILD_BORDER_1;
			D2_ASSERT(nIdx < ARRAY_SIZE(stru_6FDD0CA0));
			nPickedFile = bLowerRiver ? stru_6FDD0CA0[nIdx].nLowerFile : stru_6FDD0CA0[nIdx].nUpperFile;
		}
		else
		{
			nPickedFile = 3;
		}
	}
	else
	{
		if (tPackedInfo.nUnkb08)
		{
			nPickedFile = 0;
		}
		else
		{
			nPickedFile = 3;
		}
	}

	DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, nX + (int)(bLowerRiver), nY, bLowerRiver ? LVLPREST_ACT1_RIVER_LOWER : LVLPREST_ACT1_RIVER_UPPER, nPickedFile, FALSE);

}
//D2Common.0x6FD850B0
void __cdecl DRLGOUTWILD_SpawnRiver(struct D2DrlgLevel* pLevel, int nX)
{
	for (int nY = 0; nY < pLevel->pOutdoors->nGridHeight; ++nY)
	{
		DRLGOUTWILD_SpawnRiverPreset(pLevel, nX, nY, false);
		DRLGOUTWILD_SpawnRiverPreset(pLevel, nX, nY, true);
	}

	if (pLevel->pOutdoors->dwFlags & (OUTDOOR_RIVER|OUTDOOR_BRIDGE))
	{
		int nRand = SEED_RollLimitedRandomNumber(&pLevel->pSeed, pLevel->pOutdoors->nGridHeight - 2);

		for (int i = 0; i < pLevel->pOutdoors->nGridHeight - 2; ++i)
		{
			int nY = (nRand + i) % (pLevel->pOutdoors->nGridHeight - 1);

			if (DRLGOUTDOORS_TestGridCellSpawnValid(pLevel, nX - 1, nY) && ((pLevel->pOutdoors->dwFlags & OUTDOOR_BRIDGE) != 0 || DRLGOUTDOORS_TestGridCellSpawnValid(pLevel, nX + 2, nY)))
			{
				if (DRLGOUTDOORS_GetPackedGrid2Info(pLevel->pOutdoors, nX    , nY).nPickedFile == 3 && 
					DRLGOUTDOORS_GetPackedGrid2Info(pLevel->pOutdoors, nX + 1, nY).nPickedFile == 3)
				{
					DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, nX    , nY, LVLPREST_ACT1_BRIDGE, 1, 0);
					DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, nX + 1, nY, LVLPREST_ACT1_BRIDGE, (pLevel->pOutdoors->dwFlags & OUTDOOR_BRIDGE) != 0 ? 3 : 2, 0);
					return;
				}
			}
		}
	}
}

//D2Common.0x6FD85300
BOOL __cdecl sub_6FD85300(struct D2DrlgVertex* pDrlgVertex)
{
	struct D2DrlgVertex* pNext = pDrlgVertex->pNext;

	if (pDrlgVertex->nPosX >= pNext->nPosX || pNext->nPosY >= pNext->pNext->nPosY || pDrlgVertex->dwFlags & 1 || pNext->dwFlags & 1)
	{
		if (pDrlgVertex->nPosY <= pNext->nPosY || pNext->nPosX >= pNext->pNext->nPosX || pDrlgVertex->dwFlags & 1 || pNext->dwFlags & 1)
		{
			return FALSE;
		}
	}

	return TRUE;
}

//D2Common.0x6FD85350
BOOL __cdecl sub_6FD85350(struct D2DrlgVertex* pDrlgVertex)
{
	struct D2DrlgVertex* pNext = pDrlgVertex->pNext;

	if (pDrlgVertex->nPosY >= pNext->nPosY && pDrlgVertex->nPosX <= pNext->nPosX)
	{
		if (!(pDrlgVertex->dwFlags & 1))
		{
			return pNext->dwFlags & 1;
		}
	}

	return TRUE;
}

//D2Common.0x6FD85390
BOOL __cdecl DRLGOUTWILD_SpawnCliffCaves(struct D2DrlgLevel* pLevel, int nX, int nY)
{
	switch (DRLGGRID_GetGridEntry(pLevel->pOutdoors->pGrid, nX, nY))
	{
	case 16:
		DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, nX, nY, LVLPREST_ACT1_WILD_CLIFF_CAVE_LEFT, -1, 0);
		pLevel->pOutdoors->dwFlags |= 0x40;
		return TRUE;

	case 17:
		DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, nX, nY, LVLPREST_ACT1_WILD_CLIFF_CAVE_RIGHT, -1, 0);
		pLevel->pOutdoors->dwFlags |= 0x40;
		return TRUE;

	default:
		return FALSE;
	}
}

//D2Common.0x6FD853F0
void __cdecl DRLGOUTWILD_SpawnTownTransitionsAndCaves(struct D2DrlgLevel* pLevel)
{
	int fAdded = 0;
	int nX = 0;
	int nY = 0;

	if (pLevel->nLevelId != LEVEL_MOOMOOFARM)
	{
		if (pLevel->pOutdoors->dwFlags & 0x10)
		{
			nX = pLevel->pOutdoors->nGridWidth / 2 - 1;

			if (pLevel->pOutdoors->nGridHeight <= 0)
			{
				DRLGOUTWILD_SpawnRiver(pLevel, nX);
			}
			else
			{
				while (!DRLGOUTDOORS_GetPackedGrid2Info(pLevel->pOutdoors, nX    , nY).bHasDirection 
					&& !DRLGOUTDOORS_GetPackedGrid2Info(pLevel->pOutdoors, nX + 1, nY).bHasDirection)
				{
					++nY;

					if (nY >= pLevel->pOutdoors->nGridHeight)
					{
						DRLGOUTWILD_SpawnRiver(pLevel, nX);
						break;
					}
				}
			}
		}

		if (pLevel->pOutdoors->dwFlags & 0x80)
		{
			DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, 0, 0, LVLPREST_ACT1_TOWN_1_TRANSITION_S, 1, 0);
		}

		if (pLevel->pOutdoors->dwFlags & 0x100)
		{
			DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, pLevel->pOutdoors->nGridWidth - 7, 0, LVLPREST_ACT1_TOWN_1_TRANSITION_S, 2, 0);
		}

		if (pLevel->pOutdoors->dwFlags & 0x200)
		{
			DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, 0, 1, LVLPREST_ACT1_TOWN_1_TRANSITION_E, 1, 0);
		}

		if (pLevel->pOutdoors->dwFlags & 0x400)
		{
			DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, 0, pLevel->pOutdoors->nGridHeight - 6, LVLPREST_ACT1_TOWN_1_TRANSITION_E, 1, 0);
		}

		if (!(pLevel->pOutdoors->dwFlags & 0x40))
		{
			if (pLevel->nLevelId == LEVEL_BLOODMOOR)
			{
				fAdded = DRLGOUTDOORS_SpawnPresetFarAway(pLevel, &DRLG_GetLevel(pLevel->pDrlg, LEVEL_ROGUEENCAMPMENT)->pLevelCoords, LVLPREST_ACT1_DOE_ENTRANCE, -1, 1, 15);
			}
			else
			{
				fAdded = DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_CAVE_ENTRANCE, -1, 1, 15);
			}

			if (!fAdded)
			{
				FOG_DisplayWarning("fAdded", __FILE__, __LINE__);
			}

			pLevel->pOutdoors->dwFlags |= 0x40;
		}
	}
}

//D2Common.0x6FD85520
void __cdecl DRLGOUTWILD_SpawnSpecialPresets(struct D2DrlgLevel* pLevel)
{
	switch (pLevel->nLevelId)
	{
	case LEVEL_BLOODMOOR:
		DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_POND, -1);

		if (!(SEED_RollRandomNumber(&pLevel->pSeed) & 3))
		{
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_1, -1);
		}

		DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_1, -1);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_STONE_FILL_1, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_STONE_FILL_2, -1, 0, 15);
		return;

	case LEVEL_COLDPLAINS:
		if (SEED_RollRandomNumber(&pLevel->pSeed) & 3)
		{
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_2, -1);

			if (SEED_RollRandomNumber(&pLevel->pSeed) & 1)
			{
				DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_3, -1);
			}
		}
		else
		{
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_2, -1);
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_2, -1);
		}

		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_FALLEN_CAMP_BISHIBOSH, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_STONE_FILL_1, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_STONE_FILL_2, -1, 0, 15);
		return;

	case LEVEL_STONYFIELD:
		DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_CAIRN_STONES, -1);
		DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_CAMP, -1);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_TOWER_TOME, -1, 0, 15);

		if (SEED_RollRandomNumber(&pLevel->pSeed) & 3)
		{
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_1, -1);

			if (SEED_RollRandomNumber(&pLevel->pSeed) & 1)
			{
				DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_3, -1);
			}
		}
		else
		{
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_1, -1);
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_1, -1);
		}

		if (!(SEED_RollRandomNumber(&pLevel->pSeed) & 3))
		{
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_FALLEN_CAMP_1, -1);
		}

		DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_FALLEN_CAMP_1, -1);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_CORRAL_FILL, -1, 0, 15);
		return;

	case LEVEL_DARKWOOD:
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_INIFUS, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_RUIN, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_TREE_FILL, -1, 0, 15);

		if (SEED_RollRandomNumber(&pLevel->pSeed) & 3)
		{
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_2, -1);

			if (SEED_RollRandomNumber(&pLevel->pSeed) & 1)
			{
				DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_3, -1);
			}
		}
		else
		{
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_2, -1);
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_2, -1);
		}

		if (!(SEED_RollRandomNumber(&pLevel->pSeed) & 3))
		{
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_FALLEN_CAMP_2, -1);
		}

		DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_FALLEN_CAMP_2, -1);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_STONE_FILL_1, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_STONE_FILL_2, -1, 0, 15);
		return;

	case LEVEL_BLACKMARSH:
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_TOWER_1, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_SWAMP_FILL_1, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_SWAMP_FILL_2, -1, 0, 15);

		if (SEED_RollRandomNumber(&pLevel->pSeed) & 3)
		{
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_1, -1);

			if (SEED_RollRandomNumber(&pLevel->pSeed) & 1)
			{
				DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_3, -1);
			}
		}
		else
		{
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_1, -1);
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_1, -1);
		}

		if (!(SEED_RollRandomNumber(&pLevel->pSeed) & 3))
		{
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_FALLEN_CAMP_1, -1);
		}

		DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_FALLEN_CAMP_1, -1);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_STONE_FILL_1, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_STONE_FILL_2, -1, 0, 15);
		return;

	case LEVEL_TAMOEHIGHLAND:
		DRLGOUTWILD_SpawnCottage(pLevel, LVLPREST_ACT1_COTTAGES_2, 1);
		DRLGOUTWILD_SpawnCottage(pLevel, LVLPREST_ACT1_FALLEN_CAMP_2, 0);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_CORRAL_FILL, -1, 0, 15);
		return;

	case LEVEL_BURIALGROUNDS:
		DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, 1, 1, LVLPREST_ACT1_GRAVEYARD, -1, 0);
		return;

	case LEVEL_MOOMOOFARM:
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_BIVOUAC, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_POND, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_CORRAL_FILL, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_SWAMP_FILL_1, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_SWAMP_FILL_2, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_STONE_FILL_1, -1, 0, 15);
		DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT1_STONE_FILL_2, -1, 0, 15);
		return;

	default:
		return;
	}
}

//D2Common.0x6FD85920
void __cdecl DRLGOUTWILD_SpawnCottage(struct D2DrlgLevel* pLevel, int nLvlPrestId, int a3)
{
	if (SEED_RollRandomNumber(&pLevel->pSeed) & 3)
	{
		DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, nLvlPrestId, -1);

		if (a3 && SEED_RollRandomNumber(&pLevel->pSeed) & 1)
		{
			DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, LVLPREST_ACT1_COTTAGES_3, -1);
		}
	}
	else
	{
		DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, nLvlPrestId, -1);
		DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, nLvlPrestId, -1);
	}
}
