#include <common.h>

void DECOMP_RB_Burst_CollThBucket(struct ScratchpadStruct *sps, struct Thread *t)
{
  struct GameTracker* gGT;
  struct Driver* target, attacker;
  struct MineWeapon* mw;
  short model;
  unsigned short reason;
  struct Thread* thOther;

  gGT = sdata->gGT;
  target = t->object;
  attacker = mw->instParent->thread->object;
  thOther = sps->Union.ThBuckColl.thread;
  mw = thOther->object;

  model = t->modelIndex;

  // if this is a player of any kind, or robotcar of any kind
  if ((model == 0x18) || (model == 0x3f))
  {
    model = thOther->modelIndex;

    // nitro, green beaker, red beaker, TNT
    if ((model == 6) || (((model == 0x46 || (model == 0x47)) || (model == 0x27))))
    {
      // blasted anyone?
      RB_Hazard_HurtDriver(target, 2, attacker, 2);
    }
    else
    {

      // missile
      if (model == 0x29)
      {
        reason = 3;
      }

      // bomb
      else
      {
        reason = 1;
      }

      // blasted anyone?
      RB_Hazard_HurtDriver(target, 2, attacker, reason);

      if ((int)*(short *)(attacker + 0x552) < *(undefined2 *)(mw + 0x48))
      {
        *(short *)(target + 0x552) = *(undefined2 *)(mw + 0x48);
      }
    }

    // if this driver is not an AI
    if ((target->actionsFlagSet & 0x100000) == 0)
    {
      gGT->tileView[target->driverID].fadeFromBlack_currentValue = 0x1fff;
      gGT->tileView[target->driverID].fadeFromBlack_desiredResult = 0x1000;
      gGT->tileView[target->driverID].fade_step = 0xff78;
    }

    // icon damage timer, draw icon as red
    target->damageColorTimer = 0x1e;

    // get modelID from thread
    model = t->modelIndex;
  }

  // not DYNAMIC_ROCKET
  if (model != 0x29)
  {
    if (model < 0x2a)
    {
      // not nitro and not STATIC_CRATE_TNT
      if ((model != 6) && (model != 0x27))
      {
        return;
      }
    }
    else
    {
      // return if anything that isn't beakers
      if (0x47 < model || model < 0x46) return;
    }
  }

  // if function pointer is valid
  if (t->funcThCollide != NULL)
  {
    // execute funcThCollide
    t->funcThCollide(t, thOther, t->funcThCollide, 3);
  }
  return;
}
 