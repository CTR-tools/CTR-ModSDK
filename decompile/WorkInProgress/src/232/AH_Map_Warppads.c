#include <common.h>

void DECOMP_AH_Map_Warppads(short* ptrMap, struct Thread* warppadThread, short *param_3)
{
  struct GameTracker* gGT = sdata->gGT;
  struct Instance* warppadInst;
  char bVar1;
  char bVar2;
  int distX;
  int distY;
  int distZ;
  int color;
  int currDistance;
  int absDistance;
  int nextInst;
  int posX;
  int posY;
  
  currDistance = 0x7fffffff; // max distance?
  if (warppadThread != NULL) return;
    for (warppadThread; warppadThread != NULL; warppadThread = warppadThread->siblingThread) 
    {
      bVar1 = false;
      warppadInst = warppadThread->inst;
	  
      bVar2 = false;
      switch(warppadThread->modelIndex) {
      case 0:
        bVar2 = true;
        color = 0x17;
        break;
      case 1:
        color = 5;
        if ((gGT->timer & 2) != 0) {
          color = 4;
        }
        bVar1 = true;
        break;
      case 2:
        color = 3;
        break;
      case 3:
        color = 0xe;
        break;
      case 4:
        color = (gGT->timer >> 1 & 7) + 5;
        break;
      default:
        bVar2 = true;
        color = 0x15;
      }
      if (bVar1) {
        posX = warppadInst->matrix.t[0];
        posY = warppadInst->matrix.t[1]; // originally + 0x4c so was it supposed to be posZ?
        *(char*)0x800b5670 = 1;
        
		// Get Icon Dimensions
		UI_Map_GetIconPos(ptrMap,&posX,&posY);
        
		AH_Map_HubArrowOutter(ptrMap,(int)*param_3,posX,posY,0,0);
        
		*param_3 = *param_3 + 1;
      }
      UI_Map_DrawRawIcon(ptrMap,warppadInst->matrix.t[0],0x31,color,0,0x1000);
      if (
			(!bVar2) &&
			(
				distX = (warppadInst->matrix.t[0]) - (gGT->drivers[0]->instSelf->matrix.t[0]),
				distY = (warppadInst->matrix.t[1]) - (gGT->drivers[0]->instSelf->matrix.t[1]),
				distZ = (warppadInst->matrix.t[2]) - (gGT->drivers[0]->instSelf->matrix.t[2]),
         
				absDistance = SquareRoot0(distX * distX + distY * distY + distZ * distZ), absDistance < currDistance
			)
		  ) 
	  { 
		// closest distance
		currDistance = distX;
		// closest instance
        nextInst = warppadInst->next;
      }
	  // next thread
      warppadThread = warppadThread->siblingThread;
    } 
  
  // if instance was found
  if (nextInst != NULL) 
  {
	// play warppad sound
    PlayWarppadSound(currDistance << 1);
  }
  return;
}
 