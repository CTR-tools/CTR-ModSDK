#include <common.h>
#include "../../levelBuilder.h"

#define NUM_BLOCKS 20
// #define NUM_ANIMTEX_FRAMES 10

struct LevelFile
{
	void* ptrMap;
	struct Level level;
	struct mesh_info mInfo;
	struct IconGroup4 group4_ground;
	struct SpawnType1 spawnType1;
	// struct AnimTex animtex;
	struct CheckpointNode noderespawnsthing[16];
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
	
	int map[(31+NUM_BLOCKS*6)+1];
};

// for whatever reason it's necessary to offset every pointer by -4
struct LevelFile file =
{
	// i don't know what the map section is, other than holding pointers for most level variables
	.ptrMap = OFFSETOF(struct LevelFile, map[0])-4,
	
	// i don't know what the relation between all of these variables is, specifically
	.level =
	{
		.ptr_mesh_info = OFFSETOF(struct LevelFile, mInfo)-4,
		// .ptr_anim_tex = OFFSETOF(struct LevelFile, animtex)-4,
		.visMem = OFFSETOF(struct LevelFile, visMem)-4,
		
		// the game will add +0x400 to the Z rotation of spawn positions automatically
		// we should probably look into why this even happens...
		.DriverSpawn[0].pos = {0,0,0},
		.DriverSpawn[0].rot = {0,0-0x400,0},
		
		.DriverSpawn[1].pos = {0,0,0},
		.DriverSpawn[1].rot = {0,0-0x400,0},
		
		.DriverSpawn[2].pos = {0,0,0},
		.DriverSpawn[2].rot = {0,0-0x400,0},
		
		.DriverSpawn[3].pos = {0,0,0},
		.DriverSpawn[3].rot = {0,0-0x400,0},
		
		.ptrSpawnType1 = OFFSETOF(struct LevelFile, spawnType1)-4,
		
		.clearColor[0].rgb = {0x0, 0x0, 0x28},
		.clearColor[0].enable = 1,
		
		// amount of respawn points in the track
		// and pointer to respawn data itself
		.cnt_restart_points = 16,
		.ptr_restart_points = OFFSETOF(struct LevelFile, noderespawnsthing[0])-4,
	},
	
	// pointers and amounts of variables
	.mInfo =
	{
		.numQuadBlock = NUM_BLOCKS,
		.numVertex = NUM_BLOCKS*9, // not really used
		.unk1 = 0, // idk, fine to leave null
		.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[0])-4,
		.ptrVertexArray = OFFSETOF(struct LevelFile, levVertex[0])-4,
		.unk2 = 0, // idk, fine to leave null
		.bspRoot = OFFSETOF(struct LevelFile, bsp[0])-4,
		.numBspNodes = 3, // can be anything non-zero
	},

	/*
	.animtex =
	{
		.ptrNext = 0,
		.numFrames = NUM_ANIMTEX_FRAMES,
		.shrug = 0,
		.lottashortshuh = 0,
		.frameIndex = 0,
		.ptrarray[NUM_ANIMTEX_FRAMES] =
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0
		},
	}
	*/
	
	// quadblock texture type
	// see IconGroup4 in namespace_Decal.h
	.group4_ground =
	{
		// for these we just use the exact same texture name format as ctr_tools' texture ripper for where in VRAM the texture and its CLUT are located
		// our singular texture is named 512_0_32_20_16_16_0.png, so that's what we use
		.texLayout[0] = ImageName_Blend(512, 0, 32, 20, 16, 16, 0, TRANS_50), // very far
		.texLayout[1] = ImageName_Blend(512, 0, 32, 20, 16, 16, 0, TRANS_50), // far
		.texLayout[2] = ImageName_Blend(512, 0, 32, 20, 16, 16, 0, TRANS_50), // close
		.texLayout[3] = ImageName_Blend(512, 0, 32, 20, 16, 16, 0, TRANS_50), // very close
	},
	
	// this must exist, or else camera fly-in checks for "count" without nullptr check, and crashes dereferencing nullptr on real PSX
	.spawnType1 =
	{
		.count = 0,
	},

	// automatically-generated quadblock insertions courtesy of pngtotrack.py
	                                                                           NEW_BLOCK(00, group4_ground, 0x0000, 0x0000, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(01, group4_ground, 0x0300, 0x0000, NULL, 0x1800, 0xFF, 0x0, 0x0),                                                                           
	NEW_BLOCK(02, group4_ground, -0x300, 0x0300, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(03, group4_ground, 0x0000, 0x0300, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(04, group4_ground, 0x0300, 0x0300, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(05, group4_ground, 0x0600, 0x0300, NULL, 0x1800, 0xFF, 0x0, 0x0),
	NEW_BLOCK(06, group4_ground, -0x300, 0x0600, NULL, 0x1800, 0xFF, 0x0, 0x0),                                                                                                                                                      NEW_BLOCK(07, group4_ground, 0x0600, 0x0600, NULL, 0x1800, 0xFF, 0x0, 0x0),
	NEW_BLOCK(08, group4_ground, -0x300, 0x0900, NULL, 0x1800, 0xFF, 0x0, 0x0),                                                                                                                                                      NEW_BLOCK(09, group4_ground, 0x0600, 0x0900, NULL, 0x1800, 0xFF, 0x0, 0x0),
	NEW_BLOCK(10, group4_ground, -0x300, 0x0c00, NULL, 0x1800, 0xFF, 0x0, 0x0),                                                                                                                                                      NEW_BLOCK(11, group4_ground, 0x0600, 0x0c00, NULL, 0x1800, 0xFF, 0x0, 0x0),
	NEW_BLOCK(12, group4_ground, -0x300, 0x0f00, NULL, 0x1800, 0xFF, 0x0, 0x0),                                                                                                                                                      NEW_BLOCK(13, group4_ground, 0x0600, 0x0f00, NULL, 0x1800, 0xFF, 0x0, 0x0),
	NEW_BLOCK(14, group4_ground, -0x300, 0x1200, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(15, group4_ground, 0x0000, 0x1200, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(16, group4_ground, 0x0300, 0x1200, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(17, group4_ground, 0x0600, 0x1200, NULL, 0x1800, 0xFF, 0x0, 0x0),
	                                                                           NEW_BLOCK(18, group4_ground, 0x0000, 0x1500, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(19, group4_ground, 0x0300, 0x1500, NULL, 0x1800, 0xFF, 0x0, 0x0),                                                                           

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
			.pos = {-0x300, 0, 0x300}, // same as quadblock 02
			.distToFinish = 0x200*15,
			.nextIndex_forward = 1,
			.nextIndex_left = -1,
			.nextIndex_backward = 15,
			.nextIndex_right = -1,
		},
		[1] =
		{
			.pos = {-0x300, 0, 0x600}, // same as quadblock 06
			.distToFinish = 0x200*14,
			.nextIndex_forward = 2,
			.nextIndex_left = -1,
			.nextIndex_backward = 0,
			.nextIndex_right = -1,
		},
		[2] =
		{
			.pos = {-0x300, 0, 0x300*3}, // same as quadblock 08
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
			.pos = {0x600, 0, 0x300*3}, // same as quadblock 09
			.distToFinish = 0x200*4,
			.nextIndex_forward = 12,
			.nextIndex_left = -1,
			.nextIndex_backward = 10,
			.nextIndex_right = -1,
		},
		[12] =
		{
			.pos = {0x600, 0, 0x300*2}, // same as quadblock 07
			.distToFinish = 0x200*3,
			.nextIndex_forward = 13,
			.nextIndex_left = -1,
			.nextIndex_backward = 11,
			.nextIndex_right = -1,
		},
		[13] =
		{
			.pos = {0x600, 0, 0x300*1}, // same as quadblock 05
			.distToFinish = 0x200*2,
			.nextIndex_forward = 14,
			.nextIndex_left = -1,
			.nextIndex_backward = 12,
			.nextIndex_right = -1,
		},
		[14] =
		{
			.pos = {0x300, 0, 0x300*1}, // same as quadblock 04
			.distToFinish = 0x200*1,
			.nextIndex_forward = 15,
			.nextIndex_left = -1,
			.nextIndex_backward = 13,
			.nextIndex_right = -1,
		},
		[15] =
		{
			.pos = {0, 0, 0x300*1}, // same as quadblock 03
			.distToFinish = 0x200*0,
			.nextIndex_forward = 0,
			.nextIndex_left = -1,
			.nextIndex_backward = 14,
			.nextIndex_right = -1,
		},
	},

	.quadBlock[0].blockID =  20-0-1,
	.quadBlock[1].blockID =  20-1-1,
	.quadBlock[2].blockID =  20-2-1,
	.quadBlock[3].blockID =  20-3-1,
	.quadBlock[4].blockID =  20-4-1,
	.quadBlock[5].blockID =  20-5-1,
	.quadBlock[6].blockID =  20-6-1,
	.quadBlock[7].blockID =  20-7-1,
	.quadBlock[8].blockID =  20-8-1,
	.quadBlock[9].blockID =  20-9-1,
	.quadBlock[10].blockID = 20-10-1,
	.quadBlock[11].blockID = 20-11-1,
	.quadBlock[12].blockID = 20-12-1,
	.quadBlock[13].blockID = 20-13-1,
	.quadBlock[14].blockID = 20-14-1,
	.quadBlock[15].blockID = 20-15-1,
	.quadBlock[16].blockID = 20-16-1,
	.quadBlock[17].blockID = 20-17-1,
	.quadBlock[18].blockID = 20-18-1,
	.quadBlock[19].blockID = 20-19-1,

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
				.min = {0x2800, 0xFFE4, 0x2800},
				.max = {0x2800, 0x400, 0x2F00}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = 0,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[0])-4
				}
			}
		},
		
		// leaf with all of our quadblocks
		[2] =
		{
			.flag = 1,
			.id = 2,
			.box =
			{
				// random box that exists nowhere
				.min = {-0x1100, 0xFFE4, -0x1100},
				.max = {0x2800, 0x400, 0x2800}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = 20,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[0])-4
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
		.visLeafList[0] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP1[0])-4,
		.visFaceList[0] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP1[4])-4,
		.bspList[0] = OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP1[0])-4,
		
		// P2
		.visLeafList[1] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP2[0])-4,
		.visFaceList[1] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP2[4])-4,
		.bspList[1] = OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP2[0])-4,
		
		// P3
		.visLeafList[2] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP3[0])-4,
		.visFaceList[2] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP3[4])-4,
		.bspList[2] = OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP3[0])-4,
		
		// P4
		.visLeafList[3] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP4[0])-4,
		.visFaceList[3] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP4[4])-4,
		.bspList[3] = OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP4[0])-4,
	},
	
	// initialize for leaf nodes only
	.VisMem_bspList_RenderListP1[2*1+1] = OFFSETOF(struct LevelFile, bsp[1])-4,
	.VisMem_bspList_RenderListP2[2*1+1] = OFFSETOF(struct LevelFile, bsp[1])-4,
	.VisMem_bspList_RenderListP3[2*1+1] = OFFSETOF(struct LevelFile, bsp[1])-4,
	.VisMem_bspList_RenderListP4[2*1+1] = OFFSETOF(struct LevelFile, bsp[1])-4,
	.VisMem_bspList_RenderListP1[2*2+1] = OFFSETOF(struct LevelFile, bsp[2])-4,
	.VisMem_bspList_RenderListP2[2*2+1] = OFFSETOF(struct LevelFile, bsp[2])-4,
	.VisMem_bspList_RenderListP3[2*2+1] = OFFSETOF(struct LevelFile, bsp[2])-4,
	.VisMem_bspList_RenderListP4[2*2+1] = OFFSETOF(struct LevelFile, bsp[2])-4,
	
	.map =
	{
		(31+NUM_BLOCKS*6)<<2,
		
		OFFSETOF(struct LevelFile, level.ptr_mesh_info)-4,
		//OFFSETOF(struct LevelFile, level.ptr_anim_tex)-4,
		OFFSETOF(struct LevelFile, level.visMem)-4,
		OFFSETOF(struct LevelFile, level.ptrSpawnType1)-4,
		OFFSETOF(struct LevelFile, level.ptr_restart_points)-4,
		//OFFSETOF(struct LevelFile, animtex.ptrNext)-4,
		//OFFSETOF(struct LevelFile, animtex.numFrames)-4,
		//OFFSETOF(struct LevelFile, animtex.shrug)-4,
		//OFFSETOF(struct LevelFile, animtex.lottashortshuh)-4,
		//OFFSETOF(struct LevelFile, animtex.frameIndex)-4,
		//OFFSETOF(struct LevelFile, animtex.ptrarray)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrVertexArray)-4,
		OFFSETOF(struct LevelFile, mInfo.bspRoot)-4,
		OFFSETOF(struct LevelFile, bsp[1].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, bsp[2].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, pvs.visLeafSrc)-4,
		OFFSETOF(struct LevelFile, pvs.visFaceSrc)-4,
		OFFSETOF(struct LevelFile, visMem.visLeafList[0])-4,
		OFFSETOF(struct LevelFile, visMem.visLeafList[1])-4,
		OFFSETOF(struct LevelFile, visMem.visLeafList[2])-4,
		OFFSETOF(struct LevelFile, visMem.visLeafList[3])-4,
		OFFSETOF(struct LevelFile, visMem.visFaceList[0])-4,
		OFFSETOF(struct LevelFile, visMem.visFaceList[1])-4,
		OFFSETOF(struct LevelFile, visMem.visFaceList[2])-4,
		OFFSETOF(struct LevelFile, visMem.visFaceList[3])-4,
		OFFSETOF(struct LevelFile, visMem.bspList[0])-4,
		OFFSETOF(struct LevelFile, visMem.bspList[1])-4,
		OFFSETOF(struct LevelFile, visMem.bspList[2])-4,
		OFFSETOF(struct LevelFile, visMem.bspList[3])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP1[2*1+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP2[2*1+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP3[2*1+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP4[2*1+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP1[2*2+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP2[2*2+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP3[2*2+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP4[2*2+1])-4,
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
		PTR_MAP_QUADBLOCK(19)
	},
};