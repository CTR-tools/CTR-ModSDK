#include <common.h>

void DECOMP_RB_RainCloud_Init(struct Driver* d)
{
  struct Instance* cloudInst;
  struct RainCloud* rcloud;
  struct RainLocal* rlocal;
  unsigned short uVar3;

  // if driver -> cloudTh is invalid
  if (d->thCloud == NULL) 
  {
    cloudInst = DECOMP_INSTANCE_BirthWithThread(
		0x42, 0, SMALL, OTHER,
		RB_RainCloud_ThTick, 
		sizeof(struct RainCloud), 
		d->instSelf->thread);
	
    cloudInst->thread->funcThDestroy = DECOMP_PROC_DestroyInstance;
	
   *(int*)&cloudInst->matrix.m[0][0] = 0x1000;
   *(int*)&cloudInst->matrix.m[0][2] = 0;
   *(int*)&cloudInst->matrix.m[1][1] = 0x1000;
   *(int*)&cloudInst->matrix.m[2][0] = 0;
   cloudInst->matrix.m[2][2] = 0x1000;
	
	// cloud->posX = driver->posX
    cloudInst->matrix.t[0] = d->instSelf->matrix.t[0];
    cloudInst->matrix.t[1] = d->instSelf->matrix.t[1] + 0x80;
    cloudInst->matrix.t[2] = d->instSelf->matrix.t[2];
	
    cloudInst->alphaScale = 0x800;
	
    cloudInst->unk50 = d->instSelf->unk50;
    cloudInst->unk51 = d->instSelf->unk51;
    
	// add rain to pool
	rlocal = DECOMP_JitPool_Add(&sdata->gGT->JitPools.rain);
    
	// no idea what struct is this yet 
	if (rlocal != NULL) 
	{
      rlocal->frameCount = 0x1e;
	  
	  rlocal->unk1[0] = 0;
      rlocal->unk1[1] = 0;
      rlocal->unk1[2] = 0;
      
	  rlocal->vel[0] = 0;
      rlocal->vel[1] = FPS_HALF(-0x28);
      rlocal->vel[2] = 0;
      
	  rlocal->pos[0] = d->instSelf->matrix.t[0];
      rlocal->pos[1] = d->instSelf->matrix.t[1] + 0x80;
      rlocal->pos[2] = d->instSelf->matrix.t[2];
      
	  rlocal->cloudInst = cloudInst;
    }
    
	rcloud = cloudInst->thread->object;
    rcloud->timeMS = 0x1e00; // 7.68s
    rcloud->rainLocal = rlocal;
	rcloud->boolScrollItem = 1;
    
	if (
			// if driver has no weapon
			(d->heldItemID == 0xf) || 
			
			(d->noItemTimer != 0)
		) 
	{
      rcloud->boolScrollItem = 0;
    }
	
    d->thCloud = cloudInst->thread;
  }
  
  // if cloud already exists, and 
  // driver hits another red potion
  else 
  {
	rcloud = d->thCloud->object;
	  
	// set duration to 8 seconds
    rcloud->timeMS = 0x1e00;
    
	// random number
	int rng = DECOMP_MixRNG_Scramble();
	
	// random (related to driver offset 0x50a)
    rcloud->boolScrollItem = (short)((rng % 400) / 100);
  }
  return;
}
 