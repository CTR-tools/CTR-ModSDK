
// DecalFont_GetLineWidthStrlen
// param1 is string
// param2 is length
// param3 is font size, 1 for big text, 2 for small text
int FUN_800223f4(byte *param_1,short param_2,int param_3)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  short sVar4;

  // get first character in the string
  bVar1 = *param_1;

  // start counter for length
  // of string in pixels
  sVar4 = 0;

  // if first character is not nullptr
  if (bVar1 != 0)
  {
	// 0 for unused debug text
	// 1 for big text
	// 2 for small text
    iVar3 = (param_3 << 0x10) >> 0xf;

    do
	{
	  // if you've checked the maximum length,
	  // then quit the loop
      if (param_2 == 0) break;

	  // If the character being drawn is @, [, ^, or *,
      if ((((bVar1 == 0x40) || (bVar1 == 0x5b)) || (bVar1 == 0x5e)) || (bVar1 == 0x2a))
	  {
		// pixelWidth of button (Circle, Square, Triangle, Star)
        sVar2 = *(short *)(&DAT_80082360 + iVar3) + *(short *)(&DAT_80082460 + iVar3);
code_r0x800224ac:

		// add to full-string pixel width
        sVar4 = sVar4 + sVar2;
      }

	  // If this is not a button character
      else
	  {
		// If this is a colon or a period
        if ((bVar1 == 0x3a) || (bVar1 == 0x2e))
		{
		  // add to number of pixels
          sVar4 = sVar4 + *(short *)(&DAT_80082370 + iVar3);
        }
        else
		{
		  // If this is a normal character
          if (2 < bVar1)
		  {
			// get number of pixels in character
            sVar2 = *(short *)(&DAT_80082360 + iVar3);

			// add to length
            goto code_r0x800224ac;
          }
        }
      }

	  // advance pointer to next character
      param_1 = param_1 + 1;

	  // get next character
      bVar1 = *param_1;

	  // reduce size of string remaining
      param_2 = param_2 + -1;

    } while (bVar1 != 0);
  }

  // return number of pixels
  return (int)sVar4;
}


// DecalFont_GetLineWidth
// param1 is string
// param2 is font size, 1 for big text, 2 for small text
int FUN_800224d0(undefined4 param_1,short param_2)

{
  short sVar1;

  // DecalFont_GetLineWidthStrlen, until you hit nullptr
  sVar1 = FUN_800223f4(param_1,0xffffffff,(int)param_2);

  return (int)sVar1;
}


// param1 is the string,
// param2 is max length
// param3: X coordinate on the screen (0 is far left)
// param4: Y coordinate on the screen (0 is very top)
// param5: font size, 1 for big text, 2 for small text
// param6:
	// & 0x0fff - color
	// & 0xX000 - start at position
	// & 0x4000 - end at position
	// & 0x8000 - center at position

// DecalFont_DrawLineStrlen
void FUN_800224fc(byte *param_1,short param_2,int param_3,short param_4,short param_5,uint param_6)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  short sVar6;
  short sVar7;
  uint uVar8;
  undefined4 *puVar9;
  short sVar10;
  uint uVar11;
  int iVar12;

  // If you do not want text centered
  if ((param_6 & 0x8000) == 0)
  {
	// If you dont want text to "end" at the given X position
    if ((param_6 & 0x4000) == 0)
	{
		// make the text "start" at the given X position
		goto LAB_80022598;
	}

	// If you want text to "end" here

	// DecalFont_GetLineWidthStrlen
	// subtract X position by result
    iVar2 = FUN_800223f4(param_1,(int)param_2,(int)param_5);
  }

  // If you do want text centered
  else
  {
	// DecalFont_GetLineWidthStrlen
    iVar2 = FUN_800223f4(param_1,(int)param_2,(int)param_5);

	// Subtract X position by half of length
    iVar2 = (iVar2 << 0x10) >> 0x11;
  }

  // subtract param_3 for alignment
  param_3 = param_3 - iVar2;

LAB_80022598:

  // At this point, param_3 may or may not have
  // been modified, depending on preference

  // Draw string, starting at posX = param_3

  if (*param_1 != 0) {
    iVar2 = (int)param_5 * 2;
    iVar12 = (int)param_5 * 4;
    do {
      sVar6 = 0;
      if (param_2 == 0) {
        return;
      }
      uVar8 = 0xff;
      sVar7 = 0;

	  // Get Color Data
	  puVar9 = *(undefined4 **)((int)&PTR_DAT_80081d70 + ((int)((param_6 & 0xfff) << 0x10) >> 0xe));

	  // for all "ordinary" characters...
	  
	  // pixWidth
	  uVar11 = (uint)*(ushort *)(&DAT_80082360 + iVar2);
      
	  // character itself
	  bVar1 = *param_1;
      uVar4 = (uint)bVar1;
	  
	  // icon scale
      sVar10 = 0x1000;

	  // if character is : or . symbols
      if ((bVar1 == 0x3a) || (bVar1 == 0x2e)) 
	  {
		// width in pixels
        uVar11 = (uint)*(ushort *)(&DAT_80082370 + iVar2);
      }

      else
	  {
		// if characters are @ [ ^ * symbols, make them Circle, Square, Triangle, Cross
        if ((((bVar1 == 0x40) || (bVar1 == 0x5b)) || (bVar1 == 0x5e)) || (bVar1 == 0x2a)) 
		{
		  // icon scale
          sVar10 = *(short *)(&DAT_80082458 + iVar2);
          
		  // pixHeight
		  sVar7 = *(short *)(&DAT_80082468 + iVar2);
		  
		  // pixWidth + pixWidthSymbolOffset
          uVar11 = (uint)*(ushort *)(&DAT_80082360 + iVar2) +
                   (uint)*(ushort *)(&DAT_80082460 + iVar2);
          
		  puVar9 = (undefined4 *)PTR_DAT_80081dcc;
        }
      }
	  
	  // indentation ascii characters (unused)
      if (bVar1 < 3) 
	  {
		// iconID
        uVar8 = (uint)*(byte *)(uVar4 + iVar2 + 0x80082470);
        
		// dimensions
		sVar6 = *(short *)(&DAT_80082478 + iVar12);
        sVar7 = *(short *)(&DAT_8008247a + iVar12);
        
		// add no pixWidth
		uVar11 = 0;
      }
      else
	  {
		// normal ascii characters, 
		// 0xE0 characters from 0x20 to 0x100
        if (uVar4 - 0x21 < 0xdf)
		{
		  // 80082357 is the last byte 
		  // of the hole before IconGroupID
			
		  // get iconID based on ascii character
          uVar8 = (uint)(byte)(&DAT_80082378)[uVar4-0x21];
        }
      }
	  
	  // if iconID is valid
      if (uVar8 != 0xff) 
	  {
		// font_IconGroupID[fontType]
        iVar3 = (uint)*(ushort *)(iVar2 + -0x7ff7dca8) << 0x10; // 0x80082358
        
		if (0x7f < uVar8) 
		{
          uVar8 = uVar8 - 0x80;
          iVar5 = 0xf;
          if (iVar3 >> 0x10 == 4) {
            iVar5 = 0xe;
          }
          iVar3 = iVar5 << 0x10;
        }

		// if icon index is less than
        if ((int)(uVar8 & 0xffff) <

			// number of icons in this icon group
            (int)*(short *)(*(int *)(PTR_DAT_8008d2ac + (iVar3 >> 0xe) + 0x2114) + 0x12))
		{
		  // DecalHUD_DrawPolyGT4
          FUN_80023054(*(undefined4 *)
                        (*(int *)(PTR_DAT_8008d2ac + (iVar3 >> 0xe) + 0x2114) + (uVar8 & 0xffff) * 4
                        + 0x14),

						// Dimensions (X, Y)
						(int)(short)param_3 + (int)sVar6,
						(int)param_4 + (int)sVar7,

						// pointer to PrimMem struct
                       *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

					   // pointer to OT memory
                       *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

					   // color data
					   *puVar9,puVar9[1],puVar9[2],puVar9[3],

					   0,(int)sVar10);
        }
      }
      param_3 = param_3 + uVar11;
      param_1 = param_1 + 1;
      param_2 = param_2 + -1;
    } while (*param_1 != 0);
  }
  return;
}


// param1 is the string,
// param2: X coordinate on the screen (0 is far left)
// param3: Y coordinate on the screen (0 is very top)
// param4: size: 1 for big text, 2 for small text
// param5 is the color and alignment

// DecalFont_DrawLine
void FUN_80022878(undefined4 param_1,short param_2,short param_3,short param_4,short param_5)

{
  // DecalFont_DrawLineStrlen, keeps going until nullptr
  FUN_800224fc(param_1,0xffffffff,(int)param_2,(int)param_3,(int)param_4,(int)param_5);
  return;
}


// DecalFont_DrawLineOT
void FUN_800228c4(undefined4 param_1,short param_2,short param_3,short param_4,short param_5,
                 undefined4 param_6)

{
  undefined4 uVar1;

  // make a backup of pointer to OT memory
  uVar1 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c);

  // set new pointer to OT memory
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c) = param_6;

  // DecalFont_DrawLine
  FUN_80022878(param_1,(int)param_2,(int)param_3,(int)param_4,(int)param_5);

  // restore backup of pointer to OT memory
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c) = uVar1;

  return;
}


// param1: string
// param2: size
// param3: X coordinate on the screen (0 is far left)
// param4: Y coordinate on the screen (0 is very top)
// param5: max size in pixels of line???
// param6: font size, 1 for big text, 2 for small text
// param7 is the color and alignment

// DecalFont_DrawMultiLineStrlen
int FUN_80022930(char *param_1,short param_2,short param_3,ushort param_4,short param_5,
                short param_6,short param_7)

{
  char cVar1;
  short sVar2;
  char *pcVar3;
  short sVar4;
  char *pcVar5;
  int iVar6;

  iVar6 = 0;
  do
  {
	// pointer to string
    pcVar5 = param_1;

	// rather than using \n for new lines,
	// CTR uses \r, which is similar if you
	// try it with printf

	// while you've not reached the end of the line
    if (*param_1 != '\r')
	{
	  // get the first character
      cVar1 = *param_1;

      while( true )
	  {
		// pointer to current letter
        pcVar3 = pcVar5;

		// number of letters remaining
        sVar4 = param_2;

		// if you reached a space, and you're
		// not out of letters yet
        if ((cVar1 == ' ') && (param_2 != 0))
		{
		  // increment pointer to next letter
          pcVar3 = pcVar5 + 1;

		  // one letter less
          sVar4 = param_2 + -1;
        }

		// get next character
        cVar1 = *pcVar3;

		// if nullptr, or out of letters, quit the loop
        if ((cVar1 == '\0') || (sVar4 == 0)) break;

		// if this is a letter, number, or symbol
        if ((cVar1 != ' ') && (cVar1 != '\r')) {

		  // get the length of the next word
		  while (sVar4 != 0)
		  {
			// increment pointer to next letter
            pcVar3 = pcVar3 + 1;

			// get value of next character
            cVar1 = *pcVar3;

			// reduce number of remaining characters
            sVar4 = sVar4 + -1;

			// stop counting at a nullptr,
			// or a space (end of word),
			// or the end of the line '\r'
            if (((cVar1 == '\0') || (cVar1 == ' ')) || (cVar1 == '\r')) break;
          }
        }

		// DecalFont_GetLineWidthStrlen
        sVar2 = FUN_800223f4(param_1,(int)(pcVar3 + -(int)param_1) * 0x10000 >> 0x10,(int)param_6);

		if (
				// if pixel length is too long?
				(param_5 <= sVar2) ||
				(
					// get character
					cVar1 = *pcVar3,

					// update pointer
					pcVar5 = pcVar3,

					// update number of
					// remaining characters
					param_2 = sVar4,

					// check if this is new line
					cVar1 == '\r'
				)
           ) break;
      }
    }

	// DecalFont_DrawLineStrlen
    FUN_800224fc(param_1,(int)(pcVar5 + -(int)param_1) * 0x10000 >> 0x10,(int)param_3,
                 (int)(((uint)param_4 + iVar6) * 0x10000) >> 0x10,(int)param_6,(int)param_7);

	// posY = posY + pixel height
    iVar6 = iVar6 + (uint)*(ushort *)(&DAT_80082368 + (int)param_6 * 2);
    if (*pcVar5 == '\0') {
LAB_80022afc:
      return iVar6 * 0x10000 >> 0x10;
    }
    if (param_2 != 0) {
      pcVar5 = pcVar5 + 1;
      param_2 = param_2 + -1;
    }
    if ((*pcVar5 == '\0') || (param_1 = pcVar5, param_2 == 0)) goto LAB_80022afc;
  } while( true );
}


// DecalFont_DrawMultiLine
int FUN_80022b34(undefined4 param_1,short param_2,short param_3,short param_4,short param_5,
                short param_6)

{
  short sVar1;

  // DecalFont_DrawMultiLineStrlen with unlimited length
  sVar1 = FUN_80022930(param_1,0xffffffff,(int)param_2,(int)param_3,(int)param_4,(int)param_5,
                       (int)param_6);
  return (int)sVar1;
}

