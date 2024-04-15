#include <common.h>

// temporary workaround
extern struct Ovr233_Credits_BSS* creditsBSS;

void CS_Credits_ThTick();

void CS_Credits_Init()
{
	int i;
	int bitIndex;
	struct Instance* inst;
	
	// optimization
	//int boolAllBlue;
	#define boolAllBlue creditsBSS->boolAllBlue
	
	int boolAllGold;
	struct GameTracker* gGT;
	struct AdvProgress* advProg;
	struct CreditsObj* creditsObj;
	struct CreditsLevHeader* CLH;
	struct CreditsLevHeader* creditsDst;
	
	gGT = sdata->gGT;
	advProg = &sdata->advProgress;
	creditsObj = &creditsBSS->creditsObj;
	
	void** pointers = ST1_GETPOINTERS(gGT->level1->ptrSpawnType1);
	CLH = pointers[ST1_CREDITS];
	
	creditsBSS->DancerThread = 0;
	
	boolAllBlue = 1;
	boolAllGold = 1;
	
	for(i = 0; i < 0x12; i++)
	{
		if (boolAllBlue != 0)
		{
			bitIndex = i + 0x16;
			boolAllBlue = CHECK_ADV_BIT(advProg->rewards, bitIndex);
		}
		
		if (boolAllGold != 0)
		{
			bitIndex = i + 0x28;
			boolAllGold = CHECK_ADV_BIT(advProg->rewards, bitIndex);
		}	
	}
	
	#undef boolAllBlue
	
	if(boolAllGold != 0)
	{
		gGT->numWinners = 1;
		gGT->winnerIndex[0] = 0;
		gGT->confetti.numParticles_max = 250;
		gGT->confetti.unk2 = 250;
		gGT->renderFlags |= 4;
	}
	
	// 0 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0xd = "other" thread bucket
	creditsBSS->CreditThread =
		PROC_BirthWithObject(0x30d, CS_Credits_ThTick, 0, 0);
		
	memset(creditsObj, 0, sizeof(struct CreditsObj));
	creditsObj->countdown = FPS_DOUBLE(360);
	
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
		creditsObj->creditGhostInst[4-i] = inst;
	
		*(int*)(((unsigned int)&inst->matrix) + 0x0) = 0x1000;
		*(int*)(((unsigned int)&inst->matrix) + 0x4) = 0;
		*(int*)(((unsigned int)&inst->matrix) + 0x8) = 0x1000;
		*(int*)(((unsigned int)&inst->matrix) + 0xC) = 0;
		inst->matrix.m[2][2] = 0x1000;
		
		inst->flags |= 0x400;
		
		struct InstDrawPerPlayer* idpp = INST_GETIDPP(inst);
		idpp[0].pushBuffer = &gGT->pushBuffer_UI;
		
		#if 0
		// OG game erases other idpp's, but just ignore it
		#endif
	}
	
	creditsDst = MEMPACK_AllocHighMem(CLH->size /* "credits strings" */);
	
	memcpy(creditsDst, CLH, CLH->size);
	
	creditsBSS->numStrings = creditsDst->numStrings;
	
	char** ptrStrings = CREDITSHEADER_GETSTRINGS(creditsDst);
	creditsBSS->ptrStrings = ptrStrings;
	
	for(i = 0; i < creditsBSS->numStrings; i++)
	{
		ptrStrings[i] =
		((unsigned int)ptrStrings[i] + (unsigned int)creditsDst);
	}
	
	creditsObj->credits_posY = 340;
	creditsObj->credits_topString = ptrStrings[0x14];
}

// temporary workaround
struct Ovr233_Credits_BSS* creditsBSS = 0x800b9488;