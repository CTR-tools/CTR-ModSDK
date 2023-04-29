
// called "DebugFont" for it's simplicity,
// and appearance in early screenshots
// saying "Copyright Naughty Dog E3 1999"

// DebugFont_Init
void FUN_800222e0(int param_1)
{
  int iVar1;

  // param_1 is 8008d2ac

  // pointer to debug text
  iVar1 = *(int *)(param_1 + 0x1ff4);

  // if it is valid
  if (iVar1 != 0)
  {
	// pixelX of first character
    DAT_8008d72c = (uint)*(byte *)(iVar1 + 0x14);

	// color palette
    DAT_8008d734 = *(undefined2 *)(iVar1 + 0x16);

	// pixelY of first character
    DAT_8008d730 = (uint)*(byte *)(iVar1 + 0x15);

	// texture page
    DAT_8008d736 = *(undefined2 *)(iVar1 + 0x1a);
  }
  return;
}


// DebugFont_DrawNumbers
void FUN_80022318(int param_1,uint param_2,int param_3)

{
  undefined2 uVar1;
  uint *puVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar6 = param_2 + 7 & 0xffff;
  uVar4 = (param_3 + 7) * 0x10000;

  // backBuffer->primMem.curr
  puVar2 = *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80);

  // pointer to OT memory
  puVar3 = *(uint **)(PTR_DAT_8008d2ac + 0x147c);

  // backBuffer->primMem.curr
  *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) = puVar2 + 10;

  puVar2[1] = 0x2e000000;
  puVar2[2] = param_2 & 0xffff | param_3 << 0x10;
  puVar2[8] = uVar6 | uVar4;
  puVar2[4] = uVar6 | param_3 << 0x10;
  puVar2[6] = param_2 & 0xffff | uVar4;

  // each character is 7 pixels wide
  // and 7 pixels tall

  // '0' is 6th character in 2nd row,
  // Get X value of pixel
  // This is the bottom of two bytes
  uVar4 = DAT_8008d72c + (param_1 + 5) * 7;

  // Get Y value for top of the quad
  // bit shift to top byte
  uVar6 = (DAT_8008d730 + 7) * 0x100;

  // Get Y value for bottom of the quad
  // bit shift to top byte
  uVar5 = (DAT_8008d730 + 0xe) * 0x100;

  // Top Left corner
  puVar2[3] = uVar4 | uVar6;

  // Top Right corner
  puVar2[5] = uVar4 + 7 | uVar6;

  // Bottom Left corner
  puVar2[7] = uVar4 | uVar5;

  // Bottom Right corner
  puVar2[9] = uVar4 + 7 | uVar5;

  // texture page
  uVar1 = DAT_8008d736;

  // color palette
  *(undefined2 *)((int)puVar2 + 0xe) = DAT_8008d734;

  // texture page
  *(undefined2 *)((int)puVar2 + 0x16) = uVar1;

  *puVar2 = *puVar3 | 0x9000000;
  *puVar3 = (uint)puVar2 & 0xffffff;
  return;
}
