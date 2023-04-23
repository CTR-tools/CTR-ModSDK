#include <common.h>

// budget: 508,
// before FOR: 408

void DECOMP_CAM_ClearScreen(struct GameTracker* gGT)
{
  char numPlyr;
  char swap;
  short x;
  short y;
  short w;
  short h;
  struct DB* backDB;
  int iVar5;
  int iVar7;
  struct TileView* view;
  TILE* tile;
  int loop;
  struct Level* level1;
  
  unsigned int shiftUp;
  unsigned int shiftDown;

  backDB = gGT->backBuffer;
  tile = backDB->primMem.curr;
  numPlyr = gGT->numPlyrCurrGame;
  swap = gGT->swapchainIndex;
  level1 = gGT->level1;

  for (loop = 0; loop < numPlyr; loop++)
  {
    // pointer to tileView struct
    view = &gGT->tileView[loop];

    x = view->rect.x;
    y = view->rect.y + swap * 0x128;
    w = view->rect.w;
    h = view->rect.h;
	
	shiftUp = (unsigned int)(((unsigned short)h) << 0x10);
	shiftDown = shiftUp >> 0x10;

    // tileView rotation
	// view up/down will change where the line splits.
	// At 0x800, camera looks straight, and line is perfectly midpoint
    iVar5 = ((int)view->rot[0]-0x800 >> 3) + (shiftDown - (shiftUp >> 0x1f) >> 1);

	// if splitline is above top of screen,
	// camera looks far down and only sees bottom half
    if (iVar5 < 0)
    {
	  // top half has zero height
      iVar5 = 0;
    }
	
	// if splitline is below bottom of the screen,
	// top quad height is window sizeY, bottom quad is zero height
    iVar7 = h;

	// if splitline is below top of screen
    if (iVar5 < h)
    {
	  // set midpoint accordingly
      iVar7 = iVar5;
    }

    // if top-half clear color exists,
	// and if splitline is below top of screen (so top quad exists)
    if ((level1->clearColor[0].enable != 0) && (0 < iVar7))
    {
      tile->x0 = x;
	  tile->y0 = y;
      tile->w = w; 
	  tile->h = iVar7;

      *(int*)&tile->r0 = (unsigned int)level1->clearColor[0].rgb[0] | 0x2000000;
      *(int*)&tile->tag = view->ptrOT[0x3ff] | 0x3000000;
      view->ptrOT[0x3ff] = (unsigned int)tile & 0xffffff;
	  tile++;
    }

    // if bottom-half clear color exists,
	// and if splitline is above bottom of screen (so bottom quad exists)
    if ((level1->clearColor[1].enable != 0) && (iVar7 < h))
    {
      tile->x0 = x;
	  tile->y0 = y + iVar7;
      tile->w = w; 
	  tile->h = h - iVar7;

      *(int*)&tile->r0 = (unsigned int)level1->clearColor[1].rgb[0] | 0x2000000;
      *(int*)&tile->tag = view->ptrOT[0x3ff] | 0x3000000;
      view->ptrOT[0x3ff] = (unsigned int)tile & 0xffffff;
	  tile++;
    }
  }
  
  backDB->primMem.curr = tile;

  return;
}