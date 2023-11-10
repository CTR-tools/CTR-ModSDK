#include <common.h>

void DECOMP_GAMEPROG_NewProfile_OutsideAdv(struct GameProgress* gameProg)
{
	// GameOptions is probably a struct "inside"
	// of GameProgress, still working on it
	
	// GameProgress and GameOptions
	memset(gameProg, 0, sizeof(struct GameProgress) + sizeof(struct GameOptions));
	
	DECOMP_GAMEPROG_ResetHighScores(gameProg);
}