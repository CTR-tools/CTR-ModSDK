// MainDB_GetClipSize
// param_1 is levelID
// param_2 is numPlyrCurrGame
undefined4 FUN_80034960(undefined4 param_1,int param_2)

{
  switch(param_1) {

  // If papu's pyramid or polar pass
  case 5:
  case 0xc:

    // if 3 or 4 players
    if (2 < param_2) {
      return 2500;
    }
    break;

  // if sewer speedway
  case 8:
    return 6000;

  // if mystery caves
  case 9:
    return 2500;

  // main menu
  case 0x27:
    return 0x10;

  // adventure character selection
  case 0x28:
    return 24000;
  }
  return 3000;
}


// MainDB_PrimMem
// param_1 is &gGT->DB[x].primMem
void FUN_800349c4(uint *param_1,uint param_2)

{
  uint uVar1;

  // MEMPACK_AllocMem
  uVar1 = FUN_8003e874(param_2,s_PrimMem_8008d2b8);

  // size
  *param_1 = param_2;

  // unk 0x18
  param_1[6] = uVar1;

  // curr
  param_1[3] = uVar1;

  // start
  param_1[1] = uVar1;

  // start + size
  uVar1 = uVar1 + (param_2 & 0xfffffffc);

  // end
  param_1[2] = uVar1;

  // end - 0x100 (why?)
  param_1[4] = uVar1 - 0x100;
  return;
}

// MainDB_OTMem
// param_1 is &gGT->DB[x].otMem
void FUN_80034a28(uint *param_1,uint param_2)

{
  uint uVar1;

  // MEMPACK_AllocMem
  uVar1 = FUN_8003e874(param_2,s_OTMem_8008d2c0);

  // size
  *param_1 = param_2;

  // curr
  param_1[3] = uVar1;

  // start
  param_1[1] = uVar1;

  // end
  param_1[2] = uVar1 + (param_2 & 0xfffffffc);

  return;
}

// drawsync callback
void FUN_80034a80(void)

{
  // if OT was submitted
  if (*(char *)(8008D2AC + 0x1d30) == '\x01')
  {
	// now it's finished
    *(undefined *)(8008D2AC + 0x1d30) = 0;
  }
  return;
}

// vsync callback
void FUN_80034aa4(void)

{
  undefined *puVar1;
  long lVar2;
  uint uVar3;

  puVar1 = PTR_DAT_8008d2ac;
  uVar3 = *(uint *)PTR_DAT_8008d2ac;

  // frame timer
  *(int *)(PTR_DAT_8008d2ac + 0x1ce4) = *(int *)(PTR_DAT_8008d2ac + 0x1ce4) + 1;

  // If game is not paused
  if ((uVar3 & 0xf) == 0) {

	// Frame Counter for particles
	*(int *)(puVar1 + 0x1cf0) = *(int *)(puVar1 + 0x1cf0) + 1;
  }

  // frame duplicator
  DAT_8008d2b4 = DAT_8008d2b4 + -1;

  // count vsync calls between drawsync
  *(int *)(PTR_DAT_8008d2ac + 0x1ce0) = *(int *)(PTR_DAT_8008d2ac + 0x1ce0) + 1;

  // elapsed units since previous vsync
  // 1 unit = 1/16th millisecond
  lVar2 = GetRCnt(0xf2000001);

  // increment system
  // 1 second = ~16,000 units
  DAT_8008d988 = DAT_8008d988 + lVar2;

  // reset timer
  ResetRCnt(0xf2000001);

  // howl_PlayAudio_Update
  FUN_8002c208();

  // GAMEPAD_PollVsync
  FUN_80025410(PTR_DAT_8008d2b0);

  return;
}


//toggles sound (used by pause menu)
//0 = unpause, 1 = pause
//MainFrame_TogglePauseAudio
void FUN_80034b48(int param_1)

{
  //if we want to unpause
  if (param_1 == 0) {
    //if sound is paused
    if (DAT_8008d8a4 != 0)
	{
      // howl_StopAudio (stops menu sounds)
	  // keep backup,
	  // keep music (no music to stop),
	  // stop all fx
      FUN_8002c8a8(0,0,1);

	  // unpause audio (restore gameplay sounds)
      FUN_8002c784();

	  //set sound to unpaused
      DAT_8008d8a4 = 0;
    }
  }
  else {
    //if sound is paused
    if (DAT_8008d8a4 == 0)
	{
      // OtherFX_Stop2
      FUN_80028844(1);

	  //pause audio
      FUN_8002c510();

	  //set sound to paused
      DAT_8008d8a4 = 1;
    }
  }
  return;
}


// MainFrame_ResetDB
void FUN_80034bbc(int param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  // LOAD_Hub_Main
  // check if secondary lev needs
  // to load, or swap, param given is bigfile
  FUN_80033318(DAT_8008d86c);

  // 1 - [swapchain index]
  iVar3 = 1 - *(int *)(param_1 + 0xc);

  // set pointer to DCB
  *(int *)(param_1 + 0x10) = param_1 + iVar3 * 0xa4 + 0x18;

  // flip the swapchain index
  *(int *)(param_1 + 0xc) = iVar3;

  // number of frames drawn
  *(int *)(param_1 + 0x1cf8) = *(int *)(param_1 + 0x1cf8) + 1;

  *(undefined *)(*(int *)(param_1 + 0x10) + 0x70) = 0;

  // Reeset PrimMem
  // CurrByte = FirstByte
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x80) =
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x78);

  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x88) = 0;

  // Reset OTMem
  // CurrByte = FirstByte
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x9c) =
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x94);

  // Empty placeholder, not a Ghidra fail
  FUN_80021c8c();

  // Empty placeholder, not a Ghidra fail
  FUN_80022b94(param_1);

  ClearOTagR(*(undefined4 *)(param_1 + *(int *)(param_1 + 0xc) * 4 + 0x18c8),

				// numPlyrCurrGame << 10 | 6
               (uint)(byte)PTR_DAT_8008d2ac[0x1ca8] << 10 | 6);

  puVar1 = PTR_DAT_8008d2ac;

  // loop iteration counter
  iVar4 = 0;

  iVar3 = param_1;

  // if numPlyrCurrGame is not zero
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0')
  {
	// Initialize OTMem of each player, each 0x1000 apart,
	// overflowing OTMem of one player will impact graphics of another

	// for iVar4 = 0; iVar4 < numPlyrCurrGame; iVar4++
    do {
      iVar2 = (uint)(byte)puVar1[0x1ca8] - iVar4;

	  // increment loop iteration counter
      iVar4 = iVar4 + 1;

	  // pointer to PushBuffer->OTMem (25c-168=0xf4)
      *(int *)(iVar3 + 0x25c) =

			// ptrOT depending on swapchain index, plus playerIndex * 0x1000
           *(int *)(param_1 + *(int *)(param_1 + 0xc) * 4 + 0x18c8) + (iVar2 + -1) * 0x1000 + 0x18;

	  // next pushBuffer
      iVar3 = iVar3 + 0x110;

    } while (iVar4 < (int)(uint)(byte)puVar1[0x1ca8]);
  }

  // Initialize OTMem of non-present players to be out of bounds

  // if less than 4 players (yes, I'm certain)
  if (iVar4 < 4)
  {
	// pushBuffer (at max [3])
    iVar3 = iVar4 * 0x110 + param_1;

	// for iVar4 = iVar4 (not typo); iVar4 < 4; iVar4++
    do {

	  // increment loop counter
      iVar4 = iVar4 + 1;

	  // pointer to PushBuffer->OTMem (25c-168=0xf4)
      *(int *)(iVar3 + 0x25c) =

			// the OTMem after 3rd player,
			// pointer to OTMem of (non-present) 4th player
			*(int *)(param_1 + *(int *)(param_1 + 0xc) * 4 + 0x18c8) + 0x3018;

	  // next pushBuffer
      iVar3 = iVar3 + 0x110;

    } while (iVar4 < 4);
  }

  // something to do with OT pointers in GameTracker
  iVar3 = *(int *)(param_1 + *(int *)(param_1 + 0xc) * 4 + 0x18c8) + 4;

  // pointer to OT mem
  *(int *)(param_1 + 0x147c) = iVar3;

  // setting OT pointer in DCB
  *(int *)(*(int *)(param_1 + 0x10) + 0xa0) = iVar3;
  return;
}


// MainFrame_GameLogic
// param1 = 8008d2ac - main game struct
// param2 = 8008d2b0 - gamepad struct
void FUN_80034d54(uint *param_1,int param_2)

{
  bool bVar1;
  short sVar2;
  code *pcVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined *puVar9;
  int iVar10;
  uint *puVar11;

  // assume game is paused
  bVar1 = true;

  // If game is not paused
  if ((*param_1 & 0xf) == 0)
  {
	// game is not paused
    bVar1 = false;

	// pointer to first Player thread
    iVar10 = *(int *)(PTR_DAT_8008d2ac + 0x1b2c);

	// pointer to P1's pushBuffer struct (pos, size, etc)
    puVar9 = PTR_DAT_8008d2ac + 0x168;

	// loop through players
    while (iVar10 != 0) {
                    // WARNING: Read-only address (ram,0x8008d874) is written

	  //iVar7 = Racer struct Pointer
	  // grab object from thread
      iVar7 = *(int *)(iVar10 + 0x30);

	  // clockSend? what is clockSend?
      if (*(char *)(iVar7 + 0x45) != '\0')
	  {
		// decrease timer
        *(char *)(iVar7 + 0x45) = *(char *)(iVar7 + 0x45) + -1;
      }

      if (*(byte *)(iVar7 + 0x367) == 0)
	  {
        //if racer has not received a clock effect
        if (*(short *)(iVar7 + 0xc) == 0)
		{
          uVar5 = (uint)*(byte *)(iVar7 + 0x45);
          if (*(byte *)(iVar7 + 0x45) == 0) {
            if ((*(ushort *)(PTR_DAT_8008d2ac + 0x2570) & 1) == 0) goto LAB_80034e74;
            uVar5 = 10000;
          }
        }

		//if racer is receiving a clock effect
        else
		{
          //if racer finished the race
          if ((*(uint *)(iVar7 + 0x2c8) & 0x2000000) != 0)
		  {
            //prevent clock effect from happening
            *(undefined2 *)(iVar7 + 0xc) = 0;
          }
          uVar5 = SEXT24(*(short *)(iVar7 + 0xc));
        }

		// DISPLAY_Blur_Main
        FUN_80023d4c(puVar9,uVar5);
      }

      else
	  {
		// DISPLAY_Blur_Main
        FUN_80023d4c(puVar9,-(uint)*(byte *)(iVar7 + 0x367));

		// decrease timer
        *(char *)(iVar7 + 0x367) = *(char *)(iVar7 + 0x367) + -1;
      }
LAB_80034e74:

	  // player -> next
      iVar10 = *(int *)(iVar10 + 0x10);

	  // increment pointer to next pushBuffer struct
      puVar9 = puVar9 + 0x110;
    }

	// frame timer since boot
    param_1[0x73b] = param_1[0x73b] + 1;

	// not pushBuffer struct anymore, now main game struct
    puVar9 = PTR_DAT_8008d2ac;

	// frame timer since end of loading
    param_1[0x73f] = param_1[0x73f] + 1;

    *(undefined4 *)(puVar9 + 0x1cd4) = 0;

	// Timer_GetTime_Elapsed
	// basically, get root counter and divide by ~5
    iVar10 = FUN_8004b41c(param_1[0x742],&param_1[0x742]);

	// multiply 32, divide 100
	// divide by ~3
	uVar5 = (iVar10 << 5) / 100;

	// 1000 * 16000 units / 5246 / 3 = 1000ms
	// 1000 * elapsedUnits / 5246 / 3 = milliseconds

	// elapsed milliseconds per frame
    param_1[0x741] = uVar5;

	// if negative time elapsed somehow
    if ((int)uVar5 < 0)
	{
	  // assume 32ms passed
      param_1[0x741] = 0x20;
    }

	// 64ms = 15fps
	// if more than 64 milliseconds elapsed
    if (0x40 < (int)param_1[0x741])
	{
	  // assume only 64 milliseconds passed,
	  // let the game slow down, so physics dont break
      param_1[0x741] = 0x40;
    }

	// 32ms = 30fps
	// if millisecond timers should be forced to be frame timers
	if ((*(uint *)(PTR_DAT_8008d2ac + 4) & 0xf) != 0)
	{
	  // assume elapsed time is 32 milliseconds
      param_1[0x741] = 0x20;
    }

	// milliseconds since end of loading
    param_1[0x740] = param_1[0x740] + param_1[0x741];

    puVar9 = PTR_DAT_8008d2ac;
    if ((int)param_1[0x743] < 1)
	{
	  // if PauseAllThreads is diabled
      if ((*(uint *)PTR_DAT_8008d2ac & 0x10) == 0) {

        // if amount of frozen time left (relic races) is less or equal than zero
        if ((int)param_1[0x788] < 1) {

          // If you're not in End-Of-Race menu
          if ((*(uint *)PTR_DAT_8008d2ac & 0x200000) == 0) {
            param_1[0x744] = param_1[0x744] + param_1[0x741];
          }
        }

        // if you still have time frozen time left...
        else {

          // uVar5 = amount of frozen time left - a value that changes constantly between 31/32 (tick rate?)
          uVar5 = param_1[0x788] - param_1[0x741];

          // amount of frozen time left = new amount of time left
          param_1[0x788] = uVar5;

          // if new amount of frozen time left is less than zero
          if ((int)uVar5 < 0) {

            // amount of frozen time left equals zero
            param_1[0x788] = 0;
          }

          // if the amount of frozen time left is non negative
          else {
            uVar5 = *(uint *)(puVar9 + 0x1cec);

			// every six frames, play a sound
            if (uVar5 == (uVar5 / 6) * 6)
			{
			  // alternate between sounds each 6 frames

			  // multiple of 12
              if (uVar5 == (uVar5 / 0xc) * 0xc)
			  {
				// OtherFX_Play_LowLevel
				// Play "tick" sound
                FUN_800284d0(0x40,0,0x8c9080);
              }

			  // multiple of only 6
              else
			  {
				// OtherFX_Play_LowLevel
				// Play "tick" sound
                FUN_800284d0(0x40,0,0x8c8880);
              }
            }
          }
        }
      }
    }
    else {
      param_1[0x744] = 0;
    }

	// animate textures on PLYROBJECTLIST,
	// such as blinking eyes on Crash in main menu
    FUN_80021ac0(0xffffffff,DAT_8008d870,param_1[0x73b]);

	// animate textures for LEV related models,
	// including the ND Box Scne 1010101010101
    FUN_80021ac0(*(undefined4 *)(param_1[0x58] + 0x14),*(undefined4 *)(param_1[0x58] + 0x18),
                 param_1[0x73b]);
    iVar10 = 0;

	// pointer to first Player thread
    iVar7 = *(int *)(PTR_DAT_8008d2ac + 0x1b2c);

    iVar6 = 0;

	// loop through all players
    while (iVar7 != 0)
	{
	  // thread -> object
      iVar4 = *(int *)(iVar7 + 0x30);
      iVar8 = iVar6;

	  // Player / AI structure + 0x4a shows driver index (0-7)

	  // If this is Player 1
      if (*(char *)(iVar4 + 0x4a) == '\0') {
LAB_80035098:
        iVar10 = iVar4;
        iVar6 = iVar8;
      }
      else
	  {
		// If this is Player 2, or first AI (boss, ghost, etc)
        if (*(char *)(iVar4 + 0x4a) == '\x01') {
          iVar6 = iVar4;
        }
        iVar8 = iVar10;
        if (*(byte *)(iVar4 + 0x559) < *(byte *)(iVar10 + 0x559)) goto LAB_80035098;
      }

	  // player -> next
      iVar7 = *(int *)(iVar7 + 0x10);
    }

    if (((iVar10 != 0) && (iVar6 != 0)) &&
       (iVar7 = (uint)*(byte *)(iVar6 + 0x559) - (uint)*(byte *)(iVar10 + 0x559),
       *(short *)(iVar10 + 0x4f2) < iVar7)) {
      *(undefined2 *)(iVar10 + 0x4f2) = (short)iVar7;
    }
    iVar6 = 0;

	// loop counter
    iVar10 = 0;

	// pointer to threadbucket
    iVar7 = 0x1b2c;

    puVar11 = param_1;

	// for iVar10 = 0; iVar10 < 0x11; iVar10++
	do
	{

      if (
			(
				// if PauseAllThreads is diabled
				((*(uint *)PTR_DAT_8008d2ac & 0x10) == 0) ||

				// if this bucket cannot be paused
				((((int *)((int)param_1 + iVar7))[3] & 1U) != 0)
			) &&

		  // If threadbucket has threads
		  (*(int *)((int)param_1 + iVar7) != 0)
         )
	  {
		// if this is player threadbucket
        if (iVar10 == 0)
		{
		  // pointer to first Player thread
          iVar8 = *(int *)(PTR_DAT_8008d2ac + 0x1b2c);

		  // repeat until you're done with every player structure,
		  // you'll know you're done when you reach nullptr
          while (iVar8 != 0)
		  {
            // WARNING: Read-only address (ram,0x8008d874) is written

			// VehPickupItem_ShootOnCirclePress
            FUN_800666e4(*(undefined4 *)(iVar8 + 0x30));

			// increment pointer to go to next player
            iVar8 = *(int *)(iVar8 + 0x10);
          }
                    // WARNING: Read-only address (ram,0x8008d874) is written

		  // loop iteration counter
          iVar8 = 0;

		  // execute all 0xD (13) funcPtrs in Driver struct
		  // for iVar8 = 0; iVar8 < 0xd; iVar8++
          do
		  {
			// pointer to first Player thread
            iVar4 = *(int *)(PTR_DAT_8008d2ac + iVar6 + 0x1b2c);
            
			// if valid
			if (iVar4 != 0) 
			{
              do 
			  {
				// if no funcThTick (when would that change?)
                if ((*(int *)(iVar4 + 0x2c) == 0) &&

					// playerThread->driver->funcPtr[iVar8]
                   (pcVar3 = *(code **)(*(int *)(iVar4 + 0x30) + iVar8 * 4 + 0x54),

				   // if valid
                   pcVar3 != (code *)0x0))
				{
				  // execute the function pointer
                  (*pcVar3)(iVar4);
                }

				// go to next player
                iVar4 = *(int *)(iVar4 + 0x10);

              } while (iVar4 != 0);
            }

			// increment loop counter
            iVar8 = iVar8 + 1;
          } while (iVar8 < 0xd);
        }

		// execute all thread update functions
        FUN_800715e8(puVar11[0x6cb]);
      }

	  // next threadbucket
      puVar11 = puVar11 + 5;

	  // next threadbucket (again)
      iVar6 = iVar6 + 0x14;

	  // increment loop counter
      iVar10 = iVar10 + 1;

	  // next threadbucket
      iVar7 = iVar7 + 0x14;

	// loop through all threadbuckets
    } while (iVar10 < 0x11);

	// BOTS_UpdateGlobals
    FUN_80013374(PTR_DAT_8008d2ac);

	// Record ghost data
    FUN_80027f20(0);

    *(uint *)(PTR_DAT_8008d2ac + 0x1cd4) =
         (uint)(*(int *)(PTR_DAT_8008d2ac + 0x1cd4) * 10000) / 0x147e;

	// Particle_UpdateAllParticles
    FUN_8003f434();
  }

  // if game is paused
  else
  {
	// aku threadbucket
    if (param_1[0x711] != 0)
	{
	  // execute all thread update functions
      FUN_800715e8(param_1[0x711]);
    }
  }

  // Check if 231.dll is loaded
  iVar10 = FUN_800348e8();

  // If it is loaded
  if (iVar10 != 0) {

	// If game is not paused
    if ((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0)
	{
	  // RB_Bubbles_RoosTubes
      FUN_800b39dc();
    }

	// pointer to first burst thread
    if (*(int *)(PTR_DAT_8008d2ac + 0x1bb8) != 0) 
	{
	  // RB_Burst_DrawAll
      FUN_800b25b8();
    }
  }

  // PROC_CheckAllForDead
  FUN_80041ff4();

  // If game is not paused
  if ((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0)
  {
	// Audio_Update1
    FUN_8002d67c();
  }
  puVar9 = PTR_DAT_8008d2b0;
  param_1[1] = *param_1;

  // GAMEPAD_GetNumConnected
  iVar10 = FUN_800255b4(puVar9);


  uVar5 = *(uint *)PTR_DAT_8008d2ac;


  // If you're not in End-Of-Race menu
  if ((uVar5 & 0x200000) == 0)
  {
    if (

			// if game is paused
			(bVar1) ||

			// or		???

			// if game is paused
			((*param_1 & 0xf) != 0)
		)
	{
	  // if game has been paused for more than 5 frames,
	  // this is here so you dont spam pause button
      if (PTR_DAT_8008d2ac[0x1d38] == '\0')
	  {
        if (
			(
				// If active Menu is not Options
				(DAT_8008d908 != &DAT_80084190) &&

				// If active Menu is not AkuAku Hints
				(DAT_8008d908 != &DAT_800b518c)
			) &&

			// If you press Start
			((DAT_8008d950 & 0x1000) != 0)
		   )
		{
		  // clear gamepad input (for menus)
          FUN_80046404();

		  // Unpause game
          *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xfffffffe;

		  // unpause audio
          FUN_80034b48(0);

		  // OtherFX_Play
          FUN_80028468(1,1);

		  // MainFreeze_SafeAdvDestroy
          FUN_800399fc();

		  // ElimBG_Deactivate
          FUN_80024c08(PTR_DAT_8008d2ac);

		  // make Menu invisible
          FUN_800469c8(DAT_8008d908);

		  // set countdown since unPaused,
		  // must wait 5 frames before pausing again
          PTR_DAT_8008d2ac[0x1d39] = 5;
        }
      }
      else
	  {
		// decrease frame timer since start of pause
        PTR_DAT_8008d2ac[0x1d38] = PTR_DAT_8008d2ac[0x1d38] + -1;
      }
    }
    else
	{
	  // If you are allowed to pause the game,
	  // after waiting 5 frames since last unpause
      if (PTR_DAT_8008d2ac[0x1d39] == '\0') {
        if (
				(
					// if not in cutscene,
					// end-of-race, or main menu
					((uVar5 & 0x20202000) == 0) &&

					// if no menu
					(DAT_8008d908 == (undefined *)0x0)
				) &&
				(
					(
						DAT_8008d874 == 0 &&
						(
							(
								// RaceFlag_IsFullyOnScreen
								iVar7 = FUN_80043f1c(),

								// if not fully on screen
								iVar7 == 0 &&

								(
									// loop counter
									iVar7 = 0,

									// (72a*4 = 1ca8), numPlyrCurrGame
									*(char *)(param_1 + 0x72a) != '\0'
								)
							)
						)
					)
				)
			 )
		{
		  // for iVar7 = 0; iVar7 < ??? iVar7++
          do {
            if (
				(
					(
						// if there is a change in the number
						// of gamepads that are connected
						(iVar10 != 0) &&
						(
							(
								// check for missing gamepads, depending on numPlyrNextGame
								uVar5 = FUN_80035d70((uint)(byte)PTR_DAT_8008d2ac[0x1ca9]),

								// if a gamepad is missing that is needed
								(uVar5 & 0xffff) == 0

								// If the game is not paused
								&& ((*param_1 & 0xf) == 0)
							)
						)
					) ||

					// If anyone tries to pause the game by pressing Start
					((*(uint *)(param_2 + 0x14) & 0x1000) != 0)
				) &&

				// If an overlay is loaded in slot 230-233
               (PTR_DAT_8008d2ac[0x2541] != -1)
			  )
			{
			  // This pauses the game somehow

              *(uint *)(PTR_DAT_8008d2ac + 0x1d44) = *(uint *)PTR_DAT_8008d2ac & 0x3e0020 | 1;

			  // MainFreeze_IfPressStart
			  FUN_80039e98();

			  // wait 5 frames after pausing,
			  // before allowing functionality
			  // in the pause menu, so you dont
			  // copy input from gameplay into menu
              PTR_DAT_8008d2ac[0x1d38] = 5;
            }

			// increment loop counter
            iVar7 = iVar7 + 1;

            param_2 = param_2 + 0x50;

			// (72a*4 = 1ca8), numPlyrCurrGame
          } while (iVar7 < (int)(uint)*(byte *)(param_1 + 0x72a));
        }
      }
      else
	  {
		// reduce frame counter since previous unpause
        PTR_DAT_8008d2ac[0x1d39] = PTR_DAT_8008d2ac[0x1d39] + -1;
      }
    }
  }

  // If you're in End-Of-Race menu
  else
  {
	// if cooldown after end of VS game is zero
    if (*(short *)(PTR_DAT_8008d2ac + 0x1d36) == 0)
	{
	  // Remove on-screen comments and give
	  // menu for Retry, Change Level, etc

      uVar5 = *(uint *)(PTR_DAT_8008d2ac + 0x1d44);
      if ((uVar5 & 0x1000000) == 0) {
        if ((uVar5 & 0x8000000) == 0) {
          if (*(short *)(PTR_DAT_8008d2ac + 0x1d34) == 0) {
            return;
          }
        }
        else {
          if (*(short *)(PTR_DAT_8008d2ac + 0x1d34) == 0) {
            if ((uVar5 & 2) == 0) {
              return;
            }

			// SubmitName_DrawMenu
			sVar2 = FUN_8004aa60(0x140);

            if (sVar2 == 0) {
              return;
            }
            if (sVar2 == 1) {
              DAT_8008d918 = 0;

			  // Set Load/Save to "Slot selected" mode
              FUN_80048e2c(0x41);

			  // make menu visible
              FUN_80046990(&DAT_80085be0);

              *(uint *)(PTR_DAT_8008d2ac + 0x1d44) =
                   *(uint *)(PTR_DAT_8008d2ac + 0x1d44) | 0x1000000;
              return;
            }

			// no new high score
			PTR_DAT_8008d2ac[0x1d49] = 0xff;

            *(uint *)(PTR_DAT_8008d2ac + 0x1d44) = *(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0xf3ffffff
            ;
            return;
          }
        }
        *(short *)(PTR_DAT_8008d2ac + 0x1d34) = *(short *)(PTR_DAT_8008d2ac + 0x1d34) + -1;
      }
    }
    else 
	{
	  // not Arcade mode
      if ((uVar5 & 0x400000) == 0) {

		// If race ended a few seconds ago, start drawing comments,
		// after cooldown had some time to go down (under 0x96)
        if (*(short *)(PTR_DAT_8008d2ac + 0x1d36) < 0x96)
		{
		  // UI_VsQuipDrawAll
          FUN_800550f4();

		  // Wait for players to press X to continue
          FUN_800552a4();
        }

		// if counter is higher than 0x1e
        if (0x1e < *(short *)(PTR_DAT_8008d2ac + 0x1d36))
		{
		  // reduce countdown by one frame, every frame
          *(short *)(PTR_DAT_8008d2ac + 0x1d36) = *(short *)(PTR_DAT_8008d2ac + 0x1d36) + -1;
        }
      }

      else
	  {
		// Proceed to VS menu with Retry, Change Level, etc
        *(undefined2 *)(PTR_DAT_8008d2ac + 0x1d36) = 0;
      }
    }
  }
                    // WARNING: Read-only address (ram,0x8008d874) is written
  return;
}


// param1 is PTR_DAT_8008d2ac
// param2 is screen ID (0, 1, 2, 3)
void FUN_80035684(int param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;

  // convert index to pointer offset
  iVar4 = param_2 * 4;

  // pointer to player structure
  iVar5 = *(int *)(param_1 + iVar4 + 0x24ec);

  // get quadblock under driver
  iVar2 = *(int *)(iVar5 + 0x350);

  // lev -> ptr_mesh_info
  piVar6 = **(int ***)(param_1 + 0x160);

  if (
		// if quadblock exists
		(iVar2 != 0) &&
		(
			// quadblock -> ptr_add_tex
			puVar1 = *(uint **)(iVar2 + 0x44),

			puVar1 != (uint *)0x0
		)
	  )
  {
	// ptr_add_tex->offset0
    uVar3 = *puVar1;

    if (uVar3 != 0) {
      if ((uVar3 & 1) == 0) {
        FUN_80021ea8(
		
					// VisMem 0x0-0xF
					*(undefined4 *)(*(int *)(param_1 + 0x1a38) + iVar4),
		
					uVar3,

					 // June 1999 calls this "visLeafList"
					 // ptr_mesh_info -> numBSP?
                     (piVar6[7] + 0x1f >> 5) << 2);
      }
      else {
        FUN_80021e1c(
		
					// VisMem 0x0-0xF
					*(undefined4 *)(*(int *)(param_1 + 0x1a38) + iVar4),
					
					uVar3 & 0xfffffffc);
      }
    }

	// driver -> ptr_add_tex -> offset4
    uVar3 = *(uint *)(*(int *)(*(int *)(iVar5 + 0x350) + 0x44) + 4);

	if (uVar3 != 0) 
	{
      if ((uVar3 & 1) == 0) 
	  {
        FUN_80021ea8(
		
					// VisMem 0x10-0x1F
					*(undefined4 *)(*(int *)(param_1 + 0x1a38) + param_2 * 4 + 0x10),
					
					uVar3,

					 // June 1999 calls this "visFaceList"
					 // ptr_mesh_info -> numQuadBlock?
					 (*piVar6 + 0x1f >> 5) << 2);
      }
      else {
        FUN_80021e1c(
						// VisMem 0x10-0x1F
						*(undefined4 *)(*(int *)(param_1 + 0x1a38) + param_2 * 4 + 0x10),
                        uVar3 & 0xfffffffc);
      }
    }
  }
  return;
}

// MainFrame_VisMemFullFrame
// param1 is PTR_DAT_8008d2ac
void FUN_800357b8(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;

  if (
		(
			// called VISMEM in prototypes
			(*(int *)(param_1 + 0x1a38) != 0) &&

			// if lev exists
			(param_2 != 0)
		) &&
		(
			// loop counter
			iVar9 = 0,

			// if numPlyrCurrGame is not zero
			*(char *)(param_1 + 0x1ca8) != '\0'
		)
	)
  {
	// pointer offset (increment by 4 each iteration of loop)
    iVar7 = 0;

	// offset of 8008d2ac where P1 camera is
    iVar10 = 0x1498;

	// loop through all four cameras

	// for iVar9 = 0; iVar9 < numPlyrCurrGame; iVar9++
    do
	{
	  // CameraDC
      iVar6 = param_1 + iVar10;

	  // pointer to structure of each player
      iVar8 = *(int *)(param_1 + iVar7 + 0x24ec);

	  // CameraDC 0x20 (vismem->0x40)
      iVar2 = *(int *)(iVar6 + 0x20);

	  // remove flag 0x4000
      *(uint *)(iVar6 + 0x70) = *(uint *)(iVar6 + 0x70) & 0xffffbfff;

	  // if camera can't figure out what to draw on it's own,
	  // if not following warpball path like track select videos,
	  if (iVar2 == 0)
	  {
        if (
				(
					// driver -> quadblock under driver
					(*(int *)(iVar8 + 0x350) != 0) &&

					// quadblock -> ptr_add_tex
					(piVar1 = *(int **)(*(int *)(iVar8 + 0x350) + 0x44), piVar1 != (int *)0x0)
				) &&

				// pull vismem data from quadblock + 0x44
				(iVar2 = *piVar1, iVar2 != 0)
			)
		{
		  // if camDC->0x20 is nullptr,
		  // take from quadblock->0x44->0x0
			
		  // VisMem 0x40-0x4F
          *(int *)(*(int *)(param_1 + 0x1a38) + iVar7 + 0x40) = iVar2;

		  // quadblock -> ptr_add_tex -> 0x0
          uVar5 = **(uint **)(*(int *)(iVar8 + 0x350) + 0x44);

		  // only memcpy if size is specified
		  if ((uVar5 & 1) == 0) goto LAB_80035900;

LAB_800358e0:
		  
		  // copy until nullptr
          FUN_80021da0(
		  
			// VisMem 0x0-0xF
			*(undefined4 *)(*(int *)(param_1 + 0x1a38) + iVar7),
			uVar5 & 0xfffffffc);
        }
      }

	  // if camera can figure out what to draw on it's own,
	  // if following warpball path like track select videos,
      else
	  {
		// VisMem 0x40-0x4F
        iVar3 = *(int *)(param_1 + 0x1a38) + iVar7;

		// if this changed from previous frame
        if (*(int *)(iVar3 + 0x40) != iVar2)
		{
          *(int *)(iVar3 + 0x40) = iVar2;

		  // CameraDC 0x20
		  uVar5 = *(uint *)(iVar6 + 0x20);

		  // only memcpy if size is specified
		  if ((uVar5 & 1) != 0) goto LAB_800358e0;
LAB_80035900:

		  // called VISMEM in prototypes
          memcpy(
					// destination
					// VisMem 0x0-0xF
					*(int *)(param_1 + 0x1a38) + iVar7,

					// source
					uVar5,

					// unk size
					// get number of bits
					// lw a2 0x1c(s6) (CameraDC->0x1C)
					
					// get number of ints
					// addiu a2, 1F
					// sra a2, 5
					
					// get number of bytes
					// sll a2, 2
				);
        }
      }

	  // CameraDC 0x24
	  iVar2 = *(int *)(iVar6 + 0x24);

	  // if camera can't figure out what to draw on it's own,
	  // if not following warpball path like track select videos,
	  if (iVar2 == 0)
	  {
        if (
				(
					// driver -> quadblock under driver
					(*(int *)(iVar8 + 0x350) != 0) &&

					(
						// quadblock -> ptr_add_tex
						iVar2 = *(int *)(*(int *)(iVar8 + 0x350) + 0x44),
						iVar2 != 0
					)
				) &&

				(iVar2 = *(int *)(iVar2 + 4), iVar2 != 0)
		   )
		{
		  // if camDC->0x24 is nullptr,
		  // take from quadblock->0x44->0x4
			
		  // VisMem 0x50-0x5F
          *(int *)(*(int *)(param_1 + 0x1a38) + iVar7 + 0x50) = iVar2;

		  // quadblock -> ptr_add_tex -> 0x4
          uVar5 = *(uint *)(*(int *)(*(int *)(iVar8 + 0x350) + 0x44) + 4);

		  // only memcpy if size is specified
		  if ((uVar5 & 1) == 0)
		  {
			// called VISMEM in prototypes
            memcpy(
					// VisMem 0x0-0xF
					*(int *)(param_1 + 0x1a38) + iVar7,
					uVar5,
					// unk size
				  );
          }
          else 
		  {
			// VisMem 0x10-0x1F
			// copy until nullptr
            FUN_80021da0(*(undefined4 *)(*(int *)(param_1 + 0x1a38) + iVar7 + 0x10),
                               uVar5 & 0xfffffffc);
          }
        }
      }

	  // if camera can figure out what to draw on it's own,
	  // if following warpball path like track select videos,
      else
	  {
		// VisMem 0x50-0x5F
        iVar3 = *(int *)(param_1 + 0x1a38) + iVar7;

		// if cameraDC->0x24 changed
		if (*(int *)(iVar3 + 0x50) != iVar2)
		{
          *(int *)(iVar3 + 0x50) = iVar2;

		  // CameraDC 0x24
		  // only memcpy if size is specified
		  if ((*(uint *)(iVar6 + 0x24) & 1) == 0)
		  {
            memcpy(
					// VisMem 0x10-0x1F
					*(int *)(param_1 + 0x1a38) + iVar7 + 0x10
					
					iVar6 + 0x24,
					// unk size
					);
          }

          else
		  {
			// copy until nullptr
            FUN_80021da0(

					// VisMem 0x10-0x1F
					*(undefined4 *)(*(int *)(param_1 + 0x1a38) + iVar7 + 0x10),

					// CameraDC 0x24
					*(uint *)(iVar6 + 0x24) & 0xfffffffc);
          }

		  // quadblock under driver
          iVar2 = *(int *)(iVar8 + 0x350);

          if (
				// if no quadblock exists, or quadblock -> ptr_add_tex does not exist
				((iVar2 == 0) || (piVar1 = *(int **)(iVar2 + 0x44), piVar1 == (int *)0x0)) ||
				(
					// data from quadblock -> ptr_add_tex is invalid
					(*piVar1 == 0 || (((piVar1[1] == 0 || (piVar1[2] == 0)) ||

					// LEV -> mesh_info -> ptrQuadBlockArray
					(iVar2 = (iVar2 - *(int *)(**(int **)(param_1 + 0x160) + 0xc)) * -0x1642c859,

					// VisMem 0x10-0x1F
					(*(uint *)((iVar2 >> 7) * 4 + *(int *)(*(int *)(param_1 + 0x1a38) + iVar7 + 0x10)) &
					1 << (iVar2 >> 2 & 0x1fU)) != 0))))
				)
			  )
		  {
            uVar5 = *(uint *)(iVar6 + 0x70) & 0xffffdfff;
          }

          else
		  {
			// camera is moving on path, not followinig driver
            uVar5 = *(uint *)(iVar6 + 0x70) | 0x2000;
          }

          *(uint *)(iVar6 + 0x70) = uVar5;

		  // if driver quadblock is wall, therefore need to improvise?
		  if ((*(uint *)(iVar6 + 0x70) & 0x2000) != 0)
		  {
			// param1 is PTR_DAT_8008d2ac
			// ivar9 is screen ID (0,1,2,3)
            FUN_80035684(param_1,iVar9);
            *(uint *)(iVar6 + 0x70) = *(uint *)(iVar6 + 0x70) | 0x4000;
          }
        }
      }

	  if ((*(uint *)(iVar6 + 0x70) & 0x5000) == 0x1000)
	  {
		// param1 is PTR_DAT_8008d2ac
		// ivar9 is screen ID (0,1,2,3)
        FUN_80035684(param_1,iVar9);
      }

	  if (
			(
				// if camera is following driver "normally"
				(*(short *)(iVar6 + 0x9a) == 0) &&
                // and not wall
				((*(uint *)(iVar6 + 0x70) & 0x2000) != 0)
			) &&
			(
				(
					// quadblock under driver
					*(int *)(iVar8 + 0x350) != 0 &&

					(
						// driver -> quadblock -> ptr_add_tex
						(iVar2 = *(int *)(*(int *)(iVar8 + 0x350) + 0x44), iVar2 != 0 &&

						(iVar2 = *(int *)(iVar2 + 8), iVar2 != 0))
					)
				)
			)
		 )
	  {
		// quadblock->0x44->0x8
		  
		// CameraDC 0x28
		// which instances are visible
        *(int *)(iVar6 + 0x28) = iVar2;
      }
	  
	  // if no animated vertices
      if ((*(uint *)(param_2 + 0xdc) & 4) == 0)
	  {
		// VisMem 0x60-0x6F
        iVar2 = *(int *)(param_1 + 0x1a38) + iVar7;
		iVar8 = *(int *)(iVar2 + 0x60);

		// CameraDC 0x2C
        if (iVar8 == *(int *)(iVar6 + 0x2c)) {
          if (iVar8 == 0) goto LAB_80035ce0;
        }

		// if change since last frame
		else
		{
		  // camera 0x2C
          *(int *)(iVar2 + 0x60) = *(int *)(iVar6 + 0x2c);

          uVar5 = *(uint *)(iVar6 + 0x2c);

		  // only memcpy if size is specified
		  if ((uVar5 & 1) == 0) goto LAB_80035ce0;

		  // VisMem 0x20-0x2F (visOVertList)
		  uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x1a38) + iVar7 + 0x20);

LAB_80035c98:

		  // copy until nullptr
          FUN_80021da0(uVar4,uVar5 & 0xfffffffc);
        }
      }
	  
	  // if animated lev vertices
      else
	  {
		// VisMem 0x70-0x7F
        iVar2 = *(int *)(param_1 + 0x1a38) + iVar7;
        iVar8 = *(int *)(iVar2 + 0x70);

		// CameraDC 0x30
        if (iVar8 == *(int *)(iVar6 + 0x30)) {
          if (iVar8 != 0) goto LAB_80035cec;
        }

		// if change since previous frame
        else
		{
		  // VisMem + playerIndex*4 + 0x70 = CameraDC 0x30
          *(int *)(iVar2 + 0x70) = *(int *)(iVar6 + 0x30);
          uVar5 = *(uint *)(iVar6 + 0x30);

		  // only memcpy if size is specified
          if ((uVar5 & 1) != 0)
		  {
			// VisMem 0x30-0x3F
            uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x1a38) + iVar7 + 0x30);
            goto LAB_80035c98;
          }
        }
LAB_80035ce0:
        memcpy(
				uVar4,
				// camDC offset 0x2c or 0x30
				// unk size
				);
      }
LAB_80035cec:

	  // increment pointer
      iVar7 = iVar7 + 4;

	  // increment loop counter
      iVar9 = iVar9 + 1;

	  // increment pointer to next player's camera,
	  // each camera is 0xdc bytes large
      iVar10 = iVar10 + 0xdc;

    } while (iVar9 < (int)(uint)*(byte *)(param_1 + 0x1ca8));
  }
  return;
}

// MainFrame_InitVideoSTR
void FUN_80035d30
               (undefined4 param_1,undefined2 *param_2,undefined2 param_3,undefined2 param_4)

{
  // 8008d2c8, boolVideoStrPlay
  uGp0000035c = param_1;

  // 8008d880, videoSTR_src_vramRect
  // type RECT, which is 8 bytes
  uGp00000914 = *param_2;
  uGp00000916 = param_2[1];
  uGp00000918 = param_2[2];
  uGp0000091a = param_2[3];

  // 8008d89c, videoSTR_dst_vramX
  uGp00000930 = param_3;

  // 8008d8a0, videoSTR_dst_vramY
  uGp00000934 = param_4;
  return;
}

// MainFrame_HaveAllPads
int FUN_80035d70(short param_1)

{
  bool bVar1;
  int iVar2;
  short sVar3;
  uint uVar4;
  int iVar5;

  uVar4 = 1;
  sVar3 = 1;

  // if game is not loading
  if (DAT_8008d0f8 == -1)
  {
	// numPlyrNextGame
    iVar2 = (int)param_1;

	// if there are no players (cutscene)
	if (iVar2 == 0)
	{
	  // return 0 means gamepad is missing
      sVar3 = 0;
    }

	// if number of players is not zero
    else
	{
	  // loop counter
      iVar5 = 0;

	  // numPlyrNextGame > 0
      if (0 < iVar2)
	  {
		// loop through all players and make sure
		// all their gamepads are connected

		// iVar5 = 0; iVar5 < numPlyrNextGame; iVar5++
        do
		{
		  // only continue checking gamepads if
		  // all previous gamepads are connected
          bVar1 = uVar4 != 0;

          uVar4 = 0;
          if (
				// if there are no other gamepads unplugged (so far)
				(bVar1) &&

				// if this gamepad is plugged in
				(*(char **)(PTR_DAT_8008d2b0 + (int)(short)iVar5 * 0x50 + 0x20) != (char *)0x0)
			 )
		  {
			// Check if gamepad is compatible with game (not a gun or mouse)
			uVar4 = (uint)(**(char **)(PTR_DAT_8008d2b0 + (int)(short)iVar5 * 0x50 + 0x20) == '\0');
          }

		  // save the result
          sVar3 = (short)uVar4;

		  // increment loop counter
          iVar5 = iVar5 + 1;

        } while (iVar5 * 0x10000 >> 0x10 < iVar2);
      }
    }

	// return 0 only if a gamepad is missing
	// that is currently needed in the game
    return (int)sVar3;
  }
  return 1;
}

// Request Aku Hint, doesn't start till FUN_800b3dd8
// param1:
//	0x00 - Welcome to Adventure Arena
//	0x01 - using a warp pad (part of welcome)
// 	0x02 - Need more trophies
//	0x03 - Need 4 trophies for Boss
//	0x04 - Need 4 keys for oxide
//	0x05 - Must have 1 Boss Key
//	0x06 - This is the load/save screen
// 	0x07 - Congrats on opening new area
//	0x12 - Must have 2 Boss Key
//	0x19 - Collect every crystal in arena
//	0x1a - CTR Token
//	0x1b - Gem Cups
//	0x1c - Must get 10 relics
//	0x1d - Relic
// param2:
//	0x00 - not interrupting a warppad load screen
// 	0x01 - interrupting (CTR, Relic, or Crystal hints)
void FUN_80035e20(short param_1,undefined2 param_2)

{
  if (
		// *8008D2AC = 80096b20
		// if game is not paused
		((*puGp00000340 & 0xf) == 0) &&

		// 8008D2CC
		(sGp00000360 == -1)
	 )
  {
	// 8008D874
	// aku is now giving a hint
    uGp00000908 = 1;

	// 8008d2ac[0x93b] + 0x54
	// 8009900C + 0x54
	// driver funcPtrInit, VehPhysProc_FreezeEndEvent_Init
    *(undefined **)(puGp00000340[0x93b] + 0x54) = &FUN_80062d04;

	// 8008d2cc
	// AkuHint_RequestedHint
	sGp00000360 = param_1;

	// 8008d2ce
	// AkuHint_boolInterruptWarppad
	uGp00000362 = param_2;
  }
  return;
}



// MainFrame_RenderFrame
// param1 is PTR_DAT_8008d2ac - GameTracker
void FUN_80035e70(uint *param_1)
{
  uint *puVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  undefined *puVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  short sVar10;
  int local_54;
  int iVar11;
  uint *puVar12;
  void *p;
  int iVar13;
  undefined *puVar14;
  int iVar15;
  int iVar16;
  short sVar17;
  uint *puVar18;
  int iVar19;
  int iVar20;
  int *piVar21;
  int iVar22;
  undefined2 local_40;
  short local_3e;
  undefined2 local_3c;
  short local_3a;
  short local_38;
  short local_36;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_2a;

  iVar22 = 0;

  // param1 is PTR_DAT_8008d2ac
  // 0x58*4 = 0x160, pointer to LEV
  piVar21 = (int *)param_1[0x58];

  bVar4 = false;

  // check if 230 dll is loaded
  iVar6 = FUN_80034908();

  // check if in main menu
  if (
		// If it is loaded
		(iVar6 != 0) &&

		// check if you are in the main menu
		(DAT_8008d908 == -0x7ff4bac0) // 0x800B4540
	 )
  {
	// is main menu at highest level of hierarchy?
	// if so, dont give missing gamepads error
    bVar4 = (uRam800b4548 & 0x10) == 0;
  }

  // Missing Gamepads error dialog
  if (
		(
			(

				// If you are not in a cutscene
				((*(uint *)PTR_DAT_8008d2ac & 0x20000000) == 0) &&
				(
					// uvar7 = function(Number Of Players)
					uVar7 = FUN_80035d70((uint)(byte)PTR_DAT_8008d2ac[0x1ca9]),


					(uVar7 & 0xffff) == 0
				)
			) &&

			// If you're not in Demo Mode
			(PTR_DAT_8008d2ac[0x1d32] == '\0')
		) &&

		// if main menu is not highest level of hierarchy,
		// that is assuming player is in main menu
		(!bVar4)
	  )
	{

	// Get Y position to place the error message
    sVar17 = *(short *)(&DAT_80084250 + (int)DAT_8008d88c * 2);

	local_3a = 0xe;

    if (
			(PTR_DAT_8008d2b0[0x2d1] == -0x80) ||

			(
				// pointer goes to "Controller 1" or "Controller 2"
				sVar10 = 0,

				// if number of players is more than 2
				2 < (byte)PTR_DAT_8008d2ac[0x1ca9]
			)
		)
	{
	  // pointer goes to "1A", "1B", "1C", "1D"
      sVar10 = 2;
    }

	// loop counter
    iVar6 = 0;

	// if Number of Players is not zero
    if (PTR_DAT_8008d2ac[0x1ca9] != '\0')
	{
	  // offset into main gamepad buffer for all players.
	  // 0 for p1, 0x30 for p2, etc
      iVar19 = 0;

	  // box height
      local_3a = 0xe;

	  // for(int iVar6 = 0; iVar6 < numPlyrNextGame; iVar6++)

      do
	  {
		// check each player's gamepad buffer
        if ((*(char **)(PTR_DAT_8008d2b0 + iVar19 + 0x20) == (char *)0x0) ||
           (**(char **)(PTR_DAT_8008d2b0 + iVar19 + 0x20) != '\0')) {
          
		  iVar13 = (int)sVar17;
          
		  // box height
		  local_3a = local_3a + 8;
          
		  sVar17 = sVar17 + 8;

		  // One of 6 strings for "Gamepad x is Unplugged
          FUN_80022878(*(undefined4 *)			//  -0x7ff7bdbc should be 80084244
                        ((int)*(short *)((iVar6 + sVar10) * 2 + -0x7ff7bdbc) * 4 + DAT_8008d878),
                       0x100,iVar13,2,0xffff8000);
        }

		// increment loop counter
        iVar6 = iVar6 + 1;

		// increment offest to next player's gamepad buffer
        iVar19 = iVar19 + 0x50;

						// numPlyrNextGame
      } while (iVar6 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
    }

	// DAT_8008d878 + 0xac
	// PLEASE INSERT A CONTROLLER
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0xac),0x100,(int)sVar17,2,0xffff8000);

    local_40 = 0xffec;
    local_3c = 0x228;

	// Get Y position to place error message
    local_3e = *(short *)(&DAT_80084250 + (int)DAT_8008d88c * 2) + -3;

	// Draw 2D Menu rectangle background
    FUN_800457b0(&local_40,1,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  }
  iVar19 = 0;

  // loop counter
  iVar13 = 0;

  // offset of 8008d2ac where pushBuffer structs
  // are held for each player (pos, size, etc)
  iVar20 = 0x168;

  // NOT for pushBuffer
  // offset in another array of 0x110-byte structs
  iVar6 = iVar13;

  // "FINAL LAP!" for all players
  // for iVar13 = 0; iVar13 < 4; iVar13++
  do
  {
	// pointer to array of pushBuffer structs
    puVar14 = PTR_DAT_8008d2ac + iVar20;

	// If there is time remaining in the "Final Lap" animation
    if (*(ushort *)((int)&DAT_8008d2a0 + iVar19) != 0)
	{
	  // total animation is 0x5a frames
	  // 0x5a = 90

	  // 0x5a - [frames remaining] is frame index in the animation
      local_54 = (int)((0x5a - (uint)*(ushort *)((int)&DAT_8008d2a0 + iVar19)) * 0x10000) >> 0x10;

	  // if you are less than 81 frames into the animation
      if (local_54 < 0x51) {

		// if you are less than 11 frames into the animation
        if (local_54 < 0xb)
		{
		  // Bring the text on-screen from the right

          iVar11 = (int)(((uint)*(ushort *)(puVar14 + 0x20) + 100) * 0x10000) >> 0x10;
          iVar15 = (int)((uint)*(ushort *)(puVar14 + 0x22) << 0x10) >> 0x12;
          iVar16 = (int)((uint)*(ushort *)(puVar14 + 0x20) << 0x10) >> 0x11;
        }

		// if you are 11-81 frames in the animation
        else
		{
		  // keep the text still, in the center

          local_54 = local_54 + -10;
          iVar11 = (int)((uint)*(ushort *)(puVar14 + 0x20) << 0x10) >> 0x11;
          iVar15 = (int)((uint)*(ushort *)(puVar14 + 0x22) << 0x10) >> 0x12;
          iVar16 = iVar11;
        }
      }

	  // if you are more than 81 frames into the animation
      else
	  {
		// Move the text off-screen to the left

        local_54 = local_54 + -0x50;
        iVar11 = (int)((uint)*(ushort *)(puVar14 + 0x20) << 0x10) >> 0x11;
        iVar15 = (int)((uint)*(ushort *)(puVar14 + 0x22) << 0x10) >> 0x12;
        iVar16 = -100;
      }

	  // Interpolate the position of "Final Lap"
      FUN_8004ecd4(&local_38,iVar11,iVar15,iVar16,iVar15,local_54,10);

	  // DAT_8008d878 + 0x8cc
	  // FINAL LAP!

	  // need to specify OT, or else "FINAL LAP" will draw on top of character icons,
	  // and by doing this, "FINAL LAP" draws under the character icons instead

	  // DecalFont_DrawLineOT
      FUN_800228c4(*(undefined4 *)(DAT_8008d878 + 0x8cc),(int)local_38,(int)local_36,1,0xffff8000,

					// first PushBuffer is at 0x168,
					// 0x25c - 0x110 is 0xF4, known pushBuffer ptrOT
                   *(undefined4 *)(PTR_DAT_8008d2ac + iVar6 + 0x25c));

	  // subtract a frame from the animation
	  *(short *)((int)&DAT_8008d2a0 + iVar19) = *(short *)((int)&DAT_8008d2a0 + iVar19) + -1;
    }
    iVar19 = iVar19 + 2;

	// NOT for pushBuffer
	// increment some other pointer that also holds 0x110 structs
    iVar6 = iVar6 + 0x110;

	// increment loop counter
    iVar13 = iVar13 + 1;

	// increment pointer to next pushBuffer struct
    iVar20 = iVar20 + 0x110;

  } while (iVar13 < 4);

  // ElimBG_HandleState
  FUN_80024974(PTR_DAT_8008d2ac);

  // if LEV exists
  if (piVar21 != (int *)0x0)
  {
	// get pointer to LEV mesh_info
    iVar22 = *piVar21;
  }

  // VisMem
  // gGT->256c & (renderBucket || drawLev)
  if ((param_1[0x95b] & 0x21) != 0)
  {
	// MainFrame_VisMemFullFrame
	// use quadblock offset 0x44 with camera data
    FUN_800357b8(param_1,piVar21);
  }

  // scrolling textures
  if (
		(
			// gGT->256c & drawLev
			((param_1[0x95b] & 1) != 0) &&

			// called VISMEM in prototypes
			(*(int *)(PTR_DAT_8008d2ac + 0x1a38) != 0)
		) &&

		// if ptrLEV is valid
		(piVar21 != (int *)0x0)
	  )
  {
	// param1 is lev->ptr_tex_array,
	// param2 is 1cec (frame timer)

	// CTR_CycleTex_LEV
	// turbo pads, waterfalls, lava, etc
    FUN_80021984(piVar21[2],param_1[0x73b]);
  }

  // Menu input
  if (
		// if there is an active menu
		(DAT_8008d908 != 0) ||

		// If you're in End-Of-Race menu
		((*(uint *)PTR_DAT_8008d2ac & 0x200000) != 0)
	)
  {
	// RECTMENU_CollectInput
    FUN_80046458();
  }

  // Menu logic
  if (
		// if any Menu is active
		(DAT_8008d908 != 0) &&

		// if game is not loading
		(DAT_8008d0f8 == -1)
	  )
  {
	// RECTMENU_ProcessState
    FUN_8004680c();
  }

  // loop counter
  iVar6 = 0;

  // Camera Frustums
  // gGT->1ca8(numPlyrCurrGame) != 0
  if (*(char *)(param_1 + 0x72a) != '\0')
  {
	// offset of 8008d2ac where pushBuffer structs
	// are held for each player (pos, size, etc)
	iVar19 = 0x168;

    puVar18 = param_1;
    puVar12 = param_1;

	// for iVar6 = 0; iVar6 < numPlyrCurrGame; iVar6++
    do
	{
	  // PushBuffer_UpdateFrustum
	  // pointer to pushBuffer struct
      FUN_800430f0((int)param_1 + iVar19);

	  // 0x5d2 = 0x14b4, cameraDC = 0x1498,
	  // gGT->CameraDC[i].ptrQuadBlock
      if (puVar18[0x52d] != 0) 
	  {
		// gGT->CameraDC[i].ptrQuadBlock->weather_intensity
        uVar7 = (uint)*(byte *)(puVar18[0x52d] + 0x39);

		// (72a*4 = 1ca8), numPlyrCurrGame
        bVar2 = *(byte *)(param_1 + 0x72a);

        if (bVar2 == 0) {
          trap(0x1c00);
        }
        if (((uint)bVar2 == 0xffffffff) && (uVar7 == 0x20000000)) {
          trap(0x1800);
        }

		// gGT -> 0x1a44
		// gGT->RainBuffer[i].numParticles_max = quadblock->weather_Intensity / numPlyrCurrGame
        *(short *)(puVar12 + 0x691) = (short)((int)(uVar7 << 2) / (int)(uint)bVar2);

		// (72a*4 = 1ca8), numPlyrCurrGame
		bVar2 = *(byte *)(param_1 + 0x72a);

		if (bVar2 == 0) {
          trap(0x1c00);
        }
        if (((uint)bVar2 == 0xffffffff) && ((uint)*(byte *)(puVar18[0x52d] + 0x3a) == 0x20000000)) {
          trap(0x1800);
        }

		// gGT -> 0x1a46 
		// gGT->RainBuffer[i].vanishRate = quadblock->weather_vanishRate / numPlyrCurrGame
        *(undefined2 *)((int)puVar12 + 0x1a46) =
             (short)((int)((uint)*(byte *)(puVar18[0x52d] + 0x3a) << 2) / (int)(uint)bVar2);
      }
      
	  // 0xc*4 = 0x30, next RainBuffer
	  puVar12 = puVar12 + 0xc;
	  
	  // 0x37*4 = 0xDC, next CameraDC
      puVar18 = puVar18 + 0x37;

	  // increment loop counter
      iVar6 = iVar6 + 1;

	  // increment pushBuffer pointer to next pushBuffer
      iVar19 = iVar19 + 0x110;

	  // (72a*4 = 1ca8), numPlyrCurrGame
    } while (iVar6 < (int)(uint)*(byte *)(param_1 + 0x72a));
  }

  // param1 is PTR_DAT_8008d2ac
  // DropRain_MakeSound
  FUN_80024464(param_1);

  // frame timer for Menu row highlight
  uVar7 = (int)DAT_8008d970 << 7;

  // approximate trigonometry
  iVar6 = *(int *)(&DAT_800845a0 + (uVar7 & 0x3ff) * 4);

  // 0-90 or 180-270 degrees
  if ((uVar7 & 0x400) == 0) {
    iVar6 = iVar6 << 0x10;
  }

  iVar6 = iVar6 >> 0x10;

  // 180 - 360 degrees
  if ((uVar7 & 0x800) != 0) {
    iVar6 = -iVar6;
  }

  // red and yellow highlight menu bars
  iVar6 = (iVar6 << 6) >> 0xc;

  // if normal menu, filter out blue light in highlight
  DAT_8008d94c = (iVar6 + 0x40) * 0x100 | 0x80;

  // if save/load screen, filter out red+blue light in highlight
  DAT_8008d948 = (iVar6 + 0xa0) * 0x100 | 0x400040;

  // weather
  if (
		(
			// gGT->256c & weather
			(param_1[0x95b] & 2) != 0
		) &&
		(
			// if numPlyrCurrGame is less than 2
			(byte)PTR_DAT_8008d2ac[0x1ca8] < 2
		)
	  )
  {
	// RenderWeather
    FUN_8006f9a8(
					// pointer to start of pushBuffer buffers
					PTR_DAT_8008d2ac + 0x168,

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

					// &gGT->rainBuffer[0]
					PTR_DAT_8008d2ac + 0x1a40,

					// numPlyrCurrGame
					(uint)(byte)PTR_DAT_8008d2ac[0x1ca8],

					// check if the game is paused
					*(uint *)PTR_DAT_8008d2ac & 0xf
				);
  }

  // confetti
  if (
		// gGT->256c & confetti
		((param_1[0x95b] & 4) != 0) &&
		(
			// loop counter
			iVar6 = 0,

			// if at least one person needs confetti
			0 < *(int *)(PTR_DAT_8008d2ac + 0x2568)
		)
	)
  {
    iVar19 = 0;

	// loop through all confetti drivers
    do
	{
	  // draw confetti
      FUN_80069ffc(

					// pushBuffer of the player that won
					PTR_DAT_8008d2ac + *(int *)(PTR_DAT_8008d2ac + iVar19 + 0x2558) * 0x110 + 0x168,

				   // pointer to PrimMem struct
				   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

				   // &gGT->confetti
				   PTR_DAT_8008d2ac + 0x1b00,

				   // confetti frame timer
                   *(undefined4 *)(PTR_DAT_8008d2ac + 0x1cf0),

				   // boolean for if the game is paused (1 for yes, 0 for no)
				   *(uint *)PTR_DAT_8008d2ac & 0xf);

	  // increment loop counter
      iVar6 = iVar6 + 1;

      iVar19 = iVar6 * 4;
    } while (iVar6 < *(int *)(PTR_DAT_8008d2ac + 0x2568));
  }

  // stars
  if (
		// gGT->256c & stars
		((param_1[0x95b] & 8) != 0) &&

		// if numStars is not zero
		(*(short *)(PTR_DAT_8008d2ac + 0x1b0c) != 0)
	)
  {
	// renders stars in night sky
    FUN_8006e26c(
					// pointer to start of pushBuffer buffers
					PTR_DAT_8008d2ac + 0x168,

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

					// &gGT->stars
					PTR_DAT_8008d2ac + 0x1b0c,

					// numPlyrCurrGame
					(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]
				);
  }


  if (
		// param1 is PTR_DAT_8008d2ac
		((param_1[0x95b] & 0x100) != 0) &&

		// numPlyrCurrGame > 1
		(1 < (byte)PTR_DAT_8008d2ac[0x1ca8])
	)
  {
	// param1 is PTR_DAT_8008d2ac
    FUN_80023488(param_1);
  }

  // Gameplay HUD:
  // if not drawing intro-race title bars,
  if (
		(
			((PTR_DAT_8008d2ac[0x1d31] & 8) == 0) ||

			// if numPlyrCurrGame is not 1
			// if you're in multiplayer
			(PTR_DAT_8008d2ac[0x1ca8] != '\x01')
		) ||

		// If not drawing intro-race cutscene
		((*(uint *)PTR_DAT_8008d2ac & 0x40) == 0)
	  )
	{

    // hud flags
    bVar2 = PTR_DAT_8008d2ac[0x1d31];

	// if there is no hud (race is over)
    if ((bVar2 & 1) == 0)
	{
	  // if drawing cup standings
      if ((bVar2 & 4) != 0)
	  {
		// UI_CupStandings_InputAndDraw
        FUN_800562fc();
      }
    }

	// if hud is drawing
    else {

      uVar7 = *(uint *)PTR_DAT_8008d2ac;

	  // If you're not in Adventure Arena
      if ((uVar7 & 0x100000) == 0) {
        if (

			// If you're not in End-Of-Race menu
			((uVar7 & 0x200000) == 0) ||

			// If cooldown after end of race is not done
			(*(short *)(PTR_DAT_8008d2ac + 0x1d36) != 0)
		)
		{
			// If you're not in Crystal Challenge (in adventure mode)
			if ((uVar7 & 0x8000000) == 0)
			{
				// UI_RenderFrame_Racing
				FUN_80052f98();
			}

			// If you're in Crystal Challenge (in adventure mode)
			else
			{
				// UI_RenderFrame_CrystChall
				FUN_8005435c();
			}
        }

		// If you're in the End-Of-Race Menu
        else {
          if (1 < DAT_8008d0f8 + 5U) {

			// If you're not in Crystal Challenge
            if ((uVar7 & 0x8000000) == 0) {

			  // If you're not in Time Trial
              if ((uVar7 & 0x20000) == 0) {

				// If you're not in Arcade Mode
                if ((uVar7 & 0x400000) == 0) {

				  // If you're not in a Relic Race
                  if ((uVar7 & 0x4000000) == 0) {

					// If you're in Adventure Mode
                    if ((uVar7 & 0x80000) != 0) goto LAB_800367d4;

					// If you are not in Arcade or VS cup,
					// which leaves Single VS or Battle
                    if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) == 0)
					{
					  // VB_EndEvent_DrawMenu
                      FUN_8009f718();
                    }

					// If you are in Arcade or VS cup
                    else
					{
					  // disable drawing HUD
                      PTR_DAT_8008d2ac[0x1d31] = bVar2 & 0xfe;

					  // draw "standings"
					  // everyone's position in the cup, score, how many tracks
					  // you've driven, how many are left, name of cup, name of track, etc
                      PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] | 4;
                    }
                  }

				  // If you're in a Relic Race
				  else
				  {
					// RR_EndEvent_DrawMenu
                    FUN_800a01d8();
                  }
                }

				// If you're in Arcade Mode, or Adventure Mode
				else {
LAB_800367d4:
				  // AA_EndEvent_DrawMenu
                  FUN_8009f704();
                }
              }

			  // If you're in Time Trial
			  else
			  {
				// TT_EndEvent_DrawMenu
                FUN_8009fdc8();
              }
            }

			// If you're in Crystal Challenge
			else
			{
			  // CC_EndEvent_DrawMenu
              FUN_8009f710();
            }
          }
        }
      }

	  // If you're in Adventure Arena
	  else
	  {
		// handle transition from 233 to 232 (podium to advhub)
        if ((1 < (byte)PTR_DAT_8008d2ac[0x2579]) &&
           (PTR_DAT_8008d2ac[0x2579] = PTR_DAT_8008d2ac[0x2579] - 1,
           PTR_DAT_8008d2ac[0x2579] == '\x01'))
		{
		  // load DLL 232 (230 + 2)
          FUN_80033570(2);
        }

		// Check if 232 is loaded
        iVar6 = FUN_80034920();

		// If it is not loaded
        if (iVar6 == 0)
		{
		  // if any fade-in-from-black transition is over
          if (0xfff < *(short *)(PTR_DAT_8008d2ac + 0x139a))
		  {
			// UI_RenderFrame_AdvHub
            FUN_80054298();
          }
        }

		// If 232 dll is loaded
        else
		{
		  // if any fade-in-from-black transition is over
          if (0xfff < *(short *)(PTR_DAT_8008d2ac + 0x139a))
		  {
			// AH_Map_Main (map, icons, etc)
            FUN_800b1c90();

			// if request mask hint
            if ((int)DAT_8008d2cc != -1)
			{
			  // AH_MaskHint_Start
              FUN_800b3dd8((int)DAT_8008d2cc,(int)DAT_8008d2ce);

			  // erase queued hint
              DAT_8008d2cc = -1;
              DAT_8008d2ce = 0;
            }
          }

		  // if this is first frame of 232 loaded
          if (PTR_DAT_8008d2ac[0x2579] != '\0')
		  {
			// INSTANCE_LevDelayedLInBs
            FUN_80030ed4(*(undefined4 *)(param_1[0x58] + 0x10),
				*(undefined4 *)(param_1[0x58] + 0xc));

            puVar14 = PTR_DAT_8008d2ac;
            puVar18 = (uint *)(PTR_DAT_8008d2ac + 8);

			// nullify transition
            PTR_DAT_8008d2ac[0x2579] = 0;

			puVar5 = PTR_DAT_8008d2ac;
            *(uint *)(puVar14 + 8) = *puVar18 & 0xfffffeff;
            *(undefined2 *)(puVar5 + 0x139c) = 0x1000;
            *(undefined2 *)(puVar5 + 0x139e) = 0x2aa;
          }
        }
      }
    }
  }


  // Intro-Race title bars:
  // If drawing intro-race cutscene, only 1P, no crystal challenge
  else
  {
	// Draw the text on the top
	// and bottom of the screen
    FUN_80055840();
  }

  // rain (red beaker)
  if (
		(
			// gGT->256c & Rain
			(param_1[0x95b] & 0x10) != 0
		) &&
		(
			// if numPlyrCurrGame is less than 3
			(byte)PTR_DAT_8008d2ac[0x1ca8] < 3)
		)
  {
	// RedBeaker_RenderRain
    FUN_8006dc30(
					// 0x5a*4 = 0x168 (pushBuffer structs)
					param_1 + 0x5a,

					// gGT->backBuffer->primMem
					param_1[4] + 0x74,

					// Rain Pool
					PTR_DAT_8008d2ac + 0x19e8,

					// numPlyrCurrGame
					(uint)(byte)PTR_DAT_8008d2ac[0x1ca8],

					// check if game is paused
					*(uint *)PTR_DAT_8008d2ac & 0xf
				);
  }

  // check if 233 dll is loaded
  iVar6 = FUN_80034940();

  // ND Box split-lines
  if (
		// if it is loaded
		(iVar6 != 0) &&

		// If Level ID == 41
		// If you are at Naughty Dog Box
		(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x29)
	)
  {
	// CS_BoxScene_InstanceSplitLines
    FUN_800b0b38();
  }

  // gGT->256c & renderBucket (instances)
  if ((param_1[0x95b] & 0x20) != 0)
  {
	// This block of code draws characters on screen,
	// as well as all boxes (Weapon boxes + Wumpa boxes),
	// and weapons, I think all 3D geometry except for track
	// Does not include tire sprites

	// numPlyrCurrGame - 1
    uVar7 = (uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - 1;

	// If you're in a Relic Race
    if ((*(uint *)PTR_DAT_8008d2ac & 0x4000000) != 0)
	{
	  // modify array index
      uVar7 = uVar7 | 4;
    }

	// returns RBI pointer
	// RenderBucket_QueueLevInstances
	uVar8 = FUN_80070720(
							// 0x526*4 = 0x1498 = cameraDC array
							param_1 + 0x526,

							// gGT->backBuffer->otMem
							*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x90,

							// render bucket instance
							*(undefined4 *)(PTR_DAT_8008d2ac + 0x1c94),

							// track LOD
							(uint)(byte)(&DAT_8008d2d0)[uVar7],

							// numPlyrCurrGame
							(uint)(byte)PTR_DAT_8008d2ac[0x1ca8],

							// check if you paused the game
							*(uint *)PTR_DAT_8008d2ac & 0xf);

	// numPlyrCurrGame - 1
    uVar7 = (uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - 1;

	// If you're in a Relic Race
    if ((*(uint *)PTR_DAT_8008d2ac & 0x4000000) != 0)
	{
	  // modify array index
      uVar7 = uVar7 | 4;
    }

	// 1904 is in InstancePool, which starts at 18f8,
	// not sure what kind of data it is specifically

	// returns RBI pointer
	// RenderBucket_QueueNonLevInstances
    puVar9 = (undefined4 *)
             FUN_8007084c(
							// first taken item in InstancePool
							*(undefined4 *)(PTR_DAT_8008d2ac + 0x1904),

							// gGT->backBuffer->otMem
							*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x90,

							// render bucket instance
							uVar8,

							// track LOD
							(uint)(byte)(&DAT_8008d2d0)[uVar7],

							// numPlyrCurrGame
							(uint)(byte)PTR_DAT_8008d2ac[0x1ca8],

							// check if game is paused
							*(uint *)PTR_DAT_8008d2ac & 0xf);

	// Aug prototype
#if 0
		// ptrEnd of otmem is less than ptrCurr otmem
    if (*(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x98) <
        *(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x9c)) {
      printf("OTMEM OVERFLOW!\n");
    }
#endif

	// erase first variable in RenderBucketInstance
	*puVar9 = 0;
  }

  // gGT->256c & particles
  if ((param_1[0x95b] & 0x200) != 0)
  {
	// This block of code draws Exhaust
	// Only if param_1[0x95b] & 0x20 also happens

	  // (72a*4 = 1ca8), numPlyrCurrGame
    cVar3 = *(char *)(param_1 + 0x72a);

	// loop counter
    iVar6 = 0;

    if (cVar3 == '\0') goto code_r0x800369d8;

	// offset of 8008d2ac where pushBuffer structs
	// are held for each player (pos, size, etc)
    iVar19 = 0x168;

	// for iVar6 = 0; iVar6 < numPlyrCurrGame iVar6++
	do
	{
	  // pointer to pushBuffer struct
	  iVar13 = (int)param_1 + iVar19;

	  // increment offset to next pushBuffer struct
      iVar19 = iVar19 + 0x110;

	  // Draw particle List
      FUN_8003f590(iVar13,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1c9c));

	  // increment loop counter
      iVar6 = iVar6 + 1;

    } while (iVar6 < (int)(uint)*(byte *)(param_1 + 0x72a));
  }

  // (72a*4 = 1ca8), numPlyrCurrGame
  cVar3 = *(char *)(param_1 + 0x72a);

code_r0x800369d8:

  // loop counter
  iVar6 = 0;

  // link OT of all four player pushBuffer's
  if (cVar3 != '\0')
  {
	// offset of 8008d2ac where pushBuffer structs are held
    iVar19 = 0x168;

	// param1 is PTR_DAT_8008d2ac

	// 0x5a*4 = 0x168 (pushBuffer structs)
    puVar12 = param_1 + 0x5a;
    puVar18 = param_1;
    do
	{
	  // increment offset to next pushBuffer struct
      iVar19 = iVar19 + 0x110;

      puVar1 = puVar18 + 0x97;
      puVar18 = puVar18 + 0x44;

	  // PushBuffer_SetDrawEnv_Normal
	  // param1 otmem
	  // param2 pushBuffer
	  // param3 backbuffer
      FUN_80042a8c(*puVar1 + 0xffc,puVar12,param_1[4],0,0);

	  // increment loop counter
	  iVar6 = iVar6 + 1;

	  // pointer to pushBuffer struct
      puVar12 = (uint *)((int)param_1 + iVar19);

	// (72a*4 = 1ca8), numPlyrCurrGame
	} while (iVar6 < (int)(uint)*(byte *)(param_1 + 0x72a));
  }

  if (
		// param1 is PTR_DAT_8008d2ac
		((param_1[0x95b] & 0x100) != 0) &&

		// if numPlyrCurrGame is more than 1
		(1 < (byte)PTR_DAT_8008d2ac[0x1ca8])
	)
  {
	// param1 is PTR_DAT_8008d2ac
    FUN_80023640(param_1);
  }

  // gGT->256c & 0x40
  if ((param_1[0x95b] & 0x40) != 0)
  {
	// Check if 231.dll is loaded
    iVar6 = FUN_800348e8();

	// if it is loaded
    if (iVar6 != 0)
	{
	  // RB_Player_ToggleInvisible (battle powerup)
      FUN_800b0dbc();

	  // RB_Player_ToggleFlicker (after damage in battle mode)
      FUN_800b0e68();

	  // RB_Burst_ProcessBucket
      FUN_800b1bd8(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1bb8));

	  // RB_Blowup_ProcessBucket
      FUN_800b1714(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1bcc));

	  // RB_Spider_DrawWebs
	  // pointer to first spider thread
      FUN_800b95fc(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1bf4),param_1 + 0x5a);

	  // RB_Follower_ProcessBucket
      FUN_800b6d58(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1c08));

	  // RB_StartText_ProcessBucket
      FUN_800b9dd8(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1c1c));
    }

	// Check if DLL 232 is loaded
    iVar6 = FUN_80034920();

    if (
			// If it is loaded
			(iVar6 != 0) &&

			// If you're in Adventure Arena
			((*(uint *)PTR_DAT_8008d2ac & 0x100000) != 0)
		)
	{
	  // AH_WarpPad_AllWarppadNum
      FUN_800abbdc();
    }

	// loop counter
    iVar6 = 0;

	// Process Turbo ThreadBucket
    FUN_80069284(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1be0));

	// param1 is PTR_DAT_8008d2ac
	// (72a*4 = 1ca8), numPlyrCurrGame
    if (*(char *)(param_1 + 0x72a) != '\0')
	{
	  // offset of 8008d2ac where pushBuffer structs are stored
      iVar19 = 0x168;

      do
	  {
		// pointer to pushBuffer struct
        iVar13 = (int)param_1 + iVar19;

		// Draw Skidmarks of all Player threads
        FUN_8005c354(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),iVar13);

		// increment pointer to next pushBuffer struct
        iVar19 = iVar19 + 0x110;

		// Draw Skidmarks of all robotcar threads
        FUN_8005c354(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),iVar13);

		// increment loop counter
		iVar6 = iVar6 + 1;

		// (72a*4 = 1ca8), numPlyrCurrGame
      } while (iVar6 < (int)(uint)*(byte *)(param_1 + 0x72a));
    }
  }

  // title screen, crash and trophy
  if (
		// If in main menu (character selection, track selection, any part of it)
		((*(uint *)PTR_DAT_8008d2ac & 0x2000) != 0) &&

		(
			// Check if 230 dll is loaded
			iVar6 = FUN_80034908(),
			iVar6 != 0
		)
	  )
  {
	// MM_Title_SetTrophyDPP
    FUN_800ac178();
  }

  // gGT->256c & RenderBucket
  if ((param_1[0x95b] & 0x20) != 0)
  {
	// RenderBucket_Execute
    FUN_8006aaa8(
					// render bucket instance
					*(undefined4 *)(PTR_DAT_8008d2ac + 0x1c94),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74
                );
  }

  // gGT->256c & wheels
  if ((param_1[0x95b] & 0x80) != 0)
  {
	// This block of code draws tires
	// Only if param_1[0x95b] & 0x20 is also true

	// pointer to first Player thread
    if (*(int *)(PTR_DAT_8008d2ac + 0x1b2c) != 0)
	{
	  // Draw normal tires (no reflection)
      FUN_8006e588(
					// pointer to first Player thread
					*(int *)(PTR_DAT_8008d2ac + 0x1b2c),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

					// (72a*4 = 1ca8), numPlyrCurrGame
                   (uint)*(byte *)(param_1 + 0x72a));

	  //Draws reflected wheels (visible on ice terrain)
      FUN_8006f004(
					// pointer to first Player thread
					*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),

				   // pointer to PrimMem struct
				   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

				   // (72a*4 = 1ca8), numPlyrCurrGame
				   (uint)*(byte *)(param_1 + 0x72a));
    }

	// If number of AIs is not zero
    if (PTR_DAT_8008d2ac[0x1cab] != '\0')
	{
	  // Draw normal tires (no reflection)
      FUN_8006e588(
					// pointer to first robotcar thread
					*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),

				   // pointer to PrimMem struct
				   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

				   // (72a*4 = 1ca8), numPlyrCurrGame
				   (uint)*(byte *)(param_1 + 0x72a));

	  //Draws reflected wheels (visible on ice terrain)
	  FUN_8006f004(
					// pointer to first robotcar thread
					*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),

				   // pointer to PrimMem struct
				   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

				   // (72a*4 = 1ca8), numPlyrCurrGame
				   (uint)*(byte *)(param_1 + 0x72a));
    }

	// if pointer to first ghost thread is valid
    if (*(int *)(PTR_DAT_8008d2ac + 0x1b54) != 0)
	{
	  // Draw tires directly on screen (no reflection)
      FUN_8006e588(
					// pointer to first ghost thread
					*(int *)(PTR_DAT_8008d2ac + 0x1b54),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

					// (72a*4 = 1ca8), numPlyrCurrGame
                   (uint)*(byte *)(param_1 + 0x72a));

	  //Draws reflected wheels (visible on ice terrain)
      FUN_8006f004(
					// pointer to first ghost thread
					*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b54),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

					// (72a*4 = 1ca8), numPlyrCurrGame
					(uint)*(byte *)(param_1 + 0x72a));
    }
  }

  // gGT->256c & shadows
  if ((param_1[0x95b] & 0x400) != 0)
  {
	// This draws shadows
    FUN_8005b720();
  }

  // gGT->256c & heat particles
  if ((param_1[0x95b] & 0x800) != 0)
  {
	// draw heat effect (tiger temple fire, behind rockets, etc)
    FUN_8004b470(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1ca0),

				// 0x5a*4 = 0x168 (pushBuffer structs)
				param_1 + 0x5a,

				 // pointer to PrimMem struct
				 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

				 // (72a*4 = 1ca8), numPlyrCurrGame
				 (uint)*(byte *)(param_1 + 0x72a),

				 // swapchain index * 0x128
                 *(int *)(PTR_DAT_8008d2ac + 0xc) * 0x128);
  }

  // PushBuffer_FadeAllWindows
  FUN_80043ab8();

  // draw level
  if (
		// gGT->256c & drawLev
		((param_1[0x95b] & 1) != 0) &&

		// if LEV mesh_info is valid
		(iVar22 != 0)
	 )
  {

	// number of players
    bVar2 = PTR_DAT_8008d2ac[0x1ca8];

	// if there are two players
    if (bVar2 == 2)
	{
	  // CTR_ClearRenderLists_1P2P
      FUN_80021bbc(param_1,2);

	  // lev offset 0xDC
      if ((piVar21[0x37] & 4U) == 0)
	  {
		// animates water, 2P mode
        FUN_8006d864(param_1[0x73b],piVar21[0xd],piVar21[0xe],piVar21[0x11],
		
					// VisMem 0x20 - 0x2f (visOVertList)
                     *(undefined4 *)(param_1[0x68e] + 0x20),
					 *(undefined4 *)(param_1[0x68e] + 0x24));
      }

	  // loop counter
      iVar19 = 0;

	  // RenderLists_PreInit
      FUN_800702d4();

	  // offset 0x1CC0,
	  // bspLeafsDrawn for all render lists of all players combined
      param_1[0x730] = 0;

	  // render lists
      iVar13 = 0x1808;

	  // offset of 8008d2ac where pushBuffer structs are held
      iVar6 = 0x168;

	  // for iVar19 = 0; iVar19 < 2; iVar19++
      do
	  {
		// pointer to pushBuffer structs
        iVar20 = (int)param_1 + iVar6;

	    // VisMem = 
		// gGT 0x1a38 (68e*4)
		// lev + 0x190
		// also CameraDC

		// Vismem 0x0-0xF
        puVar9 = (undefined4 *)(param_1[0x68e] + iVar19 * 4);

		// render lists
		local_54 = (int)param_1 + iVar13;
        iVar13 = iVar13 + 0x30;

		// increment offset to next pushBuffer struct
        iVar6 = iVar6 + 0x110;

		// RenderLists_Init1P2P
        iVar20 = FUN_8006fe70(

						// LEV->mesh_info->bspRoot
						*(undefined4 *)(iVar22 + 0x18),

						// Vismem 0x0-0xF
						*puVar9,

						// pushBuffer
						iVar20,

						// render lists
						local_54,

						// VisMem 0x80-0x8F
						puVar9[0x20],

						// (72a*4 = 1ca8), numPlyrCurrGame
						(uint)*(byte *)(param_1 + 0x72a));

		// increment loop counter
		iVar19 = iVar19 + 1;

		// offset 0x1CC0,
		// bspLeafsDrawn for all render lists of all players combined
        param_1[0x730] = param_1[0x730] + iVar20;

	  } while (iVar19 < 2);

	  // loop counter
      iVar6 = 0;

	  // pointer to pushBuffer struct
      iVar19 = 0x168;

	  // param1 is PTR_DAT_8008d2ac

	  // Draw 2p LEV geometry
	  // does not include individual models like boxes
      FUN_800a0cbc(
					// 1808, render lists
					param_1 + 0x602,

					// 0x5a*4 = 0x168 (pushBuffer structs)
					param_1 + 0x5a,

					// LEV -> ptr_mesh_info
					iVar22,

					// gGT->backBuffer->primMem
					param_1[4] + 0x74,

					// Vismem 0x10-0x1F
					*(undefined4 *)(param_1[0x68e] + 0x10),
					*(undefined4 *)(param_1[0x68e] + 0x14),

					// level -> ptr_restart_main
					piVar21[0x11]
					);

      puVar18 = param_1;

	  // for iVar6 = 0; iVar6 < 2; iVar6++
	  do
	  {
		// pointer to pushBuffer struct
        iVar22 = (int)param_1 + iVar19;

		// gGT + 0x25C
		// pushBuffer->ptrOT
        puVar12 = puVar18 + 0x97;

		// gGT + 0x25C + 0x110
		// pushBuffer(next)->ptrOT
        puVar18 = puVar18 + 0x44;

		// increment offset to next pushBuffer struct
		iVar19 = iVar19 + 0x110;

		// increment loop counter
        iVar6 = iVar6 + 1;

		// CAM_SkyboxGlow
        FUN_800175cc(

			// LEV -> skyboxGlowData
			piVar21 + 0x12,

			// pushBuffer
			iVar22,

			// gGT->backBuffer->primMem
			param_1[4] + 0x74,

			// ptrOT + 0xffc?
			*puVar12 + 0xffc);

      } while (iVar6 < 2);
    }

	// param1 is PTR_DAT_8008d2ac

	// if there are not two players
    else
	{
	  // if there are less than 3 players
      if (bVar2 < 3)
	  {
		// if there is one player
        if (bVar2 == 1)
		{
		  // CTR_ClearRenderLists_1P2P
          FUN_80021bbc(param_1,1);

		  // lev offset 0xDC
		  if (((piVar21[0x37] & 4U) == 0) && (piVar21 != (int *)0x0))
		  {
			// animates water, 1P mode
			// s0 - &gGT->pushBuffer[0]
            FUN_8006d79c(param_1[0x73b],piVar21[0xd],piVar21[0xe],piVar21[0x11],
                         
						 // Vismem 0x20-0x2F (visOVertList)
						 *(undefined4 *)(param_1[0x68e] + 0x20));
          }

		  else
		  {
			// roo's pipe floors
			
			// AnimateQuads
			// s0 - &gGT->pushBuffer[0]
            FUN_80069e70(
			
						// timer
						param_1[0x73b] << 7,
			
						// lev -> 0x174 and 0x178,
						// numSCVert, and ptrSCVert
						piVar21[0x5d],
						piVar21[0x5e],
			
						// Vismem 0x30-0x3F (visSCVertList)
                        *(undefined4 *)(param_1[0x68e] + 0x30));
          }

		  // pushBuffer -> 0x18, distToScreen
          DAT_1f80001c = *(int *)(PTR_DAT_8008d2ac + 0x180);

          if (
				// If Level ID == 40
				// If you are in Adventure Character Selection Screen
				(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x28) ||

				(
					// If you are in a cutscene
					(*(uint *)PTR_DAT_8008d2ac & 0x20000000) != 0 &&

					// Level ID != 37
					// If it is not Crash Bandicoot intro (he's sleeping and snoring)
					(*(int *)(PTR_DAT_8008d2ac + 0x1a10) != 0x25)
				)
			  )
		  {
            DAT_1f800014 = 0x1e00;
            DAT_1f800018 = 0x640;
            DAT_1f80001c = 0x640;
            DAT_1f800020 = 0x500;
            DAT_1f800024 = 0x280;
            DAT_1f800028 = 0x140;
            DAT_1f80002c = 0x780;
          }
          else {
            DAT_1f800014 = DAT_1f80001c * 0x2080;
            if (DAT_1f800014 < 0) {
              DAT_1f800014 = DAT_1f800014 + 0xff;
            }
            DAT_1f800024 = DAT_1f80001c * 7;
            DAT_1f800028 = DAT_1f80001c * 0x380;
            DAT_1f800014 = DAT_1f800014 >> 8;
            DAT_1f800020 = DAT_1f80001c * 0xc;
            DAT_1f800018 = DAT_1f80001c * 0x1a;
            DAT_1f80001c = DAT_1f80001c * 0x18;
            if (DAT_1f800028 < 0) {
              DAT_1f800028 = DAT_1f800028 + 0xff;
            }
            DAT_1f800028 = DAT_1f800028 >> 8;
            DAT_1f80002c = DAT_1f800018 + 0x140;
          }

		  // RenderLists_PreInit
          FUN_800702d4();

		  // param1 is PTR_DAT_8008d2ac

		  // 0x5a*4 = 0x168 (pushBuffer structs)
          puVar18 = param_1 + 0x5a;

		  // iVar22 is LEV->mesh_info,
		  // iVar22+0x18 = LEV->mesh_info->bspRoot

		  // RenderLists_Init1P2P
          uVar7 = FUN_8006fe70(

						// LEV->mesh_info->bspRoot
						*(undefined4 *)(iVar22 + 0x18),

						// Vismem 0x0-0xF
						*(undefined4 *)param_1[0x68e],

						// pushBuffer
						puVar18,

						// render lists
						param_1 + 0x602,

						// VisMem 0x80-0x8F
						((undefined4 *)param_1[0x68e])[0x20],

						// (72a*4 = 1ca8), numPlyrCurrGame
						(uint)*(byte *)(param_1 + 0x72a));

		  // offset 0x1CC0,
		  // bspLeafsDrawn for all render lists of all players combined
          param_1[0x730] = uVar7;

		  // draw 1p LEV geometry
		  // does not include individual models like boxes
          FUN_800a0cbc(
						// 1808, render lists
						param_1 + 0x602,

						// pushBuffer structs
						puVar18,

						// LEV -> ptr_mesh_info
						*piVar21,

						// gGT->backBuffer->primMem
						param_1[4] + 0x74,

						// Vismem 0x10-0x1F
					   *(undefined4 *)(param_1[0x68e] + 0x10),

					   piVar21[0x11]
					   );

		  // Draw full level skybox
		  FUN_80069bb0(
						// level ptr_skybox
						piVar21[1],

						// pushBuffer
						puVar18,

						// gGT->backBuffer->primMem
						param_1[4] + 0x74);

		  // lev offset 0xDC,
		  // if gradient is enabled
		  if ((piVar21[0x37] & 1U) != 0)
		  {
			// CAM_SkyboxGlow
            FUN_800175cc(

				// LEV -> skyboxGlowData
				piVar21 + 0x12,

				// pushBuffer
				puVar18,

				// gGT->backBuffer->primMem
				param_1[4] + 0x74,

				// gGT+0x25C
				// pushBuffer->ptrOT
				param_1[0x97] + 0xffc);
          }
        }
      }

	  // if there are not less than 3 players
      else
	  {
		// param1 is PTR_DAT_8008d2ac

		// if there are 3 players
        if (bVar2 == 3)
		{
		  // CTR_ClearRenderLists_3P4P
          FUN_80021c2c(param_1,3);

		  // lev offset 0xDC
          if ((piVar21[0x37] & 4U) == 0)
		  {
			// animates water, 3P mode
            FUN_8006d948(param_1[0x73b],piVar21[0xd],piVar21[0xe],piVar21[0x11],
			
						// Vismem 0x20-0x2F (visOVertList)
                         *(undefined4 *)(param_1[0x68e] + 0x20),
                         *(undefined4 *)(param_1[0x68e] + 0x24),
                         *(undefined4 *)(param_1[0x68e] + 0x28));
          }

		  // loop counter
          iVar19 = 0;

		  // RenderLists_PreInit
          FUN_800702d4();

		  // offset 0x1CC0,
		  // bspLeafsDrawn for all render lists of all players combined
          param_1[0x730] = 0;

		  // 1808, render lists
          iVar13 = 0x1808;

		  // offset of 8008d2ac where pushBuffer structs are held
          iVar6 = 0x168;

		  // for iVar9 = 0; iVar9 < 3; iVar9++
          do
		  {
			// pointer to pushBuffer struct
            iVar20 = (int)param_1 + iVar6;

			// gGT -> render list for player
            local_54 = (int)param_1 + iVar13;

			// Vismem 0x0-0xF
            puVar9 = (undefined4 *)(param_1[0x68e] + iVar19 * 4);

			// next render list
			iVar13 = iVar13 + 0x30;

			// increment offset to next pushBuffer struct
            iVar6 = iVar6 + 0x110;

			// RenderLists_Init3P4P
            iVar20 = FUN_80070388(

				// LEV->mesh_info->bspRoot
				*(undefined4 *)(iVar22 + 0x18),

				// Vismem 0x0-0xF
				*puVar9,

				// pushBuffer
				iVar20,

				// render list to generate
				local_54,

				// VisMem 0x80-0x8F
				puVar9[0x20]);

			// increment loop counter
            iVar19 = iVar19 + 1;

			// offset 0x1CC0,
			// bspLeafsDrawn for all render lists of all players combined
            param_1[0x730] = param_1[0x730] + iVar20;

		  } while (iVar19 < 3);

		  // loop counter
          iVar6 = 0;

		  // offset of 8008d2ac where pushBuffer structs
		  // are held for each player (pos, size, etc)
          iVar19 = 0x168;

		  // param1 is PTR_DAT_8008d2ac

		  // draw 3p LEV geometry
		  // does not include models like boxes
          FUN_800a0cbc(
						// 1808, render lists
						param_1 + 0x602,

						// 0x5a*4 = 0x168 (pushBuffer structs)
						param_1 + 0x5a,

						// LEV -> ptr_mesh_info
						iVar22,

						// gGT->backBuffer->primMem
						param_1[4] + 0x74,

						// Vismem 0x10-0x1F
						*(undefined4 *)(param_1[0x68e] + 0x10),
						*(undefined4 *)(param_1[0x68e] + 0x14),
						*(undefined4 *)(param_1[0x68e] + 0x18),

						piVar21[0x11]
						);

          puVar18 = param_1;

		  // for iVar6 = 0; iVar6 < 3; iVar6++
          do
		  {
			// pointer to pushBuffer struct
            iVar22 = (int)param_1 + iVar19;

			// gGT + 0x25C
			// pushBuffer->ptrOT
            puVar12 = puVar18 + 0x97;

			// gGT + 0x25C + 0x110
			// pushBuffer(next)->ptrOT
            puVar18 = puVar18 + 0x44;

			// increment pointer to next pushBuffer struct
			iVar19 = iVar19 + 0x110;

			// increment loop counter
            iVar6 = iVar6 + 1;

			// CAM_SkyboxGlow
            FUN_800175cc(

				// LEV -> skyboxGlowData
				piVar21 + 0x12,

				// pushBuffer
				iVar22,

				// gGT->backBuffer->primMem
				param_1[4] + 0x74,

				// ptrOT + 0xffc?
				*puVar12 + 0xffc);

          } while (iVar6 < 3);
        }

		// if there are not 3 players
		else
		{
		  // if there are four players
          if (bVar2 == 4) {

			// param1 is PTR_DAT_8008d2ac

			// CTR_ClearRenderLists_3P4P
            FUN_80021c2c(param_1,4);

			// lev offset 0xDC
            if ((piVar21[0x37] & 4U) == 0)
			{
			  // animates water, 4P mode
              FUN_8006da50(param_1[0x73b],piVar21[0xd],piVar21[0xe],piVar21[0x11],
			  
							// Vismem 0x20-0x2F (visOVertList)
                           *(undefined4 *)(param_1[0x68e] + 0x20),
                           *(undefined4 *)(param_1[0x68e] + 0x24),
                           *(undefined4 *)(param_1[0x68e] + 0x28),
                           *(undefined4 *)(param_1[0x68e] + 0x2c));
            }

			// loop counter
            iVar19 = 0;

			// RenderLists_PreInit
            FUN_800702d4();

			// offset 0x1CC0,
			// bspLeafsDrawn for all render lists of all players combined
            param_1[0x730] = 0;

			// render list
            iVar13 = 0x1808;

			// offset to next pushBuffer struct
            iVar6 = 0x168;

			// for iVar19 = 0; iVar19 < 4; iVar19++
            do
			{
			  // pointer to pushBuffer struct
              iVar20 = (int)param_1 + iVar6;

			  // render list
              local_54 = (int)param_1 + iVar13;
			  
			  // Vismem 0x0-0xF
              puVar9 = (undefined4 *)(param_1[0x68e] + iVar19 * 4);
              
			  // render list
			  iVar13 = iVar13 + 0x30;

			  // increment pointer to next pushBuffer structure
              iVar6 = iVar6 + 0x110;

			  // RenderLists_Init3P4P
              iVar20 = FUN_80070388(

					// LEV->mesh_info->bspRoot
					*(undefined4 *)(iVar22 + 0x18),

					// Vismem 0x0-0xF
					*puVar9,

					// pushBuffer
					iVar20,

					// render list being generated
					local_54,

					// VisMem 0x80-0x8F
                    puVar9[0x20]);

			  // increment loop counter
              iVar19 = iVar19 + 1;

			  // offset 0x1CC0,
			  // bspLeafsDrawn for all render lists of all players combined
              param_1[0x730] = param_1[0x730] + iVar20;

            } while (iVar19 < 4);

			// param1 is PTR_DAT_8008d2ac

			// loop counter
            iVar6 = 0;

			// offset of 8008d2ac to pushBuffer structs
            iVar19 = 0x168;

			// draw 4p LEV geometry
			// does not include models like boxes
            FUN_800a0cbc(
			
						// 1808, render lists
						param_1 + 0x602,

						// 0x5a*4 = 0x168 (pushBuffer structs)
						param_1 + 0x5a,

						// LEV -> ptr_mesh_info
						iVar22,

						// gGT->backBuffer->primMem
						param_1[4] + 0x74,

						// Vismem 0x10-0x1F
                        *(undefined4 *)(param_1[0x68e] + 0x10),
                        *(undefined4 *)(param_1[0x68e] + 0x14),
                        *(undefined4 *)(param_1[0x68e] + 0x18),
                        *(undefined4 *)(param_1[0x68e] + 0x1c),

						piVar21[0x11]
					);

			puVar18 = param_1;

			// for iVar6 = 0; iVar6 < 4; iVar6++
            do
			{
			  // pointer to pushBuffer struct
              iVar22 = (int)param_1 + iVar19;

			  // gGT + 0x25C
			  // pushBuffer->ptrOT
              puVar12 = puVar18 + 0x97;

			  // gGT + 0x25C + 0x110
			  // pushBuffer(next)->ptrOT
              puVar18 = puVar18 + 0x44;

			  // increment offset to next pushBuffer
			  iVar19 = iVar19 + 0x110;

			  // increment loop counter
              iVar6 = iVar6 + 1;

			  // CAM_SkyboxGlow
              FUN_800175cc(

				// LEV -> skyboxGlowData
				piVar21 + 0x12,

				// pushBuffer
				iVar22,

				// gGT->backBuffer->primMem
				param_1[4] + 0x74,

				// ptrOT + 0xffc?
				*puVar12 + 0xffc);

            } while (iVar6 < 4);
          }
        }
      }
    }

	// param1 is PTR_DAT_8008d2ac

	// loop counter
    iVar6 = 0;

	// (72a*4 = 1ca8), numPlyrCurrGame
    if (*(char *)(param_1 + 0x72a) != '\0')
	{
	  // offset of 8008d2ac where pushBuffer structs are stored
      iVar22 = 0x168;

	  // pointer to the "full screen" pushBuffer, which comes 0x110
	  // bytes before each player's individual internal pushBuffer
      puVar12 = param_1 + 0x5a;

      puVar18 = param_1;
      do {

		// increment offset to next pushBuffer struct
        iVar22 = iVar22 + 0x110;

        puVar1 = puVar18 + 0x97;
        puVar18 = puVar18 + 0x44;

		// PushBuffer_SetDrawEnv_Normal
		// param1 otmem
		// param2 pushBuffer
		// param3 backbuffer
        FUN_80042a8c(*puVar1 + 0xffc,puVar12,param_1[4],0,0);

		// increment loop counter
        iVar6 = iVar6 + 1;

        puVar12 = (uint *)((int)param_1 + iVar22);

		// (72a*4 = 1ca8), numPlyrCurrGame
      } while (iVar6 < (int)(uint)*(byte *)(param_1 + 0x72a));
    }

	// multiplayer wumpa hud 3D
    if (
			// gGT->hudFlags & 1
			((PTR_DAT_8008d2ac[0x1d31] & 1) != 0) &&

			// if numPlyrCurrGame is more than 1
			(1 < (byte)PTR_DAT_8008d2ac[0x1ca8])
		)
	{
	  // UI_RenderFrame_Wumpa3D_2P3P4P
	  // param1 is gGT
      FUN_8005465c(param_1);
    }

    if (
		// param1 is PTR_DAT_8008d2ac
		((param_1[0x95b] & 0x100) != 0) &&

		// if numPlyrCurrGame is more than 1
		(1 < (byte)PTR_DAT_8008d2ac[0x1ca8])
		)
	{
	  // param1 is PTR_DAT_8008d2ac
      FUN_80023784(param_1);
    }

	if (
			// if not cutscene
			// if not in adventure arena
			// if not in main menu
			((*param_1 & 0x20102000) == 0) &&

			// If loading is 100% finished
			(DAT_8008d0f8 != -4)
		)
	{
	  // DotLights_AudioAndVideo
      FUN_800242b8(param_1);
    }

	// if drawing 2D lines between multiplayer screens
    if ((*(uint *)(PTR_DAT_8008d2ac + 0x256c) & 0x8000) != 0) {

      if (
			(
				// If you're in Battle Mode
				((*(uint *)PTR_DAT_8008d2ac & 0x20) != 0) &&

				// if numPlyrCurrGame is more than 2
				(2 < (byte)PTR_DAT_8008d2ac[0x1ca8])
			) &&
			(
				// set loop counter to zero
				iVar6 = 0,

				// numPlyrCurrGame is not zero
				PTR_DAT_8008d2ac[0x1ca8] != '\0'
			)
		 )
	  {
        iVar22 = 0;

	    // for(int iVar6 = 0; iVar6 < numPlyrCurrGame; iVar6++)
        do {
          puVar14 = PTR_DAT_8008d2ac + iVar22;

		  // Get dimensions of each window (pushBuffer)
          local_30 = *(undefined2 *)(puVar14 + 0x184);	// startX
          local_2e = *(undefined2 *)(puVar14 + 0x186);	// startY
          local_2c = *(undefined2 *)(puVar14 + 0x188);	// sizeX
          local_2a = *(undefined2 *)(puVar14 + 0x18a);	// sizeY

		  // Draw a 2D box made of four rectangles
		  FUN_80045534(&local_30,4,2,

					   // Get Color based on...
					   (&PTR_DAT_80081d70)
											// Battle Team that the player is on
                       [*(int *)(*(int *)(PTR_DAT_8008d2ac + iVar6 * 4 + 0x24ec) + 0x4e8) + 0x18],

					   0,

					   // pointer to OT mem -> curr
					   *(int *)(PTR_DAT_8008d2ac + 0x147c) + 0xc);

		  // increment loop counter
          iVar6 = iVar6 + 1;

          iVar22 = iVar22 + 0x110;

						// numPlyrCurrGame
        } while (iVar6 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
      }

	  // if numPlyrCurrGame is more than 1
      if (1 < (byte)PTR_DAT_8008d2ac[0x1ca8])
	  {
		// backBuffer->primMem.curr
        p = *(void **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80);

		// psyq macro setPolyF4
        *(undefined *)((int)p + 3) = 5;
        *(undefined *)((int)p + 7) = 0x28;

		// RGB (black)
        *(undefined *)((int)p + 6) = 0;
        *(undefined *)((int)p + 5) = 0;
        *(undefined *)((int)p + 4) = 0;

        puVar14 = PTR_DAT_8008d2ac;

		// Make four (x,y) coordinates
        *(undefined2 *)((int)p + 10) = 0x6a;
        *(undefined2 *)((int)p + 0xe) = 0x6a;
        *(undefined2 *)((int)p + 8) = 0;
        *(undefined2 *)((int)p + 0xc) = 0x200;
        *(undefined2 *)((int)p + 0x10) = 0;
        *(undefined2 *)((int)p + 0x12) = 0x6e;
        *(undefined2 *)((int)p + 0x14) = 0x200;
        *(undefined2 *)((int)p + 0x16) = 0x6e;

		// Draw a bar from left to right,
		// dividing the screen in half on top and bottom
        AddPrim((void *)(*(int *)(puVar14 + 0x147c) + 0xc),p);

		// backBuffer->primMem.curr
        *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) =
             *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) + 0x18;
      }

	  // if numPlyrCurrGame is more than 2
      if (2 < (byte)PTR_DAT_8008d2ac[0x1ca8])
	  {
		// backBuffer->primMem.curr
        p = *(void **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80);
		
		// psyq macro setPolyF4
        *(undefined *)((int)p + 3) = 5;
        *(undefined *)((int)p + 7) = 0x28;
        
		// RGB (black)
		*(undefined *)((int)p + 6) = 0;
        *(undefined *)((int)p + 5) = 0;
        *(undefined *)((int)p + 4) = 0;

        puVar14 = PTR_DAT_8008d2ac;

		// Make four (x,y) coordinates
		*(undefined2 *)((int)p + 8) = 0xfd;
        *(undefined2 *)((int)p + 0x10) = 0xfd;
        *(undefined2 *)((int)p + 10) = 0;
        *(undefined2 *)((int)p + 0xc) = 0x103;
        *(undefined2 *)((int)p + 0xe) = 0;
        *(undefined2 *)((int)p + 0x12) = 0xd8;
        *(undefined2 *)((int)p + 0x14) = 0x103;
        *(undefined2 *)((int)p + 0x16) = 0xd8;

		// Draw a bar from top to bottom,
		// dividing the screen in half on left and right
        AddPrim((void *)(*(int *)(puVar14 + 0x147c) + 0xc),p);

		// backBuffer->primMem.curr
		*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) =
             *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) + 0x18;
      }

	  // if numPlyrCurrGame is 3
      if (PTR_DAT_8008d2ac[0x1ca8] == '\x03')
	  {
		// backBuffer->primMem.curr
        p = *(void **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80);

		// psyq macro setPolyF4
        *(undefined *)((int)p + 3) = 5;
        *(undefined *)((int)p + 7) = 0x28;
		
		// RGB (black)
        *(undefined *)((int)p + 6) = 0;
        *(undefined *)((int)p + 5) = 0;
        *(undefined *)((int)p + 4) = 0;
		
		// xy0
        *(undefined2 *)((int)p + 8) = 0x100;
        *(undefined2 *)((int)p + 0x10) = 0x100;

        puVar14 = PTR_DAT_8008d2ac;

		// Make three more (x,y) coordinates
		*(undefined2 *)((int)p + 10) = 0x6c;
        *(undefined2 *)((int)p + 0xe) = 0x6c;
        *(undefined2 *)((int)p + 0xc) = 0x200;
        *(undefined2 *)((int)p + 0x12) = 0xd8;
        *(undefined2 *)((int)p + 0x14) = 0x200;
        *(undefined2 *)((int)p + 0x16) = 0xd8;

		// Draw black quad, map wil be rendered on top of this
        AddPrim((void *)(*(int *)(puVar14 + 0x147c) + 0xc),p);

		// backBuffer->primMem.curr
		*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) =
             *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) + 0x18;
      }
    }

	// if game is not loading
    if (DAT_8008d0f8 == -1) {

	  // If game is not paused
      if ((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0)
	  {
		// PickupBots_Update
        FUN_800408b8();
      }

	  // PlayLevel_UpdateLapStats
      FUN_800414f4();
    }
  }

  // If in main menu, or in adventure arena,
  // or in End-Of-Race menu
  if ((*(uint *)PTR_DAT_8008d2ac & 0x302000) != 0) {
    FUN_80047d64();
  }

  // clear swapchain
  if (
		// gGT->256c & clear swapchain
		((*(uint *)(PTR_DAT_8008d2ac + 0x256c) & 0x2000) != 0) &&

		// if lev has clear-color data, for clearing screen without skybox
		((*(char *)(param_1[0x58] + 0x163) != '\0' || (*(char *)(param_1[0x58] + 0x167) != '\0')))
	 )
  {
	// CAM_ClearScreen
    FUN_8001861c(param_1);
  }

  // gGT->256c & checkered flag
  if ((*(uint *)(PTR_DAT_8008d2ac + 0x256c) & 0x1000) != 0)
  {
    // draw checkered flag
	FUN_800444e8();
  }

  // param1 is PTR_DAT_8008d2ac

  // PushBuffer_SetDrawEnv_Normal
  // param1 otmem
  // param2 pushBuffer
  // param3 backbuffer
  // 0x4e2 = 0x1388 = pushBuffer_UI
  // 0x51f = 0x147c = pushBuffer_UI + 0xf4 (ptrOT)
  FUN_80042a8c(param_1[0x51f] + 0x10,param_1 + 0x4e2,param_1[4],0,0);

  // Timer_GetTime_Total
  uVar7 = FUN_8004b3a4();
  puVar14 = PTR_DAT_8008d2ac;
  param_1[0x737] = uVar7;

  // gGT->256c & checkered flag
  if ((*(uint *)(puVar14 + 0x256c) & 0x1000) != 0) {
    VSync(0);
  }

  // determine if drawsync has finished
  cVar3 = PTR_DAT_8008d2ac[0x1d30];

  // Pause CPU, at least until two VSyncCallback's are done (30fps),
  // or force drawing to stop if six VsyncCallback's are done (6fps)
  while( true )
  {
	// if drawSync is finished, and two VsyncCallback's have run
    if ((cVar3 == '\0') && (DAT_8008d2b4 < 1)) goto LAB_800378d0;

	// If VsyncCallback executes 6 times, and DrawSync is still not done,
	// then game is under 6fps, BreakDraw
	if (6 < *(uint *)(PTR_DAT_8008d2ac + 0x1ce0)) break;

	// check again
	cVar3 = PTR_DAT_8008d2ac[0x1d30];
  }

  // Dont finish the last DrawOTag
  // request, just stop drawing
  BreakDraw();

LAB_800378d0:

  // draw video:
  // if a STR video is playing
  if (DAT_8008d2c8 == 1)
  {
	// MM_Video_CheckIfFinished
    FUN_800b6674(1);

	// draw STR on screen by copying a rectangle from
	// one place in VRAM (offscreen) to another (in the swapchain image)
	MoveImage(&DAT_8008d880,(int)DAT_8008d89c,(int)DAT_8008d8a0);

	DrawSync(0);
  }

  // param1 is PTR_DAT_8008d2ac

  // 737 -> 1cdc
  // Timer_GetTime_Elapsed
  uVar7 = FUN_8004b41c(param_1[0x737],0);
  param_1[0x737] = uVar7;

  // if frontBuffer exists
  if (param_1[5] != 0)
  {
	// frame duplicator
    DAT_8008d2b4 = 2;

	// debug variable
    uVar7 = DAT_8008cff0 & 1;

	// unused debug timer
	*(undefined4 *)(PTR_DAT_8008d2ac + 0x1cd8) = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1cc4);

	// if not debug
	if (uVar7 == 0)
	{
	  // GameTracker frontBuffer dispEnv
      puVar14 = (undefined *)(param_1[5] + 0x5c);
    }

	// if debug
	else
	{
	  // blank dispEnv, all zeros
      puVar14 = &DAT_8008e6d4;
    }

	PutDispEnv(puVar14);

	// GameTracker frontBuffer drawEnv
    PutDrawEnv(param_1[5]);

	// wipe pointer to frontBuffer
	param_1[5] = 0;
  }

  puVar14 = PTR_DAT_8008d2ac;

  // calculate new frontBuffer based on swapchainIndex
  // swap=0, get db[1]
  // swap=1, get db[0]
  *(uint **)(param_1 + 5) = (uint *)((int)param_1 - (param_1[3] * 0xa4 + -0xbc));

  // Record that an OT has been submitted
  puVar14[0x1d30] = 1;

  // pushBuffer[0]->ptrOT + 0xffc,
  // draws from end to start
  DrawOTag(param_1[0x97] + 0xffc);

  // frame timer
  param_1[0x73a] = param_1[0x739];

  return;
}


// Draw NPC-105 wheel
void FUN_800379f4(short param_1,short param_2,short param_3,int param_4,undefined4 param_5,
                 undefined4 *param_6,undefined4 param_7,undefined4 param_8)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  short local_38;
  short local_36;
  short local_34;
  short local_32;
  short local_30;
  short local_2e;

  uVar6 = 0;
  local_48 = *param_6;
  local_44 = local_48;
  local_40 = local_48;
  local_38 = param_1;
  local_36 = param_2;
  do {
    uVar5 = (int)(short)uVar6 + (int)(short)param_5;

	// approximate trigonometry
	sVar1 = (short)*(int *)(&DAT_800845a0 + (uVar5 & 0x3ff) * 4);
    iVar4 = *(int *)(&DAT_800845a0 + (uVar5 & 0x3ff) * 4) >> 0x10;

	if ((uVar5 & 0x400) == 0) {
      iVar2 = (int)sVar1;
      if ((uVar5 & 0x800) != 0) {
        iVar3 = -iVar4;
        goto LAB_80037b18;
      }
    }
    else {
      iVar3 = (int)sVar1;
      iVar2 = iVar4;
      if ((uVar5 & 0x800) == 0) {
        iVar4 = -iVar3;
      }
      else {
LAB_80037b18:
        iVar2 = -iVar2;
        iVar4 = iVar3;
      }
    }
    local_30 = param_1 + (short)((((int)param_3 << 3) / 5) * iVar4 >> 0xc);
    local_2e = param_2 + (short)((int)param_3 * iVar2 >> 0xc);

	if ((uVar6 & 0xffff) != 0)
	{
	  // RECTMENU_DrawRwdTriangle
      FUN_800453e8(&local_38,&local_48,param_7,param_8);
    }

	uVar6 = uVar6 + param_4;
    local_34 = local_30;
    local_32 = local_2e;
    if (0x1000 < (int)(uVar6 * 0x10000) >> 0x10) {
      return;
    }
  } while( true );
}


// Draw left and right arrows around text
// Param1 - PosX
// Param2 - PosY
// Param3 - string
void FUN_80037bc0(short param_1,short param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined **ppuVar3;

  // orange color
  iVar2 = 0;

  if ((DAT_8008d970 & 4) == 0)
  {
	// red color
    iVar2 = 3;
  }

  // DecalFont_GetLineWidth
  iVar1 = FUN_800224d0(param_3,1);

  iVar1 = ((iVar1 << 0x10) >> 0x10) - ((iVar1 << 0x10) >> 0x1f) >> 1;

  // get color data
  ppuVar3 = &PTR_DAT_80081d70 + iVar2;

  // Draw left arrow
  FUN_80023190(
				// largeFont
				*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2124) + 0xf4),

				(param_1 - iVar1) + -0x14
               ,(int)param_2 + 7,

			   // pointer to PrimMem struct
			   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

			   // pointer to OT memory
			   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

			   // color data
			   *(undefined4 *)*ppuVar3,
               *(undefined4 *)(*ppuVar3 + 4),
			   *(undefined4 *)(*ppuVar3 + 8),
               *(undefined4 *)(*ppuVar3 + 0xc),

			   0,0x1000,0x800);

  // Draw right arrow
  FUN_80023190(

				// largeFont
				*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2124) + 0xf4),

				param_1 + iVar1 + 0x12,
               (int)param_2 + 7,

			   // pointer to PrimMem struct
			   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

			   // pointer to OT memory
			   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

			   // color data
			   *(undefined4 *)*ppuVar3,
               *(undefined4 *)(*ppuVar3 + 4),
			   *(undefined4 *)(*ppuVar3 + 8),
               *(undefined4 *)(*ppuVar3 + 0xc),

			   0,0x1000,0);
  return;
}


// Racing Wheel Configuration
void FUN_80037da0(void)

{
  bool bVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  undefined2 *puVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  ushort uVar14;
  short local_48 [8];
  undefined2 local_38;
  short local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_30;
  short local_2e;
  undefined2 local_2c;
  undefined2 local_2a;

  // If you press Triangle or Square
  if ((DAT_8008d950 & 0x40020) != 0) {

	// Leave configuration
    DAT_8008d864 = 0;
    return;
  }

  // Get gamepad ID from whoever opened
  // the configuration menu (0, 1, 2, 3)
  iVar11 = (int)DAT_8008d87c;

  pcVar6 = *(char **)(PTR_DAT_8008d2b0 + iVar11 * 0x50 + 0x20);

  if (pcVar6 == (char *)0x0) {

	// leave configuration
	DAT_8008d864 = 0;
    return;
  }

  if (*pcVar6 != '\0') {

	// Leave configuration
	DAT_8008d864 = 0;
    return;
  }

  // If this is NPC-105 gamepad
  bVar1 = pcVar6[1] == 0xE3;

  // make a copy
  uVar8 = (uint)bVar1;

  // If you're in the 2nd stage of configuration
  // If you're selecting Dead Zone
  if (DAT_8008d898 == 1)
  {
	// Get gamepad input from
    uVar3 = (&DAT_8009a990)[iVar11];

	// If you dont press Up or Left
    if ((uVar3 & 5) == 0)
	{
	  // If you dont press Down or Right
      if ((uVar3 & 10) == 0)
	  {
		// If you press Cross or Circle
        if ((uVar3 & 0x50) != 0)
		{
		  // Move to 3rd stage of configuration
          DAT_8008d898 = 2;

		  // Save the Dead Zone selected
          *(undefined2 *)((int)&DAT_800841fc + iVar11 * 6 + 2) =
               (&DAT_8008425c)[(int)(short)DAT_8008d868 * 3];
        }
      }

	  // If you press Down or Right
      else
	  {
		// Cycle through options
        DAT_8008d868 = DAT_8008d868 + 1;

		// If you go too far right
        if (3 < (short)DAT_8008d868)
		{
		  // cycle back to the beginning
          DAT_8008d868 = 0;
        }
      }
    }

	// If you press Up or Left
    else
	{
	  // cycle through options
      DAT_8008d868 = DAT_8008d868 - 1;

	  // if you go too far left
      if ((int)((uint)DAT_8008d868 << 0x10) < 0)
	  {
		// cycle back to the end
        DAT_8008d868 = 3;
      }
    }

	// DAT_8008d878 + 0x88c
	// SELECT DEAD ZONE AND PRESS *

	// DecalFont_DrawMultiLine
    FUN_80022b34(*(undefined4 *)(DAT_8008d878 + 0x88c),0x100,
                 (int)*(short *)(&DAT_8008d2e0 + uVar8 * 4),0x1cc,1,0xffff8000);

	FUN_80022878(

			// string
			*(undefined4 *)					// should be 0x80084258 \/
			((int)*(short *)((int)(short)DAT_8008d868 * 6 + -0x7ff7bda8) * 4 + DAT_8008d878),

			// PosX
			0x100,

			// PosY
			(int)*(short *)(&DAT_8008d2e8 + uVar8 * 4),

			1,0xffff8000);

	// Draw left and right arrows around text
	FUN_80037bc0(

		// PosX
		0x100,

		// PosY
		(int)*(short *)(&DAT_8008d2e8 + uVar8 * 4),

		// String
                 *(undefined4 *)					// should be 0x80084258 \/
                  ((int)*(short *)((int)(short)DAT_8008d868 * 6 + -0x7ff7bda8) * 4 + DAT_8008d878));

													// should be 0x8008425A \/
	DAT_8008d2f0 = SEXT24(*(short *)((int)(short)DAT_8008d868 * 6 + -0x7ff7bda6));
  }

  // If you are not in 2nd stage (value of 1)
  else
  {
	// If you are not in the 3rd stage (value of 2)
    if (DAT_8008d898 < 2)
	{
	  // If you're in the first stage of configuration
      if (DAT_8008d898 == 0)
	  {
		// DAT_8008d878 + 0x888
		// CENTER THE CONTROLLER AND PRESS *

		// DecalFont_DrawMultiLine
        FUN_80022b34(*(undefined4 *)(DAT_8008d878 + 0x888),0x100,
                     (int)*(short *)(&DAT_8008d2e0 + uVar8 * 4),0x1cc,1,0xffff8000);

		// Get gamepad ID from whoever opened
		// the configuration menu (0, 1, 2, 3)
        iVar11 = (int)DAT_8008d87c;

		// If you press Cross or Circle
        if (((&DAT_8009a990)[iVar11] & 0x50) != 0)
		{
		  // Move to 2nd stage of configuration
          DAT_8008d898 = DAT_8008d898 + 1;

		  // If this is NPC-105 gamepad
          if (bVar1) {
            PTR_DAT_8008d2b0[iVar11 * 0x50 + 0x44] = 4;
            *(undefined2 *)((int)&DAT_800841fc + (int)DAT_8008d87c * 6) = 0x80;
          }

		  // If this is not NPC-105 gamepad
          else {
            *(ushort *)((int)&DAT_800841fc + iVar11 * 6) =
                 (ushort)*(byte *)(*(int *)(PTR_DAT_8008d2b0 + iVar11 * 0x50 + 0x20) + 4);
          }

		  // clear gamepad input (for menus)
          FUN_80046404();
        }
        DAT_8008d2f0 = 0;
      }
    }

	// If you're on 2nd page of configuration (or farther)
	else
	{
	  // If you're on 3rd stage of configuration
	  // Select Range configuration
      if (DAT_8008d898 == 2)
	  {
		// get gamepad input
        uVar3 = (&DAT_8009a990)[iVar11];

		// If you dont press Up or Left
        if ((uVar3 & 5) == 0)
		{
		  // If you dont press Down or Right
          if ((uVar3 & 10) == 0)
		  {
			// If you press Cross or Circle
            if ((uVar3 & 0x50) != 0)
			{
			  // Leave Racing Configuration Menu
			  // Go back to Options Menu
              DAT_8008d864 = 0;

			  // Save "Range" value
              (&DAT_80084200)[iVar11 * 3] = (&DAT_80084274)[(int)(short)DAT_8008d894 * 3];

			  // clear gamepad input (for menus)
			  FUN_80046404();
            }
          }

		  // If you dont press Down or Right
          else
		  {
			// cycle through options
            DAT_8008d894 = DAT_8008d894 + 1;

			// If you go too far right
            if (*(short *)(&DAT_80084290 + uVar8 * 2) < (short)DAT_8008d894)
			{
			  // cycle back to the beginning
              DAT_8008d894 = 0;
            }
          }
        }

		// If you dont press Up or Left
        else
		{
		  // cycle through options
          DAT_8008d894 = DAT_8008d894 - 1;

		  // if you go too far left
          if ((int)((uint)DAT_8008d894 << 0x10) < 0)
		  {
			// cycle back to the end
            DAT_8008d894 = *(ushort *)(&DAT_80084290 + uVar8 * 2);
          }
        }

        DAT_8008d2f0 = SEXT24((short)(&DAT_80084272)[(int)(short)DAT_8008d894 * 3]);

		// DAT_8008d878 + 0x8a0
		// SELECT RANGE AND PRESS *

		// DecalFont_DrawMultiLine
        FUN_80022b34(*(undefined4 *)(DAT_8008d878 + 0x8a0),0x100,
                     (int)*(short *)(&DAT_8008d2e0 + uVar8 * 4),0x1cc,1,0xffff8000);

		// DecalFont_DrawLine
		FUN_80022878(

					// String
					*(undefined4 *)
                      ((int)*(short *)(&DAT_80084270 + (int)(short)DAT_8008d894 * 6) * 4 +
                      DAT_8008d878),

				// PosX
				0x100,

				// PosY
				(int)*(short *)(&DAT_8008d2e8 + uVar8 * 4),

				1,0xffff8000);

		// Draw left and right arrows around text
		FUN_80037bc0(

			// PosX
			0x100,

			// PosY
			(int)*(short *)(&DAT_8008d2e8 + uVar8 * 4),

			// String
                     *(undefined4 *)
                      ((int)*(short *)(&DAT_80084270 + (int)(short)DAT_8008d894 * 6) * 4 +
                      DAT_8008d878));
      }
    }
  }
  uVar8 = DAT_8008d2f0;
  iVar11 = 0;

  // If this is not NPC-105 gamepad
  if (!bVar1)
  {
	// loop counter
    iVar11 = 0;

    uVar3 = DAT_8008d2f0 & 0x3ff;

	// for iVar11 = 0; iVar11 < 3; iVar11++
	do {

	  // approximate trigonometry
      iVar7 = *(int *)(&DAT_800845a0 + uVar3 * 4);
      if ((uVar8 & 0x400) == 0) {
        iVar7 = iVar7 << 0x10;
      }
      iVar7 = iVar7 >> 0x10;
      if ((uVar8 & 0x800) != 0) {
        iVar7 = -iVar7;
      }

	  // pointer to OT mem
      iVar13 = *(int *)(PTR_DAT_8008d2ac + 0x147c);

      iVar7 = (DAT_8008d2d8 + (iVar7 * ((int)(short)iVar11 + -1) * 0x20 >> 0xc) + 0x20) * 0x10000 >>
              0x10;
      if (((int)(short)iVar11 != 1) && (uVar8 == 0x600)) {
        iVar13 = iVar13 + 0xc;
      }

	  // CTR_Box_DrawWirePrims
      FUN_80021500(
					0xe2,iVar7,
					0x11e,iVar7,
					0,0xff,0,iVar13,

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

	  // increment loop counter
	  iVar11 = iVar11 + 1;

    } while (iVar11 * 0x10000 >> 0x10 < 3);

    iVar7 = 0;
    iVar11 = 0;
    do {

	  // approximate trigonometry
	  uVar3 = (int)DAT_8008d970 * 0x40 + (iVar11 >> 5);
      iVar11 = *(int *)(&DAT_800845a0 + (uVar3 & 0x3c0) * 4);

	  if ((uVar3 & 0x400) == 0) {
        iVar11 = iVar11 << 0x10;
      }
      iVar11 = iVar11 >> 0x10;
      if ((uVar3 & 0x800) != 0) {
        iVar11 = -iVar11;
      }
      uVar3 = (int)(uVar8 * iVar11) >> 0xc;

	  // approximate trigonometry
      iVar11 = *(int *)(&DAT_800845a0 + (uVar3 & 0x3ff) * 4);

	  if ((uVar3 & 0x400) == 0) {
        iVar11 = iVar11 << 0x10;
      }
      iVar11 = iVar11 >> 0x10;
      if ((uVar3 & 0x800) != 0) {
        iVar11 = -iVar11;
      }
      iVar13 = 0;
      iVar12 = (int)(short)iVar7 * 0xc;
      do {
        iVar4 = (iVar13 << 0x10) >> 0xe;
        if ((int)(short)iVar7 == 0) {
          sVar2 = 0x114;
        }
        else {
          sVar2 = 0xec;
        }
        *(short *)((int)local_48 + iVar4) = *(short *)((int)&DAT_80084294 + iVar4 + iVar12) + sVar2;
        iVar4 = iVar13 << 0x10;
        iVar13 = iVar13 + 1;
        iVar4 = iVar4 >> 0xe;
        *(short *)((int)local_48 + iVar4 + 2) =
             (short)DAT_8008d2d8 + (short)((iVar11 << 5) >> 0xc) + 0x20 +
             *(short *)((int)&DAT_80084296 + iVar4 + iVar12);
      } while (iVar13 * 0x10000 >> 0x10 < 3);

	  // Draw arrows on either side of green bar
      FUN_800453e8(local_48,&DAT_800842ac,

					// pointer to OT mem
					*(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

      iVar7 = iVar7 + 1;
      iVar11 = iVar7 * 0x10000;

    } while (iVar7 * 0x10000 >> 0x10 < 2);

    local_38 = 0xec;
    local_34 = 0x28;
    local_32 = 0x41;
    local_36 = (short)DAT_8008d2d8;

	// RECTMENU_DrawRwdBlueRect
    FUN_80045254(&local_38,&DAT_800842b8,

					// pointer to OT mem
					*(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

    puVar9 = &local_30;
    local_30 = 0xffec;
    local_2c = 0x228;
    local_2a = 0x91;
    local_2e = (short)DAT_8008d2d8 + -0x14;

	// "return", basically
    goto LAB_80038b24;
  }

  // If this is NPC-105

  // we would have "return'd"
  // if we didn't have an NPC-105
  // at this point

  uVar3 = -DAT_8008d2f0;
  iVar7 = 0;
  do {
    uVar5 = uVar8;
    if (iVar7 == 0) {
      uVar5 = uVar3;
    }
    uVar5 = uVar5 - 0x400;

	// approximate trigonometry
    sVar2 = (short)*(int *)(&DAT_800845a0 + (uVar5 & 0x3ff) * 4);
    iVar7 = *(int *)(&DAT_800845a0 + (uVar5 & 0x3ff) * 4) >> 0x10;

	if ((uVar5 & 0x400) == 0) {
      iVar13 = (int)sVar2;
      if ((uVar5 & 0x800) != 0) {
        iVar12 = -iVar7;
        goto LAB_80038620;
      }
    }
    else {
      iVar12 = (int)sVar2;
      iVar13 = iVar7;
      if ((uVar5 & 0x800) == 0) {
        iVar7 = -iVar12;
      }
      else {
LAB_80038620:
        iVar13 = -iVar13;
        iVar7 = iVar12;
      }
    }

	// CTR_Box_DrawWirePrims
    FUN_80021500(((iVar7 * 400) / 0x5000 + 0x100) * 0x10000 >> 0x10,
                 (int)(((uint)DAT_8008d2dc + (iVar13 * 0x32 >> 0xc)) * 0x10000) >> 0x10,
                 ((iVar7 * 0x118) / 0x5000 + 0x100) * 0x10000 >> 0x10,
                 (int)(((uint)DAT_8008d2dc + (iVar13 * 0x23 >> 0xc)) * 0x10000) >> 0x10,0,0xff,0,

				 // pointer to OT mem
                 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				// pointer to PrimMem struct
				 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74
                );
    iVar11 = iVar11 + 1;
    iVar7 = iVar11 * 0x10000;
  } while (iVar11 * 0x10000 >> 0x10 < 2);

  uVar3 = (int)DAT_8008d970 << 6;

  // approximate trigonometry
  iVar11 = *(int *)(&DAT_800845a0 + (uVar3 & 0x3c0) * 4);

  if ((uVar3 & 0x400) == 0) {
    iVar11 = iVar11 << 0x10;
  }
  iVar11 = iVar11 >> 0x10;
  if ((uVar3 & 0x800) != 0) {
    iVar11 = -iVar11;
  }
  uVar8 = ((int)(iVar11 * uVar8) >> 0xc) - 0x400;
  uVar3 = uVar8 & 0xfff;

  // approximate trigonometry
  iVar11 = *(int *)(&DAT_800845a0 + (uVar8 & 0x3ff) * 4) >> 0x10;
  sVar2 = (short)*(int *)(&DAT_800845a0 + (uVar8 & 0x3ff) * 4);

  if ((uVar8 & 0x400) == 0) {
    iVar13 = (int)sVar2;
    iVar7 = iVar11;
    if ((uVar8 & 0x800) != 0) {
      iVar7 = -iVar11;
      goto LAB_800387c4;
    }
  }
  else {
    iVar7 = (int)sVar2;
    iVar13 = iVar11;
    if ((uVar8 & 0x800) == 0) {
      iVar7 = -iVar7;
    }
    else {
LAB_800387c4:
      iVar13 = -iVar13;
    }
  }
  do {
    iVar11 = 0;
    do {
      iVar12 = iVar11;
      iVar11 = (iVar12 << 0x10) >> 0xe;

	  // Draw NPC-105
      FUN_800379f4((int)(((uint)*(ushort *)((int)&DAT_800842dc + iVar11) +
                         (iVar7 * 200) / 0x5000 + 0x100) * 0x10000) >> 0x10,
                   (int)(((uint)*(ushort *)((int)&DAT_800842de + iVar11) + (uint)DAT_8008d2dc +
                         (iVar13 * 0x19 >> 0xc)) * 0x10000) >> 0x10,10,0x80,uVar3,
                   &DAT_800842d0 + iVar11,

				   // pointer to OT mem
				   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				   // pointer to PrimMem struct
				   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

      iVar11 = iVar12 + 1;
    } while ((iVar12 + 1) * 0x10000 >> 0x10 < 3);
    iVar11 = 0;
  } while ((iVar12 + 2) * 0x10000 >> 0x10 < 3);
  do {
    iVar7 = 0;
    do {
      uVar10 = 0x32;
      if ((short)iVar11 != 0) {
        uVar10 = 0x50;
      }
      uVar8 = uVar3 + iVar7 + iVar11;

	  // approximate trigonometry
      sVar2 = (short)*(int *)(&DAT_800845a0 + (uVar8 & 0x3ff) * 4);
      iVar13 = *(int *)(&DAT_800845a0 + (uVar8 & 0x3ff) * 4) >> 0x10;

	  if ((uVar8 & 0x400) == 0) {
        iVar12 = (int)sVar2;
        if ((uVar8 & 0x800) != 0) {
          iVar4 = -iVar13;
          goto LAB_8003892c;
        }
      }
      else {
        iVar4 = (int)sVar2;
        iVar12 = iVar13;
        if ((uVar8 & 0x800) == 0) {
          iVar13 = -iVar4;
        }
        else {
LAB_8003892c:
          iVar12 = -iVar12;
          iVar13 = iVar4;
        }
      }
      iVar4 = iVar13;
      if (iVar13 < 0) {
        iVar4 = iVar13 + 0x3f;
      }

	  // CTR_Box_DrawWirePrims
      FUN_80021500(((iVar4 >> 6) + 0x100) * 0x10000 >> 0x10,
                   (int)(((uint)DAT_8008d2dc + (iVar12 * 0x28 >> 0xc)) * 0x10000) >> 0x10,
                   ((iVar13 * 0x120) / 0x5000 + 0x100) * 0x10000 >> 0x10,
                   (int)(((uint)DAT_8008d2dc + (iVar12 * 0x24 >> 0xc)) * 0x10000) >> 0x10,uVar10,
                   uVar10,uVar10,

				   // pointer to OT mem
				   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				   // pointer to PrimMem struct
				   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

      iVar7 = iVar7 + 0x400;
      iVar13 = iVar11 + 0xaa;
    } while (iVar7 * 0x10000 >> 0x10 < 0x1000);
    iVar11 = iVar13;
  } while (iVar13 * 0x10000 >> 0x10 < 0x400);
  uVar14 = 0;
  do {
    iVar7 = 0;
    iVar11 = (int)((uint)uVar14 << 0x10) >> 0xe;
    iVar13 = 0;
    do {
      iVar13 = iVar13 >> 0xe;
      uVar8 = (uint)*(ushort *)((int)&DAT_800842ea + iVar11);

	  // Draw NPC-105
      FUN_800379f4((int)((*(ushort *)((int)&DAT_80084300 + iVar13) * uVar8 + 0x100) * 0x10000) >>
                   0x10,(int)(((uint)DAT_8008d2dc + *(ushort *)((int)&DAT_80084302 + iVar13) * uVar8
                              ) * 0x10000) >> 0x10,(int)*(short *)((int)&DAT_800842e8 + iVar11),0x80
                   ,uVar3,&DAT_800842f4 + iVar13,

				   // pointer to OT mem
				   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				   // pointer to PrimMem struct
				   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

      iVar7 = iVar7 + 1;
      iVar13 = iVar7 * 0x10000;
    } while (iVar7 * 0x10000 >> 0x10 < 3);

    uVar14 = uVar14 + 1;
  } while (uVar14 < 3);
  puVar9 = &local_38;
  local_38 = 0xffec;
  local_34 = 0x228;
  local_32 = 0xa0;
  local_36 = DAT_8008d2dc - 0x3c;
LAB_80038b24:

  // Draw 2D Menu rectangle background
  FUN_800457b0(puVar9,4,

		// pointer to OT mem
		*(undefined4 *)(PTR_DAT_8008d2ac + 0x147c));
  return;
}


// MainFreeze_MenuPtrOptions
void FUN_80038b5c(int param_1)

{
  bool bVar1;
  short sVar2;
  short sVar3;
  undefined *puVar4;
  ushort uVar5;
  int iVar6;
  short sVar7;
  char *pcVar8;
  int iVar9;
  ushort uVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  undefined4 local_b8;
  ushort local_b0 [4];
  ushort local_a8 [4];
  undefined2 local_a0 [4];
  short local_98;
  short local_96;
  undefined2 local_94;
  undefined2 local_92;
  short local_90;
  short local_8e;
  short local_8c;
  short local_8a;
  short local_88;
  short local_86;
  undefined2 local_80;
  short local_7e;
  undefined2 local_7c;
  short local_7a;
  int local_78;
  short local_70;
  ushort local_68;
  ushort local_60;

  // number of racing wheels
  ushort local_58;

  // number of analog gamepads
  ushort local_50;

  ushort local_48;
  short local_38;
  int local_30;

  local_70 = 0;

  // zero racing wheels by default
  local_58 = 0;

  // gamepad buffer
  local_48 = (ushort)(PTR_DAT_8008d2b0[0x2d1] == -0x80) << 1;

  local_78 = param_1;

  // MainFreeze_SafeAdvDestroy
  FUN_800399fc();

  iVar12 = 0;

  // zero analog gamepads by default
  local_50 = 0;

  // If you are in the racing wheel configuration
  if (DAT_8008d864 != 0)
  {
	// Racing Wheel Configuration
    FUN_80037da0();
    return;
  }

  // For if you are not in racing wheel configuration
  // Since you did not hit "return", you will continue with the rest of the Options menu

  // loop counter
  iVar13 = 0;

  // if numPlyrCurrGame is not zero
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0') {
    iVar6 = 0;

	// for iVar13 = 0; iVar13 < numPlyrCurrGame; iVar13++
    do
	{
      pcVar8 = *(char **)(PTR_DAT_8008d2b0 + (iVar6 >> 0x10) * 0x50 + 0x20);

	  // If this gamepad is not a racing wheel
      if (
			((pcVar8 == (char *)0x0) || (*pcVar8 != '\0')) ||

			(

				(
					// If this is not NPC-105 gamepad
					pcVar8[1] != 0xE3 &&

					// If this is not madcatz racing wheel
					(pcVar8[1] != '#')
				)
			)
		 )
	  {
        uVar14 = (uint)local_58;

		// increment number of analog gamepads
        local_58 = local_58 + 1;

        *(undefined2 *)((int)local_a8 + ((int)(uVar14 << 0x10) >> 0xf)) = (short)iVar13;
        *(undefined2 *)((int)local_a0 + ((iVar13 << 0x10) >> 0xf)) = 0;
      }

	  // if this is a racing wheel
      else {
        uVar14 = (uint)local_50;

		// increment number of racing wheels
        local_50 = local_50 + 1;

        *(undefined2 *)((int)local_b0 + ((int)(uVar14 << 0x10) >> 0xf)) = (short)iVar13;
        local_a0[iVar6 >> 0x10] = 1;
      }

	  // increment loop counter
      iVar13 = iVar13 + 1;

      iVar6 = iVar13 * 0x10000;
										// numPlyrCurrGame
    } while (iVar13 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
  }

  // 0 for no racing wheels
  // 1 for racing wheels
  uVar5 = 0;

  // if there are any analog gamepads
  if (local_58 != 0)
  {
	// check to see if there are any racing wheels
    uVar5 = (ushort)(local_50 != 0);
  }

						// numPlyrCurrGame
  sVar7 = (4 - uVar5) - (ushort)(byte)PTR_DAT_8008d2ac[0x1ca8];
  uVar5 = sVar7 * 10;

  // if there are no analog gamepads
  if (local_58 == 0) {
    local_60 = 0;
  }

  // if there are analog gamepads
  else {
    local_60 = (local_58 + 1) * 10;
  }

  iVar6 = (int)((uint)uVar5 << 0x10) >> 0x11;
  DAT_80084364 = sVar7 * -10 + 0x77;

  // loop counter
  iVar13 = 0;

  // if there are analog gamepads
  if (0 < (int)(short)local_58)
  {
	// loop counter
    iVar9 = 0;

	// for iVar13 = 0; iVar13 < numAnalog; iVar13++
    do
	{
      *(short *)(&DAT_80084344 + ((iVar9 >> 0x10) + 4) * 4) =
           (short)((uint)iVar9 >> 0x10) * 10 + 0x4f;

	  // increment loop counter
	  iVar13 = iVar13 + 1;

      iVar9 = iVar13 * 0x10000;
    } while (iVar13 * 0x10000 >> 0x10 < (int)(short)local_58);
  }

  // bit shift number of racing wheels
  iVar9 = (uint)local_50 << 0x10;

  // loop counter
  iVar13 = 0;

  // if there are racing wheels
  if (0 < iVar9) {

	// for iVar13 = 0; iVar13 < numWheels; iVar13++
    do
	{
      uVar10 = 0;
      sVar7 = (short)iVar13;

	  // if there are analog gamepads
      if ((int)(short)local_58 != 0) {
        uVar10 = (ushort)(iVar9 != 0);
      }

	  // increment loop counter
      iVar13 = iVar13 + 1;

      *(ushort *)(&DAT_80084344 + ((int)(short)local_58 + (int)sVar7 + 4) * 4) =
           (sVar7 + local_58 + uVar10) * 10 + 0x4f;
      iVar9 = (uint)local_50 << 0x10;

    } while (iVar13 * 0x10000 < iVar9);
  }
  puVar4 = PTR_DAT_8008d2ac;
  uVar10 = *(ushort *)(local_78 + 0x14) & 0xfeff;
  *(ushort *)(local_78 + 0x14) = uVar10;

  // if more than 2 screens
  if (2 < (byte)puVar4[0x1ca8]) {
    *(ushort *)(local_78 + 0x14) = uVar10 | 0x100;
  }

  local_68 = uVar5;

  // If you do not press Up
  if ((DAT_8008d950 & 1) == 0) {

	// If you do not press Down
    if ((DAT_8008d950 & 2) == 0) {

	  // if you prses Left or Right

      switch(*(undefined2 *)(local_78 + 0x1a))
	  {

	  // Do the same for all 3 sliders in Options menu

	  // FX slider
      case 0:

	  // Music slider
      case 1:

	  // Voice
      case 2:

		// Get row highlighted
        iVar13 = (int)*(short *)(local_78 + 0x1a);

		// enable OptionsMenu_TestSound
        FUN_8002b208(iVar13,1);

		// If you dont press Left
        if ((DAT_8008d974 & 4) == 0) {

		  // If you press Right
          if ((DAT_8008d974 & 8) != 0)
		  {
			// Get value of slider
            uVar14 = howl_VolumeGet(iVar13);

			// Add to the slider
            uVar14 = (uVar14 & 0xff) + 4;

			// Set maximum value at 0xff
            if (0xff < uVar14) {
              uVar14 = 0xff;
            }

			// Set the new value to the slider
            howl_VolumeSet(iVar13,uVar14 & 0xff);
          }
        }

		// If you press Left
        else
		{
		  // Get value of slider
          uVar14 = howl_VolumeGet(iVar13);

		  // Subtract from the slider
          uVar14 = (uVar14 & 0xff) - 4;

		  // Set minimum at 0
          if ((int)uVar14 < 0) {
            uVar14 = 0;
          }

		  // Set the new value to the slider
          howl_VolumeSet(iVar13,uVar14 & 0xff);
        }
        break;

	  // Mode toggle
      case 3:

		// disable OptionsMenu_TestSound
        FUN_8002b208(0,0);

		// If you press Cross or Circle
        if ((DAT_8008d950 & 0x50) != 0)
		{
		  // OtherFX_Play
          FUN_80028468(1,1);

		  // get mode, flip value, and set

		  // howl_ModeGet
          uVar14 = FUN_8002b1f0();

		  // howl_ModeSet
          FUN_8002b1fc((uint)((uVar14 & 0xff) == 0));
        }
        break;

      case 4:
      case 5:
      case 6:
      case 7:

	    // disable OptionsMenu_TestSound
        FUN_8002b208(0,0);

		// If you press Cross or Circle
        if ((DAT_8008d950 & 0x50) != 0)
		{
          uVar10 = *(ushort *)(local_78 + 0x1a);

		  // OtherFX_Play
          FUN_80028468(1,1);

		  // row selected - 4, gamepad ID
          iVar13 = (int)(((uint)uVar10 - 4) * 0x10000) >> 0x10;

		  // If the row you've selected is for configuring
		  // an analog gamepad
		  // (row - 4) < numAnalog
          if (iVar13 < (short)local_58) {
            *(uint *)PTR_DAT_8008d2ac =
                 *(uint *)PTR_DAT_8008d2ac ^
                 *(uint *)(&DAT_8008430c + (int)(short)local_a8[iVar13] * 4);
          }

		  // if the row selected is for a racing wheel gamepad
          else
		  {
			// set the racing wheel ID to configure
            DAT_8008d87c = local_b0[iVar13 - (short)local_58];

			// open racing wheel configuration
            DAT_8008d864 = 1;

			// set config page index to the first page
            DAT_8008d898 = 0;
          }
        }
        break;
      case 8:

		// disable OptionsMenu_TestSound
        FUN_8002b208(0,0);

		// If you press Cross or Circle
        if ((DAT_8008d950 & 0x50) != 0)
		{
		  // OtherFX_Play
          FUN_80028468(1,1);

          local_70 = 1;
        }
      }
      goto switchD_80038f90_caseD_9;
    }

	// if you press Down

	// OtherFX_Play
    FUN_80028468(0,1);

	// change which row is selected
    sVar7 = *(short *)(local_78 + 0x1a) + 1;
    *(short *)(local_78 + 0x1a) = sVar7;

	// if you scroll past Exit
    if (8 < (int)sVar7)
	{
	  // go back to the top
      *(undefined2 *)(local_78 + 0x1a) = 0;
      goto switchD_80038f90_caseD_9;
    }

						// number of players + 4
    if ((int)sVar7 < (int)((uint)(byte)PTR_DAT_8008d2ac[0x1ca8] + 4)) goto switchD_80038f90_caseD_9;
  }

  // if you press Up
  else
  {
	// OtherFX_Play
    FUN_80028468(0,1);

	// change which row is selected
    sVar7 = *(short *)(local_78 + 0x1a) + -1;
    *(short *)(local_78 + 0x1a) = sVar7;

	// if row is valid
    if (-1 < sVar7)
	{
	  // if you are on exit row
      if (sVar7 == 7) {

		// go to the last row above "Exit" depending on number of players
        *(short *)(local_78 + 0x1a) = (ushort)(byte)PTR_DAT_8008d2ac[0x1ca8] + 3;
      }
      goto switchD_80038f90_caseD_9;
    }
  }
  *(undefined2 *)(local_78 + 0x1a) = 8;
switchD_80038f90_caseD_9:
  uVar14 = 0;
  iVar13 = 0;
  do
  {
	// DecalFont_GetLineWidth
    iVar13 = FUN_800224d0(*(undefined4 *)
                           ((int)*(short *)((int)&DAT_80084328 + (iVar13 >> 0xf)) * 4 + DAT_8008d878
                           ),2);

    if (iVar12 << 0x10 < iVar13 << 0x10) {
      iVar12 = iVar13;
    }
    uVar14 = uVar14 + 1;
    iVar13 = uVar14 * 0x10000;
  } while ((uVar14 & 0xffff) < 3);

  // loop counter
  iVar9 = 0;

  local_b8 = 0xffff8000;

  // DAT_8008d878 + 0x510
  // OPTIONS
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x510),0x100,(iVar6 + 0x1a) * 0x10000 >> 0x10,1,
               0xffff8000);

  iVar13 = 0x17c - (iVar12 + 0x1e);
  local_38 = (short)iVar13;
  local_30 = (iVar13 * 0x10000 >> 0x10) + -5;

  // used to get strings
  iVar13 = 0;

  // for iVar9 = 0; iVar9 < 3; iVar9++
  do {
    iVar13 = iVar13 >> 0x10;
    uVar14 = howl_VolumeGet(iVar13);
    iVar15 = (uVar14 & 0xff) * local_30;
    iVar15._1_2_ = (short)((uint)iVar15 >> 8);
    sVar3 = (short)uVar5 >> 1;
    sVar7 = sVar3 + (short)(iVar13 * 10);
    if (iVar15 < 0) {
      iVar15._1_2_ = (short)((uint)(iVar15 + 0xff) >> 8);
    }
    sVar2 = (short)(iVar12 + 0x1e);
    iVar15._1_2_ = sVar2 + iVar15._1_2_ + 0x38;
    local_98 = iVar15._1_2_ + 1;
    local_94 = 3;
    local_92 = 10;
    local_96 = sVar7 + 0x30;

	// CTR_Box_DrawSolidBox
    FUN_80021894(&local_98,&DAT_8008433c,
				*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),

				// pointer to PrimMem struct
				 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
				 local_b8);

    local_96 = sVar7 + 0x2f;
    local_94 = 5;
    local_92 = 0xc;
    local_98 = iVar15._1_2_;

	// CTR_Box_DrawSolidBox
    FUN_80021894(&local_98,&DAT_80084340,

					*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

    local_90 = sVar2 + 0x38;
    local_8e = sVar7 + 0x3a;
    local_8c = sVar2 + local_38 + 0x38;
    local_8a = sVar7 + 0x30;
    local_88 = local_8c;
    local_86 = local_8e;

	// Draw sliders in Options
    FUN_800453e8(&local_90,&DAT_80084330,

					*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
    local_b8 = 0;

	// iVar13 = 0: FX:
	// iVar13 = 1: MUSIC:
	// iVar13 = 2: VOICE:
    FUN_80022878(*(undefined4 *)((int)(short)(&DAT_80084328)[iVar13] * 4 + DAT_8008d878),0x4c,
                 (iVar13 * 10 + iVar6 + 0x32) * 0x10000 >> 0x10,2);

	// increment loop counter
    iVar9 = iVar9 + 1;

	// increment pointer
    iVar13 = iVar9 * 0x10000;

  } while (iVar9 * 0x10000 >> 0x10 < 3);

  // DAT_8008d878 + 0x530
  // MODE:
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x530),0x4c,(iVar6 + 0x50) * 0x10000 >> 0x10,2,0);

  // howl_ModeGet
  uVar14 = FUN_8002b1f0();

  // if mode is zero
  if ((uVar14 & 0xff) == 0)
  {
    // DAT_8008d878 + 0x534
	// MONO
	puVar11 = (undefined4 *)(DAT_8008d878 + 0x534);
  }

  // if mode is not zero
  else
  {
	// DAT_8008d878 + 0x538
	// STEREO
	puVar11 = (undefined4 *)(DAT_8008d878 + 0x538);
  }

  // Draw "MONO" or "STEREO"
  FUN_80022878(*puVar11,0x1b4,(iVar6 + 0x50) * 0x10000 >> 0x10,2,0x4004);

  uVar5 = local_58;
  if (local_58 != 0)
  {
	// DAT_8008d878 + 0x528
	// DUAL SHOCK:
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x528),0x4c,(iVar6 + 0x5a) * 0x10000 >> 0x10,2,0);

	// Controller 1A
	// DecalFont_GetLineWidth
	iVar13 = FUN_800224d0(*(undefined4 *)((int)DAT_80084320 * 4 + DAT_8008d878),2);

	// DAT_8008d878 + 0x518
	// VIBRATE OFF
	// DecalFont_GetLineWidth
	iVar9 = FUN_800224d0(*(undefined4 *)(DAT_8008d878 + 0x518),2);

	// DAT_8008d878 + 0x514
	// VIBRATE ON
	// DecalFont_GetLineWidth
	iVar12 = FUN_800224d0(*(undefined4 *)(DAT_8008d878 + 0x514),2);

	iVar15 = 0;
    if (iVar12 << 0x10 < iVar9 << 0x10) {
      iVar12 = iVar9;
    }
    iVar12 = (iVar13 + iVar12 + 10) * 0x10000;
    iVar12 = 0x100 - ((iVar12 >> 0x10) - (iVar12 >> 0x1f) >> 1);
    if (0 < (short)uVar5) {
      iVar9 = 0;
      do {
        bVar1 = false;
        uVar5 = *(ushort *)((int)local_a8 + (iVar9 >> 0xf));
        uVar14 = (uint)uVar5;

        if (
				(*(char **)(PTR_DAT_8008d2b0 + (int)(short)uVar5 * 0x50 + 0x20) == (char *)0x0) ||
				(**(char **)(PTR_DAT_8008d2b0 + (int)(short)uVar5 * 0x50 + 0x20) != '\0')
		   ) {
          bVar1 = true;
        }
        if (bVar1) {
          local_b8 = 0x17;
        }
        else {
          local_b8 = 0;
        }

		// might be printing string for
		// "Controller 1", "Controller 2", 1A 1B 1C 1D, etc
        FUN_80022878(*(undefined4 *)
                      ((int)*(short *)(&DAT_8008431c + ((int)((uVar14 + local_48) * 0x10000) >> 0xf)
                                      ) * 4 + DAT_8008d878),iVar12 * 0x10000 >> 0x10,
                     ((int)(short)iVar15 * 10 + iVar6 + 100) * 0x10000 >> 0x10,2,local_b8);

		// if vibration is enabled,
		// gGT->gameMode1 & 0x0000X000
		if ((*(uint *)PTR_DAT_8008d2ac & *(uint *)(&DAT_8008430c + ((int)(uVar14 << 0x10) >> 0xe)))

			// == 0 means enabled,
			// == 1 means disabled (seriously, not a mistake)
            == 0)
		{
		  // DAT_8008d878 + 0x514
		  // VIBRATE ON
          puVar11 = (undefined4 *)(DAT_8008d878 + 0x514);
        }

		else
		{
		  // DAT_8008d878 + 0x518
		  // VIBRATE OFF
          puVar11 = (undefined4 *)(DAT_8008d878 + 0x518);
        }

		local_b8 = 0x17;

        if (
				(!bVar1) &&
				(
					// color red
					local_b8 = 3,

					// if vibration is enabled
					// == 0 means enabled,
					// == 1 means disabled (seriously, not a mistake)
					(*(uint *)PTR_DAT_8008d2ac & *(uint *)(&DAT_8008430c +
					((int)(uVar14 << 0x10) >> 0xe))) == 0))
		{
		  // color = white
          local_b8 = 4;
        }

		// Draw string for vibrate on and off
        FUN_80022878(*puVar11,(iVar12 + iVar13 + 10) * 0x10000 >> 0x10,
                     ((int)(short)iVar15 * 10 + iVar6 + 100) * 0x10000 >> 0x10,2,local_b8);

		iVar15 = iVar15 + 1;
        iVar9 = iVar15 * 0x10000;
      } while (iVar15 * 0x10000 < (int)((uint)local_58 << 0x10));
    }
  }
  iVar12 = (int)(short)local_50;
  if (iVar12 != 0) {
    iVar13 = 0;

	// DAT_8008d878 + 0x540
	// CONFIGURE ANALOG:
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x540),0x4c,
                 (int)(((uint)local_60 + iVar6 + 0x5a) * 0x10000) >> 0x10,2,0);

    if (0 < iVar12) {
      do {
        FUN_80022878(*(undefined4 *)
                      ((int)*(short *)(&DAT_8008431c +
                                      ((int)(((uint)local_b0[(int)(short)iVar13] + (uint)local_48) *
                                            0x10000) >> 0xf)) * 4 + DAT_8008d878),0x100,
                     (int)((iVar6 + (uint)local_60 + (int)(short)iVar13 * 10 + 100) * 0x10000) >>
                     0x10,2,0xffff8000);
        iVar13 = iVar13 + 1;
      } while (iVar13 * 0x10000 >> 0x10 < iVar12);
    }
  }

  // DAT_8008d878 + 0x52c
  // EXIT
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x52c),0x4c,
               (int)(((iVar6 + 0x8c) - (uint)local_68) * 0x10000) >> 0x10,2,0);

  local_80 = 0x4a;
  local_7c = 0x16c;
  local_7e = *(short *)(&DAT_80084344 + (int)*(short *)(local_78 + 0x1a) * 4) + sVar3 + 0x14;
  local_7a = *(short *)(&DAT_80084346 + (int)*(short *)(local_78 + 0x1a) * 4);

  // CTR_Box_DrawClearBox
  FUN_8002177c(&local_80,&DAT_8008d94c,1,

				*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),

				// pointer to PrimMem struct
				*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

  local_80 = 0x42;
  local_7e = sVar3 + 0x2b;
  local_7c = 0x17c;
  local_7a = 2;

  // RECTMENU_DrawOuterRect_Edge (transparent)
  FUN_80044f90(&local_80,&DAT_8008d438,0x20,
               *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));

  local_80 = 0x38;
  local_7c = 400;
  local_7a = 0x87 - local_68;
  local_7e = sVar3 + 0x14;

  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_80,4,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));

  if (
		(local_70 != 0) ||

		// If you press Triangle, Square, or Start
		((DAT_8008d950 & 0x41020) != 0)
	 )
  {
	// OtherFX_Play
    FUN_80028468(1,1);

	// disable OptionsMenu_TestSound
    FUN_8002b208(0,0);

	// clear gamepad input (for menus)
    FUN_80046404();

	// set desired Menu to pause Menu
    DAT_8008d924 = FUN_80039dcc();
  }
  return;
}


// MenuFuncPtr_Quit
void FUN_80039908(int param_1)

{
  short sVar1;
  undefined *puVar2;
  ushort uVar3;

  puVar2 = PTR_DAT_8008d2ac;
  if (*(short *)(param_1 + 0x1e) == 0) {
    sVar1 = *(short *)(param_1 + 0x1a);
    if (sVar1 == 0)
	{
	  // Erase ghost of previous race from RAM
      FUN_80028410();

	  // when loading is done
	  // add bit for "in menu"
      DAT_8008d100 = DAT_8008d100 | 0x2000;

	  // go to main menu
      DAT_8008d97c = 0;

	  // when loading is done
	  // remove bit for "In Adventure Arena"
      DAT_8008d104 = DAT_8008d104 | 0x100000;

	  // Unpause game
      *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xfffffffe;

	  // Level ID for main menu (39)
      FUN_8003cfc0(0x27);
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

	  // Change active Menu to pause Menu
      DAT_8008d924 = FUN_80039dcc();
    }
  }
  else
  {
    uVar3 = *(ushort *)(param_1 + 0x14) & 0xfeff;
    *(ushort *)(param_1 + 0x14) = uVar3;

	// if more than 2 screens
	if (2 < (byte)puVar2[0x1ca8])
	{
      *(ushort *)(param_1 + 0x14) = uVar3 | 0x100;
    }

	// MainFreeze_SafeAdvDestroy
	FUN_800399fc();
  }
  return;
}


// MainFreeze_SafeAdvDestroy
void FUN_800399fc(void)

{
  int iVar1;

  if (
		// If you're in Adventure Arena
		((*(uint *)PTR_DAT_8008d2ac & 0x100000) != 0) &&

		(
			// If 232 dll is loaded
			iVar1 = FUN_80034920(),
			iVar1 != 0
		)
	)
  {
	// AH_Pause_Destroy (and destroy thread)
    FUN_800b1ef8();
  }
  return;
}


// MainFreeze_MenuPtrDefault
void FUN_80039a44(int param_1)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  ushort *puVar4;
  uint uVar5;
  ushort uVar6;
  uint uVar7;

  puVar2 = PTR_DAT_8008d2ac;

  // if you have not waited 5 frames
  // since the game was paused
  if (PTR_DAT_8008d2ac[0x1d38] != '\0') {

	// quit
	return;
  }

  // assume 5 frames have passed since paused

  if (*(short *)(param_1 + 0x1e) != 0) {
    uVar6 = *(ushort *)(param_1 + 0x14) & 0xfeff;
    *(ushort *)(param_1 + 0x14) = uVar6;

	// if more than 2 screens
	if (2 < (byte)puVar2[0x1ca8])
	{
      *(ushort *)(param_1 + 0x14) = uVar6 | 0x100;
    }

	// If you're not in Adventure Arena
    if ((*(uint *)PTR_DAT_8008d2ac & 0x100000) == 0) {
      return;
    }

    if ((*(uint *)(param_1 + 8) & 0x1000) != 0) {
      return;
    }

	// Check if 232 dll is loaded
    iVar3 = FUN_80034920();

	// quit if it is not
    if (iVar3 == 0) {
      return;
    }

	// AH_Pause_Update
    FUN_800b3144();

    return;
  }
  if ((int)*(short *)(param_1 + 0x1a) < 0) {
    return;
  }
  
  // get string from row selected
  puVar4 = (ushort *)((int)*(short *)(param_1 + 0x1a) * 6 + *(int *)(param_1 + 0xc));
  uVar6 = *puVar4;
  uVar7 = (uint)*puVar4;

  // String 0xE: Options
  if (uVar6 == 0xe)
  {
	// Set desired Menu to Options
    DAT_8008d924 = &DAT_80084190;

    DAT_800841aa = 8;
    return;
  }

  // AkuAku Hints, or UkaUka Hints
  if ((uVar7 - 0xb & 0xffff) < 2) 
  {
	// Hints menu
    DAT_8008d924 = &DAT_800b518c;
    return;
  }

  // String 0x3: Quit
  if (uVar6 == 3)
  {
	// Set active Menu to Quit
    DAT_8008d924 = &DAT_800841d0;
    DAT_800841ea = 1;
    return;
  }

  // must wait 5 frames until next pause
  PTR_DAT_8008d2ac[0x1d39] = 5;

  // make Menu invisible
  FUN_800469c8(param_1);

  // MainFreeze_SafeAdvDestroy
  FUN_800399fc();

  puVar2 = PTR_DAT_8008d2ac;

  // get any flags that you already want
  // removed after loading finishes
  uVar1 = DAT_8008d104;

  // careful, it's String MINUS one
  switch((int)((uVar7 - 1) * 0x10000) >> 0x10) 
  {
 
  // String 0x1: "Restart"
  case 0:
  
  // String 0x4: "Retry"
  case 3:
  
	// Unpause game
    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xfffffffe;
    i
	// RaceFlag_IsFullyOffScreen
	Var3 = FUN_80043f28();
    if (iVar3 == 1)
	{
	  // checkered flag, begin transition on-screen
      FUN_80043fb0(1);
    }

	// if you are not showing a ghost during a race
    if (DAT_8008d958 == 0) 
	{
	  // restart race
      DAT_8008d0f8 = -5;
      return;
    }

	// If the ghost playing buffer is nullptr
    if (DAT_8008d754 == 0) 
	{
	  // restart race
      DAT_8008d0f8 = -5;
      return;
    }

	// At this point, we are certain there is a ghost
	// buffer so you must be in time trial mode

	// Make P2 the character that is saved in the
	// header of the ghost that you will see in the race
    DAT_80086e86 = *(undefined2 *)(DAT_8008d754 + 6);

	// restart race
	DAT_8008d0f8 = -5;
    return;
	
  // String 0x2: "Resume"
  case 1:

    // ElimBG_Deactivate
    FUN_80024c08(PTR_DAT_8008d2ac);

	// Unpause game
    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xfffffffe;

	// MainFrame_TogglePauseAudio(unpause)
    FUN_80034b48(0);

	// OtherFX_Play
    FUN_80028468(1,1);
    return;
  default:
    goto switchD_80039bcc_caseD_2;

  // String 0x5: "Change Character"
  case 4:

	// Erase ghost of previous race from RAM
    FUN_80028410();

	// levelID of main menu
    iVar3 = 0x27;

	// Return to character selection
    DAT_8008d97c = 1;

	// when loading is done
	// add bit for "in menu"
    DAT_8008d100 = DAT_8008d100 | 0x2000;

	// Unpause game
    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xfffffffe;
    break;
  
  // String 0x6: "Change Level"
  case 5:

	// Erase ghost of previous race from RAM
	FUN_80028410();

	// level ID of main menu
	iVar3 = 0x27;

	// return to track selection
    DAT_8008d97c = 2;

	// when loading is done
	// add bit for "in menu"
    DAT_8008d100 = DAT_8008d100 | 0x2000;

	// Unpause game
    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xfffffffe;
    break;
	
  // String 0xA: "Change Setup"
  case 9:

	// levelID of main menu
    iVar3 = 0x27;

	// return to battle setup
    DAT_8008d97c = 3;

	// when loading is done
	// add bit for "in menu"
    DAT_8008d100 = DAT_8008d100 | 0x2000;

	// Unpause game
    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xfffffffe;
    break;

  // String 0xD: "Exit To Map"
  case 0xc:

	// when loading is done
	// add this bit for In Adventure Arena
    DAT_8008d100 = DAT_8008d100 | 0x100000;

	// when loading is done
	// remove bits for Relic Race or Crystal Challenge
    DAT_8008d104 = DAT_8008d104 | 0xc000000;

	// when loading is done
	// remove bit for CTR Token Challenge
    DAT_8008d10c = DAT_8008d10c | 8;

	// Unpause game
	uVar7 = *(uint *)PTR_DAT_8008d2ac;  // get value
	uVar5 = uVar7 & 0xfffffffe;			// remove pause
    *(uint *)PTR_DAT_8008d2ac = uVar5;  // set value

	// If you are not in Adventure cup
    if ((uVar7 & 0x10000000) == 0) {

	  // 0x80000000
	  // If you're in Boss Mode
      if ((int)uVar5 < 0)
	  {
		// when loading is done remove bit for
		// Boss Race, relic, and crystal challenge
        DAT_8008d104 = uVar1 | 0x8c000000;

		// When loading is done
		// add bit to spawn driver near boss door
        DAT_8008d108 = DAT_8008d108 | 1;
      }

	  // set iVar3 to level you were in previously
      iVar3 = (int)*(short *)(puVar2 + 0x1eb4);
    }

	// If you're in Adventure Cup
    else
	{
	  // Level ID of Gemstone Valley
      iVar3 = 0x19;

	  // when loading is done remove bits for
	  // Adventure Cup, relic, and crystal challenge
      DAT_8008d104 = uVar1 | 0x1c000000;

	  // Level ID
      *(int *)(puVar2 + 0x1a10) = *(int *)(puVar2 + 0x1e58) + 100;
    }
  }

  // load level ID
  FUN_8003cfc0(iVar3);
switchD_80039bcc_caseD_2:
  return;
}


// Get_RECTMENU_Pause
undefined * FUN_80039dcc(void)

{
  undefined *puVar1;
  uint uVar2;

  uVar2 = *(uint *)PTR_DAT_8008d2ac;

  // If you're not in Adventure Arena
  if ((uVar2 & 0x100000) == 0) {

    // If you're not in Adventure Mode
    if ((uVar2 & 0x80000) == 0) {

	  // if you are not in Battle
      if ((uVar2 & 0x20) == 0) {

		// If you are not in Arcade or VS cup
        if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) == 0)
		{
		  // Single Race Pause
          puVar1 = &DAT_80084510;
        }

		// if you are in a cup
        else
		{
		  // Cup Pause
          puVar1 = &DAT_800844b8;
        }
      }

	  // if you are in Battle
      else
	  {
		// Battle Pause
        puVar1 = &DAT_80084474;
      }
    }

	// if you're in Adventure Mode
	else
	{
	  // if you're in a race
      if ((uVar2 & 0x10000000) == 0)
	  {
		// adventure race pause
        puVar1 = &DAT_800843d4;
      }

	  // if you're in a cup
      else
	  {
		// adventure cup pause
        puVar1 = &DAT_80084418;
      }
    }
  }

  // if you're in Adventure Arena
  else
  {
	// VehPickupItem_MaskBoolGoodGuy
    uVar2 = FUN_80064be4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x24ec));

	// if you use uka

	// Set string to Uka Uka Hints
    DAT_8008436e = 0xc;

	// if you use aku
    if ((uVar2 & 0xffff) != 0)
	{
	  // Set string to Aku Aku Hints
      DAT_8008436e = 0xb;
    }

	// Adventure Arena Pause
    puVar1 = &DAT_80084388;
  }
  return puVar1;
}


// MainFreeze_IfPressStart
void FUN_80039e98(void)

{
  int iVar1;
  uint uVar2;

  // RaceFlag_IsFullyOnScreen
  iVar1 = FUN_80043f1c();

  if (
		(
			(
				(
					(
						// if flag is not fully on screen
						(iVar1 == 0) &&

						// if you are not drawing loading screen (after fully off screen)
						((*(uint *)(PTR_DAT_8008d2ac + 0x256c) & 0x1000) == 0)
					) &&

					// if aku is not giving a hint
					(DAT_8008d874 == 0)
				) &&

				(
					(
						DAT_8008d908 == 0 &&
						(
							uVar2 = *(uint *)PTR_DAT_8008d2ac,

							// if not in time trial, and if not paused
							(uVar2 & 0x20000f) == 0
						)
					)
				)
			) &&

			(
				(
									// Level ID != 39
									// Not in Main Menu
					*(int *)(PTR_DAT_8008d2ac + 0x1a10) != 0x27 &&
					(
						(
							(uVar2 & 0x20000000) == 0 &&

							// If you're not in Demo Mode
							(PTR_DAT_8008d2ac[0x1d32] == '\0')
						)
					)
				)
			)
		) &&


		(
			(
							// Level ID
				1 < *(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x2aU &&
				(
					(
						// If game is not loading
						DAT_8008d0a4 == 0 &&

						// if in a state where you're seeing the boss key open an adv door,
						// or some other kind of cutscene where you can't move
						((*(uint *)(PTR_DAT_8008d2ac + 8) & 4) == 0)
					)
				)
			)
		)
	 )
  {
	// pause the game
    *(uint *)PTR_DAT_8008d2ac = uVar2 | 1;

	// set desired Menu to pause Menu
    iVar1 = FUN_80039dcc();

	// set row selected to the top row
    *(undefined2 *)(iVar1 + 0x1a) = 0;

	// make menu visible
    FUN_80046990();

	// pause audio
    FUN_80034b48(1);

	// OtherFX_Play to pause
    FUN_80028468(1,1);

	// ElimBG_Activate
    FUN_8002481c(PTR_DAT_8008d2ac);
  }
  return;
}


// MainGameEnd_SoloRaceGetReward
void FUN_80039fa8(int param_1)

{
  char *pcVar1;
  uint *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;

  puVar3 = PTR_DAT_8008d2ac;

  // pointer to first Player thread, -> object
  iVar10 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x1b2c) + 0x30);

  // no new high score
  PTR_DAT_8008d2ac[0x1d49] = 0xff;

  puVar4 = PTR_DAT_8008d2ac;
  *(uint *)(puVar3 + 0x1d44) = *(uint *)(puVar3 + 0x1d44) & 0x7bffffff;
  puVar3 = PTR_DAT_8008d2ac;

  // subtract zero seconds from final time
  iVar9 = 0;

  // if the number of time crates you collected is equal to num crates in LEV
  if (((int)*(char *)(*(int *)(puVar4 + 0x24ec) + 0x32) == *(int *)(puVar4 + 0x1e2c)) &&
     (param_1 != 0))
  {
	// subtract 10 seconds from time
    iVar9 = 0x2580;
  }

  // loop counter
  iVar5 = 0;
  iVar7 = 0;

  // loop through 5 high scores
  do {
    iVar6 = iVar7 + 1;

    if (
			// player race time, is less than...
			*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x514) - iVar9 <

			// race time in slot[iVar5] of high scores
			(int)DAT_8008d738[(iVar5 >> 0x10) * 6 + 6]
		)
	{
      puVar2 = (uint *)(PTR_DAT_8008d2ac + 0x1d44);

	  // save high score index, as new high score
	  PTR_DAT_8008d2ac[0x1d49] = (char)iVar7;

      *(uint *)(puVar3 + 0x1d44) = *puVar2 | 0x88000000;
      break;
    }
    iVar5 = iVar6 * 0x10000;
    iVar7 = iVar6;
  } while (iVar6 * 0x10000 >> 0x10 < 5);

  puVar3 = PTR_DAT_8008d2ac;

  // number of laps
  pcVar1 = PTR_DAT_8008d2ac + 0x1d33;

  iVar9 = 0;

  // set best lap time
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d3c) = *DAT_8008d738;

  // if numLaps > 0
  if ('\0' < *pcVar1) {
    iVar7 = 0;

	// loop through number of laps
    do
	{
	  // if number of laps is lower than best lap
      if (*(int *)(puVar3 + (iVar7 >> 0x10) * 4 + 0x1d14) < *(int *)(puVar3 + 0x1d3c))
	  {
		// set new lowest lap to this lap time
        *(int *)(puVar3 + 0x1d3c) = *(int *)(puVar3 + (iVar7 >> 0x10) * 4 + 0x1d14);

		// set lap ID (0,1,2) to flash, because it is new best lap
		*(int *)(puVar3 + 0x1d40) = iVar7 >> 0x10;

		// start drawing OSK, and... ?
        *(uint *)(puVar3 + 0x1d44) = *(uint *)(puVar3 + 0x1d44) | 0x8c000000;
      }

	  // increase lap index
	  iVar9 = iVar9 + 1;

	  iVar7 = iVar9 * 0x10000;

    } while (iVar9 * 0x10000 >> 0x10 < (int)(char)puVar3[0x1d33]);
  }
  puVar3 = PTR_DAT_8008d2ac;

  // If you're not in Time Trial
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20000) == 0) {
    return;
  }

  // quit function is this bit is not active
  // This bit becomes active as soon as you finish a race
  if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 4) != 0) {
    return;
  }

  // This next line seems pointless

  // Activate bit, even though it had to be active, because we
  // wouldn't get to this line if it weren't active
  *(uint *)(PTR_DAT_8008d2ac + 0x1d44) = *(uint *)(PTR_DAT_8008d2ac + 0x1d44) | 4;

  // Level ID * 0x124
  iVar9 = *(int *)(puVar3 + 0x1a10) * 0x124;

  iVar7 = ((int)((uint)DAT_8008453c << 0x10) >> 0x15) * 4 + iVar9;

  // check timeTrialFlags, see if n.tropy has NOT been beaten
  if ((*(uint *)(&DAT_8008e814 + iVar7) >> (DAT_8008453c & 0x1f) & 1) == 0)
  {
	// if timeTrialFlags show N Tropy is not open
    if ((*(uint *)(&DAT_8008e814 + iVar9) & 1) == 0)
	{
	  // if time required to win event was less than the amount of time you took to finish,
	  // meaning if you lost the event, then you did not open N Tropy
      if (*(int *)(&DAT_80083a8c + *(int *)(puVar3 + 0x1a10) * 0x18) <= *(int *)(iVar10 + 0x514))
      goto LAB_8003a27c;

	  // write to timeTrialFlags,
	  // you just opened N Tropy
	  *(uint *)(&DAT_8008e814 + iVar9) =
	  *(uint *)(&DAT_8008e814 + iVar9) | 1;

	  // | 0x8000
	  uVar8 = *(uint *)(puVar3 + 0x1d44) | 0x8008000;
    }

	// if N Tropy is open
    else
	{
	  // if time required to win event was less than the amount of time you took to finish,
	  // meaning if you lost the event, then you did not beat N Tropy, nor open N Oxide
      if (*(int *)(puVar3 + 0x1d78) <= *(int *)(iVar10 + 0x514)) goto LAB_8003a27c;

	  // write to timeTrialFlags,
	  // you just beat N Tropy and opened N Oxide
      *(uint *)(&DAT_8008e814 + iVar7) =
      *(uint *)(&DAT_8008e814 + iVar7)
		| 1 << (DAT_8008453c & 0x1f);

	  // + 0x1d44) | 0x18000000
	  uVar8 = *(uint *)(puVar3 + 0x1d44) | DAT_80084548;
    }
  }

  // if N Tropy has been beaten,
  // and oxide is open
  else
  {
	// if time required to win event was less than the amount of time you took to finish,
	// meaning if you lost the event, then you did not beat N Oxide
    if (*(int *)(puVar3 + 0x1d78) <= *(int *)(iVar10 + 0x514)) goto LAB_8003a27c;

    iVar9 = ((int)((uint)DAT_80084540 << 0x10) >> 0x15) * 4 + iVar9;

	// write to timeTrialFlags,
	// you just beat N Oxide
	*(uint *)(&DAT_8008e814 + iVar9) =
    *(uint *)(&DAT_8008e814 + iVar9)
		| 1 << ((uint)DAT_80084540 & 0x1f);

	// + 0x1d44) | 0x08800000
    uVar8 = *(uint *)(puVar3 + 0x1d44) | DAT_80084544;
  }
  *(uint *)(puVar3 + 0x1d44) = uVar8;
LAB_8003a27c:

  // GAMEPROG_CheckGhostsBeaten(oxide)
  uVar8 = FUN_80026ae4(2);

  // If Oxide was beaten on all tracks
  if ((uVar8 & 0xffff) != 0)
  {
	// Unlock Scrapbook
    DAT_8008e6f0 = DAT_8008e6f0 | 0x10;
  }
  return;
}


// MainGameEnd_SoloRaceSaveHighScore
void FUN_8003a2b4(void)

{
  undefined2 uVar1;
  undefined *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  uchar *puVar6;
  undefined4 *puVar7;
  int iVar8;

  // player structure
  iVar8 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);

  // MainGameEnd_SoloRaceGetReward
  FUN_80039fa8(0);

  puVar2 = PTR_DAT_8008d2ac;
  uVar3 = *(uint *)(PTR_DAT_8008d2ac + 0x1d44);
  if ((uVar3 & 0x10000) == 0) {
    *(uint *)(PTR_DAT_8008d2ac + 0x1d44) = uVar3 | 0x10000;
    puVar7 = DAT_8008d738;

	// if there is a new best lap
    if ((uVar3 & 0x4000000) != 0)
	{
	  // save new best lap time to high score
      *DAT_8008d738 = *(undefined4 *)(puVar2 + 0x1d3c);

	  // Player / AI structure + 0x4a shows driver index (0-7)
      uVar1 = (&DAT_80086e84)[*(byte *)(iVar8 + 0x4a)];

	  // set first byte of high score name to nullptr (waste of time?)
	  *(undefined *)(puVar7 + 1) = 0;
      puVar4 = DAT_8008d738 + 1;

	  // prevNameEntered
      puVar6 = PTR_DAT_8008d2ac + 0x1d54;

	  // save characterID in high score
      *(undefined2 *)((int)puVar7 + 0x16) = uVar1;

	  // copy name
	  memmove((uchar *)puVar4,puVar6,0x11);
    }

	// index of new high score
    iVar5 = (int)(char)PTR_DAT_8008d2ac[0x1d49];

	// if there is a new high score
    if (-1 < iVar5)
	{
	  // pointer to saved time in high score
      puVar7 = DAT_8008d738 + iVar5 * 6 + 6;

	  // if this new high score, is not
	  // high score #5 on the list
      if (iVar5 < 4)
	  {
		// move all high scores, that come after this new high score,
		// down by one slot on the list of all times
        memmove((uchar *)(puVar7 + 6),(uchar *)puVar7,(4 - iVar5) * 0x18);
      }

	  // save race time in the high score
      *puVar7 = *(undefined4 *)(iVar8 + 0x514);

	  // Player / AI structure + 0x4a shows driver index (0-7)
      uVar1 = (&DAT_80086e84)[*(byte *)(iVar8 + 0x4a)];

	  // set first byte of high score name to nullptr (waste of time?)
      *(undefined *)(puVar7 + 1) = 0;

	  // prevNameEntered
      puVar6 = PTR_DAT_8008d2ac + 0x1d54;

	  // save characterID in high score
      *(undefined2 *)((int)puVar7 + 0x16) = uVar1;

	  // copy name
	  memmove((uchar *)(puVar7 + 1),puVar6,0x11);
    }
  }
  return;
}


// MainGameEnd_Initialize
void FUN_8003a3fc(void)

{
  byte *pbVar1;
  int *piVar2;
  int iVar3;
  undefined *puVar4;
  short sVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  uint uVar9;
  undefined *puVar10;
  int iVar11;
  int iVar12;
  undefined *puVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  int iVar17;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;

  // loop counter
  iVar17 = 0;

  // If you're not in End-Of-Race menu,
  // then enable End-Of-Race menu
  if ((*(uint *)PTR_DAT_8008d2ac & 0x200000) == 0)
  {
	// pointer to player structure (P1)
    local_30 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);

	// for iVar17 = 0; iVar17 < 8; iVar17++
    do
	{
		// pointer to address of all 8 player structures,
		// if each structure is not nullptr
      if (*(int *)(PTR_DAT_8008d2ac + iVar17 * 4 + 0x24ec) != 0)
	  {
		// spawn player in position of next race, depending on
		// rank in current race (1st place, 2nd place, etc)
        (&DAT_8008d69c)[iVar17] =
             *(undefined *)(*(int *)(PTR_DAT_8008d2ac + iVar17 * 4 + 0x24ec) + 0x482);
      }

	  // increment loop counter
      iVar17 = iVar17 + 1;

    } while (iVar17 < 8);
    PTR_DAT_8008d2ac[0x1d49] = 0xff;

	// If you're drawing Weapon Roulette (randomizing)
    if ((*(uint *)PTR_DAT_8008d2ac & 0x800000) != 0)
	{
	  // OtherFX_Stop2
	  // stop weapon shuffle sound
      FUN_80028844(0x5d);

	  // disable randomizing effect in HUD
      *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xff7fffff;
    }

	uVar9 = *(uint *)PTR_DAT_8008d2ac;

	// Trophy, CTR Challenge, Crystal, Boss

	// If not in Adventure cup and not in Relic,
	// but you are in Adventure Mode
    if ((uVar9 & 0x14080000) == 0x80000) {

      // If player is in 1st place
      if (*(short *)(local_30 + 0x482) == 0)
	  {
		// If this is boss race
        if ((int)uVar9 < 0) {
          (&DAT_8008fbeb)[*(int *)(PTR_DAT_8008d2ac + 0x1eb8)] = 0;
        }

		// if this is not boss race
        else
		{
							// Level ID
          (&DAT_8008fbd4)[*(int *)(PTR_DAT_8008d2ac + 0x1a10)] = 0;
        }
      }

	  // if player is not in 1st place
	  else {

		// if this is boss race
        if ((int)uVar9 < 0) {
          iVar17 = *(int *)(PTR_DAT_8008d2ac + 0x1eb8) + 0x17;
        }

		// if this is not boss race
        else
		{
							// Level ID
          iVar17 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);
        }

		// if number of times lost is less than 10
        if ((char)(&DAT_8008fbd4)[iVar17] < '\n')
		{
		  // increment number of times lost
          (&DAT_8008fbd4)[iVar17] = (&DAT_8008fbd4)[iVar17] + '\x01';
        }
      }
    }
    puVar13 = PTR_DAT_8008d2ac;

	// Enable End-Of-Race menu
    uVar9 = *(uint *)PTR_DAT_8008d2ac;
    *(uint *)PTR_DAT_8008d2ac = uVar9 | 0x200000;


    *(uint *)(puVar13 + 0x1d44) = uVar9 & 0x3e0020 | 0x200000;
    puVar10 = PTR_DAT_8008d2ac;

	// If you are not in Battle Mode
    if ((uVar9 & 0x20) == 0)
	{
	  // loop iteration counter
      iVar17 = 0;

	  // if not zero screens
      if (puVar13[0x1ca8] != '\0')
	  {
		// offset counter
        iVar12 = 0;

        puVar10 = puVar13;

		// for iVar17 = 0; iVar17 < numPlyrCurrGame; iVar17++
        do
		{
		  // if racer is in the top 3 positions of the race (1st, 2nd, 3rd)
          if ((int)*(short *)(*(int *)(puVar10 + 0x24ec) + 0x482) < 3)
		  {
			// all this, is just to increment one value by 1

			// The code here in Versus Standings looks
			// like the code use in Battle Standings

			// Get the rank that the player finished in VS (1st, 2nd, 3rd)
			// Then get the number of times this player has finished in this rank,
			// then increment that number

            *(int *)(puVar13 + (int)*(short *)(*(int *)(puVar10 + 0x24ec) + 0x482) * 4 + iVar12 +
                    0x1e80) =
            *(int *)(puVar13 + (int)*(short *)(*(int *)(puVar10 + 0x24ec) + 0x482) * 4 + iVar12 +
					0x1e80) + 1;
          }

		  // Each player has 12 bytes,
		  // one int for how many times they came 1st
		  // one int for how many times they came 2nd
		  // one int for how many times they came 3rd
          iVar12 = iVar12 + 0xc;

		  // increment iteration counter
          iVar17 = iVar17 + 1;

		  // pointer incrementation
          puVar10 = puVar10 + 4;
        } while (iVar17 < (int)(uint)(byte)puVar13[0x1ca8]);
      }
    }

	// if in battle mode
	else 
	{
	  // if not point limit
      if ((uVar9 & 0x4000) == 0) 
	  {
		// if time limit
        if ((uVar9 & 0x8000) != 0) {
          local_38 = DAT_8008d2f4;
          local_34 = DAT_8008d2f8;
          uVar9 = 0;
          iVar17 = 0;
          do {
            iVar12 = 0;
            sVar5 = -400;

			// start with 3, then 2, 1, 0
            uVar14 = 3;

			// start with P4, and go backwards to P3, P2, P1
            puVar13 = PTR_DAT_8008d2ac + 0xc;

            do
			{
			  // pointer to each player structure, plus offset
              if (*(int *)(*(int *)(puVar13 + 0x24ec) + 0x4e4) != 0)
			  {
						// pointer to each player structure, plus offset
                if ((*(int *)(*(int *)(puVar13 + 0x24ec) + 0x4e4) == (int)sVar5) &&
                   (((int)(uVar9 & 0xff) >> (uVar14 & 0x1f) & 1U) == 0))
				{
                  *(undefined2 *)((int)&local_38 + ((iVar12 + 1) * 0x10000 >> 0xf)) = (short)uVar14;
                  uVar9 = uVar9 | 1 << (uVar14 & 0x1f);
                  iVar12 = iVar12 + 1;
                }

                else
				{
								// pointer to each player structure, plus offset
                  if (((int)sVar5 <= *(int *)(*(int *)(puVar13 + 0x24ec) + 0x4e4)) &&
                     (((int)(uVar9 & 0xff) >> (uVar14 & 0x1f) & 1U) == 0))
				  {
								// pointer to each player structure, plus offset
                    sVar5 = *(short *)(*(int *)(puVar13 + 0x24ec) + 0x4e4);
                    iVar12 = (int)(short)iVar12 + 1;
                    iVar11 = 0;
                    puVar7 = &local_38;
                    if (0 < iVar12) {
                      do {
                        if ((int)*(short *)puVar7 != 0xffffffff) {
                          uVar9 = uVar9 & ~(1 << ((int)*(short *)puVar7 & 0x1fU));
                        }
                        iVar11 = iVar11 + 1;
                        puVar7 = (undefined4 *)((int)puVar7 + 2);
                      } while (iVar11 < iVar12);
                    }
                    iVar12 = 0;

											// Battle Team that the player is on
                    uVar9 = uVar9 | 1 << ((uint)*(ushort *)(*(int *)(puVar13 + 0x24ec) + 0x4e8) &
                                         0x1f);

                    local_38 = local_38 & 0xffff0000 |

									// Battle Team that the player is on
                               (uint)*(ushort *)(*(int *)(puVar13 + 0x24ec) + 0x4e8);
                  }
                }
              }
              uVar14 = uVar14 - 1;
              puVar13 = puVar13 + -4;
            } while (-1 < (int)uVar14);

            sVar5 = (short)iVar12;
            if (((short)local_38 != -1) && (iVar12 = 0, 0 < (int)sVar5 + 1)) {
              puVar7 = &local_38;
              do {
                puVar13 = PTR_DAT_8008d2ac;

				// based on battle team, increment gGT Standing Points by 1,
				// determine how many times driver finished with each rank (1st 2nd 3rd 4th)
				*(int *)(PTR_DAT_8008d2ac + iVar17 * 4 + *(int *)(*(int *)(PTR_DAT_8008d2ac +
					(int)*(short *)puVar7 * 4 + 0x24ec) + 0x4e8) * 0xc + 0x1e80) =
                *(int *)(PTR_DAT_8008d2ac + iVar17 * 4 + *(int *)(*(int *)(PTR_DAT_8008d2ac +
					(int)*(short *)puVar7 * 4 + 0x24ec) + 0x4e8) * 0xc + 0x1e80) + 1;

                if (
						(iVar17 == 0) &&

						// address of each player structure
						(*(int *)(puVar13 + (int)*(short *)puVar7 * 4 + 0x24ec) != 0)
					)
                {
				  // set next winner index in the array of winners, this ID will get confetti
                  *(uint *)(puVar13 + *(int *)(puVar13 + 0x2568) * 4 + 0x2558) =

														// address of each player structure
                       (uint)*(byte *)(*(int *)(puVar13 + (int)*(short *)puVar7 * 4 + 0x24ec) + 0x4a
                                      );

				  // Edit gGT offsets 0x17a, 0x17c, 0x17e
				  // = PushBuffer offsets 0x12, 0x14, 0x16

				  // current fade = flash white
                  *(undefined2 *)
                   (puVar13 +
                   *(int *)(puVar13 + *(int *)(puVar13 + 0x2568) * 4 + 0x2558) * 0x110 + 0x17a) =
                       0x1fff;

				  // desired fade = neutral
                  *(undefined2 *)
                   (puVar13 +
                   *(int *)(puVar13 + *(int *)(puVar13 + 0x2568) * 4 + 0x2558) * 0x110 + 0x17c) =
                       0x1000;

				  // fade step is negative, to move downward
                  *(undefined2 *)
                   (puVar13 +
                   *(int *)(puVar13 + *(int *)(puVar13 + 0x2568) * 4 + 0x2558) * 0x110 + 0x17e) =
                       0xff78;

				  // turn driver into Robotcar
                  FUN_80017318(*(undefined4 *)(puVar13 + (int)*(short *)puVar7 * 4 + 0x24ec));

				  // increment number of winners,
				  // more people get confetti
                  *(int *)(PTR_DAT_8008d2ac + 0x2568) = *(int *)(PTR_DAT_8008d2ac + 0x2568) + 1;
                }
                puVar13 = PTR_DAT_8008d2ac;

				// amount of confetti particles
                *(undefined2 *)(PTR_DAT_8008d2ac + 0x1b04) = 0xfa;
                *(undefined2 *)(puVar13 + 0x1b06) = 0xfa;

				// save the rank that the driver (or team) finished this event
                *(int *)(puVar13 + (int)*(short *)puVar7 * 4 + 0x1da8) = iVar17;

				// numPlyrCurrGame
                pbVar1 = puVar13 + 0x1ca8;

				// loop iteration counter
                uVar14 = 0;

				// if numPlyrCurrGame is not zero
                if (*pbVar1 != 0)
				{
					// address of each player structure
                  piVar2 = (int *)(puVar13 + (int)*(short *)puVar7 * 4 + 0x24ec);

				  // for uVar14 = 0; uVar14 < numPlyrCurrGame; uVar14++
				  do
				  {
					// If two players are on the same team
                    if (*(int *)(*(int *)(puVar13 + 0x24ec) + 0x4e8) == *(int *)(*piVar2 + 0x4e8))
					{
                      uVar9 = uVar9 | 1 << (uVar14 & 0x1f);
                    }

					// increment loop iteration counter
                    uVar14 = uVar14 + 1;

					// increment pointer
                    puVar13 = puVar13 + 4;

                  } while ((int)uVar14 < (int)(uint)*pbVar1);
                }
                iVar12 = iVar12 + 1;
                puVar7 = (undefined4 *)((int)puVar7 + 2);
              } while (iVar12 < (int)sVar5 + 1);
            }
            local_38 = CONCAT22(local_38._2_2_,0xffff);
            iVar17 = iVar17 + sVar5 + 1;
          } while (iVar17 < 4);
        }
      }
	  
	  // if point limit
      else {
        uVar9 = 0;
        iVar17 = 0;
        local_38 = DAT_8008d2f4;
        local_34 = DAT_8008d2f8;
        do {
          sVar5 = -400;
          iVar12 = 0;
          uVar14 = 3;
          puVar13 = puVar10 + 0xc;
          do 
		  {
			// if points on battle team == highest num points
            if ((*(int *)(puVar13 + 0x1d90) == (int)sVar5) &&
               (((int)(uVar9 & 0xff) >> (uVar14 & 0x1f) & 1U) == 0)) 
			{
			  // there is a tie
				
              iVar12 = iVar12 + 1;
              *(undefined2 *)((int)&local_38 + (iVar12 * 0x10000 >> 0xf)) = (short)uVar14;
LAB_8003a71c:
              uVar9 = uVar9 | 1 << (uVar14 & 0x1f);
            }
            
			// if not equal
			else 
			{
			  // points on team is more than highest score
              if (((int)sVar5 <= *(int *)(puVar13 + 0x1d90)) &&
                 (((int)(uVar9 & 0xff) >> (uVar14 & 0x1f) & 1U) == 0)) 
			  {
				// set new highest score
                sVar5 = *(short *)(puVar13 + 0x1d90);
				
				// set number of winners (more than 1 if a tie)
                iVar12 = (int)(short)iVar12 + 1;
				
				// clear previous list of winners,
				// since we have someone with higher scores
                iVar11 = 0;
                puVar7 = &local_38;
                if (0 < iVar12) {
                  do {
                    if ((int)*(short *)puVar7 != 0xffffffff) {
                      uVar9 = uVar9 & ~(1 << ((int)*(short *)puVar7 & 0x1fU));
                    }
                    iVar11 = iVar11 + 1;
                    puVar7 = (undefined4 *)((int)puVar7 + 2);
                  } while (iVar11 < iVar12);
                }
                
				// reset counter
				iVar12 = 0;
                
				// new list of winners
				local_38 = local_38 & 0xffff0000 | uVar14 & 0xffff;
				
                goto LAB_8003a71c;
              }
            }
            uVar14 = uVar14 - 1;
            puVar13 = puVar13 + -4;
          } while (-1 < (int)uVar14);
		  
          if ((short)local_38 != -1) {
            iVar11 = (int)(short)iVar12 + 1;
            iVar8 = 0;
            puVar7 = &local_38;
            if (0 < iVar11) {
              do {
                iVar8 = iVar8 + 1;
				
				// save the rank that the player (or team) finished in this event
                *(int *)(puVar10 + (int)*(short *)puVar7 * 4 + 0x1da8) = iVar17;
                
				puVar7 = (undefined4 *)((int)puVar7 + 2);
              } while (iVar8 < iVar11);
            }
          }
          local_38 = CONCAT22(local_38._2_2_,0xffff);
          iVar17 = iVar17 + (short)iVar12 + 1;
        } while (iVar17 < 4);

		// iteration counter
        iVar12 = 0;

        iVar17 = 0;

		// for iVar12 = 0; iVar12 < 4; iVar12++
		do
		{
		  // If you are not in last place
          if (*(int *)(PTR_DAT_8008d2ac + iVar12 * 4 + 0x1da8) != 3)
		  {
			// Get Battle Team, then get rank of battle team (1st, 2nd, 3rd),
			// then get number of times this team has gotten this rank

			// Increment the number of times this team has finished in this rank

			// In "Battle Standings" You'll see "1st - xx" "2nd - xx", etc.
			// This is incrementing the "xx"

            *(int *)(PTR_DAT_8008d2ac +
                     *(int *)(PTR_DAT_8008d2ac + iVar12 * 4 + 0x1da8) * 4 + iVar17 + 0x1e80) =

			*(int *)(PTR_DAT_8008d2ac +
                     *(int *)(PTR_DAT_8008d2ac + iVar12 * 4 + 0x1da8) * 4 + iVar17 + 0x1e80) + 1;
          }

          puVar13 = PTR_DAT_8008d2ac;

		  // two lines combined get the address of each player structure
          puVar10 = PTR_DAT_8008d2ac + iVar12 * 4;
          iVar11 = *(int *)(puVar10 + 0x24ec);

          if (
				// if player structure is not nullptr
				(iVar11 != 0) &&

				// If this player is on a team that won the battle (0 for 1st place, 1 for 2nd, etc)
				(*(int *)(PTR_DAT_8008d2ac + *(int *)(iVar11 + 0x4e8) * 4 + 0x1da8) == 0)
			  )
		  {
			// set next winner index in the array of winners, this ID will get confetti
            *(uint *)(PTR_DAT_8008d2ac + *(int *)(PTR_DAT_8008d2ac + 0x2568) * 4 + 0x2558) =

				 // Player / AI structure + 0x4a shows driver index (0-7)
				 (uint)*(byte *)(iVar11 + 0x4a);

			// Edit PushBuffer offsets 0x17a, 0x17c, 0x17e

            *(undefined2 *)
             (puVar13 + *(int *)(puVar13 + *(int *)(puVar13 + 0x2568) * 4 + 0x2558) * 0x110 + 0x17a)
                 = 0x1fff;
            *(undefined2 *)
             (puVar13 + *(int *)(puVar13 + *(int *)(puVar13 + 0x2568) * 4 + 0x2558) * 0x110 + 0x17c)
                 = 0x1000;
            *(undefined2 *)
             (puVar13 + *(int *)(puVar13 + *(int *)(puVar13 + 0x2568) * 4 + 0x2558) * 0x110 + 0x17e)
                 = 0xff78;

			// turn driver into Robotcar
            FUN_80017318(*(undefined4 *)(puVar10 + 0x24ec));

			// increment number of winners,
			// more people get confetti
            *(int *)(PTR_DAT_8008d2ac + 0x2568) = *(int *)(PTR_DAT_8008d2ac + 0x2568) + 1;
          }
          puVar13 = PTR_DAT_8008d2ac;

		  // increment loop counter
          iVar12 = iVar12 + 1;

		  // amount of confetti particles
          *(undefined2 *)(PTR_DAT_8008d2ac + 0x1b04) = 0xfa;
          *(undefined2 *)(puVar13 + 0x1b06) = 0xfa;

          iVar17 = iVar17 + 0xc;
        } while (iVar12 < 4);
      }
    }
    puVar13 = PTR_DAT_8008d2ac;
    uVar9 = 0;

	// loop counter
    iVar12 = 0;

    iVar17 = 0;
    puVar10 = PTR_DAT_8008d2ac;

	// for iVar12 = 0; iVar12 < 4; iVar12++
	do {
      iVar8 = 0;

	  // loop counter
      iVar15 = 0;

      iVar11 = iVar17;

	  // for iVar15 = 0; iVar15 < 3; iVar15++
      do {
        iVar3 = iVar11 + 0x1e80;
        iVar6 = 3 - iVar15;
        iVar11 = iVar11 + 4;

		// increment loop counter
        iVar15 = iVar15 + 1;

        iVar8 = iVar8 + *(int *)(puVar13 + iVar3) * iVar6;
      } while (iVar15 < 3);

      *(int *)(puVar10 + 0x1de0) = iVar8 * 0x10000 >> 0x10;
      puVar4 = PTR_DAT_8008d2ac;
      puVar10 = puVar10 + 4;

	  // increment loop counter
      iVar12 = iVar12 + 1;

      iVar17 = iVar17 + 0xc;
    } while (iVar12 < 4);

	// loop counter
    iVar17 = 0;

    puVar13 = PTR_DAT_8008d2ac;

	// for iVar17 = 0; iVar17 < 4; iVar17++
	do {
      sVar5 = 0;
      uVar14 = 0xffffffff;
      uVar16 = 3;
      puVar10 = puVar4 + 0xc;
      do {
        if ((((int)sVar5 <= *(int *)(puVar10 + 0x1de0)) &&
            (((int)(uVar9 & 0xff) >> (uVar16 & 0x1f) & 1U) == 0)) &&
			
			// if team exists
           (((*(uint *)(puVar4 + 0x1dd8) & 1 << (uVar16 & 0x1f)) != 0 ||
		   
		    // not in battle mode
            ((*(uint *)puVar4 & 0x20) == 0)))) 
		{
          sVar5 = *(short *)(puVar10 + 0x1de0);
          if ((int)(short)uVar14 != 0xffffffff) {
            uVar9 = uVar9 & ~(1 << ((int)(short)uVar14 & 0x1fU));
          }
          uVar9 = uVar9 | 1 << (uVar16 & 0x1f);
          uVar14 = uVar16;
        }
        uVar16 = uVar16 - 1;
        puVar10 = puVar10 + -4;
      } while (-1 < (int)uVar16);
	  
      *(int *)(puVar13 + 0x1dc8) = (int)(short)uVar14;

	  // increment loop counter
	  iVar17 = iVar17 + 1;

	  puVar13 = puVar13 + 4;
    } while (iVar17 < 4);

	// pointer to first Player thread
    iVar17 = *(int *)(PTR_DAT_8008d2ac + 0x1b2c);

	// end race clock for all human players

	// if thread is valid
    while (iVar17 != 0)
	{
	  // UI_RaceEnd_GetDriverClock
      FUN_8005572c(*(undefined4 *)(iVar17 + 0x30));

	  // go to next thread
      iVar17 = *(int *)(iVar17 + 0x10);
    }

	// UI_VsQuipAssignAll
    FUN_80054bfc();

	// SubmitName_RestoreName
    FUN_8004aa08(2);

	// if you are in Relic Race or Time Trial
    if ((*(uint *)PTR_DAT_8008d2ac & 0x4020000) != 0)
	{
	  // MainGameEnd_SoloRaceGetReward
      FUN_80039fa8(1);

	  // If you're not in a Relic Race
      if ((*(uint *)PTR_DAT_8008d2ac & 0x4000000) == 0)
	  {
        if (

			// if you are not showing a ghost during a race
			(DAT_8008d958 == 0) ||
			(
				(
					// if ghost is not too big
					DAT_8008d744 == 0 &&

					(*(int *)(local_30 + 0x514) < *(int *)(DAT_8008d754 + 0x10))
				)
			)
		   )
		{
          // GhostTape_End
		  FUN_80027e90();

          *(uint *)(PTR_DAT_8008d2ac + 0x1d44) = *(uint *)(PTR_DAT_8008d2ac + 0x1d44) | 1;
        }
      }

	  // If you are in Relic Race
      else
	  {
		// RR_EndEvent_UnlockAward
        FUN_8009f71c();
      }
    }
  }

  // Podium_InitModels
  FUN_80041c84(PTR_DAT_8008d2ac);

  return;
}


// MainGameStart_Initialize
void FUN_8003aee8(uint *param_1,int param_2)

{
  uint uVar1;

  // DotLights_AudioAndVideo wont execute
  // if (gGT & 0x20102000 == 0), but if it did execute,
  // traffic lights would instantly hit green in cutscene
  // and main menu, while starting from top-position (0xf00)
  // when spawning in the adventure arena

  // if you're not in cutscene and not in main menu
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20002000) == 0)
  {
	// traffic light countdown
    param_1[0x743] = 0xf00;

	// fly-in camera animation
    uVar1 = *param_1 | 0x40;
  }

  // if you are:
  else
  {
	// disable traffic lights
    param_1[0x743] = 0;

	// no fly-in camera
    uVar1 = *param_1 & 0xffffffbf;
  }

  // save new game mode, removing end-of-race flag
  *param_1 = uVar1;
  *param_1 = *param_1 & 0xffdfffff;

  // this never happens in normal gameplay
  if (param_2 == 0) {

	// Music_Stop
	FUN_8002e4ec();

	// howl_StopAudio (stops menu sounds)
	// keep backup,
	// keep music (no music to stop),
	// stop all fx
    FUN_8002c8a8(0,0,1);
  }

  // VehBirth_TeleportAll
  FUN_80058898(param_1,2);
  return;
}


// MainInit_VisMem
// param1 is PTR_DAT_8008d2ac
void FUN_8003af84(int param_1)

{
  int iVar1;
  int iVar2;

  // lev offset 0x190?
  iVar1 = *(int *)(*(int *)(param_1 + 0x160) + 400);

  // called VISMEM in prototypes
  *(int *)(param_1 + 0x1a38) = iVar1;

  if (
		(iVar1 != 0) &&
		(
			iVar1 = 0,

			// numPlyrCurrGame is not zero
			*(char *)(param_1 + 0x1ca8) != '\0')
		)
  {
	// for iVar1 = 0; iVar1 < numPlyrCurrGame; iVar1++
    do {
      iVar2 = iVar1 * 4;
      *(undefined4 *)(*(int *)(param_1 + 0x1a38) + iVar2 + 0x40) = 0;
      *(undefined4 *)(*(int *)(param_1 + 0x1a38) + iVar2 + 0x50) = 0;
      *(undefined4 *)(*(int *)(param_1 + 0x1a38) + iVar2 + 0x60) = 0;
      *(undefined4 *)(*(int *)(param_1 + 0x1a38) + iVar2 + 0x70) = 0;
      iVar1 = iVar1 + 1;
    } while (iVar1 < (int)(uint)*(byte *)(param_1 + 0x1ca8));
  }
  return;
}


// MainInit_RainBuffer
// param1 is PTR_DAT_8008d2ac
void FUN_8003b008(int param_1)

{
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;

  iVar6 = 0;
  iVar5 = param_1;

  // if numPlyrCurrGame is not zero
  if (*(char *)(param_1 + 0x1ca8) != '\0') {

	// for ivar6 = 0; ivar6 < numPlyrCurrGame; ivar6++
    do
	{
	  // gGT->level1
      iVar2 = *(int *)(param_1 + 0x160);

	  // Rain Buffer
      puVar4 = (undefined4 *)(iVar5 + 0x1a40);

	  // copy rain buffer from level, to player's global rain buffer
      puVar3 = (undefined4 *)(iVar2 + 0x104);
      do {
        uVar7 = puVar3[1];
        uVar8 = puVar3[2];
        uVar9 = puVar3[3];
        *puVar4 = *puVar3;
        puVar4[1] = uVar7;
        puVar4[2] = uVar8;
        puVar4[3] = uVar9;
        puVar3 = puVar3 + 4;
        puVar4 = puVar4 + 4;
      } while (puVar3 != (undefined4 *)(iVar2 + 0x134));

	  // numPlyrCurrGame
      bVar1 = *(byte *)(param_1 + 0x1ca8);
	  
	  #if 0 // do not rewrite
      if (bVar1 == 0) trap(0x1c00);
	  if (((uint)bVar1 == 0xffffffff) && (*(int *)(iVar5 + 0x1a40) == -0x80000000)) trap(0x1800);
	  #endif

	  // gGT->rainBuffer[i].numParticles_curr
      *(int *)(iVar5 + 0x1a40) = *(int *)(iVar5 + 0x1a40) / (int)(uint)bVar1;

	  // numPlyrCurrGame
	  bVar1 = *(byte *)(param_1 + 0x1ca8);
      
	  #if 0 // do not rewrite
	  if (bVar1 == 0) trap(0x1c00);
	  if (((uint)bVar1 == 0xffffffff) && ((uint)*(ushort *)(iVar5 + 0x1a44) == 0x80000000)) trap(0x1800);
      #endif

	  // next screen
	  iVar6 = iVar6 + 1;

	  // gGT->rainBuffer[i].numParticles_max
      *(undefined2 *)(iVar5 + 0x1a44) =
           (short)((int)(uint)*(ushort *)(iVar5 + 0x1a44) / (int)(uint)bVar1);

	  // next player's rain buffer
	  iVar5 = iVar5 + 0x30;

    } while (iVar6 < (int)(uint)*(byte *)(param_1 + 0x1ca8));
  }
  return;
}

// MainInit_PrimMem
void FUN_8003b0f0(uint *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;

  uVar3 = 0x5f;
  uVar1 = 0x78;
  uVar4 = 0x96;

  // 0x1a10, levID == adventure Character Selection
  if (param_1[0x684] == 0x28)
  {
	// +0x23 = gGT->0x8C, &gGT->DB[0].primMem
    FUN_800349c4(param_1 + 0x23,0x1b800);
    iVar2 = 0x1b800;
  }

  else
  {
	// If you are not in main menu
    if ((*param_1 & 0x2000) == 0)
	{
	  // (72a*4 = 1ca8), numPlyrCurrGame
      switch(*(undefined *)(param_1 + 0x72a))
	  {
		// zero players, how?
      case 0:

		// +0x23 = gGT->0x8C, &gGT->DB[0].primMem
        FUN_800349c4(param_1 + 0x23,0x25800);
        iVar2 = 0x25800;
        goto LAB_8003b2b8;

		// 1 player
      case 1:

	    // If you're in Adventure Arena
        if ((*(uint *)PTR_DAT_8008d2ac & 0x100000) != 0)
		{
		  // +0x23 = gGT->0x8C, &gGT->DB[0].primMem
          FUN_800349c4(param_1 + 0x23,0x1c000);
          iVar2 = 0x1c000;
          goto LAB_8003b2b8;
        }

		// if level is some intro cutscene (30 - 39)
        if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x1eU < 9)
		{
		  // +0x23 = gGT->0x8C, &gGT->DB[0].primMem
          FUN_800349c4(param_1 + 0x23,0x1e000);
          iVar2 = 0x1e000;
          goto LAB_8003b2b8;
        }

		// if LEV is a track 0-25,
		// so, not a warp room
        if ((int)param_1[0x684] < 0x19)
		{
		  // primMem[1p][gGT->levelID]
          uVar3 = (uint)(byte)&DAT_8008454c[param_1[0x684]];
        }
        iVar2 = uVar3 << 10;
        break;

		// 2 players
      case 2:
		// if LEV is a track 0-25,
		// so, not a warp room
        if ((int)param_1[0x684] < 0x19)
		{
		  // primMem[2p][gGT->levelID]
          uVar1 = (uint)(byte)(&DAT_80084568)[param_1[0x684]];
        }
        iVar2 = uVar1 << 10;
        break;

		// 3 or 4 players
      case 3:
      case 4:
		// if LEV is a track 0-25,
		// so, not a warp room
        if ((int)param_1[0x684] < 0x19)
		{
		  // primMem[4p][gGT->levelID]
          uVar4 = (uint)(byte)(&DAT_80084584)[param_1[0x684]];
        }
        iVar2 = uVar4 << 10;
        break;

      default:
        return;
      }

	  // +0x23 = gGT->0x8C, &gGT->DB[0].primMem
      FUN_800349c4(param_1 + 0x23,iVar2);
    }

	// If you are in main menu
	else
	{
	  // +0x23 = gGT->0x8C, &gGT->DB[0].primMem
      FUN_800349c4(param_1 + 0x23,0x17c00);
      iVar2 = 0x17c00;
    }
  }
LAB_8003b2b8:

  // +0x4C = gGT->0x8C+0xA4, &gGT->DB[1].primMem
  FUN_800349c4(param_1 + 0x4c,iVar2);
  return;
}


// MainInit_JitPoolsReset
void FUN_8003b2d4(int param_1)

{
  // erase everything in all pools
  FUN_80030fdc(param_1 + 0x18d0); // Thread Pool
  FUN_80030fdc(param_1 + 0x18f8); // Instance Pool
  FUN_80030fdc(param_1 + 0x1920); // Small Stack Pool
  FUN_80030fdc(param_1 + 0x1948); // Medium Stack Pool
  FUN_80030fdc(param_1 + 0x1970); // Large Stack Pool (drivers)
  FUN_80030fdc(param_1 + 0x1998); // Particle Pool
  FUN_80030fdc(param_1 + 0x19c0); // Oscillator Pool
  FUN_80030fdc(param_1 + 0x19e8); // Rain Pools
  return;
}

// MainInit_OTMem
void FUN_8003b334(uint *param_1)

{
  uint uVar1;
  undefined4 uVar2;

  uVar1 = *param_1;

  // If not in main menu
  if ((uVar1 & 0x2000) == 0)
  {
	// If not in Adventure Arena
    if ((uVar1 & 0x100000) == 0) {

	  // If not in Battle
      if ((uVar1 & 0x20) == 0)
	  {
		// (72a*4 = 1ca8), numPlyrCurrGame

		// if less than 3 players
        if (*(byte *)(param_1 + 0x72a) < 3)
		{
		  // +0x2a = gGT->0xA8 (&gGT->DB[0].otMem)
          FUN_80034a28(param_1 + 0x2a,0x2000);
          uVar2 = 0x2000;
        }

		// if 3 or 4 players
        else
		{
		  // +0x2a = gGT->0xA8 (&gGT->DB[0].otMem)
          FUN_80034a28(param_1 + 0x2a,0x3000);
          uVar2 = 0x3000;
        }
      }

	  // If in Battle
      else
	  {
		// +0x2a = gGT->0xA8 (&gGT->DB[0].otMem)
        FUN_80034a28(param_1 + 0x2a,0x8000);
        uVar2 = 0x8000;
      }
    }

	// If in Adventure Arena
    else
	{
	  // +0x2a = gGT->0xA8 (&gGT->DB[0].otMem)
      FUN_80034a28(param_1 + 0x2a,0x2c00);
      uVar2 = 0x2c00;
    }
  }

  // If in main menu
  else
  {
	// +0x2a = gGT->0xA8 (&gGT->DB[0].otMem)
    FUN_80034a28(param_1 + 0x2a,0x1800);
    uVar2 = 0x1800;
  }

  // +0x53 = gGT->0xA8+0xA4 (&gGT->DB[1].otMem)
  FUN_80034a28(param_1 + 0x53,uVar2);

  // s_ot_0__8008d2fc
  // "ot[0]"

  // MEMPACK_AllocMem
  // (72a*4 = 1ca8), numPlyrCurrGame
  uVar1 = FUN_8003e874((uint)*(byte *)(param_1 + 0x72a) << 0xc | 0x18,s_ot_0__8008d2fc);

  // first index of "ot" pointer array
  param_1[0x632] = uVar1;

  // s_ot_1__8008d304
  // "ot[1]"

  // MEMPACK_AllocMem
  // (72a*4 = 1ca8), numPlyrCurrGame
  uVar1 = FUN_8003e874((uint)*(byte *)(param_1 + 0x72a) << 0xc | 0x18,s_ot_1__8008d304);

  // second index of "ot" pointer array
  param_1[0x633] = uVar1;

  return;
}

// MainInit_JitPoolsNew
void FUN_8003b43c(uint *param_1)
{
  // In theory, param_1 is PTR_DAT_8008d2ac

  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  undefined *puVar5;
  int iVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;

  // game mode
  uVar3 = *param_1;

  // This happens if you're in Adventure Arena
  uVar7 = 0x800;

  if (
		// If you're not in Adventure Arena
		((uVar3 & 0x100000) == 0) &&

		(
			// This value sets if you're not in adventure
			// arena, and not in the main menu
			uVar7 = 0x1000,

			// If you're in main menu
			(uVar3 & 0x2000) != 0
		)
	  )
  {
	// This is set if not in Adventure Arena,
	// and if you're in main menu
    uVar7 = 0x400;
  }

  // This happens if you're in Adventure Arena
  uVar9 = 0x800;

  // If you're not in Adventure Arena
  if ((uVar3 & 0x100000) == 0)
  {
	// If you're not in main menu
    if ((uVar3 & 0x2000) == 0) {
      uVar9 = 0x1000;
    }

	// If you're in main menu
    else {
      uVar9 = 0x400;

	  // if gGT->levelID == 40 (AdvGarage)
      if (param_1[0x684] == 0x28) {
        uVar9 = 0x800;
      }
    }
  }

  // add a bookmark
  FUN_8003e978();

  // param_1 + 0x634 =
  // PTR_DAT_8008d2ac + 0x18d0
  FUN_8003105c(param_1 + 0x634,uVar9 * 3 >> 7,0x48,"ThreadPool");

  // 8008d2ac + 0x18F8
  // instance size changes based on numPlyrCurrGame
  FUN_8003105c(param_1 + 0x63e,uVar9 >> 5,
			  0x74 + (0x88 * (uint)(byte)PTR_DAT_8008d2ac[0x1ca8]),
			  "InstancePool");

  // 8008d2ac + 0x1920
  FUN_8003105c(param_1 + 0x648,uVar7 * 0x19 >> 10,0x48,"SmallStackPool");

  // 8008d2ac + 0x1948
  FUN_8003105c(param_1 + 0x652,uVar7 >> 7,0x88,"MediumStackPool");

  // if you're not in main menu
  if ((*param_1 & 0x2000) == 0)
  {
	// allocate 8 driver structs
    uVar3 = uVar7 >> 9;
  }

  // if you are in main menu
  else
  {
	// allocate 4 driver structs
    uVar3 = 4;
  }

  // 8008d2ac + 0x1970
  FUN_8003105c(param_1 + 0x65c,uVar3,0x670,"LargeStackPool");

  // 8008d2ac + 0x1998
  FUN_8003105c(param_1 + 0x666,uVar7 >> 5,0x7c,"ParticlePool");

  // 8008d2ac + 0x19c0
  FUN_8003105c(param_1 + 0x670,uVar7 >> 5,0x18,"OscillatorPool");

  // 8008d2ac + 0x19e8
  FUN_8003105c(param_1 + 0x67a,uVar7 >> 9,0x28,"RainPool");

  // MEMPACK_AllocMem
  uVar1 = FUN_8003e874(uVar9,"RENDER_BUCKET_INSTANCE");

  // render bucket instance
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x1c94) = uVar1;

// ===========================================

  // 0x1920 (smallstack)
  // increment every pointer by 8 bytes,
  // to encapsulate "next" and "prev" in objects
  piVar4 = (int *)param_1[0x648];
  while (piVar4 != (int *)0x0) {
    *(int **)(piVar4 + 2) = piVar4 + 2;
    piVar4 = (int *)*piVar4;
  }
  
  // 0x1948 (medstack)
  // increment every pointer by 8 bytes,
  // to encapsulate "next" and "prev" in objects
  piVar4 = (int *)param_1[0x652];
  while (piVar4 != (int *)0x0) {
    *(int **)(piVar4 + 2) = piVar4 + 2;
    piVar4 = (int *)*piVar4;
  }
  
  // 0x1970 (largestack)
  // increment every pointer by 8 bytes,
  // to encapsulate "next" and "prev" in objects
  piVar4 = (int *)param_1[0x65c];
  puVar5 = PTR_DAT_8008d2ac;

  // for some reason, compiler optimization
  // manipulates gGT instead of the pointer,
  // but gGT gets reset at the end so whatever
  while (
			PTR_DAT_8008d2ac = puVar5,
			piVar4 != (int *)0x0
		)
  {
    *(int **)(piVar4 + 2) = piVar4 + 2;
    piVar4 = (int *)*piVar4;
    puVar5 = PTR_DAT_8008d2ac;
  }
  
  // loop count
  iVar6 = 0;

  // numPlyrCurrGame != 0
  if (puVar5[0x1ca8] != '\0')
  {
	// global clip buffers
    puVar8 = &DAT_80084228;

	// ivar6 = 0; ivar6 < numPlyrCurrGame; iVar6++
    do {

	  // increment loop counter
      iVar6 = iVar6 + 1;

									// Level ID							// numPlyrCurrGame
      iVar2 = FUN_80034960(*(undefined4 *)(puVar5 + 0x1a10),(uint)(byte)puVar5[0x1ca8]);

	  // MEMPACK_AllocMem
      uVar1 = FUN_8003e874(iVar2 << 2,"Clip Buffer");

      puVar5 = PTR_DAT_8008d2ac;
      *puVar8 = uVar1;
      puVar8 = puVar8 + 1;
    } while (iVar6 < (int)(uint)(byte)puVar5[0x1ca8]);
  }
  return;
}


// MainInit_Drivers
void FUN_8003b6d0(uint *param_1)

{
  byte bVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;


  // 8 drivers
  iVar5 = 7;

  // 8009900C + 4*8
  puVar2 = param_1 + 7;

  // for iVar5 = 7; iVar5 > -1; iVar5--)
  do
  {
	// erase pointer to driver at 8009900C
    puVar2[0x93b] = 0;

	// decrement loop counter
    iVar5 = iVar5 + -1;

	// decrement pointer
    puVar2 = puVar2 + -1;

  } while (-1 < iVar5);

  // Set number of AIs to zero
  PTR_DAT_8008d2ac[0x1cab] = 0;

  // if game mode is not:
  // 	cutscene
  //	adventure arena
  //	main menu
  if ((*param_1 & 0x20102000) == 0)
  {
	// BOTS_Adv_AdjustDifficulty
    FUN_80012598();
  }

  // GhostReplay_Init1
  FUN_80027838();

  // Check if 231 dll is loaded
  iVar5 = FUN_800348e8();

  // If it is loaded
  if (iVar5 != 0)
  {
	// RB_MinePool_Init
    FUN_800abfec();
  }

  // This is a strange way to count a loop

  // iVar5 = number of players - 1
  // (72a*4 = 1ca8), numPlyrCurrGame
  iVar5 = (uint)*(byte *)(param_1 + 0x72a) - 1;

  // if that is zero or more, which it always will be,
  // knowing you can't have zero players in a game
  if (-1 < iVar5)
  {
    puVar2 = param_1 + iVar5;

	// spawn all players

	// iVar5 = numPlyrCurrGame - 1; iVar5 > -1; iVar5--
	do {

	  // spawn a player, return Driver*
      uVar3 = FUN_80058ec0(iVar5);

	  // check that Driver is not nullptr
      if (uVar3 != 0)
	  {
		// put Driver pointer in 800990C array
        puVar2[0x93b] = uVar3;
      }

	  // strange iteration counter
      iVar5 = iVar5 + -1;

      puVar2 = puVar2 + -1;
    } while (-1 < iVar5);
  }
  if (
		(
			// not one of the following game modes ????
			((*param_1 & 0x2c122020) == 0) &&

			// numPlyrCurrGame is not 3
			(PTR_DAT_8008d2ac[0x1ca8] != '\x03')
		) &&
		(
			// assignment
			uVar3 = *(uint *)PTR_DAT_8008d2ac,

			// in Arcade or Adventure
			(uVar3 & 0x480000) != 0
		)
	)
  {
	// If you're in Boss Mode
	// 0x80000000
    if ((int)uVar3 < 0)
	{
	  // Make an AI for the boss

	  // Spawn AI for driver index 1,
	  // which is 2nd index of array
      FUN_80017164(1);
    }

	// If you're not in Boss Mode
    else {

      if (
			// If you are not in Adventure cup
			((uVar3 & 0x10000000) == 0) ||

			(
				// loop counter
				iVar5 = 1,

				// If you are in Adventure Cup, but not purple gem cup
				*(int *)(PTR_DAT_8008d2ac + 0x1e58) != 4
			)
		  )
	  {
		// (72a*4 = 1ca8), numPlyrCurrGame
        bVar1 = *(byte *)(param_1 + 0x72a);

        uVar3 = (uint)bVar1;

		// If there is 1 human
        if (bVar1 == 1)
		{
		  // Number of drivers is 8
          uVar4 = 8;
        }

		// If this is not 1P mode
        else
		{
		  // Assume 4 drivers in 3P or 4P mode
          uVar4 = 4;

		  // If this is 2P mode
          if (bVar1 == 2)
		  {
			// There are 6 racers
            uVar4 = 6;
          }
        }

		// If the number of players <
		// desired number of drivers
        if (uVar3 < uVar4)
		{
          do
		  {
			// spawn an AI at this character index
            FUN_80017164(uVar3);

			// increment number loop counter
            uVar3 = uVar3 + 1;
          } while ((int)uVar3 < (int)uVar4);
        }
      }

	  // If you are in Purple Gem Cup
	  else
	  {
		// Spawn 4 AIs

		// for iVar5 = 1; iVar5 < 5; iVar5++
        do
		{
		  // Spawn an AI
          FUN_80017164(iVar5);

		  // increment loop counter
		  iVar5 = iVar5 + 1;

        } while (iVar5 < 5);
      }
    }
  }

  // If number of AIs is not zero
  if (PTR_DAT_8008d2ac[0x1cab] != '\0') {
    FUN_80028880(0x10,0x8080);
    FUN_80028880(0x11,0x8080);
  }

  // if this is main menu
  if ((*param_1 & 0x2000) != 0) {

	// uvar3 = numPlyrCurrGame
    uVar3 = (uint)(byte)PTR_DAT_8008d2ac[0x1ca8];

	// if numPlyrCurrGame is less than 4
    if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 4) {

	  param_1 = param_1 + uVar3;

	  // uVar3 = numPlyrCurrGame; uVar3 < 4; uVar3++
	  do {

		// spawn player, return Driver*
        uVar4 = FUN_80058ec0(uVar3);

		// make sure Driver isn't nullptr
        if (uVar4 != 0)
		{
		  // put Driver pointer in 800990C array
          param_1[0x93b] = uVar4;
        }

		// increment loop counter
        uVar3 = uVar3 + 1;

        param_1 = param_1 + 1;

      } while ((int)uVar3 < 4);
    }
  }

  // if you're in time trial, not main menu, not loading.
  // basically, if you're in time trial gameplay
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20022000) == 0x20000)
  {
	// GhostReplay_Init2
    FUN_80027b88();

	// GhostTape_Start
    FUN_80027df4();
  }
  return;
}


// param1 is PTR_DAT_8008d2ac
// MainInit_FinalizeInit
void FUN_8003b934(uint *param_1)

{
  byte bVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;

  // enable collisions with all temporary walls
  // (adv hub doors, tiger temple teeth, etc)
  DAT_8008d728 = 0;

  // add a bookmark
  FUN_8003e978();

  puVar2 = PTR_DAT_8008d2ac;

  // loop counter
  iVar8 = 0;

  *(undefined4 *)(PTR_DAT_8008d2ac + 0x180) = 0x100;
  *(undefined4 *)(puVar2 + 0x274) = 0x100;

  // erase all threadBucket structs
  memset(param_1 + 0x6cb,0,0x168);

  // threadBuckets.player
  param_1[0x6cc] = 0x8008d30c; // PLAYER
  param_1[0x6cd] = 0x8008d314; // PLYR

  // threadBuckets.robot
  param_1[0x6d1] = 0x8008d31c; // ROBOT
  param_1[0x6d2] = 0x8008d324; // RBOT

  // threadBuckets.static
  param_1[0x6db] = 0x8008d32c; // STATIC
  param_1[0x6dc] = 0x8008d334; // STAT

  // threadBuckets.mine
  param_1[0x6e0] = 0x8008d33c; // MINE
  param_1[0x6e1] = 0x8008d33c; // MINE

  // threadBuckets.warppad
  param_1[0x6e5] = 0x8008d344; // WARPPAD
  param_1[0x6e6] = 0x8008d34c; // WRPD

  // threadBuckets.tracking
  param_1[0x6ea] = 0x80011434; // TRACKING
  param_1[0x6eb] = 0x8008d354; // TRKG

  // player threads can pause
  param_1[0x6ce] = 0;

  *(undefined *)(param_1 + 0x6cf) = 0x40;
  *(undefined *)((int)param_1 + 0x1b3d) = 0x40;
  *(undefined *)((int)param_1 + 0x1b3e) = 0x80;

  // robotcar threads can pause
  param_1[0x6d3] = 0;

  *(undefined *)(param_1 + 0x6d4) = 0x40;
  *(undefined *)((int)param_1 + 0x1b51) = 0x80;
  *(undefined *)((int)param_1 + 0x1b52) = 0x40;

  // static threads cant pause
  param_1[0x6dd] = 1;

  *(undefined *)(param_1 + 0x6de) = 0x40;
  *(undefined *)((int)param_1 + 0x1b79) = 0x80;
  *(undefined *)((int)param_1 + 0x1b7a) = 0x80;

  // mine threads can pause
  param_1[0x6e2] = 0;

  *(undefined *)(param_1 + 0x6e3) = 0x80;
  *(undefined *)((int)param_1 + 0x1b8d) = 0x80;
  *(undefined *)((int)param_1 + 0x1b8e) = 0x80;

  // warppad threads cant pause
  param_1[0x6e7] = 1;

  *(undefined *)(param_1 + 0x6e8) = 0x80;
  *(undefined *)((int)param_1 + 0x1ba1) = 0x40;
  *(undefined *)((int)param_1 + 0x1ba2) = 0x80;

  // tracking threads can pause
  param_1[0x6ec] = 0;

  *(undefined *)(param_1 + 0x6ed) = 0x80;

  // threadBuckets.burst
  param_1[0x6ef] = 0x8008d35c; // BURST
  param_1[0x6f0] = 0x8008d364; // BRST

  // threadBuckets.blowUp
  param_1[0x6f4] = 0x8008d36c; // BLOWUP
  param_1[0x6f5] = 0x8008d374; // BLWP

  // threadBuckets.turbo
  param_1[0x6f9] = 0x8008d37c; // TURBO
  param_1[0x6fa] = 0x8008d384; // TRBO

  // threadBuckets.spider
  param_1[0x6fe] = 0x8008d38c; // SPIDER
  param_1[0x6ff] = 0x8008d394; // SPDR

  // threadBuckets.follower
  param_1[0x703] = 0x80011440; // FOLLOWER
  param_1[0x704] = 0x8008d39c; // FLWR

  // threadBuckets.startText
  param_1[0x708] = 0x8001144c; // STARTTEXT

  *(undefined *)((int)param_1 + 0x1bb5) = 0x80;
  *(undefined *)((int)param_1 + 0x1bb6) = 0x80;

  // burst threads can pause
  param_1[0x6f1] = 0;

  *(undefined *)(param_1 + 0x6f2) = 0x80;
  *(undefined *)((int)param_1 + 0x1bc9) = 0x40;
  *(undefined *)((int)param_1 + 0x1bca) = 0x80;

  // blowup threads can pause
  param_1[0x6f6] = 0;

  *(undefined *)(param_1 + 0x6f7) = 0x80;
  *(undefined *)((int)param_1 + 0x1bdd) = 0x80;
  *(undefined *)((int)param_1 + 0x1bde) = 0;

  // turbo threads can pause
  param_1[0x6fb] = 0;

  *(undefined *)(param_1 + 0x6fc) = 0;
  *(undefined *)((int)param_1 + 0x1bf1) = 0;
  *(undefined *)((int)param_1 + 0x1bf2) = 0x80;

  // spider threads can pause
  param_1[0x700] = 0;

  *(undefined *)(param_1 + 0x701) = 0x80;
  *(undefined *)((int)param_1 + 0x1c05) = 0x40;
  *(undefined *)((int)param_1 + 0x1c06) = 0x80;

  // follower threads can pause
  param_1[0x705] = 0;

  *(undefined *)(param_1 + 0x706) = 0x40;
  *(undefined *)((int)param_1 + 0x1c19) = 0x40;
  *(undefined *)((int)param_1 + 0x1c1a) = 0x80;

  // threadBuckets.starttext
  param_1[0x709] = 0x8008d3a4; // STXT

  // threadBuckets.other
  param_1[0x70d] = 0x8008d3ac; // OTHER
  param_1[0x70e] = 0x8008d3b4; // OTHR

  // threadBuckets.akuAku
  param_1[0x712] = 0x8008d3bc; // AKUAKU
  param_1[0x713] = 0x8008d3c4; // AKUU

  // threadBuckets.camera
  param_1[0x717] = 0x8008d3cc; // CAMERA
  param_1[0x718] = 0x8008d3d4; // CAMR

  // threadBuckets.hud
  param_1[0x71c] = 0x8008d3dc; // HUD
  param_1[0x71d] = 0x8008d3e0; // THUD

  // threadBuckets.pause
  param_1[0x721] = 0x8008d3e8; // PAUSE

  // starttext threads can pause
  param_1[0x70a] = 0;

  *(undefined *)(param_1 + 0x70b) = 0x80;
  *(undefined *)((int)param_1 + 0x1c2d) = 0x80;
  *(undefined *)((int)param_1 + 0x1c2e) = 0x40;

  // "other" threads can pause
  param_1[0x70f] = 0;

  *(undefined *)(param_1 + 0x710) = 0x80;
  *(undefined *)((int)param_1 + 0x1c41) = 0x40;
  *(undefined *)((int)param_1 + 0x1c42) = 0x40;

  // aku threads can pause
  param_1[0x714] = 0;

  *(undefined *)(param_1 + 0x715) = 0x80;
  *(undefined *)((int)param_1 + 0x1c55) = 0x40;
  *(undefined *)((int)param_1 + 0x1c56) = 0x40;

  // camera threads cant pause
  param_1[0x719] = 1;

  *(undefined *)(param_1 + 0x71a) = 0x80;
  *(undefined *)((int)param_1 + 0x1c69) = 0x80;
  *(undefined *)((int)param_1 + 0x1c6a) = 0x40;

  // hud threads cant pause
  param_1[0x71e] = 1;

  *(undefined *)(param_1 + 0x71f) = 0x80;
  *(undefined *)((int)param_1 + 0x1c7d) = 0x80;
  *(undefined *)((int)param_1 + 0x1c7e) = 0x80;

  // PAUS
  param_1[0x722] = 0x8008d3f0;

  // pause threads can pause
  param_1[0x723] = 0;

  *(undefined *)(param_1 + 0x724) = 0;
  *(undefined *)((int)param_1 + 0x1c91) = 0x80;
  *(undefined *)((int)param_1 + 0x1c92) = 0;

  // reset particle linked lists
  param_1[0x727] = 0;
  param_1[0x728] = 0;

  // reset number of particles
  param_1[0x729] = 0;

  // deadc0ed, FUN_8006c684
  // RNG stuff
  param_1[0x94b] = 0x30215400;
  param_1[0x94c] = 0x493583fe;

  puVar5 = param_1;

  // for iVar8 = 0; iVar8 < 0xc; iVar8++
  do
  {
    puVar5[0x16c] = 0;
    *(undefined2 *)(puVar5 + 0x16a) = 1000;
    puVar5[0x1ad] = 0;
    puVar5[0x1ae] = 0;

	// increment loop counter
    iVar8 = iVar8 + 1;

    puVar5 = puVar5 + 0x4a;
  } while (iVar8 < 0xc);

  // erase everything in all pools
  FUN_8003b2d4(param_1);

  // 0x1d7c
  param_1[0x75f] =

	   // track length
	   // gGT -> level -> respawn points[0] -> dist_to_finish
       (uint)*(ushort *)(*(int *)(param_1[0x58] + 0x14c) + 6) *

	   // number of laps * 8
       (int)(char)PTR_DAT_8008d2ac[0x1d33] * 8;

  // MainInit_Drivers
  FUN_8003b6d0(param_1);

  // assume 1P fov
  uVar6 = 1;

  // if you are not in main menu
  if ((*param_1 & 0x2000) == 0)
  {
	// set FOV depending no numPlyrCurrGame (72a*4 = 1ca8)
    uVar6 = (uint)*(byte *)(param_1 + 0x72a);
  }

  // Initialize four PushBuffer, 4 main screens
  FUN_800426f8(param_1 + 0x5a,0,uVar6);
  FUN_800426f8(param_1 + 0x9e,1,uVar6);
  FUN_800426f8(param_1 + 0xe2,2,uVar6);
  FUN_800426f8(param_1 + 0x126,3,uVar6);

  // pointer to PushBuffer_UI
  puVar5 = param_1 + 0x4e2;

  // Initialize PushBuffer
  FUN_800426f8(puVar5,0,1);

  // pushBuffer_UI.offset6
  // rotX = 180 degrees
  *(undefined2 *)((int)param_1 + 0x138e) = 0x800;

  // PushBuffer_SetPsyqGeom
  FUN_80042910(puVar5);

  // PushBuffer_SetMatrixVP
  FUN_80042c04(puVar5);

  // loop counter
  iVar8 = 0;

  // If HUD is enabled
  if ((PTR_DAT_8008d2ac[0x1d31] & 2) != 0)
  {
	// UI_INSTANCE_InitAll
    FUN_8004cec4();
  }

  // offset of 8008d2ac where P1's pushBuffer is
  iVar10 = 0x168;

  // offset of 8008d2ac where P1's camera is
  iVar9 = 0x1498;

  *(undefined4 *)(PTR_DAT_8008d2ac + 0x1cbc) = 2;
  puVar5 = param_1;

  // for iVar8 = 0; iVar8 < 8; iVar8++
  do
  {
	  // get pointer to player structure of each driver
    iVar4 = *(int *)(PTR_DAT_8008d2ac + iVar8 * 4 + 0x24ec);

	// if pointer is not nullptr
    if (iVar4 != 0)
	{
	  // get instance
      iVar7 = *(int *)(iVar4 + 0x1c);

	  // if loop iteration is less than numPlyrCurrGame,
	  // basically: if this driver is a human player
      if (iVar8 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8])
	  {
		// param_1 + iVar9
		// pointer to cameraDC buffer

		// param_1 + iVar10
		// pointer to pushBuffer buffer

		// CAM_Init for all cameras
        FUN_80018818((int)param_1 + iVar9,iVar8,iVar4,(int)param_1 + iVar10);

        if (
				// If not in main menu (character selection, track selection, any part of it)
				((*(uint *)PTR_DAT_8008d2ac & 0x2000) == 0) ||
				(iVar8 < 1)
			)
		{
          // remove frozen camera flag
          uVar6 = puVar5[0x542] & 0xffff7fff;
        }
        else {
          
          // add frozen camera flag
          uVar6 = puVar5[0x542] | 0x8000;
        }
        
        // save flags
        puVar5[0x542] = uVar6;
      }

	  // if instance is valid
      if (iVar7 != 0)
	  {
		// set the scale (x, y, z)
        *(undefined2 *)(iVar7 + 0x1c) = 0xccc;
        *(undefined2 *)(iVar7 + 0x1e) = 0xccc;
        *(undefined2 *)(iVar7 + 0x20) = 0xccc;
      }
    }

	// += 0xDC (next cameraDC)
    puVar5 = puVar5 + 0x37;

	// increment offset to next pushBuffer
    iVar10 = iVar10 + 0x110;

	// increment loop counter
    iVar8 = iVar8 + 1;

	// increment offset to next camera
    iVar9 = iVar9 + 0xdc;

  } while (iVar8 < 8);

  // If Level ID == 39
  // If you are drawing the main menu
  if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x27)
  {
	// set demo countdown timer to 30 seconds
    *(undefined4 *)(PTR_DAT_8008d2ac + 0x1edc) = 900;
  }

  // INSTANCE_LevInitAll
  // copy InstDef to InstancePool
  FUN_80030ad4(*(undefined4 *)(param_1[0x58] + 0x10),*(undefined4 *)(param_1[0x58] + 0xc));

  // Debug_ToggleNormalSpawn == normal spawn
  if (PTR_DAT_8008d2ac[0x253f] != '\0')
  {
	// MainGameStart_Initialize
    FUN_8003aee8(param_1,1);

    if (
			// if you're in Demo Mode
			(PTR_DAT_8008d2ac[0x1d32] != '\0') &&
			(
				// loop iteration counter
				iVar8 = 0,

				// if numPlyrCurrGame is not zero
				PTR_DAT_8008d2ac[0x1ca8] != '\0'
			)
		)
	{
	  // pointer counter (adds 4 each iteration)
      iVar9 = 0;

	  // for(int iVar8 = 0; iVar8 < numPlyrCurrGame; iVar8++)
      do
	  {
		// iterate loop counter
        iVar8 = iVar8 + 1;

		// turn driver into Robotcar
        FUN_80017318(*(undefined4 *)(PTR_DAT_8008d2ac + iVar9 + 0x24ec));

		// increment pointer
        iVar9 = iVar8 * 4;

						// numPlyrCurrGame
      } while (iVar8 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
    }
  }

  // execute all camera thread update functions
  FUN_800715e8(param_1[0x716]);

  // lev -> clearColor rgb
  DAT_8008cff4 = (uint)*(byte *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xd8);
  DAT_8008cff8 = (uint)*(byte *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xd9);
  DAT_8008cffc = (uint)*(byte *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xda);

  // if numPlyrCurrGame is 1
  if (((PTR_DAT_8008d2ac[0x1ca8] == '\x01') &&
      (*(char *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x163) != '\0')) &&
     (*(char *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x167) != '\0'))
  {
	// set isbg of both DBs to false
    PTR_DAT_8008d2ac[0x30] = 0;
    PTR_DAT_8008d2ac[0xd4] = 0;
  }

  else
  {
	// set isbg of both DBs to true
    PTR_DAT_8008d2ac[0x30] = 1;
    PTR_DAT_8008d2ac[0xd4] = 1;
  }

  // gGT->db[0].drawenv.rgb
  PTR_DAT_8008d2ac[0x31] = *(undefined *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xd8);
  PTR_DAT_8008d2ac[0x32] = *(undefined *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xd9);
  PTR_DAT_8008d2ac[0x33] = *(undefined *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xda);

  // gGT->db[1].drawenv.rgb
  PTR_DAT_8008d2ac[0xd5] = *(undefined *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xd8);
  PTR_DAT_8008d2ac[0xd6] = *(undefined *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xd9);
  PTR_DAT_8008d2ac[0xd7] = *(undefined *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xda);

  if (
		// if LEV pointer is valid
		((int *)param_1[0x58] != (int *)0x0) &&

		// If LEV's meshInfo is valid
		(*(int *)param_1[0x58] != 0)
	 )
  {
	// LevInstDef_UnPack
    FUN_8003116c();
  }

  // MainInit_VisMem
  FUN_8003af84(param_1);

  // MainInit_RainBuffer
  FUN_8003b008(param_1);

  // gGT->lev (0x58*4 = 0x160)
  uVar6 = param_1[0x58];

  iVar8 = 3;

  // 0x73b*4 = 0x1CEC
  // animates water, 1P mode
  FUN_8006d79c(

	// gGT->0x1cec
	param_1[0x73b],

	// lev->water_count
	*(undefined4 *)(uVar6 + 0x34),

	// lev->water_ptr
	*(undefined4 *)(uVar6 + 0x38),

	// lev->restart (maskgrab)
	*(undefined4 *)(uVar6 + 0x44),

	*(undefined4 *)(uVar6 + 0x28)
  );

  *(undefined2 *)(param_1 + 0x4e7) = 0x1000;
  *(undefined2 *)((int)param_1 + 0x139e) = 0x200;

  // (72a*4 = 1ca8), numPlyrCurrGame
  bVar1 = *(byte *)(param_1 + 0x72a);

  if (bVar1 == 0) {
    trap(0x1c00);
  }
  if (((uint)bVar1 == 0xffffffff) && ((int)*(short *)(param_1[0x58] + 0x17c) == -0x80000000)) {
    trap(0x1800);
  }

  // number of stars per screen = number of stars in level, divided by number of players
  *(short *)(param_1 + 0x6c3) = (short)((int)*(short *)(param_1[0x58] + 0x17c) / (int)(uint)bVar1);

  // other star-related data
  *(undefined2 *)((int)param_1 + 0x1b0e) = *(undefined2 *)(param_1[0x58] + 0x17e);
  *(undefined2 *)(param_1 + 0x6c4) = *(undefined2 *)(param_1[0x58] + 0x180);
  puVar2 = PTR_DAT_8008d2ac;
  puVar3 = PTR_DAT_8008d2ac + 0xc;
  *(undefined2 *)((int)param_1 + 0x1b12) = *(undefined2 *)(param_1[0x58] + 0x182);

  // erase confetti data
  *(undefined4 *)(puVar2 + 0x1b00) = 0;
  *(undefined2 *)(puVar2 + 0x1b04) = 0;
  *(undefined2 *)(puVar2 + 0x1b06) = 0;

  // confetti VelY is negative, to move downward
  *(undefined4 *)(puVar2 + 0x1b08) = 0xfffffff6;

  // clear array of confetti winners
  do {
    *(undefined4 *)(puVar3 + 0x2558) = 0;
    puVar2 = PTR_DAT_8008d2ac;
    iVar8 = iVar8 + -1;
    puVar3 = puVar3 + -4;
  } while (-1 < iVar8);

  // If you are in a cutscene
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20000000) != 0)
  {
	// CameraDC, freecam mode
    *(undefined2 *)(PTR_DAT_8008d2ac + 0x1532) = 3;

	// disable all HUD flags
    puVar2[0x1d31] = 0;
  }

  // BOTS_EmptyFunc
  FUN_80012560();

  if (
		// If you're in Adventure Arena
		((*(uint *)PTR_DAT_8008d2ac & 0x100000) != 0) &&

		// podium reward
		(*(short *)(PTR_DAT_8008d2ac + 0x2572) != 0)
	  )
  {
	// CS_Podium_FullScene_Init
    FUN_800b0300();
  }

  // If you are in a cutscene
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20000000) != 0)
  {
	// CS_LevCamera_OnInit
    FUN_800b087c();
  }

  // PickupBots_Init
  FUN_80040850();

  return;
}


// Get Level ID from String
int FUN_8003c1d4(char *param_1)
{
  int iVar1;
  undefined *puVar2;
  int iVar3;

  // iteration counter
  iVar3 = 0;

  // array of pointers to strings
  // First pointer goes to "proto8" (dingo canyon)
  // Second pointer goes to "proto9" (dragon mines)
  // etc
  puVar2 = &DAT_80083a80;

  do
  {
	// get length of string
    iVar1 = strlen(*(char **)(puVar2 + 4));

	// compare pointer string to parameter
    iVar1 = strncmp(*(char **)(puVar2 + 4),param_1,iVar1);

	// if you found it
    if (iVar1 == 0)
	{
	  // return iteration, which is Level ID
      return iVar3;
    }

	// keep count of iterations
    iVar3 = iVar3 + 1;

	// go to next pointer
    puVar2 = puVar2 + 0x18;

	// loop 0x40 times (64)
	// there are only 64 levels
  } while (iVar3 < 0x41);

  // If you loop through all 64 and find
  // nothing, return zero as a result
  return 0;
}


// MainInit_VRAMClear
void FUN_8003c248(void)

{
	// Clear the full VRAM (1024x512) to black

#if 0
	// Function is really [this]
	// but in-line makes the
	// disassembly more complex

	RECT r;
    setRECT(&r, 0, 0, 1024, 512);
    ClearImage2(&r, 0,0,0);
	DrawSync(0);
#endif

  DRAWENV DStack128;
  undefined4 local_20;
  undefined local_1c;
  undefined local_1b;
  undefined local_1a;
  undefined local_19;
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  undefined2 local_12;

  SetDefDrawEnv(&DStack128,0,0,0x400,0x200);
  DStack128.dfe = '\x01';
  PutDrawEnv(&DStack128);
  local_19 = 2;
  local_1c = 0;
  local_1b = 0;
  local_1a = 0;
  local_14 = 0x3ff;
  local_12 = 0x1ff;
  local_18 = 0;
  local_16 = 0;
  local_20 = 0x3ffffff;
  DrawOTag(&local_20);
  local_14 = 0x3ff;
  local_12 = 1;
  local_18 = 0;
  local_16 = 0x1ff;
  DrawOTag(&local_20);
  return;
}


// MainInit_VRAMDisplay
void FUN_8003c310(void)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  RECT local_48;
  DR_MOVE local_40;
  short local_28;
  undefined2 local_26;
  short local_20;
  undefined2 local_1e;

  local_28 = 0;
  local_26 = 0x100;
  local_20 = 0;
  local_1e = 0x128;
  iVar4 = 0;
  do {
    iVar1 = 0;
    psVar3 = (short *)((int)&local_28 + ((iVar4 << 0x10) >> 0xf));
    do {
      local_48.y = 0x10c;
      local_48.w = 0x100;
      local_48.h = 0xd8;
      local_48.x = *psVar3 + 0x200;
      SetDrawMove(&local_40,&local_48,(int)*psVar3,
                  (int)*(short *)((int)&local_20 + ((iVar1 << 0x10) >> 0xf)));
      local_40.tag = local_40.tag | 0xffffff;
      DrawOTag(&local_40);
      DrawSync(0);
      iVar1 = iVar1 + 1;
      iVar2 = iVar4 + 1;
    } while (iVar1 * 0x10000 >> 0x10 < 2);
    iVar4 = iVar2;
  } while (iVar2 * 0x10000 >> 0x10 < 2);
  return;
}


// MainKillGame_StopCTR
void FUN_8003c41c(void)
{
  // set callback and save callback
  EnterCriticalSection();
  DrawSyncCallback(DAT_8008d3f8);
  ExitCriticalSection();

  StopCallback();

  // deinitialize memory card
  FUN_8003d95c();

  PadStopCom();
  ResetGraph(3);
  VSyncCallback(0);

  // stop RCnt
  FUN_8004b370();

  return;
}

// Launch Spyro 2 Demo
void FUN_8003c480(void)

{
  // CTR_ErrorScreen
  FUN_80021c94(0,0,0);

  // Music_Stop
  FUN_8002e4ec();

  // howl_StopAudio
  // clear backup, destroy music, destroy all fx
  FUN_8002c8a8(1,1,1);

  // Bank_DestroyAll
  FUN_800298e4();

  // Disable Audio
  FUN_8002ac94();

  VSync(0x1e);

  // end the game
  FUN_8003c41c();

  _96_remove();
  _96_init();

  // http://www.psxdev.net/forum/viewtopic.php?t=516
  // LoadExec("cdrom:\\MAIN.EXE;1", 0x801FFFF0, 0);
  LoadExec("cdrom:\\SPYRO2.EXE;1",(ulong)&DAT_801fff00,0);
  return;
}

// MainLoadVLC_Callback
void FUN_8003c508(void)

{
  // 8008D400, VLC is now loaded
  uGp00000494 = 1;
  
  return;
}

// MainLoadVLC
void FUN_8003c518(void)

{
  int iVar1;

  // VLC is not loaded
  DAT_8008d400 = 0;

  // DAT_8008d09c is the Pointer to "cd position of bigfile"
  iVar1 = *(int *)(DAT_8008d09c + 0xf0c) + 0x7ff;
  if (iVar1 < 0) {
    iVar1 = *(int *)(DAT_8008d09c + 0xf0c) + 0xffe;
  }

  //this one is labeled vlctable, loads some file that looks like array
  //google hints it's something for video decoding?

  // MEMPACK_AllocMem
  DAT_8008d3fc = FUN_8003e874((iVar1 >> 0xb) << 0xb,"VlcTable");

  // This table is passed as parameter to DecDCTvlc2

  // DAT_8008d09c is the Pointer to "cd position of bigfile"
  // '1' for readfile
  FUN_80032d30(DAT_8008d09c,1,0x1e0,DAT_8008d3fc,&FUN_8003c508);
  return;
}


// address 8003c58c
undefined4 main(void)

{
  // clockEffect
  ushort *puVar1;
  
  // AddBitsConfig0
  uint uVar2;
  
  // RemBitsConfig0
  uint uVar3;
  
  // AddBitsConfig8
  uint uVar4;
  
  // RemBitsConfig8
  uint uVar5;
  
  // gGT
  undefined *puVar6;
  
  // gGT or GamepadSystem
  undefined *puVar7;
  
  // checkered flag or loading stage or levID or time
  int iVar8;
  
  // gGT Config0
  uint uVar9;
  
  // gGT Config8
  uint uVar10;
  
  // gGT (duplicate)
  uint *puVar11;
  
  // audio mode, or LNG
  undefined4 uVar12;
  
  undefined auStack40 [8];

  __main();
  do {

	// if game state is 5
    if (DAT_8008d0f4 == 5)
	{
	  // sep3
	  // printf("MAINSTATE_END\n");

	  // end the game
      FUN_8003c41c();

	  // quit
      return 0;
    }

	// LOAD_NextQueuedFile
	// execute loading queue
    FUN_80032dc0();

	// CDSYS_PauseAtEnd
    FUN_8001d06c();

	// determine game state
    switch(DAT_8008d0f4) {

	// Initialize Game (happens once)
    case 0:
      memset(PTR_DAT_8008d2ac,0,0x2584);

	  // Set Video Mode to NTSC
      SetVideoMode(0);

      ResetCallback();

	  // We have 2mb RAM total
      FUN_8003e740(0x200000);

	  // LOAD_InitCD
	  // also sets debug variables to "off"
      FUN_80031c58();

	  // RaceFlag_SetFullyOffScreen
	  // Without this, checkered flag will draw one
	  // frame after the copyright page draws, then
	  // go away once Naughty Dog Box scene is ready
      FUN_80044058();

      ResetGraph(0);
      SetGraphDebug(0);

	  // MainInit_VRAMClear
      FUN_8003c248();

      SetDispMask(1);
      SetDefDrawEnv((DRAWENV *)(PTR_DAT_8008d2ac + 0x18),0,0,0x200,0xd8);
      SetDefDrawEnv((DRAWENV *)(PTR_DAT_8008d2ac + 0xbc),0,0x128,0x200,0xd8);
      SetDefDispEnv((DISPENV *)(PTR_DAT_8008d2ac + 0x74),0,0x128,0x200,0xd8);
      SetDefDispEnv((DISPENV *)(PTR_DAT_8008d2ac + 0x118),0,0,0x200,0xd8);

	  // structure to game modes, cheats, etc
      puVar6 = PTR_DAT_8008d2ac;

	  // db[0].drawEnv.isbg
	  PTR_DAT_8008d2ac[0x30] = 1;

	  // structure to game modes, cheats, etc
      puVar7 = PTR_DAT_8008d2ac;

	  // DispEnv 1 at 8008d2ac + 0x74
      *(undefined2 *)(puVar6 + 0x7c) = 0;
      *(undefined2 *)(puVar6 + 0x7e) = 0xc;
      *(undefined2 *)(puVar6 + 0x80) = 0x100;
      *(undefined2 *)(puVar6 + 0x82) = 0xd8;

	  // DispEnv 2 at 8008d2ac + 0x118
      *(undefined2 *)(puVar6 + 0x120) = 0;
      *(undefined2 *)(puVar6 + 0x122) = 0xc;
      *(undefined2 *)(puVar6 + 0x124) = 0x100;
      *(undefined2 *)(puVar6 + 0x126) = 0xd8;

	  // db[0].drawEnv
	  // r0, g0, b0
      puVar7[0x31] = 0;
      PTR_DAT_8008d2ac[0x32] = 0;
      PTR_DAT_8008d2ac[0x33] = 0;

	  // db[1].drawEnv
	  // isbg, r0, g0, b0
      PTR_DAT_8008d2ac[0xd4] = 1;
      PTR_DAT_8008d2ac[0xd5] = 0;
      PTR_DAT_8008d2ac[0xd6] = 0;
      PTR_DAT_8008d2ac[0xd7] = 0;

	  // structure to game modes, cheats, etc
      puVar6 = PTR_DAT_8008d2ac;

	  // default number of lives in battle,
	  // this is left over from prototypes, useless in retail
	  *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d80) = 5;

	  // 30 second counter?
      *(undefined2 *)(puVar6 + 0x1d52) = 9000;

	  // set lap count to 3
      puVar6[0x1d33] = 3;

	  // structure to game modes, cheats, etc
      puVar7 = PTR_DAT_8008d2ac;

	  // weapons enabled in battle
	  *(uint *)(puVar6 + 0x1da0) = *(uint *)(puVar6 + 0x1da0) | 0x34de;

	  // set numPlyrCurrGame to 1
	  puVar7[0x1ca8] = 1;

	  // set number of players to 1
      PTR_DAT_8008d2ac[0x1ca9] = 1;

	  // structure to game modes, cheats, etc
      puVar6 = PTR_DAT_8008d2ac;

	  // player teams in battle
	  *(undefined4 *)(PTR_DAT_8008d2ac + 0x1da4) = 0x3020100;

	  // traffic light countdown timer, set to negative one second
      *(undefined4 *)(puVar6 + 0x1d0c) = 0xfffffc40;

	  // start rcnt
      FUN_8004b31c();

	  // set callback and save callback
	  EnterCriticalSection();
      DAT_8008d3f8 = DrawSyncCallback(&FUN_80034a80);
	  ExitCriticalSection();

	  // MEMCARD_InitCard
      FUN_8003d7d8();

	  VSync(0);

	  // initialize gamepad systems
      FUN_800251ac(PTR_DAT_8008d2b0);

      VSync(0);

	  // GAMEPAD_GetNumConnected
	  FUN_800255b4(PTR_DAT_8008d2b0);

	  // Get CD Position fo BIGFILE
      DAT_8008d86c = FUN_80031c78("\\BIGFILE.BIG;1");

	  // Load Language
	  // takes 1 as hard-coded parameter for English
	  // PAL SCES02105 has this same function (different name), and calls it multiple times

	  // takes Pointer to "cd position of bigfile"
      FUN_80032b50(DAT_8008d86c,1);

	  // GAMEPROG_NewGame_OnBoot
      FUN_80026e48();

	  // overlayIndex_null_notUsed
      PTR_DAT_8008d2ac[0x2542] = 0;

	  // structure to game modes, cheats, etc
      puVar6 = PTR_DAT_8008d2ac;

	  // set level ID to naughty dog box (0x29 = 41)
	  *(undefined4 *)(PTR_DAT_8008d2ac + 0x1a10) = 0x29;

	  // set level name to "ndi"
      *(undefined4 *)(puVar6 + 0x1a14) = DAT_8008d16c;

	  // initialize geometry

	  // width / 2, and height / 2
      SetGeomOffset(0x100,0x78);

	  // "distance" to screen, alters FOV
      SetGeomScreen(0x140);

	  InitGeom();

	  // RenderBucket_InitDepthGTE
      FUN_8006ae74();

	  // Vector_BakeMatrixTable
      FUN_80057884();

	  // structure to game modes, cheats, etc
      puVar6 = PTR_DAT_8008d2ac;

	  // overlayIndex_EndOfRace
      PTR_DAT_8008d2ac[0x2543] = 0xff;

	  // structure to game modes, cheats, etc
      puVar7 = PTR_DAT_8008d2ac;

	  // swapchainIndex
      *(undefined4 *)(puVar6 + 0xc) = 0;

	  // backBuffer
      *(undefined **)(puVar6 + 0x10) = puVar6 + 0x18;

	  // overlayIndex_LOD
      puVar7[0x2540] = 0xff;

	  // overlayIndex_Threads
      PTR_DAT_8008d2ac[0x2541] = 0xff;

	  PutDispEnv(PTR_DAT_8008d2ac + 0x118);
      PutDrawEnv(PTR_DAT_8008d2ac + 0xbc);
      DrawSync(0);

	  // Load Intro TIM for "SCEA Presents" page from VRAM file
	  // DAT_8008d86c is the Pointer to "cd position of bigfile"
	  // Add a bookmark before loading (param_3 is 0 in the call)
      FUN_80031fdc(DAT_8008d86c,0x1fd,0,auStack40,0xffffffff);

	  // refresh screen during Intro
	  FUN_8003c310();

	  // \SOUNDS\KART.HWL;1
	  // enable audio if not already enabled
      FUN_80029988(s__sounds_kart_hwl_1_80084214);

      VSyncCallback(FUN_80034aa4);

	  // Music_SetIntro
      FUN_8002dd24();

	  // CseqMusic_StopAll
      FUN_80029258();

	  // CseqMusic_Start (no loop at end)
	  FUN_80028c78(0,0,0,0,0);

	  // Music_Start
      FUN_8002e524(0);

	  // CDSYS_XAPlay(CDSYS_XA_TYPE_EXTRA, 0x50);
	  // "Start your engines, for Sony Computer..."
      FUN_8001cdb4(1,0x50);

      // Loop until XA stops playing
      while (DAT_8008d708 != 0)
	  {
		// CDSYS_PauseAtEnd
        FUN_8001d06c();
      }

	  // DecalGlobal_Clear
      FUN_80022b9c(PTR_DAT_8008d2ac);

	  // This loads UI textures (ui_textures.vram)
	  // This includes traffic lights, font, and more
	  // In nopsx VRAM debug viewer:
	  // 	the area between 2 screen buffers and top right corner in vram
	  // DAT_8008d86c is the Pointer to "cd position of bigfile"
	  // Add a bookmark before loading (param_3 is 0 in the call)
      FUN_80031fdc(DAT_8008d86c,0x102,0,auStack40,0xffffffff);

	  // structure to game modes, cheats, etc
      puVar6 = PTR_DAT_8008d2ac;

	  // change game state (in switch statement) to 3
      DAT_8008d0f4 = 3;

	  // set loading state to begin
      DAT_8008d0f8 = 0;

      puVar1 = (ushort *)(PTR_DAT_8008d2ac + 0x2570);

	  // Turn on the "Loading..." flag
      *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | 0x40000000;
      *(ushort *)(puVar6 + 0x2570) = *puVar1 & 0xfffe;
      break;

	// Happens on first frame that loading ends
    case 1:

	  // ElimBG_Deactivate
      FUN_80024c08(PTR_DAT_8008d2ac);

	  // MainStats_RestartRaceCountLoss
      FUN_8003d068();

	  // Voiceline_ClearTimeStamp
      FUN_8002caa8();

	  // structure to game modes, cheats, etc
      puVar6 = PTR_DAT_8008d2ac;

	  // Disable End-Of-Race menu
      *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xffdfffff;

	  // Level ID == 39
	  // Main Menu Level ID
      if (*(int *)(puVar6 + 0x1a10) == 0x27)
	  {
LAB_8003ca68:

		// RaceFlag_IsFullyOffScreen
        iVar8 = FUN_80043f28();
        if (iVar8 != 0)
		{
		  // RaceFlag_SetFullyOnScreen
          FUN_8004402c();
        }
      }

	  // if not main menu
      else
	  {
		// RaceFlag_IsFullyOnScreen
        iVar8 = FUN_80043f1c();

		// if not
        if (iVar8 == 0) {

		  // If Level ID == 39
		  // If you are drawing main menu, set fully on screen
          if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x27) goto LAB_8003ca68;
        }

		// if it is
        else
		{
		  // checkered flag, begin transition off-screen
          FUN_80043fb0(2);
        }
      }
	  
	  // DropRain_Reset
      FUN_8002451c(PTR_DAT_8008d2ac);

	  // GAMEPROG_GetPtrHighScoreTrack
      FUN_80026e80();

	  // initialize all threadBuckets
      FUN_8003b934(PTR_DAT_8008d2ac);

	  // GAMEPAD_GetNumConnected
      FUN_800255b4(PTR_DAT_8008d2b0);

	  // set sound to unpaused
      DAT_8008d8a4 = 0;

	  // VehBirth_EngineAudio_AllPlayers
      FUN_80058ba4();

	  // This is in OnlineCTR
	  // 9 = intro cutscene
	  // 10 = traffic lights
	  // 11 = racing

	  // Arcade-Style track starts with intro cutscene
      uVar12 = 9;

      if (
			// If Level ID is less than 18
			// One of the Arcade tracks
			(*(uint *)(PTR_DAT_8008d2ac + 0x1a10) < 0x12) ||
			(
				// Battle-Style track starts with traffic lights
				uVar12 = 10,

				// Level ID >= 18 and < 23
				// Battle tracks
				*(uint *)(PTR_DAT_8008d2ac + 0x1a10) - 0x12 < 7)
			)
	  {
		// Audio_SetState_Safe
        FUN_8002d4cc(uVar12);
      }

	  // change game state (in switch-statement) to 3
      DAT_8008d0f4 = 3;

      *(ushort *)(PTR_DAT_8008d2ac + 0x2570) = *(ushort *)(PTR_DAT_8008d2ac + 0x2570) & 0xfffe;
      break;

	// Reset stage, reset music
    case 2:

	  // Audio_SetState_Safe
	  // restarts music
      FUN_8002d4cc(1);

	  // MEMPACK_PopState
      FUN_8003e9d0();

	  // LevInstDef_RePack
	  // ignore threads, because we PopState,
	  // so the threadpool will reset anyway
      FUN_80031268(**(undefined4 **)(PTR_DAT_8008d2ac + 0x160),0);

	  // change game state (in switch-statement) to 1
      DAT_8008d0f4 = 1;
      break;

	// Main Gameplay Update
	// Makes up all normal interaction with the game
    case 3:

	  // if loading is not finished
      if (DAT_8008d0f8 != -1)
	  {
		// RaceFlag_IsFullyOnScreen
        iVar8 = FUN_80043f1c();

        if (
			(
				// wait for flag to be fully on-screen
				// before starting to load the game
				(iVar8 == 1) ||

				// If Level ID is Naughty Dog Box
				(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x29)
			) || (DAT_8008d036 != 0)
		   )
        {
		  // Turn on the "Loading..." flag
          *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | 0x40000000;
        }

	    // structure to game modes, cheats, etc
        puVar11 = (uint *)PTR_DAT_8008d2ac;

		// get loading stage
        iVar8 = DAT_8008d0f8;

		// elapsed milliseconds per frame, locked 32 here,
		// impacts speed of flag wave during "loading...",
		// but does not impact speed of flying text
        *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d04) = 0x20;

		// if loading is finished, but still in
		// "loading mode", and if pools dont need
		// to be reset (maybe for credits?)
        if (iVar8 == -5)
		{
		  // RaceFlag_IsFullyOnScreen
          iVar8 = FUN_80043f1c();
          if (iVar8 == 1)
		  {
			// set game state to 2,
			// to initialize the world,
			// does not initialize pools
            DAT_8008d0f4 = 2;

			// nothing is being loaded anymore
            DAT_8008d0f8 = -1;

			// Turn off the "Loading..." flag
            *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xbfffffff;
            break;
          }
        }

		// if something is being loaded
        else
		{
		  // if not waiting for checkered flag to cover screen
          if (iVar8 != -4)
		  {
			// if loading VLC
            if (iVar8 == -6) 
			{
			  // if VLC is not loaded, quit.
			  // we know when it's done from a load callback
              if (DAT_8008d400 != 1) break;
            }
			
            else
			{
			  // DAT_8008d86c is the Pointer to "cd position of bigfile"
              DAT_8008d0f8 = FUN_80033610(puVar11,iVar8,DAT_8008d86c);
			  
			  // if did not just complete loading stage 9, skip logic to 
			  // load VLC, skip logic to end loading, skip logic if "if == -4",
			  // goto rendering. We can skip rendering by changing BNE on 
			  // 0x8003cca0 to "bne v0, v1, 8003cf3c"
              if (DAT_8008d0f8 != -2) goto LAB_8003ccf8;

			  // if stage 9 of loading was just finished

              if (
					// If Level ID is 39
					// If you're in main menu
					(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x27) ||

					(
						puVar11 = (uint *)PTR_DAT_8008d2ac,

						// If Level ID == 64
						// Scrapbook
						*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x40
					)
				 )
              {
				// MainLoadVLC
                FUN_8003c518();

				// start loading VLC (scroll up to iVar8 == -6)
                DAT_8008d0f8 = -6;
				
				// go back to start of main() loop
				// "j LAB_8003cf3c"
                break;
              }
            }

			// loading is finished
            DAT_8008d0f8 = -1;

			// set game state to 1, to initialize world,
			// as well as initialize all pools
            DAT_8008d0f4 = 1;

			// remove "Loading..." flag from gGT
			*puVar11 = *puVar11 & 0xbfffffff;
			
			// go back to start of main() loop,
			// "j LAB_8003cf3c"
            break;
          }
		  
		  // if == -4, if waiting for checkered flag

		  // RaceFlag_IsFullyOnScreen
          iVar8 = FUN_80043f1c();

		  // Get address of GameTracker
          puVar6 = PTR_DAT_8008d2ac;

		  // before loading starts,
		  // remove this from gGT + 8
          uVar5 = DAT_8008d10c;

		  // before loading starts,
		  // add this from gGT + 8
          uVar4 = DAT_8008d108;

		  // before loading starts, 
		  // remove this from gGT + 0
          uVar3 = DAT_8008d104;

		  // before loading starts, 
		  // add this from gGT + 0
          uVar2 = DAT_8008d100;

		  // wait for flag to be fully on-screen
          if (iVar8 == 1)
		  {
			// reset the four variables
            DAT_8008d100 = 0;
            DAT_8008d104 = 0;
            DAT_8008d108 = 0;
            DAT_8008d10c = 0;

			// Get current gGT + 8
            uVar10 = *(uint *)(PTR_DAT_8008d2ac + 8);

            PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xf7;

			// get lev ID being loaded
			iVar8 = (int)DAT_8008d0fc;

			// Get current gGT + 0
            uVar9 = *(uint *)puVar6;

			// Make all desired changes
            *(uint *)(puVar6 + 8) = uVar10 | uVar4;
            *(uint *)puVar6 = uVar9 | uVar2;
            *(uint *)puVar6 = (uVar9 | uVar2) & ~uVar3;
            *(uint *)(puVar6 + 8) = (uVar10 | uVar4) & ~uVar5;

			// start loading (generic)
			FUN_8003cf7c(iVar8);
          }

		  // if not fully on screen
          else
		  {
			// RaceFlag_IsFullyOffScreen
            iVar8 = FUN_80043f28();
            if (iVar8 == 1)
			{
			  // checkered flag, begin transition on-screen
              FUN_80043fb0(1);
            }
          }
        }
      }
LAB_8003ccf8:
      puVar6 = PTR_DAT_8008d2ac;
      if (
			(
				// Check value of traffic lights
				(-0x3c0 < *(int *)(PTR_DAT_8008d2ac + 0x1d0c)) &&

				// if not drawing intro race cutscene and if not paused
				((*(uint *)PTR_DAT_8008d2ac & 0x4f) == 0)
			) &&

			(
				// amount of milliseconds on Traffic Lights - elapsed milliseconds per frame, ~32
				iVar8 = *(int *)(PTR_DAT_8008d2ac + 0x1d0c) - *(int *)(PTR_DAT_8008d2ac + 0x1d04),

				// decrease amount of time on Traffic Lights
				*(int *)(PTR_DAT_8008d2ac + 0x1d0c) = iVar8,

				// if countdown has gone down far enough
				// for traffic lights to go off-screen
				iVar8 < -0x3c0
			)
		 )
	  {
		// set a floor value, so countdown can't go farther negative
        *(undefined4 *)(puVar6 + 0x1d0c) = 0xfffffc40;
      }

	  // frame counter
      DAT_8008d970 = DAT_8008d970 + 1;

	  // GAMEPAD_ProcessAnyoneVars
      FUN_800262d0(PTR_DAT_8008d2b0);

	  // MainFrame_ResetDB (ClearOTagR)
      FUN_80034bbc(PTR_DAT_8008d2ac,PTR_DAT_8008d2b0);

      if (
			// If you're in Demo Mode
			(PTR_DAT_8008d2ac[0x1d32] != '\0') &&

			// Turn off HUD
			(PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xfe,

			// main struct used for [0x1d32]
			puVar6 = PTR_DAT_8008d2ac,

			// if game is not loading
			DAT_8008d0f8 == -1)
		 )
	  {
		// All this code is for the 30-second timer within Demo Mode,
		// To see 30-second timer in Main Menu, go to FUN_00001604 in 230.c

		// 0x1edc is a countdown the timer
		// pressing (or holding) any button sets it to zero

		// Get the current value of the countdown timer
        iVar8 = *(int *)(PTR_DAT_8008d2ac + 0x1edc);

		// subtract one frame
        *(int *)(PTR_DAT_8008d2ac + 0x1edc) = iVar8 + -1;

		// check to see if time ran out
        if (iVar8 + -1 < 1)
		{
		  // leave demo mode
          puVar6[0x1d32] = 0;

		  // set number of players to 1
          PTR_DAT_8008d2ac[0x1ca9] = 1;

		  // go to main menu
          DAT_8008d97c = 0;
LAB_8003ce08:
			// load LEV of main menu
          FUN_8003cfc0(0x27);
        }

		// if time remains on the timer
        else {

		  // if any button is pressed by anyone
          if (*(int *)(PTR_DAT_8008d2b0 + 0x290) != 0)
		  {
			// leave demo mode
            puVar6[0x1d32] = 0;

            goto LAB_8003ce08;
          }
        }

		// if numPlyrCurrGame is 1
        if (PTR_DAT_8008d2ac[0x1ca8] == '\x01')
		{
		  // Draw text near top of screen
          uVar12 = 0x23;
        }

		// if this is multiplayer
        else
		{
		  // draw text halfway to top of screen
          uVar12 = 100;
        }

		// DAT_8008d878 + 0x8c0
		// DEMO MODE\rPRESS ANY BUTTON TO EXIT

		// DecalFont_DrawMultiLine
        FUN_80022b34(*(undefined4 *)(DAT_8008d878 + 0x8c0),0x100,uVar12,0x200,2,0xffff8000);
      }

	  // If you are not in a loading screen
      if ((*(uint *)PTR_DAT_8008d2ac & 0x40000000) == 0)
	  {
		// MainFrame_GameLogic
        FUN_80034d54(PTR_DAT_8008d2ac,PTR_DAT_8008d2b0);
      }

	  // If you are in demo mode
      if (PTR_DAT_8008d2ac[0x1d32] != '\0')
	  {
		// Turn off HUD
        PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xfe;
      }

	  // gamepad input structure
      puVar7 = PTR_DAT_8008d2b0;

	  // game state structure
      puVar6 = PTR_DAT_8008d2ac;

	  // reset vsync calls between drawsync
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1ce0) = 0;

	  // MainFrame_RenderFrame
      FUN_80035e70(puVar6,puVar7);

	  // if mask is talking in Adventure Hub
      if (DAT_8008d888 != 0)
	  {
		// AH_MaskHint_Update
        FUN_800b4470();
      }
      break;

	// In theory, this is left over from the demos,
	// which would "timeout" and restart after sitting idle
    case 4:

	  // sep3
	  // printf("MAINSTATE_EXIT\n");

	  // erase all data past the
	  // last 3 bookmarks, if there
	  // that many exist

	  // MEMPACK_PopState x3
      FUN_8003e9d0();
      FUN_8003e9d0();
      FUN_8003e9d0();

	  // CTR_ErrorScreen
      FUN_80021c94(0,0,0);

	  // Music_Stop
      FUN_8002e4ec();

	  // howl_StopAudio
	  // clear backup, destroy music, destroy all fx
      FUN_8002c8a8(1,1,1);

	  // Bank_DestroyAll
      FUN_800298e4();

	  // Disable Audio
      FUN_8002ac94();

	  // GAMEPAD_SetMainMode,
	  // param1 is gGamepads
      FUN_80025208(PTR_DAT_8008d2b0);

	  // Set vsync to 2 FPS
      VSync(0x1e);

	  // set game state to zero
      DAT_8008d0f4 = 0;

	  // Notice how there is no "break"
	  // That means the switch-statement repeats
	  // and the game goes back to state 0, to
	  // initialize all over again
    }
  } while( true );
}


// MainRaceTrack_StartLoad
void FUN_8003cf7c(short param_1)

{
  // howl_StopAudio
  // clear backup,
  // keep music,
  // destroy "most" fx, let menu fx play to end
  FUN_8002c8a8(1,0,0);

  // ElimBG_Deactivate
  FUN_80024c08(PTR_DAT_8008d2ac);

  // LOAD_LevelFile
  FUN_80034874((int)param_1);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// MainRaceTrack_RequestLoad
void FUN_8003cfc0(short param_1)

{
  int iVar1;

  // Turn off HUD
  PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xfe;

  // RaceFlag_IsFullyOffScreen
  iVar1 = FUN_80043f28();

  if (iVar1 == 1)
  {
	// checkered flag, begin transition on-screen
    FUN_80043fb0(1);
  }

  // RaceFlag_ResetTextAnim
  FUN_80044290();

  // loading stage = -4 (waiting for checkered flag)
  DAT_8008d0f8 = -4;

  // set LEV to load
  _DAT_8008d0fc = (int)param_1;

  return;
}

// MainStats_ClearBattleVS
void FUN_8003d024(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  iVar4 = 0;
  iVar3 = 0;

  // loop for 4 players
  do {
    iVar2 = 0;
    iVar1 = iVar3;

	// loop for 3 positions (1st, 2nd, 3rd)
    do
	{
	  // gp->340 = 8008d2ac
	  // gGT->1e80 = standingsPoints
      *(undefined4 *)(iGp00000340 + iVar1 + 0x1e80) = 0;
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 4;
    } while (iVar2 < 3);
    iVar4 = iVar4 + 1;
    iVar3 = iVar3 + 0xc;
  } while (iVar4 < 4);
  return;
}


// MainStats_RestartRaceCountLoss
void FUN_8003d068(void)

{
  char cVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;

  // loop counter
  uint uVar7;
  uVar7 = 0;

  // Turn off HUD
  PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xfe;

  puVar2 = PTR_DAT_8008d2ac;
  puVar6 = PTR_DAT_8008d2ac;

  // for iVar7 = 0; iVar7 < 4; iVar7++
  do
  {
	// if someone is on this battle team
    if ((*(uint *)(puVar2 + 0x1dd8) & 1 << (uVar7 & 0x1f)) == 0)
	{
	  // -500
	  // team points
      *(undefined4 *)(puVar6 + 0x1d90) = 0xfffffe0c;
    }

    else
	{
	  // erase team points
      *(undefined4 *)(puVar6 + 0x1d90) = 0;
    }
    puVar3 = PTR_DAT_8008d2ac;

	// increment loop counter
    uVar7 = uVar7 + 1;

    puVar6 = puVar6 + 4;

  } while ((int)uVar7 < 4);

  // TurboDisplayPos_Only1P
  DAT_8008d2a8 = 0;
  
  // reset number of drivers who finished the race
  DAT_8008d2aa = 0;

  // no winners, nobody gets confetti
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x2568) = 0;

  *(undefined4 *)(puVar3 + 0x1e28) = 0;	// numCrystalsInLEV
  *(undefined4 *)(puVar3 + 0x1e2c) = 0; // timeCratesInLEV
  *(undefined4 *)(puVar3 + 0x1d44) = 0;
  *(undefined4 *)(puVar3 + 0x1e20) = 0; // frozenTimeRemaining
  *(undefined4 *)(puVar3 + 0x1ec0) = 0; // zero missiles in play
  *(undefined4 *)(puVar3 + 0x1ec4) = 0; // zero players with 3 missiles


  uVar7 = *(uint *)PTR_DAT_8008d2ac;


  // If you're not in Adventure Mode
  if ((uVar7 & 0x80000) == 0) {
    return;
  }

  // if the lap you're on is not the 3rd lap,
  // then it means you just loaded track, and did not hit "Restart"
  if (*(char *)(*(int *)(puVar3 + 0x24ec) + 0x44) != '\x02') {
    return;
  }

  // If you're in Adventure Cup or Relic
  if ((uVar7 & 0x14000000) != 0) {
    return;
  }

  // if you're in boss mode
  if ((int)uVar7 < 0)
  {
	// bossID 0-5
    iVar4 = *(int *)(puVar3 + 0x1eb8);

	// pointer to somewhere random,
	// assembly is generated with pointers to
	// random places when accessing global variables,
	// there is no significance to this address
	iVar5 = iVar4 + -0x7ff70445; // 0x8008FBBB

	// get number of times lost boss race
    cVar1 = (&DAT_8008fbeb)[iVar4];

	// if you lost less than 10 times, increment counter
    if ((char)(&DAT_8008fbeb)[iVar4] < '\n') goto LAB_8003d178;
  }

  // Level ID
  iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);

  // 0x8fba4 is where the adventure profile (currently loaded) begins
  iVar5 = (int)&DAT_8008fba4 + iVar4;

  // get number of times lost this race
  cVar1 = (&DAT_8008fbd4)[iVar4];

  // if you lost more than 10 times, quit
  if ('\t' < (char)(&DAT_8008fbd4)[iVar4]) {
    return;
  }

LAB_8003d178:

  // increment number of times lost this event
  *(char *)(iVar5 + 0x30) = cVar1 + '\x01';
  return;
}
