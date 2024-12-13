#include <common.h>

void DECOMP_SubmitName_RestoreName(short param_1)
{
  struct GameTracker* gGT = sdata->gGT;

  // Time Trial or Adventure
  sdata->data10_bbb[0xd] = param_1;

  // copy the last string you typed the last time you were in
  // the OSK menu, back into the menu, avoid typing a second time
  memmove(gGT->currNameEntered, gGT->prevNameEntered, 0x11);

  // "A" or "SAVE"
  short cursor = 0;
  if (gGT->currNameEntered[0] != 0)
    cursor = 1001;

  gGT->typeCursorPosition = cursor;
}