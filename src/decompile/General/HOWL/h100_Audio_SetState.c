#include <common.h>

void DECOMP_Audio_SetState(u_int state)
{
    u_char XA_type;
    u_char XA_index;

    int iVar1;

    struct GameTracker *gGT = sdata->gGT;
    u_short level;
	
	XA_type = CDSYS_XA_TYPE_MUSIC;

    switch (state)
    {
    // stop/pause cseq music (main: case 2)
    case 1:
        sdata->boolNeedXASeek = 0;

        DECOMP_CDSYS_XAPauseRequest();

        DECOMP_Music_Restart();

        // erase backup, keep music, stop all fx
        DECOMP_howl_StopAudio(1, 0, 1);
        break;
    case 2:
    case 7:

        DECOMP_CseqMusic_StopAll();

        DECOMP_Music_Adjust(0, 0, 0, 0);

        break;
    case 5:

        DECOMP_CseqMusic_StopAll();

		level = gGT->levelID;

        // Level ID on Adventure Arena
        if (level - 0x19U < 5)
        {
            // convert levelID to a bitshifted flag
            DECOMP_Music_Adjust(0, 0, &sdata->advHubSongSet, 1 << (level - 0x19U));
        }
        break;
    case 9:
		XA_index = sdata->desiredXA_RaceIntroIndex;
		sdata->desiredXA_RaceIntroIndex += 1;
		sdata->desiredXA_RaceIntroIndex &= 3;
		goto PLAY_XA;
    
	case 10:

        DECOMP_Music_Stop();

        DECOMP_CseqMusic_StopAll();
        break;
    case 11:

        sdata->WrongWayDirection_bool = false;

        sdata->framesDrivingSameDirection = 0;

        DECOMP_Voiceline_ToggleEnable(1);
        break;

    case 12:

    // last lap, distToFinish < 9000
    case 15:

        DECOMP_Voiceline_ToggleEnable(0);

        sdata->boolNeedXASeek = 1;
        break;

    // if you are on last lap
    case 13:
        sdata->boolNeedXASeek = 0;

        DECOMP_Music_LowerVolume();

        // MUSIC_LAST_LAP
        XA_index = 6;

        goto PLAY_XA;
    case 14:

        sdata->WrongWayDirection_bool = false;

        sdata->framesDrivingSameDirection = 0;

        DECOMP_Music_RaiseVolume();

        DECOMP_Voiceline_ToggleEnable(1);

        break;
    case 16:
        sdata->boolNeedXASeek = 0;

        DECOMP_Music_Restart();

        // set XA
        XA_index = sdata->desiredXA_RaceEndIndex;

        if (61 < XA_index)
        {
            XA_type = CDSYS_XA_TYPE_EXTRA;
        }

    PLAY_XA:

        DECOMP_CDSYS_XAPlay(XA_type, XA_index);
    }
}
