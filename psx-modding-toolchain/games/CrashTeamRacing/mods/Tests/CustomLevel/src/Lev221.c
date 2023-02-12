#include <common.h>

#define OFFSETOF(TYPE, ELEMENT) ((unsigned int)&(((TYPE *)0)->ELEMENT))

struct LevelFile
{
	void* ptrMap;
	struct Level level;
	struct mesh_info mInfo;
	struct QuadBlock quadBlock;
	struct LevVertex levVertex[9];
	struct VisData visData[3];
	struct VisFromQuadBlock visFromQuadBlock;
	int visBitIndex[4];
	unsigned char emptyTexData[0x30];
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
		.numQuadBlock = 1,
		.numVertex = 0, // not really used
		.unk1 = 0, // idk, fine to leave null
		.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock)-4,
		.ptrVertexArray = OFFSETOF(struct LevelFile, levVertex[0])-4, // no -4 for some reason?
		.unk2 = 0, // idk, fine to leave null
		.ptrVisDataArray = OFFSETOF(struct LevelFile, visData[0])-4,
		.numVisData = 1, // can be anything non-zero
	},
	
	.quadBlock =
	{
		.index = {0,1,2,3,4,5,6,7,8},
		.quadFlags = 0x1800,
		.draw_order_low = 0,
		.draw_order_high = 0,
		.ptr_texture_mid =
		{
			OFFSETOF(struct LevelFile, emptyTexData[0])-4,
			OFFSETOF(struct LevelFile, emptyTexData[0])-4,
			OFFSETOF(struct LevelFile, emptyTexData[0])-4,
			OFFSETOF(struct LevelFile, emptyTexData[0])-4
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
		
		.blockID = 0,
		.respawnIndex = -1,
		.triNormalVecBitShift = 0x12,
		
		.ptr_texture_low = OFFSETOF(struct LevelFile, emptyTexData[0])-4,
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
				.max = {0xD80, 0x7C, 0x480}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.ptrVisDataArray_InstHitboxes = 0,
					.numQuads = 1,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock)-4
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
	
	.emptyTexData =
	{
		// first 0x24 empty
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,
		
		// see DCxDemo's lev.ksy
		
		// short uv1
		0xF0, 0x80, 
		
		// palletX(b6), 
		// pelletY(b10)
		0xED, 0x61, 
		
		// short uv2
		0xFF, 0x80, 
		
		// pageX(b4), 
		// pageY(b1), 
		// blending(b2), 
		// bitDepth(b2), 
		// restBits(b7)
		0x6C, 0x00,
		
		// short uv3
		0xF0, 0x8F,
		
		// short uv4
		0xFF, 0x8F
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
		18<<2,
		
		OFFSETOF(struct LevelFile, level.ptr_mesh_info)-4,
		OFFSETOF(struct LevelFile, level.visMem)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrVertexArray)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrVisDataArray)-4,
		OFFSETOF(struct LevelFile, quadBlock.ptr_texture_mid[0])-4,
		OFFSETOF(struct LevelFile, quadBlock.ptr_texture_mid[1])-4,
		OFFSETOF(struct LevelFile, quadBlock.ptr_texture_mid[2])-4,
		OFFSETOF(struct LevelFile, quadBlock.ptr_texture_mid[3])-4,
		OFFSETOF(struct LevelFile, quadBlock.ptr_texture_low)-4,
		OFFSETOF(struct LevelFile, quadBlock.visFromQuadBlock)-4,
		OFFSETOF(struct LevelFile, visData[2].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, visFromQuadBlock.visLeafSrc)-4,
		OFFSETOF(struct LevelFile, visFromQuadBlock.visFaceSrc)-4,
		OFFSETOF(struct LevelFile, visMem.visLeafList[0])-4,
		OFFSETOF(struct LevelFile, visMem.visFaceList[0])-4,
		OFFSETOF(struct LevelFile, visMem.bspList[0])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderList[2*2+1])-4,
	},
	
};
