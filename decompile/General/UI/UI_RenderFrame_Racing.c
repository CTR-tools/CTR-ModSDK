#include <common.h>

// To do: add a header
void DECOMP_AA_EndEvent_DisplayTimeAA_EndEvent_DisplayTime(u_short, short);

void DECOMP_UI_RenderFrame_Racing()
{
	short sVar1;
	short sVar2;
	u_char bVar3;
	int partTimeVariable1;
	int* ptrColor;
	u_char *pbVar6;
	int i;
	struct PushBuffer* pb;
	u_int partTimeVariable5;
	struct Icon* iconPtr;
	u_long *primMemCurr;
	char *fmt;
	int partTimeVariable3;
	POLY_G4 * TurboCounterBar;
	short sVar17;
	u_int local_7c;
	u_int local_78;
	u_int local_70;
	struct Driver* playerStruct;
	struct UiElement2D *hudStructPtr;
	void* levPtrMap;
	char cVar22;
	short wumpaModel_Pos[2];
	short LetterCTR_Pos[2];
	char string [8];
	short turboCount_Pos[2];
	u_short local_30 [2];
	struct Thread* playerThread;
	u_long *ptrOT;
	struct DB *backBuffer;
	struct Thread* turboThread;
	struct Turbo* turboThreadObject;
	int offset;
	u_int mapPosX;
	u_int mapPosY;

	#ifdef USE_ONLINE
	offset = WIDE_PICK(-19, -27);
	#else
	offset = 0;
	#endif

	struct GameTracker* gGT;
	gGT = sdata->gGT;

	int numPlyr = gGT->numPlyrCurrGame;
	int gameMode1 = gGT->gameMode1;

	// Get pointer to array of HUD structs
	hudStructPtr = (struct UiElement2D*)data.hudStructPtr[numPlyr - 1];

	levPtrMap = 0;

	// adding this here so the compiler doesn't complain
	wumpaModel_Pos[0] = 0;
	wumpaModel_Pos[1] = 0;
	turboCount_Pos[0] = 0;
	turboCount_Pos[1] = 0;

	DECOMP_UI_WeaponBG_AnimateShine();

	// if time on clock is zero
	if (gGT->elapsedEventTime == 0)
	{
		for(i = 0; i < 8; i++)
		{
			data.rankIconsTransitionTimer[i] = 0;

			pbVar6 = &sdata->kartSpawnOrderArray[i];

			data.rankIconsCurr[i] = (u_short)*pbVar6;
			data.rankIconsDesired[i] = (u_short)*pbVar6;
		}
	}

	// If not drawing intro-race cutscene
	if ((gameMode1 & START_OF_RACE) == 0)
	{
		if ((gGT->hudFlags & 0x20) == 0)
		{

			// If you press Triangle
			if ((sdata->gGamepads->gamepad[0].buttonsTapped & 0x40000) != 0)
			{
				// if & 8, remove bit 8,
				// if !& 8, add bit 8,
				// toggle map and speedometer
				sdata->HudAndDebugFlags ^= 8;
			}
		}
		else
		{
			gGT->hudFlags &= 0xdf;
		}
	}

	// numPlyrCurrGame is 0
	if
	(
		(numPlyr == '\0') &&

		// If this is an AI and not a human
		((gGT->drivers[0]->actionsFlagSet & 0x100000) != 0)
	)
	{
		// force draw speedometer, and not map, why?
		sdata->HudAndDebugFlags = 8;
	}

	if (gGT->level1->ptrSpawnType1 != 0)
	{
		void** pointers = ST1_GETPOINTERS(gGT->level1->ptrSpawnType1);
		levPtrMap = pointers[ST1_MAP];
	}

	// If you are not in Relic Race, and not in battle mode,
	// and not in time trial
	if ((gameMode1 & (RELIC_RACE | TIME_TRIAL | BATTLE_MODE)) == 0)
	{
// cant run on PC yet, drivers dont initialize
#ifndef REBUILD_PC
		DECOMP_UI_DrawRankedDrivers();
#endif
	}

	// pointer to first Player thread
	playerThread = gGT->threadBuckets[0].thread;

	cVar22 = '\0';
	if (playerThread != 0)
	{
		// Loop through all player threads
		do
		{
			// pointer to player structure
			playerStruct = (struct Driver*)playerThread->object;

			#ifdef USE_ONLINE
			playerStruct = gGT->drivers[0];
			#endif

			if
			(
				// if player has not driven backwards very far,
				(playerStruct->distanceDrivenBackwards < 0x1f5)

				||

				// racer is not going the Wrong Way
				((playerStruct->actionsFlagSet & 0x100) == 0)
			)
			{
				LAB_80053260:
				// If game is not paused
				if ((gameMode1 & PAUSE_ALL) == 0)
				{
					//execute Jump meter and landing boost processes
					DECOMP_UI_JumpMeter_Update(playerStruct);
				}
			}

			// if racer has travelled
			// wrong way for too long
			else
			{
				// If game is not paused
				if ((gameMode1 & PAUSE_ALL) == 0)
				{
					pb = &gGT->pushBuffer[playerStruct->driverID];

					// if "Time on clock" last 0xXX u_char is greater than 0x80 and less than 0xFF
					if ((gGT->elapsedEventTime & 0x80) != 0)
					{
						DECOMP_DecalFont_DrawLine
						(
							// "WRONG WAY!"
							sdata->lngStrings[0x1D],

							// midpointX
							pb->rect.x + (pb->rect.w >> 1),

						 	// midpointY, 0x1e higher
						 	pb->rect.y + (pb->rect.h >> 1) - 0x1e,

							FONT_BIG, (JUSTIFY_CENTER | ORANGE)
						);
					}

					// The text will not show if the last u_char is more than 0x00 and less than 0x7F.
					// This is what makes the text flicker, rather than drawing solid

					cVar22 = '\x01';
					goto LAB_80053260;
				}
			}

			if
			(
				// numPlyrCurrGame is less than 2 (1P mode)
				(numPlyr < 2)
				#ifndef USE_ONLINE
				&&
				// if want to draw speedometer
				((sdata->HudAndDebugFlags & 8) != 0)
				#endif
			)
			{
				#ifdef USE_ONLINE
				DECOMP_UI_DrawSpeedNeedle(hudStructPtr[9].x + offset, hudStructPtr[9].y, playerStruct);
				DECOMP_UI_DrawSlideMeter(hudStructPtr[8].x + offset - 8, hudStructPtr[8].y + 3, playerStruct);
				DECOMP_UI_JumpMeter_Draw(hudStructPtr[8].x + offset + 18, hudStructPtr[8].y - 7, playerStruct);
				DECOMP_UI_DrawSpeedBG();
				#else
				DECOMP_UI_DrawSpeedNeedle(hudStructPtr[9].x + offset, hudStructPtr[9].y, playerStruct);
				DECOMP_UI_JumpMeter_Draw(hudStructPtr[6].x, hudStructPtr[6].y, playerStruct);
				DECOMP_UI_DrawSlideMeter(hudStructPtr[8].x + offset, hudStructPtr[8].y, playerStruct);
				DECOMP_UI_DrawSpeedBG();
				#endif
			}

			//if racer hasn't finished the race
			if ((playerStruct->actionsFlagSet & 0x2000000) == 0)
			{
				// If you're not in Battle Mode
				if ((gameMode1 & BATTLE_MODE) == 0)
				{
					#ifdef USE_ONLINE
					DECOMP_UI_DrawSlideMeter(hudStructPtr[8].x + offset - 8, hudStructPtr[8].y + 3, playerStruct);
					#else
					// Draw powerslide meter
					DECOMP_UI_DrawSlideMeter(hudStructPtr[8].x + offset, hudStructPtr[8].y, playerStruct);
					#endif
				}

				// If you are not in Time Trial or Relic Race
				if ((gameMode1 & (TIME_TRIAL | RELIC_RACE)) == 0)
				{
					DECOMP_UI_DrawNumWumpa(hudStructPtr[4].x, hudStructPtr[4].y, playerStruct);
				}
			}

			// If you're in a Relic Race
			if ((gameMode1 & RELIC_RACE) != 0)
			{
				DECOMP_UI_DrawNumTimebox(hudStructPtr[0x13].x, hudStructPtr[0x13].y, playerStruct);
			}

			// If game is not paused
			if ((gameMode1 & PAUSE_ALL) == 0)
			{
				if (playerStruct->PickupWumpaHUD.numCollected != 0)
				{
					wumpaModel_Pos[0] = hudStructPtr[3].x;
					wumpaModel_Pos[1] = hudStructPtr[3].y;

					// if cooldown between items is over
					if (playerStruct->PickupWumpaHUD.cooldown == 0)
					{
						// deduct from number of queued items to pick up
						playerStruct->PickupWumpaHUD.numCollected--;

						if
						(
							(DECOMP_LOAD_IsOpen_RacingOrBattle() != 0) &&

							// If you're not in Adventure Arena
							((gameMode1 & ADVENTURE_ARENA) == 0)
						)
						{
							DECOMP_RB_Player_ModifyWumpa(playerStruct, 1);
						}


						// OtherFX_Play to get wumpa fruit
						DECOMP_OtherFX_Play(0x42, 1);

						// initial timer value
						partTimeVariable1 = FPS_DOUBLE(5);

						// if timer is already running, set new timer value
						if (playerStruct->PickupWumpaHUD.numCollected != 0) goto LAB_80053498;
					}
					else
					{
						DECOMP_UI_Lerp2D_HUD
						(
							&wumpaModel_Pos[0],
							(int)playerStruct->PickupWumpaHUD.startX,
							(int)playerStruct->PickupWumpaHUD.startY,
							hudStructPtr[3].x, hudStructPtr[3].y,
							playerStruct->PickupWumpaHUD.cooldown,
							FPS_DOUBLE(5)
						);

						// subtract one from timer
						partTimeVariable1 = playerStruct->PickupWumpaHUD.cooldown - 1;

						LAB_80053498:

						// set timer value
						playerStruct->PickupWumpaHUD.cooldown = partTimeVariable1;
					}

					struct Icon** iconPtrArray =
						ICONGROUP_GETICONS(gGT->iconGroup[0xB]);

					// "wumpaposter" icon group
					DECOMP_DecalHUD_DrawPolyFT4
					(
						iconPtrArray[0],
						(int)wumpaModel_Pos[0],
						(int)wumpaModel_Pos[1],

						// pointer to PrimMem struct
						&gGT->backBuffer->primMem,

						// pointer to OT memory
						gGT->pushBuffer_UI.ptrOT,

						0, hudStructPtr[0].scale
					);
				}

				if (playerStruct->PickupLetterHUD.cooldown != 0)
				{
					struct Instance* curr;
					LetterCTR_Pos[0] = hudStructPtr[0x12].x;
					LetterCTR_Pos[1] = hudStructPtr[0x12].y;

					// C-Letter
					if (playerStruct->PickupLetterHUD.modelID == 0x93)
					{
						curr = sdata->ptrHudC;
					}

					// T-letter
					else if (playerStruct->PickupLetterHUD.modelID == 0x94)
					{
						LetterCTR_Pos[0] += 0x1d;
						LetterCTR_Pos[1] -= 1;
						curr = sdata->ptrHudT;
					}

					// R-Letter
					else
					{
						LetterCTR_Pos[0] += 0x3a;
						curr = sdata->ptrHudR;
					}

					// make visible
					*(u_int *)&curr->flags &= 0xffffff7f;

					// reduce frame counter
					playerStruct->PickupLetterHUD.cooldown--;

					// PickupLetterHUD.startX and PickupLetterHUD.startY are start position of animation

					// Interpolate from start pos to end pos
					DECOMP_UI_Lerp2D_HUD
					(
						&LetterCTR_Pos[0], playerStruct->PickupLetterHUD.startX,
						playerStruct->PickupLetterHUD.startY,
						(int)LetterCTR_Pos[0], (int)LetterCTR_Pos[1],
						(int)playerStruct->PickupLetterHUD.cooldown,
						FPS_DOUBLE(10)
					);

					curr->matrix.t[0] = DECOMP_UI_ConvertX_2((int)LetterCTR_Pos[0],0x200);
					curr->matrix.t[1] = DECOMP_UI_ConvertY_2((int)LetterCTR_Pos[1],0x200);
					curr->matrix.t[2] = 0x200;
				}
			}

			// If you're not in a Relic Race
			if ((gameMode1 & RELIC_RACE) == 0)
			{
				//if racer hasn't finished the race
				if ((playerStruct->actionsFlagSet & 0x2000000) == 0)
				{
					// Draw weapon and number of wumpa fruit in HUD
					DECOMP_UI_Weapon_DrawSelf(hudStructPtr[0].x, hudStructPtr[0].y, hudStructPtr[0].scale, playerStruct);
				}
			}

			// if you are in relic mode
			else
			{
				// If you smashed a time crate, this variable is set to 10
				if (playerStruct->PickupTimeboxHUD.cooldown != 0)
				{
					// DAT_8008d530
					// -%ld

					// Make string with number of time crate
					// print "-x" where x is the amount of seconds
					sprintf(&string[0], &sdata->s_subtractLongInt[0], gGT->timeCrateTypeSmashed);

					// 4b4 and 4b6 are WindowStartPos(x,y) from PushBuffer, inside Driver
					DECOMP_UI_Lerp2D_HUD
					(
						&wumpaModel_Pos[0], playerStruct->PickupTimeboxHUD.startX,
						playerStruct->PickupTimeboxHUD.startY,
						0x14, 8, playerStruct->PickupTimeboxHUD.cooldown,
						FPS_DOUBLE(10)
					);

					// Decrease remaining number of frames for this to be on screen
					playerStruct->PickupTimeboxHUD.cooldown--;

					// Put string on the screen
					// This happens for 10 frames
					DECOMP_DecalFont_DrawLine(&string[0], (int)wumpaModel_Pos[0], (int)wumpaModel_Pos[1], FONT_BIG, PERIWINKLE);
				}
			}

			// if you're in battle mode, while not paused
			// and you do not have a life limit
			if ((gameMode1 & (LIFE_LIMIT | BATTLE_MODE | PAUSE_ALL)) == BATTLE_MODE)
			{
				// If the animation for adding points is over
				if (playerStruct->BattleHUD.cooldown == 0)
				{
					// Delete the change that in score that was queued
					playerStruct->BattleHUD.scoreDelta = 0;
				}

				// if the animation is not done
				else
				{
					wumpaModel_Pos[0] = hudStructPtr[0xD].x + 0x20;
					wumpaModel_Pos[1] = hudStructPtr[0xD].y;

					// if you do not have life limit (battle)
					if ((gameMode1 & LIFE_LIMIT) == 0)
					{
						// This is only with point limit,
						// points can add or subtract

						// Get what should be added to your score
						partTimeVariable1 = playerStruct->BattleHUD.scoreDelta;

						// Can't add 0, so it's +1 or -1

						// if you are losing points
						if (partTimeVariable1 < 0)
						{
							// print a minus sign with your change in score

							// -%d
							fmt = &sdata->s_subtractInt[0];

							// Make a negative number positive
							partTimeVariable1 = -partTimeVariable1;

						}

						else
						{
							// print a plus sign with your change in score

							// +%ld
							fmt = &sdata->s_additionLongInt[0];
						}
					}

					// if you do have life limit (battle)
					else
					{
						// Life can only go down, not up

						// Get your change in score
						partTimeVariable1 = playerStruct->BattleHUD.scoreDelta;

						// Print a minus sign in front of the number of lives you lose

						// -%ld
						fmt = &sdata->s_subtractLongInt[0];
					}

					// make the string that flies from the center of your screen to the corner
					sprintf((char *)&LetterCTR_Pos[0], fmt, partTimeVariable1);

					DECOMP_UI_Lerp2D_HUD
					(
						&wumpaModel_Pos[0], (int)playerStruct->BattleHUD.startX,
						(int)playerStruct->BattleHUD.startY,
						(int)(((u_int)hudStructPtr[0xD].x + 0x20) * 0x10000) >> 0x10,
						(int)(((u_int)hudStructPtr[0xD].y + 8) * 0x10000) >> 0x10,
						playerStruct->BattleHUD.cooldown,
						FPS_DOUBLE(5)
					);

					// subtract one from the number of frames that the animation lasts
					playerStruct->BattleHUD.cooldown--;

					// print the string that shows the change in your score
					DECOMP_DecalFont_DrawLine((char *)&LetterCTR_Pos[0], (int)wumpaModel_Pos[0], (int)wumpaModel_Pos[1], FONT_SMALL, RED);
				}
			}

			// If you're not in Battle Mode
			if ((gameMode1 & BATTLE_MODE) == 0)
			{
				//if racer hasn't finished the race
				if ((playerStruct->actionsFlagSet & 0x2000000) == 0)
				{
					DECOMP_UI_DrawLapCount(hudStructPtr[1].x, hudStructPtr[1].y, (u_int)hudStructPtr[1].scale, playerStruct);
				}
			}

			// if you're in battle mode
			else
			{
				// Draw how many points or lifes the player has
				DECOMP_UI_DrawBattleScores((int)hudStructPtr[0xD].x, (int)hudStructPtr[0xD].y, playerStruct);
			}

// not rewritten yet
#ifndef REBUILD_PS1
			if
			(
				// if you're in adventure mode or Arcade mode and
				((gameMode1 & (ARCADE_MODE | ADVENTURE_MODE)) != 0) &&

				//racer finished the race
				((playerStruct->actionsFlagSet & 0x2000000) != 0)
			)
			{
				DECOMP_AA_EndEvent_DisplayTime((u_int)playerStruct->driverID, 0);
			}
#endif

			partTimeVariable5 = gameMode1;

			// If you are in Relic Race, and not in battle mode,
			// and not in time trial
			if ((partTimeVariable5 & 0x4020020) == 0)
			{
				if
				(
					//if racer hasn't finished the race
					((playerStruct->actionsFlagSet & 0x2000000) == 0) ||
					(
						(
							// if numPlyrCurrGame is 2
							numPlyr == '\x02' &&

							// AND

							// Not Arcade Mode (must be VS or Battle)
							((partTimeVariable5 & 0x400000) == 0)
						)
					)
				)
				{
					sVar17 = 0;
					partTimeVariable5 = 0;
				}
				else
				{

					// if numPlyrCurrGame is less than 3
					if (numPlyr < 3) goto LAB_80053af4;

					bVar3 = (gGT->timer & 1) == 0;
					sVar17 = (u_short)bVar3 << 2;
					partTimeVariable5 = ((u_int)bVar3 << 0x12) >> 0x10;
				}

				sVar1 = hudStructPtr[5].x;
				sVar2 = hudStructPtr[5].y;
				#ifndef USE_ONLINE
				DECOMP_UI_DrawPosSuffix(sVar1, sVar2, playerStruct, (short)partTimeVariable5);
				#endif

				if (numPlyr > 2)
				{
					// Get Color Data
					ptrColor = data.ptrColor[sVar17];

					// icon pointer, specifically for the big rank icons that start at 0x19
					iconPtr = gGT->ptrIcons[(int)playerStruct->driverRank + 0x19];

					LAB_80053aec:

					DECOMP_DecalHUD_DrawPolyGT4
					(
						// icon pointer
						iconPtr,

						// position
						(int)hudStructPtr[2].x,
						(int)hudStructPtr[2].y,

						&gGT->backBuffer->primMem,
						gGT->pushBuffer_UI.ptrOT,

						// color data
						ptrColor[0],
						ptrColor[1],
						ptrColor[2],
						ptrColor[3],

						0, FP(1.0)
					);
				}
			}

			// If you're in end-of-race and Battle
			else if ((partTimeVariable5 & 0x200020) == 0x200020)
			{
				partTimeVariable5 = (u_int)((gGT->timer & 1) == 0);

				// Draw the "st", "nd", "rd" suffix after "1st, 2nd, 3rd, etc"
				DECOMP_UI_DrawPosSuffix(hudStructPtr[5].x, hudStructPtr[5].y, playerStruct, (short)(partTimeVariable5 << 2));

				// Get Color Data
				ptrColor = data.ptrColor[partTimeVariable5];

				// pointer to icon
				// get rank icon of each battle team after battle is over
				// OH GOD THIS IS CONVOLUTED and probably wrong --Super
				iconPtr = gGT->ptrIcons[gGT->battleSetup.finishedRankOfEachTeam[playerStruct->BattleHUD.teamID] + 0x19];

				goto LAB_80053aec;
			}
			LAB_80053af4:

			// draw lock-on target for driver, if
			// a missile or warpball is chasing them
			DECOMP_UI_TrackerSelf(playerStruct);

			// If you're in Battle
			if ((gameMode1 & BATTLE_MODE) != 0)
			{
				// Draw arrows over the heads of other players (not AIs)
				DECOMP_UI_BattleDrawHeadArrows(playerStruct);
			}

			if
			(
				(playerStruct->numWumpas >= 10) &&

				//if racer hasn't finished the race
				((playerStruct->actionsFlagSet & 0x2000000) == 0)
			)
			{
				// draw shining background behind wumpa fruit
				DECOMP_UI_Weapon_DrawBG(hudStructPtr[0xC].x, hudStructPtr[0xC].y, hudStructPtr[0xC].scale, playerStruct);

				// If your weapon is not "no weapon"
				if(playerStruct->heldItemID != 0xF)
				{
					// draw shining background behind weapon
					DECOMP_UI_Weapon_DrawBG(hudStructPtr[0xB].x, hudStructPtr[0xB].y, hudStructPtr[0xB].scale, playerStruct);
				}
			}

			// go to next player
			// thread = thread->sibling
			playerThread = playerThread->siblingThread;

			// TODO: use num where 0x14 = NUM_HUD
			hudStructPtr += 0x14;

			#ifdef USE_ONLINE
			break;
			#endif

		} while (playerThread != 0);
	}

	if (sdata->WrongWayDirection_bool != cVar22)
	{

		sdata->framesDrivingSameDirection = 0;
		sdata->WrongWayDirection_bool = cVar22;
	}

	sdata->framesDrivingSameDirection++;

	if (numPlyr == 1)
	{
		playerStruct = gGT->drivers[0];

		DECOMP_UI_DrawRaceClock(0x14, 8, 0, playerStruct);

		turboThread = 0;
		turboThreadObject = 0;

		if ((gGT->gameMode2 & CHEAT_TURBOCOUNT) != 0)
		{

			// Get number of boosts
			sVar1 = playerStruct->numTurbos;

			// If number of boosts is not zero
			if (sVar1 != 0)
			{
				// Read pointer from address
				turboThread = gGT->threadBuckets[TURBO].thread;

				while
				(
					// Pointer != nullptr
					turboThread != 0 &&

					// Adds 0x30 to turboThread pointer, gets value (new address) then adds 4.
					// If   [something]   != pointer that holds boost counter
					(turboThreadObject = (struct Turbo*)turboThread->object, turboThreadObject->driver != playerStruct)
				)
				{
					turboThread = turboThread->siblingThread;
				}

				// Get number of boosts
				sVar1 = playerStruct->numTurbos;
			}

			// sdata->TurboDisplayPos_Only1P
			// Position of counter
			// 0 = offscreen
			// 1 = just barely on screen
			// ...
			// 10 = clearly on screen

			if
			(
				// If number boosts is less than 3
				(sVar1 < 3) ||

				// If display counter is fully on screen
				(9 < sdata->TurboDisplayPos_Only1P)
			)
			{
				// If pointer == nullptr
				if (turboThread == 0) goto LAB_80053c98;
				LAB_80053cac:

				// Set sVar1 to current display counter position
				sVar1 = sdata->TurboDisplayPos_Only1P;
				if
				(
					// If number boosts is less than 3
					(playerStruct->numTurbos < 3) &&

					// If turbo counter is on screen
					(0 < sdata->TurboDisplayPos_Only1P)
				)
				{
					LAB_80053cd4:

					// Animate counter to move off screen
					sVar1 = sdata->TurboDisplayPos_Only1P - 1;
				}
			}

			// If you have more than 3 boosts, and
			// display counter is not fully on screen
			else
			{

				// Animate counter to move onto screen
				sVar1 = sdata->TurboDisplayPos_Only1P + 1;

				// If pointer == nullptr
				if (turboThread == 0)
				{
					LAB_80053c98:
					// If counter is off screen
					if (sdata->TurboDisplayPos_Only1P < 1)
					{
						// set svar1 to display position
						goto LAB_80053cac;
					}

					// If counter is on screen
					// decrease boost counter,
					goto LAB_80053cd4;
				}
			}

			// Set display position value
			sdata->TurboDisplayPos_Only1P = sVar1;

			// If display counter is on screen (fully or not fully)
			if (sdata->TurboDisplayPos_Only1P != 0)
			{
				// Interpolate the turbo counter slide in from the right
				DECOMP_UI_Lerp2D_Linear(
					&turboCount_Pos[0],
					0x2c8, 0x20,
					500, 0x20,
					sdata->TurboDisplayPos_Only1P, 10);

				// The actual counter number will continue to
				// increase past 1000, but the on-screen text
				// will cap at 999

				// If you have less than 1000 boosts
				if (playerStruct->numTurbos < 1000)
				{
					// DAT_8008d54c
					// %d

					// build string for on-screen boost counter
					sprintf((char *)&string[0], &sdata->s_intSpace[0], playerStruct->numTurbos);
				}

				// If you have more than 1000 boosts
				else
				{
					// 8d544
					// "999" <-- ascii string, not 2-u_char value

					// Cap the on-screen counter at 999
					sprintf((char *)&string[0], &sdata->s_999[0]);
				}

				// "Turbos"
				i = DECOMP_DecalFont_GetLineWidth(sdata->lngStrings[0x24B], 1);

				// Draw the string
				DECOMP_DecalFont_DrawLine((char *)&string[0], (int)(((u_int)turboCount_Pos[0] - i) * 0x10000) >> 0x10, (int)turboCount_Pos[1], FONT_BIG, (JUSTIFY_RIGHT | ORANGE_RED));


				// Draw the string
				DECOMP_DecalFont_DrawLine(sdata->lngStrings[0x24B], (int)(short)turboCount_Pos[0], (int)turboCount_Pos[1], FONT_BIG, (JUSTIFY_RIGHT | ORANGE));

				backBuffer = gGT->backBuffer;
				primMemCurr = backBuffer->primMem.curr;
				TurboCounterBar = 0;

				if (primMemCurr <= backBuffer->primMem.endMin100)
				{
					backBuffer->primMem.curr = primMemCurr + 9;
					TurboCounterBar = (POLY_G4 *)primMemCurr;
				}

				if (TurboCounterBar == 0)
				{
					return;
				}

				*(u_int *)&TurboCounterBar->r0 = 0x3800c8ff;
				*(u_int *)&TurboCounterBar->r1 = 0x3800c8ff;
				*(u_int *)&TurboCounterBar->r2 = 0x380000ff;
				*(u_int *)&TurboCounterBar->r3 = 0x380000ff;
				TurboCounterBar->x0 = turboCount_Pos[0] - 0xaa;
				TurboCounterBar->y0 = turboCount_Pos[1] + 9;
				TurboCounterBar->x1 = turboCount_Pos[0] + 0x32;
				TurboCounterBar->y1 = turboCount_Pos[1] + 9;
				TurboCounterBar->x2 = turboCount_Pos[0] - 0x96;
				TurboCounterBar->y2 = turboCount_Pos[1] + 0x12;
				TurboCounterBar->x3 = turboCount_Pos[0] + 0x32;
				TurboCounterBar->y3 = turboCount_Pos[1] + 0x12;

				// pointer to OT memory
				primMemCurr = gGT->pushBuffer_UI.ptrOT;

				*(int*)TurboCounterBar = *primMemCurr | 0x8000000;
				*primMemCurr = (u_int)TurboCounterBar & 0xffffff;
			}
		}
	}

	// if numPlyrCurrGame is not 1 (multiplayer)
	else
	{

		// if you have a time limit (battle)
		if ((gameMode1 & TIME_LIMIT) != 0)
		{
			// draw countdown clock
			DECOMP_UI_DrawLimitClock(0xd7,0x68,2);
		}
	}

	if(
		(levPtrMap != 0) &&
		((gameMode1 & BATTLE_MODE) == 0)
	)
	{
		if
		(
			(
				(numPlyr == 1)
				#ifndef USE_ONLINE
				&&
				// if want to draw map, not speedometer
				(sdata->HudAndDebugFlags & 8) == 0
				#endif
			) ||

			(numPlyr == 3)
		)
		{
			local_30[0] = 0;

			DECOMP_UI_Map_DrawDrivers	(levPtrMap, gGT->threadBuckets[PLAYER].thread, local_30);
			DECOMP_UI_Map_DrawDrivers	(levPtrMap, gGT->threadBuckets[ROBOT].thread, local_30);

			#ifndef USE_ONLINE
			DECOMP_UI_Map_DrawGhosts	(levPtrMap, gGT->threadBuckets[GHOST].thread);
			#endif

			DECOMP_UI_Map_DrawTracking	(levPtrMap, gGT->threadBuckets[TRACKING].thread);

			mapPosX = 500;
			#ifdef USE_ONLINE
			mapPosY = 145;
			#else
			mapPosY = 195;
			#endif

			if (numPlyr == 3)
			{
				mapPosX -= 60;
				mapPosY += 10;
			}

			// Draw the map
			DECOMP_UI_Map_DrawMap
			(
				// top half and bottom half
				gGT->ptrIcons[3],
				gGT->ptrIcons[4],

				// X and Y
				mapPosX, mapPosY,

				// Pointer to primary memory
				&gGT->backBuffer->primMem,

				// pointer to OT memory
				gGT->pushBuffer_UI.ptrOT,

				// color, in this case white
				1
			);
		}
	}

	bVar3 = false;

	// loop counter
	i = 0;

	// if numPlyrCurrGame is not 0
	if (numPlyr != '\0')
	{
		// for(int i = 0; i < numPlyrCurrGame; i++)
		do
		{
			playerStruct = gGT->drivers[i];
			pb = &gGT->pushBuffer[playerStruct->driverID];

			if
			(
				(
					//if racer finished the race
					((playerStruct->actionsFlagSet & 0x2000000) != 0) &&

					// If you're not in Arcade or Time Trial
					((gameMode1 & (ARCADE_MODE | TIME_TRIAL)) == 0)
				) &&
				(
					(
						// cooldown is finished
						gGT->timerEndOfRaceVS == 0 ||

						// cooldown has not progressed far,
						// so you still need to draw "Finished" and "Loser"
						(0x96 < gGT->timerEndOfRaceVS)
					)
				)
			)
			{

				if
				(
					// player structure + 0x482 is your rank in the race
					// 0 = 1st place, 1 = 2nd place, 2 = 3rd place, etc

					// Basically, out of all human players, if you did not come in last
					((int)playerStruct->driverRank < (int)numPlyr - 1) &&

					// If you're not in Battle Mode
					// (winner of battle wont use this function)
					((gameMode1 & BATTLE_MODE) == 0)
				)
				{
					// FINISHED!
					pbVar6 = sdata->lngStrings[0x1E];
				}

				// If you came in last place, or you're in battle
				else
				{
					// LOSER!
					pbVar6 = sdata->lngStrings[0x143];
				}

				DECOMP_DecalFont_DrawLine(
					pbVar6,
					pb->rect.x + (pb->rect.w >> 1),			// midpointX
					pb->rect.y + (pb->rect.h >> 1) - 0x1e,	// midpointY
					FONT_BIG, (JUSTIFY_CENTER | ORANGE));

				if
				(
					// If you press Cross or Start
					((sdata->gGamepads->gamepad[i].buttonsTapped & 0x1010) != 0) &&

					// If you're in End-Of-Race menu
					((gameMode1 & END_OF_RACE) != 0)
				)
				{
					// make "Finished" and "Loser" disappear, start
					// drawing the on-screen comments
					gGT->timerEndOfRaceVS = 0x96;
				}
			}

			//if item roll is not done
			if (playerStruct->itemRollTimer != 0)
			{
				bVar3 = true;
			}

			// increment the iteration counter
			i++;

		// for(int i = 0; i < numPlyrCurrGame; i++)
		} while (i < (int)numPlyr);
	}
	if
	(
		(
			// If game is not paused
			((gameMode1 & PAUSE_ALL) == 0) &&

			//item roll is done
			(!bVar3)
		) &&

		// If you're drawing Weapon Roulette (randomizing)
		((gameMode1 & ROLLING_ITEM) != 0)
	)
	{
		// stop weapon shuffle sound
		DECOMP_OtherFX_Stop2(0x5d);

		// disable the randomizing effect in the HUD
		gGT->gameMode1 &= ~ROLLING_ITEM;
	}
}