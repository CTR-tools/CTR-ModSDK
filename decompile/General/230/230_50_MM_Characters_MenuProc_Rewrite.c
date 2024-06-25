#include <common.h>

// upon pressing one of the d-pad buttons get closest available character in the direction pressed
force_inline int GETNEXTCHARACTER_MM_Characters_MenuProc(int idx, u_int button, int direction, int characterMenuIDCurrPlayer, int* characterMenuIDPerPlayer)
{
	struct GameTracker* gGT = sdata->gGT;

	// the current character slot highlighted will change depending on loop iteration
	// this is mainly so the game can look up an available character slot after encountering one that is being highlighted by another player
	int currCharacter = characterMenuIDCurrPlayer;

	// the character that the game will highlight
	int	nextCharacter = -1;

	// is directional character from current position unavailable //
	// if there is no adjacent character slot in the direction pressed, from the position of the slot currently highlighted
	int isDrtnChrFromCurrPosUnavailable = false;

	int isCharacterHighlightedByOtherPlayer = false;

	do
	{
		// directional character from current position //
		// adjacent character slot in the direction pressed, from the position of the slot currently highlighted
		int drtnChrFromCurrPos = DECOMP_MM_Characters_GetNextDriver(direction, currCharacter);

		nextCharacter = drtnChrFromCurrPos;

		if (drtnChrFromCurrPos == currCharacter)
		{
			isDrtnChrFromCurrPosUnavailable = true;

			// directional character from original position //
			// adjacent character slot in the direction pressed, from the position of the slot highlighted prior to the execution of this function
			int drtnChrFromOGPos = DECOMP_MM_Characters_GetNextDriver(direction, characterMenuIDCurrPlayer);

			// character perpendicular to directional character from original position //
			// character slot that is perpendicular to the adjacent slot in the direction pressed from the position of the slot highlighted prior to this function
			// perpendicularity is as follows: if direction is right/left go down, if up/down go left
			int chrPerpToDrtnFromOGPos = DECOMP_MM_Characters_GetNextDriver(D230.getNextDriver1[direction], drtnChrFromOGPos);
			nextCharacter = chrPerpToDrtnFromOGPos;

			if
			(
				(
					(
						(chrPerpToDrtnFromOGPos == drtnChrFromCurrPos) ||
						(drtnChrFromOGPos == drtnChrFromCurrPos)
					) || (drtnChrFromOGPos == chrPerpToDrtnFromOGPos)
				) ||
				(button = DECOMP_MM_Characters_boolIsInvalid(characterMenuIDPerPlayer, chrPerpToDrtnFromOGPos, idx), (button & 0xffff) != 0)
			)
			{
				// perpendicular character from original position //
				// character slot perpendicular from the slot highlighted prior to this function
				int perpChrFromOGPos = DECOMP_MM_Characters_GetNextDriver(D230.getNextDriver1[direction], characterMenuIDCurrPlayer);

				// character directional to perpendicular character from original position //
				// adjacent character slot in the direction pressed, from the one perpendicular to the slot highlighted prior to this function
				int chrDrtnToPerpFromOGPos =  DECOMP_MM_Characters_GetNextDriver(direction, perpChrFromOGPos);
				nextCharacter = chrDrtnToPerpFromOGPos;

				if
				(
					(
						(chrDrtnToPerpFromOGPos == currCharacter) ||
						(perpChrFromOGPos == currCharacter)
					) ||
					(
						(perpChrFromOGPos == chrDrtnToPerpFromOGPos ||
						(button = DECOMP_MM_Characters_boolIsInvalid(characterMenuIDPerPlayer, chrDrtnToPerpFromOGPos, idx), (button & 0xffff) != 0))
					)
				)
				{
					// character inversely perpendicular to directional from original position //
					// character slot that is inversely perpendicular to the adjacent slot in the direction pressed from the position of the slot highlighted prior to this function
					// said perpendicularity is as follows: right/left go up, up/down go right
					int chrInvrPerpToDrtnFromOGPos = DECOMP_MM_Characters_GetNextDriver(D230.getNextDriver2[direction], drtnChrFromOGPos);
					nextCharacter = chrInvrPerpToDrtnFromOGPos;

					if
					(
						(
							(chrInvrPerpToDrtnFromOGPos == currCharacter) ||
							(drtnChrFromOGPos == currCharacter)
						) ||
						(
							(
								drtnChrFromOGPos == chrInvrPerpToDrtnFromOGPos ||
								(button = DECOMP_MM_Characters_boolIsInvalid(characterMenuIDPerPlayer, chrInvrPerpToDrtnFromOGPos, idx), (button & 0xffff) != 0)
							)
						)
					)
					{
						// inversely perpendicular character from original position //
						// character slot inversely perpendicular from the slot highlighted prior to this function
						int invrPerpChrFromOGPos = DECOMP_MM_Characters_GetNextDriver(D230.getNextDriver2[direction], characterMenuIDCurrPlayer);

						// character directional to perpendicular character from original position //
						// adjacent character slot in the direction pressed, from the one inversely perpendicular to the slot highlighted prior to this function
						int chrDrtnToInvrPerpFromOGPos = DECOMP_MM_Characters_GetNextDriver(direction, invrPerpChrFromOGPos);
						nextCharacter = chrDrtnToInvrPerpFromOGPos;

						if
						(
							(
								(
									(chrDrtnToInvrPerpFromOGPos == currCharacter) ||
									(invrPerpChrFromOGPos == currCharacter)
								) ||
								(invrPerpChrFromOGPos == chrDrtnToInvrPerpFromOGPos)) ||
							(button = DECOMP_MM_Characters_boolIsInvalid(characterMenuIDPerPlayer, chrDrtnToInvrPerpFromOGPos, idx), (button & 0xffff) != 0)
						)
						{
							// if all else fails, the highlighted character slot remains the same
							nextCharacter = characterMenuIDCurrPlayer;
						}
					}
				}
			}
		}

		isCharacterHighlightedByOtherPlayer = false;

		for(int k = 0; k < gGT->numPlyrNextGame; k++)
		{
			// if next character is one already highlighted by another player
			if
			(
				(k != idx) &&
				nextCharacter == characterMenuIDPerPlayer[k]
			)
			{
				isCharacterHighlightedByOtherPlayer = true;
				break;
			}
		}

		if (characterMenuIDCurrPlayer != nextCharacter)
		{
			DECOMP_OtherFX_Play(0, 1);
		}

		// if there's no adjacent character from the current slot's position...
		if (isDrtnChrFromCurrPosUnavailable)
		{
			int noCharacterInDirection = !isCharacterHighlightedByOtherPlayer;
			isCharacterHighlightedByOtherPlayer = false;

			if (noCharacterInDirection) break;

			nextCharacter = characterMenuIDCurrPlayer;
		}

		// change slot currently highlighted in case the new slot is highlighted by another player
		// this will keep happening until the new slot either is free or doesn't exist
		currCharacter = nextCharacter;
	} while (isCharacterHighlightedByOtherPlayer);

	return nextCharacter;
}

force_inline void PROCESSINPUTS_MM_Characters_MenuProc(int idx, int characterSelectPlayerID, int* characterMenuIDCurrPlayer, int* characterMenuIDPerPlayer)
{
	struct GameTracker* gGT = sdata->gGT;

	u_int button = 0;

	if
	(
		(D230.isMenuTransitioning == IN_MENU) &&
		(
			// get input from this player
			button = sdata->buttonTapPerPlayer[idx],

			// If you press the D-Pad, or Cross, Square, Triangle, Circle
			button & (BTN_TRIANGLE | BTN_CIRCLE | BTN_SQUARE_one | BTN_CROSS_one | BTN_RIGHT | BTN_LEFT | BTN_DOWN | BTN_UP)
		)
	)
	{
		// if player hasn't selected a character
		if ((sdata->characterSelectFlags >> idx & 1) == 0)
		{
			int direction = -1;
			int nextCharacterMenuID = *characterMenuIDCurrPlayer;

			if (button & (BTN_RIGHT | BTN_LEFT | BTN_DOWN | BTN_UP))
			{
				if (button & (BTN_UP | BTN_LEFT))
				{
					if (button & BTN_UP)   direction = 0;
					if (button & BTN_LEFT) direction = 2;

					D230.characterSelect_MoveDir[idx] = -1;
				}

				if (button & (BTN_DOWN | BTN_RIGHT))
				{
					if (button & BTN_DOWN)  direction = 1;
					if (button & BTN_RIGHT) direction = 3;

					D230.characterSelect_MoveDir[idx] = 1;
				}

				nextCharacterMenuID = GETNEXTCHARACTER_MM_Characters_MenuProc(idx, button, direction, characterMenuIDCurrPlayer, characterMenuIDPerPlayer);
			}

			// something to prevent character duplicates between players I guess
			for (int i = 0; i < gGT->numPlyrNextGame; i++)
			{
				if ((i != idx) && (nextCharacterMenuID == characterMenuIDPerPlayer[i]))
				{
					nextCharacterMenuID = characterMenuIDPerPlayer[i];
				}
				characterMenuIDCurrPlayer = nextCharacterMenuID;
			}

			// If this player pressed Cross or Circle
			if (((sdata->buttonTapPerPlayer)[idx] & (BTN_CIRCLE | BTN_CROSS_one)) != 0)
			{
				// this player has now selected a character
				sdata->characterSelectFlags |= (1 << idx);

				int numPlyrNextGame = gGT->numPlyrNextGame;

				// Play sound
				DECOMP_OtherFX_Play(1,1);

				// if all players have selected their characters
				if (sdata->characterSelectFlags == (1 << numPlyrNextGame)-1)
				{
					// move to track selection
					D230.movingToTrackMenu = true;
					D230.isMenuTransitioning = EXITING_MENU;
				}
			}

			if
			(
				// if this is the first iteration of the loop
				(idx == 0) &&

				// if you press Square or Triangle
				((sdata->buttonTapPerPlayer[0] & (BTN_TRIANGLE | BTN_SQUARE_one)) != 0)
			)
			{
				// return to main menu
				D230.movingToTrackMenu = false;
				D230.isMenuTransitioning = EXITING_MENU;

				// Play sound
				DECOMP_OtherFX_Play(2, 1);
			}
		}
		else
		{
			// if you press Square or Triangle
			if ((button & (BTN_TRIANGLE | BTN_SQUARE_one)) != 0)
			{
				// Play sound
				DECOMP_OtherFX_Play(2, 1);

				// this player has de-selected their character
				sdata->characterSelectFlags &= ~characterSelectPlayerID;
			}
		}

		// clear input
		sdata->buttonTapPerPlayer[idx] = 0;
	}
}

force_inline void PLAYERPOLLING_MM_Characters_MenuProc(struct CharacterSelectMeta* playerCSM, int* characterMenuIDPerPlayer)
{
	struct GameTracker* gGT = sdata->gGT;

	u_int* characterSlotHighlightColor = 0;
	u_char playerHighlightColor[4];

	for (int i = 0; i < gGT->numPlyrNextGame; i++)
	{
		int characterSelectPlayerID = 1 << i;
		int characterMenuIDCurrPlayer = characterMenuIDPerPlayer[i];

		DECOMP_MM_Characters_AnimateColors(playerHighlightColor, i, sdata->characterSelectFlags & characterSelectPlayerID);

		playerCSM = &D230.csm_Active[characterMenuIDCurrPlayer];

		PROCESSINPUTS_MM_Characters_MenuProc(i, characterSelectPlayerID, &characterMenuIDCurrPlayer, characterMenuIDPerPlayer);

		// set player's character slot to highlight, after any buttons were potentially pressed
		characterMenuIDPerPlayer[i] = characterMenuIDCurrPlayer;

		struct TransitionMeta* characterSlotTransition = &D230.ptrTransitionMeta[characterMenuIDCurrPlayer];

		#ifdef USE_OXIDE
		// can't actually use the characters enum here since these use a different order
		if (characterMenuIDCurrPlayer == 15) // nitros oxide
		{
			// use same transition as Fake Crash
			characterSlotTransition = &D230.ptrTransitionMeta[14]; // fake crash
		}
		#endif

		RECT r80 =
		{
			.x = characterSlotTransition->currX + playerCSM->posX,
			.y = characterSlotTransition->currY + playerCSM->posY,
			.w = 0x34,
			.h = 0x21,
		};

		// if player has not selected a character
		if (((sdata->characterSelectFlags >> i) & 1) == 0)
		{
			// draw string
			// "1", "2", "3", "4", above the character icon
			DECOMP_DecalFont_DrawLine
			(
				D230.PlayerNumberStrings[i],
				characterSlotTransition->currX + playerCSM->posX - 6,
				characterSlotTransition->currY + playerCSM->posY - 3,
				FONT_BIG, WHITE
			);
			characterSlotHighlightColor = playerHighlightColor;
		}
		else
		{
			characterSlotHighlightColor = &D230.characterSelect_Outline;
		}

		Color color = *(Color *) characterSlotHighlightColor;
		DECOMP_RECTMENU_DrawOuterRect_HighLevel
		(
			&r80, color, 0,
			gGT->backBuffer->otMem.startPlusFour
		);
	}
}

force_inline void DISPLAYRECTMENU_MM_Characters_MenuProc(int* characterMenuIDPerPlayer)
{
	struct GameTracker* gGT = sdata->gGT;

	struct CharacterSelectMeta* csm_Active = D230.csm_Active;

	u_char colorRGBA[4];

	// draw "SELECT CHARACTER" string

	int characterSelectFontType = -1;
	char* selectCharacterString = "";
	short selectCharacterPosX = -1;
	short selectCharacterPosY = -1;

	if
	(
		// in 3P, too many characters are unlocked
		(!(D230.characterSelectIconLayout == 2 && D230.isRosterExpanded)) &&
		// in 4P, Fake Crash is unlocked
		(!(D230.characterSelectIconLayout == 3 && sdata->gameProgress.unlocks[0] & 0x800))
	)
	{
		switch(D230.characterSelectIconLayout)
		{
			// 3P character selection
			case 2:

				// SELECT
				DECOMP_DecalFont_DrawLine
				(
					sdata->lngStrings[96],
					D230.ptrTransitionMeta[15].currX + 156,
					D230.ptrTransitionMeta[15].currY + 20,
					FONT_BIG, (JUSTIFY_CENTER | ORANGE)
				);
				characterSelectFontType = FONT_BIG;

				// CHARACTER
				selectCharacterString = sdata->lngStrings[97];

				selectCharacterPosX = D230.ptrTransitionMeta[15].currX + 156;
				selectCharacterPosY = D230.ptrTransitionMeta[15].currY + 38;
				break;

			// 4P character selection
			case 3:

				// SELECT
				DECOMP_DecalFont_DrawLine
				(
					sdata->lngStrings[96],
					D230.ptrTransitionMeta[15].currX + 252,
					D230.ptrTransitionMeta[15].currY + 8,
					FONT_CREDITS, (JUSTIFY_CENTER | ORANGE)
				);
				characterSelectFontType = FONT_CREDITS;

				// CHARACTER
				selectCharacterString = sdata->lngStrings[97];

				selectCharacterPosX = D230.ptrTransitionMeta[15].currX + 252;
				selectCharacterPosY = D230.ptrTransitionMeta[15].currY + 24;
				break;

			// If you are in 1P or 2P character selection,
			// when you do NOT have a lot of characters selected
			case 4:
			case 5:
				characterSelectFontType = FONT_BIG;

				// SELECT CHARACTER
				selectCharacterString = sdata->lngStrings[95];

				selectCharacterPosX = D230.ptrTransitionMeta[15].currX + 252;
				selectCharacterPosY = D230.ptrTransitionMeta[15].currY + 10;
				break;
		}

		// Draw String
		DECOMP_DecalFont_DrawLine
		(
			selectCharacterString,
			selectCharacterPosX, selectCharacterPosY,
			characterSelectFontType, (JUSTIFY_CENTER | ORANGE)
		);
	}

	// draw all character icons

#ifndef USE_OXIDE
	#define NUM_ICONS 15
#else
	#define NUM_ICONS 16
#endif

	for (int i = 0; i < NUM_ICONS; i++, csm_Active++)
	{
		u_short characterSelectUnlockFlags = csm_Active->unlockFlags;

		if
		(
			// If character slot is unlocked by default, don't use characterSelectUnlockFlags
			// must be cast as signed
			((short)csm_Active->unlockFlags == -1) ||

			// if character is unlocked
			// from 4-byte variable that handles all rewards
			// also the variable written by cheats
			(((sdata->gameProgress.unlocks[characterSelectUnlockFlags>>5] >> (characterSelectUnlockFlags&0x1f)) & 1) != 0)
		)
		{
			u_int iconColor = D230.characterSelect_NeutralColor;

			for (int j = 0; j < gGT->numPlyrNextGame; j++)
			{
				if
				(
					((short)i == characterMenuIDPerPlayer[j]) &&

					// if player selected a character
					 (((int)(short)sdata->characterSelectFlags >> (j & 0x1fU) & 1U) != 0)
				)
				{
					iconColor = D230.characterSelect_ChosenColor;
				}
			}

			struct TransitionMeta* characterSlotTransition = &D230.ptrTransitionMeta[i];

			#ifdef USE_OXIDE
			// can't actually use the characters enum here since these use a different order
			if (i == 15) // nitros oxide
			{
				// use same transition as Fake Crash
				characterSlotTransition = &D230.ptrTransitionMeta[14]; // fake crash
			}
			#endif

			DECOMP_RECTMENU_DrawPolyGT4
			(
				gGT->ptrIcons[data.MetaDataCharacters[csm_Active->characterID].iconID],
				characterSlotTransition->currX + csm_Active->posX + 6,
				characterSlotTransition->currY + csm_Active->posY + 4,

				&gGT->backBuffer->primMem,
				gGT->pushBuffer_UI.ptrOT,

				iconColor, iconColor, iconColor, iconColor, TRANS_50_DECAL, FP(1.0)
			);
		}
	}

	// character slot highlights, character names, character 3D model rotation

	for (int i = 0; i < gGT->numPlyrNextGame; i++)
	{
		int characterMenuIDCurrPlayer = characterMenuIDPerPlayer[i];
		struct CharacterSelectMeta* csm_Active = &D230.csm_Active[characterMenuIDCurrPlayer];

		// if player has not selected a character
		if (((int)(short)sdata->characterSelectFlags >> i & 1U) == 0)
		{
			DECOMP_MM_Characters_AnimateColors
			(
				&colorRGBA, i,

				// flags of which characters are selected
				(int)(short)(sdata->characterSelectFlags & (u_short)(1 << i))
			);

			colorRGBA[0] = (u_char)((int)((u_int)colorRGBA[0] << 2) / 5);
			colorRGBA[1] = (u_char)((int)((u_int)colorRGBA[1] << 2) / 5);
			colorRGBA[2] = (u_char)((int)((u_int)colorRGBA[2] << 2) / 5);

			struct TransitionMeta* characterSlotTransition = &D230.ptrTransitionMeta[characterMenuIDCurrPlayer];

			#ifdef USE_OXIDE
			// can't actually use the characters enum here since these use a different order
			if (characterMenuIDCurrPlayer == 15) // nitros oxide
			{
				// use same transition as Fake Crash
				characterSlotTransition = &D230.ptrTransitionMeta[14]; // fake crash
			}
			#endif

			RECT r80 =
			{
				.x = characterSlotTransition->currX + csm_Active->posX + 3,
				.y = characterSlotTransition->currY + csm_Active->posY + 2,
				.w = 46,
				.h = 29,
			};

			Color color = *(Color *) &colorRGBA;
			// this draws the flashing square that appears when you highlight a character in the character select screen
			DECOMP_CTR_Box_DrawSolidBox(&r80, color, gGT->backBuffer->otMem.startPlusFour);
		}

		if
		(
			(D230.timerPerPlayer[i] == 0) &&
			(D230.characterSelect_charIDs_curr[i] == data.characterIDs[i])
		)
		{
			// get number of players
			int numPlyrNextGame = gGT->numPlyrNextGame;

			// if number of players is 1 or 2
			int fontType = FONT_CREDITS;

			// if number of players is 3 or 4
			if (numPlyrNextGame >= 3) fontType = FONT_SMALL;

			struct TransitionMeta* transitionMeta = &D230.ptrTransitionMeta[i+0x10];
			short sVar10 = transitionMeta->currY + D230.characterSelect_ptrWindowXY[i*2+1];
			short sVar6 = (short)((((u_int)(numPlyrNextGame < 3) ^ 1) << 0x12) >> 0x10);

			if ((numPlyrNextGame == 4) && (i > 1)) sVar6 = sVar10 + sVar6 - 6;
			else							       sVar6 = sVar10 + D230.textPos + sVar6;

			// draw character name string
			DECOMP_DecalFont_DrawLine
			(
				sdata->lngStrings[data.MetaDataCharacters[csm_Active->characterID].name_LNG_long],
				(int)((transitionMeta->currX + D230.characterSelect_ptrWindowXY[i * 2] + (((int)((u_int)D230.characterSelect_sizeX << 0x10) >> 0x10) - ((int)((u_int)D230.characterSelect_sizeX << 0x10) >> 0x1f) >> 1)) * 0x10000) >> 0x10,
				(int)sVar6, fontType, (JUSTIFY_CENTER | ORANGE)
			);
		}

		// spin the character
		D230.characterSelect_angle[i] += FPS_HALF(0x40);
	}

	// not sure what this is

	csm_Active = D230.csm_Active;

	for (int i = 0; i < NUM_ICONS; i++)
	{
		u_short characterSelectUnlockFlags = csm_Active[i].unlockFlags;

		if
		(
			// If Icon is unlocked (from array of icons)
			((short)csm_Active[i].unlockFlags == -1) ||

			// if character is unlocked
			// from 4-byte variable that handles all rewards
			// also the variable written by cheats
			((sdata->gameProgress.unlocks[characterSelectUnlockFlags >> 5] >> (characterSelectUnlockFlags & 0x1fU) & 1) != 0)
		)
		{
			struct TransitionMeta* characterSlotTransition = &D230.ptrTransitionMeta[i];

			#ifdef USE_OXIDE
			// can't actually use the characters enum here since these use a different order
			if (characterMenuIDCurrPlayer == 15) // nitros oxide
			{
				// use same transition as Fake Crash
				characterSlotTransition = &D230.ptrTransitionMeta[14]; // fake crash
			}
			#endif

			RECT r68 =
			{
				.x = characterSlotTransition->currX + csm_Active[i].posX,
				.y = characterSlotTransition->currY + csm_Active[i].posY,
				.w = 52,
				.h = 33,
			};

			// Draw 2D Menu rectangle background
			DECOMP_RECTMENU_DrawInnerRect(&r68, 0, gGT->backBuffer->otMem.startPlusFour);
		}
	}

	// if number of players is not zero
	if (gGT->numPlyrNextGame != 0)
	{
		short* characterSelect_ptrWindowXY = D230.characterSelect_ptrWindowXY;

		for (int i = 0; i < gGT->numPlyrNextGame; i++)
		{
			struct TransitionMeta* transitionMeta = &D230.ptrTransitionMeta[i];

			// store window width and height in one 4-byte variable

			RECT r60 =
			{
				.x = *(short *)((u_int)transitionMeta + 0xa6) + *characterSelect_ptrWindowXY,
				.y = *(short *)((u_int)transitionMeta + 0xa8) + characterSelect_ptrWindowXY[1],
				.w = D230.characterSelect_sizeX,
				.h = D230.characterSelect_sizeY,
			};

			DECOMP_MM_Characters_AnimateColors
			(
				&colorRGBA, i,

				// flags of which characters are selected
				((int)(short)sdata->characterSelectFlags >> i ^ 1U) & 1
			);

			Color color = *(Color *) &colorRGBA;
			DECOMP_RECTMENU_DrawOuterRect_HighLevel(
				&r60, color, 0,
				gGT->backBuffer->otMem.startPlusFour);

			// if player selected a character
			if (((int)(short)sdata->characterSelectFlags >> i & 1U) != 0)
			{
				RECT r58 =
				{
					.x = r60.x,
					.y = r60.y,
					.w = r60.w,
					.h = r60.h,
				};

				for (int j = 0; j < 2; j++)
				{
					r58.x += 3;
					r58.y += 2;
					r58.w -= 6;
					r58.h -= 4;

					colorRGBA[0] = (u_char)((int)((u_int)colorRGBA[0] << 2) / 5);
					colorRGBA[1] = (u_char)((int)((u_int)colorRGBA[1] << 2) / 5);
					colorRGBA[2] = (u_char)((int)((u_int)colorRGBA[2] << 2) / 5);

					color = *(Color *) colorRGBA;
					DECOMP_RECTMENU_DrawOuterRect_HighLevel(
						&r58, color, 0,
						gGT->backBuffer->otMem.startPlusFour);
				}
			}
			characterSelect_ptrWindowXY = characterSelect_ptrWindowXY + 2;

			// Draw 2D Menu rectangle background
			DECOMP_RECTMENU_DrawInnerRect(
				&r60, 9, &gGT->backBuffer->otMem.startPlusFour[3]);

			// not screen-space anymore,
			// this is viewport-space
			r60.x = 0;
			r60.y = 0;

			DECOMP_RECTMENU_DrawRwdBlueRect
			(
				&r60.x, &D230.characterSelect_BlueRectColors[0],
				&gGT->pushBuffer[i].ptrOT[0x3ff], &gGT->backBuffer->primMem
			);
		}
	}
}

void DECOMP_MM_Characters_MenuProc(struct RectMenu* unused)
{
	struct GameTracker* gGT = sdata->gGT;

	int characterMenuIDPerPlayer[4] = {-1, -1, -1, -1};

	for (int i = 0; i < 4; i++)
	{
		characterMenuIDPerPlayer[i] = D230.characterMenuID[data.characterIDs[i]];
	}

	// if menu is not in focus
	if (D230.isMenuTransitioning != IN_MENU)
	{
		DECOMP_MM_TransitionInOut(D230.ptrTransitionMeta, (int)D230.transitionFrames, FPS_DOUBLE(8));
	}

	DECOMP_MM_Characters_SetMenuLayout();
	DECOMP_MM_Characters_DrawWindows(1);

	// if transitioning in
	if (D230.isMenuTransitioning == ENTERING_MENU)
	{
		// if no more frames
		if (D230.transitionFrames == 0)
		{
			// menu is now in focus
			D230.isMenuTransitioning = IN_MENU;
		}
		else
		{
			D230.transitionFrames--;
		}
	}

	// if transitioning out
	if (D230.isMenuTransitioning == EXITING_MENU)
	{
		// increase frame
		D230.transitionFrames++;

		// if more than 12 frames
		if (D230.transitionFrames > FPS_DOUBLE(12))
		{
			// Make a backup of the characters
			// you selected in character selection screen
			DECOMP_MM_Characters_BackupIDs();

			DECOMP_MM_Characters_HideDrivers();

			// if returning to main menu
			if (D230.movingToTrackMenu == 0)
			{
				DECOMP_MM_JumpTo_Title_Returning();
				return;
			}

			// if you are in a cup
			if ((gGT->gameMode2 & CUP_ANY_KIND) != 0)
			{
				sdata->ptrDesiredMenu = &D230.menuCupSelect;
				DECOMP_MM_CupSelect_Init();
				return;
			}

			// if going to track selection
			sdata->ptrDesiredMenu = &D230.menuTrackSelect;
			DECOMP_MM_TrackSelect_Init();
			return;
		}
	}

	struct CharacterSelectMeta* playerCSM = 0;

	PLAYERPOLLING_MM_Characters_MenuProc(playerCSM, characterMenuIDPerPlayer);

	DECOMP_MM_Characters_PreventOverlap();

	struct CharacterSelectMeta* csm_Active = D230.csm_Active;

	for (int i = 0; i < 4; i++)
	{
		data.characterIDs[i] = csm_Active[characterMenuIDPerPlayer[i]].characterID;
	}

	DISPLAYRECTMENU_MM_Characters_MenuProc(characterMenuIDPerPlayer);
}