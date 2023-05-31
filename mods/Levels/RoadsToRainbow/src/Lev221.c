#include <common.h>
#include "../../levelBuilder.h"

#define NUM_BLOCKS 64

struct LevelFile
{
	void* ptrMap;
	struct Level level;
	struct mesh_info mInfo;
	struct IconGroup4 group4_ground;
	struct IconGroup4 turbo_pad[10];
	struct AnimTex turbo_pad_anim;
	struct TextureLayout texlayout_ramp_low;
	struct SpawnType1 ptrSpawnType1;
	struct CheckpointNode noderespawnsthing[NUM_BLOCKS]; // all empty, this is a battle map
	struct QuadBlock quadBlock[NUM_BLOCKS];
	struct LevVertex levVertex[NUM_BLOCKS*9];
	struct BSP bsp[3];
	struct PVS pvs;
	int visBitIndex[4];
	struct VisMem visMem;
	
	int VisMem_bitIndex_DstMemcpyP1[8]; // leave empty
	int VisMem_bspList_RenderListP1[3*2];
	int VisMem_bitIndex_DstMemcpyP2[8]; // leave empty
	int VisMem_bspList_RenderListP2[3*2];
	int VisMem_bitIndex_DstMemcpyP3[8]; // leave empty
	int VisMem_bspList_RenderListP3[3*2];
	int VisMem_bitIndex_DstMemcpyP4[8]; // leave empty
	int VisMem_bspList_RenderListP4[3*2];
	
	int map[(44+NUM_BLOCKS*6)+1];
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
		.DriverSpawn[0].pos = {0,0,0},
		.DriverSpawn[0].rot = {0,0-0x400,0},
		
		.DriverSpawn[1].pos = {-0xA80,0,0},
		.DriverSpawn[1].rot = {0,0-0x400,0},
		
		.DriverSpawn[2].pos = {-0xA80,0,0x1500+0xA80},
		.DriverSpawn[2].rot = {0,0x800-0x400,0},
		
		.DriverSpawn[3].pos = {0,0,0x1500+0xA80},
		.DriverSpawn[3].rot = {0,0x800-0x400,0},
		
		.ptrSpawnType1 = LEV_OFFSETOF(ptrSpawnType1),
		
		.clearColor[0].rgb = {0x0, 0x0, 0x28},
		.clearColor[0].enable = 1,
		
		// only non-zero for Race maps
		// battle maps need array, but still set CNT to zero
		.cnt_restart_points = 0,
		.ptr_restart_points = LEV_OFFSETOF(noderespawnsthing[0]),
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
		.numBspNodes = 3, // can be anything non-zero
	},
	
	.group4_ground =
	{
		// 512_0_32_20_16_16_0.png		
		.far    = ImageName_Blend(512, 0, 32, 20, 16, 16, BPP_4, TRANS_50), // very far
		.middle = ImageName_Blend(512, 0, 32, 20, 16, 16, BPP_4, TRANS_50), // far
		.near   = ImageName_Blend(512, 0, 32, 20, 16, 16, BPP_4, TRANS_50), // close
		.mosaic = ImageName_Blend(512, 0, 32, 20, 16, 16, BPP_4, TRANS_50), // very close
	},

	.turbo_pad =
	{
		[0] =
		{
			.far    = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 0),
			.middle = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 0),
			.near   = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 0),
			.mosaic = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 0),
		},
		[1] =
		{
			.far    = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 1),
			.middle = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 1),
			.near   = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 1),
			.mosaic = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 1),
		},
		[2] =
		{
			.far    = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 2),
			.middle = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 2),
			.near   = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 2),
			.mosaic = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 2),
		},
		[3] =
		{
			.far    = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 3),
			.middle = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 3),
			.near   = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 3),
			.mosaic = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 3),
		},
		[4] =
		{
			.far    = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 4),
			.middle = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 4),
			.near   = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 4),
			.mosaic = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 4),
		},
		[5] =
		{
			.far    = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 5),
			.middle = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 5),
			.near   = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 5),
			.mosaic = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 5),
		},
		[6] =
		{
			.far    = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 6),
			.middle = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 6),
			.near   = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 6),
			.mosaic = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 6),
		},
		[7] =
		{
			.far    = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 7),
			.middle = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 7),
			.near   = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 7),
			.mosaic = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 7),
		},
		[8] =
		{
			.far    = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 8),
			.middle = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 8),
			.near   = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 8),
			.mosaic = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 8),
		},
		[9] =
		{
			.far    = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 9),
			.middle = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 9),
			.near   = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 9),
			.mosaic = TurboPadImage(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50, 9),
		},
	},
	
	.texlayout_ramp_low = ImageName_Blend(640, 0, 32, 22, 12, 12, BPP_4, TRANS_50),

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
			LEV_OFFSETOF(turbo_pad_anim),
		},
	},
	
	// this must exist, or else camera fly-in
	// checks for "count" without nullptr check,
	// and crashes dereferencing nullptr on real PSX
	.ptrSpawnType1 =
	{
		.count = 0,
	},
	
	// +z is forward
	// +x is left, not right
	
	// spawn
	NEW_BLOCK(0, group4_ground, -0x180, 0, NULL, 0x1800, RGBtoBGR(0xFF0000)),
	NEW_BLOCK(1, group4_ground, 0x180, 0, NULL, 0x1800, RGBtoBGR(0xFF2000)),
	
	// forward
	NEW_BLOCK(2, group4_ground, -0x180, 0x300, NULL, 0x1800, RGBtoBGR(0xFF2000)),
	NEW_BLOCK(3, group4_ground, 0x180, 0x300, NULL, 0x1800, RGBtoBGR(0xFF4000)),
	
	// forward
	NEW_BLOCK(4, group4_ground, -0x180, 0x600, NULL, 0x1800, RGBtoBGR(0xFF4000)),
	NEW_BLOCK(5, group4_ground, 0x180, 0x600, NULL, 0x1800, RGBtoBGR(0xFF6000)),
	
	// forward
	NEW_BLOCK(6, group4_ground, -0x180, 0x900, NULL, 0x1800, RGBtoBGR(0xFF6000)),
	NEW_BLOCK(7, group4_ground, 0x180, 0x900, NULL, 0x1800, RGBtoBGR(0xFF8000)),
		
	// forward
	NEW_BLOCK(8, group4_ground, -0x180, 0xC00, NULL, 0x1800, RGBtoBGR(0xFF8000)),
	NEW_BLOCK(9, group4_ground, 0x180, 0xC00, NULL, 0x1800, RGBtoBGR(0xFF8000)),
	
	// right
	NEW_BLOCK(10, group4_ground, -0x480, 0x900, NULL, 0x1800, RGBtoBGR(0xFF8000)),
	NEW_BLOCK(11, group4_ground, -0x480, 0xC00, NULL, 0x1800, RGBtoBGR(0x00FF00)),
	
	// right
	NEW_BLOCK(12, group4_ground, -0x780, 0x900, NULL, 0x1800, RGBtoBGR(0x00FF00)),
	NEW_BLOCK(13, group4_ground, -0x780, 0xC00, NULL, 0x1800, RGBtoBGR(0x00FF20)),
	
	// right
	NEW_BLOCK(14, group4_ground, -0xA80, 0x900, NULL, 0x1800, RGBtoBGR(0x00FF20)),
	NEW_BLOCK(15, group4_ground, -0xA80, 0xC00, NULL, 0x1800, RGBtoBGR(0x00FF40)),
	
	// right
	NEW_BLOCK(16, group4_ground, -0xD80, 0x900, NULL, 0x1800, RGBtoBGR(0x00FF40)),
	NEW_BLOCK(17, group4_ground, -0xD80, 0xC00, NULL, 0x1800, RGBtoBGR(0x00FF60)),
	
	// down
	NEW_BLOCK(18, group4_ground, -0xA80, 0x600, NULL, 0x1800, RGBtoBGR(0x00FF60)),
	NEW_BLOCK(19, group4_ground, -0xD80, 0x600, NULL, 0x1800, RGBtoBGR(0x00FF80)),
	
	// down
	NEW_BLOCK(20, group4_ground, -0xA80, 0x300, NULL, 0x1800, RGBtoBGR(0x0000FF)),
	NEW_BLOCK(21, group4_ground, -0xD80, 0x300, NULL, 0x1800, RGBtoBGR(0x2000FF)),
	
	// down
	NEW_BLOCK(22, group4_ground, -0xA80, 0x0, NULL, 0x1800, RGBtoBGR(0x2000FF)),
	NEW_BLOCK(23, group4_ground, -0xD80, 0x0, NULL, 0x1800, RGBtoBGR(0x4000FF)),
	
	// left
	NEW_BLOCK(24, group4_ground, -0x780, 0, NULL, 0x1800, RGBtoBGR(0x4000FF)),
	NEW_BLOCK(25, group4_ground, -0x780, 0x300, NULL, 0x1800, RGBtoBGR(0x6000FF)),
	
	// left
	NEW_BLOCK(26, group4_ground, -0x480, 0, NULL, 0x1800, RGBtoBGR(0x6000FF)),
	NEW_BLOCK(27, group4_ground, -0x480, 0x300, NULL, 0x1800, RGBtoBGR(0x8000FF)),
	
	// ramp
	NEW_BLOCK(28, group4_ground, -0xA80, 0xF00, NULL, 0x9800, 0x808080), // coll (1800)
	NEW_BLOCK(29, group4_ground, -0x180, 0xF00, NULL, 0x9800, 0x808080), // coll (1800)
	NEW_BLOCK(30, group4_ground, -0xA80, 0xF00, NULL, 0x1840, 0x808080), // turbo (1840)
	NEW_BLOCK(31, group4_ground, -0x180, 0xF00, NULL, 0x1840, 0x808080), // turbo (1840)
		
	.quadBlock[28].ptr_texture_mid[0] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[29].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[30].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[31].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,

	.quadBlock[28].draw_order_low = 0x380E000,
	.quadBlock[29].draw_order_low = 0x380E000,
	.quadBlock[30].draw_order_low = 0x380E000,
	.quadBlock[31].draw_order_low = 0x380E000,
	
	.quadBlock[28].ptr_texture_low = LEV_OFFSETOF(texlayout_ramp_low),
	.quadBlock[29].ptr_texture_low = LEV_OFFSETOF(texlayout_ramp_low),
	.quadBlock[30].ptr_texture_low = LEV_OFFSETOF(texlayout_ramp_low),
	.quadBlock[31].ptr_texture_low = LEV_OFFSETOF(texlayout_ramp_low),
	
	MAKE_RAMP(
		28, 0x100, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	MAKE_RAMP(
		29, 0x100,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	MAKE_RAMP(
		30, 0x100,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	MAKE_RAMP(
		31, 0x100,
		0,4,1,
		5,6,7,
		2,8,3
	),
		
	// turn into turbo, if flagsQ is 0x1840
	.quadBlock[30].terrain_type = 1,
	.quadBlock[31].terrain_type = 1,
	
	.quadBlock[0].blockID =  32-0-1,
	.quadBlock[1].blockID =  32-1-1,
	.quadBlock[2].blockID =  32-2-1,
	.quadBlock[3].blockID =  32-3-1,
	.quadBlock[4].blockID =  32-4-1,
	.quadBlock[5].blockID =  32-5-1,
	.quadBlock[6].blockID =  32-6-1,
	.quadBlock[7].blockID =  32-7-1,
	.quadBlock[8].blockID =  32-8-1,
	.quadBlock[9].blockID =  32-9-1,
	.quadBlock[10].blockID = 32-10-1,
	.quadBlock[11].blockID = 32-11-1,
	.quadBlock[12].blockID = 32-12-1,
	.quadBlock[13].blockID = 32-13-1,
	.quadBlock[14].blockID = 32-14-1,
	.quadBlock[15].blockID = 32-15-1,
	.quadBlock[16].blockID = 32-16-1,
	.quadBlock[17].blockID = 32-17-1,
	.quadBlock[18].blockID = 32-18-1,
	.quadBlock[19].blockID = 32-19-1,
	.quadBlock[20].blockID = 32-20-1,
	.quadBlock[21].blockID = 32-21-1,
	.quadBlock[22].blockID = 32-22-1,
	.quadBlock[23].blockID = 32-23-1,
	.quadBlock[24].blockID = 32-24-1,
	.quadBlock[25].blockID = 32-25-1,
	.quadBlock[26].blockID = 32-26-1,
	.quadBlock[27].blockID = 32-27-1,
	.quadBlock[28].blockID = 32-28-1,
	.quadBlock[29].blockID = 32-29-1,
	.quadBlock[30].blockID = 32-30-1,
	.quadBlock[31].blockID = 32-31-1,
	
	// ========== Other Side Of Map ======================
	
	// spawn
	NEW_BLOCK(32, group4_ground, -0x180, 0x1500+0, NULL, 0x1800, 0x303030),
	NEW_BLOCK(33, group4_ground, 0x180, 0x1500+0, NULL, 0x1800, 0x606060),
	
	// forward
	NEW_BLOCK(34, group4_ground, -0x180, 0x1500+0x300, NULL, 0x1800, 0xFFFFFF),
	NEW_BLOCK(35, group4_ground, 0x180, 0x1500+0x300, NULL, 0x1800, 0x303030),
	
	// forward
	NEW_BLOCK(36, group4_ground, -0x180, 0x1500+0x600, NULL, 0x1800, 0xFFFFFF),
	NEW_BLOCK(37, group4_ground, 0x180, 0x1500+0x600, NULL, 0x1800, 0xD0D0D0),
	
	// forward
	NEW_BLOCK(38, group4_ground, -0x180, 0x1500+0x900, NULL, 0x1800, 0xFFFFFF),
	NEW_BLOCK(39, group4_ground, 0x180, 0x1500+0x900, NULL, 0x1800, 0x707070),
		
	// forward
	NEW_BLOCK(40, group4_ground, -0x180, 0x1500+0xC00, NULL, 0x1800, 0x707070),
	NEW_BLOCK(41, group4_ground, 0x180, 0x1500+0xC00, NULL, 0x1800, 0xD0D0D0),
	
	// right
	NEW_BLOCK(42, group4_ground, -0x480, 0x1500+0x900, NULL, 0x1800, 0xFFFFFF),
	NEW_BLOCK(43, group4_ground, -0x480, 0x1500+0xC00, NULL, 0x1800, 0xD0D0D0),
	
	// right
	NEW_BLOCK(44, group4_ground, -0x780, 0x1500+0x900, NULL, 0x1800, 0xFFFFFF),
	NEW_BLOCK(45, group4_ground, -0x780, 0x1500+0xC00, NULL, 0x1800, 0x404040),
	
	// right
	NEW_BLOCK(46, group4_ground, -0xA80, 0x1500+0x900, NULL, 0x1800, 0xFFFFFF),
	NEW_BLOCK(47, group4_ground, -0xA80, 0x1500+0xC00, NULL, 0x1800, 0x707070),
	
	// right
	NEW_BLOCK(48, group4_ground, -0xD80, 0x1500+0x900, NULL, 0x1800, 0x707070),
	NEW_BLOCK(49, group4_ground, -0xD80, 0x1500+0xC00, NULL, 0x1800, 0xD0D0D0),
	
	// down
	NEW_BLOCK(50, group4_ground, -0xA80, 0x1500+0x600, NULL, 0x1800, 0xD0D0D0),
	NEW_BLOCK(51, group4_ground, -0xD80, 0x1500+0x600, NULL, 0x1800, 0x707070),
	
	// down
	NEW_BLOCK(52, group4_ground, -0xA80, 0x1500+0x300, NULL, 0x1800, 0xFFFFFF),
	NEW_BLOCK(53, group4_ground, -0xD80, 0x1500+0x300, NULL, 0x1800, 0x606060),
	
	// down
	NEW_BLOCK(54, group4_ground, -0xA80, 0x1500+0x0, NULL, 0x1800, 0x606060),
	NEW_BLOCK(55, group4_ground, -0xD80, 0x1500+0x0, NULL, 0x1800, 0x303030),
	
	// left
	NEW_BLOCK(56, group4_ground, -0x780, 0x1500+0, NULL, 0x1800, 0x303030),
	NEW_BLOCK(57, group4_ground, -0x780, 0x1500+0x300, NULL, 0x1800, 0xFFFFFF),
	
	// left
	NEW_BLOCK(58, group4_ground, -0x480, 0x1500+0, NULL, 0x1800, 0x606060),
	NEW_BLOCK(59, group4_ground, -0x480, 0x1500+0x300, NULL, 0x1800, 0xFFFFFF),
	
	// ramp
	NEW_BLOCK(60, group4_ground, -0xA80, 0x1500-0x300, NULL, 0x9800, 0x808080), // coll (1800)
	NEW_BLOCK(61, group4_ground, -0x180, 0x1500-0x300, NULL, 0x9800, 0x808080), // coll (1800)
	NEW_BLOCK(62, group4_ground, -0xA80, 0x1500-0x300, NULL, 0x1840, 0x808080), // turbo (1840)
	NEW_BLOCK(63, group4_ground, -0x180, 0x1500-0x300, NULL, 0x1840, 0x808080), // turbo (1840)
	
	.quadBlock[60].ptr_texture_mid[0] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[61].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[62].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[63].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,

	.quadBlock[60].draw_order_low = 0x380E000,
	.quadBlock[61].draw_order_low = 0x380E000,
	.quadBlock[62].draw_order_low = 0x380E000,
	.quadBlock[63].draw_order_low = 0x380E000,
	
	.quadBlock[60].ptr_texture_low = LEV_OFFSETOF(texlayout_ramp_low),
	.quadBlock[61].ptr_texture_low = LEV_OFFSETOF(texlayout_ramp_low),
	.quadBlock[62].ptr_texture_low = LEV_OFFSETOF(texlayout_ramp_low),
	.quadBlock[63].ptr_texture_low = LEV_OFFSETOF(texlayout_ramp_low),
	
	MAKE_RAMP(
		60, 0x100, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		61, 0x100,
		2,8,3,
		5,6,7,
		0,4,1 
	),
	
	MAKE_RAMP(
		62, 0x100,
		2,8,3,
		5,6,7,
		0,4,1 
	),
	
	MAKE_RAMP(
		63, 0x100,
		2,8,3,
		5,6,7,
		0,4,1 
	),
		
	// turn into turbo, if flagsQ is 0x1840
	.quadBlock[62].terrain_type = 1,
	.quadBlock[63].terrain_type = 1,
	
	.quadBlock[32].blockID = 64-0-1,
	.quadBlock[33].blockID = 64-1-1,
	.quadBlock[34].blockID = 64-2-1,
	.quadBlock[35].blockID = 64-3-1,
	.quadBlock[36].blockID = 64-4-1,
	.quadBlock[37].blockID = 64-5-1,
	.quadBlock[38].blockID = 64-6-1,
	.quadBlock[39].blockID = 64-7-1,
	.quadBlock[40].blockID = 64-8-1,
	.quadBlock[41].blockID = 64-9-1,
	.quadBlock[42].blockID = 64-10-1,
	.quadBlock[43].blockID = 64-11-1,
	.quadBlock[44].blockID = 64-12-1,
	.quadBlock[45].blockID = 64-13-1,
	.quadBlock[46].blockID = 64-14-1,
	.quadBlock[47].blockID = 64-15-1,
	.quadBlock[48].blockID = 64-16-1,
	.quadBlock[49].blockID = 64-17-1,
	.quadBlock[50].blockID = 64-18-1,
	.quadBlock[51].blockID = 64-19-1,
	.quadBlock[52].blockID = 64-20-1,
	.quadBlock[53].blockID = 64-21-1,
	.quadBlock[54].blockID = 64-22-1,
	.quadBlock[55].blockID = 64-23-1,
	.quadBlock[56].blockID = 64-24-1,
	.quadBlock[57].blockID = 64-25-1,
	.quadBlock[58].blockID = 64-26-1,
	.quadBlock[59].blockID = 64-27-1,
	.quadBlock[60].blockID = 64-28-1,
	.quadBlock[61].blockID = 64-29-1,
	.quadBlock[62].blockID = 64-30-1,
	.quadBlock[63].blockID = 64-31-1,
	
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
				.min = {-0x3000, 0xFFE4, -0x3000},
				.max = {0x3000, 0x066E, 0x3000}
			},
			
			.data =
			{
				.branch =
				{
					// need more info on this
					.axis = {0x1000, 0x0, 0x0, 0xFF40},
					
					// 0x4000 signifies leaf node
					.childID = {0x4002, 0x4001},
				}
			}
		},
		
		// leaf with nothing in it
		[1] =
		{
			.flag = 1,
			.id = 1,
			.box =
			{
				// random box that exists nowhere
				.min = {-0x1100, 0xFFE4, 0x1100},
				.max = {0x1100, 0x400, 0x2500}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = 32,
					.ptrQuadBlockArray = LEV_OFFSETOF(quadBlock[32])
				}
			}
		},
		
		// leaf with 1 quadblock
		[2] =
		{
			.flag = 1,
			.id = 2,
			.box =
			{
				// random box that exists nowhere
				.min = {-0x1100, 0xFFE4, -0x1100},
				.max = {0x1100, 0x400, 0x1100}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = 32,
					.ptrQuadBlockArray = LEV_OFFSETOF(quadBlock[0])
				}
			}
		},
	},
	
	.pvs =
	{
		.visLeafSrc = OFFSETOF(struct LevelFile, visBitIndex[0]),
		.visFaceSrc = OFFSETOF(struct LevelFile, visBitIndex[0]),
		.visInstSrc = 0,
		.visExtraSrc = 0,
	},
	
	.visBitIndex =
	{
		// all 0xFFFFFFFFFFFF
		-1, -1, -1, -1
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
	.VisMem_bspList_RenderListP1[2*1+1] = LEV_OFFSETOF(bsp[1]),
	.VisMem_bspList_RenderListP2[2*1+1] = LEV_OFFSETOF(bsp[1]),
	.VisMem_bspList_RenderListP3[2*1+1] = LEV_OFFSETOF(bsp[1]),
	.VisMem_bspList_RenderListP4[2*1+1] = LEV_OFFSETOF(bsp[1]),
	.VisMem_bspList_RenderListP1[2*2+1] = LEV_OFFSETOF(bsp[2]),
	.VisMem_bspList_RenderListP2[2*2+1] = LEV_OFFSETOF(bsp[2]),
	.VisMem_bspList_RenderListP3[2*2+1] = LEV_OFFSETOF(bsp[2]),
	.VisMem_bspList_RenderListP4[2*2+1] = LEV_OFFSETOF(bsp[2]),
	
	.map =
	{
		(44+NUM_BLOCKS*6)<<2,
		
		// 44
		LEV_OFFSETOF(level.ptr_mesh_info),
		LEV_OFFSETOF(level.visMem),
		LEV_OFFSETOF(level.ptr_anim_tex),
		LEV_OFFSETOF(level.ptrSpawnType1),
		LEV_OFFSETOF(level.ptr_restart_points),
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
		LEV_OFFSETOF(turbo_pad_anim.ptrarray[10]),
		LEV_OFFSETOF(bsp[1].data.leaf.ptrQuadBlockArray),
		LEV_OFFSETOF(bsp[2].data.leaf.ptrQuadBlockArray),
		LEV_OFFSETOF(pvs.visLeafSrc),
		LEV_OFFSETOF(pvs.visFaceSrc),
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
		LEV_OFFSETOF(VisMem_bspList_RenderListP1[2*1+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP2[2*1+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP3[2*1+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP4[2*1+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP1[2*2+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP2[2*2+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP3[2*2+1]),
		LEV_OFFSETOF(VisMem_bspList_RenderListP4[2*2+1]),

		// (NUM_BLOCKS*6)
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
		PTR_MAP_QUADBLOCK(63)
	},
};
