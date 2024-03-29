#include <common.h>

void DECOMP_AH_MaskHint_SpawnParticles(
	short numParticles,struct ParticleEmitter* emSet,int maskAnim)

{
  struct Particle* particle;
  struct Instance* maskInst;
  int i, j;
  
  maskAnim = maskAnim + 0x1000;
  if (maskAnim > 0x3fff) {
    maskAnim = 0x3fff;
  }
  
  // "hubdustpuff"
  struct IconGroup* ig = sdata->gGT->iconGroup[0x10];
  
  // talking mask instance
  maskInst = sdata->instMaskHints3D;
  
  #ifdef USE_60FPS
  // for particles
  // only for quick-enter, and leaving, NOT for first-enter
  if(numParticles > 5)
	sdata->UnusedPadding1 = 1;
  #endif
  
  for (i = 0; i < numParticles; i++) 
  {
	  
#ifdef REBUILD_PS1
	particle =  NULL;
#else
    particle = Particle_CreateInstance(0,ig,emSet);
#endif

    if(particle == NULL) return;

	for(j = 0; j < 3; j++)
		particle->axis[j].startVal += maskInst->matrix.t[j] * 0x100;
    
	particle->axis[5].startVal = (particle->axis[5].startVal * maskAnim) >> 0xc;
    particle->axis[5].velocity = (particle->axis[5].velocity * maskAnim) >> 0xc;
    
	particle->unk18 -= 5;
  }
  
  #ifdef USE_60FPS
  // for particles
  sdata->UnusedPadding1 = 0;
  #endif
  
  return;
}