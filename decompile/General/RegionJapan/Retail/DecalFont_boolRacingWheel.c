#include <common.h>

// function that only appears in the japanese retail version

u_int DECOMP_DecalFont_boolRacingWheel()
{
	struct ControllerMeta* controllerMetaP1 = sdata->gGamepads->gamepad[0].ptrControllerMeta;
	u_int isRacingWheel = false;

	if
	(
		(
			(
				// check if ptrControllerMeta in non-P1 controllers is null
				// or check if non-P1 controller types aren't multitaps (?)

				// if P1 controller exists, is a MadCatz Racing Wheel (neGcon with payload length 3), and is "not connected", then return true
				// this check will then be used to replace all instances of PS1 button icons with appropriate racing wheel ones

				// controllerMetaP1->payLoadLength == 3
				// controllerMetaP1->controllerType == PAD_ID_NEGCON
				(controllerMetaP1->controllerData == ((PAD_ID_NEGCON << 4) | 3)) &&
				(
					(
						sdata->gGamepads->gamepad[1].ptrControllerMeta == 0 || sdata->gGamepads->gamepad[1].ptrControllerMeta->isControllerConnected != 0
					)
				)
			) &&
			(
				(
					sdata->gGamepads->gamepad[2].ptrControllerMeta == 0 || sdata->gGamepads->gamepad[2].ptrControllerMeta->isControllerConnected != 0
				)
			)
		) &&
		(
			(
				(
					(
						sdata->gGamepads->gamepad[3].ptrControllerMeta == 0 || sdata->gGamepads->gamepad[3].ptrControllerMeta->isControllerConnected != 0
					) && (controllerMetaP1 != 0)
				) && (controllerMetaP1->isControllerConnected == 0)
			)
		)
	)
	{
		isRacingWheel = true;
	}
	return isRacingWheel;
}