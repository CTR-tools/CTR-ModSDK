#include <common.h>

void DECOMP_BOTS_ThTick_RevEngine(struct Thread* botThread)
{
	struct Driver* botDriver = (struct Driver*)botThread->object;
	struct MaskHeadWeapon* mask = botDriver->botData.maskObj;

	if (botDriver->botData.ai_posBackup[1] < botDriver->posCurr.y)
	{ //mask grabbed
		botDriver->posCurr.y -= ((sdata->gGT->elapsedTimeMS << 9) >> 5);

		if (mask != NULL)
		{
			mask->pos[0] = (short)(botDriver->posCurr.x >> 8);
			mask->pos[1] = (short)(botDriver->posCurr.y >> 8);
			mask->pos[2] = (short)(botDriver->posCurr.z >> 8);
		}

		VehPhysForce_TranslateMatrix(botThread, botDriver);
		VehFrameProc_Driving(botThread, botDriver);
		VehEmitter_DriverMain(botThread, botDriver);
	}
	else
	{ //not a mask grab
		if (mask != NULL)
		{
			mask->scale = 0x1000;
			mask->duration = 0;
			mask->rot[2] &= 0xfffe;
		}

		botDriver->botData.maskObj = NULL;
		botDriver->kartState = KS_ENGINE_REVVING;
		botDriver->clockReceive = 0;
		botDriver->squishTimer = 0;

		ThTick_SetAndExec(botThread, BOTS_ThTick_Drive);
	}
}