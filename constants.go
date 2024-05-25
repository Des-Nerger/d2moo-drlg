package d2moo_drlg

type TownId int32

const (
	TownId_RogueCamp TownId = 1
	TownId_LutGhol   TownId = 40
	TownId_Kurast    TownId = 75
	TownId_PandFort  TownId = 103
	TownId_Harro     TownId = 109
	TownId_Null      TownId = 0
)

type Difficulty uint8

const (
	Difficulty_Normal Difficulty = iota
	Difficulty_Nightmare
	Difficulty_Hell
	Difficulty_Count
)

type Act uint8

const (
	Act_I Act = iota
	Act_II
	Act_III
	Act_IV
	Act_V
	Act_Count
)
