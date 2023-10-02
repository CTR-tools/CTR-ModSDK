#include <common.h>

//  (tnt, potion, warpball, etc) (not hazard? moving explosive?)

unsigned short DECOMP_RB_Hazard_CollLevInst(struct ScratchpadStruct *sps, struct Thread *th)
{
  unsigned short flag;
  short model;
  struct Instance *inst;
  struct InstanceDef *instdef;
  struct MetaDataMODEL *meta;

  // Check if the hitbox flag has the collision bit set and if InstDef is not NULL
  if ((sps->bspHitbox->flag & 0x80) &&
      (instdef = sps->bspHitbox->data.hitbox.instDef) != NULL)
  {
    inst = instdef->ptrInstace;
    model = inst->model->id;

    // Get the metadata for the model
    meta = COLL_LevModelMeta(model);

    // Check if LInC is not nullptr
    if (meta->LInC != NULL)
    {
      // Execute LInC, create a thread for this instance, and let it run thread->funcThCollide upon collision
      flag = meta->LInC(inst, th, sps);

      if (model != PU_WUMPA_FRUIT)
      {
        if (model > PU_RANDOM_CRATE || model < PU_RANDOM_CRATE)
        {
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
