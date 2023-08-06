#include <common.h>

void DECOMP_AH_MaskHint_End(int param_1)
{
    int diff;
    int volume;
    for (char i = 0; i < 3; i++)
    {
        diff = ((short*)0x800b54ec)[i] - ((u_char*)0x800b5668)[i];
        volume = ((char*)0x800b5668)[i] + ((diff * param_1) >> 12);
        
        // restore backups of Volume settings from FUN_800b3dd8
        howl_VolumeSet(i, volume & 0xFF);
    }
}
