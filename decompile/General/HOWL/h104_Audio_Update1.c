#include <common.h>

void DECOMP_Audio_Update1(void)
{
    char i;
    short uVar1;
    u_int uVar2;
    struct Driver *d=0;
    u_int maskTempo;
    int iVar7;
    struct GameTracker *gGT = sdata->gGT;

    switch (sdata->unkAudioState - 1)
    {
    case 5:
        if ((sdata->XA_State == 0) || (sdata->XA_Playing_Category != 0))
        {
            DECOMP_Audio_SetState_Safe(5);
        }
        break;
    case 7:
		#ifndef REBUILD_PS1
        Garage_LerpFX();
		#endif
        break;
    case 8:
        if (sdata->XA_State == 0)
        {
            // 9 means intro cutscene
            // 10 means traffic lights
            // 11 means racing

            // Change state to traffic lights
            DECOMP_Audio_SetState_Safe(10);
        }
        break;
    case 9:
        // If traffic lights finish counting down
        // from 0x3840 to zero
        if (gGT->trafficLightsTimer < 1)
        {
            // 9 means intro cutscene
            // 10 means traffic lights
            // 11 means racing

            // Change State to 11, which means racing
            DECOMP_Audio_SetState_Safe(11);
        }
        break;
    case 10:
        DECOMP_Audio_SetMaskSong(0);

		#ifdef USE_ONLINE
		
		d = gGT->drivers[0];
		
		#else

		// human driver in the lead
        for (i = 0; i < 8; i++)
        {
            d = gGT->driversInRaceOrder[i];

            if (
				(d != NULL) &&
                ((d->actionsFlagSet & 0x100000) == 0)
				)
            {
                break;
            }
            d = 0;
        }

		if(d == 0)
			break;
		
		#endif

		#ifndef REBUILD_PS1
        Voiceline_Update();
        Level_AmbientSound();
		#endif

        // Temporary, no Drivers yet
        #ifdef REBUILD_PS1
        break;
        #endif

        // if race has more than 2 laps
        if ((2 < sdata->gGT->numLaps) &&
            // if you are on 2nd to last lap
            ((d->lapIndex == sdata->gGT->numLaps - 2U)) &&
            // distToFinish is small
            (d->distanceToFinish_curr < 9000))
        {
            DECOMP_Audio_SetState_Safe(12);
        }
        break;
    case 11:
        DECOMP_Audio_SetMaskSong(0);

		#ifdef USE_ONLINE
		
		d = gGT->drivers[0];
		
		#else

		// human driver in the lead
        for (i = 0; i < 8; i++)
        {
            d = gGT->driversInRaceOrder[i];

            if (
				(d != NULL) &&
                ((d->actionsFlagSet & 0x100000) == 0)
				)
            {
                break;
            }
            d = 0;
        }
		
		if(d == 0)
			break;
		
		#endif

		// if need to XASeek
        if (((sdata->boolNeedXASeek != 0) && (sdata->XA_State == 0)) &&
            (9 < gGT->frameTimer_MainFrame_ResetDB - sdata->XA_PauseFrame))
        {
            // far from finish line
            if (2000 < d->distanceToFinish_curr)
            {
                // (FINAL LAP! music)
                DECOMP_CDSYS_XASeek(1, 0, 6);
            }
			
			// dont need to XASeek
            sdata->boolNeedXASeek = 0;
        }

		#ifndef REBUILD_PS1
        Level_AmbientSound();
		#endif

        // if driver is on final lap
        if (d->lapIndex == gGT->numLaps - 1U)
        {
            // Play final lap sound
            DECOMP_Audio_SetState_Safe(13);
        }
        break;
    case 12:
        maskTempo = 0;

        // if XA has been playing more than a second
        if (0xe1 < sdata->XA_CurrOffset)
        {
            DECOMP_Music_RaiseVolume();

            maskTempo = 20;
        }

        DECOMP_Audio_SetMaskSong(maskTempo);

		#ifndef REBUILD_PS1
        Level_AmbientSound();
		#endif

        if (sdata->XA_State == 0)
        {
            DECOMP_Audio_SetState_Safe(14);
        }
        break;
    case 13:
        DECOMP_Audio_SetMaskSong(20);

		#ifdef USE_ONLINE
		
		d = gGT->drivers[0];
		
		#else

		// human driver in the lead
        for (i = 0; i < 8; i++)
        {
            d = gGT->driversInRaceOrder[i];

            if (
				(d != NULL) &&
                ((d->actionsFlagSet & 0x100000) == 0)
				)
            {
                break;
            }
            d = 0;
        }
		
		if(d == 0)
			break;
		
		#endif

		#ifndef REBUILD_PS1
        Voiceline_Update();
        Level_AmbientSound();
		#endif

        if (
				// if driver's lap is the last lap
				(d->lapIndex == gGT->numLaps - 1U) &&

                // if finish line is close
                (d->distanceToFinish_curr < 9000)
			)
            {
                DECOMP_Audio_SetState_Safe(15);
            }

        break;
    case 14:

		#ifdef USE_ONLINE
		
		d = gGT->drivers[0];
		
		#else

		// human driver in the lead
		for (i = 0; i < 8; i++)
        {
            d = gGT->driversInRaceOrder[i];

            if (
				(d != NULL) &&
                (d->instSelf->thread->modelIndex == DYNAMIC_PLAYER)
				)
            {
                break;
            }
            d = 0;
        }
		
		if(d == 0)
			break;
		
		#endif

		// if need to XASeek
        if (((sdata->boolNeedXASeek != 0) && (sdata->XA_State == 0)) &&
            (9 < gGT->frameTimer_MainFrame_ResetDB - sdata->XA_PauseFrame))
        {
            // far from finish line
            if (2000 < d->distanceToFinish_curr)
            {
                DECOMP_CDSYS_XASeek(1, 0, 4);
            }
			
			// dont need to XASeek
            sdata->boolNeedXASeek = 0;
        }

		#ifndef REBUILD_PS1
        Level_AmbientSound();
		#endif

        // if the race is over for this racer
        if ((d->actionsFlagSet & 0x2000000) != 0)
        {
            // if did not just open N Tropy
            if ((gGT->unknownFlags_1d44 & 0x8000) == 0)
            {
                // If you did not just beat N Tropy in Time Trial
                if ((gGT->unknownFlags_1d44 & 0x10000000) == 0)
                {
					// defeat music
					uVar1 = 5;
					
                    if (
							(d->driverRank == 0) ||
							((gGT->gameMode1 & ADVENTURE_CUP) != 0) ||
							((gGT->gameMode2 & CUP_ANY_KIND) != 0)
					   )
                    {
                        DECOMP_OtherFX_Play(0x5f, 0);

						// victory (fanfare) music
                        uVar1 = 4;
                    }
                }

                // If you just beat N Tropy in Time Trial
                else
                {
                    // Check if N Tropy has been beaten on all tracks
                    uVar2 = DECOMP_GAMEPROG_CheckGhostsBeaten(1);

                    // If there is a track where N Tropy has not been beaten
                    if ((uVar2 & 0xffff) == 0)
                    {
                        // OtherFX_Play
                        DECOMP_OtherFX_Play(0x5f, 0);

                        // count how many times N Tropy has been beaten
                        // during this playthrough
                        iVar7 = sdata->nTropyVoiceCount;
                        sdata->nTropyVoiceCount = iVar7 + 1;

                        // pick an N Tropy XA voiceline
                        uVar1 = data.nTropyXA[iVar7];

                        // if beaten more than 5 times
                        if (5 < sdata->nTropyVoiceCount)
                        {
                            // go back to 0
                            sdata->nTropyVoiceCount = 0;
                        }
                    }

                    // If N Tropy has been beaten on all tracks
                    else
                    {
                        DECOMP_OtherFX_Play(0x5f, 0);

                        // N Tropy Unlocked XA
                        // "you've earned the right to choose me in character selection"
                        uVar1 = 0x43;
                    }
                }
            }

            // if n tropy just opened
            else
            {
                // OtherFX_Play
                DECOMP_OtherFX_Play(0x5f, 0);

                // N Tropy opened
                // "Think your fast eh, well, lets see if you can beat my fastest time"
                uVar1 = 0x46;
            }

            // desired XA
            sdata->desiredXA_3 = uVar1;

            DECOMP_Audio_SetState_Safe(0x10);
        }
        break;
    case 15:

		#ifndef REBUILD_PS1
        Level_AmbientSound();
		#endif

        if (sdata->XA_State == 0)
        {
            DECOMP_Audio_SetMaskSong(0);
        }
    }
}