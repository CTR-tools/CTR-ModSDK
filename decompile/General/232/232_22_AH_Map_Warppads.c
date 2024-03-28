#include <common.h>

void DECOMP_AH_Map_Warppads(short* ptrMap, struct Thread* warppadThread, short *param_3)
{
  struct GameTracker* gGT = sdata->gGT;
  struct Instance* warppadInst;
  struct Instance* closestInst;
  char bVar1;
  char bVar2;
  int distX;
  int distY;
  int distZ;
  int color;
  int currDistance;
  int minDistance;
  int posX;
  int posY;
  
  // find minDistance, set to max
  minDistance = 0x7fffffff;
  
  closestInst = 0;
  MATRIX* dMat = &sdata->gGT->drivers[0]->instSelf->matrix;
  
  for (
		/**/; 
		warppadThread != NULL; 
		warppadThread = warppadThread->siblingThread
	  ) 
  {
	bVar1 = false;
	bVar2 = false;
	warppadInst = warppadThread->inst;
	
	switch(warppadThread->modelIndex) 
	{
		// locked
		case 0:
			bVar2 = true;
			
			// gray
			color = 0x17;
			break;
		
		// open for trophy
		case 1:
		
			// blue/white
			color = 5;
			if ((gGT->timer & 2) != 0)
				color = 4;
		
			bVar1 = true;
			break;
	
		// beat everything
		case 2:
		
			// red
			color = 3;
			break;
	
		// open for token/relic
		case 3:

			// yellow
			color = 0xe;
			break;
	
		// SlideCol/TurboTrack
		case 4:
		
			// flash a bunch of colors (crash-pura)
			color = (gGT->timer >> 1 & 7) + 5;
			break;
	
		// unused
		#if 0
		default:
		
			// dont make a sound
			bVar2 = true;
			
			// black
			color = 0x15;
		#endif
	}
	
	if (bVar1) 
	{
		// get posZ in 3D, turns into posY in 2D
		posX = warppadInst->matrix.t[0];
		posY = warppadInst->matrix.t[2];
		
		D232.unkModeHubItems = 1;
	
		// Get Icon Dimensions
		DECOMP_UI_Map_GetIconPos(ptrMap,&posX,&posY);
	
		AH_Map_HubArrowOutter(ptrMap,(int)*param_3,posX,posY,0,0);
	
		*param_3 = *param_3 + 1;
	}
	
	DECOMP_UI_Map_DrawRawIcon(
		ptrMap, &warppadInst->matrix.t[0],
		0x31, color, 0, 0x1000);
	
	// if locked
	if(bVar2)
	{
		// skip distance check
		continue;
	}
	
	distX = warppadInst->matrix.t[0] - dMat->t[0];
	distY = warppadInst->matrix.t[1] - dMat->t[1];
	distZ = warppadInst->matrix.t[2] - dMat->t[2];
	currDistance = SquareRoot0_stub(distX * distX + distY * distY + distZ * distZ);
	
	if (minDistance > currDistance) 
	{ 
		minDistance = currDistance;
		closestInst = warppadInst;
	}
  } 
  
  // play sound from closest unlocked warppad
  if (closestInst != NULL) 
    PlayWarppadSound(minDistance << 1);
  
  return;
}
 