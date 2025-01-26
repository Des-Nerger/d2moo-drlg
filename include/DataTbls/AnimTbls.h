#pragma once 

#include <D2Common.h>
#include <D2BasicTypes.h>
#include <Archive.h>

#pragma pack(1)

enum : int { D2AnimDataRecord_MAX_FRAME_FLAGS = 144 };

struct D2AnimDataRecord
{
	char szAnimDataName[8];						//0x00
	uint32_t dwFrames;							//0x08
	int32_t dwAnimSpeed;						//0x0C
	uint8_t pFrameFlags[D2AnimDataRecord_MAX_FRAME_FLAGS];		//0x10
};

struct D2AnimDataBucket
{
	int32_t nbEntries;
	struct D2AnimDataRecord aEntries[]; // Dynamically sized
};

struct D2AnimDataTable
{
	void* pBinaryData;							//0x00
	struct D2AnimDataBucket* pHashTableBucket[256];//0x04
	struct D2AnimDataRecord tDefaultRecord;		//0x404
};

struct D2Unit;
struct D2Inventory;

#pragma pack()

//D2Common.0x6FD473C0
struct D2AnimDataTable* __cdecl DATATBLS_LoadAnimDataD2(HD2ARCHIVE hArchive);
//D2Common.0x6FD47460
void __cdecl DATATBLS_UnloadAnimDataD2(struct D2AnimDataTable* pAnimData);
//D2Common.0x6FD474A0
const struct D2AnimDataRecord* __cdecl DATATBLS_GetAnimDataRecord(struct D2Unit* pUnit, int nClassId, int nMode, int nUnitType, struct D2Inventory* pInventory);
//D2Common.0x6FD475D0 (#10640)
D2COMMON_DLL_DECL void __cdecl DATATBLS_UnitAnimInfoDebugSet(struct D2Unit* pUnit, int nAnimSpeed);
//D2Common.0x6FD47700 (#10641)
D2COMMON_DLL_DECL BOOL __cdecl DATATBLS_GetAnimDataInfo(char* szPath, int* pOutLength, int* pOutAnimSpeed, int* pOutFirstFrameTagged);


