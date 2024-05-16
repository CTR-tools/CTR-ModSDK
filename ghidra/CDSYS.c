
// called "CDSYS" because of debug strings
// "CDSYS_SetXAToLang", "CDSYS_XASeek", "CDSYS_XAPlay"

// CDSYS_Init
undefined4 FUN_8001c360(int param_1)

{
  int iVar1;

  // unused in all found builds of the game,
  // boolDebugMachine = false?
  DAT_8008e528 = 0;

  // bool boolUseDisc
  DAT_8008d6b0 = param_1;

  // If you are using disc
  if (param_1 != 0)
  {
	// initialize the CD
    iVar1 = CdInit();

	// if you fail to initialize CD
    if (iVar1 == 0)
	{
	  // fall back to parallel port (Naughty Dog Devs only)
      DAT_8008d6b0 = 0;
      return 0;
    }
	CdSetDebug(1);
  }

  // stream mode is null
  DAT_8008d6ac = 0xffffffff;

  // bool_XnfLoaded
  DAT_8008d6b4 = 0;

  // XA_State
  DAT_8008d708 = 0;

  // XA is not finished (nor started)
  DAT_8008d6b8 = 0;

  // countFail_CdSyncCallback
  DAT_8008d720 = 0;
  
  // countPass_CdReadyCallback
  DAT_8008d704 = 0;
  
  // countFail_CdReadyCallback
  DAT_8008d724 = 0;
  
  // XA_CurrOffset
  DAT_8008d6f8 = 0;

  // countPass_CdTransferCallback
  DAT_8008d6d8 = 0;

  // XA_Playing_Category
  DAT_8008d6e4 = 0;
  
  // XA_Playing_Index
  DAT_8008d6e0 = 0;
  
  // XA_StartPos
  DAT_8008d6f0 = 0;
  
  // XA_EndPos
  DAT_8008d710 = 0;
  
  // XA_VolumeBitshift
  DAT_8008d70c = 0;
  
  // XA_VolumeDeduct
  DAT_8008d6c8 = 0;
  
  // XA_MaxSampleVal
  DAT_8008d714 = 0;
  
  // XA_MaxSampleValInArr
  DAT_8008d6f4 = 0;
  
  // irqAddr
  DAT_8008d6c4 = 0;
  
  // unused
  DAT_8008d700 = 0;
  
  // XA_CurrPos
  DAT_8008d6d4 = 0;
  
  // XA_PauseFrame
  DAT_8008d6ec = 0;

  // CDSYS_SetMode_StreamData
  FUN_8001c470();

  // Just like loading LNG (for text),
  // Load XA (for audio) with 1 for ENG
  CDSYS_SetXAToLang(1);

  // Voiceline_PoolClear
  FUN_8002cae0();
  return 1;
}


// CDSYS_GetFilePosInt
// param1 is the file it is searching for,
// param2 is the position that will return
// function returns true or false if it worked or failed
uint FUN_8001c420(char *param_1,int *param_2)

{
  CdlFILE *pCVar1;
  int iVar2;
  CdlFILE CStack32;

  // cpVar1 and CStack32 are the same
  // param_1 is the string of the file searched,
  // pCVar1 is the CdlFILE that corresponds
  pCVar1 = CdSearchFile(&CStack32,param_1);

  // if file was found
  if (pCVar1 != (CdlFILE *)0x0)
  {
	// Convert file's CD position to int
    iVar2 = CdPosToInt((CdlLOC *)&CStack32);

	// set param2 to cd position
    *param_2 = iVar2;
  }

  // return true if it found file, or false if it failed
  return (uint)(pCVar1 != (CdlFILE *)0x0);
}


// CDSYS_SetMode_StreamData
void FUN_8001c470(void)

{
  u_char local_10 [8];

  if (
		// boolUseDisc
		// if you are using CD instead of parallel port
		(DAT_8008d6b0 != 0) &&

		// if stream mode is not data
		(DAT_8008d6ac != 0)
	 )
  {
	// bool_XnfLoaded
    if (DAT_8008d6b4 != 0)
	{
	  // CDSYS_XAPauseForce
      FUN_8001cfec();
    }

	// https://www.cybdyn-systems.com.au/forum/viewtopic.php?t=1956
    // CdControl('\x0e',local_10,(u_char *)0x0);
	// param_1: 0xe = CdlSetmode
	// param_2: 0x80 = Speed mode (separate modes exist)
	// param_3: 0 = normal speed, 1 = double speed

	// Set Mode to Data
	local_10[0] = CdlModeSpeed;
	CdControl(CdlSetmode, local_10, 0);

	// XA_State
	DAT_8008d708 = 0;

	// stream mode is now data
    DAT_8008d6ac = 0;

	// bool_XnfLoaded
    if (DAT_8008d6b4 != 0)
	{
	  // called when CdControl is complete
      CdSyncCallback(0);

	  // called when data is streamed
	  CdReadyCallback((CdlCB)0x0);
    }
  }
  return;
}


// CDSYS_SetMode_StreamAudio
void FUN_8001c4f4(void)

{
  u_char local_10 [8];

  if (
		(
			// If you are using CD instead of parallel port
			(DAT_8008d6b0 != 0) &&

			// bool_XnfLoaded
			(DAT_8008d6b4 != 0)
		) &&

		// if stream mode is not audio
		(DAT_8008d6ac != 1)
	  )
  {
	// https://www.cybdyn-systems.com.au/forum/viewtopic.php?t=1956
    // CdControl('\x0e',local_10,(u_char *)0x0);
	// param_1: 0xe = CdlSetmode
	// param_2: 0xE8 = set speed, play ADPCM, set sector

	// Set Mode to Audio
    local_10[0] = -0x18; // 0xE8
    CdControl('\x0e',local_10,(u_char *)0x0);

	// set stream mode to audio
	DAT_8008d6ac = 1;

	// XA_State
    DAT_8008d708 = 0;

	// called when CdControl is complete
    CdSyncCallback(FUN_8001c7a4);

	// called when audio is streamed
	CdReadyCallback(FUN_8001c7fc);
  }
  return;
}

// CDSYS_SetXAToLang
// 8001c56c
// Name found in Aug 5 Prototype
// loads correct XNF file and checks if all XA files are present on the disk
// param_1 - language index
undefined4 CDSYS_SetXAToLang(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  char **ppcVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  int iVar9;
  undefined auStack32 [8];

  // If you are using parallel port instead of CD
  if (DAT_8008d6b0 == 0) {
    uVar2 = 1;
  }

  // If you are using CD instead of parallel port
  else {

    //check lang id overflow. what's interesting is that the id is not checked during lang file loading
    if (param_1 < 8)
	{
	  // bool_XnfLoaded
      DAT_8008d6b4 = 0;

	  // CDSYS_SetMode_StreamData
      FUN_8001c470();

      //get current lang string (ENG, JPN, etc)
      ppcVar5 = &PTR_DAT_80081050 + param_1;

	  //update xa file paths
      strncpy(s_ENG_XNF_1_80081000,*ppcVar5,3);
      strncpy(s_ENG_EXTRA_S00_XA_1_80081024,*ppcVar5,3);
      strncpy(s_ENG_GAME_S00_XA_1_8008103c,*ppcVar5,3);

	  // read XNF file into buffer
      piVar3 = (int *)FUN_80032344(&DAT_80080ffc,0,auStack32);

	  // if reading XNF failed
      if (piVar3 == (int *)0x0)
	  {
		// quit the function
        return 0;
      }

	  // only load file if first 4 bytes are "XINF"
	  // and if the next 4 bytes (version) is 102 (0x66).
	  // Aug 5 had 100, Sep 3 had 101, 94426+ had 102
      if ((*piVar3 == DAT_8008cfc0) && (piVar3[1] == 0x66))
	  {
		// Get number of types
        DAT_8008d6dc = piVar3[2];

		// only continue if that's 3
        if (DAT_8008d6dc == 3) {

		  // each of these is a pointer to
		  // an array of three ints,
		  // Music, Extra, Game

		  // ptrArray_NumXAs
          DAT_8008d6fc = piVar3 + 5;

		  // ptrArray_firstXaIndex
          DAT_8008d71c = piVar3 + 8;

		  // ptrArray_numSongs
          DAT_8008d6cc = piVar3 + 0xb;

		  // ptrArray_firstSongIndex
          DAT_8008d6d0 = piVar3 + 0xe;

		  // not an array of 3 ints,
		  // array of a huge ton of data
		  // ptrArray_XaCdPos
          DAT_8008d718 = piVar3 + 0x11;

          iVar9 = 0;
          iVar8 = 0;

		  // pointer to array[3] of { byte, byte, short, ptr }
		  // where ptr is pointer to file path \XA\MUSIC\S00.XA;1.
		  // byte - digit char indices to swap (00)
		  // short - null

		  // &sdata->audioMeta[0]
          pbVar7 = &DAT_80081070;

		  // pointer to actual XA entries (big array of uint (byte[4])),
		  // comes after an array for every XA file

		  // &ptrXNF->data[ptrXNF->numXAs_total]
          DAT_8008d6e8 = DAT_8008d718 + piVar3[3];

		  // This loop bakes an array of CD Postions
		  // for every XA file, so we dont need to
		  // search the disc when we need them

          //for each xa group
          do {
            iVar6 = 0;

            //if there are xa files in the current group
            if (0 < *(int *)(iVar8 + (int)DAT_8008d6fc)) {

              //for each file entry
              do {
                cVar1 = (char)(iVar6 / 10);
                //swap 00 in S00.XA with correct digits
                *(char *)(*(int *)(pbVar7 + 4) + (uint)*pbVar7) = cVar1 + '0';
                *(char *)(*(int *)(pbVar7 + 4) + (uint)pbVar7[1]) = (char)iVar6 + cVar1 * -10 + '0';

				// CDSYS_GetFilePosInt
				// get cd position of param1, store position into param2
				iVar4 = FUN_8001c420(*(undefined4 *)(pbVar7 + 4),
                                     DAT_8008d718 + *(int *)(iVar8 + (int)DAT_8008d71c) + iVar6);
                iVar6 = iVar6 + 1;

				// if file was not found, quit the function,
				// return false for the function
                if (iVar4 == 0) goto LAB_8001c654;

              } while (iVar6 < *(int *)(iVar8 + (int)DAT_8008d6fc));
            }

            //increment relative pointer to xa group
            iVar8 = iVar8 + 4;

			// increment counter
            iVar9 = iVar9 + 1;

			// next type (8 bytes each)
            pbVar7 = pbVar7 + 8;

			// if all "types" are loaded
            if (DAT_8008d6dc <= iVar9)
			{
			  // bool_XnfLoaded
              DAT_8008d6b4 = 1;
              return 1;
            }
          } while( true );
        }
      }
    }
LAB_8001c654:
    uVar2 = 0;
  }
  return uVar2;
}

// CDSYS_XaCallbackCdSync
void FUN_8001c7a4(char param_1)

{
  int iVar1;

  // if result == CdlComplete
  if (param_1 == '\x02')
  {
	// string of command
    iVar1 = CdLastCom();

    if (iVar1 - 0x15U < 2) {
      DAT_8008d708 = 0;
    }
  }

  // if fail
  else
  {
	// count fails
    DAT_8008d720 = DAT_8008d720 + 1;
  }
  return;
}

// CDSYS_XaCallbackCdReady
void FUN_8001c7fc(char param_1)

{
  // if result == CdlDataReady
  if (param_1 == '\x01')
  {
	// cdlFile_CdReady (half of a CdlFILE struct)
    CdGetSector(&DAT_8008e6b8,3);
    DAT_8008d6d4 = CdPosToInt((CdlLOC *)&DAT_8008e6b8);

    if (
			// if XA is queued to start (CD seeking?)
			(DAT_8008d708 == 2) &&

			// if XA_CurrPos is more than XA_StartPos
			(DAT_8008d6f0 <= DAT_8008d6d4)
		)
	{
	  // XA is now playing
      DAT_8008d708 = 3;

	  // XA_CurrOffset = CurrPos - StartPos
      DAT_8008d6f8 = (DAT_8008d6d4 - DAT_8008d6f0) * 4;
    }

    if (
			// if XA is playing
			(DAT_8008d708 == 3) &&

			// if XA_CurrPos is more than XA_EndPos
			(DAT_8008d710 < DAT_8008d6d4)
		)
	{

	  // XA should stop
	  DAT_8008d708 = 4;

	  // disable music
      DAT_8008d6c8 = 0x400;
    }

	// count success
    DAT_8008d704 = DAT_8008d704 + 1;
  }

  // if fail
  else
  {
	// count fails
    DAT_8008d724 = DAT_8008d724 + 1;
  }
  return;
}


// CDSYS_SpuCallbackIRQ
void FUN_8001c8e4(void)

{
  // disable IRQ, now that it's finished
  SpuSetIRQ(0);

  /*

  From LibRef
When you call SpuReadDecodedData(), the SPU copies data from its buffers to the SpuDecodeData struct
in main memory that you specify. It copies the data one-half buffer (0x200 bytes) at a time, and returns a
code specifying which half of the buffer is currently being written to, so you can use the data from the other
half.
  */

  // 5 = SPU_CDONLY
  SpuReadDecodedData((SpuDecodedData *)&DAT_8008dd28,5);

  if (
		// if XA is not finished
		(DAT_8008d6b8 == 0) &&

		// if XA is requested to stop,
		// either by CdReadyCallback,
		// or CDSYS_XAPauseRequest
		(DAT_8008d708 == 4)
	 )
  {
	// 8008d6c8 is either 0 or 0x400
	// 8008d70c is volume of music

    DAT_8008d70c = DAT_8008d70c - DAT_8008d6c8;

	// the goal is to gradually
	// reduce audio slowly over time,
	// otherwise intro-race song still
	// plays when you pause game

	// if volume is less than zero
    if (DAT_8008d70c < 0)
	{
	  // set audio to zero
      DAT_8008d70c = 0;

	  // XA is finished
      DAT_8008d6b8 = 1;
    }

	SpuSetCommonCDVolume((short)DAT_8008d70c,(short)DAT_8008d70c);
  }
  DAT_8008d6f8 = DAT_8008d6f8 + 1;
  return;
}


// CDSYS_SpuCallbackTransfer
void FUN_8001c984(void)

{
  // irqAddr
  if (DAT_8008d6c4 == 0) 
  {
    // irqAddr
	DAT_8008d6c4 = 0x200;
  }
  else 
  {
	// irqAddr
    DAT_8008d6c4 = 0;
  }

  // interrupt SPU when this address
  // is written, or read, (XA?)
  SpuSetIRQAddr(DAT_8008d6c4);

  // set interrupt request
  SpuSetIRQ(1);

  // countPass_CdTransferCallback
  DAT_8008d6d8 = DAT_8008d6d8 + 1;

  // CDSYS_SpuGetMaxSample
  FUN_8001ca98();

  return;
}


// CDSYS_SpuEnableIRQ
void FUN_8001c9e4(void)

{
  undefined2 *puVar1;
  int iVar2;

  // Erase SpuDecodedData, 
  // wipe it all to zeros
  iVar2 = 0x1ff;
  puVar1 = &DAT_8008e126;
  DAT_8008d714 = 0;
  DAT_8008d6f4 = 0;
  do {
    *puVar1 = 0;
    iVar2 = iVar2 + -1;
    puVar1 = puVar1 + -1;
  } while (-1 < iVar2);

  // transfer by DMA
  SpuSetTransferMode(0);

  SpuSetTransferCallback(FUN_8001c984);
  SpuSetIRQCallback(FUN_8001c8e4);

  // irqAddr
  DAT_8008d6c4 = 0x200;
  
  // unused
  DAT_8008d700 = 0;

  // interrupt SPU when this address
  // is written, or read
  SpuSetIRQAddr(0x200);

  // set interrupt request (ON)
  SpuSetIRQ(1);

  return;
}


// CDSYS_SpuDisableIRQ
void FUN_8001ca64(void)

{
  // set interrupt request (OFF)
  SpuSetIRQ(0);

  SpuSetIRQCallback((SpuIRQCallbackProc)0x0);
  SpuSetTransferCallback((SpuTransferCallbackProc)0x0);
  DAT_8008d6f4 = 0;
  DAT_8008d714 = 0;
  return;
}


// CDSYS_SpuGetMaxSample
void FUN_8001ca98(void)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  short *psVar6;
  uint uVar7;
  short sVar8;

  _sVar8 = 0;
  sVar8 = 0;

  // if you are using CD instead of parallel port
  if (DAT_8008d6b0 != 0) {
    uVar2 = 0x100;
	
	// if irqAddr == 0x0, range {0x0 - 0x100}
    if (DAT_8008d6c4 == 0) {
      uVar2 = 0;
      uVar7 = 0x100;
    }
    
	// otherwise, range {0x100 - 0x200}
	else 
	{
      uVar7 = 0x200;
    }

	// curr < end
	if (uVar2 < uVar7)
	{
	  // decoded SPU data
      psVar6 = &DAT_8008dd28 + uVar2;

	  // loop through region
	  do
	  {
        iVar3 = (int)*psVar6;

		// absolute value
		if (iVar3 < 0) {
          iVar3 = -iVar3;
        }

		// if larger than cur_max
        if (_sVar8 << 0x10 < iVar3 << 0x10)
		{
		  // set new cur_max
          _sVar8 = iVar3;
        }

		// copy max
        sVar8 = (short)_sVar8;

        uVar2 = uVar2 + 1;
        psVar6 = psVar6 + 1;
      } while ((int)uVar2 < (int)uVar7);
    }

	// save max
	DAT_8008d714 = (int)sVar8;

	// XA_MaxSampleValArr
    piVar5 = &DAT_8008e6c8 + DAT_8008d6bc;
	
    DAT_8008d6bc = DAT_8008d6bc + 1;
    bVar1 = 2 < DAT_8008d6bc;
    
	*piVar5 = DAT_8008d714;
    
	if (bVar1) {
      DAT_8008d6bc = 0;
    }
    if (DAT_8008d6c0 < 3) {
      DAT_8008d6c0 = DAT_8008d6c0 + 1;
    }

	// set max to zero
	DAT_8008d6f4 = 0;

    iVar3 = DAT_8008d6bc;
    _sVar8 = DAT_8008d6c0;
    if (DAT_8008d6c0 != 0) {
      while (_sVar8 = _sVar8 + -1, _sVar8 != -1) {
        iVar3 = iVar3 + -1;
        iVar4 = iVar3 * 4;
        if (iVar3 < 0) {
          iVar3 = 2;
          iVar4 = 8;
        }

		// XA_MaxSampleValInArr
        if (DAT_8008d6f4 < *(int *)((int)&DAT_8008e6c8 + iVar4)) {
          DAT_8008d6f4 = *(int *)((int)&DAT_8008e6c8 + iVar4);
        }
      }
    }
  }
  return;
}

// CDSYS_XAGetNumTracks
undefined4 FUN_8001cbe0(int param_1)

{
  if (
		// If you are using CD instead of parallel port
		(DAT_8008d6b0 != 0) &&

		// if category is valid
		(param_1 < 3)
	 )
  {
	// get number of audio tracks in this category
    return *(undefined4 *)(param_1 * 4 + DAT_8008d6cc);
  }
  return 0;
}


// Aug 5 calls this
// CDSYS_XASeek
// param1 - bool cdControl
// param2 - xa type (game, music, extra)
// param3 - xa audioTrackID
undefined4 FUN_8001cc18(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  u_char com;
  CdlLOC aCStack32 [2];

  // If you are using parallel port instead of CD
  if (DAT_8008d6b0 == 0) {
LAB_8001cd00:
    uVar1 = 1;
  }

  // if you are using CD instead of parallel
  else
  {
	// bool_XnfLoaded
    if (DAT_8008d6b4 != 0)
	{
	  // three XA categories, 0,1,2
	  // if you go out of bounds
      if (2 < param_2)
	  {
		// quit
        return 0;
      }

	  // CDSYS_XAGetNumTracks
      iVar2 = FUN_8001cbe0(param_2);

	  // if audioTrackID is within bounds
      if (param_3 < iVar2)
	  {
		// if stream mode is not audio
        if (DAT_8008d6ac != 1)
		{
		  // CDSYS_SetMode_StreamAudio
          FUN_8001c4f4();
        }

        CdIntToPos
		(
			*(int *)
			(
				(uint)*(byte *)
				(
					DAT_8008d6e8 +
						*(int *)(param_2 * 4 + DAT_8008d6d0) * 4 + param_3 * 4 + 1
				) * 4 +

					// XA CdPos
                    DAT_8008d718 +
						*(int *)(param_2 * 4 + DAT_8008d71c) * 4
			),

			aCStack32
		);

		DAT_8008d708 = 1;

		// CdlSeekP
		// physical seek, for audio
		com = '\x16';

		if (param_1 != 0)
		{
		  // CdlSeekL
		  // logical seek, for data
          com = '\x15';
        }

        CdControl(com,(u_char *)aCStack32,(u_char *)0x0);
        goto LAB_8001cd00;
      }
    }
    uVar1 = 0;
  }
  return uVar1;
}

// CDSYS_XAGetTrackLength
// assumed to return sample length from XINF XA entry
// param1 - xa type (game, music, extra)
// param2 - xa audioTrackID
int FUN_8001cd20(int param_1,int param_2)

{
  int iVar1;

  if (
		// if you are using CD instead of parallel port
		(DAT_8008d6b0 != 0) &&

		// bool_XnfLoaded
		(DAT_8008d6b4 != 0)
	 )
  {
	// three XA categories, 0,1,2
	// if you go out of bounds
    if (2 < param_1) {
      return 0;
    }

	// CDSYS_XAGetNumTracks
    iVar1 = FUN_8001cbe0(param_1);

	// if audioTrackID is within bounds
    if (param_2 < iVar1) 
	{
	/*
		sdata->ptrArray_XaSize[
				sdata->ptrArray_firstSongIndex[categoryID] +
				audioTrackID
			].XaBytes;
	*/
      return (int)*(short *)(DAT_8008d6e8 + *(int *)(param_1 * 4 + DAT_8008d6d0) * 4 + param_2 * 4 +
                            2);
    }
  }
  return 0;
}

// CDSYS_XA_TYPE_MUSIC
// 0,1,2,3 - MUSIC_RACE_INTRO
// 04 - MUSIC_RACE_WIN -- real ND name
// 05 - MUSIC_RACE_LOSE
// 06 - MUSIC_LAST_LAP -- real ND name
// 07 - MUSIC_PODIUM_POLAR_PURA
// 08 - MUSIC_PODIUM_CORTEX_NTROPY
// 09 - MUSIC_PODIUM_PENTA
// 10 - MUSIC_PODIUM_CRASH_COCO
// 11 - MUSIC_PODIUM_PINSTRIPE
// 12 - MUSIC_PODIUM_TINY
// there's probably more

// CDSYS_XA_TYPE_EXTRA
// 0x00 - 0x1e Aku Aku hints (some unused)
// 0x1e - SPEAK_AKU_39 -- real ND name
// 0x1f - 0x3c Uka Uka hints (some unused)
// 0x3d - SPEAK_UKA_39 -- real ND name
// 0x3f - SPEAK_NTROPY_BEATEN_1
// 0x40 - SPEAK_NTROPY_BEATEN_2
// 0x41 - SPEAK_NTROPY_BEATEN_3
// 0x42 - SPEAK_NTROPY_BEATEN_4
// 0x43 - SPEAK_NTROPY_UNLOCKED
// 0x44 - SPEAK_NTROPY_BEATEN_5
// 0x45 - SPEAK_NTROPY_BEATEN_6
// 0x46 - SPEAK_NTROPY_BEATEN_7
// 0x47 - SPEAK_NTROPY_BEATEN_8

// before relics
// 0x48 - SPEAK_OXIDE_RACE_INTRO_1
// 0x49 - SPEAK_OXIDE_RACE_OUTRO_1

// after relics
// 0x4a - SPEAK_OXIDE_RACE_INTRO_2
// 0x4b - SPEAK_OXIDE_RACE_OUTRO_2

// unused
// 0x4c - SPEAK_OXIDE_BRING_TROPHIES

// intro cutscene
// "greeting creatures of this planet, I come to compete..."
// 0x4d - SPEAK_OXIDE_GAME_CUTSCENE_1
// 0x4e - SPEAK_OXIDE_GAME_CUTSCENE_2
// 0x4f - SPEAK_OXIDE_GAME_CUTSCENE_3

// "start your engines for sony, fasten seatbelts for naughty dog"
// 0x50 - SPEAK_CLANCY_BROWN_SCEA_PAGE
// 0x51 - SPEAK_CLANCY_BROWN_NAUGHTY_DOG_BOX

// unused
// 0x52 - SPEAK_CLANCY_BROWN_CTR
// 0x53 - SPEAK_CLANCY_BROWN_PRESS_START_TO_PLAY
// 0x54 - SPEAK_CLANCY_BROWN_SELECT_PLAYER
// 0x55 - SPEAK_CLANCY_BROWN_SELECT_PLAYERS
// 0x56 - SPEAK_CLANCY_BROWN_CHOOSE_A_RACE_TRACK

// CDSYS_XA_TYPE_GAME
// decimal, not hex
// 0-18 - Crash
// 19-37 - Cortex
// 38-56 - Tiny
// 57-75 - Coco
// 76-94 - Ngin
// ...
// 284-303 - Oxide
// 304 - SPEAK_ROO_RACE_INTRO
// 305 - SPEAK_ROO_RACE_OUTRO
// 306 - SPEAK_ROO_RACE_INTRO_removed
// 307 - SPEAK_ROO_RACE_OUTRO_removed
// 308 - SPEAK_PAPU_RACE_INTRO
// 309 - SPEAK_PAPU_RACE_OUTRO
// 310 - SPEAK_JOE_RACE_INTRO
// 311 - SPEAK_JOE_RACE_OUTRO
// 312 - SPEAK_PSTRIPE_RACE_INTRO
// 313 - SPEAK_PSTRIPE_RACE_OUTRO

// CDSYS_XA_TYPE_WARP
// 0x00 - CRASH_SELECTED
// 0x01 - CORTEX_SELECTED
// https://www.youtube.com/watch?v=ACntd0AP6rM&t=195s
// ...

// Aug 5
// CDSYS_XAPlay
// 0 - CDSYS_XA_TYPE_MUSIC
// 1 - CDSYS_XA_TYPE_EXTRA
// 2 - CDSYS_XA_TYPE_GAME
// 3 - CDSYS_XA_TYPE_WARP -- only in prototype
undefined4 FUN_8001cdb4(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  undefined *puVar3;
  u_char local_20;
  undefined local_1f;
  CdlLOC aCStack24 [2];

  // If you are using parallel port instead of CD,
  // which would be if you are a Naughty Dog Dev,
  // and if you're reading this, you probably aren't
  if (DAT_8008d6b0 == 0) {
    return 1;
  }

  // Only continue if you are on CD

  // bool_XnfLoaded
  if (DAT_8008d6b4 != 0)
  {
	// if category is invalid
    if (2 < param_1) {
      return 0;
    }

	// CDSYS_XAGetNumTracks
    iVar2 = FUN_8001cbe0(param_1);

	// if index is invalid within XA category
    if (iVar2 <= param_2) {
      return 0;
    }

	// If the game is loading
    if (DAT_8008d0a4 != 0)
	{
	  // OtherFX_Play: Error sound (that's funny)
      FUN_80028468(5,1);

	  // Sep 3
	  // printf("CDSYS_XAPlay failed, load_inProgress is TRUE\n");

      return 0;
    }

	// if you get here, the game must not be loading

	// if stream mode is not audio
    if (DAT_8008d6ac != 1)
	{
	  // CDSYS_SetMode_StreamAudio
      FUN_8001c4f4();
    }

	// XA_State
    DAT_8008d708 = 2;

	// volume of Voice
    bVar1 = DAT_8008d7bc;
    if (param_1 == 0)
	{
		// volume of Music
      bVar1 = DAT_8008d7b8;
    }

	// save volume
    DAT_8008d70c = (uint)bVar1 << 7;

	// save category and index of active XA
    DAT_8008d6e0 = param_2;
    DAT_8008d6e4 = param_1;

    SpuSetCommonCDVolume((short)DAT_8008d70c,(short)DAT_8008d70c);

	local_20 = '\x01';
    puVar3 = (undefined *)(DAT_8008d6e8 + *(int *)(param_1 * 4 + DAT_8008d6d0) * 4 + param_2 * 4);
    local_1f = *puVar3;

	// '\r' = 0xd = CdlSetfilter
    CdControl('\r',&local_20,(u_char *)0x0);

	// XA StartPos
	DAT_8008d6f0 =

		*(int *)((uint)(byte)puVar3[1] * 4 +

		// start position of each XA
        *(int *)(param_1 * 4 + DAT_8008d71c) * 4 + DAT_8008d718);

	// XA EndPos
    DAT_8008d710 = DAT_8008d6f0 + *(short *)(puVar3 + 2);

	// convert StartPosInt, to a real position
    CdIntToPos(DAT_8008d6f0,aCStack24);

	// XA_MaxSampleVal
	DAT_8008d714 = 0;
	
	// XA_MaxSampleValInArr
    DAT_8008d6f4 = 0;
	
	// unused
    DAT_8008d700 = 0;
    
	DAT_8008d704 = 0;
    DAT_8008d724 = 0;
    DAT_8008d6f8 = 0;

	// countPass_CdTransferCallback
    DAT_8008d6d8 = 0;

	// 0x1b = CdlReadS
	// set disc to XA StartPos
	iVar2 = CdControl('\x1b',(u_char *)aCStack24,(u_char *)0x0);

	// As of now, XA plays indefinitely, until CdReadyCallback
	// determines the current CD position is past the end position,
	// and then when IRQ determines the SPU is done playing the last
	// of the XA, CDSYS_XAPauseForce is called to stop playing XA.

	// Emulators with no IRQ support will keep playing random
	// XA audio on the disc infinitely, and never reach ND Box

    if (iVar2 == 1)
	{
	  // CDSYS_SpuEnableIRQ
      FUN_8001c9e4();

      return 1;
    }

	// if it failed, assume no XA play
    DAT_8008d708 = 0;
  }
  return 0;
}


// CDSYS_XAPauseRequest
void FUN_8001cf98(void)

{
  if (
		(
			// If you are using CD and not parallel port
			(DAT_8008d6b0 != 0) &&

			// bool_XnfLoaded
			(DAT_8008d6b4 != 0)
		) &&

		(
			(
				// if XA is playing
				DAT_8008d708 == 3 ||
				(DAT_8008d708 == 2)
			)
		)
	 )
  {
	// XA should now stop
    DAT_8008d708 = 4;

	// disable music
    DAT_8008d6c8 = 0x400;
  }
  return;
}


// CDSYS_XAPauseForce
void FUN_8001cfec(void)

{
  if (
		(
			// If you are using CD and not parallel port
			(DAT_8008d6b0 != 0) &&

			// bool_XnfLoaded
			(DAT_8008d6b4 != 0)
		) &&

		// if XA is playing
		(DAT_8008d708 != 0)
	 )
  {
	// XA is not finished (nor started)
    DAT_8008d6b8 = 0;

	// As of now, no XA playing
	// (exit 'start your engines' loop)
    DAT_8008d708 = 0;

	// cancel interrupt request
	// (useless, cause it is called in CDSYS_SpuDisableIRQ anyway)
    SpuSetIRQ(0);

	// CDSYS_SpuDisableIRQ
	FUN_8001ca64();

	// '\t' = 9 = CdlPause
	CdControl('\t',(u_char *)0x0,(u_char *)0x0);

	// save timer, copy of frameTimer_MainFrame_ResetDB
    DAT_8008d6ec = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1cf8);
  }
  return;
}


// CDSYS_PauseAtEnd
void FUN_8001d06c(void)

{
  // if XA is finished (according to IRQ)
  if (DAT_8008d6b8 != 0)
  {
	// CDSYS_XAPauseForce
    FUN_8001cfec();
  }
  return;
}
