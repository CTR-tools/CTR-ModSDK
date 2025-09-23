#pragma once

#include <ctr/macros.h>
#include <ctr/math.h>

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

typedef struct Vertex
{
    SVec3 pos;
    u16 flags;
    Color colorHi;
    Color colorLo;
} Vertex;