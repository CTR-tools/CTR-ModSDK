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
    Vertex* levVertex;
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

void COLL_ProjectPointToEdge(SVec3* out, const SVec3* v1, const SVec3* v2, const SVec3* point);
s32 COLL_BarycentricTest(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3);