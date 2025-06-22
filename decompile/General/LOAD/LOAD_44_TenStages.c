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

int DECOMP_LOAD_TenStages(struct GameTracker* gGT, int loadingStage, struct BigHeader* bigfile)
{
	u_char numPlyrNextGame;
	short sVar4;
	int iVar5;
	u_int uVar6;
	CdlCB pcVar7;
	u_int* puVar8;
	int iVar9;
	struct Level* lev;
	u_int gameMode1; //-- redundant
	int iVar12;
	char *levelNamePtr;
	u_char* moremoredata; //-- redundant
	int *piVar15;
	u_int uVar16;
	u_int uVar17;
	int vramSize;
	int boolDefault1P;
	int levelID;
	int ovrRegion1;
	int ovrRegion3;
	struct Model* m;

	// if game is loading
	if (sdata->load_inProgress != 0)
	{
		return loadingStage;
	}
	
	levelID = gGT->levelID;
	
	switch(loadingStage)
	{
		case 0:
		{
#ifndef REBUILD_PS1
			// if level is not AdvGarage or Naughty Dog Box Scene
			if ((levelID != ADVENTURE_GARAGE) && (levelID != NAUGHTY_DOG_CRATE))
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

			// Turn off HUD
			gGT->hudFlags &= 0xfe;
			gGT->hudFlags &= 0xf7;

			// disable all rendering except loading screen
			gGT->renderFlags &= 0x1000;

			gGT->level1 = 0;
			gGT->level2 = 0;

			DrawSync(0);

			// no overlay transition
			gGT->overlayTransition = 0;

			// disable certain game mode flags
			gGT->gameMode1 &= ~(GAME_CUTSCENE | END_OF_RACE | ADVENTURE_ARENA | MAIN_MENU);
			gGT->gameMode2 &= ~(LEV_SWAP | CREDITS | NO_LEV_INSTANCE);

			gGT->visMem1 = 0;
			gGT->visMem2 = 0;
			
			boolDefault1P = 1;
			
			if(levelID >= SCRAPBOOK)
			{
				// both in main menu, and after credits,
				// checked and confirmed in retail version
				gGT->gameMode1 |= MAIN_MENU;
			}
			
			// credits
			else if(levelID >= CREDITS_CRASH)
			{
				// enable cutscene flag
				gGT->gameMode1 |= GAME_CUTSCENE;
			
				// lev swap (&20) and credits (&80)
				gGT->gameMode2 |= (LEV_SWAP | CREDITS);
			}
				
			// If you're in Naughty Dog Box Scene,
			// Oxide Any% ending
			// Oxide 101% ending
			else if(levelID >= NAUGHTY_DOG_CRATE)
			{
				// Enable cutscene flag
				gGT->gameMode1 |= GAME_CUTSCENE;
			}

			// main menu or garage
			else if(levelID >= MAIN_MENU_LEVEL)
			{
				// enable flag that shows you are in main menu
				gGT->gameMode1 |= MAIN_MENU;

				if(levelID == ADVENTURE_GARAGE)
				{
					// Enter Adventure Character Selection
					sdata->mainMenuState = 4;
				}
				
				else
				{
					// get NextGame from the game you exited
					gGT->numPlyrNextGame = gGT->numPlyrCurrGame;
					gGT->numPlyrCurrGame = 4;
					boolDefault1P = 0;
				}
			}

			// intro cutscenes
			else if(levelID >= INTRO_RACE_TODAY)
			{
				// Enable cutscene flag
				gGT->gameMode1 |= GAME_CUTSCENE;

				// lev swap will be needed
				gGT->gameMode2 |= LEV_SWAP;
			}

			// if you are loading into adventure map:
			// any of the hubs: "hub1", "hub2", etc
			else if(levelID >= GEM_STONE_VALLEY)
			{
				// Change mode to Adventure Arena
				gGT->gameMode1 |= ADVENTURE_ARENA;

				// lev swap will be needed
				gGT->gameMode2 |= LEV_SWAP;
				
				#ifdef USE_HIGHMP
				if(gGT->podiumRewardID == 0)
				{
					// get CurrGame from main menu's NextGame
					gGT->numPlyrCurrGame = gGT->numPlyrNextGame;
					boolDefault1P = 0;
				}
				#endif
			}
			
			// driving track
			else
			{
				// get CurrGame from main menu's NextGame
				gGT->numPlyrCurrGame = gGT->numPlyrNextGame;
				boolDefault1P = 0;
			}
			
			if(boolDefault1P != 0)
			{
				gGT->numPlyrCurrGame = 1;
				gGT->numPlyrNextGame = 1;
			}

			// Enable HUD Instances
			gGT->hudFlags |= 2;

			gGT->Debug_ToggleNormalSpawn = 1;

			// default
			sdata->levelLOD = gGT->numPlyrCurrGame;
			
			// main menu or adv garage
			if((gGT->gameMode1 & MAIN_MENU) != 0)
			{
				sdata->levelLOD = 1;
			}
			
			// if relic, or time trial
			if((gGT->gameMode1 & (TIME_TRIAL | RELIC_RACE)) != 0)
			{
				sdata->levelLOD = 8;
			}
			
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
		case 1:
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
				ovrRegion1 = 0;

			// 223 - Relic Race
			else if ((gGT->gameMode1 & RELIC_RACE) != 0) 
				ovrRegion1 = 2;
			
			// 224 - Time Trial
			else if ((gGT->gameMode1 & TIME_TRIAL) != 0)
				ovrRegion1 = 3;
			
			// 222 - Arcade/Trophy/Boss/C-T-R token
			// if arcade, or adv that isn't listed above
			else if ((gGT->gameMode1 & (ARCADE_MODE | ADVENTURE_MODE)) != 0)
				ovrRegion1 = 1;
			
			// default VS/Battle overlay if no mode found
			else 
				ovrRegion1 = 4;
			
			#ifdef USE_HIGHMP
			ovrRegion1 = 4;
			#endif
		
			DECOMP_LOAD_OvrEndRace(ovrRegion1);
			break;
		}
		case 2:
		{
			int levelID = gGT->levelID;
			
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
		case 3:
		{
			#ifdef USE_ONLINE
			// Load Region3 for planet
			if(gGT->levelID == INTRO_OXIDE)
				ovrRegion3 = 3;
			else
			#endif
			
			// main menu + scrapbook, 230
			if (
					(levelID != ADVENTURE_GARAGE) &&
					((gGT->gameMode1 & MAIN_MENU) != 0)
				)
			{
				ovrRegion3 = 0;
			}
			
			// race threads, 231
			else if (levelID <= LAB_BASEMENT)
			{
				ovrRegion3 = 1;
			}
			
			// advHub, 232
			else if (
						(levelID <= CITADEL_CITY) &&
						(gGT->podiumRewardID == 0)
				)
			{
				ovrRegion3 = 2;
			}
			
			// Cutscene, Credits, ND, Garage, Podium
			else
			{
				ovrRegion3 = 3;
			}
			
			DECOMP_LOAD_OvrThreads(ovrRegion3);
			break;
		}
		case 4:
		{
			// if level is not AdvGarage or Naughty Dog Box Scene
			if ((levelID != ADVENTURE_GARAGE) && (levelID != NAUGHTY_DOG_CRATE))
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
				if ((sdata->gameProgress.unlocks[1] & 0x10) != 0)
					sdata->gameProgress.unlocks[0] |= 1;
				#endif
				
				mainMenuInit[sdata->mainMenuState]();
			}
			
			#ifdef USE_PRELOAD
			// TODO: Duplicate DriverMPK just for setting DriverIDs
			DECOMP_LOAD_Robots1P(data.characterIDs[0]);
			
			// only once on-boot
			if(sdata->ptrMPK != 0)
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
				BI_TIMETRIALPACK + 0xF,
				&sdata->ptrMPK, cbDRAM);
			break;
			#endif
			
			// Needed, or else Post-Boss Outro
			// will break the character animations
			sdata->ptrMPK = 0;
			
			// Clear driver extras, and podium models
			int* ptrArray = &data.driverModelExtras[0];
			for(int i = 0; i < 11; i++)
			{
				ptrArray[i] = 0;
			}
			
			DECOMP_LOAD_DriverMPK((unsigned int)bigfile, sdata->levelLOD);
			break;
		}
		case 5:
		{
			#ifdef USE_PRELOAD
			// first-boot
			if(sdata->PLYROBJECTLIST == 0)
			{
				// Never de-allocate lower than here
				sdata->bookmarkID = DECOMP_MEMPACK_PushState();
			}
			#endif
			
			sdata->PLYROBJECTLIST = (int**)((unsigned int)sdata->ptrMPK + 4);
			if (sdata->ptrMPK == 0) sdata->PLYROBJECTLIST = 0;
						
			// clear and reset
			DECOMP_LibraryOfModels_Clear(gGT);
			DECOMP_LOAD_GlobalModelPtrs_MPK();
			DECOMP_DecalGlobal_Clear(gGT);

			gGT->mpkIcons = 0;
			if (sdata->ptrMPK != 0)
			{
				gGT->mpkIcons = *(int*)sdata->ptrMPK;
				
				if(gGT->mpkIcons != 0)
					DECOMP_DecalGlobal_Store(gGT, (struct LevTexLookup*)gGT->mpkIcons);
			}
			
			// if level is not AdvGarage or Naughty Dog Box Scene
			if ((levelID != ADVENTURE_GARAGE) && (levelID != NAUGHTY_DOG_CRATE))
			{
				DECOMP_Music_Stop();
				DECOMP_CseqMusic_StopAll();
				DECOMP_Music_LoadBanks();
			}
			
			break;
		}
		case 6:
		{
			// if level is not AdvGarage or Naughty Dog Box Scene
			if ((levelID != ADVENTURE_GARAGE) && (levelID != NAUGHTY_DOG_CRATE))
			{
				iVar9 = DECOMP_Music_AsyncParseBanks();

				if (iVar9 == 0)
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
				iVar9 = 0x6b000;
				iVar12 = 0x40000;

				// If you're in Adventure Arena
				if ((gGT->gameMode1 & ADVENTURE_ARENA) != 0)
				{
					// Adv Arena Packs
					iVar9 = 0x68800;
					iVar12 = 0x68800;
				}

#ifdef REBUILD_PC
				iVar9 = 0x68800<<1;
				iVar12 = 0x68800<<1;
#endif

				// Allocate room for LEV swapping
				iVar5 = (int)DECOMP_MEMPACK_AllocMem(iVar9 + iVar12); // "HUB ALLOC"
				sdata->ptrHubAlloc = (void*)iVar5;

				// Change active allocation system to #2
				// pack = [hubAlloc, hubAlloc+size1]
				DECOMP_MEMPACK_SwapPacks(1);
				DECOMP_MEMPACK_NewPack((void*)iVar5, iVar9);

				// Change active allocation system to #3
				// pack = [hubAlloc+size1, hubAlloc+size1+size2]
				DECOMP_MEMPACK_SwapPacks(2);
				DECOMP_MEMPACK_NewPack((void*)(iVar5 + iVar9), iVar12);

				// Intro cutscene with oxide spaceship and all racers
				if ((gGT->gameMode1 & ADVENTURE_ARENA) == 0)
				{
					// Always start with pool 1
					sVar4 = 1;
				}

				// If you're in Adventure Arena
				else
				{
					// Get 1 or 2, depending on map
					sVar4 = DECOMP_LOAD_GetAdvPackIndex();

					// Then swap:
					// Turn 1 into 2
					// Turn 2 into 1
					sVar4 = 3 - sVar4;
				}

				// keep track of subpack levels
				gGT->activeMempackIndex = sVar4;
				gGT->levID_in_each_mempack[sVar4] = gGT->levelID;
				gGT->levID_in_each_mempack[3 - sVar4] = 0xffff;

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
			uVar16 = DECOMP_LOAD_GetBigfileIndex(gGT->levelID, sdata->levelLOD);

			// add VRAM to loading queue
			DECOMP_LOAD_AppendQueue(
				0, LT_SETVRAM, uVar16 + LVI_VRAM, 
				NULL, DECOMP_LOAD_VramFileCallback);

			// add LEV to loading queue
			DECOMP_LOAD_AppendQueue( 
				0, LT_GETADDR, uVar16 + LVI_LEV, 
				&sdata->ptrLevelFile, DECOMP_LOAD_DramFileCallback);

			// if world is made of multiple LEVs
			if ((gGT->gameMode2 & LEV_SWAP) != 0)
			{
				// add PTR file to loading queue
				DECOMP_LOAD_AppendQueue(
					0, LT_SETADDR, uVar16 + LVI_PTR, 
					(void*)sdata->PatchMem_Ptr, DECOMP_LOAD_Callback_PatchMem);
			}			
			break;
		}
		case 7:
		{
			// get level pointer
			lev = sdata->ptrLevelFile;
			
			#ifdef USE_LEVELDEV
			if (gGT->levelID == CUSTOM_LEVEL_ID) 
				lev = (struct Level*)CUSTOM_LEV_ADDR;
			#endif

			gGT->level1 = lev;
			gGT->visMem1 = lev->visMem;

			if (lev != 0)
			{
				DECOMP_DecalGlobal_Store(gGT, lev->levTexLookup);
			}

			DECOMP_DebugFont_Init(gGT);

			// if level is not nullptr
			if (lev != 0)
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
			if (gGT->mpkIcons != 0)
			{
				piVar15 = (int*)(*(u_int*)((u_int)gGT->mpkIcons + 4));
				
				// Removed usage of DecalGlobal_FindInMPK
				// OG game would search every string one-by-one

				for(
						struct Icon* firstIcon = (struct Icon*)piVar15; 
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
			
			// === LEV_SWAP ===
			
			if ((gGT->gameMode1 & ADVENTURE_ARENA) == 0)
				break;
			
			// podium reward
			if (gGT->podiumRewardID != 0)
			{			
				// Set Pack of the hub you're NOT on
				DECOMP_MEMPACK_SwapPacks(3 - gGT->activeMempackIndex);
				
				// Load model+vrm files on the VRAM page
				// that does NOT overwrite the hub VRAM
				iVar9 = DECOMP_LOAD_GetAdvPackIndex() - 1;

				// VRAM for podium and all related models
				DECOMP_LOAD_AppendQueue(
					0, LT_SETVRAM, BI_PODIUMVRMS + iVar9, 
					NULL, DECOMP_LOAD_VramFileCallback);

				// podium first place
				u_char* ptrIndexArr = &gGT->podium_modelIndex_First;
				struct Model** ptrModelPtrArr = &data.podiumModel_firstPlace;
				int baseIndexPM = BI_DANCEMODELWIN;

				// Fix for Oxide (faster than OG code that does nothing)
				// If Oxide WIN is requested, add 16 to load Oxide LOSE
				if (ptrIndexArr[0] == 0x8d)
					baseIndexPM = BI_DANCEMODELLOSE;
				
				int fileIndex;
				void (*drmCb)(struct LoadQueueSlot*) = DECOMP_LOAD_DramFileCallback;

				// Loop through 3 podium models
				for(int i = 0; i < 3; i++)
				{
					if(ptrIndexArr[i] != 0)
					{
						fileIndex = baseIndexPM + iVar9 + 
							(ptrIndexArr[i] - 0x7e) * 2;
						
						DECOMP_LOAD_AppendQueue(
							0, LT_GETADDR, fileIndex, 
							&ptrModelPtrArr[i], drmCb);
					}
					
					baseIndexPM = BI_DANCEMODELLOSE;
				}
				
				// TAWNA
				fileIndex = BI_DANCETAWNAGIRL + iVar9 + 
					(gGT->podium_modelIndex_tawna - 0x8f) * 2;

				// add TAWNA to loading queue
				DECOMP_LOAD_AppendQueue(
					0, LT_GETADDR, fileIndex, 
					(void*)&data.podiumModel_tawna, drmCb);

				// if 0x7e+5 (dingo)
				if (gGT->podium_modelIndex_First == 0x83)
				{
					// add "DingoFire" to loading queue
					DECOMP_LOAD_AppendQueue(
						0, LT_GETADDR, BI_DINGOFIRE + iVar9, 
						(void*)&data.podiumModel_dingoFire, drmCb);
				}

				// add Podium
				DECOMP_LOAD_AppendQueue(0, LT_GETADDR, BI_PODIUM + iVar9, 
					&data.podiumModel_podiumStands, drmCb);

				// Disable LEV instances on Adv Hub, for podium scene
				gGT->gameMode2 = gGT->gameMode2 | 0x100;
			}

			break;
		}
		case 8:
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
					m = modelPtrArr[i];
					
					if (m == 0) continue;
					if (m->id == -1) continue;
					
					gGT->modelPtr[m->id] = m;
				}
			}

			// Level ID
			iVar9 = gGT->levelID;

			// Main Menu
			if (iVar9 == 0x27)
			{
				uVar16 = 7;
LAB_800346b0:
				DECOMP_Audio_SetState_Safe(uVar16);
				return loadingStage + 1;
			}

			// One of the maps on Adventure Arena
			if (iVar9 - 0x19U < 5)
			{
				uVar16 = 6;

				// podium reward
				if (gGT->podiumRewardID == 0)
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
		}
		case 9:
		{
			if (sdata->XA_State != 2)
			{
				if
				(

					// If not in main menu (not in 2D character selection, track selection, or any part of it)
					((gGT->gameMode1 & MAIN_MENU) == 0) ||

					// If level ID == 40
					// If you are in Adventure Character Selection
					(gGT->levelID == ADVENTURE_GARAGE)
				)
				{
					// if not going to credits
					if ((gGT->gameMode2 & CREDITS) == 0)
					{
						// enable all flags except loading screen
						gameMode1 = gGT->renderFlags | 0xffffefff;
					}

					// if going to credits
					else
					{
						// disable everything (except loading screen if still there)
						// enable drawing render bucket
						gameMode1 = (gGT->renderFlags & 0x1000) | 0x20;
					}

					// apply desired value
					gGT->renderFlags = gameMode1;
				}
				else
				{
					// disable everything (except loading screen if still there)
					// enable drawing render bucket
					gGT->renderFlags = (gGT->renderFlags & 0x1000) | 0x20;

					iVar9 = DECOMP_RaceFlag_IsFullyOffScreen();
					if (iVar9 == 1)
					{
						// checkered flag, begin transition on-screen
						DECOMP_RaceFlag_BeginTransition(1);
					}
				}
				gGT->hudFlags = gGT->hudFlags | 8;
				gGT->framesInThisLEV = 0;
				gGT->msInThisLEV = 0;

				DECOMP_ElimBG_Deactivate(gGT);

				// signify end of load
				return -2;
			}
			__attribute__((fallthrough));
		}
		default:
			return loadingStage;
	}
	
	loadingStage++;
	return loadingStage;
}