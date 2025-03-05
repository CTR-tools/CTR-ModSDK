#include <common.h>

// 1924 pre-changes

void DECOMP_PushBuffer_UpdateFrustum(struct PushBuffer* pb)
{
  int cameraPosX;
  int cameraPosY;
  int cameraPosZ;
  
  int val_X;
  int val_Y;
  
  // Let the compiler figure it out,
  // the bitshifting annoys me
  union
  {
	  struct
	  {
		  short x;
		  short y;
	  };
	  
	  struct
	  {
		  int self;
	  };
  } frustumCorner[4];
  
  int iVar19;
  int corner1;
 
  int tx;
  int ty;
  int tz;

  int posX;
  int posY;
  int posZ;
  
  int min_X;
  int min_Y;
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

  DECOMP_PushBuffer_SetMatrixVP(pb);
  
  gte_ldVZ0(pb->distanceToScreen_PREV);

  cameraPosX = pb->pos[0];
  cameraPosY = pb->pos[1];
  cameraPosZ = pb->pos[2];



  val_X = pb->rect.w;  
  val_X = val_X / 2;
  
  // Is this correct?
  // SetMatrixVP changes 0x360 to 0x3b0,
  // This was an assumption based on results
  #ifdef USE_16BY9
  val_X = (val_X * 1000) / 750;
  #endif
  
  val_Y = ((pb->rect.h * 0x600) / 0x360);
  val_Y = val_Y / 2;


  frustumCorner[0].x = val_X;
  frustumCorner[0].y = val_Y;
  
  frustumCorner[1].x = -val_X;
  frustumCorner[1].y = val_Y;
  
  frustumCorner[2].x = val_X;
  frustumCorner[2].y = -val_Y;
  
  frustumCorner[3].x = -val_X;
  frustumCorner[3].y = -val_Y;
	
  
  
  corner1 = 0x1f800012;
  
  min_X = cameraPosX;
  min_Y = cameraPosY;
  min_Z = cameraPosZ;
  
  max_X = cameraPosX;
  max_Y = cameraPosY;
  max_Z = cameraPosZ;
  
  
  for (int i = 0; i < 4; i++)
  {	  
	// multiply corner of screen,
	// by view-projection matrix, 
	// to get frustum plane world-pos
    gte_ldVXY0(frustumCorner[i].self);
    gte_llv0();
	
	// this is ViewProj matrix, loaded into GTE
	// from end of PushBuffer_SetMatrixVP (called earlier)
	read_mt(tx,ty,tz);
    
#ifdef USE_16BY9
	// === Widescreen extends far-clip ====
	// wider frustum means direction goes less "far"
	// I tried 0x200 for 16x9, it's close enough
	// but 20x9 is broken no matter what
	posX = (short)tx * 0x200 + cameraPosX;
    posY = (short)ty * 0x200 + cameraPosY;
    posZ = (short)tz * 0x200 + cameraPosZ;
#else
	// far clip: pos + dir*100
	posX = (short)tx * 0x100 + cameraPosX;
    posY = (short)ty * 0x100 + cameraPosY;
    posZ = (short)tz * 0x100 + cameraPosZ;
#endif
	
	iVar19 = 0x1000;
    
	// near clip: pos + dir*1
    *(short*)(corner1+0xc) = (short)tx + cameraPosX;
    *(short*)(corner1+0xe) = (short)ty + cameraPosY;
	*(short*)(corner1+0x10) = (short)tz + cameraPosZ;
	
	// far clip: pos + dir*100
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
	
    if (*(int*)0x1f800000 < min_X) {
      min_X = *(int*)0x1f800000;
    }
    if (max_X < *(int*)0x1f800000) {
      max_X = *(int*)0x1f800000;
    }
    if (*(int*)0x1f800004 < min_Y) {
      min_Y = *(int*)0x1f800004;
    }
    if (max_Y < *(int*)0x1f800004) {
      max_Y = *(int*)0x1f800004;
    }
    if (*(int*)0x1f800008 < min_Z) {
      min_Z = *(int*)0x1f800008;
    }
    if (max_Z < *(int*)0x1f800008) {
      max_Z = *(int*)0x1f800008;
    }
	// next corner to write
    corner1 = corner1 + -6;
  } 

  pb->bbox.min[0] = (short)min_X;
  pb->bbox.min[1] = (short)min_Y;
  pb->bbox.min[2] = (short)min_Z;
  
  pb->bbox.max[0] = (short)max_X;
  pb->bbox.max[1] = (short)max_Y;
  pb->bbox.max[2] = (short)max_Z;

  // cameraPos (x,y,z)
  *(short*)0x1f800024 = cameraPosX;
  *(short*)0x1f800026 = cameraPosY;
  *(short*)0x1f800028 = cameraPosZ;

  // PushBuffer_SetFrustumPlane (x4)
  
  // these are four corners, two corners per func call,
  // combined with camera position, is used to make a plane
/*
	1f80000c -0x100 0x255 0x66 -- corner (-x,+y,-z)
	1f800012 +0x100 0x255 0x66 -- corner (+x,+y,-z)
	1f800018 -0x100 0x0D5 0x78 -- corner (-x,-y,-z)
	1f80001e +0x100 0x0D5 0x78 -- corner (+x,-y,-z)
	1f800024 0x0000 0x1a4 0x1af -- cameraPos
*/

  val_Y = PushBuffer_SetFrustumPlane(&pb->frustumData[0],0x1f80000c,0x1f800024,0x1f800012);
  pb->RenderListJmpIndex[0] = ~val_Y & 7;

  val_Y = PushBuffer_SetFrustumPlane(&pb->frustumData[0x8],0x1f800012,0x1f800024,0x1f80001e);
  pb->RenderListJmpIndex[1] = ~val_Y & 7;

  val_Y = PushBuffer_SetFrustumPlane(&pb->frustumData[0x10],0x1f80001e,0x1f800024,0x1f800018);
  pb->RenderListJmpIndex[2] = ~val_Y & 7;

  val_Y = PushBuffer_SetFrustumPlane(&pb->frustumData[0x18],0x1f800018,0x1f800024,0x1f80000c);
  pb->RenderListJmpIndex[3] = ~val_Y & 7;

  gte_ldVXY0(0);
  gte_ldVZ0(0x1000);
  gte_llv0();
  
  int retX;
  int retY;
  int retZ;
  read_mt(retX,retY,retZ);

  *(short*)&pb->frustumData[0x20] = -(short)retX;
  *(short*)&pb->frustumData[0x22] = -(short)retY;
  *(short*)&pb->frustumData[0x24] = -(short)retZ;


  int distToScreen = pb->distanceToScreen_PREV;

  int iVar9 = distToScreen;
  if (distToScreen < 0) {
    iVar9 = distToScreen + 3;
  }

  *(short*)&pb->frustumData[0x26] =
       (short)
	   (
			-(
				cameraPosX * (short)retX + 
				cameraPosY * (short)retY + 
				cameraPosZ * (short)retZ
			) >> 0xd) - (short)(iVar9 >> 2);

  int flags = (unsigned int)retX >> 0x1f;
  if (retY < 0) {
    flags = flags | 2;
  }
  if (retZ < 0) {
    flags = flags | 4;
  }

  // 0xE0, 0xE4
  pb->RenderListJmpIndex[4] = ~flags & 7;
  pb->RenderListJmpIndex[5] = flags;
  
  gte_ldVXY0(0);
  gte_ldVZ0(distToScreen / 2);
  gte_llv0();
  
  read_mt(retX,retY,retZ);
  
  *(short*)&pb->data6[0] = (short)retX + cameraPosX;
  *(short*)&pb->data6[2] = (short)retY + cameraPosY;
  *(short*)&pb->data6[4] = (short)retZ + cameraPosZ;
  return;
}
 