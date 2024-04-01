#include <common.h>

static char warppadColor[8] =
{
	// Locked: Gray
	[0] = 0x17,
	
	// Trophy: set later
	[1] = 0,
	
	// Beat Everything: Red
	[2] = 3,
	
	// token/relic: Yellow
	[3] = 0xe,
	
	// SlideCol/TurboTrack: set later
	[4] = 0,
};

void DECOMP_AH_Map_Warppads(short* ptrMap, struct Thread* warppadThread, short *param_3)
{
  struct GameTracker* gGT = sdata->gGT;
  struct Instance* warppadInst;
  char bVar1;
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
  
  MATRIX* dMat = &gGT->drivers[0]->instSelf->matrix;
  
  for (
		/**/; 
		warppadThread != NULL; 
		warppadThread = warppadThread->siblingThread
	  ) 
  {
	int index = warppadThread->modelIndex;
	warppadInst = warppadThread->inst;
	
	// Trophy: blue/white
	warppadColor[1] = 5;
	if ((gGT->timer & FPS_DOUBLE(2)) != 0)
		warppadColor[1] = 4;
	
	// SlideCol/TurboTrack
	// flash a bunch of colors (crash-pura),
	// each color should last two frames, so use timer>>1
	warppadColor[4] = ((gGT->timer >> FPS_RIGHTSHIFT(1)) & 7) + 5;
	
	color = warppadColor[index];
	
	// only for trophy
	if (index == 1) 
	{
		// get posZ in 3D, turns into posY in 2D
		posX = warppadInst->matrix.t[0];
		posY = warppadInst->matrix.t[2];
		
		D232.unkModeHubItems = 1;
	
		// Get Icon Dimensions
		DECOMP_UI_Map_GetIconPos(ptrMap,&posX,&posY);
	
		DECOMP_AH_Map_HubArrowOutter(ptrMap,(int)*param_3,posX,posY,0,0);
	
		*param_3 = *param_3 + 1;
	}
	
	DECOMP_UI_Map_DrawRawIcon(
		ptrMap, &warppadInst->matrix.t[0],
		0x31, color, 0, 0x1000);
	
	// if locked
	if(index == 0)
	{
		// skip distance check
		continue;
	}
		
	distX = warppadInst->matrix.t[0] - dMat->t[0];
	distY = warppadInst->matrix.t[1] - dMat->t[1];
	distZ = warppadInst->matrix.t[2] - dMat->t[2];
	currDistance = SquareRoot0_stub(distX * distX + distY * distY + distZ * distZ);
	
	if (minDistance > currDistance)
		minDistance = currDistance;
  }
  
#ifndef REBUILD_PS1
  // play sound from closest unlocked warppad
  if (minDistance != 0x7fffffff) 
    PlayWarppadSound(minDistance << 1);
#endif
  
  return;
}