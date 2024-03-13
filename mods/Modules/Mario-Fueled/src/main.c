#include <common.h>

void VehFire_Audio(struct Driver *driver, int param_2);

void Mini_Turbo()
{
	struct GameTracker *gGT = sdata->gGT;

	for (char i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		struct Driver* d = gGT->drivers[i];
		short meterLeft = d->turbo_MeterRoomLeft;
			if ((meterLeft < 100) && (meterLeft > 1))
			{
				VehFire_Increment(
					// driver
					d,
					// amount of reserves
					500,
					POWER_SLIDE_HANG_TIME,
					0x800);
			}
	}
}