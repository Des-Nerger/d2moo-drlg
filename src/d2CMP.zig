const c = @import("c.zig");
const debug = std.debug;
const std = @import("std");

pub fn D2CMP_10087_LoadTileLibrarySlot(
    ppTileLibraryHash: [*c][*c]c.D2TileLibraryHash,
    szFileName: [*c]const u8,
) callconv(.c) void {
    debug.print("{s}: \"{s}\"\n", .{ @src().fn_name, szFileName });
    _ = .{ ppTileLibraryHash, szFileName };
}

pub fn D2CMP_10085_GetTileFlagArray(
    pTileLibraryEntry: [*c]c.D2TileLibraryEntry,
) callconv(.c) [*c]u8 {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{pTileLibraryEntry};
    return null;
}

pub fn D2CMP_10078_GetTileStyle(
    pTileLibraryEntry: [*c]c.D2TileLibraryEntry,
) callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{pTileLibraryEntry};
    return -1;
}

pub fn D2CMP_10079_GetTileFlags(
    pTileLibraryEntry: [*c]c.D2TileLibraryEntry,
) callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{pTileLibraryEntry};
    return -1;
}

pub fn D2CMP_10081_GetTileRarity(
    pTileLibraryEntry: [*c]c.D2TileLibraryEntry,
) callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{pTileLibraryEntry};
    return -1;
}

pub fn D2CMP_10082_GetTileSequence(
    pTileLibraryEntry: [*c]c.D2TileLibraryEntry,
) callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{pTileLibraryEntry};
    return -1;
}

pub fn D2CMP_10088_GetTiles(
    ppTileLibraryHash: [*c][*c]c.D2TileLibraryHash,
    nType: c_int,
    nStyle: c_int,
    nSequence: c_int,
    pTileList: [*c][*c]c.D2TileLibraryEntry,
    nTileListSize: c_int,
) callconv(.c) c_int {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ ppTileLibraryHash, nType, nStyle, nSequence, pTileList, nTileListSize };
    return 0;
}

pub fn D2CMP_MixPalette(nTrans: u8, nColor: c_int) callconv(.c) [*c]u8 {
    debug.print("{s}\n", .{@src().fn_name});
    _ = .{ nTrans, nColor };
    return null;
}
