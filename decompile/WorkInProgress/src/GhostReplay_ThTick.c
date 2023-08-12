#include <common.h>

void DECOMP_GhostReplay_ThTick(struct Thread* t)
{
	struct Driver* d;
	struct GhostTape* tape;
	struct Instance* inst;
	struct GameTracker* gGT;
	struct GhostHeader* gh;
	short endian;
	
	int i;
	int color;
	int time;
	char* ptrCurr;
	
	d = t->object;
	if(d == NULL) return;
	
	tape = d->ghostTape;
	inst = d->instSelf;
	
	inst->scale[0] = 0xccc;
	inst->scale[1] = 0xccc;
	inst->scale[2] = 0xccc;
	
	if(
		// 6-second timer != 0, and ghost made by human
		(sdata->ghostOverflowTextTimer != 0) &&
		(d->ghostID == 0)
	  )
	{
		color = 0xFFFF8004;
		if(sdata->ghostOverflowTextTimer & 1)
			color = 0xFFFF8003;
		
		// GHOST DATA OVERFLOW
		DecalFont_DrawLine(
			sdata->lngStrings[0x169],
			0x100, 0x28, FONT_SMALL, color);
			
		// CAN NOT SAVE GHOST DATA
		DecalFont_DrawLine(
			sdata->lngStrings[0x16A],
			0x100, 0x32, FONT_SMALL, color);
			
		sdata->ghostOverflowTextTimer--;
	}
	
	gGT = sdata->gGT;
	
	if (
		(sdata->boolGhostsDrawing == 0) ||
		((gGT->gameMode1 & PAUSE_THREADS) != 0) ||
		(tape->ptrEnd == tape->ptrStart) ||
		(d->ghostBoolInit == 0)
	   )
	{
		// make invisible
		inst->flags |= 0x80;
		return;
	}
	
	if(d->reserves > 0)
	{
		d->reserves -= gGT->elapsedTimeMS;
		if(d->reserves < 0) d->reserves = 0;
	}
	
	if(d->ghostBoolStarted == 0)
	{
		if(gGT->trafficLightsTimer < 1)
		{
			d->ghostBoolStarted = 1;
			tape->timeInPacket32 = -1;
		}
	}
	
	inst->alphaScale = 0xa00;
	inst->flags = (inst->flags & 0xfff8ff7f) | 0x60000;

	time = tape->timeElapsedInRace;
	if(time < 0) time = 0;
	
	// flush and rewrite GhostPackets cache
	if(tape->timeInPacket32 < time)
	{
		
		printf("%d %d\n", tape->timeInPacket32, time);
		
		tape->packetID = -1;
		tape->timeInPacket01 = tape->timeInPacket32_backup;
	
		ptrCurr = tape->ptrCurr;
	
		for(i = 0; i < 2; /**/)
		{
			// reached end of tape
			if(ptrCurr >= tape->ptrEnd)
			{
				gh = tape->gh;
				d->ySpeed = gh->ySpeed;
				d->speedApprox = gh->speedApprox;
				
				// not an AI anymore
				d->actionsFlagSet &= ~(0x100000);
				
				BOTS_Driver_Convert(d);
				BOTS_ThTick_Drive(t);
				
				// finished race
				d->actionsFlagSet |= ~(0x2000000);
				
				// ignore collisions
				t->flags |= 0x1000;
				
				printf("Race End: %08x\n", tape->ptrEnd);
				
				return;
			}
			
			// opcode 0x80 - 0x84
			if((((u_char)ptrCurr[0] + 0x80) & 0xff) < 5)
			{
				switch((u_char)ptrCurr[0])
				{
				case 0x80:
				
					printf("Position %08x\n", ptrCurr);
					
					// posX
					endian = ((u_char)ptrCurr[1]<<8) | ptrCurr[2];
					inst->matrix.t[0] = endian;
					d->posCurr[0] = inst->matrix.t[0] << 8;
					
					// posY
					endian = ((u_char)ptrCurr[3]<<8) | ptrCurr[4];
					inst->matrix.t[1] = endian;
					d->posCurr[1] = inst->matrix.t[1] << 8;
					
					// posZ
					endian = ((u_char)ptrCurr[5]<<8) | ptrCurr[6];
					inst->matrix.t[2] = endian;
					d->posCurr[2] = inst->matrix.t[2] << 8;
					
					// rotY, rotZ
					endian = ptrCurr[9] >> 4;
					endian = ptrCurr[10] >> 4;
					
					if(i == 1) 
					{
						endian = ((u_char)ptrCurr[7]<<8) | ptrCurr[8];
				
						tape->timeInPacket32_backup += endian;
						tape->timeInPacket32 = tape->timeInPacket32_backup;
						
						printf("%d\n", endian);
					}
					
					i++;
					ptrCurr += 11;
					break;
				case 0x81:
					//printf("Animation\n");
					ptrCurr += 3;
					break;
				case 0x82:
					//printf("Boost\n");
					ptrCurr += 6;
					break;
				case 0x83:
					//printf("InstFlags\n");
					ptrCurr += 2;
					break;
				case 0x84:
					//printf("NULL\n");
					ptrCurr += 1;
					break;
				}
			}
			
			// no opcode, assume velocity
			else
			{
				//printf("Velocity\n");
				ptrCurr += 5;
			}
			
			tape->ptrCurr = ptrCurr;
		}
	}

	// ===================
	
	if(gGT->trafficLightsTimer < 1)
		tape->timeElapsedInRace += gGT->elapsedTimeMS;
}