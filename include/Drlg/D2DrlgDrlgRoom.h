#pragma once

#include "D2CommonDefinitions.h"
#include <Drlg/D2DrlgDrlgVer.h>

struct D2Drlg;
struct D2ActiveRoom;
struct D2DrlgRoom;
struct D2DrlgLevel;
struct D2DrlgOrth;
struct D2PresetUnit;

#pragma pack(1)


#pragma pack()

//D2Common.0x6FD771C0
struct D2DrlgRoom* __cdecl DRLGROOM_AllocRoomEx(struct D2DrlgLevel* pLevel, int nType);
//D2Common.0x6FD77280
void __cdecl sub_6FD77280(struct D2DrlgRoom* pDrlgRoom, BOOL bClient, uint32_t nFlags);
//D2Common.0x6FD772B0
void __cdecl DRLGROOM_FreeRoomTiles(void* pMemPool, struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD772F0
void __cdecl DRLGROOM_FreeRoomEx(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD774F0
void __cdecl DRLGROOM_FreeRoomData(void* pMemPool, struct D2DrlgOrth* pDrlgRoomData);
//D2Common.0x6FD77520
void __cdecl DRLGROOM_AllocDrlgOrthsForRooms(struct D2DrlgRoom* pDrlgRoom1, struct D2DrlgRoom* pDrlgRoom2, int nDirection);
//D2Common.0x6FD77600
void __cdecl DRLGROOM_AddOrth(struct D2DrlgOrth** ppDrlgOrth, struct D2DrlgLevel* pLevel, int nDirection, BOOL bIsPreset);
//D2Common.0x6FD776B0
BOOL __cdecl sub_6FD776B0(struct D2DrlgOrth* pDrlgOrth1, struct D2DrlgOrth* pDrlgOrth2);
//D2Common.0x6FD77740
BOOL __cdecl DRLG_GetRectanglesManhattanDistanceAndCheckNotOverlapping(struct D2DrlgCoord* pDrlgCoord1, struct D2DrlgCoord* pDrlgCoord2, int nMaxDistance, int* pDistanceX, int* pDistanceY);
//D2Common.0x6FD777B0
BOOL __cdecl DRLG_CheckNotOverlappingUsingManhattanDistance(struct D2DrlgCoord* pDrlgCoord1, struct D2DrlgCoord* pDrlgCoord2, int nMaxDistance);
//D2Common.0x6FD77800
BOOL __cdecl DRLG_CheckOverlappingWithOrthogonalMargin(struct D2DrlgCoord* pDrlgCoord1, struct D2DrlgCoord* pDrlgCoord2, int nOrthogonalDistanceMax);
//D2Common.0x6FD77890
BOOL __cdecl DRLGMAZE_CheckRoomNotOverlaping(struct D2DrlgLevel* pLevel, struct D2DrlgRoom* pDrlgRoom1, struct D2DrlgRoom* pIgnoredRoom, int nMargin);
//D2Common.0x6FD77910
void __cdecl DRLGROOM_AddRoomExToLevel(struct D2DrlgLevel* pLevel, struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD77930
BOOL __cdecl DRLGROOM_AreXYInsideCoordinates(struct D2DrlgCoord* pDrlgCoord, int nX, int nY);
//D2Common.0x6FD77980
BOOL __cdecl DRLGROOM_AreXYInsideCoordinatesOrOnBorder(struct D2DrlgCoord* pDrlgCoord, int nX, int nY);
//D2Common.0x6FD779D0
BOOL __cdecl DRLGROOM_CheckLOSDraw(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD779F0
int __cdecl sub_6FD779F0(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD77A00
int __cdecl DRLGROOM_CheckWaypointFlags(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD77A10
int __cdecl DRLGROOM_GetLevelId(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD77A20
int __cdecl DRLGROOM_GetWarpDestinationLevel(struct D2DrlgRoom* pDrlgRoom, int nSourceLevel);
//D2Common.0x6FD77AB0
int __cdecl DRLGROOM_GetLevelIdFromPopulatedRoom(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD77AF0
BOOL __cdecl DRLGROOM_HasWaypoint(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD77B20
const char* __cdecl DRLGROOM_GetPickedLevelPrestFilePathFromRoomEx(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD77B50
int __cdecl DRLGROOM_ReorderNearRoomList(struct D2DrlgRoom* pDrlgRoom, struct D2ActiveRoom** ppRoomList);
//D2Common.0x6FD77BB0
void __cdecl sub_6FD77BB0(void* pMemPool, struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD77EB0
void __cdecl DRLGROOM_SortRoomListByPosition(struct D2DrlgRoom** ppRoomList, int nListSize);
//D2Common.0x6FD77F00
BOOL __cdecl sub_6FD77F00(void* pMemPool, struct D2DrlgRoom* pDrlgRoom1, uint8_t nWarpId, struct D2DrlgRoom* pDrlgRoom2, char nWarpFlag, int nDirection);
//D2Common.0x6FD780E0
struct D2PresetUnit* __cdecl DRLGROOM_AllocPresetUnit(struct D2DrlgRoom* pDrlgRoom, void* pMemPool, int nUnitType, int nIndex, int nMode, int nX, int nY);
//D2Common.0x6FD78160
struct D2PresetUnit* __cdecl DRLGROOM_GetPresetUnits(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD78190
void __cdecl DRLGROOM_SetRoom(struct D2DrlgRoom* pDrlgRoom, struct D2ActiveRoom* pRoom);
//D2Common.0x6FD781A0
void __cdecl DRLGROOM_GetRGB_IntensityFromRoomEx(struct D2DrlgRoom* pDrlgRoom, uint8_t* pIntensity, uint8_t* pRed, uint8_t* pGreen, uint8_t* pBlue);
//D2Common.0x6FD781E0
int* __cdecl DRLGROOM_GetVisArrayFromLevelId(struct D2Drlg* pDrlg, int nLevelId);
//D2Common.0x6FD78230
struct D2Drlg* __cdecl DRLGROOM_GetDrlgFromRoomEx(struct D2DrlgRoom* pRoom);
