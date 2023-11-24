#include <common.h>

void TEST_DrawInstances(struct GameTracker* gGT)
{
	struct OTMem* otMem = &gGT->backBuffer->otMem;
	struct PrimMem* primMem = &gGT->backBuffer->primMem;

	for (
			struct Instance* curr = gGT->JitPools.instance.taken.first;
			curr != 0;
			curr = curr->next
		)
	{
		for (int i = 0; i < gGT->numPlyrCurrGame; i++)
		{
			if ((curr->flags & 0x80) != 0) continue;

			struct InstDrawPerPlayer* idpp = INST_GETIDPP(curr);

			struct TileView* view = idpp[i].tileView;
			if (view == 0) continue;

			// reset, might be off by one frame and glitch in the top-left corner,
			// when leaving character selection back to main menu
			idpp[i].tileView = 0;

			struct Model* m = curr->model;

			for (int j = 0; j < 100; j++)
			{
				// 3FF is background, 3FE is next depth slot
				void* ot = &view->ptrOT[0x3FE];

				LINE_F3* p = primMem->curr;
				primMem->curr = p + 1;

				// set Poly_LineF3 len, code, and padding
				setLineF3(p);

				// RGB
				setRGB0(p, i*0x3F, 0, 0);

				setXY3(p,
					10, 10,		// XY0
					20, 10,		// XY1
					20, 20);	// XY2

				AddPrim(ot, p);
			}
		}
	}
}