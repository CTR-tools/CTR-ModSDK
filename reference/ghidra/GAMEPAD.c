
// GAMEPAD_Init
void FUN_800251ac(int param_1)

{
  int iVar1;
  int iVar2;

  // PS/psx/sample/pad/anlgctrl/main.c
  // shows the parameters are simply
  // gGamepads->slotBuffer
  PadInitMtap(param_1 + 0x2d0,param_1 + 0x2f2);
  PadStartCom();

  // loop counter
  iVar2 = 0;

  iVar1 = param_1;

  // for iVar2 = 0; iVar2 < 8; iVar2++
  do
  {
	// no analog sticks detected
    *(undefined2 *)(iVar1 + 0x26) = 0;

    *(undefined *)(iVar1 + 0x44) = 0;

	// increment loop counter
    iVar2 = iVar2 + 1;

	// increment 0x50 bytes to next gamepad
    iVar1 = iVar1 + 0x50;

  } while (iVar2 < 8);

  *(undefined4 *)(param_1 + 0x318) = 0xffffffff;
  return;
}


// GAMEPAD_SetMainMode
void FUN_80025208(void)

{
  PadSetMainMode(0,0,0);
  PadSetMainMode(1,0,0);
  PadSetMainMode(2,0,0);
  PadSetMainMode(3,0,0);
  PadSetMainMode(0x10,0,0);
  PadSetMainMode(0x11,0,0);
  PadSetMainMode(0x12,0,0);
  PadSetMainMode(0x13,0,0);
  return;
}


// param1 is gamepadBuffer
// param2 is PadGetState
// param3 is gamepadID

// GAMEPAD_ProcessState
void FUN_800252a0(int param_1,int param_2,undefined4 param_3)

{
  undefined uVar1;
  int iVar2;
  int iVar3;

  if (param_2 == 2) {
    *(undefined *)(param_1 + 0x2c) = 0;
    *(undefined *)(param_1 + 0x2d) = 0;
  }
  else {
    if (param_2 < 3) {
      if ((param_2 == 1) && (*(short *)(param_1 + 0x26) != 0)) {
        *(undefined2 *)(param_1 + 0x26) = 1;
      }
    }
    else {
      if (param_2 == 6) 
	  {
		// gamepadType
        if (*(short *)(param_1 + 0x26) == 0) 
		{
          iVar2 = PadSetMainMode(param_3,1,0);
          if (iVar2 != 0) {
            *(undefined2 *)(param_1 + 0x26) = 1;
          }
        }
        else 
		{
		  // gamepadType
          if (*(short *)(param_1 + 0x26) == 1) 
		  {
            iVar2 = PadInfoAct(param_3,0xffffffff,0);
            if (2 < iVar2) {
              iVar2 = 2;
            }
            iVar3 = 0;
            if (0 < iVar2) {
              do {
                uVar1 = PadInfoAct(param_3,iVar3,4);
                *(undefined *)(param_1 + iVar3 + 0x2c) = uVar1;
                iVar3 = iVar3 + 1;
              } while (iVar3 < iVar2);
            }
            while (iVar2 < 2) {
              *(undefined *)(param_1 + iVar2 + 0x2c) = 0;
              iVar2 = iVar2 + 1;
            }

			// gamepad rumble
            PadSetAct(param_3,param_1 + 0x2e,2);

			iVar2 = PadSetActAlign(param_3,&DAT_8008d038);

			if (iVar2 != 0) {
              *(undefined2 *)(param_1 + 0x26) = 2;
            }
          }
        }
      }
    }
  }
  return;
}

// GAMEPAD_PollVsync
void FUN_80025410(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int local_40;
  int local_3c;

  iVar7 = 0;

  // number of ports that gameplay cares about,
  // 2 by default, no multitaps, 2 gamepads
  local_40 = 2;

  // number of gamepads per gamepad port,
  // set to 1 if there is no multitap (default)
  local_3c = 1;

  // If there is a multitap present
  if ((*(char *)(param_1 + 0x2d0) == '\0') && (*(char *)(param_1 + 0x2d1) == -0x80))
  {
	// Gameplay now only cares about one gamepad port,
	// Port 1, which has the multitap. However, the gamepad
	// system still processes input for port 2, Gameshark can
	// be programmed with button input from all 8 gamepads
    local_40 = 1;

	// There can now be 4 gamepads in one port
    local_3c = 4;
  }

  // loop counter
  iVar9 = 0;

  // If there are gamepad ports that
  // gameplay cares about (always > 0)
  if (local_40 != 0)
  {
    iVar10 = 0x2d0;

	// loop through all gamepad ports
	// that gameplay cares about. Either
	// 1 or 2, main ports on console
	do
	{
	  // loop counter
      uVar5 = 0;

	  // if max number of gamepad ports is not zero,
	  // which will always be true no matter what
      if (local_3c != 0)
	  {
        iVar8 = 2;

		// Get byte-offset of each gamepad within structure
        iVar6 = iVar7 * 0x50 + param_1;

        // loop through all gamepads that can connect
		// to this gamepad port. 1 for no mtap, 4 for mtap
        do
		{
          // padBuff
          pcVar3 = (char *)(param_1 + iVar10);

		  if (
				(
                    // if this is not a multitap,
                    // skip next block, and just start
                    // if-body with ptrPadBuff
					(pcVar3[1] == -0x80) &&

                    // assuming this is a multitap
					(
						cVar1 = *pcVar3,

                        // increment ptrPadBuff to offset
						pcVar3 = pcVar3 + iVar8,

						cVar1 != '\0'
					)
				) ||
				(*pcVar3 != '\0'))
		  {
			// no analog sticks found
            *(undefined2 *)(iVar6 + 0x26) = 0;
          }

          else
		  {
            uVar4 = (iVar9 << 4) | uVar5;

			// according to libref
			// 0 - PadStateDisCon
			// 1 - PadStateFindPad
			// and many more...
            uVar2 = PadGetState(uVar4);
			
			// GAMEPAD_ProcessState
            FUN_800252a0(iVar6,uVar2,uVar4);
          }

		  // increment offset to next gamepad
          iVar6 = iVar6 + 0x50;

		  // increment gamepad counter
          iVar7 = iVar7 + 1;

		  // increment loop counter
          uVar5 = uVar5 + 1;

          iVar8 = iVar8 + 8;
        } while ((int)uVar5 < local_3c);
      }

	  // increment loop counter
      iVar9 = iVar9 + 1;
      iVar10 = iVar10 + 0x22;
    } while (iVar9 < local_40);
  }

  // if there are less than 8 gamepads connected,
  // write to buffers of all Unplugged gamepads
  if (iVar7 < 8)
  {
    // Get byte-offset of each gamepad within structure
    param_1 = iVar7 * 0x50 + param_1;

	// iVar7 = lastGamepad; iVar7 < 8; iVar7++
	do
	{
	  // no analog sticks found
      *(undefined2 *)(param_1 + 0x26) = 0;

	  // increment loop counter
      iVar7 = iVar7 + 1;

	  // increment offset to next gamepad
      param_1 = param_1 + 0x50;

    } while (iVar7 < 8);
  }
  return;
}


// get number of gamepads connected

// GAMEPAD_GetNumConnected
uint FUN_800255b4(int param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;

  // gamepads connected (by flags)
  uVar9 = 0;

  // number of gamepads connected
  iVar6 = 0;

  // number of ports that gameplay cares about,
  // 2 by default, no multitaps, 2 gamepads
  iVar12 = 2;

  // number of gamepads per gamepad port,
  // set to 1 if there is no multitap (default)
  iVar11 = 1;

  // Set number of gamepads plugged to zero,
  // we will recount the current amount soon
  *(undefined4 *)(param_1 + 0x314) = 0;

  // If there is a multitap present
  if ((*(char *)(param_1 + 0x2d0) == '\0') && (*(char *)(param_1 + 0x2d1) == -0x80))
  {
	// Gameplay now only cares about one gamepad port,
	// Port 1, which has the multitap. However, the gamepad
	// system still processes input for port 2, Gameshark can
	// be programmed with button input from all 8 gamepads
    iVar12 = 1;

	// There can now be 4 gamepads in one port
    iVar11 = 4;
  }

  // loop counter
  iVar8 = 0;

  // If there are gamepad ports that
  // gameplay cares about (always > 0)
  if (iVar12 != 0)
  {
    iVar10 = 0x2d0;

	// loop through all gamepad ports
	// that gameplay cares about. Either
	// 1 or 2, main ports on console
    do
	{
	  // loop counter
      iVar4 = 0;

	  // if max number of gamepad ports is not zero,
	  // which will always be true no matter what
      if (iVar11 != 0)
	  {
		// byte offset into padBuff
        iVar7 = 2;

		// Get byte-offset of each gamepad within structure
        iVar5 = iVar6 * 0x50 + param_1;

		// loop through all gamepads that can connect
		// to this gamepad port. 1 for no mtap, 4 for mtap
        do
		{
		  // pointer to padBuff for this port
          pcVar2 = (char *)(param_1 + iVar10);

		  // if gamepad is connected
          if (
				(
					// if this is not a multitap,
					// skip next block, and just start
					// if-body with ptrPadBuff
					(pcVar2[1] != -0x80) ||

					(
						cVar1 = *pcVar2,
						pcVar2 = pcVar2 + iVar7,
						cVar1 == '\0'
					)
				) &&
				(*pcVar2 == '\0')
			 )
		 {
			// write flag that shows which gamepad is connected
            uVar9 = uVar9 | 1 << (iVar8 * 4 + iVar4 & 0x1fU);

			// set the "current" number of connected gamepads,
			// this will continue to overwrite until loop finishes,
			// so "current" will be the total amount in the end
            *(int *)(param_1 + 0x314) = iVar6 + 1;

            *(char **)(iVar5 + 0x20) = pcVar2;
            *(short *)(iVar5 + 0x24) = (short)iVar8 * 0x10 + (short)iVar4;
          }

		  // increment offset to next gamepad
          iVar5 = iVar5 + 0x50;

		  // increment gamepad counter
          iVar6 = iVar6 + 1;

		  // increment loop counter
          iVar4 = iVar4 + 1;

          iVar7 = iVar7 + 8;
        } while (iVar4 < iVar11);
      }

	  // increment loop counter
      iVar8 = iVar8 + 1;
      iVar10 = iVar10 + 0x22;
    } while (iVar8 < iVar12);
  }

  // write to buffers of all Unplugged gamepads

  // if there are less than 8 gamepads connected
  if (iVar6 < 8)
  {
	// Get byte-offset of each gamepad within structure
    iVar11 = iVar6 * 0x50 + param_1;

	// iVar6 = lastGamepad; iVar6 < 8; iVar6++
    do
	{
	  // This gamepad is now Unplugged
      *(undefined4 *)(iVar11 + 0x20) = 0;

	  // increment loop counter
      iVar6 = iVar6 + 1;

	  // increment offset to next gamepad
      iVar11 = iVar11 + 0x50;

    } while (iVar6 < 8);
  }

  // get the number of gamepads from last frame
  uVar3 = *(uint *)(param_1 + 0x318);

  // if this is the first time this function has run
  if (uVar3 == 0xffffffff)
  {
	// set the number of gamepads found in this function
    *(uint *)(param_1 + 0x318) = uVar9;
  }

  // if this function has executed before
  else
  {
	// if the number of gamepads changed since last frame
    if (uVar9 != uVar3)
	{
	  // set the number of gamepads found in this function
      *(uint *)(param_1 + 0x318) = uVar9;

	  // return the change
      return (uint)(((uVar9 ^ uVar3) & uVar3) != 0);
    }
  }

  // assume no change in amount of gamepads connected
  return 0;
}

// determine which buttons are held this frame,
// store a backup of "currFrame" into "lastFrame"
// param1 is pointer to gamepadSystem

// GAMEPAD_ProcessHold
void FUN_80025718(int param_1)

{
  uint uVar1;
  uint *puVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;

  uVar7 = 0;

  // loop counter
  iVar6 = 0;

  // loop through all 8 gamepadBuffers
  // for iVar6 = 0; iVar6 < 8; iVar6++
  do {

	// pointer to 8 bytes?
	pcVar3 = *(char **)(param_1 + 0x20);

	// buttonHeldPrevFrame = buttonHeldCurrFrame
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x10);

	// if pointer is invalid
    if (pcVar3 == (char *)0x0)
	{
	  // erase buttons held this frame and prev
      *(undefined4 *)(param_1 + 0x10) = 0;
      *(undefined4 *)(param_1 + 0x1c) = 0;
    }

	// if pointer is valid
    else {
      if (*pcVar3 == '\0') 
	  {
		// endian flip
        uVar4 = (uint)CONCAT11(pcVar3[2],pcVar3[3]) ^ 0xffff;
        uVar5 = 0;

		// If this is madcatz racing wheel
        if (pcVar3[1] == '#') {
          if (0x40 < (byte)pcVar3[5]) {
            uVar4 = uVar4 | 0x40;
          }
          if (0x40 < (byte)pcVar3[6]) {
            uVar4 = uVar4 | 0x80;
          }
          if (0x40 < (byte)pcVar3[7]) {
            uVar4 = uVar4 | 4;
          }
        }

		// If this is not madcatz racing wheel
        else
		{
		  // If this is ANAJ
		  // could be different from NPC-105
		  // could just be different sensitivity, or gamepad signal
          if (pcVar3[1] == 'S') {
            uVar4 = uVar4 << 0x10;
          }
        }
		
		// gamepadMapBtn to map RawInput enum
		// to Buttons enum, to support different
		// types of controllers
        puVar2 = &DAT_800824a8;
        uVar1 = DAT_800824a8;
        while (uVar1 != 0) {
          if ((uVar4 & uVar1) != 0) {
            uVar5 = uVar5 | puVar2[1];
          }
          puVar2 = puVar2 + 2;
          uVar1 = *puVar2;
        }

		// record buttons held this frame
        *(uint *)(param_1 + 0x10) = uVar5;

		// if nothing was held
        if (uVar5 == 0)
		{
		  // if you are not at risk of overflow
          if (*(ushort *)(param_1 + 0x28) < 65000)
		  {
			// count time number of frames since last input
            *(short *)(param_1 + 0x28) = *(ushort *)(param_1 + 0x28) + 1;
          }
        }

		// if buttons were pressed
        else
		{
		  // reset number of frames since last input
          *(undefined2 *)(param_1 + 0x28) = 0;
        }

        uVar7 = uVar7 | uVar5;
      }
    }

	// increment loop counter
    iVar6 = iVar6 + 1;

	// next gamepadBuffer
    param_1 = param_1 + 0x50;

  } while (iVar6 < 8);
}


// handle mapping of D-Pad and
// analog stick values onto each other

// GAMEPAD_ProcessSticks
// param_1 = PTR_DAT_8008d2b0
void FUN_80025854(int param_1)
{
  byte bVar1;
  bool bVar2;
  undefined2 uVar3;
  int iVar4;
  undefined uVar5;
  char *pcVar6;
  int iVar7;
  short sVar8;
  undefined4 *puVar9;
  int iVar10;

  iVar10 = 0;

  // racing wheel data
  puVar9 = &DAT_800841fc;

  do {

	pcVar6 = *(char **)(param_1 + 0x20);

	*(undefined4 *)(param_1 + 0x4c) = 0;

	// if pointer is invalid
	if (pcVar6 == (char *)0x0)
	{
	  // reset all joystick values to "center"
      *(undefined2 *)(param_1 + 8) = 0x80;
      *(undefined2 *)(param_1 + 10) = 0x80;
      *(undefined2 *)(param_1 + 0xc) = 0x80;
      *(undefined2 *)(param_1 + 0xe) = 0x80;
      *(undefined2 *)(param_1 + 4) = 0x80;
      *(undefined2 *)(param_1 + 6) = 0x80;
    }

	// if pointer is valid
    else
	{
      if (*pcVar6 == '\0') {
        bVar1 = pcVar6[1];
		
		// PAD_ID_ANALOG_STICK
        if (bVar1 == 0x53) 
		{
LAB_80025998:
          *(ushort *)(param_1 + 8) = (ushort)*(byte *)(*(int *)(param_1 + 0x20) + 6);
          bVar1 = *(byte *)(*(int *)(param_1 + 0x20) + 7);
          if ((bVar1 == 0xff) && ((int)*(short *)(param_1 + 2) != (uint)bVar1)) {
            *(undefined2 *)(param_1 + 10) = *(undefined2 *)(param_1 + 2);
          }
          else {
            *(ushort *)(param_1 + 10) = (ushort)bVar1;
          }
          *(ushort *)(param_1 + 2) = (ushort)bVar1;
          *(ushort *)(param_1 + 0xc) = (ushort)*(byte *)(*(int *)(param_1 + 0x20) + 4);
          *(ushort *)(param_1 + 0xe) = (ushort)*(byte *)(*(int *)(param_1 + 0x20) + 5);
        }
        else {
          if (bVar1 < 0x54) 
		  {
			// PAD_ID_NEGCON
            if (bVar1 == 0x23) {
              if (iVar10 < 4)
			  {
				// racingwheel data
                *(undefined4 **)(param_1 + 0x4c) = puVar9;
              }
              bVar1 = *(byte *)(*(int *)(param_1 + 0x20) + 4);
              *(undefined2 *)(param_1 + 10) = 0x80;
              *(undefined2 *)(param_1 + 0xc) = 0x80;
              *(undefined2 *)(param_1 + 0xe) = 0x80;
              *(ushort *)(param_1 + 8) = (ushort)bVar1;
              goto LAB_80025a0c;
            }
            *(undefined2 *)(param_1 + 8) = 0x80;
          }
          else 
		  {
			// PAD_ID_ANALOG
            if (bVar1 == 0x73) goto LAB_80025998;
			
			// PAD_ID_JOGCON
            if (bVar1 != 0xe3) {
              *(undefined2 *)(param_1 + 8) = 0x80;
              goto LAB_80025a00;
            }
			
			// === PAD_ID_JOGCON ===
			
            if (iVar10 < 4)
			{
			  // racingwheel data
              *(undefined4 **)(param_1 + 0x4c) = puVar9;
            }
            
			sVar8 = *(short *)(*(int *)(param_1 + 0x20) + 4);
            iVar4 = (int)sVar8;
			
            if (iVar4 < 0) 
			{
              iVar7 = ((-10 - iVar4) - (int)*(short *)(puVar9 + 1)) * 8;
              uVar5 = (undefined)iVar7;
			  
              if (iVar7 < 0) {
                uVar5 = 0;
              }
              if (0xff < iVar7) {
                uVar5 = 0xff;
              }
              
			  sVar8 = sVar8 + 0x80;
              if (iVar4 < -0x80) {
                sVar8 = -0x80;
LAB_8002595c:
                sVar8 = sVar8 + 0x80;
              }
            }
            
			else 
			{
              iVar7 = ((iVar4 + -10) - (int)*(short *)(puVar9 + 1)) * 8;
              uVar5 = (undefined)iVar7;
              
			  if (iVar7 < 0) {
                uVar5 = 0;
              }
              if (0xff < iVar7) {
                uVar5 = 0xff;
              }
              
			  sVar8 = sVar8 + 0x80;
              if (0x7f < iVar4) {
                sVar8 = 0x7f;
                goto LAB_8002595c;
              }
            }
            *(undefined *)(param_1 + 0x43) = uVar5;
            *(short *)(param_1 + 8) = sVar8;
          }
LAB_80025a00:

		  // reset stick values to "center"
          *(undefined2 *)(param_1 + 10) = 0x80;
          *(undefined2 *)(param_1 + 0xc) = 0x80;
          *(undefined2 *)(param_1 + 0xe) = 0x80;
        }
      }
LAB_80025a0c:
      iVar4 = (int)*(short *)(param_1 + 8) + -0x80;
      if (iVar4 < 0) {
        iVar4 = -iVar4;
      }
      if (0x30 < iVar4) {
        *(undefined2 *)(param_1 + 0x28) = 0;
      }
      iVar4 = (int)*(short *)(param_1 + 10) + -0x80;
      if (iVar4 < 0) {
        iVar4 = -iVar4;
      }
      if (0x30 < iVar4) {
        *(undefined2 *)(param_1 + 0x28) = 0;
      }
      iVar4 = (int)*(short *)(param_1 + 0xc) + -0x80;
      if (iVar4 < 0) {
        iVar4 = -iVar4;
      }
      if (0x30 < iVar4) {
        *(undefined2 *)(param_1 + 0x28) = 0;
      }
      iVar4 = (int)*(short *)(param_1 + 0xe) + -0x80;
      if (iVar4 < 0) {
        iVar4 = -iVar4;
      }
      if (0x30 < iVar4) {
        *(undefined2 *)(param_1 + 0x28) = 0;
      }
      bVar1 = *(byte *)(*(int *)(param_1 + 0x20) + 1);
      if (bVar1 == 0x53) {
LAB_80025af0:
        bVar2 = true;
      }
      else {
        if (bVar1 < 0x54) {
          bVar2 = false;
          if (bVar1 == 0x23) goto LAB_80025af0;
        }
        else {
          if ((bVar1 == 0x73) || (bVar2 = false, bVar1 == 0xe3)) goto LAB_80025af0;
        }
      }

	  // if you do not press Left
      if ((*(uint *)(param_1 + 0x10) & 4) == 0)
	  {
		// if you press Right
        if ((*(uint *)(param_1 + 0x10) & 8) != 0) {
          iVar4 = (int)*(short *)(param_1 + 4);
          if (iVar4 < 0x100) {
            uVar3 = (undefined2)(iVar4 + 0xff);
            if (0xff < iVar4 + 0xff) {
              uVar3 = 0xff;
            }
          }
          else {
            uVar3 = (undefined2)(iVar4 + -0xff);
            if (iVar4 + -0xff < 0xff) {
              uVar3 = 0xff;
            }
          }
          goto LAB_80025be4;
        }
        if (!bVar2) {
          iVar4 = (int)*(short *)(param_1 + 4);
          if (iVar4 < 0x81) {
            uVar3 = (undefined2)(iVar4 + 0xff);
            if (0x80 < iVar4 + 0xff) {
              uVar3 = 0x80;
            }
          }
          else {
            uVar3 = (undefined2)(iVar4 + -0xff);
            if (iVar4 + -0xff < 0x80) {
              uVar3 = 0x80;
            }
          }
          goto LAB_80025be4;
        }

		// make backup, curr into prev, stickLX
        *(undefined2 *)(param_1 + 4) = *(undefined2 *)(param_1 + 8);
      }

	  // if you press Left
	  else {
        iVar4 = (int)*(short *)(param_1 + 4);
        if (iVar4 < 1) {
          uVar3 = (undefined2)(iVar4 + 0xff);
          if (0 < iVar4 + 0xff) {
            uVar3 = 0;
          }
        }
        else {
          uVar3 = (undefined2)(iVar4 + -0xff);
          if (iVar4 + -0xff < 0) {
            uVar3 = 0;
          }
        }
LAB_80025be4:
        *(undefined2 *)(param_1 + 4) = uVar3;
      }

	  // if you do not press Up
      if ((*(uint *)(param_1 + 0x10) & 1) == 0) {

		// if you do not press Down
		if ((*(uint *)(param_1 + 0x10) & 2) == 0) {
          if (bVar2) {
            uVar3 = *(undefined2 *)(param_1 + 10);
          }
          else {
            iVar4 = (int)*(short *)(param_1 + 6);
            if (iVar4 < 0x81) {
              uVar3 = (undefined2)(iVar4 + 0xff);
              if (0x80 < iVar4 + 0xff) {
                uVar3 = 0x80;
              }
            }
            else {
              uVar3 = (undefined2)(iVar4 + -0xff);
              if (iVar4 + -0xff < 0x80) {
                uVar3 = 0x80;
              }
            }
          }
        }

		// if you press Down
		else {
          iVar4 = (int)*(short *)(param_1 + 6);
          if (iVar4 < 0x100) {
            uVar3 = (undefined2)(iVar4 + 0xff);
            if (0xff < iVar4 + 0xff) {
              uVar3 = 0xff;
            }
          }
          else {
            uVar3 = (undefined2)(iVar4 + -0xff);
            if (iVar4 + -0xff < 0xff) {
              uVar3 = 0xff;
            }
          }
        }
      }

	  // if you press Up
      else {
        iVar4 = (int)*(short *)(param_1 + 6);
        if (iVar4 < 1) {
          uVar3 = (undefined2)(iVar4 + 0xff);
          if (0 < iVar4 + 0xff) {
            uVar3 = 0;
          }
        }
        else {
          uVar3 = (undefined2)(iVar4 + -0xff);
          if (iVar4 + -0xff < 0) {
            uVar3 = 0;
          }
        }
      }
      *(undefined2 *)(param_1 + 6) = uVar3;
    }
    puVar9 = (undefined4 *)((int)puVar9 + 6);

	// loop counter
	iVar10 = iVar10 + 1;

	// next gamepad buffer
    param_1 = param_1 + 0x50;

	if (7 < iVar10) {
      return;
    }
  } while( true );
}


// Writes all gamepad variables
// for Tap and Release, based on Hold,
// also maps joysticks onto buttons

// GAMEPAD_ProcessTapRelease
void FUN_80025d10(int param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;

  cVar1 = DAT_8008d03e;
  iVar5 = 0;
  uVar4 = 0;
  iVar3 = param_1;
  if (0 < *(int *)(param_1 + 0x314)) {
    do {
      if (*(int *)(iVar3 + 0x20) == 0)
	  {
		// erase tap and release
        *(undefined4 *)(iVar3 + 0x14) = 0;
        *(undefined4 *)(iVar3 + 0x18) = 0;
      }
      else {
        if (cVar1 != '\0')
		{
		  // StickLX
          if (*(short *)(iVar3 + 4) < 0x20)
		  {
			// assume hold BTN_LEFT
            uVar2 = *(uint *)(iVar3 + 0x10) | 4;
LAB_80025d7c:
            *(uint *)(iVar3 + 0x10) = uVar2;
          }

		  else
		  {
		    // StickLX
            if (0xe0 < *(short *)(iVar3 + 4))
			{
			  // assume hold BTN_RIGHT
              uVar2 = *(uint *)(iVar3 + 0x10) | 8;
              goto LAB_80025d7c;
            }
          }

		  // StickLY
          if (*(short *)(iVar3 + 6) < 0x20)
		  {
			// assume hold BTN_UP
            uVar2 = *(uint *)(iVar3 + 0x10) | 1;
          }

		  else
		  {
			// StickLY
            if (*(short *)(iVar3 + 6) < 0xe1) goto LAB_80025dbc;

			// assume hold BTN_DOWN
			uVar2 = *(uint *)(iVar3 + 0x10) | 2;
          }

          *(uint *)(iVar3 + 0x10) = uVar2;
        }
LAB_80025dbc:

		// get buttons held this frame
        uVar4 = uVar4 | *(uint *)(iVar3 + 0x10);

		// tapped
        *(uint *)(iVar3 + 0x14) = ~*(uint *)(iVar3 + 0x1c) & *(uint *)(iVar3 + 0x10);

		// released
        *(uint *)(iVar3 + 0x18) = *(uint *)(iVar3 + 0x1c) & ~*(uint *)(iVar3 + 0x10);
      }
      iVar5 = iVar5 + 1;
      iVar3 = iVar3 + 0x50;
    } while (iVar5 < *(int *)(param_1 + 0x314));
  }
}

// GAMEPAD_ProcessMotors
void FUN_80025e18(int param_1)

{
  byte bVar1;
  int iVar2;
  undefined2 uVar3;
  undefined uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;

  iVar8 = 0;
  iVar5 = param_1;

  // if gamepads are connected
  if (0 < *(int *)(param_1 + 0x314)) {
    do {
      if (

			// If game is not paused
			((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0) &&

			// If you're not in Demo Mode
			(PTR_DAT_8008d2ac[0x1d32] == '\0')
		)
	  {
        if (*(int *)(iVar5 + 0x20) == 0) goto LAB_800260ac;

		// RaceFlag_IsTransitioning
        iVar2 = FUN_80043f44();
        if (iVar2 != 0) goto LAB_80026074;

		// If this is NPC-105 gamepad
        if (*(char *)(*(int *)(iVar5 + 0x20) + 1) == 0xE3)
		{
          bVar1 = 0x40;
          if (*(char *)(iVar5 + 0x44) == '\0') 
		  {
            if ((int)*(short *)(iVar5 + 0x46) == 0) 
			{
              if (
					(*(byte *)(iVar5 + 0x43) < *(byte *)(iVar5 + 0x42)) ||
					(
						bVar1 = *(byte *)(iVar5 + 0x43) >> 4, 
						*(short *)(iVar5 + 0x48) != 0
					)
				  ) 
			  {
                uVar6 = (uint)*(byte *)(iVar5 + 0x42);
                bVar1 = (byte)((int)uVar6 >> 4);
                
				if (
						((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & uVar6 & 0xf) != 0) &&
						(
							bVar1 = (byte)((int)(uVar6 - 0x10) >> 4), 
							(int)(uVar6 - 0x10) < 0
						)
					) 
				{
                  bVar1 = 0;
                }
              }
              bVar1 = bVar1 | 0x30;
              goto LAB_80025f74;
            }
			
			// motorDesired
            *(undefined *)(iVar5 + 0x2a) = *(undefined *)(iVar5 + 0x45);

			// timer 	-= 		elapsed milliseconds per frame, ~32
            iVar2 = (int)*(short *)(iVar5 + 0x46) - *(int *)(PTR_DAT_8008d2ac + 0x1d04);

            if (iVar2 < 1) {
              *(undefined2 *)(iVar5 + 0x46) = 0;
              *(undefined *)(iVar5 + 0x45) = 0;
            }
            else {
              *(undefined2 *)(iVar5 + 0x46) = (short)iVar2;
            }
          }
          else 
		  {
LAB_80025f74:
            *(byte *)(iVar5 + 0x2a) = bVar1;
          }
          if ((int)*(short *)(iVar5 + 0x48) != 0)
		  {
			// timer	-=		elapsed milliseconds per frame, ~32
            iVar2 = (int)*(short *)(iVar5 + 0x48) - *(int *)(PTR_DAT_8008d2ac + 0x1d04);
            uVar3 = (undefined2)iVar2;
            
			if (iVar2 != 0) {
              uVar3 = 0;
            }
            *(undefined2 *)(iVar5 + 0x48) = uVar3;
          }
LAB_80026030:
          *(undefined *)(iVar5 + 0x2b) = 0;
        }

		// If this is not NPC-105 gamepad
		else 
		{
		  // vib3 frame timer
          if (*(int *)(iVar5 + 0x30) == 0) 
		  {
			// no vibration
            *(undefined *)(iVar5 + 0x2a) = 0;
          }
		  
          else 
		  {
			// Frequency control (on/off)
			  
            uVar4 = 0;
            if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & *(uint *)(iVar5 + 0x3c)) == 0) {
              uVar4 = 0xff;
            }
			
			// set desired
            *(undefined *)(iVar5 + 0x2a) = uVar4;
          }
		  
		  // Strength control (percentage)
          
		  if (*(int *)(iVar5 + 0x34) == 0) 
		  {
            *(undefined *)(iVar5 + 0x40) = 0;
            if (*(int *)(iVar5 + 0x38) == 0) 
			{
              *(undefined *)(iVar5 + 0x41) = 0;
              goto LAB_80026030;
            }
            *(undefined *)(iVar5 + 0x2b) = *(undefined *)(iVar5 + 0x41);
          }
          else {
            *(undefined *)(iVar5 + 0x2b) = *(undefined *)(iVar5 + 0x40);
          }
        }
        		
		// shockFrameFreq
		if (*(int *)(iVar5 + 0x30) != 0) {
          *(int *)(iVar5 + 0x30) = *(int *)(iVar5 + 0x30) + -1;
        }
		
		// shockFrameForce1
        if (*(int *)(iVar5 + 0x34) != 0) {
          *(int *)(iVar5 + 0x34) = *(int *)(iVar5 + 0x34) + -1;
        }
		
		// shockFrameForce2
        if (*(int *)(iVar5 + 0x38) != 0) {
          *(int *)(iVar5 + 0x38) = *(int *)(iVar5 + 0x38) + -1;
        }
      }
      
	  else 
	  {
LAB_80026074:
        if (
				(*(int *)(iVar5 + 0x20) == 0) ||

				// If this is not NPC-105 gamepad
				(*(char *)(*(int *)(iVar5 + 0x20) + 1) != 0xE3) ||
				
				(*(char *)(iVar5 + 0x44) == '\0')
			)
		{
LAB_800260ac:
          *(undefined *)(iVar5 + 0x2a) = 0;
        }

		else
		{
          *(undefined *)(iVar5 + 0x2a) = 0x40;
        }

		*(undefined *)(iVar5 + 0x2b) = 0;
        *(undefined4 *)(iVar5 + 0x30) = 0;
        *(undefined4 *)(iVar5 + 0x34) = 0;
        *(undefined4 *)(iVar5 + 0x38) = 0;
        *(undefined2 *)(iVar5 + 0x46) = 0;
        *(undefined *)(iVar5 + 0x45) = 0;
      }
      if (*(char *)(iVar5 + 0x44) != '\0') {
        *(char *)(iVar5 + 0x44) = *(char *)(iVar5 + 0x44) + -1;
      }
      iVar8 = iVar8 + 1;
      iVar5 = iVar5 + 0x50;
    } while (iVar8 < *(int *)(param_1 + 0x314));
  }

  iVar8 = 0;
  iVar2 = 0;
  iVar5 = param_1;

  // if gamepads are connected
  if (0 < *(int *)(param_1 + 0x314)) {
    do {
      
	  // motorDesired
	  if (*(char *)(iVar5 + 0x2a) != '\0') 
	  {
		// motorPower
        iVar8 = iVar8 + (uint)*(byte *)(iVar5 + 0x2c);
      }
      
	  // motorDesired
	  if (*(char *)(iVar5 + 0x2b) != '\0') 
	  {
		// motorPower
        iVar8 = iVar8 + (uint)*(byte *)(iVar5 + 0x2d);
      }
      
	  iVar2 = iVar2 + 1;
      iVar5 = iVar5 + 0x50;
    } while (iVar2 < *(int *)(param_1 + 0x314));
  }

  // PlayStation can not exceed 60 units
  // of electrical power, in port 1 or 2
  if (iVar8 > 60)
  {
	// number of gamepads connected
    uVar6 = *(uint *)(param_1 + 0x314);

	// process random gamepad based on frame-based clock,
	// could be alternating gamepads each frame
    uVar10 = *(uint *)(PTR_DAT_8008d2ac + 0x1cec) % uVar6;

    if (uVar6 == 0) {
      trap(0x1c00);
    }
	
	// motor1
    if ((int)uVar10 < (int)(uVar6 + uVar10)) {
      iVar5 = uVar10 * 0x50;
      uVar9 = uVar10;
	  
	  // cut off vibrations until
	  // power is within 60 units
      do {
        if (iVar8 <= 60) break;
        iVar2 = iVar5;
        if ((int)uVar6 <= (int)uVar9) {
          iVar2 = (uVar9 - uVar6) * 0x50;
        }
        iVar2 = param_1 + iVar2;
        
		// motorDesired
		if (*(char *)(iVar2 + 0x2b) != '\0') 
		{
		  // motorDesired
          *(undefined *)(iVar2 + 0x2b) = 0;
          
		  // motorPower
		  iVar8 = iVar8 - (uint)*(byte *)(iVar2 + 0x2d);
        }
		
        uVar9 = uVar9 + 1;
        iVar5 = iVar5 + 0x50;
      } while ((int)uVar9 < (int)(uVar6 + uVar10));
    }
    iVar5 = uVar6 + uVar10;
	
	// motor2
    if ((int)uVar10 < iVar5) {
      iVar2 = uVar10 * 0x50;
      do {
        if (iVar8 <= 60) break;
        iVar7 = iVar2;
        if ((int)uVar6 <= (int)uVar10) {
          iVar7 = (uVar10 - uVar6) * 0x50;
        }
        iVar7 = param_1 + iVar7;
        
		// motorDesired
		if (*(char *)(iVar7 + 0x2a) != '\0') 
		{
		  // motorDesired
          *(undefined *)(iVar7 + 0x2a) = 0;
          
		  // motorPower
		  iVar8 = iVar8 - (uint)*(byte *)(iVar7 + 0x2c);
        }

		// loop counter
        uVar10 = uVar10 + 1;

		// gamepadBuffer
        iVar2 = iVar2 + 0x50;

      } while ((int)uVar10 < iVar5);
    }
  }

  iVar8 = 0;
  iVar5 = param_1;

  // if there are gamepads
  if (0 < *(int *)(param_1 + 0x314)) {
    do
	{
	  // index counter
      iVar8 = iVar8 + 1;

	  // motorSubmit = motorDesired
      *(undefined *)(iVar5 + 0x2e) = *(undefined *)(iVar5 + 0x2a);
      *(undefined *)(iVar5 + 0x2f) = *(undefined *)(iVar5 + 0x2b);

	  // next gamepad
	  iVar5 = iVar5 + 0x50;

	} while (iVar8 < *(int *)(param_1 + 0x314));
  }
  return;
}


// GAMEPAD_ProcessAnyoneVars
// param_1 = PTR_DAT_8008d2b0
void FUN_800262d0(int param_1)
{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;

  // determine which buttons are held this frame,
  // store a backup of "currFrame" into "lastFrame"
  uVar1 = FUN_80025718();

  // handle mapping of D-Pad and
  // analog stick values onto each other
  FUN_80025854(param_1);

  // Writes all gamepad variables
  // for Tap and Release, based on Hold
  uVar2 = FUN_80025d10(param_1);

  // GAMEPAD_ProcessMotors
  FUN_80025e18(param_1);

  // loop counter
  iVar4 = 0;

  // These are used to see if any button is pressed by anyone
  // during this frame. Reset them all to zero
  *(undefined4 *)(param_1 + 0x290) = 0;
  *(undefined4 *)(param_1 + 0x294) = 0;
  *(undefined4 *)(param_1 + 0x298) = 0;
  *(undefined4 *)(param_1 + 0x29c) = 0;

  // gamepad system structure
  iVar3 = param_1;

  // if gamepads are connected
  if (0 < *(int *)(param_1 + 0x314))
  {
	// loop through gamepads and add their inputs together

	// for iVar4 = 0; iVar4 < numGamepads; iVar4++
    do
	{
	  // Add all gamepad "holds"
      *(uint *)(param_1 + 0x290) = *(uint *)(param_1 + 0x290) | *(uint *)(iVar3 + 0x10);

	  // Add all gamepad "taps"
      *(uint *)(param_1 + 0x294) = *(uint *)(param_1 + 0x294) | *(uint *)(iVar3 + 0x14);

	  // increment loop counter
	  iVar4 = iVar4 + 1;

	  // Add all gamepad "releases" and "heldPrevFrame's"
      *(uint *)(param_1 + 0x298) = *(uint *)(param_1 + 0x298) | *(uint *)(iVar3 + 0x18);
      *(uint *)(param_1 + 0x29c) = *(uint *)(param_1 + 0x29c) | *(uint *)(iVar3 + 0x1c);

	  // increment offset to next gamepad buffer
	  iVar3 = iVar3 + 0x50;

    } while (iVar4 < *(int *)(param_1 + 0x314));
  }
}


// GAMEPAD_JogCon1 (when blasted, spinout, etc)
void FUN_800263a0(int param_1,byte param_2,undefined2 param_3)

{
  undefined *puVar1;

  // If this is human and not AI
  if (((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0) &&
     (
		// Get pointer to this player's 0x50-byte gamepad buffer
		puVar1 = PTR_DAT_8008d2b0 + (uint)*(byte *)(param_1 + 0x4a) * 0x50,

		(puVar1[0x45] & 0xf) <= (param_2 & 0xf))
	 )
  {
    puVar1[0x45] = param_2;
    *(undefined2 *)(puVar1 + 0x46) = param_3;
  }
  return;
}

// called from 232, and in EXE near skidmark code
// GAMEPAD_JogCon2
void FUN_800263fc(int param_1,undefined param_2,undefined2 param_3)

{
  undefined *puVar1;

  // If this is human and not AI
  if ((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0)
  {
	// Get pointer to this player's 0x50-byte gamepad buffer
    puVar1 = PTR_DAT_8008d2b0 + (uint)*(byte *)(param_1 + 0x4a) * 0x50;

    puVar1[0x42] = param_2;
    *(undefined2 *)(puVar1 + 0x48) = param_3;
  }
  return;
}


// GAMEPAD_ShockFreq
void FUN_80026440(int param_1,int param_2,undefined4 param_3)

{
  undefined *puVar1;

  if (
		(
			(
				// If this is human and not AI
				((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0) &&
				((*(uint *)PTR_DAT_8008d2ac & 0x100 << ((uint)*(byte *)(param_1 + 0x4a) & 0x1f)) == 0)
			) &&
			(
				// Get pointer to this player's 0x50-byte gamepad buffer
				puVar1 = PTR_DAT_8008d2b0 + (uint)*(byte *)(param_1 + 0x4a) * 0x50,

				// last input was less than 10 seconds ago
				*(ushort *)(puVar1 + 0x28) < 0x385
			)
		) &&
		(*(int *)(puVar1 + 0x30) < param_2)
	 )
  {
    *(int *)(puVar1 + 0x30) = param_2;
    *(undefined4 *)(puVar1 + 0x3c) = param_3;
  }
  return;
}


// GAMEPAD_ShockForce1
void FUN_800264c0(int param_1,undefined4 param_2,int param_3)

{
  undefined *puVar1;

  if (
		(
			(
				// If this is human and not AI
				((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0) &&

				((*(uint *)PTR_DAT_8008d2ac & 0x100 << ((uint)*(byte *)(param_1 + 0x4a) & 0x1f)) == 0)
			) &&
			(
				// Get pointer to this player's 0x50-byte gamepad buffer
				puVar1 = PTR_DAT_8008d2b0 + (uint)*(byte *)(param_1 + 0x4a) * 0x50,

				// last input was less than 10 seconds ago
				*(ushort *)(puVar1 + 0x28) < 0x385
			)
		) &&
		((int)(uint)(byte)puVar1[0x40] < param_3)
	 )
  {
    *(undefined4 *)(puVar1 + 0x34) = param_2;
    puVar1[0x40] = (char)param_3;
  }
  return;
}


// GAMEPAD_ShockForce2
void FUN_80026540(int param_1,undefined4 param_2,int param_3)

{
  undefined *puVar1;

  if (
		(
			(
				// If this is human and not AI
				((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0) &&

				((*(uint *)PTR_DAT_8008d2ac & 0x100 << ((uint)*(byte *)(param_1 + 0x4a) & 0x1f)) == 0)
			) &&
			(
				// Get pointer to this player's 0x50-byte gamepad buffer
				puVar1 = PTR_DAT_8008d2b0 + (uint)*(byte *)(param_1 + 0x4a) * 0x50,

				// last input was less than 10 seconds ago
				*(ushort *)(puVar1 + 0x28) < 0x385
			)
		) &&
		((int)(uint)(byte)puVar1[0x41] < param_3)
	 )
  {
    *(undefined4 *)(puVar1 + 0x38) = param_2;
    puVar1[0x41] = (char)param_3;
  }
  return;
}
