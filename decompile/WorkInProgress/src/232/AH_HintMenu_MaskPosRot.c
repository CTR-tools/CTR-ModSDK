#include <common.h>

void DECOMP_AH_HintMenu_MaskPosRot(void)
{
  struct Instance* mask;
  
   // convert 3 rotation shorts into rotation matrix
  ConvertRotToMatrix(sdata->instMaskHints3D + 0x30,*(int*)0x800b51e4);
  
  // instance of 3D talking mask for hints
  mask = sdata->instMaskHints3D;
  
  // Set position
 mask->matrix.t[0] = *(int*)0x800b51dc;
 mask->matrix.t[1] = *(int*)0x800b51de;
 mask->matrix.t[2] = *(int*)0x800b51e0;
  
  // set thread->object->offset 0x4
  ((int)mask->thread->object + 0x4) = *(int*)0x800b51ec;
  
  return;
}