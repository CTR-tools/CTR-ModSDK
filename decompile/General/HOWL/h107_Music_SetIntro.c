#include <common.h>

void DECOMP_Music_SetIntro(void)
{
    u_int boolSuccess;
    struct Bank thisBank;

    sdata->audioDefaults[7] = 0;

    DECOMP_Bank_Load(33, &thisBank);

    while(DECOMP_Bank_AssignSpuAddrs() == 0) {}
	
    howl_SetSong(28);
    
	while(howl_LoadSong() == 0) {}
}