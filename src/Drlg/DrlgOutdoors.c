#include "Drlg/D2DrlgOutdoors.h"

#include "D2DataTbls.h"
#include "Drlg/D2DrlgDrlg.h"
#include "Drlg/D2DrlgDrlgAnim.h"
#include "Drlg/D2DrlgDrlgGrid.h"
#include "Drlg/D2DrlgDrlgRoom.h"
#include "Drlg/D2DrlgDrlgVer.h"
#include "Drlg/D2DrlgMaze.h"
#include "Drlg/D2DrlgOutDesr.h"
#include "Drlg/D2DrlgOutPlace.h"
#include "Drlg/D2DrlgOutRoom.h"
#include "Drlg/D2DrlgOutSiege.h"
#include "Drlg/D2DrlgOutWild.h"
#include "Drlg/D2DrlgPreset.h"
#include "Drlg/D2DrlgTileSub.h"
#include "D2Seed.h"
#include <DataTbls/LevelsIds.h>


//D2Common.0x6FD7DC20
int __fastcall DRLGOUTDOORS_GetOutLinkVisFlag(struct D2DrlgLevel* pLevel, struct D2DrlgVertex* pDrlgVertex)
{
	static const struct D2Coord pOffsetCoords[] =
	{
		{ -4, 4 },
		{ 4, -4 },
		{ 12, 4 },
		{ 4, 12 }
	};

	int* pLevelIds = NULL;
	int nIndex = 0;
	int nX = 0;
	int nY = 0;

	if (pDrlgVertex->nPosX == 0)
	{
		nIndex = pDrlgVertex->nPosY == 0;
	}
	else if (pDrlgVertex->nPosY == 0)
	{
		nIndex = (pDrlgVertex->nPosX == pLevel->pOutdoors->nGridWidth - 1) + 1;
	}
	else if (pDrlgVertex->nPosX == pLevel->pOutdoors->nGridWidth - 1)
	{
		nIndex = (pDrlgVertex->nPosY == pLevel->pOutdoors->nGridHeight - 1) + 2;
	}
	else if (pDrlgVertex->nPosY == pLevel->pOutdoors->nGridHeight - 1)
	{
		nIndex = 3;
	}
	else
	{
		return 0;
	}

	nX = pLevel->nPosX + pOffsetCoords[nIndex].nX + 8 * pDrlgVertex->nPosX;
	nY = pLevel->nPosY + pOffsetCoords[nIndex].nY + 8 * pDrlgVertex->nPosY;

	for (struct D2DrlgOrth* pRoomData = pLevel->pOutdoors->pRoomData; pRoomData; pRoomData = pRoomData->pNext)
	{
		if (nIndex == pRoomData->nDirection && DRLGROOM_AreXYInsideCoordinates(pRoomData->pBox, nX, nY))
		{
			if (!pRoomData->bInit)
			{
				pLevelIds = DRLGROOM_GetVisArrayFromLevelId(pLevel->pDrlg, pLevel->nLevelId);
				for (int i = 0; i < 8; ++i)
				{
					if (pLevelIds[i] == pRoomData->pLevel->nLevelId)
					{
						return 1 << (i + 4);
					}
				}
			}

			return 0;
		}
	}

	return 0;
}

//D2Common.0x6FD7DD00
int __fastcall DRLGOUTDOORS_GetPresetIndexFromGridCell(struct D2DrlgLevel* pLevel, int nX, int nY)
{
	if (DRLGOUTDOORS_GetPackedGrid2Info(pLevel->pOutdoors, nX, nY).bHasPickedFile)
	{
		return DRLGGRID_GetGridEntry(&pLevel->pOutdoors->pGrid[0], nX, nY);
	}

	return 0;
}

//D2Common.0x6FD7DD40
void __fastcall DRLGOUTDOORS_AlterAdjacentPresetGridCells(struct D2DrlgLevel* pLevel, int nX, int nY)
{
	DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[0], nX, nY, 0, FLAG_OPERATION_OVERWRITE);
	DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[2], nX, nY, 0, FLAG_OPERATION_OVERWRITE);
}

//D2Common.0x6FD7DD70
void __fastcall DRLGOUTDOORS_SetBlankGridCell(struct D2DrlgLevel* pLevel, int nX, int nY)
{
	DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[0], nX, nY, 0, FLAG_OPERATION_OVERWRITE);
	union D2DrlgOutdoorPackedGrid2Info tPackedInfo = { 0 };
	tPackedInfo.nUnkb08 = true;
	DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[2], nX, nY, tPackedInfo.nPackedValue, FLAG_OPERATION_OVERWRITE);
}

//D2Common.0x6FD7DDB0
unsigned int __fastcall DRLGOUTDOORS_TestGridCellNonLvlLink(struct D2DrlgLevel* pLevel, int nX, int nY)
{
	return DRLGOUTDOORS_GetPackedGrid2Info(pLevel->pOutdoors, nX, nY).bLvlLink == 0;
}

//D2Common.0x6FD7DDD0
BOOL __fastcall DRLGOUTDOORS_TestGridCellSpawnValid(struct D2DrlgLevel* pLevel, int nX, int nY)
{
	union D2DrlgOutdoorPackedGrid2Info tPackedInfo = DRLGOUTDOORS_GetPackedGrid2Info(pLevel->pOutdoors, nX, nY);
	// ! (nVal & 0x1B81)
	return !(tPackedInfo.nUnkb00 || tPackedInfo.nUnkb07 || tPackedInfo.nUnkb08 || tPackedInfo.bHasPickedFile || tPackedInfo.nUnkb11 || tPackedInfo.nUnkb12);
}

//D2Common.0x6FD7DDF0
BOOL __fastcall DRLGOUTDOORS_TestOutdoorLevelPreset(struct D2DrlgLevel* pLevel, int nX, int nY, int nLevelPrestId, int nOffset, char nFlags)
{
	struct D2LvlPrestTxt* pLvlPrestTxtRecord = NULL;
	int nXStart = 0;
	int nYStart = 0;
	int nSizeX = 0;
	int nSizeY = 0;
	int nXEnd = 0;
	int nYEnd = 0;

	nXStart = nX;
	nYStart = nY;

	if (nLevelPrestId)
	{
		pLvlPrestTxtRecord = DATATBLS_GetLvlPrestTxtRecord(nLevelPrestId);
		nSizeX = pLvlPrestTxtRecord->nSizeX / 8;
		nSizeY = pLvlPrestTxtRecord->nSizeY / 8;
	}
	else
	{
		nSizeX = 1;
		nSizeY = 1;
	}

	if (nOffset)
	{
		if (nFlags & 1)
		{
			nYStart -= nOffset;
			nSizeY += nOffset;
		}

		if (nFlags & 2)
		{
			nSizeX += nOffset;
		}

		if (nFlags & 4)
		{
			nSizeY += nOffset;
		}

		if (nFlags & 8)
		{
			nXStart -= nOffset;
			nSizeX += nOffset;
		}
	}

	nXEnd = nXStart + nSizeX;
	nYEnd = nYStart + nSizeY;

	for (int i = nYStart; i < nYEnd; ++i)
	{
		for (int j = nXStart; j < nXEnd; ++j)
		{
			if (!DRLGGRID_IsPointInsideGridArea(&pLevel->pOutdoors->pGrid[2], j, i) || !DRLGOUTDOORS_TestGridCellSpawnValid(pLevel, j, i))
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

//D2Common.0x6FD7DEF0
void __fastcall DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(struct D2DrlgLevel* pLevel, int nX, int nY, int nLevelPrestId, int nPickedFile, BOOL bBorder)
{
	struct D2LvlPrestTxt* pLvlPrestTxtRecord = NULL;
	struct D2DrlgBuild* pDrlgBuild = NULL;
	int nSizeX = 0;
	int nSizeY = 0;

	nSizeX = DRLGPRESET_GetSizeX(nLevelPrestId) / 8;
	nSizeY = DRLGPRESET_GetSizeY(nLevelPrestId) / 8;

	if (nPickedFile == -1)
	{
		pDrlgBuild = pLevel->pBuild;
		while (pDrlgBuild)
		{
			if (pDrlgBuild->nPreset == nLevelPrestId)
			{
				break;
			}

			pDrlgBuild = pDrlgBuild->pNext;
		}

		if (!pDrlgBuild)
		{
			pLvlPrestTxtRecord = DATATBLS_GetLvlPrestTxtRecord(nLevelPrestId);

			pDrlgBuild = D2_ALLOC_STRC_POOL(pLevel->pDrlg->pMempool, struct D2DrlgBuild);
			pDrlgBuild->nPreset = pLvlPrestTxtRecord->dwDef;
			pDrlgBuild->nDivisor = pLvlPrestTxtRecord->dwFiles;
			pDrlgBuild->nRand = SEED_RollLimitedRandomNumber(&pLevel->pSeed, pLvlPrestTxtRecord->dwFiles);
			pDrlgBuild->pNext = pLevel->pBuild;

			pLevel->pBuild = pDrlgBuild;
		}

		pDrlgBuild->nRand = (pDrlgBuild->nRand + 1) % pDrlgBuild->nDivisor;
		nPickedFile = pDrlgBuild->nRand;
	}

	for (int j = nY; j < nY + nSizeY; ++j)
	{
		for (int i = nX; i < nX + nSizeX; ++i)
		{
			union D2DrlgOutdoorPackedGrid2Info tPackedInfo = { 0 };
			tPackedInfo.bHasPickedFile = true;
			tPackedInfo.nPickedFile = nPickedFile;

			DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[2], i, j, 0xF0000, FLAG_OPERATION_AND_NEGATED); // Clear nPickedFile
			DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[2], i, j, tPackedInfo.nPackedValue, FLAG_OPERATION_OR);

			if (bBorder && (nLevelPrestId >= LVLPREST_ACT1_WILD_BORDER_1 && nLevelPrestId <= LVLPREST_ACT1_WILD_BORDER_12 || nLevelPrestId >= LVLPREST_ACT2_DESERT_BORDER_1 && nLevelPrestId <= LVLPREST_ACT2_DESERT_BORDER_12))
			{
				tPackedInfo.nPackedValue = 0;
				tPackedInfo.nUnkb00 = true;
				DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[2], i, j, tPackedInfo.nPackedValue, FLAG_OPERATION_OR);
			}

			DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[0], i, j, 0, FLAG_OPERATION_OVERWRITE);
		}
	}

	DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[0], nX, nY, nLevelPrestId, FLAG_OPERATION_OVERWRITE);
}

//D2Common.0x6FD7E0F0
BOOL __fastcall DRLGOUTDOORS_SpawnPresetFarAway(struct D2DrlgLevel* pLevel, struct D2DrlgCoord* pDrlgCoord, int nLvlPrestId, int nRand, int nOffset, char nFlags)
{
	int nHeight = 0;
	int nWidth = 0;
	int nBaseX = 0;
	int nBaseY = 0;
	int nRandX = 0;
	int nRandY = 0;
	int nAbsX = 0;
	int nAbsY = 0;
	int nPosX = 0;
	int nPosY = 0;
	int nTemp = 0;
	int nMax = 0;
	int nX = 0;
	int nY = 0;

	nWidth = pLevel->pOutdoors->nGridWidth - 2;
	nHeight = pLevel->pOutdoors->nGridHeight - 2;

	nRandX = SEED_RollLimitedRandomNumber(&pLevel->pSeed, nWidth);
	nRandY = SEED_RollLimitedRandomNumber(&pLevel->pSeed, nHeight);

	nBaseX = pDrlgCoord->nPosX + pDrlgCoord->nWidth / 2;
	nBaseY = pDrlgCoord->nPosY + pDrlgCoord->nHeight / 2;
	nX = -1;
	nY = -1;

	for (int i = 0; i <= nHeight; ++i)
	{
		nPosY = (i + nRandY) % nHeight + 1;

		for (int j = 0; j <= nWidth; ++j)
		{
			nPosX = (j + nRandX) % nWidth + 1;

			if (DRLGOUTDOORS_TestOutdoorLevelPreset(pLevel, nPosX, nPosY, nLvlPrestId, nOffset, nFlags))
			{
				nAbsX = 8 * nPosX - nBaseX + pLevel->nPosX + 4;
				if (nAbsX < 0)
				{
					nAbsX = -nAbsX;
				}

				nAbsY = 8 * nPosY - nBaseY + pLevel->nPosY + 4;
				if (nAbsY < 0)
				{
					nAbsY = -nAbsY;
				}

				if (nAbsX <= nAbsY)
				{
					nTemp = nAbsX + 2 * nAbsY;
				}
				else
				{
					nTemp = nAbsY + 2 * nAbsX;
				}

				if (nMax < nTemp / 2)
				{
					nMax = nTemp / 2;
					nX = nPosX;
					nY = nPosY;
				}
			}
		}
	}

	if (nX == -1 || nY == -1)
	{
		return FALSE;
	}
	else
	{
		DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, nX, nY, nLvlPrestId, nRand, 0);
		return TRUE;
	}
}

//D2Common.0x6FD7E330
BOOL __fastcall DRLGOUTDOORS_SpawnOutdoorLevelPreset(struct D2DrlgLevel* pLevel, int nLevelPrestId, int nRand, int nOffset, char nFlags)
{
	struct D2Coord pCoord[256] = {};
	int nWidth = 0;
	int nRand1 = 0;
	int nRand2 = 0;
	int nArea = 0;
	int nX = 0;
	int nY = 0;

	nWidth = pLevel->pOutdoors->nGridWidth - 2;
	nArea = nWidth * (pLevel->pOutdoors->nGridHeight - 2);

	if (nArea)
	{
		for (int i = 0; i < nArea; ++i)
		{
			pCoord[i].nX = i % nWidth;
			pCoord[i].nY = i / nWidth;
		}

		for (int i = 0; i < nArea; ++i)
		{
			nRand1 = SEED_RollLimitedRandomNumber(&pLevel->pSeed, nArea);
			nRand2 = SEED_RollLimitedRandomNumber(&pLevel->pSeed, nArea);

			nX = pCoord[nRand1].nX;
			nY = pCoord[nRand1].nY;

			pCoord[nRand1].nX = pCoord[nRand2].nX;
			pCoord[nRand1].nY = pCoord[nRand2].nY;

			pCoord[nRand2].nX = nX;
			pCoord[nRand2].nY = nY;
		}

		for (int i = 0; i < nArea; ++i)
		{
			nX = pCoord[i].nX + 1;
			nY = pCoord[i].nY + 1;

			if (DRLGOUTDOORS_TestOutdoorLevelPreset(pLevel, nX, nY, nLevelPrestId, nOffset, nFlags))
			{
				DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, nX, nY, nLevelPrestId, nRand, 0);
				return TRUE;
			}
		}
	}

	return FALSE;
}

//D2Common.0x6FD7E4D0
BOOL __fastcall DRLGOUTDOORS_SpawnRandomOutdoorDS1(struct D2DrlgLevel* pLevel, int nLvlPrestId, int nRand)
{
	static const char nOffsetX[] =
	{
		-1, 0, 0, 1, -1, 1, 1, -1
	};

	static const char nOffsetY[] =
	{
		0, -1, 1, 0, -1, 1, -1, 1
	};

	struct D2Coord pCoord[256] = {};
	unsigned int nRand1 = 0;
	unsigned int nRand2 = 0;
	int nWidth = 0;
	int nArea = 0;
	int nPosX = 0;
	int nPosY = 0;
	int nX = 0;
	int nY = 0;

	nWidth = pLevel->pOutdoors->nGridWidth - 2;
	nArea = nWidth * (pLevel->pOutdoors->nGridHeight - 2);

	if (nArea)
	{
		if (nArea > 0)
		{
			for (int i = 0; i < nArea; ++i)
			{
				pCoord[i].nX = i % nWidth;
				pCoord[i].nY = i / nWidth;
			}

			for (int i = 0; i < nArea; ++i)
			{
				nRand1 = SEED_RollLimitedRandomNumber(&pLevel->pSeed, nArea);
				nRand2 = SEED_RollLimitedRandomNumber(&pLevel->pSeed, nArea);

				nX = pCoord[nRand1].nX;
				nY = pCoord[nRand1].nY;

				pCoord[nRand1].nX = pCoord[nRand2].nX;
				pCoord[nRand1].nY = pCoord[nRand2].nY;

				pCoord[nRand2].nX = nX;
				pCoord[nRand2].nY = nY;
			}

			for (int i = 0; i < nArea; ++i)
			{
				nX = pCoord[i].nX + 1;
				nY = pCoord[i].nY + 1;

				if (DRLGOUTDOORS_GetPackedGrid2Info(pLevel->pOutdoors, nX, nY).nUnkb07)
				{
					for (int j = 0; j < 8; ++j)
					{
						nPosX = nX + nOffsetX[j];
						nPosY = nY + nOffsetY[j];

						if (DRLGOUTDOORS_TestOutdoorLevelPreset(pLevel, nPosX, nPosY, nLvlPrestId, 0, 15))
						{
							DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, nPosX, nPosY, nLvlPrestId, nRand, 0);
							return TRUE;
						}
					}
				}
			}
		}

		return DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nLvlPrestId, nRand, 0, 15);
	}

	return FALSE;
}

//D2Common.0x6FD7E6D0
void __fastcall DRLGOUTDOORS_SpawnAct12Waypoint(struct D2DrlgLevel* pLevel)
{
	struct D2Coord pCoord[256] = {};
	int* pVisArray = NULL;
	int nFlags = 0;
	int nWidth = 0;
	int nRand1 = 0;
	int nRand2 = 0;
	int nArea = 0;
	int nX = 0;
	int nY = 0;

	if (pLevel->nLevelId == LEVEL_COLDPLAINS)
	{
		pVisArray = DRLGROOM_GetVisArrayFromLevelId(pLevel->pDrlg, LEVEL_COLDPLAINS);
		for (int i = 0; i < 8; ++i)
		{
			if (pVisArray[i] == LEVEL_BLOODMOOR)
			{
				nFlags = 1 << (i + 4);
				break;
			}
		}

		for (int i = 0; i < pLevel->pOutdoors->nGridHeight; ++i)
		{
			for (int j = 0; j < pLevel->pOutdoors->nGridWidth; ++j)
			{
				if (DRLGGRID_GetGridEntry(&pLevel->pOutdoors->pGrid[1], j, i) & nFlags && !DRLGOUTDOORS_TestGridCellNonLvlLink(pLevel, j,i))
				{
					if (!j)
					{
						j = 1;
					}
					if (!i)
					{
						i = 1;
					}
					if (j == pLevel->pOutdoors->nGridWidth - 1)
					{
						--j;
					}
					if (i == pLevel->pOutdoors->nGridHeight - 1)
					{
						--i;
					}

					DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[1], j, i, 0x20000, FLAG_OPERATION_OR);
					union D2DrlgOutdoorPackedGrid2Info tPackedInfo = { 0 };
					tPackedInfo.nUnkb11 = true;
					DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[2], j, i, tPackedInfo.nPackedValue, FLAG_OPERATION_OR);
					return;
				}
			}
		}
	}

	nWidth = pLevel->pOutdoors->nGridWidth - 2;
	nArea = nWidth * (pLevel->pOutdoors->nGridHeight - 2);

	if (nArea)
	{
		if (nArea > 0)
		{
			for (int i = 0; i < nArea; ++i)
			{
				pCoord[i].nX = i % nWidth;
				pCoord[i].nY = i / nWidth;
			}

			for (int i = 0; i < nArea; ++i)
			{
				nRand1 = SEED_RollLimitedRandomNumber(&pLevel->pSeed, nArea);
				nRand2 = SEED_RollLimitedRandomNumber(&pLevel->pSeed, nArea);

				nX = pCoord[nRand1].nX;
				nY = pCoord[nRand1].nY;

				pCoord[nRand1].nX = pCoord[nRand2].nX;
				pCoord[nRand1].nY = pCoord[nRand2].nY;

				pCoord[nRand2].nX = nX;
				pCoord[nRand2].nY = nY;
			}

			for (int i = 0; i < nArea; ++i)
			{
				nX = pCoord[i].nX + 1;
				nY = pCoord[i].nY + 1;

				if (DRLGOUTDOORS_TestGridCellSpawnValid(pLevel, nX, nY))
				{
					DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[1], nX, nY, 0x10000, FLAG_OPERATION_OR);
					union D2DrlgOutdoorPackedGrid2Info tPackedInfo = { 0 };
					tPackedInfo.nUnkb11 = true;
					DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[2], nX, nY, tPackedInfo.nPackedValue, FLAG_OPERATION_OR);
					break;
				}
			}
		}
	}
}

//D2Common.0x6FD7E940
void __fastcall DRLGOUTDOORS_SpawnAct12Shrines(struct D2DrlgLevel* pLevel, int nShrines)
{
	static const int dword_6FDCF948[] =
	{
		0x1000, 0x2000, 0x4000, 0x8000
	};

	struct D2Coord pCoord[256] = {};
	unsigned int nRand1 = 0;
	unsigned int nRand2 = 0;
	int nWidth = 0;
	int nIndex = 0;
	int nArea = 0;
	int nX = 0;
	int nY = 0;

	nWidth = pLevel->pOutdoors->nGridWidth - 2;
	nArea = nWidth * (pLevel->pOutdoors->nGridHeight - 2);
	nIndex = SEED_RollRandomNumber(&pLevel->pSeed) & 3;

	if (nArea)
	{
		if (nArea > 0)
		{
			for (int i = 0; i < nArea; ++i)
			{
				pCoord[i].nX = i % nWidth;
				pCoord[i].nY = i / nWidth;
			}

			for (int i = 0; i < nArea; ++i)
			{
				nRand1 = SEED_RollLimitedRandomNumber(&pLevel->pSeed, nArea);
				nRand2 = SEED_RollLimitedRandomNumber(&pLevel->pSeed, nArea);

				nX = pCoord[nRand1].nX;
				nY = pCoord[nRand1].nY;

				pCoord[nRand1].nX = pCoord[nRand2].nX;
				pCoord[nRand1].nY = pCoord[nRand2].nY;

				pCoord[nRand2].nX = nX;
				pCoord[nRand2].nY = nY;
			}

			for (int i = 0; i < nArea; ++i)
			{
				if (nShrines <= 0)
				{
					break;
				}

				nX = pCoord[i].nX + 1;
				nY = pCoord[i].nY + 1;

				if (DRLGOUTDOORS_TestGridCellSpawnValid(pLevel, nX, nY))
				{
					DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[1], nX, nY, dword_6FDCF948[nIndex], FLAG_OPERATION_OR);

					union D2DrlgOutdoorPackedGrid2Info tPackedInfo = { 0 };
					tPackedInfo.nUnkb12 = true;
					DRLGGRID_AlterGridFlag(&pLevel->pOutdoors->pGrid[2], nX, nY, tPackedInfo.nPackedValue, FLAG_OPERATION_OR);

					nIndex = (nIndex + 1) % 4;
					--nShrines;
				}
			}
		}
	}
}

//D2Common.0x6FD7EB20
//TODO: a1
void __fastcall DRLGOUTDOORS_AddAct124SecondaryBorder(struct D2DrlgLevel* pLevel, int nLvlSubId, int nLevelPrestId)
{
	struct D2UnkOutdoor a1 = {};

	a1.pLevel = pLevel;
	a1.field_4 = &pLevel->pOutdoors->nWidth;
	a1.pGrid1 = &pLevel->pOutdoors->pGrid[0];
	a1.pGrid2 = &pLevel->pOutdoors->pGrid[2];
	a1.nLevelPrestId = nLevelPrestId;
	a1.field_14 = -1;
	a1.nLvlSubId = nLvlSubId;
	a1.field_1C = DRLGOUTDOORS_TestGridCellNonLvlLink;
	a1.field_20 = DRLGOUTDOORS_TestOutdoorLevelPreset;
	a1.field_2C = DRLGOUTDOORS_AlterAdjacentPresetGridCells;
	a1.field_30 = DRLGOUTDOORS_SetBlankGridCell;
	a1.field_34 = DRLGOUTDOORS_SpawnOutdoorLevelPresetEx;

	DRLGTILESUB_AddSecondaryBorder(&a1);
}

//D2Common.0x6FD7EBA0
void __fastcall DRLGOUTDOORS_AllocOutdoorInfo(struct D2DrlgLevel* pLevel)
{
	pLevel->pOutdoors = D2_CALLOC_STRC_POOL(pLevel->pDrlg->pMempool, struct D2DrlgOutdoorInfo);
}

//D2Common.0x6FD7EBD0
//TODO: a6a, v13, v14
void __fastcall DRLGOUTDOORS_GenerateLevel(struct D2DrlgLevel* pLevel)
{
	struct D2DrlgCoord pDrlgCoord = {};
	struct D2DrlgVertex** ppVertex = NULL;
	struct D2DrlgVertex* pNextVertex = NULL;
	struct D2DrlgVertex* pVertex = NULL;
	struct D2DrlgMap* pDrlgMap = NULL;
	unsigned int dwDt1Mask = 0;
	int nX = 0;
	int nY = 0;
	int a6a = 0;
	int v14 = 0;

	struct D2DrlgOutdoorInfo* pOutdoorInfo = pLevel->pOutdoors;

	pOutdoorInfo->nWidth = 0;
	pOutdoorInfo->nHeight = 0;
	pOutdoorInfo->nGridWidth = pLevel->nWidth / 8;
	pOutdoorInfo->nGridHeight = pLevel->nHeight / 8;

	DRLGGRID_InitializeGridCells(pLevel->pDrlg->pMempool, &pOutdoorInfo->pGrid[0], pOutdoorInfo->nGridWidth, pOutdoorInfo->nGridHeight);
	DRLGGRID_InitializeGridCells(pLevel->pDrlg->pMempool, &pOutdoorInfo->pGrid[1], pOutdoorInfo->nGridWidth, pOutdoorInfo->nGridHeight);
	DRLGGRID_InitializeGridCells(pLevel->pDrlg->pMempool, &pOutdoorInfo->pGrid[2], pOutdoorInfo->nGridWidth, pOutdoorInfo->nGridHeight);
	DRLGGRID_InitializeGridCells(pLevel->pDrlg->pMempool, &pOutdoorInfo->pGrid[3], pOutdoorInfo->nGridWidth, pOutdoorInfo->nGridHeight);

	ppVertex = &pOutdoorInfo->pVertex;

	DRLGVER_CreateVertices(pLevel->pDrlg->pMempool, &pOutdoorInfo->pVertex, &pLevel->pLevelCoords, 0, pOutdoorInfo->pRoomData);

	pVertex = pOutdoorInfo->pVertex;
	do
	{
		pVertex->nPosX /= 8;
		pVertex->nPosY /= 8;
		pVertex = pVertex->pNext;
	}
	while (pVertex != *ppVertex);

	do
	{
		pNextVertex = pVertex->pNext;

		if (pVertex->nPosX == pNextVertex->nPosX && pVertex->nPosY == pNextVertex->nPosY)
		{
			if (pNextVertex == *ppVertex)
			{
				*ppVertex = pVertex;
			}

			pVertex->pNext = pNextVertex->pNext;
			pVertex->dwFlags |= pNextVertex->dwFlags;
			pVertex->nDirection = pNextVertex->nDirection;
			D2_FREE_POOL(pLevel->pDrlg->pMempool, pNextVertex);
		}

		pVertex = pVertex->pNext;
	}
	while (pVertex != *ppVertex);

	switch (DRLG_GetActNoFromLevelId(pLevel->nLevelId))
	{
	case ACT_I:
		DRLGOUTWILD_InitAct1OutdoorLevel(pLevel);
		break;

	case ACT_II:
		DRLGOUTDESR_InitAct2OutdoorLevel(pLevel);
		break;

	case ACT_III:
		DRLGOUTPLACE_InitAct3OutdoorLevel(pLevel);
		break;

	case ACT_IV:
		DRLGOUTDOORS_InitAct4OutdoorLevel(pLevel);
		break;

	case ACT_V:
		DRLGOUTSIEGE_InitAct5OutdoorLevel(pLevel);
		break;

	default:
		break;
	}

	switch (pLevel->nLevelType)
	{
	case LVLTYPE_ACT1_WILDERNESS:
		dwDt1Mask = 0x44103u;
		break;

	case LVLTYPE_ACT3_JUNGLE:
		dwDt1Mask = 0x04;
		break;

	case LVLTYPE_ACT2_DESERT:
	case LVLTYPE_ACT3_KURAST:
	case LVLTYPE_ACT4_MESA:
	case LVLTYPE_ACT4_LAVA:
		dwDt1Mask = 0x01;
		break;

	case LVLTYPE_ACT5_SIEGE:
	case LVLTYPE_ACT5_BARRICADE:
		dwDt1Mask = 0x11;
		break;

	default:
		dwDt1Mask = 0x00;
		break;
	}

	nY = pLevel->nPosY;
	for (int j = 0; j < pOutdoorInfo->nGridHeight; ++j)
	{
		nX = pLevel->nPosX;
		for (int i = 0; i < pOutdoorInfo->nGridWidth; ++i)
		{
			a6a = DRLGGRID_GetGridEntry(&pOutdoorInfo->pGrid[1], i, j);
			union D2DrlgOutdoorPackedGrid2Info tGrid2PackedInfo = DRLGOUTDOORS_GetPackedGrid2Info(pOutdoorInfo, i, j);
			if (tGrid2PackedInfo.bHasPickedFile)
			{
				v14 = DRLGGRID_GetGridEntry(pOutdoorInfo->pGrid, i, j);
				if (v14)
				{
					pDrlgCoord.nWidth = 0;
					pDrlgCoord.nPosX = nX;
					pDrlgCoord.nHeight = 0;
					pDrlgCoord.nPosY = nY;

					pDrlgMap = DRLGPRESET_AllocDrlgMap(pLevel, v14, &pDrlgCoord, &pLevel->pSeed);
					DRLGPRESET_SetPickedFileInDrlgMap(pDrlgMap, tGrid2PackedInfo.nPickedFile);
					DRLGPRESET_BuildArea(pLevel, pDrlgMap, a6a, 0);
				}
			}
			else if (!tGrid2PackedInfo.nUnkb08)
			{
				DRLGOUTPLACE_CreateOutdoorRoomEx(pLevel, nX, nY, 8, 8, a6a, tGrid2PackedInfo.nPackedValue, DRLGGRID_GetGridEntry(&pOutdoorInfo->pGrid[3], i, j), dwDt1Mask);
			}

			nX += 8;
		}

		nY += 8;
	}
}

//D2Common.0x6FD7EEE0
void __fastcall DRLGOUTDOORS_FreeOutdoorInfo(struct D2DrlgLevel* pLevel, BOOL bKeepRoomData)
{
	if (pLevel->pOutdoors->dwFlags & 0x20)
	{
		pLevel->pOutdoors->dwFlags ^= 0x20;
	}

	if (pLevel->pOutdoors->dwFlags & 0x40)
	{
		pLevel->pOutdoors->dwFlags ^= 0x40;
	}

	for (int i = 0; i < ARRAY_SIZE(pLevel->pOutdoors->pGrid); ++i)
	{
		DRLGGRID_FreeGrid(pLevel->pDrlg->pMempool, &pLevel->pOutdoors->pGrid[i]);
	}

	DRLGVER_FreeVertices(pLevel->pDrlg->pMempool, &pLevel->pOutdoors->pVertex);

	for(int i = 0; i < ARRAY_SIZE(pLevel->pOutdoors->pPathStarts); ++i)
	{
		DRLGVER_FreeVertices(pLevel->pDrlg->pMempool, &pLevel->pOutdoors->pPathStarts[i]);
	}

	memset(&pLevel->pOutdoors->pVertices[0], 0x00, 0x78);
	memset(&pLevel->pOutdoors->pVertices[6], 0x00, 0x78);
	memset(&pLevel->pOutdoors->pVertices[12], 0x00, 0x78);
	memset(&pLevel->pOutdoors->pVertices[18], 0x00, 0x78);

	pLevel->pOutdoors->nVertices = 0;

	if (!bKeepRoomData)
	{
		DRLGROOM_FreeRoomData(pLevel->pDrlg->pMempool, pLevel->pOutdoors->pRoomData);
		D2_FREE_POOL(pLevel->pDrlg->pMempool, pLevel->pOutdoors);
		pLevel->pOutdoors = NULL;
	}
}

static const uint8_t byte_6FDCF958[] =
{
	0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10,
	0x0E, 0x0E, 0x06, 0x13, 0x0E, 0x0E, 0x06, 0x13,
	0x0F, 0x0F, 0x05, 0x05, 0x0F, 0x0F, 0x15, 0x15,
	0x08, 0x08, 0x0A, 0x26, 0x08, 0x08, 0x28, 0x14,
	0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10,
	0x0E, 0x0E, 0x06, 0x13, 0x0E, 0x0E, 0x06, 0x13,
	0x0F, 0x0F, 0x05, 0x05, 0x0F, 0x0F, 0x15, 0x15,
	0x08, 0x08, 0x0A, 0x26, 0x08, 0x08, 0x28, 0x14,
	0x0D, 0x0D, 0x07, 0x07, 0x0D, 0x0D, 0x0D, 0x07,
	0x04, 0x04, 0x0B, 0x25, 0x04, 0x04, 0x0B, 0x2B,
	0x03, 0x03, 0x0C, 0x0C, 0x03, 0x03, 0x27, 0x27,
	0x09, 0x09, 0x02, 0x2B, 0x09, 0x09, 0x2C, 0x1A,
	0x0D, 0x0D, 0x07, 0x07, 0x0D, 0x0D, 0x0D, 0x07,
	0x17, 0x17, 0x29, 0x11, 0x17, 0x17, 0x29, 0x11,
	0x03, 0x03, 0x0C, 0x0C, 0x03, 0x03, 0x27, 0x27,
	0x2A, 0x2A, 0x2E, 0x2A, 0x2A, 0x2A, 0x21, 0x1F,
	0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10,
	0x0E, 0x0E, 0x06, 0x13, 0x0E, 0x0E, 0x06, 0x13,
	0x0F, 0x0F, 0x05, 0x05, 0x0F, 0x0F, 0x15, 0x15,
	0x08, 0x08, 0x0A, 0x26, 0x08, 0x08, 0x23, 0x14,
	0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10,
	0x0E, 0x0E, 0x06, 0x13, 0x0E, 0x0E, 0x06, 0x13,
	0x0F, 0x0F, 0x05, 0x05, 0x0F, 0x0F, 0x15, 0x15,
	0x08, 0x08, 0x0A, 0x26, 0x08, 0x08, 0x28, 0x14,
	0x0D, 0x0D, 0x07, 0x07, 0x0D, 0x0D, 0x0D, 0x07,
	0x04, 0x04, 0x0B, 0x25, 0x04, 0x04, 0x0B, 0x25,
	0x12, 0x12, 0x23, 0x23, 0x12, 0x12, 0x16, 0x16,
	0x24, 0x24, 0x2D, 0x22, 0x24, 0x24, 0x1C, 0x1D,
	0x0D, 0x0D, 0x07, 0x07, 0x0D, 0x0D, 0x0D, 0x07,
	0x17, 0x17, 0x29, 0x11, 0x17, 0x17, 0x29, 0x11,
	0x12, 0x12, 0x23, 0x23, 0x12, 0x12, 0x16, 0x16,
	0x18, 0x18, 0x19, 0x20, 0x18, 0x18, 0x1E, 0x01		
};

//D2Common.0x6FD7EFE0
void __fastcall DRLG_OUTDOORS_GenerateDirtPath(struct D2DrlgLevel* pLevel, struct D2DrlgRoom* pDrlgRoom)
{

	DRLGGRID_InitializeGridCells(pLevel->pDrlg->pMempool, &pDrlgRoom->pOutdoor->pDirtPathGrid, pDrlgRoom->nTileWidth + 3, pDrlgRoom->nTileHeight + 3);

	struct D2DrlgCoord tDrlgCoord = {};
	tDrlgCoord.nPosX = pDrlgRoom->nTileXPos - 1;
	tDrlgCoord.nPosY = pDrlgRoom->nTileYPos - 1;
	tDrlgCoord.nWidth = pDrlgRoom->nTileWidth + 3;
	tDrlgCoord.nHeight = pDrlgRoom->nTileHeight + 3;

	for (int i = 0; i < pLevel->pOutdoors->nVertices; ++i)
	{
		for (struct D2DrlgVertex* pVertex = pLevel->pOutdoors->pPathStarts[i]; pVertex != nullptr; pVertex = pVertex->pNext)
		{
			if (pVertex->pNext)
			{
				sub_6FD75F60(&pDrlgRoom->pOutdoor->pDirtPathGrid, pVertex, &tDrlgCoord, 1, FLAG_OPERATION_OR, 2);
			}
		}
	}

	struct D2DrlgGrid* pDirtPathGrid = &pDrlgRoom->pOutdoor->pDirtPathGrid;

	for (int nX = 1; nX <= pDrlgRoom->pDrlgCoord.nWidth; ++nX)
	{
		enum : int { nBoxDimension = 3 };
		int aFlags[nBoxDimension * nBoxDimension] = {};
		#define MapOffsetToBoxIndex(nOffsetX, nOffsetY) \
			(nBoxDimension / 2 + (nOffsetX)) * nBoxDimension + \
				(nBoxDimension - 1) - (nBoxDimension / 2 + (nOffsetY)) // inverted Y

		const int nStartY = pDrlgRoom->pDrlgCoord.nHeight + 1;
		for (int nOffsetX = -1; nOffsetX <= 1; nOffsetX++)
		{
			for (int nOffsetY = -1; nOffsetY <= 1; nOffsetY++)
			{
				aFlags[MapOffsetToBoxIndex(nOffsetX,nOffsetY)] = DRLGGRID_GetGridEntry(pDirtPathGrid, nX + nOffsetX, nStartY + nOffsetY);
			}
		}

		for (int nY = nStartY; nY >= 1; nY--)
		{
			const int nBoxCenterIndex = MapOffsetToBoxIndex(0, 0);
			if (aFlags[nBoxCenterIndex]) // center
			{
				uint32_t nDirectionsWithPathFlags = 0;
				for (int nBoxIndex = nBoxDimension* nBoxDimension - 1; nBoxIndex >= 0; --nBoxIndex)
				{
					if (nBoxIndex != nBoxCenterIndex)
					{
						nDirectionsWithPathFlags = nDirectionsWithPathFlags << 1;
						if (aFlags[nBoxIndex] != 0)
						{
							nDirectionsWithPathFlags |= 1;
						}
					}
				}

				if (nDirectionsWithPathFlags)
				{
					D2_ASSERT(nDirectionsWithPathFlags < (sizeof(byte_6FDCF958) / sizeof(byte_6FDCF958[0])));
					const uint32_t v19 = byte_6FDCF958[nDirectionsWithPathFlags];
					if (v19)
					{
						const uint32_t nNewFloorFLags = ((v19 << 8) | 0x82);
						DRLGGRID_AlterGridFlag(&pDrlgRoom->pOutdoor->pFloorGrid, nX - 1, nY - 1, nNewFloorFLags, FLAG_OPERATION_OVERWRITE);
					}
				}
			}

			// Update flags for next Y (move everything in direction of negative y, then sample the new values
			if (nY >= 2)
			{
				memcpy(aFlags, &aFlags[1], sizeof(aFlags) - sizeof(aFlags[0]));

				aFlags[MapOffsetToBoxIndex(-1, -1)] = DRLGGRID_GetGridEntry(pDirtPathGrid, nX - 1, nY - 2);
				aFlags[MapOffsetToBoxIndex( 0, -1)] = DRLGGRID_GetGridEntry(pDirtPathGrid, nX + 0, nY - 2);
				aFlags[MapOffsetToBoxIndex(+1, -1)] = DRLGGRID_GetGridEntry(pDirtPathGrid, nX + 1, nY - 2);
			}
		}
	}
}

//D2Common.0x6FD7F250
void __fastcall DRLGOUTDOORS_SpawnAct1DirtPaths(struct D2DrlgLevel* pLevel)
{
	struct D2DrlgOutdoorInfo* pOutdoors = pLevel->pOutdoors;
	pOutdoors->nVertices = 0;

	for(struct D2DrlgOrth* pRoomData = pOutdoors->pRoomData; pRoomData != nullptr; pRoomData = pRoomData->pNext)
	{
		struct D2DrlgVertex* pVertex = &pOutdoors->pVertices[pOutdoors->nVertices];
		if (pRoomData->pLevel->nLevelId == LEVEL_ROGUEENCAMPMENT)
		{
			pVertex->nDirection = pRoomData->nDirection;

			// Is west/east inverted here ?
			switch (pRoomData->nDirection)
			{
			case ALTDIR_WEST:
				pVertex->nPosX = pRoomData->pLevel->nPosX + 59;
				pVertex->nPosY = pRoomData->pLevel->nPosY + 19;
				break;

			case ALTDIR_NORTH:
				pVertex->nPosX = pRoomData->pLevel->nPosX + 29;
				pVertex->nPosY = pRoomData->pLevel->nPosY + 35;
				break;

			case ALTDIR_EAST:
				pVertex->nPosX = pRoomData->pLevel->nPosX + 4;
				pVertex->nPosY = pRoomData->pLevel->nPosY + 22;
				break;

			case ALTDIR_SOUTH:
				pVertex->nPosX = pRoomData->pLevel->nPosX + 29;
				pVertex->nPosY = pRoomData->pLevel->nPosY + 3;
				break;

			default:
				break;
			}

			++pOutdoors->nVertices;
		}
		else if (pRoomData->pLevel->nLevelId == LEVEL_MONASTERYGATE)
		{

			pVertex->nPosX = pRoomData->pLevel->nPosX + 27;
			pVertex->nPosY = pRoomData->pLevel->nPosY + 13;

			pVertex->nDirection = ALTDIR_NORTH;
			++pOutdoors->nVertices;
		}
	}

	for (int i = 0; i < pOutdoors->nGridWidth; ++i)
	{
		for (int j = 0; j < pOutdoors->nGridHeight; ++j)
		{
			const int nGrid0Entry = DRLGGRID_GetGridEntry(&pOutdoors->pGrid[0], i, j);
			union D2DrlgOutdoorPackedGrid2Info tPackedInfo = DRLGOUTDOORS_GetPackedGrid2Info(pOutdoors, i, j);

			struct D2DrlgVertex* pVertex = &pOutdoors->pVertices[pOutdoors->nVertices];

			pVertex->nPosX = pLevel->nPosX + 8 * i + 3;
			pVertex->nPosY = pLevel->nPosY + 8 * j + 3;
			pVertex->nDirection = 4;

			const int nPickedFile = tPackedInfo.nPickedFile;

			switch (nGrid0Entry)
			{
			case 4:
				if (nPickedFile == 3)
				{
					pVertex->nDirection = 3;
				}
				break;
			case 5:
				if (nPickedFile == 3)
				{
					pVertex->nDirection = 0;
				}
				break;
			case 6:
				if (nPickedFile == 3)
				{
					pVertex->nDirection = 1;
				}
				break;
			case 7:
				if (nPickedFile == 3)
				{
					pVertex->nDirection = 2;
				}
				break;
			case 24:
				pVertex->nDirection = 1;
				break;
			case 25:
				pVertex->nDirection = 0;
				break;
			case 28:
				if (nPickedFile == 1 && i == (pOutdoors->nGridWidth - 2))
				{
					pVertex->nDirection = 2;
				}
				break;
			case 51:
			case 52:
				pVertex->nDirection = nPickedFile != 0;
				break;
			default:
				break;
			}

			if (pVertex->nDirection != 4)
			{
				++pOutdoors->nVertices;
			}
		}
	}

	for (int i = 0; i < pOutdoors->nVertices; ++i)
	{
		DRLGOUTDOORS_CalculatePathCoordinates(pLevel, &pOutdoors->pVertices[i], &pOutdoors->pVertices[6 + i]);
	}

	sub_6FD7F5B0(pLevel);

	for (int i = 0; i < pOutdoors->nVertices; ++i)
	{
		if (sub_6FD80750(pLevel, i))
		{
			union D2DrlgOutdoorPackedGrid2Info tPackedInfo = { 0 };
			tPackedInfo.nUnkb07 = true;
			DRLGGRID_SetVertexGridFlags(&pOutdoors->pGrid[2], pOutdoors->pPathStarts[i], tPackedInfo.nPackedValue);
			sub_6FD7F810(pLevel, i);
		}
	}
}

//D2Common.0x6FD7F500
void __fastcall DRLGOUTDOORS_CalculatePathCoordinates(struct D2DrlgLevel* pLevel, struct D2DrlgVertex* pVertex1, struct D2DrlgVertex* pVertex2)
{
	pVertex2->nPosX = pVertex1->nPosX - pLevel->nPosX;
	pVertex2->nPosY = pVertex1->nPosY - pLevel->nPosY;

	switch (pVertex1->nDirection)
	{
	case ALTDIR_WEST:
		pVertex2->nPosX = 8 * (pVertex2->nPosX / 8) + 11;
		break;

	case ALTDIR_NORTH:
		pVertex2->nPosY = 8 * (pVertex2->nPosY / 8) + 11;
		break;

	case ALTDIR_EAST:
		pVertex2->nPosX = 8 * (pVertex2->nPosX / 8) - 5;
		break;

	case ALTDIR_SOUTH:
		pVertex2->nPosY = 8 * (pVertex2->nPosY / 8) - 5;
		break;

	default:
		break;
	}

	pVertex2->nPosX += pLevel->nPosX;
	pVertex2->nPosY += pLevel->nPosY;
}

//D2Common.0x6FD7F5B0
void __fastcall sub_6FD7F5B0(struct D2DrlgLevel* pLevel)
{
	static const int nXOffsets[] =
	{
		-1, 0, 0, 1
	};

	static const int nYOffsets[] =
	{
		0, 1, -1, 0
	};

	BOOL bBreak = FALSE;
	int nPosX = 0;
	int nPosY = 0;
	int nX = -1;
	int nY = -1;

	if (pLevel->pOutdoors->dwFlags & 0x10 && (DRLGOUTWILD_GetBridgeCoords(pLevel, &nX, &nY), nX != -1))
	{	
		nPosX = pLevel->nPosX + 8 * nX + 3;
		nPosY = pLevel->nPosY + 8 * nY + 3;
		
		for (int i = 0; i < pLevel->pOutdoors->nVertices; ++i)
		{
			pLevel->pOutdoors->pVertices[18 + i].nPosY = nPosY;

			if (pLevel->pOutdoors->pVertices[i].nPosX <= nPosX)
			{
				pLevel->pOutdoors->pVertices[18 + i].nPosX = nPosX;
				pLevel->pOutdoors->pVertices[18 + i].nDirection = 2;
			}
			else
			{
				pLevel->pOutdoors->pVertices[18 + i].nDirection = 0;
				pLevel->pOutdoors->pVertices[18 + i].nPosX = nPosX + 8;
			}
		}
	}
	else
	{
		for (int i = 0; i < pLevel->pOutdoors->nVertices; ++i)
		{
			if (i)
			{
				pLevel->pOutdoors->pVertices[18 + i].nPosX = pLevel->pOutdoors->pVertices[18].nPosX;
				pLevel->pOutdoors->pVertices[18 + i].nPosY = pLevel->pOutdoors->pVertices[18].nPosY;
				pLevel->pOutdoors->pVertices[18 + i].nDirection = 4;
			}
			else
			{
				if (pLevel->pOutdoors->nVertices == 1)
				{
					nPosX = pLevel->pOutdoors->nGridWidth / 2;
					nPosY = pLevel->pOutdoors->nGridHeight / 2;
				}
				else
				{		
					nX = 0;
					nY = 0;

					for (int j = 0; j < pLevel->pOutdoors->nVertices; ++j)
					{
						nX += pLevel->pOutdoors->pVertices[j].nPosX - pLevel->nPosX;
						nY += pLevel->pOutdoors->pVertices[j].nPosY - pLevel->nPosY;
					}

					nPosX = nX / (8 * pLevel->pOutdoors->nVertices);
					nPosY = nY / (8 * pLevel->pOutdoors->nVertices);
				}

				bBreak = FALSE;

				for (int j = 0; j < 8; ++j)
				{
					if (bBreak)
					{
						break;
					}

					for (int k = 0; k < 4; ++k)
					{
						nX = nPosX + j * nXOffsets[k];
						nY = nPosY + j * nYOffsets[k];

						if (nX >= 0 && nX < pLevel->pOutdoors->nGridWidth && nY >= 0 && nY < pLevel->pOutdoors->nGridHeight)
						{
							if (DRLGOUTDOORS_TestGridCellSpawnValid(pLevel, nX, nY))
							{
								bBreak = TRUE;
								break;
							}
						}
					}
				}

				pLevel->pOutdoors->pVertices[18].nPosX = pLevel->nPosX + 8 * nX + 3;
				pLevel->pOutdoors->pVertices[18].nPosY = pLevel->nPosY + 8 * nY + 3;
				pLevel->pOutdoors->pVertices[18].nDirection = 4;
			}
		}
	}

	for (int i = 0; i < pLevel->pOutdoors->nVertices; ++i)
	{
		DRLGOUTDOORS_CalculatePathCoordinates(pLevel, &pLevel->pOutdoors->pVertices[18 + i], &pLevel->pOutdoors->pVertices[12 + i]);
	}
}

//D2Common.0x6FD7F810
void __fastcall sub_6FD7F810(struct D2DrlgLevel* pLevel, int nVertexId)
{
	static const int nXOffsets[] =
	{
		1, 0, -1, 0
	};

	static const int nYOffsets[] =
	{
		0, 1, 0, -1
	};

	struct D2DrlgVertex* pNewVertex = NULL;
	struct D2DrlgVertex* pVertex = NULL;
	int nOffsetX = 0;
	int nOffsetY = 0;
	int nIndex = 0;

	pVertex = pLevel->pOutdoors->pPathStarts[nVertexId];

	nIndex = SEED_RollRandomNumber(&pLevel->pSeed) & 3;
	if (pVertex)
	{
		if (pLevel->pOutdoors->pVertices[18 + nVertexId].nDirection != 4)
		{
			pNewVertex = DRLGVER_AllocVertex(pLevel->pDrlg->pMempool, 0);
			pNewVertex->nPosX = pLevel->pOutdoors->pVertices[18 + nVertexId].nPosX;
			pNewVertex->nPosY = pLevel->pOutdoors->pVertices[18 + nVertexId].nPosY;
			pNewVertex->pNext = pVertex;

			pLevel->pOutdoors->pPathStarts[nVertexId] = pNewVertex;
		}

		pVertex->nPosX = pLevel->pOutdoors->pVertices[12 + nVertexId].nPosX;
		pVertex->nPosY = pLevel->pOutdoors->pVertices[12 + nVertexId].nPosY;

		pVertex = pVertex->pNext;
		if (pVertex)
		{
			while (pVertex->pNext)
			{
				nOffsetX = ((SEED_RollRandomNumber(&pLevel->pSeed) & 1) + 2) * nXOffsets[nIndex];
				nOffsetY = ((SEED_RollRandomNumber(&pLevel->pSeed) & 1) + 2) * nYOffsets[nIndex];

				nIndex = (nIndex + 1) % 4;

				pVertex->nPosX = 8 * pVertex->nPosX + pLevel->nPosX + nOffsetX + 3;
				pVertex->nPosY = 8 * pVertex->nPosY + pLevel->nPosY + nOffsetY + 3;

				pVertex = pVertex->pNext;
				if (!pVertex)
				{
					return;
				}
			}

			pVertex->nPosX = pLevel->pOutdoors->pVertices[6 + nVertexId].nPosX;
			pVertex->nPosY = pLevel->pOutdoors->pVertices[6 + nVertexId].nPosY;

			pNewVertex = DRLGVER_AllocVertex(pLevel->pDrlg->pMempool, 0);
			pNewVertex->nPosX = pLevel->pOutdoors->pVertices[0 + nVertexId].nPosX;
			pNewVertex->nPosY = pLevel->pOutdoors->pVertices[0 + nVertexId].nPosY;
			pVertex->pNext = pNewVertex;
		}
	}
}

//D2Common.0x6FD7F9B0
void __fastcall DRLGOUTDOORS_InitAct4OutdoorLevel(struct D2DrlgLevel* pLevel)
{
	static const int nMesaLvlPrestIds[] =
	{
		LVLPREST_ACT4_MESA_1_24X24, LVLPREST_ACT4_MESA_2_24X24, LVLPREST_ACT4_MESA_3_24X24
	};

	static const int nPitsLvlPrestIds[] =
	{
		LVLPREST_ACT4_PITS_1_16X16, LVLPREST_ACT4_PITS_2_16X16, LVLPREST_ACT4_PITS_2_16X16
	};

	static const int nLavaLvlPrestIds[] =
	{
		LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_LAVA_X,
		LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_DIABLO_ARM_N, LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_LAVA_X,
		LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_DIABLO_ARM_W, LVLPREST_ACT4_DIABLO_HEART, LVLPREST_ACT4_DIABLO_ARM_E, LVLPREST_ACT4_LAVA_X,
		LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_DIABLO_ARM_S, LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_LAVA_X,
		LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_DIABLO_ENTRY, LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_LAVA_X
	};


	if (pLevel->nLevelId == LEVEL_CHAOSSANCTUM)
	{
		DRLGOUTPLACE_SetOutGridLinkFlags(pLevel);
	}
	else
	{
		DRLGOUTPLACE_SetOutGridLinkFlags(pLevel);
		DRLGOUTPLACE_PlaceAct1245OutdoorBorders(pLevel);
	}

	if (pLevel->nLevelId >= LEVEL_OUTERSTEPPES)
	{
		if (pLevel->nLevelId <= LEVEL_CITYOFTHEDAMNED)
		{
			if (pLevel->pOutdoors->dwFlags & 0x400000)
			{
				DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, 0, 1, LVLPREST_ACT4_FORTRESS_TRANSITION, -1, FALSE);
			}

			if (pLevel->pOutdoors->dwFlags & 0x800000)
			{
				DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, 0, 4, LVLPREST_ACT4_FORTRESS_TRANSITION, -1, FALSE);
			}

			DRLGOUTDOORS_AddAct124SecondaryBorder(pLevel, 1, LVLPREST_ACT4_MESA_BORDER_1);
			DRLGOUTDOORS_AddAct124SecondaryBorder(pLevel, 2, LVLPREST_ACT4_MESA_BORDER_1);
			DRLGOUTDOORS_AddAct124SecondaryBorder(pLevel, 3, LVLPREST_ACT4_MESA_BORDER_1);

			if (pLevel->nLevelId == LEVEL_CITYOFTHEDAMNED)
			{
				DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT4_MESA_WARP, -1, 0, 15);
			}

			const int nMesaId = nMesaLvlPrestIds[pLevel->nLevelId - 104];
			const int nPitId = nPitsLvlPrestIds[pLevel->nLevelId - 104];

			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nMesaId + 0, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nMesaId + 1, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nMesaId + 1, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nMesaId + 2, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nMesaId + 2, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nMesaId + 3, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nMesaId + 3, -1, 0, 15);

			if (pLevel->nLevelId == LEVEL_PLAINSOFDESPAIR)
			{
				DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, LVLPREST_ACT4_MESA_2_IZUAL, -1, 0, 15);
			}

			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nMesaId + 4, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nMesaId + 4, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nMesaId + 4, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nMesaId + 4, -1, 0, 15);

			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nPitId + 0, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nPitId + 1, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nPitId + 1, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nPitId + 2, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nPitId + 2, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nPitId + 3, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nPitId + 3, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nPitId + 3, -1, 0, 15);
			DRLGOUTDOORS_SpawnOutdoorLevelPreset(pLevel, nPitId + 3, -1, 0, 15);
		}
		else if (pLevel->nLevelId == LEVEL_CHAOSSANCTUM)
		{
			for (int i = 0; i < ARRAY_SIZE(nLavaLvlPrestIds); ++i)
			{
				DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(pLevel, 3 * (i % 5), 3 * (i / 5), nLavaLvlPrestIds[i], -1, FALSE);
			}
		}
	}
}
