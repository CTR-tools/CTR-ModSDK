#include "../p_rom.h"

void SaveState()
{
	int i;
	int * driver = (int *)(sdata->gameTracker.drivers[0]);
	int * selfInstance = (int *)(sdata->gameTracker.drivers[0]->instSelf);
	int * saveBuffer = (int *)(sdata->gameTracker.drivers[p_rom->slot + 1]);
	int * instanceBuffer = p_rom->firstInstance + (instanceSize * p_rom->slot);
	int * soundBuffer = p_rom->firstSound + (soundSize * p_rom->slot);
	int * sound = (int *)(sdata->channelStatsCurr);

	for (i = 0; i < driverSize; i++)
		saveBuffer[i] = driver[i];

	for (i = 0; i < instanceSize; i++)
		instanceBuffer[i] = selfInstance[i];

	MainFrame_TogglePauseAudio(1);
	p_rom->numSounds[p_rom->slot] = sdata->numBackup_ChannelStats;
	for (i = 0; i < soundSize; i++)
		soundBuffer[i] = sound[i];
	MainFrame_TogglePauseAudio(0);

	p_rom->clock[p_rom->slot][0] = sdata->gameTracker.elapsedEventTime;
	p_rom->clock[p_rom->slot][1] = sdata->gameTracker.lapTime[0];
	p_rom->clock[p_rom->slot][2] = sdata->gameTracker.lapTime[1];
	p_rom->clock[p_rom->slot][3] = sdata->gameTracker.lapTime[2];

	p_rom->ghostBufferPointer[p_rom->slot] = sdata->GhostRecording.ptrCurrOffset;
}