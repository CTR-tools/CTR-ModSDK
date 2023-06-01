#include <common.h>

void DECOMP_MM_TrackSelect_Init(void)
{
  struct MainMenu_LevelRow *currTrack;
  short numTracks;

  // lap selection menu is closed by default
  OVR_230.trackSel_boolOpenLapBox = false;
  OVR_230.trackSel_transitionState = 0;

  // set track index to the index selected in track selection menu, starts at 0 for both Arcade and Battle
  OVR_230.menubox_trackSelect.rowSelected = sdata->trackSelIndex;
  // 12 frames when moving between selection
  OVR_230.trackSel_transitionFrames = 0xc;

  // if you are in Battle mode
  if ((sdata->gGT->gameMode1 & 0x20) != 0)
  {
    // set menu element to first battle track, Nitro Coutrt
    currTrack = &OVR_230.battleTracks[0];
    // 7 battle tracks total
    numTracks = 7;
  }
  // otherwise set menu element to first arcade track, Crash Cove
  currTrack = &OVR_230.arcadeTracks[0];
  // 18 arcade tracks total
  numTracks = 0x12;

  // If you scroll past the max number of tracks, go back to the first track
  if (numTracks <= sdata->trackSelIndex)
  {
    OVR_230.menubox_trackSelect.rowSelected = 0;
  }

  // Loop through all tracks until a unlocked track is found
  while (MM_TrackSelect_boolTrackOpen(currTrack + OVR_230.menubox_trackSelect.rowSelected * 0x10) == false)
  {
    OVR_230.menubox_trackSelect.rowSelected += 1;

    // If track index goes too high
    if (numTracks <= OVR_230.menubox_trackSelect.rowSelected)
    {
      // reset to zero
      OVR_230.menubox_trackSelect.rowSelected = 0;
    }
  }

  OVR_230.trackSel_nextTrack = OVR_230.menubox_trackSelect.rowSelected;

  MM_TrackSelect_Video_SetDefaults();
}
