#pragma once

#include "CommonDefinitions.h"
#include "D2DrlgDrlg.h"
#include "D2DrlgDrlgGrid.h"
#include <Path/Path.h>
#include <Archive.h>

struct D2LvlPrestTxt;

#pragma pack(1)

enum D2DrlgPresetRoomFlags
{
	DRLGPRESETROOMFLAG_NONE = 0,
	DRLGPRESETROOMFLAG_SINGLE_ROOM = 1 << 0,
	DRLGPRESETROOMFLAG_HAS_MAP_DS1 = 1 << 1, // needs confirmation
};

struct D2LevelFileList
{
	char szPath[D2_MAX_PATH];			//0x00
	long nRefCount;						//0x104
	struct D2DrlgFile* pFile;				//0x108
	struct D2LevelFileList* pNext;				//0x10C
};

struct D2PresetUnit
{
	int32_t nUnitType;						//0x00
	int32_t nIndex;							//0x04 see D2Common.#11278
	int32_t nMode;							//0x08
	int32_t nXpos;							//0x0C
	int32_t nYpos;							//0x10
	BOOL bSpawned;							//0x14 
	struct D2MapAI* pMapAI;					//0x18
	struct D2PresetUnit* pNext;				//0x1C
};

struct D2DrlgMap
{
	int32_t nLevelPrest;					//0x00
	int32_t nPickedFile;					//0x04
	struct D2LvlPrestTxt* pLvlPrestTxtRecord;		//0x08
	struct D2DrlgFile* pFile;					//0x0C
	struct D2DrlgCoord pDrlgCoord;				//0x10
	BOOL bHasInfo;							//0x20
	struct D2DrlgGrid pMapGrid;				//0x24
	struct D2PresetUnit* pPresetUnit;			//0x38
	BOOL bInited;							//0x3C
	int32_t nPops;							//0x40
	int32_t* pPopsIndex;					//0x44
	int32_t* pPopsSubIndex;					//0x48
	int32_t* pPopsOrientation;				//0x4C
	struct D2DrlgCoord* pPopsLocation;			//0x50
	struct D2DrlgMap* pNext;					//0x54
};

struct D2DrlgPresetRoom
{
	int32_t nLevelPrest;						//0x00
	int32_t nPickedFile;						//0x04
	struct D2DrlgMap* pMap;					//0x08
	union
	{
		struct
		{
			uint8_t nFlags;					//0x0C
			uint8_t unk0x0D[3];				//0x0D
		};
		uint32_t dwFlags;						//0x0C
	};
	struct D2DrlgGrid pWallGrid[4];			//0x10
	struct D2DrlgGrid pTileTypeGrid[4];		//0x60 aka pOrientationGrid
	struct D2DrlgGrid pFloorGrid[2];			//0xB0
	struct D2DrlgGrid pCellGrid;				//0xD8
	struct D2DrlgGrid* pMazeGrid;				//0xEC
	struct D2Coord* pTombStoneTiles;			//0xF0
	int32_t nTombStoneTiles;					//0xF4
};

#pragma pack()

//Helper function
static inline bool DRLGMAZE_HasMapDS1(struct D2DrlgRoom* pDrlgRoom)
{
	return pDrlgRoom->pMaze->nFlags & DRLGPRESETROOMFLAG_HAS_MAP_DS1;
}

//D2Common.0x6FD859A0 (#11222)
D2COMMON_DLL_DECL int DRLGPRESET_CountPresetObjectsByAct(uint8_t nAct);
//D2Common.0x6FD859E0 (#11223)
D2COMMON_DLL_DECL int DRLGPRESET_GetObjectIndexFromObjPreset(uint8_t nAct, int nUnitId);
//D2Common.0x6FD85A10
void DRLGPRESET_ParseDS1File(struct D2DrlgFile* pDrlgFile, HD2ARCHIVE hArchive, const char* szFileName);
//D2Common.0x6FD86050
void DRLGPRESET_LoadDrlgFile(struct D2DrlgFile** ppDrlgFile, HD2ARCHIVE hArchive, const char* szFile);
//D2Common.0x6FD86190
void DRLGPRESET_FreeDrlgFile(struct D2DrlgFile** ppDrlgFile);
//D2Common.0x6FD86310
struct D2PresetUnit* DRLGPRESET_CopyPresetUnit(void* pMemPool, struct D2PresetUnit* pPresetUnit, int nX, int nY);
//D2Common.0x6FD86430
void DRLGPRESET_FreePresetUnit(void* pMemPool, struct D2PresetUnit* pPresetUnit);
//D2Common.0x6FD86480 (#10020)
D2COMMON_DLL_DECL struct D2MapAI* DRLGPRESET_CreateCopyOfMapAI(void* pMemPool, struct D2MapAI* pMapAI);
//D2Common.0x6FD864F0 (#10021)
D2COMMON_DLL_DECL struct D2MapAI* DRLGPRESET_ChangeMapAI(struct D2MapAI** ppMapAI1, struct D2MapAI** ppMapAI2);
//D2Common.0x6FD86500 (#10022)
D2COMMON_DLL_DECL void DRLGPRESET_FreeMapAI(void* pMemPool, struct D2MapAI* pMapAI);
//D2Common.0x6FD86540
void DRLGPRESET_AddPresetUnitToDrlgMap(void* pMemPool, struct D2DrlgMap* pDrlgMap, struct D2Seed* pSeed);
//D2Common.0x6FD867A0
void DRLGPRESET_SpawnHardcodedPresetUnits(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD86AC0
void DRLGPRESET_AddPresetRiverObjects(struct D2DrlgMap* pDrlgMap, void* pMemPool, int nOffsetX, struct D2DrlgGrid* pDrlgGrid);
//D2Common.0x6FD86C80
void DRLGPRESET_FreePresetRoomData(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD86CE0
void DRLGPRESET_FreeDrlgGrids(void* pMemPool, struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD86D60
void DRLGPRESET_FreeDrlgGridsFromPresetRoom(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD86D80
void DRLGPRESET_AllocPresetRoomData(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD86DC0
struct D2DrlgRoom* DRLGPRESET_InitPresetRoomData(struct D2DrlgLevel* pLevel, struct D2DrlgMap* pDrlgMap, struct D2DrlgCoord* pDrlgCoord, uint32_t dwDT1Mask, int dwRoomFlags, int dwPresetFlags, struct D2DrlgGrid* a7);
//D2Common.0x6FD86E50
void DRLGPRESET_InitPresetRoomGrids(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD870F0
void DRLGPRESET_GetTombStoneTileCoords(struct D2DrlgRoom* pDrlgRoom, struct D2Coord** ppTombStoneTiles, int* pnTombStoneTiles);
//D2Common.0x6FD87130
void DRLGPRESET_AddPresetRoomMapTiles(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD87560
struct D2DrlgRoom* DRLGPRESET_BuildArea(struct D2DrlgLevel* pLevel, struct D2DrlgMap* pDrlgMap, int nFlags, BOOL bSingleRoom);
//D2Common.0x6FD87760
void DRLGPRESET_BuildPresetArea(struct D2DrlgLevel* pLevel, struct D2DrlgGrid* pDrlgGrid, int nFlags, struct D2DrlgMap* pDrlgMap, BOOL bSingleRoom);
//D2Common.0x6FD87E10
void DRLGPRESET_SetPickedFileInDrlgMap(struct D2DrlgMap* pDrlgMap, int nPickedFile);
//D2Common.0x6FD87E20
struct D2DrlgMap* DRLGPRESET_AllocDrlgMap(struct D2DrlgLevel* pLevel, int nLvlPrestId, struct D2DrlgCoord* pDrlgCoord, struct D2Seed* pSeed);
//D2Common.0x6FD87F00
int DRLGPRESET_GetSizeX(int nLvlPrestId);
//D2Common.0x6FD87F10
int DRLGPRESET_GetSizeY(int nLvlPrestId);
//D2Common.0x6FD87F20
void DRLGPRESET_FreeDrlgMap(void* pMemPool, struct D2DrlgMap* pDrlgMap);
//D2Common.0x6FD881A0 (#10008)
D2COMMON_DLL_DECL int DRLGPRESET_GetLevelPrestIdFromRoomEx(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD881B0 (#10009)
D2COMMON_DLL_DECL char* DRLGPRESET_GetPickedLevelPrestFilePathFromRoomEx(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD881D0
void DRLGPRESET_UpdatePops(struct D2DrlgRoom* pDrlgRoom, int nX, int nY, BOOL bOtherRoom);
//D2Common.0x6FD88450
void DRLGPRESET_TogglePopsVisibility(struct D2DrlgRoom* pDrlgRoom, int nPopSubIndex, struct D2DrlgCoord* pDrlgCoord, int nTick, BOOL nCellFlags);
//D2Common.0x6FD88610
void DRLGPRESET_InitLevelData(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD886F0
void DRLGPRESET_GenerateLevel(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD88810
void DRLGPRESET_ResetDrlgMap(struct D2DrlgLevel* pLevel, BOOL bKeepPreset);
//D2Common.0x6FD88850
int DRLGPRESET_MapTileType(int nId);

// D2Common.0x6FDEA700
extern struct D2LevelFileList* gpLevelFilesList_6FDEA700;
