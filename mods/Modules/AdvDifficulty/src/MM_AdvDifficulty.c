#include <common.h>
#include "macro.h"

extern struct MenuRow rows_advDifficulty[];
extern struct MenuRow rows_extraDifficulty[];

void MM_AdvDifficulty(struct RectMenu* menu)
{
	char row = menu->rowSelected;
	struct RectMenu *prevBox = menu->ptrPrevBox_InHierarchy;

	// if uninitialized
	if (row == -1)
	{
		prevBox->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
		return;
	}

	short arcadeDifficulty = 0;

	if (prevBox == &D230.menuAdventure && row < 6)
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
			arcadeDifficulty = D230.cupDifficultySpeed[row-1];
			break;
		}
		D230.desiredMenuIndex = 0;
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
			arcadeDifficulty = D230.cupDifficultySpeed[row];
			break;
		}
		D230.desiredMenuIndex = 2;
	}
	sdata->gGT->arcadeDifficulty = arcadeDifficulty;
	D230.MM_State = 2;
	menu->state |= ONLY_DRAW_TITLE;
}

struct RectMenu extra_difficulty =
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

struct RectMenu adv_difficulty =
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