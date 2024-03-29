#include <common.h>

void DECOMP_Particle_FuncPtr_SpitTire(struct Particle *p)
{
  int rng;
  int iVar2;

  if (p->axis[1].startVal >> 8 < (p->plantInst->matrix.t[1] + 0x10))
  {
	// random X
    rng = DECOMP_MixRNG_Scramble();
    p->axis[0].velocity = rng + (rng / 0x1640) * -0x1640 - 0xb20;

	// random Z
    rng = DECOMP_MixRNG_Scramble();
    p->axis[2].velocity = rng + (rng / 0x1640) * -0x1640 - 0xb20;
	
	// scale value
    iVar2 = p->axis[5].startVal;
    if (iVar2 == 0x1000)
    {
	  // random Y
      rng = DECOMP_MixRNG_Scramble();
      p->axis[1].velocity = rng + (rng / 0x12c0) * -0x12c0 + 0x1900;
	  
      p->axis[5].startVal = 0xfff;
    }
    else
    {
      if (iVar2 == 0xfff)
      {
		// random Y
        rng = DECOMP_MixRNG_Scramble();
        p->axis[1].velocity = rng + (rng / 800) * -800 + 8000;
		
        p->axis[5].startVal = 0xffe;
      }
      else
      {
        if (iVar2 != 0xffe)
        {
          return;
        }

		// random Y
        rng = DECOMP_MixRNG_Scramble();
        p->axis[1].velocity = rng + (rng / 800) * -800 + 6000;
		
        p->axis[5].velocity = 0xf801;
      }
    }
	
    iVar2 = p->plantInst->matrix.t[1];
    p->axis[1].startVal = (iVar2 + 0x10) * 0x100;
  }
}