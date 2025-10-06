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

void DECOMP_AH_Map_Warppads(struct Map* ptrMap, struct Thread* warppadThread, short* type)
{
  struct GameTracker* gGT = sdata->gGT;
  struct Instance* warppadInst;
  char bVar1;
  int color;
  Vec3 distance;
  int currDistance;
  int minDistance;
  Vec2 pos;
  
  // find minDistance, set to max
  minDistance = 0x7fffffff;
  
  MATRIX* dMat = &gGT->drivers[0]->instSelf->matrix;
  
  for (
		/**/; 
		warppadThread != NULL; 
		warppadThread = warppadThread->siblingThread
	  ) 
  {
	unsigned char warppad_state = warppadThread->modelIndex;
	warppadInst = warppadThread->inst;
	
	// Trophy: blue/white
	warppadColor[1] = 5;
	if ((gGT->timer & FPS_DOUBLE(2)) != 0)
		warppadColor[1] = 4;
	
	// SlideCol/TurboTrack
	// flash a bunch of colors (crash-pura),
	// each color should last two frames, so use timer>>1
	warppadColor[4] = ((gGT->timer >> FPS_RIGHTSHIFT(1)) & 7) + 5;
	
	color = warppadColor[warppad_state];
	
	// only for trophy
	if (warppad_state == WARPPAD_TROPHY) 
	{
		// get posZ in 3D, turns into posY in 2D
		pos.x = warppadInst->matrix.t.x;
		pos.y = warppadInst->matrix.t.z;
		
		D232.unkModeHubItems = 1;
	
		// Get Icon Dimensions
		DECOMP_UI_Map_GetIconPos(ptrMap, &pos);
	
		DECOMP_AH_Map_HubArrowOutter(ptrMap,(int)*type,&pos,0,0);
	
		*type++;
	}
	
	DECOMP_UI_Map_DrawRawIcon(
		ptrMap, &warppadInst->matrix.t,
		0x31, color, 0, 0x1000);
	
	// if locked
	if(warppad_state == WARPPAD_LOCKED)
	{
		// skip distance check
		continue;
	}
	
	distance = warppadInst->matrix.t;
	distance.x -= dMat->t.x;
	distance.y -= dMat->t.y;
	distance.z -= dMat->t.z;
	
	#if (!defined(REBUILD_PS1) || defined(REBUILD_PC))
	currDistance = SquareRoot0_stub(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
	
	if (minDistance > currDistance)
		minDistance = currDistance;
	#endif
  }
  
#ifndef REBUILD_PS1
  // play sound from closest unlocked warppad
  if (minDistance != 0x7fffffff) 
    PlayWarppadSound(minDistance << 1);
#endif
  
  return;
}