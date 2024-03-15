#include <common.h>

void DECOMP_AH_HintMenu_MaskPosRot(void)
{
  struct Instance* mask = 
	sdata->instMaskHints3D;
  
  ConvertRotToMatrix(&mask->matrix,0x800b51e4);
  
  // Set position
  mask->matrix.t[0] = *(short*)0x800b51dc;
  mask->matrix.t[1] = *(short*)0x800b51de;
  mask->matrix.t[2] = *(short*)0x800b51e0;
  
  // always 0x1000 ???
  ((struct MaskHint*)mask->thread->object)->scale = 
	*(short*)0x800b51ec;
  
  return;
}