#include <common.h>

struct MenuBox * DECOMP_CS_Garage_GetMenuBox(void)
{
  // this "MenuBox" is what displays the driver stats,
  // driver name, and arrows, before selecting the driver
  return 0x800b8598;
}

void DECOMP_CS_Garage_Init(void)
{
  // go to 3D character selection
  sdata->ptrActiveMenuBox = 0x800b8598;

  *(int*)0x800b85a0 &= 0xfffffffb;

  // 0 = just entered garage
  CS_Garage_ZoomOut(0);
}