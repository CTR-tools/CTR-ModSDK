#include <common.h>

// character selection menu, 
// RECTMENU_FuncPtr for menu: 0x800b46b4;

void MM_Characters_MenuProc()
{
	u_char numPlyrNextGame;
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
	u_int iconColor;
	u_int globalIconPerPlayerCopy3;
	int nextDriverCopy;
	int globalIconPerPlayerCopy4;
	u_short globalIconPerPlayerCopy;
	u_int globalIconPerPlayerCopy2;
	u_short* globalIconPerPlayerPtr2;
	int iVar24;
	u_int k;
	u_short* puVar26;
	short globalIconPerPlayer[4];
	RECT r80;
	u_char auStack120[8];

	u_char colorRGBA[4];

	RECT r68;
	RECT r60;
	RECT r58;

	short local_50;
	short* globalIconPerPlayerPtr;

	int i;
	int j;
	int posX;
	int posY;
	u_int characterSelectString;
	short playerIcon;
	int direction;
	
	short* psVar22;
	struct CharacterSelectMeta* csm_Active;
	
	struct GameTracker* gGT = sdata->gGT;
	
	for (i = 0; i < 4; i++)
	{
		globalIconPerPlayer[i] = D230.characterMenuID[data.characterIDs[i]];
	}
	
	// if menu is not in focus
	if (D230.isMenuTransitioning != 1) 
	{
		MM_TransitionInOut(D230.ptrTransitionMeta, (int)D230.transitionFrames, 8);
	}

	MM_Characters_SetMenuLayout();
	MM_Characters_DrawWindows(1);
	
	// if transitioning in
	if (D230.isMenuTransitioning == 0) 
	{
		// subtract frame
		D230.transitionFrames--;
	
		// if no more frames
		if (D230.transitionFrames == -1) 
		{
			// menu is now in focus
			D230.isMenuTransitioning = 1;
			
			D230.transitionFrames = 0;
		}
	}

	// if transitioning out
	if (D230.isMenuTransitioning == 2) 
	{
		// increase frame
		D230.transitionFrames++;
		
		// if more than 12 frames
		if (D230.transitionFrames > 12) 
		{
			// Make a backup of the characters
			// you selected in character selection screen
			MM_Characters_BackupIDs();
			
			MM_Characters_HideDrivers();
		
			// if returning to main menu
			if (D230.movingToTrackMenu == 0) 
			{
				MM_JumpTo_Title_Returning();
				return;
			}
		
			gGT->currLEV = 0x14;
		
			// not battle
			if((gGT->gameMode1 & 0x20) == 0)
			{
				// start loading
				MainRaceTrack_RequestLoad(0x14);
				return;
			}
			
			// else, multiplayer
		
			// battle
			sdata->ptrDesiredMenu = &D230.menuBattleWeapons;
			MM_Battle_Init();
			return;
		}
	}

	switch(D230.characterSelectIconLayout)
	{
		// 3P character selection
		case 2:
	
			// If you have a lot of characters unlocked, do not draw SELECT CHARACTER
			if (D230.isRosterExpanded) goto dontDrawSelectCharacter;
	
			// SELECT
			DecalFont_DrawLine
			(
				sdata->lngStrings[96],
				D230.ptrTransitionMeta[15].currX + 0x9c,
				D230.ptrTransitionMeta[15].currY + 0x14,
				FONT_BIG, (JUSTIFY_CENTER | ORANGE)
			);
			characterSelectType = FONT_BIG;
		
			// CHARACTER
			characterSelectString = sdata->lngStrings[97];
			
			posX = D230.ptrTransitionMeta[15].currX + 0x9c;
			posY = D230.ptrTransitionMeta[15].currY + 0x26;
			break;
		
		// 4P character selection
		case 3:
		
			// If Fake Crash is unlocked, do not draw "Select Character"
			if (sdata->gameProgress.unlocks[0] & 0x800) goto dontDrawSelectCharacter;
		
			// SELECT
			DecalFont_DrawLine
			(
				sdata->lngStrings[96],
				D230.ptrTransitionMeta[15].currX + 0xfc,
				D230.ptrTransitionMeta[15].currY + 8,
				FONT_CREDITS, (JUSTIFY_CENTER | ORANGE)
			);
			characterSelectType = FONT_CREDITS;
		
			// CHARACTER
			characterSelectString = sdata->lngStrings[97];
		
			posX = D230.ptrTransitionMeta[15].currX + 0xfc;
			posY = D230.ptrTransitionMeta[15].currY + 0x18;
			break;
		
		// If you are in 1P or 2P character selection,
		// when you do NOT have a lot of characters selected
		case 4:
		case 5:
			characterSelectType = FONT_BIG;
		
			// SELECT CHARACTER
			characterSelectString = sdata->lngStrings[95];
		
			posX = D230.ptrTransitionMeta[15].currX + 0xfc;
			posY = D230.ptrTransitionMeta[15].currY + 10;
			break;
			
		default:
			goto dontDrawSelectCharacter;
	}
	
	// Draw String
	DecalFont_DrawLine(characterSelectString, posX, posY, characterSelectType, (JUSTIFY_CENTER | ORANGE));
	
	dontDrawSelectCharacter:

	// if number of players is not zero
	if (gGT->numPlyrNextGame != 0)
	{
		globalIconPerPlayerPtr = &globalIconPerPlayer[0];

		for (i = 0; i < gGT->numPlyrNextGame; i++)
		{
			characterSelectFlags5bit = (u_short)(1 << i);
			globalIconPerPlayerCopy = globalIconPerPlayerPtr[i];
			globalIconPerPlayerCopy2 = globalIconPerPlayerCopy;
		
			MM_Characters_AnimateColors(auStack120, i, (int)(short)(sdata->characterSelectFlags & characterSelectFlags5bit));
			
			puVar26 = &D230.csm_Active[globalIconPerPlayerCopy];
			
			if
			(
				(D230.isMenuTransitioning == 1) && 
				(
					// get input from this player
					button = sdata->buttonTapPerPlayer[i], 
				
					// If you press the D-Pad, or Cross, Square, Triangle, Circle
					button & 0x4007f
				)
			)
			{
				// if character has not been selected by this player
				if (((int)(short)sdata->characterSelectFlags >> i & 1U) == 0)
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
								D230.characterSelect_MoveDir[i] = 1;
							}
				
							// If you pressed Down
							else 
							{
								// Down
								direction = 1;
				
								// Move down character selection list
								D230.characterSelect_MoveDir[i] = 1;
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
							(D230.characterSelect_MoveDir)[i] = 0xffff;
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
								globalIconPerPlayerCopy2 = MM_Characters_GetNextDriver((u_int)(u_char)D230.getNextDriver1[direction], nextDriverCopy);
								globalIconPerPlayerCopy5 = (int)(short)globalIconPerPlayerCopy2;

								if
								(
									(((globalIconPerPlayerCopy5 == globalIconPerPlayerCopy4) || (nextDriverCopy == globalIconPerPlayerCopy4)) || (nextDriverCopy == globalIconPerPlayerCopy5)) ||
									(button = MM_Characters_boolIsInvalid(globalIconPerPlayerPtr, globalIconPerPlayerCopy5, j), (button & 0xffff) != 0)
								)
								{
									nextDriver = MM_Characters_GetNextDriver((u_int)(u_char)D230.getNextDriver1[direction], (int)(short)*globalIconPerPlayerPtr2);
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
										globalIconPerPlayerCopy2 = MM_Characters_GetNextDriver((u_int)(u_char)D230.getNextDriver2[direction], globalIconPerPlayerCopy5);
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
											nextDriver = MM_Characters_GetNextDriver((u_int)(u_char)D230.getNextDriver2[direction], (int)(short)*globalIconPerPlayerPtr2);
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
							if (gGT->numPlyrNextGame) 
							{
								for (k = 0; k < gGT->numPlyrNextGame; k++)
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
					if (gGT->numPlyrNextGame) 
					{
						for (j = 0; j < gGT->numPlyrNextGame; j++)
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
						sdata->characterSelectFlags = sdata->characterSelectFlags | (u_short)(1 << i);
			
						numPlyrNextGame = gGT->numPlyrNextGame;
			
						// Play sound
						OtherFX_Play(1,1);
			
						// if all players have selected their characters
						if ((int)(short)sdata->characterSelectFlags == (1 << numPlyrNextGame)-1) 
						{
							// move to track selection
							D230.movingToTrackMenu = 1;
							D230.isMenuTransitioning = 2;
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
						D230.movingToTrackMenu = 0;
						D230.isMenuTransitioning = 2;
			
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
			iVar24 = &D230.ptrTransitionMeta[globalIconPerPlayerCopy];
			
			r80.x = ((struct TransitionMeta*)iVar24)->currX + *puVar26;
			r80.y = ((struct TransitionMeta*)iVar24)->currY + puVar26[1];
			r80.w = 0x34;
			r80.h = 0x21;
		
			// if player has not selected a character
			if (((sdata->characterSelectFlags >> i) & 1U) == 0) 
			{
				// draw string
				// "1", "2", "3", "4", above the character icon
				DecalFont_DrawLine
				(
					D230.PlayerNumberStrings[i],
					((struct TransitionMeta*)iVar24)->currX + (u_int)*puVar26 + -6,
					((struct TransitionMeta*)iVar24)->currY + (u_int)puVar26[1] + -3,
					FONT_BIG, WHITE
				);
				puVar12 = auStack120;
			}
			else
			{
				puVar12 = &D230.characterSelect_Outline;
			}
		
			RECTMENU_DrawOuterRect_HighLevel(&r80, puVar12, 0, gGT->backBuffer->otMem.startPlusFour);
		}
	}

	MM_Characters_PreventOverlap();
	
	csm_Active = D230.csm_Active;
	
	// loop through character icons

	for (i = 0; i < 0xf; i++)
	{
		iVar8 = csm_Active->unlockFlags;
		if
		(
			// If Icon is unlocked by default,
			// dont use iVar8, must be interpeted as "short"
			((short)csm_Active->unlockFlags == -1) ||
			
			// if character is unlocked
			// from 4-byte variable that handles all rewards
			// also the variable written by cheats
			(((sdata->gameProgress.unlocks[iVar8>>5] >> (iVar8&0x1f)) & 1) != 0)
		) 
		{
			iconColor = D230.characterSelect_NeutralColor;
		
			// if number of players is not zero
			if (gGT->numPlyrNextGame != 0) 
			{
				for (j = 0; j < gGT->numPlyrNextGame; j++)
				{
					if
					(
						((short)i == globalIconPerPlayer[j]) &&
			
						// if player selected a character
						 (((int)(short)sdata->characterSelectFlags >> (j & 0x1fU) & 1U) != 0)
					)
					{
						iconColor = D230.characterSelect_ChosenColor;
					}
				}
			}
		
			iVar8 = &D230.ptrTransitionMeta[i];
			
			// Draw Character Icon
			RECTMENU_DrawPolyGT4
			(
				gGT->ptrIcons[data.MetaDataCharacters[csm_Active->characterID].iconID],
				((struct TransitionMeta*)iVar8)->currX + csm_Active->posX + 6,
				((struct TransitionMeta*)iVar8)->currY + csm_Active->posY + 4,

				&gGT->backBuffer->primMem,
				gGT->pushBuffer_UI.ptrOT,

				iconColor, iconColor, iconColor, iconColor, 1, 0x1000
			);
		}
		
		csm_Active++;
	}
	
	// reset
	csm_Active = D230.csm_Active;
	
	for (i = 0; i < 4; i++)
	{
		data.characterIDs[i] = csm_Active[(int)globalIconPerPlayer[i]].characterID;
	}
	
	// if number of players is not zero
	if (gGT->numPlyrNextGame) 
	{
		for (i = 0; i < gGT->numPlyrNextGame; i++)
		{
			j = i;
			playerIcon = globalIconPerPlayer[j];
			csm_Active = &D230.csm_Active[playerIcon];
		
			// if player has not selected a character
			if (((int)(short)sdata->characterSelectFlags >> j & 1U) == 0) 
			{
				MM_Characters_AnimateColors
				(
					&colorRGBA, j,
						
					// flags of which characters are selected
					(int)(short)(sdata->characterSelectFlags & (u_short)(1 << j))
				);
					
				colorRGBA[0] = (u_char)((int)((u_int)colorRGBA[0] << 2) / 5);
				colorRGBA[1] = (u_char)((int)((u_int)colorRGBA[1] << 2) / 5);
				colorRGBA[2] = (u_char)((int)((u_int)colorRGBA[2] << 2) / 5);

				iVar8 = &D230.ptrTransitionMeta[playerIcon];
				
				r80.x = ((struct TransitionMeta*)iVar8)->currX + csm_Active->posX + 3;
				r80.y = ((struct TransitionMeta*)iVar8)->currY + csm_Active->posY + 2;
				r80.w = 0x2e;
				r80.h = 0x1d;

				// this draws the flashing blue square that appears when you highlight a character in the character select screen
				CTR_Box_DrawSolidBox
				(
					&r80, &colorRGBA,
					gGT->backBuffer->otMem.startPlusFour,
					&gGT->backBuffer->primMem
				);
			}
			if
			(
				(D230.timerPerPlayer[j] == 0) &&
				(D230.characterSelect_charIDs_curr[j] == data.characterIDs[j])
			) 
			{
				// get number of players
				numPlyrNextGame = gGT->numPlyrNextGame;
		
				// if number of players is 1 or 2
				fontType = FONT_CREDITS;
		
				// if number of players is 3 or 4
				if (numPlyrNextGame >= 3) fontType = FONT_SMALL;
		
				iVar8 = &D230.ptrTransitionMeta[j+0x10];
				sVar10 = ((struct TransitionMeta*)iVar8)->currY + D230.characterSelect_ptrWindowXY[j*2+1];
				sVar6 = (short)((((u_int)(numPlyrNextGame < 3) ^ 1) << 0x12) >> 0x10);

				if ((numPlyrNextGame == 4) && (j > 1)) sVar6 = sVar10 + sVar6 - 6;
				else							  sVar6 = sVar10 + D230.textPos + sVar6;
		
				// draw string
				DecalFont_DrawLine
				(
					sdata->lngStrings[data.MetaDataCharacters[csm_Active->characterID].name_LNG_long],
					(int)((((struct TransitionMeta*)iVar8)->currX + D230.characterSelect_ptrWindowXY[j * 2] + (((int)((u_int)D230.characterSelect_sizeX << 0x10) >> 0x10) - ((int)((u_int)D230.characterSelect_sizeX << 0x10) >> 0x1f) >> 1)) * 0x10000) >> 0x10,
					(int)sVar6, fontType, (JUSTIFY_CENTER | ORANGE)
				);
			}
			
			// rotation of each driver, 90 degrees difference
			D230.characterSelect_angle[i] += 0x40;
		}
	}
	
	// reset
	csm_Active = D230.csm_Active;

	// loop through all icons
	for (i = 0; i < 0xf; i++)
	{
		iVar8 = csm_Active[i].unlockFlags;
		
		if
		(
			// If Icon is unlocked (from array of icons)
			((short)csm_Active[i].unlockFlags == -1) ||
			
			// if character is unlocked
			// from 4-byte variable that handles all rewards
			// also the variable written by cheats
			((sdata->gameProgress.unlocks[iVar8 >> 5] >> (iVar8 & 0x1fU) & 1) != 0)
		) 
		{
			iVar8 = &D230.ptrTransitionMeta[i];
			r68.x = ((struct TransitionMeta*)iVar8)->currX + csm_Active[i].posX;
			r68.y = ((struct TransitionMeta*)iVar8)->currY + csm_Active[i].posY;
			r68.w = 0x34;
			r68.h = 0x21;
		
			// Draw 2D Menu rectangle background
			RECTMENU_DrawInnerRect(&r68, 0, gGT->backBuffer->otMem.startPlusFour);
		}
	}
	
	// if number of players is not zero
	if (gGT->numPlyrNextGame != 0) 
	{
		psVar22 = D230.characterSelect_ptrWindowXY;

		for (i = 0; i < gGT->numPlyrNextGame; i++)
		{
			j = i;
			iVar8 = &D230.ptrTransitionMeta[j];
			
			// store window width and height in one 4-byte variable
			r60.x = *(short *)(iVar8 + 0xa6) + *psVar22;
			r60.y = *(short *)(iVar8 + 0xa8) + psVar22[1];
			r60.w = D230.characterSelect_sizeX;
			r60.h = D230.characterSelect_sizeY;
			
			MM_Characters_AnimateColors
			(
				&colorRGBA, j, 
				
				// flags of which characters are selected
				((int)(short)sdata->characterSelectFlags >> j ^ 1U) & 1
			);
			
			RECTMENU_DrawOuterRect_HighLevel(
				&r60, &colorRGBA, 0, 
				gGT->backBuffer->otMem.startPlusFour);
			
			// if player selected a character
			if (((int)(short)sdata->characterSelectFlags >> j & 1U) != 0) 
			{
				r58.x = r60.x;
				r58.y = r60.y;
				r58.w = r60.w;
				r58.h = r60.h;
				
				for (iVar8 = 0; iVar8 < 2; iVar8++)
				{
					r58.x += 3;
					r58.y += 2;
					r58.w -= 6;
					r58.h -= 4;
					
					colorRGBA[0] = (u_char)((int)((u_int)colorRGBA[0] << 2) / 5);
					colorRGBA[1] = (u_char)((int)((u_int)colorRGBA[1] << 2) / 5);
					colorRGBA[2] = (u_char)((int)((u_int)colorRGBA[2] << 2) / 5);
					
					RECTMENU_DrawOuterRect_HighLevel(
						&r58, &colorRGBA, 0, 
						gGT->backBuffer->otMem.startPlusFour);
				}
			}
			psVar22 = psVar22 + 2;
		
			// Draw 2D Menu rectangle background
			RECTMENU_DrawInnerRect(&r60, 9, &gGT->backBuffer->otMem.startPlusFour[3]);
			
			r60.x = 0;
			r60.y = 0;
		
			RECTMENU_DrawRwdBlueRect
			(
				&r60.x, &D230.characterSelect_BlueRectColors[0],
				&gGT->pushBuffer[i].ptrOT[0x3ff], &gGT->backBuffer->primMem
			);
		
		}
	}
	return;
}
