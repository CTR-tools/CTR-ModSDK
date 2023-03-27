#include <common.h>

void UI_DrawLimitClock(short, short, short);
void UI_Weapon_DrawSelf(short, short, short, struct Driver*);
void UI_DrawNumWumpa(short, short, struct Driver*);
void UI_DrawNumRelic(short, short, struct Driver*);
void UI_DrawNumKey(short, short, struct Driver*);
void UI_DrawNumTrophy(short, short, struct Driver*);
void UI_DrawNumCrystal(short, short, struct Driver*);
void UI_DrawSpeedNeedle(short, short, struct Driver*);
void UI_DrawSpeedBG(short, short, struct Driver*);
void UI_JumpMeter_Update(struct Driver*);
void UI_JumpMeter_Draw(short, short, struct Driver*);
void UI_DrawSlideMeter(short, short, struct Driver*);
void VehPtr_Freeze_Init(struct Thread*,struct Driver*);

void DECOMP_UI_RenderFrame_CrystChall(void)
{
  int cooldown;
  struct GameTracker* gGT = sdata->gGT;
  struct Driver* player;
  struct UiElement2D *hudStructPtr;
  int iVar5;
  short local_18;
  short local_16;

  player = gGT->drivers[0];
  hudStructPtr = data.hudStructPtr[0];

  // If game is not paused
  if ((gGT->gameMode1 & 0xf) == 0) {
    //execute Jump meter and landing boost processes
    UI_JumpMeter_Update(player);
  }

  UI_DrawSpeedNeedle(hudStructPtr[0x12].x,hudStructPtr[0x12].y,player);

  UI_JumpMeter_Draw(hudStructPtr[0xc].x,hudStructPtr[0xc].y,player);

  UI_DrawSlideMeter(hudStructPtr[0x10].x,hudStructPtr[0x10].y,player);

  UI_DrawSpeedBG(hudStructPtr[0x12].x,hudStructPtr[0x12].y,player);

  UI_DrawNumCrystal(hudStructPtr[0x22].x + 0x10, hudStructPtr[0x22].y - 0x10,player);

  // Draw weapon and number of wumpa fruit in HUD
  UI_Weapon_DrawSelf(hudStructPtr[0].x,hudStructPtr[0].y,hudStructPtr[1].y,player);

  // TIME
  DecalFont_DrawLine((sdata->lngStrings[0x48]),0x14,8,2,0);

  // "TIME" and the actual time are printed at the same
  // X-coordinate, so we know 0x14 is the X, which only
  // leaves the next parameter as the only possible value for
  // the Y-coordinate.

  // draw countdown clock
  UI_DrawLimitClock(0x14,0x10,1);


  // If game is paused
  if ((gGT->gameMode1 & 0xf) != 0) {
    return;
  }

  if ((player->PickupWumpaHUD.numCollected) == 0)
  {
	// make invisible
    sdata->ptrHudCrystal->flags |= 0x80;
    goto LAB_800545e8;
  }
  local_18 = hudStructPtr[0x22].x;
  local_16 = hudStructPtr[0x22].y;

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
	  // VehPtr_Freeze_Init
      player->funcPtrs[0] = &VehPtr_Freeze_Init;

      //turn on 26th bit of Actions Flag set (means racer finished the race)
      (player->actionsFlagSet) |= 0x2000000;

	  // MainGameEnd_Initialize
      MainGameEnd_Initialize(0x42);
    }

	// OtherFX_Play
    OtherFX_Play(0x42,1);

	// 5 frame cooldown
    cooldown = 5;

    if ((player->PickupWumpaHUD.numCollected) != 0) goto LAB_8005456c;
  }

  // if cooldown is not done
  else
  {
	// interpolate position over course of 5 frames
    UI_Lerp2D_HUD(
					&local_18,
					&player->PickupWumpaHUD.startX,
					&player->PickupWumpaHUD.startY,
					hudStructPtr[0x22].x,
					hudStructPtr[0x22].y,

					// cooldown (0-5)
				  player->PickupWumpaHUD.cooldown,

					// 5 frames total
					5);

	// reduce cooldown between getting each wumpa (or crystal)
	cooldown = player->PickupWumpaHUD.cooldown + -1;

LAB_8005456c:

	// set new cooldown
    player->PickupWumpaHUD.cooldown = cooldown;
  }
  struct Instance* hudCrystal = sdata->ptrHudCrystal;
  iVar5 = (local_18 + -0x100) * hudStructPtr[0x23].x;
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0xff;
  }
  sdata->ptrHudCrystal->matrix.m[2][1] = iVar5 >> 8;
  iVar5 = (local_16 + -0x6c) * hudStructPtr[0x23].x;
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0xff;
  }
  hudCrystal->matrix.t[0] = iVar5 >> 8;
  hudCrystal->matrix.t[1] = hudStructPtr[0x23].x;
LAB_800545e8:
  if (
		(
			// If game is not paused
			((gGT->gameMode1 & 0xf) == 0) &&

			// item roll is done
			(player->itemRollTimer == 0)
		) &&

		// If you're drawing Weapon Roulette (randomizing)
		((gGT->gameMode1 & 0x800000) != 0)
	  )
  {
	// OtherFX_Stop2
	// stop weapon shuffle sound
    OtherFX_Stop2(0x5d);

	// Disable the randomizing effect in the HUD
    gGT->gameMode1 &= 0xff7fffff;
  }
  return;
}