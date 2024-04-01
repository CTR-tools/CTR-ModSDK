#include <common.h>

extern struct RectMenu End_AdvRaceDifficulty;
extern struct RectMenu End_arcadeDifficulty;

void DECOMP_UI_RaceEnd_MenuProc(struct RectMenu* menu)
{
  struct RectMenu *nextMenu;
  struct GameTracker *gGT;
  short option;
  u_int uVar3;
  int *GhostBufferEnd;
  int *ghostTape;
  int *ghostPlaying;
  void *startOffs;
  void *endOffs;
  void *currOffs;

  gGT = sdata->gGT;
  if (menu->unk1e == 0)
  {
    if (-1 < menu->rowSelected)
    {
      option = menu->rows[menu->rowSelected].stringIndex;
      // if not "save ghost"
      if (option != 9)
      {
        // make Menu invisible
        menu->state |= NEEDS_TO_CLOSE;
        sdata->framesSinceRaceEnded = 0;
        sdata->numIconsEOR = 1;
      }
      switch (option)
      {
      case 7:
        // Change Difficulty
        if (gGT->gameMode1 & (TIME_TRIAL|RELIC_RACE))
          return;
        nextMenu = (gGT->gameMode1 & ARCADE_MODE) ? &End_arcadeDifficulty : &End_AdvRaceDifficulty;
        nextMenu->posY_curr = (gGT->numPlyrCurrGame == 1)? 170 : 108;
        RECTMENU_Show(nextMenu);
        return;
      case 6:
        // Change level
        // Erase ghost of previous race from RAM
        GhostTape_Destroy();
        // go back to track selection
        sdata->mainMenuState = 2;
        break;
      case 4:
        // Retry
        // Turn off HUD
        gGT->hudFlags &= 0xfe;

        if (RaceFlag_IsFullyOffScreen())
        {
          // checkered flag, begin transition on-screen
          RaceFlag_BeginTransition(1);
        }

        sdata->Loading.stage = -5;

        // howl_StopAudio
        // clear backup,
        // keep music,
        // destroy "most" fx, let menu fx play to end
        howl_StopAudio(1, 0, 0);

        if ((gGT->unknownFlags_1d44 & 1) == 0)
          return;

        sdata->boolReplayHumanGhost = 1;

        GhostBufferEnd = (int)sdata->GhostRecording.ptrGhost + 0x3e00;
        ghostTape = sdata->GhostRecording.ptrGhost;
        ghostPlaying = sdata->ptrGhostTapePlaying;

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

        // Make P2 the character that is saved in the
        // header of the ghost that you will see in the race
        data.characterIDs[1] = sdata->ptrGhostTapePlaying->characterID;

        // no ghosts are drawing
        sdata->boolGhostsDrawing = 0;

        return;

      case 3:
        // Quit
        // Erase ghost of previous race from RAM
        GhostTape_Destroy();
        // go back to main menu
        sdata->mainMenuState = 0;
        // load LEV of main menu
        MainRaceTrack_RequestLoad(0x27);
        return;

      case 9:
        // Save Ghost
        sdata->framesSinceRaceEnded = 0x3f9;
        // Set Load/Save to Ghost mode
        SelectProfile_ToggleMode(0x31);
        // Change active Menu to GhostSelection
        sdata->ptrActiveMenu = &data.menuGhostSelection;
        return;

      case 13:
        // Exit To Map
        // when loading is done, add flag for "In Adventure Arena"
        sdata->Loading.OnBegin.AddBitsConfig0 |= ADVENTURE_ARENA;

        // when loading is done, remove flag for "CTR Challenge"
        sdata->Loading.OnBegin.RemBitsConfig8 |= TOKEN_RACE;

        if ((gGT->gameMode1 & ADVENTURE_CUP) != 0)
        {
          // when loading is done, remove flags for
          // adventure cup, relic race, and crystal challenge
          sdata->Loading.OnBegin.RemBitsConfig0 |= (ADVENTURE_CUP | RELIC_RACE | CRYSTAL_CHALLENGE);

          // load Gemstone valley LEV
          MainRaceTrack_RequestLoad(GEM_STONE_VALLEY);
          return;
        }

        uVar3 = (RELIC_RACE | CRYSTAL_CHALLENGE);

        if (gGT->gameMode1 < 0)
        {
          // when loading is done, add flag to spawn near boss door
          sdata->Loading.OnBegin.AddBitsConfig8 |= 1;

          // when loading is done, remove flags for
          // boss race, relic race, and crystal challenge
          uVar3 |= ADVENTURE_BOSS;
        }

        sdata->Loading.OnBegin.RemBitsConfig0 |= uVar3;

        // Load LEV in Track Selection
        MainRaceTrack_RequestLoad(gGT->prevLEV);
        return;

      case 201:
        // Press X to continue
        sdata->menuReadyToPass |= 1;
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
    menu->drawStyle &= 0xfeff;

    if (gGT->numPlyrCurrGame > 2)
    {
      menu->drawStyle |= 0x100;
    }
  }
  return;
}
