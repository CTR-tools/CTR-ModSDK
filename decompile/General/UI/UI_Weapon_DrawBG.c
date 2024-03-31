#include <common.h>

void DECOMP_UI_Weapon_DrawBG(short param_1,short param_2,short param_3,struct Driver* d)
{
  int iVar1;
  int iVar2;
  int i;
  struct GameTracker* gGT = sdata->gGT;

  // reduce frame timer until it hits zero (unused?)
  if (d->BattleHUD.juicedUpCooldown != 0) {
    d->BattleHUD.juicedUpCooldown--;
  }

  iVar2 = (int)param_3;

  // wumpaShineTheta (given to sine)
  sdata->wumpaShineTheta += FPS_HALF(0x100);

  iVar1 = iVar2 * 0xd000 >> 0x10;

  for(i = 0; i < 2; i++)
  {
	DECOMP_UI_WeaponBG_DrawShine(
			
		// Weapon Roulette background (shine)
		gGT->ptrIcons[0xc4/4],
		
		(int)param_1,(int)param_2,
		
		// pointer to PrimMem struct
		&gGT->backBuffer->primMem,
		
		// pointer to OTMem 
		gGT->pushBuffer[d->driverID].ptrOT,
		
		2+i,iVar2,iVar1,0xff0000);
  }

  return;
}