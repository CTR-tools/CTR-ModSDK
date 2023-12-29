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

enum RotateFlipType
{
	RFT_None = 0,
	RFT_Rotate90 = 1,
	RFT_Rotate180 = 2,
	RFT_Rotate270 = 3,
	RFT_FlipRotate270 = 4,
	RFT_FlipRotate180 = 5,
	RFT_FlipRotate90 = 6,
	RFT_Flip = 7,
	RFT_NoMatch = -1
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
					5,0,6,4,
					6,4,7,1,
					2,5,8,6,
					8,6,3,7
				};

				int idLow[4] =
				{
					2,0,3,1
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

					// if num == 1
					struct TextureLayout* tl = block->ptr_texture_low;

					if (num == 4)
					{
						// must remove flags that are stored in pointer
						unsigned int ptr = block->ptr_texture_mid[k];
						tl = ptr;

						if (ptr & 1)
						{
							ptr = ptr & ~(3);
							tl = *(int*)ptr;
						}

						if (tl != 0)
						{
							//move ptr to highest mid lod
							tl += 2;
						}
					}


					unsigned int draw_order_high = block->draw_order_high;
					unsigned int draw_order_low = block->draw_order_low;

					unsigned int rotAndOrder = (draw_order_low >> (8 + k * 5)) & 0x1F;
					unsigned int justRot = rotAndOrder & 7;
					unsigned int justOrder = (rotAndOrder >> 3) & 3;

					if (tl != 0)
					{
						// 2031
						if (justRot == RFT_None)
						{
							setUV4(p,
								tl->u2, tl->v2,
								tl->u0, tl->v0,
								tl->u3, tl->v3,
								tl->u1, tl->v1);
						}

						// 3210
						else if (justRot == RFT_Rotate90)
						{
							setUV4(p,
								tl->u3, tl->v3,
								tl->u2, tl->v2,
								tl->u1, tl->v1,
								tl->u0, tl->v0);
						}

						// 1302
						else if (justRot == RFT_Rotate180)
						{
							setUV4(p,
								tl->u1, tl->v1,
								tl->u3, tl->v3,
								tl->u0, tl->v0,
								tl->u2, tl->v2);
						}

						// 0123
						else if (justRot == RFT_Rotate270)
						{
							setUV4(p,
								tl->u0, tl->v0,
								tl->u1, tl->v1,
								tl->u2, tl->v2,
								tl->u3, tl->v3);
						}

						// 1032
						else if (justRot == RFT_FlipRotate270)
						{
							setUV4(p,
								tl->u1, tl->v1,
								tl->u0, tl->v0,
								tl->u3, tl->v3,
								tl->u2, tl->v2);
						}

						// 3102
						else if (justRot == RFT_FlipRotate180)
						{
							setUV4(p,
								tl->u0, tl->v0,
								tl->u2, tl->v2,
								tl->u1, tl->v1,
								tl->u3, tl->v3);
						}

						// 2301
						else if (justRot == RFT_FlipRotate90)
						{
							setUV4(p,
								tl->u2, tl->v2,
								tl->u3, tl->v3,
								tl->u0, tl->v0,
								tl->u1, tl->v1);
						}

						// 3120
						else if (justRot == RFT_Flip)
						{
							setUV4(p,
								tl->u3, tl->v3,
								tl->u1, tl->v1,
								tl->u2, tl->v2,
								tl->u0, tl->v0);
						}

						else
							continue;

						p->clut = tl->clut;
						p->tpage = tl->tpage;
					}

					int u[4];
					int v[4];

					u[0] = p->u0;
					v[0] = p->v0;

					u[1] = p->u1;
					v[1] = p->v1;

					u[2] = p->u2;
					v[2] = p->v2;

					u[3] = p->u3;
					v[3] = p->v3;

					#define SETME(x0, x1, x2, x3) p->u0 = u[x0-1], p->v0 = v[x0-1]; p->u1 = u[x1-1], p->v1 = v[x1-1]; p->u2 = u[x2-1], p->v2 = v[x2-1]; p->u3 = u[x3-1], p->v3 = v[x3-1];


					if (justOrder == 1)
					{
						// for a good example, see AdvHub Warppads

						/*SETME(1, 3, 2, 4);*/
						SETME(3, 1, 4, 2);
					}

					else if (justOrder == 2)
					{
						// for a good example, see N Gin Labs

						/*SETME(3, 4, 2, 1);*/
						SETME(4, 3, 1, 2);
					}		   

					gte_stsxy3(&posScreen1[0], &posScreen2[0], &posScreen3[0]);
					
					// automatic pass, if no frontface or backface culling
					int boolPassCull = (draw_order_low & 0x80000000) != 0;

					if (!boolPassCull)
					{
						// check CW/CCW culling
						int opZ;
						gte_nclip();
						gte_stopz(&opZ);
						boolPassCull = (opZ < 0);
					}

					if (boolPassCull)
					{
						int otZ;
						gte_avsz3();
						gte_stotz(&otZ);

						if (otZ > 8)
						{
							if (otZ > 4080)
								otZ = 4080;
							
							if ((p->tpage & 0x40) == 0)
								setSemiTrans(p, true);

							AddPrim((u_long*)ot + (otZ >> 2), pCurr);
							primMem->curr = pNext;
							
						}
					}
				}
			}
		}
	
#if USE_RL
	}
#endif
}