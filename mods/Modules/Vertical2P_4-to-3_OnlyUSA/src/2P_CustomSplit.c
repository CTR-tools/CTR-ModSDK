#include <common.h>

// stored in RDATA
void CustomSplit()
{
	int i;
	struct TileView* tileView;
	POLY_F4* p;
	int numPlyrCurrGame;
	register unsigned int* sp asm("$sp");

	numPlyrCurrGame = sdata->gGT->numPlyrCurrGame;

	// JMP to CustomSplit happens right after this, in MainFrame_RenderFrame
	//if ((sdata->gGT->renderFlags & 0x8000) != 0)

    if (
		(
			// If you're in Battle Mode
			(sdata->gGT->gameMode1 & BATTLE_MODE) &&

			// if numPlyrCurrGame is more than 2
			(2 < numPlyrCurrGame)
		)
	 )
	{
		for(i = 0; i < numPlyrCurrGame; i++)
		{
			tileView = &sdata->gGT->tileView[i];

			// Draw a 2D box made of four rectangles
			MENUBOX_DrawOuterRect_LowLevel(

				// dimensions, thickness
				(RECT*)&tileView->rect.x,4,2,

				// color data
				data.ptrColor[sdata->gGT->drivers[i]->BattleHUD.teamID + PLAYER_BLUE],

				0,

				// tileView_UI = 0x1388
				&sdata->gGT->tileView_UI.ptrOT[3]);
		}
    }

	// changed in this mod:
	// draw horizontal split when
	// numPlyrCurrGame > 2, instead of 1

    if (numPlyrCurrGame > 2)
	{
		p = (POLY_F4*)sdata->gGT->backBuffer->primMem.curr;

		// set R, G, B, CODE, all to zero,
		// this makes black color, and invalid CODE
		*(int*)&p->r0 = 0;

		// this sets CODE to the proper value
		setPolyF4(p);

		// Make four (x,y) coordinates
		p->y0 = 0x6a;
		p->y1 = 0x6a;
		p->x0 = 0;
		p->x1 = 0x200;

		p->x2 = 0;
		p->y2 = 0x6e;
		p->x3 = 0x200;
		p->y3 = 0x6e;

		// Draw a bar from left to right,
		// dividing the screen in half on top and bottom
		AddPrim(&sdata->gGT->tileView_UI.ptrOT[3],p);

		// backBuffer->primMem.curr
		sdata->gGT->backBuffer->primMem.curr = (void*)(p + 1);
    }

	// changed in this mod:
	// draw vertical split when
	// numPlyrCurrGame > 1, instead of 2

	if (numPlyrCurrGame > 1)
	{
		p = sdata->gGT->backBuffer->primMem.curr;

		// set R, G, B, CODE, all to zero,
		// this makes black color, and invalid CODE
		*(int*)&p->r0 = 0;

		// this sets CODE to the proper value
		setPolyF4(p);

		// Make four (x,y) coordinates
		p->x0 = 0xfd;
		p->x2 = 0xfd;
		p->y0 = 0;
		p->x1 = 0x103;

		p->y1 = 0;
		p->y2 = 0xd8;
		p->x3 = 0x103;
		p->y3 = 0xd8;

		// Draw a bar from left to right,
		// dividing the screen in half on top and bottom
		AddPrim(&sdata->gGT->tileView_UI.ptrOT[3],p);

		// backBuffer->primMem.curr
		sdata->gGT->backBuffer->primMem.curr = (void*)(p + 1);
    }

	// if numPlyrCurrGame is 3
    if (numPlyrCurrGame == 3)
	{
		// This is useless, cause it gets cleared
		// to black anyway, even without this block,
		// at least it does it Crash Cove, does it always?

		p = sdata->gGT->backBuffer->primMem.curr;

		// set R, G, B, CODE, all to zero,
		// this makes black color, and invalid CODE
		*(int*)&p->r0 = 0;

		// this sets CODE to the proper value
		setPolyF4(p);

		// xy0
		p->x0 = 0x100;
		p->x2 = 0x100;
		p->y0 = 0x6c;
		p->y1 = 0x6c;
		p->x1 = 0x200;
		p->y2 = 0xd8;
		p->x3 = 0x200;
		p->y3 = 0xd8;

		// Draw a bar from left to right,
		// dividing the screen in half on top and bottom
		AddPrim(&sdata->gGT->tileView_UI.ptrOT[3],p);

		// backBuffer->primMem.curr
		sdata->gGT->backBuffer->primMem.curr = (void*)(p + 1);
    }
	
	// go back to RenderFrame
	// check assembly, it fetches $ra here
	
	// assembles sw [this] 2C(sp)
	// then does lw ra 2C(sp), 
	// custom $ra accomplished
	sp[0xB] = 0x80037768;
	
	return;
}