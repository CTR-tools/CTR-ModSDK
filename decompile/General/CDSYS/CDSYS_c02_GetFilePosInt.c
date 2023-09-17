#include <common.h>

u_int CDSYS_GetFilePosInt(char* fileString, int* filePos)
{
	CdlFILE cdlFile;
	
	if(CdSearchFile(&cdlFile, fileString) != 0)
	{
		*filePos = CdPosToInt(&cdlFile.pos);
		return 1;
	}
	
	return 0;
}