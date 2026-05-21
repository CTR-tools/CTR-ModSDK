// =============================================================
// Shared types for matching/General/COLL/*.c
//
// Struct shapes are taken from src/decompile/include/namespace_Coll.h
// and src/decompile/include/namespace_Level.h. Each .c file in this
// subdir is built standalone for the permuter, so this header avoids
// nested includes and only forward-declares what the functions need.
// =============================================================

#ifndef MATCHING_COLL_H
#define MATCHING_COLL_H

// ---- primitive type aliases (per coding-standards.md) ----

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed int     s32;
typedef signed short   s16;
typedef signed char    s8;

// ---- forward declarations ----

struct InstDef;
struct Instance;
struct QuadBlock;

// ---- bounding box (namespace_Coll.h offset 0x0, size 0xC) ----

struct BoundingBox
{
    s16 min[3];
    s16 max[3];
};

// ---- BSP node (namespace_Level.h, size 0x20) ----

struct BSP
{
    // 0x0
    u16 flag;

    // 0x2
    s16 id;

    // 0x4
    struct BoundingBox box;

    // 0x10
    // tagged by flag: 0 = branch, 1 = leaf, otherwise hitbox
    union
    {
        struct
        {
            // 0x10
            s16 axis[4];

            // 0x18
            s16 childID[4];

        } branch;

        struct
        {
            // 0x10
            s32 unk1;

            // 0x14
            // null-terminated array of hitbox BSPs
            struct BSP* bspHitboxArray;

            // 0x18
            s32 numQuads;

            // 0x1C
            struct QuadBlock* ptrQuadBlockArray;

        } leaf;

        struct
        {
            // 0x10
            s16 unkShort[6];

            // 0x1C
            struct InstDef* instDef;

        } hitbox;

    } data;
};

// ---- BspSearchTriangle (namespace_Coll.h, size 0xC) ----

struct BspSearchTriangle
{
    struct QuadBlock* quadblock;
    s32 triangleID;
    s32 numCollision;
};

// ---- ScratchpadStruct (namespace_Coll.h, size 0x20C) ----
// Stored at 0x1F800108 in scratchpad RAM.

struct ScratchpadStruct
{
    char pad00[0x30];

    // 0x30
    struct BoundingBox bbox;

    char pad3C[0x88 - 0x3C];

    // 0x88
    struct BSP* bspInstHitboxArr[15];

    // 0xC4
    s32 numInstHitboxesHit;

    char padC8[0x20C - 0xC8];
};

// ---- ScratchpadStructExtended (namespace_Coll.h) ----
// Lives only in scratchpad. Used by FUN_80020334 (COLL_MOVED_FindScrub).

struct ScratchpadStructExtended
{
    // 0x0
    struct ScratchpadStruct scratchpadStruct;

    // 0x20C
    struct BspSearchTriangle bspSearchTriangle[15];

    // 0x2C0
    s32 numTriangles;
};

#endif // MATCHING_COLL_H
