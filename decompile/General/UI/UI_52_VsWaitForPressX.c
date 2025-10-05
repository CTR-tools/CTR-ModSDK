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

  *(int*)&shortArr3P4P[0] = 0x350055;
  *(int*)&shortArr3P4P[2] = 0x3500aa;
  *(int*)&shortArr3P4P[4] = 0x430055;
  *(int*)&shortArr3P4P[6] = 0x4300aa;

  RECT *r;
  struct Driver *currDriver;
  
  struct GameTracker* gGT = sdata->gGT;
  char numPlyr = gGT->numPlyrCurrGame;
  
  int tap;
  int ready = 0;
  char* pressedX;

  for (i = 0; i < numPlyr; i++)
  {
    // flags, for which players have pressed X to continue
    pressedX = &sdata->Battle_EndOfRace.boolPressX[i];

    currDriver = gGT->drivers[i];
    r = &gGT->pushBuffer[i].rect;
    tap = sdata->gGamepads->gamepad[i].buttonsTapped;

    // If Player has not pressed X to continue
    // Draw comment, and battle stats
    if ((*pressedX & 2) == 0)
    {
      // If you hit left or right on the D-Pad, or Analog Stick
      if ((tap & (BTN_LEFT | BTN_RIGHT)) != 0)
      {
        // Invert &1 bit
        *pressedX = *pressedX ^ 1;
      }

      if (
			// ready to continue, after cooldown
			(gGT->timerEndOfRaceVS < 0x78) &&
			((tap & (BTN_CROSS | BTN_START)) != 0)
		)
      {
		// invert &2 bit
        *pressedX = *pressedX ^ 2;
      }

      // If you're in Battle Mode
      if ((gGT->gameMode1 & BATTLE_MODE) != 0)
      {
		// ivar9 0x157: YOU HIT
		// ivar9 0x158: HIT YOU
		string = 0x157 + (*pressedX & 1);
		
		DecalFont_DrawLine(sdata->lngStrings[string],

                           // Midpoint between pushBuffer Start X and End X
                           r->x + (r->w >> 1),

                           (r->y + 0x23),

                           3, 0xffff8004);

        // If you have 3 screens, you need 9 prints
        // If you have 4 screens, you need 16 prints

        // for (a in players)
        // for (b in players)
        // print a hit b
        // print b hit a

        for (j = 0; j < numPlyr; j++)
        {
          // 3P4P
          short* shortArr = &shortArr3P4P[0];

          if (numPlyr == 2)
          {
            shortArr = &sdata->Battle_EndOfRace.textFlags1_2P;
          }

          // YOU HIT THEM
          if ((*pressedX & 1) == 0)
          {
            numAttacked = currDriver->numTimesAttackingPlayer[j];
          }

          // HIT YOU
          else
          {
            numAttacked = currDriver->numTimesAttackedByPlayer[j];
          }

		  // only 8 bytes, use scratchpad
		  
          sprintf(0x1f800000, "p%d:%2.02d",

                  // basically, j + 1
                  // which is (1, 2, 3, 4)
                  (j + 1),

                  // Amount of times this player hit you,
                  // or amount of times you hit them
                  numAttacked);


		  // Get font color based on battle team
          sVar4 = (short)gGT->drivers[j]->BattleHUD.teamID;
          local_78 = (sVar4 + 0x18U | 0x8000);


          DecalFont_DrawLine(0x1f800000,

                             // midpoint between Start X and Size X
                             (r->x + shortArr[j*2+0]),

                             // midpoint between Start Y and Size Y
                             (r->y + shortArr[j*2+1]),

                             2, local_78);
        }
      }
    }

    // If Player has pressed X to continue
    else
    {
      // Stop drawing comment + battle stats

	  // 4-byte RGBA = black
	  *(int*)0x1f800000 = 0;
      DECOMP_CTR_Box_DrawClearBox(r, 0x1f800000, 0, gGT->backBuffer->otMem.startPlusFour);

      // Allow Go-Back option to YouHit/HitYou
      if ((tap & BTN_SQUARE) != 0)
      {
        // invert &2 bit
        *pressedX = *pressedX ^ 2;
      }

      // increment counter of players ready to continue
      ready++;
    }
  }

  // If all players press X to continue
  if (ready == numPlyr)
  {
    // Stop drawing 4 screens, draw 1 screen and options
    gGT->timerEndOfRaceVS = 0;
    *(int*)&sdata->Battle_EndOfRace.boolPressX[0] = 0;
  }
  
  return;
}
