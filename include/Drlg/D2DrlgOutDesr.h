#pragma once

#include "D2CommonDefinitions.h"

struct D2DrlgLevel;

#pragma pack(1)


#pragma pack()


//Inlined in D2Common.0x6FD7D430
void __fastcall DRLGOUTDESR_PlaceDesertTransitionToTown(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7D430
void __fastcall DRLGOUTDESR_InitAct2OutdoorLevel(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7D870
void __fastcall DRLGOUTDESR_PlacePresetVariants(struct D2DrlgLevel* pLevel, const int* pLevelPrestIds, unsigned int nVariants, BOOL bIterateFiles);
//D2Common.6FD7D950
void __fastcall DRLGOUTDESR_PlaceCliffs(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7D9B0
void __fastcall DRLGOUTDESR_PlaceBorders(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7D9F0
void __fastcall DRLGOUTDESR_AddExits(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7DA60
void __fastcall DRLGOUTDESR_PlaceFillsInFarOasis(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7DAC0
void __fastcall DRLGOUTDESR_PlaceRuinsInLostCity(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7DB00
void __fastcall DRLGOUTDESR_PlaceFillsInLostCity(struct D2DrlgLevel* pLevel);
//D2Common.6FD7DB70
void __fastcall DRLGOUTDESR_PlaceTombEntriesInCanyon(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7DBC0
void __fastcall DRLGOUTDESR_PlaceFillsInCanyon(struct D2DrlgLevel* pLevel);
