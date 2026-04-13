#include <common.h>

// Used for XNF and only the XNF
void* DECOMP_LOAD_XnfFile(char* filename, void* ptrDestination, int* size)
{
	CdlFILE cdlFile;
	
	DECOMP_LOAD_StringToUpper(filename);
	DECOMP_CDSYS_SetMode_StreamData();
	
	if(CdSearchFile(&cdlFile, filename) == 0) 
		return 0;
	
	*size = cdlFile.size;
	
	if(ptrDestination == 0)
	{
		// allocate room for all sectors,
		// remove alignment before next Read
		int sectorSize = (cdlFile.size + 0x7ffU) & 0xfffff800;
		ptrDestination = DECOMP_MEMPACK_AllocMem(sectorSize /*, fileName*/);
		DECOMP_MEMPACK_ReallocMem(cdlFile.size);
	}
	
	char buf[8];
	CdControl(CdlSetloc, &cdlFile, buf);
	
	if(CdRead((cdlFile.size + 0x7ff)>>0xb, ptrDestination, 0x80) == 0) 
		return 0;
	
	if(CdReadSync(0, 0)) 
		return 0;
	
	return ptrDestination;
}