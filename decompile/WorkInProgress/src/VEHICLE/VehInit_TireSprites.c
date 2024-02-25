#include <common.h>

void VehInit_TireSprites(struct Thread *t)
{
    struct GameTracker *gGT = sdata->gGT;
    struct Driver *d = t->object;
    struct IconGroup *tireAnim = gGT->iconGroup[0];

    // wheel scale
    d->wheelSize = 0xccc;

    struct Icon** tire = ICONGROUP_GETICONS(tireAnim);

    d->wheelSprites = tire;
    
    
    if (
			// if character ID is oxide
			(data.characterIDs[d->driverID] == 15) &&
			(gGT->levelID != MAIN_MENU_LEVEL)
		)
    {
        d->wheelSize = 0;
    }

    d->tireColor = 0x2e808080;
    d->unkSpeedValue1 = 0xa00;

    // item held to 0xF (nothing)
    d->heldItemID = 0xf;

    // related to engine sound
    d->unk47B = 2;

    d->AxisAngle1_normalVec[1] = 0x1000;
    d->AxisAngle2_normalVec[1] = 0x1000;
    d->unk412 = 0x600;
    d->numFramesSpentSteering = 10000;

    d->terrainMeta1 = VehGetTerrain(10);
    
    d->BattleHUD.numLives = gGT->battleLifeLimit;
    d->BattleHUD.teamID = d->driverID;

    d->quip1 = 0xffff;
    d->quip3 = 0xffff;
}