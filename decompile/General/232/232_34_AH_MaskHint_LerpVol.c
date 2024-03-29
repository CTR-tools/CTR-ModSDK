#include <common.h>

void DECOMP_AH_MaskHint_LerpVol(int param_1)
{
    int diff;
    int volume;
	u_char backup;
	
    for (char i = 0; i < 3; i++)
    {
		backup = D232.audioBackup[i];
		
        diff = D232.maskAudioSettings[i] - backup;
        volume = backup + ((diff * param_1) >> 12);
        
        // restore backups of Volume settings,
		// that were originally saved in AH_MaskHint_Start
        DECOMP_howl_VolumeSet(i, volume & 0xFF);
    }
}
