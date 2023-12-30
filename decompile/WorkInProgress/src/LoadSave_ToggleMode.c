#include <common.h>

void LoadSave_ToggleMode(int mode)
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

  LoadSave_UnMuteCursors();

  data.menuBox_FourAdvProfiles.drawStyle = data.menuBox_FourAdvProfiles.drawStyle & 0xffef;
  data.menuBox_overwrite_adv.drawStyle &= 0xffef;
  if (sdata->data10_bbb[0] == 0x20) {
    data.menuBox_FourAdvProfiles.drawStyle = data.menuBox_FourAdvProfiles.drawStyle | 0x10;
    data.menuBox_overwrite_adv.drawStyle |= 0x10;
  }

  // LoadSave_Init
  LoadSave_Init(data.menuBox_FourAdvProfiles.drawStyle);

  data.menuBox_FourAdvProfiles.rowSelected = sdata->unk_8008d73C_relatedToRowHighlighted;
  *(short*)&sdata->data10_bbb = 0;
}