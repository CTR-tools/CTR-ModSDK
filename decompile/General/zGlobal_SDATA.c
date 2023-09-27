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
	
	.boolFirstBoot = 1
};