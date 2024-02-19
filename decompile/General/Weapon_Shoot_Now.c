#include <common.h>

void RB_MovingExplosive_ThTick(struct Thread* t);
void RB_Hazard_ThCollide_Missile(struct Thread* t);
void RB_GenericMine_ThTick(struct Thread* t);
void RB_Hazard_ThCollide_Generic(struct Thread* t);

void DECOMP_Weapon_Shoot_Now(struct Driver* d, int weaponID, int flags)
{
	struct Instance* dInst;
	struct Thread* weaponTh;
	struct Instance* weaponInst;
	struct MineWeapon* mw;
	struct GameTracker* gGT = sdata->gGT;
	int modelID;
	
	switch(weaponID)
	{
		// Turbo
		case 0:
		
			int boost = 0x80;
			if(d->numWumpas >= 10)
				boost = 0x100;
			
			Turbo_Increment(d, 0x960, 9, boost);
			break;
			
		// Shared code for Bomb and Missile
		case 2:
			if(gGT->numMissiles >= 12)
				return;
			
			gGT->numMissiles++;
			d->numTimesMissileLaunched++;
			
			GAMEPAD_ShockFreq(d, 8, 0);
			GAMEPAD_ShockForce1(d, 8, 0x7f);
			
			struct Driver* victim =
				Weapon_Missile_GetTargetDriver(d);
				
			// if driver not found
			if(victim == 0)
			{
				// if not battle mode
				if((gGT->gameMode1 & 0x20) == 0)
				{
					if(gGT->elapsedEventTime & 1)
					{
						// if not DYNAMIC_PLAYER
						if(d->instSelf->thread->modelIndex != 0x18)
						{
							int rank = d->driverRank;
							if(rank != 0)
							{
								victim = gGT->driversInRaceOrder[rank-1];
							}
						}
					}
				}
				
				else
				{
					int closest = 0x7fffffff;
					
					for(int i = 0; i < 8; i++)
					{
						struct Driver* tempD = gGT->drivers[i];
						
						if(tempD == 0) continue;
						if(tempD == d) continue;
						if(tempD->invisibleTimer != 0) continue;
						if(tempD->kartState == KS_MASK_GRABBED) continue;
						if(tempD->BattleHUD.teamID == d->BattleHUD.teamID) continue;
						
						int distX = tempD->posCurr[0] - d->posCurr[0];
						int distZ = tempD->posCurr[2] - d->posCurr[2];
						distX = distX >> 8;
						distZ = distZ >> 8;
						
						int dist = distX*distX + distZ*distZ;
						if(dist < closest)
						{
							closest = dist;
							victim = tempD;
						}
					}
				}
			}
			
			dInst = d->instSelf;
			
			// set up missile
			modelID = 0x29;
			int bucket = TRACKING;
			struct Thread* parentTh = 0;
			
			// bomb
			if(
				(d->heldItemID == 1) ||
				(d->heldItemID == 10)
			  )
			{
				modelID = 0x3b;
				bucket = OTHER;
				parentTh = dInst->thread;
			}
			
			// medium stack pool
			weaponInst =
				INSTANCE_BirthWithThread(
					modelID, 0, MEDIUM, bucket, 
					RB_MovingExplosive_ThTick,
					sizeof(struct TrackerWeapon), 
					parentTh);
					
			// copy matrix
			*(int*)&weaponInst->matrix.m[0][0] = *(int*)&dInst->matrix.m[0][0];
			*(int*)&weaponInst->matrix.m[0][2] = *(int*)&dInst->matrix.m[0][2];
			*(int*)&weaponInst->matrix.m[1][1] = *(int*)&dInst->matrix.m[1][1];
			*(int*)&weaponInst->matrix.m[2][0] = *(int*)&dInst->matrix.m[2][0];
			weaponInst->matrix.m[2][2] = dInst->matrix.m[2][2];
			weaponInst->matrix.t[0] = dInst->matrix.t[0];
			weaponInst->matrix.t[1] = dInst->matrix.t[1];
			weaponInst->matrix.t[2] = dInst->matrix.t[2];
			
			Rot_AxisAngle(&weaponInst->matrix, &d->AxisAngle1_normalVec, d->rotCurr.y);
					
			weaponTh = weaponInst->thread;
			weaponTh->funcThDestroy = THREAD_DestroyTracker;
			weaponTh->funcThCollide = RB_Hazard_ThCollide_Missile;
			
			struct TrackerWeapon* tw = weaponTh->object;
			tw->flags = 0;
			tw->unk54 = 0;
			tw->audioPtr = 0;
			tw->timeAlive = 0;
			tw->driverParent = d;
			tw->driverTarget = victim;
			tw->instParent = dInst;
			
			int talk;
			
			// bomb
			if(modelID == 0x3b)
			{
				talk = 10;
				d->instBombThrow = weaponInst;
				
				CTR_MatrixToRot(&tw->dir, &weaponInst->matrix, 0x11);
				PlaySound3D(0x47, weaponInst);
			}
			
			// missile
			else
			{
				talk = 11;
				
				if(victim != 0)
					if(victim->thTrackingMe == 0)
						victim->thTrackingMe = 
							RB_GetThread_ClosestTracker(victim);
				
				PlaySound3D(0x4a, weaponInst);
			}
			
			// if human and not AI
			if((d->actionsFlagSet & 0x100000) == 0)
			{
				Voiceline_RequestPlay(talk, data.characterIDs[d->driverID], 0x10);
			}
			
			tw->vel[1] = 0;
			tw->rotY = d->rotCurr.y;
			
			tw->vel[0] = weaponInst->matrix.m[0][2] >> FPS_RIGHTSHIFT(7);
			tw->vel[2] = weaponInst->matrix.m[2][2] >> FPS_RIGHTSHIFT(7);
			
			if(d->numWumpas >= 10)
			{
				tw->flags |= 1;
			}
			
			// bomb
			if(modelID == 0x3b)
			{					
				struct GamepadBuffer* gb =
					&sdata->gGamepads[d->driverID].gamepad;
				
				if(
					// hold d-pad DOWN
					((gb->buttonsHeldCurrFrame & BTN_DOWN) != 0) ||
					
					// pinstripe
					((flags & 2) != 0)
				  )
				{
					tw->flags |= 0x20;
					
					tw->vel[0] = (((tw->vel[0] / 2) * 3) / 5);
					tw->vel[2] = (((tw->vel[2] / 2) * 3) / 5);
				}
			}
			
			// missile
			else
			{
				if(d->numWumpas < 10)
				{
					tw->vel[0] /= 2;
					tw->vel[2] /= 2;
				}
			}
			
			tw->frameCount_DontHurtParent = FPS_DOUBLE(60);
			tw->unk22 = 0;
			break;
		
		// TNT/Nitro
		case 3:
		
			// tnt or nitro
			modelID = 0x27;
			if(d->numWumpas >= 10)
				modelID = 6;
			
			weaponInst =
				INSTANCE_BirthWithThread(
					modelID, 0, SMALL, MINE, 
					RB_GenericMine_ThTick,
					sizeof(struct MineWeapon), 
					0);
					
			dInst = d->instSelf;
			d->instTntSend = weaponInst;
					
			// copy matrix
			*(int*)&weaponInst->matrix.m[0][0] = *(int*)&dInst->matrix.m[0][0];
			*(int*)&weaponInst->matrix.m[0][2] = *(int*)&dInst->matrix.m[0][2];
			*(int*)&weaponInst->matrix.m[1][1] = *(int*)&dInst->matrix.m[1][1];
			*(int*)&weaponInst->matrix.m[2][0] = *(int*)&dInst->matrix.m[2][0];
			weaponInst->matrix.m[2][2] = dInst->matrix.m[2][2];
			weaponInst->matrix.t[0] = dInst->matrix.t[0];
			weaponInst->matrix.t[1] = dInst->matrix.t[1];
			weaponInst->matrix.t[2] = dInst->matrix.t[2];
			
			weaponInst->scale[0] = 0;
			weaponInst->scale[1] = 0;
			weaponInst->scale[2] = 0;
			
			weaponTh = weaponInst->thread;
			weaponTh->funcThDestroy = THREAD_DestroyInstance;
			weaponTh->funcThCollide = RB_Hazard_ThCollide_Generic;
			
			PlaySound3D(0x52, weaponInst);
			
			// if human and not AI
			if((d->actionsFlagSet & 0x100000) == 0)
			{
				Voiceline_RequestPlay(0xf, data.characterIDs[d->driverID], 0x10);
			}

			mw = weaponTh->object;
			mw->driverTarget = 0;
			mw->instParent = dInst;
			mw->crateInst = 0;
			*(int*)&mw->velocity[0] = 0;
			*(int*)&mw->velocity[2] = 0;
			mw->boolDestroyed = 0;
			mw->frameCount_DontHurtParent = FPS_DOUBLE(10);
			mw->tntSpinY = 0;
			mw->extraFlags = 0;
			
			RB_MinePool_Add(mw);
			Weapon_Potion_Throw(mw, weaponInst, flags);
			
RunMineCOLL:
			
			int pos1[3];
			int pos2[3];
			
			pos1[0] = weaponInst->matrix.t[0];
			pos1[1] = weaponInst->matrix.t[1] - 400;
			pos1[2] = weaponInst->matrix.t[2];
			
			pos2[0] = weaponInst->matrix.t[0];
			pos2[1] = weaponInst->matrix.t[1] + 64;
			pos2[2] = weaponInst->matrix.t[2];
			
			struct ScratchpadStruct *sps = 0x1f800108;
			
			sps->Union.QuadBlockColl.searchFlags = 0x1000;
			sps->Union.QuadBlockColl.unk28 = 0;
			
			sps->Union.QuadBlockColl.unk22 = 1;
			if(gGT->numPlyrCurrGame < 3)
				sps->Union.QuadBlockColl.unk22 = 3;
			
			sps->ptr_mesh_info = gGT->level1->ptr_mesh_info;
			
			COLL_SearchTree_FindQuadblock_Touching(pos1, pos2, sps, 0x40);
			
			if(sps->boolDidTouchHitbox != 0)
			{
				sps->Input1.modelID = (weaponInst->model->id) | 0x8000;
				
				RB_Hazard_CollLevInst(sps, weaponTh);
				
				struct InstDef* instDef = sps->bspHitbox->data.hitbox.instDef;
				
				int modelTouched = instDef->modelID;
				
				// fruit crate or weapon crate
				if(
					(modelTouched == 7) ||
					(modelTouched == 8)
				  )
				{
					mw->crateInst = instDef->ptrInstance;
				}
				
				else
				{
					RB_GenericMine_ThDestroy(weaponTh, weaponInst, mw);
				}
				
				sps->Union.QuadBlockColl.unk22 = 0;
				COLL_SearchTree_FindQuadblock_Touching(pos1, pos2, sps, 0);
			}
			
			RB_MakeInstanceReflective(sps, weaponInst);
			
			short* rotPtr = 0x1f800178;
			
			if(sps->boolDidTouchQuadblock == 0)
			{
				rotPtr[0] = 0;
				rotPtr[1] = 0x1000;
				rotPtr[2] = 0;
				
				mw->stopFallAtY = weaponInst->matrix.t[1];
			}
			
			else
			{
				mw->stopFallAtY = sps->Union.QuadBlockColl.hitPos[1];
			}
			
			Rot_AxisAngle(&weaponInst->matrix, rotPtr, d->angle);
			
			d->actionsFlagSet |= 0x80000000;
			
			if(flags == 0)
			{
				RB_Follower_Init(d, weaponTh);
			}
			break;
		
		// Beaker
		case 4:
		
			modelID = 0x47;
			if(d->numWumpas >= 10)
				modelID = 0x46;
			
			weaponInst =
				INSTANCE_BirthWithThread(
					modelID, 0, SMALL, MINE, 
					RB_GenericMine_ThTick,
					sizeof(struct MineWeapon), 
					0);
					
			dInst = d->instSelf;
					
			// copy matrix
			*(int*)&weaponInst->matrix.m[0][0] = *(int*)&dInst->matrix.m[0][0];
			*(int*)&weaponInst->matrix.m[0][2] = *(int*)&dInst->matrix.m[0][2];
			*(int*)&weaponInst->matrix.m[1][1] = *(int*)&dInst->matrix.m[1][1];
			*(int*)&weaponInst->matrix.m[2][0] = *(int*)&dInst->matrix.m[2][0];
			weaponInst->matrix.m[2][2] = dInst->matrix.m[2][2];
			weaponInst->matrix.t[0] = dInst->matrix.t[0];
			weaponInst->matrix.t[1] = dInst->matrix.t[1];
			weaponInst->matrix.t[2] = dInst->matrix.t[2];
			
			// potion always faces camera
			weaponInst->model->headers[0].flags |= 2;
			
			weaponTh = weaponInst->thread;
			weaponTh->funcThDestroy = THREAD_DestroyInstance;
			weaponTh->funcThCollide = RB_Hazard_ThCollide_Generic;
			
			PlaySound3D(0x52, weaponInst);
			
			// if human and not AI
			if((d->actionsFlagSet & 0x100000) == 0)
			{
				Voiceline_RequestPlay(0xf, data.characterIDs[d->driverID], 0x10);
			}
			
			mw = weaponTh->object;
			mw->instParent = dInst;
			mw->boolDestroyed = 0;
			mw->frameCount_DontHurtParent = FPS_DOUBLE(10);
			mw->extraFlags = (modelID == 0x46);
						
			struct GamepadBuffer* gb =
				&sdata->gGamepads[d->driverID].gamepad;
			
			// throw potion forward
			if ((gb->buttonsHeldCurrFrame & BTN_UP) != 0)
				flags |= 4;
			
			RB_MinePool_Add(mw);
			int ret = Weapon_Potion_Throw(mw, weaponInst, flags);
		
			if(ret == 0)
			{
				// similar to TNT, but
				// if Weapon_Potion_Throw == 0?
				weaponInst->scale[0] = 0;
				weaponInst->scale[1] = 0;
				weaponInst->scale[2] = 0;	
			
				// similar to TNT, but
				// If Weapon_Potion_Throw == 0?
				*(int*)&mw->velocity[0] = 0;
				*(int*)&mw->velocity[2] = 0;
				
				goto RunMineCOLL;
			}
			break;
		
		// Shield Bubble
		case 6:
		
		
		// Mask
		case 7:
			Weapon_Mask_UseWeapon(d, 1);
			break;
		
		// Clock
		case 8:
		
		
		// Warpball
		case 9:
		
		
		// invisibility
		case 0xc:
		
			if(d->invisibleTimer == 0)
			{
				d->instFlagsBackup = d->instSelf->flags;
				
				d->instSelf->flags =
				(d->instSelf->flags & 0xfff8ffff) | 0x60000;
				
				OtherFX_Play(0x61, 1);
			}
		
			int time = 0x1e00;
			if(d->numWumpas >= 10)
				time = 0x2d00;
			
			d->invisibleTimer = time;
			break;
		
		
		// Super Engine
		case 0xd:
		
			int engine = 0x1e00;
			if(d->numWumpas >= 10)
				engine = 0x2d00;
			
			d->superEngineTimer = engine;
			break;
	}
}