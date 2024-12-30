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

pub fn FOG_DisplayAssert(szMsg: [*c]const u8, szFile: [*c]const u8, nLine: c_int) callconv(.c) void {
    _ = .{ szMsg, szFile, nLine };
}

pub fn FOG_Trace(szFormat: [*c]const u8, ...) callconv(.c) void {
    _ = szFormat;
}
