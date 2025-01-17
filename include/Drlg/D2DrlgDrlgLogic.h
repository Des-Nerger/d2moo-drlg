#pragma once

#include "D2CommonDefinitions.h"
#include "D2DrlgDrlg.h"
#include "D2DrlgDrlgGrid.h"

#pragma pack(1)

struct D2UnkDrlgLogic
{
	struct D2DrlgRoom* pDrlgRoom;				//0x00
	struct D2DrlgGrid* field_4;				//0x04
	struct D2DrlgGrid* pTileTypeGrid;			//0x08
	struct D2DrlgGrid* pWallGrid;				//0x0C
	struct D2DrlgGrid* pFloorGrid;				//0x10
	struct D2DrlgGrid* field_14;				//0x14
	int32_t field_18;						//0x18
	int32_t nFlags;							//0x1C
};

enum D2DrlgLogicalRoomInfoFlags
{
	DRLGLOGIC_ROOMINFO_HAS_COORD_LIST = 0x1,
	DRLGLOGIC_ROOMINFO_HAS_GRID_CELLS = 0x2,
};

struct D2DrlgLogicalRoomInfo // aka struct D2DrlgCoordList
{
	int32_t dwFlags;						//0x00 D2DrlgLogicalRoomInfoFlags
	int32_t nLists;							//0x04
	struct D2DrlgGrid pIndexX;					//0x08
	struct D2DrlgGrid pIndexY;					//0x1C
	struct D2RoomCoordList* pCoordList;		//0x30
};

#pragma pack()

//D2Common.0x6FD76420
void __fastcall DRLGLOGIC_FreeDrlgCoordList(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD764A0
//TODO: v28, a1
void __fastcall DRLGLOGIC_InitializeDrlgCoordList(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgGrid* pTileTypeGrid, struct D2DrlgGrid* pFloorGrid, struct D2DrlgGrid* pWallGrid);
//D2Common.0x6FD76830
void __fastcall DRLGLOGIC_SetTileGridFlags(struct D2UnkDrlgLogic* a1, int nX, int nY, int a4);
//D2Common.0x6FD769B0
void __fastcall sub_6FD769B0(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD76A90
void __fastcall sub_6FD76A90(struct D2DrlgRoom* pDrlgRoom1, struct D2DrlgRoom* pDrlgRoom2, int nX, int nY);
//D2Common.0x6FD76B90
void __fastcall sub_6FD76B90(struct D2DrlgRoom* pDrlgRoom, int nIndex1, int nIndex2, BOOL bNode);
//D2Common.0x6FD76C20
BOOL __fastcall DRLG_CheckLayer1ButNotWallObject(struct D2DrlgTileData* pTileData);
//D2Common.0x6FD76C50
void __fastcall DRLGLOGIC_SetCoordListForTiles(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD76CF0
void __fastcall DRLGLOGIC_AssignCoordListsForGrids(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgLogicalRoomInfo* pDrlgCoordList, int nLists);
//D2Common.0x6FD76F90
void __fastcall DRLGLOGIC_AllocCoordLists(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD77080
int __fastcall DRLGLOGIC_GetRoomCoordListIndex(struct D2DrlgRoom* pDrlgRoom, int nX, int nY);
//D2Common.0x6FD77110
struct D2RoomCoordList* __fastcall sub_6FD77110(struct D2DrlgRoom* pDrlgRoom, int nX, int nY);
//D2Common.0x6FD77190
struct D2RoomCoordList* __fastcall DRLGLOGIC_GetRoomCoordList(struct D2DrlgRoom* pDrlgRoom);
