#include <common.h>

void DECOMP_AH_MaskHint_LerpVol(int param_1)
{
    int diff;
    int volume;
	u_char backup;
	
    for (char i = 0; i < 3; i++)
    {
		backup = ((u_char*)0x800b5668)[i];
		
        diff = ((short*)0x800b54ec)[i] - backup;
        volume = backup + ((diff * param_1) >> 12);
        
        // restore backups of Volume settings,
		// that were originally saved in AH_MaskHint_Start
        howl_VolumeSet(i, volume & 0xFF);
    }
}
