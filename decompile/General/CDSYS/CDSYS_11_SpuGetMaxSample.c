#include <common.h>

void DECOMP_CDSYS_SpuGetMaxSample(void)
{
    int index2;   
	short sample;
    short max;
	max = 0;

	short* ptrSpuBuf = 
		&sdata->SpuDecodedBuf[sdata->irqAddr];
	
	// absolute value, find max in block
    for (int i = 0; i < 0x100; i++)
    {
        sample = ptrSpuBuf[i];
        if (sample < 0) sample = -sample;
        if (max < sample) max = sample;
    }

    // save max for this block
    sdata->XA_MaxSampleVal = max;
    sdata->XA_MaxSampleValArr[sdata->XA_MaxSampleIndex] = max;

	// Cycle through ring buffer
    sdata->XA_MaxSampleIndex++;
    if (sdata->XA_MaxSampleIndex >= 3)
        sdata->XA_MaxSampleIndex = 0;

	// === Naughty Dog Bug ===
	// This needs to reset itself
    sdata->XA_MaxSampleNumSaved++;
    if (sdata->XA_MaxSampleNumSaved >= 3)
		sdata->XA_MaxSampleNumSaved = 3;

    // Find max of last 3 block maxes,
	// as long as 3 blocks have already passed
    sdata->XA_MaxSampleValInArr = 0;
    for (int i = 0; i < sdata->XA_MaxSampleNumSaved; i++)
        if (sdata->XA_MaxSampleValInArr < sdata->XA_MaxSampleValArr[i])
            sdata->XA_MaxSampleValInArr = sdata->XA_MaxSampleValArr[i];
}
