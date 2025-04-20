#ifndef SAPHI_ICONS_H
#define SAPHI_ICONS_H

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

typedef struct LeaderboardEntry
{
    int time;
    unsigned char country;
    unsigned char character;
    char name[18];
} LeaderboardEntry;

typedef struct CountryFlag
{
    uint32_t image[40];
    uint32_t clut[8];
} CountryFlag;

#define NUM_STANDARDS 4
#define NUM_DISPLAY_LEADERBOARDS 15

#define COUNTRIES_SIZE 0x9800
#define COUNTRIES_ADDR 0x802BE670
#define SAPHI_DLL_ADDR (COUNTRIES_ADDR + COUNTRIES_SIZE)

#define STANDARDS_ADDR 0x8000C04C
#define BOARDS_COURSE_ADDR (STANDARDS_ADDR + (sizeof(Standard) * NUM_STANDARDS))
#define COURSE_PB_ADDR (BOARDS_COURSE_ADDR + sizeof(LeaderboardEntry) * NUM_DISPLAY_LEADERBOARDS)
#define BOARDS_LAP_ADDR (COURSE_PB_ADDR + sizeof(LeaderboardEntry))
#define LAP_PB_ADDR (BOARDS_LAP_ADDR + sizeof(LeaderboardEntry) * NUM_DISPLAY_LEADERBOARDS)
#define COURSE_PB_POS (LAP_PB_ADDR + sizeof(LeaderboardEntry))
#define LAP_PB_POS (COURSE_PB_POS + sizeof(int))

void Saphi_LoadCustomIcons();
void Saphi_DrawSprite(const RECT* iconPos, const RECT* clutPos, Point pos, u_long* ot, unsigned transparency, int scale, Color color);
void Saphi_DrawCustomIcon(unsigned iconID, Point pos, u_long* ot, unsigned transparency, int scale, Color color);
void Saphi_ResetVariables();

#endif