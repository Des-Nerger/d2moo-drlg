#pragma once

#include "D2CommonDefinitions.h"
#include <Drlg/D2DrlgDrlgVer.h>

struct D2DrlgLevel;

#pragma pack(1)


#pragma pack()

//D2Common.0x6FD84CA0
void __cdecl DRLGOUTWILD_GetBridgeCoords(struct D2DrlgLevel* pLevel, int* pX, int* pY);
//D2Common.0x6FD84D30
void __cdecl DRLGOUTWILD_InitAct1OutdoorLevel(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD85060
BOOL __cdecl DRLGOUTWILD_TestSpawnRiver(struct D2DrlgLevel* pLevel, int nX);
//D2Common.0x6FD850B0
void __cdecl DRLGOUTWILD_SpawnRiver(struct D2DrlgLevel* pLevel, int nX);
//D2Common.0x6FD85300
BOOL __cdecl sub_6FD85300(struct D2DrlgVertex* pDrlgVertex);
//D2Common.0x6FD85350
BOOL __cdecl sub_6FD85350(struct D2DrlgVertex* pDrlgVertex);
//D2Common.0x6FD85390
BOOL __cdecl DRLGOUTWILD_SpawnCliffCaves(struct D2DrlgLevel* pLevel, int nX, int nY);
//D2Common.0x6FD853F0
void __cdecl DRLGOUTWILD_SpawnTownTransitionsAndCaves(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD85520
void __cdecl DRLGOUTWILD_SpawnSpecialPresets(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD85920
void __cdecl DRLGOUTWILD_SpawnCottage(struct D2DrlgLevel* pLevel, int nLvlPrestId, int a3);
