#include <common.h>

int DECOMP_LOAD_FindFile(char* filename, CdlFILE* cdlFile)
{
	if(filename == 0) return 0;
	if(cdlFile == 0) return 0;
	
	DECOMP_CDSYS_SetMode_StreamData();
	DECOMP_LOAD_StringToUpper(filename);
	
	#ifdef USE_PCDRV
	// for KART.HWL, cause CdSearchFile wont give size
	cdlFile->size = 0xbae694;
	#endif
	
	return (CdSearchFile(cdlFile, filename) != 0);
}