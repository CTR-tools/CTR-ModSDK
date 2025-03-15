#include "utils.h"

void GhostReplay_ThTick(struct Thread *);

void GhostReplay_Init(void)
{
#ifdef DISABLE_GHOSTS
	return;
#else DISABLE_GHOSTS
	char i;
	u_short uVar1;
	int iVar2;
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

	// ALWAYS initialize ghost threads
	// even if gh == 0, or else the text
	// for "Ghost Too Big" will never play
	gh = 0;
	charID = 0;

	for (i = 0; i < 2; i++)
	{
		tape = MEMPACK_AllocMem(0x268/*, "ghost tape"*/);
		sdata->ptrGhostTape[i] = tape;

		// first ghost pointer is a ghost loaded by player
		if (i == 0)
		{
			// if ghost is playing, initialize ghost
			if (sdata->boolReplayHumanGhost != 0)
			{
				// assign the ghost you loaded
				gh = sdata->ptrGhostTapePlaying;

				charID = 1;
			}

			// if no human ghost is replayed, do NOT
			// "return", the ghost[0] thread must be
			// initialized, or else the "Ghost Too Big"
			// text will not play from GhostReplay_ThTick
		}

		// second ghost pointer is n tropy or oxide
		else
		{
			timeTrialFlags = sdata->gameProgress.highScoreTracks[gGT->levelID].timeTrialFlags;

			// No ghost unlocked or no ghost in the map file
			if ((timeTrialFlags & 1) == 0 || gGT->level1->ptrSpawnType1->count == 0)
			{
				// skip initialization of ghost[1] thread
				return;
			}

			// if N Tropy Opened
			else
			{
				void** pointers = ST1_GETPOINTERS(gGT->level1->ptrSpawnType1);

				// If you have not beaten N Tropy
				if ((timeTrialFlags & 2) == 0)
				{
                    if (pointers[ST1_NTROPY] == NULL) { return; }
					gh = pointers[ST1_NTROPY];
					charID = 2;
				}

				// If you have beaten N Tropy
				else
				{
                    if (pointers[ST1_NOXIDE] == NULL) { return; }
					gh = pointers[ST1_NOXIDE];
					charID = 3;
				}
			}
		}

		sdata->boolGhostsDrawing = 1;
		recordBuffer = GHOSTHEADER_GETRECORDBUFFER(gh);

		// Signals GhostReplay_ThTick to return
		// early, and not try to "play" the ghost
		tape->ptrStart = 0;
		tape->ptrEnd = 0;

		if (gh != 0)
		{
			tape->ptrStart = &recordBuffer[0];
			tape->ptrEnd = &recordBuffer[gh->size];
		}

		tape->gh = gh;
		tape->gh_again = gh;
		tape->constDEADC0ED = 0xDEADC0ED;
		tape->ptrCurr = tape->ptrStart;
		tape->timeElapsedInRace = 0;
		tape->timeInPacket32_backup = 0;
		tape->unk20 = 0;
		tape->timeInPacket01 = 0;
		tape->timeInPacket32 = 0;

		// if n tropy / oxide
		if (i == 1)
		{
			// guaranteed gh != 0, so dont nullptr check
			gGT->timeToBeatInTimeTrial_ForCurrentEvent = gh->timeElapsedInRace;
		}

		// characterID and model
		charID = data.characterIDs[charID];

		struct Model* model = VehBirth_GetModelByName(data.MetaDataCharacters[charID].name_Debug);

		inst = INSTANCE_Birth3D(model, NULL, NULL);
		inst->unk51 = 0xc;
		inst->flags = 7;

		t = PROC_BirthWithObject(

			// creation flags
			SIZE_RELATIVE_POOL_BUCKET(
				4, NONE, LARGE, GHOST
			),

			GhostReplay_ThTick,
			0,
			0
		);

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

		VehBirth_TireSprites(t);
		VehBirth_SetConsts(ghostDriver);

		if(charID == 0xF)
			ghostDriver->wheelSize = 0;

		// pointer to TrTire, for transparent tires
		ghostDriver->wheelSprites = ICONGROUP_GETICONS(gGT->iconGroup[0xc]);

		// advance ghost by one frame,
		// just so Oxide doesn't block your view
		GhostReplay_ThTick(t);
	}
#endif
}
