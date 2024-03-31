#include <common.h>

void DECOMP_PushBuffer_FadeOneWindow(struct PushBuffer* pb)
{
  typedef struct
  {
    u_int tag;
    u_int tpage;
    POLY_F4 f4;
  } multiCmdPacket;

  int fadeStrength;
  multiCmdPacket *p = NULL;

  struct DB *backBuffer = sdata->gGT->backBuffer;
  
  short currValue = pb->fadeFromBlack_currentValue;

  // if not 0x1000, which means there must be
  // some amount of fading
  if (currValue != 0x1000)
  {
    p = (POLY_F4 *)backBuffer->primMem.curr;

    setlen(p, 7);
    p->f4.tag = 0;
    p->f4.code = 0x2a;
    p->f4.x0 = 0;
    p->f4.y0 = 0;

    // if we are fading to black
    if (currValue < 0x1001)
    {
      p->tpage = 0xe1000a40;

      // get strength of fade (0 to 0x1000)
      fadeStrength = 0xfff - currValue;
    }
    else
    {
      // fade to white
      p->tpage = 0xe1000a20;

      // get strength of fade (0 to 0x1000)
      fadeStrength = currValue - 0x1000;
    }

	#ifdef REBUILD_PC
	p->tpage |= 0x400; // set dfe=1
	#endif

    // strength of fade
    fadeStrength = fadeStrength >> 4;

    p->f4.r0 = (u_char)fadeStrength;
    p->f4.g0 = (u_char)fadeStrength;
    p->f4.b0 = (u_char)fadeStrength;
    p->f4.x1 = pb->rect.w;
    p->f4.y1 = 0;
    p->f4.x2 = 0;
    p->f4.y2 = pb->rect.h;
    p->f4.x3 = pb->rect.w;
    p->f4.y3 = pb->rect.h;
    AddPrim(pb->ptrOT, p);

    // move pointer after writing polygons
    backBuffer->primMem.curr = p + 1;
  }

  // alter the fade value by the fade velocity
  currValue += FPS_HALF(pb->fade_step);

  // if fade velocity is negative
  if (pb->fade_step < 1)
  {
    // if we go lower than the desired fade
    if (currValue < pb->fadeFromBlack_desiredResult)
    {
      // set to desired fade
      currValue = pb->fadeFromBlack_desiredResult;
    }
  }

  // if fade velocity is positive
  else
  {
    // if we go higher than the desired fade value
    if (pb->fadeFromBlack_desiredResult < currValue)
    {
      // set to desired fade value
      currValue = pb->fadeFromBlack_desiredResult;
    }
  }
  
  // set new fade value
  pb->fadeFromBlack_currentValue = currValue;
}