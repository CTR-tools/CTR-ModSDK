#include <common.h>

// copy/paste from gGT in namespace_Main.h
struct RenderList
{
	// 1P2P lists (might change in 3P4P)
	// [0] - 0x00: Force4x4
	// [1] - 0x08: DynamicSubdiv
	// [2] - 0x10: Force4x2
	// [3] - 0x18: Force4x1
	// [4] - 0x20: Water
	struct
	{
		void* ptrQuadBlocksRendered;
		struct BSP** bspListStart;
	} list[5];
	
	// 0x28
	struct BSP** bspListStart_FullDynamic;
	void* ptrQuadBlocksRendered_FullDynamic;
	
	// 0x30 large

	// one for each player
};

void TEST_226(
	struct RenderList* RL,
	struct TileView* view,
	struct mesh_info* mi,
	struct PrimMem* primMem,
	int* visMem10,
	int unk)
{
	short posScreen1[4];
	short posScreen2[4];
	short posScreen3[4];
	short posScreen4[4];
	
	struct LevVertex* pVA = &mi->ptrVertexArray[0];
	
	#if 1
	// temporary, until CAMERA_ThTick is done
	view->distanceToScreen_PREV = view->distanceToScreen_CURR;
	
	// temporary, until TileView_UpdateFrustum is done
	gte_SetGeomScreen(view->distanceToScreen_PREV);
	#endif
	
	MATRIX* mat2 = &view->matrix_ViewProj;
			
	gte_SetRotMatrix(mat2);
	gte_SetTransMatrix(mat2);
	gte_SetGeomOffset(view->rect.w >> 1, view->rect.h >> 1);
	
	void* ot = &view->ptrOT[0];
	
	#if 0
	printf("\nDump Level:\n");
	#endif
	
	int numBlock = 0;
	
	POLY_GT4* p;
	void* pNext;
	void* pCurr;
	
#define USE_RL 0

#if USE_RL
	for(int i = 0; i < 5; i++)
	{
		if(RL->list[i].bspListStart == 0) continue;
		
		int* slot;
		struct BSP* bsp;
		int count = 0;
		
		for(
			slot = RL->list[i].bspListStart;
			slot[0] != 0;
			count++,
			slot = slot[0]
		)
		{
			bsp = slot[1];
#else
		for(int i = 0; i < mi->numBspNodes; i++)
		{
			struct BSP* bsp = &mi->bspRoot[i];

			// draw leaf nodes only
			if ((bsp->flag & 1 == 0))
				continue;

			if (bsp->data.leaf.ptrQuadBlockArray == 0)
				continue;

// This gives no improvement
#if 0
			// === Test every BSP block against Frustum ===

			short posBSP[3];
			int otZ_block;

			// minX, minY, minZ
			posBSP[0] = bsp->box.min[0];
			posBSP[1] = bsp->box.min[1];
			posBSP[2] = bsp->box.min[2];
			gte_ldv0(&posBSP[0]);
			gte_rtps();
			gte_stotz(&otZ_block);
			gte_stsxy(&posScreen1[0]);
			if (posScreen1[0] > 0) goto PassFrustumBSP;
			if (posScreen1[0] < view->rect.w) goto PassFrustumBSP;
			if (otZ_block >= 0) continue;

			// fail Frustum BSP
			continue;

			PassFrustumBSP:
#endif


#endif
			for(int j = 0; j < bsp->data.leaf.numQuads; j++)
			{
				struct QuadBlock* block;
				block = &bsp->data.leaf.ptrQuadBlockArray[j];

				// dont invisible walls
				if ((block->quadFlags & (1 << 15)) != 0) continue;

				int idHigh[16] =
				{
					0,4,5,6,
					4,1,6,7,
					5,6,2,8,
					6,7,8,3
				};

				int idLow[4] =
				{
					0,1,2,3
				};

				// low LOD
				int num = 1;
				int* id = idLow;

				// high LOD
				num = 4;
				id = idHigh;
		
				for (int k = 0; k < num; k++)
				{
					p = primMem->curr;
					pNext = p + 1;
					pCurr = p;
					if (pNext > ((unsigned int)primMem->end - 0x200)) return;

					*(int*)&p->r0 = *(int*)&pVA[block->index[id[4*k+0]]].color_hi[0];
					*(int*)&p->r1 = *(int*)&pVA[block->index[id[4*k+1]]].color_hi[0];
					*(int*)&p->r2 = *(int*)&pVA[block->index[id[4*k+2]]].color_hi[0];
					*(int*)&p->r3 = *(int*)&pVA[block->index[id[4*k+3]]].color_hi[0];

					setPolyGT4(p);

					gte_ldv0(&pVA[block->index[id[4 * k + 0]]].pos[0]);
					gte_rtps();
					gte_stsxy(&posScreen1[0]);

					gte_ldv0(&pVA[block->index[id[4 * k + 1]]].pos[0]);
					gte_rtps();
					gte_stsxy(&posScreen2[0]);

					gte_ldv0(&pVA[block->index[id[4 * k + 2]]].pos[0]);
					gte_rtps();
					gte_stsxy(&posScreen3[0]);

					gte_ldv0(&pVA[block->index[id[4 * k + 3]]].pos[0]);
					gte_rtps();
					gte_stsxy(&posScreen4[0]);

					// to be in viewport, coordinates must be
					// X: [0, 0x40]
					// Y: [0, 0xA0]
					setXY4(p,
						(posScreen1[0]), (posScreen1[1]),	// XY0
						(posScreen2[0]), (posScreen2[1]),	// XY1
						(posScreen3[0]), (posScreen3[1]),	// XY2
						(posScreen4[0]), (posScreen4[1]));

					if (num == 4)
					{
						// must remove flags that are stored in pointer
						unsigned int ptr = block->ptr_texture_mid[k];
						struct TextureLayout* tl = ptr;

						if (ptr & 1)
						{
							ptr = ptr & ~(3);
							tl = *(int*)ptr;
						}

						if (tl != 0)
						{
							//move ptr to highest mid lod
							tl += 2;

							setUV4(p,
								tl->u0, tl->v0,
								tl->u1, tl->v1,
								tl->u2, tl->v2,
								tl->u3, tl->v3);

							p->clut = tl->clut;
							p->tpage = tl->tpage;
						}
					}

					else
					{
						struct TextureLayout* tl = block->ptr_texture_low;
						if (tl != 0)
						{
							setUV4(p,
								tl->u0, tl->v0,
								tl->u1, tl->v1,
								tl->u2, tl->v2,
								tl->u3, tl->v3);

							p->clut = tl->clut;
							p->tpage = tl->tpage;
						}
					}

					gte_stsxy3(&posScreen1[0], &posScreen2[0], &posScreen3[0]);

					// === NOT DONE ===
					// Need draw_order flags from quadblock
					// to determine front, back, or no culling

					// check CW/CCW culling
					int opZ;
					gte_nclip();
					gte_stopz(&opZ);
					int boolPassCull = (opZ < 0);

					if (boolPassCull)
					{
						int otZ;
						gte_avsz3();
						gte_stotz(&otZ);

						if (otZ > 8)
						{
							if (otZ < 4080)
							{
								AddPrim((u_long*)ot + (otZ >> 2), pCurr);
								primMem->curr = pNext;
							}
						}
					}
				}
			}
		}
	
#if USE_RL
	}
#endif
}