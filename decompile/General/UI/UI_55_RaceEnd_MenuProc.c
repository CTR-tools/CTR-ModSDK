#include <common.h>

void DECOMP_UI_RaceEnd_MenuProc(struct RectMenu* menu)
{
  short option;
  struct GameTracker *gGT;
  u_int uVar3;
  int iVar4;
  u_short style;

  gGT = sdata->gGT;
  
  if (menu->unk1e != 0)
  {
    menu->drawStyle &= ~(0x100);

    // if more than 2 screens
    if (2 < gGT->numPlyrCurrGame)
      menu->drawStyle |= 0x100;
  
	return;
  }
  
  int row = menu->rowSelected;
  if(row < 0) return;
  
  option = menu->rows[row].stringIndex;
  
  // if not SAVE GHOST
  if (option != 9)
  {
    // make Menu invisible
    DECOMP_RECTMENU_Hide(menu);
  }
  
  sdata->framesSinceRaceEnded = 0;
  sdata->numIconsEOR = 1;
  
  // Press * To Continue
  // do not put this in the switch,
  // switch needs to be a "small" jump table,
  // and an offest this large could bloat table
  if(option == 0xc9)
  {
    sdata->menuReadyToPass |= 1;
    return;
  }
  
  switch(option)
  {
	// Quit
	case 3:
	{
		// Erase ghost of previous race from RAM
		DECOMP_GhostTape_Destroy();
		
		// go back to main menu
		sdata->mainMenuState = 0;
		
		// load LEV of main menu
		DECOMP_MainRaceTrack_RequestLoad(0x27);
		break;
	}
	
	case 4:
	{
		// Turn off HUD
		gGT->hudFlags &= 0xfe;
	
		if (DECOMP_RaceFlag_IsFullyOffScreen() == 1)
			DECOMP_RaceFlag_BeginTransition(1);
	
		sdata->Loading.stage = -5;
	
		// howl_StopAudio
		// clear backup,
		// keep music,
		// destroy "most" fx, let menu fx play to end
		DECOMP_howl_StopAudio(1, 0, 0);
	
		// if did not improve time, then dont
		// overwrite old ghost with new ghost
		if ((gGT->unknownFlags_1d44 & 1) == 0)
			break;
		
		sdata->boolReplayHumanGhost = 1;
			
		// slower than ND's copy, I know, we'll
		// come up with a modern-gcc friendly way
		// to sort the LWs and SWs later
		memcpy(
			sdata->ptrGhostTapePlaying, 
			sdata->GhostRecording.ptrGhost, 
			0x3e00);
	
		// Make P2 the character that is saved in the
		// header of the ghost that you will see in the race
		data.characterIDs[1] = sdata->ptrGhostTapePlaying->characterID;
	
		// no ghosts are drawing
		sdata->boolGhostsDrawing = 0;
	
		break;
	}
	
	// Change Character, or Change Level
	case 5:
	case 6:
	{
		// Erase ghost of previous race from RAM
		DECOMP_GhostTape_Destroy();
	
		// 1 for character select
		// 2 for track select
		sdata->mainMenuState = option - 4;
		
		// when loading is done
		// add flag for "in menus"
		sdata->Loading.OnBegin.AddBitsConfig0 |= 0x2000;
		
		// load LEV of main menu
		DECOMP_MainRaceTrack_RequestLoad(0x27);
		break;
	}
	
	// Save Ghost
	case 9:
	{
		sdata->framesSinceRaceEnded = FPS_DOUBLE(0x3f9);
		
		#ifndef REBUILD_PS1
		// Set Load/Save to Ghost mode
		SelectProfile_ToggleMode(0x31);
		#endif
		
		// Change active Menu to GhostSelection
		sdata->ptrActiveMenu = &data.menuGhostSelection;
		break;
	}
	
	// Change Setup
	case 10:
	{
		// go to battle setup screen
		sdata->mainMenuState = 3;
		
		// load LEV of main menu
		DECOMP_MainRaceTrack_RequestLoad(0x27);
		break;
	}
	
	// Exit To Map
	case 0xd:
	{
		sdata->Loading.OnBegin.AddBitsConfig0 |= ADVENTURE_ARENA;
		sdata->Loading.OnBegin.RemBitsConfig8 |= TOKEN_RACE;
		
		sdata->Loading.OnBegin.RemBitsConfig0 |= 
		(
			ADVENTURE_CUP |
			CRYSTAL_CHALLENGE |
			RELIC_RACE |
			ADVENTURE_BOSS
		);
		
		if ((gGT->gameMode1 & ADVENTURE_CUP) != 0)
		{
			DECOMP_MainRaceTrack_RequestLoad(GEM_STONE_VALLEY);
			break;
		}
		
		// If you're in a Boss Race
		if (gGT->gameMode1 < 0)
			sdata->Loading.OnBegin.AddBitsConfig8 |= SPAWN_AT_BOSS;
		
		DECOMP_MainRaceTrack_RequestLoad(gGT->prevLEV);
		break;
	}
  }
}
