#include <common.h>

// 488 / 760



void DECOMP_UI_Map_GetIconPos(struct Map* minimap, Vec2* pos)

{
  short mode;
  int addX;
  int addY;
  int worldRangeX;
  int worldRangeY;


  #if 0
  // trap() functions were removed from original,
  // we assume dividing by zero will never happen
  #endif
  
  // rendering mode (forward, sideways, etc)
  mode = minimap->mode;
  
  worldRangeX = minimap->worldEndX - minimap->worldStartX;
  worldRangeY = minimap->worldEndY - minimap->worldStartY;
  
  if (mode == 0) 
  {
	// 0 degrees
    addX =  (pos->x * minimap->iconSizeX    ) / worldRangeX;
    addY =  (pos->y * minimap->iconSizeY * 2) / worldRangeY;
  }
  
  else if (mode == 1) 
  {
	// 90 degrees
	addX = -(pos->y * minimap->iconSizeX    ) / worldRangeY;
	addY =  (pos->x * minimap->iconSizeY * 2) / worldRangeX;
  }
  
  else if (mode == 2) 
  {
	// 180 degrees
    addX = -(pos->x * minimap->iconSizeX    ) / worldRangeX;
    addY = -(pos->y * minimap->iconSizeY * 2) / worldRangeY;
  }
  
  else 
  {
	// 270 degrees
    addX =  (pos->y * minimap->iconSizeX    ) / worldRangeY;
    addY = -(pos->x * minimap->iconSizeY * 2) / worldRangeX;
  }

  #ifdef USE_16BY9
  addX = WIDE_34(addX);
  
  if (sdata->gGT->numPlyrCurrGame == 1)
  {
	addX += ((462 - minimap->iconStartX) / 4) + 5;
  }
  #endif

  if (sdata->gGT->numPlyrCurrGame == 3) 
  {
    addX -= 60;
    addY += 10;
  }
  
  pos->x = minimap->iconStartX + addX;
  pos->y = minimap->iconStartY + addY - 0x10;
  return;
}