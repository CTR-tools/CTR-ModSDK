#include <common.h>

void ConvertRotToMatrix(MATRIX* m, short* rot);

// TileView_SetMatrixVP -- CameraMatrix, and ViewProj
void DECOMP_TileView_SetMatrixVP(struct TileView* tileView)
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

  // tileView rotation
  *(short*)0x1f8003f4 = tileView->rot[0];
  *(short*)0x1f8003f6 = tileView->rot[1];
  *(short*)0x1f8003f8 = tileView->rot[2];

  // make rotation matrix for camera's view matrix
  ConvertRotToMatrix((MATRIX *)0x1f8003d4, (short *)0x1f8003f4);

  tx = tileView->pos[0];
  ty = tileView->pos[1];
  tz = tileView->pos[2];

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
  *(int*)((int)&tileView->matrix_Camera + 0x0) = uVar3;
  *(int*)((int)&tileView->matrix_Camera + 0x4) = uVar4;
  *(int*)((int)&tileView->matrix_Camera + 0x8) = uVar5;
  *(int*)((int)&tileView->matrix_Camera + 0xC) = uVar6;
  *(short*)((int)&tileView->matrix_Camera + 0x10) = sVar7;
  tileView->matrix_Camera.t[0] = tx;
  tileView->matrix_Camera.t[1] = ty;
  tileView->matrix_Camera.t[2] = tz;

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
  *(int*)((int)&tileView->matrix_ViewProj + 0x0) = view0;
  *(int*)((int)&tileView->matrix_ViewProj + 0x4) = view4;
  *(int*)((int)&tileView->matrix_ViewProj + 0x8) = view8;
  *(int*)((int)&tileView->matrix_ViewProj + 0xC) = viewC;
  *(short*)((int)&tileView->matrix_ViewProj + 0x10) = sVar7;

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
  tileView->matrix_ViewProj.t[0] = (tx * 600) / 1000;
  tileView->matrix_ViewProj.t[1] = (ty * r360) / r600;
  tileView->matrix_ViewProj.t[2] = tz;
  
#if 1 
  // Y axis is already scaled 512/216 x 0x360/0x600 -> 4x3
  // X axis correction for 16x9 must be 9/16 x 4/3 -> 0.75
  // 16x9 is 0.75, 20x9 is 0.6, etc
  
  // 600 / 1000 for 20x9
  // 750 / 1000 for 16x9
  
  // adjustin m[0][0] will work on Roo's Tubes spawn
  // will break everywhere else, need more
  
  tileView->matrix_ViewProj.m[0][0] =
  tileView->matrix_ViewProj.m[0][0] * 600 / 1000;
  
  tileView->matrix_ViewProj.m[0][1] =
  tileView->matrix_ViewProj.m[0][1] * 600 / 1000;
  
  tileView->matrix_ViewProj.m[0][2] =
  tileView->matrix_ViewProj.m[0][2] * 600 / 1000;
#endif

  // scale Y axis (1)
  tileView->matrix_ViewProj.m[1][0] =
  tileView->matrix_ViewProj.m[1][0] * r360 / r600;

  // scale Y axis (2)
  tileView->matrix_ViewProj.m[1][1] =
  tileView->matrix_ViewProj.m[1][1] * r360 / r600;

  // scale Y axis (3)
  tileView->matrix_ViewProj.m[1][2] =
  tileView->matrix_ViewProj.m[1][2] * r360 / r600;

  // store camera matrix,
  // otherwise oxide intro cutscene bugs out,
  // when crash is sleeping on the grassy hill
  gte_r8 (uVar3);
  gte_r9 (uVar4);
  gte_r10(uVar5);
  gte_r11(uVar6);

  return;
}