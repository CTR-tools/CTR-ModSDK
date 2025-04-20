#include "saphi.h"
#include "utils.h"

enum StandardsUI
{
    SUI_NONE = 0,
    SUI_STANDARDS = 1,
    SUI_COURSE = 2,
    SUI_LAP = 3,
    SUI_MAX
};

static unsigned char showUI = 0;

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
    showUI = 0;
}

static void Saphi_DrawLeaderboard(char* title, LeaderboardEntry* boards, int selfPos, int course)
{
    const int screenCenterX = 256;
    const int menuWidth = 385;
    const int menuHeight = 212;
    const int menuX = screenCenterX - (menuWidth / 2);
    const int menuY = 2;

    DecalFont_DrawLine(title, screenCenterX, menuY + 5, FONT_SMALL, ORANGE | JUSTIFY_CENTER);

    struct GameTracker* gGT = sdata->gGT;
    u_long* ot = gGT->pushBuffer_UI.ptrOT;
    struct PrimMem* primMem = &sdata->gGT->backBuffer->primMem;

    CountryFlag* flags = (CountryFlag*) COUNTRIES_ADDR;
    Color color = { .r = 0x7F, .g = 0x7F, .b = 0x7F };
    RECT clutPos = { .x = 64, .y = 284, .w = 16, .h = 1 };
    RECT imagePos = { .x = 64, .y = 264, .w = 8, .h = 10 };
    for (int i = 0; i < NUM_DISPLAY_LEADERBOARDS; i++)
    {
        LoadImage(&imagePos, flags[boards[i].country + 112 + i].image);
        LoadImage(&clutPos, flags[boards[i].country + 112 + i].clut);

        char courseTime[11];
        char boardPos[] = {'0' + i + 1, '\0', '\0'};
        if (i >= 9)
        {
            boardPos[0] = '1';
            boardPos[1] = '0' + ((i + 1) % 10);
        }
        int yPos = menuY + 18 + 13 * i;

        int fontColor = PENTA_WHITE;
        if (i == 0) { fontColor = PLAYER_YELLOW; }
        else if (i == 1) { fontColor = SILVER; }
        else if (i == 2) { fontColor = ORANGE_RED; }
        else if (i == NUM_DISPLAY_LEADERBOARDS - 1)
        {
            if (selfPos < 10) { boardPos[0] = '0' + selfPos; boardPos[1] = '\0'; }
            else { boardPos[0] = '0' + (selfPos / 10); boardPos[1] = '0' + (selfPos % 10); }
            fontColor = OXIDE_LIGHT_GREEN;
        }
        DecalFont_DrawLine(boardPos, menuX + 15, yPos, FONT_SMALL, fontColor | JUSTIFY_CENTER);
        Saphi_DrawSprite(&imagePos, &clutPos, (Point){menuX + 30, yPos - 1}, ot, 0, 0x1000, color);
        DecalFont_DrawLine("TheRedhotbrwzyz", menuX + 65, yPos, FONT_SMALL, fontColor);

        struct TextureLayout* characterIcon = &gGT->ptrIcons[data.MetaDataCharacters[boards[i].character + i].iconID]->texLayout;

        RECT iconPos = {
            .x = (((PolyTexpage)characterIcon->tpage).x * 64) + (characterIcon->u0 / 4),
            .y = (((PolyTexpage)characterIcon->tpage).y * 256) + characterIcon->v0,
            .w = ((characterIcon->u1 - characterIcon->u0) + 1 )/ 4,
            .h = (characterIcon->v2 - characterIcon->v0) + 1,
        };

        RECT iconClut = {
            .x = ((CLUT)characterIcon->clut).x * 16,
            .y = ((CLUT)characterIcon->clut).y,
            .w = 16,
            .h = 1,
        };

        Saphi_DrawSprite(&iconPos, &iconClut, (Point){menuX + 260, yPos - 1}, ot, 0, FP(0.42), color);

        ElapsedTimeToTotalTime(courseTime, boards[i].time);
        DecalFont_DrawLine(courseTime, menuX + 280, yPos, FONT_SMALL, fontColor);

        int hasIcon = 0;
        int iconID = 0;
        Standard* standards = STANDARDS_ADDR;
        for (int j = 0; i < ICON_MAX; i++)
        {
            if (course)
            {
                if (boards[i].time >= standards[j].course) { break; }

                hasIcon = 1;
                iconID = j;
            }
            else
            {
                if (boards[i].time >= standards[j].lap) { break; }

                hasIcon = 1;
                iconID = j;
            }
        }

        if (hasIcon) { Saphi_DrawCustomIcon(iconID, (Point){menuX + 360, yPos - 1}, ot, 0, FP(0.42), color); }

        if (clutPos.y == 295) { clutPos.x = 32; clutPos.y = 290; }
        else { clutPos.y++; }
        if (i % 2 == 0 || i == NUM_DISPLAY_LEADERBOARDS - 2) { imagePos.y += 10; }
        else { imagePos.x += 8; imagePos.y = 264; }
    }

    Color menuColor = { .r = 0, .g = 0, .b = 0 };
    RECT menu = { .x = menuX, .y = menuY, .w = menuWidth, .h = menuHeight };
    CTR_Box_DrawSolidBox(&menu, &menuColor, ot, primMem);
}

void Saphi_RaceUI()
{
    struct GameTracker* gGT = sdata->gGT;
    struct GamepadBuffer * controller = &sdata->gGamepads->gamepad[0];

    if (controller->buttonsTapped & BTN_SELECT)
    {
        if (showUI) { showUI = 0; gGT->gameMode1 &= ~PAUSE_1; }
        else { showUI = 1; gGT->gameMode1 |= PAUSE_1; }
    }

    if (showUI)
    {
        const int screenCenterX = 256;
        u_long* ot = gGT->pushBuffer_UI.ptrOT;
        struct PrimMem* primMem = &sdata->gGT->backBuffer->primMem;

        if (showUI == SUI_STANDARDS)
        {
            const int menuWidth = 170;
            const int menuHeight = 140;
            const int menuX = screenCenterX - (menuWidth / 2);
            const int menuY = 5;

            DecalFont_DrawLine("Standards", screenCenterX, menuY + 5, FONT_SMALL, JUSTIFY_CENTER | PENTA_WHITE);

            int icons[] = { ICON_HERO, ICON_CHAMPION, ICON_TITAN, ICON_GOD };
            char* standards[] = { "Hero", "Champion", "Titan", "God" };
            Point pos = { .x = menuX + 10, .y = menuY + 20 };
            Color color = { .r = 0x7F, .g = 0x7F, .b = 0x7F };
            Standard* standardTimes = STANDARDS_ADDR;
            for (int i = 0; i < ARR_SIZE(icons); i++)
            {
                char lapTime[11];
                char courseTime[11];
                int fontColor = PLAYER_YELLOW;
                if (i == 1) { fontColor = POLAR_CYAN; }
                if (i == 2) { fontColor = ROO_ORANGE; }
                if (i == 3) { fontColor = SILVER; }
                ElapsedTimeToTotalTime(lapTime, standardTimes[i].lap);
                ElapsedTimeToTotalTime(courseTime, standardTimes[i].course);
                DecalFont_DrawLine(standards[i], menuX + 108, pos.y, FONT_SMALL, JUSTIFY_CENTER | fontColor);
                DecalFont_DrawLine(courseTime, menuX + 55, pos.y + 8 + 3, FONT_SMALL, fontColor);
                DecalFont_DrawLine(lapTime, menuX + 55, pos.y + 16 + 3, FONT_SMALL, fontColor);
                Saphi_DrawCustomIcon(icons[i], pos, ot, 0, 0x1000, color);
                pos.y += 30;
            }

            Color menuColor = { .r = 0, .g = 0, .b = 0 };
            RECT menu = { .x = menuX, .y = menuY, .w = menuWidth, .h = menuHeight };
            CTR_Box_DrawSolidBox(&menu, &menuColor, ot, primMem);
        }
        else if (showUI == SUI_COURSE)
        {
            Saphi_DrawLeaderboard("Course Leaderboard", (LeaderboardEntry*) BOARDS_COURSE_ADDR, 33, true);
        }
        else if (showUI == SUI_LAP)
        {
            Saphi_DrawLeaderboard("Lap Leaderboard", (LeaderboardEntry*) BOARDS_LAP_ADDR, 33, false);
        }

        if (controller->buttonsTapped & BTN_R1)
        {
            showUI += 1;
            if (showUI > SUI_MAX) { showUI = SUI_NONE + 1; }
        }
        else if (controller->buttonsTapped & BTN_L1)
        {
            showUI -= 1;
            if (showUI == SUI_NONE) { showUI = SUI_MAX - 1;}
        }
    }

    UI_RenderFrame_Racing();
}