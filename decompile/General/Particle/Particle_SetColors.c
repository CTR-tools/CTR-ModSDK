#include <common.h>

#define COLOR_FLAG_R 0x0080
#define COLOR_FLAG_G 0x0100
#define COLOR_FLAG_B 0x0200

/// @brief Returns processed color based on particle values. called from Particle_RenderList and Particle_Init
/// @param flagColors - color flags
/// @param flagAlpha - alpha flags
/// @param p - particle to work with
/// @return color
u_int DECOMP_Particle_SetColors(u_int flagColors, u_int flagAlpha, struct Particle* p)
{
  u_int color = 0;

  if (flagColors & COLOR_FLAG_R)
  { 
    //so we kinda store rgb value to a temp var
    //and reuse it in case no color flag is set.
    //this way if only red flag is set, it becomes grayscale? weird.

    //process red
    int temp = DECOMP_Particle_BitwiseClampByte(&p->axis[7].startVal);

    color |= temp;

    //process green
    if (flagColors & COLOR_FLAG_G)
      temp = DECOMP_Particle_BitwiseClampByte(&p->axis[8].startVal);

    color |= temp << 8;

    //process blue
    if (flagColors & COLOR_FLAG_B)
      temp = DECOMP_Particle_BitwiseClampByte(&p->axis[9].startVal);

    color |= temp << 16;
  }
  else
  {
    // draw white
    color = 0x01000000;
  }

  //check alpha flag
  if (flagAlpha & 0x80) color |= 0x2000000;

  return color;
}