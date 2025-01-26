#pragma once 

#include <D2BasicTypes.h>
#include <D2Composit.h>

#pragma pack()

enum D2AnimSeqEvent : uint8_t
{
	ANIMSEQ_EVENT_NONE,
	ANIMSEQ_EVENT_MELEE_ATTACK,
	ANIMSEQ_EVENT_MISSILE_ATTACK,
	ANIMSEQ_EVENT_PLAY_SOUND,
	ANIMSEQ_EVENT_TRIGGER_SKILL,

};

struct D2AnimSeqTxt
{
	uint16_t wSequence;					//0x00
	uint8_t nMode;						//0x02
	uint8_t nFrame;						//0x03
	uint8_t nDir;						//0x04
	enum D2AnimSeqEvent nEvent;				//0x05
};

struct D2AnimSeqRecord
{
	struct D2AnimSeqTxt* pAnimSeqTxtRecord;	//0x00
	int32_t nSeqFramesCount;			//0x04
	int32_t nFramesCount;				//0x08
};

//TODO: Find a better name
struct D2PlayerWeaponSequences
{
	struct D2AnimSeqRecord weaponRecords[NUM_WEAPON_CLASSES];		//0x00
};

#pragma pack()

//D2Common.0x6FD727A0 (#10682)
D2COMMON_DLL_DECL struct D2AnimSeqTxt* __cdecl DATATBLS_GetMonSeqTxtRecordFromUnit(struct D2Unit* pUnit);
//D2Common.0x6FD727C0
struct D2AnimSeqRecord* __cdecl DATATBLS_GetSeqRecordFromUnit(struct D2Unit* pUnit);
//D2Common.0x6FD728A0 (#10683)
D2COMMON_DLL_DECL int __cdecl DATATBLS_GetSeqFramePointsCount(struct D2Unit* pUnit);
//D2Common.0x6FD728C0 (#10684)
D2COMMON_DLL_DECL int __cdecl DATATBLS_GetSeqFrameCount(struct D2Unit* pUnit);
//D2Common.0x6FD728E0 (#10685)
D2COMMON_DLL_DECL void __cdecl DATATBLS_ComputeSequenceAnimation(struct D2AnimSeqTxt* pMonSeqTxt, int nTargetFramePoint, int nCurrentFramePoint, unsigned int* pMode, unsigned int* pFrame, int* pDirection, int* pEvent);
//D2Common.0x6FD72990 (#10686)
D2COMMON_DLL_DECL void __cdecl DATATBLS_GetSequenceEvent(struct D2AnimSeqTxt* pMonSeqTxt, int nSeqFramePoint, int* pEvent);
//D2Common.0x6FD6F050
void __cdecl DATATBLS_LoadMonSeqTxt(HD2ARCHIVE hArchive);
//D2Common.0x6FD6F200 (#11262)
D2COMMON_DLL_DECL struct D2AnimSeqRecord* __cdecl DATATBLS_GetMonSeqTableRecord(int nSequence);
