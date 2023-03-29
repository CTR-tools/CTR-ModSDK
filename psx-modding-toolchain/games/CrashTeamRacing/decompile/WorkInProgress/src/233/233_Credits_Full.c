#include <common.h>

// declared at bottom
extern struct Ovr233_Credits_BSS creditsBSS;

void CS_Credits_Init()
{
	int i;
	int bitIndex;
	
	// optimization
	//int boolAllBlue;
	#define boolAllBlue creditsBSS.boolGotoScrapbook
	
	int boolAllGold;
	struct GameTracker* gGT;
	struct AdvProgress* advProg;
	struct CreditsObj* creditsObj;
	
	gGT = sdata->gGT;
	advProg = &sdata->advProgress;
	creditsObj = &creditsBSS.creditsObj;
	
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
	
	// === AllocHighMem ===
	
	// === memcpy from Crash LEV ===
	
	// === Run Pointer Map ===
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