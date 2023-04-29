#include <common.h>

void DECOMP_RB_MaskWeapon_FadeAway(struct Thread* t)
{
  unsigned short uVar1;
  short totalTime;
  int ratio;
  MATRIX m;
  struct Driver* user;
  struct Instance* inst;
  struct MaskHeadWeapon* mask;
  
  inst = t->inst;
  mask = inst->thread->object;
  user = t->parentThread->object;

  // Sine(angle)  
  ratio = MATH_SIN(mask->rot[1]);

  DAT_1f800130._2_2_ = 0x40;
  DAT_1f800130._0_2_ = (((int)(mask->duration >> 5) * -4 + 0x40) * ratio >> 0xc);
  
  // Cosine(angle)
  ratio = MATH_Cos(mask->rot[1]);
  
  DAT_1f800134._0_2_ = (((int)(mask->duration >> 5) * -4 + 0x40) * ratio >> 0xc);
  
  // Copy Matrix:
  // To: Mask
  // From: Player
  LHMatrix_Parent(inst,user->instSelf,&DAT_1f800130);
  
  // alter angle for rotation
  mask->rot[1]  += -0x100;
  
  // decrease scale (x, y, z)
  inst->scale[0] += -0x100;
  inst->scale[1] += -0x100;
  inst->scale[2] += -0x100;
  
  DAT_1f800130._0_2_ = 0;
  DAT_1f800130._2_2_ = 0x40;
  DAT_1f800134._0_2_ = 0;
  
  // Copy Matrix:
  // To: Mask (Beam within mask obj?)
  // From: Player
  LHMatrix_Parent(mask->maskBeamInst,user->instSelf,&DAT_1f800130);
  
  DAT_1f800128 = 0;
  DAT_1f80012a = mask->rot[1];
  DAT_1f80012c._0_2_ = 0;
  
   // convert 3 rotation shorts into rotation matrix
  ConvertRotToMatrix(&DAT_1f800108,&DAT_1f800128);
  
  m = mask->maskBeamInst->matrix;
  MatrixRotate(m,m,&DAT_1f800108);
  
  // decrease scale (x, y, z)
  mask->maskBeamInst->scale[0] += -0x100;
  mask->maskBeamInst->scale[1] += -0x100;
  mask->maskBeamInst->scale[2] += -0x100;

  if (mask->maskBeamInst->alphaScale < 0x1000)
  {
    mask->maskBeamInst->alphaScale += 0x200;
  }

  if (mask->duration < 0x200)
  {
    totalTime = mask->duration + sdata->gGT->elapsedTimeMS;
    mask->duration = totalTime;
    if (0x200 < totalTime)
    {
      mask->duration = 0x200;
    }
  }
  else
  {
    // mask is now dead
    INSTANCE_Death(mask->maskBeamInst);
    t->flags |= 0x800;
  }
  return;
}
 