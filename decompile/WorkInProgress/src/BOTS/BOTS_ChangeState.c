#include <common.h>

// param4 - reason
undefined4 DECOMP_BOTS_ChangeState(struct Driver *driverVictim, int damageType, struct Driver *driverAttacker, int damageReason)
{
  int iVar2;

  *(undefined *)(driverVictim + 0x4ff) = 0;

  // if racer is being mask grabbed
  if (driverVictim->kartState == KartState.MASK_GRABBED)
  {
    return 0;
  }
  // if racer is not being mask grabbed
  // set kart state to normal
  driverVictim->kartState = 0;

  switch (damageType)
  {

  // if racer state is "normal"
  case 0:
    if ((*(uint *)(driverVictim + 0x5b0) & 2) != 0)
    {
      return 0;
    }
    break;

  // if racer is spinning out
  case 1:
  case 4:

    // if driver is not blasted or spinning out,
    // before spinning out a second time
    if ((*(uint *)(driverVictim + 0x5b0) & 2) == 0)
    {
      *(undefined2 *)(driverVictim + 0x5ba) = 1;
      *(undefined2 *)(driverVictim + 0x5c4) = 0;

      if (
          // Player / AI structure + 0x4a shows driver index (0-7)
          // if AI is oxide or
          (Data->characterIDs[driverVictim->driverID] != 0xf) ||

          // if racer is not on the ground
          ((driverVictim->actionsFlagSet & 1) != 0))
      {
        // set Reserves, outside turbo and ? to 0
        driverVictim->reserves = 0;
        driverVictim->turbo_outsideTimer = 0;
        *(undefined4 *)(driverVictim + 0x5cc) = 0;

        // Player / AI structure + 0x4a shows driver index (0-7)

        // if AI is oxide
        if (Data->characterIDs[driverVictim->driverID] != 0xf)
        {
          // divide speed by 2
          iVar2 = *(int *)(driverVictim + 0x5d4) >> 1;
        }

        // if the AI is any other character
        else
        {
          // divide speed by 4
          iVar2 = *(int *)(driverVictim + 0x5d4) >> 2;
        }

        // set new AI speed
        *(int *)(driverVictim + 0x5d4) = iVar2;
      }
      *(undefined4 *)(driverVictim + 0x5c8) = 0x300;

      // AI is not in progress cooldown
      *(undefined4 *)(driverVictim + 0x604) = 0;

      // driver is now spinning out
      *(uint *)(driverVictim + 0x5b0) |= 2;
    }

    // instead of 1
    if (damageType == 4)
    {
      // driver -> instance -> thread -> modelIndex == [any human]
      // This happens when player finishes race and then becomes robotcar
      if ((*(short *)(*(int *)(driverVictim->instSelf + 0x6c) + 0x44) == 0x18) &&

          // if you are not being burned
          (driverVictim->burnTimer == 0))
      {
        OtherFX_Play(0x69, 1); // 0x69 - FlameJet_Burn
      }

      // increase number of frames to be burned
      driverVictim->burnTimer = 0xf00;
    }
    break;

  // Racer is blasted
  case 2:
    *(undefined *)(driverVictim + 0x626) = 0; // 0x8008DC9A

    *(undefined2 *)(driverVictim + 0x5c4) = 0;
    *(undefined2 *)(driverVictim + 0x5ba) = 2;

    driverVictim->reserves = 0;
    driverVictim->turbo_outsideTimer = 0;

    *(undefined4 *)(driverVictim + 0x5cc) = 0; // 0x8008DC40 //0x0FF1FEB6
    // VelY of AI when blasted (const 0x300),
    // to throw them into the air
    *(undefined4 *)(driverVictim + 0x5d0) = sdata->AI_VelY_WhenBlasted_0x3000; // change y-velocity

    // if driver is not already blasted before being blasted again
    if ((*(uint *)(driverVictim + 0x5b0) & 2) == 0)
    {
      *(int *)(driverVictim + 0x5d4) = *(int *)(driverVictim + 0x5d4) >> 3;
      *(int *)(driverVictim + 0x5f4) = *(int *)(driverVictim + 0x5f4) + 0x4000;
    }

    // AI is not in progress cooldown
    *(undefined4 *)(driverVictim + 0x604) = 0;

    // Kart Emote ID = 0
    driverVictim->matrixArray = 0;

    // driver is now blasted
    *(uint *)(driverVictim + 0x5b0) |= 2;

    // if is nullPtr
    if (driverAttacker == 0)
    {
      return 1;
    }
    // if param3 holds a pointer
    // if this driver is not an AI
    if ((driverAttacker->actionsFlagSet & 0x100000) == 0)
    {
      // Make driver talk
      Voiceline_RequestPlay(1, (int)Data->characterIDs[driverVictim->driverID], 0x10);
    }
    break;

  // if racer was damaged by squish-inducing object
  case 3:
    *(undefined2 *)(driverVictim + 0x5c4) = 0;

    // driver -> instance -> thread -> modelIndex == "player" of any kind
    if ((*(short *)(*(int *)(driverVictim->instSelf + 0x6c) + 0x44) == 0x18) &&
        (*(int *)(driverVictim + 0x5c8) == 0))
    {
      OtherFX_Play(0x5a, 1); // 0x5A - squished
    }
    *(undefined2 *)(driverVictim + 0x5ba) = 3;
    *(undefined4 *)(driverVictim + 0x5c8) = 0x300;
    *(undefined2 *)(driverVictim + 0x5bc) = 0xf00;

    driverVictim->squishTimer = 0xf00; // milliseconds

    driverVictim->reserves = 0;
    driverVictim->turbo_outsideTimer = 0;

    *(undefined4 *)(driverVictim + 0x5cc) = 0;
    *(undefined4 *)(driverVictim + 0x5d0) = 0;

    // AI is not in progress cooldown
    *(undefined4 *)(driverVictim + 0x604) = 0;

    *(int *)(driverVictim + 0x5d4) = *(int *)(driverVictim + 0x5d4) >> 1;
    *(uint *)(driverVictim + 0x5b0) |= 6;
    break;

  // if racer is being mask grabbed?
  case 5:
    *(undefined2 *)(driverVictim + 0x5c4) = 0;
    *(undefined4 *)(driverVictim + 0x5d4) = 0;
    *(undefined4 *)(driverVictim + 0x5d0) = 0;
    *(undefined4 *)(driverVictim + 0x5cc) = 0;

    // make invisible
    driverVictim->instSelf->flags |= 0x80;

    *(undefined2 *)(driverVictim + 0x5bc) = 0xd20;
    *(undefined2 *)(driverVictim + 0x5ba) = 5;

    // racer is being mask grabbed
    *(undefined *)(driverVictim + 0x376) = 5;

    *(uint *)(driverVictim + 0x5b0) = *(uint *)(driverVictim + 0x5b0) | 6;

    // driver -> instance -> thread
    // TODO: Inline this below
    struct Thread* thread_1 = *(int *)(driverVictim->instSelf + 0x6c);

    // allow this thread to ignore all collisions,
    // cause mask will handle collisions for us
    // 0x1000 draw transparent (not for ghosts)
    thread_1->flags |= 0x1000;
    break;

  default:
    // set AI progress cooldown to 0x3C
    *(undefined4 *)(driverVictim + 0x604) = 0x3c;
  }

  // === Count Statistics ===
  // Exactly the same as Player_ChangeState

  if ((driverAttacker != 0) && (damageType != 0))
  {
    *(char *)(driverAttacker + 0x559) = *(char *)(driverAttacker + 0x559) + '\x01';
    if (damageReason == 3)
    {
      *(char *)(driverAttacker + 0x557) = *(char *)(driverAttacker + 0x557) + '\x01';
    }
    else
    {
      if (damageReason < 4)
      {
        if (damageReason == 1)
        {
          *(char *)(driverAttacker + 0x55a) = *(char *)(driverAttacker + 0x55a) + '\x01';
        }
      }
      else
      {
        if (damageReason != 4)
        {
          return 1;
        }
        *(char *)(driverAttacker + 0x556) = *(char *)(driverAttacker + 0x556) + '\x01';
      }
    }
  }
  return 1;
}