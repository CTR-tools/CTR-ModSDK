#include <common.h>

void DECOMP_CS_Podium_Prize_ThDestroy(struct Thread* t)
{
  // remove bits
  sdata->gGT->gameMode2 &= ~(AKU_SONG|UKA_SONG|RELIC_RACE);
  THREAD_DestroyInstance(t);
}