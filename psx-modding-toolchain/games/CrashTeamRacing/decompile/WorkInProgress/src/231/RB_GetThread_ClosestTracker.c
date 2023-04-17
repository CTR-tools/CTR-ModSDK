#include <common.h>

struct Thread* DECOMP_RB_GetThread_ClosestTracker(struct Driver* d)
{
  int distX;
  int distZ;
  struct Thread* currThread, t;
  int currDistance;
  
  // assume farthest distance
  currDistance = 0x3fffffff;
  
  // loop through all threads
  for (currThread = sdata->gGT->threadBuckets[4]; currThread != NULL;currThread = currThread->siblingThread) 
  {
    if (
			// if first item in thread's object is param_1,
			// meaning, if tracker is chasing this driver
			((struct Driver*)(currThread->object) == d) &&
			(
				// get distance between posX and posZ of 
				// driver->instSelf->position, and tracker's position, 
				distX = d->instSelf->matrix.t[0] - currThread->inst->matrix.t[0],
				distZ = d->instSelf->matrix.t[2] - currThread->inst->matrix.t[2],
				
				// if this is a new closest distance
				distX = distX * distX + distZ * distZ, distX < currDistance
			)
	  ) 
	{
	  // save closest distance
      currDistance = distX;
      t = currThread;
    }
  }
  // return thread of closest tracker
  return t;
}