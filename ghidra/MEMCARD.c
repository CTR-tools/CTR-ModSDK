// MEMCARD_SetIcon
void FUN_8003d4e4(short param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;

  // copy destination
  // overwrite psyq hand
  puVar2 = (undefined4 *)&DAT_800857a0;

  // pick a copy source
  if (param_1 == 0)
  {
	// ghost
    puVar1 = &DAT_800856a0;
  }

  else
  {
	// crash head
    puVar1 = &DAT_800855a0;
  }

  // last byte of copy (0x100)
  puVar3 = puVar1 + 0x40;

  // copy
  do {
    uVar4 = puVar1[1];
    uVar5 = puVar1[2];
    uVar6 = puVar1[3];
    *puVar2 = *puVar1;
    puVar2[1] = uVar4;
    puVar2[2] = uVar5;
    puVar2[3] = uVar6;
    puVar1 = puVar1 + 4;
    puVar2 = puVar2 + 4;
  } while (puVar1 != puVar3);
  return;
}


//calculates crc16 with polynomial p = x^16+x^12+x^5+x^0 (0x11021)
//this is a part of save game checksum calculation
//https://github.com/ShendoXT/memcardrex-plugins/blob/master/CTREdit/CTREdit/Additional/Crash Team Racing save.txt

// MEMCARD_CRC16
//param_1 - crc
//param_2 - data
uint FUN_8003d540(uint param_1,int param_2)

{
  uint uVar1;
  uint uVar2;

  //iterator i
  uVar1 = 7;

  //for (i = 7; i >= 0; i--)
  do {
    uVar2 = param_1 << 1;
    param_1 = uVar2 | param_2 >> (uVar1 & 0x1f) & 1U;

    if ((uVar2 & 0x10000) != 0) {
      param_1 = param_1 ^ 0x11021;
    }

    //i--
    uVar1 = uVar1 - 1;
  } while (-1 < (int)uVar1);

  return param_1;
}


// MEMCARD_ChecksumSave
// calculates memcard data stream checksum
// param_1 - pointer to data
// param_2 - data length (0x3e00, or 0x1680)
void FUN_8003d584(byte *param_1,int param_2)

{
  undefined2 uVar1;
  byte *pbVar2;
  undefined4 uVar3;
  int iVar4;

  //keep in mind checksum bytes are added in the end of stream

  //crc
  uVar3 = 0;
  //iterator i
  iVar4 = 0;
  //pointer to data
  pbVar2 = param_1;

  //if data length > 0
  if (0 < param_2 + -2) {
    //for each entry in data
    do {
      //i++
      iVar4 = iVar4 + 1;

      //crc = MEMCARD_CRC16
      uVar3 = FUN_8003d540(uVar3,(uint)*pbVar2);

	  //set next data entry
      pbVar2 = param_1 + iVar4;

	} while (iVar4 < param_2 + -2);
  }

  // waste, dont need to save checkpoint
  DAT_8008d8d0 = uVar3;

  // finalize checksum
  // MEMCARD_CRC16 twice
  uVar3 = FUN_8003d540(uVar3,0);
  uVar1 = FUN_8003d540(uVar3,0);

  // write checksum to data (last 2 bytes),
  // swap endians to throw off hackers,
  // which didn't really throw anyone off at all
  param_1[iVar4] = (byte)((ushort)uVar1 >> 8);
  param_1[iVar4 + 1] = (byte)uVar1;

  return;
}

// MEMCARD_ChecksumLoad
// assumed validates memcard data checksum,
// check full memcard, all 0x1680 bytes
uint FUN_8003d618(int param_1,int param_2)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;

  // previous crc
  uVar2 = DAT_8008d8d0;

  // CRC start byte
  iVar3 = DAT_8008d8b0;

  // if not the last frame of crc16
  if ((DAT_8008d8cc & 8) == 0)
  {
	// CRC end byte (start + 0x200)
    iVar5 = DAT_8008d8b0 + 0x200;
    bVar1 = false;
	
	// if checksum is not over
    if (iVar5 < param_2 + -2) goto LAB_8003d688;
  }

  // checksum is over, go to finalize
  bVar1 = true;

  // CRC end byte (last two bytes of data)
  iVar5 = param_2 + -2;

LAB_8003d688:

  // from start to end
  while (iVar3 < iVar5)
  {
	// MEMCARD_CRC16
    uVar2 = FUN_8003d540(uVar2,(uint)*(byte *)(param_1 + iVar3));
    iVar3 = iVar3 + 1;
  }

  // save last byte, as the next checksum's start byte
  DAT_8008d8b0 = iVar3;

  // new crc
  DAT_8008d8d0 = uVar2;

  // if last frame of crc16
  if (bVar1)
  {
	// finalize checksum
	// MEMCARD_CRC16 twice
    uVar2 = FUN_8003d540(uVar2,(uint)*(byte *)(param_1 + iVar3));
	iVar3 = FUN_8003d540(uVar2,(uint)*(byte *)(param_1 + iVar3 + 1));

	// return if it worked or not
	uVar4 = (uint)(iVar3 != 0);
  }

  // if not last frame of crc16
  else
  {
	// return 7, which means repeat step
    uVar4 = 7;
  }
  return uVar4;
}


// MEMCARD_StringInit
// param1 - slotIndex
uint * FUN_8003d6e8(uint param_1,uint *param_2)

{
  // if no paramter given
  if (param_2 == (uint *)0x0)
  {
	// "bu00:\0"
    param_2 = &DAT_8008d414;
  }

  // set "buXX"
  // where XX depends on param_1
  *param_2 = (((int)param_1 >> 4 & 1U) + 0x30) * 0x10000 |
             ((param_1 & 3) + 0x30) * 0x1000000 | 0x7562;

  // set bytes [4,5] with a short,
  // which sets ':' and '\0'
  *(undefined2 *)(param_2 + 1) = 0x3a;

  return param_2;
}


// MEMCARD_StringSet
// param2 slotIndex
void FUN_8003d730(char *param_1,undefined4 param_2,char *param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;

  // MEMCARD_StringInit
  FUN_8003d6e8(param_2,param_1);

  // index
  iVar3 = 0;

  // destination string
  if (*param_1 != '\0') {
    iVar2 = 1;
    do
	{
	  // loop counter
      iVar3 = iVar2;
      iVar2 = iVar3 + 1;

	  // loop to end of string
    } while (param_1[iVar3] != '\0');
  }

  // source string
  cVar1 = *param_3;

  // copy string from param_3 to param_1
  while ((cVar1 != '\0' && (iVar3 < 0x3f))) {
    cVar1 = *param_3;
    param_3 = param_3 + 1;
    param_1[iVar3] = cVar1;
    cVar1 = *param_3;
    iVar3 = iVar3 + 1;
  }
  param_1[iVar3] = '\0';
  return;
}


//8003d7d8 - initializes memcard stuff - MEMCARD_Init
//- creates 8 events (4 per card?)
//- calls InitCARD and StartCARD
void FUN_8003d7d8(void)

{
  // This section was copy/pasted by Naughty Dog,
  // psx\sample\memcard\CARD\CARD.C lines 84 to 101

  // -------------------------------------------
  EnterCriticalSection();
  DAT_8008d8d4 = OpenEvent(SwCARD,EvSpIOE,		EvMdNOINTR,	NULL);
  DAT_8008d8c4 = OpenEvent(SwCARD,EvSpERROR,	EvMdNOINTR,	NULL);
  DAT_8008d8e0 = OpenEvent(SwCARD,EvSpTIMOUT,	EvMdNOINTR,	NULL);
  DAT_8008d8c0 = OpenEvent(SwCARD,EvSpNEW,		EvMdNOINTR,	NULL);
  DAT_8008d8c8 = OpenEvent(HwCARD,EvSpIOE,		EvMdNOINTR,	NULL);
  DAT_8008d8b4 = OpenEvent(HwCARD,EvSpERROR,	EvMdNOINTR,	NULL);
  DAT_8008d8dc = OpenEvent(HwCARD,EvSpTIMOUT,	EvMdNOINTR,	NULL);
  DAT_8008d8bc = OpenEvent(HwCARD,EvSpNEW,		EvMdNOINTR,	NULL);
  EnableEvent(DAT_8008d8d4);
  EnableEvent(DAT_8008d8c4);
  EnableEvent(DAT_8008d8e0);
  EnableEvent(DAT_8008d8c0);
  EnableEvent(DAT_8008d8c8);
  EnableEvent(DAT_8008d8b4);
  EnableEvent(DAT_8008d8dc);
  EnableEvent(DAT_8008d8bc);
  ExitCriticalSection();
  // -------------------------------------------

  InitCARD(0);
  StartCARD();
  _bu_init();

  // This tells us a memory card exists,
  // If it is set to 0 with Cheat Engine,
  // the game will think the card is unformatted
  DAT_8008d8cc = 1;
  return;
}


//8003d95c - closes memcard stuff - MEMCARD_Close
void FUN_8003d95c(void)

{
  // This function was copy/pasted by Naughty Dog,
  // psx\sample\memcard\CARD\CARD.C lines 355 to 365

  StopCARD();
  EnterCriticalSection();
  CloseEvent(DAT_8008d8d4);
  CloseEvent(DAT_8008d8c4);
  CloseEvent(DAT_8008d8e0);
  CloseEvent(DAT_8008d8c0);
  CloseEvent(DAT_8008d8c8);
  CloseEvent(DAT_8008d8b4);
  CloseEvent(DAT_8008d8dc);
  CloseEvent(DAT_8008d8bc);
  ExitCriticalSection();

  return;
}


//8003d9ec - tests for 1st slot events - MEMCARD_GetNextSwEvent
//- basically gets index of first triggered event or returns 7, which is no event i guess. 7 is 3 bits.
undefined4 FUN_8003d9ec(void)

{
  long lVar1;
  undefined4 uVar2;

  // SwIOE (processing done)
  lVar1 = TestEvent(DAT_8008d8d4);
  uVar2 = 0;
  if (lVar1 != 1) 
  {
	// SwERROR (bad card)
    lVar1 = TestEvent(DAT_8008d8c4);
    uVar2 = 1;
    if (lVar1 != 1) 
	{
	  // SwTIMEOUT (no card)
      lVar1 = TestEvent(DAT_8008d8e0);
      if (lVar1 == 1) {
        uVar2 = 2;
      }
      else 
	  {
		// SwNEWCARD
        lVar1 = TestEvent(DAT_8008d8c0);
        uVar2 = 3;
        if (lVar1 != 1) {
          uVar2 = 7;
        }
      }
    }
  }
  return uVar2;
}


//8003da68 - tests for 2nd slot events - MEMCARD_GetNextHwEvent
//- same as above but for other 4 events
undefined4 FUN_8003da68(void)

{
  long lVar1;
  undefined4 uVar2;

  // HwIOE (processing done)
  lVar1 = TestEvent(DAT_8008d8c8);
  uVar2 = 0;
  if (lVar1 != 1) 
  {
	// HwERROR (bad card)
    lVar1 = TestEvent(DAT_8008d8b4);
    uVar2 = 1;
    if (lVar1 != 1) 
	{
	  // HwTIMEOUT (no card)
      lVar1 = TestEvent(DAT_8008d8dc);
      if (lVar1 == 1) {
        uVar2 = 2;
      }
      else 
	  {
		// HwNEWCARD
        lVar1 = TestEvent(DAT_8008d8bc);
        uVar2 = 3;
        if (lVar1 != 1) {
          uVar2 = 7;
        }
      }
    }
  }
  return uVar2;
}


//8003dae4 - waits for event on slot1 to happen and returns index - MEMCARD_WaitForHwEvent
//- loops while there is not a single true for mc1 events
//- only called once, wonder how that doesn't halt the exection. or maybe it does, are there hangs when save/load happens?
undefined4 FUN_8003dae4(void)

{
  long lVar1;

  do 
  {
	// HwIOE (processing done)
    lVar1 = TestEvent(DAT_8008d8c8);
    if (lVar1 == 1) {
      return 0;
    }
	
	// HwERROR (bad card)
    lVar1 = TestEvent(DAT_8008d8b4);
    if (lVar1 == 1) {
      return 1;
    }
	
	// HwTIMEOUT (no card)
    lVar1 = TestEvent(DAT_8008d8dc);
    if (lVar1 == 1) {
      return 2;
    }
	
	// HwNEWCARD
    lVar1 = TestEvent(DAT_8008d8bc);
  } while (lVar1 != 1);
  return 3;
}


//8003db54 - tests all events until no events left for both cards - MEMCARD_SkipEvents
//maybe it's a kind of clearing function?
undefined4 FUN_8003db54(void)

{
  int iVar1;

  do
  {
	// MEMCARD_GetNextSwEvent
    iVar1 = FUN_8003d9ec();
  } while (iVar1 != 7);

  do
  {
	// MEMCARD_GetNextHwEvent
    iVar1 = FUN_8003da68();
  } while (iVar1 != 7);

  return 7;
}


// MEMCARD_NewTask
// param1 slotIndex
// param2 name
// param3 pointer to memcard
// param4 memcard size
undefined4 FUN_8003db98(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  // card slot
  DAT_8008d8b8 = param_1;

  // MEMCARD_StringSet
  FUN_8003d730(&DAT_800990a4,param_1,param_2);

  // pointer to memcard 800992e4
  DAT_8008d408 = param_3;

  // reset to 8 attempts before quitting
  DAT_8008d410 = 8;

  // memcard size (0x1680)
  DAT_8008d8a8 = param_4;

  return 0;
}


// close memcard file
void FUN_8003dbf8(void)
{
  // if file is open
  if (DAT_8008d40c != -1)
  {
	// close the file
    close(DAT_8008d40c);

	// no file is open
    DAT_8008d40c = -1;
  }
  DAT_8008d404 = 0;
  return;
}


// Read from memory card
// parameters are start and end offsets
undefined4 FUN_8003dc30(long param_1,long param_2)

{
  long lVar1;

  // seek to start offset
  lVar1 = lseek(DAT_8008d40c,param_1,0);

  // read to memcard buffer in RAM, param_2 size
  if ((lVar1 != -1) && (lVar1 = read(DAT_8008d40c,DAT_8008d408,param_2), lVar1 != -1)) {
    return 7;
  }

  // close memcard file
  FUN_8003dbf8();

  return 1;
}


// Write to memory card
// start offset, pointer to data, end offset
undefined4 FUN_8003dc9c(long param_1,void *param_2,long param_3)

{
  long lVar1;

  // seek to start offset
  lVar1 = lseek(DAT_8008d40c,param_1,0);

  // write to memcard buffer in RAM, param_3 size
  if ((lVar1 != -1) && (lVar1 = write(DAT_8008d40c,param_2,param_3), lVar1 != -1)) {
    return 7;
  }

  // close memcard file
  FUN_8003dbf8();

  return 1;
}


// MEMCARD_GetFreeBytes
// param1 slotIndex
void FUN_8003dd10(undefined4 param_1)

{
  DIRENTRY *pDVar1;
  DIRENTRY *pDVar2;
  int iVar3;
  DIRENTRY DStack56;

  // MEMCARD_StringSet
  FUN_8003d730(&DAT_800990a4,param_1,&DAT_8008d41c);

  // bytes used on memory card
  iVar3 = 0;

  // 800990a4
  // string for directory and file of save that is in use
  pDVar1 = firstfile(&DAT_800990a4,&DStack56);

  pDVar2 = &DStack56;
  while (pDVar1 == pDVar2)
  {
	// add to number of bytes used
    iVar3 = iVar3 + (DStack56.size + 0x1fffU & 0xffffe000);

	pDVar2 = nextfile(&DStack56);
  }

  // bytes left on memcard = 128kb - used size
  DAT_8008d8ac = 0x1e000 - iVar3;

  return;
}



int FUN_8003ddac(void)

{
  long lVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;

  switch(DAT_8008d404) {

  case 1:

	// MEMCARD_GetNextSwEvent
	iVar3 = FUN_8003d9ec();

    if (iVar3 == 0)
	{
	  // If this is the first frame of the main game loop,
	  // after all initialization is done
      if ((DAT_8008d8cc & 1) != 0)
	  {
		// allow the "switch" statement to go to stage 2
        DAT_8008d404 = 2;

		// MEMCARD_SkipEvents do something wtih both memcards if they're present, 
        FUN_8003db54();

		// ??
		// spam read until it works?
        do {
          lVar1 = _card_load(DAT_8008d8b8);
        } while (lVar1 != 1);

        return 7;
      }
      if ((DAT_8008d8cc & 2) == 0)
	  {
		// zero free bytes on memcard
        DAT_8008d8ac = 0;

		iVar3 = 5;
      }
    }

    else {
      if (iVar3 != 3) {
        if (iVar3 != 7) {
          DAT_8008d404 = 0;

		  // zero free bytes on memcard
          DAT_8008d8ac = 0;

          return iVar3;
        }
        return 7;
      }
      FUN_8003db54();
      do {
        lVar1 = _card_clear(DAT_8008d8b8);
      } while (lVar1 != 1);
      iVar3 = FUN_8003dae4();
      if (iVar3 == 0) {
        DAT_8008d404 = 2;
        FUN_8003db54();
        do {
          lVar1 = _card_load(DAT_8008d8b8);
        } while (lVar1 != 1);
        return 7;
      }
    }

    goto LAB_8003df38;

  case 2:

	// MEMCARD_GetNextSwEvent
	iVar3 = FUN_8003d9ec();

    if (iVar3 == 0) {
      DAT_8008d404 = 0;
      DAT_8008d8cc = DAT_8008d8cc & 0xfffffffe | 2;

	  // MEMCARD_GetFreeBytes
      FUN_8003dd10(DAT_8008d8b8);

      return 3;
    }
    if (iVar3 == 3) {
      DAT_8008d404 = 0;
      DAT_8008d8cc = DAT_8008d8cc & 0xfffffffc;
      return 5;
    }
    if (iVar3 == 7) {
      return 7;
    }
LAB_8003df38:
    DAT_8008d404 = 0;
    break;

  case 3:

	// MEMCARD_GetNextSwEvent
    iVar3 = FUN_8003d9ec();

    if (iVar3 == 0)
	{
	  // allow "switch" statement to go to stage 4
      DAT_8008d404 = 4;

	  DAT_8008d8d8 = (((uint)(byte)DAT_8008d408[2] & 0xf) + 1) * 0x80;

	  // Read memory card
      uVar2 = FUN_8003dc30(DAT_8008d8d8,DAT_8008d8a8);

	  if ((DAT_8008d8d8 + DAT_8008d8a8 + 0x1fff >> 0xd < (int)(uint)(byte)DAT_8008d408[3]) &&
         (1 < DAT_8008d8d8 + DAT_8008d8a8 * 2 + 0x1fff >> 0xd)) {
        DAT_8008d8cc = DAT_8008d8cc & 0xfffffffb;
        return uVar2;
      }
      DAT_8008d8cc = DAT_8008d8cc | 4;
      return uVar2;
    }

    if (iVar3 == 7) {
      return 7;
    }

    if (0 < DAT_8008d410) {
      iVar4 = 0;
      iVar3 = 0x80;

	  // reduce remaining attempts
      DAT_8008d410 = DAT_8008d410 + -1;

	  // go to read card
      goto LAB_8003e010;
    }

	// go to close file
    goto LAB_8003e1fc;

  case 4:
  case 6:

    // MEMCARD_GetNextSwEvent
    iVar3 = FUN_8003d9ec();

    if (iVar3 == 0) {
      DAT_8008d8b0 = 0;
      DAT_8008d8d0 = 0;
      DAT_8008d404 = DAT_8008d404 + 1;
      if ((DAT_8008d8cc & 8) == 0) {
        DAT_8008d8b0 = 0;
        DAT_8008d8d0 = 0;
        return 7;
      }
      goto switchD_8003dde0_caseD_5;
    }

    if (iVar3 == 7) {
      return 7;
    }

	if (0 < DAT_8008d410) {
      iVar4 = DAT_8008d8d8 + (DAT_8008d404 + -4) * DAT_8008d8a8;
      iVar3 = DAT_8008d8a8;

	  // reduce remaining attempts
      DAT_8008d410 = DAT_8008d410 + -1;

	  // go to read card
      goto LAB_8003e010;
    }

	// go to close file
    goto LAB_8003e1fc;

  case 5:
  case 7:
switchD_8003dde0_caseD_5:

	// MEMCARD_ChecksumLoad
	// pointer to memory card, and size
    iVar3 = FUN_8003d618(DAT_8008d408,DAT_8008d8a8);

    if (iVar3 != 0)
	{
	  // if checksumLoad returned 7, then the checksum
	  // is not finished processing, it will continue next frame
      if (iVar3 == 7) {
        return 7;
      }

	  // at this point, assume checksum succeeded (return 1)

      if (((DAT_8008d8cc & 4) == 0) && (iVar4 = DAT_8008d404 + -3, DAT_8008d404 < 7))
	  {
		// Make "switch" statement go to "next" stage
        DAT_8008d404 = DAT_8008d404 + 1;

        iVar4 = DAT_8008d8d8 + iVar4 * DAT_8008d8a8;
        iVar3 = DAT_8008d8a8;
LAB_8003e010:

		// Read memory card
        uVar2 = FUN_8003dc30(iVar4,iVar3);

        return uVar2;
      }
    }
LAB_8003e1fc:
	// close memcard file
    FUN_8003dbf8();
    break;
  default:
    iVar3 = 1;
    break;
  case 9:
  case 10:
  case 0xb:

	// MEMCARD_GetNextSwEvent
    iVar3 = FUN_8003d9ec();

    if (iVar3 == 0)
	{
      if ((DAT_8008d404 != 9) && ((10 < DAT_8008d404 || ((DAT_8008d8cc & 4) != 0))))
	  {
		// close memcard file
        FUN_8003dbf8();

		// MEMCARD_GetFreeBytes
        FUN_8003dd10(DAT_8008d8b8);

        return 0;
      }
      iVar3 = DAT_8008d404 + -9;
      DAT_8008d404 = DAT_8008d404 + 1;
LAB_8003e1e4:
      iVar4 = DAT_8008d8d8 + iVar3 * DAT_8008d8a8;

	  // pointer to memory card bytes
      puVar5 = DAT_8008d408;

	  // size, 0x1680 bytes
      iVar3 = DAT_8008d8a8;
    }

	else
	{
      if (iVar3 == 7) {
        return 7;
      }

	  // reduce remaining number of attempts
	  iVar4 = DAT_8008d410 + -1;

	  // if out of attempts, go to close file
      if (DAT_8008d410 < 1) goto LAB_8003e1fc;

      iVar3 = DAT_8008d404 + -10;
      DAT_8008d410 = iVar4;
      if (DAT_8008d404 != 9) goto LAB_8003e1e4;
      iVar4 = 0;

	  // pointer to memory card icon
	  // psyq hand
	  puVar5 = &DAT_800857a0;

	  // 256 bytes, 0x100
      iVar3 = DAT_8008d8d8;
    }

	// write to memory card
    iVar3 = FUN_8003dc9c(iVar4,puVar5,iVar3);
    break;
  case 0xd:
    DAT_8008d404 = 0;
    iVar3 = 1;
    break;
  case 0xe:
    DAT_8008d404 = 0;
    iVar3 = 0;
  }
  return iVar3;
}


// MEMCARD_GetInfo
undefined4 FUN_8003e238(long param_1)

{
  undefined4 uVar1;
  long lVar2;

  if (DAT_8008d404 == 0) {
    FUN_8003db54();
    DAT_8008d404 = 1;
    DAT_8008d8b8 = param_1;

	// loop until check is "submitted",
	// result is not "returned", result
	// is found in SwCARD descriptor/event (see libref)
	do
	{
	  // check if card is connected
      lVar2 = _card_info(param_1);

	} while (lVar2 != 1);

	DAT_8008d410 = 8;
    uVar1 = 7;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}


// MEMCARD_Load
// ghidra couldn't detect parameters,
// because they were passed directly from this func to another
undefined4 FUN_8003e29c(param1, param2, param3, param4, param5)

{
  int iVar1;
  undefined4 uVar2;
  uint param_5;

  if (
		(DAT_8008d404 == 0) &&

		(
			// MEMCARD_NewTask
			iVar1 = FUN_8003db98(param1, param2, param3, param4, param5),

			// this will always be true
			iVar1 == 0
		)
	  )
  {
	// 800990a4
	// string for directory and file of save that is in use

	// 0x8001, in sys/fcntl.h
	// 0x8000 = FASYNC, for asynchronous I/O
	// 0x0001 = FREAD, for reading

    DAT_8008d40c = open(&DAT_800990a4,0x8001);

	// if open failed
    if (DAT_8008d40c == -1)
	{
	  // close memcard file
      FUN_8003dbf8();
      uVar2 = 6;
    }
    else {
      if ((param_5 & 2) == 0)
	  {
		// dont process crc16 to the end of memory,
		// just the next 0x200 bytes (async)
        DAT_8008d8cc = DAT_8008d8cc & 0xfffffff7;
      }
      else
	  {
		// process crc16 to the end of memory
        DAT_8008d8cc = DAT_8008d8cc | 8;
      }
      DAT_8008d404 = 3;

	  // Read memory card
      uVar2 = FUN_8003dc30(0,0x80);
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}


// MEMCARD_Save
undefined4 FUN_8003e344(undefined4 param_1,undefined4 param_2,
						char *param_3,undefined4 param_4,int param_5,
						uint param_6)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;

  if (DAT_8008d404 == 0)
  {
    DAT_8008d8d8 = 0x100;

	// MEMCARD_NewTask
	iVar2 = FUN_8003db98(param_1,param_2,param_4,param_5);

	// this will always be true
	if (iVar2 == 0)
	{
      if (((param_6 & 1) == 0) && (1 < DAT_8008d8d8 + param_5 * 2 + 0x1fff >> 0xd)) {
        DAT_800857a3 = (byte)(DAT_8008d8d8 + param_5 + 0x1fff >> 0xd);
        DAT_8008d8cc = DAT_8008d8cc | 4;
      }
      else {
        DAT_8008d8cc = DAT_8008d8cc & 0xfffffffb;
        DAT_800857a3 = (byte)(DAT_8008d8d8 + param_5 * 2 + 0x1fff >> 0xd);
      }
      iVar2 = 0;
      do {
        iVar4 = iVar2 + 2;
        (&DAT_800857a4)[iVar2] = 0x81;
        (&DAT_800857a5)[iVar2] = 0x40;
        iVar2 = iVar4;
      } while (iVar4 < 0x40);
      cVar1 = *param_3;
      iVar2 = 0;
      while ((cVar1 != '\0' && (iVar2 < 0x40))) {
        cVar1 = *param_3;
        param_3 = param_3 + 1;
        (&DAT_800857a4)[iVar2] = cVar1;
        cVar1 = *param_3;
        iVar2 = iVar2 + 1;
      }

	  // MEMCARD_ChecksumSave
	  // ptrData, size of data
	  // (8009aa50 and 8009aa54)
      FUN_8003d584(param_4,param_5);

	  // 800990a4
	  // string for directory and file of save that is in use

	  // In sys/fcntl.h
	  // 0x200 is FCREAT, create if it does not exist,
	  // DAT_800857a3 handles read or write

      DAT_8008d40c = open(&DAT_800990a4,(uint)DAT_800857a3 << 0x10 | 0x200);

	  if (DAT_8008d40c != -1) {
        close(DAT_8008d40c);
        DAT_8008d40c = -1;
      }

	  // 800990a4
	  // string for directory and file of save that is in use

	  // 0x8002, in sys/fcntl.h
	  // 0x8000 = FASYNC, for asynchronous I/O
	  // 0x0001 = FWRITE, for writing

      DAT_8008d40c = open(&DAT_800990a4,0x8002);

      if (DAT_8008d40c != -1) {
        DAT_8008d404 = 9;

		// write to memory card, given pointer to icon
		// and the size of the icon, psyq hand
        uVar3 = FUN_8003dc9c(0,&DAT_800857a0,DAT_8008d8d8);

        return uVar3;
      }

	  // close memcard file
      FUN_8003dbf8(0);
      return 4;
    }
  }
  return 1;
}


// MEMCARD_Format
// param1 slotIndex
undefined4 FUN_8003e51c(long param_1)

{
  char *pcVar1;
  long lVar2;
  undefined4 uVar3;

  if (DAT_8008d404 == 0)
  {
	// MEMCARD_StringInit
    pcVar1 = (char *)FUN_8003d6e8(param_1,0);

	lVar2 = format(pcVar1);
    uVar3 = 1;
    if (lVar2 == 1) {
      DAT_8008d404 = 2;

	  // slotIndex
      DAT_8008d8b8 = param_1;

	  // MEMCARD_SkipEvents
      FUN_8003db54();

      do {
        lVar2 = _card_load(DAT_8008d8b8);
      } while (lVar2 != 1);

	  DAT_8008d410 = 8;
      uVar3 = 7;
    }
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

// MEMCARD_IsFile
// param1 slotIndex
// param2 saveName
undefined4 FUN_8003e59c(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  char acStack72 [64];

  // MEMCARD_StringSet
  FUN_8003d730(acStack72,param_1,param_2);

  // 0x8002, in sys/fcntl.h
  // 0x8000 = FASYNC, for asynchronous I/O
  // 0x0001 = FWRITE, for writing
  DAT_8008d40c = open(acStack72,0x8002);

  if (DAT_8008d40c == -1) {
    uVar1 = 6;
  }
  else {
    close(DAT_8008d40c);
    DAT_8008d40c = -1;
    uVar1 = 0;
  }
  return uVar1;
}


// MEMCARD_FindFirstGhost
undefined * FUN_8003e600(undefined4 param_1,undefined4 param_2)

{
  DIRENTRY *pDVar1;
  DIRENTRY DStack48;

  // param2 = BASCUS-94426G*

  if (DAT_8008d404 == 0)
  {
    // MEMCARD_StringSet
    FUN_8003d730(&DAT_800990a4,param_1,param_2);

    // 800990a4
    // string for directory and file of save that is in use
	pDVar1 = firstfile(&DAT_800990a4,&DStack48);

	if (pDVar1 == &DStack48) {
      DAT_8008d404 = 0xf;
      strcpy();
      return &DAT_800990c4;
    }
  }
  return (undefined *)0;
}


// MEMCARD_FindNextGhost
undefined * FUN_8003e678(void)

{
  DIRENTRY *pDVar1;
  DIRENTRY DStack48;

  if (DAT_8008d404 == 0xf) {
    pDVar1 = nextfile(&DStack48);
    if (pDVar1 == &DStack48) {
      strcpy();
      return &DAT_800990c4;
    }
    DAT_8008d404 = 0;
  }
  return (undefined *)0;
}


// MEMCARD_EraseFile (unused)
// param1 slotIndex
undefined4 FUN_8003e6d4(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  long lVar2;
  char acStack72 [64];

  if (DAT_8008d404 == 0)
  {
	// MEMCARD_StringSet
    FUN_8003d730(acStack72,param_1,param_2);

	DAT_8008d404 = 0xe;
    lVar2 = erase(acStack72);
    if (lVar2 != 1) {
      DAT_8008d404 = 0xd;
    }

	// MEMCARD_GetFreeBytes
	FUN_8003dd10(param_1);

    uVar1 = 7;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}
