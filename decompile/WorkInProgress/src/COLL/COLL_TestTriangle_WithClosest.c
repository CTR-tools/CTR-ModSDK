#include <common.h>

void DECOMP_COLL_TestTriangle_WithClosest(struct QuadBlock* ptrQuad, int triangleID, struct ScratchpadStructExtended* spex)
{

  struct BspSearchTriangle* bspTriangle;
  u_short numColl;

  // first call before this function gets 15 more call
  // if null,
	// driver gets stuck, but doesn't bounce
  if (ptrQuad == NULL)
  {
    // Reset flags and values when no quadblock is provided
    spex->scratchpadStruct.Union.QuadBlockColl.searchFlags &= 0xffdf;
    *(u_short *)(spex + 0xe) = 0; // part of modelID?
    spex->numTriangles = 0;
    return;
  }

  // if this function is being called from the 
  // loop of 15 calls, from COLL_StartSearch_Player

  // since start of COLL_StartSearch_Player, check all existing
  // records of quadblock and triangle, so far

  for (char i = spex->numTriangles - 1; i >= 0; i--)
  {
    
    bspTriangle = spex->bspSearchTriangle[i];

    // if quadblock and triangleID match,
	  // meaning we've already found collision with this triangle on this frame
    if (bspTriangle->quadblock == ptrQuad && bspTriangle->triangleID == triangleID)
    {
      numColl = (u_short)bspTriangle->numCollision;
      // if collision is found less than 4 frames
      if (numColl < 0x401)
      {
        // increment
        numColl += 0x100;
        bspTriangle->numCollision += 0x100;
      }
      spex->Union.QuadBlockColl.searchFlags |= 0x20;

	    // then trigger scrub effect with 1f800116
      *(u_short *)(spex + 0xe) = numColl; // 1f800116
      return;
    }
  }

  // If collision was not found yet this frame, record it
  bspTriangle = spex->bspSearchTriangle[spex->numTriangles];
  bspTriangle->quadblock = ptrQuad;
  bspTriangle->triangleID = triangleID;
  bspTriangle->numCollision = 0; // init at zero

  spex->Union.QuadBlockColl.searchFlags &= 0xffdf; // Reset flags
  *(u_short *)(spex + 0xe) = 0; // 1f800116 (no scrub)
  spex->numTriangles++; // Move to the next slot for a new record
}