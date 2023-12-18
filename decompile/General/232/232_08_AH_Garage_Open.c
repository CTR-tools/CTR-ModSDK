#include <common.h>

void DECOMP_AH_Garage_Open(struct ScratchpadStruct* sps,struct Thread* otherTh)
{
  short sound;
  struct Instance* garageInst;
  struct BossGarageDoor* garage;
  struct Thread* garageThread;
  
  // There's nothing else on the map to collide with the door,
  // skip the IF that was in the original game
#if 0
  // thread -> modelIndex != "player" of any kind
  if (otherTh->modelIndex != 0x18) return;
#endif
  
  garageThread = sps->Union.ThBuckColl.thread;
    
  garage = garageThread->object;
  garageInst = garageThread->inst;
  
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
    if (sdata->gGT->levelID == GEM_STONE_VALLEY) 
    {
  	// play sound of oxide door opening
      sound = 0x96;
    }
    
    // Play sound
    DECOMP_OtherFX_Play(sound,1);
  }
  
  // door is now opening
  garage->direction = 1;
  
  // enable access through a door (disable collision)
  sdata->doorAccessFlags |= 1;
}