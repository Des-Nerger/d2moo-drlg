package main

import (
	"fmt"
	. "github.com/Des-Nerger/d2moo_drlg"
	"github.com/Des-Nerger/d2moo_drlg/drlg"
)

func main() {
	const (
		dwInitSeed  uint32 = 0
		nDifficulty        = Difficulty_Normal
		nAct               = Act_I
	)
	nTownId := [...]TownId{
		TownId_RogueCamp,
		TownId_LutGhol,
		TownId_Kurast,
		TownId_PandFort,
		TownId_Harro,
	}[nAct]
	fmt.Printf(
		"Hello, %#v\n",
		drlg.NewStrc(
			&drlg.ActStrc{
				NAct:       nAct,
				DwInitSeed: dwInitSeed,
				NTownId:    nTownId,
			},
			nAct,
			nil,
			dwInitSeed,
			nTownId,
			drlg.Flags(0),
			&GameStrc{
				DwInitSeed: dwInitSeed,
				BExpansion: true,
			},
			nDifficulty,
			nil,
			nil,
		),
	)
}
