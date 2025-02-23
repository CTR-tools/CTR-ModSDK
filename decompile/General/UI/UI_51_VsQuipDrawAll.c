#include <common.h>

void DECOMP_UI_VsQuipDrawAll(void) 
{
  char* print;
  short* printArr;
  struct Driver* d;
  
  struct GameTracker* gGT = sdata->gGT;
  struct Thread* thread;
  
  // loop through player threads
  for(
		thread = gGT->threadBuckets[0].thread;
		thread != 0;
		thread = thread->siblingThread
	)
  {
    // get player struct from thread
    d = (struct Driver*)thread->object;
	
	// If driver already pressed X to continue
	if ((sdata->Battle_EndOfRace.boolPressX[d->driverID] & 2) != 0)
		continue;

    // This is secretly a short[2], to hold a config bit
    printArr = (short*)d->EndOfRaceComment_ptrQuip;
	
	if (printArr == 0)
		continue;

	printArr[2] = 0;
	printArr[3] = 0;
	
	// if this is only one comment
	if ((printArr[1] & 1) == 0) 
	{
		// Print the string as a comment
		print = sdata->lngStrings[printArr[0]];
	}
	
	// if the comment is conjoined
	else 
	{
		// Add two strings together
		sprintf(0x1f800000,
	
			// Contains '%s' format:
			// Original end-of-race comment
			sdata->lngStrings[printArr[0]],
	
			// second part of comment,
			// lngIndex of driver,
			// for stuff like "hit by Crash Bandicoot" or something
			sdata->lngStrings[data.MetaDataCharacters[d->EndOfRaceComment_characterID].name_LNG_long]);
	
		// Overwrite the stack pointer to print
		print = 0x1f800000;
	}

    // get current player's pushBuffer
	RECT* r = &gGT->pushBuffer[d->driverID].rect;

    // Draw the string with a box around it
    RECTMENU_DrawQuip(
      print,
      (r->x + (r->w >> 1)), // 50% width
      (r->y + (r->h >> 3)), // 12% height
      0, 3, 0xffff8000, 4);
  }
}