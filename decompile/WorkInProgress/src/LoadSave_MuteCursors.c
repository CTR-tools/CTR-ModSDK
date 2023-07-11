#include <common.h> 

void DECOMP_LoadSave_MuteCursors(void)
{
  data.MENUBOX_DrawSelfFourAdvProfiles.state |= MUTE_SOUND_OF_MOVING_CURSOR;

  data.menuBox_GhostSelection.state |= MUTE_SOUND_OF_MOVING_CURSOR;

  data.menuBox_warning2.state |= MUTE_SOUND_OF_MOVING_CURSOR;
  return;
}

void DECOMP_LoadSave_UnMuteCursors(void)
{
  data.MENUBOX_DrawSelfFourAdvProfiles.state &= ~MUTE_SOUND_OF_MOVING_CURSOR;

  data.menuBox_GhostSelection.state &= ~MUTE_SOUND_OF_MOVING_CURSOR;

  data.menuBox_warning2.state &= ~MUTE_SOUND_OF_MOVING_CURSOR;
  return;
}