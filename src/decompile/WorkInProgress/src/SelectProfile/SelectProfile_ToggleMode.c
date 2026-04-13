#include <common.h>

void SelectProfile_ToggleMode(int mode)
{
  sdata->memcardAction = mode & 0xf;

  // 0x00 - AdvNew (garage) mode
  // 0x10 - AdvLoad (main menu) mode
  // 0x20 - Green mode
  // 0x30 - Ghost mode
  // 0x40 - SlotSelected (exiting) mode
  *(int*)&sdata->data10_bbb[0] = mode & 0xf0;

  *(short*)&sdata->data10_bbb[4] = 0;
  *(short*)&sdata->data10_bbb[6] = 0;
  *(short*)&sdata->data10_bbb[8] = 0;
  *(short*)&sdata->data10_bbb[10] = 0;
  *(short*)&sdata->data10_bbb[12] = 0;

  SelectProfile_UnMuteCursors();

  data.menuFourAdvProfiles.drawStyle = data.menuFourAdvProfiles.drawStyle & 0xffef;
  data.menuOverwriteAdv.drawStyle &= 0xffef;
  if (sdata->data10_bbb[0] == 0x20) {
    data.menuFourAdvProfiles.drawStyle = data.menuFourAdvProfiles.drawStyle | 0x10;
    data.menuOverwriteAdv.drawStyle |= 0x10;
  }

  // SelectProfile_Init
  SelectProfile_Init(data.menuFourAdvProfiles.drawStyle);

  data.menuFourAdvProfiles.rowSelected = sdata->unk_8008d73C_relatedToRowHighlighted;
  *(short*)&sdata->data10_bbb = 0;
}