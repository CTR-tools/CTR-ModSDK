#include <common.h>

void DECOMP_MM_Battle_DrawIcon_Weapon(struct Icon *icon, 
		u_int posX, int posY, struct PrimMem *primMem, u_int *ot,
        char transparency, short param_7, u_short param_8, u_int *color)
{
    if (!icon)
        return;

    POLY_FT4 *p = (POLY_FT4 *)primMem->curr;

    u_int code = 0x2e000000;
    u_int u0 = *(int*)&icon->texLayout.u0;
    u_int u1 = *(int*)&icon->texLayout.u1;
    u_int u2 = *(int*)&icon->texLayout.u2;
	
    int iVar1 = WIDE_34(0x2f);
    int iVar2 = 0x1f;
	
	posY *= 0x10000;
	
    *(u_int*)&p->r0 = (*color & 0xffffff) | code;
    *(u_int*)&p->u0 = u0;
    *(u_int*)&p->u1 = (u1 & 0xff9fffff);
    *(u_int*)&p->u2 = u2;
    *(short*)&p->u3 = *(short*)&icon->texLayout.u3;

    *(u_int*)&p->x1 = (posX) | (posY);
    *(u_int*)&p->x3 = (posX + iVar1) | (posY);
    *(u_int*)&p->x0 = (posX) | (posY+iVar2*0x10000);
    *(u_int*)&p->x2 = (posX + iVar1) | (posY+iVar2*0x10000);
	
    *(int*)p = *(int*)ot | 0x9000000;
    *(int*)ot = (int)p & 0xffffff;
	
    primMem->curr = p + 1;
}