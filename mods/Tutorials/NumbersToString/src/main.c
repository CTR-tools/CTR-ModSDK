#include <common.h>

void NumbersToString(char * str, int value, int digits, int hexadecimal);

int Hello_Main()
{
	char string[] = "   ";
	NumbersToString(string, 9999, 4, 0);

	if (!(sdata->gGT->gameMode1 & LOADING)) DecalFont_DrawLine(string, 10, 190, FONT_BIG, ORANGE);
}