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
				// controllerPacketP1->payLoadLength == 3
				// controllerPacketP1->controllerType == PAD_ID_NEGCON
				(controllerPacketP1->controllerData == ((PAD_ID_NEGCON << 4) | 3)) &&
				(
					(
						sdata->gGamepads->gamepad[1].ptrControllerPacket == 0 || sdata->gGamepads->gamepad[1].ptrControllerPacket->plugged != PLUGGED
					)
				)
			) &&
			(
				(
					sdata->gGamepads->gamepad[2].ptrControllerPacket == 0 || sdata->gGamepads->gamepad[2].ptrControllerPacket->plugged != PLUGGED
				)
			)
		) &&
		(
			(
				(
					(
						sdata->gGamepads->gamepad[3].ptrControllerPacket == 0 || sdata->gGamepads->gamepad[3].ptrControllerPacket->plugged != PLUGGED
					) && (controllerPacketP1 != 0)
				) && (controllerPacketP1->plugged == PLUGGED)
			)
		)
	)
	{
		isRacingWheel = true;
	}
	return isRacingWheel;
}