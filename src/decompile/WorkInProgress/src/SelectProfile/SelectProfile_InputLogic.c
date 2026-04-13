#include <common.h>

u_int DECOMP_SelectProfile_InputLogic(struct RectMenu* menu, short param_2, u_int confirm)
{
    u_int uVar5 = 0;
    u_int tap = sdata->buttonTapPerPlayer[0];

    // If you press D-Pad, Cross, Square, Triangle, Circle
    if ((tap & 0x4007f) != 0)
    {
        if ((confirm & 1) == 0)
        {
            u_char currRow = menu->rowSelected;

            u_char uVar3 = currRow - 2;

            if (((tap & BTN_UP) != 0) ||
                ((tap & BTN_DOWN) != 0))
            {
                uVar3 = currRow + 2;
            }
            else if ((tap & (BTN_LEFT|BTN_RIGHT)) != 0)
            {
                uVar3 = currRow ^ 1;
            }

            menu->rowSelected = uVar3;

             // if going below valid row
            if (currRow < 0)
            {
                // keep it at firstrow
                menu->rowSelected = 0;
                // save curr position
                currRow = menu->rowSelected;
            }

            if (param_2 <= currRow)
            {
                menu->rowSelected = param_2 - 1;
            }

            if (menu->rowSelected != currRow)
            {
                OtherFX_Play(0, 1);
            }
             // If you press Cross or Circle
            if (((tap & 0x50) == 0) ||
                (param_2 == 0 && (sdata->memcardAction != 1)))
            {
                // If you press Triangle or Square
                if ((tap & 0x40020) != 0)
                {
                    OtherFX_Play(2, 1);
                    uVar5 = 1;
                    // row selected is -1, so we know to reinitialize
                    // the menu when we return to it next time
                    menu->rowSelected = 0xffff;
                }
            }
             // If you do not press Cross or Circle
            else
            {
                OtherFX_Play(1, 1);
                uVar5 = 1;
                if (sdata->data94_afterRand[0x26] == 1)
                {
                    menu->rowSelected = 0;
                }
            }
        }
        else
        {
            // If you press Triangle or Square
            u_char cancel = (tap & 0x40020) != 0;
            if (cancel)
            {
                OtherFX_Play(2, 1);
                menu->rowSelected = 0xffff;
            }
            uVar5 = cancel;
            if (((confirm & 2) != 0) && ((tap & 0x50) != 0))
            {
                OtherFX_Play(1, 1);
                uVar5 = 1;
            }
        }

        RECTMENU_ClearInput();
    }
    return uVar5;
}
