#include <common.h>

void MM_Battle_CloseSubMenu(struct MenuBox *mb)
{
    mb->state |= 4;
    return;
}

void MM_Battle_DrawIcon_Weapon(struct Icon *icon, u_int posX, int posY, struct PrimMem *primMem, u_int *ot,
                               char transparency, short param_7, u_short param_8, u_int *color)
{
    if (!icon)
        return;

    POLY_FT4 *p = (POLY_FT4 *)primMem->curr;

    u_int code = (transparency == 0) ? 0x2c000000 : 0x2e000000;
    u_int u0 = icon->texLayout.u0;
    u_int u1 = icon->texLayout.u1;
    u_int u2 = icon->texLayout.u2;
    int iVar1 = ((icon->texLayout.v2 - ((int)u0 >> 8)) * (int)param_7) >> 0xc;
    int iVar2 = ((u1 - u0) * (int)param_7) >> 0xc;
    u_int screenPosX = (posX + iVar1) | (posY * 0x10000);
    u_int screenPosY = (posX + iVar2) | (posY * 0x10000);

    p->r0 = (*color & 0xffffff) | code;
    p->u0 = u0;
    p->u1 = (transparency == 0) ? screenPosY : (screenPosY & 0xff9fffff) | ((u_int)transparency - 1) * 0x200000;
    p->u2 = u2;
    p->u3 = icon->texLayout.u3;

    if ((param_8 & 1) == 0)
    {
        if (param_8 == 0)
        {
            p->x0 = screenPosX;
            p->x1 = screenPosY;
            p->x2 = (posX + iVar2) | posY;
            p->x3 = posX | posY;
        }
        else
        {
            p->x3 = screenPosX;
            p->x2 = screenPosY;
            p->x1 = (posX + iVar2) | posY;
            p->x0 = posX | posY;
        }
    }
    else
    {
        if (param_8 == 1)
        {
            p->x1 = screenPosX;
            p->x3 = screenPosY;
            p->x0 = (posX + iVar2) | posY;
            p->x2 = posX | posY;
        }
        else
        {
            p->x2 = screenPosX;
            p->x0 = screenPosY;
            p->x3 = (posX + iVar2) | posY;
            p->x1 = posX | posY;
        }
    }

    addPrim(ot, p);
    primMem->curr = p + 1;
}

void MM_Battle_Init(void)
{
    OVR_230.battle_transitionState = 0;
    OVR_230.battle_transitionFrames = 0xc;
    return;
}
