// =============================================================
// Shared types for matching/General/UI/*.c
//
// Struct shapes are taken from src/decompile/include/namespace_UI.h.
// Each .c file in this subdir is built standalone for the permuter, so
// this header avoids nested includes.
// =============================================================

#ifndef MATCHING_UI_H
#define MATCHING_UI_H

// ---- primitive type aliases (per coding-standards.md) ----

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed int     s32;
typedef signed short   s16;
typedef signed char    s8;

// ---- forward declarations ----

struct Driver;

// ---- UiElement2D (namespace_UI.h, size 0x8) ----

struct UiElement2D
{
    s16 x;
    s16 y;
    s16 z;
    s16 scale;
};

// ---- UiElement3D (namespace_UI.h, size 0x38) ----
// MATRIX is laid out as s16 m[3][3], s16 pad, s32 t[3] (size 0x20).

struct UiMatrix
{
    s16 m[3][3];
    s16 pad;
    s32 t[3];
};

struct UiElement3D
{
    // 0x0
    s16 rot[4];

    // 0x8
    struct UiMatrix m;

    // 0x28
    s16 lightDir[4];

    // 0x30
    s16 vel[4];
};

#endif // MATCHING_UI_H
