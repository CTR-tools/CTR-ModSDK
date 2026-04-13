#include <common.h>

void DECOMP_BOTS_Killplane(struct Thread* botThread)
{
	char i;
	char boolOverride;
	char currNav;
	char backCount;
	short override;
	struct NavFrame* frame;
	struct Driver* bot;

	// get object from thread
	bot = botThread->object;

	boolOverride = false;

	// check for Tiny Arena
	if (sdata->gGT->levelID == TINY_ARENA)
	{
		// edge-case override?
		switch (bot->unknown_lap_related[1])
		{
		case 0x94:
			override = 0x84;
			break;
		case 0xa0:
			override = 0x80;
			break;
		default:
			override = 0xff;
		}

		if (override != 0xff)
		{
			// pointer to nav point
			frame = bot->botData.botNavFrame;

			// goBackCount
			backCount = frame->goBackCount;
			boolOverride = (backCount < (override - 1));

			while ((boolOverride || (override + 1 < backCount)))
			{
				// nav path index
				i = bot->botData.botPath;

				// go back to previous point
				frame -= 1;

				// if this is less than address of first nav point
				if (frame < sdata->NavPath_ptrNavFrameArray[i])
				{
					// go to last nav point
					frame = sdata->NavPath_ptrHeader[i]->last - 0x14;
				}

				backCount = frame->goBackCount;
				boolOverride = (backCount < (override - 1));
			}
			bot->botData.botNavFrame = frame;
			boolOverride = true;
		}
	}

	// if not Tiny Arena, or goBackCount didn't happen
	if (!boolOverride)
	{
		// pointer to navFrame
		frame = bot->botData.botNavFrame;

		// current nav point (player turned AI)
		currNav = bot->unknown_lap_related[1];

		// goBackCount
		backCount = frame->goBackCount;

		while ((backCount == currNav || ((frame->flags & 0x4000) != 0)))
		{
			// nav path index
			i = bot->botData.botPath;

			// go back one navFrame
			frame -= 1;

			// if you go back to far
			if (frame < sdata->NavPath_ptrNavFrameArray[i])
			{
				// loop back to last navFrame
				frame = &sdata->NavPath_ptrHeader[i]->last[-1];
			}
			backCount = frame->goBackCount;
			currNav = bot->unknown_lap_related[1];
		}
		// save ptr to nav frame
		bot->botData.botNavFrame = frame;
	}

	DECOMP_BOTS_MaskGrab(botThread);
	return;
}