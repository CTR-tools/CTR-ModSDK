#include <common.h>

// Budget: 28 / 24 (overbudget)

void DECOMP_VehPtr_Drifting_Finalize(struct Driver* d)
{
  d->timeUntilDriftSpinout = d->unk46b << 5;
  d->previousFrameMultDrift = d->multDrift;
}
