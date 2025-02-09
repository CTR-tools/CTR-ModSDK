#include <common.h>

void DECOMP_VehStuckProc_PlantEaten_Update(struct Thread *t, struct Driver *d)
{
    d->NoInputTimer -= sdata->gGT->elapsedTimeMS;

	if (d->NoInputTimer <= 0)
	{
		d->NoInputTimer = 0;
	
		// respawn driver at last valid quadblock
		VehStuckProc_MaskGrab_FindDestPos((struct Thread*)d, (struct Driver*)d->lastValid);
		VehBirth_TeleportSelf(d, 0, 0x80);

		// enable collision, make visible
		t->flags &= ~(0x1000);
		t->inst->flags &= ~(HIDE_MODEL);

		// this lets you rev engine while falling
		VehStuckProc_RevEngine_Init(t, d);
	}
}