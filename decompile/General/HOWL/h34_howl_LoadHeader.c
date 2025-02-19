#include <common.h>

void DECOMP_howl_LoadHeader(char* filename)
{
	struct HowlHeader* alloc;
	int howlHeaderSize;
	int numSector;
	int ret;
	
	DECOMP_MEMPACK_PushState();
	
	// allocate room for one sector
	alloc = DECOMP_MEMPACK_AllocMem(0x800/*, filename*/);
	
// PC
#ifdef USE_PCDRV
	
	#ifdef REBUILD_PC
	int v1;
	#else
	// because this API is STRANGE
	register int v1 asm("v1");
	#endif
	
	v1 = PCopen("SOUNDS/KART.HWL", PCDRV_MODE_READ);
	sdata->fd_kartHwl = v1;
	
	v1 = PCread(sdata->fd_kartHwl, alloc, 0x800);
	
	// allocate room for howlHeader + pointerTable
	howlHeaderSize = sizeof(struct HowlHeader) + alloc->headerSize;
				
	// align up for sector size
	numSector = (howlHeaderSize + 0x800 - 1) >> 0xb;
	DECOMP_MEMPACK_ReallocMem(numSector << 0xb);
	
	char* byteOffset = (char*)alloc;
	PCread(sdata->fd_kartHwl, &byteOffset[0x800], howlHeaderSize-0x800);
	
	return;

// PS1
#else
	
	if (DECOMP_LOAD_FindFile(filename, (CdlFILE*)&sdata->KartHWL_CdLoc) == 0) 
		alloc = 0;
	
	if (alloc != 0)
	{
		// read sector #1 of HOWL, just for header
		ret = DECOMP_LOAD_HowlHeaderSectors(
					(CdlFILE*)&sdata->KartHWL_CdLoc, 
					alloc, 0, 1);
	
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
			
			// if header fit in one sector, done!
			if (numSector == 1) return;

			// if header needs a more sectors loaded,
			// like CTR-U which needs 3 sectors...

			// read remaining sectors
			ret = DECOMP_LOAD_HowlHeaderSectors(
						(CdlFILE*)&sdata->KartHWL_CdLoc, 
						(void*)((int)alloc + 0x800), 1, numSector - 1);
						
			if (ret != 0)
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
	
#endif
}