#include <common.h>

// You see this in 1P mode, right before traffic lights count down
void DECOMP_UI_RaceStart_IntroText1P(void) {
   short windowHeight;
   struct GameTracker * gGT;
   int iVar2;
   int gameMode;
   int posX;
   short * txtArray;
   char * pcVar6;
   short sVar7;
   short font;
   int textID;
   int transition;
   char trackText[12];
   RECT rect;
   int colors[2];

   gGT = sdata->gGT;

   // by default, do not transition
   // title bars to off-screen
   transition = 0;

   gameMode = gGT -> gameMode1;

   // If you are not in a relic race
   if ((gameMode & 0x4000000) == 0) {
      // BONUS ROUND
      textID = 0xbe;

      // If you are not in Crystal challenge
      if ((gameMode & 0x8000000) == 0) {

         // If you are not in Adventure Cup
         if ((gameMode & 0x10000000) == 0) {

            // If you are not in Arcade or VS cup
            if ((gGT -> gameMode2 & 0x10) == 0) {

               // ARCADE
               textID = 0x4e;

               if (
                  // If you're in Arcade Mode
                  ((gameMode & 0x400000) != 0) ||

                  (
                     // TIME TRIAL
                     textID = 0x4d,

                     // if you are in time trial mode
                     (gameMode & 0x20000) != 0
                  )
               ) goto LAB_80055930;

               if (-1 < gameMode) {
                  // TROPHY RACE
                  textID = 0xb7;

                  // If you're in a CTR Token Race
                  if ((gGT -> gameMode2 & 8) != 0) {
                     // CTR CHALLENGE
                     textID = 0x176;
                  }
                  goto LAB_80055930;
               }
               iVar2 = gGT -> bossID;
               txtArray = & data.lng_challenge;
            }

            // If you are in Arcade or VS cup
            else {
               // Get Cup ID
               iVar2 = gGT -> cup.cupID;
               txtArray = & data.arcadeVsCupStringIndex;
            }
         }

         // If you are in Adventure Cup
         else {
            // Get Cup ID
            iVar2 = gGT -> cup.cupID;
            txtArray = & data.advCupStringIndex;
         }

         // Get the name of the cup
         // Wumpa, Nitro, Crystal
         // Red, Green, Purple, etc
         textID = txtArray[iVar2];
      }
   }

   // If you are in Relic Race
   else {
      // RELIC RACE
      textID = 0xb8;
   }
   LAB_80055930:

      // if fly-in animation is one second away from finishing
      if (gGT -> cameraDC -> unk8E < 0x1f) {
         // use this to transition title bars to off-screen
         transition = 0x1e - gGT -> cameraDC -> unk8E;
      }

   // RaceFlag_IsFullyOnScreen
   iVar2 = RaceFlag_IsFullyOnScreen();

   // if not
   if (iVar2 == 0) {
      // Draw big string
      font = FONT_BIG;

      // used for transitioning bars to off-screen
      windowHeight = transition;

      if (

         // If you are not in Adventure cup
         ((gameMode & 0x10000000) == 0) &&

         // If you are not in Arcade or VS cup
         (((gGT -> gameMode2 & 0x10) == 0))
      )
	  {
		#if 0
         // X-value, X + W/2
         posX = gGT->pushBuffer[0].rect.x + ((gGT->pushBuffer[0].rect.w << 0x10) >> 0x11);
		#else
		 posX = 0x100; // screw it
		#endif

         // string of top title bar
         pcVar6 = sdata -> lngStrings[textID];

         // Y-value that transitions title text to off-screen
         sVar7 = gGT->pushBuffer[0].rect.y - (windowHeight + -7);
      }

      // If you are in any cup of any kind
      else {
         // Name of Cup

         // uVar9 * 4
         DECOMP_DecalFont_DrawLine(
            sdata -> lngStrings[textID],

			#if 0
            gGT->pushBuffer[0].rect.x + ((gGT->pushBuffer[0].rect.w << 0x10) >> 0x11),
            #else
			0x100, // screw it
			#endif

			((gGT->pushBuffer[0].rect.y - (transition + -7)) + -6),
            FONT_BIG, (JUSTIFY_CENTER | ORANGE)
         );

         // Track 1/4, 2/4, 3/4, 4/4 in cup
         sprintf(trackText, "%s %ld/4",

            // TRACK
            sdata -> lngStrings[0x175],

            // Track Index (0, 1, 2, 3) + 1
            (gGT -> cup.trackIndex) + 1);

         // string of top title bar
         pcVar6 = trackText;

         // X-value, centered
         posX = 0x100;

         // Draw small string
         font = FONT_SMALL;

         // Y-value that transitions title text to off-screen
         sVar7 = (gGT->pushBuffer[0].rect.y - (transition + -7)) + 0xb;
      }

      // Print top title text "Arcade, Time Trial, etc"
      DECOMP_DecalFont_DrawLine(pcVar6, posX, sVar7, font, (JUSTIFY_CENTER | ORANGE));

      // Print the name of the level
      // Crash Cove, Roos Tubes, etc
      DECOMP_DecalFont_DrawLine(

         // 83a88 = 110
         // 8d878 + 110*4 -> Dingo Canyon

         // Level ID
         sdata -> lngStrings[data.metaDataLEV[gGT -> levelID].name_LNG],

		 #if 0
         gGT->pushBuffer[0].rect.x + ((gGT->pushBuffer[0].rect.w << 0x10) >> 0x11),
		 #else
		 0x100, // screw it
		 #endif

         (gGT->pushBuffer[0].rect.y + gGT->pushBuffer[0].rect.h + transition + -0x17),
         FONT_BIG, (JUSTIFY_CENTER | ORANGE));

	  // same for all
	  rect.x = gGT->pushBuffer[0].rect.x;
      rect.w = gGT->pushBuffer[0].rect.w;

	  // 2-pixel height
	  // random generic color
      colors[0] = sdata->battleSetup_Color_UI_1;
	  rect.h = 2;

      // Draw tiny rectangle near big black title bar (first)
      rect.y = gGT->pushBuffer[0].rect.y - (windowHeight + -0x1c);
      Color color;
      color.self = colors[0];
      DECOMP_CTR_Box_DrawSolidBox(&rect, color,
         gGT->backBuffer->otMem.startPlusFour);

      // Draw tiny rectangle near big black title bar (second)
	  rect.y = gGT->pushBuffer[0].rect.y + gGT->pushBuffer[0].rect.h + windowHeight + -0x1e;
      DECOMP_CTR_Box_DrawSolidBox(&rect, color,
         gGT->backBuffer->otMem.startPlusFour);

	  // 30-pixel height
      // clear RGB, keep alpha (which is zero anyway)
      colors[0] = colors[0] & 0xff000000;
      color.self = colors[0];
	  rect.h = 0x1e;

      // draw big black title bar (first)
	  rect.y = gGT->pushBuffer[0].rect.y - windowHeight;
      DECOMP_CTR_Box_DrawSolidBox(&rect, color,
         gGT->backBuffer->otMem.startPlusFour);

      // draw big black title bar (second)
	  rect.y = gGT->pushBuffer[0].rect.y + gGT->pushBuffer[0].rect.h + windowHeight + -0x1e;
      DECOMP_CTR_Box_DrawSolidBox(&rect, color,
         gGT->backBuffer->otMem.startPlusFour);
   }
   return;
}
