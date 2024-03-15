#include <common.h>

void DECOMP_AH_MaskHint_Start(short hintId, u_short bool_interruptWarppad)
{
  int iVar3;
  int bitIndex;
  struct Driver* d;
  
  // copy parameters
  *(short*)0x800b5574 = bool_interruptWarppad;
  *(short*)0x800b5558 = hintId;
  
  sdata->boolDraw3D_AdvMask = 1;
    
  struct AdvProgress* adv = &sdata->advProgress;
  bitIndex = (int)hintId + 0x76;
  UNLOCK_ADV_BIT(adv->rewards,bitIndex);
  
  // If this is "welcome to adventure arena"
  if (hintId == 0) 
  {
	// "Using a Warppad" and "Map Information"
    adv->rewards[3] |= 0x800000;
    adv->rewards[4] |= 0x4000;
  }
  
  d = sdata->gGT->drivers[0];
  d->funcPtrs[0] = DECOMP_VehPhysProc_FreezeEndEvent_Init;
  
  // If Aku / Uka model pointer is nullptr
  if (sdata->modelMaskHints3D == NULL) 
  {	
	DECOMP_LOAD_TalkingMask(
		DECOMP_LOAD_GetAdvPackIndex(),
		!DECOMP_VehPickupItem_MaskBoolGoodGuy(d)
	);
	
	// 3.0s to spawn mask
    *(int*)0x800b566c = 90;
  }
  
  // if model is not nullptr
  else 
  {
	// 0.667s to spawn mask
    *(int*)0x800b566c = 20;
  }
  
  iVar3 = (bool_interruptWarppad & 1) * 3;
  
  short* input = 0x800b5200;
  
  // 800b5200-800b5206, and 800b5206-800b520c
  *(short*)0x800b51f0 = input[iVar3 + 0];
  *(short*)0x800b51f2 = input[iVar3 + 1];
  *(short*)0x800b51f4 = input[iVar3 + 2];
  
  // 800b520c-800b5212, and 800b5212-800b5218
  *(short*)0x800b51f8 = input[iVar3 + 6];
  *(short*)0x800b51fa = input[iVar3 + 7];
  *(short*)0x800b51fc = input[iVar3 + 8];
  
  for (int i = 0; i < 3; i++)
  {
	// 4 bytes for 4 volumes
    ((char*)0x800b5668)[i] = 
		DECOMP_howl_VolumeGet(i);
  } 
    
  return;
}