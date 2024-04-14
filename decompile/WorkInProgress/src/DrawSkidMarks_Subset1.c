#include <common.h>

/// @brief Adds a single skidline prim to the OT.
/// @param hiLine - short x0x1y0y1
/// @param loLine - short x2x3y2y3
/// @param param_3 
/// @param param_4 
void DrawSkidMarks_Subset1(short *hiLine, short *loLine, int param_3, int param_4)
{
	// get prim mem
	struct PrimMem *primMem = &globalGameTracker->backDB->primMem;

	// get current prim
	POLY_GT4 * pPrim = primMem->curr;

	// if have space to draw
	if ((pPrim + 1) <= primMem->endMin100) 
	{
		// alloc one prim
		primMem->curr = (void *)(pPrim + 1);

		// copy color from param4 to all 4 corners
		pPrim->r0 = (char *)(param_4 + 0x1c);
		pPrim->g0 = (char *)(param_4 + 0x1d);
		pPrim->b0 = (char *)(param_4 + 0x1e);
		pPrim->code = (char *)(param_4 + 0x1f);

		pPrim->r1 = pPrim->r0;
		pPrim->g1 = pPrim->g0;
		pPrim->b1 = pPrim->b1;
		pPrim->pad0 = pPrim->code;

		pPrim->r2 = pPrim->r0;
		pPrim->g2 = pPrim->g0;
		pPrim->b2 = pPrim->b1;
		pPrim->pad1 = pPrim->code;

		pPrim->r3 = pPrim->r0;
		pPrim->g3 = pPrim->g0;
		pPrim->b3 = pPrim->b1;
		pPrim->pad3 = pPrim->code;

		// copy high line coords to xy0 xy1 from param 1
		pPrim->x0 = hiLine[0];
		pPrim->x1 = hiLine[1];
		pPrim->y0 = hiLine[2];
		pPrim->y1 = hiLine[3];

		// copy high line coords to xy2 xy3 from param 2
		pPrim->x2 = loLine[0];
		pPrim->x3 = loLine[1];
		pPrim->y2 = loLine[2];
		pPrim->y3 = loLine[3];

		// pull texture data from global icon array (0x2f = tread)
		struct TextureLayout* texSkid = &globalGameTracker->ptrIcons[0x2F]->texLayout;

		// int 1 from texLayout
		pPrim->u0 = texSkid->u0;
		pPrim->v0 = texSkid->v0;
		pPrim->clut = texSkid->clut;

				// TODO: fix this
				if ((*(uint *)(param_4 + 0x24) & 1) == 0) {
					uVar8 = 0x40;
				}
				else {
					uVar8 = 0x60;
				}

				uVar8 = texSkid->tpage & 0xff9f | uVar8;


		// int 2 from texLayout
		pPrim->u1 = texSkid->u1;
		pPrim->v1 = texSkid->v2;
		pPrim->tpage = texSkid->tpage; // but extra flag is applied based on param_4, maybe this check already exists in other place?

		// int 3 from texLayout
		pPrim->u2 = texSkid->u2;
		pPrim->v2 = texSkid->u2;

		pPrim->u3 = texSkid->u3;
		pPrim->v3 = texSkid->u3;

		// save tag and prim ptr
		puVar9 = (uint *)(*(int *)(*(int *)(param_4 + 0x18) + 0xf4) + (param_3 >> 6) * 4);
		pPrim->tag = *puVar9 | 0xc000000;
		*puVar9 = (uint)pPrim & 0xffffff;
	}
}