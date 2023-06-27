#include <common.h>

// Not present in Sep3
// If a new memory card is plugged in with progress 
// that differs from the game, this combines the progress 
// of both. However, this bugs unlocking N Tropy, maybe more
void DECOMP_GAMEPROG_SyncGameAndCard(
	struct GameProgress* memcardProg,
	struct GameProgress* currentProg)
{
	// memcardProg is the memcard buffer
	// currentProg is sdata gameProgress
	
	int i;
	int memcardFlags;
	int currentFlags;
	int joinFlags;
	
	// combine progress of cups,
	// characters, track, scrapbook
	for(i = 0; i < 2; i++)
	{
		memcardFlags = memcardProg->unlocks[i];
		currentFlags = currentProg->unlocks[i];
		
		joinFlags = memcardFlags | currentFlags;
		
		memcardProg->unlocks[i] = joinFlags;
		currentProg->unlocks[i] = joinFlags;
	}
	
	// combine progress of beaten ghosts
	for(i = 0; i < 2; i++)
	{
		memcardFlags = memcardProg->highScoreTracks[i].timeTrialFlags;
		currentFlags = currentProg->highScoreTracks[i].timeTrialFlags;
		
		joinFlags = memcardFlags | currentFlags;
		
		memcardProg->highScoreTracks[i].timeTrialFlags = joinFlags;
		currentProg->highScoreTracks[i].timeTrialFlags = joinFlags;
	}
	
	// Naughty Dog left this incomplete
	// What if the game beat half of N Tropy's ghosts
	// and the new memory card beat the other half?
	// Now you have all ghosts beaten, but N Tropy 
	// is still locked, and can't possibly be unlocked
	
	// Need to check cup flags for an unlocked battle track,
	// and n tropy ghosts for n tropy,
	// and oxide ghosts for scrapbook
}