#include <common.h>

void DECOMP_AH_MaskHint_Start(short hintId, u_short bool_interruptWarppad)
{
  int iVar3;
  int bitIndex;
  struct Driver* d;
  
  // copy parameters
  D232.maskWarppadBoolInterrupt = bool_interruptWarppad;
  D232.maskHintID = hintId;
  
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
    D232.maskSpawnFrame = FPS_DOUBLE(90);
  }
  
  // if model is not nullptr
  else 
  {
	// 0.667s to spawn mask
    D232.maskSpawnFrame = FPS_DOUBLE(20);
  }
  
  iVar3 = (bool_interruptWarppad & 1) * 3;
  
  short* input = &D232.maskVars[0];
  
  D232.maskOffsetPos[0] = input[iVar3 + 0];
  D232.maskOffsetPos[1] = input[iVar3 + 1];
  D232.maskOffsetPos[2] = input[iVar3 + 2];
  
  D232.maskOffsetRot[0] = input[iVar3 + 6];
  D232.maskOffsetRot[1] = input[iVar3 + 7];
  D232.maskOffsetRot[2] = input[iVar3 + 8];
  
  for (int i = 0; i < 3; i++)
  {
	// 4 bytes for 4 volumes
    D232.audioBackup[i] = 
		DECOMP_howl_VolumeGet(i);
  } 
    
  return;
}