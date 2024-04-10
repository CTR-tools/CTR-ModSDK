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
		
		case 1: {
			int absSpeedApprox = d->speedApprox;
			if(absSpeedApprox < 0) absSpeedApprox = -absSpeedApprox;
			if(absSpeedApprox > 0x31) return;
			
			if((D232.maskWarppadBoolInterrupt & 1) == 0)
			{
				struct CameraDC* cdc = &gGT->cameraDC[0];
				
				cdc->driverOffset_CamEyePos[0] = D232.eyePos[0];
				cdc->driverOffset_CamEyePos[1] = D232.eyePos[1];
				cdc->driverOffset_CamEyePos[2] = D232.eyePos[2];
				
				cdc->driverOffset_CamLookAtPos[0] = D232.lookAtPos[0];
				cdc->driverOffset_CamLookAtPos[1] = D232.lookAtPos[1];
				cdc->driverOffset_CamLookAtPos[2] = D232.lookAtPos[2];
				
				cdc->flags |= 8;
				
				// === Naughty Dog Bug ===
				// ScratchpadStruct was allocated on stack memory,
				// instead of 0x1f800108, that's why FollowDriver
				// parameter is wrong, and why function allocates
				// 0x2d0 on $sp when MaskHint_Update starts
				
				#ifndef REBUILD_PS1
				
				// Get pos and rot, then set them as desired
				CAM_FollowDriver_AngleAxis(cdc,d,0x1f800108,pos,rot);
				CAM_SetDesiredPosRot(cdc,pos,rot);
				
				#else
					
				// temporary, until CAM_FollowDriver_Normal
				// and CAM_ThTick are implemented in PC port
				cdc->flags |= 0x800;
				
				// rigged result
				gGT->pushBuffer[0].pos[0] = 0xBDB0;
				gGT->pushBuffer[0].pos[1] = 0x84;
				gGT->pushBuffer[0].pos[2] = 0xFAFC;
				gGT->pushBuffer[0].rot[0] = 0x6e4;
				gGT->pushBuffer[0].rot[1] = 0xef4;
				gGT->pushBuffer[0].rot[2] = 0;
				#endif
			}
			
			D232.maskWarppadDelayFrames = FPS_DOUBLE(60);
			
			sdata->AkuAkuHintState++;
			} break;
		
		case 2:
		
			if (
				((D232.maskWarppadBoolInterrupt & 1) == 0) && 
				((gGT->cameraDC[0].flags & 0x800) == 0) &&
				(D232.maskSpawnFrame != FPS_DOUBLE(20))
			   ) 
			{
				return;
			}
			
			struct Instance* dInst = d->instSelf;
			
			#ifndef REBUILD_PS1
			CTR_MatrixToRot(rot, &dInst->matrix, 0x11);
			#else
			// Lucky enough, N Sanity Beach's first
			// mask hint, actually is 0,0,0
			rot[0] = 0;
			rot[1] = 0;
			rot[2] = 0;
			#endif
			
			// not a typo
			D232.maskCamRotStart[0] = rot[1] & 0xfff;
			D232.maskCamRotStart[2] = rot[2] & 0xfff;
			D232.maskCamRotStart[1] = rot[0] & 0xfff;
			
			D232.maskCamPosStart[0] = dInst->matrix.t[0];
			D232.maskCamPosStart[1] = dInst->matrix.t[1];
			D232.maskCamPosStart[2] = dInst->matrix.t[2];
			
			sdata->instMaskHints3D = DECOMP_VehTalkMask_Init();
			struct Instance* mhInst = sdata->instMaskHints3D;
			((struct MaskHint*)mhInst->thread->object)->scale = 0;
			
			DECOMP_AH_MaskHint_SetAnim(0);
			
			D232.maskFrameCurr = 0;
			
			sdata->AkuAkuHintState++;
			break;
			
		case 3:
		
			// first frame "whoosh" sound
			if(D232.maskFrameCurr == 0)
				DECOMP_OtherFX_Play_LowLevel(0x100,1,0xff8080);
			
			// if 3-second spawn, play more sounds
			if(D232.maskSpawnFrame == FPS_DOUBLE(0x5a))
			{
				if(D232.maskFrameCurr == FPS_DOUBLE(10))
					DECOMP_OtherFX_Play_LowLevel(0x100,0,0xd78a80);
			
				else if(D232.maskFrameCurr == FPS_DOUBLE(20))
					DECOMP_OtherFX_Play_LowLevel(0x100,1,0xaf9480);
			
				else if(D232.maskFrameCurr == FPS_DOUBLE(25))
					DECOMP_OtherFX_Play_LowLevel(0x100,0,0x879e80);
			
				else if(D232.maskFrameCurr == FPS_DOUBLE(30))
					DECOMP_OtherFX_Play_LowLevel(0x100,1,0x5fa880);
			}
			
			int timer4096 = 
				(D232.maskFrameCurr << 0xc) / D232.maskSpawnFrame;
				
			DECOMP_AH_MaskHint_SetAnim(timer4096);
			
			DECOMP_AH_MaskHint_SpawnParticles(
				3, &D232.emSet_maskSpawn[0], timer4096);
			
			// if not finished spawning
			if (D232.maskFrameCurr < D232.maskSpawnFrame)
			{
				D232.maskFrameCurr++;
				
				timer4096 = 
					(D232.maskFrameCurr << 0xc) / D232.maskSpawnFrame;
					
				DECOMP_AH_MaskHint_LerpVol(timer4096);
				break;
			}
			
			if (sdata->modelMaskHints3D != 0)
			{
				if(
					((D232.maskWarppadBoolInterrupt & 1) != 0) ||
					((gGT->cameraDC[0].flags & 0x800) != 0)
				  )
				{
					DECOMP_AH_MaskHint_LerpVol(0x1000);
					
					DECOMP_AH_MaskHint_SpawnParticles
						(0x18, &D232.emSet_maskLeave[0], 0x1000);
					
					DECOMP_VehTalkMask_PlayXA(
						sdata->modelMaskHints3D, 
						D232.maskHintID);
					
					if (
						((gGT->gameMode1 & ADVENTURE_ARENA) != 0) &&
						
						// Not "Welcome to Adventure" or "You need a Boss Key"
						(D232.maskHintID != 0) &&
						(D232.maskHintID != 0x18)
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
			
		case 4: {
			int lngIndex = 0;
			int boolFound = 0;
			short* ptrLngID = &D232.hintMenu_lngIndexArr[0];
			
			for(/**/; *ptrLngID > -1; ptrLngID++)
			{
				if (D232.maskHintID == (ptrLngID[0] - 0x17b)/2)
				{
					boolFound = 1;
					break;
				}
			}
			
			if(boolFound)
			{
				// === Cut Content? ===
				// Find LngIndex of subtitles, then dont use it,
				// and instead use generic "press start to repeat"
				
				#if 1
				
				// Code that shipped in 1999
				if(DECOMP_VehPickupItem_MaskBoolGoodGuy(d))
					lngIndex = 0x177;
				else
					lngIndex = 0x232;
				
				#else
				
				// Code that restores the effect,
				// ptrLngID[0]+0 - Title of Hint
				// ptrLngID[0]+1 - Words of Hint
				lngIndex = ptrLngID[0]+0;
				
				#endif
				
				RECT r;
				r.x = -10;
				r.y = 0xb0;
				r.w = 0x214;
				r.h = 8 + /* not a typo */
					DECOMP_DecalFont_DrawMultiLine(
						sdata->lngStrings[lngIndex],
						0x100,0xb4,400,2,0xffff8000);
						
				DECOMP_RECTMENU_DrawInnerRect(&r, 4, gGT->backBuffer->otMem.startPlusFour);
			}
			
			DECOMP_AH_MaskHint_SetAnim(0x1000);
		
			int bVar8;
			int uVar3 = D232.maskWarppadDelayFrames - 1;
			if (
					(
						(
							(D232.maskWarppadDelayFrames == 0) ||
							(
								bVar8 = D232.maskWarppadDelayFrames == 1, 
								D232.maskWarppadDelayFrames = uVar3, 
								bVar8
							)
						) &&
						(
							(
								(DECOMP_VehTalkMask_boolNoXA() != 0) ||
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
			} break;
			
		case 5:
		
			DECOMP_AH_MaskHint_SpawnParticles(20, &D232.emSet_maskLeave[0], 0x1000);
			
			// vanish sound
			DECOMP_OtherFX_Play(0x101, 1);
			
			DECOMP_VehTalkMask_End();
			
			if((D232.maskWarppadBoolInterrupt & 1) == 0)
			{
				// transition back to player
				gGT->cameraDC[0].flags |= 0x400;
			}
			
			sdata->AkuAkuHintState++;
			break;
			
		case 6:
		
			DECOMP_AH_MaskHint_LerpVol(0x1000 - gGT->cameraDC[0].unk8C);
			
			if(
				((gGT->cameraDC[0].flags & 0x200) == 0) ||
				((D232.maskWarppadBoolInterrupt & 1) != 0)
			)
			{
				DECOMP_AH_MaskHint_SetAnim(0);
				DECOMP_AH_MaskHint_LerpVol(0);
				
				D232.maskWarppadDelayFrames = 0;
				if((D232.maskWarppadBoolInterrupt & 1) != 0)
					D232.maskWarppadDelayFrames = FPS_DOUBLE(30);
				
				sdata->AkuAkuHintState++;
			}
			break;
		
		case 7:
		
			DECOMP_AH_MaskHint_LerpVol(0);
			
			D232.maskWarppadDelayFrames--;
			
			if(D232.maskWarppadDelayFrames < 1)
			{
				DECOMP_RECTMENU_ClearInput();
				
				sdata->AkuAkuHintState = 0;
				sdata->boolDraw3D_AdvMask = 0;
				
				gGT->gameMode2 &= ~(VEH_FREEZE_DOOR);
				d->funcPtrs[0] = DECOMP_VehPhysProc_Driving_Init;
			}
		
			#ifdef REBUILD_PS1
			// rigged, return camera to spawn pos.
			// temporary until camera can lerp back around
			
			int k = 0;
			gGT->pushBuffer[k].pos[0] = gGT->level1->DriverSpawn[k].pos[0];
			gGT->pushBuffer[k].pos[1] = gGT->level1->DriverSpawn[k].pos[1] + 0x20;
			gGT->pushBuffer[k].pos[2] = gGT->level1->DriverSpawn[k].pos[2];
						  
			gGT->pushBuffer[k].rot[0] = gGT->level1->DriverSpawn[k].rot[0] + 0x800;
			gGT->pushBuffer[k].rot[1] = gGT->level1->DriverSpawn[k].rot[1] - 0x400;
			gGT->pushBuffer[k].rot[2] = 0; // required
			
			// move backwards a little
			gGT->pushBuffer[k].pos[2] += (0xc0 * DECOMP_MATH_Cos(gGT->pushBuffer[k].rot[1])) >> 0xC;
			gGT->pushBuffer[k].pos[0] += (0xc0 * DECOMP_MATH_Sin(gGT->pushBuffer[k].rot[1])) >> 0xC;
			#endif
		
			break;
	}
}