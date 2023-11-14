#include <common.h>

void DECOMP_MM_HighScore_Text3D(char *string, int posX, int posY, short font, u_int flags)
{
    // draw a string
    DECOMP_DecalFont_DrawLine(string, posX, posY, font, flags);

    // draw the same string in a different place
    DECOMP_DecalFont_DrawLine(
		string, (posX + 3), (posY + 1), font, 
		(flags & (JUSTIFY_CENTER|JUSTIFY_RIGHT)) | BLACK);
}