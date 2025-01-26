const c = @import("c.zig");
const debug = std.debug;
const math = std.math;
const std = @import("std");

pub fn FOG_AllocPool(
    pMemPool: ?*anyopaque,
    nSize: c_int,
    szFile: [*c]const u8,
    nLine: c_int,
    n0: c_int,
) callconv(.c) ?*anyopaque {
    _ = .{ pMemPool, szFile, nLine, n0 };
    return c.malloc(@intCast(nSize));
}

pub fn FOG_FreePool(
    pMemPool: ?*anyopaque,
    pFree: ?*anyopaque,
    szFile: [*c]const u8,
    nLine: c_int,
    n0: c_int,
) callconv(.c) void {
    _ = .{ pMemPool, szFile, nLine, n0 };
    c.free(pFree);
}

pub fn FOG_DisplayAssert(szMsg: [*c]const u8, szFile: [*c]const u8, nLine: c_int) callconv(.c) void {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ szMsg, szFile, nLine };
}

pub fn FOG_Trace(szFormat: [*c]const u8, ...) callconv(.c) void {
    debug.print("{s}\n", .{@src().fn_name});
    _ = szFormat;
}

pub fn FOG_DisplayHalt(szMsg: [*c]const u8, szFile: [*c]const u8, nLine: c_int) callconv(.c) void {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ szMsg, szFile, nLine };
}

pub fn FOG_DisplayWarning(szMsg: [*c]const u8, szFile: [*c]const u8, nLine: c_int) callconv(.c) void {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ szMsg, szFile, nLine };
}

pub fn FOG_DisplayError(
    nCategory: c_int,
    szMsg: [*c]const u8,
    szFile: [*c]const u8,
    nLine: c_int,
) callconv(.c) void {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ nCategory, szMsg, szFile, nLine };
}

pub fn FOG_Alloc(
    nSize: c_int,
    szFile: [*c]const u8,
    nLine: c_int,
    n0: c_int,
) callconv(.c) ?*anyopaque {
    _ = .{ szFile, nLine, n0 };
    return c.malloc(@intCast(nSize));
}

pub fn FOG_Free(
    pFree: ?*anyopaque,
    szFile: [*c]const u8,
    nLine: c_int,
    n0: c_int,
) callconv(.c) void {
    _ = .{ szFile, nLine, n0 };
    return c.free(pFree);
}

pub fn FOG_ReallocPool(
    pMemPool: ?*anyopaque,
    pMemory: ?*anyopaque,
    nSize: c_int,
    szFile: [*c]const u8,
    nLine: c_int,
    n0: c_int,
) callconv(.c) ?*anyopaque {
    _ = .{ pMemPool, szFile, nLine, n0 };
    return c.realloc(pMemory, @intCast(nSize));
}

pub fn FOG_10050_EnterCriticalSection(
    pCriticalSection: [*c]c.CRITICAL_SECTION,
    nLine: c_int,
) callconv(.c) void {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ pCriticalSection, nLine };
}

pub fn FOG_FOpenFile(
    szFile: [*c]const u8,
    pFileHandle: [*c]c.HSFILE,
) callconv(.c) c.BOOL {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ szFile, pFileHandle };
    return @intFromBool(false);
}

pub fn FOG_FCloseFile(pFile: c.HSFILE) callconv(.c) void {
    debug.print("{s}\n", .{@src().fn_name});
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
) callconv(.c) c.BOOL {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ pFile, pBuffer, nSize, nBytesRead, n0, n1, n2 };
    return @intFromBool(false);
}

pub fn FOG_FGetFileSize(
    pFileHandle: c.HSFILE,
    lpFileSizeHigh: [*c]u32,
) callconv(.c) u32 {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ pFileHandle, lpFileSizeHigh };
    return 0;
}

pub fn FOG_FSetFilePointer(
    hFile: c.HSFILE,
    lDistanceToMove: i32,
    lpDistanceToMoveHigh: [*c]i32,
    dwMoveMethod: u32,
) callconv(.c) usize {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod };
    return 0;
}

pub fn FOG_10207(
    pBinFile: [*c]c.D2BinFile,
    pBinField: [*c]c.D2BinField,
    pTxt: ?*anyopaque,
    nRecordCount: c_int,
    nRecordSize: c_int,
) callconv(.c) void {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ pBinFile, pBinField, pTxt, nRecordCount, nRecordSize };
}

pub fn FOG_CreateBinFile(
    pDataBuffer: ?*anyopaque,
    nBufferSize: c_int,
) callconv(.c) [*c]c.D2BinFile {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ pDataBuffer, nBufferSize };
    return null;
}

pub fn FOG_FreeBinFile(pBinFile: [*c]c.D2BinFile) callconv(.c) void {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{pBinFile};
}

pub fn FOG_GetRecordCountFromBinFile(pBinFile: [*c]c.D2BinFile) callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{pBinFile};
    return -1;
}

pub fn FOG_AllocLinker(szFile: [*c]const u8, nLine: c_int) callconv(.c) ?*anyopaque {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ szFile, nLine };
    return null;
}

pub fn FOG_FreeLinker(pLinker: ?*anyopaque) callconv(.c) void {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{pLinker};
}

pub fn FOG_IsExpansion() callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
    return @intFromBool(true);
}

pub fn FOG_csprintf(szDest: [*c]u8, szFormat: [*c]const u8, ...) callconv(.c) [*c]const u8 {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ szDest, szFormat };
    return null;
}

pub fn FOG_GetLinkIndex(
    pLink: ?*anyopaque,
    dwCode: u32,
    bLogError: c.BOOL,
) callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ pLink, dwCode, bLogError };
    return -1;
}

pub fn FOG_GetStringFromLinkIndex(
    pLinker: ?*anyopaque,
    nIndex: c_int,
    szString: [*c]u8,
) callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ pLinker, nIndex, szString };
    return 0;
}

pub fn FOG_10215(pBin: ?*anyopaque, a2: c_int) callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ pBin, a2 };
    return -1;
}

pub fn FOG_10216_AddRecordToLinkingTable(
    pBin: ?*anyopaque,
    a2: [*c]const u8,
) callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ pBin, a2 };
    return -1;
}

pub fn FOG_GetRowFromTxt(
    pBin: ?*anyopaque,
    szText: [*c]u8,
    nColumn: c_int,
) callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ pBin, szText, nColumn };
    return -1;
}

pub fn FOG_10255(
    pLinker: ?*anyopaque,
    nId: c_int,
    a3: c_int,
) callconv(.c) [*c]u8 {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ pLinker, nId, a3 };
    return null;
}

pub fn FOG_10083_Cos_LUT(index: i16) callconv(.c) f32 {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{index};
    return math.nan(f32);
}

pub fn FOG_10084_Sin_LUT(index: i16) callconv(.c) f32 {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{index};
    return math.nan(f32);
}
