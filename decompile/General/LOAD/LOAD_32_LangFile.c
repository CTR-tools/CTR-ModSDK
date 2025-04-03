#include <common.h>

struct LngFile
{
	int numStrings;
	int offsetToPtrArr;
	char strings[1];
};

// param_1 - Pointer to "cd position of bigfile"
// param_2 - language index - 0 ja, 1 en, 2 en2, 3 fr, 4 de, 5 it, 6 es, 7 ne
void DECOMP_LOAD_LangFile(int bigfilePtr, int lang)
{
	struct LngFile *lngFile;
	int size;

	int i;
	int numStrings;
	char **strArray;

#if BUILD == EurRetail
	// This is to turn the screen black for a bit (optional)
	DECOMP_CTR_ErrorScreen(0, 0, 0);
	VSync(0);
#endif

	if (sdata->lngFile == 0)
	{
		sdata->lngFile =
			DECOMP_MEMPACK_AllocMem(sdata->langBufferSize /* "lang buffer" */);
	}
	
	lngFile = sdata->lngFile;

	DECOMP_LOAD_ReadFile(0, 
		LT_SETADDR | LT_SYNC,
		BI_LANGUAGEFILE + lang, (void*)lngFile);

	numStrings = lngFile->numStrings;
	strArray = (char**)((unsigned int)lngFile + lngFile->offsetToPtrArr);

	sdata->numLngStrings = numStrings;
	sdata->lngStrings = strArray;

	for (i = 0; i < numStrings; i++)
	{
		strArray[i] =
			(char*)((unsigned int)strArray[i] +
			(unsigned int)lngFile);
	}
#if BUILD == EurRetail
	// set voicelines to new lang
	DECOMP_CDSYS_SetXAToLang(lang);
#endif
}