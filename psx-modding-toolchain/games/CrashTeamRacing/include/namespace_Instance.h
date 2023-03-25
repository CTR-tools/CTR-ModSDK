struct ModelFrame
{
	// origin
	short pos[3];

	// size of frame depends on model
};

struct ModelAnim
{
	char name[0x10];

	short numFrames;
	short frameSize;

	// 0x14
	// same as model -> 0x30
	// copied to instance -> 0xd8
	unsigned int unkOffset0x14;

	// 0x18
	// this is where the first frame starts
	// Array of ModelFrame
};

// Note to self,
// rename Model to ModelHeaderGroup
// then make a ModelHeader
// then make Model for what is actually drawn
//		(pointers to colors, polygons, etc)

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
	short flags;

	// 0x18
	short scale[4];

	// 0x20
	unsigned int ptrCommandList;

	// 0x24
	unsigned int ptrVertexData;

	// 0x28
	unsigned int ptrTexLayout; // same as LEV

	// 0x2C
	unsigned int ptrColors; // CLUT = color lookup table

	// 0x30
	// same as anim->0x14
	unsigned int unk3;

	// 0x34
	unsigned int numAnimations;

	// 0x38
	struct ModelAnim** ptrAnimations;

	// 0x3C
	unsigned int unk4;
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
	int colorRGBA;

	// 0x20 (0x28 - 8)
	int flags;

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
	struct TileView* tileView;

	// 0x78 - another matrix? in DrawFunc_Split and DrawFunc_Normal
	MATRIX m1;
	
	// 0x98 - another matrix? in normal wheel rendering (FUN_8006e588) (and drawFuncs, like 0x78)
	MATRIX m2;

	// all get set in FUN_80070950
	// 0xb8 - copy of 0x28 (prev frame?) (flags per player?)
	int unkb8[2];

	// 0xc0 - origin of cur frame
	// 0xc4 - origin of next frame
	int unkc0[2];
	
	// 0xc8
	int ptrCommandList;
	
	// 0xcc
	int ptrTexLayout;
	
	// 0xd0
	int ptrColorLayout;
	
	// 0xd4 - Anim->offset0x14?
	int unkD4;
	
	// 0xd8 - LOD index (0,1,2,3)
	int lodIndex;

	// 0xe0 - pointer to LOD ModelHeader
	struct ModelHeader* mh;

	// 0xe4
	char unkE4[0x10];

	// 0xec - render function
	// 0xf0 - func (for what?)

	// 0xf4
	short specLight[4];

	// 0xfc
	struct Instance* birth2D;

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
	int colorRGBA;

	// 0x28
	// & 0x1 = draw instance
	// & 0x2, 0x4, 0x8 -- FUN_80030ad4 -- collision?
	// & 0xX0 = X=0 freezes animation, X=8 hides model, x=1-7 plays animations
	// & 0x80 = make invisible
	// & 0x100 = tileView exists
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
	int flags;

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
	int reflectionRGBA;

	// instance->0x5C
	// instance->0x60 (funcPtr for individual prims)
	// instance->0x64
	// instance->0x68
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

	// end of "main" Instance

	// 0x74
	struct InstDrawPerPlayer idpp[0];

	// struct is 0xFC bytes large (in 1P mode)
};
