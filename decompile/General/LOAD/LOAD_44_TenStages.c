#include <common.h>

void (*mainMenuInit[6])() =
{
	DECOMP_MM_JumpTo_Title_FirstTime,
	DECOMP_MM_JumpTo_Characters,
	DECOMP_MM_JumpTo_TrackSelect,
	DECOMP_MM_JumpTo_BattleSetup,
	DECOMP_CS_Garage_Init,
	DECOMP_MM_JumpTo_Scrapbook
};

//2nd parameter can be negative, the switch just covers from 0 to 9
int DECOMP_LOAD_TenStages(struct GameTracker* gGT, int loadingStage, struct BigHeader* bigfile)
{
	void* ptrHubFile;
	int levSwapSize1;
	int levSwapSize2;
	int boolRestart;
	short advPackIndex;
	struct Icon* firstMpkIcon;
	short bigFileIndex;
	unsigned char audioState;
	unsigned short levelID;
	unsigned char index_OvrEndRace;
	unsigned char index_OvrThread;

	// if game is loading
	if (sdata->load_inProgress != 0)
	{
		return loadingStage;
	}
	
	levelID = gGT->levelID;
	
	// Used in stage 0, 4, 5, 6
	int boolPlayMusicDuringLoading = 
		(levelID == ADVENTURE_GARAGE) || 
		(levelID == NAUGHTY_DOG_CRATE);
	
	switch(loadingStage)
	{
		case LOADING_INIT:
		{	
#ifndef REBUILD_PS1
			if (!boolPlayMusicDuringLoading)
			{
				Cutscene_VolumeBackup();
			}
#endif
			DECOMP_CDSYS_XAPauseRequest();

			// if first boot (SCEA + Copyright + ND Box)
			if (sdata->boolFirstBoot != 0)
			{
				sdata->boolFirstBoot = 0;

				// Load Intro TIM for Copyright Page from VRAM file
				DECOMP_LOAD_VramFile(bigfile, 0x1fe);
				DECOMP_MainInit_VRAMDisplay();
				
				gGT->db[0].drawEnv.isbg = 0;
				gGT->db[1].drawEnv.isbg = 0;
			}
			
			// if not first boot (dont do this for ND Box)
			else
			{
				// change active allocation system to #1
				// used for whole game (except adventure arena)
				DECOMP_MEMPACK_SwapPacks(0);

				// erase all memory loaded after first boot
				DECOMP_MEMPACK_PopToState(sdata->bookmarkID);
			}

			// pop back here for every load, after first load,
			// this permanently reserves LNG, bigfile header, etc
			sdata->bookmarkID = DECOMP_MEMPACK_PushState();

			// Reset HUD
			gGT->hudFlags &= ~(1 | 8);
			gGT->hudFlags |= 2;

			// disable all rendering except loading screen
			// no overlay transition (advhub),  use normal spawn
			gGT->renderFlags &= 0x1000;
			gGT->overlayTransition = 0;
			gGT->Debug_ToggleNormalSpawn = 1;
				
			// Required for Scrapbook "Press Start",
			// may also be required for other edge-cases
			DrawSync(0);
			
			// ========== Start of flags ===============
			

			// disable certain game mode flags
			gGT->gameMode1 &= ~(GAME_CUTSCENE | END_OF_RACE | ADVENTURE_ARENA | MAIN_MENU);
			gGT->gameMode2 &= ~(LEV_SWAP | CREDITS | NO_LEV_INSTANCE);
			
			// just scrapbook
			if(levelID >= SCRAPBOOK)
			{
				gGT->gameMode1 |= MAIN_MENU;
			}
			
			// all credits
			else if(levelID >= CREDITS_CRASH)
			{
				gGT->gameMode1 |= GAME_CUTSCENE;
				gGT->gameMode2 |= (LEV_SWAP | CREDITS);
			}
				
			// Naughty Dog Box Scene,
			// Oxide Any% ending
			// Oxide 101% ending
			else if(levelID >= NAUGHTY_DOG_CRATE)
			{
				gGT->gameMode1 |= GAME_CUTSCENE;
			}

			// main menu or garage
			else if(levelID >= MAIN_MENU_LEVEL)
			{
				gGT->gameMode1 |= MAIN_MENU;
			}

			// intro cutscenes
			else if(levelID >= INTRO_RACE_TODAY)
			{
				gGT->gameMode1 |= GAME_CUTSCENE;
				gGT->gameMode2 |= LEV_SWAP;
			}

			// if you are loading into adventure map:
			// any of the hubs: "hub1", "hub2", etc
			else if(levelID >= GEM_STONE_VALLEY)
			{
				gGT->gameMode1 |= ADVENTURE_ARENA;
				gGT->gameMode2 |= LEV_SWAP;
			}


			// ========== End of flags ===============
			// ========== Set numPlyr ================


			if (levelID <= LAB_BASEMENT)
			{
				// get CurrGame from main menu's NextGame
				gGT->numPlyrCurrGame = gGT->numPlyrNextGame;
			}
			
			#ifdef USE_HIGHMP
			else if (levelID <= GEM_STONE_VALLEY)
			{
				if(gGT->podiumRewardID == 0) //0
				{
					// get CurrGame from main menu's NextGame
					gGT->numPlyrCurrGame = gGT->numPlyrNextGame;
				}
			}
			#endif
			
			else if (levelID == MAIN_MENU_LEVEL)
			{
				// get NextGame from the game you exited
				gGT->numPlyrNextGame = gGT->numPlyrCurrGame;
				gGT->numPlyrCurrGame = 4;
			}
		
			else
			{
				gGT->numPlyrCurrGame = 1;
				gGT->numPlyrNextGame = 1;
			}
			
			
			// ========== End of setting numPlyr ================
			// ========== Set LevelLOD variables ================


			// default
			sdata->levelLOD = gGT->numPlyrCurrGame;
			
			// main menu or adv garage
			if((gGT->gameMode1 & MAIN_MENU) != 0)
			{
				sdata->levelLOD = LOD_HI;
			}
			
			// if relic, or time trial
			if((gGT->gameMode1 & (TIME_TRIAL | RELIC_RACE)) != 0)
			{
				sdata->levelLOD = LOD_RELIC_TT;
			}
			
			
			// ========== End of LevelLOD ================
			// ========== Alloc Prim + OT ================
			
			
			#ifndef USE_MOREPRIM
				// OG game
				DECOMP_MainInit_PrimMem(gGT);
				DECOMP_MainInit_OTMem(gGT);
			#else
				// Reversed order, for RAM optimizations
				DECOMP_MainInit_OTMem(gGT);
				DECOMP_MainInit_PrimMem(gGT, 0xA000);
			#endif
			
			// RAM optimization, never call DECOMP_MainInit_JitPoolsNew
			// in Stage 0, just no point, and also ptrMap in DRAM files
			// will have more room to load if the allocation is delayed
			
			break;
		}
		case LOADING_OVR_ENDRACE:
		{
			// if XA has not paused since CDSYS_XAPauseRequest in stage #0,
			// then quit the function and try again next frame
			if (sdata->XA_State == 4) return loadingStage;

			// dont load end-of-race in these modes:
			//	credits, lev swap, cutscene, main menu
			if ((gGT->gameMode2 & (LEV_SWAP | CREDITS)) != 0) break;
			if ((gGT->gameMode1 & (GAME_CUTSCENE | MAIN_MENU)) != 0) break;

			// === pick overlay to load ===
			
			// 221 - Crystal Challenge
			if ((gGT->gameMode1 & CRYSTAL_CHALLENGE) != 0) 	
				index_OvrEndRace = 0;

			// 223 - Relic Race
			else if ((gGT->gameMode1 & RELIC_RACE) != 0) 
				index_OvrEndRace = 2;
			
			// 224 - Time Trial
			else if ((gGT->gameMode1 & TIME_TRIAL) != 0)
				index_OvrEndRace = 3;
			
			// 222 - Arcade/Trophy/Boss/C-T-R token
			// if arcade, or adv that isn't listed above
			else if ((gGT->gameMode1 & (ARCADE_MODE | ADVENTURE_MODE)) != 0)
				index_OvrEndRace = 1;
			
			// default VS/Battle overlay if no mode found
			else //if (gGT->gameMode1 & VS_MODE)
				index_OvrEndRace = 4;
			
			#ifdef USE_HIGHMP
			index_OvrEndRace = 4;
			#endif
		
			DECOMP_LOAD_OvrEndRace((int)index_OvrEndRace);
			break;
		}
		case LOADING_OVR_QUADBLOCKLOD:
		{	
			// force no-load on main menu
			if (levelID == MAIN_MENU_LEVEL) 
				break;
			
			// force reload, so that 230 functions are not 
			// overwritten by 233 on first-frame loading,
			// which starts on X-Press, does not wait AT ALL
			if (levelID == ADVENTURE_GARAGE)
				gGT->overlayIndex_LOD = 0xFF;
			
			#ifdef USE_HIGHMP
			DECOMP_LOAD_OvrLOD(1);
			#else
			DECOMP_LOAD_OvrLOD(gGT->numPlyrCurrGame);
			#endif
			break;
		}	
		case LOADING_OVR_THREAD:
		{
			#ifdef USE_ONLINE
			// Load Region3 for planet
			if(gGT->levelID == INTRO_OXIDE)
				index_OvrThread = 3;
			else
			#endif
			
			// main menu + scrapbook, 230
			if (
					(levelID != ADVENTURE_GARAGE) &&
					((gGT->gameMode1 & MAIN_MENU) != 0)
				)
			{
				index_OvrThread = 0;
			}
			
			// race threads, 231
			else if (levelID <= LAB_BASEMENT)
			{
				index_OvrThread = 1;
			}
			
			// advHub, 232
			else if (
						(levelID <= CITADEL_CITY) &&
						(gGT->podiumRewardID == 0)
				)
			{
				index_OvrThread = 2;
			}
			
			// Cutscene, Credits, ND, Garage, Podium
			else
			{
				index_OvrThread = 3;
			}
			
			DECOMP_LOAD_OvrThreads((int)index_OvrThread);
			break;
		}
		case LOADING_MPK:
		{
			if (!boolPlayMusicDuringLoading)
			{
				DECOMP_Music_Restart();
			}

			// If in main menu (character selection, track selection, any part of it)
			if ((gGT->gameMode1 & MAIN_MENU) != 0)
			{
				#ifdef REBUILD_PC
				// reset value, emulate overlay reloading
				D230.menuMainMenu.state = 0x403;
				#endif
				
				#ifdef USE_OXIDE
				// if scrapbook unlocked, then unlock Oxide,
				// flag 0x1000 must match the 1<<0 in the icon array,
				// this bit was used in Aug5 to unlock SlideCol, unused
				if ((sdata->gameProgress.unlocks[1] & UNLOCK_SCRAPBOOK) != 0)
					sdata->gameProgress.unlocks[0] |= 1;
				#endif
				
				if(levelID == ADVENTURE_GARAGE)
					sdata->mainMenuState = 4;
				
				mainMenuInit[sdata->mainMenuState]();
			}
			
			#ifdef USE_PRELOAD
			// TODO: Duplicate DriverMPK just for setting DriverIDs
			DECOMP_LOAD_Robots1P(data.characterIDs[0]);
			
			// only once on-boot
			if(sdata->ptrMPK != NULL)
				break;

			int* arr = 0x8000a000;
			
			int i;
			for(i = 0; i < 16; i++)
			{
				// high lod CTR model
				DECOMP_LOAD_AppendQueue(0, LT_GETADDR,
					BI_RACERMODELHI + i,
					&arr[i], cbDRAM);
			}
		
			// Time Trial MPK
			DECOMP_LOAD_AppendQueue(0, LT_GETADDR,
				BI_TIMETRIALPACK + NITROS_OXIDE,
				&sdata->ptrMPK, cbDRAM);
			break;
			#endif
			
			// Needed, or else Post-Boss Outro
			// will break the character animations
			sdata->ptrMPK = NULL;
			
			// Clear driver extras, and podium models
			int* ptrArray = &data.driverModelExtras[0];
			for(int i = 0; i < 11; i++)
			{
				ptrArray[i] = 0;
			}

			DECOMP_LOAD_DriverMPK(bigfile, sdata->levelLOD);
			break;
		}
		case LOADING_STORE_MPK_DATA:
		{
			#ifdef USE_PRELOAD
			// first-boot
			if(sdata->PLYROBJECTLIST == NULL)
			{
				// Never de-allocate lower than here
				sdata->bookmarkID = DECOMP_MEMPACK_PushState();
			}
			#endif
			

			sdata->PLYROBJECTLIST = sdata->ptrMPK->modelPtrArray;
			
			
			if (sdata->ptrMPK == NULL) sdata->PLYROBJECTLIST = NULL;
						
			// clear and reset
			DECOMP_LibraryOfModels_Clear(gGT);
			DECOMP_LOAD_GlobalModelPtrs_MPK();
			DECOMP_DecalGlobal_Clear(gGT);

			gGT->mpkIcons = NULL;
			if (sdata->ptrMPK != NULL)
			{
				gGT->mpkIcons = sdata->ptrMPK->iconHeader;
				
				if(gGT->mpkIcons != NULL)
					DECOMP_DecalGlobal_Store(gGT, gGT->mpkIcons);
			}
			
			if (!boolPlayMusicDuringLoading)
			{
				DECOMP_Music_Stop();
				DECOMP_CseqMusic_StopAll();
				DECOMP_Music_LoadBanks();
			}
			
			break;
		}
		case LOADING_LEVFILE:
		{
			if (!boolPlayMusicDuringLoading)
			{
				boolRestart = DECOMP_Music_AsyncParseBanks();

				if (boolRestart == 0)
				{
					// quit and restart stage 6 next frame
					return loadingStage;
				}

#ifndef REBUILD_PS1
				Cutscene_VolumeRestore();
#endif
			}
			
			// == banks are done parsing ===

			// If this world is made of multiple LEVs
			if ((gGT->gameMode2 & LEV_SWAP) != 0)
			{
				// Cutscene Packs
				levSwapSize1 = 0x6b000;
				levSwapSize2 = 0x40000;

				// If you're in Adventure Arena
				if ((gGT->gameMode1 & ADVENTURE_ARENA) != 0)
				{
					// Adv Arena Packs
					levSwapSize1 = 0x68800;
					levSwapSize2 = 0x68800;
				}

#ifdef REBUILD_PC
				levSwapSize1 = 0x68800<<1;
				levSwapSize2 = 0x68800<<1;
#endif

				// Allocate room for LEV swapping
				ptrHubFile = DECOMP_MEMPACK_AllocMem(levSwapSize1 + levSwapSize2); // "HUB ALLOC"
				sdata->ptrHubAlloc = ptrHubFile;

				// Change active allocation system to #2
				// pack = [hubAlloc, hubAlloc+size1]
				DECOMP_MEMPACK_SwapPacks(1);
				DECOMP_MEMPACK_NewPack(ptrHubFile, levSwapSize1);

				// Change active allocation system to #3
				// pack = [hubAlloc+size1, hubAlloc+size1+size2]
				DECOMP_MEMPACK_SwapPacks(2);
				DECOMP_MEMPACK_NewPack((void*)((unsigned int)ptrHubFile + levSwapSize1), levSwapSize2);

				// Intro cutscene with oxide spaceship and all racers
				if ((gGT->gameMode1 & ADVENTURE_ARENA) == 0)
				{
					// Always start with pool 1
					advPackIndex = 1;
				}

				// If you're in Adventure Arena
				else
				{
					// Get 1 or 2, depending on map
					advPackIndex = DECOMP_LOAD_GetAdvPackIndex();

					// Then swap:
					// Turn 1 into 2
					// Turn 2 into 1
					advPackIndex ^= 3;
				}

				// keep track of subpack levels
				gGT->activeMempackIndex = advPackIndex;
				gGT->levID_in_each_mempack[advPackIndex] = gGT->levelID;
				gGT->levID_in_each_mempack[advPackIndex ^ 3] = 0xffff;

				// the rest of memory will load pointer maps,
				// loaded at HighMem in main pack, end of RAM,
				// so the pointer maps dont bloat subpacks
				DECOMP_MEMPACK_SwapPacks(0);
				
				#if 1
				// biggest lev_swap (cutscene/adventure)
				// is 0xBBA0 for gemstone ptr map, align up
				// by 0x800 for 0xc000, and use AllocMem,
				// HighMem is now reserved for PrimMem
				sdata->PatchMem_Size = 0xc000;
				sdata->PatchMem_Ptr = (int)DECOMP_MEMPACK_AllocMem(sdata->PatchMem_Size); //, "Patch Table Memory");
				#else
				// original game code
				sdata->PatchMem_Size = DECOMP_MEMPACK_GetFreeBytes();
				sdata->PatchMem_Ptr = DECOMP_MEMPACK_AllocHighMem(sdata->PatchMem_Size); //, "Patch Table Memory");
				#endif
				
				// For Oxide-Intro and Credits, set active pack
				DECOMP_MEMPACK_SwapPacks(gGT->activeMempackIndex);
			}

			#ifdef USE_LEVELDEV
			if(gGT->levelID == CUSTOM_LEVEL_ID)
			{
				HotReloadVRAM();
				
				// do NOT load bigfile level file,
				// instead load the hot-reload level
				break;
			}
			#endif

			// base index of the group
			bigFileIndex = DECOMP_LOAD_GetBigfileIndex(gGT->levelID, sdata->levelLOD);

			// add VRAM to loading queue
			DECOMP_LOAD_AppendQueue(
				0, LT_SETVRAM, bigFileIndex + LVI_VRAM, 
				NULL, DECOMP_LOAD_VramFileCallback);

			// add LEV to loading queue
			DECOMP_LOAD_AppendQueue( 
				0, LT_GETADDR, bigFileIndex + LVI_LEV, 
				&sdata->ptrLevelFile, DECOMP_LOAD_DramFileCallback);

			// if world is made of multiple LEVs
			if ((gGT->gameMode2 & LEV_SWAP) != 0)
			{
				// add PTR file to loading queue
				DECOMP_LOAD_AppendQueue(
					0, LT_SETADDR, bigFileIndex + LVI_PTR, 
					(void*)sdata->PatchMem_Ptr, DECOMP_LOAD_Callback_PatchMem);
			}			
			break;
		}
		case LOADING_STORE_LEV_DATA:
		{
			// get level pointer
			struct Level* lev = sdata->ptrLevelFile;
			
			#ifdef USE_LEVELDEV
			if (gGT->levelID == CUSTOM_LEVEL_ID) 
				lev = (struct Level*)CUSTOM_LEV_ADDR;
			#endif

			gGT->level1 = lev;
			gGT->visMem1 = lev->visMem;

			if (lev != NULL)
			{
				DECOMP_DecalGlobal_Store(gGT, lev->iconHeader);
			}

			DECOMP_DebugFont_Init(gGT);

			// if level is not nullptr
			if (lev != NULL)
			{
				DECOMP_LibraryOfModels_Store(gGT, lev->numModels, lev->ptrModelsPtrArray);

#ifndef REBUILD_PS1
				// == must use RDATA strings ==
				// they have bigger sizes that the 
				// search algorithm depends on

				gGT->ptrCircle = (u_int)DecalGlobal_FindInLEV(lev, rdata.s_circle);
				gGT->ptrClod = (u_int)DecalGlobal_FindInLEV(lev, rdata.s_clod);
				gGT->ptrDustpuff = (u_int)DecalGlobal_FindInLEV(lev, rdata.s_dustpuff);
				gGT->ptrSmoking = (u_int)DecalGlobal_FindInLEV(lev, rdata.s_smokering); // "Smoke Ring"
				gGT->ptrSparkle = (u_int)DecalGlobal_FindInLEV(lev, rdata.s_sparkle);
#endif
			}

			// if linked list of icons exists
			if (gGT->mpkIcons != NULL)
			{
				firstMpkIcon = gGT->mpkIcons->firstIcon;
				
				// Removed usage of DecalGlobal_FindInMPK
				// OG game would search every string one-by-one

				for(
						struct Icon* firstIcon = firstMpkIcon; 
						*(int*)&firstIcon->name[0];
						firstIcon++
					)
				{
					if(
						// "lightred"
						(*(int*)&firstIcon->name[0] == 0x6867696c) &&
						(*(int*)&firstIcon->name[4] == 0x64657274)
					)
					{
						// lets hope the order is the same in every MPK
						gGT->trafficLightIcon[0] = &firstIcon[1];
						gGT->trafficLightIcon[1] = &firstIcon[0];
						gGT->trafficLightIcon[2] = &firstIcon[3];
						gGT->trafficLightIcon[3] = &firstIcon[2];
						break;
					}
				}
			}
			
			gGT->gameMode1_prevFrame = 1;

			// RAM optimization, always do this here,
			// because now ptrMap already loaded and realloc'd
			DECOMP_MEMPACK_SwapPacks(0);
			DECOMP_MainInit_JitPoolsNew(gGT);
			
			#ifdef USE_MOREPRIM
			// Stage 7: Fill remaining heap
			DECOMP_MainInit_PrimMem(gGT, 0);
			#endif

			if ((gGT->gameMode2 & LEV_SWAP) == 0)
				break;
			
			// === Assume LEV_SWAP Active ===
			
			if ((gGT->gameMode1 & ADVENTURE_ARENA) == 0)
				break;
			
			// === Assume AdventureArena Active ===
			
			// podium reward
			if (gGT->podiumRewardID == 0)
				break;
			
			// === Assume PodiumReward Active ===
			
			// Set Pack of the hub you're NOT on
			DECOMP_MEMPACK_SwapPacks(3 - gGT->activeMempackIndex);
			
			// Load model+vrm files on the VRAM page
			// that does NOT overwrite the hub VRAM
			advPackIndex = DECOMP_LOAD_GetAdvPackIndex() - 1;

			// VRAM for podium and all related models
			DECOMP_LOAD_AppendQueue(
				0, LT_SETVRAM, BI_PODIUMVRMS + advPackIndex, 
				NULL, DECOMP_LOAD_VramFileCallback);

			// podium first place
			u_char* ptrIndexArr = &gGT->podium_modelIndex_First;
			int* ptrModelPtrArr = &data.podiumModel_firstPlace;
			int baseIndexPM = BI_DANCEMODELWIN;

			// Fix for Oxide (faster than OG code that does nothing)
			// If Oxide WIN is requested, add 16 to load Oxide LOSE
			if (ptrIndexArr[0] == 0x8d)
				baseIndexPM = BI_DANCEMODELLOSE;
			
			int fileIndex;
			int drmCb = DECOMP_LOAD_DramFileCallback;

			// Loop through 3 podium models
			for(int i = 0; i < 3; i++)
			{
				if(ptrIndexArr[i] != 0)
				{
					fileIndex = baseIndexPM + advPackIndex + 
						(ptrIndexArr[i] - 0x7e) * 2;
					
					DECOMP_LOAD_AppendQueue(
						0, LT_GETADDR, fileIndex, 
						&ptrModelPtrArr[i], drmCb);
				}
				
				baseIndexPM = BI_DANCEMODELLOSE;
			}
			
			// TAWNA
			fileIndex = BI_DANCETAWNAGIRL + advPackIndex + 
				(gGT->podium_modelIndex_tawna - STATIC_TAWNA1) * 2;

			// add TAWNA to loading queue
			DECOMP_LOAD_AppendQueue(
				0, LT_GETADDR, fileIndex, 
				(void*)&data.podiumModel_tawna, drmCb);

			// if 0x7e+5 (dingo)
			if (gGT->podium_modelIndex_First == STATIC_DINGODANCE)
			{
				// add "DingoFire" to loading queue
				DECOMP_LOAD_AppendQueue(
					0, LT_GETADDR, BI_DINGOFIRE + advPackIndex, 
					(void*)&data.podiumModel_dingoFire, drmCb);
			}

			// add Podium
			DECOMP_LOAD_AppendQueue(0, LT_GETADDR, BI_PODIUM + advPackIndex, 
				&data.podiumModel_podiumStands, drmCb);

			// Disable LEV instances on Adv Hub, for podium scene
			gGT->gameMode2 |= NO_LEV_INSTANCE;
			break;
		}
		case LOADING_SET_AUDIO_STATE:
		{
			// If going to the podium		
			if
			(
				((gGT->gameMode1 & ADVENTURE_ARENA) != 0) &&
				(gGT->podiumRewardID != 0) 
			)
			{
				struct Model** modelPtrArr = 
					&data.podiumModel_firstPlace;

				for(int i = 0; i < 8; i++)
				{
					struct Model* m = modelPtrArr[i];
					
					if (m == 0) continue;
					if (m->id == -1) continue;
					
					gGT->modelPtr[m->id] = m;
				}
			}


			// Main Menu
			if (levelID == MAIN_MENU_LEVEL)
			{
				audioState = 7;
LAB_800346b0:
				DECOMP_Audio_SetState_Safe((int)audioState);
				return ++loadingStage;
			}

			// One of the maps on Adventure Arena
			if (levelID - GEM_STONE_VALLEY < 5)
			{
				audioState = 6;

				// podium reward
				if (gGT->podiumRewardID == 0) //0
				{
					audioState = 5;
				}
				goto LAB_800346b0;
			}

			// oxide intro
			if (levelID == INTRO_RACE_TODAY)
			{
				audioState = 3;
				goto LAB_800346b0;
			}

			// credits
			if (levelID == CREDITS_TINY)
			{
				audioState = 2;
				goto LAB_800346b0;
			}

			// Naughty Dog Box
			if (levelID == NAUGHTY_DOG_CRATE)
			{
				audioState = 4;
				goto LAB_800346b0;
			}

			// stop/pause cseq music
			audioState = 1;

			if (levelID - CREDITS_CRASH < 2) goto LAB_800346b0;
			break;
		}
		case LOADING_SET_GGT_FLAGS:
		{			
			// Limited-Rendering scenarios
			if (
					(levelID == SCRAPBOOK) ||
					(levelID == MAIN_MENU_LEVEL) ||
					((gGT->gameMode2 & CREDITS) != 0)
				)
			{
				// disable rendering everything
				// draw loading screen and instances
				gGT->renderFlags = (gGT->renderFlags & 0x1000) | 0x20;
			}
			
			// Normal level
			else
			{
				// enable all flags except loading screen
				gGT->renderFlags = gGT->renderFlags | 0xffffefff;
			}

			gGT->hudFlags = gGT->hudFlags | 8;
			gGT->framesInThisLEV = 0;
			gGT->msInThisLEV = 0;

			DECOMP_ElimBG_Deactivate(gGT);

			// signify end of load
			return LOADING_END;
		}
		default:
			return loadingStage;
	}
	
	loadingStage++;
	return loadingStage;
}