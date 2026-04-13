
// called "ElimBG" to eliminate (elim) background (bg) 
// drawing of everything, while the game is in the pause menu

// ElimBG_SaveScreenshot_Chunk
void FUN_80024524(ushort *param_1,ushort *param_2,int param_3)

{
  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;

  if (param_3 != 0) {
    puVar3 = param_2 + 3;
    do {
      uVar2 = (ushort)(((uint)*param_2 & 0x3e0) >> 6);
      *param_1 = uVar2;
      param_2 = param_2 + 4;
      uVar2 = uVar2 | puVar3[-2] >> 2 & 0xf0;
      *param_1 = uVar2;
      param_3 = param_3 + -4;
      uVar2 = uVar2 | (ushort)(((uint)puVar3[-1] & 0x3c0) << 2);
      *param_1 = uVar2;
      uVar1 = *puVar3;
      puVar3 = puVar3 + 4;
      *param_1 = uVar2 | (ushort)(((uint)uVar1 & 0x3c0) << 6);
      param_1 = param_1 + 1;
    } while (param_3 != 0);
  }
  return;
}

// ElimBG_SaveScreenshot_Full
// stores VRAM in RAM (as backup)
// stores screenshot of swapchain in VRAM
void FUN_8002459c(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined2 local_38;
  short local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_30;
  short local_2e;
  undefined2 local_2c;
  undefined2 local_2a;

  iVar4 = 0;
  
  // rdataPauseData
  local_48 = 0x200;
  local_44 = 0x1000040;
  local_40 = 0x240;
  local_3c = 0x1000040;

  // make pointers relative to primMem.end for
  // vram copy, then overwrite vram with pause image

  // gGT->DB[0].primMem.end
  DAT_8008d028 = *(int *)(param_1 + 0x94);
  DAT_8008d018 = DAT_8008d028 + -0x8000;
  DAT_8008d020 = DAT_8008d028 + -0xc000;

  // gGT->DB[1].primMem.end
  DAT_8008d02c = *(int *)(param_1 + 0x138);
  DAT_8008d028 = DAT_8008d028 + -0xc800;
  DAT_8008d01c = DAT_8008d02c + -0x8000;
  DAT_8008d024 = DAT_8008d02c + -0xc000;
  DAT_8008d02c = DAT_8008d02c + -0xc800;

  // set restricted gGT->DB[0,1].primMem.end
  *(int *)(param_1 + 0x94) = DAT_8008d028;
  *(int *)(param_1 + 0x138) = DAT_8008d02c;

  // copy texture vram into PrimMem
  StoreImage(&local_48,DAT_8008d018);
  StoreImage(&local_40,DAT_8008d01c);
  
  // === copy screen into texture vram ===

  local_34 = 0x200;
  local_38 = 0;
  local_32 = 8;

  // swapchain index * Y-offset of second swapchain image
  sVar5 = (short)*(undefined4 *)(param_1 + 0xc) * 0x128;
  
  local_36 = sVar5;
  
  // start the first Store
  StoreImage(&local_38,DAT_8008d020);
  
  iVar2 = 0;
  do {
    iVar4 = 1 - iVar4;
    local_36 = sVar5 + (short)iVar2 + 8;
    local_38 = 0;
    local_34 = 0x200;
    local_32 = 8;
	
	// pause until Store is done
    DrawSync(0);
	
	// start next Store, while processing previous store
    StoreImage(&local_38,(&DAT_8008d020)[iVar4]);

	// ElimBG_SaveScreenshot_Chunk
    FUN_80024524((&DAT_8008d028)[1 - iVar4],(&DAT_8008d020)[1 - iVar4],0x1000);

	local_30 = 0x200;
    local_2c = 0x80;
    local_2a = 8;
    iVar3 = iVar2 + 8;
    local_2e = (short)iVar2;
    LoadImage(&local_30,(&DAT_8008d028)[1 - iVar4]);

	iVar1 = iVar2 + 0x10;
    iVar2 = iVar3;
  } while (iVar1 < 0xd8);

  // wait for last Store
  DrawSync(0);

  // ElimBG_SaveScreenshot_Chunk
  FUN_80024524((&DAT_8008d028)[iVar4],(&DAT_8008d020)[iVar4],0x1000);

  local_30 = 0x200;
  local_2e = (short)iVar3;
  local_2c = 0x80;
  local_2a = 8;
  LoadImage(&local_30,(&DAT_8008d028)[iVar4]);

  local_2e = 0xff;
  local_2c = 0x10;
  local_30 = 0x200;
  local_2a = 1;
  LoadImage(&local_30,&DAT_80082488);

  return;
}


// ElimBG_Activate
// param1 is PTR_DAT_8008d2ac
void FUN_8002481c(int param_1)

{
  // Sep 3

  // if game is not fully unpaused
  //if (DAT_8008d036 != 0) {
  //  printf("KYLE\'S MOMS A BITCH AND SHE SUCKS A DIRTY DICK");
  //}

  // backup render flags, and hud flags
  DAT_8008d030 = *(undefined4 *)(param_1 + 0x256c);
  DAT_8008d034 = (ushort)*(byte *)(param_1 + 0x1d31);

  // this is now the first frame of pause
  DAT_8008d036 = 1;

  return;
}


// ElimBG_ToggleInstance
// param_1 is instance
// param_2 is 0x0 or 0x1
void FUN_80024840(int param_1,int param_2)
{
  uint uVar1;

  // if game is being paused
  if (param_2 != 0)
  {
	// get instance flags
    uVar1 = *(uint *)(param_1 + 0x28);

	// if visible
	if ((uVar1 & 0x80) == 0)
	{
	  // remove 0x10000000
      uVar1 = uVar1 & 0xefffffff;
    }

	// if invisible
	else
	{
	  // add 0x10000000, so the instance
	  // is not made visible during unpause
      uVar1 = uVar1 | 0x10000000;
    }

	// store new flags
	*(uint *)(param_1 + 0x28) = uVar1;

	// make all instances invisible,
	// plus 0x20000000, which means made invisible by pausing
    *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x20000080;

	return;
  }

  // if game is being unpaused

  // if instance was not already invisible before the game paused
  if ((*(uint *)(param_1 + 0x28) & 0x30000000) == 0x20000000)
  {
    // remove bit added from pause,
	// make instance visible again
	*(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) & 0xdfffff7f;
  }
  return;
}


// ElimBG_ToggleAllInstances
// param_1 is PTR_DAT_8008d2ac
// param_2 is 0x0 or 0x1
void FUN_800248bc(int param_1,undefined4 param_2)
{
  int iVar1;
  uint uVar2;
  uint uVar3;

  // first lev instance
  uVar2 = *(uint *)(*(int *)(param_1 + 0x160) + 0x10);

  // last lev instance (first + count * 0x40)
  uVar3 = uVar2 + *(int *)(*(int *)(param_1 + 0x160) + 0xc) * 0x40;

  // loop through all LEV instances
  while (uVar2 < uVar3) {

    if (*(int *)(uVar2 + 0x2c) != 0)
	{
	  // ElimBG_ToggleInstance
      FUN_80024840(*(int *)(uVar2 + 0x2c),param_2);
    }

	// next instance
    uVar2 = uVar2 + 0x40;
  }

  // LIST_GetFirstItem
  // first taken item in InstancePool
  iVar1 = FUN_800317d8(param_1 + 0x1904);

  // loop through everything in InstancePool,
  // Driver, Weapons, everything non-lev
  while (iVar1 != 0)
  {
	// ElimBG_ToggleInstance
    FUN_80024840(iVar1,param_2);

	// LIST_GetNextItem
	iVar1 = FUN_800317cc(iVar1);
  }
  return;
}

// ElimBG_HandleState
// copying screenshot to VRAM, and backing up previous VRAM,
// draws the screenshot from VRAM
// restores the backup into VRAM when pause is done
// param_1 = PTR_DAT_8008d2ac
void FUN_80024974(int param_1)
{
  short sVar1;
  short sVar2;
  undefined *puVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  void *p;
  uint uVar7;
  char cVar8;
  uint uVar9;
  int iVar10;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;

  puVar3 = PTR_DAT_8008d2ac;

  // if this is last frame of pause
  if (DAT_8008d036 == 3) 
  {
	// rdataPauseData
    local_30 = 0x200;
    local_2c = 0x1000040;
    local_28 = 0x240;
    local_24 = 0x1000040;

	// load from RAM, back to VRAM
    LoadImage(&local_30,DAT_8008d018);
    LoadImage(&local_28,DAT_8008d01c);

	DrawSync(0);

	// restore gGT->DB[0,1].primMem.end
    *(int *)(param_1 + 0x94) = DAT_8008d018 + 0x8000;
    *(int *)(param_1 + 0x138) = DAT_8008d01c + 0x8000;

	// ElimBG_ToggleAllInstances
	FUN_800248bc(param_1,0);

	// game is not paused anymore
    DAT_8008d036 = 0;
  }

  // if this is not last frame of pause
  else
  {
	// if game is paused at all
    if (DAT_8008d036 != 0)
	{
	  // if this is the first frame of pause
      if (DAT_8008d036 == 1)
	  {
		// allow rendering of checkered flag, add rendering of RenderBucket,
		// so that Adv Pause instances can render, after non-pause instances are disabled
        *(uint *)(param_1 + 0x256c) = *(uint *)(param_1 + 0x256c) & 0x1000 | 0x20;

        puVar3[0x1d31] = puVar3[0x1d31] & 0xf6;

		// ElimBG_SaveScreenshot_Full
		FUN_8002459c(param_1);

		// ElimBG_ToggleAllInstances
		FUN_800248bc(param_1,1);

		// you are now ready to draw the screenshot
        DAT_8008d036 = 2;
      }

	  // rest of the function is for drawing screenshot

      iVar10 = 0;
      do {
        uVar9 = 0;
        sVar1 = (short)iVar10;
        do
		{
		  // backBuffer->primMem.curr
          p = *(void **)(*(int *)(param_1 + 0x10) + 0x80);

		  // increment primMem by size of primitive
          *(int *)(*(int *)(param_1 + 0x10) + 0x80) = (int)p + 0x28;
		  
		  // psyq macro setPolyFT4
          *(undefined *)((int)p + 3) = 9;
          *(undefined *)((int)p + 7) = 0x2c;
          sVar2 = (short)uVar9;
		  
		  // RGB
          *(undefined *)((int)p + 6) = 0x80;
          *(undefined *)((int)p + 5) = 0x80;
          *(undefined *)((int)p + 4) = 0x80;
		  
		  // four (x,y) positions
          *(short *)((int)p + 8) = sVar1;
          *(short *)((int)p + 10) = sVar2;
          *(short *)((int)p + 0x10) = sVar1 + 0x80;
          *(short *)((int)p + 0x12) = sVar2;
          *(short *)((int)p + 0x18) = sVar1;
          *(short *)((int)p + 0x1a) = sVar2 + 0x10;
          *(short *)((int)p + 0x20) = sVar1 + 0x80;
          *(short *)((int)p + 0x22) = sVar2 + 0x10;
		  
          iVar5 = iVar10;
          if (iVar10 < 0) {
            iVar5 = iVar10 + 3;
          }
          uVar7 = (iVar5 >> 2) + 0x200;
          iVar5 = (int)(uVar7 & 0x3ff) >> 6;
		  
		  // tpage
          *(ushort *)((int)p + 0x16) =
               (ushort)((int)(uVar9 & 0x100) >> 4) | (ushort)iVar5 | (ushort)((uVar9 & 0x200) << 2);
			   
		  // clut
          *(undefined2 *)((int)p + 0xe) = 0x3fe0;
		  
          iVar6 = (uVar7 + iVar5 * -0x40) * 4;
          
		  // v0
		  cVar8 = (char)uVar9;
          *(char *)((int)p + 0xd) = cVar8;
          
		  // u0
		  cVar4 = (char)iVar6;
          *(char *)((int)p + 0xc) = cVar4;
		  
          if (iVar6 + 0x80 < 0x100) 
		  {
			// u1
            *(char *)((int)p + 0x14) = cVar4 + -0x80;
          }
          else 
		  {
			// u1
            *(undefined *)((int)p + 0x14) = 0xff;
          }
		  
		  // u2
          iVar5 = (uVar7 + iVar5 * -0x40) * 4;
		  
		  // v2
          *(char *)((int)p + 0x1d) = cVar8 + '\x10';
		  
		  // v1
          *(char *)((int)p + 0x15) = cVar8;
		  
		  // u2
          cVar4 = (char)iVar5;
          *(char *)((int)p + 0x1c) = cVar4;
		  
          if (iVar5 + 0x80 < 0x100) 
		  {
			// u3
            *(char *)((int)p + 0x24) = cVar4 + -0x80;
          }
          else 
		  {
			// u3
            *(undefined *)((int)p + 0x24) = 0xff;
          }
		  
		  // v3 = v0 + 0x10
          uVar9 = uVar9 + 0x10;
          *(undefined *)((int)p + 0x25) = (char)uVar9;

		  // pointer to OT mem, and pointer to primitive
          AddPrim((void *)(*(int *)(PTR_DAT_8008d2ac + 0x147c) + 0x10),p);

		// while v0 (tex coord Y) < screensize
		} while ((int)uVar9 < 0xd8);
		
		// increment u0
        iVar10 = iVar10 + 0x80;
		
	  // while u0 (tex coord X) < screensize
      } while (iVar10 < 0x200);
    }
  }
  return;
}


// ElimBG_Deactivate
// param1 is PTR_DAT_8008d2ac
void FUN_80024c08(int param_1)

{
  undefined uVar1;

  // backup hud flags
  uVar1 = (undefined)DAT_8008d034;

  // if game is not unpaused
  if (DAT_8008d036 != 0)
  {
	// this is the last frame of pause
    DAT_8008d036 = 3;

	// restore render flags
	*(uint *)(param_1 + 0x256c) = *(uint *)(param_1 + 0x256c) & 0x1000 | DAT_8008d030 & 0xffffefff;

	// restore hud flags
	*(undefined *)(param_1 + 0x1d31) = uVar1;
  }

  return;
}
