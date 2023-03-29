#include <common.h>

void TileView_SetDrawEnv_DecalMP(u_long*, struct DB*, short, short, short, short, short, short, short, short);
void CTR_CycleTex_2p3p4pWumpaHUD(int, int, int);

void DECOMP_UI_RenderFrame_Wumpa3D_2P3P4P(struct GameTracker* gGT)
{
  short uVar2;
  short shineColor;
  struct UiElement2D *hudStructPtr;
  int iVar6;
  POLY_FT4 *p;
  short sVar7;
  short sVar8;
  int ptrHudData;
  int p1hudData;
  int p2hudData;
  int p3hudData;
  int p4hudData;
  struct TileView* decalMP;

  p1hudData = sdata->multiplayerWumpaHudData[0];
  p2hudData = sdata->multiplayerWumpaHudData[1];
  p3hudData = sdata->multiplayerWumpaHudData[2];
  p4hudData = sdata->multiplayerWumpaHudData[3];
  ptrHudData = p1hudData;

  // if numPlyrCurrGame is more than 2
  if (2 < gGT->numPlyrCurrGame) {
    ptrHudData = p3hudData;
  }
  // sdata->tileView_DecalMP
  decalMP = (struct TileView*)0x8009ad18;
  if (decalMP != 0)
  {
	// called once to draw all wumpas

    TileView_SetDrawEnv_DecalMP(
					(u_long *)((int)decalMP + 0xf8),

					// gGT->backBuffer
					gGT->backBuffer,

					// RECT
					ptrHudData,

					// ofsX
					(ptrHudData +
                        ((ptrHudData + 1) >> 1) + -0x100),

					// ofsY
					(ptrHudData + 2) +
					(((ptrHudData + 6) >> 1) + -0x6c),

					0,0,0,0,1);

    iVar6 = (int)decalMP->ptrOT;

    if ((iVar6 != 0) && ((decalMP->ptrOT) != 0))
	{
	  // CTR_CycleTex_2p3p4pWumpaHUD
      CTR_CycleTex_2p3p4pWumpaHUD(
        gGT->tileView->matrix_ViewProj.m[2][1] + 0xffc,
        iVar6, 
        ((int)(decalMP->ptrOT) - iVar6 >> 2) + 1);
    }
  }

  // if there is more than 1 screen
  if (1 < (gGT->numPlyrCurrGame))
  {
	// get HUD position variables [numPlyrCurrGame - 1]
    hudStructPtr = data.hudStructPtr[gGT->numPlyrCurrGame - 1];

	// if numPlyrCurrGame is not zero
	if (gGT->numPlyrCurrGame != 0)
	{
    // wumpaShineResult
      shineColor = sdata->wumpaShineResult;
      for (iVar6 = 0; iVar6 < gGT->numPlyrCurrGame; iVar6++){
        if (
			//if racer hasn't finished the race
			((((gGT->drivers[iVar6])->actionsFlagSet) & 0x2000000) == 0) &&

			((gGT->gameMode1 & END_OF_RACE) == 0)
			)
		{
          sVar7 = (
						// wumpaHudPosX
						hudStructPtr[0xc].x +

						// TileView rect.x
						decalMP->rect.x
				  ) - ((ptrHudData + 1) >> 1);

          sVar8 = (
						// wumpaHudPosY
						hudStructPtr[0xd].x +

						// TileView rect.y
						decalMP->rect.y
				  ) - ((ptrHudData + 6) >> 1);

		  // backBuffer->primMem.curr
          p = gGT->backBuffer->primMem.curr;

          // sets len and code
		      *(char*)(p->tag + 0x3) = 9;
          p->code = 0x2c;
		  
		  // if wumpa is not 10
          if (10 > gGT->drivers[iVar6]->numWumpas) {
            p->r0 = 0x80;
            p->g0 = 0x80;
            p->b0 = 0x80;
          } else {
          // wumpa shine
            p->r0 = shineColor;
            p->g0 = shineColor;
            p->b0 = shineColor;
          }
		  
          p->x0 = sVar7;
          p->y0 = sVar8;
		  
          uVar2 = (ptrHudData + 1);
          
          p->x1 = uVar2 + sVar7;
          p->y1 = sVar8;
          p->x2 = sVar7;
          p->y2 = (ptrHudData + 6) + sVar8;
          p->x3 = (ptrHudData + 1) + sVar7;
          p->y3 = (ptrHudData + 6) + sVar8;
		  
          p->u0 = ptrHudData;
          p->v0 = (ptrHudData + 2);
		  
          p->u1 = p->u0 + (ptrHudData + 1);
          p->v1 = p->v0;
          
		      p->u2 = p->u0;
		      p->v2 = p->v0 + (ptrHudData + 6);
          
		      p->u3 = p->u0 + (ptrHudData + 1);
          p->v3 = p->v0 + (ptrHudData + 6);
		  
          p->tpage =
               (ptrHudData + 2)  >> 4 |
               (ptrHudData >> 6) | 0x100 |
               ((ptrHudData + 2)  << 2);

		  // backBuffer->primMem.curr
		  // move pointer after writing polygons
          (sdata->gGT->backBuffer->primMem).curr =
						 (void *)((int)(sdata->gGT->backBuffer->primMem).curr + 0x28);

		  // pointer to OT memory, and pointer to primitive
		  AddPrim(gGT->tileView_UI.ptrOT,p);
        }
        hudStructPtr += 0xa0;
      }
    }
  }
  return;
}
 