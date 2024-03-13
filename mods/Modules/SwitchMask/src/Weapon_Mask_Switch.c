#include <common.h>

int DECOMP_VehPickupItem_MaskBoolGoodGuy(struct Driver * d)

{
  short charID;
  int goodGuy;
  charID = data.characterIDs[d->driverID];

  // if your character is...
  switch (charID) {
  // Crash
  case 0:
  // Coco
  case 3:
  // Pura
  case 6:
  // Polar
  case 7:
  // Penta
  case 13:
  // you're a good guy, get pranked by Uka instead.
    goodGuy = 0;
    break;
  // friendship ended with Uka, now Aku is my bf
  default:
    goodGuy = 1;
    break;
  }
  return goodGuy;
}