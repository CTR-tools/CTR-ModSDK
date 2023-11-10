#include <common.h>

void* DECOMP_LOAD_ReadFile_NoCallback(char* filename, void* ptrDestination, int* size)
{
	CdlFILE cdlFile;
	
	DECOMP_LOAD_StringToUpper(filename);
	DECOMP_CDSYS_SetMode_StreamData();
	
	if(CdSearchFile(&cdlFile, filename) == 0) 
		return 0;
	
	*size = cdlFile.size;
	
	if(ptrDestination == 0)
	{
		ptrDestination = DECOMP_MEMPACK_AllocMem(cdlFile.size + 0x7ff & 0xfffff800/*, fileName*/);
		
		if(ptrDestination == 0)
			return 0;
	}
	
	char buf[8];
	CdControl(CdlSetloc, &cdlFile, buf);
	
	// only allocate "needed" bytes
	DECOMP_MEMPACK_ReallocMem(cdlFile.size);
	
	if(CdRead((cdlFile.size + 0x7ff)>>0xb, ptrDestination, 0x80) == 0) 
		return 0;
	
	if(CdReadSync(0, 0)) 
		return 0;
	
	return ptrDestination;
}