#include <common.h>

void DECOMP_RobotcarWeapons_Init(void)
{
  int hub;
  int lev = sdata->gGT->levelID;

  // get hubID of level
  hub = data.metaDataLEV[lev].hubID;

  // If Level ID == 13
  // If Level ID is Oxide Station
  if (lev == 0xd) {
    hub = 0;
  }

  if (hub != (unsigned int)-1)
  {
	// set pointer to boss weapon meta
    *(unsigned int*)0x8008d8e8 = data.bossWeaponMetaPtr[hub];
  }
  return;
}