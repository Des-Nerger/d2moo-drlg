#include "D2DataTbls.h"

#include "D2Composit.h"
#include "D2Skills.h"
#include "Units/Units.h"



//D2Common.0x6FD729C0
void __cdecl DATATBLS_LoadPlrType_ModeTxt(HD2ARCHIVE hArchive)
{
	struct D2PlrModeTypeTxt* pPlrModeTypeTxt = NULL;
	struct D2PlrModeTypeTxt* pPlrType = NULL;
	struct D2PlrModeTypeTxt* pPlrMode = NULL;
	int nTypeRecords = 0;
	int nModeRecords = 0;

	struct D2BinField pTbl[] =
	{
		{ "name", TXTFIELD_ASCII, 31, 0, NULL },
		{ "token", TXTFIELD_RAW, 0, 32, NULL },
		{ "end", TXTFIELD_NONE, 0, 0, NULL }
	};

	pPlrType = (struct D2PlrModeTypeTxt*)DATATBLS_CompileTxt(hArchive, "plrtype", pTbl, &nTypeRecords, sizeof(struct D2PlrModeTypeTxt));
	pPlrMode = (struct D2PlrModeTypeTxt*)DATATBLS_CompileTxt(hArchive, "plrmode", pTbl, &nModeRecords, sizeof(struct D2PlrModeTypeTxt));

	sgptDataTables->pPlrModeDataTables.nPlrModeTypeTxtRecordCount = nModeRecords + nTypeRecords;

	pPlrModeTypeTxt = (struct D2PlrModeTypeTxt*)D2_ALLOC_POOL(nullptr, sizeof(struct D2PlrModeTypeTxt) * (nModeRecords + nTypeRecords));
	D2_ASSERT(pPlrModeTypeTxt);

	sgptDataTables->pPlrModeDataTables.pPlrModeTypeTxt = pPlrModeTypeTxt;
	sgptDataTables->pPlrModeDataTables.pPlayerType = pPlrModeTypeTxt;
	sgptDataTables->pPlrModeDataTables.pPlayerMode = pPlrModeTypeTxt + nTypeRecords;

	memcpy(sgptDataTables->pPlrModeDataTables.pPlayerType, pPlrType, sizeof(struct D2PlrModeTypeTxt) * nTypeRecords);
	memcpy(sgptDataTables->pPlrModeDataTables.pPlayerMode, pPlrMode, sizeof(struct D2PlrModeTypeTxt) * nModeRecords);

	DATATBLS_UnloadBin(pPlrType);
	DATATBLS_UnloadBin(pPlrMode);
}

//D2Common.0x6FD72B30
void __cdecl DATATBLS_LoadMonModeTxt(HD2ARCHIVE hArchive)
{
	struct D2BinField pTbl[] =
	{
		{ "name", TXTFIELD_ASCII, 31, 0, NULL },
		{ "token", TXTFIELD_RAW, 0, 32, NULL },
		{ "DT_Dir", TXTFIELD_UNKNOWN2, 0, 36, NULL },
		{ "NU_Dir", TXTFIELD_UNKNOWN2, 0, 37, NULL },
		{ "WL_Dir", TXTFIELD_UNKNOWN2, 0, 38, NULL },
		{ "GH_Dir", TXTFIELD_UNKNOWN2, 0, 39, NULL },
		{ "A1_Dir", TXTFIELD_UNKNOWN2, 0, 40, NULL },
		{ "A2_Dir", TXTFIELD_UNKNOWN2, 0, 41, NULL },
		{ "BL_Dir", TXTFIELD_UNKNOWN2, 0, 42, NULL },
		{ "SC_Dir", TXTFIELD_UNKNOWN2, 0, 43, NULL },
		{ "S1_Dir", TXTFIELD_UNKNOWN2, 0, 44, NULL },
		{ "S2_Dir", TXTFIELD_UNKNOWN2, 0, 45, NULL },
		{ "S3_Dir", TXTFIELD_UNKNOWN2, 0, 46, NULL },
		{ "S4_Dir", TXTFIELD_UNKNOWN2, 0, 47, NULL },
		{ "DD_Dir", TXTFIELD_UNKNOWN2, 0, 48, NULL },
		{ "KB_Dir", TXTFIELD_UNKNOWN2, 0, 49, NULL },
		{ "SQ_Dir", TXTFIELD_UNKNOWN2, 0, 50, NULL },
		{ "RN_Dir", TXTFIELD_UNKNOWN2, 0, 51, NULL },
		{ "end", TXTFIELD_NONE, 0, 0, NULL },
	};

	sgptDataTables->pMonModeDataTables.pMonModeTxt = (struct D2MonModeTxt*)DATATBLS_CompileTxt(hArchive, "monmode", pTbl, &sgptDataTables->pMonModeDataTables.nMonModeTxtRecordCount, sizeof(struct D2MonModeTxt));

	sgptDataTables->pMonModeDataTables.pMonMode[0] = sgptDataTables->pMonModeDataTables.pMonModeTxt;
	sgptDataTables->pMonModeDataTables.pMonMode[1] = sgptDataTables->pMonModeDataTables.pMonModeTxt;
}

//D2Common.0x6FD72E50
void __cdecl DATATBLS_LoadObjType_ModeTxt(HD2ARCHIVE hArchive)
{
	struct D2ObjModeTypeTxt* pObjModeTypeTxt = NULL;

	struct D2ObjModeTypeTxt* pObjType = NULL;
	struct D2ObjModeTypeTxt* pObjMode = NULL;
	int nTypeRecords = 0;
	int nModeRecords = 0;

	struct D2BinField pTbl[] =
	{
		{ "name", TXTFIELD_ASCII, 31, 0, NULL },
		{ "token", TXTFIELD_RAW, 0, 32, NULL },
		{ "end", TXTFIELD_NONE, 0, 0, NULL }
	};

	pObjType = (struct D2ObjModeTypeTxt*)DATATBLS_CompileTxt(hArchive, "objtype", pTbl, &nTypeRecords, sizeof(struct D2ObjModeTypeTxt));
	pObjMode = (struct D2ObjModeTypeTxt*)DATATBLS_CompileTxt(hArchive, "objmode", pTbl, &nModeRecords, sizeof(struct D2ObjModeTypeTxt));

	sgptDataTables->pObjModeDataTables.nObjModeTypeTxtRecordCount = nModeRecords + nTypeRecords;

	pObjModeTypeTxt = (struct D2ObjModeTypeTxt*)D2_ALLOC_POOL(nullptr, sizeof(struct D2ObjModeTypeTxt) * (nModeRecords + nTypeRecords));
	D2_ASSERT(pObjModeTypeTxt);

	sgptDataTables->pObjModeDataTables.pObjModeTypeTxt = pObjModeTypeTxt;
	sgptDataTables->pObjModeDataTables.pObjType = pObjModeTypeTxt;
	sgptDataTables->pObjModeDataTables.pObjMode = (struct D2ObjModeTypeTxt*)((char*)pObjModeTypeTxt + sizeof(struct D2ObjModeTypeTxt) * nTypeRecords);

	memcpy(sgptDataTables->pObjModeDataTables.pObjType, pObjType, sizeof(struct D2ObjModeTypeTxt) * nTypeRecords);
	memcpy(sgptDataTables->pObjModeDataTables.pObjMode, pObjMode, sizeof(struct D2ObjModeTypeTxt) * nModeRecords);
	DATATBLS_UnloadBin(pObjType);
	DATATBLS_UnloadBin(pObjMode);
}

//D2Common.0x6FD72FC0
void __cdecl DATATBLS_LoadCompositTxt(HD2ARCHIVE hArchive)
{
	struct D2BinField pTbl[] =
	{
		{ "name", TXTFIELD_ASCII, 31, 0, NULL },
		{ "token", TXTFIELD_RAW, 0, 32, NULL },
		{ "end", TXTFIELD_NONE, 0, 0, NULL }
	};

	sgptDataTables->pCompositTxt = (struct D2CompositTxt*)DATATBLS_CompileTxt(hArchive, "composit", pTbl, NULL, sizeof(struct D2CompositTxt));
}

//D2Common.0x6FD73040
void __cdecl DATATBLS_LoadArmTypeTxt(HD2ARCHIVE hArchive)
{
	struct D2BinField pTbl[] =
	{
		{ "name", TXTFIELD_ASCII, 31, 0, NULL },
		{ "token", TXTFIELD_RAW, 0, 32, NULL },
		{ "end", TXTFIELD_NONE, 0, 0, NULL }
	};

	sgptDataTables->pArmTypeTxt = (struct D2ArmTypeTxt*)DATATBLS_CompileTxt(hArchive, "armtype", pTbl, NULL, sizeof(struct D2ArmTypeTxt));
}

//D2Common.0x6FD730C0
void __cdecl DATATBLS_UnloadPlrMode_Type_MonMode_ObjMode_Type_Composit_ArmtypeTxt()
{
	if (sgptDataTables->pPlrModeDataTables.pPlrModeTypeTxt)
	{
		D2_FREE_POOL(nullptr, sgptDataTables->pPlrModeDataTables.pPlrModeTypeTxt);
		sgptDataTables->pPlrModeDataTables.pPlrModeTypeTxt = NULL;
	}

	if (sgptDataTables->pMonModeDataTables.pMonModeTxt)
	{
		DATATBLS_UnloadBin(sgptDataTables->pMonModeDataTables.pMonModeTxt);
		sgptDataTables->pMonModeDataTables.pMonModeTxt = NULL;
	}

	if (sgptDataTables->pObjModeDataTables.pObjModeTypeTxt)
	{
		D2_FREE_POOL(nullptr, sgptDataTables->pObjModeDataTables.pObjModeTypeTxt);
		sgptDataTables->pObjModeDataTables.pObjModeTypeTxt = NULL;
	}

	if (sgptDataTables->pCompositTxt)
	{
		DATATBLS_UnloadBin(sgptDataTables->pCompositTxt);
		sgptDataTables->pCompositTxt = NULL;
	}

	if (sgptDataTables->pArmTypeTxt)
	{
		DATATBLS_UnloadBin(sgptDataTables->pArmTypeTxt);
		sgptDataTables->pArmTypeTxt = NULL;
	}
}

//D2Common.0x6FD73150 (#10643)
struct D2PlrModeDataTbl* __cdecl DATATBLS_GetPlrMode_TypeDataTables()
{
	return &sgptDataTables->pPlrModeDataTables;
}

//D2Common.0x6FD73160 (#10644)
struct D2MonModeDataTbl* __cdecl DATATBLS_GetMonModeDataTables()
{
	return &sgptDataTables->pMonModeDataTables;
}

//D2Common.0x6FD73170 (#10645)
struct D2ObjModeDataTbl* __cdecl DATATBLS_GetObjMode_TypeDataTables()
{
	return &sgptDataTables->pObjModeDataTables;
}

//D2Common.0x6FD73180 (#10646)
struct D2PlrModeTypeTxt* __cdecl DATATBLS_GetPlrModeTypeTxtRecord(int nIndex, int bGetMode)
{
	if (nIndex >= sgptDataTables->pPlrModeDataTables.nPlrModeTypeTxtRecordCount)
	{
		return NULL;
	}

	D2_ASSERT(sgptDataTables->pPlrModeDataTables.pPlrModeTypeTxt);

	if (bGetMode)
	{
		if (bGetMode == 1)
		{
			D2_ASSERT(&sgptDataTables->pPlrModeDataTables.pPlayerMode[nIndex]);
			return &sgptDataTables->pPlrModeDataTables.pPlayerMode[nIndex];
		}
		return NULL;
	}

	D2_ASSERT(&sgptDataTables->pPlrModeDataTables.pPlayerType[nIndex]);

	return &sgptDataTables->pPlrModeDataTables.pPlayerType[nIndex];
}

//D2Common.0x6FD73230 (#10647)
struct D2MonModeTxt* __cdecl DATATBLS_GetMonModeTxtRecord(int nIndex, int bGetMode)
{
	if (nIndex >= sgptDataTables->pMonModeDataTables.nMonModeTxtRecordCount)
	{
		return NULL;
	}

	if (bGetMode)
	{
		if (bGetMode == 1)
		{
			D2_ASSERT(&sgptDataTables->pMonModeDataTables.pMonMode[1][nIndex]);
			return &sgptDataTables->pMonModeDataTables.pMonMode[1][nIndex];
		}
		return NULL;
	}

	D2_ASSERT(&sgptDataTables->pMonModeDataTables.pMonMode[0][nIndex]);

	return &sgptDataTables->pMonModeDataTables.pMonMode[0][nIndex];
}

//D2Common.0x6FD732B0 (#10648)
struct D2ObjModeTypeTxt* __cdecl DATATBLS_GetObjModeTypeTxtRecord(int nIndex, int bGetMode)
{
	if (nIndex >= sgptDataTables->pObjModeDataTables.nObjModeTypeTxtRecordCount)
	{
		return NULL;
	}

	if (bGetMode)
	{
		if (bGetMode == 1)
		{
			D2_ASSERT(&sgptDataTables->pObjModeDataTables.pObjMode[nIndex]);
			return &sgptDataTables->pObjModeDataTables.pObjMode[nIndex];
		}
		return NULL;
	}

	D2_ASSERT(&sgptDataTables->pObjModeDataTables.pObjType[nIndex]);
	return &sgptDataTables->pObjModeDataTables.pObjType[nIndex];
}

//D2Common.0x6FD73330 (#10649)
struct D2CompositTxt* __cdecl DATATBLS_GetCompositTxtRecord(int nComposit)
{
	D2_ASSERT(&sgptDataTables->pCompositTxt[nComposit]);

	return &sgptDataTables->pCompositTxt[nComposit];
}

//D2Common.0x6FD73370 (#10650)
struct D2ArmTypeTxt* __cdecl DATATBLS_GetArmTypeTxtRecord(int nId)
{
	D2_ASSERT(&sgptDataTables->pArmTypeTxt[nId]);
	return &sgptDataTables->pArmTypeTxt[nId];
}
