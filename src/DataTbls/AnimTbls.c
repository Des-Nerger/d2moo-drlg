#include "D2DataTbls.h"

#include "D2Composit.h"
#include "Units/Units.h"

#include <Archive.h>

//D2Common.0x6FD473C0
struct D2AnimDataTable* __cdecl DATATBLS_LoadAnimDataD2(HD2ARCHIVE hArchive)
{
	struct D2AnimDataTable* pAnimDataTable = D2_CALLOC_STRC_POOL(nullptr, struct D2AnimDataTable);

	char szPath[MAX_PATH] = {};
	wsprintfA(szPath, "%s\\AnimData.d2", "DATA\\GLOBAL");
	pAnimDataTable->pBinaryData = ARCHIVE_ALLOC_BUFFER_AND_READ_FILE_TO_IT(hArchive, szPath, nullptr);
;
	struct D2AnimDataBucket* pBucketBinaryData = (struct D2AnimDataBucket*)pAnimDataTable->pBinaryData;
	for (int i = 0; i < 256; ++i)
	{
		pAnimDataTable->pHashTableBucket[i] = pBucketBinaryData;
		const size_t nBucketSize = sizeof(pBucketBinaryData->nbEntries) + sizeof(struct D2AnimDataRecord) * pBucketBinaryData->nbEntries;
		pBucketBinaryData = (struct D2AnimDataBucket*)(((char*)pBucketBinaryData) + nBucketSize);
	}

	pAnimDataTable->tDefaultRecord.dwFrames = 2048;
	pAnimDataTable->tDefaultRecord.dwAnimSpeed = 256;

	return pAnimDataTable;
}

//D2Common.0x6FD47460
void __cdecl DATATBLS_UnloadAnimDataD2(struct D2AnimDataTable* pAnimData)
{
	if (pAnimData)
	{
		D2_FREE(pAnimData->pBinaryData);
		D2_FREE_POOL(nullptr, pAnimData);
	}
}

static void ToUpperCase(char* str)
{
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'z')
		{
			*str -= ' ';
		}
		++str;
	}
}

static uint8_t SimpleStringHash(char* str)
{
	uint8_t nHash = 0;
	while (*str)
	{
		nHash += *str;
		++str;
	}
	return nHash;
}

static struct D2AnimDataRecord* DATATBLS_GetAnimDataRecordFromPath(char* szPath)
{
	ToUpperCase(szPath);
	const uint8_t nHash = SimpleStringHash(szPath);

	struct D2AnimDataTable* pAnimData = DATATBLS_GetAnimData();

	struct D2AnimDataBucket* pAnimDataBucket = pAnimData->pHashTableBucket[nHash];
	for (int i = 0; i < pAnimDataBucket->nbEntries; i++)
	{
		struct D2AnimDataRecord* pBucketEntry = &pAnimDataBucket->aEntries[i];
		D2_ASSERT(strlen(szPath) <= 8); // This one is useless. Remains of a more generic function?
		D2_ASSERT(strlen(pBucketEntry->szAnimDataName) <= 8);
		// Note: Only works if strings are completly padded after null terminator.
		if (0 == memcmp(szPath, pBucketEntry->szAnimDataName, 8))
		{
			return pBucketEntry;
		}
	}
	return nullptr;
}

//D2Common.0x6FD474A0
const struct D2AnimDataRecord* __cdecl DATATBLS_GetAnimDataRecord(struct D2Unit* pUnit, int nClassId, int nMode, int nUnitType, struct D2Inventory* pInventory)
{
	int nWeaponClassCode = 0;
	char szPath[8] = {};
	D2Common_10884_COMPOSIT_unk(pUnit, nClassId, nMode, nUnitType, pInventory, szPath, &nWeaponClassCode, FALSE, 1);
	struct D2AnimDataRecord* pFound = DATATBLS_GetAnimDataRecordFromPath(szPath);
	if (pFound)
	{
		return pFound;
	}
	else
	{
		return &DATATBLS_GetAnimData()->tDefaultRecord;
	}
}

//D2Common.0x6FD475D0 (#10640)
void __cdecl DATATBLS_UnitAnimInfoDebugSet(struct D2Unit* pUnit, int nAnimSpeed)
{
	int nWeaponClassCode = 0;
	char szPath[8] = {};
	D2Common_10885_COMPOSIT_unk(pUnit, szPath, &nWeaponClassCode, 0, 1, pUnit->pInventory, -1);
	struct D2AnimDataRecord* pRecord = DATATBLS_GetAnimDataRecordFromPath(szPath);
	if (pRecord)
	{
		pRecord->dwAnimSpeed = nAnimSpeed;
	}
	FOG_DisplayHalt("DataTablesUnitAnimInfoDebugSet", __FILE__, __LINE__);
	exit(-1);
}

//D2Common.0x6FD47700 (#10641)
BOOL __cdecl DATATBLS_GetAnimDataInfo(char* szPath, int* pOutLength, int* pOutAnimSpeed, int* pOutFirstFrameTagged)
{
	struct D2AnimDataRecord* pRecord = DATATBLS_GetAnimDataRecordFromPath(szPath);
	if (pRecord)
	{
		*pOutLength = pRecord->dwFrames;
		*pOutAnimSpeed = pRecord->dwAnimSpeed;

		for (uint32_t i = 0; i < pRecord->dwFrames; ++i)
		{
			if (pRecord->pFrameFlags[i] || i >= D2AnimDataRecord_MAX_FRAME_FLAGS)
			{
				*pOutFirstFrameTagged = i;
				return TRUE;
			}
		}

		*pOutFirstFrameTagged = 0;
		return TRUE;
	}

	const struct D2AnimDataRecord* pDefaultRecord = &DATATBLS_GetAnimData()->tDefaultRecord;
	*pOutLength = pDefaultRecord->dwFrames;
	*pOutAnimSpeed = pDefaultRecord->dwAnimSpeed;
	*pOutFirstFrameTagged = *pOutLength;
	return FALSE;
}
