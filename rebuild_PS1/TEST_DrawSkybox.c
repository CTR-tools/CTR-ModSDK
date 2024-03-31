#include <common.h>

void TEST_DrawSkybox(
	struct Skybox* ptrSkybox,
	struct PushBuffer* pushBuffer,
	struct PrimMem* primMem)
{
	if (ptrSkybox == 0)
		return;

	POLY_G3* p;
	short posScreen1[4];
	short posScreen2[4];
	short posScreen3[4];
	short posScreen4[4];

	// remove transformation, standard for sky in most games,
	// 3x3 viewProj was set in previosu call to TEST_226
	gte_ldtr(0, 0, 0);

	for (int i = 0; i < 4; i++)
	{
		int index = ((((pushBuffer->rot[1] + 0x500) >> 9) + i - 2) & 0x7);
		
		struct SkyboxFace* ptrFace = ptrSkybox->ptrFaces[index];

		for (int j = 0; j < ptrSkybox->numFaces[index]; j++)
		{
			p = primMem->curr;
			void* pNext = p + 1;
			void* pCurr = p;
			if (pNext > ((unsigned int)primMem->end - 0x200)) return;

			struct ShortVertex* A = (struct ShortVertex*)((u_int)ptrSkybox->ptrVertex + (u_int)ptrFace[j].A);
			struct ShortVertex* B = (struct ShortVertex*)((u_int)ptrSkybox->ptrVertex + (u_int)ptrFace[j].B);
			struct ShortVertex* C = (struct ShortVertex*)((u_int)ptrSkybox->ptrVertex + (u_int)ptrFace[j].C);

			*(int*)&p->r0 = *(int*)&A->Color;
			*(int*)&p->r1 = *(int*)&B->Color;
			*(int*)&p->r2 = *(int*)&C->Color;

			setPolyG3(p);

			gte_ldv0(&A->Position);
			gte_rtps();
			gte_stsxy(&posScreen1[0]);

			gte_ldv0(&B->Position);
			gte_rtps();
			gte_stsxy(&posScreen2[0]);

			gte_ldv0(&C->Position);
			gte_rtps();
			gte_stsxy(&posScreen3[0]);

			// to be in viewport, coordinates must be
			// X: [0, 0x40]
			// Y: [0, 0xA0]
			setXY3(p,
				(posScreen1[0]), (posScreen1[1]),	// XY0
				(posScreen2[0]), (posScreen2[1]),	// XY1
				(posScreen3[0]), (posScreen3[1]));

			AddPrim(&pushBuffer->ptrOT[0x3ff], pCurr);
			primMem->curr = pNext;
		}
	}
}