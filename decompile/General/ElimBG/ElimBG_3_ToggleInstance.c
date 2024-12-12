#include <common.h>

void DECOMP_ElimBG_ToggleInstance(struct Instance* inst, char boolGameIsPaused)
{
	u_int flags;
	
	// if game is being paused
	if (boolGameIsPaused)
	{
		flags = inst->flags;

		if (!(flags & HIDE_MODEL))
			flags &= ~INVISIBLE_BEFORE_PAUSE;
		else
			flags |= INVISIBLE_BEFORE_PAUSE;

		inst->flags = flags;
		inst->flags |= (INVISIBLE_DURING_PAUSE | HIDE_MODEL);

		return;
	}

	if ((inst->flags & (INVISIBLE_BEFORE_PAUSE | INVISIBLE_DURING_PAUSE)) == INVISIBLE_DURING_PAUSE)
		inst->flags &= ~(INVISIBLE_DURING_PAUSE | HIDE_MODEL);
}