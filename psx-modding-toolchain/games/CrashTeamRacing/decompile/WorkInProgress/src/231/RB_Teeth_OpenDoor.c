#include <common.h>

void RB_Teeth_ThTick(struct Thread*);

void DECOMP_RB_Teeth_OpenDoor(struct Instance* inst)
{
  struct Thread* teethTh = inst->thread;
  
  // if there is no thread,
  // just in case it wasn't initialized
  if (teethTh == NULL) 
  {
	
	// 0x8 = size
	// 0 = no relation to param4
	// 0x300 flag = SmallStackPool
	// 0x3 = "static" thread bucket
    teethTh = THREAD_BirthWithObject(0x80303,RB_Teeth_ThTick,s_teeth_800b9de8,0);
	
    inst->thread = teethTh;
	
    if (teethTh == NULL) 
	{
      return;
    }
	
    teethTh->inst = inst;
	
    ((struct Teeth*)teethTh->object)->timeOpen = 0;
  }
  
  // play sound,
  // teeth opening
  PlaySound3D(0x75,inst);
  
  // door is open
  ((struct Teeth*)teethTh->object)->direction = 1;
  
  // enable access through a door (disable collision)
  sdata->doorAccessFlags |= 1;
  
  return;
}