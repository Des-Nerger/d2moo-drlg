#include "D2Waypoints.h"

#include "D2DataTbls.h"

static const int gnNumberOfWaypoints = 7 * 8 * sizeof(short);

//D2Common.0x6FDC3D20 (#11153)
BOOL __stdcall WAYPOINTS_GetLevelIdFromWaypointNo(short nWaypointNo, int* pLevelId)
{
	*pLevelId = 0;

	if (nWaypointNo < 255)
	{
		for (int i = 1; i < sgptDataTables->nLevelsTxtRecordCount; ++i)
		{
			if (DATATBLS_GetLevelsTxtRecord(i)->nWaypoint == nWaypointNo)
			{
				*pLevelId = i;
				return TRUE;
			}
		}
	}

	return FALSE;
}

//D2Common.0x6FDC3D90 (#11152)
BOOL __stdcall WAYPOINTS_GetWaypointNoFromLevelId(int nLevelId, short* pWaypointNo)
{
	struct D2LevelsTxt* pLevelsTxtRecord = NULL;

	*pWaypointNo = 255;

	pLevelsTxtRecord = DATATBLS_GetLevelsTxtRecord(nLevelId);
	if (pLevelsTxtRecord)
	{
		*pWaypointNo = pLevelsTxtRecord->nWaypoint;
	}

	return *pWaypointNo != 255;
}

//D2Common.0x6FDC3DE0 (#11146)
int __stdcall WAYPOINTS_IsActivated(struct D2WaypointData* pData, uint16_t wField)
{
	D2_ASSERT(pData);
	D2_ASSERT(wField < gnNumberOfWaypoints);

	return (pData->nFlags[wField / 16 + 1] & (1 << (wField & 15))) != 0;
}

//D2Common.0x6FDC3E80 (#11147)
void __stdcall WAYPOINTS_ActivateWaypoint(struct D2WaypointData* pData, uint16_t wField)
{
	D2_ASSERT(pData);
	D2_ASSERT(wField < gnNumberOfWaypoints);

	pData->nFlags[wField / 16 + 1] |= (1 << (wField & 15));
}

//D2Common.0x6FDC3F20 (#11148)
struct D2WaypointData* __stdcall WAYPOINTS_AllocWaypointData(void* pMemPool)
{
	struct D2WaypointData* pData = D2_CALLOC_STRC_POOL(pMemPool, struct D2WaypointData);

	pData->nFlags[0] = 0x102;
	pData->nFlags[1] |= 1;

	return pData;
}

//D2Common.0x6FDC3F70 (#11149)
void __stdcall WAYPOINTS_FreeWaypointData(void* pMemPool, struct D2WaypointData* pData)
{
	if (pData->nFlags[0] != 0x102)
	{
		D2_ASSERT(pData->nFlags[0] == 0x00 || pData->nFlags[0] == 0x101);
		pData->nFlags[0] = 0x102;
	}

	D2_FREE_POOL(pMemPool, pData);
}

//D2Common.0x6FDC3FD0 (#11150)
void __stdcall WAYPOINTS_CopyAndValidateWaypointData(struct D2WaypointData* pDestination, struct D2WaypointData* pSource)
{
	pDestination->nFlags[0] = pSource->nFlags[0];
	pDestination->nFlags[1] = pSource->nFlags[1];
	pDestination->nFlags[2] = pSource->nFlags[2];
	pDestination->nFlags[3] = pSource->nFlags[3];
	pDestination->nFlags[4] = pSource->nFlags[4];
	pDestination->nFlags[5] = pSource->nFlags[5];
	pDestination->nFlags[6] = pSource->nFlags[6];
	pDestination->nFlags[7] = pSource->nFlags[7];

	if (pDestination->nFlags[0] != 0x102)
	{
		D2_ASSERT(pDestination->nFlags[0] == 0x00 || pDestination->nFlags[0] == 0x101);
		pDestination->nFlags[0] = 0x102;
		memset(pDestination, 0x00, sizeof(struct D2WaypointData));
	}

	pDestination->nFlags[1] |= 1;
}

//D2Common.0x6FDC4060 (#11151)
void __stdcall WAYPOINTS_ValidateAndCopyWaypointData(struct D2WaypointData* pSource, struct D2WaypointData* pDestination)
{
	if (pSource->nFlags[0] != 0x102)
	{
		D2_ASSERT(pSource->nFlags[0] == 0x00 || pSource->nFlags[0] == 0x101);
		pSource->nFlags[0] = 0x102;
	}

	pDestination->nFlags[0] = pSource->nFlags[0];
	pDestination->nFlags[1] = pSource->nFlags[1];
	pDestination->nFlags[2] = pSource->nFlags[2];
	pDestination->nFlags[3] = pSource->nFlags[3];
	pDestination->nFlags[4] = pSource->nFlags[4];
	pDestination->nFlags[5] = pSource->nFlags[5];
	pDestination->nFlags[6] = pSource->nFlags[6];
	pDestination->nFlags[7] = pSource->nFlags[7];
}
