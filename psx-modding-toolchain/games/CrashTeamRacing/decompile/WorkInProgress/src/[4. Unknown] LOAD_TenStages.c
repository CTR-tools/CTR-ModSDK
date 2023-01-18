#include <common.h>

void Cutscene_VolumeBackup();
void CDSYS_XAPauseRequest();
void MEMPACK_SwapPacks(int index);
int StringToLevID(char* str);
void MEMPACK_PopToState(int id);
u_int LOAD_VramFile(struct BigHeader* bigfile, u_int fileIndex, u_int* destination, u_int* sizePtr, int callback);
void LOAD_Callback_LEV_Adv(struct LoadQueueSlot * lqs);
void UpdateIntroScreen();
int MEMPACK_PushState();
void SetPrimMemSize(u_int* param_1);
void SetOTMemSize(u_int* param_1);
void AllocateAllPools(u_int* param_1);
void LOAD_OvrEndRace(u_int* param_1);
void LOAD_OvrLOD(int param_1);
void LOAD_OvrThreads(u_int param_1);
void Music_Restart();
void MM_JumpTo_Title_FirstTime();
void MM_JumpTo_Characters();
void MM_JumpTo_TrackSelect();
void MM_JumpTo_BattleSetup();
void CS_Garage_Init();
void MM_JumpTo_Scrapbook(struct BigHeader* bigfile);
void LOAD_DriverMPK(struct BigHeader* bigfile, int levelLOD, void* callback);
void INSTANCE_ModelGlobal_Clear(struct GameTracker* gGT);
void LOAD_GlobalModelPtrs_MPK();
void DecalGlobal_Clear(struct GameTracker* gGT);
void DecalGlobal_Store(struct GameTracker* gGT, struct Icon* icon); // second parameter might be wrong --Super
void Music_Stop();
void CseqMusic_StopAll();
void Music_LoadBanks();
u_int Music_AsyncParseBanks();
void Cutscene_VolumeRestore();
void* MEMPACK_AllocMem(int allocSize);
void MEMPACK_NewPack_StartEnd(void* start, int size);
u_int LOAD_GetAdvPackIndex();
int MEMPACK_GetFreeBytes();
void* MEMPACK_AllocHighMem(int allocSize);
void LOAD_AppendQueue(int bigfile, int type, int fileIndex, void* destinationPtr, unsigned int callback);
void DebugFont_Init(struct GameTracker* gGT);
void INSTANCE_ModelGlobal_Store(struct GameTracker* gGT, int param_2, int* param_3);
int* DecalGlobal_Find1(struct Level* level, char* str);
int* DecalGlobal_Find2(u_int* param_1, char* str);
void Audio_SetState_Safe(int param_1);
u_int CheckeredFlag_IsFullyOffScreen();
void CheckeredFlag_BeginTransition(int param_1);
void ElimBG_Deactivate(int param_1);

// LOAD_TenStages
// loadingStage is loading stage
// bigfile is the Pointer to "cd position of bigfile"
int LOAD_TenStages(struct GameTracker* gGT, int loadingStage, struct BigHeader* bigfile)
{
	// u_char* hudFlags; -- redundant
	u_char numPlyrNextGame;
	// u_char* moredata; -- redundant
	short sVar4;
	int iVar5;
	u_int uVar6;
	CdlCB pcVar7;
	u_int* puVar8;
	int iVar9;
	// u_int gameMode1; -- redundant
	u_char hudFlags;
	int iVar12;
	char *levelNamePtr;
	// u_char* moremoredata; -- redundant
	int *piVar15;
	u_int uVar16;
	u_int uVar17;
	u_char auStack40 [8];

	// pointer to LEV
	iVar9 = sdata.ptrLEV_DuringLoading;

	// if game is loading
	if (sdata.load_inProgress != 0)
	{
		return loadingStage;
	}

	// if game is not loading, continue

	switch(loadingStage)
	{
		case 0:

			// if level is not in range of 0x28 and 0x28+1,
			// if level is not AdvGarage or Naughty Dog Box Scene
			if (1 < sdata->gGT->levelID - 0x28U)
			{
				Cutscene_VolumeBackup();
			}

			CDSYS_XAPauseRequest();

			// if you've already drawn intro frames
			// "sony computer entertainment" + "copyright page"
			if (sdata.boolShownIntros == 0)
			{
				// change active allocation system to #1
				// used for whole game (except adventure arena)
				MEMPACK_SwapPacks(0);

				// StringToLevID converts string to level ID
				// "proto8" -> 0 (dingo canyon)
				// "proto9" -> 1 (dragon mines)
				// "desert2" -> 2 (blizard bluff)
				// "island1" -> 3 (crash cove)
				// etc

				sdata.levelID = StringToLevID(&sdata->gGT->levelName[0]);

				// erase all memory past this bookmark
				MEMPACK_PopToState(sdata.bookmarkID);
			}

			// if you have not drawn the intro frames yet
			else
			{
				// Record that you've seen the logos,
				// so that you do not see them again
				sdata.boolShownIntros = 0;

				// Load Intro TIM for Sony Presents from VRAM file
				// Add a bookmark before loading (bigfile is 0 in the call)
				LOAD_VramFile(bigfile, 0x1fe, 0, auStack40, 0xffffffff);

				// refresh screen during Intro
				UpdateIntroScreen();

				// set isbg of both DBs to false
				sdata->gGT->db[0].drawEnv.isbg = 0;
				sdata->gGT->db[1].drawEnv.isbg = 0;
			}

			// Turn off HUD
			sdata->gGT->hudFlags &= 0xfe;

			// disable all rendering except loading screen
			sdata->gGT->renderFlags &= 0x1000;

			sdata->gGT->hudFlags &= 0xf7;

			numPlyrNextGame = sdata->gGT->numPlyrNextGame;

			// set pointer of current LEV to zero
			sdata->gGT->level1 = 0;

			// set pointer of 2nd LEV (used in adv hub) to zero
			sdata->gGT->level2 = 0;

			// set numPlyrCurrGame to numPlyrNextGame
			sdata->gGT->numPlyrCurrGame = numPlyrNextGame;

			// copy level name into global string
			// * 6? --Super
			strcpy(&sdata->gGT->levelName[0], sdata.metaDataLEV[sdata->gGT->levelID].name_Debug);

			// add a bookmark, the index of the bookmark is
			// saved into 0x8d098, which is used to erase later
			sdata.bookmarkID = MEMPACK_PushState();

			DrawSync(0);

			// no overlay transition
			sdata->gGT->overlayTransition = 0;

			levelNamePtr = &sdata->gGT->levelName[0];
			sdata->gGT->gameMode1 &= 0xdfcfdfff;
			sdata->gGT->gameMode2 &= 0xfffffe5f;

			// called VISMEM in prototypes
			sdata->gGT->visMem1 = 0;
			sdata->gGT->visMem2 = 0;

			iVar9 = strncmp(levelNamePtr, &sdata.s_ndi[0], 3);

			if
			(
				// If you're in Naughty Dog Box Scene
				(iVar9 == 0) ||
				(
					iVar9 = strncmp(&sdata->gGT->levelName[0], &sdata.s_ending[0], 6),
					iVar9 == 0
				)
			)
			{
				// Enable cutscene flag (disable controls)
				sdata->gGT->gameMode1 |= 0x20000000;

				sdata->gGT->hudFlags &= 0xfe;
			}
			else
			{
				iVar9 = strncmp(&sdata->gGT->levelName[0], &sdata.s_intro[0], 5);

				// if you are loading oxide intro cutscene (from main menu)
				if (iVar9 == 0)
				{
					// Turn off HUD
					sdata->gGT->hudFlags &= 0xfe;

					sdata->gGT->gameMode1 |= 0x20000000;

					// lev swap will be needed
					sdata->gGT->gameMode2 |= 0x20;
				}

				// if you are not loading oxide intro
				else
				{
					iVar9 = strncmp(&sdata->gGT->levelName[0], &sdata.s_screen[0], 6);

					if
					(
						// if you are loading any menu of any kind
						(iVar9 == 0) ||
						(
							iVar9 = strncmp(&sdata->gGT->levelName[0], &sdata.s_garage[0], 6),

							// if you are loading into adventure character selection screen
							iVar9 == 0
						)
					)
					{
						// Turn off HUD
						sdata->gGT->hudFlags &= 0xfe;

						// enable flag that shows you are in main menu
						sdata->gGT->gameMode1 |= 0x2000;

						sdata->gGT->numPlyrNextGame = sdata->gGT->numPlyrCurrGame;

						// Either 4P mode or main menu
						sdata->gGT->numPlyrCurrGame = 4;

						iVar9 = strncmp(&sdata->gGT->levelName[0], &sdata.s_garage[0], 6);

						// if you are loading into character selection screen
						if (iVar9 == 0)
						{
							// set numPlyrCurrGame to 1
							sdata->gGT->numPlyrCurrGame = 1;

							// Enter Adventure Character Selection
							sdata.mainMenuState = 4;
						}
					}

					// if you are not loading menu or adventure character selection
					else
					{
						iVar9 = strncmp(&sdata->gGT->levelName[0], &sdata.s_hub[0], 3);

						// if you are loading into adventure map:
						// any of the hubs: "hub1", "hub2", etc
						if (iVar9 == 0)
						{
							// Set numPlyrNextGame to 1
							sdata->gGT->numPlyrNextGame = 1;

							// set numPlyrCurrGame to 1
							sdata->gGT->numPlyrCurrGame = 1;

							// Change mode to Adventure Arena
							sdata->gGT->gameMode1 |= 0x100000;
							hudFlags = sdata->gGT->hudFlags;

							// lev swap will be needed
							sdata->gGT->gameMode2 |= 0x20;
						}

						// if you are not loading adventure hub
						else
						{

							// check to see if you are loading credits
							iVar9 = strncmp(&sdata->gGT->levelName[0], &sdata.s_credit[0], 6);

							if (iVar9 != 0)
							{
								// Turn off HUD
								sdata->gGT->hudFlags &= 0xfe;
								goto LAB_80033a70;
							}

							// set numPlyrNextGame to 1
							sdata->gGT->numPlyrNextGame = 1;

							// set numPlyrCurrGame to 1
							sdata->gGT->numPlyrCurrGame = 1;

							// enable cutscene flag
							sdata->gGT->gameMode1 |= 0x20000000;

							hudFlags = sdata->gGT->hudFlags;
					
							// lev swap (&20) and credits (&80)
							sdata->gGT->gameMode2 |= 0xa0;
						}
						sdata->gGT->hudFlags = hudFlags & 0xfe;
					}
				}
			}
LAB_80033a70:

			// Enable HUD Instances
			sdata->gGT->hudFlags |= 2;

			sdata->gGT->Debug_ToggleNormalSpawn = 1;

			// Set LOD level to 1P level
			sdata.levelLOD = 1;

			if
			(
				// If not in main menu (character selection, track selection, any part of it)
				((sdata->gGT->gameMode1 & 0x2000) == 0) &&
				(
					// set LOD level to 8P level (does this exist??)
					sdata.levelLOD = 8,

					// if not loading, and not in time trial
					(sdata->gGT->gameMode1 & 0x4020000) == 0
				)
			)
			{
				// Set LOD level to numPlyrCurrGame
				sdata.levelLOD = sdata->gGT->numPlyrCurrGame;
			}

			SetPrimMemSize(sdata->gGT);

			SetOTMemSize(sdata->gGT);

			// 2 is for cutscene
			// 1 is for If you're in Adventure Arena
			if
			(
				((sdata->gGT->gameMode1 & 0x20100000) != 0) ||

				// if going to credits
				((sdata->gGT->gameMode2 & 0x80) != 0)
			)
			{

				// (now, at beginning of mempack)
				AllocateAllPools( /*sdata->gGT*/ );

				return loadingStage + 1;
			}
			break;
		case 1:

			// if XA has not paused yet,
			// since the request above,
			// due to IRQ not being hit yet
			if (sdata.XA_State == 4)
			{
				// quit, try again next frame
				return loadingStage;
			}

			// If you're in Crystal Challenge (in adventure mode)
			if ((sdata->gGT->gameMode1 & 0x8000000) != 0)
			{
				// DLL 221 (221 + 0)
				uVar16 = 0;
DLL221_plus_uVar16:

				// Load 221 + uVar16
				LOAD_OvrEndRace(uVar16);
				return loadingStage + 1;
			}

			// If you're in Time Trial
			if ((sdata->gGT->gameMode1 & 0x20000) != 0)
			{
				// DLL 224 (221 + 3)
				uVar16 = 3;

				// Load 221 + uVar16
				goto DLL221_plus_uVar16;
			}

			// If you're in Arcade Mode
			if ((sdata->gGT->gameMode1 & 0x400000) != 0)
			{
				// DLL 222 (221 + 1)
				uVar16 = 1;

				// Load 221 + uVar16
				goto DLL221_plus_uVar16;
			}

			// If you're in a Relic Race
			if ((sdata->gGT->gameMode1 & 0x4000000) != 0)
			{
				// DLL 223 (221 + 2)
				uVar16 = 2;

				// Load 221 + uVar16
				goto DLL221_plus_uVar16;
			}

			// If you're in Adventure Mode
			if ((sdata->gGT->gameMode1 & 0x80000) != 0)
			{
				// DLL 222 (221 + 1)
				uVar16 = 1;

				// Load 221 + uVar16
				goto DLL221_plus_uVar16;
			}

			// DLL 225 (221 + 4)
			uVar16 = 4;

			// If you are not in Arcade or VS cup
			if ((sdata->gGT->gameMode2 & 0x10) == 0) goto DLL221_plus_uVar16;
			break;
		case 2:

			// 225 is for Naughty Dog Box

			// Load DLL 225 + numPlyrCurrGame
			// 226 - 229
			LOAD_OvrLOD(sdata->gGT->numPlyrCurrGame);
			break;
		case 3:

			// If in main menu (character selection, track selection, any part of it)
			if
			(
				((sdata->gGT->gameMode1 & 0x2000) != 0) &&
				(
					// DLL 230 (230 + 0)
					uVar16 = 0,

					// LevelID != 40, not on adventure character selection
					sdata->gGT->levelID != 0x28
				)
			)
			{
	LAB_80033ccc:
				// Load DLL 230 + uVar6
				LOAD_OvrThreads(uVar16);
				return loadingStage + 1;
			}

			// If you're in Adventure Arena
			if ((sdata->gGT->gameMode1 & 0x100000) != 0)
			{
				// By default, load Podium DLL

				// DLL 233 (230 + 3)
				uVar16 = 3;

				// podium reward
				if (sdata->gGT->podiumRewardID == 0)
				{
					// Load a different DLL

					// DLL 232 (230 + 2)
					uVar16 = 2;
				}

				// Load DLL 230 + uVar16
				goto LAB_80033ccc;
			}

			// podium reward
			if
			(
				(
					(
						(sdata->gGT->podiumRewardID != 0) ||

						// If you are in a cutscene
						((sdata->gGT->gameMode1 & 0x20000000) != 0)
					) ||

					// if going to credits
					((sdata->gGT->gameMode2 & 0x80) != 0)
				) ||

				// If LevelID is 40
				// If you're in Adventure Character Select Screen
				(sdata->gGT->levelID == 0x28)
			)
			{
				// DLL 233 (230 + 3)
				uVar16 = 3;

				// Load DLL 230 + uVar16
				goto LAB_80033ccc;
			}

			// DLL 231 (230 + 1)
			uVar16 = 1;
			if (sdata->gGT->overlayIndex_Threads != 1) goto LAB_80033ccc;
			break;
		case 4:

			// if level is not in range of 0x28 and 0x28+1,
			// if level is not AdvGarage or Naughty Dog Box Scene
			if (1 < sdata->gGT->levelID - 0x28U)
			{
				Music_Restart();
			}

			// If in main menu (character selection, track selection, any part of it)
			if ((sdata->gGT->gameMode1 & 0x2000) != 0)
			{
				// all these are 230 except for adv garage which is 233
				switch(sdata.mainMenuState)
				{
					// main menu
					case 0:
						MM_JumpTo_Title_FirstTime();
						break;

					case 1:
						MM_JumpTo_Characters();
						break;

					// track selection
					case 2:
						MM_JumpTo_TrackSelect();
						break;

					// battle selection
					case 3:
						MM_JumpTo_BattleSetup();
						break;

					// Character Selection 3D (Adventure)
					case 4:
						CS_Garage_Init();
						break;

					// scrapbook
					case 5:
					// why is bigfile passed as argument???
					MM_JumpTo_Scrapbook(bigfile);
				}
			}
			sdata.driverModel_lowLOD[0] = 0;
			sdata.driverModel_lowLOD[1] = 0;
			sdata.driverModel_lowLOD[2] = 0;
			sdata.ptrMPK = 0;

			// game is now loading
			sdata.load_inProgress = 1;

			// LOD level (num players, plus Time Trial flag)
			LOAD_DriverMPK(bigfile, sdata.levelLOD, &LOAD_Callback_DriverModels);
			break;
		case 5:

			// Clear all model pointers
			INSTANCE_ModelGlobal_Clear(sdata->gGT);

			// set value of PLYROBJECTLIST, the array of model pointers from MPK that was loaded in loading stage 4
			// I might be getting this wrong --Super
			sdata.PLYROBJECTLIST++;
			if (sdata.ptrMPK == 0)
			{
				sdata.PLYROBJECTLIST = 0;
			}

			LOAD_GlobalModelPtrs_MPK();

			DecalGlobal_Clear(sdata->gGT);

			if ((sdata.ptrMPK == 0) || (*sdata.ptrMPK == 0))
			{
				sdata->gGT->unkIconPtr = 0;
			}
			else 
			{
				DecalGlobal_Store(sdata->gGT);
				sdata->gGT->unkIconPtr = *sdata.ptrMPK;
			}

			// if level is not in range of 0x28 and 0x28+1,
			// if level is not AdvGarage or Naughty Dog Box Scene
			if (1 < sdata->gGT->levelID - 0x28U)
			{
				Music_Stop();

				CseqMusic_StopAll();

				Music_LoadBanks();

				return loadingStage + 1;
			}
			break;
		case 6:

			// if level is not in range of 0x28 and 0x28+1,
			// if level is not AdvGarage or Naughty Dog Box Scene
			if (1 < sdata->gGT->levelID - 0x28U)
			{
				iVar9 = Music_AsyncParseBanks();

				if (iVar9 == 0)
				{
					return loadingStage;
				}

				Cutscene_VolumeRestore();
			}

			// loop through models
			piVar15 = &sdata.driverModel_lowLOD[0];

			for (iVar9 = 0; iVar9 < 3; iVar9++)
			{
				// if pointer is valid
				if (*piVar15 != 0) 
				{
					// increment pointer by 4,
					// change pointer to file (starting at pointer map)
					// into a pointer to the model itself
					*piVar15 += 4;
				}

				piVar15++;
			};

			// If the world you're in is made of multiple LEV files
			if ((sdata->gGT->gameMode2 & 0x20) != 0)
			{
				// ivar9 is the size of one allocation pool
				// ivar12 is the size of another

				// Intro cutscene with oxide spaceship and all racers
				iVar9 = 0x6b000;

				// If you're in Adventure Arena
				if ((sdata->gGT->gameMode1 & 0x100000) != 0)
				{
					iVar9 = 0x68800;
				}

				// Intro cutscene with oxide spaceship and all racers
				iVar12 = 0x40000;

				// If you're in Adventure Arena
				if ((sdata->gGT->gameMode1 & 0x100000) != 0)
				{
					iVar12 = 0x68800;
				}

				// Size needed for HUB is var9 + var12
				// Pointer to hub is var5

				// Allocate Adventure Arena
				iVar5 = MEMPACK_AllocMem(iVar9 + iVar12, "HUB ALLOC");

				// Set ptrHubAlloc to pointer that hub will use
				sdata.ptrHubAlloc = iVar5;

				// Change active allocation system to #2
				MEMPACK_SwapPacks(1);

				// Build a new allocation system from
				// iVar5 address with a size of iVar9
				MEMPACK_NewPack_StartEnd(iVar5, iVar9);

				// Change active allocation system to #3
				MEMPACK_SwapPacks(2);

				// Build a new allocation system from
				// address (ivar5 + ivar9), which comes after
				// the previous allocation system, with
				// a size of iVar12 u_chars
				MEMPACK_NewPack_StartEnd(iVar5 + iVar9, iVar12);

				// Intro cutscene with oxide spaceship and all racers
				if ((sdata->gGT->gameMode1 & 0x100000) == 0)
				{
					// Always start with pool 1
					sVar4 = 1;
				}

				// If you're in Adventure Arena
				else
				{
					// Get 1 or 2, depending on map
					sVar4 = LOAD_GetAdvPackIndex();

					// Then swap:
					// Turn 1 into 2
					// Turn 2 into 1
					sVar4 = 3 - sVar4;
				}

				// set the memory pool system ID
				sdata->gGT->activeMempackIndex = sVar4;

				// globally store the Level ID for this mempack
				sdata->gGT->levID_in_each_mempack[sdata->gGT->activeMempackIndex] = sdata->gGT->levelID;

				// globally erase the Level ID in the other mempack
				sdata->gGT->levID_in_each_mempack[3 - sdata->gGT->activeMempackIndex] = 0xffff;

				// change active allocation system to #1
				// used for whole game (except adventure arena)
				MEMPACK_SwapPacks(0);

				// Get amount of free memory in CTR
				sdata.PatchMem_Size = MEMPACK_GetFreeBytes();

				sdata.PatchMem_Ptr = MEMPACK_AllocHighMem(sdata.PatchMem_Size, "Patch Table Memory");

				// change active allocation system
				// Swap 1 and 2 while on adventure map
				MEMPACK_SwapPacks(sdata->gGT->activeMempackIndex);
			}

			// game is now loading
			sdata.load_inProgress = 1;

			// get VRAM subfile index within BIGFILE,
			// of the track you want to load
			uVar16 =
			LOAD_GetBigfileIndex
			(

				// Level ID you want to load
				sdata->gGT->levelID,

				// LOD of level you want to load
				sdata.levelLOD, 0
			);

			// adds VRAM to loading queue
			// second parameter '3' means vram
			LOAD_AppendQueue(bigfile, 3, uVar16, 0, 0);

			// Level ID you want to load
			iVar9 = sdata->gGT->levelID;

			// if level ID some cutscene, with a super high value
			// 25-39, or 44-64
			if ((iVar9 - 0x19U < 0xe) || (iVar9 - 0x2cU < 0x14))
			{
				// get LEV subfile index within BIGFILE,
				// of the track you want to load
				uVar16 =
				LOAD_GetBigfileIndex
				(

					// Level ID you want to load
					iVar9,

					// LOD of level you want to load
					sdata.levelLOD, 1
				);

				// adds LEV to loading queue
				// '2' means dram
				LOAD_AppendQueue(bigfile, 2, uVar16, 0, &LOAD_Callback_LEV);

				// get .ptr subfile from BIGFILE
				// last param 0 for vram, 1 for lev, 2 for .ptr
				uVar6 =
				LOAD_GetBigfileIndex
				(

					// Level ID you want to load
					sdata->gGT->levelID,

					// LOD of level you want to load
					sdata.levelLOD, 2
				);

				// '1' means readfile
				uVar17 = 1;

				// callback for adv levs (not HubCallback)
				pcVar7 = LOAD_Callback_LEV_Adv;

				// HighMem patch table
				uVar16 = sdata.PatchMem_Ptr;
			}

			// if Level ID is not something insane load ordinary track
			// (arcade, battle, ND box)
			else
			{
				// get LEV subfile index within BIGFILE,
				// of the track you want to load
				uVar6 =
				LOAD_GetBigfileIndex
				(

					// Level ID you want to load
					iVar9,

					// LOD of level you want to load
					sdata.levelLOD, 1
				);

				// 2 for dram
				uVar17 = 2;

				uVar16 = 0;

				// callback for normal levs
				pcVar7 = (CdlCB *)&LOAD_Callback_LEV;
			}

			// add LEV to loading queue
			LOAD_AppendQueue(bigfile, uVar17, uVar6, uVar16, pcVar7);
			break;
		case 7:

			// Set LEV pointer
			sdata->gGT->level1 = sdata.ptrLEV_DuringLoading;

			// iVar9 is set to sdata.ptrLEV_DuringLoading at the top of the function
			sdata->gGT->visMem1 = iVar9->visMem;

			// if LEV is valid
			if (sdata->gGT->level1 != 0)
			{
				// Load Icons and IconGroups from LEV
				DecalGlobal_Store(sdata->gGT, sdata->gGT->level1->ptr_named_tex);
			}

			DebugFont_Init(sdata->gGT);

			// get level pointer
			iVar9 = sdata->gGT->level1;

			// if level is not nullptr
			if (iVar9 != 0)
			{
				// store array of model pointers in GameTracker
				INSTANCE_ModelGlobal_Store(sdata->gGT, iVar9->numModels, iVar9->ptrModelsPtrArray);

				// search for icon by string
				uVar16 = DecalGlobal_Find1(sdata->gGT->level1, "circle");
				puVar8 = sdata->gGT->level1;
				sdata->gGT->stars.unk[2] = uVar16;

				// search for icon by string
				uVar16 = DecalGlobal_Find1(*puVar8, "clod"); // &sdata.s_clod "clod"
				puVar8 = sdata->gGT->level1;
				sdata->gGT->ptrClod = uVar16;

				// search for icon by string
				uVar16 = DecalGlobal_Find1(*puVar8, "dustpuff");
				puVar8 = sdata->gGT->level1;
				sdata->gGT->ptrDustpuff = uVar16;

				// search for icon by string "Smoke Ring"
				uVar16 = DecalGlobal_Find1(*puVar8, "smokering");
				puVar8 = sdata->gGT->level1;
				sdata->gGT->ptrSmoking = uVar16;

				// search for icon by string
				uVar16 = DecalGlobal_Find1(*puVar8, "sparkle");
				sdata->gGT->ptrSparkle = uVar16;
			}

			// if linked list of icons exists
			if (sdata->gGT->unkIconPtr != 0)
			{
				// search for icon by string
				uVar16 = DecalGlobal_Find2(*(u_int *)(sdata->gGT->unkIconPtr + 4), "lightredoff");
				piVar15 = sdata->gGT->unkIconPtr;
				sdata->gGT->trafficLightIcon[0] = uVar16;

				// search for icon by string
				uVar16 = DecalGlobal_Find2(*(u_int *)(*piVar15 + 4), "lightredon");
				piVar15 = sdata->gGT->unkIconPtr;
				sdata->gGT->trafficLightIcon[1] = uVar16;

				// search for icon by string
				uVar16 = DecalGlobal_Find2(*(u_int *)(*piVar15 + 4), "lightgreenoff");
				piVar15 = sdata->gGT->unkIconPtr;
				sdata->gGT->trafficLightIcon[2] = uVar16;

				// search for icon by string
				uVar16 = DecalGlobal_Find2(*(u_int *)(*piVar15 + 4), "lightgreenon");
				sdata->gGT->trafficLightIcon[3] = uVar16;
			}
			sdata->gGT->gameMode1_prevFrame = 1;

			if
			(
				// 2 is for cutscene
				// 1 is for If you're in Adventure Arena
				((sdata->gGT->gameMode1 & 0x20100000) == 0) &&

				// if not going to credits
				((sdata->gGT->gameMode2 & 0x80) == 0)
			)
			{
				// (now, at end of mempack)
				AllocateAllPools( /*sdata->gGT*/ );

				return loadingStage + 1;
			}
			iVar9 = 7;

			// podium reward
			if (sdata->gGT->podiumRewardID != 0)
			{
				// clear all podium model pointers
				puVar8 = &sdata.podiumModel_podiumStands;
				do
				{
					*puVar8 = 0;
					iVar9 = iVar9--;
					puVar8 = puVar8--;
				} while (iVar9 > -1);
			
				// Get Memory Allocation System Index
				iVar9 = LOAD_GetAdvPackIndex();

				// change active allocation system
				// Swap 1 and 2 while on adventure map
				MEMPACK_SwapPacks(3 - sdata->gGT->activeMempackIndex);

				// game is now loading
				sdata.load_inProgress = 1;

				// add something to loading queue
				// '3' for vram
				LOAD_AppendQueue(bigfile, 3, iVar9 + 0x16b, 0, 0);

				// podium first place
				hudFlags = sdata->gGT->podium_modelIndex_First;

				if
				(
					// if this exists
					(hudFlags != 0) && 
				
					// if not 0x7e + 0xF
					// if not oxide
					(hudFlags != 0x8d)
			 	)
				{
					// add something to loading queue
					// '2' for dram
					LOAD_AppendQueue(bigfile, 2, iVar9 + ((u_int)hudFlags - 0x7e) * 2 + 0x16d, &sdata.podiumModel_firstPlace, 0xfffffffe);
				}

				// podium second place exists
				if (sdata->gGT->podium_modelIndex_Second != 0)
				{
					// adds to loading queue
					// '2' for dram
					LOAD_AppendQueue(bigfile, 2, iVar9 + ((u_int)(u_char)sdata->gGT->podium_modelIndex_Second - 0x7e) * 2 + 0x18d, &sdata.podiumModel_secondPlace, 0xfffffffe);
				}
			
				// podium third place exists
				if (sdata->gGT->podium_modelIndex_Third != 0)
				{
					// add something to loading queue
					// '2' for dram
					LOAD_AppendQueue(bigfile, 2, iVar9 + ((u_int)(u_char)sdata->gGT->podium_modelIndex_Third - 0x7e) * 2 + 0x18d, &sdata.podiumModel_thirdPlace, 0xfffffffe);
				}

				// add TAWNA to loading queue
				// '2' for dram
				LOAD_AppendQueue(bigfile, 2, iVar9 + ((u_int)(u_char)sdata->gGT->podium_modelIndex_tawna - 0x8f) * 2 + 0x1ad, &sdata.podiumModel_tawna, 0xfffffffe);

				// -0x7d = 0x83
				// 0x83 - 0x7e = 5 (dingo)
				if (sdata->gGT->podium_modelIndex_First == -0x7d)
				{
					// add "DingoFire" to loading queue
					// '2' for dram
					LOAD_AppendQueue(bigfile, 2, iVar9 + 0x1bd, &sdata.podiumModel_dingoFire, 0xfffffffe);
				}

				// add Podium
				// '2' for dram
				LOAD_AppendQueue(bigfile, 2, iVar9 + 0x1bf, 0, &LOAD_Callback_Podiums);

				// Disable LEV instances on Adv Hub, for podium scene
				sdata->gGT->gameMode2 = sdata->gGT->gameMode2 | 0x100;
			}
			break;
		case 8:

			// If you're in Adventure Arena
			if
			(
				((sdata->gGT->gameMode1 & 0x100000) != 0) &&
				(
					// loop counter
					iVar9 = 0,

					// podium reward
					sdata->gGT->podiumRewardID != 0
				)
			)
			{
				piVar15 = &sdata.podiumModel_firstPlace;

				// for iVar9 = 0; iVar9 < 8; iVar9++
				do
				{
					iVar12 = *piVar15;
					if (iVar12 != 0)
					{
						if (iVar9 < 7)
						{
							*piVar15 = iVar12 + 4;
							iVar12 = *piVar15;
						}
						if ((int)*(short *)(iVar12 + 0x10) != -1)
						{
							*(int *)(moredata + (int)*(short *)(iVar12 + 0x10) * 4 + 0x2160) = iVar12;
						}
					}

					// increment loop counter
					iVar9 = iVar9 + 1;

					piVar15 = piVar15 + 1;
				} while (iVar9 < 8);

				// change active allocation system
				// Swap 1 and 2 while on adventure map
				MEMPACK_SwapPacks((int)sdata->gGT->activeMempackIndex);
			}

			// Level ID
			iVar9 = sdata->gGT->levelID;

			// Main Menu
			if (iVar9 == 0x27)
			{
				uVar16 = 7;
LAB_800346b0:

			Audio_SetState_Safe(uVar16);

				return loadingStage + 1;
			}

			// One of the maps on Adventure Arena
			if (iVar9 - 0x19U < 5)
			{
				uVar16 = 6;

				// podium reward
				if (sdata->gGT->podiumRewardID == 0)
				{
					uVar16 = 5;
				}
				goto LAB_800346b0;
			}

			// oxide intro
			if (iVar9 == 0x1e)
			{
				uVar16 = 3;
				goto LAB_800346b0;
			}

			// credits
			if (iVar9 == 0x2c)
			{
				uVar16 = 2;
				goto LAB_800346b0;
			}

			// Naughty Dog Box
			if (iVar9 == 0x29)
			{
				uVar16 = 4;
				goto LAB_800346b0;
			}

			// stop/pause cseq music
			uVar16 = 1;

			if (iVar9 - 0x2aU < 2) goto LAB_800346b0;
			break;
		case 9:
			if (sdata.XA_State != 2)
			{

				if
				(

					// If not in main menu (not in 2D character selection, track selection, or any part of it)
					((sdata->gGT->gameMode1 & 0x2000) == 0) ||

					// If level ID == 40
					// If you are in Adventure Character Selection
					(sdata->gGT->levelID == 0x28)
				)
				{
					// if not going to credits
					if ((sdata->gGT->gameMode2 & 0x80) == 0)
					{
						// enable all flags except loading screen
						gameMode1 = sdata->gGT->renderFlags | 0xffffefff;
					}

					// if going to credits
					else
					{
						// disable everything (except loading screen if still there)
						// enable drawing render bucket
						gameMode1 = sdata->gGT->renderFlags & 0x1000 | 0x20;
					}

					// apply desired value
					sdata->gGT->renderFlags = gameMode1;
				}
				else
				{
					// disable everything (except loading screen if still there)
					// enable pause menu? Or enable 3D cars on track?
					sdata->gGT->renderFlags = sdata->gGT->renderFlags & 0x1000 | 0x20;

					iVar9 = CheckeredFlag_IsFullyOffScreen();
					if (iVar9 == 1)
					{
						// checkered flag, begin transition on-screen
						CheckeredFlag_BeginTransition(1);
					}
				}
				sdata->gGT->hudFlags = sdata->gGT->hudFlags | 8;
				sdata->gGT->framesInThisLEV = 0;
				sdata->gGT->BoxSceneTimer = 0;

				// deactivate pause
				ElimBG_Deactivate();

				loadingStage = -2;
			}
		default:
			goto switchD_80033660_caseD_a;
	}
	loadingStage++;
	switchD_80033660_caseD_a:
	return loadingStage;
}