#include <common.h> 

void DECOMP_LoadSave_MuteCursors(void)
{
  data.MENUBOX_DrawSelfFourAdvProfiles.state |= 0x800000;

  data.menuBox_GhostSelection.statae |= 0x800000;

  data.menuBox_warning2.state |= 0x800000;
  return;
}

void DECOMP_LoadSave_UnMuteCursors(void)
{
  data.MENUBOX_DrawSelfFourAdvProfiles.state &= 0xff7fffff;

  data.menuBox_GhostSelection.statae &= 0xff7fffff;

  data.menuBox_warning2.state &= 0xff7fffff;
  return;
}