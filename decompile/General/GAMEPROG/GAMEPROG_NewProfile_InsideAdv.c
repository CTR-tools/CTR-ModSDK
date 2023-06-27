#include <common.h>

void DECOMP_GAMEPROG_NewProfile_InsideAdv(struct AdvProgress* adv)
{
	// clear
	memset(adv, 0x0, sizeof(struct AdvProgress));

	// no character selected
	adv->characterID = -1;
		
	// N Sane Beach
	adv->HubLevYouSavedOn = 0x1a;
}