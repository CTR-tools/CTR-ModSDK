#include <common.h>

void DECOMP_RB_Burst_CollLevInst(struct ScratchpadStruct* sps,struct BSP* bspHitbox)
{
  short model;
  struct Instance* inst;
  struct InstDef* instdef;
  struct MetaDataMODEL* meta;
  
  instdef = bspHitbox->data.hitbox.instDef;
  if(instdef == NULL) return;
  
  inst = instdef->ptrInstance;
  if(inst == NULL) return;
  
  model = instdef->modelID;
  if(model < 7) return;
  
  // check 7 and 8,
  // 7: PU_FRUIT_CRATE
  // 8: PU_RANDOM_CRATE (weapon box)
  if (model < 9) 
  {
	// skip nullptr checks, nullptr is not possible
    meta = DECOMP_COLL_LevModelMeta(model);
    meta->LInC(inst,sps->Union.ThBuckColl.thread,sps);
	return;
  }
  
  if (model == 0x70) 
    DECOMP_RB_Teeth_OpenDoor(inst);

  return;
}