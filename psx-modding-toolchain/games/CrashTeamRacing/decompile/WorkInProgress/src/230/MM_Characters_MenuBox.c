#include <ovr_230.h>

// character selection menu, 
// MenuBox_FuncPtr for menuBox: 0x800b46b4;

void MM_Characters_MenuBox()
{
	u_char numScreens;
	int bVar2;
	int bVar3;
	u_short characterSelectFlags5bit;
	short* psVar5;
	short sVar6;
	short nextDriver;
	int iVar8;
	u_int button;
	short sVar10;
	int globalIconPerPlayerCopy5;
	u_char* puVar12;
	u_int characterSelectType;
	u_int fontType;
	u_int* iconColor;
	u_int globalIconPerPlayerCopy3;
	int nextDriverCopy;
	short* psVar18;
	int globalIconPerPlayerCopy4;
	u_short globalIconPerPlayerCopy;
	u_int globalIconPerPlayerCopy2;
	short* psVar22;
	u_short* globalIconPerPlayerPtr2;
	int iVar24;
	u_int k;
	u_short* puVar26;
	short globalIconPerPlayer[4];
	short local_80;
	short local_7e;
	u_short local_7c;
	u_short local_7a;
	u_char auStack120[8];

	u_char colorR;
	u_char colorG;
	u_char colorB;

	u_short local_68;
	u_short local_66;
	u_short local_64;
	u_short local_62;

	u_int local_60;
	u_int local_5c;
	u_int local_58;
	u_int local_54;

	short local_50;
	short* globalIconPerPlayerPtr;

	int i;
	int j;
	short transitionFrames;
	int posX;
	int posY;
	u_int characterSelectString;
	short playerIcon;
	int direction;
	
	// loop counter
	i = 0;
	
	for (i = 0; i < 4; i++)
	{
		globalIconPerPlayer[i] = OVR_230.characterIcon[data.characterIDs[i]];
	}
	
	// if menu is in focus
	if (OVR_230.isMenuTransitioning == 1) 
	{
		MM_Characters_SetMenuLayout();
		MM_Characters_DrawWindows(1);
		transitionFrames = OVR_230.transitionFrames;
	}
	
	// if transitioning (in or out)
	else
	{
		transitionFrames = OVR_230.transitionFrames;
		if (OVR_230.isMenuTransitioning < 2) 
		{
			// if transitioning in
			if (OVR_230.isMenuTransitioning == 0) 
			{
				MM_TransitionInOut(DAT_800b5a3c, (int)OVR_230.transitionFrames, 8);
				MM_Characters_SetMenuLayout();
				MM_Characters_DrawWindows(1);
		
				// subtract frame
				transitionFrames = OVR_230.transitionFrames--;
		
				// if no more frames
				if (OVR_230.transitionFrames == 0) 
				{
					// menu is now in focus
					OVR_230.isMenuTransitioning = 1;
					transitionFrames = OVR_230.transitionFrames;
				}
			}
		}
		else 
		{
			// if transitioning out
			if (OVR_230.isMenuTransitioning == 2) 
			{
				MM_TransitionInOut(DAT_800b5a3c, (int)OVR_230.transitionFrames, 8);
				MM_Characters_SetMenuLayout();
				MM_Characters_DrawWindows(1);
		
				// increase frame
				OVR_230.transitionFrames++;
				transitionFrames = OVR_230.transitionFrames;
				
				// if more than 12 frames
				if (OVR_230.transitionFrames > 12) 
				{
					// Make a backup of the characters
					// you selected in character selection screen
					MM_Characters_BackupIDs();
			
					// if returning to main menu
					if (OVR_230.movingToTrackMenu == 0) 
					{
						MM_JumpTo_Title_Returning();
						MM_Characters_HideDrivers();
						return;
					}
			
					// if going to track/cup selection
					MM_Characters_HideDrivers();
			
					// if you are in a cup
					if (sdata->gGT->gameMode2 & 0x10) 
					{
						sdata->ptrDesiredMenuBox = &OVR_230.menubox_cupSelect;
						MM_CupSelect_Init();
						return;
					}
			
					// if going to track selection
					sdata->ptrDesiredMenuBox = &OVR_230.menubox_trackSelect;
					MM_TrackSelect_Init();
					return;
				}
			}
		}
	}
	OVR_230.transitionFrames = transitionFrames;

	switch(OVR_230.characterSelectNumScreens)
	{
		default:
			goto dontDrawSelectCharacter;
	
		// 3P character selection
		case 2:
	
			// If you have a lot of characters unlocked, do not draw SELECT CHARACTER
			if (OVR_230.isRosterExpanded) goto dontDrawSelectCharacter;
	
			// SELECT
			DecalFont_DrawLine
			(
				sdata->lngStrings[97],
				(int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9c) + 0x9c) * 0x10000) >> 0x10,
				(int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9e) + 0x14) * 0x10000) >> 0x10,
				1, 0xffff8000
			);
			characterSelectType = 1;
		
			// CHARACTER
			characterSelectString = sdata->lngStrings[98];
			
			posX = (int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9c) + 0x9c) * 0x10000) >> 0x10;
			posY = *(short *)(DAT_800b5a3c + 0x9e) + 0x26;
			break;
		
		// 4P character selection
		case 3:
		
			// If Fake Crash is unlocked, do not draw "Select Character"
			if (sdata->gameProgress.Unlocks.characters_tracks & 0x800) goto dontDrawSelectCharacter;
		
			// SELECT
			DecalFont_DrawLine
			(
				sdata->lngStrings[97],
				(int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9c) + 0xfc) * 0x10000) >> 0x10,
				(int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9e) + 8) * 0x10000) >> 0x10,
				3, 0xffff8000
			);
			characterSelectType = 3;
		
			// CHARACTER
			characterSelectString = sdata->lngStrings[98];
		
			posX = (int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9c) + 0xfc) * 0x10000) >> 0x10;
			posY = *(short *)(DAT_800b5a3c + 0x9e) + 0x18;
			break;
		
		// If you are in 1P or 2P character selection,
		// when you do NOT have a lot of characters selected
		case 4:
		case 5:
			characterSelectType = 1;
		
			// SELECT CHARACTER
			characterSelectString = sdata->lngStrings[96];
		
			posX = (int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9c) + 0xfc) * 0x10000) >> 0x10;
			posY = *(short *)(DAT_800b5a3c + 0x9e) + 10;
	}
	
	// Draw String
	DecalFont_DrawLine(characterSelectString, posX, posY, characterSelectType, 0xffff8000);
	
	dontDrawSelectCharacter:

	// if number of players is not zero
	if (sdata->gGT->numScreens)
	{
		globalIconPerPlayerPtr = &globalIconPerPlayer[0];

		for (i = 0; i < sdata->gGT->numScreens; i++)
		{
			characterSelectFlags5bit = (u_short)(1 << (i & 0x1f));
			globalIconPerPlayerCopy = globalIconPerPlayerPtr[i];
			globalIconPerPlayerCopy2 = globalIconPerPlayerCopy;
		
			MM_Characters_AnimateColors(auStack120, i, (int)(short)(sdata->characterSelectFlags & characterSelectFlags5bit));
			
			puVar26 = (u_short *)(DAT_800b5a18 + (int)(short)globalIconPerPlayerCopy * 6);
			
			if
			(
				(OVR_230.isMenuTransitioning == 1) && 
				(
					// get input from this player
					button = sdata->buttonTapPerPlayer[i], 
				
					// If you press the D-Pad, or Cross, Square, Triangle, Circle
					button & 0x4007f
				)
			)
			{
				// if character has not been selected by this player
				if (((int)(short)sdata->characterSelectFlags >> (i & 0x1f) & 1U) == 0)
				{
					// If you pressed any of the D-pad buttons
					if ((button & 0xf) != 0) 
					{
						local_50 = 0;
				
						// If you do not press Up
						if ((button & 1) == 0) 
						{	
							// If you do not press Down
							if ((button & 2) == 0) 
							{
								// This must be if you press Left,
								// because the variable will change
								// if it is anything that isn't Left
									
								// Left
								direction = 2;
					
								// If you press Left
								if ((button & 4) != 0) goto LAB_800aec08;
					
								// At this point, you must have pressed Right
					
								// Right
								direction = 3;
					
								// Move down character selection list
								(&DAT_800b59e8)[i] = 1;
							}
				
							// If you pressed Down
							else 
							{
								// Down
								direction = 1;
				
								// Move down character selection list
								(&DAT_800b59e8)[i] = 1;
							}
						}
			
						// If you pressed Up
						else 
						{
							// Up
							direction = 0;
							LAB_800aec08:
							// If you press Up or Left
				
							// Move up character selection list
							(&DAT_800b59e8)[i] = 0xffff;
						}
			
						j = i;
						globalIconPerPlayerPtr2 = &globalIconPerPlayerPtr[j];
						globalIconPerPlayerCopy3 = globalIconPerPlayerCopy2;
						do
						{
							globalIconPerPlayerCopy2 = MM_Characters_GetNextDriver(direction, globalIconPerPlayerCopy3);
							globalIconPerPlayerCopy4 = globalIconPerPlayerCopy2;
							
							if (globalIconPerPlayerCopy2 == globalIconPerPlayerCopy3) 
							{
								local_50 = 1;
								nextDriver = MM_Characters_GetNextDriver(direction, (int)(short)*globalIconPerPlayerPtr2);
								nextDriverCopy = (int)nextDriver;
								globalIconPerPlayerCopy2 = MM_Characters_GetNextDriver((u_int)(u_char)(&DAT_800b5384)[direction], nextDriverCopy);
								globalIconPerPlayerCopy5 = (int)(short)globalIconPerPlayerCopy2;

								if
								(
									(((globalIconPerPlayerCopy5 == globalIconPerPlayerCopy4) || (nextDriverCopy == globalIconPerPlayerCopy4)) || (nextDriverCopy == globalIconPerPlayerCopy5)) ||
									(button = MM_Characters_boolIsInvalid(globalIconPerPlayerPtr, globalIconPerPlayerCopy5, j), (button & 0xffff) != 0)
								)
								{
									nextDriver = MM_Characters_GetNextDriver((u_int)(u_char)(&DAT_800b5384)[direction], (int)(short)*globalIconPerPlayerPtr2);
									globalIconPerPlayerCopy5 = (int)nextDriver;
									globalIconPerPlayerCopy2 = MM_Characters_GetNextDriver(direction, globalIconPerPlayerCopy5);
									globalIconPerPlayerCopy4 = (int)(short)globalIconPerPlayerCopy2;

									if
									(
										((globalIconPerPlayerCopy4 == globalIconPerPlayerCopy3) || (globalIconPerPlayerCopy5 == globalIconPerPlayerCopy3)) ||
										(
											(globalIconPerPlayerCopy5 == globalIconPerPlayerCopy4 ||
											(button = MM_Characters_boolIsInvalid(globalIconPerPlayerPtr, globalIconPerPlayerCopy4, j), (button & 0xffff) != 0))
										)
									)
									{
										nextDriver = MM_Characters_GetNextDriver(direction, (int)(short)*globalIconPerPlayerPtr2);
										globalIconPerPlayerCopy5 = (int)nextDriver;
										globalIconPerPlayerCopy2 = MM_Characters_GetNextDriver((u_int)(u_char)(&DAT_800b5388)[direction], globalIconPerPlayerCopy5);
										globalIconPerPlayerCopy4 = (int)(short)globalIconPerPlayerCopy2;

										if
										(
											((globalIconPerPlayerCopy4 == globalIconPerPlayerCopy3) || (globalIconPerPlayerCopy5 == globalIconPerPlayerCopy3)) ||
											(
												(
													globalIconPerPlayerCopy5 == globalIconPerPlayerCopy4 ||
													(button = MM_Characters_boolIsInvalid(globalIconPerPlayerPtr, globalIconPerPlayerCopy4, j), (button & 0xffff) != 0)
												)
											)
										) 
										{
											nextDriver = MM_Characters_GetNextDriver((u_int)(u_char)(&DAT_800b5388)[direction], (int)(short)*globalIconPerPlayerPtr2);
											globalIconPerPlayerCopy5 = (int)nextDriver;
											globalIconPerPlayerCopy2 = MM_Characters_GetNextDriver(direction, globalIconPerPlayerCopy5);
											globalIconPerPlayerCopy4 = (int)(short)globalIconPerPlayerCopy2;

											if
											(
												(((globalIconPerPlayerCopy4 == globalIconPerPlayerCopy3) || (globalIconPerPlayerCopy5 == globalIconPerPlayerCopy3)) || (globalIconPerPlayerCopy5 == globalIconPerPlayerCopy4)) ||
												(button = MM_Characters_boolIsInvalid(globalIconPerPlayerPtr, globalIconPerPlayerCopy4, j), (button & 0xffff) != 0)
											)
											{
												globalIconPerPlayerCopy2 = (u_int)*globalIconPerPlayerPtr2;
											}
										}
									}
								}
							}
							bVar2 = false;
				
							// If number of players is not zero
							if (sdata->gGT->numScreens) 
							{
								for (k = 0; k < sdata->gGT->numScreens; k++)
								{
									if((k != j) && ((short)globalIconPerPlayerCopy2 == globalIconPerPlayerPtr[k]))
									{
										bVar2 = true;
										break;
									}
								}
							}
							if (globalIconPerPlayerCopy3 << 0x10 != globalIconPerPlayerCopy2 << 0x10) 
							{
								// Play sound
								OtherFX_Play(0, 1);
							}
							if (local_50 != 0)
							{
								bVar3 = !bVar2;
								bVar2 = false;
								if (bVar3) break;
								globalIconPerPlayerCopy2 = (u_int)*globalIconPerPlayerPtr2;
							}
							globalIconPerPlayerCopy3 = globalIconPerPlayerCopy2;
						} while (bVar2);
					}
					globalIconPerPlayerCopy = (u_short)globalIconPerPlayerCopy2;
			
					// if number of players is not zero
					if (sdata->gGT->numScreens) 
					{
						for (j = 0; j < sdata->gGT->numScreens; j++)
						{
							if ((j != i) && ((short)globalIconPerPlayerCopy2 == globalIconPerPlayerPtr[j]))
							{
								globalIconPerPlayerCopy2 = (u_int)(u_short)globalIconPerPlayerPtr[i];
							}
							globalIconPerPlayerCopy = (u_short)globalIconPerPlayerCopy2;
						}
					}
			
					// If this player pressed Cross or Circle
					if (((sdata->buttonTapPerPlayer)[i] & 0x50) != 0) 
					{
						// this player has now selected a character
						sdata->characterSelectFlags = sdata->characterSelectFlags | (u_short)(1 << (i & 0x1fU));
			
						numScreens = sdata->gGT->numScreens;
			
						// Play sound
						OtherFX_Play();
			
						// if all players have selected their characters
						if ((int)(short)sdata->characterSelectFlags == ((0xff << ((u_int)numScreens & 0x1f) ^ 0xffU) & 0xff)) 
						{
							// move to track selection
							OVR_230.movingToTrackMenu = 1;
							OVR_230.isMenuTransitioning = 2;
						}
					}
			
					if
					(
						// if this is the first iteration of the loop
						((i & 0xffff) == 0) && 
				
						// if you press Square or Triangle
						((sdata->buttonTapPerPlayer[0] & 0x40020) != 0)
					) 
					{
						// return to main menu
						OVR_230.movingToTrackMenu = 0;
						OVR_230.isMenuTransitioning = 2;
			
						// Play sound
						OtherFX_Play(2, 1);
					}
				}
				else 
				{
					// if you press Square or Triangle
					if ((button & 0x40020) != 0) 
					{
						// Play sound
						OtherFX_Play(2, 1);
			
						// this player has de-selected their character
						sdata->characterSelectFlags = sdata->characterSelectFlags & ~characterSelectFlags5bit;
					}
				}
		
				// clear input
				sdata->buttonTapPerPlayer[i] = 0;
			}
			globalIconPerPlayerPtr[i] = globalIconPerPlayerCopy;
			iVar24 = (int)(short)globalIconPerPlayerCopy * 10 + DAT_800b5a3c;
			local_80 = *(short *)(iVar24 + 6) + *puVar26;
			local_7c = 0x34;
			local_7a = 0x21;
			local_7e = *(short *)(iVar24 + 8) + puVar26[1];
		
			// if player has not selected a character
			if (((int)(short)sdata->characterSelectFlags >> (i & 0x1f) & 1U) == 0) 
			{
				// draw string
				// "1", "2", "3", "4", above the character icon
				DecalFont_DrawLine
				(
					(&PTR_DAT_800aba28_800b5374)[i],
					(int)(((u_int)*(u_short *)(iVar24 + 6) + (u_int)*puVar26 + -6) * 0x10000) >> 0x10,
					(int)(((u_int)*(u_short *)(iVar24 + 8) + (u_int)puVar26[1] + -3) * 0x10000) >> 0x10,
					1, 4
				);
				puVar12 = auStack120;
			}
			else
			{
				puVar12 = &DAT_800b538c;
			}
		
			DrawBoxOutline_HighLevel(&local_80, puVar12, 0, sdata->gGT->backBuffer->otMem.startPlusFour);
		}
	}
	
	MM_Characters_ClearInactivePlayers();
	
	psVar18 = DAT_800b5a18 + 1;
	psVar22 = DAT_800b5a18;
	
	// loop through character icons

	for (i = 0; i < 0xf; i++)
	{
		iVar8 = psVar18[4];
		if
		(
			// If Icon is unlocked (from array of icons)
			(iVar8 == -1) ||
			
			// if character is unlocked
			// from 4-byte variable that handles all rewards
			// also the variable written by cheats
			(((u_int)(&sdata->gameProgress.Unlocks.characters_tracks)[iVar8] >> (psVar18[4] & 0x1fU) & 1) != 0)
		) 
		{
			iconColor = &OVR_230.characterSelect_NeutralColor;
		
			// if number of players is not zero
			if (sdata->gGT->numScreens != 0) 
			{
				for (j = 0; j < sdata->gGT->numScreens; j++)
				{
					if
					(
						((short)i == globalIconPerPlayer[j]) &&
			
						// if player selected a character
						 (((int)(short)sdata->characterSelectFlags >> (j & 0x1fU) & 1U) != 0)
					)
					{
						iconColor = &OVR_230.characterSelect_ChosenColor;
					}
				}
			}
		
			iVar8 = (int)(short)i * 10 + DAT_800b5a3c;
			
			// Draw Character Icon
			DecalHUD_DrawPolyGT4_Safe
			(
				sdata->gGT->ptrIcons[data.MetaDataCharacters[(int)psVar18[3]].iconID],
				(int)*(short *)(iVar8 + 6) + (int)*psVar22 + 6,
				(int)*(short *)(iVar8 + 8) + (int)*psVar18 + 4,

				&sdata->gGT->backBuffer->primMem,
				sdata->gGT->camera110_UI.ptrOT,

				*iconColor, *iconColor, *iconColor, *iconColor, 1, 0x1000
			);
		}
		psVar5 = DAT_800b5a18;

		psVar18 += 6;
		psVar22 += 6;
	}
	
	for (i = 0; i < 4; i++)
	{
		data.characterIDs[i] = psVar5[(int)globalIconPerPlayer[i] * 6 + 4];
	}
	
	// if number of players is not zero
	if (sdata->gGT->numScreens) 
	{
		for (i = 0; i < sdata->gGT->numScreens; i++)
		{
			j = i;
			playerIcon = globalIconPerPlayer[j];
			psVar22 = DAT_800b5a18 + (int)playerIcon * 6;
		
			// if player has not selected a character
			if (((int)(short)sdata->characterSelectFlags >> (j & 0x1f) & 1U) == 0) 
			{
				MM_Characters_AnimateColors
				(
					&colorR, j,
						
					// flags of which characters are selected
					(int)(short)(sdata->characterSelectFlags & (u_short)(1 << (j & 0x1f)))
				);
					
				colorR = (u_char)((int)((u_int)colorR << 2) / 5);
				colorG = (u_char)((int)((u_int)colorG << 2) / 5);
				colorB = (u_char)((int)((u_int)colorB << 2) / 5);

				iVar8 = (int)playerIcon * 10 + DAT_800b5a3c;
				local_80 = *(short *)(iVar8 + 6) + *psVar22 + 3;
				local_7c = 0x2e;
				local_7a = 0x1d;
				local_7e = *(short *)(iVar8 + 8) + psVar22[1] + 2;

				// this draws the flashing blue square that appears when you highlight a character in the character select screen
				CTR_Box_DrawSolidBox
				(
					&local_80, &colorR,
					sdata->gGT->backBuffer->otMem.startPlusFour,
					&sdata->gGT->backBuffer->primMem
				);
			}
			if
			(
				((&DAT_800b5a24)[j] == 0) &&
				((&DAT_800b59f8)[j] == (&DAT_80086e84)[j])
			) 
			{
				// get number of players
				numScreens = sdata->gGT->numScreens;
		
				// if number of players is 1 or 2
				fontType = 3;
		
				// if number of players is 3 or 4
				if (numScreens >= 3) fontType = 2;
		
				iVar8 = j * 10 + DAT_800b5a3c;
				sVar10 = *(short *)(iVar8 + 0xa8) + (DAT_800b5a0c + j * 2)[1];
				sVar6 = (short)((((u_int)(numScreens < 3) ^ 1) << 0x12) >> 0x10);

				if ((numScreens == 4) && (j > 1)) sVar6 = sVar10 + sVar6 - 6;
				else							  sVar6 = sVar10 + DAT_800b5a38 + sVar6;
		
				// draw string
				DecalFont_DrawLine
				(
					sdata->lngStrings[data.MetaDataCharacters[(int)psVar22[4]].name_LNG_long],
					(int)(((u_int)*(u_short *)(iVar8 + 0xa6) + (u_int)(u_short)DAT_800b5a0c[j * 2] + (((int)((u_int)DAT_800b5a30 << 0x10) >> 0x10) - ((int)((u_int)DAT_800b5a30 << 0x10) >> 0x1f) >> 1)) * 0x10000) >> 0x10,
					(int)sVar6, fontType, 0xffff8000
				);
			}
			
			// rotation of each driver, 90 degrees difference
			psVar22 = (short *)((int)&DAT_800b5a00 + i * 2);
		
			// spin driver each frame
			*psVar22 += 0x40;
		}
	}
	
	psVar18 = DAT_800b5a18 + 1;
	psVar22 = DAT_800b5a18;
	
	// loop through all icons

	for (i = 0; i < 0xf; i++)
	{
		iVar8 = (u_int)(u_short)psVar18[4] << 0x10;
		
		if
		(
			// If Icon is unlocked (from array of icons)
			(iVar8 >> 0x10 == -1) ||
			
			// if character is unlocked
			// from 4-byte variable that handles all rewards
			// also the variable written by cheats
			(((u_int)(&sdata->gameProgress.Unlocks.characters_tracks)[iVar8 >> 0x15] >> (psVar18[4] & 0x1fU) & 1) != 0)
		) 
		{
			iVar8 = (int)(short)i * 10 + DAT_800b5a3c;
			local_68 = *(short *)(iVar8 + 6) + *psVar22;
			local_64 = 0x34;
			local_62 = 0x21;
			local_66 = *(short *)(iVar8 + 8) + *psVar18;
		
			// Draw 2D Menu rectangle background
			DrawTextBackground(&local_68, 0, sdata->gGT->backBuffer->otMem.startPlusFour);
		}

		// advence both short* arrays by 6 shorts,
		// which is 12 (0xc) bytes, size of
		// character icon buffer
		psVar18 += 6;
		psVar22 += 6;
	}
	
	// if number of players is not zero
	if (sdata->gGT->numScreens != 0) 
	{
		psVar22 = DAT_800b5a0c;

		for (i = 0; i < sdata->gGT->numScreens; i++)
		{
			j = i;
			iVar8 = j * 10 + DAT_800b5a3c;
			
			// store window width and height in one 4-byte variable
			local_5c = CONCAT22(DAT_800b59dc, DAT_800b5a30);
		
			local_60 = CONCAT22(*(short *)(iVar8 + 0xa8) + psVar22[1], *(short *)(iVar8 + 0xa6) + *psVar22);
			
			MM_Characters_AnimateColors(&local_68, j, ((int)(short)sdata->characterSelectFlags >> (j & 0x1f) ^ 1U) & 1);
			
			DrawBoxOutline_HighLevel(&local_60, &local_68, 0, sdata->gGT->backBuffer->otMem.startPlusFour);
			
			// if player selected a character
			if (((int)(short)sdata->characterSelectFlags >> (j & 0x1f) & 1U) != 0) 
			{
				local_58 = local_60;
				local_54 = local_5c;
				for (iVar8 = 0; iVar8 < 2; iVar8++)
				{
					local_58 = CONCAT22((short)((u_int)local_58 >> 0x10) + 2, (short)local_58 + 3);
					local_68 = CONCAT11((char)((int)((u_int)local_68._1_1_ << 2) / 5), (char)((int)((u_int)(u_char)local_68 << 2) / 5));
					local_54 = CONCAT22((short)((u_int)local_54 >> 0x10) + -4, (short)local_54 + -6);
					local_66 = local_66 & 0xff00 | (u_short)(u_char)((int)((u_int)(u_char)local_66 << 2) / 5);
					
					DrawBoxOutline_HighLevel(&local_58, &local_68, 0, sdata->gGT->backBuffer->otMem.startPlusFour);
				}
			}
			psVar22 = psVar22 + 2;
		
			// Draw 2D Menu rectangle background
			DrawTextBackground(&local_60, 9, ((struct OTMem*)sdata->gGT->backBuffer->otMem.startPlusFour)->curr);
			
			local_60 = 0;
		
			BackgroundBlueRect
			(
				&local_60, &DAT_800b5398,
				sdata->gGT->camera110[i].ptrOT + 0xffc, sdata->gGT->backBuffer->primMem
			);
		
		}
	}
	return;
}