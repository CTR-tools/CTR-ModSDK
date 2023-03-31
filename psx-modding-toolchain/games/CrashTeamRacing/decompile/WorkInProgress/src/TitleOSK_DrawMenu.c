#include <common.h>

// called from funcptr function,
// as well as one other place
int TitleOSK_DrawMenu(short param_1)
{
  char bVar1;
  short cursor;
  int uVar3;
  int uVar4;
  char *currName;
  int iVar6;
  int iVar7;
  short sVar8;
  int iVar9;
  short sVar10;
  char local_58;
  char local_57;
  char local_56;
  RECT box;
  short local_48;
  short nameSize;
  short row;
  int local_30;

  iVar9 = 0;
  row = 0;

  // size of name entered is zero
  nameSize = 0;

  local_48 = param_1;
  cursor = strlen();
  cursor = cursor;

  // The string you typed for OSK
  currName = &sdata->gGT->currNameEntered;


  // if the string is not empty
  if (currName != 0) {
    bVar1 = *currName;
    do
	{
	  // if character is valid
      if (2 < bVar1)
	  {
		// add to length?
        nameSize = nameSize + 1;
      }

	  // go to next character
      currName++;

	  // get next character
      bVar1 = *currName;

	  // till you hit nullptr
    } while (bVar1 != 0);
  }

  // character currently being highlighted in OSK
  cursor = (sdata->gGT->TitleOSK_CursorPosition);

  // characters in 3x13 grid are 0x0 to 0x26
  // "cancel" is 1000
  // "save" is 1001

  // if cursor doesn't know where to go, then
  // back to the 3x13 grid of characters
  if ((0x26 < cursor) && (cursor < 1000)) {
    cursor = 0x26;
  }

  // make a copy of the index that
  // the cursor is highlighting in the menu
  sVar8 = cursor;

  sdata->data10_aaaaa[0xd] += 1;

  local_30 = 1;

  // Draw every character in each row (0 - 2)
  for (iVar7 = 0; iVar7 < 0xd; iVar7++)
  {
    if (local_30 != 0) {

	  // Draw every character in each column (0 - 13)
      for (iVar6 = 0; iVar6 < 0xd; iVar6++)
	  {
        sVar10 = 0;

		// if the character you are highlighting is the
		// one being drawn in this iteration of the loop
        if (sVar8 == (iVar6 + iVar7 * 0xd))
		{
		  // make the text flash colors
          sVar10 = ((sdata->data10_aaaaa[0xe] & 1) << 2);
        }

		// 80085d94
		// Every character A-Z then 0-9

		// uVar4 is the character you are highlighting
        uVar4 = SEXT24("ABCDEFGHIJKLMNOPQRSTUVWXYZ012345"

						// row * 0xd + column, get the character to
						// draw in iteration of the loop
					   [iVar7 * 0xd + iVar6]);


		uVar3 = uVar4 & 0xff00;
        if ((uVar4 & 0xff00) == 0x1000) {
          uVar4 = uVar4 & 0xff;
          uVar3 = 0;
        }
        if (uVar3 == 0) {
          local_57 = 0;
          local_58 = uVar4;
        }
        else {
          local_56 = 0;
          local_58 = ((uVar4 << 0x10) >> 0x18);
          local_57 = uVar4;
        }

		// draw character
        DecalFont_DrawLine(&local_58,(iVar6 * 0x16 + 0x74),
                     (iVar7 * 0x12 + 0x58),1,sVar10);
	  } 
    }
  } 

  // sdata->lngStrings + 0x4f8
  // PLEASE ENTER YOUR NAME
  DecalFont_DrawLine((sdata->lngStrings + 0x4f8),0x100,0x2c,1,0xffff8000);

  // The string you typed for OSK
  DecalFont_DrawLine(sdata->gGT->currNameEntered,0xc0,0x44,1,4);

  if (((sdata->data10_aaaaa[0xe] & 2) != 0) && (cursor < 0x10))
  {
    iVar7 = DecalFont_GetLineWidth(sdata->gGT->currNameEntered,1);

	// This draws the blinking red underscore that comes
	// after the string you entered in OSK
	DecalFont_DrawLine(&sdata->str_underscore[0],(iVar7 + 0xc0),0x44,1,0);
  }
  iVar7 = sVar8;
  uVar3 = 0;
  if (iVar7 == 0x3e9) {
    uVar3 = (sdata->data10_aaaaa[0xe] & 1) << 2;
  }

  // Draw String entered
  DecalFont_DrawLine(sdata->lngStrings[local_48 << 0x10 >> 0xe],0x1d8,0x96,1,
               uVar3 | 0x4000);
  sVar10 = 0;
  if (iVar7 == 1000) {
    sVar10 = ((sdata->data10_aaaaa[0xe] & 1) << 2);
  }

  // CANCEL
  DecalFont_DrawLine((sdata->lngStrings[0x504]),0x28,0x96,1,sVar10);

  box.h = 0x20;
  box.w = 0x1c0;
  box.y = 0x3e;
  box.x = 2;

  MenuBox_DrawOuterRect_Edge(&box,&sdata->battleSetup_Color_UI_1,0x20,
               (sdata->gGT->backBuffer->drawEnv.ofs[1]));
  box.y = 0x27;
  box.x = 0x82;

  // Draw 2D Menu rectangle background
  MenuBox_DrawInnerRect(&box,0,(sdata->gGT->backBuffer->drawEnv.ofs[1]));

  // If you dont press D-pad
  if ((sdata->buttonTapPerPlayer[0] & 0xf) == 0) {

	// If you dont press Start
    if ((sdata->buttonTapPerPlayer[0] & 0x1000) == 0) {

	  // If you dont press Triangle or Square
      if ((sdata->buttonTapPerPlayer[0] & 0x40020) == 0) {

		// If you press Cross or Circle
        if ((sdata->buttonTapPerPlayer[0] & 0x50) != 0) {
          if (iVar7 == 0x26) {
            iVar9 = 2;
            if (cursor == 0) {
              iVar9 = 2;
            }
            else {
              sdata->gGT->prevNameEntered[cursor] = 0;
            }
          }
          else {

			// If you hit any character within the 3x13 grid
            if (iVar7 < 0x26) {
              uVar3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ012345"[iVar7];
              if (("ABCDEFGHIJKLMNOPQRSTUVWXYZ012345"[iVar7] & 0xff00U) == 0x1000) {
                uVar3 = uVar3 & 0xff;
              }

			  // if name entered is less than 8 characters long
              if (nameSize < 8)
			  {
                sVar10 = cursor;
                if ((uVar3 & 0xff00) != 0) {
                  sVar10 = cursor + 1;

				  // append string of your name
                  sdata->gGT->currNameEntered[cursor] = ((uVar3 << 0x10) >> 0x18);
                }

                iVar9 = 1;

				// replace existing character?
				sdata->gGT->currNameEntered[sVar10] = uVar3;
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
                row = 1;

				// copy the string you typed at OSK so it can be
				// used again later, when is time to enter your name again
                memmove(sdata->gGT->prevNameEntered,sdata->gGT->currNameEntered,0x11);
              }

			  // If you did not hit "Save", which would
			  // only be if you hit "Cancel" instead
              else {
                iVar9 = 0;
                if (iVar7 != 1000) goto LAB_8004b0dc;
                iVar9 = 3;
                row = -1;
              }

			  // clear gamepad input (for menus)
              MenuBox_ClearInput();
            }
          }
        }
      }

	  // If you press Triangle or Square
	  else {
        cursor = cursor;
        iVar9 = 0;
        if (cursor != 0) {
          sdata->gGT->prevNameEntered[cursor + 9] = 0;
          iVar9 = 4;
          if (sdata->gGT->prevNameEntered[cursor - 2] < 3) {
            sdata->gGT->prevNameEntered[cursor - 2] = 0;
          }
        }
      }
    }

	// If you press Start
	else {
      iVar9 = 3;
      if (iVar7 == 1000) {
        row = -1;
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
    if ((sdata->buttonTapPerPlayer[0] & 1) != 0) {
      cursor = cursor + -0xd;
    }

	// If you press Down
    if ((sdata->buttonTapPerPlayer[0] & 2) != 0) {
      cursor = cursor + 0xd;
    }

	// If you press Left
    if ((sdata->buttonTapPerPlayer[0] & 4) != 0) {
      cursor = cursor + -1;
    }

    iVar9 = cursor << 0x10;

	// If you press Right
	if ((sdata->buttonTapPerPlayer[0] & 8) != 0) {
      cursor = cursor + 1;
      iVar9 = cursor * 0x10000;
    }

    iVar7 = cursor << 0x10;
    if (iVar9 < 0) {
      cursor = 0x3e9;
      iVar7 = 0x3e90000;
    }

	sVar8 = cursor;

    uVar3 = cursor - 500;
    if ((0x26 < iVar7 >> 0x10) && (uVar3 = cursor - 500, iVar7 >> 0x10 < 500)) {
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
    OtherFX_Play((data.soundIndexArray[iVar9]),1);
  

  // update cursor position
  sdata->gGT->TitleOSK_CursorPosition = sVar8;

  return row;
  }
}
 