#include <common.h>

void DECOMP_MM_HighScore_Text3D(char *string, int posX, int posY, short font, u_int flags)
{
    // Used in High Score Menu

    // draw a string
    DecalFont_DrawLine(string, posX, posY, font, flags);

    // draw the same string in a different place
    DecalFont_DrawLine(string, (posX + 3), (posY + 1), font, flags & (END_AT_X | CENTER_TEXT | BLACK));
    return;
}