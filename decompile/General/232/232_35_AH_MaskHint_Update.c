#include <common.h>

void DECOMP_AH_MaskHint_Update()
{
	struct GameTracker* gGT = sdata->gGT;
	struct Driver* d = gGT->drivers[0];
	short pos[3];
	short rot[3];
	
	switch(sdata->AkuAkuHintState-1)
	{
		case 0:
			if(sdata->XA_State != 0) return;
			
			sdata->AkuAkuHintState++;
			break;
		
		case 1:
			int absSpeedApprox = d->speedApprox;
			if(absSpeedApprox < 0) absSpeedApprox = -absSpeedApprox;
			if(absSpeedApprox > 0x31) return;
			
			if((*(int*)0x800b5574 & 1) == 0)
			{
				struct CameraDC* cdc = &gGT->cameraDC[0];
				
				cdc->driverOffset_CamEyePos[0] = *(short*)0x800b5520;
				cdc->driverOffset_CamEyePos[1] = *(short*)0x800b5522;
				cdc->driverOffset_CamEyePos[2] = *(short*)0x800b5524;
				
				cdc->driverOffset_CamLookAtPos[0] = *(short*)0x800b5528;
				cdc->driverOffset_CamLookAtPos[1] = *(short*)0x800b552a;
				cdc->driverOffset_CamLookAtPos[2] = *(short*)0x800b552c;
				
				cdc->flags |= 8;
				
				// === Naughty Dog Bug ===
				// ScratchpadStruct was allocated on stack memory,
				// instead of 0x1f800108, that's why FollowDriver
				// parameter is wrong, and why function allocates
				// 0x2d0 on $sp when MaskHint_Update starts
				
				// Get pos and rot, then set them as desired
				CAM_FollowDriver_AngleAxis(cdc,d,0x1f800108,pos,rot);
				CAM_SetDesiredPosRot(cdc,pos,rot);
			}
			
			*(short*)0x800b5570 = FPS_DOUBLE(60);
			
			sdata->AkuAkuHintState++;
			break;
		
		case 2:
		
			if (
				((*(int*)0x800b5574 & 1) == 0) && 
				((gGT->cameraDC[0].flags & 0x800) == 0) &&
				(*(int*)0x800b566c != FPS_DOUBLE(20))
			   ) 
			{
				return;
			}
			
			*(int*)0x8008d860 = VehTalkMask_Init();
			
			struct Instance* dInst = d->instSelf;
			CTR_MatrixToRot(rot, &dInst->matrix, 0x11);
			
			// not a typo
			*(short*)0x800b5568 = rot[1] & 0xfff;
			*(short*)0x800b556c = rot[2] & 0xfff;
			*(short*)0x800b556a = rot[0] & 0xfff;
			
			*(short*)0x800b5560 = dInst->matrix.t[0];
			*(short*)0x800b5562 = dInst->matrix.t[1];
			*(short*)0x800b5564 = dInst->matrix.t[2];
			
			struct Instance* mhInst = *(int*)0x8008d860;
			((struct MaskHint*)mhInst->thread->object)->scale = 0;
			
			AH_MaskHint_SetAnim(0);
			
			*(int*)0x800b5218 = 0;
			
			sdata->AkuAkuHintState++;
			break;
			
		case 3:
		
			// first frame "whoosh" sound
			if(*(int*)0x800b5218 == 0)
				OtherFX_Play_LowLevel(0x100,1,0xff8080);
			
			// if 3-second spawn, play more sounds
			if(*(short*)0x800b566c == FPS_DOUBLE(0x5a))
			{
				if(*(int*)0x800b5218 == FPS_DOUBLE(10))
					OtherFX_Play_LowLevel(0x100,0,0xd78a80);
			
				else if(*(int*)0x800b5218 == FPS_DOUBLE(20))
					OtherFX_Play_LowLevel(0x100,1,0xaf9480);
			
				else if(*(int*)0x800b5218 == FPS_DOUBLE(25))
					OtherFX_Play_LowLevel(0x100,0,0x879e80);
			
				else if(*(int*)0x800b5218 == FPS_DOUBLE(30))
					OtherFX_Play_LowLevel(0x100,1,0x5fa880);
			}
			
			int timer4096 = 
				((*(int*)0x800b5218) << 0xc) / *(short*)0x800b566c;
				
			AH_MaskHint_SetAnim(timer4096);
			AH_MaskHint_SpawnParticles(3, 0x800b521c, timer4096);
			
			// if not finished spawning
			if (*(int*)0x800b5218 < *(short*)0x800b566c)
			{
				*(int*)0x800b5218 = *(int*)0x800b5218 + 1;
				
				timer4096 = 
					((*(int*)0x800b5218) << 0xc) / *(short*)0x800b566c;
					
				AH_MaskHint_LerpVol(timer4096);
				break;
			}
			
			if (sdata->modelMaskHints3D != 0)
			{
				if(
					((*(int*)0x800b5574 & 1) != 0) ||
					((gGT->cameraDC[0].flags & 0x800) != 0)
				  )
				{
					AH_MaskHint_LerpVol(0x1000);
					
					AH_MaskHint_SpawnParticles(0x18,0x800b5384,0x1000);
					
					VehTalkMask_PlayXA(*(int*)0x8008d860,*(int*)0x800b5558);
					
					if (
						((gGT->gameMode1 & ADVENTURE_ARENA) != 0) &&
						
						// Not "Welcome to Adventure" or "You need a Boss Key"
						((int*)0x800b5558 != 0) &&
						((int*)0x800b5558 != 0x18)
					) 
					{
						// hide UI map
						gGT->hudFlags |= 0x10;
					}
					
					sdata->AkuAkuHintState++;
					break;
				}
			}
			
			// if sdata->modelMaskHints3D == NULL,
			// stay here forever stuck
			break;
			
		case 4:
			int lngIndex = 0;
			int boolFound = 0;
			short* ptrLngID = 0x800b54f4;
			
			for(/**/; *ptrLngID > -1; ptrLngID++)
			{
				if(*(int*)0x800b5558 == (ptrLngID[0] - 0x17b)/2)
				{
					boolFound = 1;
					break;
				}
			}
			
			if(boolFound)
			{
				// === Naughty Dog Bug ===
				// Why'd they replace LngIndex for subtitles
				// with this generic text? Accident or intention?
				
				#if 0
				
				// Code that shipped in 1999
				if(VehPickupItem_MaskBoolGoodGuy(d))
					lngIndex = 0x177;
				else
					lngIndex = 0x232;
				
				#else
				
				// Code that restores the effect
				lngIndex = ptrLngID[0];
				
				#endif
				
				RECT r;
				r.x = -10;
				r.y = 0xb0;
				r.w = 0x214;
				r.h = 8 + /* not a typo */
					DECOMP_DecalFont_DrawMultiLine(
						sdata->lngStrings[lngIndex],
						0x100,0xb4,400,2,0xffff8000);
						
				MENUBOX_DrawInnerRect(&r, 4, gGT->backBuffer->otMem.startPlusFour);
			}
			
			AH_MaskHint_SetAnim(0x1000);
		
			int bVar8;
			int uVar3 = *(short*)0x800b5570 - 1;
			if (
					(
						(
							(*(short*)0x800b5570 == 0) ||
							(bVar8 = *(short*)0x800b5570 == 1, *(short*)0x800b5570 = uVar3, bVar8)
						) &&
						(
							(
								(VehTalkMask_boolNoXA() != 0) ||
								((sdata->gGamepads->gamepad[0].buttonsTapped & BTN_TRIANGLE) != 0)
							)
						)
					) &&
					(
						sdata->AkuAkuHintState++,
						
						// If you're in Adventure Arena
						((gGT->gameMode1 & ADVENTURE_ARENA) != 0)
					)
				) 
			{
				// show map again
				gGT->hudFlags &= ~(0x10);
			}
			break;
			
		case 5:
		
			AH_MaskHint_SpawnParticles(20, 0x800b5384, 0x1000);
			
			// vanish sound
			OtherFX_Play(0x101, 1);
			
			VehTalkMask_End();
			
			if((*(int*)0x800b5574 & 1) == 0)
			{
				// transition back to player
				gGT->cameraDC[0].flags |= 0x400;
			}
			
			sdata->AkuAkuHintState++;
			break;
			
		case 6:
		
			AH_MaskHint_LerpVol(0x1000 - gGT->cameraDC[0].unk8C);
			
			if(
				((gGT->cameraDC[0].flags & 0x200) == 0) ||
				((*(int*)0x800b5574 & 1) != 0)
			)
			{
				AH_MaskHint_SetAnim(0);
				AH_MaskHint_LerpVol(0);
				
				*(short*)0x800b5570 = 0;
				if((*(int*)0x800b5574 & 1) != 0)
					*(short*)0x800b5570 = FPS_DOUBLE(30);
				
				sdata->AkuAkuHintState++;
			}
			break;
		
		case 7:
		
			AH_MaskHint_LerpVol(0);
			
			*(short*)0x800b5570 = *(short*)0x800b5570 - 1;
			
			if(*(short*)0x800b5570 < 1)
			{
				MENUBOX_ClearInput();
				
				sdata->AkuAkuHintState = 0;
				sdata->boolDraw3D_AdvMask = 0;
				
				gGT->gameMode2 &= ~(VEH_FREEZE_DOOR);
				d->funcPtrs[0] = VehPhysProc_Driving_Init;
			}
		
			break;
	}
}