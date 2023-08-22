#include <common.h>

int DECOMP_CseqMusic_Start(int songID, int p2, int p3, int p4, int p5)
{
	int i;
	struct Song* song;
	
	if(sdata->boolAudioEnabled == 0) return 0;
	if(sdata->ptrCseqHeader == 0) return 0;
	
	if(sdata->ptrCseqHeader->numSongs <= songID) return 0;
	
	Smart_EnterCriticalSection();
	
	for(i = 0; i < 2; i++)
	{
		song = &sdata->songPool[i];
		
		// if pool is free
		if((song->flags & 1) == 0)
		{
			// start song in this pool
			SongPool_Start(song, songID, p2, p5, p3, p4);
			
			Smart_ExitCriticalSection();
			return 1;
		}
	}
	
	Smart_ExitCriticalSection();
	return 0;
}