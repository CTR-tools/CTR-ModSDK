#include <common.h>

void ConvertRotToMatrix(MATRIX* m, short* rot);

// Camera110_SetViewMatrix -- CameraMatrix, and ViewProj
void DECOMP_Camera110_SetViewMatrix(struct Camera110* c110)
{
  // ViewProj used for tracks

  #define uint unsigned int

  // CameraMatrix
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  short sVar7;

  uint view0;
  uint view4;
  uint view8;
  uint viewC;

  int tx;
  int ty;
  int tz;

  // camera110 rotation
  *(short*)0x1f8003f4 = c110->rot[0];
  *(short*)0x1f8003f6 = c110->rot[1];
  *(short*)0x1f8003f8 = c110->rot[2];

  // make rotation matrix for camera's view matrix
  ConvertRotToMatrix((MATRIX *)0x1f8003d4, (short *)0x1f8003f4);

  tx = c110->pos[0];
  ty = c110->pos[1];
  tz = c110->pos[2];

// gte_SetLightMatrix
#define gte_r8(r0) __asm__ volatile("ctc2   %0, $8" : : "r"(r0))
#define gte_r9(r0) __asm__ volatile("ctc2   %0, $9" : : "r"(r0))
#define gte_r10(r0) __asm__ volatile("ctc2   %0, $10" : : "r"(r0))
#define gte_r11(r0) __asm__ volatile("ctc2   %0, $11" : : "r"(r0))
#define gte_r12(r0) __asm__ volatile("ctc2   %0, $12" : : "r"(r0))

  // CameraMatrix
  uVar3 = *(int*)0x1f8003d4;
  uVar4 = *(int*)0x1f8003d8;
  uVar5 = *(int*)0x1f8003dc;
  uVar6 = *(int*)0x1f8003e0;
  sVar7 = *(short*)0x1f8003e4;

  // CameraMatrix, for shadows, particles, and audio
  *(int*)((int)&c110->matrix_Camera + 0x0) = uVar3;
  *(int*)((int)&c110->matrix_Camera + 0x4) = uVar4;
  *(int*)((int)&c110->matrix_Camera + 0x8) = uVar5;
  *(int*)((int)&c110->matrix_Camera + 0xC) = uVar6;
  *(short*)((int)&c110->matrix_Camera + 0x10) = sVar7;
  c110->matrix_Camera.t[0] = tx;
  c110->matrix_Camera.t[1] = ty;
  c110->matrix_Camera.t[2] = tz;

  // transpose the camera matrix
  view0 = uVar3 & 0xffff | uVar4 & 0xffff0000;
  view4 = uVar6 & 0xffff | uVar3 & 0xffff0000;
  view8 = uVar5 & 0xffff | uVar6 & 0xffff0000;
  viewC = uVar4 & 0xffff | uVar5 & 0xffff0000;

  // load transpose camera matrix
  // similar to gte_SetLightMatrix
  gte_r8(view0);
  gte_r9(view4);
  gte_r10(view8);
  gte_r11(viewC);
  gte_r12(sVar7);

  // load inverted camera position
#define gte_ldVXY0(r0) 	__asm__ volatile("mtc2   %0, $0" : : "r"(r0))
#define gte_ldVZ0(r0) 	__asm__ volatile("mtc2   %0, $1" : : "r"(r0))
  gte_ldVXY0(-tx & 0xffff | -ty * 0x10000);
  gte_ldVZ0(-tz);

  // multiply inverted camera position, 
  // by transpose camera matrix
  gte_llv0();

  // get the result
#define read_mt(r0, r1, r2) 	__asm__ volatile( \
	"mfc2   %0, $25;"  \
	"mfc2   %1, $26;"  \
	"mfc2   %2, $27;"  \
	: : "r"(r0), "r"(r1), "r"(r2))
  read_mt(tx,ty,tz);

  // start with transpose camera matrix
  *(int*)((int)&c110->matrix_ViewProj + 0x0) = view0;
  *(int*)((int)&c110->matrix_ViewProj + 0x4) = view4;
  *(int*)((int)&c110->matrix_ViewProj + 0x8) = view8;
  *(int*)((int)&c110->matrix_ViewProj + 0xC) = viewC;
  *(short*)((int)&c110->matrix_ViewProj + 0x10) = sVar7;

  // NTSC:
  // 0x360/0x600 = 9/16 aspect,
  // 9/16 * 512/216 = 4/3

  // PAL:
  // 0x3B0/0x600 = 59/96 aspect,
  // 59/96 * 512/236 = 4/3

  // NTSC widescreen:
  // 0x360 for 4:3, 0x480 for 16:9
  
  // dynamic numerator
  #if BUILD == EurRetail
  #define r360 0x3B0
  #else
  #define r360 0x360
  #endif
  
  // constant denomenator
  #define r600 0x600

  // scale position
  c110->matrix_ViewProj.t[0] = tx;
  c110->matrix_ViewProj.t[1] = (ty * r360) / r600;
  c110->matrix_ViewProj.t[2] = tz;

  // scale Y axis (1)
  c110->matrix_ViewProj.m[1][0] =
  c110->matrix_ViewProj.m[1][0] * r360 / r600;

  // scale Y axis (2)
  c110->matrix_ViewProj.m[1][1] =
  c110->matrix_ViewProj.m[1][1] * r360 / r600;

  // scale Y axis (3)
  c110->matrix_ViewProj.m[1][2] =
  c110->matrix_ViewProj.m[1][2] * r360 / r600;

  // store camera matrix,
  // otherwise oxide intro cutscene bugs out,
  // when crash is sleeping on the grassy hill
  gte_r8 (uVar3);
  gte_r9 (uVar4);
  gte_r10(uVar5);
  gte_r11(uVar6);

  return;
}