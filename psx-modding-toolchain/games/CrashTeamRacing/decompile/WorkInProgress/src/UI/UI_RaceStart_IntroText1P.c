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
   char acStack72[24];
   RECT rect;
   short windowBottom;
   short windowTop;
   short local_2a;
   int colors[2];

   gGT = sdata -> gGT;

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
               iVar2 = sdata -> gGT -> bossID;
               txtArray = & data.lng_challenge;
            }

            // If you are in Arcade or VS cup
            else {
               // Get Cup ID
               iVar2 = sdata -> gGT -> cup.cupID;
               txtArray = & data.arcadeVsCupStringIndex;
            }
         }

         // If you are in Adventure Cup
         else {
            // Get Cup ID
            iVar2 = sdata -> gGT -> cup.cupID;
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

   // TitleFlag_IsFullyOnScreen
   iVar2 = TitleFlag_IsFullyOnScreen();

   // if not
   if (iVar2 == 0) {
      // Draw big string
      font = 1;

      // used for transitioning bars to off-screen
      windowHeight = transition;

      if (

         // If you are not in Adventure cup
         ((gameMode & 0x10000000) == 0) &&

         // If you are not in Arcade or VS cup
         (((gGT -> gameMode2 & 0x10) == 0))
      ) {
         // X-value, not 0x100???
         posX = gGT -> tileView -> rect.x + ((gGT -> tileView -> rect.w << 0x10) >> 0x11);

         // string of top title bar
         pcVar6 = sdata -> lngStrings[textID * 4];

         // Y-value that transitions title text to off-screen
         sVar7 = gGT -> tileView -> rect.y - (windowHeight + -7);
      }

      // If you are in any cup of any kind
      else {
         // Name of Cup

         // uVar9 * 4
         DecalFont_DrawLine(
            sdata -> lngStrings[textID * 4],
            gGT -> tileView -> rect.x + ((gGT -> tileView -> rect.w << 0x10) >> 0x11),
            ((gGT -> tileView -> rect.y - (transition + -7)) + -6),
            1, 0xffff8000
         );

         // Track 1/4, 2/4, 3/4, 4/4 in cup
         sprintf(acStack72, "%s %ld/4",

            // TRACK
            sdata -> lngStrings[0x5d4],

            // Track Index (0, 1, 2, 3) + 1
            (sdata -> gGT -> cup.trackIndex) + 1);

         // string of top title bar
         pcVar6 = acStack72;

         // X-value, centered
         posX = 0x100;

         // Draw small string
         font = 2;

         // Y-value that transitions title text to off-screen
         sVar7 = (gGT -> tileView -> rect.y - (transition + -7)) + 0xb;
      }

      // Print top title text "Arcade, Time Trial, etc"
      DecalFont_DrawLine(pcVar6, iVar2, sVar7, font, 0xffff8000);

      // Print the name of the level
      // Crash Cove, Roos Tubes, etc
      DecalFont_DrawLine(

         // 83a88 = 110
         // 8d878 + 110*4 -> Dingo Canyon

         // Level ID
         sdata -> lngStrings[data.metaDataLEV[sdata -> gGT -> levelID].name_LNG],
         gGT -> tileView -> rect.x + ((gGT -> tileView -> rect.w << 0x10) >> 0x11),
         (gGT -> tileView -> rect.y + gGT -> tileView -> rect.h + transition + -0x17),
         1, 0xffff8000);

      // color of rectangle that touches Black title bar
      colors[0] = sdata -> battleSetup_Color_UI_1;

      // dimensions of window, two-pixels tall
      rect = (gGT -> tileView -> rect);
      windowBottom = gGT -> tileView -> rect.y - (windowHeight + -0x1c);
      windowTop = gGT -> tileView -> rect.h;
      local_2a = 2;

      // Draw tiny rectangle near big black title bar (first)
      // CTR_Box_DrawSolidBox
      CTR_Box_DrawSolidBox( & rect, colors,

         sdata -> gGT -> backBuffer -> otMem.startPlusFour,

         // pointer to PrimMem struct
         &
         sdata -> gGT -> backBuffer -> primMem);

      // dimensions of window, two-pixels tall
      rect = (gGT -> tileView -> rect);
      windowBottom = gGT -> tileView -> rect.y + gGT -> tileView -> rect.h + windowHeight + -0x1e;
      windowTop = gGT -> tileView -> rect.h;
      local_2a = 2;

      // Draw tiny rectangle near big black title bar (second)
      // CTR_Box_DrawSolidBox
      CTR_Box_DrawSolidBox( & rect, colors,

         sdata -> gGT -> backBuffer -> otMem.startPlusFour,

         // pointer to PrimMem struct
         &
         sdata -> gGT -> backBuffer -> primMem);

      // clear RGB, keep alpha (which is zero anyway)
      colors[0] = colors[0] & 0xff000000;

      // dimensions of window, 30-pixels tall
      rect = gGT -> tileView -> rect;
      windowBottom = gGT -> tileView -> rect.y - windowHeight;
      windowTop = gGT -> tileView -> rect.h;
      local_2a = 0x1e;

      // draw big black title bar (first)
      // CTR_Box_DrawSolidBox
      CTR_Box_DrawSolidBox( & rect, colors,

         sdata -> gGT -> backBuffer -> otMem.startPlusFour,

         // pointer to PrimMem struct
         &
         sdata -> gGT -> backBuffer -> primMem);

      // dimensions of window, 30-pixels tall
      rect = gGT -> tileView -> rect;
      windowBottom = gGT -> tileView -> rect.y + gGT -> tileView -> rect.h + windowHeight + -0x1e;
      windowTop = gGT -> tileView -> rect.h;
      local_2a = 0x1e;

      // draw big black title bar (second)
      // CTR_Box_DrawSolidBox
      CTR_Box_DrawSolidBox( & rect, colors,

         sdata -> gGT -> backBuffer -> otMem.startPlusFour,

         // pointer to PrimMem struct
         &
         sdata -> gGT -> backBuffer -> primMem);
   }
   return;
}
 