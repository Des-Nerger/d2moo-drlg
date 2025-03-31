const assert = debug.assert;
const c = @import("c.zig");
// const d2cmp = @This();
const debug = std.debug;
const fs = std.fs;
const io = std.io;
const main = @import("main.zig");
const mem = std.mem;
const std = @import("std");

pub fn D2CMP_10087_LoadTileLibrarySlot(
    ppTileLibraryHash: [*c][*c]c.D2TileLibraryHash,
    szFileName: [*c]const u8,
) callconv(.c) void {
    debug.print("{s}('{s}')\n", .{ @src().fn_name, szFileName });
    errdefer unreachable;

    const file = try fs.cwd().openFileZ(szFileName, .{});
    defer file.close();

    var br = io.bufferedReader(file.reader());
    const r = br.reader();

    const he = try r.readStruct(c.D2TileLibraryHeader);
    assert(7 == he.dwVersion and 6 == he.dwFlags);
    assert(mem.allEqual(u8, he.szLibraryName[0..], 0));
    assert(br.buf.len > he.dwTileStart_pFirst and he.dwTileStart_pFirst == br.start);

    var hash = try main.allocator.create(c.D2TileLibraryHash);
    @memset(&hash.pNodes, null);
    {
        var hashes = ppTileLibraryHash;
        while (hashes.* != null) hashes += 1;
        hashes.* = hash;
    }

    const entries = try main.allocator.alloc(c.D2TileLibraryEntry, @intCast(he.nTiles));
    for (entries) |*en| {
        en.* = try r.readStruct(@TypeOf(en.*));
        inline for (
            .{ "nHeightToBottom", "nZeroByte", "nCacheIndex", "unk0x44", "pBlock", "pLRUCacheBlock" },
        ) |field_name| assert(mem.allEqual(u8, mem.asBytes(&@field(en, field_name)), 0));
    }
    // const hash_idx = d2cmp.findTileHashFunction(subInd_seq, ind_style, orient_type);
}

// fn findTileHashFunction() {
// }

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
