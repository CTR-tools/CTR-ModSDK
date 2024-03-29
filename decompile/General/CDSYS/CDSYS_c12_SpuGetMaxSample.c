#include <common.h>

void DECOMP_CDSYS_SpuGetMaxSample(void)
{
	int endIndex;
    int currIndex;
    int index2;
    
	short sample;
    short max;

    // if you are not using CD, quit
    if (sdata->boolUseDisc == false) return;

    // range {0x0 - 0x100}
    if (sdata->irqAddr == 0)
    {
        currIndex = 0;
        endIndex = 0x100;
    }
    // otherwise, range {0x100 - 0x200}
    else
    {
		currIndex = 0x100;
        endIndex = 0x200;
    }
	
    // loop through region
    for (max = 0; currIndex < endIndex; currIndex++)
    {
		// absolute value
        sample = sdata->SpuDecodedData[currIndex];
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

    currIndex = sdata->XA_SampleMaxIndex1;
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
