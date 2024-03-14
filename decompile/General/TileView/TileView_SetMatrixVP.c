#include <common.h>

#ifdef REBUILD_PC
static char buf[0x400];
#endif

// TileView_SetMatrixVP -- CameraMatrix, and ViewProj
void DECOMP_TileView_SetMatrixVP(struct TileView* tileView)
{
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

  #ifdef REBUILD_PC
  char* scratchpad;
  scratchpad = &buf[0];
  #endif

  // originally used 556 bytes

  #ifdef REBUILD_PC
  // Windows x86_64, use global scratchpad
  MATRIX* matrixDST = &scratchpad[0x3d4];
  #else
	#ifdef USE_VR
	// in DuckStation, use address usable by injection
	MATRIX* matrixDST = 0x8000C000;
	#else
	// ordinary PlayStation 1, use scratchpad
	MATRIX* matrixDST = 0x1f8003d4;
	#endif
  #endif

// Dont write matrix for VR,
// OculusTest.exe will inject the matrix manually
#ifndef USE_VR
  
  #ifndef REBUILD_PC
  *(short*)0x1f8003f4 = tileView->rot[0];
  *(short*)0x1f8003f6 = tileView->rot[1];
  *(short*)0x1f8003f8 = tileView->rot[2];
  ConvertRotToMatrix(matrixDST, (short *)0x1f8003f4);
  #else
  // only a TEST function for REBUILD_PS1 and REBUILD_PC,
  // can not be used stable, with regular PS1 modding
  *(short*)&scratchpad[0x3f4] = tileView->rot[0];
  *(short*)&scratchpad[0x3f6] = tileView->rot[1];
  *(short*)&scratchpad[0x3f8] = tileView->rot[2];
  TEST_ConvertRotToMatrix(matrixDST, (short *)&scratchpad[0x3f4]);
  #endif

// ifdef USE_VR
#else

  // if inside VR, increment each frame,
  // assuming tileView->pos resets next frame,
  // do not use this with freecam mods cause
  // it will increment infinitely into the skybox
  tileView->pos[0] += matrixDST->t[0];
  tileView->pos[1] += matrixDST->t[1];
  tileView->pos[2] += matrixDST->t[2];
  
#endif

  short t[3];

  // bit-hack, store two u16s as one u32
  *(int*)&t[0] = *(int*)&tileView->pos[0];
  t[2] = tileView->pos[2];
  
  tileView->matrix_Camera.t[0] = t[0];
  tileView->matrix_Camera.t[1] = t[1];
  tileView->matrix_Camera.t[2] = t[2];
  
  // bit-hack, negate two u16s as one u32
  *(int*)&t[0] = -*(int*)&t[0]+0x10000;
  t[2] = -t[2];
  
  // load inverted camera position
#ifndef REBUILD_PC
#define gte_ldVXY0(r0) 	__asm__ volatile("mtc2   %0, $0" : : "r"(r0))
#define gte_ldVZ0(r0) 	__asm__ volatile("mtc2   %0, $1" : : "r"(r0))
  gte_ldVXY0(*(int*)&t[0]);
  gte_ldVZ0(t[2]);
#else
  gte_ldv0(&t[0]);
#endif
  
#ifndef REBUILD_PC

// gte_SetLightMatrix
#define gte_r8(r0) __asm__ volatile("ctc2   %0, $8" : : "r"(r0))
#define gte_r9(r0) __asm__ volatile("ctc2   %0, $9" : : "r"(r0))
#define gte_r10(r0) __asm__ volatile("ctc2   %0, $10" : : "r"(r0))
#define gte_r11(r0) __asm__ volatile("ctc2   %0, $11" : : "r"(r0))
#define gte_r12(r0) __asm__ volatile("ctc2   %0, $12" : : "r"(r0))

#endif

  // CameraMatrix
  uVar3 = *(int*)&matrixDST->m[0][0];
  uVar4 = *(int*)&matrixDST->m[0][2];
  uVar5 = *(int*)&matrixDST->m[1][1];
  uVar6 = *(int*)&matrixDST->m[2][0];
  sVar7 = *(short*)&matrixDST->m[2][2];

  // CameraMatrix, for shadows, particles, and audio
  *(int*)((int)&tileView->matrix_Camera + 0x0) = uVar3;
  *(int*)((int)&tileView->matrix_Camera + 0x4) = uVar4;
  *(int*)((int)&tileView->matrix_Camera + 0x8) = uVar5;
  *(int*)((int)&tileView->matrix_Camera + 0xC) = uVar6;
  *(short*)((int)&tileView->matrix_Camera + 0x10) = sVar7;

  // transpose the camera matrix
  view0 = uVar3 & 0xffff | uVar4 & 0xffff0000;
  view4 = uVar6 & 0xffff | uVar3 & 0xffff0000;
  view8 = uVar5 & 0xffff | uVar6 & 0xffff0000;
  viewC = uVar4 & 0xffff | uVar5 & 0xffff0000;
  
  // CameraTranspose, for lightning during Driver Warping effect
  *(int*)((int)&tileView->matrix_CameraTranspose + 0x0) = view0;
  *(int*)((int)&tileView->matrix_CameraTranspose + 0x4) = view4;
  *(int*)((int)&tileView->matrix_CameraTranspose + 0x8) = view8;
  *(int*)((int)&tileView->matrix_CameraTranspose + 0xC) = viewC;
  *(short*)((int)&tileView->matrix_CameraTranspose + 0x10) = sVar7;

  // load transpose camera matrix
  // similar to gte_SetLightMatrix
#ifndef REBUILD_PC
  gte_r8(view0);
  gte_r9(view4);
  gte_r10(view8);
  gte_r11(viewC);
  gte_r12(sVar7);
#else
  gte_SetLightMatrix(&tileView->matrix_CameraTranspose);
#endif

  // multiply inverted camera position, 
  // by transpose camera matrix
  gte_llv0();

  gte_stlvnl(&tileView->matrix_CameraTranspose.t[0]);
  gte_stlvnl(&tileView->matrix_ViewProj.t[0]);

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
  
  // Do NOT set to 0x480 
  // to change 4/3 to 16/9,
  // it will zoom "in" instead of "out"
  // because of stretching Y instead of X
  
  #if BUILD == EurRetail
  #define r360 0x3B0
  #else
  #define r360 0x360
  #endif
  
  // constant denomenator
  #define r600 0x600

  // scale position
  tileView->matrix_ViewProj.t[1] =
  tileView->matrix_ViewProj.t[1] * r360 / r600;
  
  // scale Y axis (1)
  tileView->matrix_ViewProj.m[1][0] =
  tileView->matrix_ViewProj.m[1][0] * r360 / r600;

  // scale Y axis (2)
  tileView->matrix_ViewProj.m[1][1] =
  tileView->matrix_ViewProj.m[1][1] * r360 / r600;

  // scale Y axis (3)
  tileView->matrix_ViewProj.m[1][2] =
  tileView->matrix_ViewProj.m[1][2] * r360 / r600;
  
#ifdef USE_16BY9
  void ui16by9_ViewProj(struct TileView* view);
  ui16by9_ViewProj(tileView);
#endif

  // store camera matrix,
  // otherwise oxide intro cutscene bugs out,
  // when crash is sleeping on the grassy hill

#ifndef REBUILD_PC
  gte_r8 (uVar3);
  gte_r9 (uVar4);
  gte_r10(uVar5);
  gte_r11(uVar6);
#else
  gte_SetLightMatrix(&scratchpad[0x3d4]);
#endif

  return;
}