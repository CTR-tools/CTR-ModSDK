#include <common.h>

void RB_ShieldDark_ThTick(struct Thread *th)
{
  u_short shieldFlags;
  short sVar4;
  int i;
  int iVar8;
  int rotY;
  struct ShieldBomb *bomb;
  struct TileView *view;
  short pos[3];

  struct GameTracker *gGT = sdata->gGT;
  struct Instance *shieldInst = th->inst;
  struct Shield *shield = th->object;
  struct Instance *colorInst = colorInst;
  struct Instance *highlightInst = highlightInst;

  struct Driver *player = th->parentThread->object;

  // if highlight cooldown is gone
  if (shield->highlightTimer == 0)
  {
    shield->highlightRot[1] += 0x100;

    // highlight is now visible
    highlightInst->flags &= ~(0x80);

    rotY = shield->highlightRot[1];

    iVar8 = rotY;
    if (rotY < 0)
    {
      iVar8 = rotY + 0xfff;
    }

    // if highlight is finished
    if ((rotY + (iVar8 >> 12) * -0x1000) == 0x400)
    {
      // cooldown is 30 frames (one second)
      shield->highlightTimer = FPS_DOUBLE(30);

      shield->highlightRot[1] = 0xc00;

      // make highlight invisible
      highlightInst->flags |= 0x80;
    }
  }

  // if highlight cooldown is not done
  else
  {
    // decrease counter, make invisible when this is zero
    shield->highlightTimer--;

    // make invisible
    highlightInst->flags |= 0x80;

    // if timer runs out (last frame)
    if (shield->highlightTimer == 0)
    {
      // make visible
      highlightInst->flags &= ~(0x80);
    }
  }

  // If the driver that used this weapon is visible
  if (player->invisibleTimer == 0)
  {

    // if numPlyrCurrGame is not zero
    if (gGT->numPlyrCurrGame != 0)
    {
      struct InstDrawPerPlayer idpp * = INST_GETIDPP(shieldInst);
      struct InstDrawPerPlayer colorIdpp * = INST_GETIDPP(colorInst);
      struct InstDrawPerPlayer highlightIdpp * = INST_GETIDPP(highlightInst);

      for (i = 0; i < gGT->numPlyrCurrGame; i++)
      {
        view = gGT->tileView[i];
        idpp[i].tileView = view;
        colorIdpp[i].tileView = view;
        highlightIdpp[i].tileView = view;
      }
    }
  }
  else
  {
    // if numPlyrCurrGame is not zero
    if (gGT->numPlyrCurrGame != 0)
    {
      struct InstDrawPerPlayer idpp * = INST_GETIDPP(shieldInst);
      struct InstDrawPerPlayer colorIdpp * = INST_GETIDPP(colorInst);
      struct InstDrawPerPlayer highlightIdpp * = INST_GETIDPP(highlightInst);

      for (i = 0; i < gGT->numPlyrCurrGame; i++)
      {
        if (i == player->driverID)
          continue;
        view = gGT->tileView[i];
        idpp[i].tileView = view;
        colorIdpp[i].tileView = view;
        highlightIdpp[i].tileView = view;
      }
    }
  }

  // Copy matrix
  // To: shield instance, highlight instance, etc
  // From: thread (shield) -> parentthread (player) -> object (driver) -> instance
  LHMatrix_Parent(shieldInst, player->instSelf, &pos);
  LHMatrix_Parent(colorInst, player->instSelf, &pos);
  LHMatrix_Parent(highlightInst, player->instSelf, &pos);

  // set rotation variables
  *(int *)&shieldInst->matrix.m[0][0] = 0x1000;
  *(int *)&shieldInst->matrix.m[0][2] = 0;
  *(int *)&shieldInst->matrix.m[1][1] = 0x1000;
  *(int *)&shieldInst->matrix.m[2][0] = 0;
  shieldInst->matrix.m[2][2] = 0x1000;

  // set rotation variables
  *(int *)&colorInst->matrix.m[0][0] = 0x1000;
  *(int *)&colorInst->matrix.m[0][2] = 0;
  *(int *)&colorInst->matrix.m[1][1] = 0x1000;
  *(int *)&colorInst->matrix.m[2][0] = 0;
  colorInst->matrix.m[2][2] = 0x1000;

  // convert 3 rotation shorts into rotation matrix
  ConvertRotToMatrix(&highlightInst->matrix, &shield->highlightRot[0]);

  short scaleXZ;
  short scaleY;

  // if animation is not done
  if (shield->animFrame < 8)
  {
    scaleXZ = ((int *)0x800b2cf4)[shield->animFrame];
    scaleY = ((int *)0x800b2cf6)[shield->animFrame];
    // set scale
    shieldInst->scale[0] = scaleXZ;
    shieldInst->scale[1] = scaleY;
    shieldInst->scale[2] = scaleXZ;

    // set scale
    colorInst->scale[0] = scaleXZ;
    colorInst->scale[1] = scaleY;
    colorInst->scale[2] = scaleXZ;
    shield->animFrame++;
  }
  // if animation is done
  else
  {
    short timerIndex = (gGT->timer % 6);

    scaleXZ = ((short *)0x800b2d40)[timerIndex];
    scaleY = ((short *)0x800b2d42)[timerIndex];

    // set scale
    shieldInst->scale[0] = scaleXZ;
    shieldInst->scale[1] = scaleY;
    shieldInst->scale[2] = scaleXZ;

    // set scale
    colorInst->scale[0] = scaleXZ;
    colorInst->scale[1] = scaleY;
    colorInst->scale[2] = scaleXZ;

    // set scale
    highlightInst->scale[0] = scaleXZ;
    highlightInst->scale[1] = scaleY;
    highlightInst->scale[2] = scaleXZ;
  }

  // if this is not a blue shield,
  // meaning it must fade eventually
  if ((shield->flags & 4) == 0)
  {
    // duration
    short duration = shield->duration;

    // if out of time
    if (duration == 0)
    {
      // erase bubble instance from driver
      player->instBubbleHold = NULL;

      goto LAB_800b0d6c;
    }

    // subtract 32ms by hand, instead of using in-game timer?
    duration -= FPS_DOUBLE(32);
    shield->duration = duration;

    // last full second?
    if (duration < FPS_DOUBLE(1920))
    {
      sVar4 = (short)(((60 - (iVar8 >> 5)) * 3072) / 60) + 0x400;

      // transparency
      shieldInst->alphaScale = sVar4;
      colorInst->alphaScale = sVar4;
      highlightInst->alphaScale = sVar4;
    }
  }

  shieldFlags = shield->flags;

  if (((((shieldFlags & 1) != 0) || ((shieldFlags & 8) != 0)) ||

       // if race ended for this driver
       ((player->actionsFlagSet & 0x2000000) != 0))

      // if driver is being mask grabbed
      || (player->kartState == KS_MASK_GRABBED))
  {

    if ((shield->flags & 8) != 0)
    {
      view = gGT->tileView[player->driverID];

      view->fadeFromBlack_currentValue = 0x1fff;
      view->fadeFromBlack_desiredResult = 0x1000;
      view->fade_step = -(0x88);
    }

    shield->animFrame = 0;
    player->instBubbleHold = NULL;

    // RB_ShieldDark_Pop is from being mask-grabbed,
    // or from colliding with another player

    // execute, then assign per-frame funcPtr to thread
    ThTick_SetAndExec(th, RB_ShieldDark_Pop);
    return;
  }

  if ((shieldFlags & 2) == 0)
    return;

  player->instBubbleHold = NULL;
  player->numTimesMissileLaunched++;

  GAMEPAD_ShockFreq(player, 8, 0);
  GAMEPAD_ShockForce1(player, 8, 0x7f);

  // green shield
  u_char model = 0x5e;

  if ((shieldFlags & 4) != 0)
  {
    // blue shield
    model = 0x56;
  }

  // create a thread, get an instance
  struct Instance *bombInst = 
  INSTANCE_BirthWithThread(
            model, 
            s_shieldbomb_800aba04, 
            MEDIUM, OTHER, 
            RB_MovingExplosive_ThTick, 
            0x58,
            player->instSelf->thread);

  // if driver is not an AI (human)
  if ((player->actionsFlagSet & 0x100000) == 0)
  {
    // make driver talk
    VoiceLine_RequestPlay(13, data.charactersIDs[player->driverID], 0x10);
  }

  // copy instance matrices
  for (i = 0; i < 8; i++)
    ((int *)bombInst->matrix.m[0][0])[i] = ((int *)shieldInst->matrix.m[0][0])[i];

  // set funcThDestroy to remove instance from instance pool
  bombInst->thread->funcThDestroy = THREAD_DestroyInstance;

  // set scale (x, y, z) and transparency
  for (i = 0; i < 4; i++)
    ((short *)&bombInst->scale[0])[i] = 0x400;

  // get object from thread
  bomb = bombInst->thread->object;

  // frame timer to zero
  bomb->timer = 0;

  bomb->unk = 0;
  bomb->driverWhoShot = player;
  bomb->driverInst = player->instSelf;
  *(short *)((int)bomb + 0x10) = (short)(player->instSelf->matrix.m[0][2] * 3 >> 7);
  *(short *)((int)bomb + 0x12) = 0;
  *(short *)((int)bomb + 0x14) = (short)(player->instSelf->matrix.m[2][2] * 3 >> 7);
  *(short *)((int)bomb + 0x1e) = player->angle;
  *(short *)((int)bomb + 0x20) = 10;
  *(short *)((int)bomb + 0x22) = 0;
  *(short *)((int)bomb + 0x24) = 0;
  bomb[0x12] = 0;

LAB_800b0d6c:

  // green shield fade away sound
  PlaySound3D(0x58, player);

  // INSTANCE_Death
  // shield and highlight
  INSTANCE_Death(colorInst);
  INSTANCE_Death(highlightInst);

  // This thread is now dead
  th->flags |= 0x800;
}
