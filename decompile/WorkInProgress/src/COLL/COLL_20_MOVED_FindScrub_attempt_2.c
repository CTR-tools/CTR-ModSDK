#include <common.h>

void DECOMP_COLL_MOVED_FindScrub(struct QuadBlock* quadblock, int triangleID, struct ScratchpadStructExtended* spse) {
	//unsigned short searchFlags = spse->scratchpadStruct.Union.QuadBlockColl.searchFlags; //uVar1

	if (quadblock == NULL)
	{
		spse->scratchpadStruct.Union.QuadBlockColl.searchFlags &= 0xffdf;

		*(short*)(((int)spse) + 0xe) = 0;

		spse->numTriangles = 0;

		return;
	}

	for (char i = spse->numTriangles - 1; i >= 0; i--)
	{
		struct BspSearchTriangle* searchTriangle = &spse->bspSearchTriangle[i];

		if (searchTriangle->quadblock == quadblock && searchTriangle->triangleID == triangleID)
		{
			if (searchTriangle->numCollision < 0x401)
			{
				searchTriangle->numCollision += 0x100;
			}

			spse->scratchpadStruct.Union.QuadBlockColl.searchFlags |= 0x20;

			*(short*)(((int)spse) + 0xe) = (short)searchTriangle->numCollision;

			return;
		}
	}

	//it looks like the original game doesn't bounds check this. Is that a problem?

	struct BspSearchTriangle* newSearchTriangle = &spse->bspSearchTriangle[spse->numTriangles];

	newSearchTriangle->quadblock = quadblock;
	newSearchTriangle->triangleID = triangleID;
	newSearchTriangle->numCollision = 0;

	spse->scratchpadStruct.Union.QuadBlockColl.searchFlags &= 0xffdf;

	*(short*)(((int)spse) + 0xe) = 0;

	spse->numTriangles++;

	return;
}