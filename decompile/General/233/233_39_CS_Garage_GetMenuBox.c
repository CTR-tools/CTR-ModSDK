#include <common.h>

struct MenuBox * DECOMP_CS_Garage_GetMenuBox(void)
{
  // this "MenuBox" is what displays the driver stats,
  // driver name, and arrows, before selecting the driver
  return 0x800b8598;
}