#include <common.h>

void DECOMP_CDSYS_SetXAToLang(int lang)
{
	char* xaLang;
	int fileSize;
	struct XNF* xnf;
	
	if(sdata->boolUseDisc == 0) return;	
	if(lang >= 8) return;
	
	sdata->bool_XnfLoaded = 0;
	DECOMP_CDSYS_SetMode_StreamData();
	
	xaLang = data.xaLanguagePtrs[lang];
	strncpy(&data.s_XA_ENG_XNF[4],		xaLang, 3);
	strncpy(&data.s_XA_ENG_EXTRA[4],	xaLang, 3);
	strncpy(&data.s_XA_ENG_GAME[4],		xaLang, 3);
	
	xnf = DECOMP_LOAD_ReadFile_NoCallback(data.s_XA_ENG_XNF, 0, &fileSize);
	
	// read error
	if(xnf == 0) return;
	
	// header error
	if(xnf->magic != *(int*)&sdata->s_XINF[0]) return;
	
	// Aug5=100, Sep3=101, Retail=102 
	if(xnf->version != 102) return;
	
	sdata->xa_numTypes = xnf->numTypes;
	if(sdata->xa_numTypes != CDSYS_XA_NUM_TYPES) return;
	
	sdata->ptrArray_NumXAs = &xnf->numXA[0];
	sdata->ptrArray_firstXaIndex = &xnf->firstXaIndex[0];
	sdata->ptrArray_numSongs = &xnf->numSongs[0];
	sdata->ptrArray_firstSongIndex = &xnf->firstSongIndex[0];
	sdata->ptrArray_XaCdPos = XNF_GETXACDPOS(xnf);
	sdata->ptrArray_XaSize = &sdata->ptrArray_XaCdPos[xnf->numXAs_total];
	
	for(int categoryID = 0; categoryID < sdata->xa_numTypes; categoryID++)
	{
		struct AudioMeta* am = &data.audioMeta[categoryID];
		
		for(int xaID = 0; xaID < sdata->ptrArray_NumXAs[categoryID]; xaID++)
		{
			am->name[am->stringIndex_char1] = '0' + (xaID/10);
			am->name[am->stringIndex_char2] = '0' + (xaID%10);
			
			int firstXaIndex = sdata->ptrArray_firstXaIndex[categoryID];
			int* returnPtr_xaCdPos = &sdata->ptrArray_XaCdPos[firstXaIndex + xaID];
			
			// quit on error to find XA file
			if(DECOMP_CDSYS_GetFilePosInt(am->name, returnPtr_xaCdPos) == 0)
				return;
		}
	}
	
	sdata->bool_XnfLoaded = 1;
}