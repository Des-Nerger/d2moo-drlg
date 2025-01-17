const c = @import("c.zig");

pub fn SFileCloseArchive(hArchive: c.HSARCHIVE) callconv(.{ .x86_stdcall = .{} }) c.BOOL {
    _ = .{hArchive};
    return @intFromBool(false);
}

pub fn SFileOpenArchive(
    szName: [*c]u8,
    nPriority: c_int,
    nFlags: c_int,
    pArchive: [*c]c.HSARCHIVE,
) callconv(.{ .x86_stdcall = .{} }) c.BOOL {
    _ = .{ szName, nPriority, nFlags, pArchive };
    return @intFromBool(false);
}

pub fn SFileGetFileName(
    hFile: c.HANDLE,
    buffer: [*c]u8,
    length: c_int,
) callconv(.{ .x86_stdcall = .{} }) c.BOOL {
    _ = .{ hFile, buffer, length };
    return @intFromBool(false);
}

pub fn SStrCmpI(
    Str1: [*c]const u8,
    Str: [*c]const u8,
    MaxCount: usize,
) callconv(.{ .x86_stdcall = .{} }) i32 {
    _ = .{ Str1, Str, MaxCount };
    return 0;
}

pub fn SStrNCat(
    base: [*c]u8,
    append: [*c]const u8,
    max_length: c_int,
) callconv(.{ .x86_stdcall = .{} }) c_int {
    _ = .{ base, append, max_length };
    return 0;
}

pub fn SUniConvertUTF8to16(
    pBuffer: [*c]c.wchar_t,
    nBufferCount: c_int,
    szSrc: [*c]const u8,
    nSrcCount: c_int,
    pOutLength: [*c]c_int,
    a6: c_int,
) callconv(.{ .x86_stdcall = .{} }) c_int {
    _ = .{ pBuffer, nBufferCount, szSrc, nSrcCount, pOutLength, a6 };
    return 0;
}
