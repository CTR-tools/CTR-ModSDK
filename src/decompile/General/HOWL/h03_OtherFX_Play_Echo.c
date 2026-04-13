#include <common.h>

// param_3:
// 0 - normal
// 1 - echo
void DECOMP_OtherFX_Play_Echo(unsigned int soundID, int flags, int echoFlag)
{
	// ff8080:
	// 0x00 - no echo
	// 0xff - volume
	// 0x80 - distortion (none)
	// 0x80 - LR (center of left and right)
	int otherFlags = 0xff8080;
	
	if(echoFlag != 0) otherFlags |= 0x1000000;
	
	DECOMP_OtherFX_Play_LowLevel(soundID & 0xfff, flags & 0xff, otherFlags);
}