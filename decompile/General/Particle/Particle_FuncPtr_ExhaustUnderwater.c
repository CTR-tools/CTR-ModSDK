#include <common.h>

void DECOMP_Particle_FuncPtr_ExhaustUnderwater(struct Particle *p)
{
  struct IconGroup *icon;
  struct Icon** iconPtrArray;

  if (
		(3 < ((p->axis[1].startVal >> 8) + p->driverInst->matrix.t[1])) &&
		(p->framesLeftInLife < FPS_DOUBLE(27))
	  )
  {
    // bubblepop
    icon = sdata->gGT->iconGroup[8];

    if (icon != NULL)
    {
      // save icons
      p->ptrIconGroup = icon;
	  
	  struct Icon** ptrIconArray = ICONGROUP_GETICONS(icon);
      
	  // actually the first icon pointer in the array,
	  // not the pointer to the array itself
	  p->ptrIconArray = ptrIconArray[0];
    }

    p->axis[4].startVal = DECOMP_MixRNG_Scramble() & 0xfff;
    p->framesLeftInLife = 0;
  }
}