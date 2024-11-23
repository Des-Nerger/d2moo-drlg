#pragma once

#include "CommonDefinitions.h"

struct D2Drlg;
struct D2ActiveRoom;
struct D2DrlgRoom;
struct D2DrlgLevel;

#pragma pack(1)

struct D2MazeLevelId
{
	int32_t nLevelPrestId1;					//0x00
	int32_t nLevelPrestId2;					//0x04
	int32_t nPickedFile;					//0x08
	int32_t nDirection;						//0x0C
};

#pragma pack()

//D2Common.0x6FD78E50
struct D2DrlgRoom* sub_6FD78E50(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD78F70
void DRLGMAZE_PickRoomPreset(struct D2DrlgRoom* pDrlgRoom, BOOL bResetFlag);
//D2Common.0x6FD79240
struct D2DrlgRoom* sub_6FD79240(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD79360
struct D2DrlgRoom* sub_6FD79360(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD79480
void DRLGMAZE_InitLevelData(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD794A0
void DRLGMAZE_GenerateLevel(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD79E10
void DRLGMAZE_SetPickedFileAndPresetId(struct D2DrlgRoom* pDrlgRoom, int nLevelPrest, int nPickedFile, BOOL bResetFlag);
//D2Commo.0x6FD79E40
struct D2DrlgRoom* DRLGMAZE_ReplaceRoomPreset(struct D2DrlgLevel* pLevel, int nLevelPrestId1, int nLevelPrestId2, int nPickedFile, BOOL bResetFlag);
//D2Common.0x6FD79EA0
struct D2DrlgRoom* DRLGMAZE_AddAdjacentMazeRoom(struct D2DrlgRoom* pDrlgRoom, int nDirection, int bMergeRooms);
//D2Common.0x6FD7A110
void DRLGMAZE_InitBasicMazeLayout(struct D2DrlgLevel* pLevel, int nRoomsPerDirection);
//D2Common.0x6FD7A340
BOOL DRLGMAZE_LinkMazeRooms(struct D2DrlgRoom* pDrlgRoom1, struct D2DrlgRoom* pDrlgRoom2, int nDirection);
//D2Common.0x6FD7A450
void DRLGMAZE_MergeMazeRooms(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD7A570
struct D2DrlgRoom* DRLGMAZE_GetRandomRoomExFromLevel(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7A5D0
void DRLGMAZE_BuildBasicMaze(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7A830
void DRLGMAZE_PlaceAct5LavaPresets(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7A9B0
void DRLGMAZE_FillBlankMazeSpaces(struct D2DrlgLevel* pLevel, int nLevelPrest, struct D2DrlgRoom* pIgnoreRoomEx);
//D2Common.0x6FD7AAC0
void DRLGMAZE_PlaceAct2TombPrev_Act5BaalPrev(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7ABC0
void DRLGMAZE_PlaceArcaneSanctuary(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7AFD0
struct D2DrlgRoom* DRLGMAZE_PlaceAdjacentPresetRoom(struct D2DrlgRoom* pParentRoomEx, int nDirection, int bMergeRooms);
//D2Common.0x6FD7B230
void DRLGMAZE_ScanReplaceSpecialPreset(struct D2DrlgLevel* pLevel, const struct D2MazeLevelId* pMazeInit, int* pRand);
//D2Common.0x6FD7B330
void DRLGMAZE_ScanReplaceSpecialAct2SewersPresets(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7B660
void DRLGMAZE_AddSpecialPreset(struct D2DrlgLevel* pLevel, int nDirection, int nLvlPrestId, int nFile);
//D2Common.0x6FD7B710
BOOL DRLGMAZE_CheckIfMayPlaceAdjacentPresetRoom(struct D2DrlgRoom* pDrlgRoom, int nDirection);
//D2Common.0x6FD7B8B0
void DRLGMAZE_PlaceAct2TombStuff(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7BC40
struct D2DrlgRoom* DRLGMAZE_InitRoomFixedPreset(struct D2DrlgRoom* pDrlgRoom, int nDirection, int nLvlPrestId, int nFile, int bUseInitPreset);
//D2Common.0x6FD7BCD0
void DRLGMAZE_PlaceAct2LairStuff(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7BE60
void DRLGMAZE_PlaceAct3DungeonStuff(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7C000
void DRLGMAZE_PlaceAct3SewerStuff(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7C1A0
void DRLGMAZE_PlaceAct3MephistoStuff(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7C380
void DRLGMAZE_PlaceAct5TempleStuff(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7C500
void DRLGMAZE_PlaceAct5BaalStuff(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7C660
void DRLGMAZE_PlaceAct1Barracks(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7CA20
void DRLGMAZE_SetRoomSize(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD7CA40
void DRLGMAZE_PlaceAct4Lava(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7CCB0
void DRLGMAZE_PlaceAct5IceStuff(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7CEA0
void DRLGMAZE_RollAct_1_2_3_BasicPresets(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7D130
void DRLGMAZE_RollBasicPresets(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7D3D0
void DRLGMAZE_ResetMazeRecord(struct D2DrlgLevel* pLevel, BOOL bKeepMazeRecord);
