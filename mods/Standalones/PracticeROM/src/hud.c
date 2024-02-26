#include "../p_rom.h"

#define NumbersToString Torch_Subset1
#define SaveState Torch_Subset4
#define LoadState Torch_Subset7 // can potentially move back to subset6

// String variables
unsigned char speedVal[numSpeedColor] = {151, 165, 175, 185, 196, 207, 218, 229, 240, 255};
int speedColorVal[numSpeedColor] = {FOREST_GREEN, TINY_GREEN, PAPU_YELLOW, ROO_ORANGE, RED, COCO_MAGENTA, N_GIN_PURPLE, PURA_VIOLET, CRASH_BLUE, POLAR_CYAN};

char s_numbers[] = " 0000";
char s_checkpointStr[] = "Check:";
char s_progressStr[] = "Progr:";

force_inline int Div10(int value)
{
	return (value / 10);
}

void DrawDebugString()
{
	int i;
	int speedColor = SILVER;
    int turboColor = FOREST_GREEN;
    int turboFill = 0;
	struct Driver* driver = sdata->gameTracker.drivers[0];
	int xSpeed = driver->xSpeed;
	int zSpeed = zSpeed = driver->zSpeed;
	int progress = driver->distanceToFinish_curr;
	int checkpoint = driver->distanceToFinish_checkpoint;
	int speed = MATH_FastSqrt((xSpeed * xSpeed) + (zSpeed * zSpeed), 0);

    for (i = 0; i < numSpeedColor; i++)
	{
		if (speed < (int)speedVal[i]*100)
		{
			speedColor = speedColorVal[i];
			break;
		}
	}
    
    if ((driver->kartState == KS_DRIFTING) || (driver->kartState == KS_ENGINE_REVVING))
    {
        turboFill = (960 - driver->turbo_MeterRoomLeft);

        if (turboFill >= 480)
            turboColor = RED;
    }

	DecalFont_DrawLine(s_progressStr, x_progressStr, y_progressStr, FONT_SMALL, PERIWINKLE);
	DecalFont_DrawLine(s_checkpointStr, x_checkpointStr, y_checkpointStr, FONT_SMALL, PERIWINKLE);
	DecalFont_DrawLine(p_rom->currEngine, x_engine, y_engine, FONT_SMALL, PERIWINKLE);

	NumbersToString(s_numbers, Div10(driver->reserves), 4);
	DecalFont_DrawLine(s_numbers, x_reserves, y_reserves, FONT_SMALL, DINGODILE_OLIVE);

    NumbersToString(s_numbers, Div10(turboFill), 4);
	DecalFont_DrawLine(s_numbers, 360, 200, FONT_SMALL, turboColor);

	NumbersToString(s_numbers, Div10(driver->turnAngleCurr), 4);
	DecalFont_DrawLine(s_numbers, 240, y_checkpoint, FONT_SMALL, (DINGODILE_OLIVE | JUSTIFY_CENTER));

	NumbersToString(s_numbers, Div10(driver->axisRotationY), 4);
	DecalFont_DrawLine(s_numbers, x_progressStr, 114, FONT_SMALL, (DINGODILE_OLIVE | JUSTIFY_CENTER));
	
	NumbersToString(s_numbers, Div10(speed), 4);
	DecalFont_DrawLine(s_numbers, x_speed, y_speed, FONT_BIG, speedColor);
	
	NumbersToString(s_numbers, Div10(progress), 5);
	DecalFont_DrawLine(s_numbers, x_progress, y_progress, FONT_SMALL, PERIWINKLE);
	
	NumbersToString(s_numbers, Div10(checkpoint), 5);
	DecalFont_DrawLine(s_numbers, x_checkpoint, y_checkpoint, FONT_SMALL, PERIWINKLE);
}