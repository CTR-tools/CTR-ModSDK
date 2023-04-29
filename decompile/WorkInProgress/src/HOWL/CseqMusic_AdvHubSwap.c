#include <common.h>

void DECOMP_CseqMusic_AdvHubSwap(u_short songId, int p2, int p3) {
  struct Song* song;
  char i;

  if (sdata->boolAudioEnabled != 0) {
    if (
      (sdata->ptrCseqHeader != 0) &&

      // sequenceID out of range
      (songId < (sdata->ptrCseqHeader + 6))
    ) {
      Smart_EnterCriticalSection();
        for (i = 0; i < 2; i++) {
        song = &sdata->songPool[i];
          if (
            // if song is playing
            ((song->flags & 1) != 0) &&

            // if this song is the right song
            (song->id == songId)) {
            SongPool_AdvHub2(song, p2, p3);
          }
        }
      Smart_ExitCriticalSection();
    }
  }
  return;
}