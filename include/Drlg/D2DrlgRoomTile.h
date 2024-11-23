#pragma once

#include "CommonDefinitions.h"
#include "D2DrlgDrlg.h"
#include "D2DrlgDrlgGrid.h"

#pragma pack(1)

union D2C_PackedTileInformation
{
	uint32_t nPackedValue;
	struct {
		// If not wall nor floor, then it is a roof.
		uint32_t bIsWall           : 1; // BIT(0)     Is this a wall.
		uint32_t bIsFloor          : 1; // BIT(1)     Is this a floor.
		uint32_t bLOS              : 1; // BIT(2)     code-generated; added on edges
		uint32_t bEnclosed         : 1; // BIT(3)     seems to delimit an enclosure inside another area, or trees
		uint32_t bExit             : 1; // BIT(4)     arch or doorway or gateway in a wall
		uint32_t bUnk0x20          : 1; // BIT(5)     Unknown flag
		uint32_t bLayerBelow       : 1; // BIT(6)     only floor
		uint32_t bLayerAbove       : 1; // BIT(7)     wall & floor
		uint32_t nTileSequence     : 8; // BIT(8-15)  AKA tile subindex
		uint32_t bFillLOS          : 1; // BIT(16)    all tiles will get wall collision
		uint32_t bUnwalkable       : 1; // BIT(17) 
		uint32_t nWallLayer        : 2; // BIT(18-19) code-generated; set when at least Floor2 or Wall2  // (nLayer - 1) << 0x12
		//uint32_t bOverlappedLayer3 : 1; // BIT(19)    code-generated; set when has more walls, incl' of other orientations than usual; obj, shd, tree, roof, lower
		uint32_t nTileStyle        : 6; // BIT(20-25) AKA tile index
		uint32_t bRevealHidden     : 1; // BIT(26)    looks like an upper wall brought to a layer in front
		uint32_t bShadow           : 1; // BIT(27)    this layer is a shadow layer | Lectem's note: seems to be roof instead ? Or are shadow tiles interpreted as roof tiles ?
		uint32_t bLinkage          : 1; // BIT(28)    near wp, lvl links, paths // will never get hidden
		uint32_t bObjectWall       : 1; // BIT(29)    wall tiles with props; may be block reverb / other sounds (crates, barrels, tables etc.)
		uint32_t bUnk0x40000000    : 1; // BIT(30)    Unknown flag
		uint32_t bHidden           : 1; // BIT(31) 
	};
};

enum D2C_RoomTileConstants
{
	DRLGROOMTILE_TILES_SIZE = 8,
	DRLGROOMTILE_SUBTILES_SIZE = DRLGROOMTILE_TILES_SIZE * 5,
};

#pragma pack()

//D2Common.0x6FD88860
struct D2TileLibraryEntry* DRLGROOMTILE_GetTileCache(struct D2DrlgRoom* pDrlgRoom, int nType, uint32_t nPackedTileInformation);
//D2Common.0x6FD889C0
struct D2DrlgTileData* DRLGROOMTILE_InitWallTileData(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgTileData** ppTileData, int nX, int nY, uint32_t nPackedTileInformation, struct D2TileLibraryEntry* pTileLibraryEntry, int nTileType);
//D2Common.0x6FD88AC0
void DRLGROOMTILE_InitializeTileDataFlags(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgTileData* pTileData, uint32_t nTileFlags, int nType, int nX, int nY);
//D2Common.0x6FD88BE0
void DRLGROOMTILE_AddTilePresetUnits(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgTileData* pTileData, uint32_t nPackedTileInformation, int nX, int nY, int nTileType);
//D2Common.0x6FD88DD0
void DRLGROOMTILE_InitTileData(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgTileData* pTileData, int nX, int nY, uint32_t nPackedTileInformation, struct D2TileLibraryEntry* pTileLibraryEntry);
//D2Common.0x6FD88E60
struct D2DrlgTileData* DRLGROOMTILE_InitFloorTileData(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgTileData** ppTileData, int nX, int nY, uint32_t nPackedTileInformation, struct D2TileLibraryEntry* pTileLibraryEntry);
//D2Common.0x6FD88F10
struct D2DrlgTileData* DRLGROOMTILE_InitShadowTileData(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgTileData** ppTileData, int nX, int nY, uint32_t nPackedTileInformation, struct D2TileLibraryEntry* pTileLibraryEntry);
//D2Common.0x6FD88FD0
void DRLGROOMTILE_InitTileShadow(struct D2DrlgRoom* pDrlgRoom, int nX, int nY, uint32_t nPackedTileInformation);
//D2Common.0x6FD89000
void DRLGROOMTILE_LoadInitRoomTiles(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgGrid* pTilePackedInfoGrid, struct D2DrlgGrid* pTileTypeGrid, BOOL bFillBlanks, BOOL bKillEdgeX, BOOL bKillEdgeY);
//D2Common.0x6FD89360
BOOL DRLGROOMTILE_AddWarp(struct D2DrlgRoom* pDrlgRoom, int nX, int nY, uint32_t nPackedTileInformation, int nTileType);
//D2Common.0x6FD89410
void DRLGROOMTILE_LoadWallWarpTiles(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgTileData* pTileData, uint32_t nPackedTileInformation, int nTileType);
//D2Common.0x6FD89590
void DRLGROOMTILE_LoadFloorWarpTiles(struct D2DrlgRoom* pDrlgRoom, int nX, int nY, uint32_t nPackedTileInformation, int nTileType);
//D2Common.0x6FD897E0
struct D2DrlgTileData* DRLGROOMTILE_GetLinkedTileData(struct D2DrlgRoom* pDrlgRoom, BOOL bFloor, uint32_t nPackedTileInformation, int nX, int nY, struct D2DrlgRoom** ppDrlgRoom);
//D2Common.0x6FD89930
void DRLGROOMTILE_AddLinkedTileData(void* pMemPool, struct D2DrlgRoom* pDrlgRoom, int nTileType, uint32_t nPackedTileInformation, int nX, int nY);
//D2Common.0x6FD89AF0
void DRLGROOMTILE_LinkedTileDataManager(void* pMemPool, struct D2DrlgRoom* pDrlgRoom1, struct D2DrlgRoom* pDrlgRoom2, struct D2DrlgTileData* pTileData, int nTileType, uint32_t nPackedTileInformation, int nX, int nY);
//D2Common.0x6FD89CC0
void DRLGROOMTILE_GetCreateLinkedTileData(void* pMemPool, struct D2DrlgRoom* pDrlgRoom, int nTileType, uint32_t nPackedTileInformation, int nX, int nY);
//D2Common.0x6FD89E30
void DRLGROOMTILE_CountAllTileTypes(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgGrid* pTileInfoGrid, BOOL bCheckCoordinatesValidity, BOOL bKillEdgeX, BOOL bKillEdgeY);
//D2Common.0x6FD89F00
void DRLGROOMTILE_CountWallWarpTiles(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgGrid* pTileInfoGrid, struct D2DrlgGrid* pTileTypeGrid, BOOL bKillEdgeX, BOOL bKillEdgeY);
//D2Common.0x6FD89FA0
void DRLGROOMTILE_InitRoomGrids(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD89FD0
void DRLGROOMTILE_AddRoomMapTiles(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD8A010
void DRLGROOMTILE_AllocTileGrid(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD8A050
void DRLGROOMTILE_AllocTileData(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD8A130
void DRLGROOMTILE_ReallocRoofTileGrid(void* pMemPool, struct D2DrlgTileGrid* pTileGrid, int nAdditionalRoofs);
//D2Common.0x6FD8A1B0 (#10017)
D2COMMON_DLL_DECL int DRLGROOMTILE_GetNumberOfShadowsFromRoom(struct D2ActiveRoom* pRoom);
//D2Common.0x6FD8A1D0
void DRLGROOMTILE_FreeTileGrid(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD8A2E0
void DRLGROOMTILE_FreeRoom(struct D2DrlgRoom* pDrlgRoom, BOOL bKeepRoom);
//D2Common.0x6FD8A380
void DRLGROOMTILE_LoadDT1FilesForRoom(struct D2DrlgRoom* pDrlgRoom);
