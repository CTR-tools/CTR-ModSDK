#include <common.h>

void CS_Podium_Camera_ThTick(struct Thread *th)
{
  short rewardId;
  u_short uVar4;
  int frame;
  int stringOrLevID;
  int iVar8;
  int iVar9;

  short pos[3];
  short rot[3];

  // shouldn't this be a pointer?
  char camPath[8];

  // get object from thread
  u_short *podium = th->object;

  struct GameTracker *gGT = sdata->gGT;

  // if at podium, and driver needs to be hidden
  if (podium[0] == 0)
  {
    // VehStuckProc_RIP_Init
    gGT->drivers[0]->funcPtrs[0] = VehStuckProc_RIP_Init;
  }

  // CameraDC, it must be zero to follow you
  // "if the camera is following the player"
  if (gGT->cameraDC->cameraMode != 3)
  {
    if (OVR_233.cutsceneState < 1)
    {
      OVR_233.cutsceneState = 1;
    }
    OVR_233.PodiumInitUnk3 = 1;
  }

  if ((((OVR_233.cutsceneState != 0) ||

        // if pressed Start to skip scene
        (*(u_int *)0x800b0b84 != 0)) &&

       // if cup is beaten now, that was not previously beaten
       ((gGT->gameMode2 & 0x1000) != 0)) &&

      // if XA is not playing
      (sdata->ptrActiveMenu == 0))
  {
    // "Save Your Cup Progress?\0"
    stringOrLevID = 0x236;

    // if battle map is unlocked now, that was not previously unlocked
    if ((gGT->gameMode2 & 0x2000) != 0)
    {
      // "Save Your Cup Progress?\n"
      // "New Battle Arena Opened!
      stringOrLevID = 0x237;
    }

    TakeCupProgress_Activate(stringOrLevID);

    // remove FIRST_TIME_WIN_CUP | FIRST_TIME_UNLOCK_BATTLE_MAP
    gGT->gameMode2 &= ~(0x3000);
  }
  if ((OVR_233.cutsceneState == 0) || (sdata->ptrActiveMenu != 0))
  {
    frame = CAM_Path_GetNumPoints();
    iVar8 = (frame << 0x15) >> 0x10;
    if (iVar8 != 0)
    {
      uVar4 = podium[0] + gGT->elapsedTimeMS;
      uVar4 = (u_short)uVar4;
      iVar9 = uVar4;

      if (iVar8 - 4800 < iVar9)
      {
        OVR_233.PodiumInitUnk3 = 1;
      }

      if (iVar8 <= iVar9)
      {
        uVar4 = frame * 0x20 - 1;
        uVar4 = (u_short)uVar4;
        if (OVR_233.cutsceneState < 1)
        {
          OVR_233.cutsceneState = 1;
        }
      }

      frame = uVar4 * 0x10000 >> 0x15;
      OVR_233.PodiumInitUnk2 = frame;

      podium[0] = uVar4;

      CAM_Path_Move(frame, &pos, &rot, camPath);

      // store result in pushBuffer pos and rot
      struct PushBuffer* pb = &gGT->pushBuffer[0];
      pb->pos[0] = pos[0];
      pb->pos[1] = pos[1];
      pb->pos[2] = pos[2];
      pb->rot[0] = rot[0];
      pb->rot[1] = rot[1];
      pb->rot[2] = rot[2];
    }
  }
  else
  {
    if ((gGT->gameMode2 & 0x1000) != 0)
      goto LAB_800af2ec;

    // PRESS * TO CONTINUE
    DecalFont_DrawLine(sdata->lngStrings[0xC9], 256, 190, FONT_BIG, (0xffff0000 | JUSTIFY_CENTER));
  }

  if (((gGT->gameMode2 & 0x1000) == 0) && (sdata->ptrActiveMenu == NULL))
  {
    // If do not tap the "Start" button
    if (((sdata->gGamepads->gamepad[0].buttonsTapped & BTN_START) == 0) &&

        // If do not tap the "Start" button or "Cross" button
        ((OVR_233.cutsceneState == 0 || (sdata->gGamepads->gamepad[0].buttonsTapped & (BTN_START | BTN_CROSS_one)) == 0)) &&

        // if podium scene flag is enabled
        ((gGT->gameMode2 & 4) != 0))
    {
      return;
    }

    // === if you're here, it means podium scene must end ===

    // If you're not in Adventure Mode
    if ((gGT->gameMode1 & ADVENTURE_MODE) == 0)
    {
      // return to main menu
      sdata->mainMenuState = 0;

      // remove adventure hub bit and add main menu
      gGT->gameMode1 = gGT->gameMode1 & ~(ADVENTURE_ARENA) | MAIN_MENU;

      // podium reward
      gGT->podiumRewardID = 0;

      // remove podium scene bit
      gGT.gameMode2 &= ~(4);

      RaceFlag_SetDrawOrder(0);

      // go to main menu
      MainRaceTrack_RequestLoad(MAIN_MENU_LEVEL);
      return;
    }

    // if you are in adventure mode
    OVR_233.PodiumInitUnk3 = 1;

    // podium reward
    rewardId = gGT->podiumRewardID;

    // zero confetti winners
    gGT->numWinners = 0;

    // no more confetti
    gGT->renderFlags &= ~(4);

    // If this is not a "beaten oxide" podium
    if (rewardId != STATIC_BIG1)
    {
      u_char hintID;
      // if you do not go to boss cutscene
      if (CS_Boss_BoolShouldStart() == 0)
      {
        OVR_233.isCutsceneOver = 1;

        // This thread is now dead
        th->flags | 0x800;

        CS_DestroyPodium_StartDriving();

        switch (rewardId)
        {
        case STATIC_TROPHY:
          // "congratulations, you win a trophy"
          hintID = 12;
          break;

        case STATIC_RELIC:
          // "great, you earn a relic"
          hintID = 19;
          break;

        case STATIC_KEY:
          // "good job, you earned a key"
          hintID = 13;
          break;

        case STATIC_TOKEN:
          // "excellent work, you've collected a CTR token"
          hintID = 20;
          break;

        default:
          // "congratulations, you won a gem"
          hintID = 21;
          break;
        }

        // if player uses uka
        if ((VehPickupItem_MaskBoolGoodGuy(gGT->drivers[0]) & 0xffff) == 0)
        {
          // increment index to uka voices
          hintID += 0x1f;
        }

        // pause cd
        CDSYS_XAPauseForce();

        CDSYS_XAPlay(1, hintID);

        // reset podium reward
        gGT->podiumRewardID = 0;
        return;
      }

      // At this point, there must be a boss cutscene,
      // or else the function would return by now

      // Change ThTick function,
      th->funcThTick = CS_Boss_ThTick;

      // If you are not at the podium for winning a relic
      if (gGT->podiumRewardID != STATIC_RELIC)
      {
        OVR_233.unknown3 = -1;
        return;
      }

      // less than 18 relics
      if (gGT->currAdvProfile.numRelics < 18)
      {
        OVR_233.unknown3 = -1;
        return;
      }

      // Assuming the last relic was just won...
      OVR_233.unknown3 = gGT->levelID - 0x10;
      return;
    }

    // at this point, this must be "oxide beaten" podium,
    // or else the function would have returned

    // podium reward
    gGT->podiumRewardID = 0;
    // remove adventure hub bit
    gGT->gameMode1 &= ~(ADVENTURE_ARENA);
    // remove podium bit
    gGT->gameMode2 &= ~(4);

    // load LEV for beat oxide any%
    stringOrLevID = OXIDE_ENDING;

    if ((sdata->advProgress.rewards[2] & 0x100000) != 0)
    {
      // load LEV for beat oxide 100%
      stringOrLevID = OXIDE_TRUE_ENDING;
    }

    // load LEV
    MainRaceTrack_RequestLoad(stringOrLevID);

    // This thread is now dead
    th->flags | 0x800;
    return;
  }
LAB_800af2ec:

  // If you tap the "Start" button
  if ((sdata->gGamepads->gamepad[0].buttonsTapped & BTN_START) != 0)
  {
    *(u_int *)0x800b0b84 = 1;
  }
}
