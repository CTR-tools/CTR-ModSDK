#include <common.h>

// countdown clock, used for Battle Mode and Crystal Challenge
void DECOMP_UI_DrawLimitClock(short posX, short posY, short fontType)
{
	struct GameTracker* gGT;
	char* str;
	struct Driver* d;
	u_int flags;
	int i;
	int timeRemaining;
	gGT = sdata->gGT;

	// amount of time event should last, minus, time elapsed in the event.
	// basically, time remaining in the event
	timeRemaining = gGT->originalEventTime - gGT->elapsedEventTime;

	// if you run out of time
	if (timeRemaining < 0)
	{
		// Make a time string with zero milliseconds on the clock
		str = DECOMP_RECTMENU_DrawTime(0);

		// If you're not in End-Of-Race menu
		if ((gGT->gameMode1 & END_OF_RACE) == 0)
		{
			// dont check if numPlyrCurrGame != 0,
			// when would that ever be false

			// end race for all players
			for(i = 0; i < gGT->numPlyrCurrGame; i++)
			{
				// pointer of each player (P1, P2, P3, P4)
				d = gGT->drivers[i];

				//end the race for every racer
				d->actionsFlagSet |= 0x2000000;
			};

#ifndef REBUILD_PC
			MainGameEnd_Initialize();
#endif
			
		}
	}

	// if you have not run out of time
	else
	{
		// make a string with the remaining time
		str = DECOMP_RECTMENU_DrawTime(timeRemaining);
	}

	// default color is dark red
	flags = DARK_RED;

	if
	(
		// if less than 15 seconds remain
		(timeRemaining < 0x3840) &&

		// if number of frames is an even number
		((gGT->timer & FPS_DOUBLE(1)) == 0)
	)
	{
		// set color to white
		flags = WHITE;
	}

	// put the time string on the screen
	DECOMP_DecalFont_DrawLine(str, (int)posX, (int)posY, (int)fontType, flags);
	return;
}