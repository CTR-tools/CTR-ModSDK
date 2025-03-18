#include <common.h>

int bi = 0;

#ifdef REBUILD_PC
#ifndef __GNUC__
inline
#endif
#endif
int GetBitStream(unsigned int* vertData, int size)
{
	int* x = &vertData[bi >> 5];

	int size2 = 0;
	int size1 = size;
	int lastBit = ((bi&31)+size);
	
	if (lastBit >= 32)
	{
		size2 = lastBit - 32;
		size1 -= size2;
		lastBit = 32;
	}
	
	int ret = ((x[0] >> (32-lastBit)) & ((1 << size1)-1));
	
	if(size2 > 0)
		ret = (ret << size2) | ((x[1] >> (32-size2)) & ((1 << size2)-1));

	bi += size;

	return ret;
}

// copied out of PsyCross library,
// is this equal to the CTR function?
#ifndef REBUILD_PC
VECTOR* ApplyMatrixLV(MATRIX* m, VECTOR* v0, VECTOR* v1)
{
#if 1
	// correct Psy-Q implementation
	VECTOR tmpHI;
	VECTOR tmpLO;

	gte_SetRotMatrix(m);

	tmpHI.vx = v0->vx;
	tmpHI.vy = v0->vy;
	tmpHI.vz = v0->vz;

	if (tmpHI.vx < 0)
	{
		tmpLO.vx = -(-tmpHI.vx >> 0xf);
		tmpHI.vx = -(-tmpHI.vx & 0x7fff);
	}
	else
	{
		tmpLO.vx = tmpHI.vx >> 0xf;
		tmpHI.vx = tmpHI.vx & 0x7fff;
	}

	if (tmpHI.vy < 0)
	{
		tmpLO.vy = -(-tmpHI.vy >> 0xf);
		tmpHI.vy = -(-tmpHI.vy & 0x7fff);
	}
	else
	{
		tmpLO.vy = tmpHI.vy >> 0xf;
		tmpHI.vy = tmpHI.vy & 0x7fff;
	}

	if (tmpHI.vz < 0)
	{
		tmpLO.vz = -(-tmpHI.vz >> 0xf);
		tmpHI.vz = -(-tmpHI.vz & 0x7fff);
	}
	else
	{
		tmpLO.vz = tmpHI.vz >> 0xf;
		tmpHI.vz = tmpHI.vz & 0x7fff;
	}

	gte_ldlvl(&tmpLO);
	gte_rtir_sf0();
	gte_stlvnl(&tmpLO);

	gte_ldlvl(&tmpHI);
	gte_rtir();

	if (tmpLO.vx < 0)
		tmpLO.vx *= 8;
	else
		tmpLO.vx <<= 3;

	if (tmpLO.vy < 0)
		tmpLO.vy *= 8;
	else
		tmpLO.vy <<= 3;

	if (tmpLO.vz < 0)
		tmpLO.vz *= 8;
	else
		tmpLO.vz <<= 3;

	gte_stlvnl(&tmpHI);

	v1->vx = tmpHI.vx + tmpLO.vx;
	v1->vy = tmpHI.vy + tmpLO.vy;
	v1->vz = tmpHI.vz + tmpLO.vz;
#else
	APPLYMATRIX(m, v0, v1);
#endif
	return v1;
}
#endif

typedef struct CompVertex {
	u_char X;
	u_char Y;
	u_char Z;
} CompVertex;

typedef struct V4 {
	u_char X;
	u_char Y;
	u_char Z;
	u_char W;
} V4;

void DrawOneInst(struct Instance* curr)
{
	short posScreen1[4];
	short posWorld1[4];
	short posScreen2[4];
	short posWorld2[4];
	short posScreen3[4];
	short posWorld3[4];

	struct GameTracker* gGT = sdata->gGT;

	struct OTMem* otMem = &gGT->backBuffer->otMem;
	struct PrimMem* primMem = &gGT->backBuffer->primMem;

	for (int i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		struct InstDrawPerPlayer* idpp = INST_GETIDPP(curr);

		struct PushBuffer* pb = idpp[i].pushBuffer;
		if (pb == 0) continue;

#if 1
		// temporary, until CAMERA_ThTick is done
		pb->distanceToScreen_PREV = pb->distanceToScreen_CURR;

		// temporary, until PushBuffer_UpdateFrustum is done
		gte_SetGeomScreen(pb->distanceToScreen_PREV);
#endif

		// ============ Get ModelViewProj Matrix ==============

		MATRIX mvp;
		MATRIX* mat2 = &mvp;
		
		// why is this shifting by 0x10 instead of 0xC?
		
#define RCC(row, col, index) \
	((int)((int)pb->matrix_ViewProj.m[row][index] * (int)curr->matrix.m[index][col]) >> 0x10)

		mvp.m[0][0] = RCC(0, 0, 0) + RCC(0, 0, 1) + RCC(0, 0, 2);
		mvp.m[0][1] = RCC(0, 1, 0) + RCC(0, 1, 1) + RCC(0, 1, 2);
		mvp.m[0][2] = RCC(0, 2, 0) + RCC(0, 2, 1) + RCC(0, 2, 2);

		mvp.m[1][0] = RCC(1, 0, 0) + RCC(1, 0, 1) + RCC(1, 0, 2);
		mvp.m[1][1] = RCC(1, 1, 0) + RCC(1, 1, 1) + RCC(1, 1, 2);
		mvp.m[1][2] = RCC(1, 2, 0) + RCC(1, 2, 1) + RCC(1, 2, 2);

		mvp.m[2][0] = RCC(2, 0, 0) + RCC(2, 0, 1) + RCC(2, 0, 2);
		mvp.m[2][1] = RCC(2, 1, 0) + RCC(2, 1, 1) + RCC(2, 1, 2);
		mvp.m[2][2] = RCC(2, 2, 0) + RCC(2, 2, 1) + RCC(2, 2, 2);

		// ============ Get Perspective Translation ==============

		VECTOR pos;
		pos.vx = curr->matrix.t[0] - pb->matrix_Camera.t[0];
		pos.vy = curr->matrix.t[1] - pb->matrix_Camera.t[1];
		pos.vz = curr->matrix.t[2] - pb->matrix_Camera.t[2];

		// TODO: ApplyMatrixLV_stub needs to be rewritten,
		// may be optimizations that Naughty Dog used in it
		ApplyMatrixLV(&pb->matrix_ViewProj, &pos, &mat2->t[0]);

		gte_SetRotMatrix(mat2);
		gte_SetTransMatrix(mat2);
		gte_SetGeomOffset(pb->rect.w >> 1, pb->rect.h >> 1);

		// temporary, for pushBuffer_UI
		if ((curr->flags & 0x400) != 0)
		{
			gte_SetRotMatrix(&curr->matrix);
			gte_SetTransMatrix(&curr->matrix);

			// disable 3D HUD, come back later
			return;
		}

		// ============ Draw Instance ==============

		struct Model* m = curr->model;
		struct ModelHeader* mh = &m->headers[0];

		// assume unanimated
		struct ModelFrame* mf = mh->ptrFrameData;
		struct ModelAnim* ma = 0;

		// 0xD4 -> 0x350
		// 0xA0 -> 0x284

		// animated
		if (mf == 0)
		{
			// animation
			ma = m->headers[0].ptrAnimations[curr->animIndex];

			// temporary solution, plays animations
			// at 30fps while rest of the game is 60fps
			int frameIndex = FPS_HALF(curr->animFrame);

			// cast
			char* maByte = (char*)ma;
			maByte = MODELANIM_GETFRAME(maByte);
			maByte = &maByte[ma->frameSize * frameIndex];

			// frame data
			mf = maByte;
		}

		char* vertData = (char*)&mf[0] + mf->vertexOffset;

		// 3FF is background, 0x0 is minimum depth
		void* ot = &pb->ptrOT[0];

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
		CompVertex* ptrVerts = (CompVertex*)vertData;
		u_int* pCmd = mh->ptrCommandList;

		//a "shifting window", here we update the vertices and read triangle once it's ready
		//you need same cache for both colors and texture layouts
		V4 tempCoords[4] = {0};
		int tempColor[4] = {0};
		struct TextureLayout* tempTex = 0;

		//i believe this must be scratchpad, but it uses 4 bytes, this array is only 3 bytes (like array buffer for simplicity).
		//the idea is that it loads vertices to scratchpad and with proper sorting,
		//you can draw may trigles of the list with minimum additional loads
		//then once you don't need vertex data, you can overwrite same indices with new data
		#ifdef REBUILD_PC
		V4 stack[256] = { 0 };
		#else
		V4* stack = 0x1f800000;
		#endif

		// pCmd[0] is number of commands
		pCmd++;

		// compression
		int x_alu = 0;
		int y_alu = 0;
		int z_alu = 0;
		bi = 0;

		//loop commands until we hit the end marker 
		for (
				/* */;
				*pCmd != END_OF_LIST;
				
				pCmd++, stripLength++
			)
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
				// exactly Crash 2 delta compression algorithm
				// https://github.com/cbhacks/CrashEdit/blob/647a97b004e7324ac4f648dcfcecc7d3f8412da3/CrashEdit/Controls/AnimationEntryViewer.cs#L451

				// here should also check for current anim etc,
				// for now just check if anim exists and take 1st frame
				if (ma != NULL && ma->ptrDeltaArray != NULL)
				{
					//store temporal vertex packed uint
					u_int temporal = ma->ptrDeltaArray[vertexIndex];

					//printf("temporal: %08x\n", temporal);

					//extract data from packed uint
					//deltaArray bits: 0bXXXXXXXZZZZZZZZYYYYYYYYAAABBBCCC

					u_char XBits = (temporal >> 6) & 7;
					u_char YBits = (temporal >> 3) & 7;
					u_char ZBits = (temporal) & 7;

					u_char bx = (temporal >> 0x19) << 1;
					u_char by = (temporal << 7) >> 0x18;
					u_char bz = (temporal << 0xf) >> 0x18;

					// If reading a full 8 bits (7+1)
					// reset accumulator, this is an 
					// uncompressed 1-byte number
					if (XBits == 7) x_alu = 0;
					if (YBits == 7) y_alu = 0;
					if (ZBits == 7) z_alu = 0;

					// Read NumBits+1, where the first
					// extra (+1) bit, determines negative

					// convert XZY frame data
					unsigned int newX = 0;
					newX = GetBitStream(vertData, XBits+1);
					if (newX >> XBits) newX |= -(1 << XBits);

					unsigned int newY = 0;
					newY = GetBitStream(vertData, YBits+1);
					if (newY >> YBits) newY |= -(1 << YBits);

					unsigned int newZ = 0;
					newZ = GetBitStream(vertData, ZBits+1);
					if (newZ >> ZBits) newZ |= -(1 << ZBits);

					//calculate decompressed coord value
					x_alu = (x_alu + (int)newX + bx);
					y_alu = (y_alu + (int)newY + by);
					z_alu = (z_alu + (int)newZ + bz);

					//store values to stack index, axis swap is important
					stack[stackIndex].X = x_alu;
					stack[stackIndex].Y = z_alu;
					stack[stackIndex].Z = y_alu;

					//printf("result: %i %i %i\n\n", x_alu, y_alu, z_alu);

					//_sleep(1000);
				}
				else
				{
					//copy from vertex buffer to stack index
					stack[stackIndex].X = ptrVerts[vertexIndex].X;
					stack[stackIndex].Y = ptrVerts[vertexIndex].Y;
					stack[stackIndex].Z = ptrVerts[vertexIndex].Z;
				}

				//and point to next vertex
				vertexIndex++;
			}


			//push current list back and insert value from stack
			//this code already have correct value on the stack, be aware of the order
			tempCoords[0] = tempCoords[1];
			tempCoords[1] = tempCoords[2];
			tempCoords[2] = tempCoords[3];
			tempCoords[3] = stack[stackIndex];

			//push new color
			tempColor[0] = tempColor[1];
			tempColor[1] = tempColor[2];
			tempColor[2] = tempColor[3];
			tempColor[3] = mh->ptrColors[colorIndex];

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

			if (stripLength < 2)
				continue;

			void* pCurr;
			void* pNext;
			
			// The X, Z, Y, is not a typo
			posWorld1[0] = ((((mf->pos[0] + tempCoords[1].X) * mh->scale[0]) >> 8) * curr->scale[0]) >> 12;
			posWorld1[1] = ((((mf->pos[1] + tempCoords[1].Z) * mh->scale[1]) >> 8) * curr->scale[1]) >> 12;
			posWorld1[2] = ((((mf->pos[2] + tempCoords[1].Y) * mh->scale[2]) >> 8) * curr->scale[2]) >> 12;
			posWorld1[3] = 0;
			gte_ldv0(&posWorld1[0]);

			// The X, Z, Y, is not a typo
			posWorld2[0] = ((((mf->pos[0] + tempCoords[2].X) * mh->scale[0]) >> 8) * curr->scale[0]) >> 12;
			posWorld2[1] = ((((mf->pos[1] + tempCoords[2].Z) * mh->scale[1]) >> 8) * curr->scale[1]) >> 12;
			posWorld2[2] = ((((mf->pos[2] + tempCoords[2].Y) * mh->scale[2]) >> 8) * curr->scale[2]) >> 12;
			posWorld2[3] = 0;
			gte_ldv1(&posWorld2[0]);

			// The X, Z, Y, is not a typo
			posWorld3[0] = ((((mf->pos[0] + tempCoords[3].X) * mh->scale[0]) >> 8) * curr->scale[0]) >> 12;
			posWorld3[1] = ((((mf->pos[1] + tempCoords[3].Z) * mh->scale[1]) >> 8) * curr->scale[1]) >> 12;
			posWorld3[2] = ((((mf->pos[2] + tempCoords[3].Y) * mh->scale[2]) >> 8) * curr->scale[2]) >> 12;
			posWorld3[3] = 0;
			gte_ldv2(&posWorld3[0]);
			
			gte_rtpt();
			
			// automatic pass, if no frontface or backface culling
			int boolPassCull = ((flags & DRAW_CMD_FLAG_CULLING) == 0);

			// if culling is required
			if (!boolPassCull)
			{
				// assume backface culling
				int opZ;
				gte_nclip();
				gte_stopz(&opZ);
				boolPassCull = (opZ >= 0);

				// if polygon is flipped
				if ((flags & DRAW_CMD_FLAG_FLIP_NORMAL) != 0)
					boolPassCull = !boolPassCull;

				// if instance is flipped
				if ((curr->flags & REVERSE_CULL_DIRECTION) != 0)
					boolPassCull = !boolPassCull;
			}
			
			if (!boolPassCull)
				continue;
			
			// sorting
			int otZ;
			gte_avsz3();
			gte_stotz(&otZ);

			// near-range for instances should be higher
			// for instances than level (not exact number)
			if (otZ <= 32) continue;

			// make sure instances draw on top of the road,
			// reduce depth in the sorting table (not exact number)
			otZ -= 32;

			if (otZ >= 4080) continue;

			tempTex = (texIndex == 0) 
				? 0 : 							// index=0 -> tempTex = nullptr
				mh->ptrTexLayout[texIndex - 1];	// can still be nullptr
			
			if (tempTex == 0)
			{
				POLY_G3* p = primMem->curr;
				pNext = p + 1;
				pCurr = p;

				*(int*)&p->r0 = tempColor[1];
				*(int*)&p->r1 = tempColor[2];
				*(int*)&p->r2 = tempColor[3];

				setPolyG3(p);
				
				gte_stsxy3(
					&p->x0,
					&p->x1,
					&p->x2);
			}
			else
			{
				POLY_GT3* p = primMem->curr;
				pNext = p + 1;
				pCurr = p;

				*(int*)&p->r0 = tempColor[1];
				*(int*)&p->r1 = tempColor[2];
				*(int*)&p->r2 = tempColor[3];
				
				*(int*)&p->u0 = *(int*)&tempTex->u0;
				*(int*)&p->u1 = *(int*)&tempTex->u1;
				*(short*)&p->u2 = *(short*)&tempTex->u2;

				setPolyGT3(p);
				
				gte_stsxy3(
					&p->x0,
					&p->x1,
					&p->x2);
			}
			
			AddPrim((u_long*)ot + (otZ >> 2), pCurr);
			primMem->curr = pNext;
		}
	}
}

void TEST_DrawInstances(struct GameTracker* gGT)
{
	if (gGT->level1 != 0)
	{
		if (gGT->level1->ptrInstDefs != 0)
		{
			struct InstDef* instDef = gGT->level1->ptrInstDefs;

			for (int i = 0; i < gGT->level1->numInstances; i++)
			{
				struct Instance* curr = instDef[i].ptrInstance;

				if (curr != 0)
				{
					if ((curr->flags & 0x80) != 0) continue;
					if ((curr->flags & 1) == 0) continue;

					DrawOneInst(curr);
				}
			}
		}
	}

	for (
		struct Instance* curr = (struct Instance*)gGT->JitPools.instance.taken.first;
		curr != NULL;
		curr = curr->next
		)
	{
		if ((curr->flags & 0x80) != 0) continue;
		if ((curr->flags & 1) == 0) continue;
		
		// skip "scan" in 232
		if (curr->model->id == 0x78) continue;

		DrawOneInst(curr);
	}
}