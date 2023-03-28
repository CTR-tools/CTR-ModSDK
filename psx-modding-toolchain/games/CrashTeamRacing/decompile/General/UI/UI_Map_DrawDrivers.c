#include <common.h>

void UI_Map_DrawDrivers(int ptrMap,struct Thread* bucket,short *param_3)

{
  int kartColor;
  int iconID;
  struct Driver* d;
  struct GameTracker* gGT = sdata->gGT;

  // if 2P or 4P
  if((gGT->numPlyrCurrGame & 1) == 0)
  {
	  // quit, no map drawn
	  return;
  }

  for( /* bucket */ ;
		bucket != 0;
		bucket = bucket->siblingThread,
		*param_3 = *param_3 + 1
	  )
  {
	// Player structure
	d = bucket->object;
		
	// characterID + 5
	kartColor = data.characterIDs[d->driverID] + 5;
	
	// default (AI)
	iconID = 0x31;
	
	// if this is human and not AI
	if ((d->actionsFlagSet & 0x100000) == 0) 
	{
		// If this is an even numbered frame
		if ((gGT->timer & 2) == 0) {
			kartColor = 4;
		}
		
		// If you're in Adventure Arena
		if ((gGT->gameMode1 & 0x100000) != 0)
		{
			// Draw dot for Player on 2D Adv Map
			UI_Map_DrawAdvPlayer(ptrMap,&bucket->inst->matrix.t[0],0x32,kartColor,
						(d->rotCurr.y + 0x800U) | 0x1000,0x800);
		
			continue;
		}
		
		// Player
		iconID = 0x32;
	}
	
	UI_Map_DrawRawIcon(ptrMap,&bucket->inst->matrix.t[0],iconID,(short)kartColor,0,0x1000);
  }
  return;
}