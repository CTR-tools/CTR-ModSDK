#include <common.h>

void RefreshCard_NextMemcardAction(u_short memcardSlot, u_short memcardAction, u_char* filename, u_char* memcardIcon, struct GhostHeader* ghost, u_short filesize)
{
  sdata->memcardUnk1 &= ~(0x8);

  sdata->frame2_memcardAction = memcardAction;
  sdata->frame2_memcardSlot = memcardSlot;

  sdata->frame4_memcardAction = memcardAction;
  sdata->frame4_memcardSlot = memcardSlot;

  // Save filename (BASCUS...)
  sdata->ghostProfile_fileName = filename;

  // Save icon (crash/ghost/psyqhand)
  sdata->ghostProfile_fileIconHeader = memcardIcon;

  // pointer to ghostHeader (not memcard)
  sdata->ghostProfile_ptrGhostHeader = ghost;

  // size (3E00)
  sdata->ghostProfile_size3E00 = filesize;
}