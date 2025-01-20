const c = @import("c.zig");
const math = std.math;
const std = @import("std");

pub fn FOG_AllocPool(
    pMemPool: ?*anyopaque,
    nSize: c_int,
    szFile: [*c]const u8,
    nLine: c_int,
    n0: c_int,
) callconv(.{ .x86_fastcall = .{} }) ?*anyopaque {
    _ = .{ pMemPool, nSize, szFile, nLine, n0 };
    return null;
}

pub fn FOG_FreePool(
    pMemPool: ?*anyopaque,
    pFree: ?*anyopaque,
    szFile: [*c]const u8,
    nLine: c_int,
    n0: c_int,
) callconv(.{ .x86_fastcall = .{} }) void {
    _ = .{ pMemPool, pFree, szFile, nLine, n0 };
}

pub fn FOG_DisplayAssert(szMsg: [*c]const u8, szFile: [*c]const u8, nLine: c_int) callconv(.c) void {
    _ = .{ szMsg, szFile, nLine };
}

pub fn FOG_Trace(szFormat: [*c]const u8, ...) callconv(.c) void {
    _ = szFormat;
}

pub fn FOG_DisplayHalt(szMsg: [*c]const u8, szFile: [*c]const u8, nLine: c_int) callconv(.c) void {
    _ = .{ szMsg, szFile, nLine };
}

pub fn FOG_DisplayWarning(szMsg: [*c]const u8, szFile: [*c]const u8, nLine: c_int) callconv(.c) void {
    _ = .{ szMsg, szFile, nLine };
}

pub fn FOG_DisplayError(
    nCategory: c_int,
    szMsg: [*c]const u8,
    szFile: [*c]const u8,
    nLine: c_int,
) callconv(.c) void {
    _ = .{ nCategory, szMsg, szFile, nLine };
}

pub fn FOG_Alloc(
    nSize: c_int,
    szFile: [*c]const u8,
    nLine: c_int,
    n0: c_int,
) callconv(.{ .x86_fastcall = .{} }) ?*anyopaque {
    _ = .{ nSize, szFile, nLine, n0 };
    return null;
}

pub fn FOG_Free(
    pFree: ?*anyopaque,
    szFile: [*c]const u8,
    nLine: c_int,
    n0: c_int,
) callconv(.{ .x86_fastcall = .{} }) void {
    _ = .{ pFree, szFile, nLine, n0 };
}

pub fn FOG_ReallocPool(
    pMemPool: ?*anyopaque,
    pMemory: ?*anyopaque,
    nSize: c_int,
    szFile: [*c]const u8,
    nLine: c_int,
    n0: c_int,
) callconv(.{ .x86_fastcall = .{} }) ?*anyopaque {
    _ = .{ pMemPool, pMemory, nSize, szFile, nLine, n0 };
    return null;
}

pub fn FOG_10050_EnterCriticalSection(
    pCriticalSection: [*c]c.CRITICAL_SECTION,
    nLine: c_int,
) callconv(.{ .x86_fastcall = .{} }) void {
    _ = .{ pCriticalSection, nLine };
}

pub fn FOG_FOpenFile(
    szFile: [*c]const u8,
    pFileHandle: [*c]c.HSFILE,
) callconv(.{ .x86_fastcall = .{} }) c.BOOL {
    _ = .{ szFile, pFileHandle };
    return @intFromBool(false);
}

pub fn FOG_FCloseFile(pFile: c.HSFILE) callconv(.{ .x86_fastcall = .{} }) void {
    _ = .{pFile};
}

pub fn FOG_FReadFile(
    pFile: c.HSFILE,
    pBuffer: ?*anyopaque,
    nSize: usize,
    nBytesRead: [*c]c_int,
    n0: u32,
    n1: u32,
    n2: u32,
) callconv(.{ .x86_fastcall = .{} }) c.BOOL {
    _ = .{ pFile, pBuffer, nSize, nBytesRead, n0, n1, n2 };
    return @intFromBool(false);
}

pub fn FOG_FGetFileSize(
    pFileHandle: c.HSFILE,
    lpFileSizeHigh: [*c]u32,
) callconv(.{ .x86_fastcall = .{} }) u32 {
    _ = .{ pFileHandle, lpFileSizeHigh };
    return 0;
}

pub fn FOG_FSetFilePointer(
    hFile: c.HSFILE,
    lDistanceToMove: i32,
    lpDistanceToMoveHigh: [*c]i32,
    dwMoveMethod: u32,
) callconv(.{ .x86_fastcall = .{} }) usize {
    _ = .{ hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod };
    return 0;
}

pub fn FOG_10207(
    pBinFile: [*c]c.D2BinFile,
    pBinField: [*c]c.D2BinField,
    pTxt: ?*anyopaque,
    nRecordCount: c_int,
    nRecordSize: c_int,
) callconv(.{ .x86_stdcall = .{} }) void {
    _ = .{ pBinFile, pBinField, pTxt, nRecordCount, nRecordSize };
}

pub fn FOG_CreateBinFile(
    pDataBuffer: ?*anyopaque,
    nBufferSize: c_int,
) callconv(.{ .x86_stdcall = .{} }) [*c]c.D2BinFile {
    _ = .{ pDataBuffer, nBufferSize };
    return null;
}

pub fn FOG_FreeBinFile(pBinFile: [*c]c.D2BinFile) callconv(.{ .x86_stdcall = .{} }) void {
    _ = .{pBinFile};
}

pub fn FOG_GetRecordCountFromBinFile(pBinFile: [*c]c.D2BinFile) callconv(.{ .x86_stdcall = .{} }) c_int {
    _ = .{pBinFile};
    return -1;
}

pub fn FOG_AllocLinker(szFile: [*c]const u8, nLine: c_int) callconv(.{ .x86_stdcall = .{} }) ?*anyopaque {
    _ = .{ szFile, nLine };
    return null;
}

pub fn FOG_FreeLinker(pLinker: ?*anyopaque) callconv(.{ .x86_stdcall = .{} }) void {
    _ = .{pLinker};
}

pub fn FOG_IsExpansion() callconv(.{ .x86_fastcall = .{} }) c_int {
    return @intFromBool(true);
}

pub fn FOG_csprintf(szDest: [*c]u8, szFormat: [*c]const u8, ...) callconv(.C) [*c]const u8 {
    _ = .{ szDest, szFormat };
    return null;
}

pub fn FOG_GetLinkIndex(
    pLink: ?*anyopaque,
    dwCode: u32,
    bLogError: c.BOOL,
) callconv(.{ .x86_stdcall = .{} }) c_int {
    _ = .{ pLink, dwCode, bLogError };
    return -1;
}

pub fn FOG_GetStringFromLinkIndex(
    pLinker: ?*anyopaque,
    nIndex: c_int,
    szString: [*c]u8,
) callconv(.{ .x86_stdcall = .{} }) c_int {
    _ = .{ pLinker, nIndex, szString };
    return 0;
}

pub fn FOG_10215(pBin: ?*anyopaque, a2: c_int) callconv(.{ .x86_stdcall = .{} }) c_int {
    _ = .{ pBin, a2 };
    return -1;
}

pub fn FOG_10216_AddRecordToLinkingTable(
    pBin: ?*anyopaque,
    a2: [*c]const u8,
) callconv(.{ .x86_stdcall = .{} }) c_int {
    _ = .{ pBin, a2 };
    return -1;
}

pub fn FOG_GetRowFromTxt(
    pBin: ?*anyopaque,
    szText: [*c]u8,
    nColumn: c_int,
) callconv(.{ .x86_stdcall = .{} }) c_int {
    _ = .{ pBin, szText, nColumn };
    return -1;
}

pub fn FOG_10255(
    pLinker: ?*anyopaque,
    nId: c_int,
    a3: c_int,
) callconv(.{ .x86_stdcall = .{} }) [*c]u8 {
    _ = .{ pLinker, nId, a3 };
    return null;
}

pub fn FOG_10083_Cos_LUT(index: i16) callconv(.{ .x86_stdcall = .{} }) f32 {
    _ = .{index};
    return math.nan(f32);
}

pub fn FOG_10084_Sin_LUT(index: i16) callconv(.{ .x86_stdcall = .{} }) f32 {
    _ = .{index};
    return math.nan(f32);
}
