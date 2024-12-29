#include <common.h>

int DECOMP_VehPickupItem_MaskBoolGoodGuy(struct Driver * d)

{
  short charID;

  // return (0 for uka, 1 for aku)
  int goodGuy;

  // get character ID of current player (p1, p2, p3, etc)
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
  // you're a good guy, use Aku
    goodGuy = true;
    break;
  // by default, you're evil, use Uka
  default:
    goodGuy = false;
    break;
  }
  // return whether you use Aku or Uka
  return goodGuy;
}