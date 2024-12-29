#include <common.h>

void DECOMP_GAMEPROG_NewGame_OnBoot()
{
	DECOMP_GAMEPROG_NewProfile_OutsideAdv(&sdata->gameProgress);
	DECOMP_GAMEPROG_NewProfile_InsideAdv(&sdata->advProgress);
	DECOMP_GAMEPROG_GetPtrHighScoreTrack();
}