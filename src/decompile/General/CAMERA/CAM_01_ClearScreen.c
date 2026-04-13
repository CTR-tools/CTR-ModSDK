#include <common.h>

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
  struct PushBuffer* pb;
  TILE* tile;
  int loop;
  struct Level* level1;
  u_long* endOT;

  backDB = gGT->backBuffer;
  tile = backDB->primMem.curr;
  numPlyr = gGT->numPlyrCurrGame;
  swap = gGT->swapchainIndex;
  level1 = gGT->level1;

  for (loop = 0; loop < numPlyr; loop++)
  {
    // pointer to pushBuffer struct
    pb = &gGT->pushBuffer[loop];
	endOT = &pb->ptrOT[0x3FF];

    x = pb->rect.x;
    y = pb->rect.y + swap * 0x128;
    w = pb->rect.w;
    h = pb->rect.h;
	
    // pushBuffer rotation
	// cam up/down will change where the line splits.
	// At 0x800, camera looks straight, and line is perfectly midpoint
    iVar5 = ((int)pb->rot[0]-0x800 >> 3) + (h>>1);

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
#ifdef REBUILD_PC
      RECT16 r;
      r.x = x;
      r.y = y;
      r.w = w;
      r.h = iVar7;
      ClearImage(&r,
          level1->clearColor[0].rgb[0],
          level1->clearColor[0].rgb[1],
          level1->clearColor[0].rgb[2]);
#else
      tile->x0 = x;
	  tile->y0 = y;
      tile->w = w; 
	  tile->h = iVar7;

      *(int*)&tile->r0 = *(int*)&level1->clearColor[0].rgb[0];
	  tile->code = 0x2;
      
	  *(int*)tile = *(unsigned int*)endOT | 0x3000000;
      *(unsigned int*)endOT = (unsigned int)tile & 0xffffff;
	  
	  tile++;
#endif
    }

    // if bottom-half clear color exists,
	// and if splitline is above bottom of screen (so bottom quad exists)
    if ((level1->clearColor[1].enable != 0) && (iVar7 < h))
    {
#ifdef REBUILD_PC
      RECT16 r;
      r.x = x;
      r.y = y+iVar7;
      r.w = w;
      r.h = h-iVar7;
      ClearImage(&r,
          level1->clearColor[1].rgb[0],
          level1->clearColor[1].rgb[1],
          level1->clearColor[1].rgb[2]);
#else
      tile->x0 = x;
	  tile->y0 = y + iVar7;
      tile->w = w; 
	  tile->h = h - iVar7;

      *(int*)&tile->r0 = *(int*)&level1->clearColor[1].rgb[0];
	  tile->code = 0x2;

	  *(int*)tile = *(unsigned int*)endOT | 0x3000000;
      *(unsigned int*)endOT = (unsigned int)tile & 0xffffff;

	  tile++;
#endif
    }
  }
  
  backDB->primMem.curr = tile;

  return;
}