#include <common.h>

// temporary workaround
extern struct Ovr233_Credits_BSS* creditsBSS;

void CS_Credits_End()
{
	int levID;
	struct GameTracker* gGT = sdata->gGT;
	
	// erase 5 instances
	CS_Credits_DestroyCreditGhost();
	
	// kill thread
	creditsBSS->CreditThread->flags |= 0x800;
	
	// go to gemstone valley
	if(creditsBSS->boolAllBlue == 0)
	{
		levID = 0x19;
		
		gGT->gameMode1 |= ADVENTURE_MODE;
	}
	
	// go to scrapbook
	else
	{
		sdata->mainMenuState = 5;
		
		levID = 0x40;
	}
	
	MainRaceTrack_RequestLoad(levID);

	gGT->renderFlags &= 0xfffffffb;
}
