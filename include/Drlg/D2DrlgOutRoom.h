#pragma once

#include "D2CommonDefinitions.h"
#include "D2DrlgDrlgGrid.h"

struct D2DrlgRoom;
struct D2DrlgLevelLinkData;

#pragma pack(1)


struct D2DrlgOutdoorRoom
{
	struct D2DrlgGrid pTileTypeGrid;			//0x00 aka pOrientationGrid
	struct D2DrlgGrid pWallGrid;				//0x14
	struct D2DrlgGrid pFloorGrid;				//0x28
	struct D2DrlgGrid pDirtPathGrid;			//0x3C
	struct D2DrlgVertex* pVertex;				//0x50
	int32_t dwFlags;						//0x54
	int32_t dwFlagsEx;						//0x58
	int32_t unk0x5C;						//0x5C
	int32_t unk0x60;						//0x60
	int32_t nSubType;						//0x64
	int32_t nSubTheme;						//0x68
	int32_t nSubThemePicked;				//0x6C
};

#pragma pack()


//D2Common.0x6FD83D20
void __fastcall DRLGOUTROOM_FreeDrlgOutdoorRoom(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD83D90
void __fastcall DRLGOUTROOM_FreeDrlgOutdoorRoomData(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD83DE0
void __fastcall DRLGOUTROOM_AllocDrlgOutdoorRoom(struct D2DrlgRoom* pDrlgRoom);
//D2Common.6FD83E20
void __fastcall DRLGOUTROOM_InitializeDrlgOutdoorRoom(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD83EC0
BOOL __fastcall DRLGOUTROOM_LinkLevelsByLevelCoords(struct D2DrlgLevelLinkData* pLevelLinkData);
//D2Common.0x6FD83F70
BOOL __fastcall DRLGOUTROOM_LinkLevelsByLevelDef(struct D2DrlgLevelLinkData* pLevelLinkData);
//D2Common.0x6FD84010
BOOL __fastcall DRLGOUTROOM_LinkLevelsByOffsetCoords(struct D2DrlgLevelLinkData* pLevelLinkData);
