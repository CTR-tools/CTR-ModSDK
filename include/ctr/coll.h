#pragma once

#include <ctr/macros.h>
#include <ctr/math.h>
#include <ctr/lev.h>

typedef enum Axis
{
    AXIS_Z = 1,
    AXIS_X = 2,
    AXIS_Y = 3,
} Axis;

typedef enum BarycentricTest
{
    BARYCENTRIC_TEST_INVALID = -1,
    BARYCENTRIC_TEST_SNAP_V1 = 0,
    BARYCENTRIC_TEST_EDGE_V1_V2 = 1,
    BARYCENTRIC_TEST_SNAP_V2 = 2,
    BARYCENTRIC_TEST_EDGE_V2_V3 = 3,
    BARYCENTRIC_TEST_SNAP_V3 = 4,
    BARYCENTRIC_TEST_EDGE_V1_V3 = 5,
    BARYCENTRIC_TEST_INSIDE_TRIANGLE = 6,
} BarycentricTest;

typedef enum CollFlags
{
    COLLFLAGS_TEST_INSTANCES = 0x1,
    COLLFLAGS_HIGH_LOD_QUAD = 0x2,
    COLLFLAGS_CACHED_HIGH_LOD_VERTICES = 0x8,
} CollFlags;

typedef struct CollVertex
{
    SVec3 pos;
    u16 normalDominantAxis;
    const Vertex* levVertex;
    SVec3 triNormal;
    s16 planeDist;
} CollVertex;

typedef struct TestVertex
{
    SVec3 pos;
    u16 normalDominantAxis;
    SVec3 triNormal;
    s16 planeDist;
    SVec3 interpolationPoint;
} TestVertex;

typedef struct DriverQuadblockCollData
{
    SVec3 driverPos;
    s16 driverHitRadius;
    s32 driverHitRadiusSquared;
    SVec3 driverNextPos;
    u16 collFlags;
    u32 quadFlagsCheckColl;
    u32 quadFlagsIgnoreColl;
} DriverQuadblockCollData;

typedef union CollInputData
{
    DriverQuadblockCollData quadblock;
} CollInputData;

typedef struct CollDCache
{
    SVec3 inputNextPos;
    s16 inputHitRadius;
    s32 inputHitRadiusSquared;
    s16 unk0;
    s16 unk1;
    CollInputData collInput;
    const MeshInfo* meshInfo;
    BoundingBox bbox;
    s16 numVerticesTested;
    s16 numTrianglesCollided;
    s16 unk2;
    s16 numInstancesCollided;
    u32 unk3;
    const BSPNode* bspNodes;
    TestVertex collIntersection;
    u8 unk4;
    u8 currTriangleIndex;
    const Quadblock* currQuadblock;
    TestVertex coll;
    s8 barycentricTest;
    u8 collidedTriangleIndex;
    const Quadblock* collidedQuadblock;
    s32 speedScale;
    u8 unk6[0x44];
    const Vertex* collidedVertices[NUM_VERTICES_TRIANGLE];
    const CollVertex* currTestVertices[NUM_VERTICES_TRIANGLE];
    SVec3 deltaInterpolationIntersection;
    s16 unk7;
    u16 quadblockThirdIndex;
    u16 quadblockFourthIndex;
    CollVertex quadblockCollVertices[NUM_VERTICES_QUADBLOCK];
    u32 stepFlags;
    s16 normalScale;
    u8 normalBitshift;
    u8 lodShift;
} CollDCache;

#define DCACHE_COLL (*(CollDCache*) 0x1f800108)

void COLL_TestLeaf_Quadblock(const Quadblock* quadblock, CollDCache* cache);

extern u32 e_ignoreCollisionDoorFlagTerrain; // 0x8008d728