#include <common.h>

void DECOMP_RB_RainCloud_Init(struct Driver* d)
{
  struct Instance* cloudInst;
  struct Instance* rain;
  struct RainCloud* rcloud;
  unsigned short uVar3;

  // if driver -> cloudTh is invalid
  if (d->thCloud == NULL) 
  {
	// make a thread for "cloud", and return an instance
    cloudInst = INSTANCE_BirthWithThread(0x42,sdata->s_cloud1, SMALL, OTHER,RB_RainCloud_ThTick,8, d->instSelf->thread);
	
	// set funcThDestroy to remove instance from instance pool	
    cloudInst->thread->funcThDestroy = PROC_DestroyInstance;
	
	// Set rotation, 5 direction vectors
   cloudInst->matrix.m[0][0] = 0x1000;
   cloudInst->matrix.m[0][2] = 0;
   cloudInst->matrix.m[1][1] = 0x1000;
   cloudInst->matrix.m[2][0] = 0;
   cloudInst->matrix.m[2][2] = 0x1000;
	
	// cloud->posX = driver->posX
    cloudInst->matrix.t[0] = d->instSelf->matrix.t[0];
	
	// cloud->posY = driver->posY + 0x80
    cloudInst->matrix.t[1] = d->instSelf->matrix.t[1] + 0x80;
	
	// cloud->posZ = driver->posZ
    cloudInst->matrix.t[2] = d->instSelf->matrix.t[2];
	
    cloudInst->alphaScale = 0x800;
    
    // not in headers?
    *(char *)(cloudInst + 0x50) = *(char *)(d->instSelf + 0x50);
    *(char *)(cloudInst + 0x51) = *(char *)(d->instSelf + 0x51);
    
	// add rain to pool
	rain = JitPool_Add(sdata->gGT->JitPools.rain);
    
  // no idea what struct is this yet 
	if (rain != NULL) {
      *(unsigned short *)(rain + 8) = 0x1e;
      *(int *)(rain + 0x24) = cloudInst;
      *(short *)(rain + 0xc) = 0;
      *(short *)(rain + 0xe) = 0;
      *(short *)(rain + 0x10) = 0;
      *(short *)(rain + 0x14) = 0;
      *(short *)(rain + 0x16) = 0xffd8;
      *(short *)(rain + 0x18) = 0;
      *(short *)(rain + 0x1c) = d->instSelf->matrix.t[0];
      *(short *)(rain + 0x1e) = d->instSelf->matrix.t[1] + 0x80;
      *(short *)(rain + 0x20) = d->instSelf->matrix.t[2];
    }
    
	  rcloud = cloudInst->thread->object;
	
	// set duration to about 7.68s
    *(short *)(rcloud + 1) = 0x1e00;
	
    rcloud[0] = rain;
    
	// used by driver 0x50a
	*(short *)((int)rcloud + 6) = 1;
    
	if (
			// if driver has no weapon
			(d->heldItemID == 0xf) || 
			
			(d->noItemTimer != 0)
		) 
	{
	  // used by driver 0x50a
      *(short *)((int)rcloud + 6) = 0;
    }
	
    d->thCloud = cloudInst->thread;
  }
  
  // if cloud already exists, and 
  // driver hits another red potion
  else 
  {
	// set duration to 8 seconds
    *(int*)(d->thCloud->object + 4) = 0x1e00;
    
	// random number
	rng = DECOMP_MixRNG_Scramble();
	
	// random (related to driver offset 0x50a)
    *(short *)(d->thCloud->object + 6) = (short)((rng % 400) / 100);
  }
  return;
}
 