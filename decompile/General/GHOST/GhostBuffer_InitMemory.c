#include <common.h>

void GhostBuffer_ThTick(struct Thread *);

void GhostBuffer_InitMemory(void)
{
	char i;
	u_short uVar1;
	int iVar2;
	u_int uVar3;
	struct Thread *t;
	struct Instance *inst;
	struct Instance *wakeInst;
	struct Driver *ghostDriver;
	struct Model* wake;
	
	struct GhostHeader* gh;
	struct GhostTape* tape;
	
	struct GameTracker *gGT = sdata->gGT;
	sdata->boolCanSaveGhost = 0;
	sdata->boolGhostsDrawing = 0;

	// only continue if you're in time trial, not main menu, and not cutscene
	if ((gGT->gameMode1 & 0x20022000) != 0x20000) return;
	
	// === Record Buffer ===
	
	gh = MEMPACK_AllocMem(0x3e00/*, "ghost record buffer"*/);
	
	sdata->GhostRecording.ptrGhost = gh;
	sdata->GhostRecording.ptrStartOffset = &gh->recordBuffer[0];
	sdata->GhostRecording.ptrEndOffset = &gh->recordBuffer[0x3DD4];

	// === Play Buffer ===
	// 0: human ghost
	// 1: N Tropy / Oxide ghost

	for (i = 0; i < 2; i++)
	{
		tape = MEMPACK_AllocMem(0x268/*, "ghost tape"*/);
		sdata->ptrGhostTape[i] = tape;

		// first ghost pointer is a ghost loaded by player
		if (i == 0)
		{
			// assign the ghost you loaded
			gh = sdata->ptrGhostTapePlaying;
		}

		// second ghost pointer is n tropy or oxide
		else
		{
			// If you have not beaten N Tropy
			if ((sdata->gameProgress.highScoreTracks[gGT->levelID].timeTrialFlags & 2) == 0)
			{
				// assign n tropy ghost
				gh = gGT->level1->ptrSpawnType1->pointers[4];
			}

			// If you have beaten N Tropy
			else
			{
				// assign oxide ghost
				gh = gGT->level1->ptrSpawnType1->pointers[5];
			}
		}

		tape->gh = gh;
		tape->gh_again = gh;
		tape->constDEADC0ED = 0xDEADC0ED;
		tape->ptrStart = gh->recordBuffer[0];
		tape->ptrEnd = gh->recordBuffer[gh->size];

		// if n tropy / oxide
		if (i == 1)
		{
			gGT->timeToBeatInTimeTrial_ForCurrentEvent = gh->timeElapsedInRace;
		}

		// "ghost"
		// 0x4 = size
		// 0 = no relation to param4
		// 0x100 flag = LargeStackPool
		// 0x2 = ghost thread bucket
		t = THREAD_BirthWithObject(0x40102, GhostBuffer_ThTick, 0, 0);

		// Get the pointer to ghost that is attached to thread
		ghostDriver = t->object;

		// set modelID to "ghost of any kind"
		t->modelIndex = 0x4b;

		// allow this thread to ignore all collisions
		t->flags |= 0x1000;

		// ghost drivers are 0x638 bytes large
		memset(ghostDriver, 0, 0x638);

		// Driver + 0x630 = ghostID
		*(short *)((int)ghostDriver + 0x630) = i;

		// ghost not initialized
		*(short *)((int)ghostDriver + 0x632) = 0;

		ghostDriver->driverID = i + 1;

		// Driver + 0x62C = ptr ghost tape
		*(int *)((int)ghostDriver + 0x62c) = tape;

		uVar3 = VehInit_GetModelByName(data.MetaDataCharacters[data.characterIDs[i]].name_Debug);

		uVar3 = INSTANCE_Birth3D(uVar3, 0, t);

		// give instance to thread
		t->inst = uVar3;

		// Ptr Model "Wake"
		wake = gGT->modelPtr[0x43];

		// if "Wake" model exists
		if (wake)
		{
			wakeInst = INSTANCE_Birth3D(wake, 0, 0);
			ghostDriver->wakeInst = wakeInst;

			if (wakeInst != 0)
			{
				// make invisible, set to anim 1
				wakeInst->flags |= 0x90;
			}
		}

		inst = t->inst;
		inst->unk51 = 0xc;
		inst->flags |= 0x4000000;

		ghostDriver->instSelf = inst;

		VehInit_TireSprites(ghostDriver);
		VehInit_SetConsts(ghostDriver);

		// driver is an AI
		ghostDriver->actionsFlagSet |= 0x100000;

		// pointer to TrTire, for transparent tires
		ghostDriver->wheelSprites = &gGT->iconGroup[0xc]->icons[0];
	}
		
	return;
}
