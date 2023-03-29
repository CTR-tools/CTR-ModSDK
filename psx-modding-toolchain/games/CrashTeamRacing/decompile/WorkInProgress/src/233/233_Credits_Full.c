#include <common.h>

// declared at bottom
extern struct Ovr233_Credits_BSS creditsBSS;

// should have parameter, but it's not used
void CS_Credits_ThTick()
{
	int i;
	struct Instance* danceInv;
	struct CreditsObj* creditsObj;
	
	creditsObj = &creditsBSS.creditsObj;
	
	danceInv = creditsBSS.dancerInst_invisible;

	// waste?
	creditsObj->creditDanceInst = danceInv;
	
	if(danceInv != 0)
	{
		// make invisible
		danceInv->flags |= 0x80;
		
		danceInv->matrix.t[0] = creditsBSS.creditGhost_Pos[0];
		danceInv->matrix.t[1] = creditsBSS.creditGhost_Pos[1];
		danceInv->matrix.t[2] = creditsBSS.creditGhost_Pos[2];
		
		// once every 4 frames
		if((sdata->gGT->timer & 3) == 0)
		{
			for(i = 4; i > 0; i--)
			{
				CS_Credits_AnimateCreditGhost(
					creditsObj->creditGhostInst[i], 
					creditsObj->creditGhostInst[i-1], i
				);
				
				creditsObj->creditGhostInst[i] =
				creditsObj->creditGhostInst[i-1];
			}
			
			CS_Credits_AnimateCreditGhost(
				creditsObj->creditGhostInst[0],
				danceInv, i);
				
			creditsObj->creditGhostModel[0] = danceInv->model;
		}
		
		// 3 of 4 frames
		else
		{
			CS_Credits_AnimateCreditGhost(
				creditsObj->creditGhostInst[0],
				danceInv, 0);
			
			for(i = 1; i < 5; i++)
			{
				// this is not danceInv, I'm saving regsiters
				danceInv = creditsObj->creditGhostInst[i];
				
				danceInv->scale[0] += 0x4B;
				danceInv->scale[0] += 0x4B;
				danceInv->scale[0] += 0x4B;
				danceInv->alphaScale += 0x9d;
			}
		}
	}
	
	if (creditsObj->cooldown > 0)
		creditsObj->cooldown--;
	
	CS_Credits_DrawNames(creditsObj);
	CS_Credits_DrawEpilogue(creditsObj);
}

void CS_Credits_Init()
{
	int i;
	int bitIndex;
	struct Instance* inst;
	
	// optimization
	//int boolAllBlue;
	#define boolAllBlue creditsBSS.boolGotoScrapbook
	
	int boolAllGold;
	struct GameTracker* gGT;
	struct AdvProgress* advProg;
	struct CreditsObj* creditsObj;
	struct CreditsLevHeader* CLH;
	struct CreditsLevHeader* creditsDst;
	
	gGT = sdata->gGT;
	advProg = &sdata->advProgress;
	creditsObj = &creditsBSS.creditsObj;
	CLH = gGT->level1->ptrSpawnType1->pointers[6];
	
	creditsBSS.DancerThread = 0;
	creditsBSS.boolGotoScrapbook = 1;
	
	boolAllBlue = 1;
	boolAllGold = 1;
	
	for(i = 0; i < 0x12; i++)
	{
		if (boolAllBlue != 0)
		{
			bitIndex = i + 0x16;
			boolAllBlue = (advProg->rewards[bitIndex>>5] >> bitIndex) & 1;
		}
		
		if (boolAllGold != 0)
		{
			bitIndex = i + 0x28;
			boolAllGold = (advProg->rewards[bitIndex>>5] >> bitIndex) & 1;
		}	
	}
	
	if(boolAllGold != 0)
	{
		gGT->numWinners = 1;
		gGT->winnerIndex[0] = 0;
		gGT->confetti.numParticles_max = 250;
		gGT->confetti.unk2 = 250;
	}
	
	// 0 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0xd = "other" thread bucket
	creditsBSS.CreditThread =
		THREAD_BirthWithObject(0x30d, CS_Credits_ThTick, 0, 0);
		
	memset(creditsObj, 0, sizeof(struct CreditsObj));
	creditsObj->countdown = 360;
	
	// === 5 instances ===
	for(i = 0; i < 5; i++)
	{
		#if 0
		// OG game passes CreditsThread as parameter,
		// but that's pointless, so it is removed
		#endif
		
		// STATIC_AKUAKU for some reason?
		inst = INSTANCE_Birth3D(gGT->modelPtr[0x39], 0, 0);
		
		// save instance
		creditsObj->creditGhostInst[i] = inst;
	
		*(int*)(((unsigned int)&inst->matrix) + 0x0) = 0x1000;
		*(int*)(((unsigned int)&inst->matrix) + 0x4) = 0;
		*(int*)(((unsigned int)&inst->matrix) + 0x8) = 0x1000;
		*(int*)(((unsigned int)&inst->matrix) + 0xC) = 0;
		inst->matrix[2][2] = 0x1000;
		
		inst->flags |= 0x400;
		
		inst->idpp[0].tileView = &gGT->tileView_UI;
		
		#if 0
		// OG game erases other idpp's, but just ignore it
		#endif
	}
	
	creditsDst = MEMPACK_AllocHighMem(CLH->size /* "credits strings" */);
	
	memcpy(creditsDst, CLH, CLH->size);
	
	creditsBSS.numStrings = creditsDst->numStrings;
	creditsBSS.ptrStrings = creditsDst->ptrStrings;
	
	for(i = 0; i < creditsBSS.numStrings; i++)
	{
		creditsDst->ptrStrings[i] =
		((unsigned int)creditsDst->ptrStrings + (unsigned int)creditsDst);
	}
	
	creditsObj->credits_posY = 340;
	creditsObj->credits_topString = creditsDst->ptrStrings[0x14];
}

int CS_Credits_IsTextValid()
{
	struct CreditsObj* creditsObj = &creditsBSS.creditsObj;
	
	if(creditsObj->epilogue_topString != 0)
		return 0;
	
	creditsObj->countdown = 360;
	return 1;
}

void CS_Credits_NewDancer(struct Thread* dancerTh, int dancerModelID)
{
	struct CreditsObj* creditsObj = &creditsBSS.creditsObj;
	
	// kill any living thread
	if (creditsBSS.DancerThread != 0)
		creditsBSS.DancerThread->flags |= 0x800;

	// store globally, make instance invisible
	creditsBSS.DancerThread = dancerTh;
	creditsBSS.dancerInst_invisible = dancerTh->inst;
	creditsBSS.dancerInst_invisible->flags |= 0x80;
	
	creditsObj->countdown = 360;
	
	// less than TAWNA1
	if(dancerModelID < 0x8f)
	{
		// subtract CRASHDANCE
		creditsObj->epilogue_topString = 
			creditsBSS.ptrStrings[dancerModelID - 0x7e]
	}
	
	// TAWNA
	else
	{
		// subtract an extra cause of GARAGE_TOP
		creditsObj->epilogue_topString = 
			creditsBSS.ptrStrings[(dancerModelID - 0x7e) - 1]
	}
	
	creditsObj->epilogueCount200 = 200;
	
	creditsObj->epilogue_nextString = 
		CS_Credits_GetNextString(creditsObj->epilogue_topString);
}

int CS_Credits_NewCreditGhosts()
{
	int i;
	struct CreditsObj* creditsObj = &creditsBSS.creditsObj;
	
	for(i = 0; i < 5; i++)
	{
		if(
			creditsObj->creditGhostModel[i] !=
			dancerInst_invisible->model
		)
		{
			return 0;
		}
	}
	
	return 1;
}

void CS_Credits_End()
{
	int levID;
	struct GameTracker* gGT = sdata->gGT;
	
	// erase 5 instances
	CS_Credits_DestroyCreditGhost();
	
	// kill thread
	creditsBSS.CreditThread->flags |= 0x800;
	
	// go to gemstone valley
	if(creditBSS.boolGotoScrapbook == 0)
	{
		levID = 0x19;
		
		gGT->gameMode1 |= 0x80000;
	}
	
	// go to scrapbook
	else
	{
		sdata->mainMenuState = 5;
		
		levID = 0x40
	}
	
	MainRaceTrack_RequestLoad(levID);

	gGT->renderFlags &= 0xfffffffb;
}


struct Ovr233_Credits_BSS creditsBSS;