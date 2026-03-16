#include <common.h>

void DECOMP_AH_HintMenu_MaskPosRot(void)
{
  struct Instance* mask = 
	sdata->instMaskHints3D;
  
  ConvertRotToMatrix(&mask->matrix, (short*)&D232.maskRot);
  
  // Set position
  mask->matrix.t.x = D232.maskPos.x;
  mask->matrix.t.y = D232.maskPos.y;
  mask->matrix.t.z = D232.maskPos.z;
  
  struct MaskHint* hint = (struct MaskHint*)mask->thread->object;
  
  // always 0x1000 ???
  hint->scale = 
	D232.maskScale;
  
  return;
}