#include <common.h>

// Draw weapon and wumpa fruit in HUD
void DECOMP_UI_Weapon_DrawSelf(short posX,short posY,short scale,struct Driver* d)

{
  u_int currChar;
  int iconID;
  struct GameTracker* gGT;
  short posXY[0];
  
  gGT = sdata->gGT;

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
						// character ID
						currChar = data.characterIDs[d->driverID],

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
    if (((d->noItemTimer) != 0) && (((gGT->timer) & 1) == 0)) {
      return;
    }

	// If this weapon has a quantity (3 missiles)
    if (d->numHeldItems != 0)
	{
	  // Draw the number near the weapon icon to show how many
      DecalFont_DrawLine(sdata->s_spacebar,(int)posX,(int)posY,2,4);
    }
  }
  
  // if roulette shuffle
  else
  {
	iconID = 0;
	posXY[0] = posX;
	posXY[1] = posY;
	
	// If game is not paused
	if ((gGT->gameMode1 & PAUSE_ALL) == 0) {
	
		// If you're not in Battle Mode
		if ((gGT->gameMode1 & BATTLE_MODE) == 0) 
		{
			// random item
			iconID = rand();
			iconID = iconID + ((iconID / 6 + (iconID >> 0x1f) >> 1) - (iconID >> 0x1f)) * -0xc;
			
			// replace spring with turbo
			if (iconID == 5) goto LAB_800508ec;
		}
		
		// if Battle Mode
		else 
		{
			// random item
			iconID = rand();
			iconID = iconID % 0xe;
			
			// replace spring
			if (iconID == 5) {
		LAB_800508ec:
				iconID = 0;
			}
			
			// replace clock
			else if (iconID == 8) {
				iconID = 1;
			}
			
			// replace warpball
			else if (iconID == 9) {
				iconID = 3;
			}
		}
		
		// only change icon once per 2 frames,
		// take advantage of unused padding
		#ifdef USE_60FPS
		if(gGT->timer & 1)
		{
			// backup
			d->funcPtrs_compilerpadding = iconID;
		}
		else
		{
			// restore
			iconID = d->funcPtrs_compilerpadding;
		}
		#endif
	}
	
	// if timer is not finished
	if (d->PickupTimeboxHUD.cooldown != 0)
	{
		DECOMP_UI_Lerp2D_HUD(&posXY[0],d->PickupTimeboxHUD.startX,d->PickupTimeboxHUD.startY,
				(int)posX,(int)posY,d->PickupTimeboxHUD.cooldown,FPS_DOUBLE(5));
	
		// subtract one from timer
		d->PickupTimeboxHUD.cooldown--;
	}
	
	iconID = (iconID + 5);
	posX = posXY[0];
	posY = posXY[1];
  }

  DecalHUD_DrawWeapon(
				// pointer to icon, from array of icon pointers
				gGT->ptrIcons[iconID],

				(int)posX,(int)posY,

				// PrimMem
				&gGT->backBuffer->primMem,

				// OTMem
				gGT->tileView_UI.ptrOT,

				TRANS_50_DECAL,(int)scale,1);
  return;
}
