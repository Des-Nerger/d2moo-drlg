#pragma once

#include "CommonDefinitions.h"

struct D2ActiveRoom;
struct D2DrlgRoom;
struct D2Drlg;

#pragma pack(1)


#pragma pack()

//D2Common.0x6FD733D0
void DRLGACTIVATE_RoomExSetStatus_ClientInRoom(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD73450
void DRLGACTIVATE_RoomExSetStatus_ClientInSight(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD73550
void DRLGACTIVATE_RoomExSetStatus_ClientOutOfSight(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD736F0
void DRLGACTIVATE_RoomExSetStatus_Untile(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD73790
void DRLGACTIVATE_RoomExIdentifyRealStatus(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD73880
void DRLGACTIVATE_RoomExStatusUnset_Untile(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD739A0
void DRLGACTIVATE_SetClientIsInSight(struct D2Drlg* pDrlg, int nLevelId, int nX, int nY, struct D2DrlgRoom* pDrlgRoomHint);
//D2Common.0x6FD73A30
void DRLGACTIVATE_RoomExPropagateSetStatus(void* pMemPool, struct D2DrlgRoom* pDrlgRoom, uint8_t nStatus);
//D2Common.0x6FD73B40
void DRLGACTIVATE_UnsetClientIsInSight(struct D2Drlg* pDrlg, int nLevelId, int nX, int nY, struct D2DrlgRoom* pDrlgRoomHint);
//D2Common.0x6FD73BE0
void DRLGACTIVATE_RoomExPropagateUnsetStatus(struct D2DrlgRoom* pDrlgRoom, uint8_t nStatus);
//D2Common.0x6FD73C40
void DRLGACTIVATE_ChangeClientRoom(struct D2DrlgRoom* pPreviousRoom, struct D2DrlgRoom* pNewRoom);
//D2Common.0x6FD73CF0
void DRLGACTIVATE_InitializeRoomEx(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD73D80
struct D2ActiveRoom* DRLGACTIVATE_StreamRoomAtCoords(struct D2Drlg* pDrlg, int nX, int nY);
//D2Common.0x6FD73E30
void DRLGACTIVATE_InitializeRoomExStatusLists(struct D2Drlg* pDrlg);
//D2Common.0x6FD73E60
struct D2ActiveRoom* DRLGACTIVATE_GetARoomInClientSight(struct D2Drlg* pDrlg);
//D2Common.0x6FD73E90
struct D2ActiveRoom* DRLGACTIVATE_GetARoomInSightButWithoutClient(struct D2Drlg* pDrlg, struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD73EF0 (#10015)
void DRLGACTIVATE_GetRoomsAllocationStats(int* pOutStatsClientAllocatedRooms, int* pOutStatsClientFreedRooms, int* pOutStatsAllocatedRooms, int* pOutStatsFreedRooms);
//D2Common.0x6FD73F20 (#10003)
void DRLGACTIVATE_Update(struct D2Drlg* pDrlg);
//D2Common.0x6FD74060
BOOL DRLGACTIVATE_TestRoomCanUnTile(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD740F0
void DRLGACTIVATE_ToggleHasPortalFlag(struct D2DrlgRoom* pDrlgRoom, BOOL bReset);
//D2Common.0x6FD74110
uint8_t DRLGACTIVATE_GetRoomStatusFlags(struct D2DrlgRoom* pDrlgRoom);
