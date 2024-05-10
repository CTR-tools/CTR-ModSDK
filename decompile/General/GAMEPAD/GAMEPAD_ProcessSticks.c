#include <common.h>

void DECOMP_GAMEPAD_ProcessSticks(struct GamepadSystem *gGS)
{
    unsigned char bVar1;
    u_char bVar2;
    short uVar3;
    int iVar4;
    int iVar7;
    short sVar8;

    // racing wheel data
    for (char i = 0; i < 8; i++)
    {
        struct GamepadBuffer *pad = &gGS->gamepad[i];
        struct ControllerPacket *packet = pad->ptrControllerPacket;
        struct RacingWheelData *rwd = &data.rwd[i];

		// wipe to default
        pad->rwd = NULL;
        pad->stickLX = 0x80;
        pad->stickLY = 0x80;
        pad->stickLX_dontUse1 = 0x80;
        pad->stickLY_dontUse1 = 0x80;
        pad->stickRX = 0x80;
        pad->stickRY = 0x80;

        // if pointer is valid
        if (packet == NULL) continue;

        if (packet->isControllerConnected == 0)
        {
			bVar1 = packet->controllerData;
			
            if (
					(bVar1 == ((PAD_ID_ANALOG_STICK << 4) | 3)) ||
					(bVar1 == ((PAD_ID_ANALOG << 4) | 3))
				)
            {
                pad->stickLX_dontUse1 = packet->analog.leftX;
                pad->stickLY_dontUse1 = packet->analog.leftY;
                pad->stickRX = packet->analog.rightX;
                pad->stickRY = packet->analog.rightY;
            }
			
            else if (bVar1 == ((PAD_ID_NEGCON << 4) | 3))
            {
                if (i < 4)
                {
                    // racingwheel data
                    pad->rwd = rwd;
                }
                pad->stickLX_dontUse1 = packet->neGcon.twist;
            }

            else if (bVar1 == ((PAD_ID_JOGCON << 4) | 3))
            {	
				if (i < 4)
				{
					// racingwheel data
					pad->rwd = rwd;
				}
				
				sVar8 = packet->jogcon.jog_rot;
				iVar4 = (int)sVar8;
				
				if (iVar4 < 0)
				{
					iVar7 = ((-10 - iVar4) - rwd->deadZone) * 8;
					if (iVar7 < 0) iVar7 = 0;
					if (iVar7 > 0xff) iVar7 = 0xff;
					
					sVar8 += 0x80;
					if (iVar4 < -0x80)
					{
						sVar8 = -0x80;
						sVar8 += 0x80;
					}
				}
				else
				{
					iVar7 = ((iVar4 - 10) - rwd->deadZone) * 8;
					if (iVar7 < 0) iVar7 = 0;
					if (iVar7 > 0xff) iVar7 = 0xff;
					
					sVar8 += 0x80;
					if (0x7f < iVar4)
					{
						sVar8 = 0x7f;
						sVar8 += 0x80;
					}
				}
				pad->unk43 = (char)iVar7;
				pad->stickLX_dontUse1 = sVar8;
			}
        }

        iVar4 = pad->stickLX_dontUse1 - 0x80;
        if (iVar4 < 0) iVar4 = -iVar4;
        if (0x30 < iVar4) pad->framesSinceLastInput = 0;

        iVar4 = pad->stickLY_dontUse1 - 0x80;
        if (iVar4 < 0) iVar4 = -iVar4;
        if (0x30 < iVar4) pad->framesSinceLastInput = 0;

        iVar4 = pad->stickRX - 0x80;
        if (iVar4 < 0) iVar4 = -iVar4;
        if (0x30 < iVar4) pad->framesSinceLastInput = 0;
		
        iVar4 = pad->stickRY - 0x80;
        if (iVar4 < 0) iVar4 = -iVar4;
        if (0x30 < iVar4) pad->framesSinceLastInput = 0;

		pad->stickLX = pad->stickLX_dontUse1;
		pad->stickLY = pad->stickLY_dontUse1;

        // In this order: Up, Down, Left, Right
        if ((pad->buttonsHeldCurrFrame & 1) != 0) pad->stickLY = 0;
        if ((pad->buttonsHeldCurrFrame & 2) != 0) pad->stickLY = 0xFF;
        if ((pad->buttonsHeldCurrFrame & 4) != 0) pad->stickLX = 0;
        if ((pad->buttonsHeldCurrFrame & 8) != 0) pad->stickLX = 0xFF;

		#ifdef USE_ONLINE
		break;
		#endif
	}
}