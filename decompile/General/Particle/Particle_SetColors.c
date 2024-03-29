#include <common.h>

// called from Particle_RenderList and Particle_Init
u_int DECOMP_Particle_SetColors(u_int flagColors, u_int flagAlpha, struct Particle* p)
{
  u_int rgba;
  u_int channel;

  if ((flagColors & 0x80) == 0)
  {
    // draw white
    rgba = 0x1000000;

    if ((flagAlpha & 0x80) != 0)
    {
        // draw white, with alpha clipping
        rgba = 0x3000000;
    }
  }
  else
  {
    // red
    channel = DECOMP_Particle_BitwiseClampByte(&p->axis[7].startVal);
	rgba = channel;

    if ((flagColors & 0x100) != 0)
    {
      // green
      rgba = DECOMP_Particle_BitwiseClampByte(&p->axis[8].startVal);
    }
	
	rgba = channel | (rgba<<8);

    if ((flagColors & 0x200) != 0)
    {
      // blue
      channel = DECOMP_Particle_BitwiseClampByte(&p->axis[9].startVal);
    }
	
	rgba = rgba | (channel<<0x10);

    if ((flagAlpha & 0x80) != 0)
    {
        // enable alpha clipping
        rgba |= 0x2000000;
    }
  }

  // returns 0xXXBBGGRR
  // BB for blue, GG for green, RR for red, XX for flags
  return rgba;
}