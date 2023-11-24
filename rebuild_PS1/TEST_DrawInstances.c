#include <common.h>

void TEST_DrawInstances(struct GameTracker* gGT)
{
	short posScreen1[4];
	short posWorld1[4];
	short posScreen2[4];
	short posWorld2[4];
	short posScreen3[4];
	short posWorld3[4];

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

			MATRIX* mat1 = &sdata->gGT->tileView[0].matrix_ViewProj;
			*(int*)&mat1->m[0][0] = 0x1000;
			*(int*)&mat1->m[1][1] = 0x900; // -- temporary --
			*(int*)&mat1->m[2][2] = 0x1000;

			MATRIX* mat2 = &curr->matrix;

			// how do I multiply mat1 and mat2 together?
			gte_SetRotMatrix(mat1);
			gte_SetTransMatrix(mat1);

			struct Model* m = curr->model;
			struct ModelHeader* mh = &m->headers[0];
			short* vertData = mh->ptrVertexData;

			// 3FF is background, 3FE is next depth slot
			void* ot = &view->ptrOT[0x3FE];

			for (int j = 0; j < 100; j++)
			{
				LINE_F3* p = primMem->curr;
				primMem->curr = p + 1;

				// set Poly_LineF3 len, code, and padding
				setLineF3(p);

				// RGB
				setRGB0(p, 
							data.ptrColor[PLAYER_BLUE + i][0], 
							data.ptrColor[PLAYER_BLUE + i][0]>>8, 
							data.ptrColor[PLAYER_BLUE + i][0]>>16
				);

				posWorld1[0] = vertData[j * 9 + 0];
				posWorld1[1] = vertData[j * 9 + 1];
				posWorld1[2] = vertData[j * 9 + 2];
				posWorld1[3] = 0;
				gte_ldv0(&posWorld1[0]);
				gte_rtps();
				gte_stsxy(&posScreen1[0]);

				posWorld2[0] = vertData[j * 9 + 3];
				posWorld2[1] = vertData[j * 9 + 4];
				posWorld2[2] = vertData[j * 9 + 5];
				posWorld2[3] = 0;
				gte_ldv0(&posWorld2[0]);
				gte_rtps();
				gte_stsxy(&posScreen2[0]);

				posWorld3[0] = vertData[j * 9 + 6];
				posWorld3[1] = vertData[j * 9 + 7];
				posWorld3[2] = vertData[j * 9 + 8];
				posWorld3[3] = 0;
				gte_ldv0(&posWorld3[0]);
				gte_rtps();
				gte_stsxy(&posScreen3[0]);

				setXY3(p,
					posScreen1[0], posScreen1[1],	// XY0
					posScreen2[0], posScreen2[1],	// XY1
					posScreen3[0], posScreen3[1]);	// XY2

				AddPrim(ot, p);
			}
		}
	}
}