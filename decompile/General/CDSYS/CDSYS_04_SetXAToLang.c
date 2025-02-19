#include <common.h>

void DECOMP_CDSYS_SetXAToLang(int lang)
{

// PS1
#ifndef USE_PCDRV

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
	sdata->ptrArray_XaSize = (struct XaSize*)&sdata->ptrArray_XaCdPos[xnf->numXAs_total];
	
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

#endif

}

// Copied from here:
// https://github.com/Lameguy64/PSn00bSDK/blob/master/libpsn00b/psxapi/_syscalls.s
#ifdef USE_PCDRV
asm(
"## PCDRV (host file access) API                                   \n"
".section .text.PCinit, \"ax\", @progbits                          \n"
".global PCinit                                                    \n"
".type PCinit, @function                                           \n"
"                                                                  \n"
"PCinit:                                                           \n"
"	break 0, 0x101 # () -> error                                   \n"
"                                                                  \n"
"	jr    $ra                                                      \n"
"	nop                                                            \n"
"                                                                  \n"
".section .text.PCcreat, \"ax\", @progbits                         \n"
".global PCcreat                                                   \n"
".type PCcreat, @function                                          \n"
"                                                                  \n"
"PCcreat:                                                          \n"
"	li    $a2, 0                                                   \n"
"	move  $a1, $a0                                                 \n"
"	break 0, 0x102 # (path, path, 0) -> error, fd                  \n"
"                                                                  \n"
"	bgez  $v0, .Lcreate_ok # if (error < 0) fd = error             \n"
"	nop                                                            \n"
"	move  $v1, $v0                                                 \n"
".Lcreate_ok:                                                      \n"
"	jr    $ra # return fd                                          \n"
"	move  $v0, $v1                                                 \n"
"                                                                  \n"
".section .text.PCopen, \"ax\", @progbits                          \n"
".global PCopen                                                    \n"
".type PCopen, @function                                           \n"
"                                                                  \n"
"PCopen:                                                           \n"
"	move  $a2, $a1                                                 \n"
"	move  $a1, $a0                                                 \n"
"	break 0, 0x103 # (path, path, mode) -> error, fd               \n"
"                                                                  \n"
"	bgez  $v0, .Lopen_ok # if (error < 0) fd = error               \n"
"	nop                                                            \n"
"	move  $v1, $v0                                                 \n"
".Lopen_ok:                                                        \n"
"	jr    $ra # return fd                                          \n"
"	move  $v0, $v1                                                 \n"
"                                                                  \n"
".section .text.PCclose, \"ax\", @progbits                         \n"
".global PCclose                                                   \n"
".type PCclose, @function                                          \n"
"                                                                  \n"
"PCclose:                                                          \n"
"	move  $a1, $a0                                                 \n"
"	break 0, 0x104 # (fd, fd) -> error                             \n"
"                                                                  \n"
"	jr    $ra                                                      \n"
"	nop                                                            \n"
"                                                                  \n"
".section .text.PCread, \"ax\", @progbits                          \n"
".global PCread                                                    \n"
".type PCread, @function                                           \n"
"                                                                  \n"
"PCread:                                                           \n"
"	move  $a3, $a1                                                 \n"
"	move  $a1, $a0                                                 \n"
"	break 0, 0x105 # (fd, fd, length, data) -> error, length       \n"
"                                                                  \n"
"	bgez  $v0, .Lread_ok # if (error < 0) length = error           \n"
"	nop                                                            \n"
"	move  $v1, $v0                                                 \n"
".Lread_ok:                                                        \n"
"	jr    $ra # return length                                      \n"
"	move  $v0, $v1                                                 \n"
"                                                                  \n"
".section .text.PCwrite, \"ax\", @progbits                         \n"
".global PCwrite                                                   \n"
".type PCwrite, @function                                          \n"
"                                                                  \n"
"PCwrite:                                                          \n"
"	move  $a3, $a1                                                 \n"
"	move  $a1, $a0                                                 \n"
"	break 0, 0x106 # (fd, fd, length, data) -> error, length       \n"
"                                                                  \n"
"	bgez  $v0, .Lwrite_ok # if (error < 0) length = error          \n"
"	nop                                                            \n"
"	move  $v1, $v0                                                 \n"
".Lwrite_ok:                                                       \n"
"	jr    $ra # return length                                      \n"
"	move  $v0, $v1                                                 \n"
"                                                                  \n"
".section .text.PClseek, \"ax\", @progbits                         \n"
".global PClseek                                                   \n"
".type PClseek, @function                                          \n"
"                                                                  \n"
"PClseek:                                                          \n"
"	move  $a3, $a2                                                 \n"
"	move  $a2, $a1                                                 \n"
"	move  $a1, $a0                                                 \n"
"	break 0, 0x107 # (fd, fd, offset, mode) -> error, offset       \n"
"                                                                  \n"
"	bgez  $v0, .Lseek_ok # if (error < 0) offset = error           \n"
"	nop                                                            \n"
"	move  $v1, $v0                                                 \n"
".Lseek_ok:                                                        \n"
"	jr    $ra # return offset                                      \n"
"	move  $v0, $v1                                                 \n"
);
#endif