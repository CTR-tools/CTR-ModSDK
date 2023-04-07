#include <common.h>

#define OFFSETOF(TYPE, ELEMENT) ((unsigned int)&(((TYPE *)0)->ELEMENT))

struct LevelFile
{
	void* ptrMap;
	struct Level level;
	struct mesh_info mInfo;
	struct QuadBlock quadBlock[7];
	struct LevVertex levVertex[9*7];
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
		.numQuadBlock = 7,
		.numVertex = 7*9, // not really used
		.unk1 = 0, // idk, fine to leave null
		.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[0])-4,
		.ptrVertexArray = OFFSETOF(struct LevelFile, levVertex[0])-4, // no -4 for some reason?
		.unk2 = 0, // idk, fine to leave null
		.ptrVisDataArray = OFFSETOF(struct LevelFile, visData[0])-4,
		.numVisData = 3, // can be anything non-zero
	},
	
	.quadBlock[0] =
	{
		.index = {0,1,2,3,4,5,6,7,8},
		.quadFlags = 0x1800,
		.draw_order_low = 0,
		.draw_order_high = 0,
		.ptr_texture_mid =
		{
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4
		},
		
		.bbox =
		{
			.min = {-0x180, 0, -0x180},
			.max = {0x180, 0, 0x180}
		},
		
		.terrain_type = 0,
		.weather_intensity = 0,
		.weather_vanishRate = 0,
		.speedImpact = 0,

		// visData->numBlocks-currIndex-1
		.blockID = 7-0-1,
		
		.respawnIndex = -1,
		.triNormalVecBitShift = 0x12,
		
		.ptr_texture_low = OFFSETOF(struct LevelFile, group4)-4,
		.visFromQuadBlock = OFFSETOF(struct LevelFile, visFromQuadBlock)-4,
		.triNormalVecDividend =
		{
			// hi 8
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			
			// lo 2
			0x1C71,
			0x1C71,
		}
	},
	
	.quadBlock[1] =
	{
		.index = {0+9*1,1+9*1,2+9*1,3+9*1,4+9*1,5+9*1,6+9*1,7+9*1,8+9*1},
		.quadFlags = 0x1800,
		.draw_order_low = 0,
		.draw_order_high = 0,
		.ptr_texture_mid =
		{
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4
		},
		
		.bbox =
		{
			.min = {-0x180+0x300*1, 0, -0x180},
			.max = {0x180+0x300*1, 0, 0x180}
		},
		
		.terrain_type = 0,
		.weather_intensity = 0,
		.weather_vanishRate = 0,
		.speedImpact = 0,
		
		// visData->numBlocks-currIndex-1
		.blockID = 7-1-1,
		
		.respawnIndex = -1,
		.triNormalVecBitShift = 0x12,
		
		.ptr_texture_low = OFFSETOF(struct LevelFile, group4)-4,
		.visFromQuadBlock = OFFSETOF(struct LevelFile, visFromQuadBlock)-4,
		.triNormalVecDividend =
		{
			// hi 8
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			
			// lo 2
			0x1C71,
			0x1C71,
		}
	},
	
	.quadBlock[2] =
	{
		.index = {0+9*2,1+9*2,2+9*2,3+9*2,4+9*2,5+9*2,6+9*2,7+9*2,8+9*2},
		.quadFlags = 0x1800,
		.draw_order_low = 0,
		.draw_order_high = 0,
		.ptr_texture_mid =
		{
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4
		},
		
		.bbox =
		{
			.min = {-0x180+0x300*2, 0, -0x180},
			.max = {0x180+0x300*2, 0, 0x180}
		},
		
		.terrain_type = 0,
		.weather_intensity = 0,
		.weather_vanishRate = 0,
		.speedImpact = 0,
		
		// visData->numBlocks-currIndex-1
		.blockID = 7-2-1,
		
		.respawnIndex = -1,
		.triNormalVecBitShift = 0x12,
		
		.ptr_texture_low = OFFSETOF(struct LevelFile, group4)-4,
		.visFromQuadBlock = OFFSETOF(struct LevelFile, visFromQuadBlock)-4,
		.triNormalVecDividend =
		{
			// hi 8
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			
			// lo 2
			0x1C71,
			0x1C71,
		}
	},
	
	.quadBlock[3] =
	{
		.index = {0+9*3,1+9*3,2+9*3,3+9*3,4+9*3,5+9*3,6+9*3,7+9*3,8+9*3},
		.quadFlags = 0x1800,
		.draw_order_low = 0,
		.draw_order_high = 0,
		.ptr_texture_mid =
		{
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4
		},
		
		.bbox =
		{
			.min = {-0x180+0x300*3, 0, -0x180},
			.max = {0x180+0x300*3, 0, 0x180}
		},
		
		.terrain_type = 0,
		.weather_intensity = 0,
		.weather_vanishRate = 0,
		.speedImpact = 0,
		
		// visData->numBlocks-currIndex-1
		.blockID = 7-3-1,
		
		.respawnIndex = -1,
		.triNormalVecBitShift = 0x12,
		
		.ptr_texture_low = OFFSETOF(struct LevelFile, group4)-4,
		.visFromQuadBlock = OFFSETOF(struct LevelFile, visFromQuadBlock)-4,
		.triNormalVecDividend =
		{
			// hi 8
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			
			// lo 2
			0x1C71,
			0x1C71,
		}
	},
	
	.quadBlock[4] =
	{
		.index = {0+9*4,1+9*4,2+9*4,3+9*4,4+9*4,5+9*4,6+9*4,7+9*4,8+9*4},
		.quadFlags = 0x1800,
		.draw_order_low = 0,
		.draw_order_high = 0,
		.ptr_texture_mid =
		{
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4
		},
		
		.bbox =
		{
			.min = {-0x180+0x300*3, 0, -0x180+0x300*1},
			.max = {0x180+0x300*3, 0, 0x180+0x300*1}
		},
		
		.terrain_type = 0,
		.weather_intensity = 0,
		.weather_vanishRate = 0,
		.speedImpact = 0,
		
		// visData->numBlocks-currIndex-1
		.blockID = 7-4-1,
		
		.respawnIndex = -1,
		.triNormalVecBitShift = 0x12,
		
		.ptr_texture_low = OFFSETOF(struct LevelFile, group4)-4,
		.visFromQuadBlock = OFFSETOF(struct LevelFile, visFromQuadBlock)-4,
		.triNormalVecDividend =
		{
			// hi 8
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			
			// lo 2
			0x1C71,
			0x1C71,
		}
	},
	
	.quadBlock[5] =
	{
		.index = {0+9*5,1+9*5,2+9*5,3+9*5,4+9*5,5+9*5,6+9*5,7+9*5,8+9*5},
		.quadFlags = 0x1800,
		.draw_order_low = 0,
		.draw_order_high = 0,
		.ptr_texture_mid =
		{
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4
		},
		
		.bbox =
		{
			.min = {-0x180+0x300*3, 0, -0x180+0x300*2},
			.max = {0x180+0x300*3, 0, 0x180+0x300*2}
		},
		
		.terrain_type = 0,
		.weather_intensity = 0,
		.weather_vanishRate = 0,
		.speedImpact = 0,
		
		// visData->numBlocks-currIndex-1
		.blockID = 7-5-1,
		
		.respawnIndex = -1,
		.triNormalVecBitShift = 0x12,
		
		.ptr_texture_low = OFFSETOF(struct LevelFile, group4)-4,
		.visFromQuadBlock = OFFSETOF(struct LevelFile, visFromQuadBlock)-4,
		.triNormalVecDividend =
		{
			// hi 8
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			
			// lo 2
			0x1C71,
			0x1C71,
		}
	},
	
	.quadBlock[6] =
	{
		.index = {0+9*6,1+9*6,2+9*6,3+9*6,4+9*6,5+9*6,6+9*6,7+9*6,8+9*6},
		.quadFlags = 0x1800,
		.draw_order_low = 0,
		.draw_order_high = 0,
		.ptr_texture_mid =
		{
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4,
			OFFSETOF(struct LevelFile, group4)-4
		},
		
		.bbox =
		{
			.min = {-0x180+0x300*3, 0, -0x180+0x300*3},
			.max = {0x180+0x300*3, 0, 0x180+0x300*3}
		},
		
		.terrain_type = 0,
		.weather_intensity = 0,
		.weather_vanishRate = 0,
		.speedImpact = 0,
		
		// visData->numBlocks-currIndex-1
		.blockID = 7-6-1,
		
		.respawnIndex = -1,
		.triNormalVecBitShift = 0x12,
		
		.ptr_texture_low = OFFSETOF(struct LevelFile, group4)-4,
		.visFromQuadBlock = OFFSETOF(struct LevelFile, visFromQuadBlock)-4,
		.triNormalVecDividend =
		{
			// hi 8
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			0x1C71,
			
			// lo 2
			0x1C71,
			0x1C71,
		}
	},
	
	.levVertex =
	{
		[0] =
		{
			.pos = {-0x180,0,-0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[1] =
		{
			.pos = {0x180,0,-0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[2] =
		{
			.pos = {-0x180,0,0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[3] =
		{
			.pos = {0x180,0,0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[4] =
		{
			.pos = {0,0,-0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[5] =
		{
			.pos = {-0x180,0,0},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[6] =
		{
			.pos = {0,0,0},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[7] =
		{
			.pos = {0x180,0,0},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[8] =
		{
			.pos = {0,0,0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
	
		[0+9*1] =
		{
			.pos = {-0x180+0x300*1,0,-0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[1+9*1] =
		{
			.pos = {0x180+0x300*1,0,-0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[2+9*1] =
		{
			.pos = {-0x180+0x300*1,0,0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[3+9*1] =
		{
			.pos = {0x180+0x300*1,0,0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[4+9*1] =
		{
			.pos = {0+0x300*1,0,-0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[5+9*1] =
		{
			.pos = {-0x180+0x300*1,0,0},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[6+9*1] =
		{
			.pos = {0+0x300*1,0,0},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[7+9*1] =
		{
			.pos = {0x180+0x300*1,0,0},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[8+9*1] =
		{
			.pos = {0+0x300*1,0,0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[0+9*2] =
		{
			.pos = {-0x180+0x300*2,0,-0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[1+9*2] =
		{
			.pos = {0x180+0x300*2,0,-0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[2+9*2] =
		{
			.pos = {-0x180+0x300*2,0,0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[3+9*2] =
		{
			.pos = {0x180+0x300*2,0,0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[4+9*2] =
		{
			.pos = {0+0x300*2,0,-0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[5+9*2] =
		{
			.pos = {-0x180+0x300*2,0,0},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[6+9*2] =
		{
			.pos = {0+0x300*2,0,0},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[7+9*2] =
		{
			.pos = {0x180+0x300*2,0,0},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[8+9*2] =
		{
			.pos = {0+0x300*2,0,0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[0+9*3] =
		{
			.pos = {-0x180+0x300*3,0,-0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[1+9*3] =
		{
			.pos = {0x180+0x300*3,0,-0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[2+9*3] =
		{
			.pos = {-0x180+0x300*3,0,0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[3+9*3] =
		{
			.pos = {0x180+0x300*3,0,0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[4+9*3] =
		{
			.pos = {0+0x300*3,0,-0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[5+9*3] =
		{
			.pos = {-0x180+0x300*3,0,0},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[6+9*3] =
		{
			.pos = {0+0x300*3,0,0},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[7+9*3] =
		{
			.pos = {0x180+0x300*3,0,0},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[8+9*3] =
		{
			.pos = {0+0x300*3,0,0x180},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[0+9*4] =
		{
			.pos = {-0x180+0x300*3,0,-0x180+0x300*1},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[1+9*4] =
		{
			.pos = {0x180+0x300*3,0,-0x180+0x300*1},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[2+9*4] =
		{
			.pos = {-0x180+0x300*3,0,0x180+0x300*1},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[3+9*4] =
		{
			.pos = {0x180+0x300*3,0,0x180+0x300*1},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[4+9*4] =
		{
			.pos = {0+0x300*3,0,-0x180+0x300*1},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[5+9*4] =
		{
			.pos = {-0x180+0x300*3,0,0+0x300*1},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[6+9*4] =
		{
			.pos = {0+0x300*3,0,0+0x300*1},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[7+9*4] =
		{
			.pos = {0x180+0x300*3,0,0+0x300*1},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[8+9*4] =
		{
			.pos = {0+0x300*3,0,0x180+0x300*1},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[0+9*5] =
		{
			.pos = {-0x180+0x300*3,0,-0x180+0x300*2},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[1+9*5] =
		{
			.pos = {0x180+0x300*3,0,-0x180+0x300*2},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[2+9*5] =
		{
			.pos = {-0x180+0x300*3,0,0x180+0x300*2},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[3+9*5] =
		{
			.pos = {0x180+0x300*3,0,0x180+0x300*2},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[4+9*5] =
		{
			.pos = {0+0x300*3,0,-0x180+0x300*2},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[5+9*5] =
		{
			.pos = {-0x180+0x300*3,0,0+0x300*2},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[6+9*5] =
		{
			.pos = {0+0x300*3,0,0+0x300*2},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[7+9*5] =
		{
			.pos = {0x180+0x300*3,0,0+0x300*2},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[8+9*5] =
		{
			.pos = {0+0x300*3,0,0x180+0x300*2},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[0+9*6] =
		{
			.pos = {-0x180+0x300*3,0,-0x180+0x300*3},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[1+9*6] =
		{
			.pos = {0x180+0x300*3,0,-0x180+0x300*3},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[2+9*6] =
		{
			.pos = {-0x180+0x300*3,0,0x180+0x300*3},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[3+9*6] =
		{
			.pos = {0x180+0x300*3,0,0x180+0x300*3},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[4+9*6] =
		{
			.pos = {0+0x300*3,0,-0x180+0x300*3},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[5+9*6] =
		{
			.pos = {-0x180+0x300*3,0,0+0x300*3},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[6+9*6] =
		{
			.pos = {0+0x300*3,0,0+0x300*3},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[7+9*6] =
		{
			.pos = {0x180+0x300*3,0,0+0x300*3},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
		
		[8+9*6] =
		{
			.pos = {0+0x300*3,0,0x180+0x300*3},
			.flags = 0,
			.color_hi = {0xCE, 0x8F, 0x77, 0x00},
			.color_lo = {0xCE, 0x8F, 0x77, 0x00},
		},
	},
	
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
					.numQuads = 7,
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
			.u0 = 0xFF, .v0 = 0x0,
			.u1 = 0xFF, .v1 = 0x7F,
			.u2 = 0x0, 	.v2 = 0x0,
			.u3 = 0x0, 	.v3 = 0x7F,
		},

		// duplicate for low LOD
		.texLayout[1] = 
		{
			.clut = (512 >> 10) | (256 >> 6),
			.tpage = 0x4180 | (8) | (1<<4),
			.u0 = 0xFF, .v0 = 0x0,
			.u1 = 0xFF, .v1 = 0x7F,
			.u2 = 0x0, 	.v2 = 0x0,
			.u3 = 0x0, 	.v3 = 0x7F,
		},
		
		// duplicate for low LOD
		.texLayout[2] = 
		{
			.clut = (512 >> 10) | (256 >> 6),
			.tpage = 0x4180 | (8) | (1<<4),
			.u0 = 0xFF, .v0 = 0x0,
			.u1 = 0xFF, .v1 = 0x7F,
			.u2 = 0x0, 	.v2 = 0x0,
			.u3 = 0x0, 	.v3 = 0x7F,	
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
			.u0 = 0xFF, .v0 = 0x0,
			.u1 = 0xFF, .v1 = 0x7F,
			.u2 = 0x0, 	.v2 = 0x0,
			.u3 = 0x0, 	.v3 = 0x7F,			
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
		// 24 pointers
		(12+7*6)<<2,
		
		OFFSETOF(struct LevelFile, level.ptr_mesh_info)-4,
		OFFSETOF(struct LevelFile, level.visMem)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrVertexArray)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrVisDataArray)-4,
		OFFSETOF(struct LevelFile, quadBlock[0].ptr_texture_mid[0])-4,
		OFFSETOF(struct LevelFile, quadBlock[0].ptr_texture_mid[1])-4,
		OFFSETOF(struct LevelFile, quadBlock[0].ptr_texture_mid[2])-4,
		OFFSETOF(struct LevelFile, quadBlock[0].ptr_texture_mid[3])-4,
		OFFSETOF(struct LevelFile, quadBlock[0].ptr_texture_low)-4,
		OFFSETOF(struct LevelFile, quadBlock[0].visFromQuadBlock)-4,
		OFFSETOF(struct LevelFile, quadBlock[1].ptr_texture_mid[0])-4,
		OFFSETOF(struct LevelFile, quadBlock[1].ptr_texture_mid[1])-4,
		OFFSETOF(struct LevelFile, quadBlock[1].ptr_texture_mid[2])-4,
		OFFSETOF(struct LevelFile, quadBlock[1].ptr_texture_mid[3])-4,
		OFFSETOF(struct LevelFile, quadBlock[1].ptr_texture_low)-4,
		OFFSETOF(struct LevelFile, quadBlock[1].visFromQuadBlock)-4,
		OFFSETOF(struct LevelFile, quadBlock[2].ptr_texture_mid[0])-4,
		OFFSETOF(struct LevelFile, quadBlock[2].ptr_texture_mid[1])-4,
		OFFSETOF(struct LevelFile, quadBlock[2].ptr_texture_mid[2])-4,
		OFFSETOF(struct LevelFile, quadBlock[2].ptr_texture_mid[3])-4,
		OFFSETOF(struct LevelFile, quadBlock[2].ptr_texture_low)-4,
		OFFSETOF(struct LevelFile, quadBlock[2].visFromQuadBlock)-4,
		OFFSETOF(struct LevelFile, quadBlock[3].ptr_texture_mid[0])-4,
		OFFSETOF(struct LevelFile, quadBlock[3].ptr_texture_mid[1])-4,
		OFFSETOF(struct LevelFile, quadBlock[3].ptr_texture_mid[2])-4,
		OFFSETOF(struct LevelFile, quadBlock[3].ptr_texture_mid[3])-4,
		OFFSETOF(struct LevelFile, quadBlock[3].ptr_texture_low)-4,
		OFFSETOF(struct LevelFile, quadBlock[3].visFromQuadBlock)-4,
		OFFSETOF(struct LevelFile, quadBlock[4].ptr_texture_mid[0])-4,
		OFFSETOF(struct LevelFile, quadBlock[4].ptr_texture_mid[1])-4,
		OFFSETOF(struct LevelFile, quadBlock[4].ptr_texture_mid[2])-4,
		OFFSETOF(struct LevelFile, quadBlock[4].ptr_texture_mid[3])-4,
		OFFSETOF(struct LevelFile, quadBlock[4].ptr_texture_low)-4,
		OFFSETOF(struct LevelFile, quadBlock[4].visFromQuadBlock)-4,
		OFFSETOF(struct LevelFile, quadBlock[5].ptr_texture_mid[0])-4,
		OFFSETOF(struct LevelFile, quadBlock[5].ptr_texture_mid[1])-4,
		OFFSETOF(struct LevelFile, quadBlock[5].ptr_texture_mid[2])-4,
		OFFSETOF(struct LevelFile, quadBlock[5].ptr_texture_mid[3])-4,
		OFFSETOF(struct LevelFile, quadBlock[5].ptr_texture_low)-4,
		OFFSETOF(struct LevelFile, quadBlock[5].visFromQuadBlock)-4,
		OFFSETOF(struct LevelFile, quadBlock[6].ptr_texture_mid[0])-4,
		OFFSETOF(struct LevelFile, quadBlock[6].ptr_texture_mid[1])-4,
		OFFSETOF(struct LevelFile, quadBlock[6].ptr_texture_mid[2])-4,
		OFFSETOF(struct LevelFile, quadBlock[6].ptr_texture_mid[3])-4,
		OFFSETOF(struct LevelFile, quadBlock[6].ptr_texture_low)-4,
		OFFSETOF(struct LevelFile, quadBlock[6].visFromQuadBlock)-4,
		OFFSETOF(struct LevelFile, visData[2].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, visFromQuadBlock.visLeafSrc)-4,
		OFFSETOF(struct LevelFile, visFromQuadBlock.visFaceSrc)-4,
		OFFSETOF(struct LevelFile, visMem.visLeafList[0])-4,
		OFFSETOF(struct LevelFile, visMem.visFaceList[0])-4,
		OFFSETOF(struct LevelFile, visMem.bspList[0])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderList[2*2+1])-4,
	},
	
};
