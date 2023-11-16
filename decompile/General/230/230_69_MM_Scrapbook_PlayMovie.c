#include <common.h>

// prevent compiler optimization from screwing us over,
// it does not know VsyncCallback will change swapchainIndex,
// never update the register, and crash the game
DRAWENV* ScrapbookGetDrawEnv()
{
	struct GameTracker* gGT = sdata->gGT;
	return &gGT->db[1 - gGT->swapchainIndex].drawEnv;
}

void DECOMP_MM_Scrapbook_PlayMovie(struct MenuBox *mb)
{
    short lev;
    int cdPos;
	int getButtonPress=0;
	DRAWENV* ptrDrawEnv;
    const CdlFILE cdlFile;
    struct GameTracker *gGT = sdata->gGT;
	int isOn = DECOMP_TitleFlag_IsFullyOnScreen();

    // book state (0,1,2,3,4)
    switch (D230.scrapbookState)
    {

    // Init State,
    // alter checkered flag
    case 0:
        if (isOn == 1)
        {
            // checkered flag, begin transition off-screen
            DECOMP_TitleFlag_BeginTransition(2);
        }

        // go to Load State
        D230.scrapbookState = 1;

        mb->state &= ~NEEDS_TO_CLOSE;

		#ifndef REBUILD_PS1
        Audio_SetState_Safe(1);
		#endif

        break;

    // Load State,
    // find the TEST.STR file
    case 1:

        // if not fully off screen
        if (DECOMP_TitleFlag_IsFullyOffScreen() != 1)
        {
            // quit, dont start video yet
            return;
        }

        DECOMP_CDSYS_SetMode_StreamData();

        // \TEST.STR;1
        // if file was found
        if (CdSearchFile(&cdlFile, R230.s_teststr1) != 0)
        {
#ifndef REBUILD_PS1
            SpuSetCommonCDVolume(sdata->vol_Music << 7, sdata->vol_Music << 7);

            // Alloc memory to store Scrapbook
            MM_Video_AllocMem(0x200, 0xd0, 10, 0x40, 1);

            cdPos = CdPosToInt(&cdlFile.pos);

            // scrapbook runs 15fps,
            // see bottom of Duckstation screen while running

            // scrapbook is 4.91 min, 4 mins + 54 sec,
            // (4424 total / 15fps / 60 sec per min) mins,
            // 0x1148 = 4424 = numFrames

            // CD position of video, and numFrames
            MM_Video_StartStream(cdPos, 0x1148);
#endif

            // start playing movie
            D230.scrapbookState = 2;

            return;
        }

        goto GO_BACK;

    // Actually play the movie
    case 2:
	
#ifndef REBUILD_PS1
        // infinite loop (cause this is scrapbook),
        // keep doing DecodeFrame and VSync until done
        while (
			
			// gGT->DB[nextFrame] (swapchain flips in VsyncCallback)
			ptrDrawEnv = ScrapbookGetDrawEnv(),
            
			MM_Video_DecodeFrame(
				ptrDrawEnv->ofs[0],
				ptrDrawEnv->ofs[1] + 4) == 0)
        {
            VSync(0);
        }
		
		// If you press Start, Cross, Circle, Triangle, or Square
		getButtonPress = (sdata->buttonTapPerPlayer[0] & 0x41070);

        if (
				// if movie is finished,
				// means scrapbook ended, no looping
				(MM_Video_CheckIfFinished(0) == 1) ||
				(getButtonPress != 0)
			)
#endif
        {
            if (getButtonPress != 0)
            {
                DECOMP_TitleFlag_SetFullyOnScreen();
            }

            // stop video
            D230.scrapbookState = 3;
        }

        VSync(4);
        break;

    // return disc to normal,
    // return checkered flag to normal
    case 3:
#ifndef REBUILD_PS1
        SpuSetCommonCDVolume(0, 0);

        MM_Video_StopStream();

        MM_Video_ClearMem();
#endif

        if (DECOMP_TitleFlag_IsFullyOffScreen() == 1)
        {
            // checkered flag, begin transition on-screen
            DECOMP_TitleFlag_BeginTransition(1);
        }
    GO_BACK:

        // return to gameplay
        D230.scrapbookState = 4;
        break;

    // send player back to adv hub,
    // or back to main menu
    case 4:
        if (isOn == 1)
        {
            // change checkered flag back
            DECOMP_TitleFlag_SetDrawOrder(0);

			// if adventure mode
			lev = GEM_STONE_VALLEY;

            // If you're not in Adventure Mode
            if ((gGT->gameMode1 & ADVENTURE_MODE) == 0)
            {
                lev = MAIN_MENU_LEVEL;
				
                DECOMP_MM_JumpTo_Title_Returning();

                // return to main menu (adv, tt, arcade, vs, battle)
                sdata->mainMenuState = 0;
            }

			#ifndef REBUILD_PS1
            MainRaceTrack_RequestLoad(lev);
			#endif
			
            DECOMP_MENUBOX_Hide(mb);
        }
        break;
    default:
        return;
    }
}