#include <common.h>

#define SHUFFLE_AMOUNT 100

int MixRNG_Scramble();

short pads[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 101, 102, 103, 104, 105};

void Shuffle_array(short *arr, short size)
{
    short i, temp;
    char k, j;

    for (short i = 0; i < SHUFFLE_AMOUNT; i++)
    {
        MixRNG_Scramble();
        k = (sdata->randomNumber >> 8) % size;
        MixRNG_Scramble();
        j = (sdata->randomNumber >> 8) % size;
        temp = arr[j];
        arr[j] = arr[k];
        arr[k] = temp;
    }
}

void RunEntryHook()
{
    char i;
    char offsets[] = {0, 18, 22, 27};
    const char numRanges = 3;

    for (i = 0; i < numRanges; i++)
        Shuffle_array(&pads[offsets[i]], offsets[i + 1] - offsets[i]);
}
