#include <common.h>

void DECOMP_MM_JumpTo_Scrapbook(void)
{
  // go to scrapbook
  sdata->ptrActiveMenu = &D230.menuScrapbook;

  D230.menuScrapbook.state &= ~(ONLY_DRAW_TITLE);

  DECOMP_MM_Scrapbook_Init();
}