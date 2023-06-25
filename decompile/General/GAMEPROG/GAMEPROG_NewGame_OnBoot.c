#include <common.h>

void DECOMP_GAMEPROG_NewGame_OnBoot()
{
	GAMEPROG_NewProfile_OutsideAdv(&sdata->gameProgress);
	GAMEPROG_NewProfile_InsideAdv(&sdata->advProgress);
	GAMEPROG_GetPtrHighScoreTrack();
}