
#include <common.h>

// Only used for drawing player comments
void DECOMP_RECTMENU_DrawQuip(char* comment,short posX,int posY,u_int sizeX,short fontType,
                 int flags,short param_7)
{
  int lineWidth;
  short posX;
  u_int posY;
  u_int sizeX;
  u_int sizeY;

  if ((sizeX & 0xffff) == 0)
  {
    lineWidth = DecalFont_GetLineWidth(comment,(int)fontType);
    sizeX = lineWidth + 0xc;
  }

  // if text is not centered
  if ((flags & 0x8000U) != 0)
  {
	// posX with text un-centered
    posX = posX - sizeX>>1;
  }

  sizeY = (u_int)data.PlayerCommentBoxParams[0][fontType];

  // Draw string
  DecalFont_DrawLine(comment,
                posX,(data.PlayerCommentBoxParams[1][lineWidth] + posY),
                fontType, flags);

  RECT r;
  r.x = posX;
  r.y = posY;
  r.w = sizeX;
  r.h = sizeY;
  RECTMENU_DrawInnerRect(&r,(int)param_7, sdata->gGT->backBuffer->otMem.startPlusFour);
  return;
}