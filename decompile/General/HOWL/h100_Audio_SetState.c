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

        CDSYS_XAPauseRequest();

        Music_Restart();

        // erase backup, keep music, stop all fx
        howl_StopAudio(1, 0, 1);
        break;
    case 2:
    case 7:

        CseqMusic_StopAll();

        Music_Adjust(0, 0, 0, 0);

        break;
    case 5:

        CseqMusic_StopAll();

		level = gGT->levelID;

        // Level ID on Adventure Arena
        if (level - 0x19U < 5)
        {
            // convert levelID to a bitshifted flag
            Music_Adjust(0, 0, &sdata->advHubSongSet, 1 << (level - 0x19U));
        }
        break;
    case 9:
        
		// hack to save byte budget
		//CDSYS_XAPlay(XA_type, (int)sdata->desiredXA_1);

        iVar1 = (int)sdata->desiredXA_1 + 1;
        XA_index = iVar1;
        if (iVar1 < 0)
        {
            XA_index = (int)sdata->desiredXA_1 + 4;
        }
        sdata->desiredXA_1 = iVar1 + (XA_index >> 2) * -4;
		
		// hack to save byte budget,
		// jmp to XAPlay call instead of "break"
		XA_index = iVar1 - 1;
		goto PLAY_XA;
		//break;
    
	case 10:

        Music_Stop();

        CseqMusic_StopAll();
        break;
    case 11:

        sdata->WrongWayDirection_bool = false;

        sdata->framesDrivingSameDirection = 0;

        Voiceline_ToggleEnable(1);
        break;

    case 12:

    // last lap, distToFinish < 9000
    case 15:

        Voiceline_ToggleEnable(0);

        sdata->boolNeedXASeek = 1;
        break;

    // if you are on last lap
    case 13:
        sdata->boolNeedXASeek = 0;

        Music_LowerVolume();

        // MUSIC_LAST_LAP
        XA_index = 6;

        goto PLAY_XA;
    case 14:

        sdata->WrongWayDirection_bool = false;

        sdata->framesDrivingSameDirection = 0;

        Music_RaiseVolume();

        Voiceline_ToggleEnable(1);

        break;
    case 16:
        sdata->boolNeedXASeek = 0;

        Music_Restart();

        // set XA
        XA_index = sdata->desiredXA_3;

        if (61 < XA_index)
        {
            XA_type = CDSYS_XA_TYPE_EXTRA;
        }

    PLAY_XA:

        CDSYS_XAPlay(XA_type, XA_index);
    }
}
