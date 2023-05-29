#include <std/string.pat>
#include <std/ptr.pat>
#include <std/array.pat>
#include <type/types/c.pat>

// CTR: Crash Team Racing level files
// author Superstarxalien

#pragma eval_depth 512+256

struct BoundingBox
{
    std::Array<s16, 0x3> min;
    std::Array<s16, 0x3> max;
};

struct PVS
{
    std::ptr::NullablePtr<int, u32> visLeafSrc;
    std::ptr::NullablePtr<int, u32> visFaceSrc;
    std::ptr::NullablePtr<u32, u32> PTRtoPTR_visInstSrc;
    
    // either OVert or SCVert
    std::ptr::NullablePtr<int, u32> visExtraSrc;
};

struct LevVertex
{
    // 0x0
    std::Array<s16, 3> pos;
    
    // 0x6
    // FUN_8001ef50
    u16 flags;

    // 0x8
    std::Array<u8, 4> color_hi;

    // 0xC
    std::Array<u8, 4> color_lo;

    // 0x10 bytes large
};

struct QuadBlock
{
    // 0x0
    std::Array<s16, 9> index;

    // 0x12
    u16 quadFlags;

    // 0x14
    int draw_order_low; // actually for med

    // 0x18
    int draw_order_high;

    // 0x1c
    // ptr_texture_mid can point to IconGroup3, IconGroup4, or AnimTex structs
    std::ptr::NullablePtr<u32, u32> ptr_texture_mid_1;
    std::ptr::NullablePtr<u32, u32> ptr_texture_mid_2;
    std::ptr::NullablePtr<u32, u32> ptr_texture_mid_3;
    std::ptr::NullablePtr<u32, u32> ptr_texture_mid_4;

    // 0x2c
    BoundingBox bbox;

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
    // ptr_texture_low can also point to IconGroup3, IconGroup4, or AnimTex structs
    std::ptr::NullablePtr<u32, u32> ptr_texture_low;

    // 0x44
    std::ptr::NullablePtr<PVS, u32> pvs;

    // 0x48
    // explained in FUN_8001f2dc
    std::Array<s16, 10> triNormalVecDividend;

    // full struct is 0x5c bytes large
};

struct BSPbranch
{
    // 0x10
    // x, y, z, [?]
    std::Array<s16, 4> axis;

    // 0x18
    // leftChildID, rightChildID, [?], [?]
    std::Array<s16, 4> childID;
};

struct BSPleaf
{
    // 0x10
    int unk1;
    
    // 0x14
    // the code keeps looping through the 
    // array until it finds a 4-byte 0x00000000
    // to determine end of list
    std::ptr::NullablePtr<u32, u32> bspHitboxArray;

    // 0x18
    int numQuads;

    // 0x1C
    std::ptr::NullablePtr<QuadBlock, u32> ptrQuadBlockArray;
};

struct BSPhitbox
{
    // 0x10
    std::Array<s16, 6> unkShort;
    // see FUN_8001d0c4
    
    // 0x1C
    // These are always InstDef, not converted to Instance
    std::ptr::NullablePtr<u32, u32> PTRplaceholder_instDef;
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
    std::ptr::NullablePtr<QuadBlock, u32> ptrQuadBlockArray;

    // 0x10
    std::ptr::NullablePtr<LevVertex, u32> ptrVertexArray;

    // 0x14
    int unk2;

    // 0x18
    std::ptr::NullablePtr<BSP, u32> bspRoot;

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
  std::Array<s8, 0x10> unk_4;

  // 0x18 (0x1a58)
  std::Array<s16, 0x3> cameraPos;

  // 0x1E
  s16 unk_22;

  // 0x20
  // controls top color of particles
  u32 colorRGBA_top;

  // 0x24
  // controls bottom color of particles
  u32 colorRGBA_bottom;

  // 0x28
  // controls how particles are drawn
  std::Array<s32, 0x2> renderMode;

  // 0x30 -- size of struct

};

struct Gradient
{
    s16 pointFrom;
    s16 pointTo;

    // RGBA
    u32 colorFrom;
    u32 colorTo;
};

struct Spawn
{
    std::Array<s16, 0x3> pos;
    std::Array<s16, 0x3> rot;
};

struct BackgroundColor
{
    std::Array<s8, 0x3> rgb;
    s8 enable;
};

struct Level
{
    // 0x0
    // pos32er to mesh info
    std::ptr::NullablePtr<mesh_info, u32> ptr_mesh_info;

    // 0x4
    // pos32er to skybox (struct not yet known)
    std::ptr::NullablePtr<u32, u32> ptr_skybox;

    // 0x8
    // pos32er to animated textures array
    u32 PTR_ptr_anim_tex;

    // 0xc
    // number of model instances in the level
    // (i.e. every single box, fruit, etc.)
    u32 numInstances;

    // 0x10
    // pos32s to the 1st entry of the array of model instances (?)
    // each entry in the array is 0x40 bytes large
    u32 PTR_ptrInstDefs;

    // 0x14
    // number of actual models
    u32 numModels;

    // 0x18
    // pos32er to the array of pos32ers to models
    u32 PTRtoPTR_ptrModelsPtrArray;

    // 0x1c
    // unknown, extra bsp region
    u32 PTR_unk3;

    // 0x20
    // unknown, extra bsp region
    u32 PTR_unk4;

    // 0x24
    // pos32er to the array of pos32ers to model instances (?)
    // converts back and forth, Instance to InstDef
    u32 PTRtoPTR_ptrInstDefPtrArray;

    // 0x28
    // unknown, extra bsp region
    // related to water?
    u32 PTR_unk5;

    // 0x2c
    // assumed to be reserved
    u32 PTR_null1;

    // 0x30
    // assumed to be reserved
    u32 PTR_null2;

    // 0x34
    // number of vertices treated as water
    s32 count_water;

    // 0x38
    // pos32er to array of water entries
    u32 PTR_ptr_water;

    // 0x3c
    // leads to the icon pack header
    u32 PTR_ptr_named_tex;

    // 0x40
    // leads to the icon pack data
    u32 PTR_ptr_named_tex_array;

    // 0x44
    // pos32er to environment map, used by water rendering
    u32 PTR_ptr_tex_waterEnvMap;

    // 0x48
    // used for additional skybox gradients (e.g. papu's pyramid)
    std::Array<Gradient, 0x3> glowGradient;

    // 0x6c
    // array of 8 starting locations
    std::Array<Spawn, 0x8> DriverSpawn;

    // 0xCC -- next
    // unknown, extra bsp regions
    u32 PTR_unk_Lev_CC;
    u32 PTR_unk_Lev_D0;

    // 0xD4
    // assumed to be a pos32er to low textures array, there is no number of entries though
    u32 PTR_ptrLowTexArray;

    // 0xD8
    // base background color, used to clear the screen
    u32 clearColorRGBA;

    // 0xDC
    // toggles some level stuff
    // & 1 = enables glowGradient skybox gradients
    // & 2 = mask grab when underwater
    // & 4 = toggles between water and animated vertices?
    u32 configFlags;

    // 0xE0
    // pos32er to string, date, assumed bsp compilation start
    u32 PTRstring_build_start;

    // 0xE4
    // pos32er to string, date, assumed bsp compilation end
    u32 PTRstring_build_end;

    // 0xE8
    // pos32er to string, assumed build type
    u32 PTRstring_build_type;

    // 0xEC
    std::Array<s8, 0x18> unk_EC;

    // 0x104
    // used for rain and snow
    RainBuffer rainBuff;

    // 0x134
    u32 PTR_ptrSpawnType1;

    // spawn_arrays2 is for things
    // like Seal, Minecart, etc,
    // series of positions (only positions)

    // 0x138
    s32 numSpawnType2;

    // 0x13C
    u32 PTR_ptrSpawnType2;

    // spawn_arrays is for things
    // N Gin Labs barrel, Snowball,
    // series of positions and rotations

    // 0x140
    s32 numSpawnType2_PosRot;

    // 0x144
    u32 PTR_ptrSpawnType2_PosRot;

    // restart_pos32s is for respawning
    // driver on track after falling off

    // 0x148
    s32 cnt_restart_pos32s;

    // 0x14C
    u32 PTR_ptr_restart_pos32s;

    // 0x150
    std::Array<s8, 0x10> unk_150;

    // 0x160
    // for gradient clears
    std::Array<BackgroundColor, 0x3> clearColor;

    // 0x16C
    s32 unk_16C;

    // 0x170
    s32 unk_170;

    // 0x174
    s32 numSCVert;

    // 0x178
    u32 PTR_ptrSCVert;

    // 0x17c - 0x182
    std::Array<s8, 0x8> unkStarData;

    // split-lines
    // for ice, mud, water
    // 0x184
    // 0x186
    std::Array<s8, 0x4> splitLines;

    // 0x188
    u32 PTRtoPTR_LevNavHeader;

    // 0x18C
    // used in FUN_80060630
    s32 unk_18C;

    // 0x190
    u32 PTR_visMem;
    
    std::Array<s8, 0x60> footer;
};

u32 ptrMap @ 0x0;
Level LevelHeader @ 0x4;