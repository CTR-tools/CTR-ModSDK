#include <common.h>

void FrameMS_RunUpdateHook()
{
	char* string;
	int timer;
	int p;

	string = (char*)0x8000FFF8;
	timer = sdata->gGT->elapsedTimeMS;

	// at some point, upgrade this to use RCNT (more precise)
	// units, which are harder to get, but they're somewhere

	if(timer > 999) timer = 999;

	string[0] =  '0' + (timer / 100) % 10;
	string[1] =  '0' + (timer / 10) % 10;
	string[2] =  '0' + timer % 10;
	string[3] = 0;
	DecalFont_DrawLine(string, 10, 200, FONT_BIG, ORANGE);
}