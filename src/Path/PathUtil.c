#include <Path/PathUtil.h>
#include <Units/Units.h>
#include <Fog.h>

//1.10f: D2Common.0x6FDAB890
//1.13c: D2Common.0x6FD8E080
void __cdecl PATHUtil_AdvanceTowardsTarget_6FDAB890(struct D2DynamicPath* ptPath)
{
	D2_ASSERT(ptPath);
	struct D2Unit* ptTarget = ptPath->pTargetUnit;
	D2_ASSERT(ptTarget);
	uint8_t nDirection = PATH_GetDirection(ptTarget->pDynamicPath);
	int nSpeed = ptPath->dwSpeed;
	uint16_t v4 = (uint16_t)nSpeed << 8;
	const float nDistance = nSpeed;
	const uint16_t nAngleRad512 = (8 * nDirection - v4) & 0x1FF;
	ptPath->tTargetCoord.X += (int64_t)(FOG_10083_Cos_LUT(nAngleRad512) * nDistance);
	ptPath->tTargetCoord.Y += (int64_t)(FOG_10084_Sin_LUT(nAngleRad512) * nDistance);
}

//1.10f: D2Common.0x6FDAB940
//1.13c: D2Common.0x6FD8E310
void __cdecl sub_6FDAB940(struct D2PathPoint* pOutPathPoint, struct D2DynamicPath* ptPath)
{
	D2_ASSERT(ptPath);
	D2_ASSERT(ptPath->pTargetUnit);
	struct D2Unit* pTargetUnit = ptPath->pTargetUnit;
	enum D2C_UnitTypes dwTargetUnitType = (enum D2C_UnitTypes)pTargetUnit->dwUnitType;

	if (dwTargetUnitType == UNIT_OBJECT || dwTargetUnitType == UNIT_ITEM || dwTargetUnitType == UNIT_TILE)
	{
		pOutPathPoint->X = pTargetUnit->pStaticPath->tGameCoords.nX;
		pOutPathPoint->Y = pTargetUnit->pStaticPath->tGameCoords.nY;
	}
	else
	{
		struct D2DynamicPath* pTargetPath = pTargetUnit->pDynamicPath;
		if (pTargetPath)
		{
			pOutPathPoint->X = PATH_GetXPosition(pTargetPath);
			pOutPathPoint->Y = PATH_GetYPosition(pTargetPath);
		}
		else
		{
			*pOutPathPoint = (struct D2PathPoint){ 0,0 };
		}
	}

	if (ptPath->dwSpeed)
	{
		PATHUtil_AdvanceTowardsTarget_6FDAB890(ptPath);
	}
}
