#include <common.h>

void DECOMP_RB_Follower_ProcessBucket(struct Thread* t)
{
  char i;
  char id;
  int obj;
  struct Instance* inst;
  struct GameTracker* gGT = sdata->gGT;
  
  // if first thread exists
  if (t != NULL) return;
	// loop through all threads
    for (;t != 0; t = t->siblingThread)
	{
	  // if thread is not dead
      if ((t->flags & 0x800) == 0) 
	  {
        obj = t->object;
		
        inst = t->inst;
        
		// struct Follower (0x18 size in bytes)
		id = ((unsigned int)obj + 4)->driverID;

		for (i = 0; i < gGT->numPlyrNextGame; i++)
		{
			// if this camera does not belong
			// to the driver that shot the weapon
			if (id != i) {
				inst->idpp[i].unkb8 &= 0xffffffbf;
			}
        }
        
        // inst = *(int *)(*(int *)(iVar6 + 8) + 0x34) + uVar4 * 0x88;
        inst->idpp[id].unkb8 &= 0xffffffbf;
      }    
	} 
  return;
}