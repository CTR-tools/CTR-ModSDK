#include <common.h>

// Rotation Interpolation
int DECOMP_InterpBySpeed(int currentRot, int rotSpeed, int destinedRot)
{
	int iVar1;
	int newRot;

	// if desired rotation is less than current
	if (destinedRot < currentRot)
	{
		// subtract current by a rate of "speed"
		newRot = currentRot - rotSpeed;

		// if new rotation is less than desired
		if (currentRot - rotSpeed < destinedRot)
		{
			// Just use desired rotation
			return destinedRot;
		}
	}

	// if desired rotation is not less than current
	else
	{
		// make a copy of current
		iVar1 = currentRot;
		if
		(
			// desired <= current,
			// we know desired is not less than current,
			// so this really checks if it is current
			(destinedRot <= currentRot) ||
			(
				// copy desired
				newRot = destinedRot,

				// add to rotation at rate of "speed"
				iVar1 = currentRot + rotSpeed,

				// if new rotation overshoots desired,
				// probably should say >=
				currentRot + rotSpeed <= destinedRot
			)
		)
		{
			// if current = desired
			// if current is overshot past desired

			// current = desired
			newRot = iVar1;
		}
	}

	// return new current
	return newRot;
}