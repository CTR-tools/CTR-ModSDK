#include <common.h>

void DECOMP_GAMEPAD_ProcessMotors(struct GamepadSystem *gGS)
{
	int totalPower = 0;
	struct GameTracker* gGT = sdata->gGT;
	
	for(int i = 0; i < gGS->numGamepadsConnected; i++)
	{
        struct GamepadBuffer *pad = &gGS->gamepad[i];
        struct ControllerPacket *packet = pad->ptrControllerPacket;
		
		if(
			(packet != 0) &&
			(gGT->boolDemoMode == 0) &&
			((gGT->gameMode1 & 0xf) == 0) &&
			(DECOMP_RaceFlag_IsTransitioning() == 0)
		  )
		{
			if (packet->controllerData == ((PAD_ID_JOGCON << 4) | 3))
			{
				unsigned char bVar1 = 0x40;
				
				if(pad->unk44 == 0)
				{
					if(pad->unk46 == 0)
					{
						if(
							(pad->unk43 < pad->unk42) ||
							(
								bVar1 = pad->unk43 >> 4,
								pad->unk48 != 0
							)
						  )
						{
							char unk42 = pad->unk42;
							bVar1 = unk42 >> 4;
							
							if(
								(((gGT->timer & bVar1) & 0xf) != 0) &&
								(
									bVar1 = (unk42 - 0x10) >> 4,
									(unk42 - 0x10) < 0
								)
							  )
							{
								bVar1 = 0;
							}
						}
					
						bVar1 = bVar1 | 0x30;
						pad->motorDesired[0] = bVar1;
					}
					
					else
					{
						pad->motorDesired[0] = pad->unk45;
					
						pad->unk46 -= gGT->elapsedTimeMS;
						if(pad->unk46 < 1)
						{
							pad->unk46 = 0;
							pad->unk45 = 0;
						}
					}
				}
				
				else
				{
					pad->motorDesired[0] = bVar1;
				}
				
				// === Naughty Dog Bug ===
				// original code subtracts elapsed time,
				// but then does "if != 0, set = 0"
				pad->unk48 = 0;
				
				pad->motorDesired[1] = 0;
			}
			
			else
			{
				// Frequency Control (on/off)
				pad->motorDesired[0] = 0;
				
				if(pad->shockFrameFreq != 0)
					if((gGT->timer & pad->shockValFreq) == 0)
						pad->motorDesired[0] = 0xff;
					
				// Strength Control (percentage)
				pad->motorDesired[1] = 0;
				
				if(pad->shockFrameForce1 != 0)
				{
					pad->motorDesired[1] = pad->shockValForce1;
				}
					
				else
				{
					pad->shockValForce1 = 0;
					
					if(pad->shockFrameForce2 != 0)
					{
						pad->motorDesired[1] = pad->shockValForce2;
					}
					
					else
					{
						pad->shockValForce2 = 0;
					}
				}
			}
			
			if(pad->shockFrameFreq != 0) pad->shockFrameFreq--;
			if(pad->shockFrameForce1 != 0) pad->shockFrameForce1--;
			if(pad->shockFrameForce2 != 0) pad->shockFrameForce2--;
		}
		
		else
		{
			if(
				(packet == 0) ||
				(packet->controllerData != ((PAD_ID_JOGCON << 4) | 3)) ||
				(pad->unk44 == 0)
			  )
			{
				pad->motorDesired[0] = 0;
			}
			
			else
			{
				pad->motorDesired[0] = 0x40;
			}
			
			pad->motorDesired[1] = 0;
			
			pad->shockFrameFreq = 0;
			pad->shockFrameForce1 = 0;
			pad->shockFrameForce2 = 0;
			
			pad->unk45 = 0;
			pad->unk46 = 0;
		}
		
		if(pad->unk44 != 0) pad->unk44--;
		
		// Calculate Total Power
		// 1 standard DualShock uses 30 units of power
		if(pad->motorDesired[0] != 0) totalPower += pad->motorPower[0];
		if(pad->motorDesired[1] != 0) totalPower += pad->motorPower[1];
	}
	
	// PlayStation can not exceed 60 units
	// of electrical power, in port 1 or 2
	if (totalPower > 60)
	{
		int numPads = gGS->numGamepadsConnected;
		int skipIndex = gGT->timer % numPads;
		
		// === Naughty Dog Bug ===
		// OG code decreases Motor1 until power drops to 60,
		// then shuts off Motor2 for all controllers without 
		// Motor1. Dont do that, decrease Motor1 and Motor2,
		// take both motors into consideration until 60
		
		while(totalPower > 60)
		{
			// cycle back around
			if(skipIndex >= numPads)
				skipIndex = 0;
			
			struct GamepadBuffer *pad = &gGS->gamepad[skipIndex];
			
			if(pad->motorDesired[0] != 0)
			{
				pad->motorDesired[0] = 0;
				totalPower -= pad->motorPower[0];
			}
			
			if(pad->motorDesired[1] != 0)
			{
				pad->motorDesired[1] = 0;
				totalPower -= pad->motorPower[1];
			}
			
			skipIndex++;
		}
	}
	
	for(int i = 0; i < gGS->numGamepadsConnected; i++)
	{
        struct GamepadBuffer *pad = &gGS->gamepad[i];
		
		pad->motorSubmit[0] = pad->motorDesired[0];
		pad->motorSubmit[1] = pad->motorDesired[1];
	}
}