#include <common.h>

void DecalMP_01();
void DecalMP_02();
void DecalMP_03();

void RunEntryHook()
{
  data.font_charPixWidth[0] = 0;
  data.font_charPixWidth[1] = 0xD;
  data.font_charPixWidth[2] = 0xA;
  data.font_charPixWidth[3] = 0xB;
  
  data.font_puncPixWidth[0] = 0;
  data.font_puncPixWidth[1] = 8;
  data.font_puncPixWidth[2] = 5;
  data.font_puncPixWidth[3] = 8;
  
  // disable PixelLOD, cause it breaks
  *(int*)((int)DecalMP_01+0) = 0x3E00008;
  *(int*)((int)DecalMP_01+4) = 0;
  *(int*)((int)DecalMP_02+0) = 0x3E00008;
  *(int*)((int)DecalMP_02+4) = 0;
  *(int*)((int)DecalMP_03+0) = 0x3E00008;
  *(int*)((int)DecalMP_03+4) = 0;
}