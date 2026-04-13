
// RECTMENU_DrawPolyGT4
void FUN_80044ef8(param1, param2, ... param10, param11)

{
  // safety check for nullptr
  if (param_1 != 0)
  {
	// DecalHUD_DrawPolyGT4
    FUN_80023054(param1, param2, ... param10, param11);
  }

  return;
}


// RECTMENU_DrawOuterRect_Edge
void FUN_80044f90(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)
{
  if ((param_3 & 0x20) == 0)
  {
	// solid border

	// CTR_Box_DrawSolidBox
    FUN_80021894(
					param_1,
					param_2,
					param_4,

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
  }
  else
  {
	// transparent border

	// CTR_Box_DrawClearBox
    FUN_8002177c(
					param_1,
					param_2,
					1,
					param_4,

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
  }
  return;
}


// Make time string
undefined * FUN_80044ff8(int param_1)

{
  // param_1 keeps track of time in milliseconds

  // Here's how it works:
  // 32 is added to param_1 every frame,
  // 30 fps, so param_1 gets 960 added every second,
  // 60 seconds per minute, so param_1 gets 57600
  // added per minute, which is 0xe100 in hex

  // 32 is the number of milliseconds passed since
  // last frame, which is calculated here:
  // PTR_DAT_8008d2ac + 0x1d04

  // build a string
  sprintf(

		// where string will be stored
		&DAT_80099264,

		// Format
	    // Minute:Seconds:Milliseconds
		"%ld:%ld%ld:%ld%ld",

		// minutes
		param_1 / 0xe100,

		// seconds / 10
        param_1 / 0x2580 + (param_1 / 0xe100) * -6,

		// seconds
		param_1 / 0x3c0 + (param_1 / 0x2580) * -10,

		// milliseconds / 10
        ((param_1 / 6 + (param_1 >> 0x1f) >> 4) - (param_1 >> 0x1f)) + (param_1 / 0x3c0) * -10,

		// milliseconds
        ((param_1 * 100) / 0x3c0) % 10);

  // return the string
  return &DAT_80099264;
}


// RECTMENU_DrawRwdBlueRect_Subset
void FUN_80045134(uint *param_1,uint *param_2,uint *param_3,int param_4)

{
  uint *puVar1;
  uint *puVar2;

  puVar1 = *(uint **)(param_4 + 0xc);
  puVar2 = (uint *)0x0;
  if (puVar1 <= *(uint **)(param_4 + 0x10)) {
    *(uint **)(param_4 + 0xc) = puVar1 + 9;
    puVar2 = puVar1;
  }
  if (puVar2 != (uint *)0x0) {
    puVar2[1] = *param_2 & 0xffffff | 0x38000000;
    puVar2[3] = param_2[1] & 0xffffff;
    puVar2[5] = param_2[2] & 0xffffff;
    puVar2[7] = param_2[3] & 0xffffff;
    puVar2[2] = *param_1;
    puVar2[4] = (int)(short)*(ushort *)param_1 + (int)(short)*(ushort *)(param_1 + 1) & 0xffffU |
                (int)(short)*(ushort *)((int)param_1 + 2) << 0x10;
    puVar2[6] = (uint)*(ushort *)param_1 |
                ((int)(short)*(ushort *)((int)param_1 + 2) +
                (int)(short)*(ushort *)((int)param_1 + 6)) * 0x10000;
    puVar2[8] = (int)(short)*(ushort *)param_1 + (int)(short)*(ushort *)(param_1 + 1) & 0xffffU |
                ((int)(short)*(ushort *)((int)param_1 + 2) +
                (int)(short)*(ushort *)((int)param_1 + 6)) * 0x10000;
    *puVar2 = *param_3 & 0xffffff | 0x8000000;
    *param_3 = (uint)puVar2 & 0xffffff;
  }
  return;
}


// RECTMENU_DrawRwdBlueRect
// RaceWheelConfig + ArcadeDriverSelect
void FUN_80045254(undefined2 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined2 local_38;
  short local_36;
  undefined2 local_34;
  short local_32;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;

  local_38 = *param_1;
  local_34 = param_1[2];
  iVar3 = 0;
  if (*(char *)(param_2 + 3) != 0x64) {
    iVar1 = 0;
    do {
      puVar2 = (undefined4 *)((iVar1 >> 0xe) + param_2);
      local_30 = *puVar2;
      local_28 = puVar2[1];
      local_36 = param_1[1] +
                 (short)((int)((uint)*(byte *)((int)puVar2 + 3) * (int)(short)param_1[3]) / 100);
      local_32 = ((param_1[1] +
                  (short)((int)((uint)*(byte *)((int)puVar2 + 7) * (int)(short)param_1[3]) / 100)) -
                 local_36) + 1;
      local_2c = local_30;
      local_24 = local_28;

	  // RECTMENU_DrawRwdBlueRect_Subset
      FUN_80045134(&local_38,&local_30,param_3,param_4);

      iVar3 = iVar3 + 1;
      iVar1 = iVar3 * 0x10000;
    } while (*(char *)((iVar3 * 0x10000 >> 0xe) + param_2 + 3) != 0x64);
  }
  return;
}


// RECTMENU_DrawRwdTriangle
// (square gorard icon, not actual triangle)
void FUN_800453e8(undefined2 *param_1,undefined *param_2,void *param_3,int param_4)

{
  void *p;
  void *pvVar1;

  pvVar1 = *(void **)(param_4 + 0xc);
  p = (void *)0x0;
  if (pvVar1 <= *(void **)(param_4 + 0x10)) {
    *(int *)(param_4 + 0xc) = (int)pvVar1 + 0x24;
    p = pvVar1;
  }
  if (p != (void *)0x0) {
    
	// psyq macro setPolyG4
	*(undefined *)((int)p + 3) = 8;
    *(undefined *)((int)p + 7) = 0x38;
	
	// RGB
    *(undefined *)((int)p + 4) = *param_2;
    *(undefined *)((int)p + 5) = param_2[1];
    *(undefined *)((int)p + 6) = param_2[2];
	
	// rest of the primitive (four xy, four uv)
    *(undefined *)((int)p + 0xc) = param_2[4];
    *(undefined *)((int)p + 0xd) = param_2[5];
    *(undefined *)((int)p + 0xe) = param_2[6];
    *(undefined *)((int)p + 0x14) = *param_2;
    *(undefined *)((int)p + 0x15) = param_2[1];
    *(undefined *)((int)p + 0x16) = param_2[2];
    *(undefined *)((int)p + 0x1c) = param_2[8];
    *(undefined *)((int)p + 0x1d) = param_2[9];
    *(undefined *)((int)p + 0x1e) = param_2[10];
    *(undefined2 *)((int)p + 8) = *param_1;
    *(short *)((int)p + 10) = param_1[1] + -1;
    *(undefined2 *)((int)p + 0x10) = param_1[2];
    *(undefined2 *)((int)p + 0x12) = param_1[3];
    *(undefined2 *)((int)p + 0x18) = *param_1;
    *(undefined2 *)((int)p + 0x1a) = param_1[1];
    *(undefined2 *)((int)p + 0x20) = param_1[4];
    *(undefined2 *)((int)p + 0x22) = param_1[5];
	
    AddPrim(param_3,p);
  }
  return;
}


// Draw a 2D box made of four rectangles
// param1 is a pointer RECT
// param2 is x offset from edge
// param3 is y offset from edge
// param4 is color
// RECTMENU_DrawOuterRect_LowLevel
void FUN_80045534(short *param_1,short param_2,ushort param_3,undefined4 param_4,short param_5,
                 undefined4 param_6)

{
  int iVar1;
  short local_28;
  short local_26;
  short local_24;
  ushort local_22;

  // startX
  local_28 = *param_1;

  iVar1 = (int)param_5;

  // startY
  local_26 = param_1[1];

  // sizeX
  local_24 = param_1[2];

  // y offset from edge
  local_22 = param_3;

  // Draw rectangle 1
  // RECTMENU_DrawOuterRect_Edge
  FUN_80044f90(&local_28,param_4,iVar1,param_6);

  // 					sizeY - y offset from edge
  local_26 = local_26 + (param_1[3] - param_3);

  // Draw rectangle 2
  // RECTMENU_DrawOuterRect_Edge
  FUN_80044f90(&local_28,param_4,iVar1,param_6);

  // startY + y offset from edge
  local_26 = param_1[1] + param_3;

  local_22 = param_1[3] - (short)((int)((uint)param_3 << 0x10) >> 0xf);

  // x offset from edge
  local_24 = param_2;

  // Draw rectangle 3
  // RECTMENU_DrawOuterRect_Edge
  FUN_80044f90(&local_28,param_4,iVar1,param_6);

  //					sizeX - x offset frome edge
  local_28 = local_28 + (param_1[2] - param_2);

  // Draw rectangle 4
  // RECTMENU_DrawOuterRect_Edge
  FUN_80044f90(&local_28,param_4,iVar1,param_6);
  return;
}


// Draw a 2D box made of four rectangles
// RECTMENU_DrawOuterRect_HighLevel
// for colored boxes in battle mode
void FUN_80045650(undefined4 param_1,undefined4 param_2,short param_3,undefined4 param_4)

{
  // Draw a 2D box made of four rectangles
  // RECTMENU_DrawOuterRect_LowLevel
  FUN_80045534(param_1,3,2,param_2,(int)param_3,param_4);
  return;
}


// RECTMENU_DrawQuip
void FUN_8004568c(undefined4 param_1,short param_2,int param_3,uint param_4,short param_5,
                 short param_6,short param_7)

{
  int iVar1;
  short local_28;
  undefined2 local_26;
  undefined2 local_24;
  undefined2 local_22;

  if ((param_4 & 0xffff) == 0)
  {
	// DecalFont_GetLineWidth
    iVar1 = FUN_800224d0(param_1,(int)param_5);
    param_4 = iVar1 + 0xc;
  }

  // posX
  local_28 = param_2;

  // if text is not centered
  if (((int)param_6 & 0x8000U) != 0)
  {
	// posX with text un-centered
    local_28 = param_2 - (short)(((int)(param_4 << 0x10) >> 0x10) - ((int)(param_4 << 0x10) >> 0x1f)
                                >> 1);
  }

  iVar1 = (int)param_5 * 2;

  // sizeX
  local_24 = (undefined2)param_4;

  // posY
  local_26 = (undefined2)param_3;

  // sizeY
  local_22 = *(undefined2 *)(&DAT_80085af4 + iVar1);

  // Draw string
  FUN_80022878(param_1,(int)param_2,
               (int)((param_3 + (uint)*(ushort *)(&DAT_80085afc + iVar1)) * 0x10000) >> 0x10,
               (int)param_5,(int)param_6);

  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_28,(int)param_7,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  return;
}


// RECTMENU_DrawInnerRect
// param1 is a pointer to RECT (x,y,w,h)
// param2 is type of pushBuffer
	// 0: transparent, like main menu
	// 1: Black, like "gamepad unplugged"
void FUN_800457b0(undefined4 *param_1,ushort param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined *puVar2;
  undefined4 uVar3;
  short sVar4;
  short sVar5;
  undefined4 local_20;
  undefined4 local_1c;

  puVar1 = &DAT_8008d438;
  if ((param_2 & 0x10) != 0) {
    puVar1 = (undefined4 *)&DAT_8008d43c;
  }

  if ((param_2 & 2) == 0)
  {
	// RECTMENU_DrawOuterRect_HighLevel (transparent)
    FUN_80045650(param_1,puVar1,(int)(short)(param_2 | 0x20),param_3);
  }

  if ((param_2 & 8) == 0) {
    local_20 = *param_1;
    local_1c = param_1[1];
    if ((param_2 & 2) == 0) {
      local_20._2_2_ = (short)((uint)local_20 >> 0x10);
      local_20 = CONCAT22(local_20._2_2_ + 2,(short)local_20 + 3);
      local_1c._2_2_ = (short)((uint)local_1c >> 0x10);
      local_1c = CONCAT22(local_1c._2_2_ + -4,(short)local_1c + -6);
    }
    if ((param_2 & 1) == 0) {
      uVar3 = 2;
      if ((param_2 & 0x100) == 0) {
        puVar2 = &DAT_8008d468;
        uVar3 = 0;
      }
      else {
        puVar2 = &DAT_8008d464;
      }

	  // CTR_Box_DrawClearBox
      FUN_8002177c(
					&local_20,
					puVar2,
					uVar3,
					param_3,

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
    }
    else
	{
	  // draw a rectangle
	  // CTR_Box_DrawSolidBox
      FUN_80021894(
					&local_20,
					&DAT_8008d460,
					param_3,

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
    }
  }
  if ((param_2 & 4) == 0) {
    sVar4 = 0xc;
    if ((param_2 & 0x80) != 0) {
      sVar4 = 4;
    }
    sVar5 = 6;
    if ((param_2 & 0x40) != 0) {
      sVar5 = 2;
    }
    local_20 = CONCAT22(*(short *)((int)param_1 + 2) + sVar5,
                        *(short *)param_1 + *(short *)(param_1 + 1));
    local_1c = CONCAT22(*(short *)((int)param_1 + 6),sVar4);

	// CTR_Box_DrawClearBox
    FUN_8002177c(
					&local_20,
					&DAT_8008d460,
					0,
					param_3,

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

	local_20 = CONCAT22(*(short *)((int)param_1 + 2) + *(short *)((int)param_1 + 6),
                        *(short *)param_1 + sVar4);

    local_1c = CONCAT22(sVar5,*(short *)(param_1 + 1) - sVar4);

	// CTR_Box_DrawClearBox
    FUN_8002177c(
					&local_20,
					&DAT_8008d460,
					0,
					param_3,

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
  }
  return;
}


// RECTMENU_DrawFullRect
void FUN_800459ec(short *param_1,short *param_2)

{
  undefined4 *puVar1;
  short local_18;
  short local_16;
  short local_14;
  undefined2 local_12;

  if (
		// if title text exists
		(-1 < *param_1) &&

		((*(uint *)(param_1 + 4) & 4) == 0)
	 )
  {
    puVar1 = &DAT_8008d438;
    if ((param_1[10] & 0x10U) != 0) {
      puVar1 = (undefined4 *)&DAT_8008d43c;
    }
    local_18 = *param_2 + 3;
    local_16 = param_2[1] + 6;
    if ((*(uint *)(param_1 + 4) & 0x80) == 0) {
      local_16 = param_2[1] + 9 + DAT_8008236a;
    }
    else {
      if ((*(uint *)(param_1 + 4) & 0x4000) == 0)
	  {
		// pixel-height of title menu rows
        local_16 = local_16 + DAT_8008236c;
      }
      else
	  {
		// pixel-height of non-title menu rows
        local_16 = local_16 + DAT_8008236a;
      }
    }
    local_12 = 2;
    local_14 = param_2[2] + -6;

	// RECTMENU_DrawOuterRect_Edge (transparent)
    FUN_80044f90(&local_18,puVar1,(int)(short)(param_1[10] | 0x20),
                 *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  }

  // RECTMENU_DrawInnerRect
  FUN_800457b0(param_2,(int)param_1[10],*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  return;
}


// RECTMENU_GetHeight
// param_1 Menu
// param_2 return value
// param_3 bool check submenus
void FUN_80045b1c(short *param_1,short *param_2,short param_3)

{
  short sVar1;
  short sVar2;
  short *psVar3;

  // height of small text
  sVar1 = DAT_8008236c;

  // if tiny text is disabled
  if ((*(uint *)(param_1 + 4) & 0x80) == 0)
  {
	// height of large text
    sVar1 = DAT_8008236a + 3;
  }

  // if not showing only highlighted row
  if ((*(uint *)(param_1 + 4) & 0x40) == 0) 
  {
	// if not drawing only title bar
    if ((*(uint *)(param_1 + 4) & 4) == 0) 
	{
	  // MenuRow array
	  psVar3 = *(short **)(param_1 + 6);

	  // deref to get string
	  sVar2 = *psVar3;

	  // loop through all valid rows
	  while (sVar2 != -1)
	  {
		// go to next row
        psVar3 = psVar3 + 3;

		// increment menu height by row height
        *param_2 = *param_2 + sVar1;

		// get next string
		sVar2 = *psVar3;
      }
      goto LAB_80045bd0;
    }
	
	// if only showing title bar
	// height = height + lineHeight - 6
    sVar2 = *param_2 + -6;
  }
  
  // if only showing highlighted row
  else 
  {
	// height = height + lineHeight
    sVar2 = *param_2;
  }
  
  *param_2 = sVar1 + sVar2;

LAB_80045bd0:

  // if title text exists
  if (-1 < *param_1)
  {
    if ((*(uint *)(param_1 + 4) & 0x4000) == 0) {
      sVar2 = *param_2 + 6;
    }
    else {
      sVar1 = *param_2 + 9;
      sVar2 = DAT_8008236a;
    }

	// increment menu height by text height
    *param_2 = sVar2 + sVar1;
  }

  if (
		// if submenu should be checked
		(param_3 != 0) &&

		// if submenu will be drawn
		((*(uint *)(param_1 + 4) & 0x10) != 0)
	 )
  {
	// RECTMENU_GetHeight
	// recursively check height from submenus
    FUN_80045b1c(*(undefined4 *)(param_1 + 0x12),param_2,1);
  }
  return;
}

// RECTMENU_GetWidth
// param_1 Menu
// param_2 return value
// param_3 bool check submenus
void FUN_80045c50(short *param_1,short *param_2,short param_3)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  ushort *puVar4;
  undefined4 uVar5;

  // if large text
  uVar5 = 1;

  // if menu should have tiny text
  if ((*(uint *)(param_1 + 4) & 0x80) != 0) {
    uVar5 = 2;
  }

  // Menu Rows
  puVar4 = *(ushort **)(param_1 + 6);

  // deref row, to get string index
  uVar1 = *puVar4;

  // if string is valid
  if (*puVar4 != 0xffff)
  {
	// loop through all rows
    do
	{
	  // DecalFont_GetLineWidth
      iVar2 = FUN_800224d0(*(undefined4 *)(((uint)uVar1 & 0x7fff) * 4 + DAT_8008d878),
                           (int)(short)uVar5);

	  // if menu width is less than width of this string
	  if ((int)*param_2 < (iVar2 + 1) * 0x10000 >> 0x10)
	  {
		// set new width of menu
        *param_2 = (short)(iVar2 + 1);
      }

	  // next row
	  puVar4 = puVar4 + 3;

	  // next string
	  uVar1 = *puVar4;

    } while (*puVar4 != 0xffff);
  }

  // if Menu title has a string
  if (-1 < (int)*param_1)
  {
    uVar3 = 1;
    if ((*(uint *)(param_1 + 4) & 0x4000) == 0) {
      uVar3 = uVar5;
    }

	// DecalFont_GetLineWidth
    iVar2 = FUN_800224d0(*(undefined4 *)((int)*param_1 * 4 + DAT_8008d878),uVar3);

	// if menu width is less than width of this string
	if ((int)*param_2 < (iVar2 + 1) * 0x10000 >> 0x10)
	{
	  // set new width of menu
      *param_2 = (short)(iVar2 + 1);
    }
  }

  if (
		// if submenus should be checked
		(param_3 != 0) &&

		// if submenu will be drawn
		((*(uint *)(param_1 + 4) & 0x10) != 0))
  {
	// RECTMENU_GetWidth
	// recursively check submenus for width
    FUN_80045c50(*(undefined4 *)(param_1 + 0x12),param_2,1);
  }
  return;
}


// RECTMENU_DrawSelf
// param_1 - ptrMenu
// param_4 - menu width
void FUN_80045db0(short *param_1,int param_2,short param_3,ushort param_4)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  short sVar7;
  ushort uVar8;
  short sVar9;
  ushort *puVar10;
  short sVar11;
  short sVar12;
  ushort uVar13;
  uint local_78;
  short local_70;
  short local_6e;
  ushort local_6c;
  short local_6a;
  short local_68;
  short local_66;
  short local_64;
  short local_62;
  short local_60;
  short local_5e [3];
  short local_58;
  short local_50;
  short local_48;
  short local_40;
  short local_38;
  int local_30;
  int local_2c;

  // default text color (orange)
  local_78 = 0;

  local_40 = 0;
  local_38 = 0;

  // if Menu should be drawn green
  // for save/load screen
  if ((param_1[10] & 0x10U) != 0)
  {
	// make text color green
    local_78 = 0x1d;
  }
  uVar13 = (ushort)local_78;
  local_58 = param_3;

  // setting flag 0x60000 disables input in pause menu,
  // so how does this "if" make sense?
  if ((*(uint *)(param_1 + 4) & 0x60000) == 0x60000)
  {
    param_1[0xf] = 2;

	// short "+8" is really + 0x10,
	// if funcPtr exists, execute it
	if (*(code **)(param_1 + 8) != (code *)0x0) {
      (**(code **)(param_1 + 8))(param_1);
    }
  }
  sVar11 = 2;

  // if large text in rows
  if ((*(uint *)(param_1 + 4) & 0x80) == 0) {
    sVar11 = 1;
    local_50 = 2;

	// row height + 3
    local_62 = DAT_8008236a + 3;
  }

  // & 80 == 1
  // if tiny text in rows
  else {
    local_50 = 0;

	// row height
    local_62 = DAT_8008236c;

	// if tiny text in title
    if ((*(uint *)(param_1 + 4) & 0x4000) == 0) {

	  // row height
	  local_48 = DAT_8008236c;

      goto LAB_80045e94;
    }
  }

  // if large text in title
  // row height + 3
  local_48 = DAT_8008236a + 3;

LAB_80045e94:
  local_60 = 0;
  param_1[0xb] = param_1[1];
  param_1[0xc] = param_1[2];

  // RECTMENU_GetHeight
  FUN_80045b1c(param_1,&local_60,0);

  uVar2 = *(uint *)(param_1 + 4);

  // set menu width
  param_1[0x10] = param_4;

  *(uint *)(param_1 + 4) = uVar2 & 0xfffffff7;

  // set menu height
  param_1[0x11] = local_60;

  if ((uVar2 & 2) != 0) {
    local_5e[0] = 0;
	
	// RECTMENU_GetHeight
    FUN_80045b1c(param_1,local_5e,1);
	
    local_38 = (short)((uint)(-(int)local_5e[0] - (-(int)local_5e[0] >> 0x1f)) >> 1);
  }
  uVar2 = *(uint *)(param_1 + 4);
  if ((uVar2 & 1) != 0) {
    local_40 = (short)((uint)(-(int)(short)param_4 - (-(int)(short)param_4 >> 0x1f)) >> 1);
  }
  sVar12 = 0;

  // short +6 is really +C,
  // MenuRow array, deref to get string index
  puVar10 = *(ushort **)(param_1 + 6);

  // dereference short, then cast short to int,
  // get string index of the Menu title
  iVar3 = (int)*param_1;

  sVar9 = local_50 + local_38 + local_58 + param_1[0xc];

  if (
		// if title is not 0xFFFF
		(-1 < iVar3) &&

		((uVar2 & 4) == 0)
	 )
  {
    sVar7 = 1;
    if ((uVar2 & 0x4000) == 0) {
      sVar7 = sVar11;
    }
    if ((uVar2 & 0x200) == 0) {
      iVar5 = param_2 + (uint)(ushort)param_1[0xb];
      uVar8 = uVar13;
      if ((uVar2 & 1) != 0) {
        uVar8 = uVar13 | 0x8000;
      }
      local_78 = SEXT24((short)uVar8);

	  // get string from LNG
      uVar4 = *(undefined4 *)(iVar3 * 4 + DAT_8008d878);
    }
    else
	{
      local_78 = local_78 | 0xffff8000;

	  // get string from LNG
      uVar4 = *(undefined4 *)(iVar3 * 4 + DAT_8008d878);

	  iVar5 = param_2 + (uint)(ushort)param_1[0xb] +
              (((int)((uint)param_4 << 0x10) >> 0x10) - ((int)((uint)param_4 << 0x10) >> 0x1f) >> 1)
      ;
    }

	// draw title string
    FUN_80022878(uVar4,iVar5 * 0x10000 >> 0x10,(int)sVar9,(int)sVar7,local_78);

	sVar9 = local_48 + sVar9 + 6;
  }

  // if row string is not 0xFFFF
  if (*puVar10 != 0xffff)
  {
    local_30 = (((int)((uint)param_4 << 0x10) >> 0x10) - ((int)((uint)param_4 << 0x10) >> 0x1f) >> 1
               ) + 1;
    local_2c = (int)sVar11;

	// loop through all menu rows
	do
	{
      local_78 = *(uint *)(param_1 + 4);

	  if (
			// flags are disabled
			((local_78 & 0x44) == 0) ||

			// if this row is the highlighted row
			(sVar12 == param_1[0xd])
		 )
	  {
		// dereference row to get string
        uVar8 = *puVar10;

		// color of "locked" text (gray)
        uVar1 = 0x17;

		// if row is not "locked"
		if ((uVar8 & 0x8000) == 0)
		{
		  // change color to unlocked
          uVar1 = uVar13;
        }

		// if string is valid
		if ((uVar8 & 0x7fff) != 0)
		{
		  if ((local_78 & 0x200) == 0)
		  {
            iVar3 = param_2 + (uint)(ushort)param_1[0xb] + 1;

			if ((local_78 & 1) != 0)
			{
			  // center text
              uVar1 = uVar1 | 0x8000;
            }

			// get pointer to string, from index
            uVar4 = *(undefined4 *)(((uint)uVar8 & 0x7fff) * 4 + DAT_8008d878);

			iVar5 = local_2c;
          }
          else
		  {
			// center text
            uVar1 = uVar1 | 0x8000;

            iVar3 = param_2 + (uint)(ushort)param_1[0xb] + local_30;

			// get pointer to string, from index
			uVar4 = *(undefined4 *)(((uint)uVar8 & 0x7fff) * 4 + DAT_8008d878);

            iVar5 = (int)sVar11;
          }

		  // Draw string
          FUN_80022878(uVar4,iVar3 * 0x10000 >> 0x10,(int)sVar9,iVar5,(int)(short)uVar1);
        }
        sVar9 = sVar9 + local_62;
      }

	  // skip 6 bytes to next row
      puVar10 = puVar10 + 3;

	  // keep count of row
      sVar12 = sVar12 + 1;

	// as long as another row is valid
	} while (*puVar10 != 0xffff);
  }

  if ((*(uint *)(param_1 + 4) & 0x104) == 0) {
    local_70 = local_40 + (short)param_2 + param_1[0xb];
    local_6e = local_58 + param_1[0xc] + local_38;
    if ((*(uint *)(param_1 + 4) & 0x40) == 0) {
      local_6e = local_6e + param_1[0xd] * local_62 + local_50 + -1;
    }
    else {
      local_6e = local_6e + local_50 + -1;
    }
    if ((*(uint *)(param_1 + 4) & 0x80) == 0) {
      local_6a = -3;
    }
    else {
      local_6a = 1;
    }
    local_6a = local_62 + local_6a;
    if (-1 < *param_1) {
      local_6e = local_48 + local_6e + 6;
    }

	// if normal,
	// draw menu row highlight
	puVar6 = &DAT_8008d94c;

	// if draw green save/load
    if ((param_1[10] & 0x10U) != 0)
	{
	  // draw green menu row highlight
      puVar6 = &DAT_8008d948;
    }

    local_6c = param_4;

	// CTR_Box_DrawClearBox
    FUN_8002177c(&local_70,puVar6,1,

					*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
  }

  // if a submenu is being drawn in a hierarchy structure
  if ((*(uint *)(param_1 + 4) & 0x10) != 0)
  {
	// recursively call this function,
	// draw the next menu within this menu
    FUN_80045db0(
				 // offset 0x24, pointer to next menu
				 *(undefined4 *)(param_1 + 0x12),

                 (int)((param_2 + (uint)(ushort)param_1[0xb]) * 0x10000) >> 0x10,
                 (int)(short)(local_38 + local_58 + param_1[0xc] + local_62 + 0xc),

				 // same width in parent and child
                 (int)(short)param_4);
  }
  if ((*(uint *)(param_1 + 4) & 4) == 0) {
    sVar11 = param_1[0xb];
    sVar9 = param_1[0xc];
    local_62 = (local_60 + 8) - (ushort)(*(byte *)(param_1 + 4) >> 7);
  }
  else {
    sVar11 = param_1[0xb];
    sVar9 = param_1[0xc];
    local_62 = local_62 + 8;
  }
  local_64 = param_4 + 0xc;
  local_66 = local_38 + local_58 + sVar9 + -4;
  local_68 = local_40 + (short)param_2 + sVar11 + -6;

  // RECTMENU_DrawFullRect
  FUN_800459ec(param_1,&local_68);
  return;
}


// RECTMENU_ClearInput
void FUN_80046404(void)

{
  int iVar1;
  int iVar2;

  iVar2 = 0;

  // Reset button input
  DAT_8008d950 = 0;
  DAT_8008d974 = 0;

  // for iVar2 = 0; iVar2 < 4; iVar2++
  do
  {
    iVar1 = iVar2 << 0x10;

	// increment loop counter
	iVar2 = iVar2 + 1;

	iVar1 = iVar1 >> 0xe;

	// clear all gamepad input for all players
    *(undefined4 *)((int)&DAT_8009a990 + iVar1) = 0;
    *(undefined4 *)((int)&DAT_8009a964 + iVar1) = 0;

  } while (iVar2 * 0x10000 >> 0x10 < 4);

  return;
}


// RECTMENU_CollectInput
void FUN_80046458(void)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;

  // pointer to gamepad input for all players
  puVar1 = PTR_DAT_8008d2b0;

  // Reset button input
  DAT_8008d950 = 0;
  DAT_8008d974 = 0;

  if ((DAT_8008d954 == 0) || (uVar2 = 4, (*(uint *)(DAT_8008d954 + 8) & 0x8000) == 0))
  {
	// uvar2 = number of players
    uVar2 = (uint)(byte)PTR_DAT_8008d2ac[0x1ca9];
  }

  // loop counter
  iVar4 = 0;

  // if number of players is not zero
  if (uVar2 != 0)
  {
    iVar3 = 0;

	// for iVar4 = 0; iVar4 < numPlyrNextGame; iVar4++
	do
	{
	  // increment pointer counter
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 >> 0x10;

	  // save input each gamepad into variables that can be re-used

	  // Detect buttons "tapped" which only show on the first frame they are pressed
      (&DAT_8009a990)[iVar3] = *(uint *)(puVar1 + iVar3 * 0x50 + 0x14);

	  // Detect buttons "held" which show from when they are pressed, until released
      (&DAT_8009a964)[iVar3] = *(uint *)(puVar1 + iVar3 * 0x50 + 0x10);

	  // Set button input for menus. This combines input from multiple players,
	  // and is used in menus. That's why all 4 players can fight in menus

	  // Tapped buttons from any player
      DAT_8008d950 = DAT_8008d950 | (&DAT_8009a990)[iVar3];

	  // Held buttons from any player
      DAT_8008d974 = DAT_8008d974 | (&DAT_8009a964)[iVar3];

	  // distance between each player's button managment addresses
	  iVar3 = iVar4 * 0x10000;

    } while (iVar4 * 0x10000 >> 0x10 < (int)uVar2);
  }
  return;
}


// RECTMENU_ProcessInput
int FUN_80046534(int param_1)

{
  // When navigating main menu, the pointer in the value
  // of param_1 changes any time you press X or Triangle,
  // to change the submenu. DAT_8008d954 holds a copy

  // ptr + 0x1a: which row is highlighted
  // param_1 + 0x24: Pointer to next submenu (will be 0 at bottom sublevel)
  // param_1 + 0x28: Pointer to prev submenu (will be 0 at top of level of main menu)

  short sVar1;
  uint uVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  short sVar7;

  FUN_8006c684(&DAT_8008d668);
  sVar7 = 0;
  sVar1 = 0;

  if (((*(uint *)(param_1 + 8) & 4) == 0) && ((*(uint *)(param_1 + 8) & 0x60000) != 0x60000))
  {
	// save the row you are hovering over
    uVar3 = *(ushort *)(param_1 + 0x1a);

	// save it again
    uVar4 = (uint)uVar3;

	// At any time, the address (pointer + offset) that holds
	// the value of the row you are highlighting is
	// 8d954 + 0x1a

	// pointer to row selected
    iVar6 = *(int *)(param_1 + 0xc) + (int)*(short *)(param_1 + 0x1a) * 6;

    if (
			// If the submenu you're in has changed
			(DAT_8008d954 != param_1) &&

			(
				// save the current submenu address
				DAT_8008d954 = param_1,

				(*(uint *)(param_1 + 8) & 0x10000) == 0
			)
		)
	{
	  // clear gamepad input (for menus)
      FUN_80046404();
    }

	// Get button input
    uVar2 = DAT_8008d950;

    if ((*(uint *)(param_1 + 8) & 0x8000) == 0) {

		// gamepad input of P1
		uVar2 = DAT_8009a990;
    }

	// If you dont press L1 or R1
	if ((DAT_8009a964 & 0xc00) == 0) {
      sVar1 = sVar7;

	  // If you press D-Pad, Cross, Square, Triangle, Circle
      if ((uVar2 & 0x4007f) != 0)
	  {
		// If you dont press Up
        if ((uVar2 & 1) == 0)
		{
		  // If you dont press Down
          if ((uVar2 & 2) == 0)
		  {
			// If you dont press Left
            if ((uVar2 & 4) == 0)
			{
			  // if you press nothing,
			  // keep old row
              uVar5 = uVar4;

			  // If you press Right
			  if ((uVar2 & 8) != 0)
			  {
                uVar5 = (uint)*(byte *)(iVar6 + 5);
              }
            }

			// If you press Left
            else {
              uVar5 = (uint)*(byte *)(iVar6 + 4);
            }
          }

		  // If you press Down
          else {
            uVar5 = (uint)*(byte *)(iVar6 + 3);
          }
        }

		// If you press Up
        else {
          uVar5 = (uint)*(byte *)(iVar6 + 2);
        }

		// copy new row
        uVar3 = (ushort)uVar5;

        if (
				// if row has changed
				(uVar4 << 0x10 != uVar5 << 0x10) &&

				// if cursor moving sound is not muted
				((*(uint *)(param_1 + 8) & 0x800000) == 0)
			)
		{
		  // OtherFX_Play that moves cursor
          FUN_80028468(0,1);
        }

		// If you dont press Cross or Circle
        if ((uVar2 & 0x50) == 0)
		{
          if ((
				(*(uint *)(param_1 + 8) & 0x100000) == 0) &&

				// If you press Triangle or Square
				((uVar2 & 0x40020) != 0)
			)
		  {
            if ((*(uint *)(param_1 + 8) & 0x800000) == 0)
			{
			  // OtherFX_Play for "go back"
              FUN_80028468(2,1);
            }
            sVar1 = -1;

			// you are not at the top level of main menu
            *(undefined2 *)(param_1 + 0x1e) = 0;

			// set the current selected row
            *(undefined2 *)(param_1 + 0x1a) = 0xffff;

			// if funcPtr exists
            if (*(int *)(param_1 + 0x10) != 0)
			{
			  // clear gamepad input (for menus)
              FUN_80046404();

			  // call the function this menu has,
			  // pass itself as a parameter. Maybe
			  // this means "Draw itself"
              (**(code **)(param_1 + 0x10))(param_1);
            }

			// set the current selected row
            *(ushort *)(param_1 + 0x1a) = uVar3;
          }
        }

		// If you press Cross or Circle
		else
		{
		  // breakpoint at 800466c4, try to enter 4P menu,
		  // then set r2 to zero, resume, and you enter

		  // if you can enter this submenu

		  // menu->rows[menu->rowSelected] & LOCKED == false
          if (((int)*(short *)((int)*(short *)(param_1 + 0x1a) * 6 + *(int *)(param_1 + 0xc)) &
              0x8000U) == 0)
		  {
            if ((*(uint *)(param_1 + 8) & 0x800000) == 0)
			{
			  // OtherFX_Play for "enter"
              FUN_80028468(1,1);
            }

			// you are not on the top of the main menu
            *(undefined2 *)(param_1 + 0x1e) = 0;

			// set the current selected row
            *(ushort *)(param_1 + 0x1a) = uVar3;

            sVar1 = 1;

			// if you have not reached the bottom of the submenu
            if (*(int *)(param_1 + 0x10) != 0)
			{
			  // clear gamepad input (for menus)
              FUN_80046404();

			  // call the function this menu has,
			  // pass itself as a parameter. Maybe
			  // this means "Draw itself"
              (**(code **)(param_1 + 0x10))(param_1);
            }
          }

		  // if you cant enter this submenu,
		  // like 4P VS with 2 gamepads
          else
		  {
            if ((*(uint *)(param_1 + 8) & 0x800000) == 0)
			{
			  // OtherFX_Play "womp" sound
              FUN_80028468(5,1);
            }
          }
        }

		// clear gamepad input (for menus)
        FUN_80046404();
      }

	  // set the current selected row
      *(ushort *)(param_1 + 0x1a) = uVar3;
    }
  }

  // if you are not at the bottom level of
  // the submenu, go to the next level
  if ((*(uint *)(param_1 + 8) & 0x10) != 0)
  {
	// param_1 + 0x24: Pointer to next submenu
	// param_1 + 0x28: Pointer to prev submenu

	// Store the address of the next submenu's previous submenu, to this submenu
    *(int *)(*(int *)(param_1 + 0x24) + 0x28) = param_1;

	// Call this function again, going to the next submenu
    sVar1 = FUN_80046534(*(undefined4 *)(param_1 + 0x24));
  }

  // If you've reached the end of the submenu, return
  return (int)sVar1;
}

// RECTMENU_ProcessState
// birth, life, and death of Menu
void FUN_8004680c(void)

{
  code **ppcVar1;
  uint uVar2;
  int iVar3;
  short local_10 [4];

  // get ptrDesiredMenu
  iVar3 = DAT_8008d924;

  // This is a timer feature so that you
  // can give "amount of life" to a menu,
  // but this variable is never used so
  // it serves no purpose
  if (DAT_8008d90c != 0) {
    DAT_8008d90c = DAT_8008d90c + -1;
  }

  // if you want to change the Menu
  if (DAT_8008d924 != 0)
  {
    uVar2 = *(uint *)(DAT_8008d924 + 8);

	// change ActiveMenu to DesiredMenu
	DAT_8008d908 = DAT_8008d924;

	// erase DesiredMenu
    DAT_8008d924 = 0;

    *(uint *)(iVar3 + 8) = uVar2 & 0xffffefff;
    while ((uVar2 & 0x10) != 0) {
      iVar3 = *(int *)(iVar3 + 0x24);
      uVar2 = *(uint *)(iVar3 + 8);
    }
    *(uint *)(iVar3 + 8) = *(uint *)(iVar3 + 8) & 0xfffffffb;
  }


  if ((*(uint *)(DAT_8008d908 + 8) & 0x420) != 0) {

	// Get function pointer that Menu executes each frame
	ppcVar1 = (code **)(DAT_8008d908 + 0x10);

	// you are at the top level of main menu and can't go back
    *(undefined2 *)(DAT_8008d908 + 0x1e) = 1;

	// execute Menu function
    (**ppcVar1)();
  }

  if ((*(uint *)(DAT_8008d908 + 8) & 0x20) == 0)
  {
	// RECTMENU_ProcessInput
    FUN_80046534();

    if ((*(uint *)(DAT_8008d908 + 8) & 0x2000) == 0)
	{
	  // set width to zero
      local_10[0] = 0;

	  // RECTMENU_GetWidth
	  FUN_80045c50(DAT_8008d908,local_10,1);

	  // draw menu
      FUN_80045db0(DAT_8008d908,0,0,(int)local_10[0]);
    }
  }

  if ((*(uint *)(DAT_8008d908 + 8) & 0x800) == 0)
  {
	// RaceFlag_GetCanDraw
    iVar3 = FUN_80044094();

	// if the value is zero
    if (iVar3 == 0)
	{
	  // RaceFlag_SetCanDraw(true)
      FUN_80044088(1);
    }

	// enable 3d cars on track? pause the game?
    *(uint *)(PTR_DAT_8008d2ac + 0x256c) = *(uint *)(PTR_DAT_8008d2ac + 0x256c) | 0x20;
  }

  // If the menu is invisible, which is only if you
  // left the menu, and no longer need the menu,
  if ((*(uint *)(DAT_8008d908 + 8) & 0x1000) != 0)
  {
	// set ActiveMenu to nullptr
    DAT_8008d908 = 0;
  }
  return;
}


// RECTMENU_Show
void FUN_80046990(int param_1)

{
  // clear gamepad input (for menus)
  FUN_80046404();

  // save the pointer to the menu buffer
  // that is stored at bottom of 221 dll
  DAT_8008d908 = param_1;

  // Remove 0x1000 flag, making sure the menu is visible,
  // this is called in DLL 221 to keep the menu visible
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xffffefff;
  return;
}


// RECTMENU_Hide
void FUN_800469c8(int param_1)

{
  // Enable 0x1000 flag to make menu invisible, this is used
  // when the menu is diabled in 221 dll after making a choice
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x1000;
  return;
}

// RECTMENU_BoolHidden
uint FUN_800469dc(int param_1)

{
  return *(uint *)(param_1 + 8) >> 0xc & 1;
}
