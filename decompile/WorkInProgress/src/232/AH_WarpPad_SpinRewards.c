#include <common.h>

void DECOMP_AH_WarpPad_SpinRewards(struct Instance* pad, struct WarpPad* wp,short param_3,int posX,int posY,int posZ)
{
  short modelID;
  int ratio;
  
   // convert 3 rotation shorts into rotation matrix
  ConvertRotToMatrix(&pad->matrix,*(short*)((int)wp + 0x28));
  
  // instance -> model -> modelID
  modelID = pad->model->id;
  
  // if not trophy
  if (CheckModelID(modelID, STATIC_TROPHY)) 
  {
	// Gem
    if (CheckModelID(modelID, STATIC_GEM)) {
      ratio = wp->specLightGem[0];
    }
    else 
	{
	  // Relic
      if (CheckModelID(modelID, STATIC_RELIC)) {
        ratio = wp->specLightRelic[0];
      }
      else 
	  {
		// if not token
        if (CheckModelID(modelID, STATIC_TOKEN) == false) goto LAB_800abe94;
		
		// if it is a token
        ratio = wp->specLightToken[0];
      }
    }
	
    Vector_SpecLightSpin3D(pad,*(short*)((int)wp + 0x28),ratio);
  }
LAB_800abe94:

  // Sine(angle)
  ratio = MATH_Sin((wp + (int)param_3 * 2 + 0x6e));

  ratio = (int)param_3 * 0x555;
  
  pad->matrix.t[1] = posY + ((ratio << 6) >> 0xc) + 0x100;
  
  // Sine(angle)
  ratio = MATH_Sin(ratio + *(short *)(wp + 0x4a));
  
  pad->matrix.t[0] = posX + (ratio * 0xa0 >> 0xc);
  
  // Cosine(angle)
  ratio = MATH_Cos(ratio + *(short *)(wp + 0x4a));
  
  pad->matrix.t[2] = posY + (ratio * 0xa0 >> 0xc);
  return;
}