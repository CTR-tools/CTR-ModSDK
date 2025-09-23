#pragma once

#include <ctr/macros.h>
#include <ctr/math.h>

typedef struct Color
{
	uint32_t r : 8;
	uint32_t g : 8;
	uint32_t b : 8;
	uint32_t a : 8;
} Color;

typedef struct Vertex
{
    SVec3 pos;
    u16 flags;
    Color colorHi;
    Color colorLo;
} Vertex;