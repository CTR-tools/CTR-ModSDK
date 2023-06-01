#include <common.h>
#include "../../levelBuilder.h"
#include "trackSpecificData.h"

struct AnimTex_TurboPad1
{
	// 0x0
	// pointer to IconGroup4 struct to be animated
	// cycles through the entirety of ptrarray
	struct IconGroup4* ptrNext;

	// 0x4
	short numFrames;

	// 0x6
	// related to timer
	short shrug;

	// 0x8
	// related to timer
	short lottashortshuh;

	// 0xA
	// current frame
	u_short frameIndex;

	// 0xC
	// amount of elements in array is same as numFrames
	// ptrarray[numFrames] leads to the next AnimTex struct in the ptr_anim_tex array
	struct IconGroup4* ptrarray[10];
};

struct AnimTex_TurboPad2
{
	// 0x0
	// pointer to IconGroup4 struct to be animated
	// cycles through the entirety of ptrarray
	struct IconGroup4* ptrNext;

	// 0x4
	short numFrames;

	// 0x6
	// related to timer
	short shrug;

	// 0x8
	// related to timer
	short lottashortshuh;

	// 0xA
	// current frame
	u_short frameIndex;

	// 0xC
	// amount of elements in array is same as numFrames
	// ptrarray[numFrames] leads to the next AnimTex struct in the ptr_anim_tex array
	struct IconGroup4* ptrarray[11];
};

struct LevelFile
{
	void* ptrMap;
	struct Level level;
	struct mesh_info mInfo;
	struct IconGroup4 group4_checkerEdge;
	struct IconGroup4 group4_checkerCenter;
	struct IconGroup4 group4_tileEdge;
	struct IconGroup4 group4_tileCenter;
	struct IconGroup4 group4_tileCorner;
	struct IconGroup4 turbo_pad[10];
	struct IconGroup4 super_turbo_pad[10];
	struct IconGroup4 group4_placeHolder;
	struct IconGroup4 ineedtogeneratethis1;
	struct IconGroup4 ineedtogeneratethis2;
	struct IconGroup4 ineedtogeneratethis3;
	struct IconGroup4 ineedtogeneratethis4;
	struct AnimTex_TurboPad1 turbo_pad_anim;
	struct AnimTex_TurboPad2 super_turbo_pad_anim;
	struct SpawnType1 ptrSpawnType1;
	struct CheckpointNode checkpointNodes[NUM_CHECKPOINT];
	struct QuadBlock quadBlock[NUM_BLOCKS];
	struct LevVertex levVertex[NUM_BLOCKS*9];
	struct BSP bsp[9];
	struct PVS pvs[NUM_PVS];
	int leafList[2*NUM_PVS];
	int faceList[5*NUM_PVS];
	struct VisMem visMem;
	
	int VisMem_bitIndex_DstMemcpyP1[8]; // leave empty
	int VisMem_bspList_RenderListP1[9*2];
	int VisMem_bitIndex_DstMemcpyP2[8]; // leave empty
	int VisMem_bspList_RenderListP2[9*2];
	int VisMem_bitIndex_DstMemcpyP3[8]; // leave empty
	int VisMem_bspList_RenderListP3[9*2];
	int VisMem_bitIndex_DstMemcpyP4[8]; // leave empty
	int VisMem_bspList_RenderListP4[9*2];
	
	struct NavHeader* navHeader[3];
	struct NavHeader navHeader1;
	struct NavFrame navFrame[650];
	
	int map[(72+NUM_BLOCKS*6)+1];
};

struct LevelFile file =
{
	.ptrMap = LEV_OFFSETOF(map[0]),
	
	.level =
	{
		.ptr_mesh_info = LEV_OFFSETOF(mInfo),
		.visMem = LEV_OFFSETOF(visMem),
		.ptr_anim_tex = LEV_OFFSETOF(turbo_pad_anim),
		
		// the game will add +0x400 to the yaw of spawn positions automatically
		// we should probably look into why this even happens...
		
		#if 0 // Arcade mode
		.DriverSpawn[0].pos = {0x180,0,-0xc0},
		.DriverSpawn[0].rot = {0,0-0x400,0},
		#else // Simulate Time Trial Spawn
		.DriverSpawn[0].pos = {0x80,0,-0xc0},
		.DriverSpawn[0].rot = {0,0-0x400,0},
		#endif
		
		.DriverSpawn[1].pos = {0x80,0,-0xc0},
		.DriverSpawn[1].rot = {0x40,0-0x400,0},
		
		.DriverSpawn[2].pos = {-0x80,0,-0xc0},
		.DriverSpawn[2].rot = {-0x40,0-0x400,0},
		
		.DriverSpawn[3].pos = {-0x180,0,-0xc0},
		.DriverSpawn[3].rot = {-0x80,0-0x400,0},
		
		.ptrSpawnType1 = LEV_OFFSETOF(ptrSpawnType1),
		
		.clearColor[0].rgb = {0x20, 0x10, 0x80},
		.clearColor[0].enable = 1,
		
		.clearColor[1].rgb = {0x80, 0x20, 0x10},
		.clearColor[1].enable = 1,
		
		// only non-zero for Race maps
		// battle maps need array, but still set CNT to zero
		.cnt_restart_points = NUM_CHECKPOINT,
		.ptr_restart_points = LEV_OFFSETOF(checkpointNodes[0]),
		
		.LevNavHeader = LEV_OFFSETOF(navHeader[0]),
	},
	
	.mInfo =
	{
		.numQuadBlock = NUM_BLOCKS,
		.numVertex = NUM_BLOCKS*9, // not really used
		.unk1 = 0, // idk, fine to leave null
		.ptrQuadBlockArray = LEV_OFFSETOF(quadBlock[0]),
		.ptrVertexArray = LEV_OFFSETOF(levVertex[0]),
		.unk2 = 0, // idk, fine to leave null
		.bspRoot = LEV_OFFSETOF(bsp[0]),
		.numBspNodes = 9,
	},
	
	.group4_checkerEdge =
	{
		.far =    ImageName_Blend(512, 0, 32, 128, 64, 64, BPP_4, TRANS_50),
		.middle = ImageName_Blend(512, 0, 32, 128, 64, 64, BPP_4, TRANS_50),
		.near =   ImageName_Blend(512, 0, 32, 128, 64, 64, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(512, 0, 32, 128, 64, 64, BPP_4, TRANS_50)
	},
	
	.group4_checkerCenter =
	{	
		.far =    ImageName_Blend(528, 0, 32, 129, 64, 64, BPP_4, TRANS_50),
		.middle = ImageName_Blend(528, 0, 32, 129, 64, 64, BPP_4, TRANS_50),
		.near =   ImageName_Blend(528, 0, 32, 129, 64, 64, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(528, 0, 32, 129, 64, 64, BPP_4, TRANS_50)
	},
	
	.group4_tileEdge =
	{	
		.far =    ImageName_Blend(544, 0, 32, 130, 64, 64, BPP_4, TRANS_50),
		.middle = ImageName_Blend(544, 0, 32, 130, 64, 64, BPP_4, TRANS_50),
		.near =   ImageName_Blend(544, 0, 32, 130, 64, 64, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(544, 0, 32, 130, 64, 64, BPP_4, TRANS_50)
	},
	
	.group4_tileCenter =
	{	
		.far =    ImageName_Blend(560, 0, 32, 131, 64, 64, BPP_4, TRANS_50),
		.middle = ImageName_Blend(560, 0, 32, 131, 64, 64, BPP_4, TRANS_50),
		.near =   ImageName_Blend(560, 0, 32, 131, 64, 64, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(560, 0, 32, 131, 64, 64, BPP_4, TRANS_50)
	},
	
	.group4_tileCorner =
	{
		.far =    ImageName_Blend(576, 0, 32, 135, 64, 64, BPP_4, TRANS_50),
		.middle = ImageName_Blend(576, 0, 32, 135, 64, 64, BPP_4, TRANS_50),
		.near =   ImageName_Blend(576, 0, 32, 135, 64, 64, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(576, 0, 32, 135, 64, 64, BPP_4, TRANS_50)
	},
	
	.group4_placeHolder =
	{
		.far =    ImageName_Blend(592, 0, 32, 132, 16, 16, BPP_4, TRANS_50),
		.middle = ImageName_Blend(592, 0, 32, 132, 16, 16, BPP_4, TRANS_50),
		.near =   ImageName_Blend(592, 0, 32, 132, 16, 16, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(592, 0, 32, 132, 16, 16, BPP_4, TRANS_50)
	},
	
	.turbo_pad =
	{
		[0] =
		{
			.far    = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 0),
			.middle = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 0),
			.near   = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 0),
			.mosaic = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 0),
		},
		[1] =
		{
			.far    = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 2),
			.middle = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 2),
			.near   = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 2),
			.mosaic = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 2),
		},
		[2] =
		{
			.far    = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 3),
			.middle = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 3),
			.near   = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 3),
			.mosaic = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 3),
		},
		[3] =
		{
			.far    = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 5),
			.middle = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 5),
			.near   = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 5),
			.mosaic = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 5),
		},
		[4] =
		{
			.far    = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 6),
			.middle = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 6),
			.near   = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 6),
			.mosaic = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 6),
		},
		[5] =
		{
			.far    = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 8),
			.middle = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 8),
			.near   = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 8),
			.mosaic = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 8),
		},
		[6] =
		{
			.far    = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 10),
			.middle = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 10),
			.near   = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 10),
			.mosaic = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 10),
		},
		[7] =
		{
			.far    = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 11),
			.middle = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 11),
			.near   = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 11),
			.mosaic = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 11),
		},
		[8] =
		{
			.far    = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 13),
			.middle = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 13),
			.near   = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 13),
			.mosaic = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 13),
		},
		[9] =
		{
			.far    = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 14),
			.middle = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 14),
			.near   = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 14),
			.mosaic = TurboPadImage(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, 14),
		},
	},
	
	// texture made by Avery (@TheMagicJam)
	.super_turbo_pad =
	{
		[0] =
		{
			.far    = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 0),
			.middle = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 0),
			.near   = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 0),
			.mosaic = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 0),
		},
		[1] =
		{
			.far    = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 2),
			.middle = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 2),
			.near   = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 2),
			.mosaic = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 2),
		},
		[2] =
		{
			.far    = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 3),
			.middle = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 3),
			.near   = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 3),
			.mosaic = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 3),
		},
		[3] =
		{
			.far    = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 5),
			.middle = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 5),
			.near   = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 5),
			.mosaic = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 5),
		},
		[4] =
		{
			.far    = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 6),
			.middle = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 6),
			.near   = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 6),
			.mosaic = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 6),
		},
		[5] =
		{
			.far    = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 8),
			.middle = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 8),
			.near   = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 8),
			.mosaic = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 8),
		},
		[6] =
		{
			.far    = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 10),
			.middle = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 10),
			.near   = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 10),
			.mosaic = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 10),
		},
		[7] =
		{
			.far    = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 11),
			.middle = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 11),
			.near   = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 11),
			.mosaic = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 11),
		},
		[8] =
		{
			.far    = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 13),
			.middle = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 13),
			.near   = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 13),
			.mosaic = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 13),
		},
		[9] =
		{
			.far    = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 14),
			.middle = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 14),
			.near   = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 14),
			.mosaic = TurboPadImage(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, 14),
		},
	},

	.turbo_pad_anim =
	{
		.ptrNext = LEV_OFFSETOF(turbo_pad[0]),
		.numFrames = 10,
		.shrug = 0,
		.lottashortshuh = 0,
		.frameIndex = 0,
		.ptrarray =
		{
			LEV_OFFSETOF(turbo_pad[0]),
			LEV_OFFSETOF(turbo_pad[1]),
			LEV_OFFSETOF(turbo_pad[2]),
			LEV_OFFSETOF(turbo_pad[3]),
			LEV_OFFSETOF(turbo_pad[4]),
			LEV_OFFSETOF(turbo_pad[5]),
			LEV_OFFSETOF(turbo_pad[6]),
			LEV_OFFSETOF(turbo_pad[7]),
			LEV_OFFSETOF(turbo_pad[8]),
			LEV_OFFSETOF(turbo_pad[9]),
		},
	},

	.super_turbo_pad_anim =
	{
		.ptrNext = LEV_OFFSETOF(super_turbo_pad[0]),
		.numFrames = 10,
		.shrug = 0,
		.lottashortshuh = 0,
		.frameIndex = 0,
		.ptrarray =
		{
			LEV_OFFSETOF(super_turbo_pad[0]),
			LEV_OFFSETOF(super_turbo_pad[1]),
			LEV_OFFSETOF(super_turbo_pad[2]),
			LEV_OFFSETOF(super_turbo_pad[3]),
			LEV_OFFSETOF(super_turbo_pad[4]),
			LEV_OFFSETOF(super_turbo_pad[5]),
			LEV_OFFSETOF(super_turbo_pad[6]),
			LEV_OFFSETOF(super_turbo_pad[7]),
			LEV_OFFSETOF(super_turbo_pad[8]),
			LEV_OFFSETOF(super_turbo_pad[9]),
			LEV_OFFSETOF(turbo_pad_anim),
		},
	},

	.ineedtogeneratethis1 =
	{
		.far =    ImageName_Blend(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50),
		.middle = ImageName_Blend(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50),
		.near =   ImageName_Blend(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50)
	},

	.ineedtogeneratethis2 =
	{
		.far =    ImageName_Blend(596, 0, 32, 133, 32, 16, BPP_4, TRANS_50),
		.middle = ImageName_Blend(596, 0, 32, 133, 32, 16, BPP_4, TRANS_50),
		.near =   ImageName_Blend(596, 0, 32, 133, 32, 16, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(596, 0, 32, 133, 32, 16, BPP_4, TRANS_50)
	},

	.ineedtogeneratethis3 =
	{
		.far =    ImageName_Blend(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50),
		.middle = ImageName_Blend(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50),
		.near =   ImageName_Blend(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50)
	},

	.ineedtogeneratethis4 =
	{
		.far =    ImageName_Blend(604, 0, 32, 134, 32, 16, BPP_4, TRANS_50),
		.middle = ImageName_Blend(604, 0, 32, 134, 32, 16, BPP_4, TRANS_50),
		.near =   ImageName_Blend(604, 0, 32, 134, 32, 16, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(604, 0, 32, 134, 32, 16, BPP_4, TRANS_50)
	},
	
	// this must exist, or else camera fly-in
	// checks for "count" without nullptr check,
	// and crashes dereferencing nullptr on real PSX
	.ptrSpawnType1 =
	{
		.count = 0,
	},
	
/*
	NEW_BLOCK
	(
		// index, texture
		0, texgroup_ground,

		// posX, posZ
		// +z is forward, +x is left, not right
		// size of a quadblock is always 0x300 x 0x300, see "levelBuilder.h"
		0x0, 0x0,

		// vertex flags, quadblock flags
		NULL, 0x1800,

		// RGB color
		RGBtoBGR(0xFF0000),
	),
*/
	
	// +z is forward
	// +x is left, not right
	
	// behind spawn
	NEW_BLOCK(Bsp0_BehindStart1, ineedtogeneratethis1, -0x180, -0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_BehindStart2, ineedtogeneratethis2, 0x180, -0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_BehindStart3, ineedtogeneratethis3, -0x180, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_BehindStart4, ineedtogeneratethis4, 0x180, -0x300, NULL, 0x1800, 0x808080),
	
	// BR, BL, TR, TL assuming you're rotation is 0,0,0
	TEX_2X2(Bsp0_BehindStart1, group4_tileCorner, group4_tileEdge, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_BehindStart2, group4_tileEdge, group4_tileCorner, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_BehindStart1].draw_order_low = 0x802100,
	.quadBlock[Bsp0_BehindStart2].draw_order_low = 0x1044100,
	
	TEX_2X2(Bsp0_BehindStart3, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_BehindStart4, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_BehindStart3].draw_order_low = 0x800000,
	.quadBlock[Bsp0_BehindStart4].draw_order_low = 0x1044000,
	
	// spawn
	NEW_BLOCK(Bsp0_StartLine1, group4_tileEdge, -0x180, 0, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_StartLine2, group4_tileEdge, 0x180, 0, NULL, 0x1800, 0x808080),
	
	// BR, BL, TR, TL assuming you're rotation is 0,0,0
	TEX_2X2(Bsp0_StartLine1, group4_tileEdge, group4_tileCenter, group4_checkerEdge, group4_checkerCenter),
	TEX_2X2(Bsp0_StartLine2, group4_tileCenter, group4_tileEdge, group4_checkerCenter, group4_checkerEdge),
	.quadBlock[Bsp0_StartLine1].draw_order_low = 0x800000, // rotate checker
	.quadBlock[Bsp0_StartLine2].draw_order_low = 0x1044000, // rotation
	
	// flat, in front of spawn
	NEW_BLOCK(Bsp0_AfterStart1, group4_placeHolder, -0x180, 0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_AfterStart2, group4_placeHolder, 0x180, 0x300, NULL, 0x1800, 0x808080),
	
	TEX_2X2(Bsp0_AfterStart1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_AfterStart2, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_AfterStart1].draw_order_low = 0x800000,
	.quadBlock[Bsp0_AfterStart2].draw_order_low = 0x1044000,
	
	// ramp down (1/3)
	NEW_BLOCK(Bsp0_DownRamp1, group4_placeHolder, -0x180, 0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_DownRamp2, group4_placeHolder, 0x180, 0x600, NULL, 0x1800, 0x808080),
	
	TEX_2X2(Bsp0_DownRamp1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_DownRamp2, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_DownRamp1].draw_order_low = 0x800000,
	.quadBlock[Bsp0_DownRamp2].draw_order_low = 0x1044000,
	
	MAKE_RAMP(
		Bsp0_DownRamp1, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_DownRamp2, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp1, -0x180, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp2, -0x180, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	// ramp down (2/3)
	NEW_BLOCK(Bsp0_DownRamp3, group4_placeHolder, -0x180, 0x900, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_DownRamp4, group4_placeHolder, 0x180, 0x900, NULL, 0x1800, 0x808080),
	
	TEX_2X2(Bsp0_DownRamp3, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_DownRamp4, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_DownRamp3].draw_order_low = 0x800000,
	.quadBlock[Bsp0_DownRamp4].draw_order_low = 0x1044000,
	
	MAKE_RAMP(
		Bsp0_DownRamp3, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_DownRamp4, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp3, -0x300, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp4, -0x300, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	// ramp down (3/3)
	NEW_BLOCK(Bsp0_DownRamp5, group4_placeHolder, -0x180, 0xC00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_DownRamp6, group4_placeHolder, 0x180, 0xC00, NULL, 0x1800, 0x808080),
	
	TEX_2X2(Bsp0_DownRamp5, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_DownRamp6, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_DownRamp5].draw_order_low = 0x800000,
	.quadBlock[Bsp0_DownRamp6].draw_order_low = 0x1044000,
	
	MAKE_RAMP(
		Bsp0_DownRamp5, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_DownRamp6, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp5, -0x480, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp6, -0x480, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	// bottom between ramps (with intended hole)
	NEW_BLOCK(Bsp0_FlatDip1, group4_placeHolder, -0x180, 0x1200, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_FlatDip2, group4_placeHolder, 0x180, 0xF00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_FlatDip3, group4_placeHolder, 0x180, 0x1200, NULL, 0x1800, 0x808080),
	SET_POSY_FLAT(Bsp0_FlatDip1,-0x480),
	SET_POSY_FLAT(Bsp0_FlatDip2,-0x480),
	SET_POSY_FLAT(Bsp0_FlatDip3,-0x480),
	
	TEX_2X2(Bsp0_FlatDip1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_FlatDip2, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_FlatDip1].draw_order_low = 0x800000,
	.quadBlock[Bsp0_FlatDip2].draw_order_low = 0x1044000,
	TEX_2X2(Bsp0_FlatDip3, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_FlatDip3].draw_order_low = 0x1044000,
	
	// ramp up (1/3)
	NEW_BLOCK(Bsp0_UpRamp1, group4_placeHolder, -0x180, 0x1500, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_UpRamp2_Turbo_9800, turbo_pad, 0x180, 0x1500, NULL, 0x9800, 0x808080),
	.quadBlock[Bsp0_UpRamp2_Turbo_9800].draw_order_low = FACE_PosZ,
	
	TEX_2X2(Bsp0_UpRamp1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	.quadBlock[Bsp0_UpRamp1].draw_order_low = 0x800000,

	MAKE_RAMP(
		Bsp0_UpRamp1, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_UpRamp2_Turbo_9800, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp1, -0x480, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp2_Turbo_9800, -0x480, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	// ramp up (2/3)
	NEW_BLOCK(Bsp0_UpRamp3, group4_placeHolder, -0x180, 0x1800, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_UpRamp4, group4_placeHolder, 0x180, 0x1800, NULL, 0x1800, 0x808080),
	
	TEX_2X2(Bsp0_UpRamp3, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_UpRamp4, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_UpRamp3].draw_order_low = 0x800000,
	.quadBlock[Bsp0_UpRamp4].draw_order_low = 0x1044000,
	
	MAKE_RAMP(
		Bsp0_UpRamp3, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_UpRamp4, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp3, -0x300, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp4, -0x300, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	// ramp up (3/3)
	NEW_BLOCK(Bsp0_UpRamp5_Turbo_9800, super_turbo_pad, -0x180, 0x1B00, NULL, 0x9800, 0x808080),
	NEW_BLOCK(Bsp0_UpRamp6, group4_placeHolder, 0x180, 0x1B00, NULL, 0x1800, 0x808080),
	.quadBlock[Bsp0_UpRamp5_Turbo_9800].draw_order_low = FACE_PosZ,
	
	TEX_2X2(Bsp0_UpRamp6, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_UpRamp6].draw_order_low = 0x1044000,
	
	MAKE_RAMP(
		Bsp0_UpRamp5_Turbo_9800, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_UpRamp6, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp5_Turbo_9800, -0x180, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp6, -0x180, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	// turbo on ramp-up(3/3)
	NEW_BLOCK(Bsp0_UpRamp7_Turbo_1840, super_turbo_pad, -0x180, 0x1B00, NULL, 0x1840, 0x808080),
	NEW_BLOCK(Bsp0_UpRamp8_Turbo_1840, turbo_pad, 0x180, 0x1500, NULL, 0x1840, 0x808080),
	
	// turn into turbo, if flagsQ is 0x1840
	// 1 for normal, 2 for super turbo
	.quadBlock[Bsp0_UpRamp7_Turbo_1840].terrain_type = 2,
	.quadBlock[Bsp0_UpRamp8_Turbo_1840].terrain_type = 1,
	
	MAKE_RAMP(
		Bsp0_UpRamp7_Turbo_1840, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_UpRamp8_Turbo_1840, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp7_Turbo_1840, -0x180, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp8_Turbo_1840, -0x480, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	// flat, forward
	NEW_BLOCK(Bsp3_FlatTop1, group4_placeHolder, -0x180, 0x2100, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop2, group4_placeHolder, 0x180, 0x2100, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop3, group4_placeHolder, -0x180, 0x2400, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop4, group4_placeHolder, 0x180, 0x2400, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop5, group4_placeHolder, -0x180, 0x2700, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop6, group4_placeHolder, 0x180, 0x2700, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop7, group4_placeHolder, -0x180, 0x2A00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop8, group4_placeHolder, 0x180, 0x2A00, NULL, 0x1800, 0x808080),
	
	TEX_2X2(Bsp3_FlatTop1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp3_FlatTop2, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp3_FlatTop1].draw_order_low = 0x800000,
	.quadBlock[Bsp3_FlatTop2].draw_order_low = 0x1044000,
	TEX_2X2(Bsp3_FlatTop3, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp3_FlatTop4, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp3_FlatTop3].draw_order_low = 0x800000,
	.quadBlock[Bsp3_FlatTop4].draw_order_low = 0x1044000,
	
	TEX_2X2(Bsp3_FlatTop5, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	.quadBlock[Bsp3_FlatTop5].draw_order_low = 0x800000,
	
	TEX_2X2(Bsp3_FlatTop6, group4_tileCenter, group4_tileCenter, group4_tileCenter, group4_tileCenter),
	.quadBlock[Bsp3_FlatTop6].draw_order_low = 0x1044000,
	
	TEX_2X2(Bsp3_FlatTop8, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp3_FlatTop8].draw_order_low = 0x1984000,
	
	// BR, BL, TR, TL assuming you're rotation is 0,0,0
	TEX_2X2(Bsp3_FlatTop7, group4_tileEdge, group4_tileCenter, group4_tileCorner, group4_tileEdge),
	.quadBlock[Bsp3_FlatTop7].draw_order_low = 0x1800000,
	
	// ==== End of BSP block =====
	
	// flat, turn 90
	NEW_BLOCK(Bsp1_TurnLeft1, group4_placeHolder, 0x480, 0x2700, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnLeft2, group4_placeHolder, 0x480, 0x2A00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnLeft3_Turbo_9800, turbo_pad, 0x780, 0x2700, NULL, 0x9800, 0x808080), // boost
	NEW_BLOCK(Bsp1_TurnLeft4_Turbo_9800, turbo_pad, 0x780, 0x2A00, NULL, 0x9800, 0x808080), // boost
	NEW_BLOCK(Bsp1_TurnLeft5_Turbo_1840, turbo_pad, 0x780, 0x2700, NULL, 0x1840, 0x808080), // boost
	NEW_BLOCK(Bsp1_TurnLeft6_Turbo_1840, turbo_pad, 0x780, 0x2A00, NULL, 0x1840, 0x808080), // boost
	NEW_BLOCK(Bsp1_TurnLeft7, group4_placeHolder, 0xA80, 0x2700, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnLeft8, group4_placeHolder, 0xA80, 0x2A00, NULL, 0x1800, 0x808080),
	.quadBlock[Bsp1_TurnLeft3_Turbo_9800].draw_order_low = FACE_PosX,
	.quadBlock[Bsp1_TurnLeft4_Turbo_9800].draw_order_low = FACE_PosX,
	.quadBlock[Bsp1_TurnLeft5_Turbo_1840].terrain_type = 1,
	.quadBlock[Bsp1_TurnLeft6_Turbo_1840].terrain_type = 1,
	
	// BR, BL, TR, TL
	TEX_2X2(Bsp1_TurnLeft1, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp1_TurnLeft2, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp1_TurnLeft1].draw_order_low = 0x808100,
	.quadBlock[Bsp1_TurnLeft2].draw_order_low = 0x1984000,
	
	// BR, BL, TR, TL
	TEX_2X2(Bsp1_TurnLeft7, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp1_TurnLeft8, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp1_TurnLeft7].draw_order_low = 0x808100,
	.quadBlock[Bsp1_TurnLeft8].draw_order_low = 0x1984000,
	
	// flat, turn 180
	NEW_BLOCK(Bsp1_TurnBack1_Turbo_9800, turbo_pad, 0xD80, 0x2100, NULL, 0x9800, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack2_Turbo_9800, turbo_pad, 0x1080, 0x2100, NULL, 0x9800, 0x808080),
	.quadBlock[Bsp1_TurnBack1_Turbo_9800].draw_order_low = FACE_NegZ,
	.quadBlock[Bsp1_TurnBack2_Turbo_9800].draw_order_low = FACE_NegZ,
	
	NEW_BLOCK(Bsp1_TurnBack3_Turbo_1840, turbo_pad, 0xD80,  0x2100, NULL, 0x1840, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack4_Turbo_1840, turbo_pad, 0x1080,0x2100, NULL, 0x1840, 0x808080),
	.quadBlock[Bsp1_TurnBack3_Turbo_1840].terrain_type = 1,
	.quadBlock[Bsp1_TurnBack4_Turbo_1840].terrain_type = 1,
	
	NEW_BLOCK(Bsp1_TurnBack5, group4_placeHolder, 0xD80,  0x2400, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack6, group4_placeHolder, 0x1080,0x2400, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack7, group4_placeHolder, 0xD80,  0x2700, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack8, group4_placeHolder, 0x1080,0x2700, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack9, group4_placeHolder, 0xD80,  0x2A00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack10, group4_placeHolder, 0x1080,0x2A00, NULL, 0x1800, 0x808080),
	
	TEX_2X2(Bsp1_TurnBack5, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp1_TurnBack6, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp1_TurnBack5].draw_order_low = 0x800000,
	.quadBlock[Bsp1_TurnBack6].draw_order_low = 0x1044000,
	
	TEX_2X2(Bsp1_TurnBack7, group4_tileCenter, group4_tileCenter, group4_tileCenter, group4_tileCenter),
	.quadBlock[Bsp1_TurnBack7].draw_order_low = 0x1044000,
	
	TEX_2X2(Bsp1_TurnBack8, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp1_TurnBack8].draw_order_low = 0x1044000,
	
	TEX_2X2(Bsp1_TurnBack9, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp1_TurnBack9].draw_order_low = 0x1984000,
	
	// BR, BL, TR, TL assuming you're rotation is 0,0,0
	TEX_2X2(Bsp1_TurnBack10, group4_tileCenter, group4_tileEdge, group4_tileEdge, group4_tileCorner),
	.quadBlock[Bsp1_TurnBack10].draw_order_low = 0x18c4000,
	
	// ======= End of BSP block =========
	
	// fall back down,
	// here experiment with USF jump
	
	NEW_BLOCK(Bsp4_StraightWay1, group4_placeHolder, 0xD80, 0x1B00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay2, group4_placeHolder, 0x1080, 0x1B00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay3, group4_placeHolder, 0xD80, 0x1800, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay4, group4_placeHolder, 0x1080, 0x1800, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay5, group4_placeHolder, 0xD80, 0x1500, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay6, group4_placeHolder, 0x1080, 0x1500, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay7, group4_placeHolder, 0xD80, 0x1200, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay8, group4_placeHolder, 0x1080, 0x1200, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay9, group4_placeHolder, 0xD80, 0xF00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay10, group4_placeHolder, 0x1080, 0xF00, NULL, 0x1800, 0x808080),
	
	TEX_2X2(Bsp4_StraightWay1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp4_StraightWay2, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp4_StraightWay1].draw_order_low = 0x800000,
	.quadBlock[Bsp4_StraightWay2].draw_order_low = 0x1044000,
	TEX_2X2(Bsp4_StraightWay3, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp4_StraightWay4, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp4_StraightWay3].draw_order_low = 0x800000,
	.quadBlock[Bsp4_StraightWay4].draw_order_low = 0x1044000,
	TEX_2X2(Bsp4_StraightWay5, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp4_StraightWay6, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp4_StraightWay5].draw_order_low = 0x800000,
	.quadBlock[Bsp4_StraightWay6].draw_order_low = 0x1044000,
	TEX_2X2(Bsp4_StraightWay7, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp4_StraightWay8, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp4_StraightWay7].draw_order_low = 0x800000,
	.quadBlock[Bsp4_StraightWay8].draw_order_low = 0x1044000,
	TEX_2X2(Bsp4_StraightWay9, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp4_StraightWay10, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp4_StraightWay9].draw_order_low = 0x800000,
	.quadBlock[Bsp4_StraightWay10].draw_order_low = 0x1044000,
	
	NEW_BLOCK(Bsp4_StraightWay11_Turbo_9800, turbo_pad, 0xD80, 0xC00, NULL, 0x9800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay12_Turbo_1840, turbo_pad, 0xD80, 0xC00, NULL, 0x1840, 0x808080),
	.quadBlock[Bsp4_StraightWay12_Turbo_1840].terrain_type = 1,
	.quadBlock[Bsp4_StraightWay11_Turbo_9800].draw_order_low = FACE_NegZ,
	
	NEW_BLOCK(Bsp4_StraightWay13, group4_placeHolder, 0xD80, 0x900, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay14, group4_placeHolder, 0x1080, 0x900, NULL, 0x1800, 0x808080),
	
	TEX_2X2(Bsp4_StraightWay13, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp4_StraightWay14, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp4_StraightWay13].draw_order_low = 0x800000,
	.quadBlock[Bsp4_StraightWay14].draw_order_low = 0x1044000,
	
	SET_POSY_FLAT(Bsp4_StraightWay1,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay2,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay3,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay4,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay5,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay6,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay7,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay8,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay9,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay10,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay11_Turbo_9800,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay12_Turbo_1840,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay13,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay14,-0x300),
	
	// ====== End of BSP block =========

	NEW_BLOCK(Bsp2_StraightWay15, group4_placeHolder, 0xD80, 0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_StraightWay16, group4_placeHolder, 0x1080, 0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_StraightWay17, group4_placeHolder, 0xD80, 0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_StraightWay18, group4_placeHolder, 0x1080, 0x300, NULL, 0x1800, 0x808080),
	
	SET_POSY_FLAT(Bsp2_StraightWay15,-0x300),
	SET_POSY_FLAT(Bsp2_StraightWay16,-0x300),
	SET_POSY_FLAT(Bsp2_StraightWay17,-0x300),
	SET_POSY_FLAT(Bsp2_StraightWay18,-0x300),
	
	TEX_2X2(Bsp2_StraightWay15, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	.quadBlock[Bsp2_StraightWay15].draw_order_low = 0x800000,
	
	TEX_2X2(Bsp2_StraightWay16, group4_tileCenter, group4_tileCenter, group4_tileCenter, group4_tileCenter),
	.quadBlock[Bsp2_StraightWay16].draw_order_low = 0x1044000,
	
	// BR, BL, TR, TL
	TEX_2X2(Bsp2_StraightWay17, group4_tileCorner, group4_tileEdge, group4_tileEdge, group4_tileCenter),
	.quadBlock[Bsp2_StraightWay17].draw_order_low = 0x808100,
	
	TEX_2X2(Bsp2_StraightWay18, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	.quadBlock[Bsp2_StraightWay18].draw_order_low = 0x808100,
	
	NEW_BLOCK(Bsp2_TurnRight1, group4_placeHolder, 0x1380, 0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight2, group4_placeHolder, 0x1380, 0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight3, group4_placeHolder, 0x1680, 0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight4, group4_placeHolder, 0x1680, 0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight5, group4_placeHolder, 0x1980, 0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight6, group4_placeHolder, 0x1980, 0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight7, group4_placeHolder, 0x1C80, 0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight8, group4_placeHolder, 0x1C80, 0x600, NULL, 0x1800, 0x808080),
	
	// BR, BL, TR, TL
	TEX_2X2(Bsp2_TurnRight1, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_TurnRight2, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_TurnRight1].draw_order_low = 0x808100,
	.quadBlock[Bsp2_TurnRight2].draw_order_low = 0x1984000,
	
	TEX_2X2(Bsp2_TurnRight3, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_TurnRight4, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_TurnRight3].draw_order_low = 0x808100,
	.quadBlock[Bsp2_TurnRight4].draw_order_low = 0x1984000,
	
	TEX_2X2(Bsp2_TurnRight5, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_TurnRight6, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_TurnRight5].draw_order_low = 0x808100,
	.quadBlock[Bsp2_TurnRight6].draw_order_low = 0x1984000,
	
	SET_POSY_FLAT(Bsp2_TurnRight1,-0x300),
	SET_POSY_FLAT(Bsp2_TurnRight2,-0x300),
	SET_POSY_FLAT(Bsp2_TurnRight3,-0x300),
	SET_POSY_FLAT(Bsp2_TurnRight4,-0x300),
	SET_POSY_FLAT(Bsp2_TurnRight5,-0x300),
	SET_POSY_FLAT(Bsp2_TurnRight6,-0x300),
	
	MAKE_RAMP(
		Bsp2_TurnRight7, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp2_TurnRight8, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_TurnRight7, -0x300, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_TurnRight8, -0x300, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	TEX_2X2(Bsp2_TurnRight7, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp2_TurnRight7].draw_order_low = 0x1044000,
	
	// BR, BL, TR, TL assuming you're rotation is 0,0,0
	TEX_2X2(Bsp2_TurnRight8, group4_tileCenter, group4_tileEdge, group4_tileEdge, group4_tileCorner),
	.quadBlock[Bsp2_TurnRight8].draw_order_low = 0x18c4000,
	
	NEW_BLOCK(Bsp2_Middle_Turbo_1840, turbo_pad, 0x1C80, 0, NULL, 0x1840, 0x808080),
	NEW_BLOCK(Bsp2_Middle_Turbo_9800, turbo_pad, 0x1C80, 0, NULL, 0x9800, 0x808080),
	.quadBlock[Bsp2_Middle_Turbo_1840].terrain_type = 1,
	.quadBlock[Bsp2_Middle_Turbo_9800].draw_order_low = FACE_NegZ,
	
	MAKE_RAMP(
		Bsp2_Middle_Turbo_1840, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp2_Middle_Turbo_9800, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_Middle_Turbo_1840, -0x300, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_Middle_Turbo_9800, -0x300, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	NEW_BLOCK(Bsp2_GoBack0, group4_placeHolder, 0x1C80, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_GoBack1, group4_placeHolder, 0x1C80, -0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_GoBack2, group4_placeHolder, 0x1980, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_GoBack3, group4_placeHolder, 0x1980, -0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_GoBack4, group4_placeHolder, 0x1680, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_GoBack5, group4_placeHolder, 0x1680, -0x600, NULL, 0x1800, 0x808080),
	
	TEX_2X2(Bsp2_GoBack0, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp2_GoBack0].draw_order_low = 0x1044000,
	
	TEX_2X2(Bsp2_GoBack1, group4_tileEdge, group4_tileCorner, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp2_GoBack1].draw_order_low = 0x1044100,
	
	TEX_2X2(Bsp2_GoBack3, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_GoBack2, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_GoBack3].draw_order_low = 0x808100,
	.quadBlock[Bsp2_GoBack2].draw_order_low = 0x1984000,
	TEX_2X2(Bsp2_GoBack5, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_GoBack4, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_GoBack5].draw_order_low = 0x808100,
	.quadBlock[Bsp2_GoBack4].draw_order_low = 0x1984000,
	
	NEW_BLOCK(Bsp2_GoBack6, group4_placeHolder, 0x1380, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_GoBack7, group4_placeHolder, 0x1380, -0x600, NULL, 0x1800, 0x808080),
	
	TEX_2X2(Bsp2_GoBack7, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_GoBack6, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_GoBack7].draw_order_low = 0x808100,
	.quadBlock[Bsp2_GoBack6].draw_order_low = 0x1984000,
	
	MAKE_RAMP(
		Bsp2_GoBack0, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp2_GoBack1, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_GoBack0, -0x300, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_GoBack1, -0x300, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),

	SET_POSY_FLAT(Bsp2_GoBack2,-0x300),
	SET_POSY_FLAT(Bsp2_GoBack3,-0x300),
	SET_POSY_FLAT(Bsp2_GoBack4,-0x300),
	SET_POSY_FLAT(Bsp2_GoBack5,-0x300),
	SET_POSY_FLAT(Bsp2_GoBack6,-0x300),
	SET_POSY_FLAT(Bsp2_GoBack7,-0x300),
	
	NEW_BLOCK(Bsp2_TowardsRamp1, group4_placeHolder, 0xD80, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TowardsRamp2, group4_placeHolder, 0x1080, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TowardsRamp3, group4_placeHolder, 0xD80, -0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TowardsRamp4, group4_placeHolder, 0x1080, -0x600, NULL, 0x1800, 0x808080),

	TEX_2X2(Bsp2_TowardsRamp4, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_TowardsRamp2, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_TowardsRamp4].draw_order_low = 0x808100,
	.quadBlock[Bsp2_TowardsRamp2].draw_order_low = 0x1984000,
	TEX_2X2(Bsp2_TowardsRamp3, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_TowardsRamp1, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_TowardsRamp3].draw_order_low = 0x808100,
	.quadBlock[Bsp2_TowardsRamp1].draw_order_low = 0x1984000,

	SET_POSY_FLAT(Bsp2_TowardsRamp1,-0x300),
	SET_POSY_FLAT(Bsp2_TowardsRamp2,-0x300),
	SET_POSY_FLAT(Bsp2_TowardsRamp3,-0x300),
	SET_POSY_FLAT(Bsp2_TowardsRamp4,-0x300),
	
	// === Last turn, back to startline ===
	
	NEW_BLOCK(Bsp2_RampUp1, group4_placeHolder, 0xA80, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_RampUp2_Turbo_9800, super_turbo_pad, 0xA80, -0x600, NULL, 0x9800, 0x808080),
	.quadBlock[Bsp2_RampUp2_Turbo_9800].draw_order_low = FACE_NegX,
	
	MAKE_RAMP(
		Bsp2_RampUp1, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp2_RampUp2_Turbo_9800, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_RampUp1, -0x300, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_RampUp2_Turbo_9800, -0x300, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	NEW_BLOCK(Bsp2_RampUp3_Turbo_9800, turbo_pad, 0x780, -0x300, NULL, 0x9800, 0x808080),
	NEW_BLOCK(Bsp2_RampUp4, group4_placeHolder, 0x780, -0x600, NULL, 0x1800, 0x808080),
	.quadBlock[Bsp2_RampUp3_Turbo_9800].draw_order_low = FACE_NegX,
	
	MAKE_RAMP(
		Bsp2_RampUp3_Turbo_9800, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp2_RampUp4, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_RampUp3_Turbo_9800, -0x180, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_RampUp4, -0x180, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	NEW_BLOCK(Bsp2_RampUp5_Turbo_1840, super_turbo_pad, 0xA80, -0x600, NULL, 0x1840, 0x808080),
	
	MAKE_RAMP(
		Bsp2_RampUp5_Turbo_1840, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_RampUp5_Turbo_1840, -0x300, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	NEW_BLOCK(Bsp2_RampUp6_Turbo_1840, turbo_pad, 0x780, -0x300, NULL, 0x1840, 0x808080),
	
	MAKE_RAMP(
		Bsp2_RampUp6_Turbo_1840, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_RampUp6_Turbo_1840, -0x180, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	// turn into turbo, if flagsQ is 0x1840
	// 1 for normal, 2 for super turbo
	.quadBlock[Bsp2_RampUp5_Turbo_1840].terrain_type = 2,
	.quadBlock[Bsp2_RampUp6_Turbo_1840].terrain_type = 1,
	
	TEX_2X2(Bsp2_RampUp4, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_RampUp1, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_RampUp4].draw_order_low = 0x808100,
	.quadBlock[Bsp2_RampUp1].draw_order_low = 0x1984000,
	
	#define SET_ID(y, x) .quadBlock[x].blockID = y-x
	
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+0),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+1),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+2),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+3),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+4),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+5),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+6),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+7),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+8),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+9),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+10),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+11),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+12),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+13),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+14),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+15),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+16),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+17),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+18),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+19),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+20),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+21),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+22),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+23),
	
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+0),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+1),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+2),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+3),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+4),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+5),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+6),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+7),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+8),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+9),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+10),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+11),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+12),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+13),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+14),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+15),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+16),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+17),
	
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+0),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+1),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+2),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+3),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+4),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+5),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+6),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+7),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+8),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+9),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+10),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+11),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+12),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+13),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+14),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+15),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+16),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+17),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+18),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+19),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+20),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+21),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+22),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+23),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+24),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+25),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+26),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+27),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+28),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+29),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+30),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+31),
	
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+0),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+1),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+2),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+3),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+4),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+5),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+6),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+7),

	SET_ID(Bsp4_Last,Bsp4_FirstBlock+0),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+1),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+2),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+3),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+4),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+5),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+6),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+7),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+8),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+9),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+10),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+11),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+12),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+13),
	
	#define SET_CHECKPOINT(cpi, block) \
		.quadBlock[block].checkpointIndex = cpi
	
	// startline must have last checkpoint (min dist)
	SET_CHECKPOINT(CPI_OnSpawn, Bsp0_BehindStart1),
	SET_CHECKPOINT(CPI_OnSpawn, Bsp0_BehindStart2),
	SET_CHECKPOINT(CPI_OnSpawn, Bsp0_BehindStart3),
	SET_CHECKPOINT(CPI_OnSpawn, Bsp0_BehindStart4),
	SET_CHECKPOINT(CPI_OnSpawn, Bsp0_StartLine1),
	SET_CHECKPOINT(CPI_OnSpawn, Bsp0_StartLine2),
	
	// right after startline must have first checkpoint (max dist)
	SET_CHECKPOINT(CPI_AfterSpawn, Bsp0_AfterStart1),
	SET_CHECKPOINT(CPI_AfterSpawn, Bsp0_AfterStart2),
	
	SET_CHECKPOINT(CPI_DownRamp1, Bsp0_DownRamp1),
	SET_CHECKPOINT(CPI_DownRamp1, Bsp0_DownRamp2),
	SET_CHECKPOINT(CPI_DownRamp1, Bsp0_DownRamp3),
	SET_CHECKPOINT(CPI_DownRamp1, Bsp0_DownRamp4),
	SET_CHECKPOINT(CPI_DownRamp1, Bsp0_DownRamp5),
	SET_CHECKPOINT(CPI_DownRamp1, Bsp0_DownRamp6),
	
	SET_CHECKPOINT(CPI_FlatDip, Bsp0_FlatDip1),
	SET_CHECKPOINT(CPI_FlatDip, Bsp0_FlatDip2),
	SET_CHECKPOINT(CPI_FlatDip, Bsp0_FlatDip3),
	
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp1),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp2_Turbo_9800),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp3),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp4),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp5_Turbo_9800),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp6),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp7_Turbo_1840),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp8_Turbo_1840),
	
	SET_CHECKPOINT(CPI_LandJump, Bsp3_FlatTop1),
	SET_CHECKPOINT(CPI_LandJump, Bsp3_FlatTop2),
	SET_CHECKPOINT(CPI_LandJump, Bsp3_FlatTop3),
	SET_CHECKPOINT(CPI_LandJump, Bsp3_FlatTop4),
	SET_CHECKPOINT(CPI_LandJump, Bsp3_FlatTop5),
	SET_CHECKPOINT(CPI_LandJump, Bsp3_FlatTop6),
	
	SET_CHECKPOINT(CPI_Turn90, Bsp3_FlatTop7),
	SET_CHECKPOINT(CPI_Turn90, Bsp3_FlatTop8),
	
	SET_CHECKPOINT(CPI_Turn90, Bsp1_TurnLeft1),
	SET_CHECKPOINT(CPI_Turn90, Bsp1_TurnLeft2),
	SET_CHECKPOINT(CPI_Turn90, Bsp1_TurnLeft3_Turbo_9800),
	SET_CHECKPOINT(CPI_Turn90, Bsp1_TurnLeft4_Turbo_9800),
	SET_CHECKPOINT(CPI_Turn90, Bsp1_TurnLeft5_Turbo_1840),
	SET_CHECKPOINT(CPI_Turn90, Bsp1_TurnLeft6_Turbo_1840),
	
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnLeft7),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnLeft8),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack1_Turbo_9800),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack2_Turbo_9800),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack3_Turbo_1840),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack4_Turbo_1840),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack5),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack6),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack7),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack8),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack9),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack10),
		
	
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay1),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay2),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay3),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay4),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay5),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay6),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay7),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay8),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay9),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay10),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay11_Turbo_9800),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay12_Turbo_1840),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay13),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay14),
	
	SET_CHECKPOINT(CPI_Corner, Bsp2_StraightWay15),
	SET_CHECKPOINT(CPI_Corner, Bsp2_StraightWay16),
	SET_CHECKPOINT(CPI_Corner, Bsp2_StraightWay17),
	SET_CHECKPOINT(CPI_Corner, Bsp2_StraightWay18),
	SET_CHECKPOINT(CPI_Corner, Bsp2_TurnRight1),
	SET_CHECKPOINT(CPI_Corner, Bsp2_TurnRight2),
	
	SET_CHECKPOINT(CPI_PreTurbo, Bsp2_TurnRight3),
	SET_CHECKPOINT(CPI_PreTurbo, Bsp2_TurnRight4),
	SET_CHECKPOINT(CPI_PreTurbo, Bsp2_TurnRight5),
	SET_CHECKPOINT(CPI_PreTurbo, Bsp2_TurnRight6),
	SET_CHECKPOINT(CPI_PreTurbo, Bsp2_TurnRight7),
	SET_CHECKPOINT(CPI_PreTurbo, Bsp2_TurnRight8),
	
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_Middle_Turbo_9800),
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_Middle_Turbo_1840),
	
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_GoBack0),
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_GoBack1),
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_GoBack2),
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_GoBack3),
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_GoBack4),
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_GoBack5),
	
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_GoBack6),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_GoBack7),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_TowardsRamp1),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_TowardsRamp2),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_TowardsRamp3),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_TowardsRamp4),
	
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp1),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp2_Turbo_9800),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp3_Turbo_9800),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp4),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp5_Turbo_1840),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp6_Turbo_1840),
	
	.checkpointNodes =
	{
		// first node[0] is always the node
		// after crossing startline, used to get track length
		
		[CPI_AfterSpawn] =
		{
			.pos = {0, 0, 0x300},
			.distToFinish = 0x1C00,
			.nextIndex_forward = CPI_DownRamp1,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_OnSpawn,
			.nextIndex_right = -1,
		},
		
		[CPI_DownRamp1] =
		{
			.pos = {0, -0x200, 0x900},
			.distToFinish = 0x1800,
			.nextIndex_forward = CPI_FlatDip,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_AfterSpawn,
			.nextIndex_right = -1,
		},
		
		[CPI_FlatDip] =
		{
			.pos = {0x180, -0x480, 0xED4},
			.distToFinish = 0x1400,
			.nextIndex_forward = CPI_UpRamp1,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_DownRamp1,
			.nextIndex_right = -1,
		},
		
		[CPI_UpRamp1] =
		{
			.pos = {0, -0x200, 0x1800},
			.distToFinish = 0x1000,
			.nextIndex_forward = CPI_LandJump,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_FlatDip,
			.nextIndex_right = -1,
		},
		
		[CPI_LandJump] =
		{
			.pos = {0x180, 0, 0x2200},
			.distToFinish = 0xE00,
			.nextIndex_forward = CPI_Turn90,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_UpRamp1,
			.nextIndex_right = -1,
		},
		
		
		[CPI_Turn90] =
		{
			.pos = {0x180, 0, 0x2800},
			.distToFinish = 0xC00,
			.nextIndex_forward = CPI_Turn180,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_LandJump,
			.nextIndex_right = -1,
		},
		
		
		[CPI_Turn180] =
		{
			.pos = {0xF00, 0, 0x2800},
			.distToFinish = 0xA00,
			.nextIndex_forward = CPI_FlatRun,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_Turn90,
			.nextIndex_right = -1,
		},
		
		[CPI_FlatRun] =
		{
			.pos = {0xF00, -0x300, 0x1800},
			.distToFinish = 0x800,
			.nextIndex_forward = CPI_Corner,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_Turn180,
			.nextIndex_right = -1,
		},
		
		[CPI_Corner] =
		{
			.pos = {0xF00, -0x300, 0x480},
			.distToFinish = 0x7F0,
			.nextIndex_forward = CPI_PreTurbo,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_FlatRun,
			.nextIndex_right = -1,
		},
		
		[CPI_PreTurbo] =
		{
			.pos = {0x1800, -0x300, 0x480},
			.distToFinish = 0x5B0,
			.nextIndex_forward = CPI_OnTurbo,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_Corner,
			.nextIndex_right = -1,
		},
		
		// dont spawn on here, just use it for FORWARD/BACKWARD
		[CPI_OnTurbo] =
		{
			.pos = {0x1C80, -0x180, 0},
			.distToFinish = 0x520,
			.nextIndex_forward = CPI_PostTurbo,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_PreTurbo,
			.nextIndex_right = -1,
		},
		
		[CPI_PostTurbo] =
		{
			.pos = {0x1800, -0x300, -0x480},
			.distToFinish = 0x490,
			.nextIndex_forward = CPI_UpRamp2,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_OnTurbo,
			.nextIndex_right = -1,
		},
		
		[CPI_UpRamp2] =
		{
			.pos = {0xF00, -0x300, -0x480},
			.distToFinish = 0x400,
			.nextIndex_forward = CPI_OnSpawn,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_PostTurbo,
			.nextIndex_right = -1,
		},
		
		// last node,
		// must be the spawn, with dist=1
		[CPI_OnSpawn] =
		{
			.pos = {0, 0, 0},
			.distToFinish = 1,
			.nextIndex_forward = CPI_AfterSpawn,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_UpRamp2,
			.nextIndex_right = -1,
		}
	},
	
	// ========== bsp ======================
	
	.bsp =
	{
		// root node
		[0] =
		{
			.flag = 0,
			.id = 0,
			.box =
			{
				.min = {-0x8000, -0x490, -0x8000},
				.max = {0x8000, 0x066E, 0x8000}
			},
			
			.data =
			{
				.branch =
				{
					// need more info on this
					.axis = {0x1000, 0x0, 0x0, 0xFF40},
					
					// 0x4000 signifies leaf node
					.childID = {0x2, 0x1},
				}
			}
		},
		
		// branch for side of map opposite to startline
		[1] =
		{
			.flag = 0,
			.id = 1,
			.box =
			{
				.min = {0x300, -0x490, -0x800},
				.max = {0x2100, 0x100, 0x2E00}
			},
			
			.data =
			{
				.branch =
				{
					// need more info on this
					.axis = {0, 0x0, 0x1000, 0xFF40},
					
					// 0x4000 signifies leaf node
					.childID = {0x3, 0x4004},
				}
			}
		},
		
		// branch for startline side
		[2] =
		{
			.flag = 0,
			.id = 2,
			.box =
			{
				.min = {-0x300, -0x490, -0x800},
				.max = {0x300, 0x100, 0x2E00}
			},
			
			.data =
			{
				.branch =
				{
					// need more info on this
					.axis = {0, 0x0, 0x1000, 0xFF40},
					
					// 0x4000 signifies leaf node
					.childID = {0x4005, 0x4006},
				}
			}
		},
		
		// leaf with u-turn and drop
		[3] =
		{
			.flag = 0,
			.id = 3,
			.box =
			{
				.min = {0x300, -0x490, 0x781},
				.max = {0x2100, 0x100, 0x2E00}
			},
			
			.data =
			{
				.branch =
				{
					// need more info on this
					.axis = {0, 0x0, 0x1000, 0xFF40},
					
					// 0x4000 signifies leaf node
					.childID = {0x4007, 0x4008},
				}
			}
		},
		
		// leaf yet to come
		[4] =
		{
			.flag = 0x1,
			.id = 4,
			.box =
			{
				.min = {0x300, -0x490, -0x800},
				.max = {0x2100, 0x100, 0x77F}
			},
			
			.data =
			{
				.leaf =
				{
					// empty, should be [64]
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = Bsp2_BlockCount,
					.ptrQuadBlockArray = LEV_OFFSETOF(quadBlock[Bsp2_FirstBlock])
				}
			}
		},
	
		// leaf with startline
		[5] =
		{
			.flag = 0x1,
			.id = 5,
			.box =
			{
				.min = {-0x300, -0x490, -0x800},
				.max = {0x300, 0x100, 0x1D00} // see if that cuts it
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = Bsp0_BlockCount,
					.ptrQuadBlockArray = LEV_OFFSETOF(quadBlock[Bsp0_FirstBlock])
				}
			}
		},
		
		// leaf with start of 180 U-Turn
		[6] =
		{
			.flag = 0x1,
			.id = 6,
			.box =
			{
				.min = {-0x300, -0x300, 0x1D00},
				.max = {0x300, 0x100, 0x2E00}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = Bsp3_BlockCount,
					.ptrQuadBlockArray = LEV_OFFSETOF(quadBlock[Bsp3_FirstBlock])
				}
			}
		},

		[7] =
		{
			.flag = 0x1,
			.id = 7,
			.box =
			{
				.min = {0xB00, -0x490, 0x781},
				.max = {0x1300, -0x100, 0x1F00}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = Bsp4_BlockCount,
					.ptrQuadBlockArray = LEV_OFFSETOF(quadBlock[Bsp4_FirstBlock])
				}
			}
		},
		
		// leaf with end of 180 U-Turn
		[8] = 
		{
			.flag = 0x1,
			.id = 8,
			.box =
			{
				.min = {0x300, -0x300, 0x1F00},
				.max = {0x1300, 0x100, 0x2E00}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = Bsp1_BlockCount,
					.ptrQuadBlockArray = LEV_OFFSETOF(quadBlock[Bsp1_FirstBlock])
				}
			}
		}
	},
	
	.leafList =
	{
		// PVS_DROPNONE
		-1,-1,
	},
	
	.faceList =
	{
		// PVS_DROPNONE
		-1,-1,-1,-1,-1,
	},
	
	.pvs =
	{
		[PVS_DROPNONE] =
		{
			.visLeafSrc = OFFSETOF(struct LevelFile, leafList[2*PVS_DROPNONE]),
			.visFaceSrc = OFFSETOF(struct LevelFile, faceList[5*PVS_DROPNONE]),
			.visInstSrc = 0,
			.visExtraSrc = 0,
		},
	},
	
	.visMem =
	{
		// P1
		.visLeafList[0] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP1[0]),
		.visFaceList[0] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP1[4]),
		.bspList[0] = LEV_OFFSETOF(VisMem_bspList_RenderListP1[0]),
		
		// P2
		.visLeafList[1] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP2[0]),
		.visFaceList[1] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP2[4]),
		.bspList[1] = LEV_OFFSETOF(VisMem_bspList_RenderListP2[0]),
		
		// P3
		.visLeafList[2] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP3[0]),
		.visFaceList[2] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP3[4]),
		.bspList[2] = LEV_OFFSETOF(VisMem_bspList_RenderListP3[0]),
		
		// P4
		.visLeafList[3] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP4[0]),
		.visFaceList[3] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP4[4]),
		.bspList[3] = LEV_OFFSETOF(VisMem_bspList_RenderListP4[0]),
	},
	
	// initialize for leaf nodes only
	.VisMem_bspList_RenderListP1[2*4+1] = LEV_OFFSETOF(bsp[4]),
	.VisMem_bspList_RenderListP2[2*4+1] = LEV_OFFSETOF(bsp[4]),
	.VisMem_bspList_RenderListP3[2*4+1] = LEV_OFFSETOF(bsp[4]),
	.VisMem_bspList_RenderListP4[2*4+1] = LEV_OFFSETOF(bsp[4]),
	
	.VisMem_bspList_RenderListP1[2*5+1] = LEV_OFFSETOF(bsp[5]),
	.VisMem_bspList_RenderListP2[2*5+1] = LEV_OFFSETOF(bsp[5]),
	.VisMem_bspList_RenderListP3[2*5+1] = LEV_OFFSETOF(bsp[5]),
	.VisMem_bspList_RenderListP4[2*5+1] = LEV_OFFSETOF(bsp[5]),
	
	.VisMem_bspList_RenderListP1[2*6+1] = LEV_OFFSETOF(bsp[6]),
	.VisMem_bspList_RenderListP2[2*6+1] = LEV_OFFSETOF(bsp[6]),
	.VisMem_bspList_RenderListP3[2*6+1] = LEV_OFFSETOF(bsp[6]),
	.VisMem_bspList_RenderListP4[2*6+1] = LEV_OFFSETOF(bsp[6]),
	
	.VisMem_bspList_RenderListP1[2*7+1] = LEV_OFFSETOF(bsp[7]),
	.VisMem_bspList_RenderListP2[2*7+1] = LEV_OFFSETOF(bsp[7]),
	.VisMem_bspList_RenderListP3[2*7+1] = LEV_OFFSETOF(bsp[7]),
	.VisMem_bspList_RenderListP4[2*7+1] = LEV_OFFSETOF(bsp[7]),
	
	.VisMem_bspList_RenderListP1[2*8+1] = LEV_OFFSETOF(bsp[8]),
	.VisMem_bspList_RenderListP2[2*8+1] = LEV_OFFSETOF(bsp[8]),
	.VisMem_bspList_RenderListP3[2*8+1] = LEV_OFFSETOF(bsp[8]),
	.VisMem_bspList_RenderListP4[2*8+1] = LEV_OFFSETOF(bsp[8]),
	
	.navHeader = {LEV_OFFSETOF(navHeader1), 0, 0},
	
	.navHeader1 =
	{
		.magicNumber = -0x1303,
		.numPoints = 650,
		.posY_firstNode = 0,
		.last = LEV_OFFSETOF(navFrame[649]),
		
		// rampPhys
	},
		
	.map =
	{
		(72+NUM_BLOCKS*6)<<2,
		
		// 72
		LEV_OFFSETOF(level.ptr_mesh_info),
		LEV_OFFSETOF(level.visMem),
		LEV_OFFSETOF(level.ptrSpawnType1),
		LEV_OFFSETOF(level.ptr_restart_points),
		LEV_OFFSETOF(level.LevNavHeader),
		LEV_OFFSETOF(mInfo.ptrQuadBlockArray),
		LEV_OFFSETOF(mInfo.ptrVertexArray),
		LEV_OFFSETOF(mInfo.bspRoot),
		LEV_OFFSETOF(turbo_pad_anim.ptrNext),
		LEV_OFFSETOF(turbo_pad_anim.ptrarray[0]),
		LEV_OFFSETOF(turbo_pad_anim.ptrarray[1]),
		LEV_OFFSETOF(turbo_pad_anim.ptrarray[2]),
		LEV_OFFSETOF(turbo_pad_anim.ptrarray[3]),
		LEV_OFFSETOF(turbo_pad_anim.ptrarray[4]),
		LEV_OFFSETOF(turbo_pad_anim.ptrarray[5]),
		LEV_OFFSETOF(turbo_pad_anim.ptrarray[6]),
		LEV_OFFSETOF(turbo_pad_anim.ptrarray[7]),
		LEV_OFFSETOF(turbo_pad_anim.ptrarray[8]),
		LEV_OFFSETOF(turbo_pad_anim.ptrarray[9]),
		LEV_OFFSETOF(super_turbo_pad_anim.ptrNext),
		LEV_OFFSETOF(super_turbo_pad_anim.ptrarray[0]),
		LEV_OFFSETOF(super_turbo_pad_anim.ptrarray[1]),
		LEV_OFFSETOF(super_turbo_pad_anim.ptrarray[2]),
		LEV_OFFSETOF(super_turbo_pad_anim.ptrarray[3]),
		LEV_OFFSETOF(super_turbo_pad_anim.ptrarray[4]),
		LEV_OFFSETOF(super_turbo_pad_anim.ptrarray[5]),
		LEV_OFFSETOF(super_turbo_pad_anim.ptrarray[6]),
		LEV_OFFSETOF(super_turbo_pad_anim.ptrarray[7]),
		LEV_OFFSETOF(super_turbo_pad_anim.ptrarray[8]),
		LEV_OFFSETOF(super_turbo_pad_anim.ptrarray[9]),
		LEV_OFFSETOF(super_turbo_pad_anim.ptrarray[10]),
		LEV_OFFSETOF(bsp[4].data.leaf.ptrQuadBlockArray),
		LEV_OFFSETOF(bsp[5].data.leaf.ptrQuadBlockArray),
		LEV_OFFSETOF(bsp[6].data.leaf.ptrQuadBlockArray),
		LEV_OFFSETOF(bsp[7].data.leaf.ptrQuadBlockArray),
		LEV_OFFSETOF(bsp[8].data.leaf.ptrQuadBlockArray),
		LEV_OFFSETOF(pvs[0].visLeafSrc),
		LEV_OFFSETOF(pvs[0].visFaceSrc),
		LEV_OFFSETOF(visMem.visLeafList[0]),
		LEV_OFFSETOF(visMem.visLeafList[1]),
		LEV_OFFSETOF(visMem.visLeafList[2]),
		LEV_OFFSETOF(visMem.visLeafList[3]),
		LEV_OFFSETOF(visMem.visFaceList[0]),
		LEV_OFFSETOF(visMem.visFaceList[1]),
		LEV_OFFSETOF(visMem.visFaceList[2]),
		LEV_OFFSETOF(visMem.visFaceList[3]),
		LEV_OFFSETOF(visMem.bspList[0]),
		LEV_OFFSETOF(visMem.bspList[1]),
		LEV_OFFSETOF(visMem.bspList[2]),
		LEV_OFFSETOF(visMem.bspList[3]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP1[2*4+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP2[2*4+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP3[2*4+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP4[2*4+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP1[2*5+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP2[2*5+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP3[2*5+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP4[2*5+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP1[2*6+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP2[2*6+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP3[2*6+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP4[2*6+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP1[2*7+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP2[2*7+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP3[2*7+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP4[2*7+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP1[2*8+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP2[2*8+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP3[2*8+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP4[2*8+1]),
		LEV_OFFSETOF(navHeader[0]),
		LEV_OFFSETOF(navHeader1.last),

		// NUM_BLOCKS*6
		PTR_MAP_QUADBLOCK(0),
		PTR_MAP_QUADBLOCK(1),
		PTR_MAP_QUADBLOCK(2),
		PTR_MAP_QUADBLOCK(3),
		PTR_MAP_QUADBLOCK(4),
		PTR_MAP_QUADBLOCK(5),
		PTR_MAP_QUADBLOCK(6),
		PTR_MAP_QUADBLOCK(7),
		PTR_MAP_QUADBLOCK(8),
		PTR_MAP_QUADBLOCK(9),
		PTR_MAP_QUADBLOCK(10),
		PTR_MAP_QUADBLOCK(11),
		PTR_MAP_QUADBLOCK(12),
		PTR_MAP_QUADBLOCK(13),
		PTR_MAP_QUADBLOCK(14),
		PTR_MAP_QUADBLOCK(15),
		PTR_MAP_QUADBLOCK(16),
		PTR_MAP_QUADBLOCK(17),
		PTR_MAP_QUADBLOCK(18),
		PTR_MAP_QUADBLOCK(19),
		PTR_MAP_QUADBLOCK(20),
		PTR_MAP_QUADBLOCK(21),
		PTR_MAP_QUADBLOCK(22),
		PTR_MAP_QUADBLOCK(23),
		PTR_MAP_QUADBLOCK(24),
		PTR_MAP_QUADBLOCK(25),
		PTR_MAP_QUADBLOCK(26),
		PTR_MAP_QUADBLOCK(27),
		PTR_MAP_QUADBLOCK(28),
		PTR_MAP_QUADBLOCK(29),
		PTR_MAP_QUADBLOCK(30),
		PTR_MAP_QUADBLOCK(31),
		PTR_MAP_QUADBLOCK(32),
		PTR_MAP_QUADBLOCK(33),
		PTR_MAP_QUADBLOCK(34),
		PTR_MAP_QUADBLOCK(35),
		PTR_MAP_QUADBLOCK(36),
		PTR_MAP_QUADBLOCK(37),
		PTR_MAP_QUADBLOCK(38),
		PTR_MAP_QUADBLOCK(39),
		PTR_MAP_QUADBLOCK(40),
		PTR_MAP_QUADBLOCK(41),
		PTR_MAP_QUADBLOCK(42),
		PTR_MAP_QUADBLOCK(43),
		PTR_MAP_QUADBLOCK(44),
		PTR_MAP_QUADBLOCK(45),
		PTR_MAP_QUADBLOCK(46),
		PTR_MAP_QUADBLOCK(47),
		PTR_MAP_QUADBLOCK(48),
		PTR_MAP_QUADBLOCK(49),
		PTR_MAP_QUADBLOCK(50),
		PTR_MAP_QUADBLOCK(51),
		PTR_MAP_QUADBLOCK(52),
		PTR_MAP_QUADBLOCK(53),
		PTR_MAP_QUADBLOCK(54),
		PTR_MAP_QUADBLOCK(55),
		PTR_MAP_QUADBLOCK(56),
		PTR_MAP_QUADBLOCK(57),
		PTR_MAP_QUADBLOCK(58),
		PTR_MAP_QUADBLOCK(59),
		PTR_MAP_QUADBLOCK(60),
		PTR_MAP_QUADBLOCK(61),
		PTR_MAP_QUADBLOCK(62),
		PTR_MAP_QUADBLOCK(63),
		PTR_MAP_QUADBLOCK(64),
		PTR_MAP_QUADBLOCK(65),
		PTR_MAP_QUADBLOCK(66),
		PTR_MAP_QUADBLOCK(67),
		PTR_MAP_QUADBLOCK(68),
		PTR_MAP_QUADBLOCK(69),
		PTR_MAP_QUADBLOCK(70),
		PTR_MAP_QUADBLOCK(71),
		PTR_MAP_QUADBLOCK(72),
		PTR_MAP_QUADBLOCK(73),
		PTR_MAP_QUADBLOCK(74),
		PTR_MAP_QUADBLOCK(75),
		PTR_MAP_QUADBLOCK(76),
		PTR_MAP_QUADBLOCK(77),
		PTR_MAP_QUADBLOCK(78),
		PTR_MAP_QUADBLOCK(79),
		PTR_MAP_QUADBLOCK(80),
		PTR_MAP_QUADBLOCK(81),
		PTR_MAP_QUADBLOCK(82),
		PTR_MAP_QUADBLOCK(83),
		PTR_MAP_QUADBLOCK(84),
		PTR_MAP_QUADBLOCK(85),
		PTR_MAP_QUADBLOCK(86),
		PTR_MAP_QUADBLOCK(87),
		PTR_MAP_QUADBLOCK(88),
		PTR_MAP_QUADBLOCK(89),
		PTR_MAP_QUADBLOCK(90),
		PTR_MAP_QUADBLOCK(91),
		PTR_MAP_QUADBLOCK(92),
		PTR_MAP_QUADBLOCK(93),
		PTR_MAP_QUADBLOCK(94),
		PTR_MAP_QUADBLOCK(95),
		PTR_MAP_QUADBLOCK(96),
		PTR_MAP_QUADBLOCK(97),
	},
	
	.navFrame =
	{
{.pos = {128,1,-184}},
{.pos = {128,1,-173}},
{.pos = {128,1,-158}},
{.pos = {128,1,-140}},
{.pos = {128,1,-117}},
{.pos = {128,1,-91}},
{.pos = {128,1,-60}},
{.pos = {128,1,-27}},
{.pos = {128,1,11}},
{.pos = {128,1,53}},
{.pos = {128,1,98}},
{.pos = {128,1,148}},
{.pos = {128,1,203}},
{.pos = {128,1,261}},
{.pos = {128,1,321}},
{.pos = {128,1,379}},
{.pos = {128,1,439}},
{.pos = {128,1,499}},
{.pos = {128,1,558}},
{.pos = {128,1,618}},
{.pos = {128,1,678}},
{.pos = {128,1,738}},
{.pos = {128,1,798}},
{.pos = {128,1,858}},
{.pos = {128,1,915}},
{.pos = {128,1,975}},
{.pos = {128,1,1035}},
{.pos = {128,1,1095}},
{.pos = {128,1,1154}},
{.pos = {128,-2,1213}},
{.pos = {128,-9,1272}},
{.pos = {128,-19,1329}},
{.pos = {128,-33,1388}},
{.pos = {128,-50,1445}},
{.pos = {128,-70,1503}},
{.pos = {128,-95,1562}},
{.pos = {128,-123,1621}},
{.pos = {128,-154,1680}},
{.pos = {128,-188,1736}},
{.pos = {128,-226,1795}},
{.pos = {128,-268,1854}},
{.pos = {128,-313,1912}},
{.pos = {128,-360,1969}},
{.pos = {128,-412,2028}},
{.pos = {128,-463,2086}},
{.pos = {128,-490,2139}},
{.pos = {128,-518,2192}},
{.pos = {128,-545,2246}},
{.pos = {128,-573,2302}},
{.pos = {128,-601,2359}},
{.pos = {128,-630,2415}},
{.pos = {128,-659,2474}},
{.pos = {128,-688,2532}},
{.pos = {128,-718,2593}},
{.pos = {128,-749,2655}},
{.pos = {128,-781,2717}},
{.pos = {128,-812,2780}},
{.pos = {128,-844,2844}},
{.pos = {128,-875,2907}},
{.pos = {128,-908,2970}},
{.pos = {128,-939,3032}},
{.pos = {128,-970,3095}},
{.pos = {128,-1002,3158}},
{.pos = {128,-1033,3220}},
{.pos = {128,-1064,3283}},
{.pos = {128,-1096,3346}},
{.pos = {128,-1128,3410}},
{.pos = {128,-1148,3472}},
{.pos = {128,-1149,3533}},
{.pos = {128,-1150,3592}},
{.pos = {128,-1150,3652}},
{.pos = {128,-1150,3712}},
{.pos = {128,-1150,3771}},
{.pos = {128,-1150,3830}},
{.pos = {128,-1150,3888}},
{.pos = {128,-1150,3946}},
{.pos = {128,-1150,4003}},
{.pos = {128,-1150,4060}},
{.pos = {128,-1151,4114}},
{.pos = {128,-1151,4170}},
{.pos = {128,-1151,4225}},
{.pos = {128,-1151,4280}},
{.pos = {128,-1151,4334}},
{.pos = {128,-1151,4388}},
{.pos = {128,-1151,4440}},
{.pos = {128,-1151,4492}},
{.pos = {128,-1151,4545}},
{.pos = {128,-1151,4595}},
{.pos = {128,-1151,4646}},
{.pos = {128,-1151,4697}},
{.pos = {128,-1151,4748}},
{.pos = {128,-1151,4799}},
{.pos = {128,-1151,4849}},
{.pos = {128,-1151,4900}},
{.pos = {128,-1151,4951}},
{.pos = {128,-1145,4999}},
{.pos = {128,-1123,5044}},
{.pos = {128,-1095,5102}},
{.pos = {128,-1066,5163}},
{.pos = {128,-1037,5220}},
{.pos = {128,-1008,5278}},
{.pos = {128,-979,5338}},
{.pos = {128,-949,5398}},
{.pos = {128,-918,5458}},
{.pos = {128,-889,5517}},
{.pos = {128,-859,5577}},
{.pos = {128,-830,5635}},
{.pos = {128,-800,5695}},
{.pos = {128,-770,5755}},
{.pos = {128,-740,5814}},
{.pos = {128,-711,5872}},
{.pos = {128,-682,5930}},
{.pos = {128,-652,5990}},
{.pos = {128,-622,6050}},
{.pos = {128,-593,6108}},
{.pos = {128,-563,6167}},
{.pos = {128,-534,6228}},
{.pos = {128,-504,6287}},
{.pos = {128,-475,6345}},
{.pos = {128,-445,6405}},
{.pos = {128,-415,6465}},
{.pos = {128,-385,6525}},
{.pos = {128,-356,6583}},
{.pos = {128,-326,6642}},
{.pos = {128,-297,6700}},
{.pos = {128,-267,6760}},
{.pos = {128,-238,6818}},
{.pos = {128,-208,6877}},
{.pos = {128,-179,6935}},
{.pos = {128,-150,6995}},
{.pos = {128,-120,7055}},
{.pos = {128,-90,7115}},
{.pos = {128,-60,7175}},
{.pos = {128,-30,7235}},
{.pos = {128,-1,7293}},
{.pos = {128,25,7354}},
{.pos = {128,49,7416}},
{.pos = {128,68,7475}},
{.pos = {128,84,7536}},
{.pos = {128,97,7598}},
{.pos = {128,107,7659}},
{.pos = {128,112,7720}},
{.pos = {128,115,7779}},
{.pos = {128,114,7840}},
{.pos = {128,109,7902}},
{.pos = {128,101,7961}},
{.pos = {128,90,8022}},
{.pos = {128,75,8083}},
{.pos = {128,56,8144}},
{.pos = {128,34,8205}},
{.pos = {128,8,8266}},
{.pos = {128,2,8327}},
{.pos = {128,2,8387}},
{.pos = {128,2,8447}},
{.pos = {128,1,8506}},
{.pos = {128,1,8563}},
{.pos = {128,1,8621}},
{.pos = {128,1,8679}},
{.pos = {128,1,8735}},
{.pos = {128,1,8791}},
{.pos = {129,1,8848}},
{.pos = {133,1,8903}},
{.pos = {138,1,8958}},
{.pos = {145,1,9011}},
{.pos = {153,1,9064}},
{.pos = {163,1,9117}},
{.pos = {173,1,9167}},
{.pos = {185,1,9218}},
{.pos = {198,1,9269}},
{.pos = {212,1,9318}},
{.pos = {227,1,9367}},
{.pos = {243,1,9415}},
{.pos = {259,1,9460}},
{.pos = {277,1,9506}},
{.pos = {295,1,9550}},
{.pos = {315,1,9594}},
{.pos = {335,1,9637}},
{.pos = {357,1,9679}},
{.pos = {379,1,9721}},
{.pos = {402,1,9761}},
{.pos = {426,1,9800}},
{.pos = {450,1,9837}},
{.pos = {475,1,9873}},
{.pos = {501,1,9909}},
{.pos = {527,1,9943}},
{.pos = {554,1,9977}},
{.pos = {582,1,10009}},
{.pos = {611,1,10039}},
{.pos = {640,1,10069}},
{.pos = {669,1,10098}},
{.pos = {698,1,10124}},
{.pos = {727,1,10149}},
{.pos = {758,1,10176}},
{.pos = {791,1,10203}},
{.pos = {826,1,10229}},
{.pos = {862,1,10255}},
{.pos = {899,1,10279}},
{.pos = {936,1,10302}},
{.pos = {973,1,10323}},
{.pos = {1011,1,10343}},
{.pos = {1050,1,10362}},
{.pos = {1090,2,10380}},
{.pos = {1131,1,10395}},
{.pos = {1172,1,10409}},
{.pos = {1213,1,10422}},
{.pos = {1255,1,10433}},
{.pos = {1297,1,10442}},
{.pos = {1339,1,10448}},
{.pos = {1381,1,10453}},
{.pos = {1422,1,10456}},
{.pos = {1463,1,10458}},
{.pos = {1502,1,10458}},
{.pos = {1542,1,10457}},
{.pos = {1582,1,10455}},
{.pos = {1648,1,10449}},
{.pos = {1715,1,10441}},
{.pos = {1781,1,10431}},
{.pos = {1844,1,10420}},
{.pos = {1910,1,10408}},
{.pos = {1974,1,10397}},
{.pos = {2039,1,10384}},
{.pos = {2105,1,10371}},
{.pos = {2171,1,10359}},
{.pos = {2236,1,10346}},
{.pos = {2301,1,10332}},
{.pos = {2366,1,10316}},
{.pos = {2431,1,10298}},
{.pos = {2493,1,10279}},
{.pos = {2556,1,10259}},
{.pos = {2619,1,10237}},
{.pos = {2682,1,10214}},
{.pos = {2744,1,10189}},
{.pos = {2805,1,10162}},
{.pos = {2865,1,10133}},
{.pos = {2925,1,10103}},
{.pos = {2982,1,10072}},
{.pos = {3040,1,10039}},
{.pos = {3097,1,10004}},
{.pos = {3153,1,9968}},
{.pos = {3208,1,9930}},
{.pos = {3262,1,9891}},
{.pos = {3316,1,9851}},
{.pos = {3368,1,9809}},
{.pos = {3417,1,9768}},
{.pos = {3466,1,9724}},
{.pos = {3514,1,9679}},
{.pos = {3562,1,9632}},
{.pos = {3608,1,9583}},
{.pos = {3651,1,9535}},
{.pos = {3694,1,9484}},
{.pos = {3735,1,9434}},
{.pos = {3775,1,9381}},
{.pos = {3814,1,9326}},
{.pos = {3850,1,9272}},
{.pos = {3885,1,9216}},
{.pos = {3919,1,9158}},
{.pos = {3949,1,9099}},
{.pos = {3978,1,9040}},
{.pos = {4004,1,8980}},
{.pos = {4029,1,8920}},
{.pos = {4051,1,8860}},
{.pos = {4071,1,8801}},
{.pos = {4089,1,8741}},
{.pos = {4107,1,8677}},
{.pos = {4123,1,8614}},
{.pos = {4137,1,8549}},
{.pos = {4150,1,8483}},
{.pos = {4160,1,8417}},
{.pos = {4167,1,8350}},
{.pos = {4172,1,8284}},
{.pos = {4174,1,8219}},
{.pos = {4174,2,8152}},
{.pos = {4171,1,8087}},
{.pos = {4167,-2,8021}},
{.pos = {4164,-9,7954}},
{.pos = {4160,-19,7887}},
{.pos = {4156,-33,7821}},
{.pos = {4153,-51,7754}},
{.pos = {4149,-72,7688}},
{.pos = {4145,-96,7622}},
{.pos = {4142,-123,7557}},
{.pos = {4138,-155,7491}},
{.pos = {4134,-190,7425}},
{.pos = {4131,-228,7359}},
{.pos = {4127,-270,7292}},
{.pos = {4123,-314,7228}},
{.pos = {4120,-363,7162}},
{.pos = {4116,-415,7096}},
{.pos = {4112,-471,7030}},
{.pos = {4109,-528,6966}},
{.pos = {4105,-591,6900}},
{.pos = {4102,-657,6834}},
{.pos = {4096,-727,6769}},
{.pos = {4088,-766,6703}},
{.pos = {4078,-767,6639}},
{.pos = {4066,-767,6574}},
{.pos = {4051,-767,6508}},
{.pos = {4035,-767,6443}},
{.pos = {4019,-767,6381}},
{.pos = {4003,-767,6316}},
{.pos = {3985,-767,6251}},
{.pos = {3968,-767,6189}},
{.pos = {3951,-767,6124}},
{.pos = {3934,-767,6062}},
{.pos = {3916,-767,5998}},
{.pos = {3899,-767,5934}},
{.pos = {3882,-767,5871}},
{.pos = {3866,-767,5810}},
{.pos = {3850,-767,5748}},
{.pos = {3833,-767,5686}},
{.pos = {3817,-767,5625}},
{.pos = {3802,-767,5564}},
{.pos = {3786,-767,5504}},
{.pos = {3770,-767,5444}},
{.pos = {3755,-767,5385}},
{.pos = {3740,-767,5326}},
{.pos = {3725,-767,5267}},
{.pos = {3710,-767,5211}},
{.pos = {3695,-767,5154}},
{.pos = {3680,-767,5097}},
{.pos = {3666,-767,5040}},
{.pos = {3651,-767,4984}},
{.pos = {3637,-767,4930}},
{.pos = {3623,-767,4875}},
{.pos = {3609,-767,4820}},
{.pos = {3595,-767,4768}},
{.pos = {3581,-767,4714}},
{.pos = {3569,-767,4660}},
{.pos = {3558,-767,4607}},
{.pos = {3548,-767,4554}},
{.pos = {3540,-767,4501}},
{.pos = {3532,-767,4448}},
{.pos = {3525,-767,4396}},
{.pos = {3519,-767,4345}},
{.pos = {3513,-767,4295}},
{.pos = {3507,-767,4245}},
{.pos = {3500,-767,4194}},
{.pos = {3494,-767,4144}},
{.pos = {3487,-767,4095}},
{.pos = {3480,-767,4045}},
{.pos = {3474,-767,3994}},
{.pos = {3467,-767,3944}},
{.pos = {3460,-767,3894}},
{.pos = {3454,-767,3845}},
{.pos = {3447,-767,3796}},
{.pos = {3442,-767,3747}},
{.pos = {3438,-767,3698}},
{.pos = {3437,-767,3650}},
{.pos = {3437,-767,3602}},
{.pos = {3438,-767,3554}},
{.pos = {3440,-767,3507}},
{.pos = {3442,-767,3461}},
{.pos = {3445,-767,3417}},
{.pos = {3449,-767,3350}},
{.pos = {3453,-767,3285}},
{.pos = {3458,-767,3219}},
{.pos = {3466,-767,3152}},
{.pos = {3475,-766,3086}},
{.pos = {3486,-767,3020}},
{.pos = {3499,-767,2955}},
{.pos = {3513,-767,2889}},
{.pos = {3529,-767,2824}},
{.pos = {3546,-767,2762}},
{.pos = {3565,-767,2698}},
{.pos = {3586,-767,2634}},
{.pos = {3609,-767,2572}},
{.pos = {3634,-767,2509}},
{.pos = {3660,-767,2448}},
{.pos = {3688,-767,2387}},
{.pos = {3717,-767,2327}},
{.pos = {3747,-767,2270}},
{.pos = {3780,-767,2212}},
{.pos = {3815,-767,2155}},
{.pos = {3851,-767,2098}},
{.pos = {3888,-767,2043}},
{.pos = {3927,-767,1989}},
{.pos = {3968,-767,1936}},
{.pos = {4010,-767,1884}},
{.pos = {4052,-767,1835}},
{.pos = {4097,-767,1786}},
{.pos = {4144,-767,1738}},
{.pos = {4192,-767,1691}},
{.pos = {4241,-767,1646}},
{.pos = {4292,-767,1603}},
{.pos = {4344,-767,1561}},
{.pos = {4397,-767,1521}},
{.pos = {4452,-767,1482}},
{.pos = {4506,-767,1446}},
{.pos = {4563,-767,1411}},
{.pos = {4621,-767,1378}},
{.pos = {4680,-767,1347}},
{.pos = {4738,-767,1319}},
{.pos = {4799,-767,1292}},
{.pos = {4861,-767,1267}},
{.pos = {4924,-767,1245}},
{.pos = {4987,-767,1225}},
{.pos = {5049,-767,1209}},
{.pos = {5112,-767,1194}},
{.pos = {5176,-767,1181}},
{.pos = {5239,-767,1171}},
{.pos = {5303,-767,1164}},
{.pos = {5365,-767,1159}},
{.pos = {5428,-767,1156}},
{.pos = {5490,-767,1156}},
{.pos = {5550,-767,1158}},
{.pos = {5610,-767,1162}},
{.pos = {5671,-767,1169}},
{.pos = {5728,-767,1177}},
{.pos = {5787,-767,1187}},
{.pos = {5845,-767,1196}},
{.pos = {5903,-767,1205}},
{.pos = {5960,-767,1214}},
{.pos = {6015,-767,1222}},
{.pos = {6069,-767,1230}},
{.pos = {6125,-767,1238}},
{.pos = {6178,-767,1246}},
{.pos = {6233,-767,1254}},
{.pos = {6287,-767,1262}},
{.pos = {6340,-767,1270}},
{.pos = {6393,-767,1278}},
{.pos = {6446,-767,1286}},
{.pos = {6498,-767,1293}},
{.pos = {6549,-767,1300}},
{.pos = {6599,-767,1303}},
{.pos = {6650,-767,1306}},
{.pos = {6700,-767,1307}},
{.pos = {6750,-766,1306}},
{.pos = {6799,-767,1305}},
{.pos = {6847,-767,1302}},
{.pos = {6895,-767,1298}},
{.pos = {6934,-754,1293}},
{.pos = {6967,-738,1289}},
{.pos = {6998,-723,1283}},
{.pos = {7028,-710,1278}},
{.pos = {7055,-696,1271}},
{.pos = {7081,-683,1265}},
{.pos = {7106,-671,1258}},
{.pos = {7130,-659,1250}},
{.pos = {7152,-647,1242}},
{.pos = {7174,-637,1234}},
{.pos = {7195,-626,1225}},
{.pos = {7215,-616,1217}},
{.pos = {7234,-606,1207}},
{.pos = {7253,-597,1198}},
{.pos = {7270,-589,1188}},
{.pos = {7288,-580,1178}},
{.pos = {7306,-571,1168}},
{.pos = {7325,-562,1156}},
{.pos = {7343,-552,1144}},
{.pos = {7364,-542,1130}},
{.pos = {7384,-532,1115}},
{.pos = {7405,-521,1099}},
{.pos = {7427,-511,1081}},
{.pos = {7449,-500,1061}},
{.pos = {7471,-489,1040}},
{.pos = {7492,-478,1017}},
{.pos = {7511,-468,994}},
{.pos = {7529,-459,971}},
{.pos = {7546,-451,947}},
{.pos = {7561,-443,923}},
{.pos = {7576,-436,900}},
{.pos = {7589,-429,876}},
{.pos = {7602,-423,852}},
{.pos = {7613,-417,828}},
{.pos = {7624,-412,805}},
{.pos = {7633,-407,782}},
{.pos = {7642,-403,760}},
{.pos = {7651,-399,735}},
{.pos = {7658,-395,712}},
{.pos = {7665,-392,688}},
{.pos = {7671,-389,664}},
{.pos = {7676,-386,641}},
{.pos = {7680,-384,618}},
{.pos = {7684,-382,595}},
{.pos = {7687,-381,573}},
{.pos = {7688,-380,552}},
{.pos = {7689,-379,531}},
{.pos = {7690,-380,511}},
{.pos = {7690,-380,491}},
{.pos = {7689,-380,473}},
{.pos = {7688,-380,454}},
{.pos = {7686,-380,434}},
{.pos = {7685,-382,413}},
{.pos = {7681,-383,392}},
{.pos = {7671,-389,343}},
{.pos = {7657,-395,291}},
{.pos = {7639,-405,229}},
{.pos = {7617,-416,166}},
{.pos = {7593,-428,104}},
{.pos = {7566,-441,43}},
{.pos = {7538,-455,-16}},
{.pos = {7509,-469,-76}},
{.pos = {7480,-484,-136}},
{.pos = {7450,-499,-197}},
{.pos = {7421,-514,-257}},
{.pos = {7392,-528,-316}},
{.pos = {7362,-543,-377}},
{.pos = {7333,-557,-436}},
{.pos = {7302,-573,-497}},
{.pos = {7269,-590,-556}},
{.pos = {7234,-607,-615}},
{.pos = {7198,-625,-674}},
{.pos = {7162,-643,-730}},
{.pos = {7123,-663,-787}},
{.pos = {7082,-683,-843}},
{.pos = {7042,-703,-897}},
{.pos = {6998,-725,-952}},
{.pos = {6952,-748,-1006}},
{.pos = {6905,-764,-1059}},
{.pos = {6857,-765,-1109}},
{.pos = {6806,-766,-1156}},
{.pos = {6754,-766,-1201}},
{.pos = {6701,-766,-1244}},
{.pos = {6649,-766,-1285}},
{.pos = {6595,-766,-1325}},
{.pos = {6540,-766,-1363}},
{.pos = {6484,-766,-1400}},
{.pos = {6428,-766,-1436}},
{.pos = {6372,-766,-1468}},
{.pos = {6313,-767,-1501}},
{.pos = {6254,-767,-1532}},
{.pos = {6196,-767,-1560}},
{.pos = {6135,-767,-1587}},
{.pos = {6073,-767,-1613}},
{.pos = {6011,-767,-1637}},
{.pos = {5948,-767,-1659}},
{.pos = {5884,-767,-1679}},
{.pos = {5819,-767,-1697}},
{.pos = {5757,-767,-1712}},
{.pos = {5692,-767,-1725}},
{.pos = {5628,-767,-1736}},
{.pos = {5564,-767,-1746}},
{.pos = {5502,-767,-1752}},
{.pos = {5438,-767,-1757}},
{.pos = {5376,-767,-1760}},
{.pos = {5313,-767,-1761}},
{.pos = {5251,-767,-1760}},
{.pos = {5189,-767,-1757}},
{.pos = {5128,-767,-1752}},
{.pos = {5067,-767,-1745}},
{.pos = {5008,-767,-1735}},
{.pos = {4950,-767,-1724}},
{.pos = {4892,-767,-1712}},
{.pos = {4835,-767,-1697}},
{.pos = {4779,-767,-1681}},
{.pos = {4724,-767,-1662}},
{.pos = {4670,-767,-1642}},
{.pos = {4617,-767,-1621}},
{.pos = {4566,-767,-1597}},
{.pos = {4516,-767,-1572}},
{.pos = {4468,-767,-1548}},
{.pos = {4419,-767,-1522}},
{.pos = {4371,-767,-1497}},
{.pos = {4323,-767,-1473}},
{.pos = {4275,-767,-1448}},
{.pos = {4228,-767,-1424}},
{.pos = {4182,-767,-1400}},
{.pos = {4135,-767,-1376}},
{.pos = {4091,-767,-1353}},
{.pos = {4046,-767,-1330}},
{.pos = {4001,-767,-1307}},
{.pos = {3955,-767,-1283}},
{.pos = {3910,-766,-1261}},
{.pos = {3864,-767,-1240}},
{.pos = {3818,-767,-1222}},
{.pos = {3771,-767,-1205}},
{.pos = {3725,-767,-1190}},
{.pos = {3678,-767,-1177}},
{.pos = {3634,-767,-1165}},
{.pos = {3588,-767,-1153}},
{.pos = {3542,-767,-1143}},
{.pos = {3498,-767,-1133}},
{.pos = {3454,-767,-1122}},
{.pos = {3409,-767,-1112}},
{.pos = {3366,-767,-1102}},
{.pos = {3322,-767,-1091}},
{.pos = {3280,-767,-1081}},
{.pos = {3239,-767,-1072}},
{.pos = {3197,-767,-1063}},
{.pos = {3156,-767,-1057}},
{.pos = {3115,-767,-1051}},
{.pos = {3075,-765,-1047}},
{.pos = {3042,-748,-1044}},
{.pos = {3012,-734,-1043}},
{.pos = {2985,-722,-1042}},
{.pos = {2960,-709,-1042}},
{.pos = {2936,-697,-1043}},
{.pos = {2914,-687,-1044}},
{.pos = {2893,-676,-1044}},
{.pos = {2872,-667,-1045}},
{.pos = {2853,-656,-1046}},
{.pos = {2834,-647,-1047}},
{.pos = {2815,-637,-1048}},
{.pos = {2794,-627,-1048}},
{.pos = {2772,-616,-1049}},
{.pos = {2749,-604,-1050}},
{.pos = {2725,-592,-1051}},
{.pos = {2699,-580,-1052}},
{.pos = {2672,-567,-1053}},
{.pos = {2644,-553,-1055}},
{.pos = {2615,-538,-1056}},
{.pos = {2584,-523,-1057}},
{.pos = {2553,-507,-1058}},
{.pos = {2521,-491,-1060}},
{.pos = {2487,-474,-1061}},
{.pos = {2452,-457,-1062}},
{.pos = {2416,-438,-1064}},
{.pos = {2378,-420,-1066}},
{.pos = {2340,-400,-1067}},
{.pos = {2300,-380,-1069}},
{.pos = {2259,-360,-1070}},
{.pos = {2199,-330,-1073}},
{.pos = {2142,-301,-1075}},
{.pos = {2082,-272,-1078}},
{.pos = {2022,-242,-1080}},
{.pos = {1962,-212,-1083}},
{.pos = {1902,-182,-1085}},
{.pos = {1843,-152,-1087}},
{.pos = {1783,-122,-1090}},
{.pos = {1725,-93,-1092}},
{.pos = {1665,-63,-1093}},
{.pos = {1606,-33,-1092}},
{.pos = {1546,-4,-1089}},
{.pos = {1485,22,-1085}},
{.pos = {1426,44,-1076}},
{.pos = {1366,64,-1065}},
{.pos = {1306,80,-1051}},
{.pos = {1247,93,-1035}},
{.pos = {1191,102,-1017}},
{.pos = {1133,107,-995}},
{.pos = {1077,109,-972}},
{.pos = {1022,108,-946}},
{.pos = {968,103,-917}},
{.pos = {915,95,-887}},
{.pos = {864,83,-854}},
{.pos = {814,68,-819}},
{.pos = {766,49,-782}},
{.pos = {719,26,-743}},
{.pos = {675,2,-703}},
{.pos = {628,2,-659}},
{.pos = {582,2,-613}},
{.pos = {536,2,-565}},
{.pos = {491,1,-516}},
{.pos = {447,1,-466}},
{.pos = {404,1,-414}},
{.pos = {363,1,-362}},
{.pos = {323,1,-308}},
{.pos = {285,1,-256}},
{.pos = {248,1,-200}},
	},
};
