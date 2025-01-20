const c = @import("c.zig");

pub fn D2CMP_10087_LoadTileLibrarySlot(
    ppTileLibraryHash: [*c][*c]c.D2TileLibraryHash,
    szFileName: [*c]const u8,
) callconv(.{ .x86_stdcall = .{} }) void {
    _ = .{ ppTileLibraryHash, szFileName };
}

pub fn D2CMP_10085_GetTileFlagArray(
    pTileLibraryEntry: [*c]c.D2TileLibraryEntry,
) callconv(.{ .x86_stdcall = .{} }) [*c]u8 {
    _ = .{pTileLibraryEntry};
    return null;
}

pub fn D2CMP_10078_GetTileStyle(
    pTileLibraryEntry: [*c]c.D2TileLibraryEntry,
) callconv(.{ .x86_stdcall = .{} }) c_int {
    _ = .{pTileLibraryEntry};
    return -1;
}

pub fn D2CMP_10079_GetTileFlags(
    pTileLibraryEntry: [*c]c.D2TileLibraryEntry,
) callconv(.{ .x86_stdcall = .{} }) c_int {
    _ = .{pTileLibraryEntry};
    return -1;
}

pub fn D2CMP_10081_GetTileRarity(
    pTileLibraryEntry: [*c]c.D2TileLibraryEntry,
) callconv(.{ .x86_stdcall = .{} }) c_int {
    _ = .{pTileLibraryEntry};
    return -1;
}

pub fn D2CMP_10082_GetTileSequence(
    pTileLibraryEntry: [*c]c.D2TileLibraryEntry,
) callconv(.{ .x86_stdcall = .{} }) c_int {
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
) callconv(.{ .x86_stdcall = .{} }) c_int {
    _ = .{ ppTileLibraryHash, nType, nStyle, nSequence, pTileList, nTileListSize };
    return 0;
}

pub fn D2CMP_MixPalette(nTrans: u8, nColor: c_int) callconv(.{ .x86_stdcall = .{} }) [*c]u8 {
    _ = .{ nTrans, nColor };
    return null;
}
