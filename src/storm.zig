const c = @import("c.zig");
const debug = std.debug;
const std = @import("std");

pub fn SFileCloseArchive(hArchive: c.HSARCHIVE) callconv(.c) c.BOOL {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{hArchive};
    return @intFromBool(false);
}

pub fn SFileOpenArchive(
    szName: [*c]u8,
    nPriority: c_int,
    nFlags: c_int,
    pArchive: [*c]c.HSARCHIVE,
) callconv(.c) c.BOOL {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ szName, nPriority, nFlags, pArchive };
    return @intFromBool(false);
}

pub fn SFileGetFileName(
    hFile: c.HANDLE,
    buffer: [*c]u8,
    length: c_int,
) callconv(.c) c.BOOL {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ hFile, buffer, length };
    return @intFromBool(false);
}

pub fn SStrCmpI(
    Str1: [*c]const u8,
    Str: [*c]const u8,
    MaxCount: usize,
) callconv(.c) i32 {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ Str1, Str, MaxCount };
    return 0;
}

pub fn SStrNCat(
    base: [*c]u8,
    append: [*c]const u8,
    max_length: c_int,
) callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
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
) callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ pBuffer, nBufferCount, szSrc, nSrcCount, pOutLength, a6 };
    return 0;
}
