#include <time.h>
#include <D2Seed.h>
#include <D2CommonDefinitions.h>
#include <Fog.h>

//D2Common.0x6FDA5260 (#10916)
void __cdecl SEED_Return()
{
	REMOVE_LATER_Trace("SEED_Return: Useless");
}

//D2Common.0x6FDAEA80 (#10920)
int __cdecl SEED_GetRandomValue(int nValue)
{
	return (0x2F490A95 * (time(NULL) + nValue + GetTickCount()) - 0x2E330917) & 0x7FFFFFFF;
}

//D2Common.0x6FDAEAB0 (#10912)
void __cdecl SEED_InitSeed(struct D2Seed* pSeed)
{
	pSeed->nLowSeed = 1;
	pSeed->nHighSeed = 666;
}

//D2Common.0x6FDAEAC0 (#10913)
void __cdecl SEED_InitLowSeed(struct D2Seed* pSeed, int nLowSeed)
{
	pSeed->nLowSeed = nLowSeed;
	pSeed->nHighSeed = 666;
}

//D2Common.0x6FDAEAD0 (#10914)
uint32_t  __cdecl SEED_GetLowSeed(struct D2Seed* pSeed)
{
	return pSeed->nLowSeed;
}

//D2Common.0x6FDAEAE0 (#10921)
void __cdecl SEED_SetSeeds(struct D2Seed* pSeed, uint32_t  nLowSeed, uint32_t  nHighSeed)
{
	pSeed->nLowSeed = nLowSeed;
	pSeed->nHighSeed = nHighSeed;
}

//D2Common.0x6FDAEAF0 (#10922)
void __cdecl SEED_GetSeeds(struct D2Seed* pSeed, uint32_t* pLowSeed, uint32_t* pHighSeed)
{
	*pLowSeed = pSeed->nLowSeed;
	*pHighSeed = pSeed->nHighSeed;
}

//D2Common.0x6FDAEB00 (#10915)
uint32_t __cdecl SEED_GetHighSeed(struct D2Seed* pSeed)
{
	return pSeed->nHighSeed;
}

//D2Common.0x6FD7D3E0
uint32_t __cdecl SEED_RollLimitedRandomNumber(struct D2Seed* pSeed, int nMax)
{
	if (nMax > 0)
	{
		if ((nMax - 1) & nMax)
		{
			return (unsigned int)SEED_RollRandomNumber(pSeed) % nMax;
		}
		else
		{
			return SEED_RollRandomNumber(pSeed) & (nMax - 1);
		}
	}

	return 0;
}