#include <common.h>

void DECOMP_ElimBG_SaveScreenshot_Full(struct GameTracker* gGT)
{
  int iVar4;
  u_int local_48[2];
  u_int local_40[2];
  RECT rSrc;
  RECT rDst;

  iVar4 = 0;
  
  // rdataPauseData
  local_48[0] = 0x200;
  local_48[1] = 0x1000040;
  local_40[0] = 0x240;
  local_40[1] = 0x1000040;

  // vram copy, then overwrite vram with pause image

  int start1 = (int)gGT->db[0].primMem.end;
  int start2 = (int)gGT->db[1].primMem.end;
  start1 -= 0xc800;
  start2 -= 0xc800;
  gGT->db[0].primMem.end = start1;
  gGT->db[1].primMem.end = start2;

  // 0x800 byte hole
  sdata->PausePtrsVRAM[4] = start1;
  sdata->PausePtrsVRAM[5] = start2;
  
  // 0x4000 byte hole
  sdata->PausePtrsVRAM[2] = start1 + 0x800;
  sdata->PausePtrsVRAM[3] = start2 + 0x800;
  
  // 0x8000 byte hole
  sdata->PausePtrsVRAM[0] = start1 + 0x4800;
  sdata->PausePtrsVRAM[1] = start2 + 0x4800;

  // copy texture vram into PrimMem
  StoreImage(&local_48[0],sdata->PausePtrsVRAM[0]);
  StoreImage(&local_40[0],sdata->PausePtrsVRAM[1]);

  // === copy screen into texture vram ===

  #define STRIP_H 8

  rSrc.x = 0;
  rSrc.y = gGT->swapchainIndex * 0x128;
  rSrc.w = 0x200;
  rSrc.h = STRIP_H;

  rDst.x = 0x200;
  rDst.w = 0x80;
  rDst.h = STRIP_H;
  
  // start the first Store
  StoreImage(&rSrc,sdata->PausePtrsVRAM[2]);
  
  for(rDst.y = 0; rDst.y < (0xd8-STRIP_H); rDst.y += STRIP_H)
  {
    iVar4 = 1 - iVar4;
	
	// pause until Store is done
	DrawSync(0);
	
	// start next Store, while processing previous store
    rSrc.y += STRIP_H;
    StoreImage(&rSrc,sdata->PausePtrsVRAM[2+iVar4]);

    DECOMP_ElimBG_SaveScreenshot_Chunk(
		sdata->PausePtrsVRAM[4+(1-iVar4)],
		sdata->PausePtrsVRAM[2+(1-iVar4)],
		0x1000);

    LoadImage(&rDst,sdata->PausePtrsVRAM[4+(1-iVar4)]);
  }

  // wait for last Store
  DrawSync(0);

  rDst.x = 0x200;
  rDst.w = 0x80;
  rDst.h = STRIP_H;
  DECOMP_ElimBG_SaveScreenshot_Chunk(
		sdata->PausePtrsVRAM[4+(iVar4)],
		sdata->PausePtrsVRAM[2+(iVar4)],
	0x1000);

  LoadImage(&rDst,sdata->PausePtrsVRAM[4+(iVar4)]);

  rDst.x = 0x200;
  rDst.y = 0xff;
  rDst.w = 0x10;
  rDst.h = 1;
  LoadImage(&rDst,&data.pauseScreenStrip[0]);
}