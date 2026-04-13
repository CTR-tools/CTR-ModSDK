#include <common.h>

int DECOMP_VehPhysJoystick_GetStrength(int val, int max, struct RacingWheelData* rwd)
{
	int dead;
	int range;
	int dist;
	
	if(rwd == 0)
	{
		dead = 0x30;
		range = 0x7f;
		dist = 0x5e;
	}
	
	else
	{
		dead = rwd->deadZone;
		range = rwd->range;
		dist = range-dead;
	}
	
	if(val < dead)
		return 0;
	
	dead = val-dead;
	
	if(range <= val)
		return max;
	
	if((dist/2) <= dead)
	{
		dead = (dead - dist/2) * (max - max/5) * 2;
		return (dead/dist) + (max/5);
	}
	
	dead *= (max/5)*2;
	return dead / dist;
}