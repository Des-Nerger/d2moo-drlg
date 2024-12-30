#pragma once

#include "D2CommonDefinitions.h"

struct D2DrlgOrth;

#pragma pack(1)

struct D2DrlgCoord
{
	int32_t nPosX;								//0x00
	int32_t nPosY;								//0x04
	int32_t nWidth;								//0x08
	int32_t nHeight;							//0x0C
};

struct D2DrlgVertex
{
	int32_t nPosX;							//0x00
	int32_t nPosY;							//0x04
	uint8_t nDirection;						//0x08
	uint8_t pad0x09[3];						//0x09
	int32_t dwFlags;						//0x0C
	struct D2DrlgVertex* pNext;				//0x10
};

#pragma pack()

//D2Common.0x6FD782A0
struct D2DrlgVertex* __fastcall DRLGVER_AllocVertex(void* pMemPool, uint8_t nDirection);
//D2Common.0x6FD782D0
void __fastcall DRLGVER_CreateVertices(void* pMemPool, struct D2DrlgVertex** ppVertices, struct D2DrlgCoord* pDrlgCoord, uint8_t nDirection, struct D2DrlgOrth* pDrlgRoomData);
//D2Common.0x6FD786C0
void __fastcall DRLGVER_FreeVertices(void* pMemPool, struct D2DrlgVertex** ppVertices);
//D2Common.0x6FD78730
void __fastcall DRLGVER_GetCoordDiff(struct D2DrlgVertex* pDrlgVertex, int* pDiffX, int* pDiffY);
