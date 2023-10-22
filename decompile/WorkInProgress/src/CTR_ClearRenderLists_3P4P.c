#include <common.h>

void DECOMP_CTR_ClearRenderLists_3P4P(struct GameTracker* gGT, char numPlyrCurrGame)
{
  void **quads;

  if (!numPlyrCurrGame) return;
  
	// pointers to rendered quadblocks
    quads = &data.ptrRenderedQuadblockDestination_again[0];
	
	// for each player, clear render lists,
	// set default destination for rendered quadblocks
    for (char i = 0; i < numPlyrCurrGame; i++)
	  {
      gGT->LevRenderLists[i].list[0].bspListStart = 0;
      gGT->LevRenderLists[i].list[0].ptrQuadBlocksRendered = quads[i];
      gGT->LevRenderLists[i].list[1].bspListStart = 0;
      gGT->LevRenderLists[i].list[1].ptrQuadBlocksRendered = quads[i];
      gGT->LevRenderLists[i].list[2].bspListStart = 0;
      gGT->LevRenderLists[i].list[2].ptrQuadBlocksRendered = quads[i];
      gGT->LevRenderLists[i].list[3].bspListStart = 0;
	  
	  // different from prev function, cause 
	  // the RenderLists are in a different order 
	  // in 1P2P and 3P4P
      gGT->LevRenderLists[i].list[4].ptrQuadBlocksRendered = quads[i];
      gGT->LevRenderLists[i].list[3].ptrQuadBlocksRendered = quads[i];
    } 
}