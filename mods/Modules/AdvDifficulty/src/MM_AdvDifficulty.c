#include <common.h>
#include "macro.h"

extern struct MenuRow rows_advDifficulty[];
extern struct MenuRow rows_extraDifficulty[];

void MM_AdvDifficulty(struct MenuBox *mb)
{
	char row = mb->rowSelected;
	struct MenuBox *prevBox = mb->ptrPrevBox_InHierarchy;

	// if uninitialized
	if (row == -1)
	{
		prevBox->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
		return;
	}

	short arcadeDifficulty = 0;

	if (prevBox == &OVR_230.menubox_adventure && row < 6)
	{
		switch (row)
		{
		case 0:
			arcadeDifficulty = 0;
			break;
		case 4:
			arcadeDifficulty = 0x140;
			break;
		case 5:
			arcadeDifficulty = 0x280;
			break;
		default:
			arcadeDifficulty = OVR_230.cupDifficultySpeed[row-1];
			break;
		}
		OVR_230.desiredMenu = 0;
	}
	// if you are in Arcade menu
	else if (row < 5)
	{
		switch (row)
		{
		case 3:
			arcadeDifficulty = 0x140;
			break;
		case 4:
			arcadeDifficulty = 0x280;
			break;
		default:
			arcadeDifficulty = OVR_230.cupDifficultySpeed[row];
			break;
		}
		OVR_230.desiredMenu = 2;
	}
	sdata->gGT->arcadeDifficulty = arcadeDifficulty;
	OVR_230.MM_State = 2;
	mb->state |= ONLY_DRAW_TITLE;
}

struct MenuBox extra_difficulty =
    {
        #if BUILD == JpnRetail
        .stringIndexTitle = 354,
		#else
		.stringIndexTitle = 345,
		#endif
        .posX_curr = 0,
        .posY_curr = 0,
        .unk1 = 0,
        .state = CENTER_ON_X | USE_SMALL_FONT | BIG_TEXT_IN_TITLE,
        .rows = rows_extraDifficulty,
        .funcPtr = MM_AdvDifficulty,
        .width = 171,
        .height = 86
		};

struct MenuBox adv_difficulty =
    {
		#if BUILD == JpnRetail
        .stringIndexTitle = 354,
		#else
		.stringIndexTitle = 345,
		#endif
        .posX_curr = 0,
        .posY_curr = 0,
        .unk1 = 0,
        .state = CENTER_ON_X | USE_SMALL_FONT | BIG_TEXT_IN_TITLE,
        .rows = rows_advDifficulty,
        .funcPtr = MM_AdvDifficulty,
        .width = 171,
        .height = 86
		};