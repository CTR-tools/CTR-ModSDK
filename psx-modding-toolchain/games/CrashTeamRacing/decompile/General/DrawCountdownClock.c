#include <common.h>

u_char* ConvertTimeToString(int milliseconds);
void ToggleGameState_EndOfRace();
void DecalFont_DrawLine(char* str, int posX, int posY, short fontType, int flags);

// countdown clock, used for Battle Mode and Crystal Challenge
void DECOMP_DrawCountdownClock(short posX, short posY, short fontType)
{
	struct GameTracker* gGT;
	char* str;
	struct Driver* d;
	u_int flags;
	int i;
	int timeRemaining;

	// amount of time event should last, minus, time elapsed in the event.
	// basically, time remaining in the event
	timeRemaining = sdata->gGT->originalEventTime - sdata->gGT->elapsedEventTime;

	// if you run out of time
	if (timeRemaining < 0)
	{
		// Make a time string with zero milliseconds on the clock
		str = ConvertTimeToString(0);
		gGT = sdata->gGT;

		// If you're not in End-Of-Race menu
		if ((sdata->gGT->gameMode1 & 0x200000) == 0)
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

			ToggleGameState_EndOfRace();
		}
	}

	// if you have not run out of time
	else
	{
		// make a string with the remaining time
		str = ConvertTimeToString(timeRemaining);
	}

	// default color is dark red
	flags = 0x1c;

	if
	(
		// if less than 15 seconds remain
		(timeRemaining < 0x3840) &&

		// if number of frames is an even number
		((sdata->gGT->timer & 1) == 0)
	)
	{
		// set color to white
		flags = 4;
	}

	// put the time string on the screen
	DecalFont_DrawLine(str, (int)posX, (int)posY, (int)fontType, flags);
	return;
}