#include <common.h>

int MEMPACK_PushState();
u_long* LOAD_ReadFile(struct BigHeader* bigfile, u_int loadType, u_int fileIndex, u_int* destination, u_int* sizePtr, int callback);
void LOAD_VramFileCallback(struct LoadQueueSlot* lqs);
void MEMPACK_PopState();

// In Aug 5 prototype, this is called LOAD_VramFile
// basically loads ctr texture file to vram in 3 different ways based on callback value
// bigfile = bigFilePtr
// fileIndex = fileIndex
// destination = target pointer (where should we load the file, can be null)
// sizePtr = pointer to size
// callback = callback in other funcs/structs, also used to control execution by passing -1, -2 etc
u_int DECOMP_LOAD_VramFile(struct BigHeader* bigfile, u_int fileIndex, u_int* destination, u_int* sizePtr, int callback)
{
	//local queue slot
	struct LoadQueueSlot stuff;

	// Used for "SCEA Presents", "Copyright", and "UI Textures"
	//if we're not given the address to use, create new temporary place to load
	if (destination == (u_int *)0x0)
	{
		// add a bookmark
		MEMPACK_PushState();
	}

	// case -1 = we don't want to use global file queue or store file in ram
	if (callback == -1)
	{
		//prepare local loading slot for the file
		stuff.flags = 0;
		stuff.type = 3;
		stuff.ptrBigfileCdPos = bigfile;
		stuff.subfileIndex = fileIndex;
		stuff.ptrDestination = LOAD_ReadFile(bigfile, 0, fileIndex, destination, sizePtr, callback);
		stuff.size = *sizePtr;
		stuff.callback.flags = 0;

		//load all TIMs from ctr vram file (usually 1 or 2)
		LOAD_VramFileCallback(&stuff);

		VSync(2);

		// reset timer
		sdata->frameWhenLoadingFinished = 0;

	 	//if we're not given the address to use, remove temporary space used before
		if (destination == (u_int *)0x0)
		{
			MEMPACK_PopState();
		}
	}
	else
	{
		

		//case -2 = load file to ram and store to active slot of global file queue
		if (callback == -2)
		{
			stuff.ptrDestination = LOAD_ReadFile(bigfile, 3, fileIndex, 0, sizePtr, (int)LOAD_VramFileCallback);
			data.currSlot.ptrDestination = stuff.ptrDestination;
			*destination = (u_int)stuff.ptrDestination;
		}
		else
		{
			printf("ck 6\n");

			// IT CRASHES HERE NOW --Super

			//case not -1 or -2 = just return the pointer to loaded file
			stuff.ptrDestination = LOAD_ReadFile(bigfile, 3, fileIndex, destination, sizePtr, (int)LOAD_VramFileCallback);
			printf("ck 7\n");
		}
	}

	return (u_int)stuff.ptrDestination;
}