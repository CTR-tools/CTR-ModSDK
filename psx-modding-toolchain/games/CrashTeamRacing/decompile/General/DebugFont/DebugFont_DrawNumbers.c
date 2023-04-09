#include <common.h>

void DECOMP_DebugFont_DrawNumbers(int index, int screenPosX, int screenPosY)
{
  unsigned short uVar1;
  unsigned int *puVar2;
  unsigned int *puVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  struct GameTracker* gGT = sdata->gGT;
  int letterX = 6;

  uVar6 = screenPosX + 7 & 0xffff;
  uVar4 = (screenPosY + 7) * 0x10000;

  // primitive memory
  puVar2 = (unsigned int*)gGT->backBuffer->primMem.curr;

  // OT memory
  puVar3 = (unsigned int*)gGT->tileView_UI.ptrOT;

  // append memory, so that future polygons draw after
  // what we are about to add in this function
  gGT->backBuffer->primMem.curr = puVar2 + 10;

  puVar2[1] = 0x2e000000;
  puVar2[2] = screenPosX & 0xffff | screenPosY << 0x10;
  puVar2[8] = uVar6 | uVar4;
  puVar2[4] = uVar6 | screenPosY << 0x10;
  puVar2[6] = screenPosX & 0xffff | uVar4;

  // each character is 7 pixels wide
  // and 7 pixels tall

  // '0' is 6th character in 2nd row,
  // Get X value of pixel
  // This is the bottom of two bytes
  uVar4 = sdata->debugFont.pixelX + letterX * 7;

  // Get Y value for top of the quad
  // bit shift to top byte
  uVar6 = (sdata->debugFont.pixelY + 7) * 0x100;

  // Get Y value for bottom of the quad
  // bit shift to top byte
  uVar5 = uVar6 + 7 * 0x100;

  // Top Left corner
  puVar2[3] = uVar4 | uVar6;

  // Top Right corner
  puVar2[5] = uVar4 + 7 | uVar6;

  // Bottom Left corner
  puVar2[7] = uVar4 | uVar5;

  // Bottom Right corner
  puVar2[9] = uVar4 + 7 | uVar5;

  // texture page
  uVar1 = sdata->debugFont.tpage;

  // color palette
  *(unsigned short *)((int)puVar2 + 0xe) = sdata->debugFont.clut;

  // optional: (I forget what this does, change color each frame?)
  //*(unsigned short *)((int)puVar2 + 0xe) = gGT->timer >> 6;

  // texture page
  *(unsigned short *)((int)puVar2 + 0x16) = uVar1;

  *puVar2 = *puVar3 | 0x9000000;
  *puVar3 = (unsigned int)puVar2 & 0xffffff;
}