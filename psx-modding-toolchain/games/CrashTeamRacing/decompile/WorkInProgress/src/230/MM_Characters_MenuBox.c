// character selection menu, 
// MenuBox_FuncPtr for menuBox: 0x800b46b4;

void MM_Characters_MenuBox()
{
	u_char bVar1;
	char bVar2;
	char bVar3;
	u_short uVar4;
	short *psVar5;
	short sVar6;
	short sVar7;
	int iVar8;
	u_int uVar9;
	short sVar10;
	int iVar11;
	undefined *puVar12;
	undefined4 characterSelectType;
	undefined4 uVar14;
	undefined4 *puVar15;
	u_int uVar16;
	int iVar17;
	short *psVar18;
	int iVar19;
	u_short uVar20;
	u_int uVar21;
	short *psVar22;
	u_short *puVar23;
	int iVar24;
	u_int uVar25;
	u_short *puVar26;
	short globalIconPerPlayer [4];
	short local_80;
	short local_7e;
	undefined2 local_7c;
	undefined2 local_7a;
	undefined auStack120 [8];
	u_char local_70;
	u_char local_6f;
	u_char local_6e;
	undefined2 local_68;
	u_short local_66;
	undefined2 local_64;
	undefined2 local_62;
	undefined4 local_60;
	undefined4 local_5c;
	undefined4 local_58;
	undefined4 local_54;
	short local_50;
	short *local_30;

	int i;
	u_int characterSelectString;
	u_int iu;
	
	// loop counter
	i = 0;
	
	for (i = 0; i < 4; i++)
	{
		globalIconPerPlayer[i] =  OVR_230.characterIcon[data.characterIDs[i]];
	}
	
	// if menu is in focus
	if (OVR_230.isMenuTransitioning == 1) 
	{
		MM_Characters_SetMenuLayout();
		MM_Characters_DrawWindows(1);
		sVar6 = OVR_230.transitionFrames;
	}
	
	// if transitioning (in or out)
	else
	{
		sVar6 = OVR_230.transitionFrames;
		if (OVR_230.isMenuTransitioning < 2) 
		{
			// if transitioning in
			if (OVR_230.isMenuTransitioning == 0) 
			{
				MM_TransitionInOut(DAT_800b5a3c, (int)OVR_230.transitionFrames, 8);
				MM_Characters_SetMenuLayout();
				MM_Characters_DrawWindows(1);
		
				// subtract frame
				sVar6 = OVR_230.transitionFrames--;
		
				// if no more frames
				if (OVR_230.transitionFrames == 0) 
				{
					// menu is now in focus
					OVR_230.isMenuTransitioning = 1;
					sVar6 = OVR_230.transitionFrames;
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
				sVar6 = OVR_230.transitionFrames;
				
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
					if (sdata.gGT->advFlags & 0x10) 
					{
						sdata.ptrDesiredMenuBox = &OVR_230.menubox_cupSelect;
						MM_CupSelect_Init();
						return;
					}
			
					// if going to track selection
					sdata.ptrDesiredMenuBox = &OVR_230.menubox_trackSelect;
					MM_TrackSelect_Init();
					return;
				}
			}
		}
	}
	OVR_230.transitionFrames = sVar6;
	switch(OVR_230.characterSelectNumScreens)
	{
		default:
			goto dontDrawSelectCharacter;
	
		// 3P character selection
		case 2:
	
			// If you have a lot of characters unlocked,
			// do not draw SELECT CHARACTER
			if (OVR_230.isRosterExpanded) goto dontDrawSelectCharacter;
		
			// SELECT
			DecalFont_DrawLine
			(
				sdata.lngStrings[97],
				(int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9c) + 0x9c) * 0x10000) >> 0x10,
				(int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9e) + 0x14) * 0x10000) >> 0x10,
				1, 0xffff8000
			);
			characterSelectType = 1;
		
			// CHARACTER
			characterSelectString = sdata.lngStrings[98];
			
			iVar24 = (int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9c) + 0x9c) * 0x10000) >> 0x10;
			sVar6 = *(short *)(DAT_800b5a3c + 0x9e) + 0x26;
			break;
	
		// 4P character selection
		case 3:
	
			// If Fake Crash is unlocked, do not draw "Select Character"
			if (sdata.gameProgress.Unlocks.characters_tracks & 0x800) goto dontDrawSelectCharacter;
		
			// SELECT
			DecalFont_DrawLine
			(
				sdata.lngStrings[97],
				(int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9c) + 0xfc) * 0x10000) >> 0x10,
				(int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9e) + 8) * 0x10000) >> 0x10,
				3, 0xffff8000
			);
			characterSelectType = 3;
		
			// CHARACTER
			characterSelectString = sdata.lngStrings[98];
		
			iVar24 = (int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9c) + 0xfc) * 0x10000) >> 0x10;
			sVar6 = *(short *)(DAT_800b5a3c + 0x9e) + 0x18;
			break;
	
		// If you are in 1P or 2P character selection,
		// when you do NOT have a lot of characters selected
		case 4:
		case 5:
			characterSelectType = 1;
	
			// SELECT CHARACTER
			characterSelectString = sdata.lngStrings[96];
	
			iVar24 = (int)(((u_int)*(u_short *)(DAT_800b5a3c + 0x9c) + 0xfc) * 0x10000) >> 0x10;
			sVar6 = *(short *)(DAT_800b5a3c + 0x9e) + 10;
	}
	
	// Draw String
	DecalFont_DrawLine(characterSelectString, iVar24, (int)sVar6, characterSelectType, 0xffff8000);
	
	dontDrawSelectCharacter:

	// loop counter
	iu = 0;
	
	// if number of players is not zero
	if (sdata.gGT->numScreens)
	{
		local_30 = globalIconPerPlayer;
	
		for (iu = 0; iu < numPlayers; iu++)
		{
			// copy the loop counter
			sVar6 = (short)iu;
		
			// copy it again
			uVar16 = SEXT24(sVar6);
		
			uVar4 = (u_short)(1 << (uVar16 & 0x1f));
			uVar20 = local_30[uVar16];
			uVar21 = (u_int)uVar20;
		
			MM_Characters_AnimateColors(auStack120, uVar16, (int)(short)(sdata.characterSelectFlags & uVar4));
			
			puVar26 = (u_short *)(DAT_800b5a18 + (int)(short)uVar20 * 6);
			
			if
			(
				(OVR_230.isMenuTransitioning == 1) &&
				(
					// get input from this player
					uVar9 = sdata.buttonTapPerPlayer[uVar16], 
				
					// If you press the D-Pad, or Cross, Square, Triangle, Circle
					uVar9 & 0x4007f
				)
			)
			{
				// if character has not been selected by this player
				if (((int)(short)sdata.characterSelectFlags >> (uVar16 & 0x1f) & 1U) == 0)
				{
					
					// If you pressed any of the D-pad buttons
					if ((uVar9 & 0xf) != 0) 
					{
						local_50 = 0;
			
						// If you do not press Up
						if ((uVar9 & 1) == 0) 
						{	
							// If you do not press Down
							if ((uVar9 & 2) == 0) 
							{
								// This must be if you press Left,
								// because the variable will change
								// if it is anything that isn't Left
								
								// Left
								iVar24 = 2;
				
								// If you press Left
								if ((uVar9 & 4) != 0) goto LAB_800aec08;
				
								// At this point, you must have pressed Right
				
								// Right
								iVar24 = 3;
				
								// Move down character selection list
								(&DAT_800b59e8)[uVar16] = 1;
							}
				
							// If you pressed Down
							else 
							{
								// Down
								iVar24 = 1;
				
								// Move down character selection list
								(&DAT_800b59e8)[uVar16] = 1;
							}
						}
			
						// If you pressed Up
						else 
						{
							// Up
							iVar24 = 0;
							LAB_800aec08:
							// If you press Up or Left
				
							// Move up character selection list
							(&DAT_800b59e8)[uVar16] = 0xffff;
						}
			
						iVar8 = (int)sVar6;
						puVar23 = (u_short *)(local_30 + iVar8);
						uVar16 = uVar21;
						do
						{
							sVar10 = (short)uVar16;
							uVar21 = MM_Characters_GetNextDriver(iVar24, (int)sVar10);
							iVar19 = (int)(uVar21 << 0x10) >> 0x10;
							
							if (uVar21 << 0x10 == uVar16 << 0x10) 
							{
								local_50 = 1;
								sVar7 = MM_Characters_GetNextDriver(iVar24, (int)(short)*puVar23);
								iVar17 = (int)sVar7;
								uVar21 = MM_Characters_GetNextDriver((u_int)(u_char)(&DAT_800b5384)[iVar24], iVar17);
								iVar11 = (int)(short)uVar21;
								if
								(
									(((iVar11 == iVar19) || (iVar17 == iVar19)) || (iVar17 == iVar11)) ||
									(uVar9 = MM_Characters_boolIsInvalid(local_30, iVar11, iVar8), (uVar9 & 0xffff) != 0)
								) 
								{
									sVar7 = MM_Characters_GetNextDriver((u_int)(u_char)(&DAT_800b5384)[iVar24], (int)(short)*puVar23);
									iVar11 = (int)sVar7;
									uVar21 = MM_Characters_GetNextDriver(iVar24, iVar11);
									iVar19 = (int)(short)uVar21;
					
					
									if
									(
										((iVar19 == (int)sVar10) || (iVar11 == (int)sVar10)) ||
										(
											(iVar11 == iVar19 || (uVar9 = MM_Characters_boolIsInvalid(local_30, iVar19, iVar8), (uVar9 & 0xffff) != 0))
										)
									)
									{
										sVar7 = MM_Characters_GetNextDriver(iVar24, (int)(short)*puVar23);
										iVar11 = (int)sVar7;
										uVar21 = MM_Characters_GetNextDriver((u_int)(u_char)(&DAT_800b5388)[iVar24], iVar11);
										iVar19 = (int)(short)uVar21;
										if
										(
											((iVar19 == (int)sVar10) || (iVar11 == (int)sVar10)) ||
											(
												(
													iVar11 == iVar19 ||
													(uVar9 = MM_Characters_boolIsInvalid(local_30, iVar19, iVar8), (uVar9 & 0xffff) != 0)
												)
											)
										) 
										{
						
											sVar7 = MM_Characters_GetNextDriver((u_int)(u_char)(&DAT_800b5388)[iVar24], (int)(short)*puVar23);
											iVar11 = (int)sVar7;
											uVar21 = MM_Characters_GetNextDriver(iVar24, iVar11);
											iVar19 = (int)(short)uVar21;
						
											if
											(
												(((iVar19 == (int)sVar10) || (iVar11 == (int)sVar10)) || (iVar11 == iVar19)) ||
												(uVar9 = MM_Characters_boolIsInvalid(local_30, iVar19, iVar8), (uVar9 & 0xffff) != 0)
											)
											{
												uVar21 = (u_int)*puVar23;
											}
										}
									}
								}
							}
							bVar2 = false;
				
							// loop counter
							i = 0;
				
							// If number of players is not zero
							if (sdata.gGT->numScreens) 
							{
								iVar11 = 0;
				
								// for i = 0; i < numPlayers; i++
								do 
								{
									if ((iVar11 >> 0x10 != iVar8) && ((short)uVar21 == local_30[iVar11 >> 0x10]))
									{
										bVar2 = true;
										break;
									}
					
									// increment loop counter
									i = i + 1;
					
									iVar11 = i * 0x10000;
								} while (i * 0x10000 >> 0x10 < (int)(u_int)(u_char)sdata.gGT->numScreens);
							}
							if (uVar16 << 0x10 != uVar21 << 0x10) 
							{
								// Play sound
								OtherFX_Play(0,1);
							}
							if (local_50 != 0)
							{
								bVar3 = !bVar2;
								bVar2 = false;
								if (bVar3) break;
								uVar21 = (u_int)*puVar23;
							}
							uVar16 = uVar21;
						} while (bVar2);
					}
					uVar20 = (u_short)uVar21;
			
					// loop counter
					i = 0;
			
					// if number of players is not zero
					if (sdata.gGT->numScreens) 
					{
						iVar8 = 0;
			
						// for i = 0; i < numPlayers; i++
						do
						{
							if ((iVar8 >> 0x10 != (int)sVar6) && ((short)uVar21 == local_30[iVar8 >> 0x10]))
							{
								uVar21 = (u_int)(u_short)local_30[(int)sVar6];
							}
							uVar20 = (u_short)uVar21;
				
							// increment loop counter
							i = i + 1;
				
							iVar8 = i * 0x10000;
						} while (i * 0x10000 >> 0x10 < (int)(u_int)(u_char)sdata.gGT->numScreens);
					}
			
					// If this player pressed Cross or Circle
					if (((&sdata.buttonTapPerPlayer[0])[(int)sVar6] & 0x50) != 0) 
					{
						// this player has now selected a character
						sdata.characterSelectFlags = sdata.characterSelectFlags | (u_short)(1 << ((int)sVar6 & 0x1fU));
			
						bVar1 = sdata.gGT->numScreens;
			
						// Play sound
						OtherFX_Play();
			
						// if all players have selected their characters
						if ((int)(short)sdata.characterSelectFlags == ((0xff << ((u_int)bVar1 & 0x1f) ^ 0xffU) & 0xff)) 
						{
							// move to track selection
							OVR_230.movingToTrackMenu = 1;
							OVR_230.isMenuTransitioning = 2;
						}
					}
			
					if
					(
						// if this is the first iteration of the loop
						((iu & 0xffff) == 0) && 
				
						// if you press Square or Triangle
						((sdata.buttonTapPerPlayer[0] & 0x40020) != 0)
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
					if ((uVar9 & 0x40020) != 0) 
					{
						// Play sound
						OtherFX_Play(2, 1);
			
						// this player has de-selected their character
						sdata.characterSelectFlags = sdata.characterSelectFlags & ~uVar4;
					}
				}
		
				// clear input
				sdata.buttonTapPerPlayer[iu] = 0;
			}
			uVar21 = SEXT24(sVar6);
			local_30[uVar21] = uVar20;
			iVar24 = (int)(short)uVar20 * 10 + DAT_800b5a3c;
			local_80 = *(short *)(iVar24 + 6) + *puVar26;
			local_7c = 0x34;
			local_7a = 0x21;
			local_7e = *(short *)(iVar24 + 8) + puVar26[1];
		
			// if player has not selected a character
			if (((int)(short)sdata.characterSelectFlags >> (uVar21 & 0x1f) & 1U) == 0) 
			{
				// draw string
				// "1", "2", "3", "4", above the character icon
				DecalFont_DrawLine
				(
					(&PTR_DAT_800aba28_800b5374)[uVar21],
					(int)(((u_int)*(u_short *)(iVar24 + 6) + (u_int)*puVar26 + -6) * 0x10000) >> 0x10,
					(int)(((u_int)*(u_short *)(iVar24 + 8) + (u_int)puVar26[1] + -3) * 0x10000) >>
					0x10, 1, 4
				);
				puVar12 = auStack120;
			}
			else
			{
				puVar12 = &DAT_800b538c;
			}
		
			// DrawBoxOutline_HighLevel (solid)
			DrawBoxOutline_HighLevel(&local_80,puVar12,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
			
		// increment loop counter
		iu = iu + 1;
		} while ((int)(iu * 0x10000) >> 0x10 < (int)(u_int)(u_char)sdata.gGT->numScreens);
	}
	
	// loop counter
	i = 0;
	
	MM_Characters_ClearInactivePlayers();
	
	psVar18 = DAT_800b5a18 + 1;
	psVar22 = DAT_800b5a18;
	
	// loop through character icons
	
	// for i = 0; i < 0xf; i++
	do 
	{
		iVar8 = (u_int)(u_short)psVar18[4] << 0x10;
		if
		(
			// If Icon is unlocked (from array of icons)
			(iVar8 >> 0x10 == -1) ||
			
			// if character is unlocked
			// from 4-byte variable that handles all rewards
			// also the variable written by cheats
			(((u_int)(&DAT_8008e6ec)[iVar8 >> 0x15] >> (psVar18[4] & 0x1fU) & 1) != 0)
		) 
		{
			puVar15 = &DAT_800b5390;
		
			// loop counter
			iVar8 = 0;
		
			// if number of players is not zero
			if (sdata.gGT->numScreens != 0) 
			{
				iVar19 = 0;
		
				// for iVar8 = 0; iVar8 < numPlayers; iVar8++
				do 
				{
					if
					(
						((short)i == globalIconPerPlayer[iVar19 >> 0x10]) &&
			
						// if player selected a character
						(((int)(short)sdata.characterSelectFlags >> (iVar19 >> 0x10 & 0x1fU) & 1U) != 0)
					)
					{
						puVar15 = &DAT_800b5394;
					}
			
					// increment loop counter
					iVar8 = iVar8 + 1;
			
					iVar19 = iVar8 * 0x10000;
				} while (iVar8 * 0x10000 >> 0x10 < (int)(u_int)(u_char)sdata.gGT->numScreens);
			}
		
			iVar8 = (int)(short)i * 10 + DAT_800b5a3c;
			
			// Draw Character Icon
			// DecalHUD_DrawPolyGT4_Safe
			DecalHUD_DrawPolyGT4_Safe
			(
				*(undefined4 *)(PTR_DAT_8008d2ac + (int)*(short *)(&DAT_80086d8c + (int)psVar18[3] * 0x10) * 4 + 0x1eec),
				(int)*(short *)(iVar8 + 6) + (int)*psVar22 + 6,
				(int)*(short *)(iVar8 + 8) + (int)*psVar18 + 4,
					 
				// pointer to PrimMem struct
				*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
					 
				// pointer to OT mem
				*(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
					 
				*puVar15, *puVar15, *puVar15, *puVar15, 1, 0x1000
			);
		}
		psVar5 = DAT_800b5a18;
	
		// increment loop counter
		i = i + 1;
	
		psVar18 = psVar18 + 6;
		psVar22 = psVar22 + 6;
	} while (i * 0x10000 >> 0x10 < 0xf);
	
	// loop counter
	i = 0;
	
	// for i = 0; i < 4; i++
	do 
	{
		iVar8 = (i << 0x10) >> 0xf;
		
		// increment loop counter
		i = i + 1;
		
		*(short *)((int)&DAT_80086e84 + iVar8) = psVar5[(int)*(short *)((int)globalIconPerPlayer + iVar8) * 6 + 4];
	} while (i * 0x10000 >> 0x10 < 4);
	
	// loop counter
	i = 0;
	
	// if number of players is not zero
	if (sdata.gGT->numScreens) 
	{
		iVar8 = 0;
	
		// for i = 0; i < numPlayers; i++
		do 
		{
			uVar25 = iVar8 >> 0x10;
			sVar6 = globalIconPerPlayer[uVar25];
			psVar22 = DAT_800b5a18 + (int)sVar6 * 6;
		
			// if player has not selected a character
			if (((int)(short)sdata.characterSelectFlags >> (uVar25 & 0x1f) & 1U) == 0) 
			{
				MM_Characters_AnimateColors
				(
					&local_70,uVar25,
					
					// flags of which characters are selected
					(int)(short)(sdata.characterSelectFlags & (u_short)(1 << (uVar25 & 0x1f)))
				);
					
				local_70 = (u_char)((int)((u_int)local_70 << 2) / 5);
				local_6f = (u_char)((int)((u_int)local_6f << 2) / 5);
				local_6e = (u_char)((int)((u_int)local_6e << 2) / 5);
				iVar8 = (int)sVar6 * 10 + DAT_800b5a3c;
				local_80 = *(short *)(iVar8 + 6) + *psVar22 + 3;
				local_7c = 0x2e;
				local_7a = 0x1d;
				local_7e = *(short *)(iVar8 + 8) + psVar22[1] + 2;
		
				// this draws the flashing blue square that appears when you highlight a character in the character select screen
				CTR_Box_DrawSolidBox
				(
					&local_80, &local_70,
					*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),
										 
					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74
				);
			}
			if
			(
				((&DAT_800b5a24)[uVar25] == 0) &&
				((&DAT_800b59f8)[uVar25] == (&DAT_80086e84)[uVar25])
			) 
			{
				// get number of players
				bVar1 = sdata.gGT->numScreens;
		
				// if number of players is 1 or 2
				uVar14 = 3;
		
				// if number of players is 3 or 4
				if (bVar1 >= 3)
				{
					uVar14 = 2;
				}
		
				iVar8 = uVar25 * 10 + DAT_800b5a3c;
				sVar10 = *(short *)(iVar8 + 0xa8) + (DAT_800b5a0c + uVar25 * 2)[1];
				sVar6 = (short)((((u_int)(bVar1 < 3) ^ 1) << 0x12) >> 0x10);
				if ((bVar1 == 4) && (1 < (int)uVar25))
				{
					sVar6 = sVar10 + sVar6 + -6;
				}
				else
				{
					sVar6 = sVar10 + DAT_800b5a38 + sVar6;
				}
		
				// draw string
				DecalFont_DrawLine
				(
					*(undefined4 *)((int)*(short *)(&DAT_80086d88 + (int)psVar22[4] * 0x10) * 4 + DAT_8008d878),
					(int)(((u_int)*(u_short *)(iVar8 + 0xa6) + (u_int)(u_short)DAT_800b5a0c[uVar25 * 2] + (((int)((u_int)DAT_800b5a30 << 0x10) >> 0x10) - ((int)((u_int)DAT_800b5a30 << 0x10) >> 0x1f) >> 1)) * 0x10000) >> 0x10,
					(int)sVar6, uVar14, 0xffff8000
				);
			}
			
			// rotation of each driver, 90 degrees difference
			psVar22 = (short *)((int)&DAT_800b5a00 + ((i << 0x10) >> 0xf));
		
			// increment loop counter
			i = i + 1;
		
			// spin driver each frame
			*psVar22 = *psVar22 + 0x40;
		
			iVar8 = i * 0x10000;
		} while (i * 0x10000 >> 0x10 < (int)(u_int)(u_char)sdata.gGT->numScreens);
	}
	
	// loop counter
	i = 0;
	
	psVar18 = DAT_800b5a18 + 1;
	psVar22 = DAT_800b5a18;
	
	// loop through all icons
	
	// for i = 0; i < 0xf; i++
	do 
	{
		iVar8 = (u_int)(u_short)psVar18[4] << 0x10;
		
		if
		(
			// If Icon is unlocked (from array of icons)
			(iVar8 >> 0x10 == -1) ||
			
			// if character is unlocked
			// from 4-byte variable that handles all rewards
			// also the variable written by cheats
			(((u_int)(&DAT_8008e6ec)[iVar8 >> 0x15] >> (psVar18[4] & 0x1fU) & 1) != 0)
		) 
		{
			iVar8 = (int)(short)i * 10 + DAT_800b5a3c;
			local_68 = *(short *)(iVar8 + 6) + *psVar22;
			local_64 = 0x34;
			local_62 = 0x21;
			local_66 = *(short *)(iVar8 + 8) + *psVar18;
		
			// Draw 2D Menu rectangle background
			DrawTextBackground(&local_68,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
		}
	
		// increment loop counter
		i = i + 1;
	
		// advence both short* arrays by 6 shorts,
		// which is 12 (0xc) bytes, size of
		// character icon buffer
		psVar18 = psVar18 + 6;
		psVar22 = psVar22 + 6;
	} while (i * 0x10000 >> 0x10 < 0xf);
	
	// loop counter
	i = 0;
	
	// if number of players is not zero
	if (sdata.gGT->numScreens) 
	{
		psVar22 = DAT_800b5a0c;
	
		// for i = 0; i < numPlayers; i++
		do
		{
			uVar25 = SEXT24((short)i);
			iVar8 = uVar25 * 10 + DAT_800b5a3c;
			
			// store window width and height in one 4-byte variable
			local_5c = CONCAT22(DAT_800b59dc,DAT_800b5a30);
		
			local_60 = CONCAT22(*(short *)(iVar8 + 0xa8) + psVar22[1], *(short *)(iVar8 + 0xa6) + *psVar22);
			
			// MM_Characters_AnimateColors
			MM_Characters_AnimateColors(&local_68,uVar25, ((int)(short)sdata.characterSelectFlags >> (uVar25 & 0x1f) ^ 1U) & 1);
			
			// DrawBoxOutline_HighLevel (solid)
			DrawBoxOutline_HighLevel(&local_60,&local_68,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
			
			iVar8 = 0;
		
			// if player selected a character
			if (((int)(short)sdata.characterSelectFlags >> (uVar25 & 0x1f) & 1U) != 0) 
			{
				local_58 = local_60;
				local_54 = local_5c;
				do
				{
					local_58 = CONCAT22((short)((u_int)local_58 >> 0x10) + 2, (short)local_58 + 3);
					local_68 = CONCAT11((char)((int)((u_int)local_68._1_1_ << 2) / 5), (char)((int)((u_int)(u_char)local_68 << 2) / 5));
					local_54 = CONCAT22((short)((u_int)local_54 >> 0x10) + -4, (short)local_54 + -6);
					local_66 = local_66 & 0xff00 | (u_short)(u_char)((int)((u_int)(u_char)local_66 << 2) / 5);
					
					// DrawBoxOutline_HighLevel (solid)
					DrawBoxOutline_HighLevel(&local_58, &local_68, 0, *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
					
					iVar8 = iVar8 + 1;
				} while (iVar8 * 0x10000 >> 0x10 < 2);
			}
			psVar22 = psVar22 + 2;
		
			// Draw 2D Menu rectangle background
			DrawTextBackground(&local_60, 9, *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0) + 0xc);
			
			local_60 = 0;
		
			BackgroundBlueRect
			(
				&local_60, &DAT_800b5398,
				*(int *)(PTR_DAT_8008d2ac + (int)(short)i * 0x110 + 0x25c) + 0xffc,
					 
				// pointer to PrimMem struct
				*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74
			);
					 
			// increment loop counter
			i = i + 1;
		
		} while (i * 0x10000 >> 0x10 < (int)(u_int)(u_char)sdata.gGT->numScreens);
	}
	return;
}