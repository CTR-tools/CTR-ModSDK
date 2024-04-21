// & 0x1 = draw instance
// & 0x2, 0x4, 0x8 -- FUN_80030ad4 -- collision?
// & 0xX0 = X=0 freezes animation, X=8 hides model, x=1-7 plays animations
// & 0x80 = make invisible
// & 0x100 = pushBuffer exists
// & 0x200 = pixel LOD?
// & 0x400 = creditghost, screenspace instance
// & 0x2000 = split-line
// & 0x4000 = reflective
// & 0x8000 = reverse cull direction
// & 0x10000 = draw transparent (not for ghosts)
// & 0x20000 = disable vertex color, specular lighting, use instance color
// & 0x60000 = draw transparent (used by ghosts)
// & 0x8000000 = draw huge
// & 0x10000000 = invisible before pause
// & 0x20000000 = invisible only during pause
enum InstanceFlags
{
	DRAW_INSTANCE = 1,
	//
	//
	//
	//
	//
	//
	HIDE_MODEL = 0x80,
	TILEVIEW_EXISTS = 0x100,
	PIXEL_LOD = 0x200,
	SCREENSPACE_INSTANCE = 0x400,
	//
	//
	SPLIT_LINE = 0x2000,
	REFLECTIVE = 0x4000,
	REVERSE_CULL_DIRECTION = 0x8000,
	DRAW_TRANSPARENT = 0x10000,
	USE_SPECULAR_LIGHT = 0x20000,
	GHOST_DRAW_TRANSPARENT= 0x60000,
	//
	//
	//
	//
	//
	//
	//
	//
	VISIBLE_DURING_GAMEPLAY = 0x2000000,
	DRAW_HUGE = 0x8000000,
	INVISIBLE_BEFORE_PAUSE = 0x10000000,
	INVISIBLE_DURING_PAUSE = 0x20000000
};

enum MODEL_ID
{
    NOFUNC = 0x00,
    ANIMATE_IF_HIT = 0x01,
    PU_WUMPA_FRUIT = 0x02,
    PU_SMALL_BOMB = 0x03,
    PU_LARGE_BOMB = 0x04,
    PU_MISSILE = 0x05,
    PU_EXPLOSIVE_CRATE = 0x06,
    PU_FRUIT_CRATE = 0x07,
    PU_RANDOM_CRATE = 0x08,
    PU_TIME_CRATE_1 = 0x09,
    PU_TIME_CRATE_2 = 0x0A,
    PU_TIME_CRATE_3 = 0x0B,
    PU_POISON = 0x0C,
    PU_SHIELD = 0x0D,
    PU_INVINCIBILITY = 0x0E,
    PU_SPRING = 0x0F,
    PU_CLOCK = 0x10,
    PU_TURBO = 0x11,
    FLAME_JET = 0x12,
    PIRANHA_PLANT = 0x13,
    GATE = 0x14,
    START_LINE = 0x15,
    SPRING = 0x16,
    TURBO_MODEL = 0x17,
    DYNAMIC_PLAYER = 0x18,
    DYNAMIC_SMALL_BOMB = 0x19,
    DYNAMIC_LARGE_BOMB = 0x1A,
    DYNAMIC_MISSILE = 0x1B,
    DYNAMIC_EXPLOSIVE_CRATE = 0x1C,
    DYNAMIC_POISON = 0x1D,
    DYNAMIC_INVINCIBILITY = 0x1E,
    DYNAMIC_SPLINE_FOLLOWER = 0x1F,
    DYNAMIC_SNOWBALL = 0x20,
    DYNAMIC_MINE_CART = 0x21,
    TEMP_SNOWBALL = 0x22,
    FINISH_LINE = 0x23,
    ARMADILLO = 0x24,
    BLADE = 0x25,
    STATIC_CRATE_EXPLOSION = 0x26,
    STATIC_CRATE_TNT = 0x27,
    STATIC_CRATE_NITRO = 0x28,
    DYNAMIC_ROCKET = 0x29,
    DYNAMIC_BIGROCKET = 0x2A,
    STATIC_WARPEDBURST = 0x2B,
    STATIC_TURBO_EFFECT = 0x2C,
    STATIC_TURBO_EFFECT1 = 0x2D,
    STATIC_TURBO_EFFECT2 = 0x2E,
    STATIC_TURBO_EFFECT3 = 0x2F,
    STATIC_TURBO_EFFECT4 = 0x30,
    STATIC_TURBO_EFFECT5 = 0x31,
    STATIC_TURBO_EFFECT6 = 0x32,
    STATIC_TURBO_EFFECT7 = 0x33,
    STATIC_TURBO_EFFECT_DARK = 0x34,
    STATIC_SHOCKWAVE = 0x35,
    DYNAMIC_WARPBALL = 0x36,
    STATIC_FRUITDISP = 0x37,
    STATIC_BIG1 = 0x38,
    STATIC_AKUAKU = 0x39,
    STATIC_UKAUKA = 0x3A,
    DYNAMIC_BOMB = 0x3B,
    STATIC_BEAKER = 0x3C,
    STATIC_BEAKERBREAK = 0x3D,
    STATIC_AKUBEAM = 0x3E,
    DYNAMIC_ROBOT_CAR = 0x3F,
    STATIC_UKABEAM = 0x40,
    STATIC_SHIELD = 0x41,
    STATIC_CLOUD = 0x42,
    STATIC_WAKE = 0x43,
    STATIC_SHOCKWAVE_RED = 0x44,
    STATIC_SHOCKWAVE_GREEN = 0x45,
    STATIC_BEAKER_RED = 0x46,
    STATIC_BEAKER_GREEN = 0x47,
    STATIC_BEAKERBREAK_RED = 0x48,
    STATIC_BEAKERBREAK_GREEN = 0x49,
    LENSFLARE = 0x4A,
    DYNAMIC_GHOST = 0x4B,
    DYNAMIC_SEAL = 0x4C,
    DYNAMIC_ORCA = 0x4D,
    DYNAMIC_BARREL = 0x4E,
    DYNAMIC_VONLABASS = 0x4F,
    DYNAMIC_SKUNK = 0x50,
    DYNAMIC_TURTLE = 0x51,
    DYNAMIC_SPIDER = 0x52,
    DYNAMIC_SPIDERSHADOW = 0x53,
    DYNAMIC_FIREBALL = 0x54,
    DYNAMIC_DRUM = 0x55,
    DYNAMIC_SHIELD = 0x56,
    STATIC_PIPE1 = 0x57,
    STATIC_PIPE2 = 0x58,
    STATIC_VENT = 0x59,
    DYNAMIC_SHIELD_DARK = 0x5A,
    STATIC_CASTLE_SIGN = 0x5B,
    STATIC_TIME_CRATE_01 = 0x5C,
    DYNAMIC_HIGHLIGHT = 0x5D,
    DYNAMIC_SHIELD_GREEN = 0x5E,
    STATIC_GEM = 0x5F,
    STATIC_CRYSTAL = 0x60,
    STATIC_RELIC = 0x61,
    STATIC_TROPHY = 0x62,
    STATIC_KEY = 0x63,
    STATIC_TIME_CRATE_02 = 0x64,
    STATIC_TIME_CRATE_03 = 0x65,
    STATIC_INTRO_TROPHY = 0x66,
    STATIC_INTRO_CRASH = 0x67,
    STATIC_RINGTOP = 0x68,
    STATIC_RINGBOTTOM = 0x69,
    STATIC_CTR = 0x6A,
    STATIC_BANNER = 0x6B,
    STATIC_WARPPAD = 0x6C,
    STATIC_BIG0 = 0x6D,
    STATIC_BIG9 = 0x6E,
    STATIC_BIGX = 0x6F,
    STATIC_TEETH = 0x70,
    STATIC_STARTTEXT = 0x71,
    STATIC_SAVEOBJ = 0x72,
    STATIC_PINGARAGE = 0x73,
    STATIC_PAPUGARAGE = 0x74,
    STATIC_ROOGARAGE = 0x75,
    STATIC_JOEGARAGE = 0x76,
    STATIC_OXIDEGARAGE = 0x77,
    STATIC_SCAN = 0x78,
    STATIC_SUBTRACT = 0x79,
    STATIC_DOOR = 0x7A,
    STATIC_BEAM = 0x7B,
    STATIC_BOTTOMRING = 0x7C,
    STATIC_TOKEN = 0x7D,
    STATIC_CRASHDANCE = 0x7E,
    STATIC_CORTEXDANCE = 0x7F,
    STATIC_TINYDANCE = 0x80,
    STATIC_COCODANCE = 0x81,
    STATIC_NGINDANCE = 0x82,
    STATIC_DINGODANCE = 0x83,
    STATIC_POLARDANCE = 0x84,
    STATIC_PURADANCE = 0x85,
    STATIC_PINSTRIPEDANCE = 0x86,
    STATIC_PAPUDANCE = 0x87,
    STATIC_ROODANCE = 0x88,
    STATIC_JOEDANCE = 0x89,
    STATIC_NTROPYDANCE = 0x8A,
    STATIC_PENDANCE = 0x8B,
    STATIC_FAKEDANCE = 0x8C,
    STATIC_OXIDEDANCE = 0x8D,
    STATIC_GARAGETOP = 0x8E,
    STATIC_TAWNA1 = 0x8F,
    STATIC_TAWNA2 = 0x90,
    STATIC_TAWNA3 = 0x91,
    STATIC_TAWNA4 = 0x92,
    STATIC_C = 0x93,
    STATIC_T = 0x94,
    STATIC_R = 0x95,
    STATIC_CRASHINTRO = 0x96,
    STATIC_COCOINTRO = 0x97,
    STATIC_CORTEXINTRO = 0x98,
    STATIC_TINYINTRO = 0x99,
    STATIC_POLARINTRO = 0x9A,
    STATIC_DINGOINTRO = 0x9B,
    STATIC_OXIDEINTRO = 0x9C,
    STATIC_SIMPLEKARTINTRO = 0x9D,
    STATIC_TINYKARTINTRO = 0x9E,
    STATIC_DINGOKARTINTRO = 0x9F,
    STATIC_SIMPLEOBJINTRO = 0xA0,
    STATIC_PPOINTTHINGINTRO = 0xA1,
    STATIC_PRTHINGINTRO = 0xA2,
    STATIC_OXIDELILSHIP = 0xA3,
    STATIC_INTROOXIDECAM = 0xA4,
    STATIC_INTROOXIDEBODY = 0xA5,
    STATIC_STARTBANNERWAVE = 0xA6,
    STATIC_DOOR2 = 0xA7,
    STATIC_PODIUM = 0xA8,
    STATIC_PINHEAD = 0xA9,
    STATIC_PAPUHEAD = 0xAA,
    STATIC_ROOHEAD = 0xAB,
    STATIC_JOEHEAD = 0xAC,
    STATIC_OXIDEHEAD = 0xAD,
    STATIC_AKUMOUTH = 0xAE,
    STATIC_DINGOFIRE = 0xAF,
    STATIC_TOMBSTONE = 0xB0,
    STATIC_AKUBIG = 0xB1,
    STATIC_UKABIG = 0xB2,
    STATIC_UKAMOUTH = 0xB3,
    STATIC_UNUSED03 = 0xB4,
    STATIC_DOOR3 = 0xB5,
    NDI_BOX_BOX_01 = 0xB6,
    NDI_BOX_BOX_02 = 0xB7,
    NDI_BOX_BOX_02_BOTTOM = 0xB8,
    NDI_BOX_BOX_02_FRONT = 0xB9,
    NDI_BOX_BOX_02A = 0xBA,
    NDI_BOX_BOX_03 = 0xBB,
    NDI_BOX_CODE = 0xBC,
    NDI_BOX_GLOW = 0xBD,
    NDI_BOX_LID = 0xBE,
    NDI_BOX_LID2 = 0xBF,
    NDI_BOX_PARTICLES_01 = 0xC0,
    NDI_KART0 = 0xC1,
    NDI_KART1 = 0xC2,
    NDI_KART2 = 0xC3,
    NDI_KART3 = 0xC4,
    NDI_KART4 = 0xC5,
    NDI_KART5 = 0xC6,
    NDI_KART6 = 0xC7,
    NDI_KART7 = 0xC8,
    NDI_BOX_LIDB = 0xC9,
    NDI_BOX_LIDC = 0xCA,
    NDI_BOX_LIDD = 0xCB,
    STATIC_INTRO_FLASH = 0xCC,
    STATIC_INTRODOORS = 0xCD,
    STATIC_CRASHSELECT = 0xCE,
    STATIC_CORTEXSELECT = 0xCF,
    STATIC_TINYSELECT = 0xD0,
    STATIC_COCOSELECT = 0xD1,
    STATIC_NGINSELECT = 0xD2,
    STATIC_DINGOSELECT = 0xD3,
    STATIC_POLARSELECT = 0xD4,
    STATIC_PURASELECT = 0xD5,
    STATIC_ENDDOORS = 0xD6,
    STATIC_ENDFLASH = 0xD7,
    STATIC_ENDINGOXIDE = 0xD8,
    STATIC_ENDIGNOXIDE_02 = 0xD9,
    STATIC_ENDOXIDEBIGSHIP = 0xDA,
    STATIC_ENDOXIDELILSHIP = 0xDB,
    STATIC_OXIDECAMEND = 0xDC,
    STATIC_OXIDECAMEND02 = 0xDD,
    STATIC_JLOGO_FLAG = 0xDE,
    STATIC_OXIDESPEAKER = 0xDF,
    STATIC_INTROSPARKS = 0xE0,
    STATIC_GNORMALZ = 0xE1,
    STATIC_ADVHUB_DOORS = 0xE1,
    NUM_TYPES = 0xE2

};

// see 231: // modelHeader->ptrFrameData[modelHeader->ptrFrameData->vertexOffset]
struct ModelFrame
{
	// origin
	short pos[4];
	char unk16[16];
	int vertexOffset; // always 0x1C

	//char verts[0];
};

struct ModelAnim
{
	char name[0x10];

	unsigned short numFrames;
	short frameSize;

	// 0x14
	// same as model -> 0x30
	// copied to instance -> 0xd4
	// used for compressed animations,
	// or nullptr if animation is uncompressed
	u_int* ptrDeltaArray;

	// 0x18
	// struct ModelFrame firstFrame;
	// then verts, then next ModelFrame, then verts, etc...
};

#define MODELANIM_GETFRAME(x) \
	((unsigned int)x + sizeof(struct ModelAnim))

struct ModelHeader
{
	// name of individual model LOD,
	// "oxide_hi" for example
	// 0x0
	char name[0x10];

	// 0x10
	int unk1;

	// 0x14
	short maxDistanceLOD;

	// 0x16
	// 0x0 - normal 3D model
	// 0x1 - always point north
	// 0x2 - always point to camera (warppad numbers)
	unsigned short flags;

	// 0x18
	short scale[4];

	// 0x20
	unsigned int ptrCommandList;

	// 0x24
	// null if there are animations
	struct ModelFrame* ptrFrameData;

	// 0x28
	struct TextureLayout** ptrTexLayout; // same as LEV

	// 0x2C
	unsigned int* ptrColors; // CLUT = color lookup table

	// 0x30
	// same as anim->0x14
	unsigned int unk3;

	// 0x34
	unsigned int numAnimations;

	// 0x38
	struct ModelAnim** ptrAnimations;

	// 0x3C
	struct AnimTex* animtex;
};

// https://github.com/DCxDemo/CTR-tools/blob/master/formats/txt_ctr.txt
struct Model
{
	// name of model group
	// "oxide" for example
	// 0x0
	char name[0x10];

	// index of 2160 array
	// 0x10
	short id;

	// 0x12
	short numHeaders;

	// 0x14
	struct ModelHeader* headers;
};

struct InstDef
{
	// 0
	char name[0x10];

	// 0x10 (0x18 - 8)
	struct Model* model;

	// 0x14 (0x1c - 8)
	short scale[4];

	// 0x1c (0x24 - 8)
	unsigned int colorRGBA;

	// 0x20 (0x28 - 8)
	unsigned int flags;

	int unk24;
	int unk28;

	// 0x2c
	struct Instance* ptrInstance;

	// 0x30
	short pos[3];

	// 0x36
	short rot[3];

	// 0x3c
	int modelID;

	// 0x40 -- struct size
};

struct InstDrawPerPlayer
{
	// 0x74
	// used for flag & 0x2 to face camera
	struct PushBuffer* pushBuffer;

	// 0x78 - in DrawFunc_Split and DrawFunc_Normal
	MATRIX mvp;
	
	// 0x98 - in normal wheel rendering (FUN_8006e588) (and drawFuncs, like 0x78)
	MATRIX m3x3;

	// 0xb8 - same enum as Instance offset 0x28
	int instFlags;
	
	// 0xbc
	int unkbc;

	// 0xc0 - origin of cur frame
	// 0xc4 - origin of next frame
	struct ModelFrame* ptrCurrFrame;
	struct ModelFrame* ptrNextFrame;
	
	// 0xc8
	unsigned int ptrCommandList;
	
	// 0xcc
	struct TextureLayout** ptrTexLayout;
	
	// 0xd0
	unsigned int ptrColorLayout;
	
	// 0xd4
	int ptrDeltaArray;
	
	// 0xd8 - LOD index (0,1,2,3)
	int lodIndex;

    // 0xdc
    short unkDC[2];

	// 0xe0 - pointer to LOD ModelHeader
	struct ModelHeader* mh;

	// 0xe4
	int unkE4;
	int unkE8;
	int unkEC;
	int unkF0;

	// 0xec - render function
	// 0xf0 - func (for what?)

	// 0xf4
	short specLight[4];

	// 0xfc = end of struct

	// 0x74 + 0x88 = 0xFC
	// 0x88 = size of struct
};

// draws anything with a model
struct Instance
{
	// 0x0
	struct Instance* next;

	// 0x4
	struct Instance* prev;

	// 0x8
	char name[0x10];

	// 0x18
	struct Model* model;

	// 0x1c
	short scale[3];

	// 0x22
	short alphaScale;

	// 0x24
	unsigned int colorRGBA;

	// 0x28
	// see InstanceFlags enum
	unsigned int flags;

	// 0x2c
	// comes from LEVs
	struct InstDef* instDef;

	// 0x30
	// Rendering matrix (position + rotation)
	MATRIX matrix;

	// 0x50
	char unk50;
	char unk51;

	// 0x52
	char animIndex;
	char unk53;

	// 0x54
	short animFrame;

	// 0x56
	// mud, water, ice
	short vertSplit;

	// 0x58
	// on ice
	unsigned int reflectionRGBA;

	// instance->0x5C
	// instance->0x60 (funcPtr for individual prims)
	// instance->0x64
	// instance->0x68
	// instance->0x6c (ptr to Thread)
	// instance->0xEC (funcPtr for full model)
	// instance->0xF0 (8006a8e0) (animation related?)

// 8006C950 -- might be another jump

// 5C - 68 (normal kart)
// 8006C948 (or 8006C950) -- jr t10 goes to 8006ace0 (basically jr ra, except t10 is ra)
// 8006AD88 -- middle of RenderBucket_DrawInstPrim_Normal, called from RenderBucket_DrawFunc_Normal, inst->0xEC)
// 8006D55C
// 8006D428 -- called in ND box scene

// 5C - 68 (ghost kart)
// same as above, except 0x60 is:
// 8006D670 -- RenderBucket_DrawInstPrim_Ghost

	// 0x5c
	// between 8006c6f0 and 8006d5b8
	void* funcPtr[4];

	// 0x6c
	// Thread and Instance are linked together
	struct Thread* thread;

	// 0x70
	// see set in FUN_800abab0 (231)
	int bitCompressed_NormalVector_AndDriverIndex;

	// 0x74
	//struct InstDrawPerPlayer idpp[0];
};

#define INST_GETIDPP(x) \
	((unsigned int)x + sizeof(struct Instance))
	