#include <common.h>

// temporary workaround
extern struct Ovr233_Credits_BSS* creditsBSS;

void CS_Credits_NewDancer(struct Thread* dancerTh, int dancerModelID)
{
	struct CreditsObj* creditsObj = &creditsBSS->creditsObj;
	
	// kill any living thread
	if (creditsBSS->DancerThread != 0)
		creditsBSS->DancerThread->flags |= 0x800;

	// store globally, make instance invisible
	creditsBSS->DancerThread = dancerTh;
	creditsBSS->dancerInst_invisible = dancerTh->inst;
	creditsBSS->dancerInst_invisible->flags |= 0x80;
	
	creditsObj->countdown = FPS_DOUBLE(360);
	
	char** ptrStrings = creditsBSS->ptrStrings;
	
	// less than TAWNA1
	if(dancerModelID < 0x8f)
	{
		// subtract CRASHDANCE
		creditsObj->epilogue_topString = 
			ptrStrings[dancerModelID - 0x7e];
	}
	
	// TAWNA
	else
	{
		// subtract an extra cause of GARAGE_TOP
		creditsObj->epilogue_topString = 
			ptrStrings[(dancerModelID - 0x7e) - 1];
	}
	
	creditsObj->epilogueCount200 = 200;
	
	creditsObj->epilogue_nextString = 
		CS_Credits_GetNextString(creditsObj->epilogue_topString);
}
