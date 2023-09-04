#include <common.h>

void DECOMP_ElimBG_SaveScreenshot_Full(struct GameTracker* gGT)
{
	u_char *puVar1;
	u_int uVar2;
	int iVar3;
	void *pvVar4;
	int iVar5;
	void *pvVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	short sVar10;
	u_char auStack72 [4];
	u_char auStack68 [4];
	u_char auStack64 [4];
	u_char auStack60 [4];
	RECT local_38;
	RECT local_30;
	
	iVar9 = 0;
	puVar1 = auStack72 + 3;
	uVar2 = (u_int)puVar1 & 3;
	*(u_int *)(puVar1 + -uVar2) = *(u_int *)(puVar1 + -uVar2) & -1 << (uVar2 + 1) * 8 | 0x200U >> (3 - uVar2) * 8;
	auStack72 = 0x200;
	puVar1 = auStack68 + 3;
	uVar2 = (u_int)puVar1 & 3;
	*(u_int *)(puVar1 + -uVar2) = *(u_int *)(puVar1 + -uVar2) & -1 << (uVar2 + 1) * 8 | 0x1000040U >> (3 - uVar2) * 8;
	auStack68 = 0x1000040;
	puVar1 = auStack64 + 3;
	uVar2 = (u_int)puVar1 & 3;
	*(u_int *)(puVar1 + -uVar2) = *(u_int *)(puVar1 + -uVar2) & -1 << (uVar2 + 1) * 8 | 0x240U >> (3 - uVar2) * 8;
	auStack64 = 0x240;
	puVar1 = auStack60 + 3;
	uVar2 = (u_int)puVar1 & 3;
	*(u_int *)(puVar1 + -uVar2) = *(u_int *)(puVar1 + -uVar2) & -1 << (uVar2 + 1) * 8 | 0x1000040U >> (3 - uVar2) * 8;
	auStack60 = 0x1000040;
	pvVar6 = gGT->db[0].primMem.end;
	
	// make pointers relative to primMem.end for vram copy, then overwrite vram with pause image
	sdata->pause_VRAM_Backup_PrimMem[0] = (void *)((int)pvVar6 + -0x8000);
	sdata->pause_VRAM_Backup_PrimMem[2] = (void *)((int)pvVar6 + -0xc000);
	pvVar4 = gGT->db[1].primMem.end;
	sdata->pause_VRAM_Backup_PrimMem[4] = (void *)((int)pvVar6 + -0xc800);
	sdata->pause_VRAM_Backup_PrimMem[1] = (void *)((int)pvVar4 + -0x8000);
	sdata->pause_VRAM_Backup_PrimMem[3] = (void *)((int)pvVar4 + -0xc000);
	sdata->pause_VRAM_Backup_PrimMem[5] = (void *)((int)pvVar4 + -0xc800);
	gGT->db[0].primMem.end = sdata->pause_VRAM_Backup_PrimMem[4];
	gGT->db[1].primMem.end = sdata->pause_VRAM_Backup_PrimMem[5];
	
	// copy vram into PrimMem (?)
	StoreImage((RECT *)auStack72, sdata->pause_VRAM_Backup_PrimMem[0]);
	StoreImage((RECT *)auStack64, sdata->pause_VRAM_Backup_PrimMem[1]);

	local_38.w = 0x200;
	local_38.x = 0;
	local_38.h = 8;
	
	// swapchain index * Y-offset of second swapchain image
	sVar10 = (short)gGT->swapchainIndex * 0x128;
	
	local_38.y = sVar10;
	StoreImage(&local_38, sdata->pause_VRAM_Backup_PrimMem[2]);
	iVar7 = 0;
	do
	{
		iVar3 = -iVar9;
		iVar9 = iVar3 + 1;
		local_38.y = sVar10 + (short)iVar7 + 8;
		local_38.x = 0;
		local_38.w = 0x200;
		local_38.h = 8;
		DrawSync(0);
		StoreImage(&local_38, sdata->pause_VRAM_Backup_PrimMem_2[iVar9 + 2]);
		ElimBG_SaveScreenshot_Chunk(sdata->pause_VRAM_Backup_PrimMem_2[-iVar9 + 5], sdata->pause_VRAM_Backup_PrimMem_2[-iVar9 + 3], 0x1000);
		local_30.x = 0x200;
		local_30.w = 0x80;
		local_30.h = 8;
		iVar8 = iVar7 + 8;
		local_30.y = (short)iVar7;
		LoadImage(&local_30, sdata->pause_VRAM_Backup_PrimMem_2[-iVar9 + 5]);
		iVar5 = iVar7 + 0x10;
		iVar7 = iVar8;
	} while (iVar5 < 0xd8);
	DrawSync(0);
	ElimBG_SaveScreenshot_Chunk(sdata->pause_VRAM_Backup_PrimMem_2[iVar3 + 5], sdata->pause_VRAM_Backup_PrimMem_2[iVar9 + 2], 0x1000);
	local_30.x = 0x200;
	local_30.y = (short)iVar8;
	local_30.w = 0x80;
	local_30.h = 8;
	LoadImage(&local_30, sdata->pause_VRAM_Backup_PrimMem_2[iVar3 + 5]);
	local_30.y = 0xff;
	local_30.w = 0x10;
	local_30.x = 0x200;
	local_30.h = 1;
	LoadImage(&local_30, sdata->pauseScreenStrip);
	return;
}