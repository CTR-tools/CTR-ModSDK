#include <common.H>

void DECOMP_MENUBOX_ProcessState(void)
{
    void (*func)(struct MenuBox* m);
    u_int currState;
    struct MenuBox *mb;
    short local_10[4];

    // get ptrDesiredMenuBox
    mb = sdata->ptrDesiredMenuBox;

    // This is a timer feature so that you
    // can give "amount of life" to a menu,
    // but this variable is never used so
    // it serves no purpose
    if (sdata->framesRemainingInMenu != 0)
    {
        sdata->framesRemainingInMenu--;
    }

    // if you want to change the MenuBox
    if (sdata->ptrDesiredMenuBox != 0)
    {
        currState = sdata->ptrDesiredMenuBox->state;

        sdata->ptrActiveMenuBox = sdata->ptrDesiredMenuBox;

        // erase DesiredMenuBox
        sdata->ptrDesiredMenuBox = 0;

        mb->state = currState & 0xffffefff;
        while ((currState & 0x10) != 0)
        {
            mb = *(int *)(mb + 0x24);
            currState = mb->state;
        }
        mb->state &= 0xfffffffb;
    }

    if (((sdata->ptrActiveMenuBox->state) & 0x420) != 0)
    {

        // Get function pointer that MenuBox executes each frame
        func = sdata->ptrActiveMenuBox->funcPtr;

        // you are at the top level of main menu and can't go back
        sdata->ptrActiveMenuBox->unk1e = 1;

        // execute MenuBox function
        (func)(sdata->ptrActiveMenuBox);
    }

    if (((sdata->ptrActiveMenuBox->state) & 0x20) == 0)
    {
        MENUBOX_ProcessInput();

        if (((sdata->ptrActiveMenuBox->state) & 0x2000) == 0)
        {
            // set width to zero
            local_10[0] = 0;

            // get width of menubox
            MENUBOX_GetWidth(sdata->ptrActiveMenuBox, local_10, 1);

            // draw menubox
            MENUBOX_DrawSelf(sdata->ptrActiveMenuBox, 0, 0, (int)local_10[0]);
        }
    }

    if (((sdata->ptrActiveMenuBox->state) & 0x800) == 0)
    {
        mb = TitleFlag_GetCanDraw();

        // if the value is zero
        if (mb == 0)
        {
            TitleFlag_SetCanDraw(1);
        }

        // enable 3d cars on track? pause the game?
        sdata->gGT->renderFlags |= 0x20;
    }

    // If the menu is invisible, which is only if you
    // left the menu, and no longer need the menu,
    if ((sdata->ptrActiveMenuBox->state & 0x1000) != 0)
    {
        // set ActiveMenuBox to nullptr
        sdata->ptrActiveMenuBox = 0;
    }
    return;
}