#include <common.h>

void DECOMP_ElimBG_HandleState(struct GameTracker* gGT)
{
	u_char *puVar1;
	u_int *puVar2;
	short sVar3;
	short sVar4;
	struct GameTracker *psVar5;
	u_char uVar6;
	int iVar7;
	int iVar8;
	POLY_FT4 *p;
	u_int uVar9;
	u_char uVar10;
	u_int uVar11;
	int iVar12;
	u_char auStack48 [4];
	u_char auStack44 [4];
	u_char auStack40 [4];
	u_int uStack36;
	
	psVar5 = sdata->gGT;
	if (sdata->pause_state == 3)
	{
		puVar1 = auStack48 + 3;
		uVar11 = (u_int)puVar1 & 3;
		*(u_int *)(puVar1 + -uVar11) = *(u_int *)(puVar1 + -uVar11) & -1 << (uVar11 + 1) * 8 | 0x200U >> (3 - uVar11) * 8;
		auStack48 = 0x200;
		puVar1 = auStack44 + 3;
		uVar11 = (u_int)puVar1 & 3;
		*(u_int *)(puVar1 + -uVar11) = *(u_int *)(puVar1 + -uVar11) & -1 << (uVar11 + 1) * 8 | 0x1000040U >> (3 - uVar11) * 8;
		auStack44 = 0x1000040;
		puVar1 = auStack40 + 3;
		uVar11 = (u_int)puVar1 & 3;
		*(u_int *)(puVar1 + -uVar11) = *(u_int *)(puVar1 + -uVar11) & -1 << (uVar11 + 1) * 8 | 0x240U >> (3 - uVar11) * 8;
		auStack40 = 0x240;
		uVar11 = (int)&uStack36 + 3U & 3;
		puVar2 = (u_int *)(((int)&uStack36 + 3U) - uVar11);
		*puVar2 = *puVar2 & -1 << (uVar11 + 1) * 8 | 0x1000040U >> (3 - uVar11) * 8;
		uStack36 = 0x1000040;
		LoadImage((RECT *)auStack48, sdata->pause_VRAM_Backup_PrimMem[0]);
		LoadImage((RECT *)auStack40, sdata->pause_VRAM_Backup_PrimMem[1]);
		DrawSync(0);
		gGT->db[0].primMem.end = (void *)((int)sdata->pause_VRAM_Backup_PrimMem[0] + 0x8000);
		gGT->db[1].primMem.end = (void *)((int)sdata->pause_VRAM_Backup_PrimMem[1] + 0x8000);
		ElimBG_ToggleAllInstances(gGT, 0);
		sdata->pause_state = 0;
	}
	else if (sdata->pause_state != 0)
	{
		if (sdata->pause_state == 1)
		{
			gGT->renderFlags = gGT->renderFlags & 0x1000 | 0x20;
			psVar5->hudFlags = psVar5->hudFlags & 0xf6;
			ElimBG_SaveScreenshot_Full(gGT);
			ElimBG_ToggleAllInstances(gGT, 1);
			sdata->pause_state = 2;
		}
		iVar12 = 0;
		do
		{
			uVar11 = 0;
			sVar3 = (short)iVar12;
			do
			{
				p = (POLY_FT4 *)(gGT->backBuffer->primMem).curr;
				(gGT->backBuffer->primMem).curr = p + 1;
				*(u_char *)((int)&p->tag + 3) = 9;
				p->code = 0x2c;
				sVar4 = (short)uVar11;
				p->b0 = 0x80;
				p->g0 = 0x80;
				p->r0 = 0x80;
				p->x0 = sVar3;
				p->y0 = sVar4;
				p->x1 = sVar3 + 0x80;
				p->y1 = sVar4;
				p->x2 = sVar3;
				p->y2 = sVar4 + 0x10;
				p->x3 = sVar3 + 0x80;
				p->y3 = sVar4 + 0x10;
				iVar7 = iVar12;
				if (iVar12 < 0)
				{
					iVar7 = iVar12 + 3;
				}
				uVar9 = (iVar7 >> 2) + 0x200;
				iVar7 = (int)(uVar9 & 0x3ff) >> 6;
				p->tpage = (ushort)((int)(uVar11 & 0x100) >> 4) | (ushort)iVar7 | (ushort)((uVar11 & 0x200) << 2);
				p->clut = 0x3fe0;
				iVar8 = (uVar9 + iVar7 * -0x40) * 4;
				uVar10 = (u_char)uVar11;
				p->v0 = uVar10;
				uVar6 = (u_char)iVar8;
				p->u0 = uVar6;
				if (iVar8 + 0x80 < 0x100)
				{
					p->u1 = uVar6 + 0x80;
				}
				else
				{
					p->u1 = 0xff;
				}
				iVar7 = (uVar9 + iVar7 * -0x40) * 4;
				p->v2 = uVar10 + 0x10;
				p->v1 = uVar10;
				uVar6 = (u_char)iVar7;
				p->u2 = uVar6;
				if (iVar7 + 0x80 < 0x100)
				{
					p->u3 = uVar6 + 0x80;
				}
				else
				{
					p->u3 = 0xff;
				}
				uVar11 = uVar11 + 0x10;
				p->v3 = (u_char)uVar11;
				AddPrim((void *)((int)(gameTracker->tileView_UI).ptrOT + 0x10), p);
			} while ((int)uVar11 < 0xd8);
			iVar12 = iVar12 + 0x80;
		} while (iVar12 < 0x200);
	}
	return;
}