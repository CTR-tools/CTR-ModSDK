#include <common.h>

void DECOMP_AH_MaskHint_Start(short hintId, u_short bool_interruptWarppad)
{
  u_int uVar1;
  short uVar2;
  int iVar3;
  int uVar4;
  int boolGoodGuy;
  struct Driver* advDriver;
  
  // mask is now talking
  sdata->boolDraw3D_AdvMask = 1;
  
  *(short*)0x800b5574 = bool_interruptWarppad;
  
  // flag 0x76 is where hints start
  // in adventure profile
  uVar4 = (int)hintId + 0x76;
  
  // pointer to P1 player structure
  advDriver = gGT->drivers[0];
  
  // make a copy of hint index
  *(short*)0x800b5558 = hintId;
  
  advDriver->funcPtrs[0] = &VehPtr_Freeze_Init;
  
  // 0x8fba4 is where the adventure profile (currently loaded) begins
  // unlock flag that says you've viewed this mask hint before.
  sdata->advProgress.rewards[(int)uVar4 >> 5] |= 1 << (uVar4 & 0x1f);
  
  // If this is "welcome to adventure arena"
  if (hintId == 0) 
  {
	// unlock two hints, since Aku talks for a while
    *(u_int*)0x8008fbb0 = *(u_int*)0x8008fbb0 | 0x800000;
    *(u_int*)0x8008fbb4 = *(u_int*)0x8008fbb4 | 0x4000;
  }
  
  // If Aku / Uka model pointer is nullptr
  if (sdata->modelMaskHints3D == NULL) 
  {
	// This is the first time getting
	// a hint on this instance of adv hub
	  
	// get mempack index
    uVar2 = LOAD_GetAdvPackIndex();
	
    boolGoodGuy = Weapon_Mask_boolGoodGuy(advDriver);
    
	LOAD_TalkingMask(uVar2,((boolGoodGuy & 0xffff) == 0));
	
	// Take 90 frames to spawn (3 seconds)
    *(int*)0x800b566c = 0x5a;
  }
  
  // if model is not nullptr
  else 
  {
	// Take 20 frames to spawn (2/3 second)
    *(int*)0x800b566c = 0x14;
  }
  
  iVar3 = (bool_interruptWarppad & 1) * 6;
  
  DAT_800b51f0 = (&DAT_800b5200 + iVar3);
  DAT_800b51f2 = (&DAT_800b5202 + iVar3);
  DAT_800b51f4 = (&DAT_800b5204 + iVar3);
  DAT_800b51f8 = (&DAT_800b520c + iVar3);
  DAT_800b51fa = (&DAT_800b520e + iVar3);
  DAT_800b51fc = (&DAT_800b5210 + iVar3);
  
  for (i = 0; i < 3; i++)
  {
	// Make a backup of Volume settings
    uVar1 = howl_VolumeGet(i);
    ((u_int*)0x800b5668)[i] = uVar1;
  } 
  return;
}