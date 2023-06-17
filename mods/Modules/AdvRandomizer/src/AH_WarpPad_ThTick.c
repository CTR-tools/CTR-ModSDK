#include <common.h>
#define RANDOM_MODE 1

// budget: 4992

void Shuffle_array(short *, short);

void AH_WarpPad_ThTick(struct Thread *t)
{
	int i;
	int j;
	int boolOpen;
	struct GameTracker *gGT;
	struct WarpPad *warppadObj;
	struct Instance *warppadInst;
	struct Instance **visInstSrc;
	struct Instance **instArr;

	struct Driver *driver;
	struct Instance *driverInst;

	int modelID;
	int levelID;
	int x, y, z, dist;
	char *warppadLNG;

	int angleCamToWarppad;
	int angleSin, angleCos;
	MATRIX *warppadMatrix;

	int wispMaxHeight;
	int wispRiseRate;
	int rng1;
	int rng2;

	int rewardScale;
	int rewardScale2;

	int champID;
	int champSlot;
	u_int *rewards;

	char randKartSpawn[8];

	boolOpen = 0;
	gGT = sdata->gGT;
	warppadObj = t->object;
	warppadInst = t->inst;
	visInstSrc = gGT->cameraDC[0].visInstSrc;
	rewards = sdata->advProgress.rewards;

	while (visInstSrc[0] != 0)
	{
		if (visInstSrc[0] == warppadInst)
		{
			boolOpen = 1;
			break;
		}

		visInstSrc++;
	}

	// array of instances in warppad object
	instArr = &warppadObj->inst[0];
	warppadMatrix = &warppadInst->matrix;

	for (i = 0; i < WPIS_NUM_INSTANCES; i++)
	{
		if (instArr[i] != 0)
		{
			if (boolOpen)
				// make visible
				instArr[i]->flags &= ~(0x80);
			else
				// make invisible
				instArr[i]->flags |= 0x80;
		}
	}

	// This is the red triangle in DCxDemo's
	// level viewer, make it invisible.
	// Instance only exists for debugging
	warppadInst->flags |= 0x80;

	driver = gGT->drivers[0];
	driverInst = driver->instSelf;

	x = warppadMatrix->t[0] - driverInst->matrix.t[0];
	y = warppadMatrix->t[1] - driverInst->matrix.t[1];
	z = warppadMatrix->t[2] - driverInst->matrix.t[2];
	dist = x * x + y * y + z * z;

	levelID = warppadObj->levelID;

	// if near a portal
	if (
		// Trophy tracks
		((((unsigned short)(levelID)) < 0x10) && (dist < 0x144000)) ||

		// Slide Col + Turbo Track
		((((unsigned short)(levelID - 0x10)) < 2) && (dist < 0x90000)) ||

		// Battle tracks
		((((unsigned short)(levelID - 0x12)) < 7) && (dist < 0x144000)) ||

		// Gem cups
		((((unsigned short)(levelID)) >= 100) && (dist < 0x90000)))
	{
		// if you are near a new warppad, or if you already were
		// determined as near the same warppad in the last frame,
		// then use this warppad as the "closest". Otherwise the
		// game could run this for two warppads right next to each other
		if (
			(*(short *)0x800b4e86 == -1) ||
			(*(short *)0x800b4e86 == levelID))
		{
			// saved as nearest warppad
			*(short *)0x800b4e86 = levelID;

			// if not giving Aku Hint
			if (sdata->AkuAkuHintState == 0 && !RANDOM_MODE)
			{
				// default
				if (levelID < 100)
					warppadLNG =
						sdata->lngStrings
							[data.metaDataLEV[levelID].name_LNG];

				// gem cups
				else
					warppadLNG =
						sdata->lngStrings
							[data.AdvCups[levelID - 100].lngIndex_CupName];

				// midpoing X,
				// 30 pixels above botttom Y
				DecalFont_DrawLine(
					warppadLNG,
					gGT->tileView[0].rect.x + gGT->tileView[0].rect.w / 2,
					gGT->tileView[0].rect.x + gGT->tileView[0].rect.h - 30,
					FONT_BIG, (CENTER_TEXT | ORANGE));
			}

			// if track is unlocked, ignore all other ELSE-IFs
			if (instArr[WPIS_CLOSED_1S] == 0)
			{
			}

			switch (levelID)
			{
			case 101 ... 105:
				// Dont have hint "you must have 4 tokens for a gem"
				if ((rewards[4] & 0x20000) == 0)
				{
					// give hint "you must have 4 tokens for a gem"
					MainFrame_RequestMaskHint(0x1b, 0);
				}
				break;
			case 0 ... 15:
				// Dont have hint "you must have more trophies"
				if (((rewards[3] & 0x1000000) == 0) &&

					// required item is not KEY
					(instArr[WPIS_CLOSED_ITEM]->model->id != 99))
				{
					// give hint for "need more trophies"
					MainFrame_RequestMaskHint(2, 0);
				}
				break;
			case 16:
				// Dont have hint "you must have 10 relics"
				if ((rewards[4] & 0x40000) == 0)
				{
					// give hint for "need more trophies"
					MainFrame_RequestMaskHint(0x1C, 0);
				}
			}
		}

		// not near portal
		else
		{
			*(short *)0x800b4e86 = -1;
		}

		// if warppad is locked
		if (instArr[WPIS_CLOSED_1S] != 0)
		{
			angleCamToWarppad =
				ratan2(
					warppadMatrix->t[0] - gGT->tileView[0].pos[0],
					warppadMatrix->t[2] - gGT->tileView[0].pos[2]);

			angleCamToWarppad = -angleCamToWarppad;

			angleSin = MATH_Sin(angleCamToWarppad);
			angleCos = MATH_Cos(angleCamToWarppad);

			// no 10s digit
			if (instArr[WPIS_CLOSED_10S] == 0)
			{
				instArr[WPIS_CLOSED_1S]->matrix.t[0] = warppadMatrix->t[0] + (angleCos * -0x80 >> 0xC);
				instArr[WPIS_CLOSED_1S]->matrix.t[2] = warppadMatrix->t[2] + (angleSin * -0x80 >> 0xC);

				instArr[WPIS_CLOSED_ITEM]->matrix.t[0] = warppadMatrix->t[0] + ((angleCos << 7) >> 0xC);
				instArr[WPIS_CLOSED_ITEM]->matrix.t[2] = warppadMatrix->t[2] + ((angleSin << 7) >> 0xC);
			}

			// 10s digit
			else
			{
				instArr[WPIS_CLOSED_ITEM]->matrix.t[0] = warppadMatrix->t[0] + (angleCos * 0xC0 >> 0xC);
				instArr[WPIS_CLOSED_ITEM]->matrix.t[2] = warppadMatrix->t[2] + (angleSin * 0xC0 >> 0xC);

				instArr[WPIS_CLOSED_X]->matrix.t[0] = warppadMatrix->t[0] + ((angleCos << 6) >> 0xC);
				instArr[WPIS_CLOSED_X]->matrix.t[2] = warppadMatrix->t[2] + ((angleSin << 6) >> 0xC);

				instArr[WPIS_CLOSED_10S]->matrix.t[0] = warppadMatrix->t[0] + (angleCos * -0x40 >> 0xC);
				instArr[WPIS_CLOSED_10S]->matrix.t[2] = warppadMatrix->t[2] + (angleSin * -0x40 >> 0xC);

				instArr[WPIS_CLOSED_1S]->matrix.t[0] = warppadMatrix->t[0] + (angleCos * -0xa0 >> 0xC);
				instArr[WPIS_CLOSED_1S]->matrix.t[2] = warppadMatrix->t[2] + (angleSin * -0xa0 >> 0xC);
			}

			warppadObj->spinRot_Prize[0] = 0;
			warppadObj->spinRot_Prize[2] = 0;

			warppadObj->spinRot_Prize[1] += 0x40;

			// reuse variable,
			// end of function anyway
			warppadInst = instArr[WPIS_CLOSED_ITEM];

#define InstArr0 warppadInst

			ConvertRotToMatrix(
				&InstArr0->matrix,
				&warppadObj->spinRot_Prize[0]);

			modelID = InstArr0->model->id;

			switch (modelID)
			{
			case 0x62: // Trophy has no specular light
				return;

			case 0x61: // Relic
				Vector_SpecLightSpin3D(InstArr0, &warppadObj->spinRot_Prize[0], &warppadObj->specLightRelic[0]);
				return;

			case 0x7D: // Token
				Vector_SpecLightSpin3D(InstArr0, &warppadObj->spinRot_Prize[0], &warppadObj->specLightToken[0]);
				return;

			case 0x5F: // If Gem, change colors every 2 seconds
			{
				i = (gGT->timer / 0x3C) % 5;
				InstArr0->colorRGBA =
					((unsigned int)data.AdvCups[i].color[0] << 0x14) |
					((unsigned int)data.AdvCups[i].color[1] << 0xc) |
					((unsigned int)data.AdvCups[i].color[2] << 0x4);
				break;
			}

			default: // for Key or Gem
				Vector_SpecLightSpin3D(InstArr0, &warppadObj->spinRot_Prize[0], &warppadObj->specLightGem[0]);
				break;
			}

			return;
		}

		// === Assume Unlocked ===

		if (
			(instArr[WPIS_OPEN_BEAM] != 0) &&
			((gGT->timer & 1) != 0))
		{
			warppadObj->spinRot_Beam[0] = 0;
			warppadObj->spinRot_Beam[2] = 0;

			// what on earth was this RNG?
			// how'd they come up with something so random, that looks so good?
			i = MixRNG_Scramble();
			warppadObj->spinRot_Beam[1] += ((short)(i >> 3) + (short)((i >> 3) / 6) * -6 + 1) * 0x200;

			ConvertRotToMatrix(
				&instArr[WPIS_OPEN_BEAM]->matrix,
				&warppadObj->spinRot_Beam[0]);
		}

		wispRiseRate = 0x20;

		wispMaxHeight = (*(short *)0x800b4e86 != -1) ? 0x400 : 0x600;

		for (i = 0; i < 2; i++)
		{
			if (instArr[WPIS_OPEN_RING1 + i] != 0)
			{
				warppadObj->spinRot_Wisp[i][0] = 0;
				warppadObj->spinRot_Wisp[i][2] = 0;

				warppadObj->spinRot_Wisp[i][1] += 0x100;

				ConvertRotToMatrix(
					&instArr[WPIS_OPEN_RING1 + i]->matrix,
					&warppadObj->spinRot_Wisp[i][0]);

				// if height hasn't reached max height
				if (
					instArr[WPIS_OPEN_RING1 + i]->matrix.t[1] <
					(warppadInst->matrix.t[1] + wispMaxHeight))
				{
					instArr[WPIS_OPEN_RING1 + i]->matrix.t[1] += wispRiseRate;

					// if height hasn't reached 4x RiseRate,
					// first 4 frames of rising
					if (
						instArr[WPIS_OPEN_RING1 + i]->matrix.t[1] <
						(warppadInst->matrix.t[1] + wispRiseRate * 4))
					{
						// reduce transparency
						instArr[WPIS_OPEN_RING1 + i]->alphaScale -= 0x380;
					}

					// after first 4 frames
					else
					{
						// add transparency as the wisp spirals upward (~0x60  per frame)
						instArr[WPIS_OPEN_RING1 + i]->alphaScale += 0xc00 / (wispMaxHeight / wispRiseRate);
					}
				}

				// eached max height
				else
				{
					// reset height
					instArr[WPIS_OPEN_RING1 + i]->matrix.t[1] = warppadInst->matrix.t[1];

					// full transparency
					instArr[WPIS_OPEN_RING1 + i]->alphaScale = 0x1000;

					rng1 = MixRNG_Scramble() >> 3;

					rng2 = rng1;
					if (rng1 < 0)
						rng2 = rng1 + 0xfff;

					warppadObj->spinRot_Wisp[i][1] = (short)rng1 + (short)(rng2 >> 0xc) * -0x1000;
				}
			}

			wispRiseRate += 0x10;
		}

		warppadObj->spinRot_Prize[1] += 0x80;

		rewardScale = 0x100;

		if (dist > 0x1200000)
			rewardScale = 0;
		else
			// range [90, 90*2] to [0%, 100%]
			rewardScale = (((0x1200000 - dist) * 0x100) / 0x900000);

		for (i = 0; i < 3; i++)
		{
			warppadObj->spinRot_Prize[2] = 0x155;

			if (instArr[WPIS_OPEN_PRIZE1 + i] != 0)
			{
				AH_WarpPad_SpinRewards(
					instArr[WPIS_OPEN_PRIZE1 + i],
					warppadObj, i,
					warppadInst->matrix.t[0],
					warppadInst->matrix.t[1],
					warppadInst->matrix.t[2]);

				modelID = instArr[WPIS_OPEN_PRIZE1 + i]->model->id;

				if (rewardScale == 0)
				{
					// invisible
					instArr[WPIS_OPEN_PRIZE1 + i]->flags |= 0x80;
				}

				else
				{
					// visible
					instArr[WPIS_OPEN_PRIZE1 + i]->flags &= ~(0x80);

					rewardScale2 = (modelID != 0x7D) ? 0x2800 : 0x2000; // Trophy or not token

					rewardScale2 = (modelID == 0x61) ? 0x1800 : rewardScale2; // Relic

					rewardScale2 = (unsigned int)(rewardScale2 * rewardScale) >> 8;
					instArr[WPIS_OPEN_PRIZE1 + i]->scale[0] = (short)rewardScale2;
					instArr[WPIS_OPEN_PRIZE1 + i]->scale[1] = (short)rewardScale2;
					instArr[WPIS_OPEN_PRIZE1 + i]->scale[2] = (short)rewardScale2;
				}
			}

			warppadObj->thirds[i] += 0x20;
			warppadObj->spinRot_Rewards[1] += 0x4;
		}

		// make sure flag is already off-screen or driver is close to pad
		if (TitleFlag_IsTransitioning() || dist > 0x8fff)
			return;

		// if driver has not entered this warppad
		if (!warppadObj->boolEnteredWarppad)
		{
			// now in warppad
			warppadObj->boolEnteredWarppad = 1;
			warppadObj->framesWarping = 0;
		}

		// Naughty Dog Bug: spam every frame,
		// this wont have a negative performance impact cause it's IF-guarded,
		// needed cause mask hint sets state to 0xB (Freeze), then this sets
		// warp back. Without this, Freeze causes mask-grab, which makes you drive.
		// However, with this, state goes 0xA, then 0xB, then 0xA, and warp SFX
		// plays a second time. Animation also plays twice but is invisible second time
		void VehPtr_Warp_Init();
		gGT->drivers[0]->funcPtrs[0] = VehPtr_Warp_Init;

		if (warppadObj->framesWarping < 0x400)
			warppadObj->framesWarping++;

		// wait 2 full seconds before loading
		if (warppadObj->framesWarping < 61)
			return;

		// only works for trophy tracks rn
		switch (levelID)
		{
		case 0 ... 15:
			// if trophy is unlocked
			if (CHECK_ADV_BIT(rewards, (levelID + 6)) != 0)
			{
				// if never opened
				if (!sdata->boolOpenTokenRelicMenu)
				{
					// now opened
					sdata->boolOpenTokenRelicMenu = 1;

					MENUBOX_Show(0x800b4e50);

					// dont load level
					return;
				}

				// if opened, but not closed yet
				if ((MENUBOX_BoolHidden(0x800b4e50) & 0xffff) == 0)
				{
					// dont load level
					return;
				}

				// if opened, then closed
				else
				{
					// if hint is locked
					if (CHECK_ADV_BIT(rewards, (i + 0x76)) == 0)
					{
						// Token Hint or Relic Hint
						i = (gGT->gameMode2 & 8) ? 0x1a : 0x1d;
						MainFrame_RequestMaskHint(i, 1);
					}

					// if can't spawn aku cause he's already here,
					// quit function, wait till he's done to start race
					if ((AH_MaskHint_boolCanSpawn() & 0xffff) == 0)
						return;

					// reset for future gameplay
					sdata->boolOpenTokenRelicMenu = 0;
				}
			}
			break;

		// Slide Col or Turbo Track
		case 16 ... 18:

			// Add Relic
			sdata->Loading.OnBegin.AddBitsConfig0 |= RELIC_RACE;
			break;

		// Battle Tracks
		case 19 ... 25:

			// Add Crystal Challenge
			sdata->Loading.OnBegin.AddBitsConfig0 |= CRYSTAL_CHALLENGE;

			// Dont have hint "collect every crystal"
			if ((rewards[4] & 0x8000) == 0)
				MainFrame_RequestMaskHint(0x19, 1);

			// if can't spawn aku cause he's already here,
			// quit function, wait till he's done to start race
			if ((AH_MaskHint_boolCanSpawn() & 0xffff) == 0)
				return;

			gGT->originalEventTime = *(int *)(0x800b4e88 + 4 * (levelID - 0x12));
			break;
		// gem cups
		default:
			// Add Adv Cup
			sdata->Loading.OnBegin.AddBitsConfig0 |= ADVENTURE_CUP;

			gGT->cup.cupID = levelID - 100;
			gGT->cup.trackIndex = 0;
			for (i = 0; i < 8; i++)
				gGT->cup.points[i] = 0;

			levelID = data.advCupTrackIDs[4 * gGT->cup.cupID];
			break;
		}

		// Assign Characters
		// Dont worry about Token or Relic, those dont
		// use kartSpawnOrderArray, the OG game just did
		// this without an IF check at all
		if ((levelID < 0x10) || (levelID >= 100))
		{
			LOAD_Robots1P(data.characterIDs[0]);

			// spawn P1 in the back
			sdata->kartSpawnOrderArray[0] = 7;

			// variable reuse, get track speed champion
			champID = data.metaDataLEV[levelID].characterID_Champion;

			// default
			champSlot = 0;

			// If Speed Champion is on the track (Crash-Pura)
			// and is not the same characterID as Player 1
			if ((champID < 8 && champID != data.characterIDs[0]) || !RANDOM_MODE)
			{
				// Set everyone to spawn in order
				for (i = 0; i < 8; i++)
				{
					if (champID == data.characterIDs[i])
					{
						sdata->kartSpawnOrderArray[i] = 0;
						champSlot = i;
					}
					else
					{
						sdata->kartSpawnOrderArray[i] = i;
					}
				}
				sdata->kartSpawnOrderArray[7] = champSlot;
			}
			else
			{
				short start = 1;
				short end = 7;
				if (RANDOM_MODE)
				{
					sdata->kartSpawnOrderArray[0] = 0;
					start = 0;
					end = 8;
				}

				for (i = start; i < 8; i++)
				{
					randKartSpawn[i] = i;
				}

				for (i = 0; i < end; i++)
				{
					rng1 = RngDeadCoed(&sdata->const_0x30215400);
					rng2 = 7 - i;
					rng2 = (rng1 & 0xfff) % rng2 + 1;
					rng2 = (short)rng2;

					sdata->kartSpawnOrderArray[randKartSpawn[rng2]] = (char)i;

					memmove(&randKartSpawn[rng2], &randKartSpawn[rng2 + 1], (6 - i) * sizeof(short));
				}
			}

			// Rem Adventure Arena
			sdata->Loading.OnBegin.RemBitsConfig0 |= ADVENTURE_ARENA;

			MainRaceTrack_RequestLoad(levelID);
		}
	}
}