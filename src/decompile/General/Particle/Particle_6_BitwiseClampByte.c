#include <common.h>

#define CLAMP_LOW  0
#define CLAMP_HIGH 0xFF00

/// @brief Clamps int to 0-0xFF00 range, but only takes upper 8 bits from the result.
/// @param value - input value
/// @return clamped value
int DECOMP_Particle_BitwiseClampByte(int* value)
{
  if (*value < CLAMP_LOW) 
    *value = CLAMP_LOW;
  else if (*value > CLAMP_HIGH)
    *value = CLAMP_HIGH;

  return *value >> 8;
}