#include <common.h>

void DECOMP_BOTS_Adv_AdjustDifficulty(void)
{
  char i;
  short *difficultyParams;
  short *params1;
  short *params2;
  short baseModifier;
  int currDifficulty;
  int maxDifficulty;
  int modifier;
  char rowOrder[4];
  // char local_1c[12];
  struct GameTracker *gGT = sdata->gGT;
  u_int gameMode1 = gGT->gameMode1;

  short cupDifficulty = 0;

  // If you're in a Boss Race
  // 0x80000000
  if (gGT->gameMode1 < 0)
  {
    sdata->difficultyParams[0] = data.BossDifficulty[gGT->bossID].params1;
    sdata->difficultyParams[1] = data.BossDifficulty[gGT->bossID].params2;
  }
  // If you're not in a Boss Race
  // 0x80000000
  else
  {
    sdata->difficultyParams[0] = data.ArcadeDifficulty[gGT->levelID].params1;
    sdata->difficultyParams[1] = data.ArcadeDifficulty[gGT->levelID].params2;
  }

  u_int advCheat = (gGT->gameMode2 & 0x40000);

  // If you're not in Arcade Mode
  if ((gameMode1 & ARCADE_MODE) == 0)
  {
    // If you're not in Adventure Cup
    if ((gameMode1 & ADVENTURE_CUP) == 0)
    {
      // If you're in a Boss Race
      // 0x80000000
      if ((int)gameMode1 < 0)
      {
        // base difficulty modifier based on number of times lost
        baseModifier = BOTS_Adv_NumTimesLostEvent(sdata->advProgress.timesLostBossRace[gGT->bossID]);
        maxDifficulty = gGT->bossID * 5;
        modifier = baseModifier - 225; 

        // if Adv Difficulty cheat is activated
        if (advCheat != 0)
        {
          maxDifficulty = gGT->bossID * 7;
          modifier = baseModifier - 321;
        }
      }
      // If you're not in a Boss Race
      else
      {
        short trophyIndex = gGT->currAdvProfile.numTrophies + 1;
        baseModifier = BOTS_Adv_NumTimesLostEvent(sdata->advProgress.timesLostRacePerLev[gGT->levelID]);
        modifier = baseModifier - 60;
        maxDifficulty = (trophyIndex * 35) >> 2;

        // if negative (never happens to my knowledge)
        // if (maxDifficulty < 0)
        // {
        //   maxDifficulty += 3;
        // }

        // if Adv Difficulty cheat is activated
        if (advCheat != 0)
        {
          modifier = baseModifier - 100;
          maxDifficulty = trophyIndex * 12;
        }
      }
      currDifficulty = maxDifficulty - modifier;
    }
    // If you're in Adventure Cup
    else
    {
      short track = gGT->cup.trackIndex;
      baseModifier = BOTS_Adv_NumTimesLostEvent(sdata->advProgress.timesLostCupRace[track]);
      maxDifficulty = track * 5;
      // If you're in Purple Gem Cup
      if (gGT->cup.cupID == 4)
      {
        modifier = baseModifier - 225;

        // if Adv Difficulty cheat is activated
        if (advCheat != 0)
        {
          maxDifficulty = track * 7;
          modifier = baseModifier - 321;
        }
      }
      // If you're in Adventure Cup (Red, Green, Blue, Yellow)
      else
      {
        modifier = baseModifier - 205;

        // if Adventure Difficulty cheat is activated
        if (advCheat != 0)
        {
          maxDifficulty = track * 7;
          modifier = baseModifier - 300;
        }
      }
      currDifficulty = maxDifficulty - modifier;
      goto CUP_DIFFICULTY;
    }
  }
  // If you're in Arcade Mode
  else
  {
    // Get Difficulty mode (Easy, Medium, Hard)
    currDifficulty = gGT->arcadeDifficulty;

    // If Super Hard Mode is enabled
    if ((gGT->gameMode2 & CHEAT_SUPERHARD) != 0)
    {
      // Override difficulty
      currDifficulty = 0x140;
    }
  CUP_DIFFICULTY:
    cupDifficulty = currDifficulty + 0x50;
  }

  // each track and mode points to different arrays
  params1 = sdata->difficultyParams[0];
  params2 = sdata->difficultyParams[1];

  difficultyParams = sdata->arcade_difficultyParams;

  // reset if difficulty value got too big (?)
  if ((currDifficulty << 0x10) < 0)
    currDifficulty = 0;

  for (i = 0; i < 14; i++)
  {
    difficultyParams[i] = params1[i] + (short)((currDifficulty * (params2[i] - params1[i])) / 0xf0);
  }

  difficultyParams = sdata->cup_difficultyParams;

  // if you are playing any cup mode
  if (((gameMode1 & ADVENTURE_CUP) != 0) || ((gGT->gameMode2 & CUP_ANY_KIND) != 0))
  {
    for (i = 0; i < 14; i++)
    {
      difficultyParams[i] = params1[i] + (short)((cupDifficulty * (params2[i] - params1[i])) / 0xf0);
    }
  }

  // reset counter
  sdata->unk_counter_upTo450 = 0;

  // set RNG constant if not
  if ((sdata->const_0x30215400 == 0) && (sdata->const_0x493583fe == 0))
  {
    sdata->const_0x30215400 = 0x30215400;
    sdata->const_0x493583fe = 0x493583fe;
  }

  // loop through 3 AI paths
  for (i = 0; i < 3; i++)
  {
    // lazy memset
    LIST_Clear(&sdata->unk_NavRelated[i]);

    // If you are not in a cutscene and not in main menu
    if ((gameMode1 & (GAME_CUTSCENE | MAIN_MENU)) == 0)
    {
      // Initialize each AI path (0,1,2)
      BOTS_InitNavPath(gGT, i);
    }
  }

  BOTS_SetGlobalNavData(0);

  // set number of AIs to zero
  gGT->numBotsNextGame = 0;

  // If you are not in Arcade or VS cup
  if (((gGT->gameMode2 & CUP_ANY_KIND) == 0) || (gGT->cup.trackIndex == 0))
  {
    if (gGT->numPlyrCurrGame == 2)
    {
      // {0, 1, 2, 4, 5, 6, 3, 7}
      *(int *)&sdata->kartSpawnOrderArray[0] = data.kartSpawnOrder.VS_2P_1;
      *(int *)&sdata->kartSpawnOrderArray[4] = data.kartSpawnOrder.VS_2P_2;
    }
    else if (2 < gGT->numPlyrCurrGame)
    {
      // {0, 1, 2, 3, 4, 5, 6, 7}
      *(int *)&sdata->kartSpawnOrderArray[0] = data.kartSpawnOrder.VS_3P_4P_1;
      *(int *)&sdata->kartSpawnOrderArray[4] = data.kartSpawnOrder.VS_3P_4P_2;
    }

    // If you're not loading and
    // If you're not in Time Trial
    if ((gameMode1 & (LOADING | TIME_TRIAL)) == 0)
    {
      // If you're not in Crystal Challenge (in adventure mode)
      if ((gameMode1 & CRYSTAL_CHALLENGE) == 0)
      {

        // If you're in Boss Race
        if ((int)gameMode1 < 0)
        {
          // {0, 1, 2, 3, 4, 5, 6, 7}
          *(int *)&sdata->kartSpawnOrderArray[0] = data.kartSpawnOrder.boss_challenge_1;
          *(int *)&sdata->kartSpawnOrderArray[4] = data.kartSpawnOrder.boss_challenge_2;
        }

        // If you're not in Boss Race
        else
        {

          // If you're not in Adventure Cup
          if (((gameMode1 & ADVENTURE_CUP) == 0) ||

              // If this is not the purple gem cup
              (gGT->cup.cupID != 4))
          {

            // If you're not in Adventure Mode
            if ((gameMode1 & ADVENTURE_MODE) == 0)
            {
              // {0, 1, 2, 3, 4, 5, 6, 7}
              *(int *)&sdata->kartSpawnOrderArray[0] = data.kartSpawnOrder.arcade_1;
              *(int *)&sdata->kartSpawnOrderArray[4] = data.kartSpawnOrder.arcade_2;
            }
          }
          // If this is Puprle Gem Cup
          else
          {
            // {0, 1, 2, 3, 4, 5, 6, 7}
            *(int *)&sdata->kartSpawnOrderArray[0] = data.kartSpawnOrder.purple_cup_1;
            *(int *)&sdata->kartSpawnOrderArray[4] = data.kartSpawnOrder.purple_cup_2;
          }
        }
      }

      // If you're in Crystal Challenge (in adventure mode)
      else
      {
        // {0, 1, 2, 3, 4, 5, 6, 7}
        *(int *)&sdata->kartSpawnOrderArray[0] = data.kartSpawnOrder.crystal_challenge_1;
        *(int *)&sdata->kartSpawnOrderArray[4] = data.kartSpawnOrder.crystal_challenge_2;
      }
    }

    // If you're Loading or in Time Trial
    else
    {
      // {1, 2, 0, 3, 4, 5, 6, 7}
      *(int *)&sdata->kartSpawnOrderArray[0] = data.kartSpawnOrder.time_trial_1;
      *(int *)&sdata->kartSpawnOrderArray[4] = data.kartSpawnOrder.time_trial_2;
    }
  }

  u_int rng = RngDeadCoed(&sdata->const_0x30215400);
  rowOrder[0] = 0;
  // local_1c[0] = 0;
  rowOrder[1] = rng & 1;
  // local_1c[1] = rowOrder[1] ^ 1;
  rowOrder[2] = rowOrder[1] + 1;
  // local_1c[2] = local_1c[1] + 1;
  rowOrder[3] = 2;
  // local_1c[3] = 2;

  for (i = 0; i < 8; i++)
  {
    // nav path index of this driver
    sdata->driver_pathIndexIDs[i] = rowOrder[sdata->kartSpawnOrderArray[i]];
  }

  // If you're in Boss Race
  if ((int)gameMode1 < 0)
  {
    // P1 goes to path 0
    sdata->driver_pathIndexIDs[0] = 0;

    // Boss goes to path 1
    sdata->driver_pathIndexIDs[1] = 1;
  }

  // If this is Battle mode
  if ((gameMode1 & BATTLE_MODE) != 0)
  {
    // loop 4 players
    for (i = 0; i < 4; i++)
    {
      // nav path index of this driver
      sdata->driver_pathIndexIDs[i] = (char)((rng & 0xfff) / 0x555);
    }
  }

  // if you are in any cup,
  // and if this is not the first track
  if ((((gameMode1 & ADVENTURE_CUP) != 0) || ((gGT->gameMode2 & CUP_ANY_KIND) != 0)) && gGT->cup.trackIndex != 0)
  {
    short playerPoint = -1;
    char playerIndex = 0;
    char topIndex = 0;

    // loop all drivers
    for (i = 0; i < 8; i++)
    {
      if ((gGT->numPlyrCurrGame <= i) &&
          // point has not been updated?
          (playerPoint < gGT->cup.points[i]))
      {
        playerPoint = gGT->cup.points[i];
        playerIndex = i;
      }

      // if this driver starts at top speed
      if (sdata->accelerateOrder[i] == 0)
      {
        topIndex = i;
      }
      // swap accel order
      char temp = sdata->accelerateOrder[playerIndex];
      sdata->accelerateOrder[playerIndex] = sdata->accelerateOrder[topIndex];
      sdata->accelerateOrder[topIndex] = temp;
    }
  }
  else
  {
    rng = (rng >> 8) & 3;

    for (i = 0; i < 4; i++, rng++)
    {
      rowOrder[i] = rng;
      // local_1c[i] = rng + 4;
    }

    for (i = 0; i < 8; i++)
    {
      // set acceleration order to spawn order?
      sdata->accelerateOrder[i] = rowOrder[sdata->kartSpawnOrderArray[i]];
    }
  }
}
