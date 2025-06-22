#include <common.h>

u_char* DECOMP_RECTMENU_DrawTime(int milliseconds)
{
	// 32 is added to milliseconds every frame,
	// 960 per second, the rest is basic math

	#ifdef REBUILD_PC
		// Overwrite unused mempack,
		// the original game actually did this
		char* str = &sdata->mempack[4];
	#else
		char* str = (char*)0x1f800000;
	#endif

	// build a string
	sprintf(

		str,

#ifndef REBUILD_PS1
		// Format
		// Minute:Seconds:Milliseconds
		&rdata.s_timeString[0],
#else
		"%ld:%ld%ld:%ld%ld",
#endif

		milliseconds / 0xe100,				// minutes
		(milliseconds / 0x2580) % 6,		// seconds / 10
		(milliseconds / 0x3c0) % 10,		// seconds
        ((milliseconds * 10) / 0x3c0) % 10,	// milliseconds / 10
        ((milliseconds * 100) / 0x3c0) % 10	// milliseconds
	  );

	return str;
}