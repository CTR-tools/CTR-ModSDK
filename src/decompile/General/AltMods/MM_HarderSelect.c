
#define ROW_EASY 0
#define ROW_MEDIUM 1
#define ROW_HARD 2
#define ROW_SUPER_HARD 3
#define ROW_ULTRA_HARD 4
#define EXD_VALID_ROWS 5

struct MenuRow rowsHarder[] =
{
    {346, 0,1,0,0}, // EASY
	{347, 0,2,1,1}, // MEDIUM
    {348, 1,3,2,2}, // HARD
	
    {7, 2,4,3,3}, // SUPER HARD // 588
	{8, 3,4,4,4}, // ULTRA HARD // 589
	
	{-1}
};

void MM_MenuHarderProc(struct RectMenu* menu);

struct RectMenu menuHarder =
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
    .rows = rowsHarder,
    .funcPtr = MM_MenuHarderProc,
    .width = 171,
    .height = 86
};

void MM_MenuHarderProc(struct RectMenu* menu)
{
	short row = menu->rowSelected;

	// if uninitialized
	if (row == -1)
	{
		menu->ptrPrevBox_InHierarchy->state &= 
			~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
		return;
	}

	// if you are on a valid row
	if (row < EXD_VALID_ROWS)
	{
		struct GameTracker* gGT = sdata->gGT;
		
		if (row == ROW_SUPER_HARD)
			gGT->arcadeDifficulty = 0x140; // original super hard cheat value
		else if (row == ROW_ULTRA_HARD)
			gGT->arcadeDifficulty = 0x280; // popular ultra hard gameshark code
		else
			gGT->arcadeDifficulty = D230.cupDifficultySpeed[row];

		D230.desiredMenuIndex = 2;
		D230.MM_State = 2;
		menu->state |= ONLY_DRAW_TITLE;
	}
}