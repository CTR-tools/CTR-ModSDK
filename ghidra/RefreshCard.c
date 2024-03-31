
// RefreshCard_BoolGhostForLEV
int FUN_800469f0(short param_1)

{
  short sVar1;
  int iVar2;
  short sVar3;

  sVar3 = 0;
  iVar2 = 0;
  sVar1 = 0;

  // if ghost profiles are present
  if (0 < DAT_8009aa5c)
  {
	// loop through ghost profiles
    do {
      sVar3 = sVar1;
      sVar1 = (short)iVar2;
      iVar2 = iVar2 + 1;

	  // Check trackID of each profile
      if ((&DAT_8009aa88)[sVar1 * 0x1a] == param_1) {
        sVar3 = sVar3 + 1;
      }
      sVar1 = sVar3;
    } while (iVar2 * 0x10000 >> 0x10 < (int)DAT_8009aa5c);
  }
  return (int)sVar3;
}


void FUN_80046a74(void)

{
  DAT_8009aa30 = DAT_8009aa30 & 0xfffffff7 | 6;
  return;
}



uint FUN_80046a90(short param_1)

{
  uint uVar1;

  if ((param_1 == 8) && ((DAT_8009aa30 & 6) != 0)) {
    return 1;
  }
  uVar1 = 0;
  if ((((DAT_8009aa30 & 6) == 0) && (DAT_8009aa3e == DAT_8009aa42)) &&
     (DAT_8009aa40 == DAT_8009aa44)) {
    uVar1 = (uint)(DAT_8009aa34 == param_1);
  }
  return uVar1;
}



void FUN_80046b1c(undefined2 param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined2 param_6)

{
  // param2 is 1 for SLOTS
  // param2 is 3 for ghost data

  DAT_8009aa30 = DAT_8009aa30 & 0xfffffff7;

  DAT_8009aa3a = param_2;

  // slotIndex
  DAT_8009aa3c = param_1;

  DAT_8009aa42 = param_2;

  // param1 always zero?
  DAT_8009aa44 = param_1;

  // Name of the save
  DAT_8009aa48 = param_3;

  DAT_8009aa4c = param_4;

  // if reading, copy data to this address
  DAT_8009aa50 = param_5;

  // if reading, copy data of this size
  DAT_8009aa54 = param_6;
  return;
}


// RefreshCard_GhostEncodeByte
uint FUN_80046b60(int param_1)
{
  // only called from RefreshCard_GhostEncodeProfile

  uint uVar1;
  short sVar2;

  sVar2 = (short)param_1;
  if (sVar2 < 10) {
    return param_1 + 0x30U & 0xff;
  }
  if (sVar2 < 0x24) {
    return param_1 + 0x37U & 0xff;
  }
  if (sVar2 < 0x3e) {
    uVar1 = param_1 + 0x3dU & 0xff;
  }
  else {
    uVar1 = 0x2d;
    if (sVar2 != 0x3e) {
      return 0x5f;
    }
  }
  return uVar1;
}


// RefreshCard_GhostDecodeByte
int FUN_80046bc0(byte param_1)
{
  // only called from RefreshCard_GhostDecodeProfile

  if (param_1 == 0x2d) {
    return 0x3e;
  }
  if (param_1 == 0x5f) {
    return 0x3f;
  }
  if (param_1 < 0x3a) {
    return (uint)param_1 - 0x30;
  }
  if (0x5a < param_1) {
    return (int)(((uint)param_1 + 0xffc3) * 0x10000) >> 0x10;
  }
  return (int)(((uint)param_1 + 0xffc9) * 0x10000) >> 0x10;
}


// WARNING: Removing unreachable block (ram,0x80046e88)
// WARNING: Removing unreachable block (ram,0x80046ed4)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// RefreshCard_GhostEncodeProfile
void FUN_80046c30(
	uint param_1,	// index to save (or load) to
	ushort param_2, // character ID array
	ushort param_3, // Level ID Array
	int param_4,	// amount of time
	undefined4 *param_5) // string typed from OSK

{
  bool bVar1;
  undefined4 *puVar2;
  undefined uVar3;
  byte bVar4;
  int iVar5;
  char *pcVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  undefined4 *puVar15;
  undefined4 *puVar16;
  char local_138 [128];
  undefined4 local_b8 [32];
  ushort local_38;
  uint local_30;

  local_30 = SEXT24((short)param_2);
  local_38 = param_2;
  do {
    bVar1 = true;

	// if time is more than 9:59:99
    if (0x8c9ff < param_4)
	{
	  // set time to 9:59:99
      param_4 = 0x8c9ff;
    }

    uVar11 = local_30 | (int)((uint)param_3 << 0x10) >> 0xc;
    uVar12 = uVar11 | param_4 << 9;
    uVar13 = uVar12 | param_1 << 0x1d;

	// RefreshCard_GhostEncodeByte
    uVar3 = FUN_80046b60(uVar11 & 0x3f);

    _DAT_80085a3c = CONCAT11(uVar3,DAT_80085a3c);
    _DAT_80085a3c = _DAT_80085a3c & 0xffff0000 | (uint)_DAT_80085a3c;

	// RefreshCard_GhostEncodeByte
    uVar3 = FUN_80046b60((uVar12 & 0xfc0) >> 6);

    _DAT_80085a3c = CONCAT12(uVar3,_DAT_80085a3c);
    _DAT_80085a3c = _DAT_80085a3c & 0xff000000 | (uint)_DAT_80085a3c;

	// RefreshCard_GhostEncodeByte
    bVar4 = FUN_80046b60((uVar12 & 0x3f000) >> 0xc);

    _DAT_80085a3c = _DAT_80085a3c & 0xffffff | (uint)bVar4 << 0x18;
    bVar4 = FUN_80046b60((uVar12 & 0xfc0000) >> 0x12);
    _DAT_80085a40 = _DAT_80085a40 & 0xffffff00 | (uint)bVar4;

	// RefreshCard_GhostEncodeByte
    uVar3 = FUN_80046b60(uVar13 >> 0x18 & 0x3f);

    _DAT_80085a40 = CONCAT11(uVar3,DAT_80085a40);
    _DAT_80085a40 = _DAT_80085a40 & 0xffff0000 | (uint)_DAT_80085a40;

	// RefreshCard_GhostEncodeByte
    uVar3 = FUN_80046b60(uVar13 >> 0x1e);

	// loop counter
    iVar14 = 0;

	_DAT_80085a40 = (uint)CONCAT12(uVar3,_DAT_80085a40);

	// If there is ghost data to load
    if (0 < DAT_8009aa5c)
	{
	  // for iVar14 = 0; iVar14 < numGhosts; iVar14++
      do {
        iVar5 = strcmp();

		// increment loop counter
        iVar14 = iVar14 + 1;

        if (iVar5 == 0) {
          bVar1 = false;
          break;
        }
      } while (iVar14 * 0x10000 >> 0x10 < (int)DAT_8009aa5c);
    }
    param_1 = param_1 + 1 & 7;
    if (bVar1)
	{
      local_138[0] = '\0';

	  // length of string
	  iVar14 = strlen();

	  // param_3 = levelID
      strcat(

		// append end of string
		local_138 + iVar14,

		// lngStrings[MetaDataLEV[id].name_LNG]
        *(char **)((int)*(short *)(&DAT_80083a88 + (int)(short)param_3 * 0x18) * 4 +
				DAT_8008d878)
	  );

	  // ":"
      strcat(local_138,&DAT_8008d46c);

	  // length of string
      iVar14 = strlen();

	  // local_38 = 80086E84
      strcat(

		// append end of string
		local_138 + iVar14,

		// lngStrings[MetaDataCharacters[id].name_LNG_long]
		*(char **)((int)*(short *)(&DAT_80086d8a + ((int)((uint)local_38 << 0x10) >> 0xc)) * 4
                + DAT_8008d878)
	  );

	  // ":"
	  strcat(local_138,&DAT_8008d46c);

	  // make a string with amount of time
	  // param_4 is the number of milliseconds in the race (or lap)
      pcVar6 = (char *)FUN_80044ff8(param_4);

	  // append end of string
      strcat(local_138,pcVar6);

	  // CTR_ScrambleGhostString (why?)
	  FUN_80022234(local_b8,local_138);

      puVar2 = &DAT_800992a4;
      puVar16 = local_b8;
      do {
        puVar15 = puVar16;
        puVar7 = puVar2;
        uVar9 = puVar15[1];
        uVar8 = puVar15[2];
        uVar10 = puVar15[3];
        *puVar7 = *puVar15;
        puVar7[1] = uVar9;
        puVar7[2] = uVar8;
        puVar7[3] = uVar10;
        puVar16 = puVar15 + 4;
        puVar2 = puVar7 + 4;
      } while (puVar16 != local_b8 + 0xc);
      uVar10 = puVar15[5];
      uVar8 = puVar15[6];
      uVar3 = *(undefined *)(puVar15 + 7);
      puVar7[4] = *puVar16;
      puVar7[5] = uVar10;
      puVar7[6] = uVar8;
      *(undefined *)(puVar7 + 7) = uVar3;
      *(undefined *)((int)puVar7 + 0x1d) = *(undefined *)((int)puVar15 + 0x1d);
                    // WARNING: Read-only address (ram,0x8009abe5) is written
                    // WARNING: Read-only address (ram,0x8009abe9) is written

	  // copy string into ghostProfile_current
	  DAT_8009abcc = DAT_80085a30;
      DAT_8009abd0 = DAT_80085a34;
      DAT_8009abd4 = DAT_80085a38;
      DAT_8009abd8 = _DAT_80085a3c;
      DAT_8009abdc = _DAT_80085a40;

	  // 80085a44
	  // BASCUS-94426G*
      DAT_8009abe0._0_1_ = s_BASCUS_94426G__80085a44[0];

	  // OSK name
      ram0x8009abe1 = *param_5;
      ram0x8009abe5 = param_5[1];
      ram0x8009abe9 = param_5[2];
      DAT_8009abed = param_5[3];
      DAT_8009abf1 = *(undefined *)(param_5 + 4);

      DAT_8009abf2 = 1;

	  // trackID
      DAT_8009abf4 = param_3;

	  // characterID
      DAT_8009abf6 = local_38;

      DAT_8009abf8 = (short)param_1;
      DAT_8009abfc = param_4;
      return;
    }
  } while( true );
}


// RefreshCard_GhostDecodeProfile
void FUN_80047034(undefined4 *param_1,undefined4 *param_2)

{
  undefined uVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  uint uVar11;
  uint uVar12;

  // RefreshCard_GhostDecodeByte
  uVar2 = FUN_80046bc0((uint)*(byte *)((int)param_2 + 0xd));
  iVar3 = FUN_80046bc0((uint)*(byte *)((int)param_2 + 0xe));
  iVar4 = FUN_80046bc0((uint)*(byte *)((int)param_2 + 0xf));
  iVar5 = FUN_80046bc0((uint)*(byte *)((int)param_2 + 0x10));
  iVar6 = FUN_80046bc0((uint)*(byte *)((int)param_2 + 0x11));
  iVar7 = FUN_80046bc0((uint)*(byte *)((int)param_2 + 0x12));

  uVar11 = (int)(short)uVar2 | (iVar3 << 0x10) >> 10;
  uVar12 = uVar11 | (iVar4 << 0x10) >> 4 | iVar5 << 0x12 | iVar6 << 0x18;
  *(ushort *)((int)param_1 + 0x2a) = uVar2 & 0xf;
  *(short *)(param_1 + 10) = (short)((uVar11 & 0x1f0) >> 4);
  param_1[0xc] = (uVar12 & 0x1ffffe00) >> 9;
  *(ushort *)(param_1 + 0xb) =
       ((ushort)(uVar12 >> 0x10) | (ushort)((uint)(iVar7 << 0x1e) >> 0x10)) >> 0xd;
  *(undefined *)((int)param_1 + 0x26) = 0;
  uVar8 = param_2[1];
  uVar9 = param_2[2];
  uVar10 = param_2[3];
  *param_1 = *param_2;
  param_1[1] = uVar8;
  param_1[2] = uVar9;
  param_1[3] = uVar10;
  uVar1 = *(undefined *)(param_2 + 5);
  param_1[4] = param_2[4];
  *(undefined *)(param_1 + 5) = uVar1;
  *(undefined *)((int)param_1 + 0x29) = 0;
  return;
}


// RefreshCard_StartMemcardAction
// 2 = null
// 3 = save main CTR save file (adv, high score, etc)
// 5 = load ghost profile
// 6 = save ghost files
// 7 = load main ctr save file (adv, high score, etc)
void FUN_80047198(undefined2 param_1)

{
  DAT_8008d478 = param_1;
  DAT_8008d964 = 0;
  DAT_8008d984 = 0;
  return;
}


// RefreshCard_StopMemcardAction
void FUN_800471ac(void)

{
  // memcard action = null
  DAT_8008d478 = 2;
  
  DAT_8008d964 = 1;
  return;
}



void FUN_800471c4(undefined2 param_1)

{
  DAT_8008d47a = param_1;
  FUN_80046a74();
  return;
}



void FUN_800471e8(void)

{
  // if data has not been wiped to "default state"
  // before reading memcard, then wipe it now
  if (DAT_8008d968 == 0)
  {
	// 8008d474 is ptr to memcard data
	// GAMEPROG_InitFullMemcard
    FUN_80026c24(PTR_DAT_8008d474);

	// dont do this a second time
    DAT_8008d968 = 1;
  }

  DAT_8008d928 = 0;
  DAT_8008d95c = 1;
  return;
}


// RefreshCard_GetNumGhostsTotal
void FUN_80047224(void)

{
  // By default, there are zero ghosts available to load
  DAT_8009aa5c = 0;
  return;
}


// RefreshCard_GameProgressAndOptions
void FUN_80047230(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;

  DAT_8008d95c = 1;
  DAT_8008d928 = 1;
  DAT_8008d96c = 0xffff;

  // GAMEPROG_SyncGameAndCard
  // params are: memcardPtr, ram ptr
  // not "save", more like "sync" memcard and ram
  FUN_80026d7c(PTR_DAT_8008d474 + 0x144,&DAT_8008e6e8);

  // pointer to memcard GameProgress and partially GameOptions
  puVar2 = (undefined4 *)(PTR_DAT_8008d474 + 0x15f4);
  puVar4 = (undefined4 *)(PTR_DAT_8008d474 + 0x144);

  // GameProgress struct
  puVar1 = &DAT_8008e6e8;

  // Copy to memory card
  do {
    puVar8 = puVar1;
    puVar3 = puVar4;
    uVar5 = puVar3[1];
    uVar6 = puVar3[2];
    uVar7 = puVar3[3];
    *puVar8 = *puVar3;
    puVar8[1] = uVar5;
    puVar8[2] = uVar6;
    puVar8[3] = uVar7;
    puVar4 = puVar3 + 4;
    puVar1 = puVar8 + 4;
  } while (puVar4 != puVar2);

  uVar5 = puVar3[5];
  uVar6 = puVar3[6];
  puVar8[4] = *puVar4;
  puVar8[5] = uVar5;
  puVar8[6] = uVar6;

  // RaceConfig_LoadGameOptions
  FUN_80043c10();
  return;
}



void FUN_800472d0(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 local_1c;
  undefined4 *puVar4;
  undefined4 uVar5;
  char *pcVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  undefined *local_20;

  bVar1 = false;
  switch(DAT_8008d47a) {
  case 0:
    bVar1 = true;
    
	// memcard action = null
	DAT_8008d478 = 2;
	
    DAT_8008d984 = 1;
    break;
  case 1:
  
	// if not loading profile
    if (DAT_8008d478 != 7) 
	{
	  // memcard action = null
      DAT_8008d478 = 2;
      goto LAB_800475b4;
    }
	
	// if DAT_8008d478 == 7, continue here...
	
	// memcard action = null
    DAT_8008d478 = 2;
	
    FUN_800471c4();
    uVar5 = 4;

	// 800859e4
	// BASCUS-94426-SLOTS
    pcVar6 = s_BASCUS_94426_SLOTS_800859e4;

	puVar7 = (undefined4 *)0x0;
    local_20 = (undefined *)0x0;
    local_1c = 0;
LAB_80047544:
    FUN_80046b1c(0,uVar5,pcVar6,puVar7,local_20,local_1c);
    DAT_8008d984 = 0;
    break;
  case 5:
  case 6:
    bVar1 = true;
    break;
  case 7:
  case 8:
  case 9:

	// if loading ghost profile
	if (DAT_8008d478 == 5)
	{
      FUN_800471c4(4);

	  // ghost profile (save or load?)
	  FUN_80046b1c(0,3,&DAT_8009aa60 + (int)DAT_8009aa5a * 0x34,0,DAT_8008d754,0x3e00);
    }
    else {
      if (DAT_8008d478 < 6) 
	  {
		// if saving main CTR save file
        if (DAT_8008d478 == 3) 
		{
		  // memcard action = null
          DAT_8008d478 = 2;
          
		  FUN_800471c4(3);

		  // 800859e4
		  // BASCUS-94426-SLOTS
          pcVar6 = s_BASCUS_94426_SLOTS_800859e4;

		  puVar7 = (undefined4 *)&DAT_800859f8;

		  // size of memory card buffer
          local_1c = 0x1680;

		  // 8008d470 -> 800992E4, holds all memory card bytes
          local_20 = PTR_DAT_8008d470;
LAB_8004753c:
          uVar5 = 2;
          goto LAB_80047544;
        }
      }
      else {
        
		// if saving ghost profile
		if (DAT_8008d478 == 6) 
		{
          if (-1 < (int)DAT_8009aa56)
		  {
			// Get offset in array based on index,
			// the string of each profile is 0x34 bytes apart
            iVar2 = (int)DAT_8009aa56 * 0x34;

			// This happens as soon as you start saving ghost,
			// and "Saving..." appears on the screen

			// Generate 0x14-character string for profile name
			// BASCUS-94426GT xxxxx
			DAT_80099284 = *(undefined4 *)(&DAT_8009aa60 + iVar2);
            DAT_80099288 = *(undefined4 *)(&DAT_8009aa64 + iVar2);
            DAT_8009928c = *(undefined4 *)(&DAT_8009aa68 + iVar2);
            DAT_80099290 = *(undefined4 *)(&DAT_8009aa6c + iVar2);
            DAT_80099294 = *(undefined4 *)(&DAT_8009aa70 + iVar2);
            DAT_80099298 = (&DAT_8009aa74)[iVar2];

			FUN_800471c4(3);

			// Name of Ghost profile to save to
            FUN_80046b1c(0,5,&DAT_80099284,0,0,0);

            DAT_8008d984 = 0;
            iVar2 = ((int)DAT_8009aa5c + -1) - (int)DAT_8009aa56;
            if (iVar2 != 0)
			{
			  // Get byte index, given array index
              iVar3 = (int)DAT_8009aa56 * 0x34;

			  // copy the string
              memmove(&DAT_8009aa60 + iVar3,&DAT_8009aa94 + iVar3,iVar2 * 0x34);
            }

			// decrease number of ghost profiles
            DAT_8009aa5c = DAT_8009aa5c + -1;
            break;
          }
          FUN_800471c4(3);
          pcVar6 = (char *)&DAT_80085a30;
          puVar7 = &DAT_800992a4;

		  // size of two memcard slots
          local_1c = 0x3e00;

		  // address of ghost recording buffer
          local_20 = DAT_8008fbf4;

          goto LAB_8004753c;
        }
      }
    }
LAB_800475b4:
    bVar1 = true;
    DAT_8008d984 = 1;
  }
  
  // if NEWCARD detected
  iVar2 = FUN_80046a90(3);
  if (iVar2 != 0) {
    FUN_800471e8();

	// RefreshCard_GetNumGhostsTotal
    FUN_80047224();

    goto LAB_80047a08;
  }
  
  iVar2 = FUN_80046a90(0);
  
  // if memory card is present
  if (iVar2 == 0) 
  {
    iVar2 = FUN_80046a90(1);
    local_1c = 6;
    if (iVar2 == 0) {
      
	  // if TIMEOUT (no card) detected
	  iVar2 = FUN_80046a90(2);
      
	  // no TIMEOUT
	  if (iVar2 == 0) 
	  {
        iVar2 = FUN_80046a90(5);
        
		// if data found on memcard
		if (iVar2 == 0) 
		{
          iVar2 = FUN_80046a90(4);
          if (iVar2 != 0) 
		  {
LAB_800479bc:
            
			// wrapper for resetting GameProg
			FUN_800471e8();
			
            DAT_8008d95c = 0;
            
			// reset gameProg (again?)
			DAT_8008d968 = 0;
			
			// "Loading..."
            FUN_800471c4(4);
			
            uVar5 = 3;

			// 800859e4
			// BASCUS-94426-SLOTS
            pcVar6 = s_BASCUS_94426_SLOTS_800859e4;

			puVar7 = (undefined4 *)0x0;

			// size of memory card buffer
            local_1c = 0x1680;

			// 8008d470 -> 800992E4, holds all memory card bytes
            local_20 = PTR_DAT_8008d470;
LAB_800479f4:
            bVar1 = false;
            FUN_80046b1c(0,uVar5,pcVar6,puVar7,local_20,local_1c);
            DAT_8008d984 = 0;
            goto LAB_80047a08;
          }
		  
		  // check if memcard is unformatted
          iVar2 = FUN_80046a90(6);
          if (iVar2 != 0)
		  {
			// RefreshCard_GetNumGhostsTotal
            FUN_80047224();

            FUN_800471e8();
			
			// "Warning, memcard unformatted"
            local_1c = 1;
            
			goto LAB_800476b4;
          }
          
		  iVar2 = FUN_80046a90(7);
          if (iVar2 == 0) goto LAB_80047a08;
          
		  DAT_8008d984 = 1;
          
		  if (DAT_8008d47a == 3) 
		  {
			// if saving ghost profile
            if (DAT_8008d478 == 6) {
              if (-1 < DAT_8009aa56) {
                DAT_8009aa56 = -1;
				
				/// "Saving..."
                FUN_800471c4(3);
                
				uVar5 = 2;
                pcVar6 = (char *)&DAT_80085a30;
                puVar7 = &DAT_800992a4;

				// max size of ghost recording buffer
				local_1c = 0x3e00;

				// address of ghost recording buffer
                local_20 = DAT_8008fbf4;

                goto LAB_800479f4;
              }

              iVar2 = ((int)DAT_8009aa5c + -1) - (int)DAT_8009aa58;

			  if (iVar2 != 0)
			  {
				// get ghost profile
                iVar3 = (int)DAT_8009aa58 * 0x34;

				// copy from profile array to current profile
                memmove(&DAT_8009aa94 + iVar3,&DAT_8009aa60 + iVar3,iVar2 * 0x34);
              }

              puVar4 = &DAT_8009abcc;
              puVar7 = (undefined4 *)(&DAT_8009aa60 + (int)DAT_8009aa58 * 0x34);

			  // increment number of ghost profiles
              DAT_8009aa5c = DAT_8009aa5c + 1;

              do {
                local_1c = puVar4[1];
                uVar5 = puVar4[2];
                uVar8 = puVar4[3];
                *puVar7 = *puVar4;
                puVar7[1] = local_1c;
                puVar7[2] = uVar5;
                puVar7[3] = uVar8;
                puVar4 = puVar4 + 4;
                puVar7 = puVar7 + 4;
              } while (puVar4 != &DAT_8009abfc);
              *puVar7 = DAT_8009abfc;
            }
            DAT_8008d964 = 1;
            local_1c = 8;
            
			// memcard action = null
			DAT_8008d478 = 2;
			
            goto LAB_80047984;
          }
          if (DAT_8008d47a < 4) {
            if (DAT_8008d47a == 2)
			{
			  // RefreshCard_GetNumGhostsTotal
              FUN_80047224();

			  FUN_800471e8();
              DAT_8008d928 = 1;
              if (-1 < DAT_8008d978)
			  {
				// if chose load or save (0 or 1)
                if (DAT_8008d978 < 2)
				{
				  // 8008d474 is ptr to memcard data
				  // GAMEPROG_InitFullMemcard
                  FUN_80026c24(PTR_DAT_8008d474);

				  // NULL
                  FUN_800471c4(8);

				  // 800859e4
				  // BASCUS-94426-SLOTS
                  FUN_80046b1c(0,1,s_BASCUS_94426_SLOTS_800859e4,0,0,0);

				  bVar1 = false;
                }
                else {

				  // if you are deleting data
                  if (DAT_8008d978 == 2) {
                    DAT_8008d984 = 1;
                  }
                }
              }
            }
            goto LAB_80047a08;
          }
          if (DAT_8008d47a != 4) {
            if (DAT_8008d47a != 5) goto LAB_80047a08;

			// RefreshCard_GetNumGhostsTotal
            FUN_80047224();

			goto LAB_800479bc;
          }
		  
		  // if loading ghost profile
          if (DAT_8008d478 == 5)
		  {
			// you want to show a ghost during a race
            DAT_8008d958 = 1;

			DAT_8008d964 = 1;
            local_1c = 8;
          }
          else
		  {
			// If memory card save has correct version number
            if (*(int *)PTR_DAT_8008d474 == 0x1600ffee)
			{
			  // the save is not outdated
              DAT_8008d944 = 0;

			  // RefreshCard_GameProgressAndOptions
              FUN_80047230();

              local_1c = 8;
            }
            else
			{
			  // the save is outdated
              DAT_8008d944 = 1;

              FUN_800471e8();
			  
			  // "No Data"
              local_1c = 9;
            }
          }
          FUN_800471c4(local_1c);
		  
		  // memcard action = null
          DAT_8008d478 = 2;
        }
        else
		{
		  // the save is not outdated
          DAT_8008d944 = 0;
          FUN_800471e8();
          DAT_8008d984 = 1;
		  
		  // "No Data"
          local_1c = 9;
		  
          if ((DAT_8008d978 != 0) && ((DAT_8008d978 < 0 || (local_1c = 8, 2 < DAT_8008d978))))
          goto LAB_80047a08;
LAB_80047984:
          DAT_8008d984 = 1;
          FUN_800471c4(local_1c);
        }

		// 800859e4
		// BASCUS-94426-SLOTS
        FUN_80046b1c(0,1,s_BASCUS_94426_SLOTS_800859e4,0,0,0);

		bVar1 = false;
        goto LAB_80047a08;
      }
	  
	  // TIMEOUT (no card)
      FUN_800471e8();
	  
	  // "Error occured while reading memory card"
      local_1c = 7;
    }
  }
  
  // if no memory card
  else {
    FUN_800471e8();

	// RefreshCard_GetNumGhostsTotal
    FUN_80047224();

	// "Warning, no memory card"
	local_1c = 0;
  }
LAB_800476b4:
  FUN_800471c4(local_1c);

  // 800859e4
  // BASCUS-94426-SLOTS
  FUN_80046b1c(0,1,s_BASCUS_94426_SLOTS_800859e4,0,0,0);

  DAT_8008d984 = 1;
  bVar1 = false;
LAB_80047a08:
  if ((bVar1) && (iVar2 = FUN_80046a90(8), iVar2 == 0))
  {
	// 800859e4
	// BASCUS-94426-SLOTS
    FUN_80046b1c(0,1,s_BASCUS_94426_SLOTS_800859e4,0,0,0);
  }
  return;
}



void FUN_80047a58(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  iVar4 = -1;
  if ((DAT_8009aa30 & 1) == 0) {
    if (DAT_8009aa36 != 0) {
      iVar4 = FUN_8003ddac();
      DAT_8009aa3e = DAT_8009aa36;
      DAT_8009aa40 = DAT_8009aa38;
    }
  }
  else {
    DAT_8009aa3e = DAT_8009aa36;
    DAT_8009aa40 = DAT_8009aa38;
    uVar1 = DAT_8009aa30 & 0xfffffffe;
    if ((DAT_8009aa30 & 2) == 0) {
      uVar1 = DAT_8009aa30 & 0xfffffffa;
    }
    DAT_8009aa30 = uVar1;

    switch(DAT_8009aa36)
	{
    case 1:
	  // MEMCARD_GetInfo
      iVar4 = FUN_8003e238((int)DAT_8009aa38);
      break;
    case 2:
	  // MEMCARD_Save
      iVar4 = FUN_8003e344((int)DAT_8009aa38,DAT_8009aa48,DAT_8009aa4c,DAT_8009aa50,
                           (int)DAT_8009aa54,0);
      break;
    case 3:
	  // MEMCARD_Load
      iVar4 = FUN_8003e29c((int)DAT_8009aa38,DAT_8009aa48,DAT_8009aa50,(int)DAT_8009aa54,0);
      break;

    case 4:
      // MEMCARD_Format
	  iVar4 = FUN_8003e51c((int)DAT_8009aa38);
      break;

    case 5:
	  // MEMCARD_EraseFile (unused)
      iVar4 = FUN_8003e6d4((int)DAT_8009aa38,DAT_8009aa48);
    }
  }
  iVar2 = iVar4 << 0x10;

  if (
		(DAT_8009aa36 == 1) &&
		(
			iVar3 = iVar2 >> 0x10,
			iVar2 = iVar4 << 0x10,
			iVar3 == 3
		)
	  )
  {
    iVar4 = 0;

	// Set number of ghost profiles to zero
    DAT_8009aa5c = 0;

	// 80085a44
	// BASCUS-94426G*
	// MEMCARD_FindFirstGhost
    iVar3 = FUN_8003e600((int)DAT_8009aa38,s_BASCUS_94426G__80085a44);

	iVar2 = 0;

	// loop until you have gone through all memory card saves
    while (iVar3 != 0)
	{
	  // If there are less than 7 ghosts loaded
      if (iVar2 >> 0x10 < 7)
	  {
		// RefreshCard_GhostDecodeProfile
        FUN_80047034(&DAT_8009aa60 + (iVar2 >> 0x10) * 0x34);

		// increment ghost counter
        DAT_8009aa5c = DAT_8009aa5c + 1;
      }

	  // increment number of ghosts loaded
      iVar4 = iVar4 + 1;

	  // MEMCARD_FindNextGhost
      iVar3 = FUN_8003e678();

	  // bitshifted version of numGhosts
      iVar2 = iVar4 * 0x10000;
    }

	// slotIndex, and saveName
	FUN_8003e59c((int)DAT_8009aa38,DAT_8009aa48);

    DAT_8009aa30 = DAT_8009aa30 | 8;

	// slotIndex, and saveName
    iVar2 = FUN_8003e59c((int)DAT_8009aa38,DAT_8009aa48);

	iVar2 = iVar2 << 0x10;
  }
  switch(iVar2 >> 0x10) {
  
  // from MEMCARD_GetNextSwEvent == IOE (processing done)
  case 0:
    DAT_8009aa34 = 7;
    if ((DAT_8009aa36 == 1) && (DAT_8009aa34 = 4, (DAT_8009aa30 & 8) == 0)) {
      DAT_8009aa34 = 7;
    }
    break;
  
  // from MEMCARD_GetInfo, 
  // from MEMCARD_Save if seek() fails or write() fails
  // from MEMCARD_Load if seek() fails or read() fails
  // from MEMCARD_GetNextSwEvent fail (ERROR, bad card)
  case 1:
    DAT_8009aa34 = 2;
    break;
	
  // from MEMCARD_GetNextSwEvent fail (TIMEOUT, no card)
  case 2:
    DAT_8009aa34 = 0;
    DAT_8009aa36 = 0;
    goto switchD_80047c84_caseD_8;
  
  // from MEMCARD_GetNextSwEvent fail (NEWCARD)
  case 3:
    DAT_8009aa34 = 3;
    if (DAT_8009aa36 == 4) {
      DAT_8009aa34 = 7;
    }
    break;
  
  // from MEMCARD_Save if open() fails
  case 4:
    DAT_8009aa34 = 1;
    break;
  
  // from FUN_8003ddac
  case 5:
    DAT_8009aa34 = 6;
    break;
  
  // from MEMCARD_Load if open() fails
  case 6:
    DAT_8009aa34 = 5;
    break;
  
  // from MEMCARD_GetInfo, 
  // from MEMCARD_Save if write() works
  // from MEMCARD_Load if read() works
  case 7:
    DAT_8009aa34 = 8;
	
  default:
    goto switchD_80047c84_caseD_8;
  }
  
  DAT_8009aa36 = 0;
  
switchD_80047c84_caseD_8:
  
  if ((DAT_8009aa36 == 0) && (DAT_8009aa3a != 0)) {
    DAT_8009aa36 = DAT_8009aa3a;
    DAT_8009aa3a = 0;

	// slotIndex
	DAT_8009aa38 = DAT_8009aa3c;

    DAT_8009aa30 = DAT_8009aa30 & 0xfffffffd | 1;
  }
  return;
}

// spammed in main menu, adv arena, and end-of-race
// supposedly triggers memcard routines. if noped, game hangs at CHECKING... screen
// the 2 functions are only called here.
void FUN_80047d64(void)
{
  // if PauseAllThreads is diabled
  if ((*(uint *)PTR_DAT_8008d2ac & 0x10) == 0)
  {
    FUN_80047a58();

	// Handles BASCUS-94426-SLOTS file for
	// Adventure saves and time trial scores
    FUN_800472d0();
  }
  return;
}
