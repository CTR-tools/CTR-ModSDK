#include <common.h>

void DECOMP_UI_VsQuipDrawAll(void) {
  short posX;
  short posY;
  short width;
  short height;
  short* printIndex;
  char* print;
  struct Driver* d;
  RECT r;
  struct GameTracker* gGT = sdata->gGT;
  struct ThreadBucket* bucket;
  short i;
  char acStack160[128];

  // pointer to first Player thread
  bucket = &gGT->threadBuckets[0];
  // initialize iterator
  i = 0;

  // if thread exists
  if (bucket != 0) {

    // loop through all threads
    do {
      // get current player's pushBuffer
      r = gGT->pushBuffer[i].rect;
      // Dimensions of each player's pushBuffer
      // PosX, PosY, Width, Height
      posX = r.x;
      posY = r.y;
      width = r.w;
      height = r.h;

      // get player struct from thread
      d = bucket->thread->object;
      // if anyone press x at end-of-race screen

      // Player struct's Offset 0x56c holds which LNG string
      // will be this player's End-Of-Race comment,
      // 0 - PAUSED, 1 - RESTART, 21A - The Dominator, etc
      printIndex = (short*)d->EndOfRaceComment_lngIndex;

      if ((( & sdata->Battle_EndOfRace.Flags_PressX)[i] & 2) == 0 &&

        // make sure the comment is valid
        (printIndex != 0)) {

        printIndex[1] = 0;

        // if this is only one comment
        if ((printIndex[1] & 1) == 0) {
          // Print the string as a comment
          print = sdata->lngStrings[*printIndex];
        }

        // if the comment is conjoined
        else {
          // Add two strings together
          sprintf(acStack160, "%s%s",

            // original end-of-race comment
            sdata->lngStrings[*printIndex],

            // second part of comment,
            // lngIndex of driver,
            // for stuff like "hit by Crash Bandicoot" or something

            sdata->lngStrings[data.MetaDataCharacters[d->EndOfRaceComment_characterID].name_LNG_long]);

          // Overwrite the stack pointer to print
          print = acStack160;
        }

        // Draw the string with a box around it
        RECTMENU_DrawQuip(
          // The string to print
          print,

          // X-position of pushBuffer, plus 50% of width
          (posX + (width >> 1)),

          // Y-position of pushBuffer, plus 12% of height
          (posY + (height >> 3)),

          0, 3, 0xffff8000, 4);
      }

      // next player thread
      bucket = bucket->unk2;
      // increment loop counter
      i++;
    } while (bucket != 0);
  }
  return;
}