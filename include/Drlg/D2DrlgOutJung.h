#pragma once

#include "D2CommonDefinitions.h"

struct D2DrlgLevel;

#pragma pack(1)

#pragma pack()


//D2Common.0x6FD7FC20
void __cdecl DRLGOUTJUNG_BuildJungle(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7FE50
void __cdecl DRLGOUTJUNG_BuildLowerKurast(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7FFA0
void __cdecl DRLGOUTJUNG_BuildKurastBazaar(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD800E0
void __cdecl DRLGOUTJUNG_BuildUpperKurast(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD80230
void __cdecl DRLGOUTJUNG_SpawnRandomPreset(struct D2DrlgLevel* pLevel, int nLevelPrestId1, int nLevelPrestId2, int a4);
