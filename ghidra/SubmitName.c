
// SubmitName_RestoreName
void FUN_8004aa08(undefined2 param_1)

{
  undefined2 uVar1;

  DAT_8008d906 = param_1;

  // copy the last string you typed the last time you were in
  // the OSK menu, back into the menu, avoid typing a second time
  memmove(PTR_DAT_8008d2ac + 0x1d65,PTR_DAT_8008d2ac + 0x1d54,0x11);

  // move cursor to 'A' letter
  uVar1 = 0;

  // if string exists
  if (PTR_DAT_8008d2ac[0x1d65] != '\0')
  {
	// move cursor to 'save' button
    uVar1 = 1001;
  }

  // set cursor position of OSK
  *(undefined2 *)(PTR_DAT_8008d2ac + 0x1d4c) = uVar1;

  return;
}


// SubmitName_DrawMenu (on-screen keyboard)
// called from funcptr function,
// as well as one other place
int FUN_8004aa60(ushort param_1)

{
  byte bVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  short sVar8;
  int iVar9;
  short sVar10;
  undefined local_58;
  undefined local_57;
  undefined local_56;
  undefined2 local_50;
  undefined2 local_4e;
  undefined2 local_4c;
  undefined2 local_4a;
  ushort local_48;
  short local_40;
  short local_38;
  int local_30;

  iVar9 = 0;
  local_38 = 0;

  // size of name entered is zero
  local_40 = 0;

  local_48 = param_1;
  _sVar2 = strlen();
  sVar2 = (short)_sVar2;

  // The string you typed for OSK
  pbVar5 = PTR_DAT_8008d2ac + 0x1d65;


  // if the string is not empty
  if (PTR_DAT_8008d2ac[0x1d65] != '\0') {
    bVar1 = *pbVar5;
    do
	{
	  // if character is valid
      if (2 < bVar1)
	  {
		// add to length?
        local_40 = local_40 + 1;
      }

	  // go to next character
      pbVar5 = pbVar5 + 1;

	  // get next character
      bVar1 = *pbVar5;

	  // till you hit nullptr
    } while (bVar1 != 0);
  }

  // character currently being highlighted in OSK
  _sVar2 = (int)*(short *)(PTR_DAT_8008d2ac + 0x1d4c);

  // characters in 3x13 grid are 0x0 to 0x26
  // "cancel" is 1000
  // "save" is 1001

  // if cursor doesn't know where to go, then
  // back to the 3x13 grid of characters
  if ((0x26 < _sVar2) && (_sVar2 < 1000)) {
    _sVar2 = 0x26;
  }

  // make a copy of the index that
  // the cursor is highlighting in the menu
  sVar8 = (short)_sVar2;

  DAT_8008d8f2 = DAT_8008d8f2 + 1;

  // loop counter
  iVar7 = 0;

  local_30 = 1;

  // Draw every character in each row (0 - 2)
  // for iVar7 = 0; iVar7 < 0xd; iVar7++
  do {
    iVar6 = 0;
    if (local_30 != 0) {

	  // Draw every character in each column (0 - 13)
	  // for iVar6 = 0; iVar6 < 0xd; iVar6++
      do
	  {
        sVar10 = 0;

		// if the character you are highlighting is the
		// one being drawn in this iteration of the loop
        if ((int)sVar8 == (iVar6 + iVar7 * 0xd) * 0x10000 >> 0x10)
		{
		  // make the text flash colors
          sVar10 = (short)(((uint)DAT_8008d8f2 & 1) << 2);
        }

		// 80085d94
		// Every character A-Z then 0-9

		// uVar4 is the character you are highlighting
        uVar4 = SEXT24(u_ABCDEFGHIJKLMNOPQRSTUVWXYZ012345_80085d94

						// row * 0xd + column, get the character to
						// draw in iteration of the loop
					   [(int)(short)iVar7 * 0xd + (int)(short)iVar6]);


		uVar3 = uVar4 & 0xff00;
        if ((uVar4 & 0xff00) == 0x1000) {
          uVar4 = uVar4 & 0xff;
          uVar3 = 0;
        }
        if (uVar3 == 0) {
          local_57 = 0;
          local_58 = (char)uVar4;
        }
        else {
          local_56 = 0;
          local_58 = (char)((uVar4 << 0x10) >> 0x18);
          local_57 = (char)uVar4;
        }

		// draw character
        FUN_80022878(&local_58,((int)(short)iVar6 * 0x16 + 0x74) * 0x10000 >> 0x10,
                     ((int)(short)iVar7 * 0x12 + 0x58) * 0x10000 >> 0x10,1,(int)sVar10);

		// iterate loop counter
		iVar6 = iVar6 + 1;

	  } while (iVar6 * 0x10000 >> 0x10 < 0xd);
    }

	// iterate loop counter
    iVar7 = iVar7 + 1;

  } while (iVar7 * 0x10000 >> 0x10 < 3);

  // DAT_8008d878 + 0x4f8
  // PLEASE ENTER YOUR NAME
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x4f8),0x100,0x2c,1,0xffff8000);

  // PTR_DAT_8008d2ac + 0x1d65
  // The string you typed for OSK
  FUN_80022878(PTR_DAT_8008d2ac + 0x1d65,0xc0,0x44,1,4);

  if (((DAT_8008d8f2 & 2) != 0) && (sVar2 < 0x10))
  {
	// DecalFont_GetLineWidth
    iVar7 = FUN_800224d0(PTR_DAT_8008d2ac + 0x1d65,1);

	// DAT_8008d4ac
	// _

	// This draws the blinking red underscore that comes
	// after the string you entered in OSK
	FUN_80022878(&DAT_8008d4ac,(iVar7 + 0xc0) * 0x10000 >> 0x10,0x44,1,0);
  }
  iVar7 = (int)sVar8;
  uVar3 = 0;
  if (iVar7 == 0x3e9) {
    uVar3 = ((uint)DAT_8008d8f2 & 1) << 2;
  }

  // Draw String
  FUN_80022878(*(undefined4 *)(((int)((uint)local_48 << 0x10) >> 0xe) + DAT_8008d878),0x1d8,0x96,1,
               uVar3 | 0x4000);
  sVar10 = 0;
  if (iVar7 == 1000) {
    sVar10 = (short)(((uint)DAT_8008d8f2 & 1) << 2);
  }

  // DAT_8008d878 + 0x504
  // CANCEL
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x504),0x28,0x96,1,(int)sVar10);

  local_50 = 0x20;
  local_4c = 0x1c0;
  local_4e = 0x3e;
  local_4a = 2;

  // RECTMENU_DrawOuterRect_Edge (transparent)
  FUN_80044f90(&local_50,&DAT_8008d438,0x20,
               *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  local_4e = 0x27;
  local_4a = 0x82;

  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_50,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));

  // If you dont press D-pad
  if ((DAT_8009a990 & 0xf) == 0) {

	// If you dont press Start
    if ((DAT_8009a990 & 0x1000) == 0) {

	  // If you dont press Triangle or Square
      if ((DAT_8009a990 & 0x40020) == 0) {

		// If you press Cross or Circle
        if ((DAT_8009a990 & 0x50) != 0) {
          if (iVar7 == 0x26) {
            iVar9 = 2;
            if ((int)sVar2 == 0) {
              iVar9 = 2;
            }
            else {
              PTR_DAT_8008d2ac[(int)sVar2 + 0x1d64] = 0;
            }
          }
          else {

			// If you hit any character within the 3x13 grid
            if (iVar7 < 0x26) {
              uVar3 = (uint)(ushort)u_ABCDEFGHIJKLMNOPQRSTUVWXYZ012345_80085d94[iVar7];
              if (((int)u_ABCDEFGHIJKLMNOPQRSTUVWXYZ012345_80085d94[iVar7] & 0xff00U) == 0x1000) {
                uVar3 = uVar3 & 0xff;
              }

			  // if name entered is less than 8 characters long
              if (local_40 < 8)
			  {
                sVar10 = sVar2;
                if ((uVar3 & 0xff00) != 0) {
                  sVar10 = sVar2 + 1;

				  // append string of your name
                  PTR_DAT_8008d2ac[(int)sVar2 + 0x1d65] = (char)((uVar3 << 0x10) >> 0x18);
                }

                iVar9 = 1;

				// replace existing character?
				PTR_DAT_8008d2ac[(int)sVar10 + 0x1d65] = (char)uVar3;
              }

			  // if name length is too long
              else {
                iVar9 = 5;
              }
            }

			// if you are not in the 3x13 grid
            else {

			  // If you hit "Save" with ID 1000 (0x3e9)
              if (iVar7 == 0x3e9) {
                iVar9 = 2;
                local_38 = 1;

				// copy the string you typed at OSK so it can be
				// used again later, when is time to enter your name again
                memmove(PTR_DAT_8008d2ac + 0x1d54,PTR_DAT_8008d2ac + 0x1d65,0x11);
              }

			  // If you did not hit "Save", which would
			  // only be if you hit "Cancel" instead
              else {
                iVar9 = 0;
                if (iVar7 != 1000) goto LAB_8004b0dc;
                iVar9 = 3;
                local_38 = -1;
              }

			  // clear gamepad input (for menus)
              FUN_80046404();
            }
          }
        }
      }

	  // If you press Triangle or Square
	  else {
        _sVar2 = (int)sVar2;
        iVar9 = 0;
        if (_sVar2 != 0) {
          PTR_DAT_8008d2ac[_sVar2 + 0x1d64] = 0;
          iVar9 = 4;
          if ((byte)(PTR_DAT_8008d2ac + _sVar2 + -2)[0x1d65] < 3) {
            (PTR_DAT_8008d2ac + _sVar2 + -2)[0x1d65] = 0;
          }
        }
      }
    }

	// If you press Start
	else {
      iVar9 = 3;
      if (iVar7 == 1000) {
        local_38 = -1;
      }
      else {
        sVar8 = 1000;
        iVar9 = 1;
      }
    }
  }

  // If you dont press D-pad
  else {

	// If you press Up
    if ((DAT_8009a990 & 1) != 0) {
      _sVar2 = _sVar2 + -0xd;
    }

	// If you press Down
    if ((DAT_8009a990 & 2) != 0) {
      _sVar2 = _sVar2 + 0xd;
    }

	// If you press Left
    if ((DAT_8009a990 & 4) != 0) {
      _sVar2 = _sVar2 + -1;
    }

    iVar9 = _sVar2 << 0x10;

	// If you press Right
	if ((DAT_8009a990 & 8) != 0) {
      _sVar2 = _sVar2 + 1;
      iVar9 = _sVar2 * 0x10000;
    }

    iVar7 = _sVar2 << 0x10;
    if (iVar9 < 0) {
      _sVar2 = 0x3e9;
      iVar7 = 0x3e90000;
    }

	sVar8 = (short)_sVar2;

    uVar3 = _sVar2 - 500;
    if ((0x26 < iVar7 >> 0x10) && (uVar3 = _sVar2 - 500, iVar7 >> 0x10 < 500)) {
      sVar8 = 0x3e9;
      uVar3 = 0x1f5;
    }
    if ((uVar3 & 0xffff) < 500) {
      sVar8 = 0x26;
    }
    iVar9 = 1;

	// if cursor goes too far
    if (0x3ea < sVar8)
	{
	  // go back to 'A' letter
      sVar8 = 0;
    }
  }
LAB_8004b0dc:

// if you want to play a sound
  if (iVar9 != 0)
  {
	// OtherFX_Play
											// 0x80085DE4
    FUN_80028468((uint)*(ushort *)(iVar9 * 4 + -0x7ff7a21c),1);
  }

  // update cursor position
  *(short *)(PTR_DAT_8008d2ac + 0x1d4c) = sVar8;

  return (int)local_38;
}


// SubmitName_MenuProc (on-screen keyboard)
void FUN_8004b144(int param_1)

{
  short sVar1;

  // SubmitName_DrawMenu
  sVar1 = FUN_8004aa60(0x13f);

  *(short *)(param_1 + 0x1a) = sVar1;
  if (sVar1 != 0) 
  {
	// if name entered for Time Trial
    if (DAT_8008d906 == 1) 
	{
	  // if hit CANCEL
      if (sVar1 < 0)
	  {
		// Change active Menu to
		//  end of race menu with "Save Ghost" option
        DAT_8008d924 = &DAT_800a0458;
      }
	  
	  // if hit SAVE
      else
	  {
		// Set Load/Save to Ghost mode, with slot 1 selected
        FUN_80048e2c(0x31);

		// Change active Menu to GhostSelection
		DAT_8008d924 = &DAT_80085bb4;
      }
    }
	
    else 
	{  
	  // if name entered for Adventure
	  if ((DAT_8008d906 < 2) && (DAT_8008d906 == 0)) 
	  {
		// if hit CANCEL
        if (sVar1 < 0)
		{
		  // ptrDesiredMenu = CS_Garage_GetMenuPtr
          DAT_8008d924 = (undefined *)FUN_800b854c();

		  // CS_Garage_ZoomOut (1 = just hit OSK cancel)
          FUN_800b7784(1);
        }
        
		// if hit ENTER
		else 
		{
		  // make backup of name entered
		  DAT_8008fbbc = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d54);
          DAT_8008fbc0 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d58);
          DAT_8008fbc4 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d5c);
          DAT_8008fbc8 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d60);
          DAT_8008fbcc = PTR_DAT_8008d2ac[0x1d64];

		  // Set Load/Save to New Adventure mode
          FUN_80048e2c(1);

		  // Change active menu to draw four adv profiles
          DAT_8008d924 = &DAT_80085b88;
        }
      }
    }
  }
  return;
}
