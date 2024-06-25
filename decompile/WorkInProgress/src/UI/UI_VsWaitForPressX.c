#include <common.h>

void DECOMP_UI_VsWaitForPressX(void)
{
  char i,j;
  char numAttacked;
  short sVar4;
  int *puVar6;
  int iVar8;
  int string;
  int local_78;
  short shortArr3P4P[2*4];
  char acStack88[8];
  short local_50;
  short local_4e;
  char *local_38;
  char *local_34;

  *(int*)&shortArr3P4P[0] = 0x350055;
  *(int*)&shortArr3P4P[2] = 0x3500aa;
  *(int*)&shortArr3P4P[4] = 0x430055;
  *(int*)&shortArr3P4P[6] = 0x4300aa;

  struct Driver *currDriver;
  struct RECT *viewport;
  struct GameTracker *gGT = sdata->gGT;
  char numPlyr = gGT->numPlyrCurrGame;
  short ready = 0;
  int tap;
  u_int pressedX;
  u_int eor_flag;

  // if a player exists
  if (numPlyr)
  {
    local_34 = acStack88;

    for (i = 0; i < numPlyr; i++)
    {
      // flags, for which players have pressed X to continue
      pressedX = sdata->Battle_EndOfRace.Flags_PressX[i];

      viewport = &gGT->pushBuffer[i].rect;

      // Pointer to each player (9900C, 99010, etc)
      currDriver = gGT->drivers[i];

      // get buttons tapped
      tap = sdata->gGamepads[i].gamepad->buttonsTapped;

      // If Player has not pressed X to continue
      // Draw comment, and battle stats
      if ((*pressedX & 2) == 0)
      {
        // If you hit left or right on the D-Pad, or Analog Stick
        if (((tap & 4) != 0) ||
            ((tap & 8) != 0))
        {
          // Flip the first bit
          // If it is 1, make it 0
          // If it is 0, make it 1
          *pressedX = *pressedX ^ 1;
        }

        // If player hit X (to blacken their screen to proceed to next menu)
        if (((tap & 0x1010) != 0) &&

            // if cooldown has gone down a bit,
            // This way you can't press X immediately
            // after seeing on-screen comments
            (gGT->timerEndOfRaceVS < 0x78))
        {
          // Flip the 2nd bit, change 0 to 2
          pressedX = pressedX ^ 2;
        }

        // If you want to see YOU HIT (assumed by default)
        // set string to YOU HIT
        string = 0x157;

        // If you want to see HIT YOU
        if ((pressedX & 1) != 0)
        {
          // if you want to see who hit you
          string = 0x158;
        }

        // If you're in Battle Mode
        if ((gGT->gameMode1 & 0x20) != 0)
        {
          local_78 - 0x7ffc;

          // ivar9 0x157: YOU HIT
          // ivar9 0x158: HIT YOU
          DecalFont_DrawLine(sdata->lngStrings[string],

                             // Midpoint between pushBuffer Start X and End X
                             viewport->x + (viewport->w >> 1),

                             (viewport->y + 0x23),

                             3, 0xffff8004);

          // if numPlyrCurrGame is not zero
          if (numPlyr)
          {
            // same as checking HIT YOU vs YOU HIT before
            local_38 = pressedX;

            // If you have 3 screens, you need 9 prints
            // If you have 4 screens, you need 16 prints

            // for (a in players)
            // for (b in players)
            // print a hit b
            // print b hit a

            for (j = 0; j < numPlyr; j++)
            {
              // Get Battle Team of player
              sVar4 = (short)gGT->drivers[j]->BattleHUD.teamID;

			  short* shortArr;

              // 3P4P
              shortArr = &shortArr3P4P[0];

              if (numPlyr == 2)
              {
                shortArr = &sdata->Battle_EndOfRace.textFlags1_2P[0];
              }

              local_50 = puVar6[j];
              local_4e = *(short *)((int)puVar6[j] + 2);
              iVar8 = (int)local_4e;

              // YOU HIT THEM
              if ((*local_38 & 1) == 0)
              {
                numAttacked = currDriver->numTimesAttackingPlayer[0];
              }

              // HIT YOU
              else
              {
                numAttacked = currDriver->numTimesAttackedByPlayer[0];
              }

              sprintf(acStack88, "p%d:%2.02d",

                      // basically, j + 1
                      // which is (1, 2, 3, 4)
                      (j + 1),

                      // Amount of times this player hit you,
                      // or amount of times you hit them
                      numAttacked,

                      local_78);

              local_78 = (sVar4 + 0x18U | 0x8000);

              DecalFont_DrawLine(acStack88,

                                 // midpoint between Start X and Size X
                                 (viewport->x + shortArr[j*2+0]),

                                 // midpoint between Start Y and Size Y
                                 (viewport->y + shortArr[j*2+1]),

                                 2);
            }
          }
        }
      }

      // If Player has pressed X to continue
      else
      {
        // Stop drawing comment + battle stats

        memset(local_34, 0, 4);

        // rectangle parameters, screen dimensions
        r.x = viewport->x;
        r.y = viewport->y;
        r.w = viewport->w;
        r.h = viewport->h;

        Color color = *(Color *)local_34;
        DECOMP_CTR_Box_DrawClearBox(&r, color, 0, gGT->backBuffer->otMem.startPlusFour);

        // If player presses Square, to go back to view End-Of-Race comment,
        // or in Battle mode this includes "Hit You / You Hit" screen
        if ((tap & 0x8000) != 0)
        {
          // Flip 2nd bit back from 1 to 0
          *pressedX = *pressedX ^ 2;
        }

        // increment counter of players ready to continue
        ready++;
      }
    }
  }

  // if number players ready to continue is equal to numPlyrCurrGame
  // Basically: If all players press X to continue
  if (ready == numPlyr)
  {
    // Stop drawing 4 screens, draw 1 screen and options
    gGT->timerEndOfRaceVS = 0;
    eor_flag = &sdata->Battle_EndOfRace.textFlags1_2P; // 8008d567 ?
    for (j = 3; -1 < j; j--)
    {
      *eor_flag = 0;
      eor_flag -= 1;
    }
  }
  return;
}
