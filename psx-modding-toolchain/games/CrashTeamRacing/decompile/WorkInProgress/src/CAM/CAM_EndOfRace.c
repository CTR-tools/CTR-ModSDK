#include <common.h>

void CAM_EndOfRace_Battle(struct CameraDC* cDC, struct Driver* d);

void CAM_EndOfRace(struct CameraDC* cDC, struct Driver* d)
{
  // If not in Battle Mode and number of restart points is greater than 1 and number of players is less than 3
  if ((sdata->gGT->flags & 0x20) == 0) &&
      (1 < sdata->gGT->level1->ptrSpawnType1) &&
      (sdata->gGT->numPlyrCurrGame < 3)
  {
    // Activate end-of-race cDC flag in CameraDC struct
    cDC->flags |= 0x20;
  }
  else
  {
    // Call function to initialize end-of-race cDC for Battle Mode
    CAM_EndOfRace_Battle(cDC, d);
  }
  return;
}