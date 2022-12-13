#include "../p_rom.h"

void howl_TogglePause(int enable);

void SaveState()
{
	int i;
	int * driver = (int *)(sdata->gGT->drivers[0]);
	int * selfInstance = (int *)(sdata->gGT->drivers[0]->instSelf);
	int * saveBuffer = (int *)(sdata->gGT->drivers[p_rom->slot + 1]);
	int * instanceBuffer = p_rom->firstInstance + (instanceSize * p_rom->slot);
	int * soundBuffer = p_rom->firstSound + (soundSize * p_rom->slot);
	int * sound = (int *)(sdata->channelStatsCurr);

	for (i = 0; i < driverSize; i++)
		saveBuffer[i] = driver[i];

	for (i = 0; i < instanceSize; i++)
		instanceBuffer[i] = selfInstance[i];

	howl_TogglePause(1);
	p_rom->numSounds[p_rom->slot] = sdata->numBackup_ChannelStats;
	for (i = 0; i < soundSize; i++)
		soundBuffer[i] = sound[i];
	howl_TogglePause(0);

	p_rom->clock[p_rom->slot][0] = sdata->gGT->elapsedEventTime;
	p_rom->clock[p_rom->slot][1] = sdata->gGT->lapTime[0];
	p_rom->clock[p_rom->slot][2] = sdata->gGT->lapTime[1];
	p_rom->clock[p_rom->slot][3] = sdata->gGT->lapTime[2];

	p_rom->ghostBufferPointer[p_rom->slot] = sdata->GhostRecording.ptrCurrOffset;
}