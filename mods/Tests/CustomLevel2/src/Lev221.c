#include <common.h>

#define OFFSETOF(TYPE, ELEMENT) ((unsigned int)&(((TYPE *)0)->ELEMENT))

#define NEW_VERTEX(posX, posY, posZ, flag, colR, colG, colB) \
{ \
	.pos = {posX, posY, posZ}, \
	.flags = flag, \
	.color_hi = {colR, colG, colB, 0}, \
	.color_lo = {colR, colG, colB, 0}, \
}

#define NEW_BLOCK(qIndex, posX, posZ, sizeX, sizeZ, flagV, flagQ, colR, colG, colB) \
	.levVertex[9*qIndex+0] = NEW_VERTEX(posX-sizeX/2, 0, posZ-sizeZ/2, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+1] = NEW_VERTEX(posX+sizeX/2, 0, posZ-sizeZ/2, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+2] = NEW_VERTEX(posX-sizeX/2, 0, posZ+sizeZ/2, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+3] = NEW_VERTEX(posX+sizeX/2, 0, posZ+sizeZ/2, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+4] = NEW_VERTEX(posX, 0, posZ-sizeZ/2, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+5] = NEW_VERTEX(posX-sizeX/2, 0, posZ, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+6] = NEW_VERTEX(posX, 0, posZ, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+7] = NEW_VERTEX(posX+sizeX/2, 0, posZ, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+8] = NEW_VERTEX(posX, 0, posZ+sizeZ/2, flagV, colR, colG, colB), \
	.quadBlock[qIndex] = \
	{ \
		.index = {9*qIndex+0,9*qIndex+1,9*qIndex+2,9*qIndex+3,9*qIndex+4,9*qIndex+5,9*qIndex+6,9*qIndex+7,9*qIndex+8}, \
		.quadFlags = flagQ, \
		.draw_order_low = 0, \
		.draw_order_high = 0, \
		.ptr_texture_mid = \
		{ \
			OFFSETOF(struct LevelFile, group4)-4, \
			OFFSETOF(struct LevelFile, group4)-4, \
			OFFSETOF(struct LevelFile, group4)-4, \
			OFFSETOF(struct LevelFile, group4)-4 \
		}, \
		\
		.bbox = \
		{ \
			.min = {posX-sizeX/2, 0, posZ-sizeZ/2}, \
			.max = {posX+sizeX/2, 0, posZ+sizeZ/2} \
		}, \
		.terrain_type = 0, \
		.weather_intensity = 0, \
		.weather_vanishRate = 0, \
		.speedImpact = 0, \
		\
		.blockID = NUM_BLOCKS-qIndex-1, \
		.respawnIndex = -1, \
		.triNormalVecBitShift = 0x12, \
		\
		.ptr_texture_low = OFFSETOF(struct LevelFile, group4)-4, \
		.visFromQuadBlock = OFFSETOF(struct LevelFile, visFromQuadBlock)-4, \
		\
		.triNormalVecDividend = \
		{ \
			/* hi 2 */ \
			0x1C71, \
			0x1C71, \
			0x1C71, \
			0x1C71, \
			0x1C71, \
			0x1C71, \
			0x1C71, \
			0x1C71, \
			\
			/* lo 2 */ \
			0x1C71, \
			0x1C71, \
		} \
	}

#define PTR_MAP_QUADBLOCK(x) \
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_mid[0])-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_mid[1])-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_mid[2])-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_mid[3])-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_low)-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].visFromQuadBlock)-4

#define NUM_BLOCKS 6

struct LevelFile
{
	void* ptrMap;
	struct Level level;
	struct mesh_info mInfo;
	struct QuadBlock quadBlock[NUM_BLOCKS];
	struct LevVertex levVertex[NUM_BLOCKS*9];
	struct VisData visData[3];
	struct VisFromQuadBlock visFromQuadBlock;
	int visBitIndex[4];
	struct IconGroup4 group4;
	struct VisMem visMem;
	int VisMem_bitIndex_DstMemcpy[8]; // leave empty
	int VisMem_bspList_RenderList[3*2];
	int map[100];
};

struct LevelFile file =
{
	.ptrMap = OFFSETOF(struct LevelFile, map[0])-4,
	
	.level =
	{
		.ptr_mesh_info = OFFSETOF(struct LevelFile, mInfo)-4,
		.visMem = OFFSETOF(struct LevelFile, visMem)-4
	},
	
	.mInfo =
	{
		.numQuadBlock = NUM_BLOCKS,
		.numVertex = NUM_BLOCKS*9, // not really used
		.unk1 = 0, // idk, fine to leave null
		.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[0])-4,
		.ptrVertexArray = OFFSETOF(struct LevelFile, levVertex[0])-4, // no -4 for some reason?
		.unk2 = 0, // idk, fine to leave null
		.ptrVisDataArray = OFFSETOF(struct LevelFile, visData[0])-4,
		.numVisData = 3, // can be anything non-zero
	},
	
	NEW_BLOCK
	(
		// index
		0, 
		
		// posX, posY, sizeX, sizeY
		0x0, 0x0, 0x300, 0x300,
		
		// vertex flags, quadblock flags
		NULL, 0x1800,
		
		// colorRGB
		0xFF, 0x00, 0x0
	),
	
	NEW_BLOCK(1, 0, 0x300, 0x300, 0x300, NULL, 0x1800, 0xFF, 0x20, 0x0),
	NEW_BLOCK(2, 0, 0x600, 0x300, 0x300, NULL, 0x1800, 0xFF, 0x40, 0x0),
	NEW_BLOCK(3, 0, 0x900, 0x300, 0x300, NULL, 0x1800, 0xFF, 0x60, 0x0),
	NEW_BLOCK(4, 0, 0xC00, 0x300, 0x300, NULL, 0x1800, 0xFF, 0x80, 0x0),
	NEW_BLOCK(5, 0, 0xF00, 0x300, 0x300, NULL, 0x1800, 0xFF, 0xA0, 0x0), 
	
	.visData =
	{
		// root node
		[0] =
		{
			.flag = 0,
			.id = 0,
			.box =
			{
				.min = {0xE0C6, 0xFFE4, 0xDFDB},
				.max = {0x20C0, 0x066E, 0x208F}
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
				.min = {0x1680, 0xA2, 0x4E1},
				.max = {0x1FB1, 0x515, 0xA80}
			},
			
			.data =
			{
				// nothing in it
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
				.min = {0xFE80, 0xFFE4, 0xFE80},
				.max = {0x1D80, 0x7C, 0x1D80}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.ptrVisDataArray_InstHitboxes = 0,
					.numQuads = NUM_BLOCKS,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[0])-4
				}
			}
		},
	},
	
	.visFromQuadBlock =
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
	
	// A quadblock can draw 32 textures,
	.group4 =
	{
		// duplicate for low LOD
		.texLayout[0] = 
		{
			.clut = (512 >> 10) | (256 >> 6),
			.tpage = 0x4180 | (8) | (1<<4),
			.u0 = 2, .v0 = 0,
			.u1 = 2, .v1 = 2,
			.u2 = 0, .v2 = 0,
			.u3 = 0, .v3 = 2,	
		},

		// duplicate for low LOD
		.texLayout[1] = 
		{
			.clut = (512 >> 10) | (256 >> 6),
			.tpage = 0x4180 | (8) | (1<<4),
			.u0 = 2, .v0 = 0,
			.u1 = 2, .v1 = 2,
			.u2 = 0, .v2 = 0,
			.u3 = 0, .v3 = 2,	
		},
		
		// duplicate for low LOD
		.texLayout[2] = 
		{
			.clut = (512 >> 10) | (256 >> 6),
			.tpage = 0x4180 | (8) | (1<<4),
			.u0 = 2, .v0 = 0,
			.u1 = 2, .v1 = 2,
			.u2 = 0, .v2 = 0,
			.u3 = 0, .v3 = 2,	
		},
		
		// drawn directly under player
		.texLayout[3] = 
		{
			// X(b6) Y(b10)
			// row of 16 pixels, or row of 256 pixels,
			// this is how it chooses what colors to use
			.clut = (512 >> 10) | (256 >> 6),
			
			// each page is 256x256 large
			
			// pageX(b4), 
			// pageY(b1), 
			// blending(b2), 
			// bitDepth(b2), 
			// restBits(b7)
			.tpage = 0x4180 | (8) | (1<<4), // page = (2,1) (512,256)
			
			// coordinates within page
			.u0 = 2, .v0 = 0,
			.u1 = 2, .v1 = 2,
			.u2 = 0, .v2 = 0,
			.u3 = 0, .v3 = 2,			
		},
	},
	
	.visMem =
	{
		.visLeafList[0] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpy[0])-4,
		.visFaceList[0] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpy[4])-4,
		.bspList[0] = OFFSETOF(struct LevelFile, VisMem_bspList_RenderList[0])-4
	},
	
	// initialize for leaf nodes only
	.VisMem_bspList_RenderList[2*2+1] = OFFSETOF(struct LevelFile, visData[2])-4,
	
	.map =
	{
		// 18 pointers
		(12+NUM_BLOCKS*6)<<2,
		
		OFFSETOF(struct LevelFile, level.ptr_mesh_info)-4,
		OFFSETOF(struct LevelFile, level.visMem)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrVertexArray)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrVisDataArray)-4,
		PTR_MAP_QUADBLOCK(0),
		PTR_MAP_QUADBLOCK(1),
		PTR_MAP_QUADBLOCK(2),
		PTR_MAP_QUADBLOCK(3),
		PTR_MAP_QUADBLOCK(4),
		PTR_MAP_QUADBLOCK(5),
		OFFSETOF(struct LevelFile, visData[2].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, visFromQuadBlock.visLeafSrc)-4,
		OFFSETOF(struct LevelFile, visFromQuadBlock.visFaceSrc)-4,
		OFFSETOF(struct LevelFile, visMem.visLeafList[0])-4,
		OFFSETOF(struct LevelFile, visMem.visFaceList[0])-4,
		OFFSETOF(struct LevelFile, visMem.bspList[0])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderList[2*2+1])-4,
	},
};
