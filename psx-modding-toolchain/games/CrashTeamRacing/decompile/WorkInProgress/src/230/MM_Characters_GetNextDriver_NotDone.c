#include <common.h>

int DECOMP_MM_Characters_GetNextDriver(short dpad, char characterID)
{
  char nextDriver;
  char unlocked;
  char newDriver;

  // param_1 is the direction you hit on d-pad (up, down, left, right)
  // param_2 is driver you currently have highlighted

  // 800b5a18 is pointer to array of character icons
  // each character icon is 0xc bytes large

  // offset 4 is 4-byte array of which driver you get when you press on D-Pad
  nextDriver = *(char*)0x800b5a1c[characterID] + dpad;

  // offset 10 (0xA) determines if that driver is unlocked
  unlocked = *(u_char*)0x800b5a22[bVar1];

  // set new driver to the driver
  // you'd get when pressing Up button
  newDriver = nextDriver;

  if (
      // if desired driver is not unlocked
      (unlocked != -1) &&

      ((sdata->GameProgress.unlocks)[unlocked] >> (unlocked & 1) == 0)) {

    // set new driver to the driver you already have
    newDriver = characterID;
  }

  // return new driver
  return newDriver;
}