#include <common.h>

int DECOMP_Player_GetBaseSpeed(struct Driver* driver)
{
  int netSpeed;
  int statAdditional;
  int speedAdditional;
  int netSpeedCap;

  statAdditional = (int)driver->const_Speed_ClassStat;
  netSpeedCap = (int)driver->const_SacredFireSpeed * 2 - (int)driver->const_SingleTurboSpeed - (int)driver->fireSpeedCap;
  if (netSpeedCap < 0) {
    netSpeedCap = 0;
  }

  int netWumpaFruitCount = (int)driver->numWumpas;
  if (netWumpaFruitCount > 9) {
    netWumpaFruitCount = 9;
  }

  int turboMultiplier = (int)driver->turboConst;
  if (turboMultiplier > 5) {
    turboMultiplier = 5;
  }

  int netSpeedStat = ((driver->const_SpeedometerScale_ClassStat - statAdditional) * 0x1000) / 5 + -1;
  speedAdditional = (netWumpaFruitCount * netSpeedStat) / 10 + turboMultiplier * netSpeedStat >> 0xc;

  if ((driver->actionsFlagSet & 0x800000) != 0) {
    speedAdditional = speedAdditional + driver->const_MaskSpeed;
  }

  if (driver->reserves != 0) {
    statAdditional = statAdditional + (int)driver->fireSpeedCap;
    if (netSpeedCap < speedAdditional) {
      speedAdditional = netSpeedCap;
    }
  }

  netSpeed = statAdditional + speedAdditional - driver->const_DamagedSpeed;

  if (0x6400 < netSpeed) {
    netSpeed = 0x6400;
  }

  return netSpeed;
}