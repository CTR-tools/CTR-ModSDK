
// QueueLoadTrack_MenuProc
void FUN_80043b30(undefined4 param_1)

{
  undefined *puVar1;
  uint uVar2;

  // If you're in Time Trial
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20000) != 0)
  {
	// Set P3 to N Tropy
    DAT_80086e88 = 0xc;

	// Set P4 to N Oxide
    DAT_80086e8a = 0xf;
  }

  // If you're in Adventure Mode
  if ((*(uint *)PTR_DAT_8008d2ac & 0x80000) != 0) {

	// Change mode to Adventure Arena
    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | 0x100000;
  }

  puVar1 = PTR_DAT_8008d2ac;

  // If you're not in Battle Mode
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0)
  {
    *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d84) = 0x2a300;

	// Turn off 0x10000: Time limit (battle)
	// Turn off 0x4000: Point limit (battle)
	// Turn off 0x8000 Life limit (battle)
    uVar2 = *(uint *)PTR_DAT_8008d2ac;
    *(uint *)puVar1 = uVar2 & 0xfffe3fff;
  }

  // MainRaceTrack_RequestLoad(track in trackSelection)
  FUN_8003cfc0((int)*(short *)(PTR_DAT_8008d2ac + 0x1eb0));

  // RECTMENU_Hide
  FUN_800469c8(param_1);
  return;
}


// QueueLoadTrack_GetMenuPtr
undefined * FUN_80043c04(void)

{
  return &DAT_80085a94;
}
