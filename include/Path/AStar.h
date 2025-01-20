#pragma once

#include "D2CommonDefinitions.h"
#include "Path.h"
#include "D2Seed.h"

// Note: Very similar to D1's path finding, but using a cache for the open/closed set

#pragma pack(1)

struct D2PathFoWallNode					    //sizeof 0x38
{
	struct D2PathPoint tPoint;						//0x00
	int16_t nFScore;							//0x04
	int16_t nHeuristicDistanceToTarget;			//0x06
	int16_t nBestDistanceFromStart;				//0x08
	uint16_t wPad;								//0x0A
	struct D2PathFoWallNode* pBestParent;		    //0x0C
	struct D2PathFoWallNode* pChildren[8];			//0x10
	struct D2PathFoWallNode* pNextCachePoint;		//0x30
	struct D2PathFoWallNode* pNextSortedByFScore;	//0x34
};

enum : size_t {
	D2PathFoWallContext_CACHE_SIZE = 128,
	D2PathFoWallContext_STORAGE_SIZE = 200,
	D2PathFoWallContext_STACK_SIZE = 200,
};

struct D2PathFoWallContext						  //sizeof 0x32EC
{
	struct D2PathFoWallNode* aPendingCache[D2PathFoWallContext_CACHE_SIZE];  //0x0000 Open set
	struct D2PathFoWallNode* aVisitedCache[D2PathFoWallContext_CACHE_SIZE];  //0x0200 Closed set
	struct D2PathFoWallNode* pSortedListByFScore;		  //0x0400 Sorted in ascending order (best first)
	struct D2PathFoWallNode aNodesStorage[D2PathFoWallContext_STORAGE_SIZE]; //0x0404 Allocator
	int32_t nNodesCount;							  //0x2FC4 Number of allocated nodes
	struct D2PathFoWallNode* aPointsStack[D2PathFoWallContext_STACK_SIZE];   //0x2FC8 Stack used for propagation of best distance
	int32_t nStackCount;							  //0x32E8
};


#pragma pack()

//D2Common.0x6FDA69E0
int __fastcall PATH_AStar_ComputePath(struct D2PathInfo* pPathInfo);

//D2Common.0x6FDA6D10
int __fastcall PATH_AStar_PushToVisitedCache(struct D2PathFoWallContext* pContext, struct D2PathFoWallNode* pNode);

//1.10f: D2Common.0x6FDA6D50
//1.13c: D2Common.0x6FDCB3C0
BOOL __fastcall PATH_AStar_ExploreChildren(struct D2PathInfo* pPathInfo, struct D2PathFoWallContext* pContext, struct D2PathFoWallNode* a3, struct D2PathPoint tTargetCoord);

//1.10f: D2Common.0x6FDA7230
//1.13c: D2Common.0x6FDCAF70
int __stdcall PATH_AStar_Heuristic(struct D2PathPoint tPoint1, struct D2PathPoint tPoint2);
// Helper function
int16_t PATH_AStar_HeuristicForNeighbor(struct D2PathPoint tPoint, struct D2PathPoint tNeighbor);

//1.00:  D2Common.0x10057A10
//1.10f: D2Common.0x6FDA7280
//1.13c: D2Common.0x6FDCAF20
struct D2PathFoWallNode* __fastcall PATH_AStar_GetNodeFromPendingCache(struct D2PathFoWallContext* pContext, struct D2PathPoint tPathPoint);
//1.00:  D2Common.0x10057A10
//1.10f: D2Common.0x6FDA72D0
//1.13c: D2Common.0x6FDCAED0
struct D2PathFoWallNode* __fastcall PATH_AStar_FindPointInVisitedCache(struct D2PathFoWallContext* pContext, struct D2PathPoint tPathPoint);

//1.10f: D2Common.0x6FDA7320
//1.13c: D2Common.0x6FDCAE20
void __fastcall PATH_AStar_MakeCandidate(struct D2PathFoWallContext* pContext, struct D2PathFoWallNode* pNode);

//1.10f: D2Common.0x6FDA7390
//1.13c: D2Common.0x6FDCAC50
void __fastcall PATH_AStar_PropagateNewFScoreToChildren(struct D2PathFoWallContext* pContext, int nUnused, struct D2PathFoWallNode* pNewNode);

//1.10f: D2Common.0x6FDA7450
//1.13c: Inlined
struct D2PathFoWallNode* __fastcall PATH_AStar_GetNewNode(struct D2PathFoWallContext* pContext);

//1.10f: D2Common.0x6FDA7490
//1.13c: D2Common.0x6FDCAFB0
BOOL __fastcall PATH_AStar_EvaluateNeighbor(struct D2PathInfo* pPathInfo, struct D2PathFoWallContext* pContext, struct D2PathFoWallNode* pCurrentNode, struct D2PathPoint tNewPointCoord, struct D2PathPoint tTargetCoord);

//D2Common.0x6FDA78A0
signed int __fastcall PATH_AStar_FlushNodeToDynamicPath(struct D2PathFoWallNode* pNode, struct D2PathInfo* pPathInfo);

