#pragma once

#include <ctr/macros.h>
#include <ctr/math.h>
#include <ctr/prim.h>

#define NUM_VERTICES_QUADBLOCK 9
#define NUM_VERTICES_TRIANGLE 3

typedef union Color
{
    struct
    {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    };
    u32 color;
} Color;

typedef struct TextureLayout
{
    UV uv0;
    CLUT clut;
    UV uv1;
    PolyTexpage texpage;
    UV uv2;
    UV uv3;
} TextureLayout;

typedef struct TextureGroup
{
	TextureLayout far;
	TextureLayout middle;
	TextureLayout near;
	TextureLayout mosaic;
} TextureGroup;

typedef struct Vertex
{
    SVec3 pos;
    u16 flags;
    Color colorHi;
    Color colorLo;
} Vertex;

typedef struct VisibleSet
{
	u32* visibleBSPNodes;
	u32* visibleQuadblocks;
	u32* visibleInstances;
	u32* visibleExtra;
} VisibleSet;

typedef struct Quadblock
{
	u16 index[NUM_VERTICES_QUADBLOCK]; // 0x0
	u16 flags; // 0x12
	u32 drawOrderLow; // 0x14
	u32 drawOrderHigh; // 0x18
	u32 offMidTextures[4]; // 0x1C
	BoundingBox bbox; // 0x2C
	u8 terrain; // 0x38
	u8 weatherIntensity; // 0x39
	u8 weatherVanishRate; // 0x3A
	s8 speedImpact; // 0x3B
	u16 id; // 0x3C
	u8 checkpointIndex; // 0x3E
	u8 triNormalVecBitshift; // 0x3F
	u32 offLowTexture; // 0x40
	VisibleSet visibleSet; // 0x44
	u16 triNormalVecDividend[NUM_VERTICES_QUADBLOCK + 1]; // 0x48
} Quadblock;

typedef struct BSPBranch
{
	u16 flags; // 0x0
	u16 id; // 0x2
	BoundingBox bbox; // 0x4
	SVec3 axis; // 0x10
	u16 likelyPadding; // 0x16
	u16 leftChildID; // 0x18
	u16 rightChildID; // 0x1A
	u16 unk1; // 0x1C
	u16 unk2; // 0x1E
} BSPBranch;

typedef struct BSPLeaf
{
	u16 flags; // 0x0
	u16 id; // 0x2
	BoundingBox bbox; // 0x4
	u32 likelyPadding; // 0x10
	u32 offHitbox; // 0x14
	u32 numQuads; // 0x18
	Quadblock* quadblocks; // 0x1C
} BSPLeaf;

typedef union BSPNode
{
    BSPBranch branch;
    BSPLeaf leaf;
} BSPNode;

typedef struct MeshInfo
{
	u32 numQuadblocks; // 0x0
	u32 numVertices; // 0x4
	u32 unk1; // 0x8
	Quadblock* quadblocks; // 0xC
	Vertex* vertices; // 0x10
	u32 unk2; // 0x14
	BSPNode* bspNodes; // 0x18
	u32 numBSPNodes; // 0x1C
} MeshInfo;