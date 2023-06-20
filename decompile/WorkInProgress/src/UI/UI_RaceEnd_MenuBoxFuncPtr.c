#include <common.h>

void DECOMP_UI_RaceEnd_MenuBoxFuncPtr(struct MenuBox *menu)

{
  short option;
  struct GameTracker *gGT;
  u_int uVar3;
  int iVar4;
  struct GhostRecording *GhostBufferEnd;
  struct GhostRecording *ghostRec;
  struct GhostRecording *ghostReplay;
  u_short style;
  void *startOffs;
  void *endOffs;
  void *currOffs;

  gGT = sdata->gGT;
  if (menu->unk1e == 0)
  {

    if (-1 < menu->unk1a)
    {
      if (menu->unk1a * 6 + menu->rows != 9)
      {

        // make MenuBox invisible
        MENUBOX_Hide(menu);
      }
      sdata->framesSinceRaceEnded = 0;
      sdata->numIconsEOR = 1;

      // rows[rowSelected].titleLngID
      option = menu->unk1a * 6 + menu->rows;

      // if "Change Level"
      if (option == 6)
      {
        // Erase ghost of previous race from RAM
        GhostBuffer_Destroy();

        // go back to track selection
        sdata->mainMenuState = 2;
      }

      // if not "Change Level"
      else
      {
        if (option < 7)
        {
          // If "Retry"
          if (option == 4)
          {
            // Turn off HUD
            sdata->gGT->hudFlags &= 0xfe;

            iVar4 = TitleFlag_IsFullyOffScreen();

            if (iVar4 == 1)
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

            if ((sdata->gGT->unknownFlags_1d44 & 1) == 0)
            {
              return;
            }

            sdata->boolPlayGhost = 1;

            GhostBufferEnd = (int)sdata->GhostRecording.ptrGhost + 0xf80;

            // Ghost recording buffer
            ghostRec = sdata->GhostRecording.ptrGhost;

            // Ghost replay buffer (to watch while you drive)
            ghostReplay = sdata->ptrGhostTapePlaying;

            if ((((u_int)*ghostRec | (u_int)*ghostReplay) & 3) == 0)
            {
              // Copy ghost recording buffer
              do
              {
                startOffs = ghostRec[1];
                endOffs = ghostRec[2];
                currOffs = ghostRec[3];
                *ghostReplay = *ghostRec;
                ghostReplay[1] = startOffs;
                ghostReplay[2] = endOffs;
                ghostReplay[3] = currOffs;
                ghostRec = (int)ghostRec + 0x10;
                ghostReplay = (int)ghostReplay + 0x10;
              } while (ghostRec != GhostBufferEnd);
            }

            // The contents of this "else" are identical to the "if" above,
            // you can tell by copying the contents and searching with CTRL + F

            else
            {
              // copy ghost recording buffer
              do
              {
                startOffs = ghostRec[1];
                endOffs = ghostRec[2];
                currOffs = ghostRec[3];
                *ghostReplay = *ghostRec;
                ghostReplay[1] = startOffs;
                ghostReplay[2] = endOffs;
                ghostReplay[3] = currOffs;
                ghostRec = (int)ghostRec + 0x10;
                ghostReplay = (int)ghostReplay + 0x10;
              } while (ghostRec != GhostBufferEnd);
            }

            // Make P2 the character that is saved in the
            // header of the ghost that you will see in the race
            data.characterIDs[1] = (sdata->ptrGhostTapePlaying + 6);

            // no ghosts are drawing
            sdata->boolGhostsDrawing = 0;

            return;
          }

          if (option < 5)
          {
            // If not "Quit"
            if (option != 3)
            {
              sdata->framesSinceRaceEnded = 0;
              sdata->numIconsEOR = 1;
              return;
            }

            // If "Quit"...

            // Erase ghost of previous race from RAM
            GhostBuffer_Destroy();

            // go back to main menu
            sdata->mainMenuState = 0;

            // load LEV of main menu
            MainRaceTrack_RequestLoad(0x27);
            return;
          }

          // Erase ghost of previous race from RAM
          GhostBuffer_Destroy();

          // go to character selection
          sdata->mainMenuState = 1;
        }
        else
        {
          // If not "Change Setup"
          if (option != 10)
          {
            if (option < 0xb)
            {
              // If not "Save Ghost"
              if (option != 9)
              {
                sdata->framesSinceRaceEnded = 0;
                sdata->numIconsEOR = 1;
                return;
              }

              // If it is "Save Ghost"

              sdata->framesSinceRaceEnded = 0x3f9;

              // Set Load/Save to Ghost mode
              LoadSave_ToggleMode(0x31);

              // Change active MenuBox to GhostSelection
              sdata->ptrActiveMenuBox = &data.menuBox_GhostSelection;
              return;
            }

            // If "Exit To Map" chosen
            if (option == 0xd)
            {
              // when loading is done, add flag for "In Adventure Arena"
              sdata->Loading.OnBegin.AddBitsConfig0 |= 0x100000;

              // when loading is done, remove flag for "CTR Challenge"
              sdata->Loading.OnBegin.RemBitsConfig8 |= 8;

              // If you are in Adventure cup
              if ((sdata->gGT->gameMode1 & ADVENTURE_CUP) != 0)
              {
                // when loading is done, remove flags for
                // adventure cup, relic race, and crystal challenge
                sdata->Loading.OnBegin.RemBitsConfig0 |= 0x1c000000;

                // load Gemstone valley LEV
                MainRaceTrack_RequestLoad(0x19);
                return;
              }

              // when loading is done,
              // remove relic race, and crystal challenge
              uVar3 = sdata->Loading.OnBegin.RemBitsConfig0 | 0xc000000;

              // If you're in a Boss Race
              // 0x80000000
              if (sdata->gGT->gameMode1 < 0)
              {
                // when loading is done,
                // add flag to spawn near boss door
                sdata->Loading.OnBegin.AddBitsConfig8 = sdata->Loading.OnBegin.AddBitsConfig8 | 1;

                // when loading is done, remove flags for
                // boss race, relic race, and crystal challenge
                uVar3 = sdata->Loading.OnBegin.RemBitsConfig0 | 0x8c000000;
              }

              // set flags that you want removed after
              // the loading is finished
              sdata->Loading.OnBegin.RemBitsConfig0 = uVar3;

              // Load LEV in Track Selection
              MainRaceTrack_RequestLoad((sdata->gGT + 0x1eb4));
              return;
            }

            // If not "Press X to continue"
            // how would that be in a menu?
            if (option != 0xc9)
            {
              sdata->framesSinceRaceEnded = 0;
              sdata->numIconsEOR = 1;
              return;
            }

            sdata->menuReadyToPass |= 1;
            sdata->framesSinceRaceEnded = 0;
            sdata->numIconsEOR = 1;
            return;
          }

          // go to battle setup screen
          sdata->mainMenuState = 3;
        }
      }

      // when loading is done
      // add flag for "in menus"
      sdata->Loading.OnBegin.AddBitsConfig0 = sdata->Loading.OnBegin.AddBitsConfig0 | 0x2000;

      // load LEV of main menu
      MainRaceTrack_RequestLoad(0x27);
    }
  }
  else
  {
    style = menu->drawStyle & 0xfeff;
    menu->drawStyle = style;

    // if more than 2 screens
    if (2 < gGT->numPlyrCurrGame)
    {
      menu->drawStyle = style | 0x100;
    }
  }
  return;
}
