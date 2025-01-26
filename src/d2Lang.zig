const c = @import("c.zig");
const debug = std.debug;
const std = @import("std");

pub fn D2LANG_GetStringByReferenceString(string: [*c]u8) callconv(.c) ?*const c.Unicode {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{string};
    return null;
}

pub fn D2LANG_GetStringFromTblIndex(index: c_short) callconv(.c) ?*const c.Unicode {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{index};
    return null;
}

pub fn D2LANG_GetTblIndex(
    szReference: [*c]u8,
    pUnicode: [*c]?*const c.Unicode,
) callconv(.c) c_short {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ szReference, pUnicode };
    return -1;
}
