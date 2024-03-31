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
	struct PushBuffer* pb,
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
	pb->distanceToScreen_PREV = pb->distanceToScreen_CURR;

	// temporary, until PushBuffer_UpdateFrustum is done
	gte_SetGeomScreen(pb->distanceToScreen_PREV);
#endif

	MATRIX* mat2 = &pb->matrix_ViewProj;

	gte_SetRotMatrix(mat2);
	gte_SetTransMatrix(mat2);
	gte_SetGeomOffset(pb->rect.w >> 1, pb->rect.h >> 1);

	void* ot = &pb->ptrOT[0];

#if 0
	printf("\nDump Level:\n");
#endif

	int numBlock = 0;

	POLY_GT4* p;
	void* pNext;
	void* pCurr;

#define USE_RL 0

#if USE_RL
	for (int i = 0; i < 5; i++)
	{
		if (RL->list[i].bspListStart == 0) continue;

		int* slot;
		struct BSP* bsp;
		int count = 0;

		for (
			slot = RL->list[i].bspListStart;
			slot[0] != 0;
			count++,
			slot = slot[0]
			)
		{
			bsp = slot[1];
#else
	for (int i = 0; i < mi->numBspNodes; i++)
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
		// edit: did I forget gte_avsz3(); the last time I tested?
		// Is that why the test gave no improvement?
		gte_stotz(&otZ_block);
		gte_stsxy(&posScreen1[0]);
		if (posScreen1[0] > 0) goto PassFrustumBSP;
		if (posScreen1[0] < pb->rect.w) goto PassFrustumBSP;
		if (otZ_block >= 0) continue;

		// fail Frustum BSP
		continue;

	PassFrustumBSP:
#endif


#endif
		for (int j = 0; j < bsp->data.leaf.numQuads; j++)
		{
			struct QuadBlock* block;
			block = &bsp->data.leaf.ptrQuadBlockArray[j];

			// dont invisible walls
			if ((block->quadFlags & (1 << 15)) != 0) continue;

			int boolWater = 0;

			// check for water
			if((bsp->flag & 2) != 0)
			{
				POLY_F4* p = primMem->curr;
				void* pNext = p + 1;

				p->r0 = 0x7F;
				p->g0 = 0x7F;
				p->b0 = 0xFF;
				setPolyF4(p);

				gte_ldv0(&pVA[block->index[0]].pos[0]);
				gte_rtps();
				gte_stsxy(&posScreen1[0]);

				gte_ldv0(&pVA[block->index[1]].pos[0]);
				gte_rtps();
				gte_stsxy(&posScreen2[0]);

				gte_ldv0(&pVA[block->index[2]].pos[0]);
				gte_rtps();
				gte_stsxy(&posScreen3[0]);

				gte_ldv0(&pVA[block->index[3]].pos[0]);
				gte_rtps();
				gte_stsxy(&posScreen4[0]);

				setXY4(p,
					(posScreen1[0]), (posScreen1[1]),	// XY0
					(posScreen2[0]), (posScreen2[1]),	// XY1
					(posScreen3[0]), (posScreen3[1]),	// XY2
					(posScreen4[0]), (posScreen4[1]));

				// automatic pass, if no frontface or backface culling
				int boolPassCull = (block->draw_order_low & 0x80000000) != 0;

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
					short midX = (p->x0 + p->x1 + p->x2 + p->x3) / 4;
					short midY = (p->y0 + p->y1 + p->y2 + p->y3) / 4;

					short midArr[4] = { midX, midY, 0, 0 };
					gte_ldv0(midArr);

					int otZ;
					gte_avsz3();
					gte_stotz(&otZ);

					if (otZ > 0)
					{
						if (otZ > 4080)
							otZ = 4080;

						AddPrim((u_long*)ot + (otZ >> 2), p);
						primMem->curr = pNext;
					}
				}
				
				// next quadblock
				continue;
			}

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

				*(int*)&p->r0 = *(int*)&pVA[block->index[id[4 * k + 0]]].color_hi[0];
				*(int*)&p->r1 = *(int*)&pVA[block->index[id[4 * k + 1]]].color_hi[0];
				*(int*)&p->r2 = *(int*)&pVA[block->index[id[4 * k + 2]]].color_hi[0];
				*(int*)&p->r3 = *(int*)&pVA[block->index[id[4 * k + 3]]].color_hi[0];

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
					short midX = (p->x0 + p->x1 + p->x2 + p->x3) / 4;
					short midY = (p->y0 + p->y1 + p->y2 + p->y3) / 4;

					short midArr[4] = { midX, midY, 0, 0 };
					gte_ldv0(midArr);

					int otZ;
					gte_avsz3();
					gte_stotz(&otZ);

					if (otZ > 0)
					{
						if (otZ > 4080)
							otZ = 4080;

						if ((p->tpage & 0x40) == 0)
							setSemiTrans(p, true);

						AddPrim((u_long*)ot + (otZ >> 2), pCurr);
						primMem->curr = pNext;

						//void AddPrimPGXP(void*, POLY_GT4*);
						//AddPrimPGXP(ot, pCurr);
						//primMem->curr = p + 4;

					}
				}
			}
		}
	}

#if USE_RL
		}
#endif
	}

void AddPrimPGXP(void* ot, POLY_GT4 * p)
{
	POLY_GT4 backup;
	POLY_GT4* b = &backup;
	memcpy(b, p, sizeof(POLY_GT4));

	short midX = (b->x0 + b->x1 + b->x2 + b->x3) / 4;
	short midY = (b->y0 + b->y1 + b->y2 + b->y3) / 4;

	char midU = (b->u0 + b->u1 + b->u2 + b->u3) / 4;
	char midV = (b->v0 + b->v1 + b->v2 + b->v3) / 4;

	char midR = (b->r0 + b->r1 + b->r2 + b->r3) / 4;
	char midG = (b->g0 + b->g1 + b->g2 + b->g3) / 4;
	char midB = (b->b0 + b->b1 + b->b2 + b->b3) / 4;

	short midArr[4] = { midX, midY, 0, 0 };
	gte_ldv0(midArr);

	for (int i = 0; i < 4; i++)
	{
		setPolyGT4(p);

		p->clut = b->clut;
		p->tpage = b->tpage;

		if ((p->tpage & 0x40) == 0)
			setSemiTrans(p, true);

		// 0 top right
		// 1 bottom right
		// 2 top left
		// 3 bottom left

		switch (i)
		{
		case 0:
			p->x0 = b->x0;
			p->y0 = b->y0;
			p->u0 = b->u0;
			p->v0 = b->v0;
			p->r0 = b->r0;
			p->g0 = b->g0;
			p->b0 = b->b0;

			p->x1 = (b->x1 + b->x0) / 2;
			p->y1 = (b->y1 + b->y0) / 2;
			p->u1 = (b->u1 + b->u0) / 2;
			p->v1 = (b->v1 + b->v0) / 2;
			p->r1 = (b->r1 + b->r0) / 2;
			p->g1 = (b->g1 + b->g0) / 2;
			p->b1 = (b->b1 + b->b0) / 2;

			p->x2 = (b->x2 + b->x0) / 2;
			p->y2 = (b->y2 + b->y0) / 2;
			p->u2 = (b->u2 + b->u0) / 2;
			p->v2 = (b->v2 + b->v0) / 2;
			p->r2 = (b->r2 + b->r0) / 2;
			p->g2 = (b->g2 + b->g0) / 2;
			p->b2 = (b->b2 + b->b0) / 2;

			p->x3 = midX;
			p->y3 = midY;
			p->u3 = midU;
			p->v3 = midV;
			p->r3 = midR;
			p->g3 = midG;
			p->b3 = midB;
			break;

		case 1:
			p->x0 = (b->x0 + b->x1) / 2;
			p->y0 = (b->y0 + b->y1) / 2;
			p->u0 = (b->u0 + b->u1) / 2;
			p->v0 = (b->v0 + b->v1) / 2;
			p->r0 = (b->r0 + b->r1) / 2;
			p->g0 = (b->g0 + b->g1) / 2;
			p->b0 = (b->b0 + b->b1) / 2;

			p->x1 = b->x1;
			p->y1 = b->y1;
			p->u1 = b->u1;
			p->v1 = b->v1;
			p->r1 = b->r1;
			p->g1 = b->g1;
			p->b1 = b->b1;

			p->x2 = midX;
			p->y2 = midY;
			p->u2 = midU;
			p->v2 = midV;
			p->r2 = midR;
			p->g2 = midG;
			p->b2 = midB;

			p->x3 = (b->x3 + b->x1) / 2;
			p->y3 = (b->y3 + b->y1) / 2;
			p->u3 = (b->u3 + b->u1) / 2;
			p->v3 = (b->v3 + b->v1) / 2;
			p->r3 = (b->r3 + b->r1) / 2;
			p->g3 = (b->g3 + b->g1) / 2;
			p->b3 = (b->b3 + b->b1) / 2;
			break;

		case 2:
			p->x0 = (b->x0 + b->x2) / 2;
			p->y0 = (b->y0 + b->y2) / 2;
			p->u0 = (b->u0 + b->u2) / 2;
			p->v0 = (b->v0 + b->v2) / 2;
			p->r0 = (b->r0 + b->r2) / 2;
			p->g0 = (b->g0 + b->g2) / 2;
			p->b0 = (b->b0 + b->b2) / 2;

			p->x1 = midX;
			p->y1 = midY;
			p->u1 = midU;
			p->v1 = midV;
			p->r1 = midR;
			p->g1 = midG;
			p->b1 = midB;

			p->x2 = b->x2;
			p->y2 = b->y2;
			p->u2 = b->u2;
			p->v2 = b->v2;
			p->r2 = b->r2;
			p->g2 = b->g2;
			p->b2 = b->b2;

			p->x3 = (b->x3 + b->x2) / 2;
			p->y3 = (b->y3 + b->y2) / 2;
			p->u3 = (b->u3 + b->u2) / 2;
			p->v3 = (b->v3 + b->v2) / 2;
			p->r3 = (b->r3 + b->r2) / 2;
			p->g3 = (b->g3 + b->g2) / 2;
			p->b3 = (b->b3 + b->b2) / 2;
			break;

		default:
			p->x0 = midX;
			p->y0 = midY;
			p->u0 = midU;
			p->v0 = midV;
			p->r0 = midR;
			p->g0 = midG;
			p->b0 = midB;

			p->x1 = (b->x1 + b->x3) / 2;
			p->y1 = (b->y1 + b->y3) / 2;
			p->u1 = (b->u1 + b->u3) / 2;
			p->v1 = (b->v1 + b->v3) / 2;
			p->r1 = (b->r1 + b->r3) / 2;
			p->g1 = (b->g1 + b->g3) / 2;
			p->b1 = (b->b1 + b->b3) / 2;

			p->x2 = (b->x2 + b->x3) / 2;
			p->y2 = (b->y2 + b->y3) / 2;
			p->u2 = (b->u2 + b->u3) / 2;
			p->v2 = (b->v2 + b->v3) / 2;
			p->r2 = (b->r2 + b->r3) / 2;
			p->g2 = (b->g2 + b->g3) / 2;
			p->b2 = (b->b2 + b->b3) / 2;

			p->x3 = b->x3;
			p->y3 = b->y3;
			p->u3 = b->u3;
			p->v3 = b->v3;
			p->r3 = b->r3;
			p->g3 = b->g3;
			p->b3 = b->b3;
			break;
		}

		int otZ;
		gte_avsz3();
		gte_stotz(&otZ);

		if (otZ > 4080)
			otZ = 4080;

		AddPrim((u_long*)ot + (otZ >> 2), p++);
	}
}