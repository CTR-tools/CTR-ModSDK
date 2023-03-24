#include <common.h>

void DECOMP_UI_Weapon_DrawBG(short param_1,short param_2,short param_3,struct Driver* d)
{
  int iVar1;
  int iVar2;

  // reduce frame timer until it hits zero (unused?)
  if (d->BattleHUD.juicedUpCooldown != 0) {
    d->BattleHUD.juicedUpCooldown--;
  }

  iVar2 = (int)param_3;

  // wumpaShineTheta (given to sine)
  sdata->wumpaShineTheta += 0x100;

  iVar1 = iVar2 * 0xd000 >> 0x10;
  
  UI_WeaponBG_DrawShine(
				// Weapon Roulette background (shine)
				sdata->gGT->ptrIcons[0xc4],

				(int)param_1,(int)param_2,

				// pointer to PrimMem struct
				&sdata->gGT->backBuffer->primMem,

				// pointer to OTMem 
				sdata->gGT->tileView_UI.ptrOT,

				2,iVar2,iVar1,0xff0000);

  UI_WeaponBG_DrawShine(
				// Weapon Roulette background (shine)
			  sdata->gGT->ptrIcons[0xc4],

				(int)param_1,(int)param_2,

				// pointer to PrimMem struct
				&sdata->gGT->backBuffer->primMem,

				// pointer to OTMem 
				sdata->gGT->tileView_UI.ptrOT,

				3,iVar2,iVar1,0xff0000);
  return;
}