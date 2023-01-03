#include <common.h>

void GAMEPROG_NewProfile_OutsideAdv(struct GameProgress* gameProg)
{
	// GameProgress and GameOptions
	memset(gameProg, 0, 0x14bc);
	
	GAMEPROG_ResetHighScores(gameProg);
}