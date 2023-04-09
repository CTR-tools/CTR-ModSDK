#include <common.h>

void DECOMP_AH_Garage_Open(int collisionDataScratchpad,struct Thread* garageThread)
{
  short sound;
  struct Instance* garageInst;
  struct BossGarageDoor* garage;
  
  // thread -> modelIndex == "player" of any kind
  if (garageThread->modelIndex == 0x18) 
  {
	// collisionDataScratchpad -> thread -> object
    garage = (struct BossGarageDoor*)(((struct Thread*)collisionDataScratchpad + 0x18)->object);
	
	// collisionDataScratchpad -> thread -> instance
    garageInst = (((struct Thread*)collisionDataScratchpad + 0x18)->inst);
	
    if (
			// if door is not opening
			(garage->direction != 1) && 
			
			// if door is closed,
			// if posY is the same as instDef posY
			(garageInst->matrix.t[1] == garageInst->instDef->pos[1])
       ) 
	{
	  // if you are not in gemstone valley
	  // play sound of normal boss door opening
      sound = 0x95;
	  
	  // Level ID
	  // if you are in Gemstone Valley
      if (sdata->gGT->levelID == 0x19) 
	  {
		// play sound of oxide door opening
        sound = 0x96;
      }
	  
	  // Play sound
      OtherFX_Play(sound,1);
    }
	
	// door is now opening
    garage->direction = 1;
	
	// enable access through a door (disable collision)
    sdata->doorAccessFlags |= 1;
  }
  return;
}