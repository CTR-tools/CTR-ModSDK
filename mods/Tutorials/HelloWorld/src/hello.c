#include <common.h>

/*
BUILD is a variable assigned during compilation time.
It takes the value build_id defined in config.json
You can also see what these aliases for BUILD equal to
in include/gccHeaders.h
*/
char RegionString[] =
#if BUILD == UsaRetail
	"NTSC-U";
#elif BUILD == EurRetail
	"PAL";
#elif BUILD == JpnRetail
	"NTSC-J";
#elif BUILD == SepReview
	"September 3 Prototype";
#elif BUILD == JpnTrial
	"Japan Store Trial";
#else
	"Unknown build";
#endif

// The PAL version has a bigger screen display, so the Y position needs to be lower (by making its value higher)
int height =
#if BUILD == EurRetail
	220;
#else
	200;
#endif

void Hello_Main()
{
	if (!(sdata->gGT->gameMode1 & LOADING))
	{
		/*
			For the last two parameters in DecalFont_DrawLine,
			check include/namespace_Decal.h
		*/
		DecalFont_DrawLine(RegionString, 10, height, FONT_SMALL, ORANGE);
		DecalFont_DrawLine("Hello World!", 10, height - 10, FONT_SMALL, ORANGE);
	}
}