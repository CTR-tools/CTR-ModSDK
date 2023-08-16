#include <common.h>

void DECOMP_CseqMusic_AdvHubSwap(u_short songId, int p2, int p3) 
{
  struct Song* song;
  int i;

  // Temporarily commented out, while trying to fit byte budget
  
  //if (sdata->boolAudioEnabled == 0) return;
  //if (sdata->ptrCseqHeader == 0) return;
  //if (songId >= sdata->ptrCseqHeader->numSongs) return;
  
  Smart_EnterCriticalSection();
        
  for (i = 0; i < 2; i++) 
  {
    song = &sdata->songPool[i];
        
	// if song is playing
	if (song->flags & 1)
	{
		if (song->id == songId)
		{
			SongPool_AdvHub2(song, p2, p3);
		}
    }
  }
  
  Smart_ExitCriticalSection();
  return;
}