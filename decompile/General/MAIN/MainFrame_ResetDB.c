#include <common.h>

void DECOMP_MainFrame_ResetDB(struct GameTracker* gGT)
{
	struct GameTracker* psVar1;
	int iVar2;
	u_long* puVar3;
	int iVar4;
	struct DB* db;
	int ot_tileView_UI;
	
// Dont use this in DECOMP until drivers->stepFlagSet is written
#ifndef REBUILD_PS1
	// check if new adv hub should be loaded,
	// this was a random place for ND to put it
	LOAD_Hub_Main(sdata->ptrBigfile1);
#endif
	
#ifndef REBUILD_PC
	gGT->swapchainIndex = 1 - gGT->swapchainIndex;
#endif
	
	gGT->backBuffer = &gGT->db[gGT->swapchainIndex];
	gGT->frameTimer_MainFrame_ResetDB++;
	
	ot_tileView_UI = gGT->ot_tileView_UI[gGT->swapchainIndex];
	
	db = gGT->backBuffer;
	*(u_char*)&db->unk_primMemRelated = 0;
	db->primMem.curr = db->primMem.start;
	db->primMem.unk1 = 0;
	db->otMem.curr = db->otMem.start;
	
// These functions literally do nothing,
// even in the OG game, they're empty
#if 0
	CTR_EmptyFunc_MainFrame_ResetDB();
	DecalGlobal_EmptyFunc_MainFrame_ResetDB();
#endif
	
	ClearOTagR(ot_tileView_UI, gGT->numPlyrCurrGame << 10 | 6);
	
	for(iVar4 = 0; iVar4 < gGT->numPlyrCurrGame; iVar4++)
	{
		iVar2 = (u_int)(u_char)gGT->numPlyrCurrGame - iVar4;
			
		gGT->tileView[iVar4].ptrOT = 
			(int)ot_tileView_UI + 
			(gGT->numPlyrCurrGame - iVar4 - 1) * 0x1000 
			+ 0x18;
	}
	
	for(iVar4; iVar4 < 4; iVar4++)
	{
		// but why?
		gGT->tileView[iVar4].ptrOT = 
			(int)ot_tileView_UI + 
			3 * 0x1000 
			+ 0x18;
	}
	
	puVar3 = (int)ot_tileView_UI + 4;
	gGT->tileView_UI.ptrOT = puVar3;
	db->otMem.startPlusFour = puVar3;
	return;
}