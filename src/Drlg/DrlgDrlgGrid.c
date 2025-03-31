#include <Drlg/D2DrlgDrlg.h>
#include <Drlg/D2DrlgDrlgGrid.h>
#include <Drlg/D2DrlgDrlgRoom.h>


void(__cdecl* gpfFlagOperations[])(int*, int) =
{
	DRGLGRID_OrFlag,
	DRGLGRID_AndFlag,
	DRGLGRID_XorFlag,
	DRGLGRID_OverwriteFlag,
	DRGLGRID_OverwriteFlagIfZero,
	DRGLGRID_AndNegatedFlag
};


//D2Common.0x6FD75BA0
void __cdecl DRGLGRID_OverwriteFlag(int* pFlag, int nFlag)
{
	*pFlag = nFlag;
}

//D2Common.0x6FD75BB0
void __cdecl DRGLGRID_OrFlag(int* pFlag, int nFlag)
{
	*pFlag |= nFlag;
}

//D2Common.0x6FD75BC0
void __cdecl DRGLGRID_AndFlag(int* pFlag, int nFlag)
{
	*pFlag &= nFlag;
}

//D2Common.0x6FD75BD0
void __cdecl DRGLGRID_XorFlag(int* pFlag, int nFlag)
{
	*pFlag ^= nFlag;
}

//D2Common.6FD75BE0
void __cdecl DRGLGRID_OverwriteFlagIfZero(int* pFlag, int nFlag)
{
	if (*pFlag == 0)
	{
		*pFlag = nFlag;
	}
}

//D2Common.6FD75BF0
void __cdecl DRGLGRID_AndNegatedFlag(int* pFlag, int nFlag)
{
	*pFlag &= ~nFlag;
}

//D2Common.0x6FD75C00
BOOL __cdecl DRLGGRID_IsGridValid(struct D2DrlgGrid* pDrlgGrid)
{
	return pDrlgGrid && pDrlgGrid->pCellsFlags;
}

//D2Common.0x6FD75C20
BOOL __cdecl DRLGGRID_IsPointInsideGridArea(struct D2DrlgGrid* pDrlgGrid, int nX, int nY)
{
	return nX >= 0 && nX < pDrlgGrid->nWidth && nY >= 0 && nY < pDrlgGrid->nHeight;
}

//D2Common.0x6FD75C50
void __cdecl DRLGGRID_AlterGridFlag(struct D2DrlgGrid* pDrlgGrid, int nX, int nY, int nFlag, enum FlagOperation eOperation)
{
	gpfFlagOperations[eOperation](&pDrlgGrid->pCellsFlags[nX + pDrlgGrid->pCellsRowOffsets[nY]], nFlag);
}

//D2Common.0x6FD75C80
int* __cdecl DRLGGRID_GetGridFlagsPointer(struct D2DrlgGrid* pDrlgGrid, int nX, int nY)
{
	return &pDrlgGrid->pCellsFlags[nX + pDrlgGrid->pCellsRowOffsets[nY]];
}

//D2Common.0x6FD75CA0
int __cdecl DRLGGRID_GetGridEntry(struct D2DrlgGrid* pDrlgGrid, int nX, int nY)
{
	return pDrlgGrid->pCellsFlags[nX + pDrlgGrid->pCellsRowOffsets[nY]];
} // Alternatively, use memcpy to please UBSan.

//D2Common.0x6FD75CC0
void __cdecl DRLGGRID_AlterAllGridFlags(struct D2DrlgGrid* pDrlgGrid, int nFlag, enum FlagOperation eOperation)
{
	for (int nY = 0; nY < pDrlgGrid->nHeight; ++nY)
	{
		for (int nX = 0; nX < pDrlgGrid->nWidth; ++nX)
		{
			DRLGGRID_AlterGridFlag(pDrlgGrid, nX, nY, nFlag, eOperation);
		}
	}
}

//D2Common.0x6FD75D20
void __cdecl DRLGGRID_AlterEdgeGridFlags(struct D2DrlgGrid* pDrlgGrid, int nFlag, enum FlagOperation eOperation)
{
	int* pFlagsFirstRow = &pDrlgGrid->pCellsFlags[pDrlgGrid->pCellsRowOffsets[0]];
	int* pFlagsLastRow = &pDrlgGrid->pCellsFlags[pDrlgGrid->pCellsRowOffsets[pDrlgGrid->nHeight - 1]];

	for (int i = 0; i < pDrlgGrid->nWidth; ++i)
	{
		gpfFlagOperations[eOperation](&pFlagsFirstRow[i], nFlag);
		gpfFlagOperations[eOperation](&pFlagsLastRow[i], nFlag);
	}

	for (int i = 1; i < pDrlgGrid->nHeight; ++i)
	{
		const int nCurRowOffset = pDrlgGrid->pCellsRowOffsets[i];
		gpfFlagOperations[eOperation](&pDrlgGrid->pCellsFlags[nCurRowOffset + 0                    ], nFlag);
		gpfFlagOperations[eOperation](&pDrlgGrid->pCellsFlags[nCurRowOffset + pDrlgGrid->nWidth - 1], nFlag);
	}
}

//D2Common.6FD75DE0
//TODO: Name
void __cdecl sub_6FD75DE0(struct D2DrlgGrid* pDrlgGrid, struct D2DrlgVertex* pDrlgVertex, int nFlag, enum FlagOperation eOperation, BOOL bAlterNextVertex)
{
	struct D2DrlgVertex* pNext = pDrlgVertex->pNext;

	if (pDrlgVertex->nPosX == pNext->nPosX && pDrlgVertex->nPosY == pNext->nPosY)
	{
		DRLGGRID_AlterGridFlag(pDrlgGrid, pDrlgVertex->nPosX, pDrlgVertex->nPosY, nFlag, eOperation);
		return;
	}

	int nEndX = 0;
	int nEndY = 0;
	int nX = 0;
	int nY = 0;
	if (pDrlgVertex->nPosX == pNext->nPosX)
	{
		nX = pDrlgVertex->nPosX;
		if (pDrlgVertex->nPosY >= pNext->nPosY)
		{
			nY = pNext->nPosY + 1;
			nEndY = pDrlgVertex->nPosY;
		}
		else
		{
			nY = pDrlgVertex->nPosY + 1;
			nEndY = pNext->nPosY;
		}

		while (nY != nEndY)
		{
			DRLGGRID_AlterGridFlag(pDrlgGrid, nX, nY, nFlag, eOperation);

			++nY;
		}
	}
	else
	{
		nY = pDrlgVertex->nPosY;
		if (pDrlgVertex->nPosX >= pNext->nPosX)
		{
			nEndX = pDrlgVertex->nPosX;
			nX = pNext->nPosX + 1;
		}
		else
		{
			nEndX = pNext->nPosX;
			nX = pDrlgVertex->nPosX + 1;
		}

		while (nX != nEndX)
		{
			DRLGGRID_AlterGridFlag(pDrlgGrid, nX, nY, nFlag, eOperation);

			++nX;
		}
	}

	DRLGGRID_AlterGridFlag(pDrlgGrid, pDrlgVertex->nPosX, pDrlgVertex->nPosY, nFlag, eOperation);

	if (bAlterNextVertex)
	{
		DRLGGRID_AlterGridFlag(pDrlgGrid, pDrlgVertex->pNext->nPosX, pDrlgVertex->pNext->nPosY, nFlag, eOperation);
	}
}

//D2Common.0x6FD75F10
void __cdecl DRLGGRID_SetVertexGridFlags(struct D2DrlgGrid* pDrlgGrid, struct D2DrlgVertex* pDrlgVertex, int nFlag)
{
	int nX = 0;
	int nY = 0;

	struct D2DrlgVertex* pVertex = pDrlgVertex;

	while (pVertex)
	{
		nX = pVertex->nPosX;
		nY = pVertex->nPosY;
		pVertex = pVertex->pNext;

		if (nX >= 0 && nX < pDrlgGrid->nWidth && nY >= 0 && nY < pDrlgGrid->nHeight)
		{
			DRLGGRID_AlterGridFlag(pDrlgGrid, nX, nY, nFlag, FLAG_OPERATION_OR);
		}
	}
}

//D2Common.0x6FD75F60
//TODO: Name
void __cdecl sub_6FD75F60(struct D2DrlgGrid* pDrlgGrid, struct D2DrlgVertex* pDrlgVertex, struct D2DrlgCoord* pDrlgCoord, int nFlag, enum FlagOperation eOperation, int nSize)
{
	int nX = pDrlgVertex->nPosX;
	int nY = pDrlgVertex->nPosY;

	int nXDiff = pDrlgVertex->pNext->nPosX - nX;
	int nYDiff = pDrlgVertex->pNext->nPosY - nY;

	int nXInc = 0;
	if (nXDiff >= 0)
	{
		nXInc = 1;
	}
	else
	{
		nXDiff = -nXDiff;
		nXInc = -1;
	}

	int nYInc = 0;
	if (nYDiff >= 0)
	{
		nYInc = 1;
	}
	else
	{
		nYDiff = -nYDiff;
		nYInc = -1;
	}

	int nIndexX = nX - pDrlgCoord->nPosX;
	int nIndexY = nY - pDrlgCoord->nPosY;

	int nCheck = 0;
	if (nXDiff >= nYDiff)
	{
		for (int i = 0; i < nSize; ++i)
		{
			if (DRLGROOM_AreXYInsideCoordinates(pDrlgCoord, nX, nY + i))
			{
				DRLGGRID_AlterGridFlag(pDrlgGrid, nIndexX, nIndexY + i, nFlag, eOperation);
			}
		}

		for (int j = 0; j < nXDiff; ++j)
		{
			nX += nXInc;
			nCheck += nYDiff;

			if (nCheck > nXDiff)
			{
				nY += nYInc;
				nCheck -= nXDiff;
			}

			nIndexX = nX - pDrlgCoord->nPosX;
			nIndexY = nY - pDrlgCoord->nPosY;

			for (int i = 0; i < nSize; ++i)
			{
				if (DRLGROOM_AreXYInsideCoordinates(pDrlgCoord, nX, nY + i))
				{
					DRLGGRID_AlterGridFlag(pDrlgGrid, nIndexX, nIndexY + i, nFlag, eOperation);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < nSize; ++i)
		{
			if (DRLGROOM_AreXYInsideCoordinates(pDrlgCoord, nX + i, nY))
			{
				DRLGGRID_AlterGridFlag(pDrlgGrid, nIndexX + i, nIndexY, nFlag, eOperation);
			}
		}

		for (int j = 0; j < nYDiff; ++j)
		{
			nY += nYInc;
			nCheck += nXDiff;

			if (nCheck > nYDiff)
			{
				nX += nXInc;
				nCheck -= nYDiff;
			}

			nIndexX = nX - pDrlgCoord->nPosX;
			nIndexY = nY - pDrlgCoord->nPosY;

			for (int i = 0; i < nSize; ++i)
			{
				if (DRLGROOM_AreXYInsideCoordinates(pDrlgCoord, nX + i, nY))
				{
					DRLGGRID_AlterGridFlag(pDrlgGrid, nIndexX + i, nIndexY, nFlag, eOperation);
				}
			}
		}
	}
}

//D2Common.0x6FD76230
void __cdecl DRLGGRID_InitializeGridCells(void* pMemPool, struct D2DrlgGrid* pDrlgGrid, int nWidth, int nHeight)
{
	pDrlgGrid->nWidth = nWidth;
	pDrlgGrid->nHeight = nHeight;

	// nHeight for the row offsets, nHeight + nWidth for the cells
	pDrlgGrid->pCellsRowOffsets = (int*)D2_CALLOC_POOL(pMemPool, sizeof(int) * nHeight * (nWidth + 1));
	
	pDrlgGrid->pCellsFlags = &pDrlgGrid->pCellsRowOffsets[nHeight];

	int nRowOffset = 0;
	for (int i = 0; i < nHeight; ++i)
	{
		pDrlgGrid->pCellsRowOffsets[i] = nRowOffset;
		nRowOffset += nWidth;
	}

	pDrlgGrid->unk0x10 = 0;
}

//D2Common.0x6FD762B0
void __cdecl DRLGGRID_FillGrid(struct D2DrlgGrid* pDrlgGrid, int nWidth, int nHeight, int* pCellPos, int* pCellRowOffsets)
{

	pDrlgGrid->nWidth = nWidth;
	pDrlgGrid->nHeight = nHeight;

	pDrlgGrid->pCellsFlags = pCellPos;
	memset(pCellPos, 0x00, sizeof(int) * nHeight * nWidth);

	pDrlgGrid->pCellsRowOffsets = pCellRowOffsets;

	int nRowOffset = 0;
	for (int i = 0; i < nHeight; ++i)
	{
		pDrlgGrid->pCellsRowOffsets[i] = nRowOffset;
		nRowOffset += nWidth;
	}

	pDrlgGrid->unk0x10 = 0;
}

//D2Common.0x6FD76310
void __cdecl DRLGGRID_FillNewCellFlags(void* pMemPool, struct D2DrlgGrid* pDrlgGrid, int* pCellPos, struct D2DrlgCoord* pDrlgCoord, int nWidth)
{

	pDrlgGrid->nWidth = pDrlgCoord->nWidth;
	pDrlgGrid->nHeight = pDrlgCoord->nHeight;

	pDrlgGrid->pCellsFlags = &pCellPos[pDrlgCoord->nPosX + nWidth * pDrlgCoord->nPosY];

	pDrlgGrid->pCellsRowOffsets = (int32_t*)D2_ALLOC_POOL(pMemPool, sizeof(int) * pDrlgCoord->nHeight);

	int nOffset = 0;
	for (int i = 0; i < pDrlgCoord->nHeight; ++i)
	{
		pDrlgGrid->pCellsRowOffsets[i] = nOffset;
		nOffset += nWidth;
	}

	pDrlgGrid->unk0x10 = 1;
}

//D2Common.0x6FD76380
void __cdecl DRLGGRID_AssignCellsOffsetsAndFlags(struct D2DrlgGrid* pDrlgGrid, int* pCellPos, struct D2DrlgCoord* pDrlgCoord, int nWidth, int* pCellFlags)
{
	pDrlgGrid->nWidth = pDrlgCoord->nWidth;
	pDrlgGrid->nHeight = pDrlgCoord->nHeight;

	pDrlgGrid->pCellsFlags = &pCellPos[pDrlgCoord->nPosX + nWidth * pDrlgCoord->nPosY];
	pDrlgGrid->pCellsRowOffsets = pCellFlags;

	for (int i = 0; i < pDrlgCoord->nHeight; ++i)
	{
		pDrlgGrid->pCellsRowOffsets[i] = i * nWidth;
	}

	pDrlgGrid->unk0x10 = 1;
}

//D2Common.0x6FD763E0
void __cdecl DRLGGRID_FreeGrid(void* pMemPool, struct D2DrlgGrid* pDrlgGrid)
{
	if (pDrlgGrid->pCellsRowOffsets)
	{
		D2_FREE_POOL(pMemPool, pDrlgGrid->pCellsRowOffsets);
	}

	pDrlgGrid->pCellsFlags = NULL;
	pDrlgGrid->pCellsRowOffsets = NULL;
}

//D2Common.0x6FD76410
void __cdecl DRLGGRID_ResetGrid(struct D2DrlgGrid* pDrlgGrid)
{
	pDrlgGrid->pCellsFlags = 0;
	pDrlgGrid->pCellsRowOffsets = 0;
}
