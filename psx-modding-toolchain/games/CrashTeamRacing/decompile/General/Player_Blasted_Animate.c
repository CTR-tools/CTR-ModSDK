#include <common.h>

void Player_Blasted_Animate(struct Thread *thread,struct Driver *driver)
{
	u_char animationFrame;
	int iVar2;
	
	driver->animationIndex = 6;
	iVar2 = (int)((u_int)(u_short)driver->NoInputTimer << 0x10) >> 0x15;
	animationFrame = (u_char)(iVar2 % Data.betweenIDsAndMeta[0x1094]);
	if (*(char *)&driver->KartStates != 0)
	{
		animationFrame = (char)Data.betweenIDsAndMeta[0x1094] - (animationFrame + 1);
	}
	driver->animationFrame = animationFrame;
	return;
}
