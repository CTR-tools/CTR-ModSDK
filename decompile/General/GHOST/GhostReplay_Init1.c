#include <common.h>

void GhostReplay_ThTick(struct Thread *);

void GhostReplay_Init1(void)
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
	int timeTrialFlags;
	
	struct GhostHeader* gh;
	struct GhostTape* tape;
	int charID;
	char* recordBuffer;
	
	struct GameTracker *gGT = sdata->gGT;
	
	// This has to run from MainInit_Drivers
	sdata->boolCanSaveGhost = 0;
	sdata->boolGhostsDrawing = 0;

	// only continue if you're in time trial, not main menu, and not cutscene
	if ((gGT->gameMode1 & 0x20022000) != 0x20000) return;
	
	// === Record Buffer ===
	
	// In the future, this can move to GhostTape_Start, when byte budget allows
	
	gh = MEMPACK_AllocMem(0x3e00/*, "ghost record buffer"*/);
	recordBuffer = GHOSTHEADER_GETRECORDBUFFER(gh);
	sdata->GhostRecording.ptrGhost = gh;
	sdata->GhostRecording.ptrStartOffset = &recordBuffer[0];
	sdata->GhostRecording.ptrEndOffset = &recordBuffer[0x3DD4];

	// === Replay Buffer ===
	// 0: human ghost
	// 1: N Tropy / Oxide ghost

	for (i = 0; i < 2; i++)
	{
		tape = MEMPACK_AllocMem(0x268/*, "ghost tape"*/);
		sdata->ptrGhostTape[i] = tape;

		// first ghost pointer is a ghost loaded by player
		if (i == 0)
		{
			// if not playing a human ghost, skip this ghost
			if (sdata->boolReplayHumanGhost == 0) continue;
			
			// assign the ghost you loaded
			gh = sdata->ptrGhostTapePlaying;
			
			charID = 1;
		}

		// second ghost pointer is n tropy or oxide
		else
		{
			timeTrialFlags = sdata->gameProgress.highScoreTracks[gGT->levelID].timeTrialFlags;
			
			// if not opened N Tropy, skip this ghost
			if ((timeTrialFlags & 1) == 0) continue;
			
			// If you have not beaten N Tropy
			if ((timeTrialFlags & 2) == 0)
			{
				// assign n tropy ghost
				gh = gGT->level1->ptrSpawnType1->pointers[4];
				
				charID = 2;
			}

			// If you have beaten N Tropy
			else
			{
				// assign oxide ghost
				gh = gGT->level1->ptrSpawnType1->pointers[5];
				
				charID = 3;
			}
		}
		
		sdata->boolGhostsDrawing = 1;
		recordBuffer = GHOSTHEADER_GETRECORDBUFFER(gh);

		tape->gh = gh;
		tape->gh_again = gh;
		tape->constDEADC0ED = 0xDEADC0ED;
		tape->ptrStart = &recordBuffer[0];
		tape->ptrEnd = &recordBuffer[gh->size];
		tape->ptrCurr = tape->ptrStart;
		tape->timeElapsedInRace = 0;
		tape->timeInPacket32_backup = 0;
		tape->unk20 = 0;
		tape->timeInPacket01 = 0;
		tape->timeInPacket32 = 0;

		// if n tropy / oxide
		if (i == 1)
		{
			gGT->timeToBeatInTimeTrial_ForCurrentEvent = gh->timeElapsedInRace;
		}

		// characterID and model
		charID = data.characterIDs[charID];
		uVar3 = VehInit_GetModelByName(data.MetaDataCharacters[charID].name_Debug);

		inst = INSTANCE_Birth3D(uVar3, 0, 0);
		inst->unk51 = 0xc;
		inst->flags = 7;

		// "ghost"
		// 0x4 = size
		// 0 = no relation to param4
		// 0x100 flag = LargeStackPool
		// 0x2 = ghost thread bucket
		t = THREAD_BirthWithObject(0x40102, GhostReplay_ThTick, 0, 0);
		t->modelIndex = 0x4b;	// ghost
		t->flags |= 0x1000;		// ignore collisions
		
		t->inst = inst;
		inst->thread = t;
		
		// ghost drivers are 0x638 bytes large
		ghostDriver = t->object;
		memset(ghostDriver, 0, 0x638);
		ghostDriver->ghostID = i;
		ghostDriver->driverID = i + 1;
		ghostDriver->ghostBoolInit = 1;
		ghostDriver->ghostBoolStarted = 0;
		ghostDriver->ghostTape = tape;
		ghostDriver->instSelf = inst;
		ghostDriver->actionsFlagSet |= 0x100000; // AI driver

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

		VehInit_TireSprites(t);
		VehInit_SetConsts(ghostDriver);
		
		if(charID == 0xF)
			ghostDriver->wheelSize = 0;

		// pointer to TrTire, for transparent tires
		ghostDriver->wheelSprites = ICONGROUP_GETICONS(&gGT->iconGroup[0xc]);
		
		// advance ghost by one frame,
		// just so Oxide doesn't block your view
		GhostReplay_ThTick(t);
	}
		
	return;
}
