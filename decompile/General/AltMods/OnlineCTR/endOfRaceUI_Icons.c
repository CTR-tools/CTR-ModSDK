#include <common.h>
#include "global.h"

extern int bestCourseIndex;
extern int bestLapIndex;

extern const char maxCourseStr[12];
extern const char maxLapStr[9];
extern char courseTimeStr[12];
extern char lapTimeStr[9];

char * GetTimeString(int msElapsed, int course)
{
    char * ret;
    if (course)
    {
        ret = courseTimeStr;
        if ((msElapsed / HOURS(1)) < 10)
	    {
            courseTimeStr[0] = ((msElapsed / HOURS(1)) % 10) + '0';
            courseTimeStr[2] = ((msElapsed / MINUTES(10)) % 6) + '0';
            courseTimeStr[3] = ((msElapsed / MINUTES(1)) % 10) + '0';
            courseTimeStr[5] = ((msElapsed / SECONDS(10)) % 6) + '0';
            courseTimeStr[6] = ((msElapsed / SECONDS(1)) % 10) + '0';
            courseTimeStr[8] = (((msElapsed * 10) / SECONDS(1)) % 10) + '0';
            courseTimeStr[9] = (((msElapsed * 100) / SECONDS(1)) % 10) + '0';
            courseTimeStr[10] = (((msElapsed * 1000) / SECONDS(1)) % 10) + '0';
	    }
        else { memcpy(courseTimeStr, maxCourseStr, sizeof(maxCourseStr)); }
    }
    else
    {
        ret = lapTimeStr;
        if ((msElapsed / MINUTES(1)) < 10)
        {
            lapTimeStr[0] = ((msElapsed / MINUTES(1)) % 10) + '0';
            lapTimeStr[2] = ((msElapsed / SECONDS(10)) % 6) + '0';
            lapTimeStr[3] = ((msElapsed / SECONDS(1)) % 10) + '0';
            lapTimeStr[5] = (((msElapsed * 10) / SECONDS(1)) % 10) + '0';
            lapTimeStr[6] = (((msElapsed * 100) / SECONDS(1)) % 10) + '0';
            lapTimeStr[7] = (((msElapsed * 1000) / SECONDS(1)) % 10) + '0';
        }
        else { memcpy(lapTimeStr, maxLapStr, sizeof(maxLapStr)); }
    }
    while (*ret == '0' || *ret == ':') { ret++; }
    return ret;
}

void UpdateBestTimes()
{
    int bestCourse = HOURS(100);
    int bestLap = MINUTES(10);
    for (int i = 0; i < octr->NumDrivers; i++)
    {
        int index = octr->raceStats[i].slot;
        if ((octr->nameBuffer[index][0] == 0) ||
            (octr->raceStats[i].finalTime == 0)) { continue; }

        if (octr->raceStats[i].finalTime < bestCourse)
        {
            bestCourse = octr->raceStats[i].finalTime;
            bestCourseIndex = index;
        }

        if (octr->raceStats[i].bestLap < bestLap)
        {
            bestLap = octr->raceStats[i].bestLap;
            bestLapIndex = index;
        }
    }
}

void EndOfRace_Icons()
{
    const int spacing = 150;
    const int iconHeight = 25;
    const short xStart = 0;
    Point pos = MakePoint(xStart, 20);
    const int scale = FP(1);
    UpdateBestTimes();
    for (int i = 0; i < octr->NumDrivers; i++)
    {
        int index = octr->raceStats[i].slot;
        if ((octr->nameBuffer[index][0] == 0) ||
            (octr->raceStats[i].finalTime == 0)) { continue; }

        struct Icon * icon = sdata->gGT->ptrIcons[data.MetaDataCharacters[data.characterIDs[index]].iconID];
        char racePos = i + '1';
        DECOMP_DecalFont_DrawLineStrlen(&racePos, 1, pos.x + 27, pos.y, FONT_SMALL, RED);
        DECOMP_DecalFont_DrawLineStrlen(octr->nameBuffer[index], NAME_LEN, pos.x + 38, pos.y + 1, FONT_SMALL, index == 0 ? BLUE : ORANGE);
        DECOMP_DecalFont_DrawLineStrlen(GetTimeString(octr->raceStats[i].finalTime, true), 12, pos.x + 38, pos.y + 8 + 1, FONT_SMALL, index == bestCourseIndex ? TINY_GREEN : WHITE);
        DECOMP_DecalFont_DrawLineStrlen(GetTimeString(octr->raceStats[i].bestLap, false), 8, pos.x + 38, pos.y + 16 + 1, FONT_SMALL, index == bestLapIndex ? TINY_GREEN : WHITE);
        DECOMP_UI_DrawDriverIcon(icon, pos, sdata->gGT->pushBuffer_UI.ptrOT, 1, scale, MakeColor(0x80, 0x80, 0x80));

        pos.x += 126;
        if (i == 3)
        {
            pos.x = xStart;
            pos.y += iconHeight;
        }
    }
}