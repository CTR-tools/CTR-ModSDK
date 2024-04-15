#include <common.h>

// temporary workaround
extern struct Ovr233_Credits_BSS* creditsBSS;

int CS_Credits_IsTextValid()
{
	// This dang byte budget
	//struct CreditsObj* creditsObj = &creditsBSS->creditsObj;
	struct CreditsObj* creditsObj = 0x800b94bc;
	
	if(creditsObj->epilogue_topString != 0)
		return 0;
	
	creditsObj->countdown = FPS_DOUBLE(360);
	return 1;
}