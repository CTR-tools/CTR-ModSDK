#include <common.h>

void Weapon_Shoot_OnCirclePress(struct Driver *d)
{
    u_char weapon;

    if (d->ChangeState_param2 != 0)
    {
        Player_ChangeState(d, d->ChangeState_param2, d->ChangeState_param3, d->ChangeState_param4);
    }

    // If you want to fire a weapon
    if ((d->actionsFlagSet & 0x8000) == 0)
        return;

    // Remove the request to fire a weapon, since we will fire it now
    d->actionsFlagSet &= ~(0x8000);

    // Set weapon to one bomb
    weapon = 1;

    // If this weapon is not 3 bombs
    if ((d->heldItemID != 10) &&

        (
            // Set weapon to missile
            weapon = 2,

            // if this weapon is not 3 missiles
            d->heldItemID != 11))
    {
        // Set to the original weapon the player has
        weapon = d->heldItemID;
    }

    // whaat???
    // If weapon is bomb, change to missile?????
    if (weapon == 1)
    {
        weapon = 2;
    }
    
    Weapon_Shoot_Now(d, weapon, 0);
}