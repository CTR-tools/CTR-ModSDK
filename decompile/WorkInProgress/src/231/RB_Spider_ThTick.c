#include <common.h>

void RB_Spider_ThTick(struct Thread* spiderTh)
{
  short sVar2;
  int iVar3;

  struct Driver* victim;
  struct Instance* spiderInst;
  struct Instance* coll;
  struct Spider* spider;

  spider = spiderTh->object;

  spiderInst = spiderTh->inst;

  // delay cycle by varying frames
  if (spider->delay != 0)
  {
    spider->delay--;
    return;
  }

  *(short*)(spider + 0x8) += 1;

  // If spider is on ground
  if (spider->boolNearRoof == 0)
  {
    // if animation finished more than 4 times
    if (4 < spider->animLoopCount)
    {
      // Play animation backwards
      sVar2 = *(short *)spiderInst->animFrame + -1;

      // if animation is at beginning
      if ((int)*(short *)spiderInst->animFrame + -1 < 1)
      {
        // reset animation frame
        spiderInst->animFrame = 0;

        // reset counter
        spider->animLoopCount = 0;

        // spider is now at ceiling
        spider->boolNearRoof = 1;

        // set animation to WiggleLegsAndTeeth
        goto LAB_800b9a14;
      }

      // set new animation frame
      spiderInst->animFrame = sVar2;

      // last frame of last animation
      if (sVar2 == 0xc)
      {
        // play sound: spider move up
        PlaySound3D(0x79, spiderInst);
      }

      goto LAB_800b9a1c;
    }

    sVar2 = spiderInst->animFrame;

    iVar3 = INSTANCE_GetNumAnimFrames(spiderInst);

    // if animation is done
    if (iVar3 <= (int)sVar2 + 1)
    {
      // restart animation
      spiderInst->animFrame = 0;

      // increment number of times animation finishes
      sVar2 = spider->animLoopCount;
      spider->animLoopCount = sVar2 + 1;

      // if animation finishes 5 times
      if (sVar2 + 1 == 5)
      {
        // set animation to zero
        spiderInst->animIndex = 0;

        sVar2 = INSTANCE_GetNumAnimFrames(spiderInst, 0);

        // set animation frame to last frame
        spiderInst->animFrame = sVar2 + -1;
      }
      goto LAB_800b9aa8;
    }
  }

  // if spider is near ceiling
  else
  {
    // if spider animation played more than 4 times
    if (4 < spider->animLoopCount)
    {
      sVar2 = spiderInst->animFrame;

      iVar3 = INSTANCE_GetNumAnimFrames(spiderInst, 0);

      // if animation is not done
      if ((int)sVar2 < iVar3 - 1)
      {
        spiderInst->animFrame += 1;
      }

      // if animation finished
      else
      {
        // reset animation counter
        spider->animLoopCount = 0;

        // move spider to ground
        spider->boolNearRoof = 0;
      LAB_800b9a14:

        // set animation to WiggleLegsAndTeeth
        spiderInst->animIndex = 1;
      }
    LAB_800b9a1c:

      spiderInst->matrix.t[1] = (int)spiderInst->instDef->pos[1] + (int)((short *)0x800b9da4)[spiderInst->animFrame];

      // if animation frame is less than 11
      if ((int)spiderInst->animFrame < 0xb)
      {
        // change spider scaleX and scaleZ based on animation frame

        // scaleX
        spider->inst->scale[0] = (short)(((int)spiderInst->animFrame << 0xc) / 10) + 0x1800;

        // scaleZ
        spider->inst->scale[2] = (short)(((int)spiderInst->animFrame << 0xc) / 10) + 0x1800;
      }
      goto LAB_800b9aa8;
    }

    sVar2 = spiderInst->animFrame;

    iVar3 = INSTANCE_GetNumAnimFrames(spiderInst);

    // if animation is finished
    if (iVar3 - 1 <= (int)sVar2)
    {
      // restart animation to frame zero
      spiderInst->animFrame = 0;

      // increment number of times animation finishes
      sVar2 = spider->animLoopCount;
      spider->animLoopCount = sVar2 + 1;

      // if animation finishes 5 times
      if ((short)(sVar2 + 1) == 5)
      {
        // set animation to ChangePosition
        spiderInst->animIndex = 0;

        // set animation frame to zero
        spiderInst->animFrame = 0;

        // play sound: spider move down
        PlaySound3D(0x7a, spiderInst);
      }
      goto LAB_800b9aa8;
    }
  }

  // increment animation frame
  spiderInst->animFrame += 1;

LAB_800b9aa8:

  // check for collision with all Players
  coll = LinkedCollide_Radius(spiderInst, spiderTh, sdata->gGT->threadBuckets[PLAYER], 0x9000);

  // if there is no collision
  if (coll == 0)
  {
    // check for collision with all robot cars
    coll = LinkedCollide_Radius(spiderInst, spiderTh, sdata->gGT->threadBuckets[ROBOT], 0x9000);

    // if there is no collision
    if (coll == 0)
    {
      // check for collision with all Mines (tnts, beakers, etc)
      coll = LinkedCollide_Radius(spiderInst, spiderTh, sdata->gGT->threadBuckets[MINE], 0x9000);

      // if there is a collision
      if (coll != 0)
      {
        coll->thread->funcThCollide(coll->thread);
      }
    }
    // if you collide with robotcar
    else
    {
      RB_Hazard_HurtDriver(coll->thread->object, 1, 0, 0);
    }
  }

  // if you collide with player
  else
  {
    victim = coll->thread->object;

    // spin out
    spiderInst = RB_Hazard_HurtDriver(victim, 1, 0, 0);

    if ((spiderInst != 0) && (victim->kartState != KS_SPINNING))
    {
      // Play sound
      OtherFX_Play(0x7b, 1);

      // make driver talk
      VoiceLine_RequestPlay(1, data.characterIDs[victim->driverID], 0x10);
    }
  }
  return;
}