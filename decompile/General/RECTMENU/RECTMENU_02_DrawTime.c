#include <common.h>

u_char* DECOMP_RECTMENU_DrawTime(int milliseconds)
{
	// Here's how it works:
	// 32 is added to milliseconds every frame,
	// 30 fps, so milliseconds gets 960 added every second,
	// 60 seconds per minute, so milliseconds gets 57600
	// added per minute, which is 0xe100 in hex

	// 32 is the number of milliseconds passed since
	// last frame, which is calculated here:
	// PTR_DAT_8008d2ac + 0x1d04

	// build a string
	sprintf(

		// where string will be stored
		&sdata->fillerAfterMempack[0x60],

#ifndef REBUILD_PS1
		// Format
		// Minute:Seconds:Milliseconds
		&rdata.s_timeString[0],
#else
		"%ld:%ld%ld:%ld%ld",
#endif

		// minutes
		milliseconds / 0xe100,

		// seconds / 10
		(milliseconds / 0x2580) % 6,

		// seconds
		(milliseconds / 0x3c0) % 10,

		// milliseconds / 10
        ((milliseconds * 10) / 0x3c0) % 10,

		// milliseconds
        ((milliseconds * 100) / 0x3c0) % 10
	  );

	// return the string
	return &sdata->fillerAfterMempack[0x60];
}