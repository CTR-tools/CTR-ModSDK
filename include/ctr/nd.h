#ifndef ND_H
#define ND_H

#include <ctr/macros.h>
#include <ctr/math.h>

void ND_Music_SetIntro();
void ND_LOAD_XnfFile(char* filename, u32 address, char* dummy);
s32 ND_SquareRoot0_stub(s32 n);
s32 ND_MATH_VectorLength(const SVec3* vector);
int ND_printf(const char* format, ...);

#endif