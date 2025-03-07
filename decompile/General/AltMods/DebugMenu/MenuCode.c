#include "DebugStructs.h"

void DebugMenu_InitMenuPositionSize(
	struct DebugMenu* dm, 
	int charSizeX, int charSizeY, 
	int posX, int posY)
{
	int len = 0;
	int rowCount = 0;
	struct DebugRow* dr;
	
	dm->posX = posX;
	dm->posY = posY;
	
	#ifdef REBUILD_PC
	dm->firstRow = dm->currRow;
	#endif
	
	dr = DMENU_GETROWS(dm);
	while(dr->actionFlag != 0)
	{
		int rowLen = strlen(dr->rowText);
		
		if (len < (rowLen+1))
			len = rowLen+1;
		
		dr++;
		rowCount++;
	}
	
	dm->sizeX = (charSizeX * len) + 6;
	dm->sizeY = (charSizeY * rowCount) + 6;
	
	dr = DMENU_GETROWS(dm);
	while(dr->actionFlag != 0)
	{
		if(dr->actionFlag == 1)
		{
			DebugMenu_InitMenuPositionSize(
				dr->subMenu,
				charSizeX, charSizeY,
				dm->posX + dm->sizeX + 10,
				posY);
		}
		
		dr++;
	}
}

extern struct DebugMenu menuDbgMain;

void DebugMenu_Init()
{
	DebugMenu_InitMenuPositionSize(
		&menuDbgMain,8,8,0x14,0x41);
}

void DebugMenu_DrawIfOpen()
{
	struct GameTracker* gGT = sdata->gGT;
	
	int buttonTap = sdata->gGamepads->gamepad[0].buttonsTapped;

	if ((buttonTap & BTN_SELECT) != 0)
		gGT->gameMode1 ^= DEBUG_MENU;

	if ((gGT->gameMode1 & DEBUG_MENU) == 0)
		return;
	
	void DebugMenu_Draw(struct DebugMenu* dm);
	DebugMenu_Draw(&menuDbgMain);
}


void DebugMenu_Update(struct DebugMenu* dm)
{
	int buttonTap = sdata->buttonTapPerPlayer[0];
	
	if (buttonTap != 0)
		DECOMP_RECTMENU_ClearInput();
	
	struct DebugRow* dr = dm->currRow;
	
	if ((buttonTap & BTN_UP) != 0)
	{
		if(dr == DMENU_GETROWS(dm))
			return;
		
		dm->currRow--;
	}
	
	if ((buttonTap & BTN_DOWN) != 0)
	{
		if(dr[1].actionFlag == 0)
			return;
		
		dm->currRow++;
	}
	
	if ((buttonTap & BTN_CROSS) != 0)
	{
		if(dr->actionFlag == 1)
		{
			void DbgMenuEnter(struct DebugMenu* dm);
			DbgMenuEnter(dm);
			
			// link to child
			dm->childMenu = dr->subMenu;
			
			// link to parent
			dm->childMenu->parentMenu = dm;
		}
		
		if(dr->actionFlag == 3)
		{
			struct GameTracker* gGT = sdata->gGT;
			
			dr->funcDbg(gGT, dr->actionParam);
			gGT->gameMode1 &= ~(DEBUG_MENU);
		}
	}
	
	if ((buttonTap & BTN_SQUARE) != 0)
	{
		dm->parentMenu->childMenu = 0;
	}
}

void DebugMenu_Draw(struct DebugMenu* dm)
{
	struct GameTracker* gGT = sdata->gGT;
	
	// must be room for 100 POLY_F4s
	struct PrimMem* primMem = &gGT->backBuffer->primMem;
	POLY_F4* test = primMem->curr;
	test = test + 100;
	if(test > primMem->endMin100) return;
	
	if(dm->childMenu == 0)
		DebugMenu_Update(dm);
	
	// insert primitives to UI
	void* ot = gGT->pushBuffer_UI.ptrOT;
		
	int rowCount = 0;
	struct DebugRow* dr;
	
	char text[16];
	dr = DMENU_GETROWS(dm);
	while(dr->actionFlag != 0)
	{
		void DebugFont_DrawLine(char* text, int posX, int posY, int color);
		
		// Need background box
		// Need arrow indication,
		// Need color
		
		int color = 0x808080;
		if(dr->subMenu == dm->childMenu)
			color = 0x804000;
		
		if(dr == dm->currRow)
			sprintf(text, ">%s", dr->rowText);
		else
			sprintf(text, " %s", dr->rowText);

		DebugFont_DrawLine(
			text,
			3 + dm->posX,
			3 + dm->posY + (rowCount * 8),
			color
		);
		
		dr++;
		rowCount++;
	}
	
	dr = DMENU_GETROWS(dm);
	while(dr->actionFlag != 0)
	{
		if(dr->actionFlag == 1)
		{
			if(dr->subMenu == dm->childMenu)
			{
				DebugMenu_Draw(dr->subMenu);	
			}
		}
		
		dr++;
	}
	
	RECT* r = &dm->posX;
	
	int color = 0;
	DECOMP_CTR_Box_DrawClearBox(r, &color, 0, ot);
}