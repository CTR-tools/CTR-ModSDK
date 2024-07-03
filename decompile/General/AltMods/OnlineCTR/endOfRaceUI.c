#include <common.h>
#include "global.h"

int currCam;
int bestCourseIndex;
int bestLapIndex;

static void SetNextCamera(bool increase)
{
	int driverCount = octr->NumDrivers;
	while (true)
	{
		currCam = increase ? (currCam + 1) % driverCount : (currCam + driverCount - 1) % driverCount;
		if (octr->nameBuffer[currCam][0])
		{
			sdata->gGT->cameraDC[0].driverToFollow = sdata->gGT->drivers[currCam];
			return;
		}
	}
}

void EndOfRace_Camera()
{
    const char s_switchCam[] = "Press R1 or L1 to change the camera";
	DECOMP_DecalFont_DrawLine(s_switchCam, 0x100, 5, FONT_SMALL, JUSTIFY_CENTER | ORANGE);

	struct GamepadBuffer * pad = &sdata->gGamepads->gamepad[0];
	if (pad->buttonsTapped & BTN_R1) { SetNextCamera(true); }
	if (pad->buttonsTapped & BTN_L1) { SetNextCamera(false); }
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
    char s_time[15];
    TotalTime tt;
    const int playersPerRow = 4;
    const int rectSpace = 5;
    const int iconSpacing = 126;
    const int iconHeight = 28;
    const int xStart = 0;
    const int yStart = 20;
    const int scale = FP(1);
    int playersFinished = 0;
    int rectHeightMultiplier = 1;
    Point pos = MakePoint(xStart, yStart);
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
        ElapsedTimeToTotalTime(&tt, octr->raceStats[i].finalTime);
        if (tt.hours > 0)
        {
            sprintf(s_time, "%d:%02d:%02d", tt.hours, tt.minutes, tt.seconds);
        }
        else
        {
            sprintf(s_time, "%d:%02d.%03d", tt.minutes, tt.seconds, tt.miliseconds);
        }
        DECOMP_DecalFont_DrawLine(s_time, pos.x + 38, pos.y + 8 + 1, FONT_SMALL, index == bestCourseIndex ? TINY_GREEN : WHITE);
        ElapsedTimeToTotalTime(&tt, octr->raceStats[i].bestLap);
        tt.minutes = min(tt.minutes, 9);
        sprintf(s_time, "%d:%02d.%03d", tt.minutes, tt.seconds, tt.miliseconds);
        DECOMP_DecalFont_DrawLine(s_time, pos.x + 38, pos.y + 16 + 1, FONT_SMALL, index == bestLapIndex ? TINY_GREEN : WHITE);
        DECOMP_UI_DrawDriverIcon(icon, pos, sdata->gGT->pushBuffer_UI.ptrOT, 1, scale, MakeColor(0x80, 0x80, 0x80));

        pos.x += iconSpacing;
        playersFinished++;
        if (playersFinished == playersPerRow)
        {
            pos.x = xStart;
            pos.y += iconHeight;
        }
        else if (playersFinished > playersPerRow) { rectHeightMultiplier = 2; }
    }
    const RECT bgRect = {.x = 0, .y = yStart - rectSpace, .w = 512, .h = rectSpace * 2 + iconHeight * rectHeightMultiplier - 3};
    DECOMP_RECTMENU_DrawInnerRect(&bgRect, 0, sdata->gGT->backBuffer->otMem.startPlusFour);
}