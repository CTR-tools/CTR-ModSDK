#include <common.h>

void DECOMP_VehBirth_TireSprites(struct Thread *t)
{
    struct GameTracker *gGT = sdata->gGT;
    struct Driver *d = t->object;
    struct IconGroup *tireAnim = gGT->iconGroup[0];
	int driverID = d->driverID;

    struct Icon** tire = ICONGROUP_GETICONS(tireAnim);
    d->wheelSprites = tire;

    d->wheelSize = 0xccc;

	// compiler might reuse these registers in the IF,
	// first set item to "none" and driverID, then
	// check for Oxide in characterIDs

	d->heldItemID = 0xf;
    d->BattleHUD.teamID = driverID;

    if (
			// if character ID is oxide
			(data.characterIDs[driverID] == 0xf) &&
			(gGT->levelID != MAIN_MENU_LEVEL)
		)
    {
        d->wheelSize = 0;
    }

    d->tireColor = 0x2e808080;
    d->unkSpeedValue1 = 0xa00;

    // unused by decomp, but if this function is combined
	// with retail code, the variable must be set to 2
    d->unk47B = 2;

    d->AxisAngle1_normalVec.y = 0x1000;
    d->AxisAngle2_normalVec[1] = 0x1000;
    d->unk412 = 0x600;
    d->numFramesSpentSteering = 10000;

#ifndef REBUILD_PS1
    d->terrainMeta1 = VehAfterColl_GetTerrain(10);
#endif

    d->BattleHUD.numLives = gGT->battleLifeLimit;

    d->quip1 = 0xffff;
    d->quip3 = 0xffff;
}