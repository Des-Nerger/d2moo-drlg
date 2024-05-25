package drlg

import (
	. "github.com/Des-Nerger/d2moo_drlg"
)

type AutoMapFn func(*ActiveRoomStrc)
type TownAutoMapFn func(int32, int32, int32, int32)

type Flags uint32

const Flag_OnClient, Flag_Refresh Flags = 0x01, 0x10

type ActStrc struct {
	NAct       Act
	DwInitSeed uint32
	NTownId    TownId
}

type ActiveRoomStrc struct {
}

type Strc struct {
}

func NewStrc(
	pAct *ActStrc,
	nAct Act,
	pArchive *Archive,
	nInitSeed uint32,
	nTownId TownId,
	nFlags Flags,
	pGame *GameStrc,
	nDifficulty Difficulty,
	fnAutoMap AutoMapFn,
	fnTownAutoMap TownAutoMapFn,
) *Strc {
	return &Strc{}
}
