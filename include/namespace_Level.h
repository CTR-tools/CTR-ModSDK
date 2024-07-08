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
	CREDITS_CRASH,
	CREDITS_CORTEX,
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

enum TerrainType
{
	TERRAIN_MUD = 14,
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

// textures used for a quad in a quadblock
// ctr-tools only rips the "near" and "mosaic" texture levels, but the idea is that middle and far are to use lower-quality textures
struct IconGroup4
{
	struct TextureLayout far;
	struct TextureLayout middle;
	struct TextureLayout near;
	struct TextureLayout mosaic;
};

struct AnimTex
{
	// 0x0
	// pointer to IconGroup4 struct to be animated
	// cycles through the entirety of ptrarray
	int* ptrActiveTex;

	// 0x4
	short numFrames;

	// 0x6
	short frameDuration;

	// 0x8
	short shiftFactor;

	// 0xA
	u_short frameIndex;

	// 0xC
	// size = numFrames
	// After this array is the next AnimTex
	//struct IconGroup4* ptrarray[0];
};

#define ANIMTEX_GETARRAY(x) \
	((unsigned int)x + sizeof(struct AnimTex))

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
	// todo: this is a packed bit value
	// refactor to a usable struct somehow
	/*
		drawOrderLow |
		faceFlags[0].packedValue << (8 + 0 * 5) |
		faceFlags[1].packedValue << (8 + 1 * 5) |
		faceFlags[2].packedValue << (8 + 2 * 5) |
		faceFlags[3].packedValue << (8 + 3 * 5) |
		(doubleSided ? 1 : 0) << 31)
	*/
	/*
		//where 5 bits of faceFlags are
		3 bits Rotation = x & 7;
		2 bits faceMode = (x >> 3) & 3;
	*/
	unsigned int draw_order_low;



	// 0x18
	// 4 bytes, byte per mid quad
	unsigned int draw_order_high;

	// 0x1c
	// used for the textures of all 4 quads in a medium-level quadblock
	// usually points to IconGroup4, but can also point to AnimTex structs
	// member 0 is 0,0 in xy, 1 is 1,0, 2 is 0,1, 3 is 1,1
	void* ptr_texture_mid[4];

	// 0x2c
	struct BoundingBox bbox;

	// 0x38
	char terrain_type;
	char weather_intensity;
	char weather_vanishRate;
	char speedImpact;

	// 0x3C
	short blockID;

	// used for checkpoint progression
	// and also respawns
	char checkpointIndex;

	char triNormalVecBitShift;

	// 0x40
	// used for the texture of a quad in low level of detail
	// the same as ptr_texture_mid, just not as an array
	void* ptr_texture_low;

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
	short data[2];
};

struct WaterVert
{
	struct LevVertex* v;
	struct OVert* w;
};

// used for rain and snow particles
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
  // controls top color of particles
  unsigned int colorRGBA_top;

  // 0x24
  // controls bottom color of particles
  unsigned int colorRGBA_bottom;

  // 0x28
  // controls how particles are drawn
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

enum ST1
{
	ST1_MAP=0,
	ST1_SPAWN=1,
	ST1_CAMERA_EOR,
	ST1_CAMERA_PATH,
	ST1_NTROPY,
	ST1_NOXIDE,
	ST1_CREDITS
};

struct SpawnType1
{
	int count;

	//void* pointers[0];
};
#define ST1_GETPOINTERS(x) \
	((unsigned int)x + sizeof(struct SpawnType1))

struct SpawnType2
{
	int numCoords;
	short* posCoords;
};

// per-quadblock checkpoint node
// each node holds the amount of distance to finish line as well as the index of the nodes that go before or after it
// and position values, which are used for respawns as well as the warp orb path
// they're also used for the track videos on the main menu!
struct CheckpointNode
{
	// 0x0
	short pos[3];

	// 0x6
	unsigned short distToFinish;

	// 0x8
	unsigned char nextIndex_forward;
	unsigned char nextIndex_left;
	unsigned char nextIndex_backward;
	unsigned char nextIndex_right;

	// 0xC -- size
};

struct SkyboxFace {
	u_short A; //ABC stores offsets to add to ptrVerts. divide by 12 if you need an index
	u_short B;
	u_short C;
	u_short D; //this is uh, ot ptr increment? always 0 in the files
};

struct ShortVertex {
	SVECTOR Position; //this is padded 2*4
	CVECTOR Color;
};

#define NUM_SKYBOX_SEGMENTS 8
struct Skybox
{
	int numVertex;
	struct ShortVertex* ptrVertex;

	short numFaces[NUM_SKYBOX_SEGMENTS];
	struct SkyboxFace* ptrFaces[NUM_SKYBOX_SEGMENTS];

	// struct SkyboxFace allFaces[0];
};
#define SKY_GETFACES(x) \
	((unsigned int)x + sizeof(struct Skybox))

struct LevTexLookup
{
	int numIcon;
	struct Icon* firstIcon;
	int numIconGroup;
	struct IconGroup** firstIconGroupPtr;
};

struct Level
{
	// 0x0
	// pointer to mesh info
	struct mesh_info* ptr_mesh_info;

	// 0x4
	// pointer to skybox (struct not yet known)
	struct Skybox* ptr_skybox;

	// 0x8
	// pointer to array of animated texture structs
	struct AnimTex* ptr_anim_tex;

	// 0xc
	// number of model instances in the level
	// (i.e. every single box, fruit, etc.)
	unsigned int numInstances;

	// 0x10
	// points to the 1st entry of the array of InstDefs
	// (whatever they are)
	struct InstDef* ptrInstDefs;

	// 0x14
	// number of actual models
	unsigned int numModels;

	// 0x18
	// pointer to the array of pointers to models
	struct Model** ptrModelsPtrArray;

	// 0x1c
	// unknown, extra bsp region
	void* unk3;

	// 0x20
	// unknown, extra bsp region
	void* unk4;

	// 0x24
	// pointer to the array of pointers to model instances (?)
	// converts back and forth, Instance to InstDef
	struct InstDef** ptrInstDefPtrArray;

	// 0x28
	// unknown, extra bsp region
	// related to water?
	void* unk5;

	// 0x2c
	// assumed to be reserved
	void* null1;

	// 0x30
	// assumed to be reserved
	void* null2;

	// 0x34
	// number of vertices treated as water
	int numWaterVertices;

	// 0x38
	// pointer to array of water entries
	struct WaterVert* ptr_water;

	// 0x3c
	// leads to the icon pack header
	struct LevTexLookup* levTexLookup;

	// 0x40
	// leads to the icon pack data
	struct Icon* ptr_named_tex_array;

	// 0x44
	// pointer to environment map, used by water rendering
	void* ptr_tex_waterEnvMap;

	// 0x48
	// used for additional skybox gradients (e.g. papu's pyramid)
	struct
	{
		short pointFrom;
		short pointTo;

		// RGBA
		u_int colorFrom;
		u_int colorTo;

	} glowGradient[3];

	// 0x6c
	// array of 8 starting locations
	struct
	{
		short pos[3];
		short rot[3];
	} DriverSpawn[8];

	// 0xCC -- next
	// unknown, extra bsp regions
	void* unk_Lev_CC;
	void* unk_Lev_D0;

	// 0xD4
	// assumed to be a pointer to low textures array, there is no number of entries though
	void* ptrLowTexArray;

	// 0xD8
	// Used in Coco Park, encoded as Blue
	u_int clearColorRGBA;

	// 0xDC
	// toggles some level stuff
	// & 1 = enables glowGradient skybox gradients
	// & 2 = mask grab when underwater
	// & 4 = toggles between water and animated vertices?
	u_int configFlags;

	// 0xE0
	// pointer to string, date, assumed bsp compilation start
	char* build_start;

	// 0xE4
	// pointer to string, date, assumed bsp compilation end
	char* build_end;

	// 0xE8
	// pointer to string, assumed build type
	char* build_type;

	// 0xEC
	char unk_EC[0x18];

	// 0x104
	// used for rain and snow
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
	struct CheckpointNode* ptr_restart_points;

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
	short unkStarData[4];

	// split-lines
	// for ice, mud, water
	// 0x184
	// 0x186
	char splitLines[4];

	// 0x188
	struct NavHeader** LevNavTable;

	// 0x18C
	// used in FUN_80060630
	int unk_18C;

	// 0x190
	struct VisMem* visMem;

	char footer[0x60];
};

_Static_assert(sizeof(struct RainBuffer) == 0x30);