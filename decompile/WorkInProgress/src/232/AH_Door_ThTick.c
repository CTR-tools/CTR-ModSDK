#include <common.h>

void VehPtr_Freeze_Init(struct Thread *, struct Driver *);
void VehPtr_Driving_Init(struct Thread *, struct Driver *);

void DECOMP_AH_Door_ThTick(struct Thread *doorTh)
{
  char doorIsOpen;
  short doorID;
  short lev;
  short numKeys;
  u_short doorFlags;
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
  short otherRot[3];
  short* scaler;

  struct GameTracker* gGT = sdata->gGT;
  struct WoodDoor* door = doorTh->object;
  struct Instance* doorInst = doorTh->inst;
  struct Instance* keyInst;
  struct Driver* driver = gGT->drivers[0];
  struct Instance* driverInst;
  struct CameraDC* cDC = gGT->cameraDC;
  int *piVar16;

  doorID = *(short *)(door + 0xd);

  // Assume door is closed
  doorIsOpen = false;

  lev = gGT->levelID;

  // check if the door that the player approached is open
  if (
      // If you are on N Sanity Beach
      (lev == 0x1a && (
        // 0x40 -> Door open from Beach to Glacier
        (doorID == 4 && ((sdata->advProgress.rewards[3] & 0x40) != 0)) ||
        // 0x10 -> Door open from Beach to Gemstone Valley
        (doorID == 5 && ((sdata->advProgress.rewards[3] & 0x10) != 0)))) ||
      // Check Gemstone Valley and the door to Gem Cup room
      (lev == 0x19 && ((sdata->advProgress.rewards[3] & 0x20) != 0)) ||
      // Check Lost Ruins and the door to Glacier Park
      (lev == 0x1b && ((sdata->advProgress.rewards[3] & 0x80) != 0)) ||
      // Check Glacier Park and the door to Citadel City
      (lev == 0x1c && ((sdata->advProgress.rewards[3] & 0x100) != 0)))
  {
    // door is open
    doorIsOpen = true;
  }

  // Cosine(angle)
  ratio = MATH_Cos((int)doorInst->instDef->rot[1]);

  // X distance of player and door
  distX = doorInst->matrix.t[0] + (ratio * 0x300 >> 0xc) - driver->instSelf->matrix.t[0];

  // Y distance of player and door
  distY = doorInst->matrix.t[1] - driver->instSelf->matrix.t[1];

  // Sine(angle)
  ratio = MATH_Sin((int)doorInst->instDef->rot[1]);

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
    numKeys = ((short *)0x800b4e7c)[(lev + -0x19)];
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
      MainFrame_RequestMaskHint(hintId, 0);
    }
    return;
  }

  if (
      // if player is far from the door
      (0x8ffff < dist) &&
      // flags
      ((*(u_short *)((int)door + 0x1c) & 0x10) == 0))
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
    goto joined_r0x800b06ec;
  }

  // if camera is not transitioning out (yet),
  // while keys are still spinning in air
  if ((*(u_short *)((int)door + 0x1c) & 1) == 0)
  {

    if (*(short *)((int)door + 0x1e) != 0)
    {
      *(short *)((int)door + 0x1e) += -1;
      goto LAB_800b0404;
    }

    // If the game is paused
    if ((gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) != 0)
    {
      goto LAB_800b0404;
    }

    // If you are here, game must not be paused

    driver->funcPtrs[0] = VehPtr_Freeze_Init;

    // flags
    *(u_short *)((int)door + 0x1c) |= 0x10;

    // if timer is less than four full seconds
    if (*(short *)((int)door + 0x26) < 0x78)
    {
      if (driver->speedApprox < 0x80)
      {
        desiredPos[0] = -0xc98;
        desiredPos[1] = 0x99f;
        desiredPos[2] = 0x232;

        // if keys are not spawned, create them
        if (door->keyInst == NULL)
        {

          // if number of keys is more than zero
          if (numKeys)
          {
            // spawn instances for every key you have,
            // this makes them spin in a circle before
            // seeing the doors animate open
            for (i = 0; i < numKeys; i++)
            {
              // DAT_800aba88
              // "key"

              keyInst = INSTANCE_Birth3D(gGT->modelPtr[0x63], &DAT_800aba88, doorTh);

              // Set Key Color
              keyInst->colorRGBA = 0xdca6000;

              // specular lighting
              keyInst->flags |= 0x20000;

              *(short *)(door + 9) += 1;

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
          *(char *)(door + 8) = gGT->hudFlags;

          // Disable HUD
          gGT->hudFlags = 0;

          // For watching hub doors animate open
        }

        // if more than zero
        if (0 < numKeys)
        {
          piVar16 = (int*)(door + 10);

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
                keyInst->scale[0] += 0x40;
                keyInst->scale[1] += 0x40;
                keyInst->scale[2] += 0x40;
              }

              // if key posY is less than (player posY + 0xa0)
              if (keyInst->matrix.t[1] < (driver->instSelf->matrix.t[0] + 0xa0))
              {
                // increase key posY
                keyInst->matrix.t[1] += 4;
              }

              if (1 < numKeys)
              {

                iVar18 = i * (0x1000 / numKeys);
                iVar17 = (int)keyInst->scale[0];

                if (iVar17 < 0)
                {
                  iVar17 += 0x1f;
                }

                ratio = MATH_Sin(*(short *)(door + 0xc) + iVar18, piVar16);

                keyInst->matrix.t[0] = driver->instSelf->matrix.t[0] + ((iVar17 >> 5) * ratio >> 0xc);

                ratio = MATH_Cos(*(short *)(door + 0xc) + iVar18);

                keyInst->matrix.t[2] = driver->instSelf->matrix.t[2] + ((iVar17 >> 5) * ratio >> 0xc);
              }

              Vector_SpecLightSpin3D(keyInst, piVar16, &desiredPos);

              // convert 3 rotation shorts into rotation matrix
              ConvertRotToMatrix(&keyInst->matrix, piVar16);
            }
            door->keyInst[i] = keyInst;
          }
        }
        *(short *)(door + 10) = 0;
        *(short *)(door + 0xb) = 0;

        // increment frame counter
        *(short *)((int)door + 0x26) += 1;

        // spin rate of key
        *(short *)((int)door + 0x2a) += 0x40;
        *(short *)(door + 0xc) += 0x10;

        // play four distorted "token unlock" sounds,
        // then play some dramatic sound, then play
        // sound of doors creeking open

        switch (*(short *)((int)door + 0x26))
        {
        case 0x10:
          OtherFX_Play_LowLevel(0x67, 1, 0xff7680);
          break;
        case 0x0F:
          OtherFX_Play_LowLevel(0x67, 1, 0xeb8080);
          break;
        case 0x14:
          OtherFX_Play_LowLevel(0x67, 1, 0xd78a80);
          break;
        case 0x19:
          OtherFX_Play_LowLevel(0x67, 1, 0xc39480);
          break;
        case 0x50:
          // sound of hub doors unlocking ??
          // or just a dramatic sound ??

          // point is it's right before doors
          // "creek" open
          OtherFX_Play(0x93, 1);
          break;
        default:
          // doors "creek" open
          OtherFX_Play(0x94, 1);

          if (*(short *)((int)door + 0x26) != 0x78)
            goto LAB_800b0404;
          break;
        }
      }
      goto LAB_800b0404;
    }

    // After four full seconds,
    // start the camera zoom-out

    ratio = MATH_Cos((int)doorInst->instDef->rot[1]);

    i = MATH_Cos((int)doorInst->instDef->rot[1] + 0x400);

    // desired posX for transition
    desiredPos[0] = doorInst->matrix.t[0] + (short)(ratio * 0x312 >> 0xc) +
                    (short)(i * 0x600 >> 0xc);
    // desired posY for transition
    desiredPos[1] = doorInst->matrix.t[0] + 0x17a;

    // desired posZ for transition
    desiredPos[2] = doorInst->matrix.t[0] + (short)(ratio * 0x312 >> 0xc) +
                    (short)(i * 0x600 >> 0xc);

    // desired rotation for transition
    desiredRot[0] = doorInst->instDef->rot[0] + 0x800;
    desiredRot[1] = doorInst->instDef->rot[1];
    desiredRot[2] = doorInst->instDef->rot[2];

    // set desired position and rotation for CamerDC transition
    CAM_SetDesiredPosRot(&gGT->cameraDC[0], &desiredPos, &desiredRot);

    GAMEPAD_Vib_2(driver, 0, 0);

    // start camera out transition (in "else" below)
    doorFlags = *(u_short *)(door + 7) | 1;
  }
  // if camera is transitioning out,
  // after keys are done spinning in air
  else
  {
    // set transition out to take two full seconds (can't patch?)
    *(short *)((int)door + 0x1e) = 0x3c;

    if (((cDC->flags & 0x200) != 0) || ((*(u_short *)(door + 7) & 4) != 0))
    {
      if (((cDC->flags & 0x800) != 0) && ((*(u_short *)(door + 7) & 2) == 0))
      {
        *(u_short *)(door + 7) |= 2;
      }
      goto LAB_800b0404;
    }

    driver->funcPtrs[0] = VehPtr_Driving_Init;

    doorFlags = *(u_short *)(door + 7) | 4;
  }
  *(u_short *)(door + 7) = doorFlags;

LAB_800b0404:

  if ((*(u_short *)(door + 7) & 1) == 0)
    return;

  // if doors are 90 degrees open,
  // then allow passage, and quit function
  if (0x3ff < *(short *)((int)door + 0x16))
  {

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
    else
    {
      if (
          // if this is N Sane Beach
          (lev == 0x1a) &&

          // Door #5 (beach -> ruins)
          (doorID == 5))
      {
        // record that door is open
        sdata->advProgress.rewards[3] |= 0x10;
      }
      else
      {
        // Gemstone valley (cup door)
        if (lev == 0x19)
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
      }
    }
    cDC->flags |= 0x400;

    driver->funcPtrs[0] = VehPtr_Driving_Init;

    *(u_short *)(door + 7) &= 0xffef | 4;

    // bring HUD back
    gGT->hudFlags = *(char *)(door + 8);

    return;
  }

  // if doors are less than 90 degrees open

  scaler = (short*)0x800aba8c;
  
  // scaler[1] = DAT_800aba90;
  // scaler[2] = DAT_800aba94;
  // scaler[3] = DAT_800aba98;
  // scaler[4] = DAT_800aba9c;
  // scaler[5] = DAT_800abaa0;

  // right-hand door rotX
  desiredRot[0] = *(short *)(door + 5);

  // increase opening rotation
  *(short *)((int)door + 0x16) += 0x10;

  // right-hand door rotY and rotZ
  desiredRot[1] = doorInst->instDef->rot[1] - *(short *)((int)door + 0x16);
  desiredRot[2] = *(short *)(door + 6);

  // left-hand door rot[x,y,z]
  otherRot[0] = *(short *)(door + 5);
  otherRot[1] = doorInst->instDef->rot[1] + *(short *)((int)door + 0x16);
  otherRot[2] = *(short *)(door + 6);

  // convert 3 rotation shorts into rotation matrix
  ConvertRotToMatrix(&doorInst->matrix, &otherRot);

  // convert 3 rotation shorts into rotation matrix
  ConvertRotToMatrix(&door->otherDoor->matrix, &desiredRot);

  // if less than 11 frames have passed,
  // decrease key scale, then quit function
  if (*(short *)((int)door + 0x32) < 0xb)
  {
    // loop through 4 keys
    for (i = 0; i < 4; i++)
    {
      keyInst = door->keyInst[i];
      // if instance exists
      if (keyInst != NULL)
      {
        // decrease scale of key,
        // by using array of values per frame
        // scale = short array[door->numFrame]
        keyInst->scale[0] = *(short *)((int)scaler + (int)*(short *)((int)door + 0x32) * 2);
        keyInst->scale[1] = *(short *)((int)scaler + (int)*(short *)((int)door + 0x32) * 2);
        keyInst->scale[2] = *(short *)((int)scaler + (int)*(short *)((int)door + 0x32) * 2);
      }
    }

    // increase Numframe
    *(short *)((int)door + 0x32) += 1;

    return;
  }

  // if 11 or more frames have passed,
  // destroy four key instances.

  // loop through 4 keys
  for (i = 0; i < 4; i++)
  {
    INSTANCE_Death(door->keyInst[i]);
    door->keyInst[i] = NULL;
  }

  return;
}