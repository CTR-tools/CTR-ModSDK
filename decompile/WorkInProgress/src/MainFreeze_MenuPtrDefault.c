#include <common.h>

void DECOMP_MainFreeze_MenuPtrDefault(struct MenuBox *menu)
{
    int levID;
    u_short string;
    u_int gameMode;

    struct GameTracker *gGT = sdata->gGT;
    gameMode = gGT->gameMode1;

    // if you have not waited 5 frames
    // since the game was paused
    if (gGT->cooldownfromPauseUntilUnpause != 0)
    {
        // quit
        return;
    }

    // assume 5 frames have passed since paused

    if (menu->unk1e != 0)
    {
        menu->drawStyle &= 0xfeff;

        // if more than 2 screens
        if (2 < gGT->numPlyrCurrGame)
        {
            menu->drawStyle |= 0x100;
        }

        // If you're not in Adventure Arena
        if ((gameMode & ADVENTURE_ARENA) == 0 ||
            // menu is closing
            (menu->state & 0x1000) != 0)
        {
            return;
        }

        // quit adv hub is not loaded
        if (LOAD_IsOpen_AdvHub() == 0)
            return;

        AH_Pause_Update();

        return;
    }
    if (menu->rowSelected < 0)
    {
        return;
    }

    // get string from row selected
    string = menu->rows[menu->rowSelected].stringIndex;

    // String 0xE: Options
    if (string == 0xe)
    {
        // Set desired MenuBox to Options
        sdata->ptrActiveMenuBox = &data.menuBox_optionsMenu_racingWheel;

        data.menuBox_optionsMenu_racingWheel.unk1 = 8;
        return;
    }

    // AkuAku Hints, or UkaUka Hints
    if (((u_int)string - 0xb & 0xffff) < 2)
    {
        // Hints menu
        sdata->ptrActiveMenuBox = (struct MenuBox *)0x800b518c;
        return;
    }

    // String 0x3: Quit
    if (string == 3)
    {
        // Set active MenuBox to Quit
        sdata->ptrActiveMenuBox = &data.menuBox_quit;
        data.menuBox_quit.rowSelected = 1;
        return;
    }

    // must wait 5 frames until next pause
    gGT->cooldownFromUnpauseUntilPause = 5;

    // make MenuBox invisible
    MENUBOX_Hide(menu);

    MainFreeze_SafeAdvDestroy();

    // careful, it's String MINUS one
    switch (string - 1)
    {

    // String 0x1: "Restart"
    case 0:

    // String 0x4: "Retry"
    case 3:

        // Unpause game
        gGT->gameMode1 &= 0xfffffffe;

        if (TitleFlag_IsFullyOffScreen() == 1)
        {
            // checkered flag, begin transition on-screen
            TitleFlag_BeginTransition(1);
        }

        // if you are not showing a ghost during a race
        if (sdata->boolPlayGhost == 0)
        {
            // restart race
            sdata->Loading.stage = -5;
            return;
        }

        // If the ghost playing buffer is nullptr
        if (sdata->ptrGhostTapePlaying == 0)
        {
            // restart race
            sdata->Loading.stage = -5;
            return;
        }

        // At this point, we are certain there is a ghost
        // buffer so you must be in time trial mode

        // Make P2 the character that is saved in the
        // header of the ghost that you will see in the race
        data.characterIDs[1] = *(short *)((int)sdata->ptrGhostTapePlaying + 6);

        // restart race
        sdata->Loading.stage = -5;
        return;

    // String 0x2: "Resume"
    case 1:

        // deactivate pause??
        ElimBG_Deactivate(gGT);

        // Unpause game
        gGT->gameMode1 &= 0xfffffffe;

        // unpause audio
        MainFrame_TogglePauseAudio(0);

        OtherFX_Play(1, 1);
        return;

    // String 0x5: "Change Character"
    case 4:

        // Erase ghost of previous race from RAM
        GhostBuffer_Destroy();

        // main menu
        levID = 0x27;

        // Return to character selection
        sdata->mainMenuState = 1;

        // when loading is done
        // add bit for "in menu"
        sdata->Loading.OnBegin.AddBitsConfig0 |= 0x2000;

        // Unpause game
        gGT->gameMode1 &= 0xfffffffe;
        break;

    // String 0x6: "Change Level"
    case 5:

        // Erase ghost of previous race from RAM
        GhostBuffer_Destroy();

        // level ID of main menu
        levID = 0x27;

        // return to track selection
        sdata->mainMenuState = 2;

        // when loading is done
        // add bit for "in menu"
        sdata->Loading.OnBegin.AddBitsConfig0 |= 0x2000;

        // Unpause game
        gGT->gameMode1 &= 0xfffffffe;
        break;

    // String 0xA: "Change Setup"
    case 9:

        // levelID of main menu
        levID = 0x27;

        // return to battle setup
        sdata->mainMenuState = 3;

        // when loading is done
        // add bit for "in menu"
        sdata->Loading.OnBegin.AddBitsConfig0 |= 0x2000;

        // Unpause game
        gGT->gameMode1 &= 0xfffffffe;
        break;

    // String 0xD: "Exit To Map"
    case 0xc:

        // when loading is done
        // add this bit for In Adventure Arena
        sdata->Loading.OnBegin.AddBitsConfig0 |= 0x100000;

        // when loading is done
        // remove bits for Relic Race or Crystal Challenge
        sdata->Loading.OnBegin.RemBitsConfig0 |= 0xc000000;

        // when loading is done
        // remove bit for CTR Token Challenge
        sdata->Loading.OnBegin.RemBitsConfig8 |= 8;

        // Unpause game
        gGT->gameMode1 &= 0xfffffffe;

        // If you are not in Adventure cup
        if ((gameMode & ADVENTURE_CUP) == 0)
        {
            // 0x80000000
            // If you're in Boss Mode
            if (gameMode < 0)
            {
                // when loading is done remove bit for
                // Boss Race, relic, and crystal challenge
                sdata->Loading.OnBegin.RemBitsConfig0 |= 0x8c000000;

                // When loading is done
                // add bit to spawn driver near boss door
                sdata->Loading.OnBegin.AddBitsConfig8 = sdata->Loading.OnBegin.AddBitsConfig8 | 1;
            }

            // set iVar3 to level you were in previously
            levID = gGT->prevLEV;
        }

        // If you're in Adventure Cup
        else
        {
            // Level ID of Gemstone Valley
            levID = 0x19;

            // when loading is done remove bits for
            // Adventure Cup, relic, and crystal challenge
            sdata->Loading.OnBegin.RemBitsConfig0 |= 0x1c000000;

            // Level ID
            gGT->levelID = gGT->cup.cupID + 100;
        }
    default:
        break;
    }
    // load level ID
    MainRaceTrack_RequestLoad(levID);
    return;
}