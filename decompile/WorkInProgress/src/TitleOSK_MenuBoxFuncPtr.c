#include <common.h>

void DECOMP_TitleOSK_MenuBoxFuncPtr(struct MenuBox *mb)
{
  short selection = TitleOSK_DrawMenu(0x13f);
  struct GameTracker *gGT = sdata->gGT;

  mb->rowSelected = selection;
  // if no row is selected (or canceled?)
  if (selection == 0)
  {
    return;
  }

  if (sdata->data10_bbb[0xd] == 1)
  {
    if (selection < 0)
    {
      // Change active MenuBox to
      // end of race menu with "Save Ghost" option
      sdata->ptrDesiredMenuBox = (struct MenuBox *)0x800a0458;
    }
    else
    {
      // Set Load/Save to Ghost mode, with slot 1 selected
      LoadSave_ToggleMode(0x31);
      // Change active MenuBox to GhostSelection
      sdata->ptrDesiredMenuBox = &data.menuBox_GhostSelection;
    }
  }
  else if ((sdata->data10_bbb[0xd] < 2) && (sdata->data10_bbb[0xd] == 0))
  {
    if (selection < 0)
    {
      // Change active MenuBox back to Adv char select
      sdata->ptrDesiredMenuBox = CS_Garage_GetMenuBox();
      CS_Garage_ZoomOut(1);
    }
    else
    {
      // make backup of name entered
      sdata->advProgress.name[0] = gGT->prevNameEntered[0];
      sdata->advProgress.name[4] = gGT->prevNameEntered[4];
      sdata->advProgress.name[8] = gGT->prevNameEntered[8];
      sdata->advProgress.name[0xc] = gGT->prevNameEntered[0xc];
      sdata->advProgress.name[0x10] = gGT->prevNameEntered[0x10];
      // Set Load/Save to New Adventure mode
      LoadSave_ToggleMode(1);
      // Change active menuBox to draw four adv profiles
      sdata->ptrDesiredMenuBox = &data.MENUBOX_DrawSelfFourAdvProfiles;
    }
  }
}