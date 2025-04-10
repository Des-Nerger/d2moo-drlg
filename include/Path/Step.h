#pragma once

#include "D2CommonDefinitions.h"
#include <D2Seed.h>
#include "Path.h"
#pragma pack(1)

#pragma pack()


//1.10:  D2Common.0x1005E6D0
//1.10f: D2Common.0x6FDAC5E0
void __cdecl PATH_GetDirectionVector(struct D2Coord* pDirectionVector, int* pOutDirection, DWORD dwStartPrecisionX, DWORD dwStartPrecisionY, DWORD dwTargetPrecisionX, DWORD dwTargetPrecisionY);
//1.00:  D2Common.0x1005F220
//1.10f: D2Common.0x6FDACC40
//1.13c: D2Common.0x6FD5DA40
void PATH_RecacheRoomAtCoordIfNeeded(struct D2DynamicPath* pPath, struct D2ActiveRoom* pHintRoom, uint32_t nPrecisionX, uint32_t nPrecisionY);
//1.00:  Inlined
//1.10f: Inlined
//1.13c: D2Common.6FD5DC80
void PATH_ResetMovement(struct D2DynamicPath* pDynamicPath);
//1.00:  D2Common.0x1005F420
//1.10f: D2Common.0x6FDACEC0
//1.13c: D2Common.0x6FD5D8E0
BOOL __cdecl sub_6FDACEC0(struct D2DynamicPath* pDynamicPath, union D2FP32_16* a2, struct D2Unit** pUnit);
//1.00:  Inlined
//1.10f: D2Common.0x6FDAD330
//1.13c: D2Common.0x6FD5DC80
void PATH_ResetMovement(struct D2DynamicPath* pDynamicPath);
//1.00:  D2Common.0x1005FAB0
//1.10f: D2Common.0x6FDAD5E0
BOOL __cdecl sub_6FDAD5E0(struct D2DynamicPath* pDynamicPath, struct D2ActiveRoom* pDestRoom, struct D2PathPoint tDest);
//1.00:  D2Common.0x100604E0 Note: Changed since then. Used to look for the room using coordinates
//1.10f: D2Common.0x6FDAE250
void __cdecl PATHMISC_SetRoom(struct D2DynamicPath* pPath, struct D2ActiveRoom* pNewRoom);


//1.00:  D2Common.0x10060640 (#10227)
//1.10f: D2Common.0x6FDADF00 (#10230)
D2COMMON_DLL_DECL BOOL __cdecl D2Common_10230(struct D2DynamicPath* pDynamicPath, int a2, struct D2ActiveRoom* pRoom, unsigned int a4, __int16 a5);
//1.00:  D2Common.0x10060120 (#10228)
//1.10f: D2Common.0x6FDADC20 (#10231)
D2COMMON_DLL_DECL int __cdecl D2Common_10231(struct D2DynamicPath* pDynamicPath, struct D2Unit* pUnit_unused, struct D2ActiveRoom* pRooms, uint16_t nX, uint16_t nY);
//1.00:  D2Common.0x100606B0 (#10229)
//1.10f: D2Common.0x6FDADF50 (#10232)
//1.13c: D2Common.0x6FD5DCE0 (#10223)
D2COMMON_DLL_DECL BOOL __cdecl D2Common_10232(struct D2DynamicPath* pPath, struct D2Unit* pUnit, struct D2ActiveRoom* pDestRoom, int nTargetX, int nTargetY);
//1.00:  D2Common.0x10060A60 (#10230)
//1.10f: D2Common.0x6FDAE290 (#10233)
//1.13c: D2Common.0x6FD5DB40 (#10770)
D2COMMON_DLL_DECL void __cdecl PATH_RecacheRoomIfNeeded(struct D2DynamicPath* pDynamicPath);
//1.00:  D2Common.0x10060C40 (#10231)
//1.10f: D2Common.0x6FDAE500 (#10234)
D2COMMON_DLL_DECL BOOL __cdecl D2Common_10234(struct D2DynamicPath* pDynamicPath);
//1.00:  D2Common.0x10060C60 (#10231)
//1.10f: D2Common.0x6FDAE520 (#10235)
D2COMMON_DLL_DECL void __cdecl D2Common_10235_PATH_UpdateRiderPath(struct D2Unit* pRiderUnit, struct D2Unit* pMountUnit);



