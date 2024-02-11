#include <common.h>

int DECOMP_Player_GetBaseSpeed(struct Driver* driver)
{
  int netSpeed;
  int statAdditional;
  int speedAdditional;
  int netSpeedCap;

  // {0, 0x42e, 2, 14640, 15020, 15400, 14450}
  // {0, 0x42c, 2, 13140, 13520, 13900, 12950}
  // subtraction = 

  statAdditional = (int)driver->const_Speed_ClassStat;
  
  #if 1
  netSpeedCap = 6144;
  #else
  netSpeedCap = (int)driver->const_SacredFireSpeed * 2 - (int)driver->const_SingleTurboSpeed;
  #endif
  
  netSpeedCap -= (int)driver->fireSpeedCap;
  
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

  #if 1
  
  int netSpeedStat = 0x12bfff;
  
  #else
  
  int netSpeedStat = (((driver->const_SpeedometerScale_ClassStat - driver->const_Speed_ClassStat) * 0x1000) / 5) - 1;
  
  #endif
  
  speedAdditional = (netWumpaFruitCount * netSpeedStat) / 10 + turboMultiplier * netSpeedStat >> 12;

  if ((driver->actionsFlagSet & 0x800000) != 0) 
  {
    speedAdditional += driver->const_MaskSpeed;
  }

  if (driver->reserves != 0) 
  {
    statAdditional += (int)driver->fireSpeedCap;
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