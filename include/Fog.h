#pragma once

#include <D2Dll.h>
#include <D2BasicTypes.h>
#include <StormHandles.h>
#include <stdlib.h>
#include <string.h>

//1.10f Image base: 0x6FF50000

#ifdef D2_VERSION_110F
constexpr int FogImageBase = 0x6FF50000;
#endif


#pragma pack(1)

struct D2TxtLinkNode
{
	char szText[32];				//0x00
	int nLinkIndex;					//0x20
	struct D2TxtLinkNode* pPrevious;	//0x24
	struct D2TxtLinkNode* pNext;		//0x28
};

struct D2TxtLinkTbl
{
	union
	{
		char szCode[4];				//0x00
		uint32_t dwCode;			//0x00
	};
	int nLinkIndex;					//0x04
};

struct D2TxtLink
{
	int32_t nRecords;				//0x00
	int32_t nAllocatedCells;		//0x04
	struct D2TxtLinkTbl* pTbl;			//0x08
	struct D2TxtLinkNode* pFirstNode;	//0x0C
};


struct D2BinFile
{
	uint8_t* pDataBuffer;			//0x00
	uint8_t* pData;					//0x04
	int32_t nRecordCount;			//0x08
	int32_t nCellCount;				//0x0C
};

typedef enum : uint32_t
{
	TXTFIELD_NONE,
	TXTFIELD_ASCII,
	TXTFIELD_DWORD,
	TXTFIELD_WORD,
	TXTFIELD_BYTE,
	TXTFIELD_UNKNOWN1,
	TXTFIELD_UNKNOWN2,
	TXTFIELD_BYTE2,
	TXTFIELD_DWORD2,
	TXTFIELD_RAW,
	TXTFIELD_ASCIITOCODE,
	TXTFIELD_UNKNOWN3,
	TXTFIELD_UNKNOWN4,
	TXTFIELD_CODETOBYTE,
	TXTFIELD_UNKNOWN5,
	TXTFIELD_CODETOWORD,
	TXTFIELD_UNKNOWN6,
	TXTFIELD_NAMETOINDEX,
	TXTFIELD_NAMETOINDEX2,
	TXTFIELD_NAMETODWORD,
	TXTFIELD_NAMETOWORD,
	TXTFIELD_NAMETOWORD2,
	TXTFIELD_KEYTOWORD,
	TXTFIELD_CUSTOMLINK,
	TXTFIELD_UNKNOWN7,
	TXTFIELD_CALCTODWORD,
	TXTFIELD_BIT
} D2C_TxtFieldTypes;

struct D2BinField
{
	const char* szFieldName;		//0x00
	D2C_TxtFieldTypes nFieldType;	//0x04
	int32_t nFieldLength;			//0x08
	int32_t nFieldOffset;			//0x0C
	void* pLinkField;				//0x10
};

struct D2UnkExcel
{
	struct D2UnkExcel* pNext;			//0x00
	uint32_t dwHash;				//0x04
	struct D2BinField* pBinField;		//0x08
};


enum D2C_AsyncDataPriority
{
	ASYNC_DATA_PRIORITY_NORMAL = 0,
	ASYNC_DATA_PRIORITY_HIGH = 1,
};

enum D2C_AsyncDataFlags : uint32_t
{
	ASYNC_DATA_FLAGS_LOADED                    = 0x1,
	ASYNC_DATA_FLAGS_OWNS_BUFFER               = 0x2,
	ASYNC_DATA_FLAGS_POSTPONED_PRIORITY_CHANGE = 0x8,

	ASYNC_DATA_FLAGS_DEBUG_TAG      = 0x41737960,
	ASYNC_DATA_FLAGS_DEBUG_TAG_MASK = 0xFFFFFFF0,
};

struct AsyncDataLoadFileCallback																			   // sizeof(0x1C)
{
	DWORD(* callback)(void* pFileData, size_t nDataLength, struct AsyncDataLoadFileCallback* pCallbackData); // 0x00
	DWORD userData[4];																						   // 0x04
	void* pData;																							   // 0x14
	size_t nFileSize;																						   // 0x18
};

struct AsyncData							 // sizeof(0x54)
{
	HSFILE hFile;							 // 0x00
	void* pMemPool;							 // 0x04
	OVERLAPPED tOverlapped;					 // 0x08
	struct AsyncDataLoadFileCallback pAsyncOpDesc;	 // 0x1C
	struct AsyncDataEventSlot* pEventSlot;	 // 0x38
	void* pBuffer;							 // 0x3C
	uint32_t nFileSize;						 // 0x40
	uint32_t nPriority;						 // 0x44 D2C_AsyncDataPriority
	uint32_t nFlags;						 // 0x48
	uint32_t nPreviousPriority;				 // 0x4C
	struct AsyncData* pNextPostponedPriorityChange; // 0x50
};

struct AsyncDataEventSlot  // sizeof(0x0C)
{
	HANDLE hEvent;		   // 0x00
	DWORD bSlotAvailable;  // 0x04
	struct AsyncData* pAsyncOp;   // 0x08
};


struct QServer;

#pragma pack()

typedef int (*D2ExceptionCallback)();

// D2FUNC_DLL(FOG, csprintf, const char*, , (char* szDest, const char* szFormat, ...), 0xDD90)
// D2FUNC_DLL(FOG, InitErrorMgr, void, , (const char* szProgramName, D2ExceptionCallback pExceptionCallback, const char* szVersion, BOOL bLogToFile), 0xE1B0)
// D2FUNC_DLL(FOG, SetLogPrefix, int, , (const char* szLogPrefix), 0xE1A0)
// D2FUNC_DLL(FOG, GetSystemInfo, void*, , (), 0xDF20)
void FOG_DisplayAssert(const char* szMsg, const char* szFile, int nLine);
// D2FUNC_DLL(FOG, DisplayHalt, void, , (const char* szMsg, const char* szFile, int nLine), 0xED60)
void FOG_DisplayWarning(const char* szMsg, const char* szFile, int nLine);
// D2FUNC_DLL(FOG, DisplayError, void, , (int nCategory, const char* szMsg, const char* szFile, int nLine), 0xEDF0)
// // Log to default logfile with date and `\n` at end of message
void FOG_Trace(const char* szFormat, ...);
// // Log to file. Will be prefixed with "D2" and suffixed by date. Log includes date prefix and `\n` at end of message.
// D2FUNC_DLL(FOG, TraceF, void, , (const char* pFileSubName, const char* szFormat, ...), 0x120E0)
// // Append to the default logfile. No date nor '\n'.
// D2FUNC_DLL(FOG, TraceAppend, void, , (const char* szFormat, ...), 0x12180)
// D2FUNC_DLL(FOG, TraceMemory, void, , (const char* pFileSubName, const char* szMessage, void* pMemory, size_t nByteCount, BOOL bLogOffset, BOOL bNoCopy, BOOL bNoASCII), 0x12210)
// D2FUNC_DLL(FOG, CrashDeadlockDetected, void, , (HANDLE hThreadToWalk), 0xFA10)
// D2FUNC_DLL(FOG, CrashDumpThread, void, , (HANDLE hThreadToWalk), 0x1DE0)
// D2FUNC_DLL(FOG, IsHandlingError, BOOL, , (), 0xF2A0)
// D2FUNC_DLL(FOG, Alloc, void*, , (int nSize, const char* szFile, int nLine, int n0), 0x8F50)
void FOG_Free(void* pFree, const char* szFile, int nLine, int n0);
// D2FUNC_DLL(FOG, Realloc, void, , (void* pMemory, int nSize, const char* szFile, int nLine, int n0), 0x8F90)
void *FOG_AllocPool(void* pMemPool, int nSize, const char* szFile, int nLine, int n0);
void FOG_FreePool(void* pMemPool, void* pFree, const char* szFile, int nLine, int n0);
void* FOG_ReallocPool(void* pMemPool, void* pMemory, int nSize, const char* szFile, int nLine, int n0);
void FOG_10050_EnterCriticalSection(/*_Acquires_lock_(*_Curr_) CRITICAL_SECTION*/void* pCriticalSection, int nLine);
// D2FUNC_DLL(FOG, 10055_GetSyncTime, int32_t, , (), 0xA690)
// // Noop, same as 10048, 10049, 10053, 10054, 10146, 10194, 10195, 10196, 10197, 10220, 10221, 10225, 10232, 10240, 10241, 10242
// D2FUNC_DLL(FOG, 10082_Noop, void, , (), 0x1DE0)
// D2FUNC_DLL(FOG, 10083_Cos_LUT, float, , (int16_t index), 0x1DF0)
// D2FUNC_DLL(FOG, 10084_Sin_LUT, float, , (int16_t index), 0x1E10)
// D2FUNC_DLL(FOG, Decode14BitsFromString, unsigned, , (uint16_t* p2Characters), 0x1B20)
// D2FUNC_DLL(FOG, Encode14BitsToString, void, , (uint16_t* p2Characters, uint32_t value), 0x1B40)
// // Note: works up to value 0xFC05FC00
// D2FUNC_DLL(FOG, Decode32BitsFromString, unsigned, , (uint32_t* p4Characters), 0x1B60)
// D2FUNC_DLL(FOG, Encode32BitsToString, void , , (uint32_t* p4Characters, uint32_t value), 0x1BA0)
// D2FUNC_DLL(FOG, AsyncDataInitialize, void, , (BOOL bEnableAsyncOperations), 0xC010)
// D2FUNC_DLL(FOG, AsyncDataDestroy, void, , (), 0xC0E0)
// D2FUNC_DLL(FOG, AsyncDataLoadFileEx, struct AsyncData*, , (void* pMemPool, const char* pFileName, BOOL bAllowAsync, LONG nFileOffset, int nFileSize, void* pBuffer, struct AsyncDataLoadFileCallback* asyncOpDesc, int a8, const char* sourceFile, int sourceLine), 0xC2B0)
// D2FUNC_DLL(FOG, AsyncDataTestLoaded, BOOL, , (struct AsyncData* pAsyncData), 0xC480)
// D2FUNC_DLL(FOG, AsyncDataWaitAndGetBuffer, void, , (struct AsyncData* pAsyncData), 0xC630)
// D2FUNC_DLL(FOG, AsyncDataGetBuffer, void*, , (struct AsyncData* pAsyncData), 0xC700)
// D2FUNC_DLL(FOG, AsyncDataGetBufferSize, DWORD, , (struct AsyncData* pAsyncData), 0xC790)
// D2FUNC_DLL(FOG, AsyncDataSetResults, void, , (struct AsyncData* pAsyncData, void* pBuffer, int nBufferSize), 0xC7E0)
// D2FUNC_DLL(FOG, AsyncDataFree, void, , (struct AsyncData* pAsyncData), 0xC880)
// D2FUNC_DLL(FOG, AsyncDataSetPriority, void, , (struct AsyncData* pAsyncData, int nPriority), 0xC4E0)
// D2FUNC_DLL(FOG, AsyncDataHandlePriorityChanges, void, , (BOOL bPostpone), 0xC5A0)
// D2FUNC_DLL(FOG, MPQSetConfig, BOOL, , (int dwDirectAccessFlags, int bEnableSeekOptimization), 0x11590)
// D2FUNC_DLL(FOG, FOpenFile, BOOL, , (const char* szFile, HSFILE* pFileHandle), 0x11600)
// D2FUNC_DLL(FOG, FCloseFile, void, , (HSFILE pFile), 0x11610)
// D2FUNC_DLL(FOG, FReadFile, BOOL, , (HSFILE pFile, void* pBuffer, size_t nSize, int* nBytesRead, uint32_t, uint32_t, uint32_t), 0x11620)
// D2FUNC_DLL(FOG, FGetFileSize, uint32_t, , (HSFILE pFileHandle, uint32_t* lpFileSizeHigh), 0x11650)
// D2FUNC_DLL(FOG, FSetFilePointer, size_t, , (HSFILE hFile, int32_t lDistanceToMove, int32_t* lpDistanceToMoveHigh, uint32_t dwMoveMethod), 0x11660)
// D2FUNC_DLL(FOG, CreateFileA, HANDLE, , (LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile), 0x11680);
// D2FUNC_DLL(FOG, DeleteFileA, BOOL, , (LPCSTR lpFileName), 0x116B0);
// D2FUNC_DLL(FOG, CloseFile, BOOL, , (HANDLE hFILE), 0x116C0);
// D2FUNC_DLL(FOG, CreatePathHierarchy, BOOL, , (char* szPath), 0x11730)
// D2FUNC_DLL(FOG, GetSavePath, size_t, , (char* pPathBuffer, size_t nBufferSize), 0x11900)
// D2FUNC_DLL(FOG, GetInstallPath, BOOL, , (char* pPathBuffer, size_t nBufferSize), 0x11870)
// D2FUNC_DLL(FOG, UseDirect, BOOL, , (), 0x11A10)
// D2FUNC_DLL(FOG, ComputeStringCRC16, uint16_t, , (const char* szString), 0x3DB0)
// D2FUNC_DLL(FOG, CreateNewPoolSystem, void, , (void** pMemPoolSystem, const char* szName, uint32_t nPools, uint32_t nUnused), 0xA280)
// D2FUNC_DLL(FOG, DestroyMemoryPoolSystem, void, , (void* pMemoryPoolSystem), 0xA100)
// D2FUNC_DLL(FOG, GetMemoryUsage, DWORD, , (void*), 0xA4E0)
// D2FUNC_DLL(FOG, InitializeServer, QServer*, , (int, int, int, int, void*, void*, void*, void*), 0x4150)
// D2FUNC_DLL(FOG, SetMaxClientsPerGame, int, , (QServer*, int), 0x4970)
// D2FUNC_DLL(FOG, 10152, int, , (void*, const uint8_t*, int), 0x44F0)
// D2FUNC_DLL(FOG, WaitForSingleObject, int, , (void*, int), 0x4A60)
// D2FUNC_DLL(FOG, 10156, int, , (void*, int, uint8_t*, int), 0x59D0)
// D2FUNC_DLL(FOG, 10157, int, , (void*, int, const uint8_t*, int), 0x5EA0)
// D2FUNC_DLL(FOG, 10158, int, , (void*, int), 0x6210)
// D2FUNC_DLL(FOG, 10159, int, , (void*, int, char*, int), 0x6180)
// D2FUNC_DLL(FOG, 10161, int, , (void*, int), 0x6310)
// D2FUNC_DLL(FOG, 10162, int, , (void*, int, const char*, int), 0x6380)
// D2FUNC_DLL(FOG, 10163, int, , (void*, int, const char*, int), 0x66E0)
// D2FUNC_DLL(FOG, 10164, int, , (void*, int, int, int), 0x69D0)
// D2FUNC_DLL(FOG, 10165, int, , (void*, int, const char*, int), 0x6A10)
// D2FUNC_DLL(FOG, 10166, int, , (void*, int, int, int), 0x6C90)
// D2FUNC_DLL(FOG, 10170, int, , (void*, int), 0x6F70)
// D2FUNC_DLL(FOG, 10171, int, , (void*, void*), 0x6FB0)
// D2FUNC_DLL(FOG, 10172, int, , (void*, int, int), 0x6FD0)
// D2FUNC_DLL(FOG, 10173, int, , (void*, int), 0x7040)
// D2FUNC_DLL(FOG, 10175, int, , (void*, const uint8_t*, int, int), 0x7420)
// D2FUNC_DLL(FOG, 10177, int, , (void*, int), 0x5E60)
// D2FUNC_DLL(FOG, SetHackListEnabled, int, , (QServer* pServer, BOOL bHacklistEnabled), 0x75A0)
// D2FUNC_DLL(FOG, 10180, int, , (void*), 0x4920)
// D2FUNC_DLL(FOG, 10181, int, , (void*, const uint8_t*, int, int), 0x75C0)
// D2FUNC_DLL(FOG, 10182_Return, int, , (void*), 0x1B10)
// D2FUNC_DLL(FOG, 10183_Return, int, , (void*, int), 0x7620)
// D2FUNC_DLL(FOG, 10186, int, , (void*, int, int), 0x44C0)
// D2FUNC_DLL(FOG, 10187, int, , (void*, int, int), 0x7630)
// D2FUNC_DLL(FOG, 10207, void, , (struct D2BinFile* pBinFile, struct D2BinField* pBinField, void* pTxt, int nRecordCount, int nRecordSize), 0xAA60)
// D2FUNC_DLL(FOG, CreateBinFile, struct D2BinFile*, , (void* pDataBuffer, int nBufferSize), 0xA8B0)
// D2FUNC_DLL(FOG, FreeBinFile, void, , (struct D2BinFile* pBinFile), 0xAA10)
// D2FUNC_DLL(FOG, GetRecordCountFromBinFile, int, , (struct D2BinFile* pBinFile), 0xAA50)
// D2FUNC_DLL(FOG, AllocLinker, void*, , (const char* szFile, int nLine), 0xB720)
// D2FUNC_DLL(FOG, FreeLinker, void, , (void* pLinker), 0xB750)
// D2FUNC_DLL(FOG, GetLinkIndex, int, , (void* pLink, uint32_t dwCode, BOOL bLogError), 0xB810)
// D2FUNC_DLL(FOG, GetStringFromLinkIndex, int, , (void* pLinker, int nIndex, char* szString), 0xB8F0)
// D2FUNC_DLL(FOG, 10215, int, , (void* pBin, int a2), 0xB990)
// D2FUNC_DLL(FOG, 10216_AddRecordToLinkingTable, int, , (void* pBin, const char* a2), 0xBD80)
// D2FUNC_DLL(FOG, GetRowFromTxt, int, , (void* pBin, char* szText, int nColumn), 0xBC20)
// D2FUNC_DLL(FOG, 10219, int, , (uint8_t*), 0xC9E0)
// D2FUNC_DLL(FOG, 10222, int, , (const uint8_t*, int), 0xCC90)
// D2FUNC_DLL(FOG, 10223, int, , (uint8_t*, int, const uint8_t*, int), 0xCD50)
// D2FUNC_DLL(FOG, 10224, int, , (char*, int, uint8_t*, int), 0xCE00)
// D2FUNC_DLL(FOG, IsExpansion, int, , (), 0xD730)
// D2FUNC_DLL(FOG, ComputeChecksum, uint32_t, , (void* pData, size_t dwSize), 0x3940)
// D2FUNC_DLL(FOG, PopCount, uint32_t, , (void* pData, size_t dwSize), 0x3970)
// D2FUNC_DLL(FOG, 10233, void, , (const char*, int), 0xF300)
// D2FUNC_DLL(FOG, LeadingZeroesCount, uint32_t, , (uint32_t nValue), 0x39A0)
// D2FUNC_DLL(FOG, 10255, char*, , (void* pLinker, int nId, int a3), 0xBB20)


#define D2_ALLOC(size) FOG_Alloc((size), __FILE__, __LINE__, 0)
#define D2_CALLOC(size) memset(FOG_Alloc(size, __FILE__, __LINE__, 0), 0x00, size)
#define D2_ALLOC_STRC(type) (type*)FOG_Alloc(sizeof(type), __FILE__, __LINE__, 0)
#define D2_CALLOC_STRC(type) (type*)memset(FOG_Alloc(sizeof(type), __FILE__, __LINE__, 0), 0x00, sizeof(type))
#define D2_FREE(ptr) FOG_Free(ptr, __FILE__, __LINE__, 0)


#define D2_ALLOC_POOL(pMemPool, size) FOG_AllocPool(pMemPool, size, __FILE__, __LINE__, 0)
#define D2_CALLOC_POOL(pMemPool, size) memset(FOG_AllocPool(pMemPool, size, __FILE__, __LINE__, 0),0x00,size)
#define D2_REALLOC_POOL(pMemPool, pMem, size) FOG_ReallocPool(pMemPool, pMem, size, __FILE__, __LINE__, 0)
#define D2_ALLOC_STRC_POOL(pMemPool, type) (type*)FOG_AllocPool(pMemPool, sizeof(type), __FILE__, __LINE__, 0)
#define D2_CALLOC_STRC_POOL(pMemPool, type) (type*)memset(FOG_AllocPool(pMemPool, sizeof(type), __FILE__, __LINE__, 0), 0x00, sizeof(type))
#define D2_FREE_POOL(pMemPool, ptr) FOG_FreePool(pMemPool, ptr, __FILE__, __LINE__, 0)

#ifndef NDEBUG
// Assert that an expression must be true, otherwise assume the program state will not be recoverable.
// In debug builds, this will trigger a log and exit, in release this is used as a hint for performance optimization.
// Do NOT use this if the program can recover when expr if false, as it is used as a hint for performance and can impact generated code.
// For recoverable errors, use D2_VERIFY
#define D2_DISPLAY_ASSERT_THEN_BREAK(msg) \
    (FOG_DisplayAssert(msg, __FILE__, __LINE__), /* __debugbreak */ __builtin_debugtrap())
#define D2_ASSERT(expr) (void)( (!!(expr)) || (D2_DISPLAY_ASSERT_THEN_BREAK(#expr), exit(-1) , 0))/*; _Analysis_assume_(expr)*/
#define D2_ASSERTM(expr,msg) (void)( (!!(expr)) || (D2_DISPLAY_ASSERT_THEN_BREAK(msg), exit(-1) , 0))/*; _Analysis_assume_(expr)*/
#define D2_CHECK(expr) (void)( (!!(expr)) || (FOG_DisplayWarning(#expr, __FILE__, __LINE__), 0))/*; _Analysis_assume_(expr)*/


// Assert that an expression must be true, even though the program may be recoverable.
// Contrary to D2_ASSERT, this is still evaluated in release builds, and can be used anywhere the expression would be valid.
// This is to be used when one can recover from an error
// Example:
// if(D2_VERIFY(ptr != nullptr)) ptr->method(); // The only difference between debug and release build is the logging and breakpoint
#define D2_VERIFY(expr) ((!!(expr)) || (D2_DISPLAY_ASSERT_THEN_BREAK(#expr), false))
#define D2_VERIFYM(expr,msg) ((!!(expr)) || (D2_DISPLAY_ASSERT_THEN_BREAK(msg), false))
#else
  #if defined(__clang__)
    // the argument to '__builtin_assume' has side effects that will be discarded
    #pragma clang diagnostic ignored "-Wassume"
  #endif // defined(__clang__)
#define D2_ASSERT(expr) (__assume(expr), (void)0)
#define D2_ASSERTM(expr,msg) (__assume(expr), (void)0)
#define D2_VERIFY(expr) (!!(expr))
#define D2_VERIFYM(expr,msg) (!!(expr))
#define D2_CHECK(expr) (__assume(expr), (void)0)
#endif
#define D2_UNREACHABLE D2_ASSERT(false)


#define D2_LOCK(pCriticalSection) D2_ASSERT(pCriticalSection); FOG_10050_EnterCriticalSection(pCriticalSection, __LINE__);
#define D2_UNLOCK(pCriticalSection) D2_ASSERT(pCriticalSection); LeaveCriticalSection(pCriticalSection);
