#pragma once

#include "D2CommonDefinitions.h"
#include "Path.h"
#include "D2Seed.h"

#pragma pack(1)

enum PATH_IDASTAR_CONSTANTS
{
	IDASTAR_MAXPROOM = 50000, // Max size of a room for IDAStar (ptRoomCoords->nSizeGameX * ptRoomCoords->nSizeGameY <= MAXPROOM)
};

struct D2PathIDAStarNode             // sizeof 0x1C
{
	uint16_t nFScore;                    // 0x00
	uint16_t nHeuristicDistanceToTarget; // 0x02
	uint16_t nBestDistanceFromStart;     // 0x04
	int16_t nEvaluationsCount;           // 0x06
	struct D2PathPoint tCoord;              // 0x08
	int* pNeighborsSequence;             // 0x0C
	int nNextNeighborIndex;              // 0x10
	struct D2PathIDAStarNode* pParent;		 // 0x14
	struct D2PathIDAStarNode* pBestChild;   // 0x18
};

enum : size_t { D2PathIDAStarContext_STORAGE_SIZE = 900 };

struct D2PathIDAStarContext                           // sizof 0x36FD8
{
	struct D2PathIDAStarNode* pCurrentNode;				  // 0x00000
	struct D2PathIDAStarNode aNodesStorage[D2PathIDAStarContext_STORAGE_SIZE];	  // 0x00004
	int32_t nNodesCount;								  // 0x06274
	struct D2PathPoint nCoord[3];							  // 0x06278
	int32_t nStride;									  // 0x06284
	int32_t nXOffset;										  // 0x06288
	int32_t nYOffset;										  // 0x0628C
	int32_t aCoordData[IDASTAR_MAXPROOM];				  // 0x06290
	BOOL bRandomDirection;								  // 0x36FD0
	struct D2Seed* pSeed;									  // 0x36FD4
};

#pragma pack()

//1.10f: D2Common.0x6FDA7970
//1.13c: D2Common.0x6FDC0E40
int __cdecl PATH_IdaStar_6FDA7970(struct D2PathInfo* pPathInfo);

//1.10f: D2Common.0x6FDA7D40
//1.13c: D2Common.0x6FDC08F0
struct D2PathIDAStarNode* __cdecl PATH_IDAStar_VisitNodes(struct D2PathIDAStarContext* pContext, int nFScoreCutoff, struct D2PathInfo* pPathInfo);

//1.10c: D2Common.0x6FDA81C0
//1.13f: D2Common.0x6FDC07E0
void __cdecl PATH_IDAStar_GetNextNeighborIndex(struct D2PathIDAStarNode* pNode, struct D2PathIDAStarContext* pContext);

//1.10f: Inlined
//1.13c: D2Common.0x6FDC0840
struct D2PathIDAStarNode* __cdecl sub_6FDC0840(struct D2PathIDAStarNode* pNode, struct D2PathIDAStarContext* pContext);

//1.10f: Inlined
//1.13c: D2Common.0x6FDC0650
signed int __cdecl PATH_IDAStar_FlushNodeToDynamicPath(struct D2PathIDAStarNode* pNode, struct D2PathInfo* pPathInfo);