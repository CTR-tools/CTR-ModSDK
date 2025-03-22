#include <common.h>

void DECOMP_ElimBG_SaveScreenshot_Full(struct GameTracker* gGT)
{
  int iVar4;
  u_int local_48[2];
  u_int local_40[2];
  RECT rect1;
  RECT rect2;
  RECT rSrc;
  RECT rDst;

  iVar4 = 0;
  
  // rdataPauseData
  //TODO: modify this code to just properly assign to the rect's members instead of this jank.
  ((u_int*)&rect1)[0] = 0x200;
  ((u_int*)&rect1)[1] = 0x1000040;
  ((u_int*)&rect2)[0] = 0x240;
  ((u_int*)&rect2)[1] = 0x1000040;

  // vram copy, then overwrite vram with pause image

  uint32_t start1 = (uint32_t)gGT->db[0].primMem.end;
  uint32_t start2 = (uint32_t)gGT->db[1].primMem.end;
  start1 -= 0xc800;
  start2 -= 0xc800;
  gGT->db[0].primMem.end = (void*)start1;
  gGT->db[1].primMem.end = (void*)start2;

  // 0x800 byte hole
  sdata->PausePtrsVRAM[4] = (char*)start1;
  sdata->PausePtrsVRAM[5] = (char*)start2;
  
  // 0x4000 byte hole
  sdata->PausePtrsVRAM[2] = (char*)(start1 + 0x800);
  sdata->PausePtrsVRAM[3] = (char*)(start2 + 0x800);
  
  // 0x8000 byte hole
  sdata->PausePtrsVRAM[0] = (char*)(start1 + 0x4800);
  sdata->PausePtrsVRAM[1] = (char*)(start2 + 0x4800);

  // copy texture vram into PrimMem
  StoreImage(&rect1,(uint32_t*)sdata->PausePtrsVRAM[0]);
  StoreImage(&rect2,(uint32_t*)sdata->PausePtrsVRAM[1]);

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
  StoreImage(&rSrc,(uint32_t*)sdata->PausePtrsVRAM[2]);
  
  for(rDst.y = 0; rDst.y < (0xd8-STRIP_H); rDst.y += STRIP_H)
  {
    iVar4 = 1 - iVar4;
	
	// pause until Store is done
	DrawSync(0);
	
	// start next Store, while processing previous store
    rSrc.y += STRIP_H;
    StoreImage((RECT*)&rSrc, (uint32_t*)sdata->PausePtrsVRAM[2 + iVar4]);

    DECOMP_ElimBG_SaveScreenshot_Chunk(
		(u_short*)sdata->PausePtrsVRAM[4+(1-iVar4)],
		(u_short*)sdata->PausePtrsVRAM[2+(1-iVar4)],
		0x1000);

    LoadImage(&rDst,(uint32_t*)sdata->PausePtrsVRAM[4+(1-iVar4)]);
  }

  // wait for last Store
  DrawSync(0);

  DECOMP_ElimBG_SaveScreenshot_Chunk(
		(u_short*)sdata->PausePtrsVRAM[4+(iVar4)],
		(u_short*)sdata->PausePtrsVRAM[2+(iVar4)],
		0x1000);

  LoadImage(&rDst,(uint32_t*)sdata->PausePtrsVRAM[4+(iVar4)]);

  rDst.y = 0xff;
  rDst.w = 0x10;
  rDst.h = 1;
  LoadImage(&rDst,(uint32_t*)&data.pauseScreenStrip[0]);
}