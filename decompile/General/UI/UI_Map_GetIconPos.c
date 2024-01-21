#include <common.h>

void DECOMP_UI_Map_GetIconPos(short* ptrMap,int* posX,int* posY)

{
  short sVar1;
  int iVar2;
  int iVar4;

  int ptrMap6 = ptrMap[6];
  int ptrMap7 = ptrMap[7] - 0x10;

  #if 0
  // trap() functions were removed from original,
  // we assume dividing by zero will never happen
  #endif
  
  // rendering mode (forward, sideways, etc)
  sVar1 = ptrMap[8];
  
  if (sVar1 == 0) 
  {
    iVar2 = ptrMap6 + WIDE_34(*posX * ptrMap[4]    ) / (ptrMap[0] - ptrMap[2]);
    iVar4 = ptrMap7 + (*posY * ptrMap[5] * 2) / (ptrMap[1] - ptrMap[3]);
  }
  
  else if (sVar1 == 1) 
  {
	iVar4 = ptrMap7 + (*posX * ptrMap[5] * 2) / (ptrMap[0] - ptrMap[2]);
	iVar2 = ptrMap6 - WIDE_34(*posY * ptrMap[4]    ) / (ptrMap[1] - ptrMap[3]);
  }
  
  else if (sVar1 == 2) 
  {
    iVar2 = ptrMap6 - WIDE_34(*posX * ptrMap[4]    ) / (ptrMap[0] - ptrMap[2]);
    iVar4 = ptrMap7 - (*posY * ptrMap[5] * 2) / (ptrMap[1] - ptrMap[3]);
  }
  
  else 
  {
    iVar4 = ptrMap7 - (*posX * ptrMap[5] * 2) / (ptrMap[0] - ptrMap[2]);
    iVar2 = ptrMap6 + WIDE_34(*posY * ptrMap[4]    ) / (ptrMap[1] - ptrMap[3]);
  }

  if (sdata->gGT->numPlyrCurrGame == 3) 
  {
    iVar2 -= 0x3c;
    iVar4 += 10;
  }
  
  #ifdef USE_16BY9
  if((sdata->gGT->gameMode1 & MAIN_MENU) == 0)
  	iVar2 += 4;
  #endif
  
  *posX = iVar2;
  *posY = iVar4;
  return;
}

// 436