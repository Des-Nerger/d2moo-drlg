#pragma once

#include "D2CommonDefinitions.h"

struct D2DrlgLevel;

#pragma pack(1)


#pragma pack()

//D2Common.0x6FD84100
int __fastcall sub_6FD84100(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD84110
void __fastcall DRLGOUTSIEGE_InitAct5OutdoorLevel(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD844F0
void __fastcall DRLGOUTSIEGE_PlaceCaves(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD84580
void __fastcall DRLGOUTSIEGE_PlaceBarricadeEntrancesAndExits(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD846C0
void __fastcall sub_6FD846C0(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD84700
void __fastcall DRLGOUTSIEGE_AddACt5SecondaryBorder(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD84780
int __fastcall sub_6FD84780(struct D2DrlgLevel* pLevel, int nStyle, int a3);
//D2Common.0x6FD84820
BOOL __fastcall sub_6FD84820(struct D2DrlgLevel* pLevel, int nX, int nY, int a4, int a5, unsigned int a6);
//D2Common.0x6FD84870
void __fastcall DRLGOUTSIEGE_PlaceSpecialPresets(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD84910
void __fastcall DRLGOUTSIEGE_PlacePrisons(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD84BB0
void __fastcall DRLGOUTSIEGE_ConnectBarricadeAndSiege(struct D2DrlgLevel* pLevel);
