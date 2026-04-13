#include <common.h>

unsigned int DECOMP_howl_InstrumentPitch(int basePitch, int pitchIndex, unsigned int distort)
{
  // param_3
  // (>> 0) & 0x40 - distortion
  // (>> 6) & 0xXX - pitch/octave?
  
  unsigned int freq = data.noteFrequency
				[
					pitchIndex + ((int)distort>>6) -2
				] * basePitch >> 0xc;
		
  distort &= 0x3f;		
  freq &= 0xffff;
  
  if(distort != 0)
  {
	  freq = freq * (data.distortConst_Music[distort] + 0x100000) >> 0x14; 
  }
  
  return freq;
}