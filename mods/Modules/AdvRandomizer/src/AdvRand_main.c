#include <common.h>
#define RANDOM_MODE 1
#define SHUFFLE_AMOUNT 100

short newPads[27] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 101, 102, 103, 104, 105};
short newHubs[5] = {0, 1, 2, 3, 4};

void Shuffle_array(short *arr, short size)
{
    short i, temp;
    char k, j;

    for (short i = 0; i < SHUFFLE_AMOUNT; i++)
    {
        k = (MixRNG_Scramble() >> 8) % size;
        j = (MixRNG_Scramble() >> 8) % size;
        temp = arr[j];
        arr[j] = arr[k];
        arr[k] = temp;
    }
}

void AH_Rand(void)
{
    char i;
    char offsets[] = {0, 16, 18, 22, 27};
    const char numRanges = 4;

    if (!RANDOM_MODE)
        return;

    for (i = 0; i < numRanges; i++)
        Shuffle_array(&newPads[offsets[i]], offsets[i + 1] - offsets[i]);

    Shuffle_array(&newHubs[1], 4);
}
