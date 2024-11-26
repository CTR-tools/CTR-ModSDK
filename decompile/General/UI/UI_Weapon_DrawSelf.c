#include <common.h>

// Draw weapon and wumpa fruit in HUD
void DECOMP_UI_Weapon_DrawSelf(short posX,short posY,short scale,struct Driver* d)

{
  u_int currChar;
  int itemID;
  int iconID;
  struct GameTracker* gGT;
  short posXY[2];
  
  // beat 7360
  
  gGT = sdata->gGT;
  itemID = d->heldItemID;

  // If you do have "no weapon icon"
  if (itemID == ITEM_NONE) return;

  // If you are not shuffling through weapon roulette
  if (itemID != ITEM_ROULLETE)
  {
    iconID = itemID + 5;

	// If your weapon is a mask
	if (itemID == ITEM_MASK)
	{
#ifndef PENTA_MASK_FIX
		currChar = data.characterIDs[d->driverID];
		
		// Not Crash, Coco, Polar, Pura
		if (
		(currChar != CRASH_BANDICOOT) &&
		(currChar != COCO_BANDICOOT) &&
		(currChar != POLAR) &&
		(currChar != PURA)
		)
#else
	// Use good guy function to include Penta too
		if (DECOMP_VehPickupItem_MaskBoolGoodGuy(d) == 0)
#endif
		{
		// This is a bad guy, change icon to Uka
		iconID = 0x32;
		}
	}

    if (
		(d->numWumpas >= 10) &&

		// TNT, Potion, Shield
		(
			((unsigned int)(itemID - ITEM_TNT) < 2) || 
			(itemID == ITEM_SHIELD)
		)
	   )
	{
      iconID = itemID + 0x11;
    }
	
	// make weapon flicker
    if (
			((d->noItemTimer) != 0) && 
			((gGT->timer & FPS_DOUBLE(1)) == 0)
		) 
	{
      return;
    }

	// If this weapon has a quantity (3 missiles)
    if (d->numHeldItems != 0)
	{
	  // Get the ascii character to represent the quantity
	  // of weapon that you have (3 missiles)
	  sdata->s_spacebar[0] = d->numHeldItems + '0';
		
	  // Draw the number near the weapon icon to show how many
      DECOMP_DecalFont_DrawLine(sdata->s_spacebar,posX,posY,2,4);
    }
  }
  
  // if roulette shuffle
  else
  {
	itemID = 0;
	posXY[0] = posX;
	posXY[1] = posY;
	
	// If game is not paused
	if ((gGT->gameMode1 & PAUSE_ALL) == 0) 
	{
		// random item
		itemID = rand();
	
		// If you're not in Battle Mode
		if ((gGT->gameMode1 & BATTLE_MODE) == 0) 
		{
			itemID = itemID % ITEM_INVISIBILITY;
			
			// replace spring with turbo
			if (itemID == ITEM_SPRING) goto REPLACE_SPRING;
		}
		
		// if Battle Mode
		else 
		{
			itemID = itemID % 14;
			
			// replace spring
			if (itemID == ITEM_SPRING) {
		REPLACE_SPRING:
				itemID = ITEM_TURBO;
			}
			
			// replace clock
			else if (itemID == ITEM_CLOCK) {
				itemID = ITEM_1X_BOMB;
			}
			
			// replace warpball
			else if (itemID == ITEM_WARPBALL) {
				itemID = ITEM_TNT;
			}
		}
		
		// only change icon once per 2 frames,
		// take advantage of unused padding
		#ifdef USE_60FPS
		if(gGT->timer & 1)
		{
			// backup
			d->funcPtrs_compilerpadding = itemID;
		}
		else
		{
			// restore
			itemID = d->funcPtrs_compilerpadding;
		}
		#endif
	}
	
	// if timer is not finished
	if (d->PickupTimeboxHUD.cooldown != 0)
	{
		DECOMP_UI_Lerp2D_HUD(&posXY[0],d->PickupTimeboxHUD.startX,d->PickupTimeboxHUD.startY,
				posX,posY,d->PickupTimeboxHUD.cooldown,FPS_DOUBLE(5));
	
		// subtract one from timer
		d->PickupTimeboxHUD.cooldown--;
	}
	
	iconID = itemID + 5;
	
	posX = posXY[0];
	posY = posXY[1];
  }

  DECOMP_DecalHUD_DrawWeapon(
		// pointer to icon, from array of icon pointers
		gGT->ptrIcons[iconID],
	
		posX,posY,
	
		// PrimMem
		&gGT->backBuffer->primMem,
	
		// OTMem
		gGT->pushBuffer_UI.ptrOT,
	
		TRANS_50_DECAL,scale,1);
		
  return;
}
