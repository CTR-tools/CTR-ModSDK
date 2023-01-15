#include <common.h>

// To do: add a header
void WeaponBackground_AnimateShine();
void DrawHUD_DriverIcons();
void ProcessPlayerJumpBoosts(struct Driver*);
void DrawSpeedometerNeedle(short, short, struct Driver*);
void DrawJumpMeter(short, short, struct Driver*);
void DrawPowerslideMeter(short, short, struct Driver*);
void DrawSpeedometerBackground();
void DrawNumWumpa(int, int, struct Driver*);
void DrawNumTimebox(int, int, struct Driver*);
u_int LOAD_IsOpen_RacingOrBattle();
void RB_Player_ModifyWumpa(struct Driver*, int);
void OtherFX_Play(int, int);
void InterpolatePosition2D_HUD(short *, short, short, short, short, int, short);
void DecalHUD_DrawPolyFT4(struct Icon*, u_int, int, struct PrimMem*, u_long*, u_char, short);
int UI_ConvertX_2(int, int);
int UI_ConvertY_2(int, int);
void DrawWeapon(short, short, short, struct Driver*);
void DecalFont_DrawLine(char*, int, int, int, int);
void DrawLapCounter(short, short, u_int, struct Driver*);
void DrawBattleScores(int, int, struct Driver*);
void AA_EndEvent_DisplayTime(u_short, short);
void DrawPlacmentSuffix(short, short, struct Driver*, short);
void DecalHUD_DrawPolyGT4(struct Icon*, u_int, int, struct PrimMem*, u_long*, u_int, u_int, u_int, u_int, u_char, short);
void UpdateTrackerTargets(struct Driver*);
void Battle_DrawArrowsOverHeads(struct Driver*);
void DrawWeaponBackground(short, short, short, struct Driver*);
void DrawRaceClock(u_short paramX, u_short, u_int, struct Driver*);
void InterpolatePosition2D_Linear(short *, short, short, short, short, int, short);
int DecalFont_GetLineWidth(char*, short);
void DrawCountdownClock(short, short, short);
void Map_DrawDrivers(u_int, struct Thread*, short *);
void Map_DrawGhosts(u_int, struct Thread*);
void Map_DrawTracking(u_int, struct Thread*);
void Map_DrawMap(struct Icon*, struct Icon*, short, short, struct PrimMem*, u_long*, u_int);
void OtherFX_Stop2(u_int);

void DECOMP_DrawHUD_Racing()
{
	short sVar1;
	short sVar2;
	u_char bVar3;
	int partTimeVariable1;
	u_int partTimeVariable4;
	u_char **ppuVar5;
	u_char *pbVar6;
	int i;
	struct Camera110 *cam110;
	u_int partTimeVariable5;
	struct Icon* iconPtr;
	u_long *primMemCurr;
	u_short *puVar12;
	char *fmt;
	int partTimeVariable3;
	u_short *driverRankIndexAbsolute;
	POLY_G4 * TurboCounterBar;
	struct Instance* ptrHudC;
	short sVar17;
	u_short *driverRankIndexLeft;
	u_int local_7c;
	u_int local_78;
	u_int local_74;
	u_int local_70;
	struct Driver* playerStruct;
	struct HudElement *hudStructPtr;
	int levPtrMap;
	char cVar22;
	short wumpaModel_PosX;
	short wumpaModel_PosY;
	short LetterCTR_PosX;
	short LetterCTR_PosY;
	char acStack80 [24];
	u_short local_38;
	short local_36;
	u_short local_30 [4];
	struct Thread* playerThread;
	struct Instance* ptrHudR;
	struct Instance* ptrHudT;
	u_long *ptrOT;
	struct DB *backBuffer;
	struct Thread* turboThread;
	struct Turbo* turboThreadObject;
	struct Icon* icon1;
	struct Icon* icon2;

	// Get pointer to array of HUD structs
	hudStructPtr = (struct HudElement*)data.hudStructPtr[sdata->gGT->numPlayers - 1];

	levPtrMap = 0;

	// adding this here so the compiler doesn't complain
	wumpaModel_PosX = 0;
	wumpaModel_PosY = 0;
	icon1 = 0;
	icon2 = 0;
	local_36 = 0;

	WeaponBackground_AnimateShine();

	// if time on clock is zero
	if (sdata->gGT->elapsedEventTime == 0)
	{

		// loop counter
		i = 0;

		driverRankIndexLeft = (u_short*)&data.unk_between_hudStructPtr_menuRow_arcadeEndRace[0x5C];
		driverRankIndexAbsolute = (u_short*)&data.unk_between_hudStructPtr_menuRow_arcadeEndRace[0x4C];
		// something for each driver?
		puVar12 = (u_short*)&data.unk_between_hudStructPtr_menuRow_arcadeEndRace[0x6C];

		// for i = 0; i < 8; i++
		do
		{
			*puVar12 = 0;
			puVar12 = puVar12 + 1;
			pbVar6 = &sdata->kartSpawnOrderArray[i];

			// increment loop counter
			i = i + 1;

			*driverRankIndexAbsolute = (u_short)*pbVar6;
			driverRankIndexAbsolute++;
			*driverRankIndexLeft = (u_short)*pbVar6;
			driverRankIndexLeft++;
		} while (i < 8);
	}

	// If not drawing intro-race cutscene
	if ((sdata->gGT->gameMode1 & 0x40) == 0)
	{
		if ((sdata->gGT->hudFlags & 0x20) == 0)
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
			sdata->gGT->hudFlags &= 0xdf;
		}
	}

	// number of screens is 0
	if
	(
		(sdata->gGT->numPlayers == '\0') &&

		// If this is an AI and not a human
		((sdata->gGT->drivers[0]->actionsFlagSet & 0x100000) != 0)
	)
	{
		// force draw speedometer, and not map, why?
		sdata->HudAndDebugFlags = 8;
	}

	if (sdata->gGT->level1->ptrSpawnType1 != 0)
	{
		levPtrMap = sdata->gGT->level1->ptrSpawnType1->pointers[0];
	}

	// If you are not in Relic Race, and not in battle mode,
	// and not in time trial
	if ((sdata->gGT->gameMode1 & 0x4020020) == 0)
	{
		DrawHUD_DriverIcons();
	}

	// pointer to first Player thread
	playerThread = sdata->gGT->threadBuckets[0].thread;

	cVar22 = '\0';
	if (playerThread != 0)
	{
		// Loop through all player threads
		do
		{
			// pointer to player structure
			playerStruct = (struct Driver*)playerThread->object;

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
				if ((sdata->gGT->gameMode1 & 0xf) == 0)
				{
					//execute Jump meter and landing boost processes
					ProcessPlayerJumpBoosts(playerStruct);
				}
			}

			// if racer has travelled
			// wrong way for too long
			else
			{
				// If game is not paused
				if ((sdata->gGT->gameMode1 & 0xf) == 0)
				{
					// Player / AI structure + 0x4a shows driver index (0-7)
					// This is a pointer to each player's camera110 buffer
					cam110 = &sdata->gGT->camera110[playerStruct->driverID];

					// if "Time on clock" last 0xXX u_char is greater than 0x80 and less than 0xFF
					if ((sdata->gGT->elapsedEventTime & 0x80) != 0)
					{
						DecalFont_DrawLine
						(
							// "WRONG WAY!"
							sdata->lngStrings[0x74],

							// Midpoint between Start X and Size X
							(int)(((u_int)cam110->rect.x + ((int)((u_int)cam110->rect.w << 0x10) >> 0x11)) * 0x10000) >> 0x10,

						 	// Midpoint between Start Y and Size Y, except 0x1e higher
						 	(int)(((u_int)cam110->rect.y + ((int)((u_int)cam110->rect.h << 0x10) >> 0x11) + -0x1e) * 0x10000) >> 0x10,

							1, 0xffff8000
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
				// number of screens is less than 2 (1P mode)
				(sdata->gGT->numPlayers < 2) &&

				// if want to draw speedometer
				((sdata->HudAndDebugFlags & 8) != 0)
			)
			{
				// draw spedometer needle
				DrawSpeedometerNeedle(hudStructPtr[0x12].x, hudStructPtr[0x12].y, playerStruct);

				// draw jump meter
				DrawJumpMeter(hudStructPtr[0xC].x, hudStructPtr[0xC].y, playerStruct);

				// Draw Powerslide Meter
				DrawPowerslideMeter(hudStructPtr[0x10].x, hudStructPtr[0x10].y, playerStruct);

				// draw background of spedometer
				DrawSpeedometerBackground(hudStructPtr[0x12].x, hudStructPtr[0x12].y, playerStruct);
			}

			//if racer hasn't finished the race
			if ((playerStruct->actionsFlagSet & 0x2000000) == 0)
			{

				// If you're not in Battle Mode
				if ((sdata->gGT->gameMode1 & 0x20) == 0)
				{
					// Draw powerslide meter
					DrawPowerslideMeter(hudStructPtr[0x10].x, hudStructPtr[0x10].y, playerStruct);
				}

				// If you are not in Time Trial or Relic Race
				if ((sdata->gGT->gameMode1 & 0x4020000) == 0)
				{
					DrawNumWumpa((int)hudStructPtr[8].x, (int)hudStructPtr[8].y, playerStruct);
				}
			}

			// If you're in a Relic Race
			if ((sdata->gGT->gameMode1 & 0x4000000) != 0)
			{
				DrawNumTimebox((int)hudStructPtr[0x26].x, (int)hudStructPtr[0x26].y, playerStruct);
			}

			// If game is not paused
			if ((sdata->gGT->gameMode1 & 0xf) == 0)
			{
				if (playerStruct->PickupWumpaHUD.remaining != 0)
				{
					wumpaModel_PosX = hudStructPtr[6].x;
					wumpaModel_PosY = hudStructPtr[6].y;

					// if cooldown between items is over
					if (playerStruct->PickupTimeboxHUD.cooldown == 0)
					{
						// deduct from number of queued items to pick up
						playerStruct->PickupWumpaHUD.remaining--;

						// Check if 231 dll is loaded
						partTimeVariable1 = LOAD_IsOpen_RacingOrBattle(&wumpaModel_PosX);

						// If it is loaded
						if
						(
							(partTimeVariable1 != 0) &&

							// If you're not in Adventure Arena
							((sdata->gGT->gameMode1 & 0x100000) == 0)
						)
						{
							RB_Player_ModifyWumpa(playerStruct, 1);
						}

						// OtherFX_Play to get wumpa fruit
						OtherFX_Play(0x42, 1);

						// initial timer value
						partTimeVariable1 = 5;

						// if timer is already running, set new timer value
						if (playerStruct->PickupWumpaHUD.remaining != 0) goto LAB_80053498;
					}
					else
					{
						InterpolatePosition2D_HUD
						(
							&wumpaModel_PosX,
							(int)playerStruct->PickupWumpaHUD.startX,
							(int)playerStruct->PickupWumpaHUD.startY,
							hudStructPtr[6].x, hudStructPtr[6].y,
							playerStruct->PickupTimeboxHUD.cooldown,
							5
						);

						// subtract one from timer
						partTimeVariable1 = playerStruct->PickupTimeboxHUD.cooldown - 1;

						LAB_80053498:

						// set timer value
						playerStruct->PickupTimeboxHUD.cooldown = partTimeVariable1;
					}

					// "wumpaposter" icon group
					DecalHUD_DrawPolyFT4
					(
						sdata->gGT->iconGroup[0xB]->icons[0],
						(int)wumpaModel_PosX,
						(int)wumpaModel_PosY,

						// pointer to PrimMem struct
						&sdata->gGT->backBuffer->primMem,

						// pointer to OT memory
						sdata->gGT->camera110_UI.ptrOT,

						0, hudStructPtr[1].y
					);
				}
				ptrHudC = sdata->ptrHudC;
				ptrHudR = sdata->ptrHudR;
				ptrHudT = sdata->ptrHudT;
				if (playerStruct->PickupLetterHUD.cooldown != 0)
				{
					// C-Letter
					if (playerStruct->PickupLetterHUD.modelID == 0x93)
					{
						// make visible
						*(u_int *)&ptrHudC->flags &= 0xffffff7f;

						LetterCTR_PosX = hudStructPtr[0x24].x;
						ptrHudR = ptrHudC;
						LAB_80053584:
						LetterCTR_PosY = hudStructPtr[0x24].y;
						ptrHudT = ptrHudR;
					}

					// not C-Letter
					else
					{
						// not T-Letter
						if (playerStruct->PickupLetterHUD.modelID != 0x94)
						{
							// R-Letter

							// make visible
							*(u_int *)&ptrHudR->flags &= 0xffffff7f;

							LetterCTR_PosX = hudStructPtr[0x24].x + 0x3a;
							goto LAB_80053584;
						}

						// T-Letter

						// make visible
						*(u_int *)&ptrHudT->flags &= 0xffffff7f;

						LetterCTR_PosX = hudStructPtr[0x24].x + 0x1d;
						LetterCTR_PosY = hudStructPtr[0x24].y--;
					}

					// reduce frame counter
					playerStruct->PickupLetterHUD.cooldown--;

					// PickupLetterHUD.startX and PickupLetterHUD.startY are start position of animation

					// Interpolate from start pos to end pos
					InterpolatePosition2D_HUD
					(
						&LetterCTR_PosX, playerStruct->PickupLetterHUD.startX,
						playerStruct->PickupLetterHUD.startY,
						(int)LetterCTR_PosX, (int)LetterCTR_PosY,
						(int)playerStruct->PickupLetterHUD.cooldown,
						10
					);

					// Convert X
					partTimeVariable4 = UI_ConvertX_2((int)LetterCTR_PosX, 0x200);
					ptrHudT->matrix.t[0] = partTimeVariable4;

					// Convert Y
					partTimeVariable4 = UI_ConvertY_2((int)LetterCTR_PosY,0x200);
					ptrHudT->matrix.t[1] = partTimeVariable4;

					ptrHudT->matrix.t[2] = 0x200;
				}
			}

			// If you're not in a Relic Race
			if ((sdata->gGT->gameMode1 & 0x4000000) == 0)
			{
				//if racer hasn't finished the race
				if ((playerStruct->actionsFlagSet & 0x2000000) == 0)
				{
					// Draw weapon and number of wumpa fruit in HUD
					DrawWeapon(hudStructPtr[0].x, hudStructPtr[0].y, hudStructPtr[1].y, playerStruct);
				}
			}

			// if you are in relic mode
			else
			{
				// If you smashed a time crate, this variable is set to 10
				if (playerStruct->TensDiscountFromRelicRace != 0)
				{
					// DAT_8008d530
					// -%ld

					// Make string with number of time crate
					// print "-x" where x is the amount of seconds
					sprintf(acStack80, &sdata->s_subtractLongInt[0], sdata->gGT->timeCrateTypeSmashed);

					// 4b4 and 4b6 are WindowStartPos(x,y) from Camera110, inside Driver
					InterpolatePosition2D_HUD
					(
						&wumpaModel_PosX, playerStruct->PickupTimeboxHUD.startX,
						playerStruct->PickupTimeboxHUD.startY,
						0x14, 8, playerStruct->TensDiscountFromRelicRace,
						10
					);

					// Decrease remaining number of frames for this to be on screen
					playerStruct->TensDiscountFromRelicRace--;

					// Put string on the screen
					// This happens for 10 frames
					DecalFont_DrawLine(acStack80, (int)wumpaModel_PosX, (int)wumpaModel_PosY, 1, 1);
				}
			}

			// if you're in battle mode, while not paused
			// and you do not have a life limit
			if ((sdata->gGT->gameMode1 & 0x802f) == 0x20)
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
					wumpaModel_PosX = hudStructPtr[0x1A].x + 0x20;
					wumpaModel_PosY = hudStructPtr[0x1A].y;

					// if you do not have life limit (battle)
					if ((sdata->gGT->gameMode1 & 0x8000) == 0)
					{
						// This is only with point limit,
						// points can add or subtract

						// Get what should be added to your score
						partTimeVariable1 = playerStruct->BattleHUD.scoreDelta;

						// Can't add 0, so it's +1 or -1

						// if you are losing points
						if (partTimeVariable1 < 1)
						{
							// print a minus sign with your change in score

							// -%d
							fmt = &sdata->s_subtractInt[0];

							// Get own absolute value of the change
							if (partTimeVariable1 < 0)
							{
								// Make a negative number positive
								partTimeVariable1--;
							}
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
					sprintf((char *)&LetterCTR_PosX, fmt, partTimeVariable1);

					InterpolatePosition2D_HUD
					(
						&wumpaModel_PosX, (int)playerStruct->BattleHUD.startX,
						(int)playerStruct->BattleHUD.startY,
						(int)(((u_int)hudStructPtr[0x1A].x + 0x20) * 0x10000) >> 0x10,
						(int)(((u_int)hudStructPtr[0x1A].y + 8) * 0x10000) >> 0x10,
						playerStruct->BattleHUD.cooldown,
						5
					);

					// subtract one from the number of frames that the animation lasts
					playerStruct->BattleHUD.cooldown--;

					// print the string that shows the change in your score
					DecalFont_DrawLine((char *)&LetterCTR_PosX, (int)wumpaModel_PosX, (int)wumpaModel_PosY, 2, 3);
				}
			}

			// If you're not in Battle Mode
			if ((sdata->gGT->gameMode1 & 0x20) == 0)
			{
				//if racer hasn't finished the race
				if ((playerStruct->actionsFlagSet & 0x2000000) == 0)
				{
					// Draw which lap they are on (1/3, 2/3, 3/3, etc)
					DrawLapCounter(hudStructPtr[2].x, hudStructPtr[2].y, (u_int)hudStructPtr[3].y, playerStruct);
				}
			}

			// if you're in battle mode
			else
			{
				// Draw how many points or lifes the player has
				DrawBattleScores((int)hudStructPtr[0x1A].x, (int)hudStructPtr[0x1A].y, playerStruct);
			}

			if
			(
				// if you're in adventure mode or Arcade mode and
				((sdata->gGT->gameMode1 & 0x480000) != 0) &&

				//racer finished the race
				((playerStruct->actionsFlagSet & 0x2000000) != 0)
			)
			{
				// Player / AI structure + 0x4a shows driver index (0-7)

				// DLL 222
				// Display total time it took to finish race
				AA_EndEvent_DisplayTime((u_int)playerStruct->driverID, 0);
			}
			partTimeVariable5 = sdata->gGT->gameMode1;

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
							// if number of screens is 2
							sdata->gGT->numPlayers == '\x02' &&

							// AND

							// Not Arcade Mode (must be VS or Battle)
							((partTimeVariable5 & 0x400000) == 0)
						)
					)
				)
				{
					sVar17 = 0;
					sVar1 = hudStructPtr[0xA].x;
					sVar2 = hudStructPtr[0xA].y;
					partTimeVariable5 = 0;
				}
				else
				{

					// if number of screens is less than 3
					if (sdata->gGT->numPlayers < 3) goto LAB_80053af4;
					sVar1 = hudStructPtr[0xA].x;
					sVar2 = hudStructPtr[0xA].y;
					bVar3 = (sdata->gGT->timer & 1) == 0;
					sVar17 = (u_short)bVar3 << 2;
					partTimeVariable5 = ((u_int)bVar3 << 0x12) >> 0x10;
				}

				// Draw the "st", "nd", "rd" suffix after "1st, 2nd, 3rd, etc"
				// "Placment" TYPO IN THE CHAT --Super
				DrawPlacmentSuffix(sVar1, sVar2, playerStruct, (short)partTimeVariable5);

				// if more than 2 players
				if (2 < sdata->gGT->numPlayers)
				{
					// pointer to OT memory
					ptrOT = sdata->gGT->camera110_UI.ptrOT;

					// position, from hud struct
					sVar1 = hudStructPtr[4].x;
					sVar2 = hudStructPtr[4].y;

					// gGT->backBuffer
					backBuffer = sdata->gGT->backBuffer;

					// Get Color Data
					ppuVar5 = (u_char **)&data.ptrColor[sVar17];

					// Four colors, one for each corner
					local_7c = *ppuVar5[0];
					local_78 = *ppuVar5[1];
					local_74 = *ppuVar5[2];
					local_70 = *ppuVar5[3];

					// icon pointer, specifically for the big rank icons that start at 0x19
					iconPtr = sdata->gGT->ptrIcons[(int)playerStruct->driverRank + 0x19];
					LAB_80053aec:

					DecalHUD_DrawPolyGT4
					(
						// icon pointer
						iconPtr,

						// position
						(int)sVar1,
						(int)sVar2,

						&backBuffer->primMem,

						ptrOT,

						// color data
						local_7c,
						local_78,
						local_74,
						local_70,

						0, 0x1000
					);
				}
			}

			// if you are in Relic Race, or Battle, or Time Trial
			else
			{
				// If you're in end-of-race and Battle
				if ((partTimeVariable5 & 0x200020) == 0x200020)
				{
					partTimeVariable5 = (u_int)((sdata->gGT->timer & 1) == 0);

					// Draw the "st", "nd", "rd" suffix after "1st, 2nd, 3rd, etc"
					DrawPlacmentSuffix(hudStructPtr[0xA].x, hudStructPtr[0xA].y, playerStruct, (short)(partTimeVariable5 << 2));

					sVar1 = hudStructPtr[4].x;
					sVar2 = hudStructPtr[4].y;

					// pointer to OT memory
					ptrOT = sdata->gGT->camera110_UI.ptrOT;

					// gGT->backBuffer
					backBuffer = sdata->gGT->backBuffer;

					// Get Color Data
					ppuVar5 = (u_char **)&data.ptrColor[partTimeVariable5];

					// Four colors, one for each corner
					local_7c = *ppuVar5[0];
					local_78 = *ppuVar5[1];
					local_74 = *ppuVar5[2];
					local_70 = *ppuVar5[3];

					// pointer to icon
					// get rank icon of each battle team after battle is over
					// OH GOD THIS IS CONVOLUTED and probably wrong --Super
					iconPtr = sdata->gGT->ptrIcons[sdata->gGT->battleSetup.data30[playerStruct->BattleHUD.teamID] + 0x19];

					goto LAB_80053aec;
				}
			}
			LAB_80053af4:

			// UpdateTrackerTargets
			// draw lock-on target for driver, if
			// a missile or warpball is chasing them
			UpdateTrackerTargets(playerStruct);

			// If you're in Battle
			if ((sdata->gGT->gameMode1 & 0x20) != 0)
			{
				// Draw arrows over the heads of other players (not AIs)
				Battle_DrawArrowsOverHeads(playerStruct);
			}

			if
			(
				(
					// if 9 < number of wumpa fruit
					// if you have 10 wumpa fruit
					('\t' < playerStruct->numWumpas) &&

					//if racer hasn't finished the race
					((playerStruct->actionsFlagSet & 0x2000000) == 0)
				) &&
				(
					// draw shining background behind wumpa fruit
					DrawWeaponBackground(hudStructPtr[0x18].x, hudStructPtr[0x18].y, hudStructPtr[0x19].y, playerStruct),

					// If your weapon is not "no weapon"
					playerStruct->heldItemID != '\x0f'
				)
			)
			{
				// draw shining background behind weapon
				DrawWeaponBackground(hudStructPtr[0x16].x, hudStructPtr[0x16].y, hudStructPtr[0x17].y, playerStruct);
			}

			// go to next player
			// thread = thread->sibling
			playerThread = playerThread->siblingThread;

			// next HUD structure
			hudStructPtr += 0x28;

		} while (playerThread != 0);
	}

	if (sdata->WrongWayDirection_bool != cVar22)
	{

		sdata->framesDrivingSameDirection = 0;
		sdata->WrongWayDirection_bool = cVar22;
	}

	sdata->framesDrivingSameDirection++;

	// if number of screens is 1
	if (sdata->gGT->numPlayers == '\x01')
	{
		playerStruct = sdata->gGT->drivers[0];

		DrawRaceClock(0x14, 8, 0, playerStruct);

		turboThread = 0;
		turboThreadObject = 0;

		// If Turbo Counter Cheat is Enabled
		if ((sdata->gGT->gameMode1 & 0x8000000) != 0)
		{

			// Get number of boosts
			sVar1 = playerStruct->numTurbos;

			// If number of boosts is not zero
			if (sVar1 != 0)
			{
				// Read pointer from address
				turboThread = sdata->gGT->threadBuckets[TURBO].thread;

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
					sVar1 = sdata->TurboDisplayPos_Only1P--;
				}
			}

			// If you have more than 3 boosts, and
			// display counter is not fully on screen
			else
			{

				// Animate counter to move onto screen
				sVar1 = sdata->TurboDisplayPos_Only1P++;

				// If pointer == nullptr
				if (i == 0)
				{
					LAB_80053c98:
					// If counter is off screen
					if (sdata->TurboDisplayPos_Only1P < 1)
					{
						// set svar1 to display position
						// does the "else" get skipped?
						goto LAB_80053cac;
					}

					// If counter is on screen
					// decrease boost counter,
					// does the "else" get skipped?
					goto LAB_80053cd4;
				}
			}

			// Set display position value
			sdata->TurboDisplayPos_Only1P = sVar1;

			// If display counter is on screen (fully or not fully)
			if (sdata->TurboDisplayPos_Only1P != 0)
			{
				// Interpolate the turbo counter slide in from the right
				InterpolatePosition2D_Linear(&local_38, 0x2c8, 0x20, 500, 0x20, sdata->TurboDisplayPos_Only1P, 10);

				// The actual counter number will continue to
				// increase past 1000, but the on-screen text
				// will cap at 999

				// If you have less than 1000 boosts
				if (playerStruct->numTurbos < 1000)
				{
					// DAT_8008d54c
					// %d

					// build string for on-screen boost counter
					sprintf((char *)&wumpaModel_PosX, &sdata->s_intSpace[0]);
				}

				// If you have more than 1000 boosts
				else
				{
					// 8d544
					// "999" <-- ascii string, not 2-u_char value

					// Cap the on-screen counter at 999
					sprintf((char *)&wumpaModel_PosX, &sdata->s_999[0]);
				}

				// "Turbos"
				i = DecalFont_GetLineWidth(sdata->lngStrings[0x92c], 1);

				// Draw the string
				DecalFont_DrawLine((char *)&wumpaModel_PosX, (int)(((u_int)local_38 - i) * 0x10000) >> 0x10, (int)local_36, 1, 0x4022);

				// DAT_8008d550
				// %s

				// "Turbos"
				sprintf((char *)&wumpaModel_PosX, &sdata->s_str[0], sdata->lngStrings[0x92c]);

				// Draw the string
				DecalFont_DrawLine((char *)&wumpaModel_PosX, (int)(short)local_38, (int)local_36, 1, 0x4000);

				backBuffer = sdata->gGT->backBuffer;
				primMemCurr = backBuffer->primMem.curr;
				TurboCounterBar = 0;

				if (*(int *)primMemCurr <= backBuffer->primMem.unk1)
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
				TurboCounterBar->x0 = local_38 - 0xaa;
				TurboCounterBar->y0 = local_36 + 9;
				TurboCounterBar->x1 = local_38 + 0x32;
				TurboCounterBar->y1 = local_36 + 9;
				TurboCounterBar->x2 = local_38 - 0x96;
				TurboCounterBar->y2 = local_36 + 0x12;
				TurboCounterBar->x3 = local_38 + 0x32;
				TurboCounterBar->y3 = local_36 + 0x12;

				// pointer to OT memory
				primMemCurr = sdata->gGT->camera110_UI.ptrOT;

				*(int*)TurboCounterBar = *primMemCurr | 0x8000000;
				*primMemCurr = (u_int)TurboCounterBar & 0xffffff;
			}
		}
	}

	// if number of screens is not 1 (multiplayer)
	else
	{

		// if you have a time limit (battle)
		if ((sdata->gGT->gameMode1 & 0x10000) != 0)
		{
			// draw countdown clock
			DrawCountdownClock(0xd7,0x68,2);
		}
	}

	if
	(
		(
			(
				// if number of screens is 1
				(sdata->gGT->numPlayers == '\x01') &&

				// if ptr_map is valid
				(levPtrMap != 0)
			) &&
			(
				// if want to draw map, not speedometer
				(sdata->HudAndDebugFlags & 8) == 0
			)
		) ||

		(
			(
				// if number of screens is 3
				sdata->gGT->numPlayers == '\x03' &&

				// if ptr_map is valid
				(levPtrMap != 0)
			)
		)
	)
	{
		local_30[0] = 0;

		Map_DrawDrivers(levPtrMap, sdata->gGT->threadBuckets[PLAYER].thread, local_30);

		Map_DrawDrivers(levPtrMap, sdata->gGT->threadBuckets[ROBOT].thread, local_30);

		// Draw all ghosts on 2D map
		Map_DrawGhosts(levPtrMap, sdata->gGT->threadBuckets[GHOST].thread);

		// Draw all "Tracking" warpballs on 2D map
		Map_DrawTracking(levPtrMap, sdata->gGT->threadBuckets[TRACKING].thread);

		// if ptr_map is valid
		if (levPtrMap != 0)
		{

			// If number of screens is 1
			if (sdata->gGT->numPlayers == '\x01')
			{
				// pointer to backBuffer
				backBuffer = sdata->gGT->backBuffer;

				// pointer to OT memory
				ptrOT = sdata->gGT->camera110_UI.ptrOT;

				// posX
				partTimeVariable4 = 500;

				// two halves of the map textures
				icon1 = sdata->gGT->ptrIcons[3];
				icon2 = sdata->gGT->ptrIcons[4];

				// posY
				local_74 = 0xc3;
			}

			// if number of screens is not 1
			else
			{
				// posX
				partTimeVariable4 = 0x1b8;

				// if number of screens is not 3
				if (sdata->gGT->numPlayers != '\x03') goto LAB_80054040;

				// This happens only if number of screens is 3
				// pointer to backBuffer
				backBuffer = sdata->gGT->backBuffer;

				// pointer to OT memory
				ptrOT = sdata->gGT->camera110_UI.ptrOT;

				// two halves of the map textures
				icon1 = sdata->gGT->ptrIcons[3];
				icon2 = sdata->gGT->ptrIcons[4];

				// posY
				local_74 = 0xcd;
			}

			// Draw the map
			Map_DrawMap
			(
				// top half and bottom half
				icon1, icon2,

				// X and Y
				partTimeVariable4, local_74,

				// Pointer to primary memory
				&backBuffer->primMem,

				// pointer to OT memory
				ptrOT,

				// color, in this case white
				1
			);
		}
	}
	LAB_80054040:
	bVar3 = false;

	// loop counter
	levPtrMap = 0;

	// if number of screens is not 0
	if (sdata->gGT->numPlayers != '\0')
	{
		i = 0;

		// for(int levPtrMap = 0; levPtrMap < numScreens; levPtrMap++)
		do
		{
			// pointer to array of pointers for each driver (9900C, 99010, etc)
			playerStruct = sdata->gGT->drivers[i];

			// pointer to each player's camera110 buffer
			cam110 = &sdata->gGT->camera110[playerStruct->driverID];

			if
			(
				(
					//if racer finished the race
					((playerStruct->actionsFlagSet & 0x2000000) != 0) &&

					// If you're not in Arcade or Time Trial
					((sdata->gGT->gameMode1 & 0x420000) == 0)
				) &&
				(
					(
						// cooldown is finished
						sdata->gGT->timerEndOfRaceVS == 0 ||

						// cooldown has not progressed far,
						// so you still need to draw "Finished" and "Loser"
						(0x96 < sdata->gGT->timerEndOfRaceVS)
					)
				)
			)
			{

				if
				(
					// player structure + 0x482 is your rank in the race
					// 0 = 1st place, 1 = 2nd place, 2 = 3rd place, etc

					// Basically, out of all human players, if you did not come in last
					((int)playerStruct->driverRank < (int)sdata->gGT->numPlayers - 1) &&

					// If you're not in Battle Mode (winner of battle mode wont be in this function)
					((sdata->gGT->gameMode1 & 0x20) == 0)
				)
				{

					// Position is the same regardless of win or lose

					// Midpoint between camera110 Start X and End X
					partTimeVariable3 = (u_int)cam110->rect.x + ((int)((u_int)cam110->rect.w << 0x10) >> 0x11);

					// Midpoint between camera110 Start Y and End Y
					partTimeVariable5 = (u_int)cam110->rect.y + ((int)((u_int)cam110->rect.h << 0x10) >> 0x11);

					// FINISHED!
					pbVar6 = sdata->lngStrings[0x78];
				}

				// If you came in last place, or you're in battle
				else
				{
					// Position is the same regardless of win or lose

					// Midpoint between camera110 Start X and End X
					partTimeVariable3 = (u_int)cam110->rect.x + ((int)((u_int)cam110->rect.w << 0x10) >> 0x11);

					// Midpoint between camera110 Start Y and End Y
					partTimeVariable5 = (u_int)cam110->rect.y + ((int)((u_int)cam110->rect.h << 0x10) >> 0x11);

					// LOSER!
					pbVar6 = sdata->lngStrings[0x50c];
				}

				// In some cases, this cuts off bits, but sometimes
				// [number] * 0x10000 >> 0x10 = [number]

				DecalFont_DrawLine(pbVar6, partTimeVariable3 * 0x10000 >> 0x10, (partTimeVariable5 - 0x1e) * 0x10000 >> 0x10, 1, 0xffff8000);

				if
				(
					// If you press Cross or Start
					((sdata->gGamepads->gamepad[i].buttonsTapped & 0x1010) != 0) &&

					// If you're in End-Of-Race menu
					((sdata->gGT->gameMode1 & 0x200000) != 0)
				)
				{
					// make "Finished" and "Loser" disappear, start
					// drawing the on-screen comments
					sdata->gGT->timerEndOfRaceVS = 0x96;
				}
			}

			//if item roll is not done
			if (playerStruct->itemRollTimer != 0)
			{
				bVar3 = true;
			}

			// increment the iteration counter
			levPtrMap++;

			i++;

		// for(int levPtrMap = 0; levPtrMap < numScreens; levPtrMap++)
		} while (levPtrMap < (int)sdata->gGT->numPlayers);
	}
	if
	(
		(
			// If game is not paused
			((sdata->gGT->gameMode1 & 0xf) == 0) &&
			
			//item roll is done
			(!bVar3)
		) &&

		// If you're drawing Weapon Roulette (randomizing)
		((sdata->gGT->gameMode1 & 0x800000) != 0)
	)
	{
		// stop weapon shuffle sound
		OtherFX_Stop2(0x5d);

		// disable the randomizing effect in the HUD
		sdata->gGT->gameMode1 &= 0xff7fffff;
	}

return;
}