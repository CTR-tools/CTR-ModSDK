#include <common.h>

void DECOMP_TitleOSK_RestoreName(short param_1)
{
  short cursor;

  sdata->data10_bbb[0xd] = param_1;

  // copy the last string you typed the last time you were in
  // the OSK menu, back into the menu, avoid typing a second time
  memmove(sdata->gGT->currNameEntered,sdata->gGT->prevNameEntered,0x11);

  // move cursor to 'A' letter
  cursor = 0;

  // if string exists
  if (sdata->gGT->currNameEntered != 0)
  {
	// move cursor to 'save' button
    cursor = 0x3e9;
  }
  // set cursor position of OSK
  sdata->gGT->TitleOSK_CursorPosition = cursor;
}