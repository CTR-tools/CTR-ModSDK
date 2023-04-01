#include <common.h>

void DECOMP_TileView_UpdateFrustum(struct TileView* tileView)

{
  short cameraPosX;
  short cameraPosY;
  short cameraPosZ;
  int val_Y;
  int val_X;
  int min_Y;
  int half_Y;
  int min_X;
  int tx;
  int posX;
  short uVar12;
  int ty;
  int posY;
  short uVar15;
  int tz;
  int posZ;
  short uVar18;
  int iVar19;
  int i;
  int corner1;
  u_int uVar22;
  int distToScreen;
  int min_Z;
  int max_X;
  int max_Y;
  int max_Z;
  
  #if 0
  // TRAP checks removed
  // assume no divide by zero
  #endif

#define gte_ldVXY0(r0) 	__asm__ volatile("mtc2   %0, $0" : : "r"(r0))
#define gte_ldVZ0(r0) 	__asm__ volatile("mtc2   %0, $1" : : "r"(r0))

  // get the result
#define read_mt(r0, r1, r2) 	__asm__ volatile( \
	"mfc2   %0, $25;"  \
	"mfc2   %1, $26;"  \
	"mfc2   %2, $27;"  \
	: : "r"(r0), "r"(r1), "r"(r2))

  TileView_SetMatrixVP(tileView);

  // disable the rest of the function by setting
  // 80043124 to 0x08010E3E (j 0x800438f8),
  // proves the rest of this function updates frustum

  cameraPosX = tileView->pos[0];
  cameraPosY = tileView->pos[1];
  cameraPosZ = tileView->pos[2];

  min_Y = tileView->rect.w;
  val_X = min_Y / 2;

  min_X = (tileView->rect.h * 0x600) / 0x360;
  val_Y = (min_X / 2) << 0x10;
  
  distToScreen = tileView->distanceToScreen_PREV;
  
  // first "do" loop iteration
  // X | (Y << 0x10)
  uVar22 = val_X | val_Y;
  
  // distToScreen
  gte_ldVZ0(distToScreen);
  
  // -1 * rect.w/2
  half_Y = -min_Y / 2 & 0xffff;
  
  min_X = -min_X;
  corner1 = 0x1f800012;
  
  min_X = cameraPosX;		// min X 1f800000 (default cameraPosX)
  min_Y = cameraPosY;		// min Y 1f800004 (default cameraPosY)
  min_Z = cameraPosZ;		// min Z 1f800008 (default cameraPosZ)
  
  max_X = cameraPosX;		// max X 1f800000 (default cameraPosX)
  max_Y = cameraPosY;	// max Y 1f800004 (default cameraPosY)
  max_Z = cameraPosZ;	// max Z 1f800008 (default cameraPosZ)
  
  // uVar5, uVar6, uVar8, uVar9 never change
  // beyond this point, they are constant
  
  // 4 points (uVar22) (x,y,z):
  // uVar6, uVar5, distToScreen
  // uVar8, uVar5, distToScreen
  // uVar8, uVar9, distToScreen
  // uVar6, uVar9, distToFinish_checkpoint
  
  for (i = 4; i > 0; i--)
  {
	// multiply corner of screen,
	// by view-projection matrix, 
	// to get frustum plane world-pos
    gte_ldVXY0(uVar22);
    gte_llv0();

	if (i == 2) 
	{
	  // prepare for third iteration
      uVar22 = val_X | min_X / 2 << 0x10;
    }
    else {
      if (i < 3) {
        if (i == 1) 
		{
		  // prepare for fourth iteration
          uVar22 = half_Y | min_X / 2 << 0x10;
        }
      }
      else {
        if (i == 3) 
		{
		  // prepare for second iteration
          uVar22 = half_Y | val_Y;
        }
      }
    }
	
	// this is ViewProj matrix, loaded into GTE
	// from end of TileView_SetMatrixVP (called earlier)
	read_mt(tx,ty,tz);
    
	// result of read_mt, plus cameraPos (x,y,z),
	posX = tx * 0x100 + cameraPosX;
    posY = ty * 0x100 + cameraPosY;
    posZ = tz * 0x100 + cameraPosZ;
    
	iVar19 = 0x1000;
    
	// result of read_mt, plus cameraPos (x,y,z),
	// over 4 loop iterations, this writes four corners,
    *(int*)(corner1+0xc) = (char)tx + cameraPosX;
    *(int*)(corner1+0xe) = (char)ty + cameraPosY;
	*(int*)(corner1+0x10) = (char)tz + cameraPosZ;
	
    *(int*)0x1f800000 = posX;
    *(int*)0x1f800004 = posY;
    *(int*)0x1f800008 = posZ;
    
	// === X Axis ===
	if (((cameraPosX < -0x8000) && (-0x8000 < posX)) || ((-0x8000 < cameraPosX && (posX < -0x8000)))) {
      ty = (-0x8000 - cameraPosX) * 0x1000;
      tx = posX - cameraPosX;
      tz = ty / tx;

      if (tz < 0x1000) {
        *(int*)0x1f800000 = -0x8000;
        *(int*)0x1f800004 = cameraPosY + (tz * (posY - cameraPosY) >> 0xc);
        *(int*)0x1f800008 = cameraPosZ + (tz * (posZ - cameraPosZ) >> 0xc);
        iVar19 = tz;
      }
    }
	
	// === Y Axis ===
    if (((cameraPosY < -0x8000) && (-0x8000 < posY)) || ((-0x8000 < cameraPosY && (posY < -0x8000)))) {
      ty = (-0x8000 - cameraPosY) * 0x1000;
      tx = posY - cameraPosY;
      tz = ty / tx;

      if (tz < iVar19) {
        *(int*)0x1f800004 = -0x8000;
        *(int*)0x1f800000 = cameraPosX + (tz * (posX - cameraPosX) >> 0xc);
        *(int*)0x1f800008 = cameraPosZ + (tz * (posZ - cameraPosZ) >> 0xc);
        iVar19 = tz;
      }
    }
	
	// === Z Axis ===
    if (((cameraPosZ < -0x8000) && (-0x8000 < posZ)) || ((-0x8000 < cameraPosZ && (posZ < -0x8000)))) {
      ty = (-0x8000 - cameraPosZ) * 0x1000;
      tx = posZ - cameraPosZ;
      tz = ty / tx;

      if (tz < iVar19) {
        *(int*)0x1f800008 = -0x8000;
        *(int*)0x1f800000 = cameraPosX + (tz * (posX - cameraPosX) >> 0xc);
        *(int*)0x1f800004 = cameraPosY + (tz * (posY - cameraPosY) >> 0xc);
        iVar19 = tz;
      }
    }
	
	// === X Axis ===
    if (((cameraPosX < 0x7fff) && (0x7fff < posX)) || ((0x7fff < cameraPosX && (posX < 0x7fff)))) {
      ty = (0x7fff - cameraPosX) * 0x1000;
      tx = posX - cameraPosX;
      tz = ty / tx;

      if (tz < iVar19) {
        *(int*)0x1f800000 = 0x7fff;
        *(int*)0x1f800004 = cameraPosY + (tz * (posY - cameraPosY) >> 0xc);
        *(int*)0x1f800008 = cameraPosZ + (tz * (posZ - cameraPosZ) >> 0xc);
        iVar19 = tz;
      }
    }
	
	// === Y Axis ===
    if (((cameraPosY < 0x7fff) && (0x7fff < posY)) || ((0x7fff < cameraPosY && (posY < 0x7fff)))) {
      ty = (0x7fff - cameraPosY) * 0x1000;
      tx = posY - cameraPosY;
      tz = ty / tx;

      if (tz < iVar19) {
        *(int*)0x1f800004 = 0x7fff;
        *(int*)0x1f800000 = cameraPosX + (tz * (posX - cameraPosX) >> 0xc);
        *(int*)0x1f800008 = cameraPosZ + (tz * (posZ - cameraPosZ) >> 0xc);
        iVar19 = tz;
      }
    }
	
	// === Z Axis ===
    if (((cameraPosZ < 0x7fff) && (0x7fff < posZ)) || ((0x7fff < cameraPosZ && (posZ < 0x7fff)))) {
      tx = (0x7fff - cameraPosZ) * 0x1000;
      posZ = posZ - cameraPosZ;
      ty = tx / posZ;

      if (ty < iVar19) {
        *(int*)0x1f800008 = 0x7fff;
        *(int*)0x1f800000 = cameraPosX + (ty * (posX - cameraPosX) >> 0xc);
        *(int*)0x1f800004 = cameraPosY + (ty * (posY - cameraPosY) >> 0xc);
      }
    }
	
	// === Set 6 Min/Max X,Y,Z variables ===
	
    if (*(int*)0x1f800000 < max_X) {
      max_X = *(int*)0x1f800000;
    }
    if (min_X < *(int*)0x1f800000) {
      min_X = *(int*)0x1f800000;
    }
    if (*(int*)0x1f800004 < max_Y) {
      max_Y = *(int*)0x1f800004;
    }
    if (min_Y < *(int*)0x1f800004) {
      min_Y = *(int*)0x1f800004;
    }
    if (*(int*)0x1f800008 < max_Z) {
      max_Z = *(int*)0x1f800008;
    }
    if (min_Z < *(int*)0x1f800008) {
      min_Z = *(int*)0x1f800008;
    }
	// next corner to write
    corner1 = corner1 + -6;
  } 

  tileView->bbox.min[0] = (char)max_X;
  tileView->bbox.max[0] = (char)min_X;
  tileView->bbox.max[1] = (char)min_Y;
  tileView->bbox.min[1] = (char)max_Y;
  tileView->bbox.max[2] = (char)min_Z;
  tileView->bbox.min[2] = (char)max_Z;

  // cameraPos (x,y,z)
  *(int*)0x1f800024 = cameraPosX;
  *(int*)0x1f800024 = cameraPosY;
  *(int*)0x1f800028 = cameraPosZ;

  // Changing stuff here is what caused EuroAli's
  // discovery for widescreen, so that polygons aren't
  // clipped outside of original 4:3 viewport

  // TileView_SetFrustumPlane (x4)
  
  // these are four corners, two corners per func call,
  // combined with camera position, is used to make a plane
/*
	1f80000c -0x100 0x255 0x66 -- corner (-x,+y,-z)
	1f800012 +0x100 0x255 0x66 -- corner (+x,+y,-z)
	1f800018 -0x100 0x0D5 0x78 -- corner (-x,-y,-z)
	1f80001e +0x100 0x0D5 0x78 -- corner (+x,-y,-z)
	1f800024 0x0000 0x1a4 0x1af -- cameraPos
*/

  val_Y = TileView_SetFrustumPlane(&tileView->frustumData[0],0x1f80000c,0x1f800024,0x1f800012);
  tileView->RenderListJmpIndex[0] = ~val_Y & 7;

  val_Y = TileView_SetFrustumPlane(&tileView->frustumData[0x8],0x1f800012,0x1f800024,0x1f80001e);
  tileView->RenderListJmpIndex[1] = ~val_Y & 7;

  val_Y = TileView_SetFrustumPlane(&tileView->frustumData[0x10],0x1f80001e,0x1f800024,0x1f800018);
  tileView->RenderListJmpIndex[2] = ~val_Y & 7;

  val_Y = TileView_SetFrustumPlane(&tileView->frustumData[0x18],0x1f800018,0x1f800024,0x1f80000c);
  tileView->RenderListJmpIndex[3] = ~val_Y & 7;

  gte_ldVXY0(0);
  gte_ldVZ0(0x1000);
  gte_llv0();
  
  read_mt(val_Y,min_X,min_Y);

  tileView->frustumData[0x20] = -(char)val_Y;
  tileView->frustumData[0x22] = -(char)min_X;
  tileView->frustumData[0x24] = -(char)min_Y;

  min_X = distToScreen;
  if (distToScreen < 0) {
    min_X = distToScreen + 3;
  }

  tileView->frustumData[0x26] =
       (char)(-(cameraPosX * val_Y + cameraPosY * min_X + cameraPosZ * min_Y) >> 0xd) -
       (char)(min_X >> 2);

  val_Y = val_Y >> *(int*)0x1f;
  if (min_X < 0) {
    val_Y = val_Y | 2;
  }
  if (min_Y < 0) {
    val_Y = val_Y | 4;
  }

  // 0xE0, 0xE4
  tileView->RenderListJmpIndex[4] = ~val_Y & 7;
  tileView->RenderListJmpIndex[5] = val_Y;
  
  gte_ldVXY0(0);
  gte_ldVZ0(distToScreen / 2);
  gte_llv0();
  
  read_mt(uVar12,uVar15,uVar18);
  
  tileView->data6[0] = uVar12 + cameraPosX;
  tileView->data6[2] = uVar15 + cameraPosY;
  tileView->data6[4] = uVar18 + cameraPosZ;
  return;
}
 