#include <common.h>

struct LngFile
{
	int numStrings;
	int offsetToPtrArr;
	char strings[1];
};

void LOAD_LangFile(int bigfilePtr, int lang)
{
	struct LngFile *lngFile;
	int size;

	int i;
	int numStrings;
	char **strArray;

#if BUILD != JpnRetail
	if (sdata->lngFile == 0)
	{
		sdata->lngFile = MEMPACK_AllocMem(sdata->langBufferSize + 0x7ffU & 0xfffff800 /*"lang buffer"*/);
	}
#endif

	lngFile = LOAD_ReadFile(bigfilePtr, 1, 0xEA + lang, sdata->lngFile, &size, 0);

	// This is not ReadFileAsync, this is ReadFile,
	// so the program halts until completion of read

	numStrings = lngFile->numStrings;
	strArray = (unsigned int)lngFile + lngFile->offsetToPtrArr;

	sdata->numLngStrings = numStrings;
	sdata->lngStrings = strArray;

	for (i = 0; i < numStrings; i++)
	{
		strArray[i] =
			(unsigned int)strArray[i] +
			(unsigned int)lngFile;
	}

	CTR_ErrorScreen(0, 0, 0);
	VSync(0);
}