#include <common.h>

void DECOMP_UI_WeaponBG_DrawShine(struct Icon *icon, short posX, short posY, struct PrimMem *primMem, u_long *ot, char param_6, short param_7, short param_8, int param9)
{
    
    short sVar1;
    short sVar2;
    short sVar3;
    short sVar4;
    short sVar5;
    short sVar6;
    POLY_GT4 *p;
    int i;
    short sVar11;
    short sVar12;
    
	u_int *wumpaShine = &sdata->wumpaShineColor1[0];

    if (param_6 == 3)
    {
        wumpaShine = &sdata->wumpaShineColor2[0];
    }

    sVar3 = (short)(((icon->texLayout.u1 - icon->texLayout.u0) * (int)param_7) >> 0xc);
    sVar1 = posX + sVar3;
    param_7 = param_7 >> 0xc;
    sVar12 = sVar1 - param_7;
	
    sVar4 = (short)(((icon->texLayout.v2 - icon->texLayout.v0) * (int)param_8) >> 0xc);
    sVar2 = posY + sVar4;
    param_8 = param_8 >> 0xc;
    sVar11 = sVar2 - param_8;

    // loop 4 times
    for (i = 0; i < 4; i++)
    {
        p = primMem->curr;
        *(int*)&p->u0 = *(int*)&icon->texLayout.u0;
        *(int*)&p->u1 = *(int*)&icon->texLayout.u1;
        *(int*)&p->u2 = *(int*)&icon->texLayout.u2;
        *(short*)&p->u3 = *(short*)&icon->texLayout.u3;

        switch (i)
        {
        case 0:
            // xy0
            p->x0 = posX;
            p->y0 = posY;

            p->x1 = sVar1;
            p->y1 = posY;
            p->x2 = posX;
            p->y2 = sVar2;
            p->x3 = sVar1;
            p->y3 = sVar2;
            break;

        case 1:
            // xy0
            sVar5 = (posX + sVar3 << 1) - param_7;
            p->x0 = sVar5;
            p->y0 = posY;

            p->x1 = sVar12;
            p->y1 = posY;
            p->x2 = sVar5;
            p->y2 = sVar2;
            p->x3 = sVar12;
            p->y3 = sVar2;
            break;

        case 2:
            // xy0
            sVar5 = (posY + sVar4 << 1) - param_8;
            p->x0 = posX;
            p->y0 = sVar5;

            p->x1 = sVar1;
            p->y1 = sVar5;
            p->x2 = posX;
            p->y2 = sVar11;
            p->x3 = sVar1;
            p->y3 = sVar11;
            break;

        case 3:
            // xy0
            sVar5 = (posX + sVar3 << 1) - param_7;
            sVar6 = (posY + sVar4 << 1) - param_8;
            p->x0 = sVar5;
            p->y0 = sVar6;

            p->x1 = sVar12;
            p->y1 = sVar6;
            p->x2 = sVar5;
            p->y2 = sVar11;
            p->x3 = sVar12;
            p->y3 = sVar11;
            break;
        }

        // color RGB
        *(u_int *)&p->r0 = wumpaShine[2];
        *(u_int *)&p->r1 = wumpaShine[1];
        *(u_int *)&p->r2 = wumpaShine[1];
        *(u_int *)&p->r3 = wumpaShine[0];

        setPolyGT4(p);

        if (param_6 != 0)
        {
            p->tpage = (p->tpage & ~(0x60)) | (((u_short)param_6 - 1) * 0x20);
            p->code |= 2;
        }

        AddPrim(ot, p);

        // increment primMem
        primMem->curr = p + 1;
    }
}