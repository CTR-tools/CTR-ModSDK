#include <common.h>

void GhostBuffer_ThTick(struct Thread *);

void GhostBuffer_InitMemory(void)
{
	char i;
	ushort uVar1;
	int iVar2;
	u_int uVar3;
	struct Thread *t;
	struct Instance *inst;
	struct Instance *wakeInst;
	struct Driver *ghostDriver;
	struct Model* wake;
	int *piVar7;
	
	struct GameTracker *gGT = sdata->gGT;

	// bool canSaveGhost
	sdata->boolCanSaveGhost = 0;

	// no ghosts are drawing
	sdata->boolGhostsDrawing = 0;

	// if you're in time trial, not main menu, and not laoding.
	// basically, if you're in time trial gameplay
	if ((gGT->gameMode1 & 0x20022000) == 0x20000)
	{
		// Allocate room to record a new ghost

		sdata->GhostRecording.ptrGhost = MEMPACK_AllocMem(0x3e00, "ghost record buffer");

		// First 0x28 bytes are a header

		// pointer to start of recording
		sdata->GhostRecording.ptrStartOffset = (int)sdata->GhostRecording.ptrGhost + 0x28;

		// pointer to end of recording
		sdata->GhostRecording.ptrEndOffset = (int)sdata->GhostRecording.ptrGhost + 0x3df;

		// Allocate room for two ghost tapes,
		// one for N Tropy / Oxide
		// one for a previously saved player Ghost
		for (i = 0; i < 2; i++)
		{
			// MEMPACK_AllocMem
			piVar7 = (int *)MEMPACK_AllocMem(0x268, "ghost tape");

			// set pointer to this ghost tape (array of two)
			data.ptrGhostTape[i] = piVar7;

			// first ghost pointer is a ghost loaded by player
			if (i == 0)
			{
				// assign the ghost you loaded
				piVar7[0x99] = sdata->ptrGhostTapePlaying;
			}

			// second ghost pointer is n tropy or oxide
			else
			{
				if (i == 1)
				{
					// If you have not beaten N Tropy
					if ((sdata->gameProgress.highScoreTracks[gGT->levelID].timeTrialFlags & 2) == 0)
					{
						// assign n tropy ghost
						piVar7[0x99] = gGT->level1->ptrSpawnType1->pointers[4];
					}

					// If you have beaten N Tropy
					else
					{
						// assign oxide ghost
						piVar7[0x99] = gGT->level1->ptrSpawnType1->pointers[5];
					}
				}
			}

			// ghostTape->0x0 = ptrGhostHeader
			iVar2 = piVar7[0x99];
			*piVar7 = iVar2;

			// ghostTape->ptrStart = ptrGhostHeader->0x28
			piVar7[1] = iVar2 + 0x28;
			
			// size = ptrGhostHeader->size
			uVar1 = *(u_short *)(iVar2 + 2);
			
			// 0xDEADC0ED
			piVar7[0x98] = -0x21523f13;
			
			// ghostTape->ptrEnd = ptrGhostHeader->0x28 + size
			piVar7[2] = iVar2 + 0x28 + (u_int)uVar1;

			// only do this one time in a loop that executes twice,
			// first ghost (index zero) is a ghost made by the player,
			// second ghost (index one) is N Tropy or Oxide
			if (i == 1)
			{
				// ptrGhostHeader->timeElapsedInRace
				gGT->timeToBeatInTimeTrial_ForCurrentEvent = *(u_int *)(*piVar7 + 0x10);
			}
		}

		// Initialize two ghost tapes,
		// one for N Tropy / Oxide
		// one for a previously saved player Ghost
		for (i = 0; i < 2; i++)
		{
			// "ghost"
			// 0x4 = size
			// 0 = no relation to param4
			// 0x100 flag = LargeStackPool
			// 0x2 = ghost thread bucket
			t = THREAD_BirthWithObject(0x40102, GhostBuffer_ThTick, sdata->s_ghost, 0);

			// Get the pointer to ghost that is attached to thread
			ghostDriver = t->object;

			// set modelID to "ghost of any kind"
			t->modelIndex = 0x4b;

			// allow this thread to ignore all collisions
			t->flags |= 0x1000;

			// ghost drivers are 0x638 bytes large
			memset(ghostDriver, 0, 0x638);

			// Driver + 0x630 = ghostID
			*(short *)(ghostDriver + 0x18c) = i;

			// ghost not initialized
			*(short *)((int)ghostDriver + 0x632) = 0;

			ghostDriver->driverID = i + 1;

			// Driver + 0x62C = ptr ghost tape
			*(int *)((int)ghostDriver + 0x62c) = sdata->ptrGhostTape[i];

			uVar3 = Driver_SearchModelByString(data.MetaDataCharacters[data.characterIDs[i + 1]].name_Debug);

			uVar3 = INSTANCE_Birth3D(uVar3, uVar3, t);

			// give instance to thread
			t->inst = uVar3;

			// Ptr Model "Wake"
			wake = gGT->modelPtr[0x43];

			// if "Wake" model exists
			if (wake)
			{
				//  -- ptrModel, name, thread
				wakeInst = INSTANCE_Birth3D(wake, wake, 0);

				// offset 0x4f8
				// ptrInstance Wake
				ghostDriver->wakeInst = wakeInst;

				// if wake exists
				if (wakeInst != 0)
				{
					// make invisible, set to anim 1
					wakeInst->flags |= 0x90;
				}
			}

			// get instance from thread
			inst = t->inst;

			inst->unk51 = 0xc;

			inst->flags |= 0x4000000;

			ghostDriver->instSelf = inst;

			// initialize tire data
			VehInit_TireSprites();

			// set stats, based on driver engine
			VehInit_SetConsts(ghostDriver);

			// driver is an AI
			ghostDriver->actionsFlagSet |= 0x100000;

			// pointer to TrTire, for transparent tires then to its wheelSprites
			ghostDriver->wheelSprites = gGT->ptrIcons[0xc]->texLayout.u0;
		}
	}
	return;
}
