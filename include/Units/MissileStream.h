#pragma once

#include "D2CommonDefinitions.h"

struct D2Unit;

#pragma pack(1)

struct D2MissileStream
{
	int32_t* unk0x00;							//0x00
	int32_t unk0x04;							//0x04
};

#pragma pack()

// Note: MISSSTREAM functions are all unreferenced except for MISSTREAM_FreeMissileStream which is probably just a security.

//D2Common.0x6FDBC230 (#11213)
D2COMMON_DLL_DECL void __cdecl MISSTREAM_AllocMissileStream(struct D2Unit* pMissile);
//D2Common.0x6FDBC280 (#11214)
D2COMMON_DLL_DECL void __cdecl MISSTREAM_FreeMissileStream(struct D2Unit* pMissile);
//D2Common.0x6FDBC2E0 (#11215)
D2COMMON_DLL_DECL void __cdecl MISSTREAM_ExecuteHit(struct D2Unit* pUnit, int nCollisionMask, int nCollisionPattern, void (__cdecl* pfnHit)(struct D2Unit*, struct D2Unit*));
//D2Common.0x6FDBC3B0
int __cdecl MISSTREAM_Return1(struct D2Unit* pUnit1, void* pUnit2);
//D2Common.0x6FDBC3C0 (#11216)
D2COMMON_DLL_DECL void __cdecl MISSTREAM_Update(struct D2Unit* a1, struct D2Unit* pMissile, int a3, int a4, int (__cdecl* pfCreate)(struct D2Unit*, int, int, int, int, int), void (__cdecl* a6)(int));
