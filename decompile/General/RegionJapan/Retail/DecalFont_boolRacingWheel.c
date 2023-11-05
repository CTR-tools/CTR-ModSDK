#include <common.h>

// function that only appears in the japanese retail version

u_int DECOMP_DecalFont_boolRacingWheel()
{
	char* ptrRawInput;
	u_int result;
	
	ptrRawInput = sdata->gGamepads->gamepad[0]->ptrRawInput;
	result = 0;
	// check if raw input pointers for other gamepads don't exist
	if
	(
		(
			(
				// # is the id for the madcatz mc2 racing wheel
				(ptrRawInput[1] == '#') &&
				(
					(
						sdata->gGamepads->gamepad[1]->ptrRawInput == 0 || sdata->gGamepads->gamepad[1]->ptrRawInput[0] != '\0'
					)
				)
			) &&
			(
				(
					sdata->gGamepads->gamepad[2]->ptrRawInput == 0 || sdata->gGamepads->gamepad[2]->ptrRawInput[0] != '\0'
				)
			)
		) &&
		(
			(
				(
					(
						sdata->gGamepads->gamepad[3]->ptrRawInput == 0 || sdata->gGamepads->gamepad[3]->ptrRawInput[0] != '\0'
					) && (ptrRawInput != 0)
				) && (ptrRawInput[0] == '\0')
			)
		)
	)
	{
		result = 1;
	}
	return result;
}