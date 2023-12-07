#include <std/ptr.pat>
#include <std/string.pat>
#include <std/fxpt.pat>
#include <std/array.pat>
#include <type/types/c.pat>
#include <type/color.pat>

// CTR: Crash Team Racing level files
// author Superstarxalien

#pragma pattern_limit 500000

//using BSP; --these crashed before

fn ctr_ptr_base(auto thing)
{
	return 4;
};

struct CTRLEVPtr<PointeeTy, PointerTy>
{
	PointerTy pointerValue [[no_unique_address, hidden]];
	if (pointerValue == 0x0)
	{
		padding[sizeof(PointerTy)];
	}
	else
	{
		PointeeTy *data : PointerTy [[pointer_base("ctr_ptr_base")]];
	}
};

fn format_ctr_string(auto thing)
{
	return std::format(std::string::replace(thing, "\x00", ""));
};

fn format_ctr_fixedpoint(short thing)
{
	return std::format("{0}", std::fxpt::to_fixed(thing, 24));
};

struct MatrixMatrix
{
	s16 m[3];
};

struct MATRIX
{
	MatrixMatrix m[3];
	s32 t[3];
};

struct BoundingBox
{
	s16 min[3];
	s16 max[3];
};

struct PVS
{
	CTRLEVPtr<int, u32> visLeafSrc;
	CTRLEVPtr<int, u32> visFaceSrc;
	CTRLEVPtr<u32, u32> PTRtoPTR_visInstSrc;
	
	// either OVert or SCVert
	CTRLEVPtr<int, u32> visExtraSrc;
};

struct LevVertex
{
	// 0x0
	s16 pos[3];
	
	// 0x6
	// FUN_8001ef50
	u16 flags;

	// 0x8
	type::RGBA8 color_hi;

	// 0xC
	type::RGBA8 color_lo;

	// 0x10 bytes large
};

struct QuadBlock
{
	// 0x0
	s16 index[9];

	// 0x12
	u16 quadFlags;

	// 0x14
	int draw_order_low; // actually for med

	// 0x18
	int draw_order_high;

	// 0x1c
	// ptr_texture_mid can point to IconGroup3, IconGroup4, or AnimTex structs
	CTRLEVPtr<u32, u32> ptr_texture_mid[4];

	// 0x2c
	BoundingBox bbox;

	// 0x38
	s8 terrain_type;
	s8 weather_intensity;
	s8 weather_vanishRate;
	s8 speedImpact;

	// 0x3C
	short blockID;

	// used for checkpoint progression
	// and also respawns
	s8 checkpointIndex;

	s8 triNormalVecBitShift;

	// 0x40
	// ptr_texture_low can also point to IconGroup3, IconGroup4, or AnimTex structs
	CTRLEVPtr<u32, u32> ptr_texture_low;

	// 0x44
	CTRLEVPtr<PVS, u32> pvs;

	// 0x48
	// explained in FUN_8001f2dc
	s16 triNormalVecDividend[10];

	// full struct is 0x5c bytes large
};

bitfield Tpage
{
	x : 4 [[format("format_tpage_x")]];
	y : 1 [[format("format_tpage_y")]];
	blend_mode : 2 [[format("format_tpage_blend")]];
	bpp : 2 [[format("format_tpage_bpp")]];
	rest : 7;
};

fn format_texturelayout_v(u8 thing)
{
	return std::format("{0}", thing+(parent.clut));
};

struct TextureLayout
{
	// 0x14
	// top left corner
	u8 u0;
    u8 v0;

	// 0x16
	// holds X and Y with bit shifting
	u16 clut;

	// 0x18
	// top right corner
	u8 u1;
	u8 v1;

	// 0x1a
	// holds X and Y with bit shifting
	Tpage tpage;

	// 0x1c
	// bottom left corner
	u8 u2;
	u8 v2;

	// 0x1e
	// bottom right corner
	u8 u3;
	u8 v3;	
};

struct IconGroup4
{
	TextureLayout far;
	TextureLayout middle;
	TextureLayout near;
	TextureLayout mosaic;
};

struct AnimTex
{
	// 0x0
	// pointer to next AnimTex struct...
	// cycles through the entirety of ptrarray
	CTRLEVPtr<u32, u32> ptrNext;

	// 0x4
	short numFrames;

	// 0x6
	short frameDuration;

	// 0x8
	short shiftFactor;

	// 0xA
	// current frame
	u16 frameIndex;

	// 0xC
	// amount of elements in array is same as numFrames
	// ptrarray[numFrames] leads to the ptrNext of some other AnimTex struct or something
	CTRLEVPtr<IconGroup4, u32> ptrarray[this.numFrames];
};

struct ModelHeader
{
	// name of individual model LOD,
	// "oxide_hi" for example
	// 0x0
	char name[0x10] [[format("format_ctr_string")]];

	// 0x10
	int unk1;

	// 0x14
	short maxDistanceLOD;

	// 0x16
	// 0x0 - normal 3D model
	// 0x1 - always point north
	// 0x2 - always point to camera (warppad numbers)
	u16 flags;

	// 0x18
	short scale[4];

	// 0x20
	u32 ptrCommandList;

	// 0x24
	CTRLEVPtr<LevVertex, u32> ptrVertexData;

	// 0x28
	CTRLEVPtr<TextureLayout, u32> ptrTexLayout; // same as LEV

	// 0x2C
	u32 ptrColors; // CLUT = color lookup table

	// 0x30
	// same as anim->0x14
	u32 unk3;

	// 0x34
	u32 numAnimations;

	// 0x38
	CTRLEVPtr<u32, u32> ptrAnimations;

	// 0x3C
	u32 unk4;
};

struct Model
{
	// name of model group
	// "oxide" for example
	// 0x0
	char name[0x10] [[format("format_ctr_string")]];

	// index of 2160 array
	// 0x10
	short id;

	// 0x12
	short numHeaders;

	// 0x14
	CTRLEVPtr<u32, u32> headers[this.numHeaders];
};

struct Thread
{
	// 0x0
	CTRLEVPtr<u32, u32> next;

	// 0x4
	CTRLEVPtr<u32, u32> prev;

	// 0x8
	CTRLEVPtr<u32, u32> name;

	// 0xc
	// weapons hold drivers as parentThreads when fired
	CTRLEVPtr<u32, u32> parentThread;

	// 0x10
	// players hold other players,
	// cameras hold other cameras, etc
	CTRLEVPtr<u32, u32> siblingThread;

	// 0x14
	// drivers hold weapons as childThreads when fired
	CTRLEVPtr<u32, u32> childThread;

	// 0x18
	// unused, can pause a thread for
	// any number of frames
	int cooldownFrameCount;


	// & 0xff = threadBucket
	// 		0 - player
	// 		1 - robotcar
	// 		etc

	// & 0x0X00 = object pool (X=1,2,3)
	// & 0x0400 = init with sibling
	// & 0x0800 = dead thread, need to delete
	// & 0x1000 = disable collision
	// & 0x2000 = init with parent

	// & 0xXXX0000 = size of object allocated

	// 0x1c
	u32 flags;

	// 0x20
	int timesDestroyed;

	// 0x24
	u32 *funcThDestroy : u32;

	// 0x28
	u32 *funcThCollide : u32;

	// 0x2c
	u32 *funcThTick : u32;

	// This would be 9900C for players, or a pointer
	// to a camera, etc
	// 0x30
	CTRLEVPtr<u32, u32> object;

	// Thread and Instance are linked together,
	// except Camera storing CameraDC here
	// 0x34
	CTRLEVPtr<u32, u32> inst;

	// FUN_80058d2c uses 0x38 - 0x44

	// 0x38
	int driver_unk1;

	// 0x3c
	int driver_unk2;

	// 0x40
	short driver_unk3;

	// 0x42
	// only for driver collisions
	short driver_HitRadius;

	// only needs to be a char,
	// but padding makes it an int
	// 0x44
	int modelIndex;

	// this struct is 0x48 bytes large
};

bitfield InstanceFlag
{
	DRAW_INSTANCE : 1;
	POSSIBLY_COLLISION : 3;
	PLAY_ANIMATION : 3;
	HIDE_MODEL : 1;
	TILEVIEW_EXISTS : 1;
	PIXEL_LOD : 1;
	SCREENSPACE_INSTANCE : 1;
	UNKNOWN_1 : 2;
	SPLIT_LINE : 1;
	REFLECTIVE : 1;
	REVERSE_CULL_DIRECTION : 1;
	DRAW_TRANSPARENT : 1;
	DISABLE_VCOLOR_USE_INSTCOLOR : 1;
	UNKNOWN_2 : 9;
	DRAW_HUGE : 1;
	INVISIBLE_BEFORE_PAUSE : 1;
	INVISIBLE_DURING_PAUSE : 1;
};

struct Instance
{
	// 0x0
	CTRLEVPtr<u32, u32> next;

	// 0x4
	CTRLEVPtr<u32, u32> prev;

	// 0x8
	char name[0x10] [[format("format_ctr_string")]];

	// 0x18
	CTRLEVPtr<Model, u32> model;

	// 0x1c
	short scale[3];

	// 0x22
	short alphaScale;

	// 0x24
	type::RGBA8 colorRGBA;

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
	InstanceFlag flags;

	// 0x2c
	// comes from LEVs
	CTRLEVPtr<u32, u32> instDef;

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
	u32 reflectionRGBA;

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
	u32 *funcPtr[4] : u32;

	// 0x6c
	// Thread and Instance are linked together
	CTRLEVPtr<Thread, u32> thread;

	// 0x70
	// see set in FUN_800abab0 (231)
	int bitCompressed_NormalVector_AndDriverIndex;

	// end of "main" Instance

	// 0x74
	//struct InstDrawPerPlayer idpp[0];

	// struct is 0xFC bytes large (in 1P mode)
};

struct FixedPoint
{
	short [[format("format_ctr_fixedpoint")]];
};

struct InstDef
{
	// 0
	char name[0x10] [[format("format_ctr_string")]];

	// 0x10 (0x18 - 8)
	CTRLEVPtr<Model, u32> model;

	// 0x14 (0x1c - 8)
	FixedPoint scale[4];

	// 0x1c (0x24 - 8)
	type::RGBA8 colorRGBA;

	// 0x20 (0x28 - 8)
	InstanceFlag flags;

	int unk24;
	int unk28;

	// 0x2c
	CTRLEVPtr<Instance, u32> ptrInstance;

	// 0x30
	short pos[3];

	// 0x36
	short rot[3];

	// 0x3c
	int modelID;

	// 0x40 -- struct size
};

struct BSPbranch
{
	// 0x10
	// x, y, z, [?]
	s16 axis[4];

	// 0x18
	// leftChildID, rightChildID, [?], [?]
	s16 childID[4];
};

struct BSPleaf
{
	// 0x10
	int unk1;
	
	// 0x14
	// the code keeps looping through the 
	// array until it finds a 4-byte 0x00000000
	// to determine end of list
	//CTRLEVPtr<BSP, u32> bspHitboxArray; --these crashed before
	CTRLEVPtr<u32, u32> bspHitboxArray;

	// 0x18
	int numQuads;

	// 0x1C
	CTRLEVPtr<QuadBlock, u32> ptrQuadBlockArray;
};

struct BSPhitbox
{
	// 0x10
	s16 unkShort[6];
	// see FUN_8001d0c4
	
	// 0x1C
	// These are always InstDef, not converted to Instance
	CTRLEVPtr<u32, u32> PTRplaceholder_instDef;
};

union BSPdata
{
	// 0x10
	BSPbranch branch;

	// 0x10
	BSPleaf leaf;
	
	// 0x10
	BSPhitbox hitbox;
};

struct BSP
{
	// 0x0
	u16 flag;

	// 0x2
	short id;

	// 0x4
	BoundingBox box;

	// 0x10

	// determined by flag
	// 0: vis_data_branch
	// 1: vis_data_leaf
	BSPdata data;

	// 0x20 bytes large
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
	CTRLEVPtr<QuadBlock, u32> ptrQuadBlockArray;

	// 0x10
	CTRLEVPtr<LevVertex, u32> ptrVertexArray;

	// 0x14
	int unk2;

	// 0x18
	CTRLEVPtr<BSP, u32> bspRoot;

	// 0x1C
	int numBspNodes;

	// 0x20 bytes large
};

// used for rain and snow particles
struct RainBuffer
{
	// 0x0 (0x1a40)
	s32 numParticles_curr;

	// 0x4 (0x1a44)
	// if zero, then there is no max
	s16 numParticles_max;
	s16 vanishRate;

	// 0x8
	s8 unk_4[0x10];

	// 0x18 (0x1a58)
	s16 cameraPos[3];

	// 0x1E
	s16 unk_22;

	// 0x20
	// controls top color of particles
	type::RGBA8 colorRGBA_top;

	// 0x24
	// controls bottom color of particles
	type::RGBA8 colorRGBA_bottom;

	// 0x28
	// controls how particles are drawn
	s32 renderMode[2];

	// 0x30 -- size of struct

};

struct Gradient
{
	s16 pointFrom;
	s16 pointTo;

	// RGBA
	type::RGBA8 colorFrom;
	type::RGBA8 colorTo;
};

struct Spawn
{
	s16 pos[3];
	s16 rot[3];
};

struct BackgroundColor
{
	type::RGB8 rgb;
	s8 enable;
};

fn format_tpage_x(auto thing)
{
	return std::format("{0}", thing*64);
};

fn format_tpage_y(auto thing)
{
	return std::format("{0}", thing*256);
};

fn format_tpage_blend(auto thing)
{
	if (thing == 0)
	{
		return std::format("50% Opacity");
	}
	if (thing == 1)
	{
		return std::format("Additive");
	}
	if (thing == 2)
	{
		return std::format("Subtractive");
	}
	if (thing == 3)
	{
		return std::format("Additive, 25% Opacity");
	}
};

fn format_tpage_bpp(auto thing)
{
	if (thing == 0)
	{
		return std::format("4bpp");
	}
	if (thing == 1)
	{
		return std::format("8bpp");
	}
	if (thing == 2)
	{
		return std::format("16bpp");
	}
};

struct Skybox
{
	int numVertex;
	CTRLEVPtr<LevVertex, u32> ptrVertex;
	int numFaces[8];
	CTRLEVPtr<s16, u32> ptrFaces[8];
};

struct Icon
{
	// https://github.com/DCxDemo/CTR-tools/blob/master/ctr-tools/CTRFramework/CTRFramework.Code/lev/TextureLayout.cs

	// 0x0
	char name[0x10] [[format("format_ctr_string")]];

	// 0x10
	int global_IconArray_Index;

	TextureLayout texLayout;
};

struct IconGroup
{
	// 0x0
	char name[16] [[format("format_ctr_string")]];

	// 0x10
	short groupID;

	// 0x12
	short numIcons;

	// This is an array, not a pointer,
	// see below...
	// 0x14
	CTRLEVPtr<Icon, u32> icons[this.numIcons];
};

struct Level
{
	// 0x0
	// pointer to mesh info
	CTRLEVPtr<mesh_info, u32> ptr_mesh_info;

	// 0x4
	// pointer to skybox (struct not yet known)
	CTRLEVPtr<Skybox, u32> ptr_skybox;

	// 0x8
	// pointer to animated textures array
	CTRLEVPtr<AnimTex, u32> ptr_anim_tex;

	// 0xc
	// number of model instances in the level
	// (i.e. every single box, fruit, etc.)
	u32 numInstances;

	// 0x10
	// points to the 1st entry of the array of model instances (?)
	// each entry in the array is 0x40 bytes large
	CTRLEVPtr<InstDef, u32> ptrInstDefs;

	// 0x14
	// number of actual models
	u32 numModels;

	// 0x18
	// pointer to the array of pointers to models
	u32 PTRtoPTR_ptrModelsPtrArray;

	// 0x1c
	// unknown, extra bsp region
	CTRLEVPtr<u32, u32>unk3;

	// 0x20
	// unknown, extra bsp region
	CTRLEVPtr<u32, u32>unk4;

	// 0x24
	// pointer to the array of pointers to model instances (?)
	// converts back and forth, Instance to InstDef
	u32 PTRtoPTR_ptrInstDefPtrArray;

	// 0x28
	// unknown, extra bsp region
	// related to water?
	CTRLEVPtr<u32, u32>unk5;

	// 0x2c
	// assumed to be reserved
	CTRLEVPtr<u32, u32>null1;

	// 0x30
	// assumed to be reserved
	CTRLEVPtr<u32, u32>null2;

	// 0x34
	// number of vertices treated as water
	s32 numWaterVertices;

	// 0x38
	// pointer to array of water entries
	CTRLEVPtr<u32, u32>ptr_water;

	// 0x3c
	// leads to the icon pack header
	CTRLEVPtr<u32, u32> ptr_named_tex;

	// 0x40
	// leads to the icon pack data
	CTRLEVPtr<Icon, u32>ptr_named_tex_array;

	// 0x44
	// pointer to environment map, used by water rendering
	CTRLEVPtr<u32, u32>ptr_tex_waterEnvMap;

	// 0x48
	// used for additional skybox gradients (e.g. papu's pyramid)
	Gradient glowGradient[3];

	// 0x6c
	// array of 8 starting locations
	Spawn DriverSpawn[8];

	// 0xCC -- next
	// unknown, extra bsp regions
	CTRLEVPtr<u32, u32>unk_Lev_CC;
	CTRLEVPtr<u32, u32>unk_Lev_D0;

	// 0xD4
	// assumed to be a pointer to low textures array, there is no number of entries though
	CTRLEVPtr<CTRLEVPtr<u32, u32>, u32>ptrLowTexArray;

	// 0xD8
	// base background color, used to clear the screen
	type::RGBA8 clearColorRGBA;

	// 0xDC
	// toggles some level stuff
	// & 1 = enables glowGradient skybox gradients
	// & 2 = mask grab when underwater
	// & 4 = toggles between water and animated vertices?
	u32 configFlags;

	// 0xE0
	// pointer to string, date, assumed bsp compilation start
	u32 PTRstring_build_start;

	// 0xE4
	// pointer to string, date, assumed bsp compilation end
	u32 PTRstring_build_end;

	// 0xE8
	// pointer to string, assumed build type
	u32 PTRstring_build_type;

	// 0xEC
	s8 unk_EC[0x18];

	// 0x104
	// used for rain and snow
	RainBuffer rainBuff;

	// 0x134
	CTRLEVPtr<u32, u32>ptrSpawnType1;

	// spawn_arrays2 is for things
	// like Seal, Minecart, etc,
	// series of positions (only positions)

	// 0x138
	s32 numSpawnType2;

	// 0x13C
	CTRLEVPtr<u32, u32>ptrSpawnType2;

	// spawn_arrays is for things
	// N Gin Labs barrel, Snowball,
	// series of positions and rotations

	// 0x140
	s32 numSpawnType2_PosRot;

	// 0x144
	CTRLEVPtr<u32, u32>ptrSpawnType2_PosRot;

	// restart_points is for respawning
	// driver on track after falling off

	// 0x148
	s32 cnt_restart_points;

	// 0x14C
	CTRLEVPtr<u32, u32>ptr_restart_points;

	// 0x150
	s8 unk_150[0x10];

	// 0x160
	// for gradient clears
	BackgroundColor clearColor[3];

	// 0x16C
	s32 unk_16C;

	// 0x170
	s32 unk_170;

	// 0x174
	s32 numSCVert;

	// 0x178
	CTRLEVPtr<u32, u32>ptrSCVert;

	// 0x17c - 0x182
	s8 unkStarData[8];

	// split-lines
	// for ice, mud, water
	// 0x184
	// 0x186
	s8 splitLines[4];

	// 0x188
	u32 PTRtoPTR_LevNavHeader;

	// 0x18C
	// used in FUN_80060630
	s32 unk_18C;

	// 0x190
	CTRLEVPtr<u32, u32>visMem;
	
	s8 footer[0x60];
};

Level LevelHeader @ 0x4;

struct QuadBlockSection
{
	CTRLEVPtr<u32, u32> ptr_texture_mid[4];
	CTRLEVPtr<u32, u32> ptr_texture_low;
	CTRLEVPtr<PVS, u32> pvs;
};

fn format_mapNumPtrs(u32 mapNumPtrs)
{
	u32 numQB @ addressof(LevelHeader.ptr_mesh_info.data);
	u32 mapPtrsTotal = mapNumPtrs >> 2;
	u32 mapPtrsGeneralSectionNum = ((mapNumPtrs - ((numQB*6)<<2))>>2);
	return std::format
	(
		"General: {0} | QuadBlock: {2} ({1} QuadBlocks) | Total: {3}",
		mapPtrsGeneralSectionNum, numQB, numQB*6, mapPtrsTotal
	);
};

struct Map
{
	u32 mapNumPtrs [[format("format_mapNumPtrs")]];

	u32 numQB @ addressof(LevelHeader.ptr_mesh_info.data) [[hidden]];
	u32 mapPtrsGeneralSectionNum = ((this.mapNumPtrs - ((numQB*6)<<2))>>2);

	CTRLEVPtr<u32, u32> mapPtrsGeneralSection[this.mapPtrsGeneralSectionNum];
	QuadBlockSection mapPtrsQuadBlockSection[numQB];
};

CTRLEVPtr<Map, u32> ptrMap @ 0x0;
QuadBlock quadBlockArray[LevelHeader.ptr_mesh_info.data.numQuadBlock] @ addressof(LevelHeader.ptr_mesh_info.data.ptrQuadBlockArray.data);
LevVertex levVertexArray[LevelHeader.ptr_mesh_info.data.numVertex] @ addressof(LevelHeader.ptr_mesh_info.data.ptrVertexArray.data);
//AnimTex anim_tex_array[?] @ addressof(LevelHeader.ptr_anim_tex.data);
