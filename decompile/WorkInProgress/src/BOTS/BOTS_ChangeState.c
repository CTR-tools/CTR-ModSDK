#include <common.h>

// param4 - reason
u_char DECOMP_BOTS_ChangeState(
	struct Driver *victim, int damageType, 
	struct Driver *attacker, int damageReason)
{
  int newSpeed;

  victim->ChangeState_param2 = 0;

  if (victim->kartState == KS_MASK_GRABBED)
  {
    return 0;
  }
  
  // if racer is not being mask grabbed
  // set kart state to normal
  victim->kartState = KS_NORMAL;

  switch (damageType)
  {
  // if racer state is "normal"
  case 0:
    if ((victim->botFlags & 2) != 0)
    {
      return 0;
    }
    break;

  // if racer is spinning out
  case 1:
  case 4:
    // if driver is not blasted or spinning out,
    // before spinning out a second time
    if ((victim->botFlags & 2) == 0)
    {
      victim->unk5ba = 1;
      *(short *)(victim + 0x5c4) = 0;

      if (
          // Player / AI structure + 0x4a shows driver index (0-7)
          // if AI is oxide or
          (data.characterIDs[victim->driverID] != 0xf) ||

          // if racer is not on the ground
          ((victim->actionsFlagSet & 1) != 0))
      {
        // set Reserves, outside turbo and ? to 0
        victim->reserves = 0;
        victim->turbo_outsideTimer = 0;
        *(int *)(victim + 0x5cc) = 0;

        // Player / AI structure + 0x4a shows driver index (0-7)

        // if AI is oxide
        if (data.characterIDs[victim->driverID] != 0xf)
        {
          // divide speed by 2
          newSpeed = *(int *)(victim + 0x5d4) >> 1;
        }
        // if the AI is any other character
        else
        {
          // divide speed by 4
          newSpeed = *(int *)(victim + 0x5d4) >> 2;
        }

        // set new AI speed
        *(int *)(victim + 0x5d4) = newSpeed;
      }

      *(int *)(victim + 0x5c8) = 0x300;

      // AI is not in progress cooldown
      *(int *)(victim + 0x604) = 0;

      // driver is now spinning out
      victim->botFlags |= 2;
    }

    // instead of 1
    if (damageType == 4)
    {
      // This happens when player finishes race and then becomes robotcar
      if ((victim->instSelf->thread->modelIndex == 0x18) &&
          // if you are not being burned
          (victim->burnTimer == 0))
      {
        OtherFX_Play(0x69, 1); // 0x69 - FlameJet_Burn
      }

      // increase number of frames to be burned
      victim->burnTimer = 0xf00;
    }
    break;

  // Racer is blasted
  case 2:
    victim->unk626 = 0; // 0x8008DC9A

    *(short *)(victim + 0x5c4) = 0;
    victim->unk5ba = 2;

    victim->reserves = 0;
    victim->turbo_outsideTimer = 0;

    *(int *)(victim + 0x5cc) = 0; // 0x8008DC40 //0x0FF1FEB6
	
    // VelY of AI when blasted (const 0x300),
    // to throw them into the air
    *(int *)(victim + 0x5d0) = sdata->AI_VelY_WhenBlasted_0x3000; // change y-velocity

    // if driver is not already blasted before being blasted again
    if ((victim->botFlags & 2) == 0)
    {
      *(int *)(victim + 0x5d4) = *(int *)(victim + 0x5d4) >> 3;
      victim->ai_posBackup[1] += 0x4000;
    }

    // AI is not in progress cooldown
	victim->ai_progress_cooldown = 0;

    victim->matrixArray = 0;

    // driver is now blasted
    victim->botFlags |= 2;

    // if is nullPtr
    if (attacker == 0)
    {
      return 1;
    }
    // if param3 holds a pointer
    // if this driver is not an AI
    if ((attacker->actionsFlagSet & 0x100000) == 0)
    {
      // Make driver talk
      Voiceline_RequestPlay(1, data.characterIDs[victim->driverID], 0x10);
    }
    break;

  // if racer was damaged by squish-inducing object
  case 3:
    *(short *)(victim + 0x5c4) = 0;

    // driver -> instance -> thread -> modelIndex == "player" of any kind
    if ((victim->instSelf->thread->modelIndex == 0x18) &&
        (*(int *)(victim + 0x5c8) == 0))
    {
      OtherFX_Play(0x5a, 1); // 0x5A - squished
    }
    victim->unk5ba = 3;
    *(int *)(victim + 0x5c8) = 0x300;
    *(short *)(victim + 0x5bc) = 0xf00;

    victim->squishTimer = 0xf00; // milliseconds

    victim->reserves = 0;
    victim->turbo_outsideTimer = 0;

    *(int *)(victim + 0x5cc) = 0;
    *(int *)(victim + 0x5d0) = 0;

    // AI is not in progress cooldown
    victim->ai_progress_cooldown = 0;

    *(int *)(victim + 0x5d4) = *(int *)(victim + 0x5d4) >> 1;
    victim->botFlags |= 6;
    break;

  // if racer is being mask grabbed?
  case 5:
    *(short *)(victim + 0x5c4) = 0;
    *(int *)(victim + 0x5d4) = 0;
    *(int *)(victim + 0x5d0) = 0;
    *(int *)(victim + 0x5cc) = 0;

    // make invisible
    victim->instSelf->flags |= 0x80;

    victim->unk5bc[0] = 0xd20;
    victim->unk5ba = 5;

    victim->kartState = KS_MASK_GRABBED;
    victim->botFlags |= 6;

    // TODO: Inline this below
    struct Thread *thread_1 = victim->instSelf->thread;

    // allow this thread to ignore all collisions,
    // cause mask will handle collisions for us
    // 0x1000 draw transparent (not for ghosts)
    thread_1->flags |= 0x1000;
    break;

  default:
    victim->ai_progress_cooldown = 60;
  }

  // === Count Statistics ===
  // Exactly the same as VehPickState_NewState

  if (damageType)
  {
    attacker->numTimesAttacked++;
    switch (damageType){
      case 1:
        attacker->numTimesBombsHitSomeone++;
      case 3:
        attacker->numTimesMissileHitSomeone++;
      case 4:
        attacker->numTimesMovingPotionHitSomeone++;
    }
  }
  return 1;
}