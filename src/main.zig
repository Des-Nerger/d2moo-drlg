const assert = debug.assert;
const c = @import("c.zig");
const debug = std.debug;
const std = @import("std");

pub fn main() void {
    var act = c.D2DrlgAct{
        .nAct = c.ACT_I,
        .dwInitSeed = 0,
        .nTownId = c.D2TOWN_ROGUECAMP,
    };
    const pDrlg = c.DRLG_AllocDrlg(
        &act,
        act.nAct,
        null, // archive
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
