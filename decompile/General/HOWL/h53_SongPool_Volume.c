#include <common.h>

void DECOMP_SongPool_Volume(struct Song* song, int newVol, int newStep, int boolImm)
{
	// if immediate change request, 
	// without fading volume
	if(boolImm != 0)
	{
		song->vol_Curr = newVol;
	}
	
	song->vol_New = newVol;
	song->vol_StepRate = newStep;
}