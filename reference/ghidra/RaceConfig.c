
// RaceConfig_LoadGameOptions
void FUN_80043c10(void)

{
  int iVar1;

  if (DAT_8008d8f0 == 0) {
    DAT_8008d8f0 = 1;
    iVar1 = 0;

	// loop 3 times (fx, music, voice)
	do {
      howl_VolumeSet((int)(short)iVar1,(uint)(byte)(&DAT_8008fb7c)[(int)(short)iVar1 * 2]);
      iVar1 = iVar1 + 1;
      DAT_800841fc = DAT_8008fb82;
      _DAT_80084200 = DAT_8008fb86;
      DAT_80084204 = DAT_8008fb8a;
      DAT_80084208 = DAT_8008fb8e;
      DAT_8008420c = DAT_8008fb92;
      DAT_80084210 = DAT_8008fb96;
    } while (iVar1 * 0x10000 >> 0x10 < 3);

    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | DAT_8008fb9c & 0xf00;

	// howl_ModeSet
	FUN_8002b1fc((uint)DAT_8008fba0 & 1);
  }
  return;
}

// RaceConfig_SaveGameOptions
void FUN_80043d24(void)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;

  // loop counter
  iVar4 = 0;

  // pointer counter
  iVar3 = 0;

  do
  {
	// get value for each type of volume and clamp to 0x100
    uVar1 = howl_VolumeGet(iVar3 >> 0x10);

	// store a backup of volume
	*(ushort *)(&DAT_8008fb7c + (iVar3 >> 0x10) * 2) = uVar1 & 0xff;

	// loop counter
    iVar4 = iVar4 + 1;

	// pointer counter
    iVar3 = iVar4 * 0x10000;

  } while (iVar4 * 0x10000 >> 0x10 < 3);

  DAT_8008fb82 = DAT_800841fc;
  DAT_8008fb86 = _DAT_80084200;
  DAT_8008fb8a = DAT_80084204;
  DAT_8008fb8e = DAT_80084208;
  DAT_8008fb92 = DAT_8008420c;
  DAT_8008fb96 = DAT_80084210;
  DAT_8008fb9c = *(uint *)PTR_DAT_8008d2ac & 0xf00;

  // howl_ModeGet
  uVar2 = FUN_8002b1f0();

  // store a saftery-copy of mode?
  DAT_8008fba0 = (ushort)((uVar2 & 0xff) != 0);
  return;
}
