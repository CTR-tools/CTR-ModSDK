#include <common.h>

struct Thread* DECOMP_RB_GetThread_ClosestTracker(struct Driver* d)
{
  int distX;
  int distZ;
  struct Thread* currThread; 
  struct Thread* closestTh=0;
  int smallestDist;
  
  // assume farthest distance
  smallestDist = 0x3fffffff;
  
  // loop through all threads
  for (
		currThread = sdata->gGT->threadBuckets[TRACKING].thread; 
		currThread != NULL;
		currThread = currThread->siblingThread
	) 
  {
	struct TrackerWeapon* tw = 
		currThread->object;
	  
    if (tw->driverTarget != d)
		continue;
	
	struct Instance* dInst = d->instSelf;
	struct Instance* currInst = currThread->inst;
		
	if(
		// get distance between posX and posZ of 
		// driver->instSelf->position, and tracker's position, 
		distX = dInst->matrix.t[0] - currInst->matrix.t[0],
		distZ = dInst->matrix.t[2] - currInst->matrix.t[2],
		
		// if this is a new closest distance
		distX = distX * distX + distZ * distZ, distX < smallestDist
	  )
	
	{
		// save closest distance
		smallestDist = distX;
		closestTh = currThread;
	}
  }
  // return thread of closest tracker
  return closestTh;
}