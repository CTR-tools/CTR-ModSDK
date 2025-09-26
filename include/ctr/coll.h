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

typedef struct CollVertex
{
    SVec3 pos;
    u16 normalDominantAxis;
    const Vertex* levVertex;
    SVec3 triNormal;
    u16 planeDist;
} CollVertex;

typedef struct TestVertex
{
    SVec3 pos;
    u16 normalDominantAxis;
    SVec3 triNormal;
    u16 planeDist;
    SVec3 interpolationPoint;
} TestVertex;

typedef struct DriverQuadblockCollData
{
    SVec3 driverPos;
    s16 driverHitRadius;
    s32 driverHitRadiusSquared;
    SVec3 driverNextPos;
    u16 collFlags;
    u16 searchFlags;
    s16 unk0;
    u32 skipCollNoQuadFlagsMatch;
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
    MeshInfo* meshInfo;
    BoundingBox bbox;
    s16 numVerticesTested;
    s16 numTrianglesTouched;
    s16 unk2;
    s16 numInstancesCollided;
    u32 unk3;
    BSPNode* bspNodes;
    TestVertex collIntersection;
    u8 unk4;
    u8 currTriangleIndex;
    Quadblock* currQuadblock;
    SVec3 collPos;
    u16 normalDominantAxis_TriCollided;
    SVec3 normalTriCollided;
    s16 unk5;
    SVec3 interpolationPoint;
    u8 barycentricTest;
    u8 collidedTriangleIndex;
    Quadblock* collidedQuadblock;
    s32 speedScale;
    u8 unk6[0x44];
    Vertex* collidedVertices[NUM_VERTICES_TRIANGLE];
    CollVertex* currTestVertices[NUM_VERTICES_TRIANGLE];
    SVec3 distInterpolationIntersection;
    s16 unk7;
    u16 quadblockThirdIndex;
    u16 quadblockFourthIndex;
    CollVertex quadblockCollVertices[NUM_VERTICES_QUADBLOCK];
    u32 stepFlags;
    s16 normalScale;
    u8 normalBitshift;
    u8 lodShift;
} CollDCache;

#define DCACHE_COLL (*(CollDCache*) 0x1f800000)

void COLL_ProjectPointToEdge(SVec3* out, const SVec3* v1, const SVec3* v2, const SVec3* point);
void COLL_LoadQuadblockData_LowLOD(CollDCache* cache, Quadblock* quadblock);
void COLL_LoadQuadblockData_HighLOD(CollDCache* cache, Quadblock* quadblock);
s32 COLL_BarycentricTest(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3);