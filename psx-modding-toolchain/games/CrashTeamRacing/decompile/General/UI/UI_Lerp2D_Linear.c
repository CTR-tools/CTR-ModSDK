#include <common.h>

// param1 pointer to array of two shorts (x,y)
void DECOMP_UI_Lerp2D_Linear(short* ptrPos, short startX, short startY, short endX, short endY, int curFrame, short endFrame)
{
	int endFrameInt;
	int newPosX;

	// Get end frame
	endFrameInt = (int)endFrame;

	// If interpolation is not done yet
	if (curFrame <= endFrameInt)
	{
		newPosX = curFrame * ((int)endX - (int)startX);

		// newPosY
		curFrame = curFrame * ((int)endY - (int)startY);

		// posX
		*ptrPos = startX + (short)(newPosX / endFrameInt);

		// posY
		ptrPos[1] = startY + (short)(curFrame / endFrameInt);
		return;
	}

	// if you already reached the end

	// Set X and Y to EndX and EndY
	*ptrPos = endX;
	ptrPos[1] = endY;
	return;
}