#include <common.h>

u_int DECOMP_Music_AsyncParseBanks(void)
{
    char bVar1;
    char newState;
    u_short index;
    u_int uVar4;
    struct GameTracker *gGT = sdata->gGT;
    struct Bank thisBank;
    int level = gGT->levelID;
	char* arr = &sdata->audioDefaults[7];

    // loading state of song (one byte)
    switch (arr[1])
    {

    case 0:
        // unsuccessful
        if (DECOMP_Bank_AssignSpuAddrs() == 0)
            goto PARSE_FINISH;

        // If you're in a Boss Race
        if (gGT->gameMode1 < 0)
        {
            newState = 1;

            if (5 < gGT->bossID)
                break;

            uVar4 = sdata->songBankBossID[gGT->bossID];
        }
        else
        {
            // Level ID

            // if Level ID < 30
            // any level that can be driven on (Arcade, Battle, Adventure)
            if (level < INTRO_RACE_TODAY)
            {
                // Get index from array
                index = data.levBank_FX[level];
            }
            else
            {
                // If you're drawing main menu
                if (level == MAIN_MENU_LEVEL)
                {
                    index = 0x20;
                }
                else
                {

                    // If you're drawing Any% ending cutscene
                    if (level == OXIDE_ENDING)
                    {
                        index = 0x23;
                    }

                    // If you're drawing 100% ending cutscene
                    else
                    {
                        if (level == OXIDE_TRUE_ENDING)
                        {
                            index = 0x24;
                        }

                        // if you're drawing anything else
                        else
                        {
                            newState = 1;
                            if (level != 44)
                                break;
                            index = 0x25;
                        }
                    }
                }
            }
        }

        DECOMP_Bank_Load(index, &thisBank);

        newState = 1;
        break;

    case 1:
        // unsuccessful
        if (DECOMP_Bank_AssignSpuAddrs() == 0)
            goto PARSE_FINISH;

        sdata->bankCount = 0;
        sdata->bankPodiumStage = 0;
        sdata->bankLoad54 = 0;

        // If you're drawing any Arcade or Battle maps
        if ((level < GEM_STONE_VALLEY) &&

            // Basically:
            // If you're in Trophy Race, CTR Challenge Race,
            // Or non-purple cup (red, green, blue, yellow)
            // Or if you're in Arcade Mode
            
            // This will always be true
            ((((uVar4 = gGT->gameMode1,

                      // If you're in Adventure Mode
                      (uVar4 & ADVENTURE_MODE) != 0 &&

                          // Not in any of these...
                          // Boss Race or Adventure Arena
                          // Or Crystal Challenge or Relic Race
                          ((uVar4 & 0x8c100000) == 0)) &&

                  ((
                      // If you are not in Adventure cup
                      (uVar4 & ADVENTURE_CUP) == 0 ||

                      // If this is not the purple gem cup
                      (gGT->cup.cupID != 4)))) ||

              ((gGT->gameMode1 & ARCADE_MODE) != 0))))
        {
            DECOMP_Bank_Load(54, &thisBank);

            sdata->bankLoad54 = 1;
        }

        newState = 2;

        break;
    case 2:

        if (DECOMP_Bank_AssignSpuAddrs() == 0)
            goto PARSE_FINISH;

        // If you're on any Arcade or Battle map
        if (level < GEM_STONE_VALLEY)
        {
            // not adventure mode, not adventure cup
            if ((((gGT->gameMode1 & ADVENTURE_MODE) == 0) ||

                ((gGT->gameMode1 & ADVENTURE_CUP) == 0)) ||

                // If this is not the purple gem cup
                (gGT->cup.cupID != 4))
            {
                newState = 3;

                // numPlyrCurrGame
                if (sdata->bankCount < gGT->numPlyrCurrGame)
                {
                    if ((sdata->bankLoad54 == 0) ||

                        // if characterID is secret character
                        (7 < data.characterIDs[sdata->bankCount]))
                    {
                        // bank = characterID + 0x37
                        index = data.characterIDs[sdata->bankCount] + 0x37;

                        // load bank
                        goto LOAD_BANK;
                    }

                    // skip load bank
                    goto LAB_8002e178;
                }
            }

            // if purple gem cup, or some other modes
            else
            {
                // load 5 banks, one for each driver
                if (sdata->bankCount < 5)
                {
                    index = data.characterIDs[sdata->bankCount] + 0x37;

                LOAD_BANK:

                    DECOMP_Bank_Load(index, &thisBank);

                LAB_8002e178:
                    sdata->bankCount = sdata->bankCount + 1;
                    goto PARSE_FINISH;
                }
                newState = 3;
            }
        }
        else
        {
            newState = 3;

            // Level ID in the Adventure Arena
            if (level - 25 < 5)
            {
                if (sdata->bankCount == 0)
                {
                    if ((sdata->bankLoad54 != 0) ||

                        // characterID is special character
                        (7 < data.characterIDs[0]))
                    {
                        goto LAB_8002e178;
                    }

                    // bank = characterID + 0x37
                    index = data.characterIDs[0] + 0x37;

                    // load bank
                    goto LOAD_BANK;
                }
                newState = 3;

                // podium reward
                if (gGT->podiumRewardID != 0)
                {
                    if (sdata->bankPodiumStage == 0)
                    {
                        bVar1 = gGT->podium_modelIndex_First;

                    LOAD_BANK_PODIUM:

                        DECOMP_Bank_Load((bVar1 - 88), &thisBank);
                    }
                    else
                    {
                        if (sdata->bankPodiumStage == 1)
                        {
                            if (gGT->podium_modelIndex_Second != 0)
                            {
                                bVar1 = gGT->podium_modelIndex_Second;
                                goto LOAD_BANK_PODIUM;
                            }
                        }
                        else
                        {
                            newState = 3;
                            if (sdata->bankPodiumStage != 2)
                                break;

                            if (gGT->podium_modelIndex_Third != 0)
                            {
                                bVar1 = gGT->podium_modelIndex_Third;
                                goto LOAD_BANK_PODIUM;
                            }
                        }
                    }
                    sdata->bankPodiumStage = sdata->bankPodiumStage + 1;
                    goto PARSE_FINISH;
                }
            }
        }
        break;
    case 3:

        if (DECOMP_Bank_AssignSpuAddrs() == 0)
            goto PARSE_FINISH;

        // If you're in a Boss Race
        // 0x80000000
        if (gGT->gameMode1 < 0)
        {
            index = 0x19;
            if (gGT->bossID < 6)
                goto SET_SONG;
        }
        else
        {
            // if Level ID < 30
            // any level that can be driven on (Arcade, Battle, Adventure)
            if (level < INTRO_RACE_TODAY)
            {
                // Set Song ID depending on track
                index = data.levBank_Song[level];
            }
            else
            {
                if (level == MAIN_MENU_LEVEL)
                {
                    index = 27;
                }
                else
                {
                    if (level == INTRO_RACE_TODAY)
                    {
                        index = 29;
                    }
                    else
                    {
                        if (level == NAUGHTY_DOG_CRATE)
                        {
                            index = 28;
                        }
                        else
                        {
                            // Any% ending
                            if (level == OXIDE_ENDING)
                            {
                                index = 30;
                            }
                            else
                            {
                                // 100% ending
                                if (level == OXIDE_TRUE_ENDING)
                                {
                                    index = 31;
                                }
                                else
                                {
                                    newState = 4;

                                    // If not in credits, quit
                                    if (level != CREDITS_CRASH)
                                        break;

                                    // credits
                                    index = 32;
                                }
                            }
                        }
                    }
                }
            }
        SET_SONG:
            DECOMP_howl_SetSong(index);
        }
        newState = 4;
        break;

    case 4:
        newState = 5;

        if (DECOMP_howl_loadSong() == 0)
            goto PARSE_FINISH;

        break;

    #if 0
    case -0xbad1ab1f:
        goto PARSE_FINISH;
	#endif

    default:
        return 1;
    }

    // loading state of song (one byte)
    arr[1] = newState;
PARSE_FINISH:
    // state == 5 is finished. 
    // if false, function failed.
    return (arr[1] == 5);
}
 