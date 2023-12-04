#include <common.h>

int bi = 0;
int GetBit(unsigned char* vertData)
{
	int ret = (vertData[bi >> 3] & (1 << (bi & 7))) != 0;
	bi++;
	return ret;
}

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

			// not this, this is identity matrix
#if 0
			MATRIX* mat1 = &view->matrix_ViewProj;
			*(int*)&mat1->m[0][0] = 0x1000;
			*(int*)&mat1->m[1][1] = 0x900; // -- temporary --
			*(int*)&mat1->m[2][2] = 0x1000;
#endif

			// HARD-CODE MATRIX
#if 0
			// copy from running CTR instance in no$psx,
			// INSTANCE IDPP offset 0x78 is a 4x4 MVP
			// INSTANCE IDPP offset 0x98 is a 3x3, idk
			MATRIX* mat2 = &curr->matrix;
			*(int*)&mat2->m[0][0] = 0x332;
			*(int*)&mat2->m[0][2] = 0x205;
			*(int*)&mat2->m[1][1] = 0xFDAC;
			*(int*)&mat2->m[2][0] = 0x13B;
			*(int*)&mat2->m[2][2] = 0xFFFFFAC2;
			mat2->t[0] = 0;
			mat2->t[1] = 0x58;
			mat2->t[2] = 0x320;
#endif

#if 1
			// shouldn't need this, matrix is invalid
			curr->scale[0] = 0xCCC / 4;
			curr->scale[1] = 0xCCC / 4;
			curr->scale[2] = 0xCCC / 4;

			MATRIX* mat2 = MulMatrix(&view->matrix_ViewProj, &curr->matrix);
			//MATRIX* mat2 = &curr->matrix;

			// where does this come from?
			mat2->t[0] = 0;
			mat2->t[1] = 0x58;
			mat2->t[2] = 0x320;
#endif

			if (gGT->numPlyrNextGame > 2)
				mat2->t[2] = 0x3E8;

			// how do I multiply mat1 and mat2 together?
			gte_SetRotMatrix(mat2);
			gte_SetTransMatrix(mat2);
			SetGeomOffset(view->rect.w >> 1, view->rect.h >> 1);

			struct Model* m = curr->model;

#if 0 // ANIM_TEST
			m = gGT->modelPtr[0x3e];
#endif

			struct ModelHeader* mh = &m->headers[0];

			// assume unanimated
			struct ModelFrame* mf = mh->ptrFrameData;
			struct ModelAnim* ma = 0;

			// animated
			if (mf == 0)
			{
				// HARD-CODE MATRIX
#if 1
				// copy from running CTR instance in no$psx,
				// INSTANCE IDPP offset 0x78 is a 4x4 MVP
				// INSTANCE IDPP offset 0x98 is a 3x3, idk
				MATRIX* mat2 = &curr->matrix;
				*(int*)&mat2->m[0][0] = 0x3db1;
				*(int*)&mat2->m[0][2] = 0xf90204;
				*(int*)&mat2->m[1][1] = 0xfea8f8ab;
				*(int*)&mat2->m[2][0] = 0x262095c;
				*(int*)&mat2->m[2][2] = 0xfffff328;
				mat2->t[0] = 0xfffffcb0;
				mat2->t[1] = 0x284;
				mat2->t[2] = 0xfb0;
				gte_SetRotMatrix(mat2);
				gte_SetTransMatrix(mat2);
#endif
				// animation
				ma = m->headers[0].ptrAnimations[0];

				int frameIndex = gGT->timer % ma->numFrames;
				gGT->timer++;

				// if animation is compressed
				if (ma->modelDeltaArray != 0)
				{
					// reset to first frame
					frameIndex = 0;
				}

				// cast
				char* maByte = (char*)ma;
				maByte = MODELANIM_GETFRAME(maByte);
				maByte = &maByte[ma->frameSize * frameIndex];

				// frame data
				mf = maByte;
			}

			char* vertData = (char*)&mf[0] + mf->vertexOffset;

			// 3FF is background, 0x0 is minimum depth
			void* ot = &view->ptrOT[0];

			//helper type, kinda same as RGB
			//a 255 grid "compressed vertex" 0 = 0.0 and 255 = 1.0. 256 steps only.
			typedef struct CompVertex {
				u_char X;
				u_char Y;
				u_char Z;
			} CompVertex;

			//flag values and end of list
#define END_OF_LIST 0xFFFFFFFF
#define DRAW_CMD_FLAG_NEW_STRIP (1 << 7)
#define DRAW_CMD_FLAG_SWAP_VERTEX (1 << 6)
#define DRAW_CMD_FLAG_FLIP_NORMAL (1 << 5)
#define DRAW_CMD_FLAG_CULLING (1 << 4)
#define DRAW_CMD_FLAG_COLOR_SCRATCHPAD (1 << 3)
#define DRAW_CMD_FLAG_NEW_VERTEX (1 << 2)
//bits 0 and 1 assumed unused

//variables
//sequentially point to the next vertex, increases once NEW_VERTEX flag comes in
			int vertexIndex = 0;
			//current strip length
			int stripLength = 0;
			CompVertex* ptrVerts = vertData;
			u_int* pCmd = mh->ptrCommandList;

			//a "shifting window", here we update the vertices and read triangle once it's ready
			//you need same cache for both colors and texture layouts
			CompVertex tempCoords[4];
			int tempColor[4];
			struct TextureLayout* tempTex[4];

			//i believe this must be scratchpad, but it uses 4 bytes, this array is only 3 bytes (like array buffer for simplicity).
			//the idea is that it loads vertices to scratchpad and with proper sorting,
			//you can draw may trigles of the list with minimum additional loads
			//then once you don't need vertex data, you can overwrite same indices with new data
			CompVertex stack[256];

			// pCmd[0] is number of commands
			pCmd++;

			// compression
			int x_alu = 0;
			int y_alu = 0;
			int z_alu = 0;
			bi = 0;

			//loop commands until we hit the end marker 
			while (*pCmd != END_OF_LIST)
			{
				//extract individual values from the command
				//refactor to a set of inline macros?
				u_short flags = (*pCmd >> (8 * 3)) & 0xFF; //8 bits
				u_short stackIndex = (*pCmd >> 16) & 0xFF; //8 bits
				u_short colorIndex = (*pCmd >> 9) & 0x7F; // 7 bits
				u_short texIndex = *pCmd & 0x1FF; //9 bits

				// if got a new vertex, load it
				if ((flags & DRAW_CMD_FLAG_NEW_VERTEX) == 0)
				{
					//copy from vertex buffer to stack index
					stack[stackIndex] = ptrVerts[vertexIndex];

					//and point to next vertex
					vertexIndex++;
				}

				//push current list back and insert value from stack
				//this code already have correct value on the stack, be aware of the order
				tempCoords[0] = tempCoords[1];
				tempCoords[1] = tempCoords[2];
				tempCoords[2] = tempCoords[3];
				tempCoords[3] = stack[stackIndex];

				if (ma != 0)
				{
					// Similar to Crash 2
					// https://github.com/cbhacks/CrashEdit/blob/647a97b004e7324ac4f648dcfcecc7d3f8412da3/CrashEdit/Controls/AnimationEntryViewer.cs#L451

					if (ma->modelDeltaArray != 0)
					{
						// == Does not work yet ==

						int temporal = ma->modelDeltaArray->arr[stackIndex];

						int XBits = (temporal) & 7;
						int YBits = (temporal >> 3) & 7;
						int ZBits = (temporal >> 6) & 7;

						int bx = (temporal >> 0x19) << 1;
						int by = (temporal << 7) >> 0x18;
						int bz = (temporal << 0xf) >> 0x18;

						if (XBits == 7) x_alu = 0;
						if (YBits == 7) y_alu = 0;
						if (ZBits == 7) z_alu = 0;

						// XZY frame data
						int newX = GetBit(vertData) ? -(1 << XBits) : 0;
						for (int j = 0; j < XBits; ++j)
						{
							newX |= GetBit(vertData) << (XBits - 1 - j);
						}

						int newY = GetBit(vertData) ? -(1 << YBits) : 0;
						for (int j = 0; j < YBits; ++j)
						{
							newY |= GetBit(vertData) << (YBits - 1 - j);
						}

						int newZ = GetBit(vertData) ? -(1 << ZBits) : 0;
						for (int j = 0; j < ZBits; ++j)
						{
							newZ |= GetBit(vertData) << (ZBits - 1 - j);
						}

						x_alu = (x_alu + newX + bx) % 256;
						y_alu = (y_alu + newY + by) % 256;
						z_alu = (z_alu + newZ + bz) % 256;

						tempCoords[3].X = x_alu;
						tempCoords[3].Y = y_alu;
						tempCoords[3].Z = z_alu;
					}
				}

				//push new color
				tempColor[0] = tempColor[1];
				tempColor[1] = tempColor[2];
				tempColor[2] = tempColor[3];
				tempColor[3] = mh->ptrColors[colorIndex];

				tempTex[0] = tempTex[1];
				tempTex[1] = tempTex[2];
				tempTex[2] = tempTex[3];
				tempTex[3] = (texIndex == 0 ? 0 : mh->ptrTexLayout[texIndex - 1]);

				//this is probably some tristrip optimization, so we can reuse vertex from the last triangle
				//and only spend 1 command
				if ((flags & DRAW_CMD_FLAG_SWAP_VERTEX) != 0)
				{
					tempCoords[1] = tempCoords[0];
					tempColor[1] = tempColor[0];
				}

				//if got reset flag, reset tristrip vertex counter
				if ((flags & DRAW_CMD_FLAG_NEW_STRIP) != 0)
				{
					stripLength = 0;
				}

				//enough data to add prim
				if (stripLength >= 2)
				{
					void* pFinal;

					if (tempTex[3] == 0)
					{
						POLY_G3* p = primMem->curr;
						primMem->curr = p + 1;

						*(int*)&p->r0 = tempColor[1];
						*(int*)&p->r1 = tempColor[2];
						*(int*)&p->r2 = tempColor[3];

						setPolyG3(p);

						// === Copy/Paste in both prims
						short zz;
						posWorld1[0] = ((mf->pos[0] + tempCoords[1].X) * mh->scale[0]) >> 8;
						posWorld1[1] = ((mf->pos[2] + tempCoords[1].Y) * mh->scale[2]) >> 8;
						posWorld1[2] = ((mf->pos[1] + tempCoords[1].Z) * mh->scale[1]) >> 8;
						posWorld1[3] = 0;
						zz = posWorld1[2];
						posWorld1[2] = posWorld1[1];
						posWorld1[1] = zz;
						posWorld1[0] = (posWorld1[0] * curr->scale[0]) >> 12;
						posWorld1[1] = (posWorld1[1] * curr->scale[1]) >> 12;
						posWorld1[2] = (posWorld1[2] * curr->scale[2]) >> 12;
						gte_ldv0(&posWorld1[0]);
						gte_rtps();
						gte_stsxy(&posScreen1[0]);

						posWorld2[0] = ((mf->pos[0] + tempCoords[2].X) * mh->scale[0]) >> 8;
						posWorld2[1] = ((mf->pos[2] + tempCoords[2].Y) * mh->scale[2]) >> 8;
						posWorld2[2] = ((mf->pos[1] + tempCoords[2].Z) * mh->scale[1]) >> 8;
						posWorld2[3] = 0;
						zz = posWorld2[2];
						posWorld2[2] = posWorld2[1];
						posWorld2[1] = zz;
						posWorld2[0] = (posWorld2[0] * curr->scale[0]) >> 12;
						posWorld2[1] = (posWorld2[1] * curr->scale[1]) >> 12;
						posWorld2[2] = (posWorld2[2] * curr->scale[2]) >> 12;
						gte_ldv0(&posWorld2[0]);
						gte_rtps();
						gte_stsxy(&posScreen2[0]);

						posWorld3[0] = ((mf->pos[0] + tempCoords[3].X) * mh->scale[0]) >> 8;
						posWorld3[1] = ((mf->pos[2] + tempCoords[3].Y) * mh->scale[2]) >> 8;
						posWorld3[2] = ((mf->pos[1] + tempCoords[3].Z) * mh->scale[1]) >> 8;
						posWorld3[3] = 0;
						zz = posWorld3[2];
						posWorld3[2] = posWorld3[1];
						posWorld3[1] = zz;
						posWorld3[0] = (posWorld3[0] * curr->scale[0]) >> 12;
						posWorld3[1] = (posWorld3[1] * curr->scale[1]) >> 12;
						posWorld3[2] = (posWorld3[2] * curr->scale[2]) >> 12;
						gte_ldv0(&posWorld3[0]);
						gte_rtps();
						gte_stsxy(&posScreen3[0]);

						// to be in viewport, coordinates must be
						// X: [0, 0x40]
						// Y: [0, 0xA0]
						setXY3(p,
							(posScreen1[0]), (posScreen1[1]),	// XY0
							(posScreen2[0]), (posScreen2[1]),	// XY1
							(posScreen3[0]), (posScreen3[1]));	// XY2

						pFinal = p;
					}
					else
					{
						POLY_GT3* p = primMem->curr;
						primMem->curr = p + 1;

						*(int*)&p->r0 = tempColor[1];
						*(int*)&p->u0 = *(int*)&tempTex[3]->u0;

						*(int*)&p->r1 = tempColor[2];
						*(int*)&p->u1 = *(int*)&tempTex[3]->u1;

						*(int*)&p->r2 = tempColor[3];
						*(short*)&p->u2 = *(short*)&tempTex[3]->u2;

						setPolyGT3(p);

						// === Copy/Paste in both prims
						short zz;
						posWorld1[0] = ((mf->pos[0] + tempCoords[1].X) * mh->scale[0]) >> 8;
						posWorld1[1] = ((mf->pos[2] + tempCoords[1].Y) * mh->scale[2]) >> 8;
						posWorld1[2] = ((mf->pos[1] + tempCoords[1].Z) * mh->scale[1]) >> 8;
						posWorld1[3] = 0;
						zz = posWorld1[2];
						posWorld1[2] = posWorld1[1];
						posWorld1[1] = zz;
						posWorld1[0] = (posWorld1[0] * curr->scale[0]) >> 12;
						posWorld1[1] = (posWorld1[1] * curr->scale[1]) >> 12;
						posWorld1[2] = (posWorld1[2] * curr->scale[2]) >> 12;
						gte_ldv0(&posWorld1[0]);
						gte_rtps();
						gte_stsxy(&posScreen1[0]);

						posWorld2[0] = ((mf->pos[0] + tempCoords[2].X) * mh->scale[0]) >> 8;
						posWorld2[1] = ((mf->pos[2] + tempCoords[2].Y) * mh->scale[2]) >> 8;
						posWorld2[2] = ((mf->pos[1] + tempCoords[2].Z) * mh->scale[1]) >> 8;
						posWorld2[3] = 0;
						zz = posWorld2[2];
						posWorld2[2] = posWorld2[1];
						posWorld2[1] = zz;
						posWorld2[0] = (posWorld2[0] * curr->scale[0]) >> 12;
						posWorld2[1] = (posWorld2[1] * curr->scale[1]) >> 12;
						posWorld2[2] = (posWorld2[2] * curr->scale[2]) >> 12;
						gte_ldv0(&posWorld2[0]);
						gte_rtps();
						gte_stsxy(&posScreen2[0]);

						posWorld3[0] = ((mf->pos[0] + tempCoords[3].X) * mh->scale[0]) >> 8;
						posWorld3[1] = ((mf->pos[2] + tempCoords[3].Y) * mh->scale[2]) >> 8;
						posWorld3[2] = ((mf->pos[1] + tempCoords[3].Z) * mh->scale[1]) >> 8;
						posWorld3[3] = 0;
						zz = posWorld3[2];
						posWorld3[2] = posWorld3[1];
						posWorld3[1] = zz;
						posWorld3[0] = (posWorld3[0] * curr->scale[0]) >> 12;
						posWorld3[1] = (posWorld3[1] * curr->scale[1]) >> 12;
						posWorld3[2] = (posWorld3[2] * curr->scale[2]) >> 12;
						gte_ldv0(&posWorld3[0]);
						gte_rtps();
						gte_stsxy(&posScreen3[0]);

						// to be in viewport, coordinates must be
						// X: [0, 0x40]
						// Y: [0, 0xA0]
						setXY3(p,
							(posScreen1[0]), (posScreen1[1]),	// XY0
							(posScreen2[0]), (posScreen2[1]),	// XY1
							(posScreen3[0]), (posScreen3[1]));	// XY2

						pFinal = p;
					}

					int otZ;
					gte_stsxy3(&posScreen1[0], &posScreen2[0], &posScreen3[0]);
					gte_avsz3();
					gte_stotz(&otZ);
					AddPrim((u_long*)ot + (otZ >> 1), pFinal);

					if ((flags & DRAW_CMD_FLAG_FLIP_NORMAL) != 0)
					{
						//swap 2 coords to flip the normal here or can have 2 separate sumbission branches
					}
				}

				//strip length increases
				stripLength++;

				//proceed to the next command
				pCmd++;
			}
		}
	}
}