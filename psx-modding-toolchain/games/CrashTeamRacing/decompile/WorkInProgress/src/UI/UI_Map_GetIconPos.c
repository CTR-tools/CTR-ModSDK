#include <common.h>

void DECOMP_UI_Map_GetIconDimensions(int *ptrMap,int *posX,int *posY)

{
  short sVar1;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  iVar4 = ptrMap[7] - 0x10;
  iVar2 = *ptrMap - ptrMap[2];
  sVar1 = ptrMap[8];
  iVar3 = ptrMap[1] - ptrMap[3];
  if (sVar1 == 0) {
    if (iVar2 == 0) {
      trap(0x1c00);
    }
    if ((iVar2 == -1) && (*posX * ptrMap[4] == -0x80000000)) {
      trap(0x1800);
    }
    iVar1 = *posY * ptrMap[5] * 2;
    if (iVar3 == 0) {
      trap(0x1c00);
    }
    if ((iVar3 == -1) && (iVar1 == -0x80000000)) {
      trap(0x1800);
    }
    iVar2 = ptrMap[6] + (*posX * ptrMap[4]) / iVar2;
    iVar4 += iVar1 / iVar3;
  }
  else {
    if (sVar1 == 1) {
      iVar1 = *posX * ptrMap[5] * 2;
      if (iVar2 == 0) {
        trap(0x1c00);
      }
      if ((iVar2 == -1) && (iVar1 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar3 == 0) {
        trap(0x1c00);
      }
      if ((iVar3 == -1) && (*posY * ptrMap[4] == -0x80000000)) {
        trap(0x1800);
      }
      iVar4 += iVar1 / iVar2;
      iVar2 = ptrMap[6] - (*posY * ptrMap[4]) / iVar3;
    }
    else {
      if (sVar1 == 2) {
        if (iVar2 == 0) {
          trap(0x1c00);
        }
        if ((iVar2 == -1) && (*posX * ptrMap[4] == -0x80000000)) {
          trap(0x1800);
        }
        iVar1 = *posY * ptrMap[5] * 2;
        if (iVar3 == 0) {
          trap(0x1c00);
        }
        if ((iVar3 == -1) && (iVar1 == -0x80000000)) {
          trap(0x1800);
        }
        iVar2 = ptrMap[6] - (*posX * ptrMap[4]) / iVar2;
        iVar4 -= iVar1 / iVar3;
      }
      else {
        iVar1 = *posX * ptrMap[5] * 2;
        if (iVar2 == 0) {
          trap(0x1c00);
        }
        if ((iVar2 == -1) && (iVar1 == -0x80000000)) {
          trap(0x1800);
        }
        if (iVar3 == 0) {
          trap(0x1c00);
        }
        if ((iVar3 == -1) && (*posY * ptrMap[4] == -0x80000000)) {
          trap(0x1800);
        }
        iVar4 -= iVar1 / iVar2;
        iVar2 = ptrMap[6] + (*posY * ptrMap[4]) / iVar3;
      }
    }
  }

  if (sdata->gGT->numPlyrCurrGame == 3) {
    iVar2 -= 0x3c;
    iVar4 += 10;
  }
  *posX = iVar2;
  *posY = iVar4;
  return;
}