#include <common.h>

void DECOMP_PickupBots_Init(void)
{
  int hub;
  int lev = sdata->gGT->levelID;

  // get hubID of level
  hub = data.metaDataLEV[lev].hubID;

  // If Level ID is Oxide Station
  if (lev == OXIDE_STATION) {
    hub = 0;
  }

  if (hub > -1)
  {
	// set pointer to boss weapon meta
  // sdata->bossWeaponMeta = data.bossWeaponMetaPtr[hub]
    *(unsigned int*)0x8008d8e8 = data.bossWeaponMetaPtr[hub];
  }
  return;
}