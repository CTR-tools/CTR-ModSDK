#include <common.h>
#define RANDOM_MODE 1

extern short newPads[];

void AH_WarpPad_ThTick(struct Thread *t);
void AH_WarpPad_ThDestroy(struct Thread *t);

void AH_WarpPad_LInB(struct Instance *inst)
{
	int i;
	int levelID;
	short swap;
	struct Thread *t;
	struct WarpPad *warppadObj;

	struct GameTracker *gGT;

	int unlockItem_numOwned;
	int unlockItem_numNeeded;
	int unlockItem_modelID;

	int *arrTokenCount;
	short *arrKeysNeeded;
	struct Instance *newInst;

	short *battleTrackArr;

	gGT = sdata->gGT;

	t =
		PROC_BirthWithObject(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET(
				sizeof(struct WarpPad),
				NONE,
				MEDIUM,
				WARPPAD),

			AH_WarpPad_ThTick, // behavior
			0,				   // debug name
			0				   // thread relative
		);

	if (t == 0)
		return;
	inst->thread = t;
	t->inst = inst;

	t->funcThDestroy = AH_WarpPad_ThDestroy;

	// 0 - locked
	// 1 - open for trophy
	// 2 - unlocked all
	// 3 - open for relic/token
	// 4 - purple token or SlideCol/TurboTrack

	// locked
	t->modelIndex = 0;

	// make invisible
	// this is the red triangle
	// instance from DCxDemo's LEV Viewer
	inst->flags |= 0x80;

	warppadObj = t->object;
	warppadObj->levelID = 0;
	warppadObj->boolEnteredWarppad = 0;
	warppadObj->framesWarping = 0;

	for (i = 0; i < WPIS_NUM_INSTANCES; i++)
		warppadObj->inst[i] = 0;

	// each warppad has a name "warppad#xxx"
	// "warppad#0" is dingo canyon, level ID 0
	// "warppad#16" is slide col, level ID 16
	// "warppad#102" is gem cup 2
	// "warppad#104" is gem cup 4
	// etc

	levelID = 0;
	for (i = 8; inst->name[i] != 0; i++)
	{
		levelID = levelID * 10 + inst->name[i] - '0';
	}

	swap = (levelID > 22) ? newPads[levelID - 79] : newPads[levelID];

	warppadObj->levelID = levelID;

	if (RANDOM_MODE)
		warppadObj->levelID = swap;

	unlockItem_numNeeded = -1;

	// Trophy Track
	if (levelID < 0x10)
	{
		// if trophy owned
		if (CHECK_ADV_BIT(sdata->advProgress.rewards, (swap + 6)) != 0)
		{
		GetKeysRequirement:
			arrKeysNeeded = (short*)0x800b4e7c;

			// keys needed to unlock track again
			unlockItem_modelID = 99;
			unlockItem_numOwned = gGT->currAdvProfile.numKeys;
			unlockItem_numNeeded = arrKeysNeeded[gGT->levelID - 0x19];
		}

		// if trophy not owned
		else
		{
			// number trophies needed to open
			unlockItem_modelID = 0x62;
			unlockItem_numOwned = gGT->currAdvProfile.numTrophies;
			unlockItem_numNeeded = data.metaDataLEV[levelID].numTrophiesToOpen;
		}
	}

	else if (levelID == SLIDE_COLISEUM)
	{
		// number relics needed to open
		unlockItem_modelID = 0x61;
		unlockItem_numOwned = gGT->currAdvProfile.numRelics;
		unlockItem_numNeeded = 10;
	}

	else if (levelID == TURBO_TRACK)
	{
		// number gems needed to open
		unlockItem_modelID = 0x5f;
		unlockItem_numNeeded = 5;

		// count number of gems owned
		unlockItem_numOwned = 0;
		for (i = 0; i < 5; i++)
			if (CHECK_ADV_BIT(sdata->advProgress.rewards, (i + 0x6a)) != 0)
				unlockItem_numOwned++;
	}

	// battle maps
	else if (levelID < GEM_STONE_VALLEY)
	{
		goto GetKeysRequirement;
	}

	// gem cups
	else
	{
		// number tokens needed to open
		unlockItem_modelID = 0x7d;
		unlockItem_numNeeded = 4;

		arrTokenCount = &gGT->currAdvProfile.numCtrTokens.red;
		unlockItem_numOwned = arrTokenCount[levelID - 100];
	}

	// if unlocked
	if (unlockItem_numOwned >= unlockItem_numNeeded)
	{
		warppadObj->digit1s = 0;

		// if beam model exists
		if (gGT->modelPtr[0x7B] != 0)
		{
			newInst = INSTANCE_Birth3D(gGT->modelPtr[0x7B], 0, t);

			// copy matrix
			*(int *)((int)&newInst->matrix + 0x0) = *(int *)((int)&inst->matrix + 0x0);
			*(int *)((int)&newInst->matrix + 0x4) = *(int *)((int)&inst->matrix + 0x4);
			*(int *)((int)&newInst->matrix + 0x8) = *(int *)((int)&inst->matrix + 0x8);
			*(int *)((int)&newInst->matrix + 0xC) = *(int *)((int)&inst->matrix + 0xC);
			*(short *)((int)&newInst->matrix + 0x10) = *(short *)((int)&inst->matrix + 0x10);
			newInst->matrix.t[0] = inst->matrix.t[0];
			newInst->matrix.t[1] = inst->matrix.t[1];
			newInst->matrix.t[2] = inst->matrix.t[2];

			newInst->alphaScale = 0xc00;

			warppadObj->inst[WPIS_OPEN_BEAM] = newInst;
		}

		// if spiral ring exists
		if (gGT->modelPtr[0x7C] != 0)
		{
			for (i = 0; i < 2; i++)
			{
				newInst = INSTANCE_Birth3D(gGT->modelPtr[0x7C], 0, t);

				// copy matrix
				*(int *)((int)&newInst->matrix + 0x0) = *(int *)((int)&inst->matrix + 0x0);
				*(int *)((int)&newInst->matrix + 0x4) = *(int *)((int)&inst->matrix + 0x4);
				*(int *)((int)&newInst->matrix + 0x8) = *(int *)((int)&inst->matrix + 0x8);
				*(int *)((int)&newInst->matrix + 0xC) = *(int *)((int)&inst->matrix + 0xC);
				*(short *)((int)&newInst->matrix + 0x10) = *(short *)((int)&inst->matrix + 0x10);
				newInst->matrix.t[0] = inst->matrix.t[0];
				newInst->matrix.t[1] = inst->matrix.t[1] + i * 0x400;
				newInst->matrix.t[2] = inst->matrix.t[2];

				newInst->alphaScale = 0x400;

				warppadObj->inst[WPIS_OPEN_RING1 + i] = newInst;
			}
		}

		for (i = 0; i < 3; i++)
			warppadObj->thirds[i] = 0x555 * i;

		warppadObj->spinRot_Prize[0] = 0;
		warppadObj->spinRot_Prize[1] = 0;
		warppadObj->spinRot_Prize[2] = 0;

		warppadObj->spinRot_Beam[0] = 0;
		warppadObj->spinRot_Beam[1] = 0;
		warppadObj->spinRot_Beam[2] = 0;

		for (i = 0; i < 2; i++)
		{
			warppadObj->spinRot_Wisp[i][0] = 0;
			warppadObj->spinRot_Wisp[i][1] = 0;
			warppadObj->spinRot_Wisp[i][2] = 0;
		}

		if (levelID < 0x10)
		{
			// unlocked all
			t->modelIndex = 2;

			// if trophy not owned
			if (CHECK_ADV_BIT(sdata->advProgress.rewards, (swap + 6)) == 0)
			{
				// open for trophy
				t->modelIndex = 1;

				newInst = INSTANCE_Birth3D(gGT->modelPtr[0x62], 0, t);

				newInst->scale[0] = 0x2800;
				newInst->scale[1] = 0x2800;
				newInst->scale[2] = 0x2800;

				warppadObj->inst[WPIS_OPEN_PRIZE1] = newInst;
			}

			// if token not owned
			if (CHECK_ADV_BIT(sdata->advProgress.rewards, (swap + 0x4c)) == 0)
			{
				// open for relic/token
				if (t->modelIndex != 1)
					t->modelIndex = 3;
			BattleTrack:
				newInst = INSTANCE_Birth3D(gGT->modelPtr[0x7D], 0, t);

				// specular lighting
				newInst->flags |= 0x30000;

				newInst->scale[0] = 0x2000;
				newInst->scale[1] = 0x2000;
				newInst->scale[2] = 0x2000;

				i = data.metaDataLEV[swap].ctrTokenGroupID;

				// token color
				newInst->colorRGBA =
					((unsigned int)data.AdvCups[i].color[0] << 0x14) |
					((unsigned int)data.AdvCups[i].color[1] << 0xc) |
					((unsigned int)data.AdvCups[i].color[2] << 0x4);

				// === Naughty Dog Bug ===
				// They made an array where every token color
				// could have it's own specular light, but they're
				// all the same specLight, so just use the first one

				warppadObj->specLightToken[0] = *(short *)0x800b4e1c;
				warppadObj->specLightToken[1] = *(short *)0x800b4e1e;
				warppadObj->specLightToken[2] = *(short *)0x800b4e20;

				warppadObj->inst[WPIS_OPEN_PRIZE2] = newInst;
			}

		SlideColTurboTrack:

			// if relic not owned
			if (levelID < 0x12) // check this cause of "goto BattleTrack"
				if (CHECK_ADV_BIT(sdata->advProgress.rewards, (swap + 0x16)) == 0)
				{
					// SlideCol/TurboTrack
					if (levelID >= 0x10)
						t->modelIndex = 4;

					// open for token/relic
					else if (t->modelIndex != 1)
						t->modelIndex = 3;

					newInst = INSTANCE_Birth3D(gGT->modelPtr[0x61], 0, t);

					// relic blue
					newInst->colorRGBA = 0x20a5ff0;

					// specular lighting
					newInst->flags |= 0x20000;

					newInst->scale[0] = 0x1800;
					newInst->scale[1] = 0x1800;
					newInst->scale[2] = 0x1800;

					warppadObj->inst[WPIS_OPEN_PRIZE3] = newInst;
				}

			for (i = 0; i < 3; i++)
			{
				newInst = warppadObj->inst[WPIS_OPEN_PRIZE1 + i];

				if (newInst == 0)
					continue;

				// copy matrix
				*(int *)((int)&newInst->matrix + 0x0) = *(int *)((int)&inst->matrix + 0x0);
				*(int *)((int)&newInst->matrix + 0x4) = *(int *)((int)&inst->matrix + 0x4);
				*(int *)((int)&newInst->matrix + 0x8) = *(int *)((int)&inst->matrix + 0x8);
				*(int *)((int)&newInst->matrix + 0xC) = *(int *)((int)&inst->matrix + 0xC);
				*(short *)((int)&newInst->matrix + 0x10) = *(short *)((int)&inst->matrix + 0x10);
				newInst->matrix.t[0] = inst->matrix.t[0];
				newInst->matrix.t[1] = inst->matrix.t[1] + 0x100;
				newInst->matrix.t[2] = inst->matrix.t[2];
			}
		}

		// slide col, turbo track
		else if (levelID < 0x12)
		{
			// already unlocked
			t->modelIndex = 2;

			goto SlideColTurboTrack;
		}

		// battle tracks
		else if (levelID < 0x19)
		{
			battleTrackArr = 0x800aba3c;
			i = battleTrackArr[swap - 0x12] + 0x6f;

			// already unlocked
			t->modelIndex = 2;

			if (CHECK_ADV_BIT(sdata->advProgress.rewards, i) == 0)
			{
				// rainbow
				t->modelIndex = 4;

				goto BattleTrack;
			}
		}

		// gemstone valley
		else
		{
			// bit index of gem
			i = (swap - 100) + 0x6a;

			// if gem is already unlocked, quit
			if (CHECK_ADV_BIT(sdata->advProgress.rewards, i) != 0)
			{
				// beaten
				t->modelIndex = 2;

				return;
			}

			// rainbow color
			t->modelIndex = 4;

			newInst = INSTANCE_Birth3D(gGT->modelPtr[0x5f], 0, t);

			// specular lighting
			newInst->flags |= 0x20000;

			i = swap - 100;

			// token color
			newInst->colorRGBA =
				((unsigned int)data.AdvCups[i].color[0] << 0x14) |
				((unsigned int)data.AdvCups[i].color[1] << 0xc) |
				((unsigned int)data.AdvCups[i].color[2] << 0x4);

			warppadObj->inst[WPIS_OPEN_PRIZE1] = newInst;

			// store in Gem array
			warppadObj->specLightGem[0] = *(short *)0x800b4ddc;
			warppadObj->specLightGem[1] = *(short *)0x800b4dde;
			warppadObj->specLightGem[2] = *(short *)0x800b4de0;

			// for matrix copy
			goto SlideColTurboTrack;
		}

		return;
	}

	// === if locked ===

	if (unlockItem_numNeeded < 10)
	{
		warppadObj->digit10s = 0;
		warppadObj->digit1s = unlockItem_numNeeded;
	}

	else
	{
		warppadObj->digit10s = 1;
		warppadObj->digit1s = unlockItem_numNeeded - 10;
	}

	// ====== Item ========

	// WPIS_CLOSED_ITEM
	newInst = INSTANCE_Birth3D(gGT->modelPtr[unlockItem_modelID], 0, t);

	// copy matrix
	*(int *)((int)&newInst->matrix + 0x0) = *(int *)((int)&inst->matrix + 0x0);
	*(int *)((int)&newInst->matrix + 0x4) = *(int *)((int)&inst->matrix + 0x4);
	*(int *)((int)&newInst->matrix + 0x8) = *(int *)((int)&inst->matrix + 0x8);
	*(int *)((int)&newInst->matrix + 0xC) = *(int *)((int)&inst->matrix + 0xC);
	*(short *)((int)&newInst->matrix + 0x10) = *(short *)((int)&inst->matrix + 0x10);
	newInst->matrix.t[0] = inst->matrix.t[0];
	newInst->matrix.t[1] = inst->matrix.t[1] + 0x100;
	newInst->matrix.t[2] = inst->matrix.t[2];

	newInst->scale[0] = 0x2000;
	newInst->scale[1] = 0x2000;
	newInst->scale[2] = 0x2000;

	// no specular for trophy
	if (unlockItem_modelID != 0x62)
	{
		// specular lighting
		newInst->flags |= 0x20000;

		// relic
		if (unlockItem_modelID == 0x61)
		{
			// Relic blue color
			newInst->colorRGBA = 0x20a5ff0;

			warppadObj->specLightRelic[0] = *(short *)0x800b4dfc;
			warppadObj->specLightRelic[1] = *(short *)0x800b4dfe;
			warppadObj->specLightRelic[2] = *(short *)0x800b4e00;
		}

		// Key
		else if (unlockItem_modelID == 99)
		{
			// Key color
			newInst->colorRGBA = 0xdca6000;

			// store in Gem array (intended by ND, not a bug)
			warppadObj->specLightGem[0] = *(short *)0x800b4ddc;
			warppadObj->specLightGem[1] = *(short *)0x800b4dde;
			warppadObj->specLightGem[2] = *(short *)0x800b4de0;
		}

		// Gem
		else if (unlockItem_modelID == 0x5f)
		{
			// dont set color, that gets set in ThTick

			// store in Gem array
			warppadObj->specLightGem[0] = *(short *)0x800b4ddc;
			warppadObj->specLightGem[1] = *(short *)0x800b4dde;
			warppadObj->specLightGem[2] = *(short *)0x800b4de0;
		}

		// assume token
		else
		{
			i = levelID - 100;

			// token color
			newInst->colorRGBA =
				((unsigned int)data.AdvCups[i].color[0] << 0x14) |
				((unsigned int)data.AdvCups[i].color[1] << 0xc) |
				((unsigned int)data.AdvCups[i].color[2] << 0x4);

			// === Naughty Dog Bug ===
			// They made an array where every token color
			// could have it's own specular light, but they're
			// all the same specLight, so just use the first one

			warppadObj->specLightToken[0] = *(short *)0x800b4e1c;
			warppadObj->specLightToken[1] = *(short *)0x800b4e1e;
			warppadObj->specLightToken[2] = *(short *)0x800b4e20;
		}
	}

	warppadObj->inst[WPIS_CLOSED_ITEM] = newInst;

	// ====== "X" ========

	// WPIS_CLOSED_X
	newInst = INSTANCE_Birth3D(gGT->modelPtr[0x6F], 0, t);

	// copy matrix
	*(int *)((int)&newInst->matrix + 0x0) = 0x1000;
	*(int *)((int)&newInst->matrix + 0x4) = 0;
	*(int *)((int)&newInst->matrix + 0x8) = 0x1000;
	*(int *)((int)&newInst->matrix + 0xC) = 0;
	*(short *)((int)&newInst->matrix + 0x10) = 0x1000;
	newInst->matrix.t[0] = inst->matrix.t[0];
	newInst->matrix.t[1] = inst->matrix.t[1] + 0x100;
	newInst->matrix.t[2] = inst->matrix.t[2];

	newInst->scale[0] = 0x2000;
	newInst->scale[1] = 0x2000;
	newInst->scale[2] = 0x2000;

	// always face camera
	newInst->model->headers[0].flags |= 1;

	warppadObj->inst[WPIS_CLOSED_X] = newInst;

	// ====== "10s" ========

	if (warppadObj->digit10s != 0)
	{
		// WPIS_CLOSED_10S
		newInst = INSTANCE_Birth3D(gGT->modelPtr[0x38], 0, t);

		// copy matrix
		*(int *)((int)&newInst->matrix + 0x0) = 0x1000;
		*(int *)((int)&newInst->matrix + 0x4) = 0;
		*(int *)((int)&newInst->matrix + 0x8) = 0x1000;
		*(int *)((int)&newInst->matrix + 0xC) = 0;
		*(short *)((int)&newInst->matrix + 0x10) = 0x1000;
		newInst->matrix.t[0] = inst->matrix.t[0];
		newInst->matrix.t[1] = inst->matrix.t[1] + 0x100;
		newInst->matrix.t[2] = inst->matrix.t[2];

		newInst->scale[0] = 0x2000;
		newInst->scale[1] = 0x2000;
		newInst->scale[2] = 0x2000;

		// always face camera
		for (i = 0; i < newInst->model->numHeaders; i++)
			newInst->model->headers[i].flags |= 1;

		warppadObj->inst[WPIS_CLOSED_10S] = newInst;
	}

	// ====== "1s" ========

	// STATIC_BIG (1-8)
	i = 0x38;
	if (warppadObj->digit1s == 0)
		i = 0x6d; // '0'
	if (warppadObj->digit1s == 9)
		i = 0x6e; // '9'

	// WPIS_CLOSED_1S
	newInst = INSTANCE_Birth3D(gGT->modelPtr[i], 0, t);

	// copy matrix
	*(int *)((int)&newInst->matrix + 0x0) = 0x1000;
	*(int *)((int)&newInst->matrix + 0x4) = 0;
	*(int *)((int)&newInst->matrix + 0x8) = 0x1000;
	*(int *)((int)&newInst->matrix + 0xC) = 0;
	*(short *)((int)&newInst->matrix + 0x10) = 0x1000;
	newInst->matrix.t[0] = inst->matrix.t[0];
	newInst->matrix.t[1] = inst->matrix.t[1] + 0x100;
	newInst->matrix.t[2] = inst->matrix.t[2];

	newInst->scale[0] = 0x2000;
	newInst->scale[1] = 0x2000;
	newInst->scale[2] = 0x2000;

	// always face camera
	for (i = 0; i < newInst->model->numHeaders; i++)
		newInst->model->headers[i].flags |= 1;

	warppadObj->inst[WPIS_CLOSED_1S] = newInst;
}