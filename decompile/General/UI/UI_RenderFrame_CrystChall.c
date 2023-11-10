#include <common.h>

void DECOMP_UI_DrawNumRelic(short, short);
void DECOMP_UI_DrawNumKey(short, short);
void DECOMP_UI_DrawNumTrophy(short, short);
void DECOMP_UI_DrawNumCrystal(short, short, struct Driver*);
void DECOMP_UI_DrawSpeedNeedle(short, short, struct Driver*);
void DECOMP_UI_DrawSpeedBG(short, short, struct Driver*);
void DECOMP_UI_JumpMeter_Update(struct Driver*);
void DECOMP_UI_JumpMeter_Draw(short, short, struct Driver*);
void DECOMP_UI_DrawSlideMeter(short, short, struct Driver*);

// 692 by default, budget 768

void DECOMP_UI_RenderFrame_CrystChall(void)
{
  struct GameTracker* gGT = sdata->gGT;
  struct Driver* player;
  struct UiElement2D *hudStructPtr;
  int iVar5;
  short local_18[2];

  player = gGT->drivers[0];
  hudStructPtr = data.hudStructPtr[0];

  // If game is not paused
  if ((gGT->gameMode1 & PAUSE_ALL) == 0) {
    //execute Jump meter and landing boost processes
    DECOMP_UI_JumpMeter_Update(player);
  }

  DECOMP_UI_DrawSpeedNeedle(hudStructPtr[0x12].x,hudStructPtr[0x12].y,player);

  DECOMP_UI_JumpMeter_Draw(hudStructPtr[0xc].x,hudStructPtr[0xc].y,player);

  DECOMP_UI_DrawSlideMeter(hudStructPtr[0x10].x,hudStructPtr[0x10].y,player);

  DECOMP_UI_DrawSpeedBG(hudStructPtr[0x12].x,hudStructPtr[0x12].y,player);

  DECOMP_UI_DrawNumCrystal(hudStructPtr[0x22].x + 0x10, hudStructPtr[0x22].y - 0x10,player);

  // Draw weapon and number of wumpa fruit in HUD
  UI_Weapon_DrawSelf(hudStructPtr[0].x,hudStructPtr[0].y,hudStructPtr[1].y,player);

  // TIME
  DecalFont_DrawLine(sdata->lngStrings[0x12],0x14,8,FONT_SMALL,ORANGE);

  // "TIME" and the actual time are printed at the same
  // X-coordinate, so we know 0x14 is the X, which only
  // leaves the next parameter as the only possible value for
  // the Y-coordinate.

  // draw countdown clock
  UI_DrawLimitClock(0x14,0x10,1);


  // If game is paused
  if ((gGT->gameMode1 & PAUSE_ALL) != 0) {
    return;
  }

  if ((player->PickupWumpaHUD.numCollected) == 0)
  {
	// make invisible
    sdata->ptrHudCrystal->flags |= 0x80;
    goto LAB_800545e8;
  }
  local_18[0] = hudStructPtr[0x22].x;
  local_18[1] = hudStructPtr[0x22].y;

  // make visible
  sdata->ptrHudCrystal->flags &= 0xffffff7f;

  // if cooldown between grabbing items is over,
  // which also means item has moved to the hud icon
  if ((player->PickupWumpaHUD.cooldown) == 0) {

	// add one to your crystal count
    player->numCrystals++;

	// deduct from number of queued items to pick up
    player->PickupWumpaHUD.numCollected--;

	// if you have enough crystals to win the race
    if (gGT->numCrystalsInLEV <= player->numCrystals)
	{
      player->funcPtrs[0] = VehPtr_Freeze_Init;

      //turn on 26th bit of Actions Flag set (means racer finished the race)
      player->actionsFlagSet |= 0x2000000;

      MainGameEnd_Initialize();
    }

    OtherFX_Play(0x42,1);

    if (player->PickupWumpaHUD.numCollected != 0)
		player->PickupWumpaHUD.cooldown = 5;
  }

  // if cooldown is not done
  else
  {
	// interpolate position over course of 5 frames
    UI_Lerp2D_HUD(
		&local_18[0],
		(int)player->PickupWumpaHUD.startX,
		(int)player->PickupWumpaHUD.startY,
		(int)hudStructPtr[0x22].x,
		(int)hudStructPtr[0x22].y,

		// cooldown (0-5)
		player->PickupWumpaHUD.cooldown,

		// 5 frames total
		5);

	// reduce cooldown between getting each wumpa (or crystal)
	player->PickupWumpaHUD.cooldown--;
  }
  
  struct Instance* hudCrystal = sdata->ptrHudCrystal;
  
  // posX
  iVar5 = (local_18[0] + -0x100) * hudStructPtr[0x23].x;
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0xff;
  }
  hudCrystal->matrix.t[0] = iVar5 >> 8;
  
  // posY
  iVar5 = (local_18[1] + -0x6c) * hudStructPtr[0x23].x;
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0xff;
  }
  hudCrystal->matrix.t[1] = iVar5 >> 8;
  
  // posZ
  hudCrystal->matrix.t[2] = hudStructPtr[0x23].x;

LAB_800545e8:

  // quit if game is paused, or item is 
  // rolling, or not drawing roulette
  if((gGT->gameMode1 & PAUSE_ALL) != 0) return;
  if(player->itemRollTimer != 0) return;
  if((gGT->gameMode1 & ROLLING_ITEM) == 0) return;

  // if not paused, item stopped rolling, and 
  // weapon roulette sound is playing, then
  // stop the sound and remove flag
  OtherFX_Stop2(0x5d);
  gGT->gameMode1 &= ~(ROLLING_ITEM);
  
  return;
}