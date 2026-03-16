#include <common.h>

void DECOMP_PushBuffer_UpdateFrustum(struct PushBuffer* pb)
{
  int cameraPosX;
  int cameraPosY;
  int cameraPosZ;
  
  int val_X;
  int val_Y;
  
  // Let the compiler figure it out,
  // the bitshifting annoys me
  union FrustumCornerIN frustumCorner[4];
  
  int iVar19;
 
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
  
  struct ScratchpadFrustum* spf = (struct ScratchpadFrustum*)0x1f800000;
  
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

  
  min_X = cameraPosX;
  min_Y = cameraPosY;
  min_Z = cameraPosZ;
  
  max_X = cameraPosX;
  max_Y = cameraPosY;
  max_Z = cameraPosZ;
  
  struct FrustumCornerOUT* fcOUT = &spf->fc[3];
  
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
    
    fcOUT->pos.x = (short)tx + cameraPosX;
    fcOUT->pos.y = (short)ty + cameraPosY;
	fcOUT->pos.z = (short)tz + cameraPosZ;
	
	// far clip: pos + dir*100
    spf->pos.x = posX;
    spf->pos.y = posY;
    spf->pos.z = posZ;
    
	// === X Axis ===
	if (((cameraPosX < -0x8000) && (-0x8000 < posX)) || ((-0x8000 < cameraPosX && (posX < -0x8000)))) {
      ty = (-0x8000 - cameraPosX) * 0x1000;
      tx = posX - cameraPosX;
      tz = ty / tx;

      if (tz < 0x1000) {
        spf->pos.x = -0x8000;
        spf->pos.y = cameraPosY + (tz * (posY - cameraPosY) >> 0xc);
        spf->pos.z = cameraPosZ + (tz * (posZ - cameraPosZ) >> 0xc);
        iVar19 = tz;
      }
    }
	
	// === Y Axis ===
    if (((cameraPosY < -0x8000) && (-0x8000 < posY)) || ((-0x8000 < cameraPosY && (posY < -0x8000)))) {
      ty = (-0x8000 - cameraPosY) * 0x1000;
      tx = posY - cameraPosY;
      tz = ty / tx;

      if (tz < iVar19) {
        spf->pos.y = -0x8000;
        spf->pos.x = cameraPosX + (tz * (posX - cameraPosX) >> 0xc);
        spf->pos.z = cameraPosZ + (tz * (posZ - cameraPosZ) >> 0xc);
        iVar19 = tz;
      }
    }
	
	// === Z Axis ===
    if (((cameraPosZ < -0x8000) && (-0x8000 < posZ)) || ((-0x8000 < cameraPosZ && (posZ < -0x8000)))) {
      ty = (-0x8000 - cameraPosZ) * 0x1000;
      tx = posZ - cameraPosZ;
      tz = ty / tx;

      if (tz < iVar19) {
        spf->pos.z = -0x8000;
        spf->pos.x = cameraPosX + (tz * (posX - cameraPosX) >> 0xc);
        spf->pos.y = cameraPosY + (tz * (posY - cameraPosY) >> 0xc);
        iVar19 = tz;
      }
    }
	
	// === X Axis ===
    if (((cameraPosX < 0x7fff) && (0x7fff < posX)) || ((0x7fff < cameraPosX && (posX < 0x7fff)))) {
      ty = (0x7fff - cameraPosX) * 0x1000;
      tx = posX - cameraPosX;
      tz = ty / tx;

      if (tz < iVar19) {
        spf->pos.x = 0x7fff;
        spf->pos.y = cameraPosY + (tz * (posY - cameraPosY) >> 0xc);
        spf->pos.z = cameraPosZ + (tz * (posZ - cameraPosZ) >> 0xc);
        iVar19 = tz;
      }
    }
	
	// === Y Axis ===
    if (((cameraPosY < 0x7fff) && (0x7fff < posY)) || ((0x7fff < cameraPosY && (posY < 0x7fff)))) {
      ty = (0x7fff - cameraPosY) * 0x1000;
      tx = posY - cameraPosY;
      tz = ty / tx;

      if (tz < iVar19) {
        spf->pos.y = 0x7fff;
        spf->pos.x = cameraPosX + (tz * (posX - cameraPosX) >> 0xc);
        spf->pos.z = cameraPosZ + (tz * (posZ - cameraPosZ) >> 0xc);
        iVar19 = tz;
      }
    }
	
	// === Z Axis ===
    if (((cameraPosZ < 0x7fff) && (0x7fff < posZ)) || ((0x7fff < cameraPosZ && (posZ < 0x7fff)))) {
      tx = (0x7fff - cameraPosZ) * 0x1000;
      posZ = posZ - cameraPosZ;
      ty = tx / posZ;

      if (ty < iVar19) {
        spf->pos.z = 0x7fff;
        spf->pos.x = cameraPosX + (ty * (posX - cameraPosX) >> 0xc);
        spf->pos.y = cameraPosY + (ty * (posY - cameraPosY) >> 0xc);
      }
    }
	
	// === Set 6 Min/Max X,Y,Z variables ===
	
    if (min_X > spf->pos.x) min_X = spf->pos.x;
    if (min_Y > spf->pos.y) min_Y = spf->pos.y;
    if (min_Z > spf->pos.z) min_Z = spf->pos.z;
    
    if (max_X < spf->pos.x) max_X = spf->pos.x;
    if (max_Y < spf->pos.y) max_Y = spf->pos.y;
    if (max_Z < spf->pos.z) max_Z = spf->pos.z;
    
	// next corner to write
    fcOUT--;
  } 

  pb->bbox.min[0] = (short)min_X;
  pb->bbox.min[1] = (short)min_Y;
  pb->bbox.min[2] = (short)min_Z;
  
  pb->bbox.max[0] = (short)max_X;
  pb->bbox.max[1] = (short)max_Y;
  pb->bbox.max[2] = (short)max_Z;

  // cameraPos (x,y,z)
  spf->camPos.x = cameraPosX;
  spf->camPos.y = cameraPosY;
  spf->camPos.z = cameraPosZ;

  // PushBuffer_SetFrustumPlane (x4)
  val_Y = PushBuffer_SetFrustumPlane(&pb->frustumData[0],&spf->fc[0],&spf->camPos.x,&spf->fc[1]);
  pb->RenderListJmpIndex[0] = ~val_Y & 7;

  val_Y = PushBuffer_SetFrustumPlane(&pb->frustumData[0x8],&spf->fc[1],&spf->camPos.x,&spf->fc[3]);
  pb->RenderListJmpIndex[1] = ~val_Y & 7;

  val_Y = PushBuffer_SetFrustumPlane(&pb->frustumData[0x10],&spf->fc[3],&spf->camPos.x,&spf->fc[2]);
  pb->RenderListJmpIndex[2] = ~val_Y & 7;

  val_Y = PushBuffer_SetFrustumPlane(&pb->frustumData[0x18],&spf->fc[2],&spf->camPos.x,&spf->fc[0]);
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

  // Negation Flags
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
 