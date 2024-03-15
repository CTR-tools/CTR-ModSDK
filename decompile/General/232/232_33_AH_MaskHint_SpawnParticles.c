#include <common.h>

void DECOMP_AH_MaskHint_SpawnParticles(short numParticles,short param_2,int maskAnim)

{
  struct Particle* particle;
  struct Instance* maskInst;
  int i;
  
  maskAnim = maskAnim + 0x1000;
  if (maskAnim > 0x3fff) {
    maskAnim = 0x3fff;
  }
  
  // "hubdustpuff"
  struct IconGroup* ig = sdata->gGT->iconGroup[0x10];
  
  // talking mask instance
  maskInst = sdata->instMaskHints3D;
  
  for (i = 0; i < numParticles; i++) 
  {
    particle = Particle_CreateInstance(0,ig,param_2);
    if(particle == NULL) return;

    particle->axis[0].startVal += maskInst->matrix.t[0] * 0x100;
    particle->axis[1].startVal += maskInst->matrix.t[1] * 0x100;
    particle->axis[2].startVal += maskInst->matrix.t[2] * 0x100;
    
	particle->axis[5].startVal = (particle->axis[5].startVal * maskAnim) >> 0xc;
    particle->axis[5].velocity = (particle->axis[5].velocity * maskAnim) >> 0xc;
    
	particle->unk18 -= 5;
  }
  return;
}