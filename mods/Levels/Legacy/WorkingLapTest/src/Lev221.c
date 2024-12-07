// Only for generating LEV files
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Woverride-init"
#pragma GCC diagnostic ignored "-Woverflow"

#include <common.h>
#include "../../levelBuilder.h"

#define NUM_BLOCKS 20

struct LevelFile
{
	void* ptrMap;
	struct Level level;
	struct mesh_info mInfo;
	struct IconGroup4 test_texture;
	struct SpawnType1 spawnType1;
	struct CheckpointNode noderespawnsthing[16];
	struct QuadBlock quadBlock[NUM_BLOCKS];
	struct LevVertex levVertex[NUM_BLOCKS*9];
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
	
	int map[(3)+1];
};

struct LevelFile file =
{
	.ptrMap = LEV_OFFSETOF(map[0]),
	
	.level =
	{
		.ptr_mesh_info = LEV_OFFSETOF(mInfo),
		.visMem = LEV_OFFSETOF(visMem),
		
		// the game will add +0x400 to the yaw of spawn positions automatically
		// we should probably look into why this even happens...
		.DriverSpawn[0].pos = {0,0,0},
		.DriverSpawn[0].rot = {0,0-0x400,0},
		
		.DriverSpawn[1].pos = {0,0,0},
		.DriverSpawn[1].rot = {0,0-0x400,0},
		
		.DriverSpawn[2].pos = {0,0,0},
		.DriverSpawn[2].rot = {0,0-0x400,0},
		
		.DriverSpawn[3].pos = {0,0,0},
		.DriverSpawn[3].rot = {0,0-0x400,0},
		
		.ptrSpawnType1 = LEV_OFFSETOF(spawnType1),
		
		.configFlags = 1,

		.glowGradient[0] =
		{
			.pointFrom = -0xF0,
			.pointTo = -0x10,
			.colorFrom = 0x8000,
			.colorTo = 0,
		},
		
		// amount of respawn points in the track
		// and pointer to respawn data itself
		.cnt_restart_points = 16,
		.ptr_restart_points = LEV_OFFSETOF(noderespawnsthing[0]),
	},
	
	// pointers and amounts of variables
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
	
	// quadblock texture type
	// see IconGroup4 in namespace_Decal.h
	.test_texture =
	{
		.far =    ImageName_Blend(512, 0, 32, 128, 32, 32, BPP_4, ADD), // very far
		.middle = ImageName_Blend(512, 0, 32, 128, 32, 32, BPP_4, ADD), // far
		.near =   ImageName_Blend(512, 0, 32, 128, 32, 32, BPP_4, ADD), // close
		.mosaic = ImageName_Blend(512, 0, 32, 128, 32, 32, BPP_4, ADD), // close
	},
	
	// this must exist, or else camera fly-in checks for "count" without nullptr check, and crashes dereferencing nullptr on real PSX
	.spawnType1 =
	{
		.count = 0,
	},

	// automatically-generated quadblock insertions courtesy of pngtotrack.py
	                                                                              NEW_BLOCK(0, test_texture, 0x0000, 0x0000, NULL, 0x1800,          (0xFFFFFF)),NEW_BLOCK(1,  test_texture, 0x0300, 0x0000, NULL, 0x1800,         (0x000000)),                                                                           
	NEW_BLOCK(2,  test_texture, -0x300, 0x0300, NULL, 0x1800, RGBtoBGR(0x804000)),NEW_BLOCK(3, test_texture, 0x0000, 0x0300, NULL, 0x1800,          (0xFFFFFF)),NEW_BLOCK(4,  test_texture, 0x0300, 0x0300, NULL, 0x1800, RGBtoBGR(0x804000)),NEW_BLOCK(5,  test_texture, 0x0600, 0x0300, NULL, 0x1800, RGBtoBGR(0x804000)),
	NEW_BLOCK(6,  test_texture, -0x300, 0x0600, NULL, 0x1800, RGBtoBGR(0x804000)),                                                                                                                                                            NEW_BLOCK(7,  test_texture, 0x0600, 0x0600, NULL, 0x1800, RGBtoBGR(0x804000)),
	NEW_BLOCK(8,  test_texture, -0x300, 0x0900, NULL, 0x1800, RGBtoBGR(0x804000)),                                                                                                                                                            NEW_BLOCK(9,  test_texture, 0x0600, 0x0900, NULL, 0x1800, RGBtoBGR(0x804000)),
	NEW_BLOCK(10, test_texture, -0x300, 0x0c00, NULL, 0x1800, RGBtoBGR(0x804000)),                                                                                                                                                            NEW_BLOCK(11, test_texture, 0x0600, 0x0c00, NULL, 0x1800, RGBtoBGR(0x804000)),
	NEW_BLOCK(12, test_texture, -0x300, 0x0f00, NULL, 0x1800, RGBtoBGR(0x804000)),                                                                                                                                                            NEW_BLOCK(13, test_texture, 0x0600, 0x0f00, NULL, 0x1800, RGBtoBGR(0x804000)),
	NEW_BLOCK(14, test_texture, -0x300, 0x1200, NULL, 0x1800, RGBtoBGR(0x804000)),NEW_BLOCK(15, test_texture, 0x0000, 0x1200, NULL, 0x1800, RGBtoBGR(0x804000)),NEW_BLOCK(16, test_texture, 0x0300, 0x1200, NULL, 0x1800, RGBtoBGR(0x804000)),NEW_BLOCK(17, test_texture, 0x0600, 0x1200, NULL, 0x1800, RGBtoBGR(0x804000)),
	                                                                              NEW_BLOCK(18, test_texture, 0x0000, 0x1500, NULL, 0x1800, RGBtoBGR(0x804000)),NEW_BLOCK(19, test_texture, 0x0300, 0x1500, NULL, 0x1800, RGBtoBGR(0x804000)),                                                                           

	/*
	
	   00 01    
	02 03 04 05 
	06       07 
	08       09 
	10       11 
	12       13 
	14 15 16 17 
	   18 19    
	
	*/
	
	// checkpoint and respawn indices
	// starts at 2 and ends at 3, which are the first and last quadblocks in terms of progression respectively
	// 0, 1, 18, and 19 aren't used for progression
	.quadBlock[2].checkpointIndex = 0,
	.quadBlock[6].checkpointIndex = 1,
	.quadBlock[8].checkpointIndex = 2,
	.quadBlock[10].checkpointIndex = 3,
	.quadBlock[12].checkpointIndex = 4,
	.quadBlock[14].checkpointIndex = 5,
	.quadBlock[15].checkpointIndex = 6,
	.quadBlock[16].checkpointIndex = 7,
	.quadBlock[17].checkpointIndex = 8,
	.quadBlock[13].checkpointIndex = 9,
	.quadBlock[11].checkpointIndex = 10,
	.quadBlock[9].checkpointIndex = 11,
	.quadBlock[7].checkpointIndex = 12,
	.quadBlock[5].checkpointIndex = 13,
	.quadBlock[4].checkpointIndex = 14,
	.quadBlock[3].checkpointIndex = 15,

	// checkpoint and respawn data, split into 16 nodes
	// the positions of each node are the same as certain quadblocks
	.noderespawnsthing =
	{
		[0] =
		{
			.pos = {-0x300, 0, 0x300}, // same as quadblock 2
			.distToFinish = 0x200*15,
			.nextIndex_forward = 1,
			.nextIndex_left = -1,
			.nextIndex_backward = 15,
			.nextIndex_right = -1,
		},
		[1] =
		{
			.pos = {-0x300, 0, 0x600}, // same as quadblock 6
			.distToFinish = 0x200*14,
			.nextIndex_forward = 2,
			.nextIndex_left = -1,
			.nextIndex_backward = 0,
			.nextIndex_right = -1,
		},
		[2] =
		{
			.pos = {-0x300, 0, 0x300*3}, // same as quadblock 8
			.distToFinish = 0x200*13,
			.nextIndex_forward = 3,
			.nextIndex_left = -1,
			.nextIndex_backward = 1,
			.nextIndex_right = -1,
		},
		[3] =
		{
			.pos = {-0x300, 0, 0x300*4}, // same as quadblock 10
			.distToFinish = 0x200*12,
			.nextIndex_forward = 4,
			.nextIndex_left = -1,
			.nextIndex_backward = 2,
			.nextIndex_right = -1,
		},
		[4] =
		{
			.pos = {-0x300, 0, 0x300*5}, // same as quadblock 12
			.distToFinish = 0x200*11,
			.nextIndex_forward = 5,
			.nextIndex_left = -1,
			.nextIndex_backward = 3,
			.nextIndex_right = -1,
		},
		[5] =
		{
			.pos = {-0x300, 0, 0x300*6}, // same as quadblock 14
			.distToFinish = 0x200*10,
			.nextIndex_forward = 6,
			.nextIndex_left = -1,
			.nextIndex_backward = 4,
			.nextIndex_right = -1,
		},
		[6] =
		{
			.pos = {0, 0, 0x300*6}, // same as quadblock 15
			.distToFinish = 0x200*9,
			.nextIndex_forward = 7,
			.nextIndex_left = -1,
			.nextIndex_backward = 5,
			.nextIndex_right = -1,
		},
		[7] =
		{
			.pos = {0x300, 0, 0x300*6}, // same as quadblock 16
			.distToFinish = 0x200*8,
			.nextIndex_forward = 8,
			.nextIndex_left = -1,
			.nextIndex_backward = 6,
			.nextIndex_right = -1,
		},
		[8] =
		{
			.pos = {0x600, 0, 0x300*6}, // same as quadblock 17
			.distToFinish = 0x200*7,
			.nextIndex_forward = 9,
			.nextIndex_left = -1,
			.nextIndex_backward = 7,
			.nextIndex_right = -1,
		},
		[9] =
		{
			.pos = {0x600, 0, 0x300*5}, // same as quadblock 13
			.distToFinish = 0x200*6,
			.nextIndex_forward = 10,
			.nextIndex_left = -1,
			.nextIndex_backward = 8,
			.nextIndex_right = -1,
		},
		[10] =
		{
			.pos = {0x600, 0, 0x300*4}, // same as quadblock 11
			.distToFinish = 0x200*5,
			.nextIndex_forward = 11,
			.nextIndex_left = -1,
			.nextIndex_backward = 9,
			.nextIndex_right = -1,
		},
		[11] =
		{
			.pos = {0x600, 0, 0x300*3}, // same as quadblock 9
			.distToFinish = 0x200*4,
			.nextIndex_forward = 12,
			.nextIndex_left = -1,
			.nextIndex_backward = 10,
			.nextIndex_right = -1,
		},
		[12] =
		{
			.pos = {0x600, 0, 0x300*2}, // same as quadblock 7
			.distToFinish = 0x200*3,
			.nextIndex_forward = 13,
			.nextIndex_left = -1,
			.nextIndex_backward = 11,
			.nextIndex_right = -1,
		},
		[13] =
		{
			.pos = {0x600, 0, 0x300*1}, // same as quadblock 5
			.distToFinish = 0x200*2,
			.nextIndex_forward = 14,
			.nextIndex_left = -1,
			.nextIndex_backward = 12,
			.nextIndex_right = -1,
		},
		[14] =
		{
			.pos = {0x300, 0, 0x300*1}, // same as quadblock 4
			.distToFinish = 0x200*1,
			.nextIndex_forward = 15,
			.nextIndex_left = -1,
			.nextIndex_backward = 13,
			.nextIndex_right = -1,
		},
		[15] =
		{
			.pos = {0, 0, 0x300*1}, // same as quadblock 3
			.distToFinish = 0x200*0,
			.nextIndex_forward = 0,
			.nextIndex_left = -1,
			.nextIndex_backward = 14,
			.nextIndex_right = -1,
		},
	},

	// ========== bsp ======================
	
	.bsp =
	{
		// root node
		BSP_BRANCH(0, SPLIT_Z, 0x1, 0x2),
		
		// bsp[1], start with quadblock[0], 2 quadblocks
		BSP_LEAF(1, 0, 2),
		
		// bsp[2], start with quadblock[2], 18 quadblocks
		BSP_LEAF(2, 2, 18),
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