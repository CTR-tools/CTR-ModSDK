#include <common.h>

// Interpolate anything really
int DECOMP_InterpBySpeed(int current, int interpSpeed, int desired)
{
	int iVar1;
	int newCurrent;

	// if desired value is less than current
	if (desired < current)
	{
		// subtract current by a rate of "speed"
		newCurrent = current - interpSpeed;

		// if new value is less than desired
		if (newCurrent < desired)
		{
			// Just use desired value
			return desired;
		}
	}
	// if desired value is not less than current
	else
	{
		// keep current value, for now
		newCurrent = current;

		// desired <= current,
		// we know desired is not less than current,
		// so this really checks if it is current	
		if ((desired <= current) ||
			(
				// copy desired
				newCurrent = desired,

				// add to value at rate of "speed"
				iVar1 = current + interpSpeed,

				// if new value overshoots desired,
				// probably should say >=
				iVar1 <= desired
			)
		)
		{
			// if current = desired
			// if current is overshot past desired

			// current = desired
			newCurrent = iVar1;
		}
	}
	// return new current
	return newCurrent;
}