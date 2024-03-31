#include <common.h>

int Timer_GetTime_Total();

char ChRand_Repeat(int index, int character)
{
	int i;

	// check if character is taken
	// previously (<)
	// or by self (=)
	for(i = 0; i <= index; i++)
		if(data.characterIDs[i] == character)
			return 1;

	return 0;
}

void ChRand_SetCharacters()
{
	int id;

	// this randomizes non-players, but if you want
	// all drivers randomized, then set 'i' to zero here
	int i = sdata->gGT->numPlyrCurrGame;

	// if in a cup
	if
	(
		(sdata->gGT->gameMode1 & ADVENTURE_CUP) ||

		// arcade cup
		((sdata->gGT->gameMode2 & CUP_ANY_KIND) != 0)
	)
	{
		// if this is not the first track of a cup,
		// then dont randomize. Keep characters from first track
		if(sdata->gGT->cup.trackIndex != 0) return;
	}

	// loop through drivers
	while(i < 8)
	{
		// random
		MixRNG_Scramble();

		id = (
				// system clock
				(Timer_GetTime_Total() & 0xf )

				+

				// from RNG
				(sdata->randomNumber >> 8)

			 ) % 15; // 15 characters

		// avoid repeats
		if(ChRand_Repeat(i, id)) continue;

		// set value
		data.characterIDs[i] = id;
		i++;
	}
}