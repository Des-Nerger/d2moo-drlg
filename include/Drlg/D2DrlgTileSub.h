#pragma once

#include "CommonDefinitions.h"
#include "D2DrlgDrlg.h"
#include "D2DrlgDrlgGrid.h"
#include <DataTbls/LevelsTbls.h>


#pragma pack(1)


struct D2UnkOutdoor
{
	struct D2DrlgLevel* pLevel;			//0x00
	int32_t* field_4;					//0x04
	struct D2DrlgGrid* pGrid1;				//0x08
	struct D2DrlgGrid* pGrid2;				//0x0C
	int32_t nLevelPrestId;				//0x10
	int32_t field_14;					//0x14
	int32_t nLvlSubId;					//0x18
	unsigned int(* field_1C)(struct D2DrlgLevel* pLevel, int nX, int nY);						//0x1C
	BOOL(* field_20)(struct D2DrlgLevel* pLevel, int nX, int nY, int nId, int nOffset, char nFlags);						//0x20
	BOOL(* field_24)(struct D2DrlgLevel* pLevel, int nX, int nY, int a4, int a5, unsigned int a6);						//0x24
	int(* field_28)(struct D2DrlgLevel* pLevel, int nStyle, int a3);						//0x28
	void(* field_2C)(struct D2DrlgLevel* pLevel, int nX, int nY);						//0x2C
	void(* field_30)(struct D2DrlgLevel* pLevel, int nX, int nY);						//0x30
	void(* field_34)(struct D2DrlgLevel* pLevel, int nX, int nY, int nLevelPrestId, int nRand, BOOL a6);						//0x34
};

struct D2UnkOutdoor2
{
	struct D2DrlgRoom* pDrlgRoom;									//0x00
	struct D2DrlgOutdoorRoom* pOutdoorRooms[DRLG_MAX_WALL_LAYERS];	//0x04
	struct D2DrlgGrid* pWallsGrids[DRLG_MAX_WALL_LAYERS];			//0x14
	struct D2DrlgGrid* pFloorGrid;									//0x24
	int32_t field_28;											//0x28
	int32_t field_2C;											//0x28
	int32_t nSubWaypoint_Shrine;								//0x2C
	int32_t nSubTheme;											//0x30
	int32_t nSubThemePicked;									//0x34
};

struct D2UnkOutdoorStrc3
{
	int32_t nLevelId;						//0x00
	int32_t nExcludedLevel1;				//0x04
	int32_t nExcludedLevel2;				//0x08
	int32_t nRand;							//0x0C
	int32_t nNextRand;						//0x10
	int32_t nFlags;							//0x14
};

struct D2DrlgSubstGroup
{
	struct D2DrlgCoord tBox;
	int32_t field_10;
	int32_t field_14;
};


#pragma pack()


//D2Common.0x6FD8A460
void DRLGTILESUB_AddSecondaryBorder(struct D2UnkOutdoor* a1);
//D2Common.0x6FD8A750
BOOL DRLGTILESUB_TestReplaceSubPreset(int a1, int a2, struct D2UnkOutdoor* a3, struct D2DrlgSubstGroup* pSubstGroup, struct D2LvlSubTxt* pLvlSubTxtRecord);
//D2Common.0x6FD8A8E0
void DRLGTILESUB_ReplaceSubPreset(int a1, int a2, struct D2UnkOutdoor* a3, struct D2DrlgSubstGroup* pSubstGroup, struct D2LvlSubTxt* pLvlSubTxtRecord, int a6);
//D2Common.0x6FD8AA80
void sub_6FD8AA80(struct D2UnkOutdoor2* a1);
//D2Common.0x6FD8ACE0
void sub_6FD8ACE0(void* pMemPool, int nX, int nY, struct D2UnkOutdoor2* a4, struct D2DrlgSubstGroup* pSubstGroup, struct D2LvlSubTxt* pLvlSubTxtRecord, int a7);
//D2Common.0x6FD8B010
BOOL sub_6FD8B010(int a1, int a2, struct D2UnkOutdoor2* a3, struct D2DrlgSubstGroup* pSubstGroup, struct D2LvlSubTxt* pLvlSubTxtRecord);
//D2Common.0x6FD8B130
BOOL sub_6FD8B130(int a1, int a2, struct D2UnkOutdoor2* a3, struct D2DrlgSubstGroup* pSubstGroup, struct D2LvlSubTxt* pLvlSubTxtRecord);
//D2Common.0x6FD8B290
void DRLGTILESUB_DoSubstitutions(struct D2UnkOutdoor2* pOutdoorLevel, struct D2LvlSubTxt* pLvlSubTxtRecord);
//D2Common.0x6FD8B640
void DRLGTILESUB_InitializeDrlgFile(HD2ARCHIVE hArchive, struct D2LvlSubTxt* pLvlSubTxtRecord);
//D2Common.0x6FD8B770
void DRLGTILESUB_FreeDrlgFile(struct D2LvlSubTxt* pLvlSubTxtRecord);
//D2Common.0x6FD8B7E0
int DRLGTILESUB_PickSubThemes(struct D2DrlgRoom* pDrlgRoom, int nSubType, int nSubTheme);
