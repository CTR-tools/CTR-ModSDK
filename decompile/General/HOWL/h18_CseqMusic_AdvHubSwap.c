#include <common.h>

void DECOMP_CseqMusic_AdvHubSwap(u_short songId, struct SongSet* songSet, int songSetActiveBits) 
{
  struct Song* song;
  int i;

  // Temporarily commented out, while trying to fit byte budget
  #if 0
  if (sdata->boolAudioEnabled == 0) return;
  if (sdata->ptrCseqHeader == 0) return;
  if (songId >= sdata->ptrCseqHeader->numSongs) return;
  #endif
  
  DECOMP_Smart_EnterCriticalSection();
        
  for (i = 0; i < 2; i++) 
  {
    song = &sdata->songPool[i];
        
	// if song is playing
	if (song->flags & 1)
	{
		if (song->id == songId)
		{
			DECOMP_SongPool_AdvHub2(song, songSet, songSetActiveBits);
		}
    }
  }
  
  DECOMP_Smart_ExitCriticalSection();
  return;
}