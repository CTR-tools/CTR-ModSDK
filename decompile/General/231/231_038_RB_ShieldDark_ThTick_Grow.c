#include <common.h>

void DECOMP_RB_ShieldDark_ThTick_Grow(struct Thread *th)
{
  u_short shieldFlags;
  short sVar4;
  int i;
  int rotY;
  struct TrackerWeapon* tw;
  struct PushBuffer* pb;

  struct GameTracker* gGT = sdata->gGT;
  struct Instance* shieldInst = th->inst;
  struct Shield* shield = th->object;
  struct Instance* colorInst = shield->instColor;
  struct Instance* highlightInst = shield->instHighlight;

  struct Thread* playerTh = th->parentThread;
  struct Driver* player = playerTh->object;
  struct Instance* driverInst = playerTh->inst;

  // if highlight cooldown is gone
  if (shield->highlightTimer == 0)
  {
    shield->highlightRot[1] += FPS_HALF(0x100);

    // highlight is now visible
    highlightInst->flags &= ~(0x80);

    rotY = shield->highlightRot[1];

    int iVar8 = rotY;
    if (rotY < 0)
      iVar8 = rotY + 0xfff;

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

  struct InstDrawPerPlayer* idpp = INST_GETIDPP(shieldInst);
  struct InstDrawPerPlayer* colorIdpp = INST_GETIDPP(colorInst);
  struct InstDrawPerPlayer* highlightIdpp = INST_GETIDPP(highlightInst);

  // If the driver that used this weapon is visible
  if (player->invisibleTimer == 0)
  {
      for (i = 0; i < gGT->numPlyrCurrGame; i++)
      {
        pb = &gGT->pushBuffer[i];
        idpp[i].pushBuffer = pb;
        colorIdpp[i].pushBuffer = pb;
        highlightIdpp[i].pushBuffer = pb;
      }
  }
  
  // if driver is not invisible
  else
  {
      for (i = 0; i < gGT->numPlyrCurrGame; i++)
      {
        if (i == player->driverID)
          continue;

        idpp[i].pushBuffer = 0;
        colorIdpp[i].pushBuffer = 0;
        highlightIdpp[i].pushBuffer = 0;
      }
  }

  short pos[3];
  pos[0] = 0; 
  pos[1] = 0; 
  pos[2] = 0;

  // Copy matrix
  // To: shield instance, highlight instance, etc
  // From: thread (shield) -> parentthread (player) -> object (driver) -> instance
  LHMatrix_Parent(shieldInst, 	driverInst, &pos[0]);
  LHMatrix_Parent(colorInst, 	driverInst, &pos[0]);
  LHMatrix_Parent(highlightInst,driverInst, &pos[0]);

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
    scaleXZ = ((int *)0x800b2cf4)[shield->animFrame*2+0];
    scaleY =  ((int *)0x800b2cf4)[shield->animFrame*2+1];
	
    // set scale
    shieldInst->scale[0] = WIDE_34(scaleXZ);
    shieldInst->scale[1] = scaleY;
    shieldInst->scale[2] = scaleXZ;

    // set scale
    colorInst->scale[0] = WIDE_34(scaleXZ);
    colorInst->scale[1] = scaleY;
    colorInst->scale[2] = scaleXZ;
	
	#ifdef USE_60FPS
	if(sdata->gGT->timer & 1)
	#endif
		// next frame
		shield->animFrame++;
  }
  
  // if animation is done
  else
  {
    short timerIndex = 
		(
			(gGT->timer >> FPS_RIGHTSHIFT(0))
			% 6
		);

    scaleXZ = ((short *)0x800b2d40)[timerIndex*2+0];
    scaleY =  ((short *)0x800b2d40)[timerIndex*2+1];

    // set scale
    shieldInst->scale[0] = WIDE_34(scaleXZ);
    shieldInst->scale[1] = scaleY;
    shieldInst->scale[2] = scaleXZ;

    // set scale
    colorInst->scale[0] = WIDE_34(scaleXZ);
    colorInst->scale[1] = scaleY;
    colorInst->scale[2] = scaleXZ;

    // set scale
    highlightInst->scale[0] = scaleXZ;
    highlightInst->scale[1] = scaleY;
    highlightInst->scale[2] = WIDE_34(scaleXZ);
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

    // subtract 32ms by hand
    duration -= FPS_HALF(32);
    shield->duration = duration;

    // 2.0 seconds
    if (duration < 1920)
    {
      sVar4 = (short)(((60 - (duration >> 5)) * 3072) / 60) + 0x400;

      // transparency
      shieldInst->alphaScale = sVar4;
      colorInst->alphaScale = sVar4;
      highlightInst->alphaScale = sVar4;
    }
  }

  shieldFlags = shield->flags;

  if (
		((shieldFlags & 1) != 0) || 
		((shieldFlags & 8) != 0) ||
		
		// if race ended for this driver
		((player->actionsFlagSet & 0x2000000) != 0) ||

		// if driver is being mask grabbed
		(player->kartState == KS_MASK_GRABBED)
	  )
  {

    if ((shieldFlags & 8) != 0)
    {
      pb = &gGT->pushBuffer[player->driverID];

      pb->fadeFromBlack_currentValue = 0x1fff;
      pb->fadeFromBlack_desiredResult = 0x1000;
      pb->fade_step = -(0x88);
    }

    shield->animFrame = 0;
    player->instBubbleHold = NULL;

    // execute, then assign per-frame funcPtr to thread
	void RB_ShieldDark_ThTick_Pop();
    ThTick_SetAndExec(th, RB_ShieldDark_ThTick_Pop);
    return;
  }

  if ((shieldFlags & 2) == 0)
    return;

  player->instBubbleHold = NULL;
  player->numTimesMissileLaunched++;

  DECOMP_GAMEPAD_ShockFreq(player, 8, 0);
  DECOMP_GAMEPAD_ShockForce1(player, 8, 0x7f);

  // green shield
  u_char model = 0x5e;

  if ((shieldFlags & 4) != 0)
  {
    // blue shield
    model = 0x56;
  }

  // create a thread, get an instance
  struct Instance *bombInst = 
	DECOMP_INSTANCE_BirthWithThread(
		model, 0, MEDIUM, OTHER, 
        DECOMP_RB_MovingExplosive_ThTick, 
        sizeof(struct TrackerWeapon),
        playerTh);
		
  struct Thread* bombTh = bombInst->thread;
  bombTh->funcThDestroy = DECOMP_PROC_DestroyInstance;

  #ifdef USE_ONLINE
  if(player->driverID == 0)
  #else
  // if driver is not an AI (human)
  if ((player->actionsFlagSet & 0x100000) == 0)
  #endif
  {
    // make driver talk
    Voiceline_RequestPlay(13, data.characterIDs[player->driverID], 0x10);
  }

  // copy position and rotation from one instance to another 
  *(int*)&bombInst->matrix.m[0][0] = *(int*)&shieldInst->matrix.m[0][0];
  *(int*)&bombInst->matrix.m[0][2] = *(int*)&shieldInst->matrix.m[0][2];
  *(int*)&bombInst->matrix.m[1][1] = *(int*)&shieldInst->matrix.m[1][1];
  *(int*)&bombInst->matrix.m[2][0] = *(int*)&shieldInst->matrix.m[2][0];
  bombInst->matrix.m[2][2] = shieldInst->matrix.m[2][2];
  bombInst->matrix.t[0] = shieldInst->matrix.t[0];
  bombInst->matrix.t[1] = shieldInst->matrix.t[1];
  bombInst->matrix.t[2] = shieldInst->matrix.t[2];

  // set scale (x, y, z) and transparency
  for (i = 0; i < 4; i++)
    bombInst->scale[i] = 0x400;

  // get object from thread
  tw = bombTh->object;

  tw->flags = 0;
  tw->driverTarget = 0;
  tw->timeAlive = 0;
  tw->audioPtr = 0;
  tw->frameCount_Blind = 0;
  
  tw->driverParent = player;
  tw->instParent = driverInst;
  
  // do NOT patch for 60fps,
  // velocity uses elapsedTime
  tw->vel[1] = 0;
  tw->vel[0] = (driverInst->matrix.m[0][2] * 3) >> 7;
  tw->vel[2] = (driverInst->matrix.m[2][2] * 3) >> 7;
  
  tw->rotY = player->angle;
  tw->frameCount_DontHurtParent = FPS_DOUBLE(10);

LAB_800b0d6c:

  // green shield fade away sound
  PlaySound3D(0x58, shieldInst);

  // shield and highlight
  DECOMP_INSTANCE_Death(colorInst);
  DECOMP_INSTANCE_Death(highlightInst);

  // This thread is now dead
  th->flags |= 0x800;
}

 