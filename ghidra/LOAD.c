// generic overlay callback
void FUN_800319e8(void)

{
  // gp -> 0x138
  // sdata->load_inProgress = 0;
  uGp00000138 = 0;

  return;
}

// 230 overlay callback
void FUN_800319f4(void)

{
  // dll 230 is now loaded
  PTR_DAT_8008d2ac[0x2541] = 0;

  // gp -> 0x138
  // sdata->load_inProgress = 0;
  uGp00000138 = 0;

  return;
}

// 231 overlay callback
void FUN_80031a08(void)

{
  // dll 231 is now loaded
  PTR_DAT_8008d2ac[0x2541] = 1;

  // gp -> 0x138
  // sdata->load_inProgress = 0;
  uGp00000138 = 0;

  return;
}

// 232 overlay callback
void FUN_80031a20(void)

{
  // dll 232 is now loaded
  PTR_DAT_8008d2ac[0x2541] = 2;

  // gp -> 0x138
  // sdata->load_inProgress = 0;
  uGp00000138 = 0;

  return;
}

// 233 overlay callback
void FUN_80031a38(void)

{
  // dll 233 is now loaded
  PTR_DAT_8008d2ac[0x2541] = 3;

  // gp -> 0x138
  // sdata->load_inProgress = 0;
  uGp00000138 = 0;

  return;
}

// callback maskhint3D
// param_1 - LoadQueueSlot
void FUN_80031a50(int param_1)

{
  // gp -> 0x138
  // sdata->load_inProgress = 0;
  uGp00000138 = 0;

  // gp->184
  // sdata->modelMaskHints3D modelptr

  // param_1 -> 0xC
  // LoadQueueSlot -> ptrDestination
  uGp00000184 = *(undefined4 *)(param_1 + 0xc);

  return;
}

// LOAD_Callback_Podiums
// param_1 - LoadQueueSlot
void FUN_80031a64(int param_1)
{
  // param_1 -> 0xC
  // LoadQueueSlot -> ptrDestination
  DAT_80083a38 = *(undefined4 *)(param_1 + 0xc);

  // gp -> 0x138
  // sdata->load_inProgress = 0;
  uGp00000138 = 0;

  return;
}

// LOAD_Callback_LEV
// param_1 - LoadQueueSlot
void FUN_80031a78(int param_1)

{
  // flags
  if ((*(ushort *)(param_1 + 4) & 2) == 0)
  {
    // gp -> 0x138
    // sdata->load_inProgress = 0;
    uGp00000138 = 0;
  }

  // gp -> 0x120 (0x8008d08c)
  // sdata->ptrLEV_DuringLoading
  // param_1 -> 0xC
  // LoadQueueSlot -> ptrDestination
  uGp00000120 = *(undefined4 *)(param_1 + 0xc);

  return;
}

// LOAD_Callback_LEV_Adv
// param_1 - LoadQueueSlot
void FUN_80031aa4(int param_1)

{
  // game is done loading
  DAT_8008d0a4 = 0;

  // LOAD_RunPtrMap
  // 8008d08c is pointer to LEV
  FUN_800326b4(DAT_8008d08c,*(int **)(param_1 + 0xc) + 1,**(int **)(param_1 + 0xc) >> 2);

  // change active allocation system to #1
  // used for whole game (except adventure arena)
  FUN_8003e80c(0);

  // MEMPACK_ClearHighMem
  // Erase Credits from RAM
  FUN_8003e938();

  // change active allocation system
  // swap 1 and 2 during adventure mode
  FUN_8003e80c((int)*(short *)(PTR_DAT_8008d2ac + 0x254a));
  return;
}

// LOAD_Callback_DriverModels
// param_1 - LoadQueueSlot
void FUN_80031b00(int param_1)

{
  // address of loading drivers
  // 8008D088
  uGp0000011c = *(undefined4 *)(param_1 + 0xc);

  // gp -> 0x138
  // sdata->load_inProgress = 0;
  uGp00000138 = 0;
  return;
}


// Sep review copy calls this
// LOAD_HubCallback
void FUN_80031b14(int param_1)

{
  short *psVar1;

  // game is done loading
  DAT_8008d0a4 = 0;

  // LOAD_Callback_LEV_Adv
  FUN_80031aa4(param_1);

  // swap 1 and 2 during adventure mode
  psVar1 = (short *)(PTR_DAT_8008d2ac + 0x254a);

  // set the pointer of the LEV being loaded, that
  // you are about to enter, in Adventure Hub
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x164) = DAT_8008d08c;

  // change active allocation system
  FUN_8003e80c((int)*psVar1);

  return;
}


// LOAD_GlobalModelPtrs_MPK
void FUN_80031b50(void)

{
  undefined *puVar1;
  int iVar2;
  int *piVar3;
  int iVar4;

  puVar1 = PTR_DAT_8008d2ac;

  // loop counter
  iVar4 = 0;

  // extra drivers in VS mode
  piVar3 = &DAT_80083a10;

  // for iVar4 = 0; iVar4 < 3; iVar4++
  do
  {
	// model pointer
    iVar2 = *piVar3;

    if (
		// if model is valid
		(iVar2 != 0) &&

		// if model-> id is not -1
		((int)*(short *)(iVar2 + 0x10) != -1)
	   )
	{
	  // store model in GameTracker's array of model IDs
      *(int *)(puVar1 + (int)*(short *)(iVar2 + 0x10) * 4 + 0x2160) = iVar2;
    }

	// increment loop counter
    iVar4 = iVar4 + 1;

    piVar3 = piVar3 + 1;
  } while (iVar4 < 3);

  // if PLYROBJECTLIST is valid
  if (DAT_8008d870 != 0)
  {
	// store model pointers until hitting nullptr
    FUN_8003147c(PTR_DAT_8008d2ac, 0xffffffff, DAT_8008d870);
  }
  return;
}


// LOAD_HubSwapPtrs
void FUN_80031bdc(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;

  // If the secondary LEV in adv hub is valid
  if (*(int *)(param_1 + 0x164) != 0)
  {
	// swap 0x160 and 0x164, so that the
	// secondary LEV becomes active

	// pointer to active LEV
    uVar1 = *(undefined4 *)(param_1 + 0x160);

	// called VISMEM in prototypes
    uVar2 = *(undefined4 *)(param_1 + 0x1a38);

	// set active LEV to inactive LEV
	*(int *)(param_1 + 0x160) = *(int *)(param_1 + 0x164);

	// record that hub has been swapped at least once
	*(undefined2 *)(param_1 + 0x2548) = 1;

	// set inactive LEV to previously-active LEV
    *(undefined4 *)(param_1 + 0x164) = uVar1;

	// called VISMEM in prototypes
	*(undefined4 *)(param_1 + 0x1a38) = *(undefined4 *)(param_1 + 0x1a3c);

	// called VISMEM in prototypes
    *(undefined4 *)(param_1 + 0x1a3c) = uVar2;
  }
  return;
}


// LOAD_StringToUpper
void FUN_80031c1c(byte *param_1)

{
  byte bVar1;

  bVar1 = *param_1;

  // while you haven't reached the end
  while (bVar1 != 0)
  {
	// if you detect a lowercase letter
    if ((uint)bVar1 - 0x61 < 0x1a)
	{
	  // make it uppercase
      *param_1 = bVar1 - 0x20;
    }

	// go to the next character
    param_1 = param_1 + 1;

	// set pVar1 to this character so it
	// can check for null terminator
    bVar1 = *param_1;
  }
  return;
}

// Aug 5 says
// "CD Init Error!"
// LOAD_InitCD
void FUN_80031c58(void)

{
  // CDSYS_Init
  FUN_8001c360(1);
  return;
}


// Aug 5 calls this
// LOAD_ReadDirectory
u_long * FUN_80031c78(char *param_1)

{
  CdlFILE *pCVar1;
  u_long *buf;
  int iVar2;
  u_long uVar3;
  u_char auStack48 [8];
  CdlFILE CStack40;

  // CDSYS_SetMode_StreamData
  FUN_8001c470();

  // cpVar1 and CStack40 are the same
  // param_1 is the string of the file searched,
  // pCVar1 is the CdlFILE that corresponds
  pCVar1 = CdSearchFile(&CStack40,param_1);

  // if BIGFILE was found on disc
  if (pCVar1 != (CdlFILE *)0x0)
  {
	// MEMPACK_AllocMem,
	// dont worry about size, we realloc in a minute
    buf = (u_long *)FUN_8003e874(0x4000,param_1);

	// 2 = CdlSetloc
    CdControl('\x02',(u_char *)&CStack40,auStack48);

	iVar2 = CdRead(8,buf,0x80);
    if (iVar2 != 0) {
      iVar2 = CdReadSync(0,(u_char *)0x0);
      if (iVar2 != 0) {
        return (u_long *)0;
      }

	  // get CD position of param_1 file
      uVar3 = CdPosToInt((CdlLOC *)&CStack40);

	  // save cdpos of bigfile, in header of bigfile
      *buf = uVar3;

	  // MEMPACK_ReallocMem,
	  // size of two int's, plus number of BigEntry
      FUN_8003e94c(buf[1] * 8 + 8);

	  // According to Aug 5:
	  // uvar3 = buf[0] = firstSector
	  // buf[1] = numFiles

	  // save it in another variable
	  DAT_8008d09c = buf;

	  // return CD position
      return buf;
    }
  }

  // not found, return false
  return (u_long *)0;
}


// LOAD_DramFileCallback
void FUN_80031d30(int param_1)

{
  int *piVar1;
  int *piVar2;
  code *pcVar3;
  int iVar4;

  piVar1 = *(int **)(param_1 + 0xc);

  if (piVar1 != (int *)0x0)
  {
    iVar4 = *piVar1;
    if (iVar4 < 0)
	{
	  // add flag
      *(ushort *)(param_1 + 4) = *(ushort *)(param_1 + 4) | 2;
    }
    else {
      piVar2 = (int *)((int)(piVar1 + 1) + iVar4);

	  // LOAD_RunPtrMap
      FUN_800326b4(piVar1 + 1,piVar2 + 1,*piVar2 >> 2);

	  // if overly allocated
      if ((*(ushort *)(param_1 + 4) & 1) != 0)
	  {
		// MEMPACK_ReallocMem
        FUN_8003e94c(iVar4 + 4);
      }
    }
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 4;
  }

  // get callback funcPtr
  pcVar3 = *(code **)(param_1 + 0x14);

  // check that callback is not zero, and has value 0x80xxxxxx
  if ((pcVar3 != (code *)0x0) && (((uint)pcVar3 & 0xff000000) == 0x80000000))
  {
	// execute funcPtr
    (*pcVar3)(param_1);
  }

  // ready to load next file
  DAT_8008d0a0 = 1;

  return;
}


// In Aug 5 prototype, this is
// called LOAD_DramFile
undefined4
FUN_80031e00(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4,
            int param_5)

{
	// param1 is Pointer to "cd position of bigfile"

  undefined4 local_28;
  undefined2 local_24;
  undefined2 local_22;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;

  if (param_5 == -1) {

	// offset 0x4: flags
	local_24 = 0;

	// offset 0x6: type
    local_22 = 2;

	// offset 0x0: bigfilePtr
    local_28 = param_1;

	// offset 0x8: subfileIndex
    local_20 = param_2;

	// called with same parameters as given to LOAD_DramFile
	// assembly shows those registers dont change

	// offset 0xC: ptrDestination
	// LOAD_ReadFile
    local_1c = FUN_800321b4();

	// offset 0x10: size
	local_18 = *param_4;

	// offset 0x14: callback
    local_14 = 0;

	// call the callback func
    FUN_80031d30(&local_28);
  }
  else {
    if (param_5 == -2)
	{
		// LOAD_ReadFile
		local_1c = FUN_800321b4(param_1,2,param_2,0,param_4,FUN_80031d30);

		DAT_80083a48 = local_1c;
		*param_3 = local_1c;
    }
    else
	{
		// LOAD_ReadFile
		local_1c = FUN_800321b4(param_1,2,param_2,param_3,param_4,FUN_80031d30);
    }
  }
  return local_1c;
}


// LOAD_VramFileCallback
// ctr texture file is either a single TIM, or multiple TIMS with a header
// https://github.com/CTR-tools/CTR-tools/blob/master/formats/txt_vram.txt
// param_1 = pointer to file queue slot
void FUN_80031ee4(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  //psy-q RECT struct
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  undefined2 local_12;

  //get file pointer from queue slot
  piVar2 = *(int **)(param_1 + 0xc);

  //if it's not empty
  if (piVar2 != (int *)0x0) {

    //are there multiple TIMs? (header 0x00000020)
    if (*piVar2 == 0x20) {

      //we got multiple TIMs, begin [readsize - load tim] loop

      iVar3 = piVar2[1];
      piVar2 = piVar2 + 2;

      //loop through all TIMs
      while (iVar3 != 0) {

        //read rect and load to vram (psy-q func)
        local_18 = *(undefined2 *)((int)piVar2 + 0xc);
        local_16 = *(undefined2 *)((int)piVar2 + 0xe);
        local_14 = *(undefined2 *)((int)piVar2 + 0x10);
        local_12 = *(undefined2 *)((int)piVar2 + 0x12);
        LoadImage(&local_18,(int)piVar2 + 0x14);

        //calulate pointers for next iteration
        iVar1 = iVar3 >> 2;
        iVar3 = piVar2[iVar1];
        piVar2 = piVar2 + iVar1 + 1;
      }
    }
    else {

      //only 1 TIM in this file

      //read rect and load to vram (psy-q func)
      local_18 = *(undefined2 *)((int)piVar2 + 0xc);
      local_16 = *(undefined2 *)((int)piVar2 + 0xe);
      local_14 = *(undefined2 *)((int)piVar2 + 0x10);
      local_12 = *(undefined2 *)((int)piVar2 + 0x12);
      LoadImage(&local_18,(int)piVar2 + 0x14);
    }
  }

  // record the frame that loading finished
  DAT_8008d0a8 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1ce4);

  return;
}

// In Aug 5 prototype, this is
// called LOAD_VramFile
//basically loads ctr texture file to vram in 3 different ways based on param_5 value
//param_1 = bigFilePtr
//param_2 = fileIndex
//param_3 = target pointer (where should we load the file, can be null)
//param_4 = ???
//param_5 = callback in other funcs/structs, also used to control execution by passing -1, -2 etc
undefined4
FUN_80031fdc(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4,
            int param_5)

{
  //local queue slot
  undefined4 local_30;
  undefined2 local_2c;
  undefined2 local_2a;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;

  // Used for "SCEA Presents", "Copyright", and "UI Textures"
  //if we're not given the address to use, create new temporary place to load
  if (param_3 == (undefined4 *)0x0) {

	// MEMPACK_PushState
    FUN_8003e978();
  }

  //case -1 = we don't want to use global file queue or store file in ram
  if (param_5 == -1) {

    //prepare local loading slot for the file
    local_2c = 0;
    local_2a = 3;
    local_30 = param_1;
    local_28 = param_2;
    local_24 = FUN_800321b4(); // LOAD_ReadFile
    local_20 = *param_4;
    local_1c = 0;

    //load all TIMs from ctr vram file (usually1 or 2)
    FUN_80031ee4(&local_30);

	VSync(2);

	// reset timer
    DAT_8008d0a8 = 0;

   //if we're not given the address to use, remove temporary space used before
    if (param_3 == (undefined4 *)0x0) {

	  // MEMPACK_PopState
	  FUN_8003e9d0();
    }
  }
  else {

    //case -2 = load file to ram and store to active slot of global file queue
    if (param_5 == -2)
	{
				// LOAD_ReadFile
      local_24 = FUN_800321b4(param_1,3,param_2,0,param_4,FUN_80031ee4);
      DAT_80083a48 = local_24;
      *param_3 = local_24;
    }
    else
	{
    //case not -1 or -2 = just return the pointer to loaded file

				// LOAD_ReadFile
      local_24 = FUN_800321b4(param_1,3,param_2,param_3,param_4,FUN_80031ee4);
    }
  }

  return local_24;
}


// In Sep Review copy, this is called
// LOAD_ReadFileASyncCallback
void FUN_80032110(char param_1)

{
  // Make the system forget the callback
  // function, because we will execute now
  CdReadCallback(0);

  // result == CdlComplete
  if (param_1 == '\x02') 
  {
    if ((DAT_80083a40 & 1) != 0)
	{
	  // MEMPACK_ReallocMem
      FUN_8003e94c(DAT_80083a4c);
    }

	// If a function pointer callback exists
    if (DAT_8008d85c != (code *)0x0)
	{
	  // Execute callback function
      (*DAT_8008d85c)(&DAT_80083a3c);
    }
  }
  else {
    if ((DAT_80083a40 & 1) != 0) {

	  // MEMPACK_PopState
      FUN_8003e9d0();
    }
    DAT_8008d0a1 = 1;
  }
  return;
}

// In Aug 5 prototype, this is
// called LOAD_ReadFile
// param1 is bigfile
// param2 is load type (ram, dram, vram)
// param3 is subfileIndex
// param4 is destination (can be nullptr)
// param5 is pointer to size
// param6 is callback
u_long * FUN_800321b4(int *param_1,undefined4 param_2,int param_3,u_long *param_4,int *param_5,
                     int param_6)

{
	// param1 is the Pointer to CD posiiton of BIGFILE

  bool bVar1;
  uint uVar2;
  int iVar3;
  code *pcVar4;
  uint uVar5;
  u_long *buf;
  CdlLOC aCStack56 [2];
  u_char auStack48 [8];

  bVar1 = true;

  // CDSYS_SetMode_StreamData
  FUN_8001c470();

  uVar5 = 0;

  // bigfile + subfileIndex
  // get size of file from bigfile header
  *param_5 = (param_1 + param_3 * 2)[3];

  // bigfile cdpos + subfileOffset
  CdIntToPos(*param_1 + (param_1 + param_3 * 2)[2],aCStack56);

  // if a destination pointer is not given
  if (param_4 == (u_long *)0x0)
  {
	// set flag that we used MEMPACK_AllocMem
	// to store this ReadFile somewhere random
    DAT_80083a40 = DAT_80083a40 | 1;

	// MEMPACK_AllocMem
	// 8008d0ac = "FILE"
    buf = (u_long *)FUN_8003e874(*param_5 + 0x7ffU & 0xfffff800,&DAT_8008d0ac);

	// if allocation failed
    if (buf == (u_long *)0x0)
	{
	  // function  failed
      return (u_long *)0;
    }
  }

  // if destination pointer is given
  else {
    DAT_80083a40 = DAT_80083a40 & 0xfffe;

	// use that
    buf = param_4;
  }
  while ((uVar5 == 0 || (!bVar1)))
  {
	// 2 = CdlSetloc
    uVar5 = CdControl('\x02',(u_char *)aCStack56,auStack48);

	// If no callback function pointer is given
	if (param_6 == 0)
	{
	  // Set function pointers to nullptr
      DAT_8008d85c = 0;
      pcVar4 = (code *)0x0;
    }

	// If you want a callback function pointer
	// to execute after LOAD_ReadFile is done
    else
	{
	  // Save the function pointer address
      DAT_8008d85c = param_6;

	  // LOAD_ReadFileASyncCallback
      pcVar4 = FUN_80032110;
    }

	// Save this function as a callback,
	// which does not execute the function pointer
	CdReadCallback(pcVar4);

    uVar2 = CdRead(*param_5 + 0x7ffU >> 0xb,buf,0x80);
    uVar5 = uVar5 & uVar2;
    if (param_6 == 0) {
      iVar3 = CdReadSync(0,(u_char *)0x0);
      bVar1 = iVar3 == 0;
    }
  }
  if ((param_6 == 0) && (param_4 == (u_long *)0x0))
  {
	// MEMPACK_ReallocMem
    FUN_8003e94c(*param_5);
  }
  return buf;
}


// Read file on disc, store in buffer
// LOAD_ReadFile_NoCallback
u_long * FUN_80032344(char *param_1,u_long *param_2,u_long *param_3)

{
  CdlFILE *pCVar1;
  int iVar2;
  u_long *buf;
  CdlFILE CStack56;
  u_char auStack32 [8];

  // LOAD_StringToUpper
  FUN_80031c1c(param_1);

  // CDSYS_SetMode_StreamData
  FUN_8001c470();

  // cpVar1 and CStack56 are the same
  // param_1 is the string of the file searched,
  // pCVar1 is the CdlFILE that corresponds
  pCVar1 = CdSearchFile(&CStack56,param_1);

  buf = param_2;

  // if the file was found
  if (pCVar1 != (CdlFILE *)0x0)
  {
	// return file size to parameter
    *param_3 = CStack56.size;

    if (
			(param_2 == (u_long *)0x0) &&

			(
				// MEMPACK_AllocMem
				buf = (u_long *)FUN_8003e874(CStack56.size + 0x7ff & 0xfffff800,param_1),

				// if allocation failed
				buf == (u_long *)0x0
			)
		)
	{
	  // function failed
      return (u_long *)0;
    }

	// 2 = CdlSetloc
    CdControl('\x02',(u_char *)&CStack56,auStack32);

	// read entire file into buf
    iVar2 = CdRead(CStack56.size + 0x7ff >> 0xb,buf,0x80);

    if ((iVar2 == 0) || (iVar2 = CdReadSync(0,(u_char *)0x0), iVar2 != 0)) {
      buf = (u_long *)0x0;
    }
    else {
      if (param_2 == (u_long *)0x0)
	  {
		// MEMPACK_ReallocMem
        FUN_8003e94c(CStack56.size);
      }
    }
  }
  return buf;
}


// find file on disc
// LOAD_FindFile
uint FUN_80032438(char *param_1,CdlFILE *param_2)

{
  uint uVar1;
  CdlFILE *pCVar2;

  // if filename is nullptr, or CdlFILE given is nullptr
  if ((param_1 == (char *)0x0) || (param_2 == (CdlFILE *)0x0))
  {
	// set to zero, so function returns zero
    uVar1 = 0;
  }
  else
  {
	// CDSYS_SetMode_StreamData
    FUN_8001c470();

	// LOAD_StringToUpper
    FUN_80031c1c(param_1);

	// cpVar2 and param_2 are the same
	// param_2 is the string of the file searched,
	// pCVar2 is the CdlFILE that corresponds
    pCVar2 = CdSearchFile(param_2,param_1);

	// return if file was found
    uVar1 = (uint)(pCVar2 != (CdlFILE *)0x0);
  }
  return uVar1;
}

// same as 80032594, but doesn't store params and calls CdReadSync
// only called from howl_LoadHeader
// param_1 is the address to CdlFile of Kart.HWL
// param_2 is ptrDestination
// param_3 is firstSector
// param_4 is numSector

// LOAD_HowlHeaderSectors
undefined4 FUN_80032498(CdlLOC *param_1,u_long *param_2,int param_3,int param_4)

{
  int iVar1;
  CdlLOC aCStack40 [2];
  u_char auStack32 [8];

  // CDSYS_SetMode_StreamData
  FUN_8001c470();

  // (numSectors * 0x800 - cdlFile.size) < 0x800
  if ((param_3 + param_4) * 0x800 - (int)param_1[1] < 0x800) {

	// Get CD Position of Kart.HWL
    iVar1 = CdPosToInt(param_1);

	// Convert (iVar1 + param_3) into
	// CD position, and store it in aCStack40
    CdIntToPos(iVar1 + param_3,aCStack40);

	// 2 = CdlSetloc
    CdControl('\x02',(u_char *)aCStack40,auStack32);

    iVar1 = CdRead(param_4,param_2,0x80);

	if (
		// if read is correct
		(iVar1 != 0) &&

		(
			// wait until read is complete
			iVar1 = CdReadSync(0,(u_char *)0x0),

			// if zero sectors remain
			iVar1 == 0
		)
	   )
	{
	  // it worked
      return 1;
    }
  }
  return 0;
}


// LOAD_HowlCallback
void FUN_8003254c(char param_1)

{
  // disable callback
  CdReadCallback(0);

  // result == CdlComplete
  if (param_1 == '\x02') {
    DAT_8008d840 = 0;
  }
  else {
      //else error?
    DAT_8008d840 = 0xffffffff;
  }
  return;
}


// loads howl related data from CD, only called from howl funcs
// used to load sample banks and cseq data
// also stores current params and loading status to global struct at DAT_8008d840
// param_1 - CdlLoc, file cd location (Kart.HWL)
// param_2 - pointer to load data to
// param_3 - offset from the beginning of file in sectors
// param_4 - number of sectors to load
// LOAD_HowlSectorChainStart
uint FUN_80032594(CdlLOC *param_1,u_long *param_2,int param_3,int param_4)

{
  // stores func result
  uint uVar1;
  // hidden var, stores cd reading result
  int iVar2;
  CdlLOC aCStack40 [2];
  u_char auStack32 [8];

  // if no sectors to load, result = true
  if (param_4 == 0) {
    uVar1 = 1;
  }
  else
  {
	// save parameters for LOAD_HowlSectorChainEnd

    // this seems to be some 5 int howl struct at DAT_8008d840, 1st int being current loading status
    DAT_8008d844 = param_1;
    DAT_8008d848 = param_2;
    DAT_8008d84c = param_3;
    DAT_8008d850 = param_4;

    // CDSYS_SetMode_StreamData
    FUN_8001c470();

    // if amount of data you requested to load, does not
    // overflow the size of Kart.HWL
    if ((param_3 + param_4) * 0x800 - (int)param_1[1] < 0x800)
	{
	  // convert CD location of Kart.HWL to sector
	  iVar2 = CdPosToInt(param_1);

	  // get absolute offset in sectors and convert to cdlloc
	  // store position into aCStack40
      CdIntToPos(iVar2 + param_3,aCStack40);

	  // 2 = CdlSetloc
      //spin round round to data it wants to read
      CdControl('\x02',(u_char *)aCStack40,auStack32);

      //set howl loading from cd status to 1. possible values are 0, 1 and -1
	  DAT_8008d840 = 1;

	  // Let the system know that a callback is
	  // going to be called. This does not execute
	  // the callback, but just records that it exists

      // sets callback to be called when reading is done
      // callback func basically reports this info back to howl struct
      CdReadCallback(FUN_8003254c);

      // read sectors from given address
      iVar2 = CdRead(param_4,param_2,0x80);

      // cd reading result
      uVar1 = (uint)(iVar2 != 0);
    }
    else {
      // result = false if it overflows
      uVar1 = 0;
    }
  }
  return uVar1;
}


//loads pending data from cd
//basically wrapper for FUN_80032594

// LOAD_HowlSectorChainEnd
uint FUN_8003266c(void)

{
  uint uVar1;

  //if loading status is -1 (error?)
  if (DAT_8008d840 == -1) {
    //call load func again passing params stored from previous call
    FUN_80032594(DAT_8008d844,DAT_8008d848,DAT_8008d84c,DAT_8008d850);
    uVar1 = 0;
  }
  else {
    //return current loading status ( 1 or 0 )
    uVar1 = (uint)(DAT_8008d840 == 0);
  }
  return uVar1;
}


// LOAD_RunPtrMap
// Change file-relative pointers to RAM pointers
// param_1 - ptr data origin
// param_2 - ptr patch table array
// param_3 - patch table array size
void FUN_800326b4(int param_1,int *param_2,int param_3)

{
  int *piVar1;
  int *piVar2;

  //get ptrEnd
  piVar2 = param_2 + param_3;

  //basically if patch table array length > 0
  if (param_2 < piVar2) {
    do {
      //get next ptr to fix
      piVar1 = (int *)((*param_2 >> 2) * 4 + param_1);
      //for loop increment
      param_2 = param_2 + 1;
      //fix pointer
      *piVar1 = *piVar1 + param_1;
      //while not reached the end of the array
    } while (param_2 < piVar2);
  }
  return;
}


// LOAD_Robots2P
// and load MPK for AI models
// param_1 bigfile
// param_2 = P1 Character ID
// param_3 = P2 Character ID
// param_4 = load driver callback
void FUN_80032700(undefined4 param_1,uint param_2,uint param_3,undefined4 param_4)
{
  // There are 28 bytes, 7 sets of 4 bytes,
  // for any combination of 4 characters
  // that can be chosen in 2P race. It loops
  // through every combination of 4 racers
  // until it finds one that doesn't have
  // a character ID chosen by the players

  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;

  iVar4 = 0;
  pbVar6 = &DAT_80083a54;
  iVar5 = 0;

  // Idk why they chose to do it this way...

  // Continue looping until all 6 characters
  // all have different character IDs.
  while( true ) {
    bVar1 = false;
    iVar2 = iVar5;

	// Keep count of AI index (0-3) for 4 AIs
    iVar3 = 0;

    do
	{
	  // if the characters you chose, match any AIs
      if ((param_2 == (uint)(byte)(&DAT_80083a54)[iVar2]) ||
         (param_3 == (uint)(byte)(&DAT_80083a54)[iVar2]))
	  {
		// remember that you failed
        bVar1 = true;
      }

	  // increment AI index counter
      iVar3 = iVar3 + 1;

	  // quit after...
    } while (
				// you've gotten through 4 AIs
				(iVar3 < 4) &&

				(
					// check the next set of 4 AIs
					iVar2 = iVar3 + iVar5,

					!bVar1
				)
			);

	// If there are no repeating Character IDs
	// Leave the loop
	if (!bVar1) break;

	// if you are here, then the list of 4 AIs,
	// wont work cause one of them is a player

	// check the next set of 4 AIs
    pbVar6 = pbVar6 + 4;
    iVar5 = iVar5 + 4;

	// increment number of fails
    iVar4 = iVar4 + 1;

	// if it failed to find 4 AIs in a row,
	// that doesn't have player characters,
	// more than 6 times...
    if (6 < iVar4)
	{
	  // Aug 5
	  //FUN_8006fbac("ERROR: Didn\'t find a suitable Robot4 Packet for Player1 = %d Player2 = %d!\n",
      //             param_2,param_3);

      return;
    }
  }

  // by this point, we must have
  // 4 AIs in a row that do not
  // match a character that the player chose

  // Set Character ID 3 -- 1st AI
  DAT_80086e88 = (ushort)*pbVar6;

  // Set Character ID 4 -- 2nd AI
  DAT_80086e8a = (ushort)pbVar6[1];

  // Set Character ID 5 -- 3rd AI
  DAT_80086e8c = (ushort)pbVar6[2];

  // Set Character ID 6 -- 4th AI
  DAT_80086e8e = (ushort)pbVar6[3];

  //add to load queue from range 324=packs\2P_arcade\*.mpk
  FUN_80032d30(param_1,2,iVar4 + 0x144,0,param_4);
  return;
}


// LOAD_Robots1P
// param_1 will always be P1 Character ID
void FUN_800327dc(int param_1)
{
  // Set P1 Character ID to P1 Character ID (kinda pointless)
  DAT_80086e84 = (undefined2)param_1;

  // Boolean for loop
  bool bVar1 = true;

  // Character ID to give to array index.
  // Start with ID 0 (crash bandicoot)
  int iVar2 = 0;

  // Index of Character ID array,
  // to give Character ID to.
  // Start with index 1 (first AI)
  int iVar4 = 1;

  // Pointer to Unsigned Short Address
  // where character ID will be set
  undefined2 *puVar3;

  // Set pointer to P2 Character ID
  puVar3 = &DAT_80086e86;

  do {

	// Quit the loop if this is false
    if (!bVar1) {
      return;
    }

	// If iVar2 != P1 Character ID
	// Meaning: Dont set an AI Character ID to P1's Character ID
    if (iVar2 != param_1) {

	  // Set Character ID to iVar2
      *puVar3 = (short)iVar2;

	  // Go to next index in Short Array
      puVar3 = puVar3 + 1;

	  // Keep count of how many AIs you've set
      iVar4 = iVar4 + 1;
    }

	// Go to next character ID value
	// 0 - Crash
	// 1 - Cortex
	// 2 - Tiny
	// etc
    iVar2 = iVar2 + 1;

	// Stop the loop when all 7 AIs are set
    bVar1 = iVar4 < 8;

	// Stop the loop when a character ID
	// is a secret character (should never happen)
  } while (iVar2 < 8);

  // Leave the function
  return;
}


// LOAD_DriverMPK
void FUN_8003282c(undefined4 param_1,int param_2,undefined4 param_3)

{
  uint uVar1;

  // 3P or 4P (because of unsigned)
  if (param_2 - 3U < 2)
  {
	//add to load queue 3 files from range 332=models\racers\low\*.ctr
	//add to load queue 1 file from range 348=packs\4player\*.mpk
	// second param '2' means load dram
    FUN_80032d30(param_1,2,(int)DAT_80086e84 + 0x14c,&DAT_80083a10,0xfffffffe);
    FUN_80032d30(param_1,2,(int)DAT_80086e86 + 0x14c,&DAT_80083a14,0xfffffffe);
    FUN_80032d30(param_1,2,(int)DAT_80086e88 + 0x14c,&DAT_80083a18,0xfffffffe);
    FUN_80032d30(param_1,2,(int)DAT_80086e8a + 0x15c,0,param_3);

    return;
  }

  if (
		// If there is only 1 player
		(param_2 == 1) &&

		(
			// assigns main struct flags to local var
			uVar1 = *(uint *)PTR_DAT_8008d2ac,

			// If not in time trial
			(uVar1 & 0x22000) != 0x20000)
		)
  {
    if (
		(
			// 2 is for cutscene
			// 1 is for If you're in Adventure Arena
			((uVar1 & 0x20100000) != 0) ||

			// if going to credits
			((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x80) != 0)
		) ||

		// If level ID is 40
		// If you are in Adventure Character Select Screen
		(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x28)
	   )
	{
	  //add to load queue from range 276=packs\1P_adventure\*.mpk
	  // second param '2' means load dram
      FUN_80032d30(param_1,2,(int)DAT_80086e84 + 0x114,0,param_3);

      return;
    }

	// if not a boss race
    if (-1 < (int)uVar1) {
      if (
			// If you are in Adventure cup
			((uVar1 & 0x10000000) != 0) &&

			// If this is the purple gem cup
			(*(int *)(PTR_DAT_8008d2ac + 0x1e58) == 4)
		 )
	  {
		//add to load queue from range 242=models\racers\hi\*.ctr
		//basically load hi model for P1
		// second param '2' means load dram
        FUN_80032d30(param_1,2,(int)DAT_80086e84 + 0xf2,&DAT_80083a10,0xfffffffe);

		// add to load queue fixed 331=packs\1P_gem_cups\331_bosses.mpk
		// second param '2' means load dram
        FUN_80032d30(param_1,2,0x14b,0,param_3);

		// Purple Gem Cup

		// Set P2 to Ripper Roo
        DAT_80086e86 = 10;

		// Set P3 to Papu Papu
        DAT_80086e88 = 9;

		// Set P4 to Komodo Joe
        DAT_80086e8a = 0xb;

		// Set P5 to Pinstripe
        DAT_80086e8c = 8;

        return;
      }

	  // If you got this far, the code has already determined
	  // That you are in 1P Mode

	  // If not in main menu
      if ((*(uint *)PTR_DAT_8008d2ac & 0x22000) != 0x2000) {

		// Calculate AI Character IDs for 1P Arcade
        FUN_800327dc((int)DAT_80086e84);
      }

	  // add to load queue from range 260=packs\1P_arcade\*.mpk
	  // second param '2' means load dram
      FUN_80032d30(param_1,2,(int)DAT_80086e84 + 0x104,0,param_3);

      return;
    }
  }
  else
  {
	// If you are in 2P mode
    if (
			(param_2 != 8) &&


			// If you're not in Time Trial
			((*(uint *)PTR_DAT_8008d2ac & 0x20000) == 0)
		)
	{
	  // add to load queue from range 308=models\racers\med\*.ctr
	  // second param '2' means load dram
      FUN_80032d30(param_1,2,(int)DAT_80086e84 + 0x134,&DAT_80083a10,0xfffffffe);
      FUN_80032d30(param_1,2,(int)DAT_80086e86 + 0x134,&DAT_80083a14,0xfffffffe);

	  // Calculate AI character IDs with the character IDs that players chose,
	  // then load MPK with the models of those AIs
      FUN_80032700(param_1,(int)DAT_80086e84,(int)DAT_80086e86,param_3);

      return;
    }
  }

  // For Time Trial, Relic Race, and Boss Race

  // add to load queue from range 242=models\racers\hi\*.ctr
  // second param '2' means load dram
  FUN_80032d30(param_1,2,(int)DAT_80086e84 + 0xf2,&DAT_80083a10,0xfffffffe);

  // add to load queue from range 292=packs\1P_timetrial\*.mpk
  // second param '2' means load dram
  FUN_80032d30(param_1,2,(int)DAT_80086e86 + 0x124,0,param_3);

  return;
}



// LOAD_LangFile
// param_1 - Pointer to "cd position of bigfile"
// param_2 - language index - 0 ja, 1 en, 2 en2, 3 fr, 4 de, 5 it, 6 es, 7 ne
void FUN_80032b50(undefined4 param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined auStack24 [8];

  // allocate buffer, if null
  if (DAT_8008d858 == 0) 
  {
	// MEMPACK_AllocMem
    DAT_8008d858 = FUN_8003e874(DAT_8008cf6c,"lang buffer");
  }

  // piVar1 will equal DAT_8008d858 if load succeeds
  // FUN_800321b4 is called LOAD_ReadFile in earlier builds
  piVar1 = (int *)FUN_800321b4(param_1,1,param_2 + 0xea,DAT_8008d858,auStack24,0);

  // if file read successful
  if (piVar1 != (int *)0x0)
  {
    iVar4 = *piVar1;
    iVar2 = (int)piVar1 + piVar1[1];
    iVar5 = 0;
    DAT_8008d110 = iVar4; // number of strings in lng file
    DAT_8008d878 = iVar2; // pointer to string pointer array

	// if have strings to process
    if (0 < iVar4) {
		// make every string pointer absolute
		// this is actually a for loop, ivar5 is increment
      do {
        piVar3 = (int *)(((iVar5 << 0x10) >> 0xe) + iVar2); // basically, (pointer to array + increment * 4)
        iVar5 = iVar5 + 1;
        *piVar3 = *piVar3 + (int)piVar1;
      } while (iVar5 * 0x10000 >> 0x10 < iVar4); // index converted to short (2 bytes)
    }
  }
  return;
}


//returns file index in bigfile according to params
// param1 is level ID
// param2 is LOD number
// param3 is vram/lev/ptr selector.
int FUN_80032c24(uint param_1,int param_2,int param_3)
{
  // If Level ID is 0 - 17, if level_id is a race track - 18 in total
  if (param_1 < 0x12) {
    return param_1 * 8 + (uint)(byte)(&DAT_8008d0b4)[param_2-1] + param_3;
  }

  // If Level ID is 19 - 24, if level_id is a battle map - 7 in total
  if (param_1 - 0x12 < 7) {
    return (param_1 - 0x12) * 8 + (uint)(byte)(&DAT_8008d0b4)[param_2-1] + param_3 + 0x90;
  }

  // one of the intro cutscenes, 9 in total
  if (param_1 - 0x1e < 9) {
    return (param_1 - 0x1e) * 3 + param_3 + 0x203;
  }

  // other 2 oxide cutscenes, 2 in total
  if (param_1 - 0x2a < 2) {
    return (param_1 - 0x2a) * 2 + param_3 + 0x21e;
  }

  //adv_player_select, main menu lev
  if (param_1 == 0x28) {
    return param_3 + 0xd9;
  }

  //intro_box, intro box lev
  if (param_1 == 0x29) {
    return param_3 + 0x201;
  }

  // if credits, 20 in total (all chars + 4 trophy girls)
  if (param_1 - 0x2c < 0x14) {
    return (param_1 - 0x2c) * 3 + param_3 + 0x222;
  }

  // menu_models, chars and kart for adventure select screen
  if (param_1 == 0x27) {
    return param_3 + 0xd7;
  }

  // 0x19 - 0x1d are adventure hubs
  // if hub, 5 in total
  
  // if not scrapbook
  if (param_1 != 0x40) {
    return (param_1 - 0x19) * 3 + param_3 + 200;
  }

  // scrapbook
  return param_3 + 0x25e;
}



// LOAD_AppendQueue
// param1 is always the Pointer to "cd position of bigfile"
// param2 is type, 1 for readfile, 2 for dram, 3 for vram
// param3 is the index of the subfile within BIGFILE
// param4 is ptrDestination. If null, destination is Mempack_AllocMem
// param5 is callbackFuncPtr
void FUN_80032d30(undefined4 param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5)
{
  int iVar1;

  //read queue length
  iVar1 = (int)DAT_8008d0a2;

  //if we have less than 8 files in the queue
  if (iVar1 < 8) {

    // sizeof(LoadQueueSlot) = 24 bytes
	// the array is at 80096344
    *(undefined2 *)(&DAT_80096348 + iVar1 * 6) = 0;
    (&DAT_80096344)[iVar1 * 6] = param_1;	// Pointer to "cd position of bigfile"

	// param2 is type, 1 for readfile, 2 for dram, 3 for vram
    *(undefined2 *)((int)&DAT_80096348 + iVar1 * 0x18 + 2) = param_2;

	// index of subfile within BIGFILE
    (&DAT_8009634c)[iVar1 * 6] = param_3;

	// ptrDestination, if null, will be
	// set to Mempack_AllocMem
    (&DAT_80096350)[iVar1 * 6] = param_4;

	// size is set to zero, because size gets
	// written while loading queue executes,
	// it pulls from bigfile header
    (&DAT_80096354)[iVar1 * 6] = 0;

	// callback funcPtr
    (&DAT_80096358)[iVar1 * 6] = param_5;

	//increase queue length
    DAT_8008d0a2 = DAT_8008d0a2 + 1;
  }
  return;
}

// LOAD_CDRequestCallback
void FUN_80032d8c(int param_1)

{
  // Sep 3
  // printf("LOAD_CDRequestCallback\n");

  if (*(code **)(param_1 + 0x14) != (code *)0x0) {
    (**(code **)(param_1 + 0x14))();
  }

  // ready to load next file
  DAT_8008d0a0 = 1;

  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// LOAD_NextQueuedFile
// cycles through loading queue and executes, not sure how though
void FUN_80032dc0(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;

  if (
		(
			// if queue is ready to load next file
			(DAT_8008d0a0 != '\0') &&
			(DAT_8008d708 == 0)
		) &&

		// if you have requests in your loading queue
		(DAT_8008d0a2 != 0)
	  )
  {
	// queue is not ready for next file, after this one
    DAT_8008d0a0 = '\0';

    iVar3 = 1;

	// if this is not a retry attempt of previous load,
	// then read the next file in the queue
    if (DAT_8008d0a1 == '\0')
	{
	  // Copy the first element of the queue
	  // into temporary addresses where it can be executed

	  // These 6 lines can be simplifed to
	  // 	memcpy(0x80083a3c, 0x80096344, 24);

      DAT_80083a3c = DAT_80096344;
      DAT_80083a40 = DAT_80096348;
      DAT_80083a44 = DAT_8009634c;
      DAT_80083a48 = DAT_80096350;
      DAT_80083a4c = DAT_80096354;
      DAT_80083a50 = DAT_80096358;

	  // if you have more than one request in the queue
      if (1 < DAT_8008d0a2)
	  {
        puVar2 = &DAT_8009635c;
        puVar1 = (undefined4 *)&DAT_8009632c;

		// for(iVar3 = 1; iVar3 < queueLength; iVar3++)
        do
		{
		  // shift members of the queue closer to the front

		  // These next 10 lines can be simplified to
		  //	memcpy(0x80096344 + (iVar3-1)*24, 0x80096344 + (iVar3)*24, 24);

          uVar4 = puVar2[1];
          uVar5 = puVar2[2];
          uVar6 = puVar2[3];
          puVar1[6] = *puVar2;
          puVar1[7] = uVar4;
          puVar1[8] = uVar5;
          puVar1[9] = uVar6;
          uVar4 = puVar2[5];
          puVar1[10] = puVar2[4];
          puVar1[0xb] = uVar4;

		  // increment pointer counter
          iVar3 = iVar3 + 1;
          puVar2 = puVar2 + 6;
          puVar1 = puVar1 + 6;
        } while (iVar3 < DAT_8008d0a2);
      }
    }

	// if it is a retry
	else
	{
	  // erase retry variable,
	  // it will be set back to 1 if it fails again
      DAT_8008d0a1 = '\0';
    }
    if (DAT_80083a42 == 2)
	{
					// LOAD_DramFile
		// DAT_80083a3c eventually changes back to BIGFILE, not queue ptr
      DAT_80083a48 = FUN_80031e00(DAT_80083a3c,DAT_80083a44,DAT_80083a48,&DAT_80083a4c,DAT_80083a50);
    }
    else {
      if (DAT_80083a42 < 3) {
        if (DAT_80083a42 == 1)
		{
						// LOAD_ReadFile
		  // DAT_80083a3c eventually changes back to BIGFILE, not queue ptr
          DAT_80083a48 = FUN_800321b4(DAT_80083a3c,1,DAT_80083a44,DAT_80083a48,&DAT_80083a4c,
                                      FUN_80032d8c);
        }
      }
      else {
        if (DAT_80083a42 == 3)
		{
						// LOAD_VramFile
		  // DAT_80083a3c eventually changes back to BIGFILE, not queue ptr
          DAT_80083a48 = FUN_80031fdc(DAT_80083a3c,DAT_80083a44,DAT_80083a48,&DAT_80083a4c,
                                      DAT_80083a50);
        }
      }
    }

	// subtract from queue length
    DAT_8008d0a2 = DAT_8008d0a2 + -1;
  }
  if (
		// if a timer exists
		(DAT_8008d0a8 != 0) &&

		// if two frames have passed since the file finished loading
		(2 < (uint)(*(int *)(PTR_DAT_8008d2ac + 0x1ce4) - DAT_8008d0a8))
	 )
  {

	// When each element is added to loading queue, it has
	// the option of having a function pointer to be called
	// as a callback when the element is done loading

	// if this function pointer is not nullptr
	if (DAT_80083a50 != (code *)0x0)
	{
	  // execute the function pointer
      (*DAT_80083a50)(&DAT_80083a3c);
    }

	// reset timer
    DAT_8008d0a8 = 0;

	// If we used MEMPACK_AllocMem,
	// rather than some other place
	// to store Readfile
    if ((_DAT_80083a40 & 1) != 0) {

	  // MEMPACK_PopState
      FUN_8003e9d0();
    }

	// ready to load next file
    DAT_8008d0a0 = '\x01';
  }
  return;
}


// LOAD_Hub_ReadFile
// param1 is the Pointer to "cd position of bigfile"
// param2 is levID to load
// param3 is mem allocator ID
void FUN_80032ffc(undefined4 param_1,int param_2,int param_3)

{
  undefined *puVar1;
  undefined4 uVar2;

  // If this sub-mempack does not already have this LEV loaded, then load it
  if ((int)*(short *)(PTR_DAT_8008d2ac + param_3 * 2 + 0x254c) != param_2)
  {
	// erase mask hint model pointer,
	// different hubs need different mask
    DAT_8008d0f0 = 0;

	// change active allocation
    FUN_8003e80c(param_3);

	// MEMPACK_ClearLowMem
    FUN_8003e9b8();

	puVar1 = PTR_DAT_8008d2ac;

	// game is now loading
    DAT_8008d0a4 = 1;

	// clear pointer to secondary LEV (for adv hub)
    *(undefined4 *)(PTR_DAT_8008d2ac + 0x164) = 0;

    *(short *)(puVar1 + param_3 * 2 + 0x254c) = (short)param_2;

	// Get index of VRAM sub-file within BIGFILE, given Level ID and LOD number
    uVar2 = FUN_80032c24(param_2,1,0);

	// param1 is the Pointer to "cd position of bigfile"
	// var2 is the subfile index within BIGFILE
	// add to loading queue
	// second parameter '3' means vram
    FUN_80032d30(param_1,3,uVar2,0,0);

	// Get index of LEV sub-file within BIGFILE, given Level ID and LOD number
	uVar2 = FUN_80032c24(param_2,1,1);

	// param1 is the Pointer to "cd position of bigfile"
	// var2 is the subfile index within BIGFILE
	// add to loading queue
	// second parameter '2' means dram
	FUN_80032d30(param_1,2,uVar2,0,&FUN_80031a78);

	// Get index of sub-file within BIGFILE, given Level ID and LOD number
	uVar2 = FUN_80032c24(param_2,1,2);

	// param1 is the Pointer to "cd position of bigfile"
	// var2 is the subfile index within BIGFILE
	// 8008d090 = highMem PatchTable
	// add to loading queue
	// Call LOAD_HubCallback when this is done
	// second parameter '1' means readfile
	FUN_80032d30(param_1,1,uVar2,DAT_8008d090,FUN_80031b14);
  }
  return;
}


// LOAD_Hub_SwapNow
void FUN_80033108(void)

{
  undefined *puVar1;
  int iVar2;

  // 8008d2ac + 0x164 is set as soon as
  // LOAD_HubCallback is executed, and it
  // is set to zero when loading a hub begins

  // This infinitely waits until the next
  // hub is finished loading

  iVar2 = *(int *)(PTR_DAT_8008d2ac + 0x164);
  while (iVar2 == 0)
  {
	// LOAD_NextQueuedFile
	// execute loading queue
    FUN_80032dc0();

    VSync(0);
    iVar2 = *(int *)(PTR_DAT_8008d2ac + 0x164);
  }

  // Aug 5
  // FUN_8006fbac("gGT->level2 = 0x%08x\n",*(undefined4 *)(PTR_DAT_8008d2ac + 0x164));
  // FUN_8006fbac("SWAPPING 1...\n");

  // LevInstDef_RePack
  // also erase any threads attached to instances
  FUN_80031268(**(undefined4 **)(PTR_DAT_8008d2ac + 0x160),1);

  // Aug 5
  // FUN_8006fbac("SWAPPING 2...\n");

  // LOAD_HubSwapPtrs
  FUN_80031bdc(PTR_DAT_8008d2ac,1);

  puVar1 = PTR_DAT_8008d2ac;

  // This actually does the swapping
  // If it is 1, make it 2
  // If it is 2, make it 1
  *(short *)(PTR_DAT_8008d2ac + 0x254a) = 3 - *(short *)(PTR_DAT_8008d2ac + 0x254a);

  // make a backup of your levelID before exiting the level,
  // this is used to help you return to an adventure hub after finishing a race
  *(undefined4 *)(puVar1 + 0x1eb4) = *(undefined4 *)(puVar1 + 0x1a10);

  // Set Level ID
  *(int *)(puVar1 + 0x1a10) =
       (int)*(short *)(puVar1 + (int)*(short *)(puVar1 + 0x254a) * 2 + 0x254c);

  // Audio_AdvHub_SwapSong
  FUN_8002d50c(puVar1 + 0x1a10);

  // Aug 5
  // FUN_8006fbac("SWAPPING 3...\n");

  // Clear all model pointers
  FUN_800314c0(PTR_DAT_8008d2ac);

  /*
  In Aug 5
  if (DAT_8008d870 == 0)
  {
    printf("ERROR: No PLYROBJECTLIST!\n");
  }
  */

  // if PLYROBJECTLIST is valid
  if (DAT_8008d870 != 0)
  {
	// LOAD_GlobalModelPtrs_MPK
    FUN_80031b50();
  }

  // Get next level
  iVar2 = *(int *)(PTR_DAT_8008d2ac + 0x160);

  /*
  In Aug 5
  if(iVar2 == 0)
  {
     printf("ERROR: No LEVEL!\n");
  }
  */

  // If you have a level
  if (iVar2 != 0)
  {
	// store array of model pointers in GameTracker
    FUN_8003147c(PTR_DAT_8008d2ac,*(undefined4 *)(iVar2 + 0x14),*(undefined4 *)(iVar2 + 0x18));

	// INSTANCE_LevInitAll
	// copy InstDef to InstancePool
	FUN_80030ad4(*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x10),
                 *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xc));

	// LevInstDef_UnPack
	FUN_8003116c(**(undefined4 **)(PTR_DAT_8008d2ac + 0x160));

	// DecalGlobal_Store
	// Load Icons and IconGroups from LEV
    FUN_80022bdc(PTR_DAT_8008d2ac,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x3c));
  }

  // change active allocation system
  // swap 1 and 2 during adventure mode
  FUN_8003e80c((int)*(short *)(PTR_DAT_8008d2ac + 0x254a));

  // MainInit_VisMem
  FUN_8003af84(PTR_DAT_8008d2ac);

  puVar1 = PTR_DAT_8008d2ac;

  // called VISMEM in prototypes
  iVar2 = *(int *)(PTR_DAT_8008d2ac + 0x1a38);

  // quadblock under the camera
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x14b4) = 0;

  // clear VisMem inside camera
  *(undefined4 *)(puVar1 + 0x14c0) = 0;
  *(undefined4 *)(puVar1 + 0x14b8) = 0;
  *(undefined4 *)(puVar1 + 0x14bc) = 0;
  *(undefined4 *)(puVar1 + 0x14c4) = 0;
  *(undefined4 *)(puVar1 + 0x14c8) = 0;

  // clear VisMem SRC pointers
  *(undefined4 *)(iVar2 + 0x40) = 0;
  *(undefined4 *)(*(int *)(puVar1 + 0x1a38) + 0x50) = 0;
  *(undefined4 *)(*(int *)(puVar1 + 0x1a38) + 0x60) = 0;
  *(undefined4 *)(*(int *)(puVar1 + 0x1a38) + 0x70) = 0;

  // uadblock under driver
  *(undefined4 *)(*(int *)(puVar1 + 0x24ec) + 0x350) = 0;

  *(undefined4 *)(puVar1 + 0x1cfc) = 0;
  *(undefined4 *)(puVar1 + 0x1d00) = 0;
  return;
}


// LOAD_Hub_Main
// check if secondary lev needs
// to load, or swap, param given is bigfile
void FUN_80033318(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 local_50 [16];

  // copy array from RAM onto Stack
  puVar1 = &DAT_80011180;
  puVar2 = local_50;
  do {
    puVar4 = puVar2;
    puVar3 = puVar1;
    uVar6 = puVar3[1];
    uVar7 = puVar3[2];
    uVar8 = puVar3[3];
    *puVar4 = *puVar3;
    puVar4[1] = uVar6;
    puVar4[2] = uVar7;
    puVar4[3] = uVar8;
    puVar1 = puVar3 + 4;
    puVar2 = puVar4 + 4;
  } while (puVar3 + 4 != (undefined4 *)&DAT_800111b0);

  uVar6 = puVar3[5];
  uVar7 = puVar3[6];
  puVar4[4] = 0x1c;
  puVar4[5] = uVar6;
  puVar4[6] = uVar7;

  // loop counter
  iVar9 = 0;

  // if numPlyrCurrGame is not zero
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0') {

    // for(int iVar9 = 0; iVar9 < numPlyrCurrGame; iVar9++)
    do
	{
	  // if game is not loading
      if (DAT_8008d0f8 == -1)
	  {
		// can be 0,1,2,3
		// 0: dont need to load hub
		// 1-3: index of which hub connects to this one
        iVar5 =

			// pointer to address of each player structure
			(int)(*(uint *)(*(int *)(PTR_DAT_8008d2ac + iVar9 * 4 + 0x24ec)

			// if need to load new lev
			+ 0xbc) & 0x30) >> 4;

		// if new lev does not need to load
        if (iVar5 == 0)
		{
          if (
				((int)(*(uint *)(*(int *)

					// pointer to address of each player structure
					(PTR_DAT_8008d2ac + iVar9 * 4 + 0x24ec)

						// if player needs to swap hub (adv)
						+ 0xbc) & 0xc0) >> 6 != 0)
				||

				// if you need to swap LEVs (global, like oxide intro)
				(PTR_DAT_8008d2ac[0x2574] != '\0')
			 )
		  {
			// reset bool
            PTR_DAT_8008d2ac[0x2574] = 0;

			// LOAD_Hub_SwapNow
            FUN_80033108();
          }
        }

		// if new lev needs to load
        else {

		  // if Level ID is somewhere on adventure arena
          if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x19U < 5)
		  {
			// LOAD_Hub_ReadFile
            FUN_80032ffc(
							// param1 always DAT_8008d86c
							param_1,

							// levID from the array of hubs that connect to this one
							local_50[

								// Level ID (0 - 5) of adventure map, * 3
								(*(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x19U) * 3 + iVar5 + -1
							],

							// memory allocator ID (1 or 2)
							3 - (int)*(short *)(PTR_DAT_8008d2ac + 0x254a)
                        );
          }
        }
      }

	  // increment loop counter
      iVar9 = iVar9 + 1;

					// numPlyrCurrGame
    } while (iVar9 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
  }
  return;
}

// param1 alter which DLL loads
// DLL = 225 + param_1
void FUN_80033474(int param_1)

{
  // if overlayIndex_LOD needs reloading
  if ((uint)(byte)PTR_DAT_8008d2ac[0x2540] != param_1 - 1U)
  {
	// game is now loading
    DAT_8008d0a4 = 1;

	// Load DLL
	// add to load queue from range 225 (param1 + 0xe1)
	// DAT_8008d09c is the Pointer to "cd position of bigfile"
	// second parameter '1' means readfile
    FUN_80032d30(DAT_8008d09c,1,param_1 + 0xe1,&DAT_800a0cb8,&FUN_800319e8);

	// overlayIndex_LOD loaded
	PTR_DAT_8008d2ac[0x2540] = (char)(param_1 - 1U);

	// force overlayIndex_Threads to reload
    PTR_DAT_8008d2ac[0x2541] = 0xff;
  }
  return;
}

// param1 alter which DLL loads
// DLL loaded = param_1 + 221
void FUN_800334f4(uint param_1)

{
  // if overlayIndex_EndOfRace needs reloading
  if ((uint)(byte)PTR_DAT_8008d2ac[0x2543] != param_1)
  {
	// game is now loading
    DAT_8008d0a4 = 1;

	// Load DLL
	//add to load queue from range 221 (param1 + 0xdd)
	// DAT_8008d09c is the Pointer to "cd position of bigfile"
	// second parameter '1' means readfile
    FUN_80032d30(DAT_8008d09c,1,param_1 + 0xdd,&DAT_8009f6fc,&FUN_800319e8);

	// save new overlayIndex_EndOfRace
	PTR_DAT_8008d2ac[0x2543] = (char)param_1;

	// force LOD overlay to reload,
	// by nullifying the saved index
    PTR_DAT_8008d2ac[0x2540] = 0xff;
  }
  return;
}

// param1 alter which DLL loads
// DLL loaded = param_1 + 230
void FUN_80033570(uint param_1)

{
  // if overlayIndex_Threads needs reloading
  if ((uint)(byte)PTR_DAT_8008d2ac[0x2541] != param_1)
  {
	// game is now loading
    DAT_8008d0a4 = 1;

	// do not save overlayIndex_Threads,
	// the value will be written in a callback
	PTR_DAT_8008d2ac[0x2541] = 0xff;	// but why? why not do it here?

	// Load DLL to 0xab9f0
	// add to load queue from range 230 (param1 + 0xe6)
	// DAT_8008d09c is the Pointer to "cd position of bigfile"
	// second parameter '1' means readfile
    FUN_80032d30(DAT_8008d09c,1,param_1 + 0xe6,&DAT_800ab9f0,(&PTR_FUN_80083a70)[param_1]);
  }
  return;
}


// Get Memory Allocation System Index
undefined4 FUN_800335dc(void)

{
  if (
		// Level ID != 25
		// Not on GemStone Valley
		(*(int *)(PTR_DAT_8008d2ac + 0x1a10) != 0x19) &&

		// Level ID != 28
		// Not on Glacier Park
		(*(int *)(PTR_DAT_8008d2ac + 0x1a10) != 0x1c)
     )
  {
    return 1;
  }
  return 2;
}

// case 0 - splashscreens / cutscenes
// case 1 - overlay level1
// case 2 - overlay level2
// case 3 - overlay level3
// case 4 - leave main menu, load drivers
// case 5 - model pointers (2160)
// case 6 - load LEV
// case 7 - load icons and models from LEV
// case 8 - adventure swap hubs
// case 9 - enable loading screen (checkered flag)

// LOAD_TenStages
// param_1 is gGT
// param_2 is loading stage
// param_3 is the Pointer to "cd position of bigfile"
int FUN_80033610(undefined4 param_1,int param_2,undefined4 param_3)

{
  byte *pbVar1;
  undefined uVar2;
  undefined *puVar3;
  short sVar4;
  int iVar5;
  undefined4 uVar6;
  code *pcVar7;
  undefined4 *puVar8;
  int iVar9;
  uint uVar10;
  byte bVar11;
  int iVar12;
  char *pcVar13;
  undefined *puVar14;
  int *piVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined auStack40 [8];

  puVar3 = PTR_DAT_8008d2ac;

  // pointer to LEV
  iVar9 = DAT_8008d08c;

  // if game is loading
  if (DAT_8008d0a4 != 0) {
    return param_2;
  }

  // if game is not loading, continue

  switch(param_2) {
  case 0:

	// if level is not in range of 0x28 and 0x28+1,
	// if level is not AdvGarage or Naughty Dog Box Scene
    if (1 < *(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x28U)
	{
	  // Cutscene_VolumeBackup
      FUN_8002c18c();
    }

	// CDSYS_XAPauseRequest
    FUN_8001cf98();

	// if you've already drawn intro frames
	// "sony computer entertainment" + "copyright page"
    if (DAT_8008d0bc == 0)
	{
	  // change active allocation system to #1
	  // used for whole game (except adventure arena)
      FUN_8003e80c(0);

	  // FUN_8003c1d4 converts string to level ID
	  // "proto8" -> 0 (dingo canyon)
	  // "proto9" -> 1 (dragon mines)
	  // "desert2" -> 2 (blizard bluff)
	  // "island1" -> 3 (crash cove)
	  // etc

	  // DAT_8008d83e = Get Level ID from String
      DAT_8008d83e = FUN_8003c1d4(PTR_DAT_8008d2ac + 0x1a14);

	  // erase all memory past this bookmark
      FUN_8003ea08(DAT_8008d098);
    }

	// if you have not drawn the intro frames yet
    else
	{
	  // Record that you've seen the logos,
	  // so that you do not see them again
      DAT_8008d0bc = 0;

	  // Load Intro TIM for Sony Presents from VRAM file
	  // Add a bookmark before loading (param_3 is 0 in the call)
      FUN_80031fdc(param_3,0x1fe,0,auStack40,0xffffffff);

	  // refresh screen during Intro
      FUN_8003c310();

	  // set isbg of both DBs to false
      PTR_DAT_8008d2ac[0x30] = 0;
      PTR_DAT_8008d2ac[0xd4] = 0;
    }

    puVar3 = PTR_DAT_8008d2ac;

	// Turn off HUD
    PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xfe;

    puVar14 = PTR_DAT_8008d2ac;

	// disable all rendering except loading screen
	*(uint *)(puVar3 + 0x256c) = *(uint *)(puVar3 + 0x256c) & 0x1000;

    puVar14[0x1d31] = puVar14[0x1d31] & 0xf7;
    puVar3 = PTR_DAT_8008d2ac;

	// uvar2 = number of players
    uVar2 = PTR_DAT_8008d2ac[0x1ca9];

	// set pointer of current LEV to zero
    *(undefined4 *)(PTR_DAT_8008d2ac + 0x160) = 0;

	// set pointer of 2nd LEV (used in adv hub) to zero
    *(undefined4 *)(puVar3 + 0x164) = 0;

	// set numPlyrCurrGame to number of players
    puVar3[0x1ca8] = uVar2;

	// copy level name into global string
	strcpy(PTR_DAT_8008d2ac + 0x1a14,
           (&PTR_s_proto8_80083a84)[*(int *)(PTR_DAT_8008d2ac + 0x1a10) * 6]);

	// add a bookmark, the index of the bookmark is
	// saved into 0x8d098, which is used to erase later
    DAT_8008d098 = FUN_8003e978();

	DrawSync(0);
    puVar3 = PTR_DAT_8008d2ac;

	// no overlay transition
	PTR_DAT_8008d2ac[0x2579] = 0;

    puVar14 = PTR_DAT_8008d2ac;
    pcVar13 = PTR_DAT_8008d2ac + 0x1a14;
    *(uint *)puVar3 = *(uint *)puVar3 & 0xdfcfdfff;
    *(uint *)(puVar3 + 8) = *(uint *)(puVar3 + 8) & 0xfffffe5f;

	// called VISMEM in prototypes
    *(undefined4 *)(puVar14 + 0x1a38) = 0;
    *(undefined4 *)(puVar14 + 0x1a3c) = 0;

	// DAT_8008d0c0
	// "ndi"
    iVar9 = strncmp(pcVar13,&DAT_8008d0c0,3);

    if (
			// If you're in Naughty Dog Box Scene
			(iVar9 == 0) ||
			(
				// s_ending_8008d0c4
				// "ending"
				iVar9 = strncmp(PTR_DAT_8008d2ac + 0x1a14,s_ending_8008d0c4,6),
				iVar9 == 0
			)
       ) {
      puVar3 = PTR_DAT_8008d2ac;
      pbVar1 = PTR_DAT_8008d2ac + 0x1d31;

	  // Enable cutscene flag (disable controls)
      *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | 0x20000000;

      puVar3[0x1d31] = *pbVar1 & 0xfe;
    }
    else
	{
	  // s_intro_8008d0cc
	  // "intro"
	  iVar9 = strncmp(PTR_DAT_8008d2ac + 0x1a14,s_intro_8008d0cc,5);

	  // pointer to main game structure
	  puVar3 = PTR_DAT_8008d2ac;

	  // if you are loading oxide intro cutscene (from main menu)
      if (iVar9 == 0)
	  {
		// Turn off HUD
        PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xfe;

        puVar14 = PTR_DAT_8008d2ac;
        *(uint *)puVar3 = *(uint *)puVar3 | 0x20000000;

		// lev swap will be needed
        *(uint *)(puVar14 + 8) = *(uint *)(puVar14 + 8) | 0x20;
      }

	  // if you are not loading oxide intro
      else
	  {
		// s_screen_8008d0d4
		// "screen"
        iVar9 = strncmp(PTR_DAT_8008d2ac + 0x1a14,s_screen_8008d0d4,6);

	  if (
			// if you are loading any menu of any kind
			(iVar9 == 0) ||
			(
				// s_garage_8008d0dc
				// "garage"
				iVar9 = strncmp(PTR_DAT_8008d2ac + 0x1a14,s_garage_8008d0dc,6),

				// if you are loading into adventure character selection screen
				iVar9 == 0
			)
		  )
		{
          puVar3 = PTR_DAT_8008d2ac;
          uVar10 = *(uint *)PTR_DAT_8008d2ac;

		  // Turn off HUD
          PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xfe;

          puVar14 = PTR_DAT_8008d2ac;

		  // enable flag that shows you are in main menu
          *(uint *)puVar3 = uVar10 | 0x2000;

		  // set number of players to numPlyrCurrGame
          puVar14[0x1ca9] = puVar14[0x1ca8];

		  // set numPlyrCurrGame to 4
		  // Either 4P mode or main menu
          PTR_DAT_8008d2ac[0x1ca8] = 4;

		  // s_garage_8008d0dc
		  // "garage"
          iVar9 = strncmp(PTR_DAT_8008d2ac + 0x1a14,s_garage_8008d0dc,6);

		  // if you are loading into character selection screen
          if (iVar9 == 0)
		  {
			// set numPlyrCurrGame to 1
            PTR_DAT_8008d2ac[0x1ca8] = 1;

			// Enter Adventure Character Selection
            DAT_8008d97c = 4;
          }
        }

		// if you are not loading menu or adventure character selection
		else {

		  // DAT_8008d0e4
		  // "hub"
          iVar9 = strncmp(PTR_DAT_8008d2ac + 0x1a14,&DAT_8008d0e4,3);

		  // pointer to main game structure
		  puVar3 = PTR_DAT_8008d2ac;

		  // if you are loading into adventure map:
		  // any of the hubs: "hub1", "hub2", etc
		  if (iVar9 == 0)
		  {
			// Set Number of Players to 1
            PTR_DAT_8008d2ac[0x1ca9] = 1;

			// set numPlyrCurrGame to 1
			puVar3[0x1ca8] = 1;

            puVar14 = PTR_DAT_8008d2ac;

			// Change mode to Adventure Arena
            *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | 0x100000;
            bVar11 = puVar14[0x1d31];

			// lev swap will be needed
            uVar10 = *(uint *)(puVar14 + 8) | 0x20;
          }

		  // if you are not loading adventure hub
		  else {

			// check to see if you are loading credits
            iVar9 = strncmp(PTR_DAT_8008d2ac + 0x1a14,s_credit_8008d0e8,6);

            puVar3 = PTR_DAT_8008d2ac;

			if (iVar9 != 0)
			{
			  // Turn off HUD
              PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xfe;
              goto LAB_80033a70;
            }

			// set Number of Players to 1
            PTR_DAT_8008d2ac[0x1ca9] = 1;

			// set numPlyrCurrGame to 1
            puVar3[0x1ca8] = 1;

            puVar14 = PTR_DAT_8008d2ac;

			// enable cutscene flag
            *(uint *)puVar3 = *(uint *)puVar3 | 0x20000000;

            bVar11 = puVar14[0x1d31];
			
			// lev swap (&20) and credits (&80)
            uVar10 = *(uint *)(puVar14 + 8) | 0xa0;
          }
          *(uint *)(puVar14 + 8) = uVar10;
          puVar14[0x1d31] = bVar11 & 0xfe;
        }
      }
    }
LAB_80033a70:

	// Enable HUD Instances
    PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] | 2;

	// Debug_ToggleNormalSpawn
    PTR_DAT_8008d2ac[0x253f] = 1;

	// Set LOD level to 1P level
    DAT_8008d83c = 1;

    if (
			// If not in main menu (character selection, track selection, any part of it)
			((*(uint *)PTR_DAT_8008d2ac & 0x2000) == 0) &&
			(
				// set LOD level to 8P level (does this exist??)
				DAT_8008d83c = 8,

				// if not loading, and not in time trial
				(*(uint *)PTR_DAT_8008d2ac & 0x4020000) == 0)
		)
	{
	  // Set LOD level to numPlyrCurrGame
	  DAT_8008d83c = (ushort)(byte)PTR_DAT_8008d2ac[0x1ca8];
    }

	// MainInit_PrimMem
    FUN_8003b0f0(PTR_DAT_8008d2ac);

	// MainInit_OTMem
    FUN_8003b334(PTR_DAT_8008d2ac);

	// 2 is for cutscene
	// 1 is for If you're in Adventure Arena
    if (((*(uint *)PTR_DAT_8008d2ac & 0x20100000) != 0) ||

		// if going to credits
       ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x80) != 0))
	{

	  // MainInit_JitPoolsNew
	  // (now, at beginning of mempack)
      FUN_8003b43c( /*PTR_DAT_8008d2ac*/ );

      return param_2 + 1;
    }
    break;
  case 1:

	// if XA has not paused yet,
	// since the request above,
	// due to IRQ not being hit yet
    if (DAT_8008d708 == 4)
	{
	  // quit, try again next frame
      return param_2;
    }

    uVar10 = *(uint *)PTR_DAT_8008d2ac;

	// If you're in Crystal Challenge (in adventure mode)
    if ((uVar10 & 0x8000000) != 0)
	{
	  // DLL 221 (221 + 0)
      uVar16 = 0;
LAB_80033bd8:

	  // Load 221 + uVar16
      FUN_800334f4(uVar16);
      return param_2 + 1;
    }

    // If you're in Time Trial
    if ((uVar10 & 0x20000) != 0)
	{
	  // DLL 224 (221 + 3)
      uVar16 = 3;

	  // Load 221 + uVar16
      goto LAB_80033bd8;
    }

	// If you're in Arcade Mode
    if ((uVar10 & 0x400000) != 0)
	{
	  // DLL 222 (221 + 1)
      uVar16 = 1;

	  // Load 221 + uVar16
      goto LAB_80033bd8;
    }

	// If you're in a Relic Race
    if ((uVar10 & 0x4000000) != 0)
	{
	  // DLL 223 (221 + 2)
      uVar16 = 2;

	  // Load 221 + uVar16
      goto LAB_80033bd8;
    }

	// If you're in Adventure Mode
	if ((uVar10 & 0x80000) != 0)
	{
	  // DLL 222 (221 + 1)
      uVar16 = 1;

	  // Load 221 + uVar16
      goto LAB_80033bd8;
    }

	// DLL 225 (221 + 4)
	uVar16 = 4;

	// If you are not in Arcade or VS cup				DLL 221 + uVar16
    if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) == 0) goto LAB_80033bd8;
    break;
  case 2:

	// 225 is for Naughty Dog Box

	// Load DLL 225 + numPlyrCurrGame
	// 226 - 229
    FUN_80033474((uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
    break;
  case 3:

	// If in main menu (character selection, track selection, any part of it)
    if (((*(uint *)PTR_DAT_8008d2ac & 0x2000) != 0) &&


       (
			// DLL 230 (230 + 0)
			uVar16 = 0,

			// LevelID != 40, not on adventure character selection
			*(int *)(PTR_DAT_8008d2ac + 0x1a10) != 0x28)
	   )
	{
LAB_80033ccc:
	  // Load DLL 230 + uVar6
      FUN_80033570(uVar16);
      return param_2 + 1;
    }

	// If you're in Adventure Arena
    if ((*(uint *)PTR_DAT_8008d2ac & 0x100000) != 0)
	{
	  // By default, load Podium DLL

	  // DLL 233 (230 + 3)
      uVar16 = 3;

	  // podium reward
      if (*(short *)(PTR_DAT_8008d2ac + 0x2572) == 0)
	  {
		// Load a different DLL

		// DLL 232 (230 + 2)
        uVar16 = 2;
      }

	  // Load DLL 230 + uVar16
      goto LAB_80033ccc;
    }

	// podium reward
    if ((((*(short *)(PTR_DAT_8008d2ac + 0x2572) != 0) ||

		  // If you are in a cutscene
         ((*(uint *)PTR_DAT_8008d2ac & 0x20000000) != 0)) ||

		// if going to credits
        ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x80) != 0)) ||

		// If LevelID is 40
		// If you're in Adventure Character Select Screen
       (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x28))
	{
	  // DLL 233 (230 + 3)
      uVar16 = 3;

	  // Load DLL 230 + uVar16
      goto LAB_80033ccc;
    }

	// DLL 231 (230 + 1)
    uVar16 = 1;
    if (PTR_DAT_8008d2ac[0x2541] != '\x01') goto LAB_80033ccc;
    break;
  case 4:

	// if level is not in range of 0x28 and 0x28+1,
	// if level is not AdvGarage or Naughty Dog Box Scene
    if (1 < *(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x28U)
	{
	  // Music_Restart
      FUN_8002e4c0();
    }

	// If in main menu (character selection, track selection, any part of it)
    if ((*(uint *)PTR_DAT_8008d2ac & 0x2000) != 0)
	{
	  // all these are 230 except
	  // for adv garage, 233

      switch(DAT_8008d97c)
	  {
	  // main menu
      case 0:
	    // MM_JumpTo_Title_FirstTime
        FUN_800b4364();
        break;

	  case 1:
	    // MM_JumpTo_Characters
        FUN_800b446c();
        break;

	  // track selection
	  case 2:
	    // MM_JumpTo_TrackSelect
        FUN_800b4430();
        break;

	  // battle selection
	  case 3:
	    // MM_JumpTo_BattleSetup
        FUN_800b43f4();
        break;

	  // Character Selection 3D (Adventure)
      case 4:
	    // CS_Garage_Init
        FUN_800b8558();
        break;

	  // scrapbook
      case 5:
		// MM_JumpTo_Scrapbook
        FUN_800b44a8(param_3);
      }
    }
    DAT_80083a10 = 0;
    DAT_80083a14 = 0;
    DAT_80083a18 = 0;
    DAT_8008d088 = (int *)0x0;

	// game is now loading
    DAT_8008d0a4 = 1;

	// LOAD_DriverMPK
	// 8008d83c = LOD level (num players, plus Time Trial flag)
    FUN_8003282c(param_3,(int)(short)DAT_8008d83c,&FUN_80031b00);
    break;
  case 5:

	// Clear all model pointers
    FUN_800314c0(PTR_DAT_8008d2ac);

	// set value of PLYROBJECTLIST,
	// the array of model pointers from MPK 
	// that was loaded in loading stage 4
    DAT_8008d870 = DAT_8008d088 + 1;
    if (DAT_8008d088 == (int *)0x0) {
      DAT_8008d870 = (int *)0x0;
    }

	// LOAD_GlobalModelPtrs_MPK
    FUN_80031b50();

	// DecalGlobal_Clear
    FUN_80022b9c(PTR_DAT_8008d2ac);

    if ((DAT_8008d088 == (int *)0x0) || (*DAT_8008d088 == 0)) {
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b28) = 0;
    }
    else 
	{
	  // DecalGlobal_Store
      FUN_80022bdc(PTR_DAT_8008d2ac);
      *(int *)(PTR_DAT_8008d2ac + 0x1b28) = *DAT_8008d088;
    }

	// if level is not in range of 0x28 and 0x28+1,
	// if level is not AdvGarage or Naughty Dog Box Scene
    if (1 < *(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x28U) {

	  // Music_Stop
	  FUN_8002e4ec();

	  // CseqMusic_StopAll
	  FUN_80029258();

	  // Music_LoadBanks
      FUN_8002dd74();

      return param_2 + 1;
    }
    break;
  case 6:

	// if level is not in range of 0x28 and 0x28+1,
	// if level is not AdvGarage or Naughty Dog Box Scene
    if (1 < *(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x28U)
	{
	  // Music_AsyncParseBanks
      iVar9 = FUN_8002de48();

      if (iVar9 == 0) {
        return param_2;
      }

	  // Cutscene_VolumeRestore
      FUN_8002c1d0();
    }

	// loop counter
    iVar9 = 0;

	// loop through models
    piVar15 = &DAT_80083a10;

	// for iVar9 = 0; iVar9 < 3; iVar9++
	do 
	{
	  // if pointer is valid
      if (*piVar15 != 0) 
	  {
		// increment pointer by 4,
		// change pointer to file (starting at pointer map)
		// into a pointer to the model itself
        *piVar15 = *piVar15 + 4;
      }

	  // increment loop counter
      iVar9 = iVar9 + 1;

      piVar15 = piVar15 + 1;
    } while (iVar9 < 3);

	// If the world you're in is made of multiple LEV files
    if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x20) != 0)
	{
	  // ivar9 is the size of one allocation pool
	  // ivar12 is the size of another

	  // Intro cutscene with oxide spaceship and all racers
      iVar9 = 0x6b000;

	  // If you're in Adventure Arena
      if ((*(uint *)PTR_DAT_8008d2ac & 0x100000) != 0) {
        iVar9 = 0x68800;
      }

	  // Intro cutscene with oxide spaceship and all racers
	  iVar12 = 0x40000;

	  // If you're in Adventure Arena
      if ((*(uint *)PTR_DAT_8008d2ac & 0x100000) != 0) {
        iVar12 = 0x68800;
      }

	  // Size needed for HUB is var9 + var12
	  // Pointer to hub is var5

	  // Allocate Adventure Arena
	  // MEMPACK_AllocMem
      iVar5 = FUN_8003e874(iVar9 + iVar12,"HUB ALLOC");

	  // Set 8008d854 to pointer that hub will use
      DAT_8008d854 = iVar5;

	  // Change active allocation system to #2
	  FUN_8003e80c(1);

	  // Build a new allocation system from
	  // iVar5 address with a size of iVar9
	  FUN_8003e830(iVar5,iVar9);

	  // Change active allocation system to #3
	  FUN_8003e80c(2);

	  // Build a new allocation system from
	  // address (ivar5 + ivar9), which comes after
	  // the previous allocation system, with
	  // a size of iVar12 bytes
	  FUN_8003e830(iVar5 + iVar9,iVar12);

	  // Get Game Mode structure
	  puVar3 = PTR_DAT_8008d2ac;

	  // Intro cutscene with oxide spaceship and all racers
      if ((*(uint *)PTR_DAT_8008d2ac & 0x100000) == 0)
	  {
		// Always start with pool 1
        sVar4 = 1;
      }

	  // If you're in Adventure Arena
	  else
	  {
		// Get 1 or 2, depending on map
        sVar4 = FUN_800335dc();

		// Then swap:
		// Turn 1 into 2
		// Turn 2 into 1
        sVar4 = 3 - sVar4;
      }

      puVar14 = PTR_DAT_8008d2ac;

	  // set the memory pool system ID
      *(short *)(puVar3 + 0x254a) = sVar4;

	  // globally store the Level ID for this mempack
      *(undefined2 *)(puVar14 + (int)*(short *)(puVar14 + 0x254a) * 2 + 0x254c) =
           *(undefined2 *)(puVar14 + 0x1a10);

	  // globally erase the Level ID in the other mempack
      *(undefined2 *)(puVar14 + (3 - (int)*(short *)(puVar14 + 0x254a)) * 2 + 0x254c) = 0xffff;

	  // change active allocation system to #1
	  // used for whole game (except adventure arena)
	  FUN_8003e80c(0);

	  // Get amount of free memory in CTR
      DAT_8008d094 = FUN_8003e85c();

	  // MEMPACK_AllocHighMem
      DAT_8008d090 = FUN_8003e8e8(DAT_8008d094,"Patch Table Memory");

	  // change active allocation system
	  // Swap 1 and 2 while on adventure map
      FUN_8003e80c((int)*(short *)(PTR_DAT_8008d2ac + 0x254a));
    }

	// game is now loading
    DAT_8008d0a4 = 1;

	// get VRAM subfile index within BIGFILE,
	// of the track you want to load
    uVar16 = FUN_80032c24(

			// Level ID you want to load
			*(undefined4 *)(PTR_DAT_8008d2ac + 0x1a10),

			// LOD of level you want to load
			(int)(short)DAT_8008d83c,0);

	// adds VRAM to loading queue
	// second parameter '3' means vram
	FUN_80032d30(param_3,3,uVar16,0,0);

	// Level ID you want to load
    iVar9 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);

	// if level ID some cutscene, with a super high value
	// 25-39, or
	// 44-64
    if ((iVar9 - 0x19U < 0xe) || (iVar9 - 0x2cU < 0x14))
	{
	  // get LEV subfile index within BIGFILE,
	  // of the track you want to load
      uVar16 = FUN_80032c24(

			// Level ID you want to load
			iVar9,

			// LOD of level you want to load
			(int)(short)DAT_8008d83c,1);

	  // adds LEV to loading queue
	  // '2' means dram
      FUN_80032d30(param_3,2,uVar16,0,&FUN_80031a78);

	  // get .ptr subfile from BIGFILE
	  // last param 0 for vram, 1 for lev, 2 for .ptr
      uVar6 = FUN_80032c24(

			// Level ID you want to load
			*(undefined4 *)(PTR_DAT_8008d2ac + 0x1a10),

			// LOD of level you want to load
			(int)(short)DAT_8008d83c,2);

	  // '1' means readfile
      uVar17 = 1;

	  // callback for adv levs (not HubCallback)
      pcVar7 = FUN_80031aa4;

	  // HighMem patch table
      uVar16 = DAT_8008d090;
    }

	// if Level ID is not something insane

	// Load ordinary track (arcade, battle, ND box)
    else
	{
	  // get LEV subfile index within BIGFILE,
	  // of the track you want to load
      uVar6 = FUN_80032c24(

			// Level ID you want to load
			iVar9,

			// LOD of level you want to load
			(int)(short)DAT_8008d83c,1);

	  // 2 for dram
      uVar17 = 2;

      uVar16 = 0;

	  // callback for normal levs
      pcVar7 = (code *)&FUN_80031a78;
    }

	// add LEV to loading queue
    FUN_80032d30(param_3,uVar17,uVar6,uVar16,pcVar7);
    break;
  case 7:

	// Set LEV pointer
    *(int *)(PTR_DAT_8008d2ac + 0x160) = DAT_8008d08c;

	// iVar9 is set to DAT_8008d08c at the top of the function

	// gGT->VisMem = lev->VisMem (400 = 0x190)
    *(undefined4 *)(puVar3 + 0x1a38) = *(undefined4 *)(iVar9 + 400);

	// if LEV is valid
	if (*(int *)(puVar3 + 0x160) != 0)
	{
	  // DecalGlobal_Store
	  // Load Icons and IconGroups from LEV
      FUN_80022bdc(puVar3,*(undefined4 *)(*(int *)(puVar3 + 0x160) + 0x3c));
    }

	// DebugFont_Init
	FUN_800222e0(PTR_DAT_8008d2ac);

	// get level pointer
	iVar9 = *(int *)(PTR_DAT_8008d2ac + 0x160);

	// if level is not nullptr
    if (iVar9 != 0)
	{
	  // store array of model pointers in GameTracker
      FUN_8003147c(PTR_DAT_8008d2ac,*(undefined4 *)(iVar9 + 0x14),*(undefined4 *)(iVar9 + 0x18));

	  // search for icon by string
	  uVar16 = FUN_80022c88(*(undefined4 *)(PTR_DAT_8008d2ac + 0x160),"circle");
      puVar8 = (undefined4 *)(PTR_DAT_8008d2ac + 0x160);
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b14) = uVar16;

	  // search for icon by string
      uVar16 = FUN_80022c88(*puVar8,"clod"); // &DAT_800111ec = "clod"
	  puVar8 = (undefined4 *)(PTR_DAT_8008d2ac + 0x160);
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b18) = uVar16;

	  // search for icon by string
	  uVar16 = FUN_80022c88(*puVar8,"dustpuff");
      puVar8 = (undefined4 *)(PTR_DAT_8008d2ac + 0x160);
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b1c) = uVar16;

	  // search for icon by string "Smoke Ring"
	  uVar16 = FUN_80022c88(*puVar8,"smokering");
      puVar8 = (undefined4 *)(PTR_DAT_8008d2ac + 0x160);
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b20) = uVar16;

	  // search for icon by string
	  uVar16 = FUN_80022c88(*puVar8,"sparkle");
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b24) = uVar16;
    }

	// if linked list of icons exists
	if (*(int *)(PTR_DAT_8008d2ac + 0x1b28) != 0) {

	  // search for icon by string
	  uVar16 = FUN_80022d2c(*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x1b28) + 4),"lightredoff");
	  piVar15 = (int *)(PTR_DAT_8008d2ac + 0x1b28);
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1ecc) = uVar16;

	  // search for icon by string
	  uVar16 = FUN_80022d2c(*(undefined4 *)(*piVar15 + 4),"lightredon");
      piVar15 = (int *)(PTR_DAT_8008d2ac + 0x1b28);
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1ed0) = uVar16;

	  // search for icon by string
	  uVar16 = FUN_80022d2c(*(undefined4 *)(*piVar15 + 4),"lightgreenoff");
      piVar15 = (int *)(PTR_DAT_8008d2ac + 0x1b28);
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1ed4) = uVar16;

	  // search for icon by string
	  uVar16 = FUN_80022d2c(*(undefined4 *)(*piVar15 + 4),"lightgreenon");
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1ed8) = uVar16;
    }
    puVar3 = PTR_DAT_8008d2ac;
    *(undefined4 *)(PTR_DAT_8008d2ac + 4) = 1;

    if (
			// 2 is for cutscene
			// 1 is for If you're in Adventure Arena
			((*(uint *)puVar3 & 0x20100000) == 0) &&

			// if not going to credits
			((*(uint *)(puVar3 + 8) & 0x80) == 0)
		)
	{
	  // MainInit_JitPoolsNew
	  // (now, at end of mempack)
      FUN_8003b43c( /*PTR_DAT_8008d2ac*/ );

      return param_2 + 1;
    }
    iVar9 = 7;

	// podium reward
    if (*(short *)(PTR_DAT_8008d2ac + 0x2572) != 0)
	{
	  // clear all podium model pointers
      puVar8 = &DAT_80083a38;
      do {
        *puVar8 = 0;
        iVar9 = iVar9 + -1;
        puVar8 = puVar8 + -1;
      } while (-1 < iVar9);
	  
	  // Get Memory Allocation System Index
      iVar9 = FUN_800335dc();

	  // change active allocation system
	  // Swap 1 and 2 while on adventure map
      FUN_8003e80c(3 - (int)*(short *)(PTR_DAT_8008d2ac + 0x254a));

	  // game is now loading
      DAT_8008d0a4 = 1;

	  // add something to loading queue
	  // '3' for vram
      FUN_80032d30(param_3,3,iVar9 + 0x16b,0,0);

	  // podium first place
      bVar11 = PTR_DAT_8008d2ac[0x2575];

      if (
			// if this exists
			(bVar11 != 0) && 
			
			// if not 0x7e + 0xF
			// if not oxide
			(bVar11 != 0x8d)
		 )
	  {
		// add something to loading queue
		// '2' for dram
        FUN_80032d30(param_3,2,iVar9 + ((uint)bVar11 - 0x7e) * 2 + 0x16d,&DAT_80083a1c,0xfffffffe);
      }

	  // podium second place exists
      if (PTR_DAT_8008d2ac[0x2576] != 0)
	  {
		// adds to loading queue
		// '2' for dram
        FUN_80032d30(param_3,2,iVar9 + ((uint)(byte)PTR_DAT_8008d2ac[0x2576] - 0x7e) * 2 + 0x18d,
                     &DAT_80083a20,0xfffffffe);
      }
	  
	  // podium third place exists
      if (PTR_DAT_8008d2ac[0x2577] != 0)
	  {
		// add something to loading queue
		// '2' for dram
        FUN_80032d30(param_3,2,iVar9 + ((uint)(byte)PTR_DAT_8008d2ac[0x2577] - 0x7e) * 2 + 0x18d,
                     &DAT_80083a24,0xfffffffe);
      }

	  // add TAWNA to loading queue
	  // '2' for dram
      FUN_80032d30(param_3,2,iVar9 + ((uint)(byte)PTR_DAT_8008d2ac[0x2578] - 0x8f) * 2 + 0x1ad,
                   &DAT_80083a28,0xfffffffe);

	  // -0x7d = 0x83
	  // 0x83 - 0x7e = 5 (dingo)
      if (PTR_DAT_8008d2ac[0x2575] == -0x7d)
	  {
		// add "DingoFire" to loading queue
		// '2' for dram
        FUN_80032d30(param_3,2,iVar9 + 0x1bd,&DAT_80083a30,0xfffffffe);
      }

	  // add Podium
	  // '2' for dram
      FUN_80032d30(param_3,2,iVar9 + 0x1bf,0,&FUN_80031a64);

	  // Disable LEV instances on Adv Hub, for podium scene
      *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x100;
    }
    break;
  case 8:

    // If you're in Adventure Arena
    if (
			((*(uint *)PTR_DAT_8008d2ac & 0x100000) != 0) &&
			(
				// loop counter
				iVar9 = 0,

				// podium reward
				*(short *)(PTR_DAT_8008d2ac + 0x2572) != 0
			)
	   ) {
      piVar15 = &DAT_80083a1c;

	  // for iVar9 = 0; iVar9 < 8; iVar9++
      do {
        iVar12 = *piVar15;
        if (iVar12 != 0) {
          if (iVar9 < 7) {
            *piVar15 = iVar12 + 4;
            iVar12 = *piVar15;
          }
          if ((int)*(short *)(iVar12 + 0x10) != -1) {
            *(int *)(puVar3 + (int)*(short *)(iVar12 + 0x10) * 4 + 0x2160) = iVar12;
          }
        }

		// increment loop counter
        iVar9 = iVar9 + 1;

        piVar15 = piVar15 + 1;
      } while (iVar9 < 8);

	  // change active allocation system
	  // Swap 1 and 2 while on adventure map
      FUN_8003e80c((int)*(short *)(PTR_DAT_8008d2ac + 0x254a));
    }

	// Level ID
    iVar9 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);

	// Main Menu
    if (iVar9 == 0x27) {
      uVar16 = 7;
LAB_800346b0:

	  // Audio_SetState_Safe
      FUN_8002d4cc(uVar16);

      return param_2 + 1;
    }

	// One of the maps on Adventure Arena
    if (iVar9 - 0x19U < 5) {
      uVar16 = 6;

	  // podium reward
      if (*(short *)(PTR_DAT_8008d2ac + 0x2572) == 0) {
        uVar16 = 5;
      }
      goto LAB_800346b0;
    }

	// oxide intro
    if (iVar9 == 0x1e) {
      uVar16 = 3;
      goto LAB_800346b0;
    }

	// credits
    if (iVar9 == 0x2c) {
      uVar16 = 2;
      goto LAB_800346b0;
    }

	// Naughty Dog Box
    if (iVar9 == 0x29) {
      uVar16 = 4;
      goto LAB_800346b0;
    }

	// stop/pause cseq music
	uVar16 = 1;

    if (iVar9 - 0x2aU < 2) goto LAB_800346b0;
    break;
  case 9:
    if (DAT_8008d708 != 2) {

      if (

			// If not in main menu (not in 2D character selection, track selection, or any part of it)
			((*(uint *)PTR_DAT_8008d2ac & 0x2000) == 0) ||

			// If level ID == 40
			// If you are in Adventure Character Selection
			(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x28)

		 )
	  {
		// if not going to credits
        if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x80) == 0)
		{
		  // enable all flags except loading screen
          uVar10 = *(uint *)(PTR_DAT_8008d2ac + 0x256c) | 0xffffefff;
        }

		// if going to credits
        else
		{
		  // disable everything (except loading screen if still there)
		  // enable drawing render bucket
          uVar10 = *(uint *)(PTR_DAT_8008d2ac + 0x256c) & 0x1000 | 0x20;
        }

		// apply desired value
        *(uint *)(PTR_DAT_8008d2ac + 0x256c) = uVar10;
      }
      else
	  {
		  // disable everything (except loading screen if still there)
		  // enable pause menu? Or enable 3D cars on track?
        *(uint *)(PTR_DAT_8008d2ac + 0x256c) = *(uint *)(PTR_DAT_8008d2ac + 0x256c) & 0x1000 | 0x20;

		// RaceFlag_IsFullyOffScreen
        iVar9 = FUN_80043f28();
        if (iVar9 == 1)
		{
		  // checkered flag, begin transition on-screen
          FUN_80043fb0(1);
        }
      }
      PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] | 8;
      puVar3 = PTR_DAT_8008d2ac;
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1cfc) = 0;
      *(undefined4 *)(puVar3 + 0x1d00) = 0;

	  // ElimBG_Deactivate
      FUN_80024c08();

	  param_2 = -2;
    }
  default:
    goto switchD_80033660_caseD_a;
  }
  param_2 = param_2 + 1;
switchD_80033660_caseD_a:
  return param_2;
}

// LOAD_TalkingMask
// param1 is mempack index
// param2 is aku or uka
void FUN_800347d0(int param_1,int param_2)

{
  int iVar1;

  // erase mask hint model pointer
  DAT_8008d0f0 = 0;

  *(undefined2 *)(PTR_DAT_8008d2ac + param_1 * 2 + 0x254c) = 0xffff;

  // change active allocation system to ???
  FUN_8003e80c(param_1);

  // MEMPACK_ClearLowMem
  FUN_8003e9b8();

  // different variation of aku/uka
  iVar1 = (param_1 + -1) * 2;

  // Game is now loading
  DAT_8008d0a4 = 1;

  // load the vram for 3D mask hints
  // DAT_8008d09c is the Pointer to "cd position of bigfile"
  // '3' for vram
  FUN_80032d30(DAT_8008d09c,3,param_2 * 4 + iVar1 + 0x1b6,0,0);

  // load the model for 3D mask hints,
  // see the callback function for proof
  // '2' for dram
  FUN_80032d30(DAT_8008d09c,2,param_2 * 4 + iVar1 + 0x1b7,0,&FUN_80031a50);
  return;
}

// LOAD_LevelFile
// param1 is lev ID being loaded
void FUN_80034874(undefined4 param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined4 uVar3;
  int iVar4;

  puVar1 = PTR_DAT_8008d2ac;

  // erase mask hint model pointer
  DAT_8008d0f0 = 0;

  // Turn off HUD
  PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xfe;

  puVar2 = PTR_DAT_8008d2ac;

  // Level ID
  // set active lev ID to the lev ID being loaded
  uVar3 = *(undefined4 *)(puVar1 + 0x1a10);
  *(undefined4 *)(puVar1 + 0x1a10) = param_1;

  // make a backup of your levelID before exiting the level,
  // this is used to help you return to an adventure hub after finishing a race
  *(undefined4 *)(puVar1 + 0x1eb4) = uVar3;

  // disable all render flags except checkeredFlag
  *(uint *)(puVar2 + 0x256c) = *(uint *)(puVar2 + 0x256c) & 0x1000;

  // RaceFlag_IsFullyOffScreen
  iVar4 = FUN_80043f28();
  if (iVar4 == 1)
  {
	// checkered flag, begin transition on-screen
    FUN_80043fb0(1);
  }

  // set loading state to begin
  DAT_8008d0f8 = 0;

  return;
}

// LOAD_IsOpen_RacingOrBattle (231)
uint FUN_800348e8(void)
{
  return (uint)(PTR_DAT_8008d2ac[0x2541] == '\x01');
}


// LOAD_IsOpen_MainMenu (230)
uint FUN_80034908(void)
{
  return (uint)(PTR_DAT_8008d2ac[0x2541] == '\0');
}


// LOAD_IsOpen_AdvHub (232)
uint FUN_80034920(void)
{
  return (uint)(PTR_DAT_8008d2ac[0x2541] == '\x02');
}


// LOAD_IsOpen_Podiums (233)
uint FUN_80034940(void)
{
  return (uint)(PTR_DAT_8008d2ac[0x2541] == '\x03');
}
