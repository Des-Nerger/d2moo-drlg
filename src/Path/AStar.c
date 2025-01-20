#include "Path/Path.h"
#include "Path/AStar.h"

#include "D2Collision.h"
#include "D2Dungeon.h"
#include <math.h>

//1.10f: D2Common.0x6FDD17E0
//1.13c: D2Common.0x6FDDB458
const int gaIdaStar_PointCacheHashMaskX[D2PathFoWallContext_CACHE_SIZE] =
{
	57, 92, 72, 94, 119, 80, 14, 84, 93, 17, 20, 37, 87, 70, 100, 108,
	30, 91, 85, 60, 40, 3, 118, 78, 81, 109, 43, 26, 67, 27, 49, 75,
	69, 2, 58, 36, 55, 5, 122, 125, 11, 35, 77, 59, 29, 18, 28, 82,
	63, 86, 83, 105, 90, 48, 101, 38, 115, 9, 41, 89, 95, 19, 1, 61,
	51, 7, 110, 34, 126, 47, 15, 6, 99, 22, 104, 4, 71, 97, 121, 114,
	0, 112, 62, 54, 23, 111, 74, 123, 45, 120, 44, 50, 31, 39, 42, 66,
	33, 113, 53, 64, 16, 65, 106, 96, 88, 24, 46, 56, 103, 68, 10, 117,
	25, 32, 124, 127, 76, 8, 79, 21, 102, 52, 107, 73, 13, 116, 98, 12
};

//1.10f: D2Common.0x6FDD19E0
//1.13c: D2Common.0x6FDDB658
const int gaIdaStar_PointCacheHashMaskY[D2PathFoWallContext_CACHE_SIZE] =
{
	114, 80, 68, 91, 97, 73, 127, 88, 18, 58, 101, 41, 19, 108, 6, 8,
	24, 99, 83, 33, 77, 56, 74, 37, 43, 107, 85, 12, 75, 30, 27, 23,
	92, 69, 115, 2, 84, 7, 17, 20, 117, 67, 31, 121, 111, 105, 120, 96,
	94, 122, 47, 25, 4, 112, 34, 62, 10, 89, 1, 40, 76, 71, 49, 51,
	90, 55, 118, 50, 116, 106, 109, 42, 45, 65, 28, 60, 123, 36, 98, 48,
	124, 22, 64, 38, 15, 102, 110, 79, 57, 125, 59, 21, 70, 63, 93, 86,
	66, 35, 16, 53, 61, 103, 29, 52, 119, 46, 100, 3, 0, 126, 32, 81,
	87, 9, 26, 14, 95, 113, 13, 54, 104, 82, 44, 72, 5, 78, 11, 39
};


//1.10f: Inlined
//1.13c: D2Common.0x6FDCB2C0
BOOL PATH_AStar_TargetLocationHasEnoughRoom(struct D2PathInfo* pPathInfo)
{
	if (!pPathInfo->pDynamicPath->pTargetUnit)
	{
		return TRUE;
	}
	struct D2ActiveRoom* pStartRoom = pPathInfo->pStartRoom;
	const int nTargetY = pPathInfo->tTargetCoord.Y;
	const int nTargetX = pPathInfo->tTargetCoord.X;
	const int32_t nCollisionMask = pPathInfo->nCollisionMask;
	const int32_t nCollisionPattern = pPathInfo->nCollisionPattern;
	return !COLLISION_CheckAnyCollisionWithPattern(pStartRoom, nTargetX - 2, nTargetY - 2, nCollisionPattern, nCollisionMask)
		|| !COLLISION_CheckAnyCollisionWithPattern(pStartRoom, nTargetX - 2, nTargetY + 2, nCollisionPattern, nCollisionMask)
		|| !COLLISION_CheckAnyCollisionWithPattern(pStartRoom, nTargetX + 2, nTargetY - 2, nCollisionPattern, nCollisionMask)
		|| !COLLISION_CheckAnyCollisionWithPattern(pStartRoom, nTargetX + 2, nTargetY + 2, nCollisionPattern, nCollisionMask)
		|| !COLLISION_CheckAnyCollisionWithPattern(pStartRoom, nTargetX - 2, nTargetY + 0, nCollisionPattern, nCollisionMask)
		|| !COLLISION_CheckAnyCollisionWithPattern(pStartRoom, nTargetX + 0, nTargetY - 2, nCollisionPattern, nCollisionMask)
		|| !COLLISION_CheckAnyCollisionWithPattern(pStartRoom, nTargetX + 2, nTargetY + 0, nCollisionPattern, nCollisionMask)
		|| !COLLISION_CheckAnyCollisionWithPattern(pStartRoom, nTargetX + 0, nTargetY + 2, nCollisionPattern, nCollisionMask);
}

// Helper function
static struct D2PathFoWallNode* PATH_IdaStar_FindSortedByFScoreInsertionPoint(struct D2PathFoWallContext* pContext, uint16_t nFScore)
{
	struct D2PathFoWallNode* pInsertionPoint = nullptr;
	for (struct D2PathFoWallNode* pCurrent = pContext->pSortedListByFScore;
		pCurrent != nullptr;
		pCurrent = pCurrent->pNextSortedByFScore)
	{
		if (pCurrent->nFScore >= nFScore)
		{
			break;
		}
		pInsertionPoint = pCurrent;
	}
	return pInsertionPoint;
}

// Helper function
static struct D2PathFoWallNode* PATH_AStar_RemoveFromPendingCache(struct D2PathFoWallContext* pContext, struct D2PathFoWallNode* pToRemove)
{
	struct D2PathFoWallNode* pPreviousPoint = nullptr;

	const uint8_t nCacheIndex = (gaIdaStar_PointCacheHashMaskX[pToRemove->tPoint.X & 0x7F] + gaIdaStar_PointCacheHashMaskY[pToRemove->tPoint.Y & 0x7F]) & 0x7F;
	for (struct D2PathFoWallNode* pCacheEntry = pContext->aPendingCache[nCacheIndex];
		pCacheEntry != nullptr;
		pCacheEntry = pCacheEntry->pNextCachePoint)
	{
		if (pCacheEntry == pToRemove)
		{
			break;
		}

		pPreviousPoint = pCacheEntry;

		// Safety check, original game didn't actually stop on pCache0Entry != nullptr
		// This is because it expects the point to be in the list!
		D2_ASSERT(pCacheEntry->pNextCachePoint != nullptr);
	}

	if (pPreviousPoint)
	{
		pPreviousPoint->pNextCachePoint = pToRemove->pNextCachePoint;
	}
	else
	{
		pContext->aPendingCache[nCacheIndex] = pToRemove->pNextCachePoint; // Handle the case where pContext->aCache0[nCacheIndex] == pToRemove
	}
	pToRemove->pNextCachePoint = 0; // Not in the cache list anymore
	return pPreviousPoint;
}

//1.10f: Inlined
//1.13c: D2Common.0x6FDCB220
// TODO: rename?
struct D2PathFoWallNode* PATH_AStar_PopBestScoreForVisit(struct D2PathFoWallContext* pContext)
{
	struct D2PathFoWallNode* pPopped = pContext->pSortedListByFScore;
	if (pPopped)
	{
		// pop from sorted list
		pContext->pSortedListByFScore = pPopped->pNextSortedByFScore;
		PATH_AStar_RemoveFromPendingCache(pContext, pPopped);
		PATH_AStar_PushToVisitedCache(pContext, pPopped);
	}
	return pPopped;
}

//1.00:  D2Common.0x10056EC0
//1.10f: D2Common.0x6FDA69E0
//1.13c: D2Common.0x6FDCB630
int __fastcall PATH_AStar_ComputePath(struct D2PathInfo* pPathInfo)
{
	if (!PATH_AStar_TargetLocationHasEnoughRoom(pPathInfo))
	{
		return 0;
	}

	const struct D2PathPoint tStartCoord = pPathInfo->tStartCoord;
	const struct D2PathPoint tTargetCoord = pPathInfo->tTargetCoord;

	struct D2PathFoWallContext tContext = {};
	tContext.nNodesCount = 1;

	const int nDistToTarget = PATH_AStar_Heuristic(tTargetCoord, tStartCoord);
	tContext.aNodesStorage[0].nBestDistanceFromStart = 0;
	tContext.aNodesStorage[0].nHeuristicDistanceToTarget = nDistToTarget;
	tContext.aNodesStorage[0].nFScore = nDistToTarget;
	tContext.aNodesStorage[0].tPoint = tStartCoord;
	PATH_AStar_MakeCandidate(&tContext, &tContext.aNodesStorage[0]);
	struct D2PathFoWallNode* pBestNode = 0;
	for (struct D2PathFoWallNode* pCurNodeToVisit = PATH_AStar_PopBestScoreForVisit(&tContext);
		pCurNodeToVisit != nullptr;
		pCurNodeToVisit = PATH_AStar_PopBestScoreForVisit(&tContext)
		)
	{
		if (pBestNode == nullptr
			|| pCurNodeToVisit->nHeuristicDistanceToTarget < pBestNode->nHeuristicDistanceToTarget
			|| (pCurNodeToVisit->nHeuristicDistanceToTarget == pBestNode->nHeuristicDistanceToTarget
				&& pCurNodeToVisit->nBestDistanceFromStart > (pBestNode->nBestDistanceFromStart + 5))
			)
		{
			pBestNode = pCurNodeToVisit;
		}

		if (// If reached target point
			pCurNodeToVisit->nHeuristicDistanceToTarget == 0
			// or can't allocate new nodes
			|| !PATH_AStar_ExploreChildren(pPathInfo, &tContext, pCurNodeToVisit, tTargetCoord)
			)
		{
			break; // Then stop here
		}
	}
	if (pBestNode)
	{
		return PATH_AStar_FlushNodeToDynamicPath(pBestNode, pPathInfo);
	}
	return 0;
}

//D2Common.0x6FDA6D10
int __fastcall PATH_AStar_PushToVisitedCache(struct D2PathFoWallContext* pContext, struct D2PathFoWallNode* pNode)
{
	const uint8_t nHash = (gaIdaStar_PointCacheHashMaskX[pNode->tPoint.X & 0x7F] + gaIdaStar_PointCacheHashMaskY[pNode->tPoint.Y & 0x7F]) & 0x7F;
	pNode->pNextCachePoint = pContext->aVisitedCache[nHash];
	pContext->aVisitedCache[nHash] = pNode;
	return nHash;
}

//1.10f: D2Common.0x6FDA6D50
//1.13c: D2Common.0x6FDCB3C0
BOOL __fastcall PATH_AStar_ExploreChildren(struct D2PathInfo* pPathInfo, struct D2PathFoWallContext* pContext, struct D2PathFoWallNode* a3, struct D2PathPoint tTargetCoord)
{
	static const struct D2Coord aOffsets[] =
	{
		{-1,-1},
		{-1,1},
		{1,-1},
		{1,1},
		{-1,0},
		{0,-1},
		{1,0},
		{0,1}
	};

	for (int i = 0; i < ARRAY_SIZE(aOffsets); i++)
	{
		struct D2Coord tOffset = aOffsets[i];
		struct D2PathPoint tNewPointCoord = a3->tPoint;
		tNewPointCoord.X += tOffset.nX;
		tNewPointCoord.Y += tOffset.nY;

		if (!COLLISION_CheckAnyCollisionWithPattern(pPathInfo->pStartRoom, tNewPointCoord.X, tNewPointCoord.Y, pPathInfo->nCollisionPattern, pPathInfo->nCollisionMask) &&
			!PATH_AStar_EvaluateNeighbor(pPathInfo, pContext, a3, tNewPointCoord, tTargetCoord))
		{
			return FALSE;
		}
	}

	return TRUE;
}

//1.10f: D2Common.0x6FDA7230
//1.13c: D2Common.0x6FDCAF70
// Diagonal distance with D=2 and D2=3 (2 to move to an adjacent pixel, 3 in diagonal)
// http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html#diagonal-distance 
// Note: This heuristic returns values in the same order as the Euclidian distance to pixel centers
//       It is both "admissible" and "consistent".
// Sample return values for the first quadrant:
// dY
// |6 7 8 9
// |4 5 6 8
// |2 3 5 7
// |0 2 4 6
// +-------dX
int __stdcall PATH_AStar_Heuristic(struct D2PathPoint tPoint1, struct D2PathPoint tPoint2)
{
	const int nDiffX = abs(tPoint1.X - tPoint2.X);
	const int nDiffY = abs(tPoint1.Y - tPoint2.Y);
	if (nDiffX < nDiffY)
	{
		return nDiffX + 2 * nDiffY;
	}
	else
	{
		return nDiffY + 2 * nDiffX;
	}
}

// Helper function
int16_t PATH_AStar_HeuristicForNeighbor(struct D2PathPoint tPoint, struct D2PathPoint tNeighbor)
{
	if (tPoint.X == tNeighbor.X || tPoint.Y == tNeighbor.Y)
	{
		return 2; // Adjacent pixel
	}
	else
	{
		return 3; // Diagonal pixel
	}
}

//1.00:  D2Common.0x10057A10
//1.10f: D2Common.0x6FDA7280
//1.13c: D2Common.0x6FDCAF20
struct D2PathFoWallNode* __fastcall PATH_AStar_GetNodeFromPendingCache(struct D2PathFoWallContext* pContext, struct D2PathPoint tPathPoint)
{
	const uint8_t nHash = (uint8_t)((gaIdaStar_PointCacheHashMaskX[tPathPoint.X & 0x7F] + gaIdaStar_PointCacheHashMaskY[tPathPoint.Y & 0x7F]) & 0x7F);
	for (struct D2PathFoWallNode* pNode = pContext->aPendingCache[nHash];
		pNode != nullptr;
		pNode = pNode->pNextCachePoint)
	{
		if (tPathPoint.X == pNode->tPoint.X && tPathPoint.Y == pNode->tPoint.Y)
		{
			return pNode;
		}
	}
	return nullptr;
}

//1.00:  D2Common.0x10057A10
//1.10f: D2Common.0x6FDA72D0
//1.13c: D2Common.0x6FDCAED0
struct D2PathFoWallNode* __fastcall PATH_AStar_FindPointInVisitedCache(struct D2PathFoWallContext* pContext, struct D2PathPoint tPathPoint)
{
	const uint8_t nHash = (uint8_t)((gaIdaStar_PointCacheHashMaskX[tPathPoint.X & 0x7F] + gaIdaStar_PointCacheHashMaskY[tPathPoint.Y & 0x7F]) & 0x7F);
	for (struct D2PathFoWallNode* pNode = pContext->aVisitedCache[nHash];
		pNode != nullptr;
		pNode = pNode->pNextCachePoint)
	{
		if (tPathPoint.X == pNode->tPoint.X && tPathPoint.Y == pNode->tPoint.Y)
		{
			return pNode;
		}
	}
	return nullptr;
}

//1.10f: D2Common.0x6FDA7320
//1.13c: D2Common.0x6FDCAE20
void __fastcall PATH_AStar_MakeCandidate(struct D2PathFoWallContext* pContext, struct D2PathFoWallNode* pNode)
{
	const uint8_t nHash = (gaIdaStar_PointCacheHashMaskX[pNode->tPoint.X & 0x7F] + gaIdaStar_PointCacheHashMaskY[pNode->tPoint.Y & 0x7F]) & 0x7F;
	pNode->pNextCachePoint = pContext->aPendingCache[nHash];
	pContext->aPendingCache[nHash] = pNode;

	struct D2PathFoWallNode* pInsertionPoint = PATH_IdaStar_FindSortedByFScoreInsertionPoint(pContext, pNode->nFScore);
	if (pInsertionPoint)
	{
		pNode->pNextSortedByFScore = pInsertionPoint->pNextSortedByFScore;
		pInsertionPoint->pNextSortedByFScore = pNode;
	}
	else
	{
		pNode->pNextSortedByFScore = pContext->pSortedListByFScore;
		pContext->pSortedListByFScore = pNode;
	}
}

//1.10f: D2Common.0x6FDA7390
//1.13c: D2Common.0x6FDCAC50
//Should be __thiscall but we have to use __fastcall, hence nUnused
void __fastcall PATH_AStar_PropagateNewFScoreToChildren(struct D2PathFoWallContext* pContext, int nUnused, struct D2PathFoWallNode* pNewNode)
{
	D2_MAYBE_UNUSED(nUnused);

	pContext->aPointsStack[pContext->nStackCount++] = pNewNode;
	while (pContext->nStackCount != 0)
	{
		struct D2PathFoWallNode* pCurrentPoint = pContext->aPointsStack[--pContext->nStackCount];
		for (int i = 0; i < ARRAY_SIZE(pCurrentPoint->pChildren); i++)
		{
			struct D2PathFoWallNode* pChild = pCurrentPoint->pChildren[i];
			if (!pChild)
			{
				break;
			}
			const int16_t nDistanceBetweenPoints = PATH_AStar_HeuristicForNeighbor(pCurrentPoint->tPoint, pChild->tPoint);
			const int16_t nDistanceFromStart = nDistanceBetweenPoints + pCurrentPoint->nBestDistanceFromStart;
			if (nDistanceFromStart < pChild->nBestDistanceFromStart)
			{
				pChild->pBestParent = pCurrentPoint;
				pChild->nBestDistanceFromStart = nDistanceFromStart;
				pChild->nFScore = nDistanceFromStart + pChild->nHeuristicDistanceToTarget;
				pContext->aPointsStack[pContext->nStackCount++] = pChild;
			}
		}
	}
}

//1.10f: D2Common.0x6FDA7450
//1.13c: Inlined
struct D2PathFoWallNode* __fastcall PATH_AStar_GetNewNode(struct D2PathFoWallContext* pContext)
{
	if (pContext->nNodesCount == ARRAY_SIZE(pContext->aNodesStorage))
	{
		return nullptr;
	}
	struct D2PathFoWallNode* pNewNode = &pContext->aNodesStorage[pContext->nNodesCount++];
	memset(pNewNode, 0, sizeof(*pNewNode));
	return pNewNode;
}

// Helper function
static void PATH_AStar_AddChildToNode(struct D2PathFoWallNode* pNode, struct D2PathFoWallNode* pChild)
{
	for (int i = 0; i < ARRAY_SIZE(pNode->pChildren); i++)
	{
		struct D2PathFoWallNode** ppChild = &pNode->pChildren[i];
		if (*ppChild == nullptr)
		{
			*ppChild = pChild;
			break;
		}
	}
}

//1.10f: D2Common.0x6FDA7490
//1.13c: D2Common.0x6FDCAFB0
BOOL __fastcall PATH_AStar_EvaluateNeighbor(struct D2PathInfo* pPathInfo, struct D2PathFoWallContext* pContext, struct D2PathFoWallNode* pCurrentNode, struct D2PathPoint tNewPointCoord, struct D2PathPoint tTargetCoord)
{
	const int16_t nDistanceBetweenPoints = PATH_AStar_HeuristicForNeighbor(pCurrentNode->tPoint, tNewPointCoord);
	const int16_t nNewPointDistance = pCurrentNode->nBestDistanceFromStart + nDistanceBetweenPoints;
	{
		struct D2PathFoWallNode* pNewNode = PATH_AStar_GetNodeFromPendingCache(pContext, tNewPointCoord);
		if (pNewNode)
		{
			PATH_AStar_AddChildToNode(pCurrentNode, pNewNode);
			if (nNewPointDistance < pNewNode->nBestDistanceFromStart)
			{
				pNewNode->pBestParent = pCurrentNode;
				pNewNode->nBestDistanceFromStart = nNewPointDistance;
				pNewNode->nFScore = nNewPointDistance + pNewNode->nHeuristicDistanceToTarget;
			}
			return TRUE;
		}
	}

	{
		struct D2PathFoWallNode* pNewNode = PATH_AStar_FindPointInVisitedCache(pContext, tNewPointCoord);
		if (pNewNode)
		{
			PATH_AStar_AddChildToNode(pCurrentNode, pNewNode);
			if (nNewPointDistance < pNewNode->nBestDistanceFromStart)
			{
				pNewNode->pBestParent = pCurrentNode;
				pNewNode->nBestDistanceFromStart = nNewPointDistance;
				pNewNode->nFScore = nNewPointDistance + pNewNode->nHeuristicDistanceToTarget;
				PATH_AStar_PropagateNewFScoreToChildren(pContext,/*unused*/0, pNewNode);
			}
			return TRUE;
		}
	}

	{
		struct D2PathFoWallNode* pNewNode = PATH_AStar_GetNewNode(pContext);
		if (pNewNode)
		{
			PATH_AStar_AddChildToNode(pCurrentNode, pNewNode);

			pNewNode->tPoint = tNewPointCoord;
			pNewNode->nHeuristicDistanceToTarget = PATH_AStar_Heuristic(tNewPointCoord, tTargetCoord);

			pNewNode->pBestParent = pCurrentNode;
			pNewNode->nBestDistanceFromStart = nNewPointDistance;
			pNewNode->nFScore = pNewNode->nBestDistanceFromStart + pNewNode->nHeuristicDistanceToTarget;
			PATH_AStar_MakeCandidate(pContext, pNewNode);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

//1.10f: D2Common.0x6FDA78A0
//1.13c: D2Common.0x6FDCAB50
// Takes a node list, and builds the path using straight lines into the path info.
// Note that the node list stores the path from the end to the beginning (in reverse order).
// It also seems like it won't copy the last point of the path list (first of the array), not sure if it's intended or not.
signed int __fastcall PATH_AStar_FlushNodeToDynamicPath(struct D2PathFoWallNode* pNode, struct D2PathInfo* pPathInfo)
{
	if (!pNode)
	{
		return 0;
	}

	int nbPoints = 0;
	struct D2PathPoint tempPathPoints[78];
	// Assumes all points are conex, so we can't have a delta of -2, hence used for init
	int prevDeltaX = -2;
	int prevDeltaY = -2;
	while (pNode && pNode->pBestParent && nbPoints < D2DynamicPath_MAXPATHLEN)
	{
		struct D2PathFoWallNode* pNextPoint = pNode->pBestParent;
		const int deltaX = pNode->tPoint.X - pNextPoint->tPoint.X;
		const int deltaY = pNode->tPoint.Y - pNextPoint->tPoint.Y;
		// If the direction doesn't change, then ignore the point
		if (deltaX != prevDeltaX || deltaY != prevDeltaY)
		{
			++nbPoints;
			// Store path in reverse order
			tempPathPoints[D2DynamicPath_MAXPATHLEN - nbPoints] = pNode->tPoint;
			prevDeltaX = deltaX;
			prevDeltaY = deltaY;
		}
		pNode = pNextPoint;
	}

	// Note: IDAStar returns 0 if only 1 point is found. Optimization ?
	if (nbPoints < 1 || nbPoints >= D2DynamicPath_MAXPATHLEN)
	{
		return 0;
	}

	memcpy(pPathInfo->pDynamicPath->PathPoints, &tempPathPoints[D2DynamicPath_MAXPATHLEN - nbPoints], sizeof(struct D2PathPoint) * nbPoints);
	return nbPoints;
}
