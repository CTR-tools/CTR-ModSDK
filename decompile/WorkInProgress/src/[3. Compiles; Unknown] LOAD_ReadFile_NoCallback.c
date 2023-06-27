#include <common.h>

void CDSYS_SetMode_StreamData();

// Read file on disc, store in buffer
u_long * DECOMP_LOAD_ReadFile_NoCallback(char *fileString, u_long *bufAddress, u_long *fileSize)
{
	CdlFILE *CdlFILESearch;
	int iVar2;
	u_long *buf;
	CdlFILE Cdl;
	u_char auStack32 [8];

	// capitalize string
	LOAD_StringToUpper(fileString);

	CDSYS_SetMode_StreamData();

	// CdlFILESearch and Cdl are the same
	// CdlFILESearch is the CdlFILE that corresponds
	CdlFILESearch = CdSearchFile(&Cdl, fileString);

	buf = bufAddress;

	// if the file was found
	if (CdlFILESearch != (CdlFILE *)0x0)
	{
		printf("file found\n");

		// return file size to parameter
		*fileSize = Cdl.size;

		if
		(
			(bufAddress == (u_long *)0x0) &&
			(
				buf = (u_long *)MEMPACK_AllocMem(Cdl.size + 0x7ff & 0xfffff800), // fileString
				// if allocation failed
				buf == (u_long *)0x0
			)
		)
		{
			#if BUILD == SepReview
				printf("\nERROR: LOAD_ReadFile unable to allocate %d bytes for file \'%s\'!\n", *fileSize, fileString);
				buf = (u_long *)0x0;
			#else
				// function failed
				return (u_long *)0;
			#endif
		}
		#if BUILD == SepReview
			else
			{
		#endif

		CdControl(CdlSetloc, (u_char *)&Cdl, auStack32);

		/*
		// read entire file into buf
		iVar2 = CdRead(Cdl.size + 0x7ff >> 0xb, buf, 0x80);

		if ((iVar2 == 0) || (iVar2 = CdReadSync(0, (u_char *)0x0), iVar2 != 0))
		{
			#if BUILD == SepReview
				printf("\nERROR: LOAD_ReadFile unable to read file \'%s\'!\n",param_1);
			#endif
			buf = (u_long *)0x0;
		}
		*/
		if
		(
			// read entire file into buf, then check failure
			(CdRead(Cdl.size + 0x7ff >> 0xb, buf, 0x80) == 0) ||

			// check number of remaining sectors, failure if any remain
			(CdReadSync(0, (u_char *)0x0) != 0)
		)
		{
			#if BUILD == SepReview
				printf("\nERROR: LOAD_ReadFile unable to read file \'%s\'!\n", fileString);
			#endif
			buf = (u_long *)0x0;
		}
		else
		{
			if (bufAddress == (u_long *)0x0)
			{
				#if BUILD == EurRetail
				MEMPACK_ReallocMem(Cdl.size + 0x7ff & 0xfffff800);
				
				#else
				MEMPACK_ReallocMem(Cdl.size);

				#endif
			}
		}
		#if BUILD == SepReview
			}
		#endif
	}
	return buf;
}