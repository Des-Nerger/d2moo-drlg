#pragma once

#include "D2CommonDefinitions.h"

#include <D2BitManip.h>

#define NUM_QUEST_WORDS 48

//D2Common.0x6FDAE800 (#11107)
D2COMMON_DLL_DECL BOOL __cdecl QUESTRECORD_GetQuestState(struct D2BitBuffer* pQuestRecord, int nQuest, int nState);
//D2Common.0x6FDAE850 (#11108)
D2COMMON_DLL_DECL void __cdecl QUESTRECORD_SetQuestState(struct D2BitBuffer* pQuestRecord, int nQuest, int nState);
//D2Common.0x6FDAE890 (#11109)
D2COMMON_DLL_DECL void __cdecl QUESTRECORD_ClearQuestState(struct D2BitBuffer* pQuestRecord, int nQuest, int nState);
//D2Common.0x6FDAE8D0 (#11110)
D2COMMON_DLL_DECL void __cdecl QUESTRECORD_ResetIntermediateStateFlags(struct D2BitBuffer* pQuestRecord, int nQuest);
//D2Common.0x6FDAE920 (#11111)
D2COMMON_DLL_DECL struct D2BitBuffer* __cdecl QUESTRECORD_AllocRecord(void* pMemPool);
//D2Common.0x6FDAE970 (#11112)
D2COMMON_DLL_DECL void __cdecl QUESTRECORD_FreeRecord(void* pMemPool, struct D2BitBuffer* pQuestRecord);
//D2Common.0x6FDAE9B0 (#11113)
D2COMMON_DLL_DECL void __cdecl QUESTRECORD_CopyBufferToRecord(struct D2BitBuffer* pQuestRecord, uint8_t* pBuffer, uint16_t nBufferSize, BOOL bResetStates);
//D2Common.0x6FDAEA40 (#11114)
D2COMMON_DLL_DECL void __cdecl QUESTRECORD_CopyRecordToBuffer(struct D2BitBuffer* pQuestRecord, uint8_t* pBuffer, uint16_t nBufferSize, int nUnused);
