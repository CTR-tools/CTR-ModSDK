#include <common.h>

int Hello_Main()
{
	if (!(sdata->gGT->gameMode1 & LOADING))
	{
		/*
			BUILD is a variable assigned during compilation time.
			It takes the value build_id defined in config.json
			You can also see what these aliases for BUILD equal to
			in include/gccHeaders.h
			For the last two parameters in DecalFont_DrawLine, also
			check include/namespace_Decal.h
		*/
		#if BUILD == UsaRetail
			DecalFont_DrawLine("NTSC-U", 10, 200, FONT_SMALL, ORANGE);
		#elif BUILD == EurRetail
			DecalFont_DrawLine("PAL", 10, 220, FONT_SMALL, ORANGE);
		#elif BUILD == JpnRetail
			DecalFont_DrawLine("NTSC-J", 10, 200, FONT_SMALL, ORANGE);
		#elif BUILD == SepReview
			DecalFont_DrawLine("September 3 Prototype", 10, 200, FONT_SMALL, ORANGE);
		#elif BUILD == JpnTrial
			DecalFont_DrawLine("Japan Store Trial", 10, 200, FONT_SMALL, ORANGE);
		#else
			DecalFont_DrawLine("Unknown build", 10, 200, FONT_SMALL, ORANGE);
		#endif
		
		#if BUILD == EurRetail
		// The PAL version has a bigger screen display, so the Y position needs to be lower (by making its value higher)
			DecalFont_DrawLine("Hello World!", 10, 210, FONT_SMALL, ORANGE);
		#else
			DecalFont_DrawLine("Hello World!", 10, 190, FONT_SMALL, ORANGE);
		#endif
	}
}