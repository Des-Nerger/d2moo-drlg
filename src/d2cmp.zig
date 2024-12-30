const c = @import("c.zig");

pub fn D2CMP_10087_LoadTileLibrarySlot(
    ppTileLibraryHash: [*c][*c]c.D2TileLibraryHash,
    szFileName: [*c]const u8,
) callconv(.{ .x86_stdcall = .{} }) void {
    _ = .{ ppTileLibraryHash, szFileName };
}
