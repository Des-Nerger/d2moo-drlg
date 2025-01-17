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
