#pragma once

#include "CommonDefinitions.h"
#include <Drlg/D2DrlgDrlg.h>

#pragma pack(1)


#pragma pack()

//D2Common.0x6FD8B8A0 (#10038)
D2COMMON_DLL_DECL struct D2DrlgAct* DUNGEON_AllocAct(uint8_t nActNo, uint32_t nInitSeed, BOOL bClient, struct D2Game* pGame, uint8_t nDifficulty, void* pMemPool, int nTownLevelId, AUTOMAPFN pfAutoMap, TOWNAUTOMAPFN pfTownAutoMap);
//D2Common.0x6FD8B950 (#10039)
D2COMMON_DLL_DECL void DUNGEON_FreeAct(struct D2DrlgAct* pAct);
//D2Common.0x6FD8B9D0
void* DUNGEON_GetMemPoolFromAct(struct D2DrlgAct* pAct);
//D2Common.0x6FD8B9E0 (#10026)
D2COMMON_DLL_DECL void DUNGEON_ToggleRoomTilesEnableFlag(struct D2ActiveRoom* pRoom, BOOL bEnabled);
//D2Common.0x6FD8BA20 (#10027)
D2COMMON_DLL_DECL struct D2Unit* DUNGEON_GetWarpTileFromRoomAndSourceLevelId(struct D2ActiveRoom* pRoom, int nSourceLevel, struct D2LvlWarpTxt** ppLvlWarpTxtRecord);
//D2Common.0x6FD8BAB0 (#10028)
D2COMMON_DLL_DECL struct D2LvlWarpTxt* DUNGEON_GetLvlWarpTxtRecordFromRoomAndUnit(struct D2ActiveRoom* pRoom, struct D2Unit* pUnit);
//D2Common.0x6FD8BAF0 (#10030)
D2COMMON_DLL_DECL struct D2DrlgTileData* DUNGEON_GetFloorTilesFromRoom(struct D2ActiveRoom* pRoom, int* pFloorCount);
//D2Common.0x6FD8BB20 (#10031)
D2COMMON_DLL_DECL struct D2DrlgTileData* DUNGEON_GetWallTilesFromRoom(struct D2ActiveRoom* pRoom, int* pWallCount);
//D2Common.0x6FD8BB60 (#10032)
D2COMMON_DLL_DECL struct D2DrlgTileData* DUNGEON_GetRoofTilesFromRoom(struct D2ActiveRoom* pRoom, int* pRoofCount);
//D2Common.0x6FD8BBA0 (#10033)
D2COMMON_DLL_DECL struct D2DrlgTileData* DUNGEON_GetTileDataFromAct(struct D2DrlgAct* pAct);
//D2Common.0x6FD8BBB0 (#10034)
D2COMMON_DLL_DECL void DUNGEON_GetRoomCoordinates(struct D2ActiveRoom* pRoom, struct D2DrlgCoords* pCoords);
//D2Common.0x6FD8BC10 (#10035)
D2COMMON_DLL_DECL void DUNGEON_GetAdjacentRoomsListFromRoom(struct D2ActiveRoom* pRoom, struct D2ActiveRoom*** pppRoomList, int* pNumRooms);
//D2Common.0x6FD8BC50
struct D2ActiveRoom* DUNGEON_AllocRoom(struct D2DrlgAct* pAct, struct D2DrlgRoom* pDrlgRoom, struct D2DrlgCoords* pDrlgCoords, struct D2DrlgRoomTiles* pRoomTiles, int nLowSeed, uint32_t dwFlags);
//D2Common.0x6FD8BD90 (#10040)
D2COMMON_DLL_DECL BOOL DUNGEON_DoRoomsTouchOrOverlap(struct D2ActiveRoom* ptFirst, struct D2ActiveRoom* ptSecond);
//D2Common.0x6FD8BE30 (#10043)
D2COMMON_DLL_DECL BOOL DUNGEON_AreTileCoordinatesInsideRoom(struct D2ActiveRoom* pRoom, int nX, int nY);
//D2Common.0x6FD8BE90 (#10048)
D2COMMON_DLL_DECL int DUNGEON_CheckRoomsOverlapping_BROKEN(struct D2ActiveRoom* pPrimary, struct D2ActiveRoom* pSecondary);
//D2Commmon.0x6FD8BF00 (#10051)
D2COMMON_DLL_DECL struct D2ActiveRoom* DUNGEON_FindRoomByTileCoordinates(struct D2DrlgAct* pAct, int nX, int nY);
//D2Common.0x6FD8BF50 (#10050)
D2COMMON_DLL_DECL struct D2ActiveRoom* DUNGEON_GetAdjacentRoomByTileCoordinates(struct D2ActiveRoom* pRoom, int nX, int nY);
//D2Common.0x6FD8BFF0 (#10049)
D2COMMON_DLL_DECL void DUNGEON_CallRoomCallback(struct D2ActiveRoom* pRoom, ROOMCALLBACKFN pfnRoomCallback, void* pArgs);
//D2Common.0x6FD8C080 (#10052)
D2COMMON_DLL_DECL void D2Common_10052(struct D2ActiveRoom* pRoom, RECT* pRect);
//D2Common.0x6FD8C170 (#10053)
D2COMMON_DLL_DECL void DUNGEON_GetSubtileRect(struct D2ActiveRoom* pRoom, RECT* pRect);
//D2Common.0x6FD8C210 (#10054)
D2COMMON_DLL_DECL void DUNGEON_GetRGB_IntensityFromRoom(struct D2ActiveRoom* pRoom, uint8_t* pIntensity, uint8_t* pRed, uint8_t* pGreen, uint8_t* pBlue);
//D2Common.0x6FD8C240 (#10041)
D2COMMON_DLL_DECL struct D2ActiveRoom* DUNGEON_FindRoomBySubtileCoordinates(struct D2DrlgAct* pAct, int nX, int nY);
//D2Common.0x6FD8C290
BOOL DUNGEON_AreSubtileCoordinatesInsideRoom(struct D2DrlgCoords* pDrlgCoords, int nX, int nY);
//D2Common.0x6FD8C2F0 (#10046)
D2COMMON_DLL_DECL struct D2ActiveRoom* DUNGEON_FindActSpawnLocation(struct D2DrlgAct* pAct, int nLevelId, int nTileIndex, int* pX, int* pY);
//D2Common.0x6FD8C340 (#10045)
D2COMMON_DLL_DECL struct D2ActiveRoom* DUNGEON_FindActSpawnLocationEx(struct D2DrlgAct* pAct, int nLevelId, int nTileIndex, int* pX, int* pY, int nUnitSize);
//D2Common.0x6FD8C4A0 (#10029)
D2COMMON_DLL_DECL struct D2Unit* DUNGEON_GetFirstUnitInRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C4E0 (#10100)
D2COMMON_DLL_DECL void DUNGEON_IncreaseAlliedCountOfRoom(struct D2ActiveRoom* pRoom);
//D2Comon.0x6FD8C4F0 (#10036)
D2COMMON_DLL_DECL int DUNGEON_GetAlliedCountFromRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C510 (#10101)
D2COMMON_DLL_DECL void DUNGEON_DecreaseAlliedCountOfRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C550
struct D2Unit** DUNGEON_GetUnitListFromRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C580
struct D2Unit** DUNGEON_GetUnitUpdateListFromRoom(struct D2ActiveRoom* pRoom, BOOL bUpdate);
//D2Common.0x6FD8C5C0 (#10055)
D2COMMON_DLL_DECL struct D2PresetUnit* DUNGEON_GetPresetUnitsFromRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C600
struct D2RoomCollisionGrid* DUNGEON_GetCollisionGridFromRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C630
void DUNGEON_SetCollisionGridInRoom(struct D2ActiveRoom* pRoom, struct D2RoomCollisionGrid* pCollisionGrid);
//D2Common.0x6FD8C660 (#10063)
D2COMMON_DLL_DECL void DUNGEON_SetClientIsInSight(struct D2DrlgAct* pAct, int nLevelId, int nX, int nY, struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C6B0 (#10064)
D2COMMON_DLL_DECL void DUNGEON_UnsetClientIsInSight(struct D2DrlgAct* pAct, int nLevelId, int nX, int nY, struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C700 (#10062)
D2COMMON_DLL_DECL void DUNGEON_ChangeClientRoom(struct D2ActiveRoom* pRoom1, struct D2ActiveRoom* pRoom2);
//D2Common.0x6FD8C730 (#10065)
D2COMMON_DLL_DECL struct D2ActiveRoom* DUNGEON_StreamRoomAtCoords(struct D2DrlgAct* pAct, int nX, int nY);
//D2Common.0x6FD8C770 (#10056)
D2COMMON_DLL_DECL struct D2ActiveRoom* DUNGEON_GetRoomFromAct(struct D2DrlgAct* pAct);
//D2Common.0x6FD8C7A0 (#10057)
D2COMMON_DLL_DECL int DUNGEON_GetLevelIdFromRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C7C0 (#10058)
D2COMMON_DLL_DECL int DUNGEON_GetWarpDestinationLevel(struct D2ActiveRoom* pRoom, int nSourceLevel);
//D2Common.0x6FD8C7E0 (#10059)
D2COMMON_DLL_DECL int DUNGEON_GetLevelIdFromPopulatedRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C800 (#10060)
D2COMMON_DLL_DECL BOOL DUNGEON_HasWaypoint(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C840 (#10061)
D2COMMON_DLL_DECL const char* DUNGEON_GetPickedLevelPrestFilePathFromRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C860 (#10066)
D2COMMON_DLL_DECL void DUNGEON_AllocDrlgDelete(struct D2ActiveRoom* pRoom, int nUnitType, D2UnitGUID nUnitGuid);
//D2Common.0x6FD8C8B0 (#10067)
D2COMMON_DLL_DECL void DUNGEON_FreeDrlgDelete(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C910 (#10068)
D2COMMON_DLL_DECL struct D2DrlgDelete* DUNGEON_GetDrlgDeleteFromRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C940 (#10069)
D2COMMON_DLL_DECL struct D2ActiveRoom* DUNGEON_GetARoomInClientSight(struct D2DrlgAct* pAct);
//D2Common.0x6FD8C980 (#10070)
D2COMMON_DLL_DECL struct D2ActiveRoom* DUNGEON_GetARoomInSightButWithoutClient(struct D2DrlgAct* pAct, struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8C9E0 (#10071)
D2COMMON_DLL_DECL BOOL DUNGEON_TestRoomCanUnTile(struct D2DrlgAct* pAct, struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8CA60 (#10072)
D2COMMON_DLL_DECL bool DUNGEON_GetRoomStatusFlags(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8CA80 (#10073)
D2COMMON_DLL_DECL BOOL D2Common_10073(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8CAE0 (#10074)
D2COMMON_DLL_DECL BOOL D2Common_10074(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8CB10 (#10075)
D2COMMON_DLL_DECL void D2Common_10075(struct D2ActiveRoom* pRoom, BOOL bSet);
//D2Common.0x6FD8CB60 (#10079)
D2COMMON_DLL_DECL void DUNGEON_AddClientToRoom(struct D2ActiveRoom* pRoom, struct D2Client* pClient);
//D2Common.0x6FD8CC50
void DUNGEON_UpdateClientListOfRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8CD10 (#10080)
D2COMMON_DLL_DECL void DUNGEON_RemoveClientFromRoom(struct D2ActiveRoom* pRoom, struct D2Client* pClient);
//D2Common.0x6FD8CDF0 (#10081)
D2COMMON_DLL_DECL int D2Common_10081_GetTileCountFromRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8CE40
void DUNGEON_FreeRoom(void* pMemPool, struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8CF10 (#10076)
D2COMMON_DLL_DECL void DUNGEON_RemoveRoomFromAct(struct D2DrlgAct* pAct, struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8D000 (#10077)
D2COMMON_DLL_DECL void D2Common_10077(struct D2ActiveRoom* pRoom1, struct D2ActiveRoom* pRoom2);
//D2Common.0x6FD8D030 (#10078)
D2COMMON_DLL_DECL void DUNGEON_UpdateAndFreeInactiveRooms(struct D2DrlgAct* pAct);
//D2Common.0x6FD8D040 (#10044)
D2COMMON_DLL_DECL int DUNGEON_CheckLOSDraw(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8D060
struct D2DrlgEnvironment* DUNGEON_GetEnvironmentFromAct(struct D2DrlgAct* pAct);
//D2Common.0x6FD8D090 (#10088)
D2COMMON_DLL_DECL struct D2Drlg* DUNGEON_GetDrlgFromAct(struct D2DrlgAct* pAct);
//D2Common.0x6FD912D0 (#10089)
D2COMMON_DLL_DECL int DUNGEON_GetInitSeedFromAct(struct D2DrlgAct* pAct);
//D2Common.0x6FD8D0C0 (#10007)
D2COMMON_DLL_DECL struct D2DrlgRoom* DUNGEON_GetRoomExFromRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8D0D0 (#10086)
D2COMMON_DLL_DECL BOOL DUNGEON_IsTownLevelId(int nLevelId);
//D2Common.0x6FD8D0E0 (#10082)
D2COMMON_DLL_DECL BOOL DUNGEON_IsRoomInTown(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8D100 (#10083)
D2COMMON_DLL_DECL int D2COMMON_10083_Return0(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8D130 (#10084)
D2COMMON_DLL_DECL int D2Common_10084(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8D140 (#10085)
D2COMMON_DLL_DECL int DUNGEON_GetTownLevelIdFromActNo(uint8_t nAct);
//D2Common.0x6FD8D180 (#10087)
D2COMMON_DLL_DECL int D2Common_10087(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8D1C0 (#10090)
D2COMMON_DLL_DECL int DUNGEON_GetNumberOfPopulatedRoomsInLevel(struct D2DrlgAct* pAct, int nLevelId);
//D2Common.0x6FD8D1E0 (#10025)
D2COMMON_DLL_DECL int* DUNGEON_GetWarpCoordinatesFromRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8D220 (#10091)
D2COMMON_DLL_DECL void DUNGEON_UpdateWarpRoomSelect(struct D2ActiveRoom* pRoom, int nLevelId);
//D2Common.0x6FD8D260 (#10092)
D2COMMON_DLL_DECL void DUNGEON_UpdateWarpRoomDeselect(struct D2ActiveRoom* pRoom, int nLevelId);
//D2Common.0x6FD8D2A0 (#10093)
D2COMMON_DLL_DECL void DUNGEON_UpdatePops(struct D2ActiveRoom* pRoom, int nX, int nY, BOOL bOtherRoom);
//D2Common.0x6FD8D2E0 (#10094)
D2COMMON_DLL_DECL void DUNGEON_GetTombStoneTileCoords(struct D2ActiveRoom* pRoom, struct D2Coord** ppTombStoneTiles, int* pnTombStoneTiles);
//D2Common.0x6FD8D300 (#10095)
D2COMMON_DLL_DECL int D2Common_10095(struct D2ActiveRoom* pRoom, int nX, int nY);
//D2Common.0x6FD8D3A0 (#10096)
D2COMMON_DLL_DECL struct D2RoomCoordList* D2Common_10096(struct D2ActiveRoom* pRoom, int nX, int nY);
//D2Common.0x6FD8D3C0 (#10097)
D2COMMON_DLL_DECL struct D2RoomCoordList* DUNGEON_GetRoomCoordList(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8D3D0 (#10098)
D2COMMON_DLL_DECL void DUNGEON_GetPortalLevelArrayFromPortalFlags(void* pMemPool, int nFlags, int** ppLevels, int* pnLevels);
//D2Common.0x6FD8D4B0 (#10099)
D2COMMON_DLL_DECL int DUNGEON_GetPortalFlagFromLevelId(int nPortalLevelId);
//D2Common.0x6FD8D4F0 (#10037)
D2COMMON_DLL_DECL int DUNGEON_GetTownLevelIdFromAct(struct D2DrlgAct* pAct);
//D2Common.0x6FD8D520 (#10047)
D2COMMON_DLL_DECL int DUNGEON_GetHoradricStaffTombLevelId(struct D2DrlgAct* pAct);
//D2Common.0x6FD8D540 (#10102)
D2COMMON_DLL_DECL void DUNGEON_ToggleHasPortalFlag(struct D2ActiveRoom* pRoom, BOOL bReset);
//D2Common.0x6FD8D560 (#10104)
D2COMMON_DLL_DECL void DUNGEON_AnimateTiles(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8D580 (#10105)
D2COMMON_DLL_DECL void DUNGEON_InitRoomTileAnimation(struct D2DrlgAct* pAct, struct D2ActiveRoom* pRoom1, struct D2ActiveRoom* pRoom2);
//D2Common.0x6FD8D5C0 (#10103)
D2COMMON_DLL_DECL void DUNGEON_SetActCallbackFunc(struct D2DrlgAct* pAct, ACTCALLBACKFN pActCallbackFunction);
//D2Common.0x6FD8D600 (#10106)
D2COMMON_DLL_DECL void DUNGEON_SaveKilledUnitGUID(struct D2ActiveRoom* pRoom, D2UnitGUID nUnitGUID);

//////////////////////////////////////
// Coordinates conversion functions	//
//      see doc/Coordinates.md		//
//////////////////////////////////////

//D2Common.0x6FD8D690 (#10107)
D2COMMON_DLL_DECL void DUNGEON_ClientToGameTileCoords(int* pX, int* pY);
//D2Common.0x6FD8D870 (#10108)
D2COMMON_DLL_DECL void DUNGEON_ClientToGameSubtileCoords(int* pX, int* pY);
//D2Common.0x6FD8D8A0 (#10109)
D2COMMON_DLL_DECL void DUNGEON_ClientToGameCoords(int* pX, int* pY);

//D2Common.0x6FD8D6E0 (#10110)
D2COMMON_DLL_DECL void DUNGEON_GameTileToClientCoords(int* pX, int* pY);
//D2Common.0x6FD8D630 (#10111)
D2COMMON_DLL_DECL void DUNGEON_GameSubtileToClientCoords(int* pX, int* pY);
//D2Common.0x6FD8D660 (#10112)
D2COMMON_DLL_DECL void DUNGEON_GameToClientCoords(int* pX, int* pY);
//D2Common.0x6FD8D8C0 (#10113)
D2COMMON_DLL_DECL void DUNGEON_GameTileToSubtileCoords(int* pX, int* pY);

//D2Common.0x6FD8D710 (#10114)
D2COMMON_DLL_DECL void DUNGEON_ClientTileDrawPositionToGameCoords(int nX, int nY, int* pX, int* pY);
//D2Common.0x6FD8D790 (#10115)
D2COMMON_DLL_DECL void DUNGEON_GameToClientTileDrawPositionCoords(int nX, int nY, int* pX, int* pY);

//D2Common.0x6FD8D7D0 (#10116)
D2COMMON_DLL_DECL void DUNGEON_ClientSubileDrawPositionToGameCoords(int nX, int nY, int* pX, int* pY);
//D2Common.0x6FD8D830 (#10117)
D2COMMON_DLL_DECL void DUNGEON_GameToClientSubtileDrawPositionCoords(int nX, int nY, int* pX, int* pY);

// Helper function, official name coming from D2Common.0x6FDBCF10
static inline bool DungeonTestRoomGame(const struct D2ActiveRoom* pRoom, int nX, int nY)
{
	return nX >= pRoom->tCoords.nSubtileX && nX < (pRoom->tCoords.nSubtileX + pRoom->tCoords.nSubtileWidth)
        && nY >= pRoom->tCoords.nSubtileY && nY < (pRoom->tCoords.nSubtileY + pRoom->tCoords.nSubtileHeight);

}
// Helper function
static inline struct D2ActiveRoom* DUNGEON_GetRoomAtPosition(struct D2ActiveRoom* pRoom, int32_t nSubtileX, int32_t nSubtileY)
{
    if (!pRoom)
    {
        return nullptr;
    }

    if (DungeonTestRoomGame(pRoom, nSubtileX , nSubtileY))
    {
        return pRoom;
    }

    struct D2ActiveRoom** ppRoomList = nullptr;
    int32_t nNumRooms = 0;
    DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, &ppRoomList, &nNumRooms);

    for (int32_t i = 0; i < nNumRooms; ++i)
    {
        struct D2ActiveRoom* pAdjacentRoom = ppRoomList[i];
        if (pAdjacentRoom && DungeonTestRoomGame(pAdjacentRoom, nSubtileX, nSubtileY))
        {
            return pAdjacentRoom;
        }
    }

    return nullptr;
}
