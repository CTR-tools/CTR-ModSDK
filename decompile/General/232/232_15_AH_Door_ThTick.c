#include <common.h>

// current 2208
// budget 3276

void DECOMP_AH_Door_ThTick(struct Thread* t)
{
  char doorIsOpen;
  short doorID;
  short lev;
  short numKeys;
  u_short hintId;
  u_int chkRewards;
  int i;
  int ratio;
  int distX;
  int distY;
  int distZ;
  int dist;
  int iVar17;
  int iVar18;
  short desiredPos[3];
  short desiredRot[3];
  short* scaler;

  struct GameTracker* gGT = sdata->gGT;
  struct WoodDoor* door = t->object;
  struct Instance* doorInst = t->inst;
  struct Instance* keyInst;
  struct Driver* driver = gGT->drivers[0];
  struct Instance* driverInst;
  struct CameraDC* cDC = gGT->cameraDC;
  int *piVar16;

  doorID = door->doorID;

  // Assume door is closed
  doorIsOpen = false;

  lev = gGT->levelID;

  // check if the door that the player approached is open
  if (door->doorRot[1] == 0x400)
  {
    // door is open
    doorIsOpen = true;
  }

  // Cosine(angle)
  ratio = DECOMP_MATH_Cos((int)doorInst->instDef->rot[1]);

  // X distance of player and door
  distX = doorInst->matrix.t[0] + (ratio * 0x300 >> 0xc) - driver->instSelf->matrix.t[0];

  // Y distance of player and door
  distY = doorInst->matrix.t[1] - driver->instSelf->matrix.t[1];

  // Sine(angle)
  ratio = DECOMP_MATH_Sin((int)doorInst->instDef->rot[1]);

  // Z distance of player and door
  distZ = doorInst->matrix.t[2] + (ratio * 0x300 >> 0xc) - driver->instSelf->matrix.t[2];

  // distance from player and door
  dist = distX * distX + distY * distY + distZ * distZ;

  // If player is close to a door
  if (dist < 0x90000)
  {
    // if door is open
    if (doorIsOpen)
    {
      // enable access through a door (disable collision)
      sdata->doorAccessFlags |= 2;
    }

    // if door is locked
    else
    {
      // remove access (enable collision)
      sdata->doorAccessFlags &= 0xfffffffd;
    }
  }

  // If this is N Sane Beach
  if (lev == 0x1a)
  {

    // if this is beach -> gemstone,
    // must have 1 key
    numKeys = 1;

    // If this is door from beach -> glacier
    if (doorID == 4)
    {
      // must have 2 keys
      numKeys = 2;
    }
  }
  // If not N Sane Beach
  else
  {
    // get number of keys for whichever door is on the hub
    numKeys = D232.arrKeysNeeded[(lev + -0x19)];
  }

  // if in a state where you're seeing the boss key open an adv door,
  // or some other kind of cutscene where you can't move
  if ((gGT->gameMode2 & 4) != 0)
    return;

  // If door is open
  if (doorIsOpen)
  {
    // camera transition, watch door open
    if ((cDC->flags & 0x200) != 0)
    {
      // quit, come back when camera transition ends
      return;
    }

    // check if hint is unlocked
    chkRewards = sdata->advProgress.rewards[3] & 0x20000000;

    // "Congrats on opening this new area..."
    hintId = 7;

  joined_r0x800b06ec:

    // if hint is not unlocked
    if (chkRewards == 0)
    {
      DECOMP_MainFrame_RequestMaskHint(hintId, 0);
    }
    return;
  }

  // == if door is closed ==

  if (
      // if player is far from the door
      (0x8ffff < dist) &&
      // flags
      ((door->camFlags & WdCam_CutscenePlaying) == 0))
  {
    return;
  }

  // if player has less than that amount
  if (gGT->currAdvProfile.numKeys < numKeys)
  {
    // if one key is required
    if (numKeys == 1)
    {
      // check if hint is unlocked
      chkRewards = sdata->advProgress.rewards[3] & 0x8000000;

      // Aku Hint "You must have a boss key"
      hintId = 5;
    }

    // not one...
    else
    {
      // if not 2...
      if (numKeys != 2)
      {
        // no hint for that
        return;
      }

      // if 2 keys are needed to enter

      // check if hint is unlocked
      chkRewards = sdata->advProgress.rewards[4] & 0x100;

      // Aku Hint "You must have two boss keys"
      hintId = 0x12;
    }
	
	// request hint and quit
    goto joined_r0x800b06ec;
  }

  // == door is closed, ready to unlock ==

  // if camera is not transitioning out (yet),
  // while keys are spinning in air (4 seconds)
  if ((door->camFlags & WdCam_FlyingOut) == 0)
  {
    // If the game is paused
    if ((gGT->gameMode1 & 0xf) != 0)
    {
      return;
    }

    // If you are here, game must not be paused

    driver->funcPtrs[0] = DECOMP_VehPhysProc_FreezeEndEvent_Init;

    door->camFlags |= WdCam_CutscenePlaying;

    // if timer is less than four full seconds
    if (door->frameCount_doorOpenAnim < FPS_DOUBLE(0x78))
    {
      if (driver->speedApprox < 0x80)
      {
		// Actually, specLightDir
        desiredPos[0] = -0xc98;
        desiredPos[1] = 0x99f;
        desiredPos[2] = 0x232;

        // if keys are not spawned, create them
        if (door->keyInst[0] == NULL)
        {
          // if number of keys is more than zero
          if (numKeys != 0)
          {
            // spawn instances for every key you have,
            // this makes them spin in a circle before
            // seeing the doors animate open
            for (i = 0; i < numKeys; i++)
            {
			  // name = "key"
              keyInst = DECOMP_INSTANCE_Birth3D(gGT->modelPtr[0x63], 0, t);

              // Set Key Color
              keyInst->colorRGBA = 0xdca6000;

              // specular lighting
              keyInst->flags |= 0x20000;

              driverInst = driver->instSelf;

              keyInst->matrix.m[0][0] = driverInst->matrix.m[0][0];
              keyInst->matrix.m[0][2] = driverInst->matrix.m[0][2];
              keyInst->matrix.m[1][0] = driverInst->matrix.m[1][0];
              keyInst->matrix.m[2][0] = driverInst->matrix.m[2][0];
              keyInst->matrix.m[2][2] = driverInst->matrix.m[2][2];

              // copy position for key from driver
              keyInst->matrix.t[0] = driverInst->matrix.t[0];
              keyInst->matrix.t[1] = driverInst->matrix.t[1];
              keyInst->matrix.t[2] = driverInst->matrix.t[2];

              // set scale to zero
              keyInst->scale[0] = 0;
              keyInst->scale[1] = 0;
              keyInst->scale[2] = 0;

              door->keyInst[i] = keyInst;
            }
          }

          // Make a backup of HUD variable
          door->hudFlags = (char)gGT->hudFlags;

          // Disable HUD
          gGT->hudFlags = 0;

          // For watching hub doors animate open
        }

        // if more than zero
        if (0 < numKeys)
        {
          // loop through all keys
          for (i = 0; i < numKeys; i++)
          {
            keyInst = door->keyInst[i];
            if (keyInst != NULL)
            {
              // if scale < 0xa00
              if (keyInst->scale[0] < 0xa00)
              {
                // increase scale on X, Y, Z
                keyInst->scale[0] += FPS_HALF(0x40);
                keyInst->scale[1] += FPS_HALF(0x40);
                keyInst->scale[2] += FPS_HALF(0x40);
              }

              // if key posY is less than (player posY + 0xa0)
              if (keyInst->matrix.t[1] < (driver->instSelf->matrix.t[1] + 0xa0))
              {
                // increase key posY
                keyInst->matrix.t[1] += FPS_HALF(4);
              }

              if (1 < numKeys)
              {

                iVar18 = i * (0x1000 / numKeys);
                iVar17 = (int)keyInst->scale[0];

                if (iVar17 < 0)
                {
                  iVar17 += 0x1f;
                }

                ratio = DECOMP_MATH_Sin(door->keyOrbit + iVar18);

                keyInst->matrix.t[0] = driver->instSelf->matrix.t[0] + ((iVar17 >> 5) * ratio >> 0xc);

                ratio = DECOMP_MATH_Cos(door->keyOrbit + iVar18);

                keyInst->matrix.t[2] = driver->instSelf->matrix.t[2] + ((iVar17 >> 5) * ratio >> 0xc);
              }

			  piVar16 = &door->keyRot[0];

#ifndef REBUILD_PS1
			  // desiredPos is actually specLightDir in this case, variable re-use
              Vector_SpecLightSpin3D(keyInst, piVar16, &desiredPos[0]);

              // convert 3 rotation shorts into rotation matrix
              ConvertRotToMatrix(&keyInst->matrix, piVar16);
#endif
            }
            door->keyInst[i] = keyInst;
          }
        }
		
        door->keyRot[0] = 0;
        door->keyRot[1] += FPS_HALF(0x40);
        door->keyRot[2] = 0;

        door->keyOrbit += 0x10;

        door->frameCount_doorOpenAnim++;

        // Sound effects when keys float in air

        switch (door->frameCount_doorOpenAnim)
        {
        case FPS_DOUBLE(0x0A):
          DECOMP_OtherFX_Play_LowLevel(0x67, 1, 0xff7680);
          break;
        case FPS_DOUBLE(0x0F):
          DECOMP_OtherFX_Play_LowLevel(0x67, 1, 0xeb8080);
          break;
        case FPS_DOUBLE(0x14):
          DECOMP_OtherFX_Play_LowLevel(0x67, 1, 0xd78a80);
          break;
        case FPS_DOUBLE(0x19):
          DECOMP_OtherFX_Play_LowLevel(0x67, 1, 0xc39480);
          break;
        case FPS_DOUBLE(0x50):
          // unlock door sound
          DECOMP_OtherFX_Play(0x93, 1);
          break;
		case FPS_DOUBLE(0x78):
          // on last frame, doors "creek" open
          DECOMP_OtherFX_Play(0x94, 1);
          break;
		
		default:
		  break;
        }
      }
      return;
    }

    // == After 4 seconds ==

    ratio = DECOMP_MATH_Cos((int)doorInst->instDef->rot[1]);

    i = DECOMP_MATH_Cos((int)doorInst->instDef->rot[1] + 0x400);

    // desired posX for transition
    desiredPos[0] = doorInst->matrix.t[0] + (short)(ratio * 0x312 >> 0xc) +
                    (short)(i * 0x600 >> 0xc);
    // desired posY for transition
    desiredPos[1] = doorInst->matrix.t[1] + 0x17a;

	ratio = DECOMP_MATH_Sin((int)doorInst->instDef->rot[1]);

	i = DECOMP_MATH_Sin((int)doorInst->instDef->rot[1] + 0x400);

    // desired posZ for transition
    desiredPos[2] = doorInst->matrix.t[2] + (short)(ratio * 0x312 >> 0xc) +
                    (short)(i * 0x600 >> 0xc);

    // desired rotation for transition
    desiredRot[0] = doorInst->instDef->rot[0] + 0x800;
    desiredRot[1] = doorInst->instDef->rot[1];
    desiredRot[2] = doorInst->instDef->rot[2];

    // set desired position and rotation for CamerDC transition
    DECOMP_CAM_SetDesiredPosRot(&gGT->cameraDC[0], &desiredPos[0], &desiredRot[0]);

#ifndef REBUILD_PS1
    GAMEPAD_JogCon2(driver, 0, 0);
#endif

    // start camera out transition (in "else" below)
    door->camFlags |= WdCam_FlyingOut;
	
	return;
  }

  // == door is opening ==

  door->doorRot[1] += FPS_HALF(0x10);
  
  // right-hand door rot[x,y,z]
  desiredRot[0] = door->doorRot[0];
  desiredRot[1] = doorInst->instDef->rot[1] - door->doorRot[1];
  desiredRot[2] = door->doorRot[2];
  
  // converted to TEST in rebuildPS1
  ConvertRotToMatrix(&door->otherDoor->matrix, &desiredRot[0]);
  
  // left-hand door rot[x,y,z]
  desiredRot[1] = doorInst->instDef->rot[1] + door->doorRot[1];

  // converted to TEST in rebuildPS1
  ConvertRotToMatrix(&doorInst->matrix, &desiredRot[0]);
  
  // if less than 11 frames have passed,
  // decrease key scale, then quit function
  if (door->keyShrinkFrame < 0xb)
  {
  	scaler = (short*)R232.keyFrame;
  	
  	// loop through 4 keys
  	for (i = 0; i < 4; i++)
  	{
  		keyInst = door->keyInst[i];
  		// if instance exists
  		if (keyInst != NULL)
  		{
  			// decrease scale of key
  			keyInst->scale[0] = scaler[door->keyShrinkFrame];
  			keyInst->scale[1] = scaler[door->keyShrinkFrame];
  			keyInst->scale[2] = scaler[door->keyShrinkFrame];
  		}
  	}
  
  	door->keyShrinkFrame++;
  
  	return;
  }
	
  // loop through 4 keys
  for (i = 0; i < 4; i++)
  {
  	if(door->keyInst[i] != NULL)
  	{
  		DECOMP_INSTANCE_Death(door->keyInst[i]);
  		door->keyInst[i] = NULL;
  	}
  }
	
  // if not last frame of opening door
  if(door->doorRot[1] < 0x400) return;
  
  
  // == Door is fully open ==
    
  if (
      // if this is N Sane Beach
      ((lev == 0x1a) &&
  
       // if this is door #4 (beach -> glacier)
       (doorID == 4)) ||
  
      // if this is lost ruins (ruins -> glacier)
      (lev == 0x1b))
  {
    // open all doors to glacier
    sdata->advProgress.rewards[3] |= 0xc0;
  }
  
  else if (
        // if this is N Sane Beach
        (lev == 0x1a) &&
  
        // Door #5 (beach -> ruins)
        (doorID == 5))
  {
    // record that door is open
    sdata->advProgress.rewards[3] |= 0x10;
  }
    
  // Gemstone valley (cup door)
  else if (lev == 0x19)
  {
    // record that door is open
    sdata->advProgress.rewards[3] |= 0x20;
  }
    
  // Glacier Park (glacier -> citadel)
  else
  {
    // record that door is open
    sdata->advProgress.rewards[3] |= 0x100;
  }
  	
  cDC->flags |= 0x400;
  
  driver->funcPtrs[0] = DECOMP_VehPhysProc_Driving_Init;
  
  // cutscene over
  door->camFlags &= ~(0x10);
  
  // bring HUD back
  gGT->hudFlags = (char)door->hudFlags;
}