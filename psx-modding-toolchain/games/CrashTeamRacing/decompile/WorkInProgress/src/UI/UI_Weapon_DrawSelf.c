#include <common.h>

// Draw weapon and wumpa fruit in HUD
void DECOMP_UI_Weapon_DrawSelf(short posX,short posY,short scale,struct Driver* d)

{
  u_int currChar;
  struct DB* backBuff;
  u_long otMem;
  int iconID;
  short local_20;
  short local_1e;

  // If you are not shuffling through weapon roulette
  if (d->heldItemID != 0x10)
  {
	// If you do have "no weapon icon"
    if (d->heldItemID == 0xf) {
      return;
    }

	// If you have a weapon that is ready to use

    iconID = d->heldItemID + 5;

	// Get the ascii character to represent the quantity
	// of weapon that you have (3 missiles)
    sdata->s_spacebar[0] = d->numHeldItems + '0';

	if (
			(
				(
					// If your weapon is a mask
					(d->heldItemID == 7) &&
					(
						// get character used

													// character ID
						currChar = SEXT24(data.characterIDs[d->driverID]),

						// if not Crash
						currChar != 0
					)
				) &&

				// if not Coco
				(currChar != 3)
			) &&

			(
				(
					// if not Polar
					currChar != 6 &&

					// If not Pura (7, same as mask weaponID)
					// This is some insane compiler optimization
					(currChar != d->heldItemID)
				)
			)
		)
	{
	  // This is a bad guy, change icon to Uka
      iconID = 0x32;
    }

	// if 9 < amount of wumpa fruit
	// if you have 10 wumpa fruit
    if ((9 < d->numWumpas) &&

		// If your weapon is less than, or equal to, 6
       ((d->heldItemID - 3 < 2 || (d->heldItemID == 6))))
	{
      iconID = d->heldItemID + 0x11;
    }
    if (((d->noItemTimer) != 0) && (((sdata->gGT->timer) & 1) == 0)) {
      return;
    }

	// If this weapon has a quantity (3 missiles)
    if (d->numHeldItems != 0)
	{
	  // Draw the number near the weapon icon to show how many
      DecalFont_DrawLine(sdata->s_spacebar,(int)posX,(int)posY,2,4);
    }

	// pointer to back buffer
    backBuff = sdata->gGT->backBuffer;

	// pointer to OT memory
    otMem = &sdata->gGT->tileView_UI.ptrOT;

    iconID = iconID << 2;
    goto LAB_80050abc;
  }
  iconID = 0;
  local_20 = posX;
  local_1e = posY;

  // If game is not paused
  if ((sdata->gGT->gameMode1 & 0xf) == 0) {

	// If you're not in Battle Mode
    if ((sdata->gGT->gameMode1 & 0x20) == 0) {
      iconID = rand();
      iconID = iconID + ((iconID / 6 + (iconID >> 0x1f) >> 1) - (iconID >> 0x1f)) * -0xc;
      if (iconID == 5) goto LAB_800508ec;
    }
    else {
      iconID = rand();
      iconID = iconID % 0xe;
      if (iconID == 5) {
LAB_800508ec:
        iconID = 0;
      }
      else {
        if (iconID == 8) {
          iconID = 1;
        }
        else {
          if (iconID == 9) {
            iconID = 3;
          }
        }
      }
    }
  }

  // if timer is not finished
  if (d->PickupTimeboxHUD.cooldown != 0)
  {
    UI_Lerp2d_HUD(&local_20,d->PickupTimeboxHUD.startX,d->PickupTimeboxHUD.startY,
                 (int)posX,(int)posY,d->PickupTimeboxHUD.cooldown,5);

	// subtract one from timer
    d->PickupTimeboxHUD.cooldown--;
  }

  // pointer to back buffer
  backBuff = sdata->gGT->backBuffer;

  // pointer to OT memory
  otMem = sdata->gGT->tileView_UI.ptrOT;

  iconID = (iconID + 5) * 4;
  posX = local_20;
  posY = local_1e;
LAB_80050abc:

  DecalHUD_DrawWeapon(
				// pointer to icon, from array of icon pointers
				sdata->gGT->ptrIcons[iconID],

				(int)posX,(int)posY,

				// PrimMem
				&backBuff->primMem,

				// OTMem
				otMem,

				1,(int)scale,1);
  return;
}
