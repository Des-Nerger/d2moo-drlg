#pragma once

#include "D2CommonDefinitions.h"
#include <Drlg/D2DrlgDrlg.h>


#pragma pack(1)

enum D2JungleAttach {
	JUNGLE_MAX_ATTACH = 3,
	JUNGLE_PRESET2_ATTACH_POINT = 2
};


enum D2JunglePresetFlags {
	// Related to pPreset1 having a value in the direction
	JUNGLE_FLAG_LEFT_	= 0b0001, // West : deltaX < 0
	JUNGLE_FLAG_RIGHT_	= 0b0010, // East : deltaX > 0
	JUNGLE_FLAG_BOTTOM_	= 0b0100, // South: deltaY > 0
	JUNGLE_FLAG_TOP_	= 0b1000, // North: deltaY < 0
};

struct D2Jungle
{
	struct D2DrlgCoord pDrlgCoord;							//0x00
	int32_t field_10;									//0x10 Orientation of the jungle ?
	int32_t nBranch;									//0x14
	struct D2Jungle* pBasedOnJungle;						//0x18 Jungle we are based from
	struct D2Jungle* pJungleBranches[JUNGLE_MAX_ATTACH];	//0x1C Jungles that are based on this one
	int32_t nPresetsBlocksX;							//0x18
	int32_t nPresetsBlocksY;							//0x2C
	int32_t* pJungleDefs;								//0x30
	int32_t nJungleDefs;								//0x34
};


#pragma pack()

//D2Common.0x6FD80480
void __fastcall DRLGOUTPLACE_BuildKurast(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD806A0
void __fastcall DRLGOUTPLACE_InitAct3OutdoorLevel(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD80750
BOOL __fastcall sub_6FD80750(struct D2DrlgLevel* pLevel, int nVertexId);
//D2Common.0x6FD80BE0
int __fastcall sub_6FD80BE0(int a1, int a2, int a3);
//D2Common.0x6FD80C10
int __fastcall sub_6FD80C10(int a1, int a2, int a3, int a4, int a5);
//D2Common.0x6FD80C80
void __fastcall DRLGOUTPLACE_SetBlankBorderGridCells(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD80DA0
void __fastcall DRLGOUTPLACE_SetOutGridLinkFlags(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD80E10
void __fastcall DRLGOUTPLACE_PlaceAct1245OutdoorBorders(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD81330
BOOL __fastcall sub_6FD81330(struct D2DrlgLevelLinkData* pLevelLinkData);
//D2Common.0x6FD81380
BOOL __fastcall sub_6FD81380(struct D2DrlgLevelLinkData* pLevelLinkData);
//D2Common.0x6FD81430
void __fastcall sub_6FD81430(struct D2DrlgCoord* pDrlgCoord1, struct D2DrlgCoord* pDrlgCoord2, int a3, int a4);
//D2Common.0x6FD81530
BOOL __fastcall sub_6FD81530(struct D2DrlgLevelLinkData* pLevelLinkData);
//D2Common.0x6FD815E0
void __fastcall sub_6FD815E0(struct D2DrlgCoord* pDrlgCoord1, struct D2DrlgCoord* pDrlgCoord2, int a3, int a4);
//D2Common.0x6FD81720
BOOL __fastcall sub_6FD81720(struct D2DrlgLevelLinkData* pLevelLinkData);
//D2Common.0x6FD81850
void __fastcall sub_6FD81850(struct D2DrlgCoord* pDrlgCoord1, struct D2DrlgCoord* pDrlgCoord2, int a3, int a4);
//D2Common.0x6FD81950
BOOL __fastcall sub_6FD81950(struct D2DrlgLevelLinkData* pLevelLinkData);
//D2Common.0x6FD81AD0
BOOL __fastcall sub_6FD81AD0(struct D2DrlgLevelLinkData* pLevelLinkData);
//D2Common.0x6FD81B30
BOOL __fastcall sub_6FD81B30(struct D2DrlgLevelLinkData* pLevelLinkData);
//D2Common.0x6FD81BF0
BOOL __fastcall sub_6FD81BF0(struct D2DrlgLevelLinkData* pLevelLinkData);
//D2Common.0x6FD81CA0
BOOL __fastcall sub_6FD81CA0(struct D2DrlgLevelLinkData* pLevelLinkData);
//D2Common.0x6FD81D60
void __fastcall DRLGOUTPLACE_CreateLevelConnections(struct D2Drlg* pDrlg, uint8_t nActNo);
//D2Common.0x6FD82050
BOOL __fastcall sub_6FD82050(struct D2DrlgLevelLinkData* pLevelLinkData, int nIteration);
//D2Common.0x6FD82130
BOOL __fastcall sub_6FD82130(struct D2DrlgLevelLinkData* pLevelLinkData, int nIteration);
//D2Common.0x6FD821E0
BOOL __fastcall DRLGOUTPLACE_LinkAct2Outdoors(struct D2DrlgLevelLinkData* pLevelLinkData, int nIteration);
//D2Common.0x6FD82240
BOOL __fastcall DRLGOUTPLACE_LinkAct2Canyon(struct D2DrlgLevelLinkData* pLevelLinkData, int nIteration);
//D2Comon.0x6FD822A0
BOOL __fastcall DRLGOUTPLACE_LinkAct4Outdoors(struct D2DrlgLevelLinkData* pLevelLinkData, int nIteration);
//D2Common.0x6FD82300
BOOL __fastcall DRLGOUTPLACE_LinkAct4ChaosSanctum(struct D2DrlgLevelLinkData* pLevelLinkData, int nIteration);
//D2Common.0x6FD82360
void __fastcall sub_6FD82360(struct D2DrlgLevel* pLevel, int nIteration, int* pRand);
//D2Common.0x6FD823C0
void __fastcall sub_6FD823C0(struct D2Drlg* pDrlg, struct D2DrlgLink* pDrlgLink, int(__fastcall* a3)(struct D2DrlgLevelLinkData*, int), void(__fastcall* a4)(struct D2DrlgLevel*, int, int*));
//D2Common.0x6FD826D0
void __fastcall sub_6FD826D0(struct D2Drlg* pDrlg, int nStartId, int nEndId);
//D2Common.0x6FD82750
void __fastcall sub_6FD82750(struct D2Drlg* pDrlg, int nStartId, int nEndId);
//D2Common.0x6FD82820
struct D2DrlgLevel* __fastcall DRLG_GenerateJungles(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD83970
void __fastcall sub_6FD83970(struct D2DrlgCoord* pDrlgCoord, struct D2Jungle* pJungle, int nRand, int nSizeX, int nSizeY);
//D2Common.0x6FD83A20
void __fastcall DRLGOUTPLACE_InitOutdoorRoomGrids(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD83C90
void __fastcall DRLGOUTPLACE_CreateOutdoorRoomEx(struct D2DrlgLevel* pLevel, int nX, int nY, int nWidth, int nHeight, int dwRoomFlags, int dwOutdoorFlags, int dwOutdoorFlagsEx, int dwDT1Mask);
