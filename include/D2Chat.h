#pragma once

#include "CommonDefinitions.h"
#pragma pack(1)

struct D2HoverText
{
	uint32_t dwDisplayTime;					//0x00
	uint32_t dwExpireTime;						//0x04
	uint8_t nLangId;							//0x08
	uint8_t pad0x09[3];						//0x09
	BOOL bUsed;								//0x0C
	char szMsg[256];						//0x10
};
#pragma pack()

//D2Common.0x6FDC3BF0 (#10892)
D2COMMON_DLL_DECL struct D2HoverText* CHAT_AllocHoverMsg(void* pMemPool, const char* szText, int nTimeout);
//D2Common.0x6FDC3C80 (#10893)
D2COMMON_DLL_DECL void CHAT_FreeHoverMsg(void* pMemPool, struct D2HoverText* pHoverMsg);
//D2Common.0x6FDC3CA0 (#10894)
D2COMMON_DLL_DECL uint32_t CHAT_GetDisplayTimeFromHoverMsg(struct D2HoverText* pHoverMsg);
//D2Common.0x6FDC3CB0 (#10895)
D2COMMON_DLL_DECL uint32_t CHAT_GetTimeoutFromHoverMsg(struct D2HoverText* pHoverMsg);
//D2Common.0x6FDC3CC0 (#10896)
D2COMMON_DLL_DECL void CHAT_CopyHoverMsgToBuffer(struct D2HoverText* pHoverMsg, char* szMessage);
//D2Common.0x6FDC3CE0 (#10897)
D2COMMON_DLL_DECL BOOL CHAT_GetUsedFromHoverMsg(struct D2HoverText* pHoverMsg);
//D2Common.0x6FDC3CF0 (#10898)
D2COMMON_DLL_DECL void CHAT_SetUsedInHoverMsg(struct D2HoverText* pHoverMsg, BOOL bUsed);
//D2Common.0x6FDC3D00 (#10899)
D2COMMON_DLL_DECL uint8_t CHAT_GetLangIdFromHoverMsg(struct D2HoverText* pHoverMsg);
//D2Common.0x6FDC3D10 (#10900)
D2COMMON_DLL_DECL void CHAT_SetLangIdInHoverMsg(struct D2HoverText* pHoverMsg, uint8_t nLangId);
