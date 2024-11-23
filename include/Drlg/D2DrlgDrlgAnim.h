#pragma once

#include "CommonDefinitions.h"
#include "D2DrlgDrlg.h"
#include "D2DrlgDrlgGrid.h"

#pragma pack(1)


#pragma pack()

//D2Common.0x6FD75480
void DRLGANIM_InitCache(struct D2Drlg* pDrlg, struct D2DrlgTileData* pTileData);
//D2Common.0x6FD75560
void DRLGANIM_TestLoadAnimatedRoomTiles(struct D2DrlgRoom* pDrlgRoom, struct D2DrlgGrid* pDrlgGrid, struct D2DrlgGrid* pTileTypeGrid, int nTileType, int nTileX, int nTileY);
//D2Common.0x6FD756B0
void DRLGANIM_AnimateTiles(struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD75740
void DRLGANIM_AllocAnimationTileGrids(struct D2DrlgRoom* pDrlgRoom, int nAnimationSpeed, struct D2DrlgGrid* pWallGrid, int nWalls, struct D2DrlgGrid* pFloorGrid, int nFloors, struct D2DrlgGrid* pShadowGrid);
//D2Common.0x6FD757B0
void DRLGANIM_AllocAnimationTileGrid(struct D2DrlgRoom* pDrlgRoom, int nAnimationSpeed, struct D2DrlgTileData* pTiles, int nTiles, struct D2DrlgGrid* pDrlgGrid, int nUnused);
//D2Common.0x6FD75B00
void DRLGANIM_UpdateFrameInAdjacentRooms(struct D2DrlgRoom* pDrlgRoom1, struct D2DrlgRoom* pDrlgRoom2);
