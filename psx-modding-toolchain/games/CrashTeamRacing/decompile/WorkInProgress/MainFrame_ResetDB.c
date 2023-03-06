#include <common.h>

void MainFrame_ResetDB(struct GameTracker* sdata->gGT)
{
	struct GameTracker* psVar1;
	int iVar2;
	u_long* puVar3;
	int iVar4;
	struct DB* psVar5;
	struct GameTracker* psVar6;
	
	LOAD_Hub_Main(sdata_ptrBigfile1);
	iVar4 = 1 - sdata->gGT->swapchainIndex;
	sdata->gGT->backBuffer = (struct DB*)((int)sdata->gGT + iVar4*  0xa4 + 0x18);
	sdata->gGT->swapchainIndex = iVar4;
	sdata->gGT->frameTimer_MainFrame_ResetDB++;
	*(u_char*)&sdata->gGT->backBuffer->unk_primMemRelated = 0;
	(sdata->gGT->backBuffer->primMem).curr = (sdata->gGT->backBuffer->primMem).start;
	(sdata->gGT->backBuffer->primMem).unk1 = 0;
	(sdata->gGT->backBuffer->otMem).curr = (sdata->gGT->backBuffer->otMem).start;
	CTR_EmptyFunc_MainFrame_ResetDB();
	DecalGlobal_EmptyFunc_MainFrame_ResetDB();
	ClearOTagR((u_long*)sdata->gGT->ot_camera110_UI[sdata->gGT->swapchainIndex], (u_int)(u_char)::sdata->gGT->numPlyrCurrGame << 10 | 6);
	psVar1 = ::sdata->gGT;
	iVar4 = 0;
	psVar6 = sdata->gGT;
	if (::sdata->gGT->numPlyrCurrGame != '\0')
	{
		do
		{
			iVar2 = (u_int)(u_char)psVar1->numPlyrCurrGame - iVar4;
			iVar4 = iVar4 + 1;
			psVar6->camera110[0].ptrOT = (u_long*)((int)sdata->gGT->ot_camera110_UI[sdata->gGT->swapchainIndex] + (iVar2 - 1) * 0x1000 + 0x18);
			psVar6 = (struct GameTracker*)(psVar6->db[1].drawEnv.dr_env.code + 0xd);
		} while (iVar4 < (int)(u_int)(u_char)psVar1->numPlyrCurrGame);
	}
	if (iVar4 < 4)
	{
		iVar2 = (int)sdata->gGT->db + iVar4 * 0x110 - 0x18;
		do
		{
			iVar4 = iVar4 + 1;
			*(int*)(iVar2 + 0x25c) = (int)sdata->gGT->ot_camera110_UI[sdata->gGT->swapchainIndex] + 0x3018;
			iVar2 = iVar2 + 0x110;
		} while (iVar4 < 4);
	}
	psVar5 = sdata->gGT->backBuffer;
	puVar3 = (u_long*)((int)sdata->gGT->ot_camera110_UI[sdata->gGT->swapchainIndex] + 4);
	(sdata->gGT->camera110_UI).ptrOT = puVar3;
	(psVar5->otMem).startPlusFour = puVar3;
	return;
}