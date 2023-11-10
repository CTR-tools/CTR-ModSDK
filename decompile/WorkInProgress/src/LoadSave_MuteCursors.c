#include <common.h> 

void DECOMP_LoadSave_MuteCursors(void)
{
  data.menuBox_FourAdvProfiles.state |= MUTE_SOUND_OF_MOVING_CURSOR;

  data.menuBox_GhostSelection.state |= MUTE_SOUND_OF_MOVING_CURSOR;

  data.menuBox_warning2.state |= MUTE_SOUND_OF_MOVING_CURSOR;
  return;
}

void DECOMP_LoadSave_UnMuteCursors(void)
{
  data.menuBox_FourAdvProfiles.state &= ~MUTE_SOUND_OF_MOVING_CURSOR;

  data.menuBox_GhostSelection.state &= ~MUTE_SOUND_OF_MOVING_CURSOR;

  data.menuBox_warning2.state &= ~MUTE_SOUND_OF_MOVING_CURSOR;
  return;
}