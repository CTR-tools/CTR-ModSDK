#include <common.h>

void DECOMP_RB_MaskWeapon_FadeAway(struct Thread* t)
{
  unsigned short uVar1;
  short totalTime;
  int ratio;
  MATRIX* m;
  struct Instance* inst;
  struct Instance* driverInst;
  struct Instance* maskBeamInst;
  struct MaskHeadWeapon* mask;
  
  inst = t->inst;
  mask = inst->thread->object;
  driverInst = t->parentThread->inst;
  maskBeamInst = mask->maskBeamInst;
  
  struct MaskHeadScratch* mhs = 0x1f800108;

  // Set up First pass (maskInst)

  int durationAdjusted = ((int)(mask->duration >> 5) * -4 + 0x40);
  mhs->posOffset[0] = ((durationAdjusted * MATH_Sin(mask->rot[1])) >> 0xc);
  mhs->posOffset[2] = ((durationAdjusted * MATH_Cos(mask->rot[1])) >> 0xc);
  mhs->posOffset[1] = 0x40;

  mask->rot[1] += FPS_HALF(-0x100);
  
  struct Instance* instCurr;
  instCurr = inst;
  
  // First time is MaskInst,
  // Second time is BeamInst
  for(int i = 0; i < 2; i++)
  {
	LHMatrix_Parent(instCurr, driverInst, &mhs->posOffset[0]);
	
	instCurr->scale[0] += FPS_HALF(-0x100);
	instCurr->scale[1] += FPS_HALF(-0x100);
	instCurr->scale[2] += FPS_HALF(-0x100);
	
	// position offset
	mhs->posOffset[0] = 0;
	mhs->posOffset[2] = 0;
  	
  	instCurr = maskBeamInst;
  }
  
  mhs->rot[0] = 0;
  mhs->rot[1] = mask->rot[1];
  mhs->rot[2] = 0;
  ConvertRotToMatrix(&mhs->m, &mhs->rot[0]);
  
  m = &maskBeamInst->matrix;
  MatrixRotate(m,m,&mhs->m);

  if(maskBeamInst->alphaScale < 0x1000)
	maskBeamInst->alphaScale += FPS_HALF(0x200);

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
  DECOMP_INSTANCE_Death(maskBeamInst);
  t->flags |= 0x800;
  return;
}
 