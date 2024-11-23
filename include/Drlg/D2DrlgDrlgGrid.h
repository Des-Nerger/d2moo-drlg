#pragma once

#include "CommonDefinitions.h"
#include "D2DrlgDrlgVer.h"

#pragma pack(1)

enum FlagOperation
{
	FLAG_OPERATION_OR,
	FLAG_OPERATION_AND,
	FLAG_OPERATION_XOR,
	FLAG_OPERATION_OVERWRITE,
	FLAG_OPERATION_OVERWRITE_IF_ZERO,
	FLAG_OPERATION_AND_NEGATED,
};


struct D2DrlgGrid
{
	int32_t* pCellsFlags;					//0x00
	int32_t* pCellsRowOffsets;				//0x04
	int32_t nWidth;							//0x08
	int32_t nHeight;						//0x0C
	int32_t unk0x10;						//0x10 Maybe indicates if uninitialized? No memset when set to 1
};

#pragma pack()

//D2Common.0x6FD75BA0
void DRGLGRID_OverwriteFlag(int* pFlag, int nFlag);
//D2Common.0x6FD75BB0
void DRGLGRID_OrFlag(int* pFlag, int nFlag);
//D2Common.0x6FD75BC0
void DRGLGRID_AndFlag(int* pFlag, int nFlag);
//D2Common.0x6FD75BD0
void DRGLGRID_XorFlag(int* pFlag, int nFlag);
//D2Common.6FD75BE0
void DRGLGRID_OverwriteFlagIfZero(int* pFlag, int nFlag);
//D2Common.6FD75BF0
void DRGLGRID_AndNegatedFlag(int* pFlag, int nFlag);
//D2Common.0x6FD75C00
BOOL DRLGGRID_IsGridValid(struct D2DrlgGrid* pDrlgGrid);
//D2Common.0x6FD75C20
BOOL DRLGGRID_IsPointInsideGridArea(struct D2DrlgGrid* pDrlgGrid, int nX, int nY);
//D2Common.0x6FD75C50
void DRLGGRID_AlterGridFlag(struct D2DrlgGrid* pDrlgGrid, int nX, int nY, int nFlag, enum FlagOperation eOperation);
//D2Common.0x6FD75C80
int* DRLGGRID_GetGridFlagsPointer(struct D2DrlgGrid* pDrlgGrid, int nX, int nY);
//D2Common.0x6FD75CA0
int DRLGGRID_GetGridEntry(struct D2DrlgGrid* pDrlgGrid, int nX, int nY);
//D2Common.0x6FD75CC0
void DRLGGRID_AlterAllGridFlags(struct D2DrlgGrid* pDrlgGrid, int nFlag, enum FlagOperation eOperation);
//D2Common.0x6FD75D20
void DRLGGRID_AlterEdgeGridFlags(struct D2DrlgGrid* pDrlgGrid, int nFlag, enum FlagOperation eOperation);
//D2Common.6FD75DE0
void sub_6FD75DE0(struct D2DrlgGrid* pDrlgGrid, struct D2DrlgVertex* pDrlgVertex, int nFlag, enum FlagOperation eOperation, BOOL bAlterNextVertex);
//D2Common.0x6FD75F10
void DRLGGRID_SetVertexGridFlags(struct D2DrlgGrid* pDrlgGrid, struct D2DrlgVertex* pDrlgVertex, int nFlag);
//D2Common.0x6FD75F60
void sub_6FD75F60(struct D2DrlgGrid* pDrlgGrid, struct D2DrlgVertex* pDrlgVertex, struct D2DrlgCoord* pDrlgCoord, int nFlag, enum FlagOperation eOperation, int nSize);
//D2Common.0x6FD76230
void DRLGGRID_InitializeGridCells(void* pMemPool, struct D2DrlgGrid* pDrlgGrid, int nWidth, int nHeight);
//D2Common.0x6FD762B0
void DRLGGRID_FillGrid(struct D2DrlgGrid* pDrlgGrid, int nWidth, int nHeight, int* pCellPos, int* pCellRowOffsets);
//D2Common.0x6FD76310
void DRLGGRID_FillNewCellFlags(void* pMemPool, struct D2DrlgGrid* pDrlgGrid, int* pCellPos, struct D2DrlgCoord* pDrlgCoord, int nWidth);
//D2Common.0x6FD76380
void DRLGGRID_AssignCellsOffsetsAndFlags(struct D2DrlgGrid* pDrlgGrid, int* pCellPos, struct D2DrlgCoord* pDrlgCoord, int nWidth, int* pCellFlags);
//D2Common.0x6FD763E0
void DRLGGRID_FreeGrid(void* pMemPool, struct D2DrlgGrid* pDrlgGrid);
//D2Common.0x6FD76410
void DRLGGRID_ResetGrid(struct D2DrlgGrid* pDrlgGrid);
