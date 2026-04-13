#include <common.h>

// byte budget 580/632
void DECOMP_UI_TrackerBG(
	struct Icon *targetIcon, short centerX, short centerY, 
	struct PrimMem *primMem, u_long *ot,
	short angleX, short angleY, int color)
{
  short rightX;
  short bottomY;
  short offsY;
  short tmpX;
  short tmpY;
  POLY_FT4 *p;
  int offsX;
  int quadIndex;
  short topY;
  short leftX;

  // wumpaShineTheta (given to sine)
  sdata->wumpaShineTheta += FPS_HALF(0x100);

  offsX = ((targetIcon->texLayout.u1 - targetIcon->texLayout.u0) * angleX) >> 0xc;
  offsY = ((targetIcon->texLayout.v2 - targetIcon->texLayout.v0) * angleY) >> 0xc;

  rightX = centerX + offsX;
  angleX >>= 0xc;
  leftX = rightX - angleX;

  bottomY = centerY + offsY;
  angleY >>= 0xc;
  topY = bottomY - angleY;
  
  int altX0 = (centerX + (offsX * 2)) - angleX;
  int altY0 = (centerY + (offsY * 2)) - angleY;

  // loop 4 times
  for (quadIndex = 0; quadIndex < 4; quadIndex++)
  {
    p = primMem->curr;
	primMem->curr = (p+1);
	
    *(int*)&p->r0 = *(int*)&color;
    *(int*)&p->u0 = *(int*)&targetIcon->texLayout.u0;
    *(int*)&p->u1 = *(int*)&targetIcon->texLayout.u1;
    *(short*)&p->u2 = *(short*)&targetIcon->texLayout.u2;
    *(short*)&p->u3 = *(short*)&targetIcon->texLayout.u3;

	setPolyFT4(p);

    p->tpage = (p->tpage & 0xff9f);
    p->code |= 2;

	// compiler optimization will remove this,
	// if not using widescreen hacks
	int len = 0;
	
	#ifdef USE_16BY9
	// widescreen, need to scale X by 75%,
	// so subtract 12% from left and 12% from right
	len = (offsX * 125) / 1000;
	#endif

	// quadIndex(0)
	p->x0 = centerX + len;
	p->x1 = rightX;
	p->y0 = centerY;
	p->y2 = bottomY;
	
    switch (quadIndex)
    {	
    case 1:
      p->x0 = altX0 - len;
      p->x1 = leftX;
	  break;

    case 2:
      p->y0 = altY0;
      p->y2 = topY;
	  break;

    case 3:
      p->x0 = altX0 - len;
      p->y0 = altY0;

      p->x1 = leftX;
      p->y2 = topY;
    }
	
	p->x2 = p->x0;
	p->y1 = p->y0;
	
	p->x3 = p->x1;
	p->y3 = p->y2;
	
    AddPrim(ot, p);
  }
  return;
}
