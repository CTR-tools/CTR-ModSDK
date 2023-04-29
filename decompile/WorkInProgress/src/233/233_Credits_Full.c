#include <common.h>

// declared at bottom
//extern struct Ovr233_Credits_BSS creditsBSS;

// temporary workaround
extern struct Ovr233_Credits_BSS* creditsBSS;
#define creditsBSS. creditsBSS->

#if 0
void CS_Credits_DrawNames(struct CreditsObj* creditsObj)
{
	int currY;
	char* currString;
	char* nextString;
	
	if(creditsObj->credits_topString == 0) return;
	
	// make text move upward
	creditsObj->credits_posY--;
	
	// if scroll off-screen
	if(creditsObj->credits_posY < -20)
	{
		creditsObj->credits_topString = 
			CS_Credits_GetNextString(creditsObj->credits_topString);
			
		creditsObj->credits_posY += 20;
	}
	
	currY = creditsObj->credits_posY;
	currString = creditsObj->credits_topString;
	
	// keep going till lines draw off-screen
	if(currY < 0x114)
	{
		// [still need this]
	}
}

void CS_Credits_DrawEpilogue(struct CreditsObj* creditsObj)
{
	if(creditsBSS.boolAllBlue == 0) return;
	if(creditsObj->epilogue_topString == 0) return;
	
	// === To do ===
}
#endif

// CS_Credits_ThTick is it's own WIP file

// CS_Credits_Init has been moved to General

int CS_Credits_IsTextValid()
{
	struct CreditsObj* creditsObj = &creditsBSS.creditsObj;
	
	if(creditsObj->epilogue_topString != 0)
		return 0;
	
	creditsObj->countdown = 360;
	return 1;
}

// CS_Credits_NewDancer is in General

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

// CS_Credits_End moved to General

//struct Ovr233_Credits_BSS creditsBSS;

// temporary workaround
struct Ovr233_Credits_BSS* creditsBSS = 0x800b9488;