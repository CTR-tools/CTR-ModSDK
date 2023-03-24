#include <common.h>

void UI_Map_DrawGhosts(int ptrMap,struct Thread* bucket)
{
  int iconID;
  struct Driver* d;
  struct GameTracker* gGT = sdata->gGT;

  for( /* bucket */ ;
		bucket != 0;
		bucket = bucket->siblingThread
	  )
  {
	d = bucket->object;
	  
	// Need to finish Driver struct
	  
	// if ghost not initialized
    if (*(short*)((int)d + 0x632) == 0) continue;
	  
	// ghost made by player
	if (*(short*)((int)d + 0x630) == 0) 
	{
		// flash red and blue
		
		iconID = 6;
		if ((gGT->timer & 1) != 0)
			iconID = 5;
	}
	
	// ghost is N Tropy or Oxide
	else 
	{
		// N Tropy doesn't flicker
		iconID = 0x11;
	
		// if timeTrialFlags for this track show [ n tropy beaten, oxide open ]
		if((sdata->gameProgress.highScoreTracks[gGT->levelID].timeTrialFlags & 2) != 0)
		{
			// oxide flickers
			
			iconID = 3;
			if ((gGT->timer & 1) != 0)
				iconID = 4;
		}
	}
	
	UI_Map_DrawRawIcon(ptrMap,&bucket->inst->matrix.t[0],0x31,iconID,0,0x1000);
  }
  return;
}
