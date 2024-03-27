#include <common.h>

void DECOMP_AH_HintMenu_MaskPosRot(void)
{
  struct Instance* mask = 
	sdata->instMaskHints3D;
  
  ConvertRotToMatrix(&mask->matrix, &D232.maskRot[0]);
  
  // Set position
  mask->matrix.t[0] = D232.maskPos[0];
  mask->matrix.t[1] = D232.maskPos[1];
  mask->matrix.t[2] = D232.maskPos[2];
  
  // always 0x1000 ???
  ((struct MaskHint*)mask->thread->object)->scale = 
	D232.maskScale;
  
  return;
}