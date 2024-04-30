#include <common.h>

void DECOMP_VehPickupItem_ShootOnCirclePress(struct Driver *d)
{
    u_char weapon;

    if (d->ChangeState_param2 != 0)
    {
		#ifndef REBUILD_PS1
        DECOMP_VehPickState_NewState(d, d->ChangeState_param2, d->ChangeState_param3, d->ChangeState_param4);
		#endif
	}

    // If you want to fire a weapon
    if ((d->actionsFlagSet & 0x8000) == 0)
        return;

    // Remove the request to fire a weapon, since we will fire it now
    d->actionsFlagSet &= ~(0x8000);

	weapon = d->heldItemID;

	// Missiles and Bombs share code,
	// Change Bomb1x, Bomb3x, Missile3x, to Missile1x	
	if(
		(weapon == 1) ||
		(weapon == 10) ||
		(weapon == 11)
	  )
	{
		weapon = 2;
	}
    
    DECOMP_VehPickupItem_ShootNow(d, weapon, 0);
}