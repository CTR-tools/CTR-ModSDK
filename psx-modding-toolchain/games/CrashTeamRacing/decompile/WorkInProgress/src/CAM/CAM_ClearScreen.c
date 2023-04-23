#include <common.h>

void DECOMP_CAM_ClearScreen(struct GameTracker* gGT)
{
  char numPlyr;
  char swap;
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  struct DB* backDB;
  int iVar5;
  unsigned int uVar6;
  int iVar7;
  struct TileView* view;
  TILE* tile;
  int iVar11;
  int iVar12;

  backDB = gGT->backBuffer;
  tile = backDB->primMem.curr;
  numPlyr = gGT->numPlyrCurrGame;
  swap = gGT->swapchainIndex;

  for (iVar12 = 0; iVar12 < numPlyr; iVar12++)
  {
    // pointer to tileView struct
    view = &gGT->tileView[iVar12];

    // window sizeX
    sVar1 = view->rect.w;

    // window startX
    sVar2 = view->rect.x;

    // window startY
    sVar3 = view->rect.y;

    // window sizeY
    sVar4 = (short)view->rect.h;

    // tileView rotation
	// view up/down will change where the line splits.
	// At 0x800, camera looks straight, and line is perfectly midpoint
    iVar5 = ((int)view->rot[0] + -0x800 >> 3) + (sVar4 - (sVar4 >> 0xf) >> 1);

	// if splitline is above top of screen,
	// camera looks far down and only sees bottom half
    if (iVar5 < 0)
    {
	  // top half has zero height
      iVar5 = 0;
    }
	
	// if splitline is below bottom of the screen,
	// top quad height is window sizeY, bottom quad is zero height
    iVar7 = sVar4;

	// if splitline is below top of screen
    if (iVar5 < sVar4)
    {
	  // set midpoint accordingly
      iVar7 = iVar5;
    }
	

    // if top-half clear color exists,
	// and if splitline is below top of screen (so top quad exists)
    if ((gGT->level1->clearColor[0].enable != 0) && (0 < iVar7))
    {
      tile->x0 = sVar2;
	  tile->y0 = ((int)sVar3 + swap * 0x128);
      tile->w = sVar1; 
	  tile->h = iVar7;

      *(int*)&tile->r0 = (unsigned int)gGT->level1->clearColor[0].rgb[0] | 0x2000000;

      *(int*)&tile->tag = view->ptrOT[0x3ff] | 0x3000000;
      view->ptrOT[0x3ff] = tile & 0xffffff;
	  tile++;
    }

    // if bottom-half clear color exists,
	// and if splitline is above bottom of screen (so bottom quad exists)
    if ((gGT->level1->clearColor[1].enable != 0) && (iVar7 < sVar4))
    {
      tile->x0 = sVar2;
	  tile->y0 = ((int)sVar3 + swap * 0x128 + iVar7);
      tile->w = sVar1; 
	  tile->h = sVar4 - iVar7;

      *(int*)&tile->r0 = (unsigned int)gGT->level1->clearColor[1].rgb[0] | 0x2000000;

      *(int*)&tile->tag = view->ptrOT[0x3ff] | 0x3000000;
      view->ptrOT[0x3ff] = tile & 0xffffff;
	  tile++;
    }
  }
  
  backDB->primMem.curr = tile;

  return;
}