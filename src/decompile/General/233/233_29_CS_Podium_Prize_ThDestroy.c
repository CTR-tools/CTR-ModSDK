#include <common.h>

void DECOMP_CS_Podium_Prize_ThDestroy(struct Thread* t)
{
  // remove bits
  sdata->gGT->gameMode2 &= ~(INC_RELIC | INC_KEY | INC_TROPHY);
  PROC_DestroyInstance(t);
}