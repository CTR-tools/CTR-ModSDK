
void UpdateCheckpointTracker(int driverID);
typedef void (*VehicleFuncPtr)(struct Thread* thread, struct Driver* driver);

void RunVehicleThread(VehicleFuncPtr func, struct Thread* thread, struct Driver* driver)
{
    UpdateCheckpointTracker(driver->driverID);
    if (func == nullptr) { return; }

    bool restore = false;
    if ((sdata->gGT->gameMode1 & END_OF_RACE) && (checkpointTracker[driver->driverID].raceFinished == 0))
    {
        sdata->gGT->gameMode1 &= ~(END_OF_RACE);
        restore = true;
    }
    func(thread, driver);
    if (restore) { sdata->gGT->gameMode1 |= END_OF_RACE; }
}


// TODO: This isnt called anymore,
// need to decide if still needed
#if 0
void RunVehicleSet13(struct Thread* dThread, struct Driver* dOnline)
{
	if(dThread->funcThTick != 0)
		return;

	// This only works because we have NO collision
	// and therefore NO bounce physics, update P1
	// first, then update other drivers later
	
	// We can still "eventually" have mask-weapon
	// collision, but no "bounce" physics with this logic
		
	for(int iVar11 = 0; iVar11 < 13; iVar11++)
	{
		VehicleFuncPtr pcVar5 = dOnline->funcPtrs[iVar11];
		
		if(pcVar5 == NULL)
			continue;
		
		RunVehicleThread(pcVar5, dThread, dOnline);
		
		#ifdef USE_60FPS
			#ifndef REBUILD_PS1
				// if this function just ran
				if(pcVar5 == VehFrameProc_Driving)
				{
					// only if jumping animation,
					// otherwise wheelie gets bugged
					if(dOnline->instSelf->animIndex == 3)
					{
						dOnline->matrixIndex =
						dOnline->matrixIndex >> 1;
					}
				}
			#endif
		#endif
	}
}
#endif