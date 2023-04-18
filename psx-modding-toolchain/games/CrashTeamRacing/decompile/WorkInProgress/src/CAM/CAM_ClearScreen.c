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
  u_long *primmemNext;
  u_long *primmemCurr;
  int iVar11;
  int iVar12;

  backDB = gGT->backBuffer;
  primmemCurr = backDB->primMem.curr;
  numPlyr = gGT->numPlyrCurrGame;

  // if numPlyrCurrGame is not zero
  if (numPlyr)
    return;

  primmemNext = primmemCurr + 1;

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

    // tileView rotation?
    iVar5 = ((int)view->distanceToScreen_PREV + -0x800 >> 3) + (sVar4 - (sVar4 >> 0xf) >> 1);

    if (iVar5 < 0)
    {
      iVar5 = 0;
    }
    iVar7 = sVar4;

    if (iVar5 < sVar4)
    {
      iVar7 = iVar5;
    }

    iVar5 = view->ptrOT;

    // if top-half clear color exists
    if ((gGT->level1->clearColor[0].enable != 0) && (0 < iVar7))
    {
      // swapchain index
      swap = gGT->swapchainIndex;

      // draw colored quad?
      primmemNext[2] = (int)sVar1 | iVar7 << 0x10;

      // Y-pos in VRAM, position of window + swapIndex*0x128
      primmemNext[1] = (int)sVar2 | ((int)sVar3 + swap * 0x128) * 0x10000;

      // top half clear color
      *primmemNext = (unsigned int)gGT->level1->clearColor[0].rgb[0] | 0x2000000;

      primmemNext = primmemNext + 4;
      *primmemCurr = *(unsigned int *)(iVar5 + 0xffc) | 0x3000000;
      uVar6 = (unsigned int)primmemCurr & 0xffffff;
      primmemCurr = primmemCurr + 4;
      *(unsigned int *)(iVar5 + 0xffc) = uVar6;
    }

    // if bottom-half clear color exists
    if ((gGT->level1->clearColor[1].enable != 0) && (iVar7 < sVar4))
    {
      // swapchain index
      swap = gGT->swapchainIndex;

      // draw colored quad?
      primmemNext[2] = (int)sVar1 | (sVar4 - iVar7) * 0x10000;

      // Y-pos in VRAM, position of window + swapIndex*0x128
      primmemNext[1] = (int)sVar2 | ((int)sVar3 + swap * 0x128 + iVar7) * 0x10000;

      // bottom half clear color
      *primmemNext = (unsigned int)gGT->level1->clearColor[1].rgb[0] | 0x2000000;

      primmemNext = primmemNext + 4;
      *primmemCurr = *(unsigned int *)(iVar5 + 0xffc) | 0x3000000;
      uVar6 = (unsigned int)primmemCurr & 0xffffff;
      primmemCurr = primmemCurr + 4;
      *(unsigned int *)(iVar5 + 0xffc) = uVar6;
    }
  }
  // set new backBuffer->primMem.curr
  backDB->primMem.curr = primmemCurr;

  return;
}