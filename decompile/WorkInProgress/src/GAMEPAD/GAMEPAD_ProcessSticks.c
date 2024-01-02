#include <common.h>

void GAMEPAD_ProcessSticks(struct GamepadSystem *gGS)
{
    char bVar1;
    u_char bVar2;
    short uVar3;
    int iVar4;
    char uVar5;
    int iVar7;
    short sVar8;

    // racing wheel data
    for (char i = 0; i < 8; i++)
    {
        struct GamepadBuffer *pad = gGS->gamepad[i];
        struct ControllerPacket *packet = pad->ptrControllerPacket;
        struct RacingWheelData *rwd = &data.rwd[i];

        pad->rwd = NULL;

        // if pointer is invalid
        if (packet == NULL)
        {
            // center the position
            pad->stickLX = 0x80;
            pad->stickLY = 0x80;
            pad->stickLX_dontUse1 = 0x80;
            pad->stickLY_dontUse1 = 0x80;
            pad->stickRX = 0x80;
            pad->stickRY = 0x80;
        }

        // if pointer is valid
        else
        {
            if (packet->isControllerConnected == 0)
            {
                if (packet->controllerData == ((PAD_ID_ANALOG_STICK << 4) | 3))
                {
                LAB_80025998:
                    pad->stickLX_dontUse1 = packet->analog.leftX;
                    bVar1 = packet->analog.rightX;
                    if ((bVar1 == 0xff) && (pad->unk_1 != bVar1))
                    {
                        pad->stickLY_dontUse1 = pad->unk_1;
                    }
                    else
                    {
                        pad->stickLY_dontUse1 = bVar1;
                    }
                    pad->unk_1 = bVar1;
                    pad->stickRX = packet->analog.rightX;
                    pad->stickRY = packet->analog.rightY;
                }
                else
                {
                    if (bVar1 < (PAD_ID_ANALOG_STICK | 4))
                    {
                        if (bVar1 == (PAD_ID_NEGCON << 4 | 3))
                        {
                            if (i < 4)
                            {
                                // racingwheel data
                                pad->rwd = rwd;
                            }
                            pad->stickLX_dontUse1 = packet->analog.rightX;
                            pad->stickLY_dontUse1 = 0x80;
                            pad->stickRX = 0x80;
                            pad->stickRY = 0x80;
                            goto LAB_80025a0c;
                        }
                        pad->stickLX_dontUse1 = 0x80;
                    }
                    else
                    {
                        if (bVar1 == (PAD_ID_ANALOG << 4 | 3))
                            goto LAB_80025998;
                        if (bVar1 != (PAD_ID_JOGCON << 4 | 3))
                        {
                            pad->stickLX_dontUse1 = 0x80;
                            goto LAB_80025a00;
                        }
                        if (i < 4)
                        {
                            // racingwheel data
                            pad->rwd = rwd;
                        }
                        iVar4 = packet->analog.rightX;
                        if (iVar4 < 0)
                        {
                            iVar7 = ((-10 - iVar4) - rwd->deadZone) * 8;
                            uVar5 = iVar7;
                            if (iVar7 < 0)
                            {
                                uVar5 = 0;
                            }
                            if (0xff < iVar7)
                            {
                                uVar5 = 0xff;
                            }
                            sVar8 += 0x80;
                            if (iVar4 < -0x80)
                            {
                                sVar8 = -0x80;
                            LAB_8002595c:
                                sVar8 += 0x80;
                            }
                        }
                        else
                        {
                            iVar7 = ((iVar4 - 10) - rwd->deadZone) * 8;
                            uVar5 = iVar7;
                            if (iVar7 < 0)
                            {
                                uVar5 = 0;
                            }
                            if (0xff < iVar7)
                            {
                                uVar5 = 0xff;
                            }
                            sVar8 += 0x80;
                            if (0x7f < iVar4)
                            {
                                sVar8 = 0x7f;
                                goto LAB_8002595c;
                            }
                        }
                        pad->data14[0x13] = uVar5;
                        pad->stickLX_dontUse1 = sVar8;
                    }
                LAB_80025a00:
                    // reset stick values to "center"
                    pad->stickLY_dontUse1 = 0x80;
                    pad->stickRX = 0x80;
                    pad->stickRY = 0x80;
                }
            }
        LAB_80025a0c:

            iVar4 = pad->stickLX_dontUse1 - 0x80;
            if (iVar4 < 0)
            {
                iVar4 = -iVar4;
            }

            if (0x30 < iVar4)
            {
                pad->framesSinceLastInput = 0;
            }

            iVar4 = pad->stickLY_dontUse1 - 0x80;
            if (iVar4 < 0)
            {
                iVar4 = -iVar4;
            }

            if (0x30 < iVar4)
            {
                pad->framesSinceLastInput = 0;
            }

            iVar4 = pad->stickRX - 0x80;
            if (iVar4 < 0)
            {
                iVar4 = -iVar4;
            }

            if (0x30 < iVar4)
            {
                pad->framesSinceLastInput = 0;
            }

            iVar4 = pad->stickRY - 0x80;
            if (iVar4 < 0)
            {
                iVar4 = -iVar4;
            }
            if (0x30 < iVar4)
            {
                pad->framesSinceLastInput = 0;
            }

            if (packet->controllerData == ((PAD_ID_ANALOG_STICK << 4) | 3))
            {
            LAB_80025af0:
                bVar2 = true;
            }
            else
            {
                if (bVar1 < (PAD_ID_ANALOG_STICK << 4 | 4))
                {
                    bVar2 = false;
                    if (bVar1 == (PAD_ID_NEGCON << 2 | 3))
                        goto LAB_80025af0;
                }
                else
                {
                    if ((bVar1 == (PAD_ID_ANALOG << 4 | 3)) || (bVar2 = false, bVar1 == (PAD_ID_JOGCON << 4 | 3)))
                        goto LAB_80025af0;
                }
            }

            // if you do not press Left
            if ((pad->buttonsHeldCurrFrame & 4) == 0)
            {
                // if you press Right
                if ((pad->buttonsHeldCurrFrame & 8) != 0)
                {
                    iVar4 = pad->stickLX;
                    if (iVar4 < 0x100)
                    {
                        uVar3 = (short)(iVar4 + 0xff);
                        if (0xff < iVar4 + 0xff)
                        {
                            uVar3 = 0xff;
                        }
                    }
                    else
                    {
                        uVar3 = (short)(iVar4 - 0xff);
                        if (iVar4 - 0xff < 0xff)
                        {
                            uVar3 = 0xff;
                        }
                    }
                    goto LAB_80025be4;
                }
                if (!bVar2)
                {
                    iVar4 = pad->stickLX;
                    if (iVar4 < 0x81)
                    {
                        uVar3 = (short)(iVar4 + 0xff);
                        if (0x80 < iVar4 + 0xff)
                        {
                            uVar3 = 0x80;
                        }
                    }
                    else
                    {
                        uVar3 = (short)(iVar4 - 0xff);
                        if (iVar4 - 0xff < 0x80)
                        {
                            uVar3 = 0x80;
                        }
                    }
                    goto LAB_80025be4;
                }

                // make backup, curr into prev, stickLX
                pad->stickLX = pad->stickLX_dontUse1;
            }

            // if you press Left
            else
            {
                iVar4 = pad->stickLX;
                if (iVar4 < 1)
                {
                    uVar3 = (short)(iVar4 + 0xff);
                    if (0 < iVar4 + 0xff)
                    {
                        uVar3 = 0;
                    }
                }
                else
                {
                    uVar3 = (short)(iVar4 - 0xff);
                    if (iVar4 - 0xff < 0)
                    {
                        uVar3 = 0;
                    }
                }
            LAB_80025be4:
                pad->stickLX = uVar3;
            }

            // if you do not press Up
            if ((pad->buttonsHeldCurrFrame & 1) == 0)
            {

                // if you do not press Down
                if ((pad->buttonsHeldCurrFrame & 2) == 0)
                {
                    if (bVar2)
                    {
                        uVar3 = pad->stickLY_dontUse1;
                    }
                    else
                    {
                        iVar4 = pad->stickLY;
                        if (iVar4 < 0x81)
                        {
                            uVar3 = (short)(iVar4 + 0xff);
                            if (0x80 < iVar4 + 0xff)
                            {
                                uVar3 = 0x80;
                            }
                        }
                        else
                        {
                            uVar3 = (short)(iVar4 - 0xff);
                            if (iVar4 - 0xff < 0x80)
                            {
                                uVar3 = 0x80;
                            }
                        }
                    }
                }

                // if you press Down
                else
                {
                    iVar4 = pad->stickLY;
                    if (iVar4 < 0x100)
                    {
                        uVar3 = (short)(iVar4 + 0xff);
                        if (0xff < iVar4 + 0xff)
                        {
                            uVar3 = 0xff;
                        }
                    }
                    else
                    {
                        uVar3 = (short)(iVar4 - 0xff);
                        if (iVar4 - 0xff < 0xff)
                        {
                            uVar3 = 0xff;
                        }
                    }
                }
            }

            // if you press Up
            else
            {
                iVar4 = pad->stickLY;
                if (iVar4 < 1)
                {
                    uVar3 = (short)(iVar4 + 0xff);
                    if (0 < iVar4 + 0xff)
                    {
                        uVar3 = 0;
                    }
                }
                else
                {
                    uVar3 = (short)(iVar4 - 0xff);
                    if (iVar4 - 0xff < 0)
                    {
                        uVar3 = 0;
                    }
                }
            }
            pad->stickLY = uVar3;
        }
    }
}
