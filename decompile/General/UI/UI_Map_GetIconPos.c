#include <common.h>

// 488 / 760

struct Map
{
	short worldEndX;
	short worldEndY;
	short worldStartX;
	short worldStartY;
	
	short iconSizeX;
	short iconSizeY;
	short iconStartX;
	short iconStartY;
	
	short mode;
};

void DECOMP_UI_Map_GetIconPos(short* m,int* posX,int* posY)

{
  short mode;
  int addX;
  int addY;
  int worldRangeX;
  int worldRangeY;

  struct Map* map = &m[0];

  #if 0
  // trap() functions were removed from original,
  // we assume dividing by zero will never happen
  #endif
  
  // rendering mode (forward, sideways, etc)
  mode = map->mode;
  
  worldRangeX = map->worldEndX - map->worldStartX;
  worldRangeY = map->worldEndY - map->worldStartY;
  
  if (mode == 0) 
  {
	// 0 degrees
    addX =  (*posX * map->iconSizeX    ) / worldRangeX;
    addY =  (*posY * map->iconSizeY * 2) / worldRangeY;
  }
  
  else if (mode == 1) 
  {
	// 90 degrees
	addX = -(*posY * map->iconSizeX    ) / worldRangeY;
	addY =  (*posX * map->iconSizeY * 2) / worldRangeX;
  }
  
  else if (mode == 2) 
  {
	// 180 degrees
    addX = -(*posX * map->iconSizeX    ) / worldRangeX;
    addY = -(*posY * map->iconSizeY * 2) / worldRangeY;
  }
  
  else 
  {
	// 270 degrees
    addX =  (*posY * map->iconSizeX    ) / worldRangeY;
    addY = -(*posX * map->iconSizeY * 2) / worldRangeX;
  }

  if (sdata->gGT->numPlyrCurrGame == 3) 
  {
    addX -= 0x3c;
    addY += 10;
  }
  
  #ifdef USE_16BY9
  //int distToRight = map->iconSizeX - addX;
  //addX = map->iconSizeX - WIDE_34(distToRight);
  #endif

// See how the origin of the map changes constantly?
// The map icon has to somehow scale with respect to this
// origin, otherwise the 3D->2D IconPos will never work
#if 0
  if(*(int*)0x8000c000 == 0)
  {
	addX = 0;
	addY = 0;
  }
  
  else if(*(int*)0x8000c000 == 1)
  {
	addX = map->iconSizeX;
	addY = map->iconSizeY;
  }

  *(int*)0x8000c000 = (*(int*)0x8000c000 + 1) % 2;
#endif
  
  *posX = map->iconStartX + addX;
  *posY = map->iconStartY + addY - 0x10;
  return;
}