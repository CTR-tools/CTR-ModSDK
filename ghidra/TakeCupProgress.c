
// TakeCupProgress_Activate (beta 'Arcade' was Gran Prix)
// Only called from 233, when you are at the cup
// podium and you need to save progress
void FUN_8004b230(undefined2 param_1)

{
  // string index to print
  DAT_8008d938 = param_1;

  // 80085a68 is where a menu buffer is stored
  // for "Save Game", "yes / no"

  // Draw the menu
  FUN_80046990(&DAT_80085a68);

  return;
}


// TakeCupProgress_MenuProc (beta 'Arcade' was Gran Prix)
void FUN_8004b258(int param_1)

{
  short sVar1;

  if (*(short *)(param_1 + 0x1e) == 1)
  {
	// if there is a string to print
    if ((int)DAT_8008d938 != 0)
	{
	  // print "Save your cup progress?"
	  // and optionally "New Battle Arena Opened!"

	  // DecalFont_DrawMultiLine
      FUN_80022b34(*(undefined4 *)((int)DAT_8008d938 * 4 + DAT_8008d878),0x100,0x3c,0x1cc,1,
                   0xffff8000);
    }
  }
  else {
    sVar1 = *(short *)(param_1 + 0x1a);
    if (sVar1 == 0) {
      DAT_8008d918 = 1;

	  // Set Load/Save to "Slot Selected" mode
      FUN_80048e2c(0x41);

	  // Change active Menu to Warning
      DAT_8008d924 = &DAT_80085be0;
    }
    else {
      if (sVar1 < 1) {
        if (sVar1 != -1) {
          return;
        }
      }
      else {
        if (sVar1 != 1) {
          return;
        }
      }

	  // Make the menu disappear
      FUN_800469c8();
    }
  }
  return;
}