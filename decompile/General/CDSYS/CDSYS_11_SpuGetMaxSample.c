#include <common.h>

void DECOMP_CDSYS_SpuGetMaxSample(void)
{
    int index2;   
	short sample;
    short max;
	max = 0;

	#if 0 // impossible
    if (sdata->boolUseDisc == false) return;
	#endif
	
	short* ptrSpuBuf = 
		&sdata->SpuDecodedBuf[sdata->irqAddr];
	
    // loop through region
    for (int i = 0; i < 0x100; i++)
    {
		// absolute value
        sample = ptrSpuBuf[i];
        if (sample < 0) sample = -sample;

		// find max
        if (max < sample) max = sample;
    }

    // save max
    sdata->XA_MaxSampleVal = max;

    sdata->XA_MaxSampleValArr[sdata->XA_SampleMaxIndex1] = max;

    // XA_MaxSampleValArr
    sdata->XA_SampleMaxIndex1++;

    if (2 < sdata->XA_SampleMaxIndex1)
    {
        sdata->XA_SampleMaxIndex1 = 0;
    }

    if (sdata->XA_SampleMaxIndex2 < 3)
    {
        sdata->XA_SampleMaxIndex2++;
    }

    // set max to zero
    sdata->XA_MaxSampleValInArr = 0;

    int currIndex = sdata->XA_SampleMaxIndex1;
    index2 = sdata->XA_SampleMaxIndex2;
    if (index2 == 0) return;

    for (; index2 != -1; index2--)
    {
		currIndex--;
		if(currIndex < 0)
			currIndex = 2;
		
        if (sdata->XA_MaxSampleValInArr < sdata->XA_MaxSampleValArr[currIndex])
            sdata->XA_MaxSampleValInArr = sdata->XA_MaxSampleValArr[currIndex];
    }
}
