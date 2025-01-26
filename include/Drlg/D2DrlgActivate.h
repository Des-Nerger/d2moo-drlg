#pragma once

#include "D2CommonDefinitions.h"

struct D2ActiveRoom;
struct D2DrlgRoom;
struct D2Drlg;

#pragma pack(1)


#pragma pack()

//D2Common.0x6FD733D0
void __cdecl DRLGACTIVATE_RoomExSetStatus_ClientInRoom(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD73450
void __cdecl DRLGACTIVATE_RoomExSetStatus_ClientInSight(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD73550
void __cdecl DRLGACTIVATE_RoomExSetStatus_ClientOutOfSight(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD736F0
void __cdecl DRLGACTIVATE_RoomExSetStatus_Untile(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD73790
void __cdecl DRLGACTIVATE_RoomExIdentifyRealStatus(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD73880
void __cdecl DRLGACTIVATE_RoomExStatusUnset_Untile(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD739A0
void __cdecl DRLGACTIVATE_SetClientIsInSight(struct D2Drlg* pDrlg, int nLevelId, int nX, int nY, struct D2DrlgRoom* pDrlgRoomHint);
//D2Common.0x6FD73A30
void __cdecl DRLGACTIVATE_RoomExPropagateSetStatus(void* pMemPool, struct D2DrlgRoom* pDrlgRoom, uint8_t nStatus);
//D2Common.0x6FD73B40
void __cdecl DRLGACTIVATE_UnsetClientIsInSight(struct D2Drlg* pDrlg, int nLevelId, int nX, int nY, struct D2DrlgRoom* pDrlgRoomHint);
//D2Common.0x6FD73BE0
void __cdecl DRLGACTIVATE_RoomExPropagateUnsetStatus(struct D2DrlgRoom* pDrlgRoom, uint8_t nStatus);
//D2Common.0x6FD73C40
void __cdecl DRLGACTIVATE_ChangeClientRoom(struct D2DrlgRoom* pPreviousRoom, struct D2DrlgRoom* pNewRoom);
//D2Common.0x6FD73CF0
void __cdecl DRLGACTIVATE_InitializeRoomEx(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD73D80
struct D2ActiveRoom* __cdecl DRLGACTIVATE_StreamRoomAtCoords(struct D2Drlg* pDrlg, int nX, int nY);
//D2Common.0x6FD73E30
void __cdecl DRLGACTIVATE_InitializeRoomExStatusLists(struct D2Drlg* pDrlg);
//D2Common.0x6FD73E60
struct D2ActiveRoom* __cdecl DRLGACTIVATE_GetARoomInClientSight(struct D2Drlg* pDrlg);
//D2Common.0x6FD73E90
struct D2ActiveRoom* __cdecl DRLGACTIVATE_GetARoomInSightButWithoutClient(struct D2Drlg* pDrlg, struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD73EF0 (#10015)
void __cdecl DRLGACTIVATE_GetRoomsAllocationStats(int* pOutStatsClientAllocatedRooms, int* pOutStatsClientFreedRooms, int* pOutStatsAllocatedRooms, int* pOutStatsFreedRooms);
//D2Common.0x6FD73F20 (#10003)
void __cdecl DRLGACTIVATE_Update(struct D2Drlg* pDrlg);
//D2Common.0x6FD74060
BOOL __cdecl DRLGACTIVATE_TestRoomCanUnTile(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD740F0
void __cdecl DRLGACTIVATE_ToggleHasPortalFlag(struct D2DrlgRoom* pDrlgRoom, BOOL bReset);
//D2Common.0x6FD74110
uint8_t __cdecl DRLGACTIVATE_GetRoomStatusFlags(struct D2DrlgRoom* pDrlgRoom);
