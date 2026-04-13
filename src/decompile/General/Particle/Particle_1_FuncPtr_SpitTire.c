#include <common.h>

void DECOMP_Particle_FuncPtr_SpitTire(struct Particle *p)
{
  int rng;
  int iVar2;

  // Wait until tires are 0x10 units above
  // the ground, which is where the plant
  // actually "spits" tires from the mouth
  iVar2 = p->plantInst->matrix.t[1] + 0x10;
  
  if ((p->axis[1].startVal >> 8) >= iVar2)
  {
	  return;
  }
  
  p->axis[1].startVal = iVar2 * 0x100;
  
  // random X
  rng = DECOMP_MixRNG_Scramble();
  p->axis[0].velocity = rng + (rng / 0x1640) * -0x1640 - 0xb20;
  
  // random Z
  rng = DECOMP_MixRNG_Scramble();
  p->axis[2].velocity = rng + (rng / 0x1640) * -0x1640 - 0xb20;
  
  // scale value
  iVar2 = p->axis[5].startVal;
  
  switch(iVar2)
  {
	  // frame #1
	  case 0x1000:
	  {
		  // random Y
		  rng = DECOMP_MixRNG_Scramble();
		  p->axis[1].velocity = rng + (rng / 0x12c0) * -0x12c0 + 0x1900;
		  
		  // frame #2
		  p->axis[5].startVal = 0xfff;
		  break;
	  }
	  
	  // frame #2
	  case 0xfff:
	  {
		  // random Y
		  rng = DECOMP_MixRNG_Scramble();
		  p->axis[1].velocity = rng + (rng / 800) * -800 + 8000;
		  
		  // frame #3
		  p->axis[5].startVal = 0xffe;
		  break;
	  }
	  
	  // frame #3
	  case 0xffe:
	  {
		  // random Y
		  rng = DECOMP_MixRNG_Scramble();
		  p->axis[1].velocity = rng + (rng / 800) * -800 + 6000;
		  
		  p->axis[5].velocity = 0xf801;
		  break;
	  }
	  
	  default:
		return;
  }
  
  p->axis[0].velocity = FPS_HALF(p->axis[0].velocity);
  p->axis[1].velocity = FPS_HALF(p->axis[1].velocity);
  p->axis[2].velocity = FPS_HALF(p->axis[2].velocity);
}