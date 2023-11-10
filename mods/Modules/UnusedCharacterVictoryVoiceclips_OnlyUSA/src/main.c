#include <common.h>

// hook end of CAM_EndOfRace,
// leave this as JAL hook, dont change to JR/JMP hook,
// cause CAM_EndOfRace happens on first frame of demo mode,
// and also JR hook breaks in VS
void CAM_EndOfRace_hook(struct CameraDC* camDC, struct Driver* d)
{
	int id;
	int loop1;
	int r;

	// enable CDSYS_XAPlay so this
	// play can run successfully
	sdata->boolUseDisc = 1;

	// get rank
	r = (int)d->driverRank;

	// 0, 1, 2
	if(r < 3)
	{
		// get characterID
		id = data.characterIDs[d->driverID];

		// play audio
		CDSYS_XAPlay(2, id*0x13 + 0x10+r);
	}

	// disable all other CDSYS_XAPlay
	// so this play is not overwritten
	sdata->boolUseDisc = 0;

	// call original
	CAM_EndOfRace(camDC, d);
}

// after a few frames, when nothing is left
// to overwrite the "player finished" XA
void CdReadyCallbackHook()
{
	// enable again
	sdata->boolUseDisc = 1;
}
