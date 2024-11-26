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

  case CRASH_BANDICOOT:
  case COCO_BANDICOOT:
  case PURA:
  case POLAR:
  case PENTA_PENGUIN:
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