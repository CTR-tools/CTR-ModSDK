#include <common.h>

extern struct MenuBox new_retryExitToMap;
extern struct MenuBox retry_arcadeDifficulty;

void DECOMP_UI_RaceEnd_MenuBoxFuncPtr(struct MenuBox *menu)
{
  short option;
  struct GameTracker *gGT;
  u_int uVar3;
  int *GhostBufferEnd;
  int *ghostTape;
  int *ghostPlaying;
  u_short style;
  void *startOffs;
  void *endOffs;
  void *currOffs;

  gGT = sdata->gGT;
  if (menu->unk1e == 0)
  {
    if (-1 < menu->unk1a)
    {
      option = menu->rows[menu->rowSelected].stringIndex;
      // if not "save ghost"
      if (option != 9 || option != 7)
      {
        // make MenuBox invisible
        menu->state |= NEEDS_TO_CLOSE;
        sdata->framesSinceRaceEnded = 0;
        sdata->numIconsEOR = 1;
      }
      switch (option)
      {
      case 7:
        // Change Difficulty
        if (gGT->gameMode1 & TIME_TRIAL)
          return;
        sdata->ptrActiveMenuBox = (gGT->gameMode1 & ARCADE_MODE) ? &retry_arcadeDifficulty : &new_retryExitToMap;
        sdata->ptrActiveMenuBox->state &= ~NEEDS_TO_CLOSE;
        return;
      case 6:
        // Change level
        // Erase ghost of previous race from RAM
        GhostBuffer_Destroy();
        // go back to track selection
        sdata->mainMenuState = 2;
        break;

      case 4:
        // Retry
        // Turn off HUD
        gGT->hudFlags &= 0xfe;

        if (TitleFlag_IsFullyOffScreen())
        {
          // checkered flag, begin transition on-screen
          TitleFlag_BeginTransition(1);
        }

        sdata->Loading.stage = -5;

        // howl_StopAudio
        // clear backup,
        // keep music,
        // destroy "most" fx, let menu fx play to end
        howl_StopAudio(1, 0, 0);

        if ((gGT->unknownFlags_1d44 & 1) == 0)
          return;

        sdata->boolPlayGhost = 1;

        GhostBufferEnd = (int)sdata->GhostRecording.ptrGhost + 0x3e00;
        ghostTape = sdata->GhostRecording.ptrGhost;
        ghostPlaying = sdata->ptrGhostTapePlaying;

        if ((((u_int)*ghostTape | (u_int)*ghostPlaying) & 3) == 0)
        {
          // Copy ghost recording buffer
          do
          {
            startOffs = ghostTape[1];
            endOffs = ghostTape[2];
            currOffs = ghostTape[3];
            *ghostPlaying = *ghostTape;
            ghostPlaying[1] = startOffs;
            ghostPlaying[2] = endOffs;
            ghostPlaying[3] = currOffs;
            ghostTape = (int)ghostTape + 0x10;
            ghostPlaying = (int)ghostPlaying + 0x10;
          } while (ghostTape != GhostBufferEnd);
        }
        else
        {
          // copy ghost recording buffer
          do
          {
            startOffs = ghostTape[1];
            endOffs = ghostTape[2];
            currOffs = ghostTape[3];
            *ghostPlaying = *ghostTape;
            ghostPlaying[1] = startOffs;
            ghostPlaying[2] = endOffs;
            ghostPlaying[3] = currOffs;
            ghostTape = (int)ghostTape + 0x10;
            ghostPlaying = (int)ghostPlaying + 0x10;
          } while (ghostTape != GhostBufferEnd);
        }

        // Make P2 the character that is saved in the
        // header of the ghost that you will see in the race
        data.characterIDs[1] = *(short *)((int)sdata->ptrGhostTapePlaying + 6);

        // no ghosts are drawing
        sdata->boolGhostsDrawing = 0;

        return;

      case 3:
        // Quit
        // Erase ghost of previous race from RAM
        GhostBuffer_Destroy();
        // go back to main menu
        sdata->mainMenuState = 0;
        // load LEV of main menu
        MainRaceTrack_RequestLoad(0x27);
        return;

      case 9:
        // Save Ghost
        sdata->framesSinceRaceEnded = 0x3f9;
        // Set Load/Save to Ghost mode
        LoadSave_ToggleMode(0x31);
        // Change active MenuBox to GhostSelection
        sdata->ptrActiveMenuBox = &data.menuBox_GhostSelection;
        return;

      case 0xd:
        // Exit To Map
        // when loading is done, add flag for "In Adventure Arena"
        sdata->Loading.OnBegin.AddBitsConfig0 |= ADVENTURE_ARENA;

        // when loading is done, remove flag for "CTR Challenge"
        sdata->Loading.OnBegin.RemBitsConfig8 |= 8;

        if ((gGT->gameMode1 & ADVENTURE_CUP) != 0)
        {
          // when loading is done, remove flags for
          // adventure cup, relic race, and crystal challenge
          sdata->Loading.OnBegin.RemBitsConfig0 |= 0x1c000000;

          // load Gemstone valley LEV
          MainRaceTrack_RequestLoad(0x19);
          return;
        }

        uVar3 = sdata->Loading.OnBegin.RemBitsConfig0 | 0xc000000;

        if (gGT->gameMode1 < 0)
        {
          // when loading is done, add flag to spawn near boss door
          sdata->Loading.OnBegin.AddBitsConfig8 |= 1;

          // when loading is done, remove flags for
          // boss race, relic race, and crystal challenge
          uVar3 = sdata->Loading.OnBegin.RemBitsConfig0 | 0x8c000000;
        }

        sdata->Loading.OnBegin.RemBitsConfig0 = uVar3;

        // Load LEV in Track Selection
        MainRaceTrack_RequestLoad(gGT->prevLEV);
        return;

      case 0xc9:
        // Press X to continue
        sdata->menuReadyToPass |= 1;
        sdata->framesSinceRaceEnded = 0;
        sdata->numIconsEOR = 1;
        return;
      }

      // when loading is done
      // add flag for main menu
      sdata->Loading.OnBegin.AddBitsConfig0 |= MAIN_MENU;

      // load LEV of main menu
      MainRaceTrack_RequestLoad(MAIN_MENU_LEVEL);
    }
  }
  else
  {
    style = menu->drawStyle & 0xfeff;
    menu->drawStyle = style;

    if (2 < gGT->numPlyrCurrGame)
    {
      menu->drawStyle = style | 0x100;
    }
  }
  return;
}
