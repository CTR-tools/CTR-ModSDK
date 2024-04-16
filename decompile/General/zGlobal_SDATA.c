
#ifndef REBUILD_PC
#define NO_BSS 1
#endif

#include <common.h>

#if __GNUC__
char memcardBytes[0x1680];
#endif

struct sData sdata_static =
{
	.langBufferSize = 0x3F04,
	
#if NO_BSS
	.arcade_difficultyParams = 0x8008da48,
	.cup_difficultyParams = 0x8008da64,
#else
	.arcade_difficultyParams = &sdata_static.arcadeDiff[0],
	.cup_difficultyParams = &sdata_static.cupDiff[0],
#endif
	
	.driver_pathIndexIDs =
	{
		0, -1, -1, 2,
		0, -1, -1, 2
	},
	
	// twice as many frames, half as much
	// step for each frame of acceleration
	.AI_AccelFrameCount = 0xa0,
	.AI_AccelFrameSteps = 0x18,
	
	.AI_VelY_WhenBlasted_0x3000 = 0x3000,
	
	.s_camera = "camera",
	
	.FirstPersonCamera =
	{
		.posOffset = {0,0x60,0,0},
		.rotOffset = {0x800,0x800,0,0},
	},
	
	.s_DCH = "DCH",
	.s_SPN = "SPN",
	.s_ITL = "ITL",
	.s_GRM = "GRM",
	.s_FRN = "FRN",
	.s_ENG = "ENG",
	.s_JPN = "JPN",
	
	.s_XINF = "XINF",
	
	.s_BLADE = "BLADE",
	.s_TURBO = "TRUBO",
	.s_SPRING = "SPRING",
	.s_GATE = "GATE",
	
	.s_NO_FUNC = "NO_FUNC",
	
	.boolDebugDispEnv = 0,
	.LevClearColorRGB = {0,0,0},
	
	.HudAndDebugFlags = 0x100,
	
	.unk_CTR_MatrixToRot_table =
	{
		0,1,2,0,
		0,0,0,0,
		
		1,2,0,1,
		0,0,0,0,
	},
	
	.trafficLightsTimer_prevFrame = 0,
	
	//.PausePtrsVRAM = {},
	.pause_backup_renderFlags = 0,
	.pause_state = 0,
	
	.unkPadSetActAlign = 
	{
		0,1,-1,-1,
		-1,-1,1,0
	},
	
	.s_ghost = "ghost",
	.s_ghost1 = "ghost1",
	.s_ghost0 = "ghost0",
	
	.audioRNG = 0x15A37E63,
	.boolAudioEnabled = 0,
	.s_HOWL = "HOWL",
	
	.advHubSongSet =
	{
		.numSeqs = 0x14,
		.ptrSongSetBits = &data.advHubSongSetBytes[0],
	},
	
	.reverbModeBossID =
	{
		3,1,1,0,3,3,
		
		// padding
		0,0
	},
	
	.songBankBossID =
	{
		0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1E,
		
		// padding
		0,0
	},
	
	#if BUILD >= UsaRetail
	.garageSoundIDs =
	{
		0xDC, 0xDF, 0, 0xE7, 0, 0xEE, 0xF0, 0
	},
	#endif
	
	.ptrMPK = 0,
	.ptrLEV_DuringLoading = 0,
	.PatchMem_Ptr = 0,
	
	#if BUILD >= UsaRetail
	.PatchMem_Size = 0,
	#endif
	
	.bookmarkID = 0,
	.ptrBigfileCdPos_2 = 0,
	
	.queueReady = 1,
	.queueRetry = 0,
	.queueLength = 0,
	.UnusedPadding1 = 0,
	
	.load_inProgress = 0,
	.frameWhenLoadingFinished = 0,
	
	.s_FILE = "FILE",
	
	#if BUILD >= EurRetail
	.lngFile = 0,
	#endif
	
	.levBigLodIndex =
	{
		0,2,4,4,6,6,6,6
	},
	
	.boolFirstBoot = 1,
	
	.s_ndi = "ndi",
	.s_ending = "ending",
	.s_intro = "intro",
	.s_screen = "screen",
	.s_garage = "garage",
	.s_hub = "hub",
	.s_credit = "credit",
	
	.modelMaskHints3D = 0,
	
	.mainGameState = 0,
	
	.Loading =
	{
		.stage = -1,
		
		// MAIN MENU LEVEL
		.Lev_ID_To_Load = 0x27,
		
		// OnBegin is all zeros
	},
	
	.numLngStrings = 0,
	
	.s_credit9 = "credit9",
	.s_credit8 = "credit8",
	.s_credit7 = "credit7",
	.s_credit6 = "credit6",
	.s_credit5 = "credit5",
	.s_credit4 = "credit4",
	.s_credit3 = "credit3",
	.s_credit2 = "credit2",
	.s_credit1 = "credit1",
	
	.s_ending2 = "ending2",
	.s_ending1 = "ending1",
	
	.s_ndi_needToRename = "ndi",
	
	.s_garage1 = "garage1",
	
	.s_intro9 = "intro9",
	.s_intro8 = "intro8",
	.s_intro7 = "intro7",
	.s_intro6 = "intro6",
	.s_intro5 = "intro5",
	.s_intro4 = "intro4",
	.s_intro3 = "intro3",
	.s_intro2 = "intro2",
	.s_intro1 = "intro1",
	
	.s_hub5 = "hub5",
	.s_hub4 = "hub4",
	.s_hub3 = "hub3",
	.s_hub2 = "hub2",
	.s_hub1 = "hub1",
	
	.s_battle7 = "battle7",
	.s_battle6 = "battle6",
	.s_battle5 = "battle5",
	.s_battle4 = "battle4",
	.s_battle3 = "battle3",
	.s_battle2 = "battle2",
	.s_battle1 = "battle1",
	
	.s_secret2 = "secret2",
	.s_secret1 = "secret1",
	.s_space = "space",
	.s_ice1 = "ice1",
	.s_labs1 = "labs1",
	.s_castle1 = "castle1",
	.s_cave1 = "cave1",
	.s_sewer1 = "sewer1",
	.s_blimp1 = "blimp1",
	.s_tube1 = "tube1",
	.s_temple2 = "temple2",
	.s_temple1 = "temple1",
	.s_island1 = "island1",
	.s_desert2 = "desert2",
	.s_proto9 = "proto9",
	.s_proto8 = "proto8",
	
	// all zeros
	//.finalLapTextTimer = {},
	
	#if BUILD >= UsaRetail
	.TurboDisplayPos_Only1P = 0,
	.numPlayersFinishedRace = 0,
	#endif
	
#if NO_BSS
	.gGT = 0x80096b20,
	.gGamepads = 0x80096804,
#else
	.gGT = &sdata_static.gameTracker,
	.gGamepads = &sdata_static.gamepadSystem,
#endif
	
	.vsyncTillFlip = 0,
	
	.s_PrimMem = "PrimMem",
	.s_OTMem = "OTMem",
	
	.boolPlayVideoSTR = 0,
	
	.AkuHint_RequestedHint = -1,
	.AkuHint_boolInterruptWarppad = 0,
	
	.LOD = {1,2,4,4,8,8,8,8},
	
	// one for RaceWheel, one for Namco
	.unk_drawingRaceWheelRects = {0x3C, 0x64},
	
	.posY_MultiLine = {0x92, 0xA0, 0x81, 0x8F},
	
	.posY_Arrows = {0x81, 0x8F},
	
	.unk_RaceWheelConfig = {0x320, -1, -1},
	
	.s_ot0 = "ot[0]",
	.s_ot1 = "ot[1]",
	.s_PLAYER = "PLAYER",
	.s_PLYR = "PLYR",
	.s_ROBOT = "ROBOT",
	.s_RBOT = "RBOT",
	.s_STATIC = "STATIC",
	.s_STAT = "STAT",
	.s_MINE = "MINE",
	.s_WARPPAD = "WARPPAD",
	.s_WRPD = "WRPD",
	.s_TRKG = "TRKG",
	.s_BURST = "BURST",
	.s_BRST = "BRST",
	.s_BLOWUP = "BLOWUP",
	.s_BLWP = "BLWP",
	.s_TURBO_again = "TURBO",
	.s_TRBO = "TRBO",
	.s_SPIDER = "SPIDER",
	.s_SPDR = "SPDR",
	.s_FLWR = "FLWR",
	.s_STXT = "STXT",
	.s_OTHER = "OTHER",
	.s_OTHR = "OTHR",
	.s_AKUAKU = "AKUAKU",
	.s_AKUU = "AKUU",
	.s_CAMERA = "CAMERA",
	.s_CAMR = "CAMR",
	.s_HUD = "HUD",
	.s_THUD = "THUD",
	.s_PAUSE = "PAUSE",
	.s_PAUS = "PAUS",
	
	.MainDrawCb_DrawSyncPtr = 0,
	.ptrVlcTable = 0,
	.bool_IsLoaded_VlcTable = 0,
	
	#if BUILD >= JpnTrial
	.region = "XXXX",
	#endif
	
	.unk_card_8008D404 = 0,
	.memcard_ptrStart = 0,
	.memcard_fd = -1,
	.memcard_remainingAttempts = 8,
	.s_memcardDirHeader = "bu00:",
	.s_AnyFile = "*",
	
#if NO_BSS
	.PtrMempack = 0x800990E4,
#else
	.PtrMempack = &sdata_static.mempack[0],
#endif

	.randomNumber = 100,
	.unk_8008d428 = 0,
	.unk_8008d42C = 0,
	
	.battleSetupExpandMenu = -1,
	.battleSetupRowHighlighted = 5,
	.battleSetupWeaponHighlighted = 0,
	.battleSetup_Color_UI_1 = 0x405000,
	.battleSetup_Color_UI_2 = 0x60A000,
	
	.RaceFlag_AnimationType = 0,
	.RaceFlag_Position = 0,
	.unk_CheckFlag1 = 300,
	.RaceFlag_CanDraw = 1,
	.unk_CheckFlag2 = 0,
	.RaceFlag_DrawOrder = 0,
	.padding_8008d44e = 0,
	
#if BUILD >= UsaRetail
	.RaceFlag_LoadingTextAnimFrame = -1,
	.RaceFlag_Transition = 0,
#endif

	.RaceFlag_ElapsedTime = 0,
	.RaceFlag_CopyLoadStage = -1,
	
	.DrawSolidBoxData = {0, 0xc0c0c0, 0},
	
	.strcatData1_colon = ":",
	
#if NO_BSS
	.ptrToMemcardBuffer1 = 0x800992e4,
	.ptrToMemcardBuffer2 = 0x800992e4,
#elif __GNUC__
	.ptrToMemcardBuffer1 = &memcardBytes[0],
	.ptrToMemcardBuffer2 = &memcardBytes[0],
#else
	.ptrToMemcardBuffer1 = &sdata_static.memcardBytes[0],
	.ptrToMemcardBuffer2 = &sdata_static.memcardBytes[0],
#endif
	
	.unk8008d478 = 0x50002,
	
	.LoadSave_SpinRateY = {64, -47, 51, 0},
	
	.stringFormat1 = "%02ld",
	.stringFormat2 = "%ld",
	.greyColor = 0x808080,
	.greenColor = 0x20c020,
	.s_percent_sign = 0x25,
	.redColor = 0xA0A000,
	.ghostIconColor = 0x808080,
	
	.unk_BeforeTokenMenu =
	{
		0xEC, 0xFF,	// -20
		0x14, 0x0,	// 20
		0x28, 0x2,	// 552
		0xAA, 0x0	// 170
	},
	
	.str_underscore = "_",
	
	.boolOpenTokenRelicMenu = 0,
	.ptrPushBufferUI = 0,
	.ptrFruitDisp = 0,
	.menuReadyToPass = 0,
	
	.s_token = "token",
	.s_relic1 = "relic1",
	.s_key1 = "key1",
	.s_trophy1 = "trophy1",
	.s_big1 = "big1",
	.s_hudc = "hudc",
	.s_hudt = "hudt",
	.s_hudr = "hudr",
	
	.unknownWhatThisIs = 0x908000,
	.raceClockStr = " :  :  ",
	.s_Ln = "l ",
	.s_int = "%d",
	.s_intDividing = "%d/%d",
	.s_printDividing = " / ",
	.s_longInt = "%ld",
	.s_spacebar = " ",
	.s_x = "x",
	
	.framesSinceRaceEnded = 0,
	
	.s_subtractLongInt = "-%ld",
	.s_additionLongInt = "+%ld",
	.s_subtractInt = "-%d",
	.s_999 = "999 ",
	.s_intSpace = "%d ",
	.s_str = "%s",
	
	.multiplayerWumpaHudData = 
	{
		0x18003e0, 0x180020, 0x1000320, 0x180020
	},
	
	.Battle_EndOfRace =
	{
		.Flags_PressX = 0,
		
		// default
		#ifndef USE_NEW2P
		
		.textFlags1_2P = 0x350100,
		.textFlags2_2P = 0x430100,
		
		// split side-by-side
		#else
		.textFlags1_2P = 0x350080,
		.textFlags2_2P = 0x430080,
		#endif
	},
	
	.numIconsEOR = 1,
	
	.s_additionInt = "+%d",
	
	.UnlockBitIndex =
	{
		.CupCompletion_curr = {0xc, 0x10, 0x14, 0},
		.CupCompletion_prev = {0x18, 0x1c, 0x20, 0},
		.UnlockBattleMap = {2, 3, 4, 0},
	},
	
	.unk_UsedIn_FUN_80057884 = 0,
	
	.s_NOSCRUB = "NOSCRUB",
	.s_ROAD = "ROAD",
	.s_SANDBAG = "SANDBAG",
	.s_RUBBER = "RUBBER",
	.s_SOILD = "SOLID",
	.s_mud = "mud",
	.s_metal = "metal",
	.s_none = "none",
	.s_snow = "snow",
	.s_track = "track",
	.s_ice = "ice",
	.s_stone = "stone",
	.s_water = "water",
	.s_wood = "wood",
	.s_grass = "grass",
	.s_dirt = "dirt",
	.s_asphalt = "asphalt",
	.s_player = "player",
	.s_turbo1 = "turbo1",
	.s_turbo2 = "turbo2",
	.s_doctor1 = "doctor1",
	.s_bomb1 = "bomb1",
	.s_shield = "shield",
	.s_nitro1 = "nitro1",
	.s_tnt1 = "tnt1",
	.s_beaker1 = "beaker1",
	
	.boolIsMaskThreadAlive = 0,
	.s_head = "head"
};