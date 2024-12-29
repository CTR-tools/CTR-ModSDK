#include <common.h>

void DECOMP_GAMEPAD_SetMainMode()
{
  PadSetMainMode(0,0,0);
  PadSetMainMode(1,0,0);
  PadSetMainMode(2,0,0);
  PadSetMainMode(3,0,0);
  PadSetMainMode(0x10,0,0);
  PadSetMainMode(0x11,0,0);
  PadSetMainMode(0x12,0,0);
  PadSetMainMode(0x13,0,0);
}