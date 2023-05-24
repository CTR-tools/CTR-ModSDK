enum LevelID
{
	DINGO_CANYON=0, // 0.
	DRAGON_MINES=1, // 1.
	BLIZZARD_BLUFF,
	CRASH_COVE,
	TIGER_TEMPLE,
	PAPU_PYRAMID,
	ROO_TUBES,
	HOT_AIR_SKYWAY,
	SEWER_SPEEDWAY,
	MYSTERY_CAVES,
	CORTEX_CASTLE,
	N_GIN_LABS,
	POLAR_PASS,
	OXIDE_STATION,
	COCO_PARK,
	TINY_ARENA,
	SLIDE_COLISEUM,
	TURBO_TRACK,
	NITRO_COURT,
	RAMPAGE_RUINS,
	PARKING_LOT,
	SKULL_ROCK,
	THE_NORTH_BOWL,
	ROCKY_ROAD,
	LAB_BASEMENT,
	GEM_STONE_VALLEY,
	N_SANITY_BEACH,
	THE_LOST_RUINS,
	GLACIER_PARK,
	CITADEL_CITY,
	INTRO_RACE_TODAY,
	INTRO_COCO,
	INTRO_TINY,
	INTRO_POLAR,
	INTRO_DINGODILE,
	INTRO_CORTEX,
	INTRO_SPACE,
	INTRO_CRASH,
	INTRO_OXIDE,
	MAIN_MENU_LEVEL,
	ADVENTURE_CHARACTER_SELECT,
	NAUGHTY_DOG_CRATE,
	OXIDE_ENDING,
	OXIDE_TRUE_ENDING,
	CREDITS_LEVEL,
	CREDITS_CRASH,
	CREDITS_TINY,
	CREDITS_COCO,
	CREDITS_N_GIN,
	CREDITS_DINGO,
	CREDITS_POLAR,
	CREDITS_PURA,
	CREDITS_PINSTRIPE,
	CREDITS_PAPU,
	CREDITS_ROO,
	CREDITS_JOE,
	CREDITS_TROPY,
	CREDITS_PENTA,
	CREDITS_FAKE_CRASH,
	CREDITS_OXIDE,
	CREDITS_AMI,
	CREDITS_ISABELLA,
	CREDITS_LIZ,
	CREDITS_MEGUMI,
	SCRAPBOOK
};

// transparent parameter of getTPage()
enum BlendMode
{
	// 50% transparency
	TRANS_50=0,

	// additive blending
	ADD=1,

	// subtractive blending
	SUBTRACT=2,

	// additive blending on 25% transparency
	ADD_25=3
};

// for drawing on quadblocks
struct IconGroup4
{
	struct TextureLayout texLayout[4];
};

struct AnimTex
{
	// 0x0
	// pointer to next AnimTex struct...
	// cycles through the entirety of ptrarray
	struct AnimTex* ptrNext;

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
	// ptrarray[numFrames] leads to the ptrNext of some other AnimTex struct or something
	struct AnimTex* ptrarray[1];
};

struct PVS
{
	int* visLeafSrc;
	int* visFaceSrc;
	struct Instance** visInstSrc;
	
	// either OVert or SCVert
	int* visExtraSrc;
};

struct QuadBlock
{
	// 0x0
	short index[9];

	// 0x12
	u_short quadFlags;

	// 0x14
	int draw_order_low; // actually for "med"

	// 0x18
	int draw_order_high;

	// 0x1c
	struct IconGroup4* ptr_texture_mid[4];

	// 0x2c
	struct BoundingBox bbox;

	// 0x38
	char terrain_type;
	char weather_intensity;
	char weather_vanishRate;
	char speedImpact;

	// 0x3C
	short blockID;
	char respawnIndex;
	char triNormalVecBitShift;

	// 0x40
	struct IconGroup4* ptr_texture_low;

	// 0x44
	struct PVS* pvs;

	// 0x48
	// explained in FUN_8001f2dc
	short triNormalVecDividend[10];

	// full struct is 0x5c bytes large
};

// BSP box that contains geometry
struct BSP
{
	// 0x0
	u_short flag;

	// 0x2
	short id;

	// 0x4
	struct BoundingBox box;

	// 0x10

	// determined by flag
	// 0: vis_data_branch
    // 1: vis_data_leaf
	union
	{
		// 0x10
		struct
		{
			// 0x10
			// x, y, z, [?]
			short axis[4];

			// 0x18
			// leftChildID, rightChildID, [?], [?]
			short childID[4];

		} branch;

		// 0x10
		struct
		{
			// 0x10
			int unk1;
			
			// 0x14
			// the code keeps looping through the 
			// array until it finds a 4-byte 0x00000000
			// to determine end of list
			struct BSP* bspHitboxArray;

			// 0x18
			int numQuads;

			// 0x1C
			struct QuadBlock* ptrQuadBlockArray;
		} leaf;
		
		// 0x10
		struct
		{
			// 0x10
			short unkShort[6];
			// see FUN_8001d0c4
			
			// 0x1C
			// These are always InstDef, not converted to Instance
			struct InstDef* instDef;
		} hitbox;

	} data;

	// 0x20 bytes large
};

struct LevVertex
{
	// 0x0
	short pos[3];
	
	// 0x6
	// FUN_8001ef50
	u_short flags;

	// 0x8
	unsigned char color_hi[4];

	// 0xC
	unsigned char color_lo[4];

	// 0x10 bytes large
};

// scenery vertex
struct SCVert
{
	struct LevVertex* v;
	int offset_pos_xy;
	int offset_pos_zw;
	int offset_color_rgba;
};

// ocean vertex
struct OVert
{
	// int & 0x003f
	// int & 0x0fc0
	// int & 0xf000

	// 2 bytes large,
	// always in pairs of two
};

struct WaterVert
{
	struct LevVertex* v;
	struct OVert* w;
};

struct RainBuffer
{
  // 0x0 (0x1a40)
  int numParticles_curr;

  // 0x4 (0x1a44)
  // if zero, then there is no max
  short numParticles_max;
  short vanishRate;

  // 0x8
  char unk_4[0x10];

  // 0x18 (0x1a58)
  short cameraPos[3];

  // 0x1E
  short unk_22;

  // 0x20
  unsigned int colorRGBA_top;
  unsigned int colorRGBA_bottom;

  // 0x28
  int renderMode[2];

  // 0x30 -- size of struct

};

struct VisMem
{
	// 4 of each for number of players

	// 0x00-0x3F are all DST
	// 0x40-0x7F are all SRC
	// SRC constantly copies to DST
	// DST never changes 
	// SRC always changes based on CamDC
	// why is the copy needed?

	// 0x00-0x0F
	// list of BSP leaf nodes
	// size = numLeaf/32
	int* visLeafList[4]; // real ND name

	// 0x10-0x1F
	// bit index quadblock visibility
	// size = numQuadBlock/32 bytes
	int* visFaceList[4]; // real ND name

	// 0x20-0x2F
	// bit index ocean visibility
	int* visOVertList[4]; // real ND name

	// 0x30-0x3F
	// bit index scenery visibility
	void* visSCVertList[4]; // real ND name

	// 0x40-0x4F
	void* visLeafSrc[4]; // copies to other

	// 0x50-0x5F
	void* visFaceSrc[4]; // copies to other

	// 0x60-0x6F
	void* visOVertSrc[4]; // copies to other

	// 0x70-0x7F
	void* visSCVertSrc[4]; // copies to other

	// 0x80-0x8F
	// size = 8 * numBspNodes,
	// this is the memory where RenderLists exist,
	// allows every BSP to link to another BSP
	void* bspList[4];
};

struct mesh_info
{
	// 0x0
	int numQuadBlock;

	// 0x4
	int numVertex;

	// 0x8
	int unk1;

	// 0xC
	struct QuadBlock* ptrQuadBlockArray;

	// 0x10
	struct LevVertex* ptrVertexArray;

	// 0x14
	int unk2;

	// 0x18
	struct BSP* bspRoot;

	// 0x1C
	int numBspNodes;

	// 0x20 bytes large
};

struct SpawnType1
{
	int count;
	
	// more than 1, determined by "count"
	void* pointers[1];
};

struct SpawnType2
{
	int numCoords;
	short* posCoords;
};

// need a better name for this,
// also for track-select video,
// progression data, player respawn, etc
struct WarpballPathNode
{
	// 0x0
	short pos[3];
	
	// 0x6
	short distToFinish;
	
	// 0x8
	char nextIndex_forward;
	char nextIndex_left;
	char nextIndex_backward;
	char nextIndex_right;
	
	// 0xC -- size
};

struct Level
{
	// 0x0
	struct mesh_info* ptr_mesh_info;

	// 0x4
	void* ptr_skybox;

	// 0x8
	struct AnimTex* ptr_anim_tex;

	// 0xc
	unsigned int numInstances;

	// 0x10
	// each one 0x40 bytes large
	void* ptrInstDefs;

	// 0x14
	unsigned int numModels;

	// 0x18
	struct Model** ptrModelsPtrArray;

	// 0x1c
	void* unk3;

	// 0x20
	void* unk4;

	// 0x24
	// converts back and forth, Inst to InstDef
	struct InstDef** ptrInstDefPtrArray;

	// 0x28
	// related to water?
	void* unk5;

	// 0x2c
	void* null1;

	// 0x30
	void* null2;

	// 0x34
	int count_water;

	// 0x38
	struct WaterVert* ptr_water;

	// 0x3c
	void* ptr_named_tex;

	// 0x40
	void* ptr_named_tex_array;

	// 0x44
	void* ptr_tex_waterEnvMap;

	// 0x48
	struct
	{
		short pointFrom;
		short pointTo;

		// RGBA
		u_int colorFrom;
		u_int colorTo;

	} glowGradient[3];

	// 0x6c
	struct
	{
		short pos[3];
		short rot[3];
	} DriverSpawn[8];

	// 0xCC -- next
	char unk_Lev_CC[0xC];

	// 0xD8
	// for fullscreen clears
	u_int clearColorRGBA;

	// 0xDC
	// & 2 = mask grab when underwater
	u_int configFlags;

	// 0xE0
	char* build_start;

	// 0xE4
	char* build_end;

	// 0xE8
	char* build_type;

	// 0xEC
	char unk_EC[0x18];

	// 0x104
	struct RainBuffer rainBuffer;

	// 0x134
	struct SpawnType1* ptrSpawnType1;

	// spawn_arrays2 is for things
	// like Seal, Minecart, etc,
	// series of positions (only positions)

	// 0x138
	int numSpawnType2;

	// 0x13C
	struct SpawnType2* ptrSpawnType2;

	// spawn_arrays is for things
	// N Gin Labs barrel, Snowball,
	// series of positions and rotations

	// 0x140
	int numSpawnType2_PosRot;

	// 0x144
	struct SpawnType2* ptrSpawnType2_PosRot;

	// restart_points is for respawning
	// driver on track after falling off

	// 0x148
	int cnt_restart_points;

	// 0x14C
	struct WarpballPathNode* ptr_restart_points;

	// 0x150
	char unk_150[0x10];

	// 0x160
	// for gradient clears
	struct
	{
		char rgb[3];
		char enable;

		// 0 - top half
		// 1 - bottom half
		// 2 - gradient
	} clearColor[3];

	// 0x16C
	int unk_16C;

	// 0x170
	int unk_170;

	// 0x174
	int numSCVert;

	// 0x178
	void* ptrSCVert;

	// 0x17c - 0x182
	char unkStarData[0x8];

	// split-lines
	// for ice, mud, water
	// 0x184
	// 0x186
	char splitLines[4];

	// 0x188
	struct NavHeader** LevNavHeader;

	// 0x18C
	// used in FUN_80060630
	int unk_18C;

	// 0x190
	struct VisMem* visMem;
	
	char footer[0x60];
};