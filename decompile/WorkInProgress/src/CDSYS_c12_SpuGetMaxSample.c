#include <common.h>

void DECOMP_CDSYS_SpuGetMaxSample(void)
{
    u_char currIndex;
    char index2;
    int sample;
    int *ptrSample;
    uint cur_Max;
    short max;

    cur_Max = 0;
    max = 0;

    // if you are not using CD, quit
    if (sdata->boolUseDisc == false) return;

    currIndex = 0x100;

    // range {0x0 - 0x100}
    if (sdata->irqAddr == 0)
    {
        currIndex = 0;
        cur_Max = 0x100;
    }
    // otherwise, range {0x100 - 0x200}
    else
    {
        cur_Max = 0x200;
    }

    // curr < end
    if (currIndex < cur_Max)
    {

        // loop through region
        for (; currIndex < cur_Max; currIndex++)
        {

            // decoded SPU data
            sample = *sdata->SpuDecodedData[currIndex];

            // absolute value
            if (sample < 0)
            {
                sample = -sample;
            }

            // if larger than cur_max
            if ((cur_Max << 0x10) < (sample << 0x10))
            {
                // set new cur_max
                cur_Max = sample;
            }

            // copy max
            max = (short)cur_Max;
        }
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

    for (; index2 != -1; currIndex--, index2--)
    {
        if (sdata->XA_MaxSampleValInArr < sdata->XA_MaxSampleValArr[currIndex])
        {
            sdata->XA_MaxSampleValInArr = sdata->XA_MaxSampleValArr[currIndex];
        }
    }
}
