#ifndef SAPHI_ICONS_H
#define SAPHI_ICONS_H

#define SAPHI_DLL_ADDR 0x802BE670
#define STANDARDS_ADDR (Standard*) 0x8000C04C

#include <common.h>

enum CustomIcons
{
    ICON_CHAMPION,
    ICON_GOD,
    ICON_HERO,
    ICON_TITAN,
};

typedef struct TotalTime
{
	int hours;
	int minutes;
	int seconds;
	int miliseconds;
} TotalTime;

typedef struct Standard
{
    int course;
    int lap;
} Standard;

void Saphi_LoadCustomIcons();
void Saphi_DrawCustomIcon(unsigned iconID, Point pos, u_long* ot, unsigned transparency, int scale, Color color);
void Saphi_ResetVariables();

#endif