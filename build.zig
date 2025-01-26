const Build = std.Build;
const std = @import("std");

pub fn build(b: *Build) void {
    const exe = b.addExecutable(.{
        .name = "d2moo-drlg",
        .root_module = b.createModule(.{
            .root_source_file = b.path("src/main.zig"),
            .target = b.standardTargetOptions(.{
                .default_target = .{
                    .cpu_arch = .x86, // if (builtin.cpu.arch.isAARCH64() or builtin.cpu.arch.isArm()) .thumb
                    .os_tag = .windows,
                    .abi = .gnu,
                },
                .whitelist = &.{
                    // .{ .cpu_arch = .aarch64, .os_tag = .windows, .abi = .gnu },
                    // .{ .cpu_arch = .thumb, .os_tag = .windows, .abi = .gnu },
                    .{ .cpu_arch = .x86, .os_tag = .windows, .abi = .gnu },
                    // .{ .cpu_arch = .x86_64, .os_tag = .windows, .abi = .gnu },
                },
            }),
            .optimize = b.standardOptimizeOption(.{ .preferred_optimize_mode = .ReleaseSafe }),
        }),
    });
    exe.want_lto = false;
    exe.linkLibC();
    exe.addIncludePath(b.path("include"));
    for ([_]struct { []const u8, []const u8 }{
        .{ "D2CMP_DLL_DECL", "" },
        .{ "D2COMMON_DLL_DECL", "" },
        .{ "D2LANG_DLL_DECL", "" },
        .{ "FOG_DLL_DECL", "" },
        .{ "STORM_DLL_DECL", "" },
    }) |key_value|
        @call(.auto, Build.Module.addCMacro, .{exe.root_module} ++ key_value);
    exe.addCSourceFiles(.{
        .flags = &.{ "-O", "-std=c23" },
        .root = b.path("src"),
        .files = &.{
            "Archive.c",
            "BitManip/BitManip.c",
            "Calc.c",
            "D2Collision.c",
            "D2Composit.c",
            "D2Dungeon.c",
            "D2Environment.c",
            "D2Inventory.c",
            "D2QuestRecord.c",
            "D2Seed.c",
            "D2Skills.c",
            "D2StatList.c",
            "D2States.c",
            "D2StrTable.c",
            "D2Unicode/D2UnicodeChar.c",
            "D2Unicode/D2UnicodeStr.c",
            "D2Unicode/D2UnicodeUtf.c",
            "D2Unicode/D2UnicodeWin.c",
            "D2Waypoints.c",
            "DataTbls/AnimTbls.c",
            "DataTbls/ArenaTbls.c",
            "DataTbls/BeltsTbls.c",
            "DataTbls/DataTbls.c",
            "DataTbls/FieldTbls.c",
            "DataTbls/HoradricCube.c",
            "DataTbls/InvTbls.c",
            "DataTbls/ItemsTbls.c",
            "DataTbls/LevelsTbls.c",
            "DataTbls/MissilesTbls.c",
            "DataTbls/MonsterTbls.c",
            "DataTbls/ObjectsTbls.c",
            "DataTbls/OverlayTbls.c",
            "DataTbls/SequenceTbls.c",
            "DataTbls/SkillsTbls.c",
            "DataTbls/TokenTbls.c",
            "Drlg/DrlgActivate.c",
            "Drlg/DrlgDrlg.c",
            "Drlg/DrlgDrlgAnim.c",
            "Drlg/DrlgDrlgGrid.c",
            "Drlg/DrlgDrlgLogic.c",
            "Drlg/DrlgDrlgRoom.c",
            "Drlg/DrlgDrlgVer.c",
            "Drlg/DrlgDrlgWarp.c",
            "Drlg/DrlgMaze.c",
            "Drlg/DrlgOutDesr.c",
            "Drlg/DrlgOutJung.c",
            "Drlg/DrlgOutPlace.c",
            "Drlg/DrlgOutRoom.c",
            "Drlg/DrlgOutSiege.c",
            "Drlg/DrlgOutWild.c",
            "Drlg/DrlgOutdoors.c",
            "Drlg/DrlgPreset.c",
            "Drlg/DrlgRoomTile.c",
            "Drlg/DrlgTileSub.c",
            "File.c",
            "Items/ItemMods.c",
            "Items/Items.c",
            "Monsters/Monsters.c",
            "Path/AStar.c",
            "Path/IDAStar.c",
            "Path/Path.c",
            "Path/PathMisc.c",
            "Path/PathUtil.c",
            "Path/PathWF.c",
            "Path/Step.c",
            "Units/Missile.c",
            "Units/UnitRoom.c",
            "Units/Units.c",
        },
    });
    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    b.step("run", "Run the app").dependOn(&run_cmd.step);
}
