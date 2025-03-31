const assert = debug.assert;
const c = @import("c.zig");
const debug = std.debug;
const heap = std.heap;
const mem = std.mem;
const process = std.process;
const std = @import("std");

pub var allocator: mem.Allocator = arena.allocator();
var arena = heap.ArenaAllocator.init(heap.page_allocator);
fn arenaReset() void {
    if (!arena.reset(.retain_capacity))
        debug.print("ArenaAllocator pre-heating failed: no big deal", .{});
}

pub fn main() !void {
    _ = allocator.alloc(u8, 64 * 1024 * 1024) catch unreachable;
    arenaReset();
    defer {
        debug.print("ArenaAllocator will deinit {} bytes\n", .{arena.queryCapacity()});
        assert(true == arena.reset(.free_all));
        debug.print("now it's {} bytes\n", .{arena.queryCapacity()});
    }

    const args = try process.argsAlloc(allocator);
    defer process.argsFree(allocator, args);

    assert(0 == std.c.chdir(args[1])); // FIXME to posix.chdir
    {
        const resulted_cwd = try process.getCwdAlloc(allocator);
        defer arenaReset();
        debug.print("cd /d '{s}'\n", .{resulted_cwd});
        assert(mem.eql(u8, mem.trimRight(u8, args[1], "\\"), resulted_cwd));
    }

    const hArchive: c.HD2ARCHIVE = null;
    {
        const a2, const a3 = .{ 1, 0 };
        // c.DATATBLS_LoadAllTxts(hArchive, a2, a3);
        c.DATATBLS_LoadMonPresetTxt(hArchive);
        c.DATATBLS_LoadLevelsTxt(hArchive);
        c.DATATBLS_LoadLevelDefsBin(hArchive);
        c.DATATBLS_LoadLvlPrestTxt(hArchive, a2);
        c.DATATBLS_LoadLvlMazeTxt(hArchive);
        c.DATATBLS_LoadLvlSubTxt(hArchive, a2, a3);
        c.DATATBLS_LoadObjectsTxt(hArchive);
    }
    debug.print("datatbls_load_success\n", .{});

    var act = c.D2DrlgAct{
        .nAct = c.ACT_I,
        .dwInitSeed = 42,
        .nTownId = c.LEVEL_CATACOMBSLEV1, //
        // c.LEVEL_DENOFEVIL, // c.LEVEL_BLOODMOOR, // c.LEVEL_TOWERCELLARLEV5, //
        // c.LEVEL_BURIALGROUNDS, // c.LEVEL_ROGUEENCAMPMENT, //
        // c.LEVEL_CRYPT, // c.LEVEL_JAILLEV3, //
    };
    const pDrlg = c.DRLG_AllocDrlg(
        &act,
        act.nAct,
        hArchive,
        act.dwInitSeed,
        act.nTownId,
        0, // flags
        null, // game
        c.DIFFMODE_NORMAL,
        null, // auto_map
        null, // town_auto_map
    ).?;
    defer c.DRLG_FreeDrlg(pDrlg);
    assert(pDrlg.*.nAct == act.nAct);
}
