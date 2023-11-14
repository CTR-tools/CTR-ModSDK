#include <common.h>

void MM_JumpTo_Scrapbook(void)
{
  // go to scrapbook
  sdata->ptrActiveMenuBox = &D230.menubox_scrapbook;

  D230.menubox_scrapbook.state &= ~(ONLY_DRAW_TITLE);

  MM_Scrapbook_Init();
}