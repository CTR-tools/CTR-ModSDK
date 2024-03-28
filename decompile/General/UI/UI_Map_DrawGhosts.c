#include <common.h>

void DECOMP_UI_Map_DrawGhosts(int ptrMap,struct Thread* bucket)
{
  int color;
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
		
		color = CORTEX_RED;
		if ((gGT->timer & FPS_DOUBLE(1)) != 0)
			color = CRASH_BLUE;
	}
	
	// ghost is N Tropy or Oxide
	else 
	{
		// N Tropy doesn't flicker
		color = TROPY_LIGHT_BLUE;
	
		// if timeTrialFlags for this track show [ n tropy beaten, oxide open ]
		if((sdata->gameProgress.highScoreTracks[gGT->levelID].timeTrialFlags & 2) != 0)
		{
			// oxide flickers
			
			color = RED;
			if ((gGT->timer & FPS_DOUBLE(1)) != 0)
				color = WHITE;
		}
	}
	
	DECOMP_UI_Map_DrawRawIcon(
		ptrMap, &bucket->inst->matrix.t[0],
		0x31, color, 0, 0x1000);
  }
  return;
}
