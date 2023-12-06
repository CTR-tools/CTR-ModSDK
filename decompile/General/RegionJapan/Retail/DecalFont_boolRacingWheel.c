#include <common.h>

// function that only appears in the japanese retail version

u_int DECOMP_DecalFont_boolRacingWheel()
{
	struct ControllerPacket* controllerPacketP1 = sdata->gGamepads->gamepad[0].ptrControllerPacket;
	u_int isRacingWheel = false;

	if
	(
		(
			(
				// check if ptrControllerPacket in non-P1 controllers is null
				// or check if non-P1 controller types aren't multitaps (?)

				// if P1 controller exists, is a MadCatz Racing Wheel (neGcon with payload length 3), and is "not connected", then return true
				// this check will then be used to replace all instances of PS1 button icons with appropriate racing wheel ones

				// controllerPacketP1->payLoadLength == 3
				// controllerPacketP1->controllerType == PAD_ID_NEGCON
				(controllerPacketP1->controllerData == ((PAD_ID_NEGCON << 4) | 3)) &&
				(
					(
						sdata->gGamepads->gamepad[1].ptrControllerPacket == 0 || sdata->gGamepads->gamepad[1].ptrControllerPacket->isControllerConnected != 0
					)
				)
			) &&
			(
				(
					sdata->gGamepads->gamepad[2].ptrControllerPacket == 0 || sdata->gGamepads->gamepad[2].ptrControllerPacket->isControllerConnected != 0
				)
			)
		) &&
		(
			(
				(
					(
						sdata->gGamepads->gamepad[3].ptrControllerPacket == 0 || sdata->gGamepads->gamepad[3].ptrControllerPacket->isControllerConnected != 0
					) && (controllerPacketP1 != 0)
				) && (controllerPacketP1->isControllerConnected == 0)
			)
		)
	)
	{
		isRacingWheel = true;
	}
	return isRacingWheel;
}