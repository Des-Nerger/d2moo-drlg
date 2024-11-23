#pragma once 

#include <D2BasicTypes.h>
#include <Archive.h>

struct D2ActiveRoom;

#pragma pack(1)
struct D2CollisionField
{
	int32_t nWidth;							//0x00
	int32_t nHeight;						//0x04
	int32_t nArea;							//0x08
	int32_t nCenterX;						//0x0C
	int32_t nCenterY;						//0x10
};

struct D2Field
{
	int32_t nX;								//0x00
	int32_t nY;								//0x04
};
#pragma pack()

//D2Common.0x6FD51FC0
BOOL DATATBLS_LoadExpFieldD2(HD2ARCHIVE hArchive);
//D2Common.0x6FD52010 (#11089)
D2COMMON_DLL_DECL BOOL DATATBLS_InitializeCollisionFieldTable(char* pExpField, int nSize);
//D2Common.0x6FD520F0 (#11090)
D2COMMON_DLL_DECL BOOL DATATBLS_FreeCollisionFieldTable();
//D2Common.0x6FD52140 (#11091)
D2COMMON_DLL_DECL void DATATBLS_GetCollisionFieldCenter(int* pCenterX, int* pCenterY);
//D2Common.0x6FD52160 (#11092)
D2COMMON_DLL_DECL int DATATBLS_GetCollisionFieldWidth();
//D2Common.0x6FD52170 (#11093)
D2COMMON_DLL_DECL int DATATBLS_GetCollisionFieldHeight();
//D2Common.0x6FD52180 (#11094)
D2COMMON_DLL_DECL struct D2Field* DATATBLS_AllocField();
//D2Common.0x6FD521D0 (#11095)
D2COMMON_DLL_DECL void DATATBLS_FreeField(struct D2Field* pField);
//D2Common.0x6FD52210 (#11096)
D2COMMON_DLL_DECL void DATATBLS_SetFieldCoordinates(struct D2Field* pField, int nX, int nY);
//D2Common.0x6FD52250 (#11097)
D2COMMON_DLL_DECL int D2Common_11097(struct D2Field* pField, int nX, int nY);
//D2Common.0x6FD522A0 (#11098)
D2COMMON_DLL_DECL int D2Common_11098(struct D2Field* pField, int* pX, int* pY);
//D2Common.0x6FD52360 (#11099)
D2COMMON_DLL_DECL BOOL D2Common_11099(struct D2Field* pField, struct D2ActiveRoom* pRoom, int nX, int nY, uint16_t fMask);

