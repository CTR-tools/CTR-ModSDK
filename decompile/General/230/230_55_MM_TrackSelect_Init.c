#include <common.h>

void DECOMP_MM_TrackSelect_Init()
{
	struct MainMenu_LevelRow *selectMenu;
	short numTracks;

	// lap selection menu is closed by default
	D230.trackSel_boolOpenLapBox = false;
	D230.trackSel_transitionState = 0;

	// set track index to the index selected in track selection menu, starts at 0 for both Arcade and Battle
	D230.menubox_trackSelect.rowSelected = sdata->trackSelIndex;
	
	// 12 frames when moving between selection
	D230.trackSel_transitionFrames = 12;
	
	// Set menu and num of tracks based on game mode
	if ((sdata->gGT->gameMode1 & BATTLE_MODE) != 0)
	{
		selectMenu = D230.battleTracks;
		numTracks = 7;
	}
	else
	{
		selectMenu = D230.arcadeTracks;
		numTracks = 18;
	}

	// If you scroll past the max number of tracks, go back to the first track
	if (numTracks <= sdata->trackSelIndex)
	{
		D230.menubox_trackSelect.rowSelected = 0;
	}

	// Loop through all tracks until an unlocked track is found
	while (!MM_TrackSelect_boolTrackOpen(&selectMenu[D230.menubox_trackSelect.rowSelected]))
	{
		D230.menubox_trackSelect.rowSelected++;

		// If track index goes too high, reset to zero
		if (numTracks <= D230.menubox_trackSelect.rowSelected)
		{
			D230.menubox_trackSelect.rowSelected = 0;
		}
	}

	D230.trackSel_currTrack = D230.menubox_trackSelect.rowSelected;

	MM_TrackSelect_Video_SetDefaults();
}