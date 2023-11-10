#include <common.h>

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