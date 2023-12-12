#include <common.h>

void DECOMP_Music_SetIntro(void)
{
    u_int boolSuccess;
    struct Bank thisBank;

    sdata->audioDefaults[7] = 0;

    Bank_Load(33, &thisBank);

    while(Bank_AssignSpuAddrs() == 0) {}
	
    howl_SetSong(28);
    
	while(howl_LoadSong() == 0) {}
}