#pragma once

#include <D2BasicTypes.h>
#include <D2Common.h>

#pragma pack(1)

struct D2Seed
{
	union
	{
		struct
		{
			uint32_t nLowSeed;					//0x00
			uint32_t nHighSeed;					//0x04
		};
		uint64_t lSeed;		//0x00
	};
};
#pragma pack()

//D2Common.0x6FDA5260 (#10916)
D2COMMON_DLL_DECL void __cdecl SEED_Return();
//D2Common.0x6FDAEA80 (#10920)
D2COMMON_DLL_DECL int __cdecl SEED_GetRandomValue(int nValue);
//D2Common.0x6FDAEAB0 (#10912)
D2COMMON_DLL_DECL void __cdecl SEED_InitSeed(struct D2Seed* pSeed);
//D2Common.0x6FDAEAC0 (#10913)
D2COMMON_DLL_DECL void __cdecl SEED_InitLowSeed(struct D2Seed* pSeed, int nLowSeed);
//D2Common.0x6FDAEAD0 (#10914)
D2COMMON_DLL_DECL uint32_t  __cdecl SEED_GetLowSeed(struct D2Seed* pSeed);
//D2Common.0x6FDAEAE0 (#10921)
D2COMMON_DLL_DECL void __cdecl SEED_SetSeeds(struct D2Seed* pSeed, uint32_t  nLowSeed, uint32_t  nHighSeed);
//D2Common.0x6FDAEAF0 (#10922)
D2COMMON_DLL_DECL void __cdecl SEED_GetSeeds(struct D2Seed* pSeed, uint32_t* pLowSeed, uint32_t* pHighSeed);
//D2Common.0x6FDAEB00 (#10915)
D2COMMON_DLL_DECL uint32_t  __cdecl SEED_GetHighSeed(struct D2Seed* pSeed);
//D2Common.0x6FD78E30 + Inlined at many places
inline uint64_t __cdecl SEED_RollRandomNumber(struct D2Seed* pSeed)
{
	uint64_t lSeed = pSeed->nHighSeed + 0x6AC690C5LL * pSeed->nLowSeed;

	pSeed->lSeed = lSeed;

	return lSeed;
}

//D2Common.0x6FD7D3E0
uint32_t __cdecl SEED_RollLimitedRandomNumber(struct D2Seed* pSeed, int nMax);

inline uint32_t SEED_RollPercentage(struct D2Seed* pSeed)
{
	return (SEED_RollRandomNumber(pSeed) % 100);
}
