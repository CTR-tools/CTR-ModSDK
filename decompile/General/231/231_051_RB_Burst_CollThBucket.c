#include <common.h>

void DECOMP_RB_Burst_CollThBucket(struct ScratchpadStruct *sps, struct Thread *t)
{
  struct GameTracker* gGT;
  struct TrackerWeapon* tw;
  short model;
  unsigned short reason;
  struct Thread* weaponTh;

  gGT = sdata->gGT;
  
  weaponTh = sps->Union.ThBuckColl.thread;
  void* weaponObj = weaponTh->object;
  
  struct Driver* attacker;
  struct Driver* victim = t->object;
  model = t->modelIndex;
  
  // if this is a player of any kind, or robotcar of any kind
  if ((model == 0x18) || (model == 0x3f))
  {
    model = weaponTh->modelIndex;

    // nitro, green beaker, red beaker, TNT
    if ((model == 6) || (((model == 0x46 || (model == 0x47)) || (model == 0x27))))
    {
	  attacker = 
		((struct MineWeapon*)weaponObj)->
			instParent->thread->object;
		
      // blasted anyone?
      RB_Hazard_HurtDriver(victim, 2, attacker, 2);
    }
    else
    {
	  // bomb
      reason = 1;
	  
      // missile
      if (model == 0x29)
      {
		// missile
        reason = 3;
      }
	  
	  attacker = 
		((struct TrackerWeapon*)weaponObj)->
			driverParent;

      // blasted anyone?
      RB_Hazard_HurtDriver(victim, 2, attacker, reason);

      if (attacker->longestShot < tw->timeAlive)
		attacker->longestShot = tw->timeAlive;
    }

    // if this driver is not an AI
    if ((victim->actionsFlagSet & 0x100000) == 0)
    {
	  struct PushBuffer* pb = &gGT->pushBuffer[victim->driverID];
		
      pb->fadeFromBlack_currentValue = 0x1fff;
      pb->fadeFromBlack_desiredResult = 0x1000;
      pb->fade_step = 0xff78;
    }

    // icon damage timer, draw icon as red
    victim->damageColorTimer = 0x1e;

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
      if ((0x47 < model) || (model < 0x46)) return;
    }
  }

  // if function pointer is valid
  if (t->funcThCollide != NULL)
  {
    // execute funcThCollide
    t->funcThCollide(t);
  }
  return;
}
 