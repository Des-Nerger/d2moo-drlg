#include "Path/Path.h"

#include "D2Collision.h"
#include "D2DataTbls.h"
#include "D2Dungeon.h"
#include "D2Inventory.h"
#include <D2BitManip.h>
#include "D2Monsters.h"
#include "Path/IDAStar.h"
#include "Units/UnitRoom.h"
#include "Units/Units.h"
#include <DataTbls/MonsterIds.h>
#include <D2Math.h>
#include "Path/IDAStar.h"
#include "Path/PathMisc.h"
#include "Path/PathUtil.h"
#include "Path/PathWF.h"
#include "Path/AStar.h"
#include "Path/Step.h"
#include <math.h>

static const enum D2C_CollisionPattern gaCollisionPatternsFromSize_6FDD1DE4[COLLISION_UNIT_SIZE_COUNT] =
{
	COLLISION_PATTERN_NONE,
	COLLISION_PATTERN_SMALL_UNIT_PRESENCE,
	COLLISION_PATTERN_SMALL_UNIT_PRESENCE,
	COLLISION_PATTERN_BIG_UNIT_PRESENCE
};
static const int gaOffsetsForSnappingToCardinalDirection[9][9] =
{
	{-1,  0,  0,  0, 0, 0, 0, 0, 1},
	{-1, -1,  0,  0, 0, 0, 0, 1, 1},
	{-1, -1, -1,  0, 0, 0, 1, 1, 1},
	{-1, -1, -1, -1, 0, 1, 1, 1, 1},
	{-1, -1, -1, -1, 0, 1, 1, 1, 1},
	{-1, -1, -1, -1, 0, 1, 1, 1, 1},
	{-1, -1, -1,  0, 0, 0, 1, 1, 1},
	{-1, -1,  0,  0, 0, 0, 0, 1, 1},
	{-1,  0,  0,  0, 0, 0, 0, 0, 1}
};

static const uint32_t dword_6FDD1F88[PATH_NB_DIRECTIONS] =
{
	0x00000000, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 
	0x00000001, 0x00000004, 0x00000004, 0x00000004, 0x00000004, 0x00000004, 0x00000004, 0x00000004, 
	0x00000004, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 
	0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 
	0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 
	0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 
	0xFFFFFFFC, 0xFFFFFFFC, 0xFFFFFFFC, 0xFFFFFFFC, 0xFFFFFFFC ,0xFFFFFFFC, 0xFFFFFFFC, 0xFFFFFFFC, 
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

static const int gaPathTypeFlags_6FDD2088[] =
{
/*[ 0]*/0x21900,
/*[ 1]*/0x1900,
/*[ 2]*/0,
/*[ 3]*/0,
/*[ 4]*/0x60000,
/*[ 5]*/0,
/*[ 6]*/0,
/*[ 7]*/0x21900,
/*[ 8]*/0x1E600,
/*[ 9]*/0x1E800,
/*[10]*/0x60000,
/*[11]*/0x1E604,
/*[12]*/0,
/*[13]*/0x100,
/*[14]*/0x60000,
/*[15]*/0x800,
/*[16]*/0,
/*[17]*/0,
};
static_assert(ARRAY_SIZE(gaPathTypeFlags_6FDD2088) == PATHTYPE_COUNT, "This array must have PATHTYPE_COUNT entries");
// 1.10f: D2Common.0x6FDD20D0
static const int32_t gaOffsetForPathType[] =
{
/*[ 0]*/0,
/*[ 1]*/0,
/*[ 2]*/0,
/*[ 3]*/0,
/*[ 4]*/0,
/*[ 5]*/2,
/*[ 6]*/-2,
/*[ 7]*/0,
/*[ 8]*/0,
/*[ 9]*/0,
/*[10]*/0,
/*[11]*/0,
/*[12]*/-4,
/*[13]*/0,
/*[14]*/0,
/*[15]*/0,
/*[16]*/0,
/*[17]*/0,
};
static_assert(ARRAY_SIZE(gaOffsetForPathType) == PATHTYPE_COUNT, "This array must have PATHTYPE_COUNT entries");

typedef int(__cdecl* PathFunctionType)(struct D2PathInfo*);

//D2Common.0x6FDD1F40
static const PathFunctionType scpfnPathFunction[] = {
/*[ 0]*/PATH_IdaStar_6FDA7970
/*[ 1]*/,PATH_AStar_ComputePath
/*[ 2]*/,PATH_Toward_6FDAA9F0
/*[ 3]*/,sub_6FDAB0B0
/*[ 4]*/,nullptr
/*[ 5]*/,PATH_Toward_6FDAA9F0
/*[ 6]*/,PATH_Toward_6FDAA9F0
/*[ 7]*/,PATH_Straight_Compute
/*[ 8]*/,PATH_Knockback_Server
/*[ 9]*/,PATH_Leap_6FDAB1E0
/*[10]*/,nullptr
/*[11]*/,PATH_Knockback_Client
/*[12]*/,PATH_BackupTurn_Compute
/*[13]*/,PATH_Toward_6FDAA9F0
/*[14]*/,nullptr
/*[15]*/,PATH_ComputePathOrSlideAlongObstacles
/*[16]*/,PATH_IdaStar_6FDA7970
/*[17]*/,nullptr
};
static_assert(ARRAY_SIZE(scpfnPathFunction) == PATHTYPE_COUNT, "This array must have PATHTYPE_COUNT entries");

// Helper function
void PATH_UpdateClientCoords(struct D2DynamicPath* pDynamicPath)
{
	// To game "pixels"
	int nX = pDynamicPath->tGameCoords.dwPrecisionX >> 11;
	int nY = pDynamicPath->tGameCoords.dwPrecisionY >> 11;

	DUNGEON_GameToClientCoords(&nX, &nY);

	pDynamicPath->dwClientCoordX = nX;
	pDynamicPath->dwClientCoordY = nY;
}

//D2Common.0x6FDA8220
void __cdecl sub_6FDA8220(struct D2DynamicPath* pDynamicPath)
{
	pDynamicPath->dwFlags &= (~PATH_UNKNOWN_FLAG_0x00001);

	if (pDynamicPath->pRoom)
	{
		for (int i = 0; i < pDynamicPath->dwPathPoints; ++i)
		{
			const struct D2DrlgCoords* pRoomCoords = &pDynamicPath->pRoom->tCoords;
			if (pDynamicPath->PathPoints[i].X < pRoomCoords->nSubtileX)
			{
				pDynamicPath->dwFlags |= PATH_UNKNOWN_FLAG_0x00001;
				break;
			}

			if (pDynamicPath->PathPoints[i].X >= pRoomCoords->nSubtileX + pRoomCoords->nSubtileWidth)
			{
				pDynamicPath->dwFlags |= PATH_UNKNOWN_FLAG_0x00001;
				break;
			}

			if (pDynamicPath->PathPoints[i].Y < pRoomCoords->nSubtileY)
			{
				pDynamicPath->dwFlags |= PATH_UNKNOWN_FLAG_0x00001;
				break;
			}

			if (pDynamicPath->PathPoints[i].Y >= pRoomCoords->nSubtileY + pRoomCoords->nSubtileHeight)
			{
				pDynamicPath->dwFlags |= PATH_UNKNOWN_FLAG_0x00001;
				break;
			}
		}
	}
}

//D2Common.0x6FDA82A0 (#10141)
void __cdecl PATH_GetClientCoordsVelocity(struct D2Unit* pUnit, int* pX, int* pY)
{
	if (pUnit && UNITS_IsInMovingMode(pUnit) && pUnit->pDynamicPath->dwPathPoints)
	{
		*pX = pUnit->pDynamicPath->tVelocityVector.nX;
		*pY = pUnit->pDynamicPath->tVelocityVector.nY;
		*pX >>= 11;
		*pY >>= 11;
		DUNGEON_GameToClientCoords(pX, pY);
	}
	else
	{
		*pX = 0;
		*pY = 0;
	}
}

//D2Common.0x6FDA8320 (#10222)
void __cdecl PATH_AddCollisionFootprintForUnit(struct D2Unit* pUnit)
{
	struct D2Coord pCoords = {};

	UNITS_GetCoords(pUnit, &pCoords);

	switch (pUnit->dwUnitType)
	{
	case UNIT_MONSTER:
		COLLISION_SetMaskWithPattern(UNITS_GetRoom(pUnit), pCoords.nX, pCoords.nY, pUnit->pDynamicPath->dwCollisionPattern, UNITS_GetCollisionMask(pUnit));
		break;
	case UNIT_OBJECT:
		COLLISION_SetMaskWithSizeXY(UNITS_GetRoom(pUnit), pCoords.nX, pCoords.nY, UNITS_GetUnitSizeX(pUnit), UNITS_GetUnitSizeY(pUnit), UNITS_GetCollisionMask(pUnit));
		break;
	default:
		COLLISION_SetMaskWithSize(UNITS_GetRoom(pUnit), pCoords.nX, pCoords.nY, UNITS_GetUnitSizeX(pUnit), UNITS_GetCollisionMask(pUnit));
		break;
	}
}

//D2Common.0x6FDA8450 (#10223)
BOOL __cdecl PATH_RemoveCollisionFootprintForUnit(struct D2Unit* pUnit, BOOL bForce)
{
	struct D2Coord pCoords = {};
	UNITS_GetCoords(pUnit, &pCoords);

	switch (pUnit->dwUnitType)
	{
	case UNIT_PLAYER:
		if (bForce || (pUnit->dwAnimMode != PLRMODE_DEAD && pUnit->dwAnimMode != PLRMODE_DEATH))
		{
			COLLISION_ResetMaskWithPattern(UNITS_GetRoom(pUnit), pCoords.nX, pCoords.nY, pUnit->pDynamicPath->dwCollisionPattern, UNITS_GetCollisionMask(pUnit));
			return TRUE;
		}
		break;
	case UNIT_MONSTER:
		if (bForce || (pUnit->dwAnimMode != MONMODE_DEAD && pUnit->dwAnimMode != MONMODE_DEATH))
		{
			COLLISION_ResetMaskWithPattern(UNITS_GetRoom(pUnit), pCoords.nX, pCoords.nY, pUnit->pDynamicPath->dwCollisionPattern, UNITS_GetCollisionMask(pUnit));
			return TRUE;
		}
		break;
	case UNIT_OBJECT:
		if (bForce || UNITS_HasCollision(pUnit))
		{
			COLLISION_ResetMaskWithSizeXY(UNITS_GetRoom(pUnit), pCoords.nX, pCoords.nY, UNITS_GetUnitSizeX(pUnit), UNITS_GetUnitSizeY(pUnit), UNITS_GetCollisionMask(pUnit));
			return TRUE;
		}
		break;
	default:
		COLLISION_ResetMaskWithSize(UNITS_GetRoom(pUnit), pCoords.nX, pCoords.nY, UNITS_GetUnitSizeX(pUnit), UNITS_GetCollisionMask(pUnit));
		return TRUE;
	}
	return FALSE;
}

//1.10f: Inlined
//1.13C: D2Common.0x6FD85780
BOOL __cdecl PATH_IsTargetDestinationAllowed(struct D2PathInfo* pPathInfo, struct D2Unit* pUnit)
{
	if (pUnit && pUnit->dwUnitType == UNIT_MONSTER) // Only monsters may have restricted access to town
	{
		if (MONSTERS_CanBeInTown(pUnit)) // If it can be in town, everything's fine
		{
			return TRUE;
		}

		// Otherwise check if the target is in town
		struct D2ActiveRoom* pTargetRoom = pPathInfo->pTargetRoom;
		if (!pTargetRoom)
		{
			// Try to find target room
			struct D2ActiveRoom* pRoomHalfway = COLLISION_GetRoomBySubTileCoordinates(
				pPathInfo->pStartRoom,
				pPathInfo->tStartCoord.X + (pPathInfo->tTargetCoord.X - pPathInfo->tStartCoord.X) / 2,
				pPathInfo->tStartCoord.Y + (pPathInfo->tTargetCoord.Y - pPathInfo->tStartCoord.Y) / 2);
			pTargetRoom = COLLISION_GetRoomBySubTileCoordinates(pRoomHalfway, pPathInfo->tTargetCoord.X, pPathInfo->tTargetCoord.Y);
		}
		if (pTargetRoom && DUNGEON_IsRoomInTown(pTargetRoom))
		{
			return FALSE;
		}
	}

	return TRUE;
}

// Author: Araksson
//1.10f: Inlined
//1.13C: D2Common.0x6FD85780
static int PATH_MissileToTarget(struct D2DynamicPath* pPath, struct D2Unit* pUnit)
{
	switch (pPath->dwPathType)
	{
	case PATHTYPE_MISSILE:
		if (!PATH_ComputePathClassicMissile(pPath, pUnit))
		{
			pPath->dwFlags &= ~PATH_UNKNOWN_FLAG_0x00020;
			return 0;
		}
		break;
	case PATHTYPE_CHARGEDBOLT:
		PATH_ComputePathChargedBolt_6FDAB4A0(pPath, &pUnit->pSeed);
		break;
	case PATHTYPE_BLESSEDHAMMER:
		PATH_ComputePathBlessedHammer_6FDAB3C0(pPath);
		break;
	default:
		FOG_DisplayWarning("Not a missile path!", __FILE__, __LINE__);
		pPath->dwFlags &= ~PATH_UNKNOWN_FLAG_0x00020;
		return 0;
	}

	pPath->dwFlags |= PATH_UNKNOWN_FLAG_0x00020;
	return pPath->dwPathPoints;
}

//1.10f: Inlined
//1.13C: D2Common.D2Common.0x6FD85470
uint8_t PATH_UpdateTargetUnit(struct D2PathInfo* pPathInfo)
{
	struct D2DynamicPath* pPath = pPathInfo->pDynamicPath;
	struct D2Unit* pPathTargetUnit = pPath->pTargetUnit;
	if (pPathTargetUnit)
	{
		pPath->tTargetCoord.X = UNITS_GetXPosition(pPathTargetUnit);
		pPath->tTargetCoord.Y = UNITS_GetYPosition(pPathTargetUnit);

		if (0 == memcmp(&pPath->tTargetCoord, &(struct D2PathPoint){0, 0}, sizeof(struct D2PathPoint)))
		{
			return 0;
		}
		switch (pPathTargetUnit->dwUnitType)
		{
		case UNIT_PLAYER:
		case UNIT_MONSTER:
			if (pPath->dwSpeed)
			{
				PATHUtil_AdvanceTowardsTarget_6FDAB890(pPath);
			}
			return 1;
		case UNIT_OBJECT:
			if (!UNITS_IsDoor(pPathTargetUnit))
			{
				return 2;
			}
			return PATH_AdvanceToDoor(pPathInfo);
		case UNIT_ITEM:
			return 2;
		default:
			return 1;
		}
	}
	return 1;
}

//1.00:  D2Common.0x10059110 (#10141)
//1.10f: D2Common.0x6FDA8600 (#10142)
//1.13c: D2Common.0x6FD86230 (#10334)
int __cdecl D2Common_10142(struct D2DynamicPath* pPath, struct D2Unit* pUnit, int bAllowInTown)
{


	// BROKEN



	if (!pPath)
	{
		return 0;
	}
	D2_ASSERT(pPath->pUnit == pUnit);

	if (pPath->dwFlags & PATH_MISSILE_MASK)
	{
		return PATH_MissileToTarget(pPath, pUnit);
	}
	pPath->nCollidedWithMask = 0;
	struct D2Unit* const pTargetUnit = pPath->pTargetUnit;
	if (pTargetUnit && (UNITS_GetXPosition(pTargetUnit) == 0 || UNITS_GetYPosition(pTargetUnit) == 0))
	{
		return 0;
	}

	struct D2PathInfo tPathInfo = {};
	struct D2PathPoint tStart = { pPath->tGameCoords.wPosX, pPath->tGameCoords.wPosY };
	tPathInfo.tStartCoord = tStart;
	if (0 != memcmp(&tPathInfo.tStartCoord, &(struct D2PathPoint){0, 0}, sizeof(struct D2PathPoint)))
	{
		tPathInfo.nUnitSize = pPath->dwUnitSize;
		tPathInfo.nCollisionPattern = pPath->dwCollisionPattern;
		tPathInfo.pDynamicPath = pPath;
		tPathInfo.nCollisionMask = pPath->nMoveTestCollisionMask;
		tPathInfo.nDistMax = pPath->nDistMax;
		tPathInfo.nMinimumFScoreToEvaluate = pPath->nIDAStarInitFScore;
		tPathInfo.field_14 = PATH_UpdateTargetUnit(&tPathInfo);

		if (0 != memcmp(&pPath->tTargetCoord, &(struct D2PathPoint){0, 0}, sizeof(struct D2PathPoint)))
		{
			tPathInfo.tTargetCoord = pPath->tTargetCoord;
			if (0 != memcmp(&tPathInfo.tStartCoord, &tPathInfo.tTargetCoord, sizeof(struct D2PathPoint))
				&& abs(tPathInfo.tStartCoord.X - tPathInfo.tTargetCoord.X) <= 100
				&& abs(tPathInfo.tStartCoord.Y - tPathInfo.tTargetCoord.Y) <= 100
				)
			{
				tPathInfo.pStartRoom = pPath->pRoom;
				tPathInfo.pTargetRoom = COLLISION_GetRoomBySubTileCoordinates(tPathInfo.pStartRoom, tPathInfo.tTargetCoord.X, tPathInfo.tTargetCoord.Y);

				if (tPathInfo.pStartRoom && 
#ifdef D2_VERSION_113C
					tPathInfo.pTargetRoom && // Optimization done in 1.13f
#endif
					(PATH_IsTargetDestinationAllowed(&tPathInfo, pUnit) || bAllowInTown))
				{
					tPathInfo.nPathType = pPath->dwPathType;

					BOOL bRemovedTargetUnitFootprint = FALSE;
					PATH_RemoveCollisionFootprintForUnit(pUnit, FALSE);
					if (pPath->pTargetUnit
						&& UNITS_GetUnitSizeX(pPath->pTargetUnit)
						&& (pPath->dwFlags & PATH_UNKNOWN_FLAG_0x00800) != 0)
					{
						bRemovedTargetUnitFootprint = PATH_RemoveCollisionFootprintForUnit(pPath->pTargetUnit, FALSE);
					}

					BOOL bUpdatePath = 1;
					if ((pPath->dwFlags & PATH_UNKNOWN_FLAG_0x01000) != 0
						&& COLLISION_CheckAnyCollisionWithPattern(
							tPathInfo.pStartRoom,
							tPathInfo.tTargetCoord.X,
							tPathInfo.tTargetCoord.Y,
							pPath->dwCollisionPattern,
							pPath->nMoveTestCollisionMask))
					{
						bUpdatePath = PATH_PreparePathTargetForPathUpdate(&tPathInfo);
					}

					pPath->dwCurrentPointIdx = 0;
					pPath->dwPathPoints = 0;
					pPath->tFinalTargetCoord = tPathInfo.tTargetCoord;
					if (bUpdatePath)
					{
						D2_ASSERT(scpfnPathFunction[tPathInfo.nPathType]);
						pPath->dwPathPoints = scpfnPathFunction[tPathInfo.nPathType](&tPathInfo);
					}
					D2_ASSERT(0 == memcmp(&tPathInfo.tStartCoord, &tStart, sizeof(struct D2PathPoint)));
					if (bRemovedTargetUnitFootprint)
					{
						PATH_AddCollisionFootprintForUnit(pPath->pTargetUnit);
					}
					PATH_AddCollisionFootprintForUnit(pUnit);
					if (!pPath->dwPathPoints)
					{
						pPath->dwFlags &= ~PATH_UNKNOWN_FLAG_0x00020;
						return 0;
					}

					PATH_ComputeVelocityAndDirectionVectorsToNextPoint(pPath, 1, 1);
					if (pPath->dwCurrentPointIdx < pPath->dwPathPoints)
					{
						sub_6FDA8220(pPath);
						pPath->tPrevTargetCoord = pPath->tTargetCoord;
						pPath->unk0x38 = 0;
						if ((pPath->dwFlags & PATH_UNKNOWN_FLAG_0x00010) == 0 && !pPath->pTargetUnit)
						{
							pPath->tTargetCoord = pPath->PathPoints[pPath->dwPathPoints - 1];
						}

						if (pPath->dwPathPoints)
						{
							pPath->dwFlags |= PATH_UNKNOWN_FLAG_0x00020;
						}
						else
						{
							pPath->dwFlags &= ~PATH_UNKNOWN_FLAG_0x00020;
						}
						return pPath->dwPathPoints;
					}
				}

			}
		}
	}
	pPath->dwCurrentPointIdx = 0;
	pPath->dwPathPoints = 0;
	pPath->dwFlags &= ~PATH_UNKNOWN_FLAG_0x00020;
	return 0;
}

//D2Common.0x6FDA8E30
int __cdecl PATH_ComputePathClassicMissile(struct D2DynamicPath* pDynamicPath, struct D2Unit* pUnit)
{
	int nXDistance = 0;
	int nYDistance = 0;
	int nOldX = 0;
	int nOldY = 0;
	char szText[256] = {};
	D2_MAYBE_UNUSED(szText);

	struct D2Coord pCoords = {};

	nOldX = pDynamicPath->tGameCoords.wPosX;
	nOldY = pDynamicPath->tGameCoords.wPosY;

	pDynamicPath->dwCurrentPointIdx = 0;

	if (pDynamicPath->pTargetUnit)
	{
		UNITS_GetCoords(pDynamicPath->pTargetUnit, &pCoords);

		pDynamicPath->tTargetCoord.X = pCoords.nX;
		pDynamicPath->tTargetCoord.Y = pCoords.nY;
	}

	nXDistance = nOldX - pDynamicPath->tTargetCoord.X;
	if (nXDistance < 0)
	{
		nXDistance = -nXDistance;
	}

	D2_ASSERTM(nXDistance < 100, FOG_csprintf(szText, "Missile Firing too far : %d", pUnit ? pUnit->dwClassId : -1));

	nYDistance = nOldY - pDynamicPath->tTargetCoord.Y;
	if (nYDistance < 0)
	{
		nYDistance = -nYDistance;
	}

	D2_ASSERTM(nYDistance < 100, FOG_csprintf(szText, "Missile Firing too far : %d", pUnit ? pUnit->dwClassId : -1));

	if (pDynamicPath->tTargetCoord.X && pDynamicPath->tTargetCoord.Y)
	{
		pDynamicPath->PathPoints[0].X = pDynamicPath->tTargetCoord.X;
		pDynamicPath->PathPoints[0].Y = pDynamicPath->tTargetCoord.Y;

		pDynamicPath->dwPathPoints = 1;
		pDynamicPath->unk0x38 = 0;
		PATH_ComputeVelocityAndDirectionVectorsToNextPoint(pDynamicPath, 1, 1);

		if (!(pDynamicPath->pRoom && DungeonTestRoomGame(pDynamicPath->pRoom, pDynamicPath->tTargetCoord.X, pDynamicPath->tTargetCoord.Y)))
		{
			pDynamicPath->dwFlags |= PATH_UNKNOWN_FLAG_0x00001;
		}

		return pDynamicPath->dwPathPoints;
	}

	return 0;
}

//D2Common.0x6FDA8FE0
void __cdecl PATH_FindValidTargetCoordsByMovingOrthogonally(struct D2PathInfo* pPathInfo)
{
	struct D2PathPoint tCoords = pPathInfo->tTargetCoord;

	const int nDeltaX = tCoords.X - pPathInfo->tStartCoord.X;
	const int nDeltaY = tCoords.Y - pPathInfo->tStartCoord.Y;
	const int nAbsDeltaX = abs(nDeltaX);
	const int nAbsDeltaY = abs(nDeltaY);
	if (nAbsDeltaX < 5 && nAbsDeltaY < 5 && (nDeltaX != 0 || nDeltaY != 0))
	{
		const int nRemappedX = nDeltaX + 4;
		const int nRemappedY = nDeltaY + 4;
		// A convoluted way to chose one the 4 cardinal directions.
		const int nOffsetX = gaOffsetsForSnappingToCardinalDirection[nRemappedY][nRemappedX];
		const int nOffsetY = gaOffsetsForSnappingToCardinalDirection[nRemappedX][nRemappedY];

		int nChebyshevDistance = MAX(nAbsDeltaX, nAbsDeltaY);
		while (nChebyshevDistance < 5)
		{
			tCoords.X += nOffsetX;
			tCoords.Y += nOffsetY;

			if (COLLISION_CheckAnyCollisionWithPattern(pPathInfo->pStartRoom, tCoords.X, tCoords.Y, pPathInfo->nCollisionPattern, pPathInfo->nCollisionMask))
			{
				break;
			}

			++nChebyshevDistance;
			pPathInfo->tTargetCoord.X = tCoords.X;
			pPathInfo->tTargetCoord.Y = tCoords.Y;
		}
	}
}

//D2Common.0x6FDA90C0
uint8_t __cdecl PATH_AdvanceToDoor(struct D2PathInfo* pPathInfo)
{
	struct D2Unit* pTargetUnit = pPathInfo->pDynamicPath->pTargetUnit;

	D2_ASSERT(UNITS_IsDoor(pTargetUnit));

	if (!UNITS_CheckIfObjectOrientationIs1(pTargetUnit))
	{
		if (pPathInfo->pDynamicPath->tGameCoords.wPosX >= UNITS_GetXPosition(pTargetUnit))
		{
			pPathInfo->pDynamicPath->tTargetCoord.X += 2;
		}
		else
		{
			pPathInfo->pDynamicPath->tTargetCoord.X -= 2;
		}
	}
	else
	{
		if (pPathInfo->pDynamicPath->tGameCoords.wPosY >= UNITS_GetYPosition(pTargetUnit))
		{
			pPathInfo->pDynamicPath->tTargetCoord.Y += 2;
		}
		else
		{
			pPathInfo->pDynamicPath->tTargetCoord.Y -= 2;
		}
	}

	return 2;
}

//D2Common.0x6FDA9190 (#10156)
void __cdecl PATH_FreeDynamicPath(void* pMemPool, struct D2DynamicPath* pDynamicPath)
{
	D2_FREE_POOL(pMemPool, pDynamicPath);
}

//D2Common.0x6FDA91B0 (#11282)
//Unused
int __cdecl PATH_GetCollisionPatternFromMonStats2Txt(int nMonsterId)
{
	struct D2MonStats2Txt* pMonStats2TxtRecord = NULL;

	pMonStats2TxtRecord = UNITS_GetMonStats2TxtRecordFromMonsterId(nMonsterId);
	if (pMonStats2TxtRecord && pMonStats2TxtRecord->nSizeX >= 0 && pMonStats2TxtRecord->nSizeX < COLLISION_UNIT_SIZE_COUNT)
	{
		enum D2C_CollisionPattern nCollisionPattern = gaCollisionPatternsFromSize_6FDD1DE4[pMonStats2TxtRecord->nSizeX];

		if (pMonStats2TxtRecord->dwFlags & gdwBitMasks[MONSTATS2FLAGINDEX_REVIVE] || pMonStats2TxtRecord->dwFlags & gdwBitMasks[MONSTATS2FLAGINDEX_SMALL])
		{
			if (!(pMonStats2TxtRecord->dwFlags & gdwBitMasks[MONSTATS2FLAGINDEX_ISATT]))
			{
				if (nCollisionPattern == COLLISION_PATTERN_SMALL_UNIT_PRESENCE)
				{
					nCollisionPattern = COLLISION_PATTERN_SMALL_PET_PRESENCE;
				}
				else if (nCollisionPattern == COLLISION_PATTERN_BIG_UNIT_PRESENCE)
				{
					nCollisionPattern = COLLISION_PATTERN_BIG_PET_PRESENCE;
				}
			}
		}

		return nCollisionPattern;
	}

	return COLLISION_PATTERN_SMALL_UNIT_PRESENCE;
}

//D2Common.0x6FDA9250 (#11281)
int __cdecl D2Common_11281_CollisionPatternFromSize(struct D2Unit* pUnit, int nSize)
{
	if (nSize < 0 && nSize >= COLLISION_UNIT_SIZE_COUNT)
	{
		return COLLISION_PATTERN_SMALL_UNIT_PRESENCE;
	}
	
	const enum D2C_CollisionPattern nCollisionPattern = gaCollisionPatternsFromSize_6FDD1DE4[nSize];
	if (pUnit && pUnit->dwUnitType == UNIT_MONSTER && MONSTERS_CanBeInTown(pUnit))
	{
		const struct D2MonStatsTxt* pMonStatsTxtRecord = DATATBLS_GetMonStatsTxtRecord(pUnit->dwClassId);
		if (!pMonStatsTxtRecord || !(pMonStatsTxtRecord->dwMonStatsFlags & gdwBitMasks[MONSTATSFLAGINDEX_INTERACT]))
		{
			if (nCollisionPattern == COLLISION_PATTERN_SMALL_UNIT_PRESENCE)
			{
				return COLLISION_PATTERN_SMALL_PET_PRESENCE;
			}
			else if (nCollisionPattern == COLLISION_PATTERN_BIG_UNIT_PRESENCE)
			{
				return COLLISION_PATTERN_BIG_PET_PRESENCE;
			}
		}
	}

	return nCollisionPattern;
}

//D2Common.0x6FDA92F0 (#10214)
//TODO: Find a name
void __cdecl D2Common_10214(struct D2Unit* pUnit)
{
	if (pUnit->pDynamicPath)
	{
		if (UNITS_GetRoom(pUnit))
		{
			PATH_RemoveCollisionFootprintForUnit(pUnit, 1);
			pUnit->pDynamicPath->dwCollisionPattern = D2Common_11281_CollisionPatternFromSize(pUnit, pUnit->pDynamicPath->dwUnitSize);
			PATH_AddCollisionFootprintForUnit(pUnit);
		}
		else
		{
			pUnit->pDynamicPath->dwCollisionPattern = D2Common_11281_CollisionPatternFromSize(pUnit, pUnit->pDynamicPath->dwUnitSize);
		}
	}
}

//D2Common.0x6FDA9480 (#10152)
void __cdecl PATH_AllocDynamicPath(void* pMemPool, struct D2ActiveRoom* pRoom, int nX, int nY, struct D2Unit* pUnit, BOOL bSetFlag)
{
	struct D2DynamicPath* pDynamicPath = D2_CALLOC_STRC_POOL(pMemPool, struct D2DynamicPath);

	pUnit->pDynamicPath = pDynamicPath;

	pDynamicPath->pUnit = pUnit;
	pDynamicPath->dwUnitSize = UNITS_GetUnitSizeX(pUnit);

	pDynamicPath->dwCollisionPattern = D2Common_11281_CollisionPatternFromSize(pUnit, pDynamicPath->dwUnitSize);

	pDynamicPath->dwVelocity = 2048;
	pDynamicPath->pRoom = pRoom;
	pDynamicPath->nStepNum = 0;
	pDynamicPath->tGameCoords.dwPrecisionX = PATH_ToFP16Center(nX);
	pDynamicPath->tGameCoords.dwPrecisionY = PATH_ToFP16Center(nY);

	pDynamicPath->nSavedStepsCount = 1;
	pDynamicPath->SavedSteps[0].X = nX;
	pDynamicPath->SavedSteps[0].Y = nY;

	if (pUnit->dwUnitType == UNIT_PLAYER)
	{
		pDynamicPath->nFootprintCollisionMask = COLLIDE_PLAYER;
		pDynamicPath->nMoveTestCollisionMask = COLLIDE_MASK_PLAYER_PATH;
		PATH_SetType(pDynamicPath, PATHTYPE_STRAIGHT);
		pDynamicPath->nDistMax = 73;
		pDynamicPath->nIDAStarInitFScore = 70;
	}
	else if (pUnit->dwUnitType == UNIT_MONSTER)
	{
		pDynamicPath->nFootprintCollisionMask = COLLIDE_MONSTER;
		PATH_SetType(pDynamicPath, PATHTYPE_TOWARD);

		int nClassId = pUnit->dwClassId;

		struct D2MonStatsTxt* pMonStatsTxtRecord = DATATBLS_GetMonStatsTxtRecord(nClassId);
		if (pMonStatsTxtRecord)
		{
			nClassId = pMonStatsTxtRecord->nBaseId;
		}

		if (nClassId == MONSTER_WRAITH1)
		{
			pDynamicPath->dwCollisionPattern = COLLISION_PATTERN_SMALL_NO_PRESENCE;
			pDynamicPath->nMoveTestCollisionMask = COLLIDE_MISSILE_BARRIER | COLLIDE_DOOR;
			pDynamicPath->nDistMax = 14;
		}
		else
		{
			if (pMonStatsTxtRecord && pMonStatsTxtRecord->dwMonStatsFlags & gdwBitMasks[MONSTATSFLAGINDEX_FLYING])
			{
				pDynamicPath->nDistMax = 14;
				pDynamicPath->nMoveTestCollisionMask = COLLIDE_MASK_FLYING_UNIT;
			}
			else
			{
				pDynamicPath->nDistMax = 14;
				pDynamicPath->nMoveTestCollisionMask = 
					(pMonStatsTxtRecord && (pMonStatsTxtRecord->dwMonStatsFlags & gdwBitMasks[MONSTATSFLAGINDEX_OPENDOORS]) != 0) 
					? COLLIDE_MASK_MONSTER_THAT_CAN_OPEN_DOORS
					: COLLIDE_MASK_MONSTER_PATH;
			}
		}
	}
	else if (pUnit->dwUnitType == UNIT_MISSILE)
	{
		pDynamicPath->nFootprintCollisionMask = COLLIDE_NONE;
		pDynamicPath->nMoveTestCollisionMask = COLLIDE_NONE;
		PATH_SetType(pDynamicPath, PATHTYPE_MISSILE);
	}

	if (pRoom)
	{
		PATH_AddCollisionFootprintForUnit(pUnit);
		UNITROOM_AddUnitToRoom(pUnit, pDynamicPath->pRoom);
	}
	
	PATH_UpdateClientCoords(pDynamicPath);
	
	if (bSetFlag)
	{
		pDynamicPath->dwFlags |= PATH_UNKNOWN_FLAG_0x00010;
	}
}

//D2Common.0x6FDA9720
//TODO: Find a name
void __cdecl sub_6FDA9720(struct D2DynamicPath* pDynamicPath, uint8_t nDirection)
{
	enum D2C_UnitTypes nUnitType;

	if (pDynamicPath->pUnit)
	{
		nUnitType = (enum D2C_UnitTypes)(pDynamicPath->pUnit->dwUnitType);
	}
	else
	{
		nUnitType = UNIT_TYPES_COUNT;
	}

	const uint8_t nNormalizedDirection = PATH_NormalizeDirection(nDirection);
	switch (nUnitType)
	{
	case UNIT_OBJECT:
	case UNIT_ITEM:
		pDynamicPath->nDirection = nNormalizedDirection;
		break;
	case UNIT_MISSILE:
		if (!(pDynamicPath->dwFlags & PATH_UNKNOWN_FLAG_0x00040))
		{
			pDynamicPath->nDirection = nNormalizedDirection;
		}
		break;
	default:
		if (nNormalizedDirection != pDynamicPath->nNewDirection)
		{
			pDynamicPath->nNewDirection = nNormalizedDirection;
			pDynamicPath->nDiffDirection = dword_6FDD1F88[PATH_NormalizeDirection(nNormalizedDirection - pDynamicPath->nDirection)];
		}
		break;
	}
}

//D2Common.0x6FDA9770 (#10193)
//TODO: Check name
void __cdecl D2COMMON_10193_PATH_AdjustDirection(struct D2DynamicPath* pDynamicPath)
{
	if ((pDynamicPath->nDirection != pDynamicPath->nNewDirection) && !(pDynamicPath->dwFlags & PATH_UNKNOWN_FLAG_0x00040))
	{
		pDynamicPath->nDirection = PATH_NormalizeDirection(pDynamicPath->nDirection + pDynamicPath->nDiffDirection);

		const uint8_t dirDiff = PATH_NormalizeDirection(pDynamicPath->nDirection - pDynamicPath->nNewDirection);
		if (dirDiff > 31)
		{
			if (pDynamicPath->nDiffDirection > 63)
			{
				pDynamicPath->nDirection = pDynamicPath->nNewDirection;
			}
		}
		else if (dirDiff < 31)
		{
			if (pDynamicPath->nDiffDirection < 63)
			{
				pDynamicPath->nDirection = pDynamicPath->nNewDirection;
			}
		}
	}
}

//D2Common.0x6FDA97C0 (#10216)
//TODO: Find a name
void __cdecl D2Common_10216(struct D2DynamicPath* pDynamicPath, int nX, int nY, int a4)
{
	if (pDynamicPath)
	{
		const uint8_t nNormalizedDirection = PATH_NormalizeDirection(PATH_ComputeDirectionFromPreciseCoords_6FDAC760(pDynamicPath->tGameCoords.dwPrecisionX, pDynamicPath->tGameCoords.dwPrecisionY, PATH_ToFP16Center(nX), PATH_ToFP16Center(nY)));
		if (a4)
		{
			pDynamicPath->nNewDirection = nNormalizedDirection;
			pDynamicPath->nDirection = nNormalizedDirection;
		}
		else
		{
			sub_6FDA9720(pDynamicPath, nNormalizedDirection);
		}
	}
}

//D2Common.0x6FDA9850 (#10228)
//TODO: Find a name
void __cdecl D2Common_10228(struct D2Unit* pUnit)
{
	if (pUnit->pDynamicPath)
	{
		PATH_RemoveCollisionFootprintForUnit(pUnit, 1);
	}
}

//D2Common.0x6FDA9870 (#10143)
void __cdecl PATH_SetUnitDeadCollision(struct D2Unit* pUnit, BOOL bForGameLogic)
{
	D2_ASSERT(pUnit->pDynamicPath != nullptr);
	if (bForGameLogic || pUnit->dwUnitType != UNIT_MONSTER)
	{
		PATH_RemoveCollisionFootprintForUnit(pUnit, TRUE);
		COLLISION_SetMaskWithSizeXY(pUnit->pDynamicPath->pRoom, pUnit->pDynamicPath->tGameCoords.wPosX, pUnit->pDynamicPath->tGameCoords.wPosY, 3, 3, COLLIDE_CORPSE);
		PATH_RecacheRoomIfNeeded(pUnit->pDynamicPath);
	}
	else // Called from Client, related to corpse being displayed
	{
		PATH_RemoveCollisionFootprintForUnit(pUnit, TRUE);
		pUnit->pDynamicPath->dwCollisionPattern = COLLISION_PATTERN_SMALL_NO_PRESENCE;
		PATH_SetFootprintCollisionMask(pUnit->pDynamicPath, COLLIDE_CORPSE);
		PATH_AddCollisionFootprintForUnit(pUnit);
		PATH_RecacheRoomIfNeeded(pUnit->pDynamicPath);
	}
}

//D2Common.0x6FDA98F0 (#10144)
void __cdecl PATH_SetUnitAliveCollision(struct D2Unit* pUnit, BOOL bForGameLogic)
{
	if (bForGameLogic)
	{
		return;
	}
	//else: Called from Client to remove corpse collision

	D2_ASSERT(pUnit && pUnit->dwUnitType == UNIT_MONSTER);
	if (pUnit->pDynamicPath && pUnit->pDynamicPath->nFootprintCollisionMask == COLLIDE_CORPSE)
	{
		int nCollisionPattern = D2Common_11281_CollisionPatternFromSize(pUnit, UNITS_GetUnitSizeX(pUnit));

		if (pUnit->dwUnitType == UNIT_MONSTER)
		{
			const int nClassId = MONSTERS_GetBaseIdFromMonsterId(pUnit->dwClassId);

			if (nClassId == MONSTER_WRAITH1 || nClassId == MONSTER_BIRD1 || nClassId == MONSTER_BIRD2 || nClassId == MONSTER_PARROT)
			{
				nCollisionPattern = COLLISION_PATTERN_SMALL_NO_PRESENCE;
			}
		}

		if (UNITS_GetRoom(pUnit))
		{
			PATH_RemoveCollisionFootprintForUnit(pUnit, 1);
			pUnit->pDynamicPath->dwCollisionPattern = nCollisionPattern;
			PATH_SetFootprintCollisionMask(pUnit->pDynamicPath, COLLIDE_MONSTER);
			PATH_AddCollisionFootprintForUnit(pUnit);
		}
		else
		{
			pUnit->pDynamicPath->dwCollisionPattern = nCollisionPattern;
			PATH_SetFootprintCollisionMask(pUnit->pDynamicPath, COLLIDE_MONSTER);
		}
	}
}

//1.10f: D2Common.0x6FDA9A70 (#10146)
//1.13c: D2Common.0x6FD84D40 (#10488)
void __cdecl PATH_SetVelocity(struct D2DynamicPath* pDynamicPath, int nVelocity, const char* szFile, int nLine)
{
	if (pDynamicPath)
	{
		if (nVelocity != pDynamicPath->dwVelocity)
		{
			pDynamicPath->unk0x38 = 15;
		}

		pDynamicPath->dwVelocity = nVelocity;
		pDynamicPath->dwMaxVelocity = nVelocity;
	}
	else
	{
		FOG_Trace("PathSetVelocity passed NULL hPath from FILE:%s  LINE:%d", szFile, nLine);
	}
}

//D2Common.0x6FDA9AB0 (#10147)
int __cdecl PATH_GetVelocity(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->dwVelocity;
}

//D2Common.0x6FDA9AC0 (#10148)
void __cdecl PATH_SetMaxVelocity(struct D2DynamicPath* pDynamicPath, int nMaxVelocity)
{
	pDynamicPath->dwMaxVelocity = nMaxVelocity;
}

//D2Common.0x6FDA9AE0 (#10149)
int __cdecl PATH_GetMaxVelocity(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->dwMaxVelocity;
}

//D2Common.0x6FDA9AF0 (#10150)
void __cdecl PATH_SetAcceleration(struct D2DynamicPath* pDynamicPath, int nAcceleration)
{
	pDynamicPath->dwAcceleration = nAcceleration;
}

//D2Common.0x6FDA9B10 (#10151)
int __cdecl PATH_GetAcceleration(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->dwAcceleration;
}

//D2Common.0x6FDA9B20 (#10153)
//TODO: Find a name
void __cdecl D2Common_10153(struct D2DynamicPath* pDynamicPath)
{
	pDynamicPath->dwPathPoints = 0;
	pDynamicPath->dwFlags &= (~PATH_UNKNOWN_FLAG_0x00020);
}

//D2Common.0x6FDA9B40 (#10208)
//TODO: Check name
void __cdecl D2COMMON_10208_PathSetPathingFlag(struct D2DynamicPath* pDynamicPath, BOOL bSet)
{
	if (bSet)
	{
		pDynamicPath->dwFlags |= PATH_UNKNOWN_FLAG_0x00020;
	}
	else
	{
		pDynamicPath->dwFlags &= (~PATH_UNKNOWN_FLAG_0x00020);
	}
}

//D2Common.0x6FDA9B70 (#10209)
//TODO: Check name
BOOL __cdecl D2COMMON_10209_PathCheckPathingFlag(struct D2DynamicPath* pDynamicPath)
{
	return (pDynamicPath->dwFlags & PATH_UNKNOWN_FLAG_0x00020);
}

//D2Common.0x6FDA9B80 (#10154)
int __cdecl PATH_GetNumberOfPathPoints(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->dwPathPoints;
}

//D2Common.0x6FDA9B90 (#11291)
void __cdecl PATH_SetNumberOfPathPoints(struct D2DynamicPath* pDynamicPath, int a2)
{
	if (a2 < D2DynamicPath_MAXPATHLEN)
	{
		pDynamicPath->dwPathPoints = a2;
	}
	else
	{
		pDynamicPath->dwPathPoints = D2DynamicPath_MAXPATHLEN - 1;
	}
}

//D2Common.0x6FDA9BC0 (#10155)
//TODO: Find a name
int __cdecl D2Common_10155(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->dwCurrentPointIdx;
}

//D2Common.0x6FDA9BD0 (#10157)
int __cdecl PATH_GetPathPoints(struct D2DynamicPath* pDynamicPath, struct D2PathPoint** ppPathPoints)
{
	*ppPathPoints = pDynamicPath->PathPoints;
	return pDynamicPath->dwPathPoints;
}

//D2Common.0x6FDA9BF0 (#10158)
uint8_t __cdecl PATH_GetDirection(struct D2DynamicPath* pDynamicPath)
{
	if (pDynamicPath)
	{
		return pDynamicPath->nDirection;
	}

	return 0;
}

//D2Common.0x6FDA9C10 (#10159)
uint8_t __cdecl PATH_GetNewDirection(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->nNewDirection;
}

//D2Common.0x6FDA9C20 (#10160)
//TODO: Check name
void __cdecl D2COMMON_10160_PathUpdateDirection(struct D2DynamicPath* pDynamicPath, uint8_t nDirection)
{
	D2_ASSERT(nDirection < PATH_NB_DIRECTIONS);

	sub_6FDA9720(pDynamicPath, nDirection);
}

//D2Common.0x6FDA9C90 (#10161)
void __cdecl PATH_SetDirection(struct D2DynamicPath* pDynamicPath, uint8_t nDirection)
{
	if (pDynamicPath)
	{
		pDynamicPath->nDirection = PATH_NormalizeDirection(nDirection);
		pDynamicPath->nNewDirection = PATH_NormalizeDirection(nDirection);
	}
}

//D2Common.0x6FDA9CB0 (#10162)
int __cdecl PATH_GetXPosition(struct D2DynamicPath* pDynamicPath)
{
	D2_ASSERT(pDynamicPath);

	return pDynamicPath->tGameCoords.wPosX;
}

//D2Common.0x6FDA9CF0 (#10163)
int __cdecl PATH_GetYPosition(struct D2DynamicPath* pDynamicPath)
{
	D2_ASSERT(pDynamicPath);

	return pDynamicPath->tGameCoords.wPosY;
}

//D2Common.0x6FDA9D30 (#10194)
int __cdecl PATH_GetPrecisionX(struct D2DynamicPath* pDynamicPath)
{
	D2_ASSERT(pDynamicPath);

	return pDynamicPath->tGameCoords.dwPrecisionX;
}

//D2Common.0x6FDA9D60 (#10195)
int __cdecl PATH_GetPrecisionY(struct D2DynamicPath* pDynamicPath)
{
	D2_ASSERT(pDynamicPath);

	return pDynamicPath->tGameCoords.dwPrecisionY;
}

//D2Common.0x6FDA9D90 (#10196)
void __cdecl PATH_SetPrecisionX(struct D2DynamicPath* pDynamicPath, int nPrecisionX)
{
	pDynamicPath->tGameCoords.dwPrecisionX = nPrecisionX;
}

//D2Common.0x6FDA9DA0 (#10197)
void __cdecl PATH_SetPrecisionY(struct D2DynamicPath* pDynamicPath, int nPrecisionY)
{
	pDynamicPath->tGameCoords.dwPrecisionY = nPrecisionY;
}

//D2Common.0x6FDA9DB0 (#10164)
int __cdecl PATH_GetClientCoordX(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->dwClientCoordX;
}

//D2Common.0x6FDC3CE0 (#10165)
int __cdecl PATH_GetClientCoordY(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->dwClientCoordY;
}

//D2Common.0x6FDA9DC0
void __cdecl PATH_SetClientCoordX(struct D2DynamicPath* pDynamicPath, int nTargetX)
{
	pDynamicPath->dwClientCoordX = nTargetX;
}

//D2Common.0x6FDA9DD0
void __cdecl PATH_SetClientCoordY(struct D2DynamicPath* pDynamicPath, int nTargetY)
{
	pDynamicPath->dwClientCoordY = nTargetY;
}

//D2Common.0x6FDA9DE0 (#10175)
//TODO: Check name
int __cdecl D2COMMON_10175_PathGetFirstPointX(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->tTargetCoord.X;
}

//D2Common.0x6FDA9DF0 (#10176)
//TODO: Check name
int __cdecl D2COMMON_10176_PathGetFirstPointY(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->tTargetCoord.Y;
}

//D2Common.0x6FDA9E00 (#10224)
//TODO: Find a name
int __cdecl D2Common_10224(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->tFinalTargetCoord.X;
}

//D2Common.0x6FDA9E10 (#10225)
//TODO: Find a name
int __cdecl D2Common_10225(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->tFinalTargetCoord.Y;
}

//D2Common.0x6FDA9E20 (#10177)
int __cdecl D2COMMON_10177_PATH_GetLastPointX(struct D2DynamicPath* pDynamicPath)
{
	if (pDynamicPath->dwPathPoints > 0)
	{
		return pDynamicPath->PathPoints[pDynamicPath->dwPathPoints-1].X;
	}

	return 0;
}

//D2Common.0x6FDA9E40 (#10178)
int __cdecl D2COMMON_10178_PATH_GetLastPointY(struct D2DynamicPath* pDynamicPath)
{
	if (pDynamicPath->dwPathPoints > 0)
	{
		return pDynamicPath->PathPoints[pDynamicPath->dwPathPoints-1].Y;
	}

	return 0;
}

//D2Common.0x6FDB9C10 (#10166)
struct D2ActiveRoom* __cdecl PATH_GetRoom(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->pRoom;
}

//D2Common.0x6FDA9E60 (#10167)
void __cdecl PATH_SetRoom(struct D2DynamicPath* pDynamicPath, struct D2ActiveRoom* pRoom)
{
	pDynamicPath->pRoom = pRoom;
}

//D2Common.0x6FDA9E70 (#10168)
struct D2ActiveRoom* __cdecl PATH_GetNextRoom(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->pPreviousRoom;
}

//D2Common.0x6FDA9E80 (#10169)
void __cdecl PATH_ClearNextRoom(struct D2DynamicPath* pDynamicPath)
{
	pDynamicPath->pPreviousRoom = NULL;
}

//D2Common.0x6FDA9E90 (#10170)
//TODO: Check name
void __cdecl D2COMMON_10170_PathSetTargetPos(struct D2DynamicPath* pDynamicPath, int nX, int nY)
{
	if (pDynamicPath)
	{
		pDynamicPath->tTargetCoord.X = nX;
		pDynamicPath->tTargetCoord.Y = nY;
		pDynamicPath->pTargetUnit = NULL;
	}
}

//D2Common.0x6FDA9EC0 (#10172)
//TODO: Find a name
BOOL __cdecl PATH_IsCurrentRoomInvalid(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->dwFlags & PATH_CURRENT_ROOM_INVALID;
}

//D2Common.0x6FDA9ED0 (#10173)
//TODO: Find a name
void __cdecl PATH_SetCurrentRoomInvalid(struct D2DynamicPath* pDynamicPath, BOOL bSet)
{
	if (bSet)
	{
		pDynamicPath->dwFlags |= PATH_CURRENT_ROOM_INVALID;
	}
	else
	{
		pDynamicPath->dwFlags &= (~PATH_CURRENT_ROOM_INVALID);
	}
}

//D2Common.0x6FDA9F00 (#10145)
void __cdecl PATH_SetUnusedFlag_0x00004(struct D2DynamicPath* pDynamicPath, BOOL bSet)
{
	if (bSet)
	{
		pDynamicPath->dwFlags |= PATH_UNUSED_FLAG_0x00004;
	}
	else
	{
		pDynamicPath->dwFlags &= (~PATH_UNUSED_FLAG_0x00004);
	}
}

//D2Common.0x6FDA9F30 (#10174)
BOOL __cdecl PATH_GetUnusedFlag_0x00004(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->dwFlags & PATH_UNUSED_FLAG_0x00004;
}

//D2Common.0x6FDA9F40 (#10179)
void __cdecl PATH_SetTargetUnit(struct D2DynamicPath* pDynamicPath, struct D2Unit* pUnit)
{
	pDynamicPath->pTargetUnit = pUnit;

	if (pUnit)
	{
		pDynamicPath->dwTargetType = pUnit->dwUnitType;
		pDynamicPath->dwTargetId = pUnit->dwUnitId;
	}
}

//D2Common.0x6FDA9F60 (#10171)
void __cdecl PATH_GetTargetTypeAndGUID(struct D2DynamicPath* pDynamicPath, int* pTargetType, D2UnitGUID* pTargetGUID)
{
	D2_ASSERT(pDynamicPath->pTargetUnit);

	*pTargetType = pDynamicPath->dwTargetType;
	*pTargetGUID = pDynamicPath->dwTargetId;
}

//D2Common.0x6FDA9FA0 (#10180)
struct D2Unit* __cdecl PATH_GetTargetUnit(struct D2DynamicPath* pDynamicPath)
{
	if (pDynamicPath)
	{
		return pDynamicPath->pTargetUnit;
	}

	return NULL;
}

//D2Common.0x6FDA9FC0 (#10181)
int __cdecl PATH_GetFootprintCollisionMask(struct D2DynamicPath* pDynamicPath)
{
	if (pDynamicPath)
	{
		return pDynamicPath->nFootprintCollisionMask;
	}
	
	// Note: this returns 0xFFFF not 0xFFFFFFFF because D2C_CollisionFlags is 16bits.
	return COLLIDE_ALL_MASK;
}

//D2Common.0x6FDA9FE0 (#10182)
void __cdecl PATH_SetFootprintCollisionMask(struct D2DynamicPath* pDynamicPath, int nCollisionMask)
{
	if (pDynamicPath->pRoom)
	{
		if (pDynamicPath->pUnit && pDynamicPath->pUnit->dwUnitType == UNIT_MISSILE)
		{
			COLLISION_ResetMaskWithSize(pDynamicPath->pRoom, pDynamicPath->tGameCoords.wPosX, pDynamicPath->tGameCoords.wPosY, pDynamicPath->dwUnitSize, pDynamicPath->nFootprintCollisionMask);
		}
		else
		{
			COLLISION_ResetMaskWithPattern(pDynamicPath->pRoom, pDynamicPath->tGameCoords.wPosX, pDynamicPath->tGameCoords.wPosY, pDynamicPath->dwCollisionPattern, pDynamicPath->nFootprintCollisionMask);
		}
	}

	pDynamicPath->nFootprintCollisionMask = nCollisionMask;

	if (pDynamicPath->pRoom)
	{
		if (pDynamicPath->pUnit && pDynamicPath->pUnit->dwUnitType == UNIT_MISSILE)
		{
			COLLISION_SetMaskWithSize(pDynamicPath->pRoom, pDynamicPath->tGameCoords.wPosX, pDynamicPath->tGameCoords.wPosY, pDynamicPath->dwUnitSize, nCollisionMask);
		}
		else
		{
			COLLISION_SetMaskWithPattern(pDynamicPath->pRoom, pDynamicPath->tGameCoords.wPosX, pDynamicPath->tGameCoords.wPosY, pDynamicPath->dwCollisionPattern, nCollisionMask);
		}
	}
}

//D2Common.0x6FDAA0C0 (#10183)
int __cdecl PATH_GetMoveTestCollisionMask(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->nMoveTestCollisionMask;
}

//D2Common.0x6FDAA0D0 (#10184)
void __cdecl PATH_SetMoveTestCollisionMask(struct D2DynamicPath* pDynamicPath, int nCollisionMask)
{
	pDynamicPath->nMoveTestCollisionMask = nCollisionMask;
}

//D2Common.0x6FDAA0E0 (#10185)
void __cdecl PATH_SetType(struct D2DynamicPath* pDynamicPath, int nPathType)
{

	D2_ASSERT(!(pDynamicPath->pUnit && pDynamicPath->pUnit->dwUnitType == UNIT_PLAYER && nPathType == PATHTYPE_TOWARD));

	int nFlag = gaPathTypeFlags_6FDD2088[nPathType];
	if ((nFlag & PATH_UNKNOWN_FLAG_0x02000) && !(pDynamicPath->dwFlags & PATH_UNKNOWN_FLAG_0x04000))
	{
		pDynamicPath->dwPrevPathType = pDynamicPath->dwPathType;
	}

	if ((nFlag & PATH_WITH_PREVIOUS_VELOCITY) && !(pDynamicPath->dwFlags & PATH_UNKNOWN_FLAG_0x10000))
	{
		pDynamicPath->nPreviousVelocity = pDynamicPath->dwVelocity;
	}

	pDynamicPath->dwPathType = nPathType;
	pDynamicPath->dwFlags = nFlag | pDynamicPath->dwFlags & 0xFFF800FF;
	pDynamicPath->nDirOffset = gaOffsetForPathType[nPathType];

	D2_ASSERT(pDynamicPath->dwPrevPathType != PATHTYPE_KNOCKBACK_CLIENT);
	D2_ASSERT(pDynamicPath->dwPrevPathType != PATHTYPE_KNOCKBACK_SERVER);
	D2_ASSERT((nPathType != PATHTYPE_MISSILE) || (pDynamicPath->nDistMax < D2DynamicPath_MAXPATHLEN));
}

//D2Common.0x6FDAA1E0 (#10186)
void __cdecl PATH_ResetToPreviousType(struct D2DynamicPath* pDynamicPath)
{
	D2_ASSERT(pDynamicPath->pUnit);

	if (pDynamicPath->dwFlags & PATH_WITH_PREVIOUS_VELOCITY)
	{
		pDynamicPath->dwVelocity = pDynamicPath->nPreviousVelocity;
	}

	if (pDynamicPath->pUnit->dwUnitType != UNIT_PLAYER)
	{
		if (pDynamicPath->dwFlags & PATH_UNKNOWN_FLAG_0x02000)
		{
			PATH_SetType(pDynamicPath, pDynamicPath->dwPrevPathType);
		}
	}
	else
	{
		PATH_SetType(pDynamicPath, PATHTYPE_STRAIGHT);
	}
}

//D2Common.0x6FDAA240 (#10187)
int __cdecl PATH_GetType(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->dwPathType;
}

//D2Common.0x6FDAA250 (#10190)
// TODO: rename
void __cdecl D2COMMON_10190_PATH_SetDistance(struct D2DynamicPath* pDynamicPath, uint8_t nDistance)
{
	pDynamicPath->nDist = nDistance;
}

//D2Common.0x6FDAA270 (#10191)
// TODO: rename
uint8_t __cdecl D2COMMON_10191_PATH_GetDistance(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->nDist;
}

//D2Common.0x6FDAA280 (#10188)
void __cdecl PATH_SetNewDistance(struct D2DynamicPath* pDynamicPath, uint8_t nNewDistance)
{
	if (pDynamicPath)
	{
		if (nNewDistance >= (D2DynamicPath_MAXPATHLEN - 1))
		{
			nNewDistance = (D2DynamicPath_MAXPATHLEN - 1);
		}

		pDynamicPath->nDistMax = nNewDistance;
		pDynamicPath->nDist = nNewDistance;
	}
}

//D2Common.0x6FDAA2B0 (#10189)
uint8_t __cdecl PATH_GetMaxDistance(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->nDistMax;
}

//D2Common.0x6FDAA2C0 (#10201)
//TODO: Find a name
uint16_t __cdecl D2Common_10201(struct D2DynamicPath* pDynamicPath)
{
	if (!pDynamicPath->dwVelocity)
	{
		pDynamicPath->nCollidedWithMask = COLLISION_CheckMaskWithSize(pDynamicPath->pRoom, pDynamicPath->tGameCoords.wPosX, pDynamicPath->tGameCoords.wPosY, pDynamicPath->dwUnitSize, (uint16_t)~COLLIDE_CORPSE);
	}

	return pDynamicPath->nCollidedWithMask;
}

//D2Common.0x6FDAA300 (#10202)
//TODO: Find a name
uint16_t __cdecl D2Common_10202(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->nCollidedWithMask;
}

//D2Common.0x6FDAA310 (#10192)
void __cdecl PATH_SetIDAStarInitFScore(struct D2DynamicPath* pDynamicPath, int nIDAStarInitFScore)
{
	D2_ASSERT(pDynamicPath->dwPathType != PATHTYPE_IDASTAR);

	pDynamicPath->nIDAStarInitFScore = nIDAStarInitFScore;
}

//D2Common.0x6FDAA350 (#10198)
//TODO: Check name
int __cdecl D2COMMON_10198_PathGetSaveStep(struct D2DynamicPath* pDynamicPath, struct D2PathPoint** ppPathPoints)
{
	D2_ASSERT(pDynamicPath->dwFlags & PATH_SAVE_STEPS_MASK);

	*ppPathPoints = pDynamicPath->SavedSteps;
	return pDynamicPath->nSavedStepsCount;
}

//D2Common.0x6FDAA390 (#10199)
//TODO: Check name
int __cdecl D2COMMON_10199_PathGetSaveX(struct D2DynamicPath* pDynamicPath)
{
	D2_ASSERT(pDynamicPath->dwFlags & PATH_SAVE_STEPS_MASK);

	if (pDynamicPath->nSavedStepsCount)
	{
		return pDynamicPath->SavedSteps[pDynamicPath->nSavedStepsCount -1].X;
	}

	return 0;
}

//D2Common.0x6FDAA3E0 (#10200)
//TODO: Check name
int __cdecl D2COMMON_10200_PathGetSaveY(struct D2DynamicPath* pDynamicPath)
{
	D2_ASSERT(pDynamicPath->dwFlags & PATH_SAVE_STEPS_MASK);

	if (pDynamicPath->nSavedStepsCount)
	{
		return pDynamicPath->SavedSteps[pDynamicPath->nSavedStepsCount - 1].Y;
	}

	return 0;
}

//D2Common.0x6FDAA430 (#10203)
//TODO: Check name
void __cdecl D2COMMON_10203_PATH_SetRotateFlag(struct D2DynamicPath* pDynamicPath, BOOL bReset)
{
	if (pDynamicPath)
	{
		if (bReset)
		{
			pDynamicPath->dwFlags &= (~PATH_UNKNOWN_FLAG_0x00040);
		}
		else
		{
			pDynamicPath->dwFlags |= PATH_UNKNOWN_FLAG_0x00040;
		}
	}
}

//D2Common.0x6FDAA460 (#10204)
//TODO: Check name
void __cdecl D2COMMON_10204_PATH_ClearPoint2(struct D2DynamicPath* pDynamicPath)
{
	pDynamicPath->tPrevTargetCoord.X = 0;
	pDynamicPath->tPrevTargetCoord.Y = 0;
}

//D2Common.0x6FDAA480 (#10205)
void __cdecl PATH_SetStepNum(struct D2DynamicPath* pDynamicPath, uint8_t nSteps)
{
	if (pDynamicPath)
	{
		if (nSteps > 0 && nSteps < PATH_MAX_STEPNUM)
		{
			pDynamicPath->nStepNum = nSteps - 1;
		}
		else
		{
			pDynamicPath->nStepNum = 0;
		}
	}
}

//D2Common.0x6FDAA4B0 (#10206)
int __cdecl PATH_GetStepNum(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->nStepNum + 1;
}

//D2Common.0x6FDAA4C0 (#10207)
//TODO: Find a name
void __cdecl D2Common_10207(struct D2DynamicPath* pDynamicPath, char a2, char a3)
{
	pDynamicPath->unk0x67 = a2;
	pDynamicPath->dwSpeed = a3;
}

//D2Common.0x6FDAA4E0 (#10217)
void __cdecl PATH_SetDistance(struct D2DynamicPath* pDynamicPath, int nDist)
{
	D2_ASSERT(nDist >= 0 && nDist <= 255);

	pDynamicPath->nDistance = nDist;
}

//D2Common.0x6FDAA520 (#10218)
int __cdecl PATH_GetDistance(struct D2DynamicPath* pDynamicPath)
{
	return pDynamicPath->nDistance;
}

//D2Common.0x6FDAA530 (#10219)
void __cdecl PATH_AddToDistance(struct D2DynamicPath* pDynamicPath, int nAddition)
{
	int nDistance = nAddition + pDynamicPath->nDistance;
	pDynamicPath->nDistance = D2Clamp(nDistance, 0, 0xFF);
}

//D2Common.0x6FDAA570 (#10210)
int __cdecl PATH_GetUnitCollisionPattern(struct D2Unit* pUnit)
{
	return pUnit->pDynamicPath->dwCollisionPattern;
}

//D2Common.0x6FDAA580 (#10211)
void __cdecl PATH_SetUnitCollisionPattern(struct D2Unit* pUnit, int nCollisionPattern)
{
	pUnit->pDynamicPath->dwCollisionPattern = nCollisionPattern;
}

//D2Common.0x6FDAA5A0 (#10212)
//TODO: Check name
void __cdecl D2COMMON_10212_PATH_SetMoveFlags(struct D2Unit* pUnit, BOOL bSet)
{
	struct D2DynamicPath* pDynamicPath = pUnit->pDynamicPath;

	D2_ASSERT(pDynamicPath);

	if (bSet)
	{
		pUnit->dwFlagEx |= UNITFLAGEX_UNK_PATH_RELATED;
		pDynamicPath->unk0x38 = 0;
	}
	else
	{
		pUnit->dwFlagEx &= (~UNITFLAGEX_UNK_PATH_RELATED);
		pDynamicPath->unk0x38 = 0;
	}
}

//D2Common.0x6FDAA600 (#10213)
//TODO: Find a name
void __cdecl D2Common_10213(struct D2Unit* pUnit)
{
	if (pUnit && !(pUnit->dwFlags & UNITFLAG_ISASYNC) && (pUnit->dwFlagEx & UNITFLAGEX_UNK_PATH_RELATED))
	{
		struct D2DynamicPath* pDynamicPath = pUnit->pDynamicPath;
		D2_ASSERT(pDynamicPath);

		++pDynamicPath->unk0x38;

		if (pDynamicPath->unk0x38 > 1)
		{
			pDynamicPath->unk0x38 = 0;
			if (!D2Common_10227(pUnit))
			{
				if (D2Common_10236(pUnit, pDynamicPath->pTargetUnit != nullptr))
				{
					UNITS_ChangeAnimMode(pUnit, 2);
				}
			}
		}
	}
}

//D2Common.0x6FDAA6A0 (#10220)
int __cdecl PATH_ComputeSquaredDistance(int nX1, int nY1, int nX2, int nY2)
{
	const int deltaX = (nX2 - nX1);
	const int deltaY = (nY2 - nY1);
	return deltaX * deltaX + deltaY * deltaY;
}

//D2Common.0x6FDAA6D0 (#10221)
void __cdecl PATH_AddCollisionFootprintForOptionalUnit(struct D2Unit* pUnit)
{
	if (pUnit)
	{
		PATH_AddCollisionFootprintForUnit(pUnit);
	}
}

//D2Common.0x6FDAA6F0 (#10237)
//TODO: Find a name
BOOL __cdecl D2Common_10237(struct D2Unit* pUnit)
{
	if (pUnit && pUnit->pDynamicPath)
	{
		return (pUnit->pDynamicPath->dwCurrentPointIdx < pUnit->pDynamicPath->dwPathPoints);
	}

	return FALSE;
}
