#define SDATA_DEV 1
#include <common.h>

struct sData sdata_static =
{
	.langBufferSize = 0x3F04,
	
	//.unkPtr_8008da48 = &sdata_static.unk_data1c_1[0],
	//.unkPtr_8008da64 = &sdata_static.unk_data1c_2[0],
	
	.unkPtr_8008da48 = 0x8008da48,
	.unkPtr_8008da64 = 0x8008da64,
	
	.driver_pathIndexIDs =
	{
		0, -1, -1, 2,
		0, -1, -1, 2
	},
	
	.AI_timeToFullAccel_0xa0 = 0xa0,
	.AI_dragDuringAccel_0x18 = 0x18,
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
	
	.pause_VRAM_Backup_PrimMem = {},
	.pause_backup_renderFlags = 0,
	.pause_state = 0,
	
	.unk_padSetActAlign = 
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
	.finalLapTextTimer = {},
	
	#if BUILD >= UsaRetail
	.TurboDisplayPos_Only1P = 0,
	.numPlayersFinishedRace = 0,
	#endif
	
	// Hard-code is required,
	// cause the structs are in BSS, therefore excluded 
	// by SDATA, so the zeros dont bloat the EXE
	
	//.gGT = &sdata_static.gameTracker,
	//.gGamepads = &sdata_static.gamepadSystem,
	.gGT = 0x80096b20,
	.gGamepads = 0x80096804,
	
	.vsyncTillFlip = 0,
	
	.s_PrimMem = "PrimMem",
	.s_OTMem = "OTMem",
	
	.boolPlayVideoSTR = 0,
	
	.AkuHint_RequestedHint = -1,
	.AkuHint_boolInterruptWarppad = 0,
	
	.LOD = {1,2,4,4,8,8,8,8},
	
	// one for RaceWheel, one for Namco
	.unk_drawingRaceWheelRects = {0x3C, 0x64},
	
	.posY_MultiLine = {0x92, 0xA0},
	
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
};