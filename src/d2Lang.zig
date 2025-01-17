const c = @import("c.zig");

pub fn D2LANG_GetStringByReferenceString(string: [*c]u8) callconv(.{ .x86_fastcall = .{} }) ?*const c.Unicode {
    _ = .{string};
    return null;
}

pub fn D2LANG_GetStringFromTblIndex(index: c_short) callconv(.{ .x86_fastcall = .{} }) ?*const c.Unicode {
    _ = .{index};
    return null;
}

pub fn D2LANG_GetTblIndex(
    szReference: [*c]u8,
    pUnicode: [*c]?*const c.Unicode,
) callconv(.{ .x86_stdcall = .{} }) c_short {
    _ = .{ szReference, pUnicode };
    return -1;
}
