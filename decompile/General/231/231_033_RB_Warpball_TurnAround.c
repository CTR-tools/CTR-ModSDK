#include <common.h>

void DECOMP_RB_Warpball_TurnAround(struct Thread* t)
{
  struct TrackerWeapon* tw;
  struct Instance* inst;
  unsigned short flags;
  struct GameTracker* gGT = sdata->gGT;
  short sVar3;
  short rot;
  
  tw = t->object;
  inst = t->inst;
  flags = tw->flags;
  
  if (
		// if not snap to point???
		((flags & 0x100) != 0) || 
		
		// if no driver is being chased
		(tw->driverTarget == NULL)
	  ) 
  {
    if ((flags & 4) != 0) 
	{
		tw->flags = (flags & 0xfffb) | 0x208;
    }
	
    tw->vel[0] = -tw->vel[0];
    tw->vel[1] = -tw->vel[1];
    tw->vel[2] = -tw->vel[2];
	
    inst->matrix.t[0] += ((int)tw->vel[0] * gGT->elapsedTimeMS) >> 5;
    inst->matrix.t[1] += ((int)tw->vel[1] * gGT->elapsedTimeMS) >> 5;
    inst->matrix.t[2] += ((int)tw->vel[2] * gGT->elapsedTimeMS) >> 5;
    
	// increment counter
	tw->turnAround++;
    
	if (
			// if count too high
			(0x78 < sVar3) || 
			
			// pointer to driver being chased,
			// is null, so warpball is chasing nobody
			(tw->driverTarget == 0)
		) 
	{
      tw->driverParent->instBombThrow = 0;
	  
	  // play sound warpball death
      PlaySound3D(0x4f,inst);
      
	  RB_Warpball_Death(t);
    }
	
	// if attempted to turn around 3 times
    if ((tw->turnAround & 3) == 0) 
	{
	  tw->ptrNodeNext = tw->ptrNodeCurr;
	  
	  struct CheckpointNode* first =
		&sdata->gGT->level1->ptr_restart_points[0];
	  
	  // set new end to 10 path indices ahead of current
      tw->ptrNodeCurr = &first[tw->ptrNodeCurr->nextIndex_backward];
    }
	
	struct CheckpointNode* cn =
		tw->ptrNodeCurr;
	
	// rotation
    rot = ratan2(
			cn->pos[0] - inst->matrix.t[0], 
			cn->pos[2] - inst->matrix.t[2]
		);
		
	// rotation
    tw->dir[1] = rot;
  }
  return;
}
 