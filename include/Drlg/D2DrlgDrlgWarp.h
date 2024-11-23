#pragma once

#include "CommonDefinitions.h"

struct D2Drlg;
struct D2DrlgLevel;
struct D2LvlWarpTxt;
struct D2ActiveRoom;
struct D2DrlgRoom;
struct D2Unit;

#pragma pack(1)


#pragma pack()

//D2Common.0x6FD78780
struct D2ActiveRoom* DRLGWARP_GetDestinationRoom(struct D2DrlgRoom* pDrlgRoom, int nSourceLevel, int* pDestinationLevel, struct D2LvlWarpTxt** ppLvlWarpTxtRecord);
//D2Common.0x6FD787F0
void DRLGWARP_ToggleRoomTilesEnableFlag(struct D2DrlgRoom* pDrlgRoom, BOOL bEnabled);
//D2Common.0x6FD78810
void DRLGWARP_UpdateWarpRoomSelect(struct D2DrlgRoom* pDrlgRoom, int nLevelId);
//D2Common.0x6FD78870
void DRLGWARP_UpdateWarpRoomDeselect(struct D2DrlgRoom* pDrlgRoom, int nLevelId);
//D2Common.0x6FD788D0
struct D2ActiveRoom* sub_6FD788D0(struct D2Drlg* pDrlg, int nLevelId, int nTileIndex, int* pX, int* pY);
//D2Common.0x6FD78C10
struct D2DrlgRoom* DRLGWARP_GetWaypointRoomExFromLevel(struct D2DrlgLevel* pLevel, int* pX, int* pY);
//D2Common.0x6FD78CC0
int* DRLGWARP_GetWarpIdArrayFromLevelId(struct D2Drlg* pDrlg, int nLevelId);
//D2Common.0x6FD78D10
int DRLGWARP_GetWarpDestinationFromArray(struct D2DrlgLevel* pLevel, uint8_t nArrayId);
//D2Common.0x6FD78D80
struct D2LvlWarpTxt* DRLGWARP_GetLvlWarpTxtRecordFromWarpIdAndDirection(struct D2DrlgLevel* pLevel, uint8_t nWarpId, char szDirection);
//D2Common.0x6FD78DF0
struct D2LvlWarpTxt* DRLGWARP_GetLvlWarpTxtRecordFromUnit(struct D2DrlgRoom* pDrlgRoom, struct D2Unit* pUnit);
