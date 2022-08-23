#include <common.h>

int MATH_Sin(unsigned int angle);

// used for character icons in races
// get position of icon based on a circular motion to move the driver up or down in the ranks
// param1 = pointer to (x,y) position
// param2 = drawn position
// param3 = absolute position
// param4 = frame counter
void DECOMP_InterpolatePosition2D_Angular(short* ptrPos, short drawnPosition, short absolutePosition, short frameCounter)
{
	int angle;
	int drawnPositionInt;
	int absolutePositionInt;
	short bitshiftDrawnPosition;

	// all rotations are counter-clockwise, frameCounter * 0x1b * x is used to make the circular motion (x,y) positive or negative, to change the radius and side of rotation.
	// Moving up moves icon to the right
	// Moving down moves icon to the left
	// 0x1b is a constant for base radius

	// drawn position
	drawnPositionInt = (int)drawnPosition;

	// absolute position
	absolutePositionInt = (int)absolutePosition;

	// if driver "just" passed another driver
	if (absolutePositionInt < drawnPositionInt)
	{
		// Sine(angle)
		angle = MATH_Sin(((int)frameCounter << 0xb) / 5);

		// absolutePositionInt - drawnPositionInt is a negative number
		drawnPositionInt = (int)frameCounter * 0x1b * (absolutePositionInt - drawnPositionInt);

		bitshiftDrawnPosition = (short)((u_int)drawnPositionInt >> 0x10);
		drawnPositionInt = (int)(drawnPositionInt / 20);
		*ptrPos = (short)(angle * 0x14 >> 0xc) + 0x14;
	}

	// if driver "was" passed by another driver
	else
	{
		// Sine(angle)
		angle = MATH_Sin(((int)frameCounter << 0xb) / 5);

		// absolutePositionInt - drawnPositionInt is a positive number
		drawnPositionInt = (int)frameCounter * 0x1b * (absolutePositionInt - drawnPositionInt);

		bitshiftDrawnPosition = (short)((u_int)drawnPositionInt >> 0x10);
		drawnPositionInt = (int)(drawnPositionInt / 20);
		*ptrPos = 0x14 - (short)(angle * 0x14 >> 0xc);
	}
	ptrPos[1] = drawnPosition * 0x1b + ((short)(drawnPositionInt >> 1) - (bitshiftDrawnPosition >> 0xf)) + 0x39;
	return;
}