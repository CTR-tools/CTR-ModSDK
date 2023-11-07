#include <common.h>

void * DECOMP_LOAD_ReadFile(struct BigHeader* bigfile, u_int loadType, int subfileIndex, void *destination, int *size, void * callback)
{
	// param1 is the Pointer to CD position of BIGFILE

	u_char bVar1;
	u_int uVar2;
	int iVar3;
	CdlCB pcVar4;
	int uVar5;
	void *buf;
	CdlLOC aCStack56[2];
	u_char auStack48[8];

	bVar1 = true;

	pcVar4 = (CdlCB)0x0;

	DECOMP_CDSYS_SetMode_StreamData();

	uVar5 = 0;

	struct BigEntry* entry = BIG_GETENTRY(bigfile);

	// get size of file from bigfile header
	*size = entry[subfileIndex].size;

	// bigfile cdpos + subfileOffset
	CdIntToPos(bigfile->cdpos + entry[subfileIndex].offset, aCStack56);

	// if a destination pointer is not given
	if (destination == (void *)0x0)
	{
		// set flag that we used MEMPACK_AllocMem
		// to store this ReadFile somewhere random
		//DAT_80083a40 = DAT_80083a40 | 1;
		data.currSlot.flags = data.currSlot.flags | 1;

		// MEMPACK_AllocMem
		buf = (void *)DECOMP_MEMPACK_AllocMem(*size + 0x7ffU & 0xfffff800); // "FILE"

		// if allocation failed
		if (buf == (void *)0x0)
		{
			// function  failed
			return (void *)0;
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
#ifdef REBUILD_PC
		uVar5 = 1;
#endif

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
			pcVar4 = (CdlCB)&DECOMP_LOAD_ReadFileASyncCallback;
		}

		// Save this function as a callback,
		// which does not execute the function pointer
		CdReadCallback(pcVar4);

		uVar2 = CdRead(*size + 0x7ffU >> 0xb,buf,0x80);
		uVar5 = uVar5 & uVar2;

#ifndef REBUILD_PC
		if (callback == 0)
#endif
		{
			iVar3 = CdReadSync(0,(u_char *)0x0);
			bVar1 = iVar3 == 0;
		}
	}

	if ((callback == 0) && (destination == (void *)0x0))
	{
		DECOMP_MEMPACK_ReallocMem(*size);
	}
	return buf;
}