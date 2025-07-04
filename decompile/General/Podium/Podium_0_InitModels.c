#include <common.h>

void DECOMP_Podium_InitModels(struct GameTracker *gGT)
{
  struct Driver *driver;
  char i;
  char rank;
  char index;

  // Default podium values
  gGT->podium_modelIndex_First = 0;
  gGT->podium_modelIndex_Second = 0;
  gGT->podium_modelIndex_Third = 0;
    
  unsigned char* podiumModelIndexArr =
	&gGT->podium_modelIndex_First;

  for (i = 0; i < 8; i++)
  {
    // Pointer to player structure
    driver = gGT->drivers[i];

    if (driver == NULL) continue;
    
    rank = driver->driverRank;
    
	if (rank < 3)
    {
	  index = data.characterIDs[driver->driverID];
      podiumModelIndexArr[rank] = index + STATIC_CRASHDANCE;
	  
	  if(rank != 0) continue;
	  
	  // === Rank0, first place ===
	  
	  switch (index)
	  {
	  	// Crash + Coco
	  	case 0:
	  	case 3:
	  	// (Isabella)
	  	gGT->podium_modelIndex_tawna = STATIC_TAWNA2;
	  	break;
	  	
	  	// Polar + Pura
	  	case 6:
	  	case 7:
	  	// (Liz)
	  	gGT->podium_modelIndex_tawna = STATIC_TAWNA3;
	  	break;
	  
	  	// Cortex + NGin
	  	case 1:
	  	case 4:
	  	// (Megumi)
	  	gGT->podium_modelIndex_tawna = STATIC_TAWNA4;
	  	break;
	  
	  	default:
	  	// (Ami)
	  	gGT->podium_modelIndex_tawna = STATIC_TAWNA1;
	  	break;
	  }
    }
  }
}