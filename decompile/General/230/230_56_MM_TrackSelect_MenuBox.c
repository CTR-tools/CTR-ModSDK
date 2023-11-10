#include <common.h>

void MM_TransitionInOut(struct TransitionMeta*, int, int);
void MM_Characters_RestoreIDs();
void MM_Battle_Init();
char MM_TrackSelect_boolTrackOpen(void*);

void DECOMP_MM_TrackSelect_MenuBox(struct MenuBox *mb)
{
	char bVar1;
	char bVar2;
	char bVar3;
	char bVar4;
	short sVar5;
	u_short currTrack;
	short sVar7;
	short elapsedFrames;
	u_int uVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	int *piVar12;
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

	elapsedFrames = OVR_230.trackSel_transitionFrames;

	// if you are not in track selection menu
	if (OVR_230.trackSel_transitionState != 1)
	{
		// if transitioning in
		if (OVR_230.trackSel_transitionState == 0)
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

			MM_TransitionInOut(&OVR_230.transitionMeta_trackSel[0], elapsedFrames, 8);

			elapsedFrames--;

			// ran out of frames
			if (elapsedFrames == 0)
			{
				// menu is now in focus
				OVR_230.trackSel_transitionState = 1;
			}
		}
		// transitioning out
		else if (OVR_230.trackSel_transitionState == 2)
		{
			MM_TransitionInOut(&OVR_230.transitionMeta_trackSel[0], elapsedFrames, 8);

			elapsedFrames++;

			if (elapsedFrames > 12)
			{
				// if track has not been chosen
				if (OVR_230.trackSel_postTransition_boolStart == 0)
				{
					// return to character selection
					sdata->ptrDesiredMenuBox = &OVR_230.menubox_characterSelect;
					MM_Characters_RestoreIDs();
					return;
				}

				// if track has been chosen

				// if you are in battle mode
				if ((gGT->gameMode1 & BATTLE_MODE) != 0)
				{
					// open weapon selection menu
					sdata->ptrDesiredMenuBox = &OVR_230.menubox_battleWeapons;
					MM_Battle_Init();
					return;
				}

				// if you are not in battle mode

				// if you are in time trial mode
				if ((gGT->gameMode1 & MAIN_MENU) != 0)
				{
					// allocate room at the end of RAM for ghosts
					sdata->ptrGhostTapePlaying = MEMPACK_AllocHighMem(0x3e00, OVR_230.s_loaded_ghost_data);

					memset(sdata->ptrGhostTapePlaying, 0, 0x28);

					// by default, dont show ghost in race
					sdata->boolReplayHumanGhost = 0;

					LoadSave_ToggleMode(0x30);

					// open the ghost selection menu
					sdata->ptrDesiredMenuBox = &data.menuBox_GhostSelection;
					return;
				}

				// passthrough MenuBox for the function
				// TitleBeginTrack
				sdata->ptrDesiredMenuBox = &data.menuBox_TitleBeginTrack;

				// make error message posY appear
				// near middle of screen
				sdata->errorMessagePosIndex = 0;

				return;
			}
		}
	}
	OVR_230.trackSel_transitionFrames = elapsedFrames;
	sVar7 = OVR_230.trackSel_transitionState;

	// if you are in battle mode
	if ((gGT->gameMode1 & BATTLE_MODE) != 0)
	{
		selectMenu = &OVR_230.battleTracks[0];

		numTracks = 7;
	}

	selectMenu = &OVR_230.arcadeTracks[0];

	numTracks = 18;

	currTrack = mb->rowSelected;

	// if you're not loading a LEV
	if (OVR_230.trackSel_changeTrack_frameCount == 0)
	{
		// if lap selection menu is closed
		if (OVR_230.trackSel_boolOpenLapBox == 0)
		{
			switch (sdata->buttonTapPerPlayer[0] & (BTN_UP | BTN_DOWN | BTN_TRIANGLE | BTN_SQUARE_one | BTN_CROSS_one | BTN_CIRCLE))
			{
				
			case BTN_UP:
				
				// change track sound
				OtherFX_Play(0, 1);
				
				// look for unlocked track
				do
				{
					currTrack--;
					
					// if index is negative
					if (currTrack < 0)
						// set to the last track
						currTrack = numTracks - 1;
					
				} while (!MM_TrackSelect_boolTrackOpen(&selectMenu[currTrack]));
				
				OVR_230.trackSel_direction = 1;
				goto LAB_800b0424;
			
			case BTN_DOWN:
				
				// change track sound
				OtherFX_Play(0, 1);
				
				// look for unlocked track
				do
				{
					currTrack++;
					
					// if you go beyond max number of tracks
					if (currTrack >= numTracks)
						// set to the first trrack
						currTrack = 0;

				} while (!MM_TrackSelect_boolTrackOpen(&selectMenu[currTrack]));
				
				OVR_230.trackSel_direction = -1;
				goto LAB_800b0424;
			
			case BTN_CROSS_one:
			case BTN_CIRCLE:
				// "enter/confirm" sound
				OtherFX_Play(1, 1);
				if ((gGT->gameMode1 & (BATTLE_MODE | TIME_TRIAL)) == 0)
				{
					// open lap select menu
					OVR_230.trackSel_boolOpenLapBox = sVar7;
					goto LAB_800b04b8;
				}
				// ready to race
				OVR_230.trackSel_postTransition_boolStart = sVar7;
				// transition out (but go into race)
				OVR_230.trackSel_transitionState = 2;
				break;
				
			case BTN_TRIANGLE:
			case BTN_SQUARE_one:
				// "go back" sound
				OtherFX_Play(2, 1);
				// not ready to race
				OVR_230.trackSel_postTransition_boolStart = 0;
				// transition out
				OVR_230.trackSel_transitionState = 2;
				break;
			default:
				goto LAB_800b04b8;
			}

		LAB_800b0424:
			// 3 frames of moving track list
			OVR_230.trackSel_changeTrack_frameCount = 3;
			OVR_230.trackSel_currTrack = currTrack;

		LAB_800b04b8:
			// clear gamepad input (for menus)
			MENUBOX_ClearInput();
			goto LAB_800b05b8;
		}
	}

	// if you are loading a LEV
	else
	{
		// if lap selection menu is closed
		if (OVR_230.trackSel_boolOpenLapBox == 0)
			goto LAB_800b05b8;
	}

	sVar7 = 0;

	// copy LapRow from 8d920 to temp variable b55ae
	*(char *)0x800b55ae = sdata->uselessLapRowCopy;

	// If you're in track selection menu
	if (OVR_230.trackSel_transitionState == 1)
	{
		sVar7 = MENUBOX_ProcessInput((struct MenuBox *)0x800b5594);
	}

	// This function might alter b55ae to make sure it doesn't go out of bounds
	MENUBOX_DrawSelf((struct MenuBox *)0x800b5594,
									 OVR_230.transitionMeta_trackSel[2].currX,
									 OVR_230.transitionMeta_trackSel[2].currY, 0xa4);

	// put LapRow back into 8d920
	sdata->uselessLapRowCopy = *(char *)0x800b55ae;

	// get number of laps from a short array based on lap row number
	// Lap Row = 0 -> 3
	// Lap Row = 1 -> 5
	// Lap Row = 2 -> 7

	gGT->numLaps = ((short *)0x800b5574)[*(char *)0x800b55ae];
	
	// if it is time to start the race
	if (sVar7 == 1)
	{
		// try to start the race
		OVR_230.trackSel_transitionState = 2;

		// if this is 1 (which it is), the race starts,
		// otherwise, you go back to character selection
		OVR_230.trackSel_postTransition_boolStart = sVar7;
	}

	// If it is not time to start the race
	else
	{
		if (sVar7 == -1)
		{
			// close lap selection menu
			OVR_230.trackSel_boolOpenLapBox = 0;
		}
	}

	// If "One Lap Race" Cheat is enabled
	if ((gGT->gameMode2 & CHEAT_ONELAP) != 0)
	{
		// Set number of Laps to 1
		gGT->numLaps = 1;
	}

LAB_800b05b8:

	// decrease frame from track list motion
	iVar9 = OVR_230.trackSel_changeTrack_frameCount + -1;
	if ((0 < OVR_230.trackSel_changeTrack_frameCount) && (OVR_230.trackSel_changeTrack_frameCount = iVar9, iVar9 == 0))
	{
		mb->rowSelected = OVR_230.trackSel_currTrack;
	}

	// not transitioning
	uVar14 = 0;

	// if you are transitioning out of level selection
	if (
			(OVR_230.trackSel_changeTrack_frameCount != 0) ||
			(OVR_230.trackSel_transitionState == 2))
	{
		// transitioning,
		// which means stop drawing track video,
		// just draw icon
		uVar14 = 1;
	}

	MM_TrackSelect_Video_State(uVar14);

	uVar15 = (u_int)numTracks;
	sVar7 = mb->rowSelected;
	gGT->currLEV = selectMenu[sVar7].levID;
	iVar9 = (int)sVar7 + -1;

	for (iVar18 = 0; iVar18 < 4; iVar18++)
	{
		do
		{
			iVar10 = iVar9;
			if (iVar9 << 0x10 < 0)
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
		if (0 < OVR_230.trackSel_changeTrack_frameCount)
		{
			uVar15 = uVar15 + (((3 - OVR_230.trackSel_changeTrack_frameCount) * 0x73) / 3) * (int)OVR_230.trackSel_direction;
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
		iVar11 = (u_int)OVR_230.transitionMeta_trackSel[0].currX + (MATH_Cos(uVar15) * 0x19 >> 9) + -0xb4;

		// posY of track list
		// 800b5548 is for transition in and out
		iVar9 = (u_int)OVR_230.transitionMeta_trackSel[0].currY + (MATH_Sin(uVar15) * 200 >> 0xc);

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
				if ((timeTrialFlags & ((u_short *)0x800b55c8)[iVar17]) != 0)
				{
					// 0x0E: driver_9 (papu) (yellow)
					// 0x16: silver

					// pointer to color data of star
					piVar12 = data.ptrColor[((u_short *)0x800b55c4)[iVar17]];

					struct Icon** iconPtrArray =
						ICONGROUP_GETICONS(gGT->iconGroup[5]);

					DecalHUD_DrawPolyGT4(iconPtrArray[0x37],
						iVar11 + 0x104, (int)sVar7 + iVar17 * 8 + 4,

						// pointer to PrimMem struct
						&gGT->backBuffer->primMem,

						// pointer to OT mem
						gGT->tileView_UI.ptrOT,

						// color data
						piVar12[0],
						piVar12[1],
						piVar12[2],
						piVar12[3],

						0, FP(1.0));
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
		DecalFont_DrawLine(
				sdata->lngStrings[data.metaDataLEV[selectMenu[iVar10].levID].name_LNG],
				(iVar11 + 8),
				(iVar9 + 0x65),
				1, 0);

		if ((OVR_230.trackSel_changeTrack_frameCount == 0) && ((short)iVar18 == 4))
		{
			// if you are in time trial mode
			if ((gGT->gameMode1 & MAIN_MENU) != 0)
			{
				// Check if this track has Ghost Data
				uVar15 = GhostData_NumGhostsForLEV(selectMenu[iVar10].levID);

				// If this track has Ghost Data
				if ((uVar15 & 0xffff) != 0)
				{
					// Flash Colors
					if ((sdata->frameCounter & 4) == 0)
					{
						uVar14 = 0xffff8004;
					}
					else
					{
						uVar14 = 0xffff8001;
					}

					// "GHOST DATA EXISTS"
					DecalFont_DrawLine(sdata->lngStrings[0x1ac], 
						(iVar11 + 0x80),
						(iVar9 + 0x76),
						2, uVar14);
				}
			}
			q.x = r.x + 6;
			q.y = r.y + 4;
			q.w = r.w - 12;
			q.h = r.h - 8;

			CTR_Box_DrawClearBox(&q, &sdata->menuRowHighlight_Normal, TRANS_50_DECAL,
													 gGT->backBuffer->otMem.startPlusFour,

													 // pointer to PrimMem struct
													 &gGT->backBuffer->primMem);
		}
		uVar15 = (u_int)numTracks;

		// Draw 2D Menu rectangle background
		MENUBOX_DrawInnerRect(&r, 0, gGT->backBuffer->otMem.startPlusFour);

		do
		{
			if (uVar15 <= iVar10)
			{
				iVar10 = 0;
			}
			uVar8 = MM_TrackSelect_boolTrackOpen(&selectMenu[iVar10]);
			iVar10++;
		} while ((uVar8 & 0xffff) == 0);

		iVar18 = iVar18 + 1;
		iVar9 = iVar18 * 0x10000;
		if (8 < iVar18 * 0x10000 >> 0x10)
		{	
			p.w = 0xb0;
			p.h = 0x4b;
		
			// posX of "SELECT LEVEL"
			p.x = OVR_230.transitionMeta_trackSel[1].currX + 0x134;
			
			// posY of "SELECT LEVEL"
			// near-top if map exists, near-mid if no map
			p.y = OVR_230.transitionMeta_trackSel[1].currY + 0x3a;
				if (-1 < selectMenu[mb->rowSelected].mapTextureID)
					p.y = OVR_230.transitionMeta_trackSel[1].currY + 5;

			// _OVR_230.trackSel_boolOpenLapBox is the boolean to show
			// the selection menu for number of laps:
			// 3, 5, 7

			// If the lap selection menu is closed
			if (OVR_230.trackSel_boolOpenLapBox == 0)
			{
				// "SELECT"
				DecalFont_DrawLine(sdata->lngStrings[0x69],
					(OVR_230.transitionMeta_trackSel[3].currX + 0x18c),
					(OVR_230.transitionMeta_trackSel[3].currY + (u_int)p.y),
					1, 0xffff8000);

				// "LEVEL"
				DecalFont_DrawLine(sdata->lngStrings[0x6a],
					(OVR_230.transitionMeta_trackSel[3].currX + 0x18c),
					(OVR_230.transitionMeta_trackSel[3].currY + (u_int)p.y + 0x10),
					1, 0xffff8000);
			}
		
			// next, draw the map icon, below "SELECT LEVEL",
			// exactly 0x22 (34) pixels below the text
			p.y += 0x22;
		
			if (
					(-1 < selectMenu[mb->rowSelected].mapTextureID) &&

					// If lap selection menu is closed
					(OVR_230.trackSel_boolOpenLapBox == 0)
				)
			{
				int mapID = selectMenu[mb->rowSelected].mapTextureID;
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

					UI_Map_DrawMap(

							// top half
							iconMap0,

							// bottom half
							iconMap1,

							// 100, 0x4b, 0xb0

							// X
							(int)((short *)0x800b55cc)[iVar18 * 3] + 
									p.x +
									(OVR_230.transitionMeta_trackSel[2].currX - OVR_230.transitionMeta_trackSel[1].currX) +
									(0xb0 >> 1) +
									(iVar9 >> 1),

							// Y
							(int)((short *)0x800b55ce)[iVar18 * 3] + 
									p.y +
									(OVR_230.transitionMeta_trackSel[2].currY - OVR_230.transitionMeta_trackSel[1].currY) +
									//0x49+0x22+
									(100 >> 1) +
									(iVar10 >> 1),

							// pointer to PrimMem struct
							&gGT->backBuffer->primMem,

							// pointer to OT mem
							gGT->tileView_UI.ptrOT,

							// 1 = draw map with regular color (white) - used for the main layer of the minimap in the track select screen
							// 2 = draw map blue - used for the outline of the minimap in the track select screen
							// 3 = draw map black - used for the shadow of the minimap in the track select screen
							(u_int)((char *)0x800b55d0)[iVar18 * 6]);
				}
			}
			MM_TrackSelect_Video_Draw(
					&p, selectMenu, (int)(short)OVR_230.trackSel_currTrack,
					(u_int)(OVR_230.trackSel_transitionState == 2), 0);
			return;
		}
	} while (true);
}