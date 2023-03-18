#include <common.h>

void DECOMP_DISPLAY_Swap(void)
{
  struct GameTracker* gGT;
  struct DB* db;

  gGT = sdata->gGT;

  // get pointer to the "new" frontBufferDB, which is current backBuffer
  db = &gGT->db[gGT->swapchainIndex];

  // flip swapchain index (0->1) (1->0)
  gGT->swapchainIndex = 1 - gGT->swapchainIndex;

  // Set value of frontBuffer DB
  gGT->frontBuffer = db;

  // frontBuffer->dispEnv
  PutDispEnv(&db->dispEnv);
  
  // frontBuffer
  PutDrawEnv(db);
  return;
}