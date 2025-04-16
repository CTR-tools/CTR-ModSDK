#pragma once

#include <common.h>

enum CustomIcons
{
    ICON_CHAMPION,
    ICON_GOD,
    ICON_HERO,
    ICON_TITAN,
};

void LoadCustomIcons();
void DrawCustomIcon(unsigned iconID, Point pos, u_long* ot, unsigned transparency, int scale, Color color);