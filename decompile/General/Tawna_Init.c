#include <common.h>

void DECOMP_Tawna_Init(struct GameTracker *gGT)
{
  struct Driver *driver;
  char i;
  char rank;
  char index;

  // Default podium values
  gGT->podium_modelIndex_First = 0;
  gGT->podium_modelIndex_Second = 0;
  gGT->podium_modelIndex_Third = 0;

  for (i = 0; i < 8; i++)
  {
    // Pointer to player structure
    driver = gGT->drivers[i];

    if (driver == NULL) continue;
    
    // 0 = 1st place, 1 = 2nd place, 2 = 3rd place, etc
    rank = driver->driverRank;
    index = data.characterIDs[driver->driverID];

	if (rank == 0)
    {
      // First place
      gGT->podium_modelIndex_First = index + 0x7e;
      
	  // Set podium_modelIndex_tawna based on char index
      switch (index)
      {
		// Crash + Coco
        case 0:
        case 3:
          // STATIC_TAWNA2 (Isabella)
          gGT->podium_modelIndex_tawna = 0x90;
          break;
        
		// Polar + Pura
		case 6:
        case 7:
          // STATIC_TAWNA3 (Liz)
          gGT->podium_modelIndex_tawna = 0x91;
          break;
		
		// Cortex + NGin
		case 1:
        case 4:
          // STATIC_TAWNA4 (Megumi)
          gGT->podium_modelIndex_tawna = 0x92;
		  break;
		
	    default:
		  // STATIC_TAWNA1 (Ami)
		  gGT->podium_modelIndex_tawna = 0x8f;
          break;
      }
	
	  continue;
    }

    if (rank == 1)
    {
      gGT->podium_modelIndex_Second = index + 0x7e;
	  continue;
	}
    
    else if (rank == 2)
    {
      gGT->podium_modelIndex_Third = index + 0x7e;
	  continue;
	}
  }
}