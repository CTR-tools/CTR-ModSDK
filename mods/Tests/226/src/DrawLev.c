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

void DrawLevel(
	struct RenderList* RL,
	struct TileView* view,
	struct mesh_info* mi,
	struct PrimMem* primMem,
	int* visMem10,
	int unk)
{
	printf("\nDump Level:\n");
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
			
			// number of quads, per bsp block, per list
			printf("List %d, bsp %d, numBlock %d\n",
						i, count, bsp->data.leaf.numQuads);
		}
		
		printf("List %d, bsp %d\n\n", i, count);
	}
}