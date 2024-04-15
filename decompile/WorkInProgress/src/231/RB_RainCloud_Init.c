#include <common.h>

void DECOMP_RB_RainCloud_Init(struct Driver* d)
{
  char* rain;
  struct Instance* cloudInst;
  struct RainCloud* rcloud;
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
    
    // not in headers?
    *(char *)(cloudInst + 0x50) = *(char *)(d->instSelf + 0x50);
    *(char *)(cloudInst + 0x51) = *(char *)(d->instSelf + 0x51);
    
	// add rain to pool
	rain = JitPool_Add(sdata->gGT->JitPools.rain);
    
	// no idea what struct is this yet 
	if (rain != NULL) 
	{
      *(short *)((int)rain + 8) = 0x1e;
	  
	  // short[4]
      *(short *)((int)rain + 0xc) = 0;
      *(short *)((int)rain + 0xe) = 0;
      *(short *)((int)rain + 0x10) = 0;
      
	  // short[4]
	  *(short *)((int)rain + 0x14) = 0;
      *(short *)((int)rain + 0x16) = 0xffd8;
      *(short *)((int)rain + 0x18) = 0;
      
	  // short[4]
	  *(short *)((int)rain + 0x1c) = d->instSelf->matrix.t[0];
      *(short *)((int)rain + 0x1e) = d->instSelf->matrix.t[1] + 0x80;
      *(short *)((int)rain + 0x20) = d->instSelf->matrix.t[2];
      
	  *(int *)(  (int)rain + 0x24) = cloudInst;
    }
    
	rcloud = cloudInst->thread->object;
    rcloud->timeMS = 0x1e00; // 7.68s
    rcloud->rainBuffer = rain;
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
	rng = DECOMP_MixRNG_Scramble();
	
	// random (related to driver offset 0x50a)
    rcloud->boolScrollItem = (short)((rng % 400) / 100);
  }
  return;
}
 