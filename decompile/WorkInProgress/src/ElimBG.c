#include <common.h>

void DECOMP_ElimBG_SaveScreenshot_Chunk(u_short *param_1, u_short *param_2, int param_3)
{
  u_short uVar1;
  u_short* puVar2;

  if (param_3 == 0) return;

  puVar2 = param_2 + 3;
  
  for(; param_3 > 0; param_3 -= 4, param_2 += 4, puVar2 += 4, param_1++) {
    uVar1 = (u_short)((param_2[0] & 0x3e0) >> 6);
    uVar1 |= puVar2[-2] >> 2 & 0xf0;
    uVar1 |= (u_short)((puVar2[-1] & 0x3c0) << 2);
    uVar1 |= (u_short)((*puVar2 & 0x3c0) << 6);
    *param_1 = uVar1;
  };
}

void DECOMP_ElimBG_SaveScreenshot_Full(struct GameTracker* gGT)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  u_int local_48[2];
  u_int local_40[2];
  RECT local_38;
  RECT local_30;

  iVar4 = 0;
  local_48[0] = 0x200;
  local_48[1] = 0x1000040;
  local_40[0] = 0x240;
  local_40[1] = 0x1000040;

  // vram copy, then overwrite vram with pause image

  sdata->pause_VRAM_Backup_PrimMem[4] = gGT->db[0].otMem.start;
  sdata->pause_VRAM_Backup_PrimMem[0] = sdata->pause_VRAM_Backup_PrimMem[4] - 0x8000;
  sdata->pause_VRAM_Backup_PrimMem[2] = sdata->pause_VRAM_Backup_PrimMem[4] - 0xc000;

  sdata->pause_VRAM_Backup_PrimMem[5] = gGT->db[1].otMem.start;
  sdata->pause_VRAM_Backup_PrimMem[4] = sdata->pause_VRAM_Backup_PrimMem[4] - 0xc800;
  sdata->pause_VRAM_Backup_PrimMem[1] = sdata->pause_VRAM_Backup_PrimMem[5] - 0x8000;
  sdata->pause_VRAM_Backup_PrimMem[3] = sdata->pause_VRAM_Backup_PrimMem[5] - 0xc000;
  sdata->pause_VRAM_Backup_PrimMem[5] = sdata->pause_VRAM_Backup_PrimMem[5] - 0xc800;

  gGT->db[0].otMem.start; = sdata->pause_VRAM_Backup_PrimMem[4];
  gGT->db[1].otMem.start; = sdata->pause_VRAM_Backup_PrimMem[5];

  // copy vram into PrimMem
  StoreImage(&local_48,sdata->pause_VRAM_Backup_PrimMem[0]);
  StoreImage(&local_40,sdata->pause_VRAM_Backup_PrimMem[1]);

  local_38.w = 0x200;
  local_38.x = 0;
  local_38.h = 8;

  // swapchain index * Y-offset of second swapchain image
  sVar5 = gGT->swapchainIndex * 0x128;
  local_38.y = sVar5;
  StoreImage(&local_38,sdata->pause_VRAM_Backup_PrimMem[2]);
  iVar2 = 0;
  do {
    iVar4 = 1 - iVar4;
    local_38.y = sVar5 + iVar2 + 8;
    local_38.x = 0;
    local_38.w = 0x200;
    local_38.h = 8;
    DrawSync(0);
    StoreImage(&local_38,((char*)sdata->pause_VRAM_Backup_PrimMem[2])[iVar4]);

    DECOMP_ElimBG_SaveScreenshot_Chunk(((char*)sdata->pause_VRAM_Backup_PrimMem[4])[1 - iVar4],(&sdata->pause_VRAM_Backup_PrimMem[2])[1 - iVar4],0x1000);

	  local_30.x = 0x200;
    local_30.w = 0x80;
    local_30.h = 8;
    iVar3 = iVar2 + 8;
    local_30.y = iVar2;
    LoadImage(&local_30,((char*)sdata->pause_VRAM_Backup_PrimMem[4])[1 - iVar4]);

	  iVar1 = iVar2 + 0x10;
    iVar2 = iVar3;
  } while (iVar1 < 0xd8);

  DrawSync(0);

  DECOMP_ElimBG_SaveScreenshot_Chunk(((char*)sdata->pause_VRAM_Backup_PrimMem[4])[iVar4],((char*)sdata->pause_VRAM_Backup_PrimMem[2])[iVar4],0x1000);

  local_30.x = 0x200;
  local_30.y = iVar3;
  local_30.w = 0x80;
  local_30.h = 8;
  LoadImage(&local_30,((char*)sdata->pause_VRAM_Backup_PrimMem[4])[iVar4]);

  local_30.y = 0xff;
  local_30.w = 0x10;
  local_30.x = 0x200;
  local_30.h = 1;
  LoadImage(&local_30,&data.pauseScreenStrip[0]);
}

void DECOMP_ElimBG_Activate(struct GameTracker* gGT)
{
	sdata->pause_backup_renderFlags = gGT->renderFlags;
	sdata->pause_backup_hudFlags = gGT->hudFlags;
	sdata->pause_state = 1;
}

void DECOMP_ElimBG_ToggleInstance(struct Instance* inst, char boolGameIsPaused)
{
	u_int flags;
	
	// if game is being paused
	if (boolGameIsPaused)
	{
		flags = inst->flags;

		if (!(flags & HIDE_MODEL))
			flags &= ~INVISIBLE_BEFORE_PAUSE;
		else
			flags |= INVISIBLE_BEFORE_PAUSE;

		inst->flags = flags;
		inst->flags |= (INVISIBLE_DURING_PAUSE | HIDE_MODEL);

		return;
	}

	if ((inst->flags & (INVISIBLE_BEFORE_PAUSE | INVISIBLE_DURING_PAUSE)) == INVISIBLE_DURING_PAUSE)
		inst->flags &= ~(INVISIBLE_DURING_PAUSE | HIDE_MODEL);
}

void DECOMP_ElimBG_ToggleAllInstances(struct GameTracker* gGT, char boolGameIsPaused)
{
  struct Item* item;
  struct InstDef* instdef;
  u_int last;

  // first lev instance
    instdef = gGT->level1->ptrInstDefs;

  // last lev instance (first + count * 0x40)
    last = instdef + (gGT->level1->numInstances * 0x40);

  // loop through all LEV instances
    while((u_int)instdef < last) 
    {
      if (instdef->ptrInstance != NULL) {
        DECOMP_ElimBG_ToggleInstance(instdef->ptrInstance, boolGameIsPaused);
      }
      instdef += 0x40;
    }

  // first taken item in InstancePool
  item = LIST_GetFirstItem(gGT->JitPools.instance.taken.first);

  // loop through everything in InstancePool,
  // Driver, Weapons, everything non-lev
  while (item != NULL)
  {
    DECOMP_ElimBG_ToggleInstance(item, boolGameIsPaused);
	  item = LIST_GetNextItem(item);
  }
}

void DECOMP_ElimBG_HandleState(struct GameTracker *gGT)
{
  short sVar1;
  short sVar2;
  char cVar4;
  int iVar5;
  int iVar6;
  POLY_FT4 *p;
  u_int uVar7;
  char cVar8;
  u_int uVar9;
  int iVar10;
  u_int local_30[2];
  u_int local_28[2];

  // if this is last frame of pause
  if (sdata->pause_state == 3)
  {
  local_30[0] = 0x200;
  local_30[1] = 0x1000040;
  local_28[0] = 0x240;
  local_28[1] = 0x1000040;

  // load from RAM, back to VRAM
  LoadImage(&local_30, sdata->pause_VRAM_Backup_PrimMem[0]);
  LoadImage(&local_28, sdata->pause_VRAM_Backup_PrimMem[1]);

  DrawSync(0);

  // restore gGT->DB[0,1].primMem.end
  gGT->db[0].otMem.start = sdata->pause_VRAM_Backup_PrimMem[0] + 0x8000;
  gGT->db[1].otMem.start = sdata->pause_VRAM_Backup_PrimMem[1] + 0x8000;

  // Enable all instances
  DECOMP_ElimBG_ToggleAllInstances(gGT, 0);

  // game is not paused anymore
  sdata->pause_state = 0;
  }
  // if this is not last frame of paus
  // if game is paused at all
  else if (sdata->pause_state != 0)
  {
      // if this is the first frame of pause
      if (sdata->pause_state == 1)
      {
        // allow rendering of checkered flag, add rendering of RenderBucket,
        // so that Adv Pause instances can render, after non-pause instances are disabled
        gGT->renderFlags &= 0x1000 | 0x20;

        gGT->hudFlags &= 0xf6;

        DECOMP_ElimBG_SaveScreenshot_Full(gGT);

        // Disable all instances
        // (prevent PrimMem from overwriting VRAM backup)
        DECOMP_ElimBG_ToggleAllInstances(gGT, 1);

        // you are now ready to draw the screenshot
        sdata->pause_state = 2;
      }
      // rest of the function is for drawing screenshot
      iVar10 = 0;
      do
      {
        uVar9 = 0;
        sVar1 = (short)iVar10;
        do
        {
          // backBuffer->primMem.curr
          p = (POLY_FT4 *)gGT->backBuffer->primMem.curr;

          // increment primMem by size of primitive
          gGT->backBuffer->primMem.curr = p + 1;

          setPolyFT4(p);

          sVar2 = (short)uVar9;

          // RGB
          setRGB0(p, 0x80, 0x80, 0x80);

          // four (x,y) positions
          setXY4(p,sVar1,sVar2, sVar1 + 0x80, sVar2, sVar1,sVar2 + 0x10, sVar1 +0x80, sVar2+0x10);
          
          iVar5 = iVar10;
          if (iVar10 < 0)
          {
            iVar5 = iVar10 + 3;
          }
          uVar7 = (iVar5 >> 2) + 0x200;
          iVar5 = (int)(uVar7 & 0x3ff) >> 6;

          // tpage
          p->tpage =
          ((uVar9 & 0x100) >> 4) | (u_short)iVar5 | ((uVar9 & 0x200) << 2);

          // clut
          setClut(p, 0x3fe0);

          iVar6 = (uVar7 + iVar5 * -0x40) * 4;

          // v0
          p->v0 = (char)uVar9;

          // u0
          p->u0 = (char)iVar6;

          if (iVar6 + 0x80 < 0x100)
          {
            // u1
            p->u1 = cVar4 + -0x80;
          }
          else
          {
            // u1
            p->u1 = 0xff;
          }

          // u2
          iVar5 = (uVar7 + iVar5 * -0x40) * 4;

          // v2
          p->v2 = cVar8 + 0x10;

          // v1
          p->v1 = cVar8;

          // u2
          p->u2 = (char)iVar5;

          if (iVar5 + 0x80 < 0x100)
          {
            // u3
            p->u3 = cVar4 + -0x80;
          }
          else
          {
            // u3
            p->u3 = 0xff;
          }

          // v3 = v0 + 0x10
          p->v3 = (char) uVar9 + 0x10;

          // pointer to OT mem, and pointer to primitive
          AddPrim(&gGT->tileView_UI.ptrOT[3], p);

          // while v0 (tex coord Y) < screensize
        } while ((int)uVar9 < 0xd8);

        // increment u0
        iVar10 = iVar10 + 0x80;

        // while u0 (tex coord X) < screensize
      } while (iVar10 < 0x200);
  }
}

void DECOMP_ElimBG_Deactivate(struct GameTracker *gGT)
{
	u_char backup = (u_char)sdata->pause_backup_hudFlags;
	
	if (sdata->pause_state)
	{
		sdata->pause_state = 3;
		gGT->renderFlags &= 0x1000 | (backup & 0xffffefff);
		gGT->hudFlags = backup;
	}
}