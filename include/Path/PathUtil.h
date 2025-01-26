#pragma once

#include "D2CommonDefinitions.h"
#include "Path.h"
#pragma pack(1)

#pragma pack()


//1.10f: D2Common.0x6FDAB890
//1.13c: D2Common.0x6FD8E080
void __cdecl PATHUtil_AdvanceTowardsTarget_6FDAB890(struct D2DynamicPath* ptPath);

//1.10f: D2Common.0x6FDAB940
//1.13c: D2Common.0x6FD8E310
void __cdecl sub_6FDAB940(struct D2PathPoint* pOutPathPoint, struct D2DynamicPath* ptPath);
