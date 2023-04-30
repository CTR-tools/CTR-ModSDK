#include <common.h>

void Tawna_Init(struct GameTracker * gGT)
{
  struct Driver* driver;
  char index;
  char rank;
  char i;

  // default podium values
  gGT->podium_modelIndex_First = 0;
  gGT->podium_modelIndex_Second = 0;
  gGT->podium_modelIndex_Third = 0;

  // STATIC_TAWNA1
  gGT->podium_modelIndex_tawna = 0x8f;

  for (i = 0; i < 8; i++) {
    // pointer to player structure
    driver = gGT->drivers[i];
    // if address is not nullptr
    if (driver != NULL) {
      // 0 = 1st place, 1 = 2nd place, 2 = 3rd place, etc
      rank = driver->driverRank;

      // If the current driver is in 2nd place
      if (rank == 1) {
        gGT->podium_modelIndex_Second = data.characterIDs[driver->driverID] + 0x7e;
      } else if (rank == 0) {
        // first place
        index = data.characterIDs[driver->driverID];
        gGT->podium_modelIndex_First = index + 0x7e;
        switch (index) {
        case 0:
          // STATIC_TAWNA2
          gGT->podium_modelIndex_tawna = 0x90;
          break;
        case 0x7f:
          // STATIC_TAWNA3
          gGT->podium_modelIndex_tawna = 0x92;
          break;
        case 0x7d:
          // STATIC_TAWNA4
          gGT->podium_modelIndex_tawna = 0x91;
        }
      } else if (rank == 2) {
        // third place
        gGT->podium_modelIndex_Third = data.characterIDs[driver->driverID] + 0x7e;
      }
    }
  }
}
