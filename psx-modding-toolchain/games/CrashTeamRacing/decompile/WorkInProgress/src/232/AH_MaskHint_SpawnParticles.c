#include <common.h>

void DECOMP_AH_MaskHint_SpawnParticles(short numParticles,short param_2,int maskAnim)

{
  struct Particle* particle;
  struct Instance* maskInst;
  int i;
  
  maskAnim = maskAnim + 0x1000;
  if (0x3fff < maskAnim) {
    maskAnim = 0x3fff;
  }
  
  if (numParticles > 0) {
    for (i = 0; i < numParticles; i++) 
	{
	  // Create instance in particle pool of "hubdustpuff"
      particle = Particle_CreateInstance(0,sdata->gGT->ptrIcons[0x10],param_2);
	  
	  // talking mask instance
      maskInst = sdata->instMaskHints3D;
	  
	  // if particle created properly
      if (particle != NULL) 
	  {
        particle->axis[0].startVal += maskInst->matrix.t[0] * 0x100;
        particle->axis[1].startVal += maskInst->matrix.t[1] * 0x100;
        particle->unk18 -= 5;
        particle->axis[2].startVal += maskInst->matrix.t[2] * 0x100;
        particle->axis[5].startVal *= maskAnim >> 0xc;
        particle->axis[5].velocity *= maskAnim >> 0xc;
      }
    } 
  }
  return;
}