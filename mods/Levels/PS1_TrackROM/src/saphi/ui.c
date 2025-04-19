#include "saphi.h"
#include "utils.h"

char showStandards = 0;

static void ElapsedTimeToTotalTime(char * out, int elapsedTime)
{
    TotalTime totalTime;
	totalTime.hours = elapsedTime / HOURS(1);
	elapsedTime -= HOURS(1) * totalTime.hours;
	totalTime.minutes = elapsedTime / MINUTES(1);
	elapsedTime -= MINUTES(1) * totalTime.minutes;
	totalTime.seconds = elapsedTime / SECONDS(1);
	elapsedTime -= SECONDS(1) * totalTime.seconds;
	totalTime.miliseconds = (elapsedTime * 1000) / SECONDS(1);
    if (totalTime.hours > 0) { sprintf(out, "%d:%02d:%02d.%02d", totalTime.hours, totalTime.minutes, totalTime.seconds, totalTime.miliseconds); }
    else { sprintf(out, "%d:%02d.%02d", totalTime.minutes, totalTime.seconds, totalTime.miliseconds); }
}

void Saphi_ResetVariables()
{
    showStandards = 0;
}

void Saphi_RaceUI()
{
    UI_RenderFrame_Racing();

    struct GameTracker* gGT = sdata->gGT;
    struct GamepadBuffer * controller = &sdata->gGamepads->gamepad[0];

    if (controller->buttonsTapped & BTN_SELECT)
    {
        showStandards = !showStandards;
        if (showStandards) { gGT->gameMode1 |= PAUSE_1; }
        else { gGT->gameMode1 &= ~PAUSE_1; }
    }

    if (showStandards)
    {
        const int screenCenterX = 256;
        const int menuWidth = 170;
        const int menuHeight = 140;
        const int menuX = 256 - (menuWidth / 2);
        const int menuY = 5;

        DecalFont_DrawLine("Standards", screenCenterX, menuY + 5, FONT_SMALL, JUSTIFY_CENTER | PENTA_WHITE);

        int icons[] = { ICON_CHAMPION, ICON_HERO, ICON_TITAN, ICON_GOD };
        char* standards[] = { "Champion", "Hero", "Titan", "God" };
        Point pos = { .x = menuX + 10, .y = menuY + 20 };
        Color color = { .r = 0x7F, .g = 0x7F, .b = 0x7F };
        Standard* standardTimes = STANDARDS_ADDR;
        for (int i = 0; i < ARR_SIZE(icons); i++)
        {
            char lapTime[11];
            char courseTime[11];
            ElapsedTimeToTotalTime(lapTime, standardTimes[i].lap);
            ElapsedTimeToTotalTime(courseTime, standardTimes[i].course);
            DecalFont_DrawLine(standards[i], menuX + 108, pos.y, FONT_SMALL, JUSTIFY_CENTER | PENTA_WHITE);
            DecalFont_DrawLine(courseTime, menuX + 55, pos.y + 8 + 3, FONT_SMALL, PENTA_WHITE);
            DecalFont_DrawLine(lapTime, menuX + 55, pos.y + 16 + 3, FONT_SMALL, PENTA_WHITE);
            Saphi_DrawCustomIcon(icons[i], pos, gGT->pushBuffer_UI.ptrOT, 0, 0x1000, color);
            pos.y += 30;
        }

        Color menuColor = { .r = 0, .g = 0, .b = 0 };
        RECT menu = { .x = menuX, .y = menuY, .w = menuWidth, .h = menuHeight };
        CTR_Box_DrawSolidBox(&menu, &menuColor, gGT->pushBuffer_UI.ptrOT, &sdata->gGT->backBuffer->primMem);
    }
}