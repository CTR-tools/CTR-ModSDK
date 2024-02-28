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

  sdata->PausePtrsVRAM[4] = gGT->db[0].otMem.end;
  sdata->PausePtrsVRAM[0] = sdata->PausePtrsVRAM[4] - 0x8000;
  sdata->PausePtrsVRAM[2] = sdata->PausePtrsVRAM[4] - 0xc000;

  sdata->PausePtrsVRAM[5] = gGT->db[1].otMem.end;
  sdata->PausePtrsVRAM[4] = sdata->PausePtrsVRAM[4] - 0xc800;
  sdata->PausePtrsVRAM[1] = sdata->PausePtrsVRAM[5] - 0x8000;
  sdata->PausePtrsVRAM[3] = sdata->PausePtrsVRAM[5] - 0xc000;
  sdata->PausePtrsVRAM[5] = sdata->PausePtrsVRAM[5] - 0xc800;

  gGT->db[0].otMem.end = sdata->PausePtrsVRAM[4];
  gGT->db[1].otMem.end = sdata->PausePtrsVRAM[5];

  // copy texture vram into PrimMem
  StoreImage(&local_48[0],sdata->PausePtrsVRAM[0]);
  StoreImage(&local_40[0],sdata->PausePtrsVRAM[1]);

  // === copy screen into texture vram ===

  rSrc.w = 0x200;
  rSrc.x = 0;
  rSrc.h = 8;
  
  rDst.x = 0x200;
  rDst.w = 0x80;
  rDst.h = 8;

  // swapchain index * Y-offset of second swapchain image=
  rSrc.y = gGT->swapchainIndex * 0x128;
  
  // start the first Store
  StoreImage(&rSrc,sdata->PausePtrsVRAM[2]);
  
  for(rDst.y = 0; rDst.y < (0xd8-8); rDst.y += 8)
  {
    iVar4 = 1 - iVar4;
	
	// pause until Store is done
	DrawSync(0);
	
	// start next Store, while processing previous store
    rSrc.y += 8;
    StoreImage(&rSrc,sdata->PausePtrsVRAM[2+iVar4]);

    DECOMP_ElimBG_SaveScreenshot_Chunk(
		sdata->PausePtrsVRAM[4+(1-iVar4)],
		sdata->PausePtrsVRAM[2+(1-iVar4)],
		0x1000);

    LoadImage(&rDst,sdata->PausePtrsVRAM[4+(1-iVar4)]);
  }

  // wait for last Store
  DrawSync(0);

  DECOMP_ElimBG_SaveScreenshot_Chunk(
		sdata->PausePtrsVRAM[4+(iVar4)],
		sdata->PausePtrsVRAM[2+(iVar4)],
	0x1000);

  LoadImage(&rDst,sdata->PausePtrsVRAM[4+(iVar4)]);

  rDst.y = 0xff;
  rDst.w = 0x10;
  rDst.h = 1;
  LoadImage(&rDst,&data.pauseScreenStrip[0]);
}