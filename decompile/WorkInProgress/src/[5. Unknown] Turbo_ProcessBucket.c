#include <common.h>

// Turbo_ProcessBucket
void DECOMP_Turbo_ProcessBucket(struct Thread* turboThread)
{
	u_short uVar1;
	int driverInstance;
	u_int uVar5;
	struct Instance* threadInstance;
	struct Instance* objectInstance;
	struct GameTracker* gameTracker;
	int i;

	gameTracker = sdata->gGT;
	// if first thread is valid
	if (turboThread != 0)
	{
		// loop through all threads
		do
		{
			

			// get instance from thread
			threadInstance = turboThread->inst;

			// get object from thread
			objectInstance = ((struct Turbo*)turboThread->object)->inst;

			// object -> driver -> instSelf
			driverInstance = ((struct Turbo*)turboThread->object)->driver->instSelf;

			i = 0;

			// numPlyrCurrGame is not zero
			if (gameTracker->numPlyrCurrGame > 0) 
			{
				// each InstDrawPerPlayer
				// for i = 0; i < numPlyrCurrGame; i++
				do
				{
					// if tileView does not exist ?
					// judging by 0x28 being copied to 0xb8 ?
					if ((*(u_int *)&driverInstance->idpp.data[0][0x40] & 0x100) == 0)
					{
						// flags
						*(u_int *)&objectInstance->inst->idpp.data[0][0x40] = *(u_int *)&objectInstance->inst->idpp.data[0][0x40] & (driverInstance->idpp.data[0][0x40] | 0xffffffbf);
						*(u_int *)&threadInstance->inst->idpp.data[0][0x40] = *(u_int *)&threadInstance->inst->idpp.data[0][0x40] & (driverInstance->idpp.data[0][0x40] | 0xffffffbf);
				
						uVar5 = *(u_int *)&driverInstance->idpp.data[0][0x6c];
						*(u_int *)&threadInstance->idpp.data[0][0x6c] = uVar5;
						*(u_int *)&objectInstance->idpp.data[0][0x6c] = uVar5;
						uVar5 = *(u_int *)&driverInstance->idpp.data[0][0x70];
						*(u_int *)&threadInstance->idpp.data[0][0x6c] = uVar5;
						*(u_int *)&objectInstance->idpp.data[0][0x6c] = uVar5;
						uVar1 = *(u_short *)&driverInstance->idpp.data[0][0x64];
						*(u_short *)&threadInstance->idpp.data[0][0x64] = uVar1;
						*(u_short *)&objectInstance->idpp.data[0][0x64] = uVar1;
						uVar1 = *(u_short *)&driverInstance->idpp.data[0][0x66];
						*(u_short *)&threadInstance->idpp.data[0][0x66] = uVar1;
						*(u_short *)&objectInstance->idpp.data[0][0x66] = uVar1;
					}
			
					// InstDrawPerPlayer
					threadInstance = (int)threadInstance + 0x88;
					objectInstance = (int)objectInstance + 0x88;
					i = i + 1;
					driverInstance = (int)driverInstance + 0x88;
			
				} while (i < gameTracker->numPlyrCurrGame);
			}

		// go to next thread

		// thread = thread->sibling
	 	turboThread = turboThread->siblingThread;

		} while (turboThread != 0);
	}
	return;
}