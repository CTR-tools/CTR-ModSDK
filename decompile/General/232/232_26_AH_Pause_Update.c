#include <common.h>

void DECOMP_AH_Pause_Update()
{
	struct GameTracker* gGT;
	gGT = sdata->gGT;
	
	if(D232.ptrPauseObject == 0)
	{
		struct PauseObject* ptrPauseObject;
		ptrPauseObject = &D232.pauseObject;
		
		D232.ptrPauseObject = ptrPauseObject;
		D232.pausePageTimer = 0;
		D232.pausePageCurr = gGT->levelID-0x19;
		gGT->advPausePage = D232.pausePageCurr;
		
		// 0 = size
		// 0 = no relation to param4
		// 0x300 = SmallStackPool
		// 0xd = "other" thread bucket
		struct Thread* t =
			DECOMP_PROC_BirthWithObject(0x30d, 0, 0, 0);
			
		ptrPauseObject->t = t;
		
		for(int i = 0; i < 0xe; i++)
		{
			struct Instance* inst =
				DECOMP_INSTANCE_Birth3D(
					gGT->modelPtr[0x5F], 0, t);
					
			ptrPauseObject->PauseMember[i].inst = inst;
			ptrPauseObject->PauseMember[i].rot[0] = 0;
			ptrPauseObject->PauseMember[i].rot[1] = 0;
			ptrPauseObject->PauseMember[i].rot[2] = 0;
			
			// make invisible (0x80)
			// creditghost (0x400)
			// specular light (0x20000)
			inst->flags |= 0x20480;
			
			struct InstDrawPerPlayer *idpp = 
				INST_GETIDPP(inst);
				
			idpp[0].pushBuffer = &gGT->pushBuffer_UI;
			for(int j = 1; j < gGT->numPlyrCurrGame; j++)
				idpp[j].pushBuffer = 0;
			
			*(int*)&inst->matrix.m[0][0] = 0x1000;
			*(int*)&inst->matrix.m[0][2] = 0;
			*(int*)&inst->matrix.m[1][1] = 0x1000;
			*(int*)&inst->matrix.m[2][0] = 0;
			inst->matrix.m[2][2] = 0x1000;
			inst->matrix.t[2] = 0x100;
		}
	}
	
	int tap = sdata->buttonTapPerPlayer[0];
	
	if((tap & (BTN_RIGHT|BTN_LEFT)) != 0)
	{
		if((tap & BTN_RIGHT) != 0)
		{
			D232.pausePageDir = 1;
			gGT->advPausePage += 1;

			if(gGT->advPausePage > 6)
				gGT->advPausePage = 0;
		}
	
		// assume BTN_LEFT
		else
		{
			D232.pausePageDir = -1;
			gGT->advPausePage += -1;
			
			if(gGT->advPausePage < 0)
				gGT->advPausePage = 6;
			
		}
		
		DECOMP_OtherFX_Play(0, 1);
	}
	
	// page is flipping
	if (D232.pausePageTimer != 0)
		D232.pausePageTimer--;
	
	// page is not flipping, flip desired
	else if(gGT->advPausePage != D232.pausePageCurr)
	{
		D232.pausePagePrev = D232.pausePageCurr;
		D232.pausePageDir_dup = D232.pausePageDir;
		
		D232.pausePageTimer = FPS_DOUBLE(8);
		
		D232.pausePageCurr = gGT->advPausePage;
	}
	
	int pageID;
	int posX;
	
	// second half
	if (D232.pausePageTimer < FPS_DOUBLE(5))
	{
		pageID = D232.pausePageCurr;
		posX = D232.pausePageTimer * D232.pausePageDir * FPS_HALF(-0x80);
	}
	
	// first half
	else
	{
		pageID = D232.pausePagePrev;
		posX = (FPS_DOUBLE(8)-D232.pausePageTimer) * D232.pausePageDir * FPS_HALF(0x80);
	}
	
	DECOMP_AH_Pause_Draw(pageID, posX);
}