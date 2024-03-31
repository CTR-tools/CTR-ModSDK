#include "common.h"


// draws level skybox
// param_1 - lev ptr_skybox
// param_2 - pushBuffer
// param_3 - primMem
void DrawSky_Full(Skybox* pSkybox, void* pPushBuffer, void* primMem)
{
	//just jump out 
	if (pSkybox == NULL) return;

	// register v0
	undefined4 uVar1;

	// register backups
	undefined4 unaff_s0;
	undefined4 unaff_s1;
	undefined4 unaff_s2;
	undefined4 unaff_retaddr;

	// primMem curr
	uVar1 = *(undefined4 *)(primMem + 0xc);

	// backup
	DAT_1f800000 = unaff_ra;
	DAT_1f800004 = unaff_s0;
	DAT_1f800008 = unaff_s1;
	DAT_1f80000c = unaff_s2;

	// load pushBuffer ViewProj to gte
	gte_ldR11R12(*(undefined4 *)(pPushBuffer + 0x28));
	gte_ldR13R21(*(undefined4 *)(pPushBuffer + 0x2c));
	gte_ldR22R23(*(undefined4 *)(pPushBuffer + 0x30));
	gte_ldR31R32(*(undefined4 *)(pPushBuffer + 0x34));
	gte_ldR33(*(undefined4 *)(pPushBuffer + 0x38));

	// remove transformation,
	// standard for sky in most games
	gte_ldtr(0,0,0);

	// These get modified in between skybox segments,
	// the C output is wrong
	DAT_1f800010 = pPushBuffer->rot[1] + 0x500U >> 7 & 0x1c;
	DAT_1f800014 = DAT_1f800010 >> 1;

	//it probably modifies segment index on the register in between, then uses it in the segment function?
	//does it like uses horizontal angle, something like 4096 / 512 then draw segments around it?

	// draw four skybox segments
	uVar1 = DrawSky_Piece(pSkybox, pPushBuffer, primMem, &pPushBuffer->ptrOT[0x3ff]);
	uVar1 = DrawSky_Piece(pSkybox, pPushBuffer, primMem, &pPushBuffer->ptrOT[0x3ff]);
	uVar1 = DrawSky_Piece(pSkybox, pPushBuffer, primMem, &pPushBuffer->ptrOT[0x3ff]);
	uVar1 = DrawSky_Piece(pSkybox, pPushBuffer, primMem, &pPushBuffer->ptrOT[0x3ff]);

	// restore
	unaff_ra = DAT_1f800000;
	unaff_s0 = DAT_1f800004;
	unaff_s1 = DAT_1f800008;
	unaff_s2 = DAT_1f80000c;

	// new primMem curr
	*(undefined4 *)(primMem + 0xc) = uVar1;
}


u_int numSegment = 8;

// draws skybox segment
// every skybox is splitted in 8 segments, only 4 are drawn at a time
// pSkybox - lev ptr_skybox
// pPushBuffer - pushBuffer, do we really use tileview in this func?
// primMem - primMem
// ptrOT - pushBuffer->ptrOT
void DrawSky_Piece(Skybox* pSkybox, void* pPushBuffer, void* primMem, int ptrOT)
{
	//numsegment is hardcoded in_t5 + 8, guess it's the segment index (1 to 8) coming from some register?
	//or maybe i got it all wrong
	//if (*(ushort *)(in_t5 + 8) != 0) 
	if (numSegment == 0) return;

	//store segment pointer and amount of faces to read
	//basically read numFaces of SkyboxFace structs starting from the pFace
	short* numFaces = pSkybox->sizes[numSegment - 1];
	SkyboxFace* pFace = pSkybox->pFaces[numSegment - 1];


	//load initial vertex
	//can have less casts with pFace->A / 12, but it guess it's slower
	ShortVertex* A = (ShortVertex *)((u_int)pSkybox->pVerts + (u_int)pFace->A);
	ShortVertex* B = (ShortVertex *)((u_int)pSkybox->pVerts + (u_int)pFace->B);
	ShortVertex* C = (ShortVertex *)((u_int)pSkybox->pVerts + (u_int)pFace->C);

	//since we loaded one already...
	numFaces--;

	//?
	pOTcurr = (uint *)(((int)*(uint *)(pFace + 2) >> 0x10) + ptrOT);

	//draw all tris of the current segment
	//can refactor to for loop over pointer, iterator is not used anywhere
	//the pre-loop assignments probably should be properly included in the refactored loop instead
	while( true )
	{
		pOTprev = pOTcurr;

		//load poly coords to GTE
		gte_ldv0(A->Position);
		gte_ldv1(B->Position);
		gte_ldv2(C->Position);

		//load poly colors to GTE, any reason why?
		gte_ldRGB0(A->Color);
		gte_ldRGB1(B->Color);
		gte_ldRGB2(C->Color);

		//translate vertices to screen coords
		gte_rtpt_b();		//RotTransPers3?
		
		//store gte screen coord in ram to check on cpu whether we need it at all.
		//wonder if there is some hardware check for such things?
		u_int sxy0 = gte_stSXY0();
		u_int sxy1 = gte_stSXY1();
		u_int sxy2 = gte_stSXY2();
		u_int flag = gte_stFLAG();

		//if not off screen, add prim? whats in_t7 here? screen size?
		if ((((uint)(flag << 0xd) >> 0x1d == 0) &&
					(sxy2 = ~(sxy0 - in_t7 | sxy1 - in_t7 | sxy2 - in_t7) | sxy0 & sxy1 & sxy2,
					-1 < (int)sxy2)) && (-1 < (int)(sxy2 << 0x10))) 
		{
			//guess it's passed to addprim macro?

			//store screen coords
			gte_stSXY0();
			gte_stSXY1();
			gte_stSXY2();

			//store color, ahem, do we even need to bother gte for color here?
			//like cant we just use the original color in ram
			gte_stRGB0();
			gte_stRGB1();
			gte_stRGB2();

			//the last segment here is the only difference, guess it was goto originally
			//ghidra breaks and duplicates the entire branch after it, lets just break at the end instead

			//select pointer logic based on whether it's last face or not
			//im not too familiar with macros here
			if (numFaces - 1 != 0)
			{
				// write PrimMem and OTMem
				uVar3 = (uint)in_v0 & 0xffffff;
				*in_v0 = *puVar10 | 0x6000000;

				in_v0 = in_v0 + 7;
				*puVar10 = uVar3;
			}
			else
			{
				// write PrimMem and OTMem
				*in_v0 = *in_t9 | 0x6000000;
				*in_t9 = (uint)in_v0 & 0xffffff;

				break;
			}
		}

		//originally this came before gte stuff, but doesnt make much sense there
		//load vertices for the next iteration
		A = (ShortVertex *)((u_int)pSkybox->pVerts + (u_int)pFace->A);
		B = (ShortVertex *)((u_int)pSkybox->pVerts + (u_int)pFace->B);
		C = (ShortVertex *)((u_int)pSkybox->pVerts + (u_int)pFace->C);

		pOTcurr = (uint *)(((int)*(uint *)(pFace + 2) >> 0x10) + ptrOT);
		//let the outside know the current ot ptr?
		in_t9 = pOTprev;
	
		//decrement remaining faces
		numFaces--;
		//next tri
		pFace++;
	}
}