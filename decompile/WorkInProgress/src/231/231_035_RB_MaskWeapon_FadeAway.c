#include <common.h>

void DECOMP_RB_MaskWeapon_FadeAway(struct Thread* t)
{
  unsigned short uVar1;
  short totalTime;
  int ratio;
  MATRIX m;
  struct Driver* user;
  struct Instance* inst;
  struct Instance* maskBeamInst;
  struct MaskHeadWeapon* mask;
  
  inst = t->inst;
  mask = inst->thread->object;
  user = t->parentThread->object;
  maskBeamInst = mask->maskBeamInst;

  // Sine(angle)  
  ratio = MATH_SIN(mask->rot[1]);
  *(short*)0x1f800130 = (((int)(mask->duration >> 5) * -4 + 0x40) * ratio >> 0xc);
  
  // Cosine(angle)
  ratio = MATH_Cos(mask->rot[1]);
  *(short*)0x1f800134 = (((int)(mask->duration >> 5) * -4 + 0x40) * ratio >> 0xc);
  
  *(short*)0x1f800132 = 0x40;
  
  // Copy Matrix:
  // To: Mask
  // From: Player
  LHMatrix_Parent(inst,user->instSelf,0x1f800130);
  
  // alter angle for rotation
  mask->rot[1]  += -0x100;
  
  // decrease scale (x, y, z)
  inst->scale[0] += -0x100;
  inst->scale[1] += -0x100;
  inst->scale[2] += -0x100;
  
  // position offset
  *(short*)0x1f800130 = 0;
  *(short*)0x1f800132 = 0x40;
  *(short*)0x1f800134 = 0;
  
  // Copy Matrix:
  // To: Mask (Beam within mask obj?)
  // From: Player
  LHMatrix_Parent(maskBeamInst,user->instSelf,0x1f800130);
  
  *(short*)0x1f800128 = 0;
  *(short*)0x1f80012a = mask->rot[1];
  *(short*)0x1f80012c = 0;
  
   // convert 3 rotation shorts into rotation matrix
  ConvertRotToMatrix(0x1f800108, 0x1f800128);
  
  m = maskBeamInst->matrix;
  MatrixRotate(m,m,01f800108);
  
  // decrease scale (x, y, z)
  maskBeamInst->scale[0] += -0x100;
  maskBeamInst->scale[1] += -0x100;
  maskBeamInst->scale[2] += -0x100;

  if (maskBeamInst->alphaScale < 0x1000)
  {
    maskBeamInst->alphaScale += 0x200;
  }

  totalTime = mask->duration;

  if (totalTime < 0x200)
  {
    totalTime += sdata->gGT->elapsedTimeMS;
    
	if (totalTime > 0x200)
		totalTime = 0x200;
    
	mask->duration = totalTime;
	return;
  }
    
  // mask is now dead
  INSTANCE_Death(maskBeamInst);
  t->flags |= 0x800;
  return;
}
 