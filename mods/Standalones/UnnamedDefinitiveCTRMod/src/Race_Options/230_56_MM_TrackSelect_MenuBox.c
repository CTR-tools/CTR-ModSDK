#include <common.h>

void MM_TransitionInOut(struct TransitionMeta*, int, int);
void MM_Characters_RestoreIDs();
void MM_Battle_Init();
char MM_TrackSelect_boolTrackOpen(void*);

void UDCTRM_RaceOptions();

u_int UDCTRM_RO_isOpen = false;

void DECOMP_MM_TrackSelect_MenuProc(struct RectMenu* menu)
{
	char bVar1;
	char bVar2;
	char bVar3;
	char bVar4;
	short sVar5;
	short currTrack;
	short sVar7;
	short elapsedFrames;
	u_int uVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	int *starColor;
	u_int uVar14;
	u_int uVar15;
	int iVar17;
	int iVar18;
	RECT r;
	RECT q;
	RECT p;
	u_int local_44;
	short numTracks;

	struct MainMenu_LevelRow *selectMenu;
	struct GameTracker *gGT = sdata->gGT;

	elapsedFrames = D230.trackSel_transitionFrames;

	// if you are not in track selection menu
	if (D230.trackSel_transitionState != IN_MENU)
	{
		// if transitioning in
		if (D230.trackSel_transitionState == ENTERING_MENU)
		{
			// make error message posY appear
			// near bottom of screen
			sdata->errorMessagePosIndex = 1;

			// if you are in Battle mode
			if ((gGT->gameMode1 & BATTLE_MODE) != 0)
			{
				// make error message posY appear
				// near top of screen
				sdata->errorMessagePosIndex = 2;
			}

			MM_TransitionInOut(&D230.transitionMeta_trackSel[0], elapsedFrames, 8);
			
			// ran out of frames
			if (elapsedFrames == 0)
			{
				// menu is now in focus
				D230.trackSel_transitionState = IN_MENU;
			}
			
			else
			{
				elapsedFrames--;
			}
		}
		// transitioning out
		else if (D230.trackSel_transitionState == EXITING_MENU)
		{
			MM_TransitionInOut(&D230.transitionMeta_trackSel[0], elapsedFrames, 8);
			elapsedFrames++;

			if (elapsedFrames > 12)
			{
				// if track has not been chosen
				if (D230.trackSel_StartRaceAfterFadeOut == 0)
				{
					// return to character selection
					sdata->ptrDesiredMenu = &D230.menuCharacterSelect;
					MM_Characters_RestoreIDs();
					return;
				}

				// if track has been chosen

				// if you are in battle mode
				if ((gGT->gameMode1 & BATTLE_MODE) != 0)
				{
					// open weapon selection menu
					sdata->ptrDesiredMenu = &D230.menuBattleWeapons;
					MM_Battle_Init();
					return;
				}

				// if you are not in battle mode

				// if you are in time trial mode
				if ((gGT->gameMode1 & TIME_TRIAL) != 0)
				{
					// allocate room at the end of RAM for ghosts
					sdata->ptrGhostTapePlaying = MEMPACK_AllocHighMem(0x3e00, R230.s_loaded_ghost_data);

					memset(sdata->ptrGhostTapePlaying, 0, 0x28);

					// by default, dont show ghost in race
					sdata->boolReplayHumanGhost = 0;

					SelectProfile_ToggleMode(0x30);

					// open the ghost selection menu
					sdata->ptrDesiredMenu = &data.menuGhostSelection;
					return;
				}

				// passthrough Menu for the function
				// QueueLoadTrack
				sdata->ptrDesiredMenu = &data.menuQueueLoadTrack;

				// make error message posY appear
				// near middle of screen
				sdata->errorMessagePosIndex = 0;

				return;
			}
		}
	}
	D230.trackSel_transitionFrames = elapsedFrames;

	// default arcade tracks
	selectMenu = &D230.arcadeTracks[0];
	numTracks = 18;

	// if you are in battle mode
	if ((gGT->gameMode1 & BATTLE_MODE) != 0)
	{
		selectMenu = &D230.battleTracks[0];
		numTracks = 7;
	}

	currTrack = menu->rowSelected;

	/////////////////////////// CHANGED FOR UDCTRM ///////////////////////////
	if (!(UDCTRM_RO_isOpen))
	{
		// if not changing levels
		if (D230.trackSel_changeTrack_frameCount == 0)
		{
			switch (sdata->buttonTapPerPlayer[0] & (BTN_UP | BTN_DOWN | BTN_TRIANGLE | BTN_SQUARE_one | BTN_CROSS_one | BTN_CIRCLE | BTN_START))
			{
				
			case BTN_UP:
				
				// look for unlocked track
				do
				{
					currTrack--;
					
					// if index is negative
					if (currTrack < 0)
						// set to the last track
						currTrack = numTracks - 1;
					
				} while (!MM_TrackSelect_boolTrackOpen(&selectMenu[currTrack]));
				
				D230.trackSel_currTrack = currTrack;
				D230.trackSel_changeTrack_frameCount = 3;
				D230.trackSel_direction = 1;
				
				OtherFX_Play(0, 1);
				break;
			
			case BTN_DOWN:
				
				// look for unlocked track
				do
				{
					currTrack++;
					
					// if you go beyond max number of tracks
					if (currTrack >= numTracks)
						// set to the first trrack
						currTrack = 0;

				} while (!MM_TrackSelect_boolTrackOpen(&selectMenu[currTrack]));
				
				D230.trackSel_currTrack = currTrack;
				D230.trackSel_changeTrack_frameCount = 3;
				D230.trackSel_direction = -1;
				
				OtherFX_Play(0, 1);
				break;
			
			case BTN_CROSS_one:
			case BTN_CIRCLE:
				// "enter/confirm" sound
				OtherFX_Play(1, 1);
				
				// if Battle or Time Trial, skip straight to level
				D230.trackSel_StartRaceAfterFadeOut = D230.trackSel_transitionState;
				D230.trackSel_transitionState = EXITING_MENU;
				break;
				
			case BTN_TRIANGLE:
			case BTN_SQUARE_one:
				// "go back" sound
				OtherFX_Play(2, 1);
				// not ready to race
				D230.trackSel_StartRaceAfterFadeOut = 0;
				// transition out
				D230.trackSel_transitionState = EXITING_MENU;
				break;
			case BTN_START:
				if (!(gGT->gameMode1 & BATTLE_MODE))
				{
					OtherFX_Play(1, 1);
					UDCTRM_RO_isOpen = true;
				}
				break;
			default:
				break;
			}

			// clear gamepad input (for menus)
			RECTMENU_ClearInput();
		}
	}
	else
	{
		UDCTRM_RaceOptions();
	}
	/////////////////////////// SECTION 1          ///////////////////////////

	// decrease frame from track list motion
	iVar9 = D230.trackSel_changeTrack_frameCount + -1;
	if ((0 < D230.trackSel_changeTrack_frameCount) && (D230.trackSel_changeTrack_frameCount = iVar9, iVar9 == 0))
	{
		menu->rowSelected = D230.trackSel_currTrack;
	}

	// not transitioning
	uVar14 = 0;

	// if you are transitioning out of level selection
	if
	(
		(D230.trackSel_changeTrack_frameCount != 0) ||
		(D230.trackSel_transitionState == EXITING_MENU) ||
		(UDCTRM_RO_isOpen != 0)
	)
	{
		// transitioning,
		// which means stop drawing track video,
		// just draw icon
		uVar14 = 1;
	}

	MM_TrackSelect_Video_State(uVar14);

	uVar15 = (u_int)numTracks;
	gGT->currLEV = selectMenu[menu->rowSelected].levID;
	iVar9 = (int)menu->rowSelected + -1;

	for (iVar18 = 0; iVar18 < 4; iVar18++)
	{
		do
		{
			iVar10 = iVar9;
			if (iVar9 < 0)
			{
				iVar10 = uVar15 - 1;
			}

			uVar8 = MM_TrackSelect_boolTrackOpen(&selectMenu[iVar10]);

			iVar9 = iVar10 - 1;
		} while ((uVar8 & 0xffff) == 0);

		iVar9 = iVar10 - 1;
	}
	iVar18 = 0;
	iVar9 = 0;

	// loop through tracks in track list
	do
	{
		// This part actually "moves" the rows,
		// when pressing the Up and Down buttons on D-Pad
		uVar15 = ((iVar9 >> 0x10) + -4) * 0x73;
		if (0 < D230.trackSel_changeTrack_frameCount)
		{
			uVar15 = uVar15 + (((3 - D230.trackSel_changeTrack_frameCount) * 0x73) / 3) * (int)D230.trackSel_direction;
		}

		// This is just MATH_Cos and Math_Sin 
		#if 0
		// approximate trigonometry
		sVar7 = (short)data.trigApprox[uVar15];
		iVar9 = data.trigApprox[uVar15] >> 0x10;

		if ((uVar15 & 0x400) == 0)
		{
			iVar17 = (int)sVar7;
			iVar11 = iVar9;
			if ((uVar15 & 0x800) != 0)
			{
				iVar11 = -iVar9;
				goto LAB_800b0774;
			}
		}
		else
		{
			iVar11 = (int)sVar7;
			iVar17 = iVar9;
			if ((uVar15 & 0x800) == 0)
			{
				iVar11 = -iVar11;
			}
			else
			{
			LAB_800b0774:
				iVar17 = -iVar17;
			}
		}
		#endif
		r.w = 0x100;
		r.h = 0x19;

		// posX of track list
		// 800b5546 is for transition in and out
		iVar11 = (u_int)D230.transitionMeta_trackSel[0].currX + (MATH_Cos(uVar15) * 0x19 >> 9) + -0xb4;

		// posY of track list
		// 800b5548 is for transition in and out
		iVar9 = (u_int)D230.transitionMeta_trackSel[0].currY + (MATH_Sin(uVar15) * 200 >> 0xc);

		sVar7 = (short)iVar9 + 0x60;
		r.x = (short)iVar11;
		r.y = sVar7;

		// if you are in time trial mode
		if ((gGT->gameMode1 & TIME_TRIAL) != 0)
		{
			// backup level ID
			sVar5 = gGT->levelID;

			// draw stars if N Tropy or Oxide are beaten,
			// loop twice
			for (iVar17 = 0; iVar17 < 2; iVar17++)
			{
				// set level ID to the level you're hovering on, in the main menu
				gGT->levelID = selectMenu[iVar10].levID;

				// (useless?)
				GAMEPROG_GetPtrHighScoreTrack();

				int timeTrialFlags = sdata->gameProgress.highScoreTracks[gGT->levelID].timeTrialFlags;

				// if star is earned
				if (((timeTrialFlags >> D230.timeTrialFlagGet[iVar17]) & 1) != 0)
				{
					// pointer to color data of star
					starColor = data.ptrColor[D230.timeTrialStarCol[iVar17]];

					struct Icon** iconPtrArray = ICONGROUP_GETICONS(gGT->iconGroup[5]);

					DecalHUD_DrawPolyGT4
					(
						iconPtrArray[0x37],
						iVar11 + 0x104, (int)sVar7 + iVar17 * 8 + 4,

						// pointer to PrimMem struct
						&gGT->backBuffer->primMem,

						// pointer to OT mem
						gGT->pushBuffer_UI.ptrOT,

						// color data
						starColor[0],
						starColor[1],
						starColor[2],
						starColor[3],

						0, FP(1.0)
					);
				}
			}
			// restore levelID
			gGT->levelID = sVar5;

			// (useless?)
			GAMEPROG_GetPtrHighScoreTrack();
		}

		// alphabet
		// DAT_80083A88 goes to "n"
		// + 0x18 -> "o"
		// + 0x18 -> "p"
		// + 0x18 -> "q"
		// and so on
		
		// Draw string
		DecalFont_DrawLine
		(
			sdata->lngStrings[data.metaDataLEV[selectMenu[iVar10].levID].name_LNG],
			(iVar11 + 8),
			(iVar9 + 0x65),
			FONT_BIG, ORANGE
		);

		if ((D230.trackSel_changeTrack_frameCount == 0) && ((short)iVar18 == 4))
		{
			// if you are in time trial mode
			if ((gGT->gameMode1 & TIME_TRIAL) != 0)
			{
				// Check if this track has Ghost Data
				uVar15 = RefreshCard_BoolGhostForLEV(selectMenu[iVar10].levID);

				// If this track has Ghost Data
				if ((uVar15 & 0xffff) != 0)
				{
					// Flash Colors
					if ((sdata->frameCounter & 4) == 0)
					{
						uVar14 = (JUSTIFY_CENTER | WHITE);
					}
					else
					{
						uVar14 = (JUSTIFY_CENTER | PERIWINKLE);
					}

					// "GHOST DATA EXISTS"
					DecalFont_DrawLine
					(
						sdata->lngStrings[0x6B], 
						(iVar11 + 0x80),
						(iVar9 + 0x76),
						FONT_SMALL, uVar14
					);
				}
			}
			q.x = r.x + 6;
			q.y = r.y + 4;
			q.w = r.w - 12;
			q.h = r.h - 8;

			CTR_Box_DrawClearBox
			(
				&q, &sdata->menuRowHighlight_Normal, TRANS_50_DECAL,

				gGT->backBuffer->otMem.startPlusFour,

				// pointer to PrimMem struct
				&gGT->backBuffer->primMem
			);
		}
		uVar15 = (u_int)numTracks;

		// Draw 2D Menu rectangle background
		RECTMENU_DrawInnerRect(&r, 0, gGT->backBuffer->otMem.startPlusFour);

		do
		{
			iVar10++;
			
			if (uVar15 <= iVar10)
			{
				iVar10 = 0;
			}
			uVar8 = MM_TrackSelect_boolTrackOpen(&selectMenu[iVar10]);
			
		} while ((uVar8 & 0xffff) == 0);

		iVar18 = iVar18 + 1;
		iVar9 = iVar18 * 0x10000;
		if (8 < iVar18 * 0x10000 >> 0x10)
		{	
			p.w = 0xb0;
			p.h = 0x4b;
		
			// posX of "SELECT LEVEL"
			p.x = D230.transitionMeta_trackSel[1].currX + 0x134;
			
			// posY of "SELECT LEVEL"
			// near-top if map exists, near-mid if no map
			p.y = D230.transitionMeta_trackSel[1].currY + 0x3a;
			
			if (-1 < selectMenu[menu->rowSelected].mapTextureID)
				p.y = D230.transitionMeta_trackSel[1].currY + 5;
		
			/////////////////////////// CHANGED FOR UDCTRM ///////////////////////////
			if ((gGT->gameMode1 & BATTLE_MODE) == 0)
			{
				p.y += 8;

				// "OPTIONS"
				DecalFont_DrawMultiLine
				(
					sdata->lngStrings[604],
					(D230.transitionMeta_trackSel[3].currX + 0x18c),
					(D230.transitionMeta_trackSel[3].currY + (u_int)p.y + 180),
					250,
					FONT_SMALL, (JUSTIFY_CENTER | ORANGE)
				);
			}
			/////////////////////////// SECTION 2         ///////////////////////////
		
			if (-1 < selectMenu[menu->rowSelected].mapTextureID)
			{
				int mapID = selectMenu[menu->rowSelected].mapTextureID;
				struct Icon* iconMap0 = gGT->ptrIcons[mapID+0];
				struct Icon* iconMap1 = gGT->ptrIcons[mapID+1];

				// icon data
				bVar1 = iconMap0->texLayout.v2;
				bVar2 = iconMap0->texLayout.v0;
				bVar3 = iconMap1->texLayout.v2;
				bVar4 = iconMap1->texLayout.v0;

				iVar9 = (iconMap0->texLayout.u1 - iconMap0->texLayout.u0);

				// draw six track minimaps on menu
				// map 1 is the regular color, which is white
				// map 2 is blue and shifted 2px to the left
				// map 3 is blue and shifted 2px to the right
				// map 4 is blue and shifted 1px downwards
				// map 5 is blue and shifted 1px upwards
				// map 6 is black and shifted 6px downwards and 12px to the right
				for (iVar18 = 0; iVar18 < 6; iVar18++)
				{
					iVar10 = ((((u_int)bVar1 - (u_int)bVar2) + (u_int)bVar3) - (u_int)bVar4);

					UI_Map_DrawMap
					(
						// top half
						iconMap0,

						// bottom half
						iconMap1,

						// X
						D230.drawMapOffset[iVar18].offsetX + 
									p.x +
									(D230.transitionMeta_trackSel[2].currX - D230.transitionMeta_trackSel[1].currX) +
									(0xb0 >> 1) +
									(iVar9 >> 1),

						// Y
						D230.drawMapOffset[iVar18].offsetY + 
									p.y +
									(D230.transitionMeta_trackSel[2].currY - D230.transitionMeta_trackSel[1].currY) +
									0x49+0x22+
									0x10 + // idk how bitshifting pulls 0x10 in ghidra, but that's it
									(iVar10 >> 1),

						// pointer to PrimMem struct
						&gGT->backBuffer->primMem,

						// pointer to OT mem
						gGT->pushBuffer_UI.ptrOT,

						// 1 = draw map with regular color (white) - used for the main layer of the minimap in the track select screen
						// 2 = draw map blue - used for the outline of the minimap in the track select screen
						// 3 = draw map black - used for the shadow of the minimap in the track select screen
						D230.drawMapOffset[iVar18].type
					);
				}
			}
			MM_TrackSelect_Video_Draw
			(
				&p, selectMenu, (int)(short)D230.trackSel_currTrack,
				(u_int)(D230.trackSel_transitionState == EXITING_MENU), 0
			);
			return;
		}
	} while (true);
}