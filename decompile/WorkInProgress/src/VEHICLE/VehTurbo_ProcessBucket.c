#include <common.h>

void DECOMP_VehTurbo_ProcessBucket(struct Thread* turboThread)
{
	u_short temp2;
	u_int temp4;
	struct Instance* driverInstance;
	struct Instance* inst;
	struct Turbo* turbo;
	
	char numPlyr = sdata->gGT->numPlyrCurrGame;

	// if first thread is valid
	if (turboThread != NULL)
	{
		// loop through all threads
		do
		{
			inst = turboThread->inst;
			turbo = turboThread->object;
			driverInstance = turbo->driver->instSelf;

			if (numPlyr) 
			{
				// each InstDrawPerPlayer
				for (char i = 0; i < numPlyr; i++)
				{
					temp4 = driverInstance->idpp[i].instFlags;
					// judging by 0x28 being copied to 0xb8 ?
					if ((temp4 & 0x100) == 0)
					{
						// flags
						turbo->inst->idpp[i].instFlags &= (temp4 | 0xffffffbf);
						inst->idpp[i].instFlags &= (temp4 | 0xffffffbf);
				
						temp4 = driverInstance->idpp[i].unkE4[0];
						inst->idpp[i].unkE4[0] = temp4;
						turbo->idpp[i].unkE4[0] = temp4;
						temp4 = driverInstance->idpp[i].unkE4[4];
						inst->idpp[i].unkE4[4] = temp4;
						turbo->idpp[i].unkE4[4] = temp4;

						temp2 = driverInstance->idpp[i].unkDC[0];
						inst->idpp[i].unkDC[0] = temp2;
						turbo->idpp[i].unkDC[0] = temp2;
						temp2 = driverInstance->idpp[i].unkDC[1];
						inst->idpp[i].unkDC[1] = temp2;
						turbo->idpp[i].unkDC[1] = temp2;
					}
				}
			}
		// go to next thread
	 	turboThread = turboThread->siblingThread;
		} while (turboThread != NULL);
	}
}