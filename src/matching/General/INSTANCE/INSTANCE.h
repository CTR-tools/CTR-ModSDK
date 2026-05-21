// =============================================================
// Shared types for matching/General/INSTANCE/*.c
//
// Struct shapes are taken from src/decompile/include/namespace_Instance.h.
// Each .c file in this subdir is built standalone for the permuter, so
// this header avoids nested includes.
// =============================================================

#ifndef MATCHING_INSTANCE_H
#define MATCHING_INSTANCE_H

// ---- primitive type aliases (per coding-standards.md) ----

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed int     s32;
typedef signed short   s16;
typedef signed char    s8;

// ---- forward declarations ----

struct Thread;
struct InstDef;
struct TextureLayout;
struct AnimTex;

// ---- ModelFrame (namespace_Instance.h) ----

struct ModelFrame
{
    // 0x0
    s16 pos[4];

    char unk16[16];

    // 0x18 -- always 0x1C
    s32 vertexOffset;
};

// ---- ModelAnim (namespace_Instance.h) ----

struct ModelAnim
{
    // 0x0
    char name[0x10];

    // 0x10
    u16 numFrames;

    // 0x12
    s16 frameSize;

    // 0x14 -- delta array for compressed anims, null otherwise
    u32* ptrDeltaArray;

    // 0x18 -- ModelFrame stream begins here
};

// ---- ModelHeader (namespace_Instance.h) ----

struct ModelHeader
{
    // 0x0
    char name[0x10];

    // 0x10
    s32 unk1;

    // 0x14
    s16 maxDistanceLOD;

    // 0x16
    u16 flags;

    // 0x18
    s16 scale[4];

    // 0x20
    u32 ptrCommandList;

    // 0x24
    struct ModelFrame* ptrFrameData;

    // 0x28
    struct TextureLayout** ptrTexLayout;

    // 0x2C
    u32* ptrColors;

    // 0x30
    u32 unk3;

    // 0x34
    u32 numAnimations;

    // 0x38
    struct ModelAnim** ptrAnimations;

    // 0x3C
    struct AnimTex* animtex;
};

// ---- Model (namespace_Instance.h) ----

struct Model
{
    // 0x0
    char name[0x10];

    // 0x10
    s16 id;

    // 0x12
    s16 numHeaders;

    // 0x14
    struct ModelHeader* headers;
};

// ---- Instance (namespace_Instance.h, partial) ----
//
// Only the offsets touched by functions in this subdir are spelled out.
// The rest is left as raw padding so layout stays byte-compatible.

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

    // 0x1C
    s16 scale[3];

    // 0x22
    s16 alphaScale;

    // 0x24
    u32 colorRGBA;

    // 0x28
    u32 flags;

    // 0x2C
    struct InstDef* instDef;
};

#endif // MATCHING_INSTANCE_H
