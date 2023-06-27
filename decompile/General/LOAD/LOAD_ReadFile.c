#include <common.h>

void CDSYS_SetMode_StreamData();

u_long * DECOMP_LOAD_ReadFile(struct BigHeader* bigfile, u_int loadType, int subfileIndex, u_long *destination, int *size, void * callback)
{
	// param1 is the Pointer to CD position of BIGFILE

	u_char bVar1;
	u_int uVar2;
	int iVar3;
	CdlCB pcVar4;
	int uVar5;
	u_long *buf;
	CdlLOC aCStack56[2];
	u_char auStack48[8];

	bVar1 = true;

	pcVar4 = (CdlCB)0x0;

	CDSYS_SetMode_StreamData();

	uVar5 = 0;

	// get size of file from bigfile header
	*size = bigfile->entry[subfileIndex].size;

	// bigfile cdpos + subfileOffset
	CdIntToPos(bigfile->cdpos + bigfile->entry[subfileIndex].offset, aCStack56);

	// if a destination pointer is not given
	if (destination == (u_long *)0x0)
	{
		// set flag that we used MEMPACK_AllocMem
		// to store this ReadFile somewhere random
		//DAT_80083a40 = DAT_80083a40 | 1;
		data.currSlot.flags = data.currSlot.flags | 1;

		// MEMPACK_AllocMem
		buf = (u_long *)MEMPACK_AllocMem(*size + 0x7ffU & 0xfffff800); // "FILE"

		// if allocation failed
		if (buf == (u_long *)0x0)
		{
			// function  failed
			return (u_long *)0;
		}
	}

	// if destination pointer is given
	else
	{
		data.currSlot.flags = data.currSlot.flags & 0xfffe;

		// use that
		buf = destination;
	}

	while ((uVar5 == 0 || (!bVar1)))
	{
		uVar5 = CdControl(CdlSetloc, (u_char *)aCStack56, auStack48);

		// If no callback function pointer is given
		if (callback == 0)
		{
			// Set function pointers to nullptr
			sdata->ReadFileAsyncCallbackFuncPtr = 0;
		}

		// If you want a callback function pointer
		// to execute after LOAD_ReadFile is done
		else
		{
			// Save the function pointer address
			sdata->ReadFileAsyncCallbackFuncPtr = callback;
			pcVar4 = (CdlCB)&LOAD_ReadFileASyncCallback;
		}

		// Save this function as a callback,
		// which does not execute the function pointer
		CdReadCallback(pcVar4);

		uVar2 = CdRead(*size + 0x7ffU >> 0xb,buf,0x80);
		uVar5 = uVar5 & uVar2;
		if (callback == 0)
		{
			iVar3 = CdReadSync(0,(u_char *)0x0);
			bVar1 = iVar3 == 0;
		}
	}

	if ((callback == 0) && (destination == (u_long *)0x0))
	{
		MEMPACK_ReallocMem(*size);
	}
	return buf;
}