#pragma once

#include "D2CommonDefinitions.h"

struct D2ActiveRoom;
struct D2DrlgAct;

#pragma pack(1)

enum D2EnvironmentPeriodOfDay
{
	ENVPERIOD_DAY   = 0,
	ENVPERIOD_DUSK  = 1,
	ENVPERIOD_NIGHT = 2,
	ENVPERIOD_DAWN  = 3,
	NUM_ENVIRONMENT_PERIODS_OF_DAY
};

enum D2EnvironmentDayCycles : int32_t {
	ENVCYCLE_SUNRISE,
	ENVCYCLE_MORNING,
	ENVCYCLE_NOON,
	ENVCYCLE_AFTERNOON,
	ENVCYCLE_SUNSET,
	ENVCYCLE_NIGHT,
	NUM_ENVIRONMENT_CYCLES
};

enum D2EnvironmentConstants
{
	ENV_HALF_CIRCLE_DEGREES = 180,
	ENV_FULL_CIRCLE_DEGREES = 360,
};

struct D2EnvironmentCycle
{
	int32_t nTicksBegin;			//0x00
	int32_t nPeriodOfDay;				//0x04
	uint8_t nRed;					//0x08
	uint8_t nGreen;				//0x09
	uint8_t nBlue;					//0x0A
	uint8_t nIntensity;			//0x0B Unused
};

struct D2DrlgEnvironment
{
	int32_t nCycleIndex;					//0x00
	int32_t nPeriodOfDay;					//0x04
	int32_t nTicks;							//0x08
	int32_t nIntensity;						//0x0C
	uint32_t dwInitTick;					//0x10
	int32_t unk0x14;						//0x14
	uint8_t nRed;							//0x18
	uint8_t nGreen;							//0x19
	uint8_t nBlue;							//0x1A
	uint8_t pad0x1B;						//0x1B
	float fCos;								//0x1C
	float fLast;							//0x20
	float fSin;								//0x24
	int32_t nTimeRate;						//0x28
	int32_t nTimeRateIndex;					//0x2C
	BOOL bEclipse;							//0x30
	int32_t nPrev;							//0x34
};

#pragma pack()

//D2Common.0x6FD8D8E0
struct D2DrlgEnvironment* __fastcall ENVIRONMENT_AllocDrlgEnvironment(void* pMemPool);
//D2Common.0x6FD8D970
void __fastcall ENVIRONMENT_UpdateLightIntensity(struct D2DrlgEnvironment* pEnvironment, int nLevelId, int nAct);
//D2Common.0x6FD8DAC0
void __fastcall ENVIRONMENT_UpdateLightColor(struct D2DrlgEnvironment* pEnvironment, int nAct);
//D2Common.6FD8DBE0
void __fastcall ENVIRONMENT_FreeDrlgEnvironment(void* pMemPool, struct D2DrlgEnvironment* pEnvironment);
//D2Common.0x6FD8DC00 (#10923)
D2COMMON_DLL_DECL BOOL __stdcall ENVIRONMENT_UpdatePeriodOfDay(struct D2DrlgAct* pAct, struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8DC70
void __fastcall ENVIRONMENT_UpdateTicks(struct D2DrlgEnvironment* pEnvironment, int nActNo);
//D2Common.0x6FD8DD60 (#10924)
D2COMMON_DLL_DECL BOOL __stdcall ENVIRONMENT_UpdateCycleIndex(struct D2DrlgAct* pAct, int nActNo);
//D2Common.0x6FD8DDD0 (#10927)
D2COMMON_DLL_DECL void __stdcall ENVIRONMENT_GetLightColorFromAct(struct D2DrlgAct* pAct, uint8_t* pRed, uint8_t* pGreen, uint8_t* pBlue);
//D2Common.0x6FD8DE00 (#10926)
D2COMMON_DLL_DECL int __stdcall ENVIRONMENT_GetIntensityFromAct(struct D2DrlgAct* pAct);
//D2Common.0x6FD8DE20 (#10933)
D2COMMON_DLL_DECL int __stdcall ENVIRONMENT_GetPeriodOfDayFromAct(struct D2DrlgAct* pAct, int* pBaseTime);
//D2Common.0x6FD8DE70 (#10928)
D2COMMON_DLL_DECL int __stdcall ENVIRONMENT_GetUnusedMember(struct D2DrlgAct* pAct);
//D2Common.0x6FD8DE90 (#10929)
D2COMMON_DLL_DECL void __stdcall ENVIRONMENT_NextEnvCycle(struct D2DrlgAct* pAct, struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8DF30 (#10930)
D2COMMON_DLL_DECL int __stdcall ENVIRONMENT_GetCycleIndexFromAct(struct D2DrlgAct* pAct);
//D2Common.0x6FD8DF40 (#10932)
D2COMMON_DLL_DECL void __stdcall ENVIRONMENT_InitializeEnvironment(struct D2DrlgAct* pAct, struct D2ActiveRoom* pRoom, int nIndex, int nTicks, BOOL bEclipse);
//D2Common.0x6FD8E080 (#10931)
D2COMMON_DLL_DECL void __stdcall ENVIRONMENT_GetCycleIndex_Ticks_EclipseFromAct(struct D2DrlgAct* pAct, int* pCycleIndex, int* pTicks, BOOL* pEclipse);
//D2Common.0x6FD8E0B0 (#10925)
D2COMMON_DLL_DECL void __stdcall ENVIRONMENT_GetStatistics(struct D2DrlgAct* pAct, float* pCos, float* pLast, float* pSin, int* a5);
//D2Common.0x6FD8E0F0 (#10934)
D2COMMON_DLL_DECL int __stdcall ENVIRONMENT_GetTimeRateFromAct(struct D2DrlgAct* pAct);
//D2Common.0x6FD8E100 (#10935)
D2COMMON_DLL_DECL void __stdcall ENVIRONMENT_SetNextTimeRate(struct D2DrlgAct* pAct, struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8E1B0 (#10936)
D2COMMON_DLL_DECL void __stdcall ENVIRONMENT_TaintedSunBegin(struct D2DrlgAct* pAct);
//D2Common.0x6FD8E1E0 (#10937)
D2COMMON_DLL_DECL void __stdcall ENVIRONMENT_TaintedSunEnd(struct D2DrlgAct* pAct);
