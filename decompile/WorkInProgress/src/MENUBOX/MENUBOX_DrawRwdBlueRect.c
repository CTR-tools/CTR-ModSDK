#include <common.h>

void DECOMP_MENUBOX_DrawRwdBlueRect_Subset(short *pos, int *color, u_long *ot, struct PrimMem *primMem)
{
  POLY_G4 *p = (POLY_G4 *)primMem->curr;

  if (p <= primMem->endMin100)
  {
    primMem->curr = p + 1;
  }
  if (p != NULL)
  {
    p->code = 0x38;
    p->r0 = color[0] & 0xffffff;
    p->r1 = color[1] & 0xffffff;
    p->r2 = color[2] & 0xffffff;
    p->r3 = color[3] & 0xffffff;
    p->x0 = pos[0];
    p->x1 = (pos[0] + 1) | (pos[1] << 16);
    p->x2 = pos[0] | ((pos[1] + pos[2]) << 16);
    p->x3 = (pos[0] + 1) | ((pos[1] + pos[2]) << 16);
    AddPrim(ot, p);
  }
}

void DECOMP_MENUBOX_DrawRwdBlueRect(RECT *rect, char *metas, u_long *ot, struct PrimMem *primMem)
{
    short pos[4];
    int gradient[2];
    int colors[4];

    pos[0] = rect->x;
    pos[2] = rect->w;

    for (int i = 0; (metas[i * 4] + 3) != 13; i++)
    {
        int* meta = (int*)&metas[i * 4];
        gradient[0] = meta[0];
        gradient[1] = meta[1];
        colors[0] = gradient[0];
        colors[1] = gradient[0];
        colors[2] = gradient[1];
        colors[3] = gradient[1];
        pos[1] = rect->y + (short)(meta[3] * rect->h / 100);
        pos[3] = rect->y + (short)(meta[7] * rect->h / 100) - pos[1] + 1;

        MenuBox_DrawRwdBlueRect_Subset(&pos, &colors, ot, primMem);
    }
}
