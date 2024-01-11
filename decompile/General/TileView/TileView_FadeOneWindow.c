#include <common.h>

void DECOMP_TileView_FadeOneWindow(struct TileView *view)
{
  typedef struct
  {
    u_int tag;
    u_int tpage;
    POLY_F4 f4;
  } multiCmdPacket;

  short newFade;
  int fadeStrength;
  multiCmdPacket *p = NULL;

  struct DB *backBuffer = sdata->gGT->backBuffer;

  // if tileView->fadeFromBlack_currentValue
  // is not 0x1000, which means there must be
  // some amount of fading
  if (view->fadeFromBlack_currentValue != 0x1000)
  {
    p = (POLY_F4 *)backBuffer->primMem.curr;

    setlen(p, 7);
    p->f4.tag = 0;
    p->f4.code = 0x2a;
    p->f4.x0 = 0;
    p->f4.y0 = 0;

    // if we are fading to black
    if (view->fadeFromBlack_currentValue < 0x1001)
    {
      p->tpage = 0xe1000a40;

      // get strength of fade (0 to 0x1000)
      fadeStrength = 0xfff - newFade;
    }
    else
    {
      // fade to white
      p->tpage = 0xe1000a20;

      // get strength of fade (0 to 0x1000)
      fadeStrength = view->fadeFromBlack_currentValue - 0x1000;
    }

    // strength of fade
    fadeStrength = fadeStrength >> 4;

    p->f4.r0 = (u_char)fadeStrength;
    p->f4.g0 = (u_char)fadeStrength;
    p->f4.b0 = (u_char)fadeStrength;
    p->f4.x1 = view->rect.w;
    p->f4.y1 = 0;
    p->f4.x2 = 0;
    p->f4.y2 = view->rect.h;
    p->f4.x3 = view->rect.w;
    p->f4.y3 = view->rect.h;
    AddPrim(view->ptrOT, p);

    // move pointer after writing polygons
    backBuffer->primMem.curr = (int)p + sizeof(multiCmdPacket);
  }

  // alter the fade value by the fade velocity
  newFade = view->fadeFromBlack_currentValue + view->fade_step;

  // set new fade value (temporarily)
  view->fadeFromBlack_currentValue = newFade;

  // if fade velocity is negative
  if (view->fade_step < 1)
  {
    // if we go lower than the desired fade
    if (newFade < view->fadeFromBlack_desiredResult)
    {
      // set to desired fade
      view->fadeFromBlack_currentValue = view->fadeFromBlack_desiredResult;
    }
  }

  // if fade velocity is positive
  else
  {
    // if we go higher than the desired fade value
    if (view->fadeFromBlack_desiredResult < newFade)
    {
      // set to desired fade value
      view->fadeFromBlack_currentValue = view->fadeFromBlack_desiredResult;
    }
  }
}