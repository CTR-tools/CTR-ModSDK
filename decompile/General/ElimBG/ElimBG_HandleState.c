#include <common.h>

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
	// rdataPauseData
	local_30[0] = 0x200;
	local_30[1] = 0x1000040;
	local_28[0] = 0x240;
	local_28[1] = 0x1000040;
	
	// load from RAM, back to VRAM
	LoadImage(&local_30, sdata->PausePtrsVRAM[0]);
	LoadImage(&local_28, sdata->PausePtrsVRAM[1]);
	
	DrawSync(0);
	
	gGT->db[0].primMem.end = (int)gGT->db[0].primMem.end + 0xc800;
	gGT->db[1].primMem.end = (int)gGT->db[1].primMem.end + 0xc800;
	
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
        gGT->renderFlags &= 0x1000;
		gGT->renderFlags |= 0x20;

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
          p->tpage = (u_short)iVar5;
		  
          // clut
          p->clut = 0x3fe0;

          iVar6 = (uVar7 + iVar5 * -0x40) * 4;

          p->v0 = uVar9;
          p->v1 = uVar9;

          // u0
		  cVar4 = (char)iVar6;
          p->u0 = cVar4;

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

          // u2
		  cVar4 = (char)iVar5;
          p->u2 = cVar4;

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
		  uVar9 += 0x10;
          p->v2 = (char)uVar9;
          p->v3 = (char)uVar9;

          // pointer to OT mem, and pointer to primitive
          AddPrim(&gGT->pushBuffer_UI.ptrOT[4], p);

          // while v0 (tex coord Y) < screensize
        } while ((int)uVar9 < 0xd8);

        // increment u0
        iVar10 = iVar10 + 0x80;

        // while u0 (tex coord X) < screensize
      } while (iVar10 < 0x200);
  }
}