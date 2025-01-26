#pragma once

#include "D2CommonDefinitions.h"
#pragma pack(1)

struct D2WaypointActTable
{
	bool bTableInitialized;					//0x00
	int32_t nStartLevelId;						//0x01
	int32_t nEndLevelId;						//0x05
	char nWpNo;								//0x09
	char nLastWpNo;							//0x0A
};

struct D2WaypointCoordTable
{
	int32_t nX;									//0x00
	int32_t nY;									//0x04
	int32_t nTextX;								//0x08
	int32_t nTextY;								//0x0C
	int32_t nClickX;							//0x10
	int32_t nClickY;							//0x14
};

struct D2WaypointData
{
	// Called "history" in the original game
	uint16_t nFlags[8];							//0x00
};

struct D2WaypointFlagTable
{
	uint16_t nArrayId;							//0x00
	uint16_t nFlag;								//0x02
};

struct D2WaypointTable
{
	int32_t nLevelId;							//0x00
	bool bActivated;						//0x04
};
#pragma pack()

//D2Common.0x6FDC3D20 (#11153)
D2COMMON_DLL_DECL BOOL __cdecl WAYPOINTS_GetLevelIdFromWaypointNo(short nWaypointNo, int* pLevelId);
//D2Common.0x6FDC3D90 (#11152)
D2COMMON_DLL_DECL BOOL __cdecl WAYPOINTS_GetWaypointNoFromLevelId(int nLevelId, short* pWaypointNo);
//D2Common.0x6FDC3DE0 (#11146)
D2COMMON_DLL_DECL int __cdecl WAYPOINTS_IsActivated(struct D2WaypointData* pData, uint16_t wField);
//D2Common.0x6FDC3E80 (#11147)
D2COMMON_DLL_DECL void __cdecl WAYPOINTS_ActivateWaypoint(struct D2WaypointData* pData, uint16_t wField);
//D2Common.0x6FDC3F20 (#11148)
D2COMMON_DLL_DECL struct D2WaypointData* __cdecl WAYPOINTS_AllocWaypointData(void* pMemPool);
//D2Common.0x6FDC3F70 (#11149)
D2COMMON_DLL_DECL void __cdecl WAYPOINTS_FreeWaypointData(void* pMemPool, struct D2WaypointData* pData);
//D2Common.0x6FDC3FD0 (#11150)
D2COMMON_DLL_DECL void __cdecl WAYPOINTS_CopyAndValidateWaypointData(struct D2WaypointData* pDestination, struct D2WaypointData* pSource);
//D2Common.0x6FDC4060 (#11151)
D2COMMON_DLL_DECL void __cdecl WAYPOINTS_ValidateAndCopyWaypointData(struct D2WaypointData* pSource, struct D2WaypointData* pDestination);
