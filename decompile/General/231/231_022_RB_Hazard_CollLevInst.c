#include <common.h>

//  (tnt, potion, warpball, etc) (not hazard? moving explosive?)

unsigned short DECOMP_RB_Hazard_CollLevInst(struct ScratchpadStruct *sps, struct Thread *th)
{
  unsigned short flag;
  short model;
  struct Instance* inst;
  struct InstDef* instdef;
  struct MetaDataMODEL* meta;

  // Check if the hitbox flag has the collision bit set and if InstDef is not NULL
  if ((sps->bspHitbox->flag & 0x80) &&
      (instdef = sps->bspHitbox->data.hitbox.instDef) != NULL)
  {
    inst = instdef->ptrInstance;
    model = inst->model->id;

    // Get the metadata for the model
    meta = DECOMP_COLL_LevModelMeta(model);

    // Check if LInC is not nullptr
    if (meta->LInC != NULL)
    {
      // Execute LInC, create a thread for this instance, and let it run thread->funcThCollide upon collision
      flag = meta->LInC(inst, th, sps);

	  // if not PU_WUMPA_FRUIT
      if (model != 2) 
	  {
		// useless
        if (model < 2) {
          return flag;
        }
		
		// anything except for
		// 7: PU_FRUIT_CRATE,
		// 8: PU_RANDOM_CRATE (weapon box)
        if (8 < model) {
          return flag;
        }
        if (model < 7) {
          return flag;
        }
      }
      return 0;
    }
  }
  
  // make potion open teeth,
  // or make warpball turn around
  return 1;
}
