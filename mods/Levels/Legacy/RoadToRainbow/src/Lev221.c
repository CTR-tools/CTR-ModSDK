// Only for generating LEV files
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Woverride-init"
#pragma GCC diagnostic ignored "-Woverflow"

#include <common.h>
#include "../../levelBuilder.h"

#define NUM_BLOCKS 66

struct LevelFile
{
	void* ptrMap;
	struct Level level;
	struct mesh_info mInfo;
	
	// NonScroll "High" textures
	struct IconGroup4 group4_ground;
	
	// NonScroll "Low" textures
	struct TextureLayout texlayout_ramp_low;
	
	// Scroll textures, one "duplicate" per set,
	// Duplicate MUST have higher texY than original
	struct IconGroup4 turbo_pad[10];
	struct IconGroup4 turbo_pad_dup;
	
	// CycleTex_LEV requires data in THIS order
	struct AnimTex turbo_pad_anim;
	struct IconGroup4* TPA_ptrarray[10];
	void* animTexTerminator;
	
	// SpawnData
	struct SpawnType1 ptrSpawnType1;
	
	// Geometry
	struct QuadBlock quadBlock[NUM_BLOCKS];
	struct LevVertex levVertex[NUM_BLOCKS*9];
	
	// Checkpoints
	struct CheckpointNode noderespawnsthing[NUM_BLOCKS]; // all empty, this is a battle map
	
	// Visibility
	struct BSP bsp[3];
	struct PVS pvs;
	int visBitIndex[4];
	struct VisMem visMem;
	
	// leave empty
	// DstMemcpy must be big for PVS to copy into,
	// RenderList must be big enough for 2 pointers to all BSP nodes
	int VisMem_bitIndex_DstMemcpyP1[8];
	int VisMem_bspList_RenderListP1[3*2];
	int VisMem_bitIndex_DstMemcpyP2[8];
	int VisMem_bspList_RenderListP2[3*2];
	int VisMem_bitIndex_DstMemcpyP3[8];
	int VisMem_bspList_RenderListP3[3*2];
	int VisMem_bitIndex_DstMemcpyP4[8];
	int VisMem_bspList_RenderListP4[3*2];
	
	int map[3];
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
		.numBspNodes = 3,
	},
	
	.group4_ground =
	{
		// 512_0_32_20_16_16_0.png		
		.far    = ImageName_Blend(512, 0, 32, 20, 16, 16, BPP_4, TRANS_50), // very far
		.middle = ImageName_Blend(512, 0, 32, 20, 16, 16, BPP_4, TRANS_50), // far
		.near   = ImageName_Blend(512, 0, 32, 20, 16, 16, BPP_4, TRANS_50), // close
		.mosaic = ImageName_Blend(512, 0, 32, 20, 16, 16, BPP_4, TRANS_50), // very close
	},
	
	.texlayout_ramp_low = ImageName_Blend(640, 0, 32, 22, 12, 12, BPP_4, TRANS_50),

	.turbo_pad =
	{
		// Dont move to LevelBuilder.h,
		// This changes depending on the level
		
		#define SAME_TURBO_SINGLE(XX) \
		ImageName_Scroll(576, 16, 32, 21, 32, 16, BPP_4, TRANS_50, XX)
		
		#define SAME_TURBO_GROUP(XX) \
		{ \
			.far    = SAME_TURBO_SINGLE(XX), \
			.middle = SAME_TURBO_SINGLE(XX), \
			.near   = SAME_TURBO_SINGLE(XX), \
			.mosaic = SAME_TURBO_SINGLE(XX), \
		}
		
		[0] = SAME_TURBO_GROUP(0),
		[1] = SAME_TURBO_GROUP(2),
		[2] = SAME_TURBO_GROUP(3),
		[3] = SAME_TURBO_GROUP(5),
		[4] = SAME_TURBO_GROUP(6),
		[5] = SAME_TURBO_GROUP(8),
		[6] = SAME_TURBO_GROUP(10),
		[7] = SAME_TURBO_GROUP(11),
		[8] = SAME_TURBO_GROUP(13),
		[9] = SAME_TURBO_GROUP(14),
	},
	
	.turbo_pad_dup =
	{
		.far	= ImageName_Blend(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50),
		.middle	= ImageName_Blend(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50),
		.near	= ImageName_Blend(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50),
		.mosaic	= ImageName_Blend(576, 0, 32, 21, 32, 16, BPP_4, TRANS_50),
	},
	
	.turbo_pad_anim =
	{
		.ptrActiveTex = LEV_OFFSETOF(turbo_pad[0]),
		.numFrames = 10,
		.frameDuration = 0,
		.shiftFactor = 0,
		.frameIndex = 0,
	},
	
	.TPA_ptrarray =
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
	
	// CycleTex_LEV uses pointer to first AnimTex
	// to symbolize the end of the final ptrArray
	.animTexTerminator = 
		LEV_OFFSETOF(turbo_pad_anim),
	
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
	.quadBlock[28].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[28].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[28].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,

	.quadBlock[29].ptr_texture_mid[0] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[29].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[29].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[29].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,

	.quadBlock[30].ptr_texture_mid[0] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[30].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[30].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[30].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,

	.quadBlock[31].ptr_texture_mid[0] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[31].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[31].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[31].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,

	// see NikoLevelUSF/trackSpecificData.h
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
	.quadBlock[60].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[60].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[60].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,

	.quadBlock[61].ptr_texture_mid[0] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[61].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[61].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[61].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,

	.quadBlock[62].ptr_texture_mid[0] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[62].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[62].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[62].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,

	.quadBlock[63].ptr_texture_mid[0] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[63].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[63].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[63].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,

	// see TileTrauma/trackSpecificData.h
	.quadBlock[60].draw_order_low = 0x1144500,
	.quadBlock[61].draw_order_low = 0x1144500,
	.quadBlock[62].draw_order_low = 0x1144500,
	.quadBlock[63].draw_order_low = 0x1144500,
	
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
	
	// invisible, not on BSP
	NEW_BLOCK(64, turbo_pad[0], 		0x6FFF, 0x6FFF, NULL, 0, 0x808080),
	NEW_BLOCK(65, turbo_pad_dup, 		0x6FFF, 0x6FFF, NULL, 0, 0x808080),
	
	// ========== bsp ======================
	
	.bsp =
	{
		// root node
		BSP_BRANCH(0, SPLIT_X, 0x1, 0x2),
		
		BSP_LEAF(1, 32, 32),
		BSP_LEAF(2, 0, 32),
	},
	
	.pvs =
	{
		.visLeafSrc = LEV_OFFSETOF(visBitIndex[0]),
		.visFaceSrc = LEV_OFFSETOF(visBitIndex[0]),
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
	
	.map =
	{
		(2)<<2,

		LEV_OFFSETOF(pvs.visLeafSrc),
		LEV_OFFSETOF(pvs.visFaceSrc),
	},
};
