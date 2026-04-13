#include <common.h>

// param1 pointer to array of two shorts (x,y)
void DECOMP_UI_Lerp2D_HUD(short* ptrPos, short startX, short startY, short endX, short endY, int curFrame, short endFrame)
{
	int endFrameInt;
	int newPosX;

	newPosX = curFrame * ((int)startX - (int)endX);
	endFrameInt = (int)endFrame;

	// newPosY
	curFrame = curFrame * ((int)startY - (int)endY);
	
	*ptrPos = endX + (short)(newPosX / endFrameInt);
	ptrPos[1] = endY + (short)(curFrame / endFrameInt);
	return;
}