#include <common.h>

void RunEntryHook()
{
  // flip the wumpa shine manually
  // I know this sucks, whatever
  
  data.hud_1P_P1[0xC].x = 0xAA;
  data.hud_2P_P1[0xC].x = 0x38;
  data.hud_2P_P2[0xC].x = 0x38;
  data.hud_4P_P1[0xC].x = 8;
  data.hud_4P_P2[0xC].x = 0x10D4;
  data.hud_4P_P3[0xC].x = 8;
  data.hud_4P_P4[0xC].x = 0x10D4;
  
  // disable PixelLOD, cause it breaks mirrored
  *(int*)((int)DecalMP_01+0) = 0x3E00008;
  *(int*)((int)DecalMP_01+4) = 0;
  *(int*)((int)DecalMP_02+0) = 0x3E00008;
  *(int*)((int)DecalMP_02+4) = 0;
  *(int*)((int)DecalMP_03+0) = 0x3E00008;
  *(int*)((int)DecalMP_03+4) = 0;
}