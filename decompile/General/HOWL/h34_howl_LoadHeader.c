#include <common.h>

void DECOMP_howl_LoadHeader(char* filename)
{
	struct HowlHeader* alloc;
	int howlHeaderSize;
	int numSector;
	int ret;
	
	if (DECOMP_LOAD_FindFile(filename, &sdata->KartHWL_CdLoc) == 0) return;
	
	DECOMP_MEMPACK_PushState();
	
	// allocate room for one sector
	alloc = DECOMP_MEMPACK_AllocMem(0x800/*, filename*/);
	
	if (alloc != 0)
	{
		// read sector #1 of HOWL, just for header
		ret = DECOMP_LOAD_HowlHeaderSectors(
					&sdata->KartHWL_CdLoc, alloc, 0, 1);
	
		if(
			// confirm first sector loaded properly
			(ret != 0)
			
			// assume loaded correct file
			#if 0
			&& (alloc->magic == *(int*)&sdata->s_HOWL[0])
			&& (alloc->version == 0x80) // different in other CTR builds
			#endif
		  )
		{
			// allocate room for howlHeader + pointerTable
			howlHeaderSize = sizeof(struct HowlHeader) + alloc->headerSize;
						
			// align up for sector size
			numSector = (howlHeaderSize + 0x800 - 1) >> 0xb;
			DECOMP_MEMPACK_ReallocMem(numSector << 0xb);
			
			if (
					// if header fit in one sector, just continue
					(numSector < 2) ||
					
					// if header needs a more sectors loaded,
					// like CTR-U which needs 3 sectors
					(
						ret = DECOMP_LOAD_HowlHeaderSectors(
							&sdata->KartHWL_CdLoc, (int)alloc+0x800, 1, numSector-1),
							
						ret != 0
					)
				)
			{
				// initilaize header and pointer table
				DECOMP_howl_ParseHeader(alloc);
					
				// reallocate room just howlHeader + pointerTable,
				// deallocate sector-alignment padding
				DECOMP_MEMPACK_ReallocMem(howlHeaderSize);
					
				//do NOT PopState
				return;
			}
		}
	}
	
	DECOMP_MEMPACK_PopState();
}