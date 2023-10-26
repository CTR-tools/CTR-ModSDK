#include <common.h>

void DECOMP_MainFrame_VisMemFullFrame(struct GameTracker* gGT, struct Level* level)
{
	int visSrc;
	int dest;
	int iVar7;
	struct PVS * pvs;
	struct QuadBlock* qb;
	struct CameraDC* camDC;
	struct Driver* driver;

	if
	(
		(
			// called VISMEM in prototypes
			(gGT->visMem1 != 0) &&

			// if lev exists
			(level != 0)
		) &&
		(
			// if numPlyrCurrGame is not zero
			gGT->numPlyrCurrGame != 0
		)
	)
	{
		// loop through all four cameras
		for(char i = 0; i < gGT->numPlyrCurrGame; i++)
		{
			// CameraDC
			camDC = gGT->CameraDC[i];

			// pointer to structure of each player
			driver = gGT->drivers[i];

			// remove flag 0x4000
			camDC->flags &= ~(0x4000);

			visSrc = camDC->visLeafSrc[i];

			// if camera can't figure out what to draw on it's own,
			// if not following warpball path like track select videos,
			if (visSrc == 0)
			{
				if
				(
					(
						// driver -> quadblock under driver
						(driver->underDriver != NULL) &&

						(pvs = driver->underDriver->pvs, pvs != NULL)
					) &&

					// pull vismem data from quadblock + 0x44
					(visSrc = pvs->visLeafSrc[i], visSrc != NULL)
				)
				{
					gGT->visMem1->visLeafSrc[i] = visSrc;

					if ((visSrc & 1) == 0) goto LAB_80035900;
				
				LAB_800358e0:
					// copy until nullptr
					FUN_80021da0(
						gGT->visMem1->visLeafList[i],
						visSrc & ~(1 | 2)
					);
				}
			}

			// if camera can figure out what to draw on it's own,
			// if following warpball path like track select videos,
			else
			{
				// if this changed from previous frame
				if (gGT->visMem1->visLeafSrc[i] != visSrc)
				{
					gGT->visMem1->visLeafSrc[i] = visSrc;

					// if size is not specified
					if ((visSrc & 1) != 0) goto LAB_800358e0;
					
				LAB_80035900:

					// called VISMEM in prototypes
					memcpy
					(
						// destination
						// VisMem 0x0-0xF
						gGT->visMem1->visLeafList[i],

						// source
						visSrc,

						// unk size
						// get number of bits
						// lw a2 0x1c(s6) (CameraDC->0x1C)
						
						// get number of ints
						// addiu a2, 1F
						// sra a2, 5
						
						// get number of bytes
						// sll a2, 2
					);
				}
			}

			visSrc = camDC->visFaceSrc[i];

			// if camera can't figure out what to draw on it's own,
			// if not following warpball path like track select videos,
			if (visSrc == 0)
			{
				if
				(
					(
						// driver -> quadblock under driver
						(driver->underDriver != 0) &&

						(
							pvs = driver->underDriver->pvs,
							pvs != 0
						)
					) &&

					(visSrc = pvs->visFaceSrc[i], visSrc != 0)
				)
				{
					// if camDC->visFaceSrc is nullptr,
					// take from quadblock->0x44
					
					// VisMem 0x50-0x5F
					gGT->visMem1->visFaceSrc[i] = visSrc;

					if ((visSrc & 1) == 0)
					{
						// called VISMEM in prototypes
						memcpy
						(
							gGT->visMem1->visLeafList[i],
							visSrc,
							// unk size
						);
					}
					else 
					{
						// copy until nullptr
						FUN_80021da0(
							gGT->visMem1->visFaceList[i],
							visSrc & 0xfffffffc
						);
					}
				}
			}

			// if camera can figure out what to draw on it's own,
			// if following warpball path like track select videos,
			else
			{
				// if this changed from the previous frame
				if (gGT->visMem1->visFaceSrc[i] != visSrc)
				{
					gGT->visMem1->visFaceSrc[i] = visSrc;

					if ((visSrc & 1) == 0)
					{
						memcpy
						(
							gGT->visMem1->visFaceList[i],
					
							visSrc,
							// unk size
						);
					}
					else
					{
						// copy until nullptr
						FUN_80021da0(
							gGT->visMem1->visFaceList[i],
							visSrc & 0xfffffffc
						);
					}

					// quadblock under driver
					qb = driver->underDriver;

					if
					(
						((qb == NULL) || (pvs = qb->pvs, pvs == NULL)) ||
						
							(
								pvs->visLeafSrc[i] == NULL ||
								
								(
									(
										(pvs->visFaceSrc[i] == 0 || (pvs->visInstSrc[i] == NULL)) ||

										// LEV -> mesh_info -> ptrQuadBlockArray
										(iVar7 = ((int)qb - gGT->level1->ptr_mesh_info->ptrQuadBlockArray) * -0x1642c859,

										(*(u_int* )((iVar7 >> 7) * 4 + gGT->visMem1->visFaceList[i]) & 1 << (iVar7 >> 2 & 0x1fU)) != 0)
									)
								)
							)
						)
					{
						cameraDC->flags &= ~(0x2000);
					}

					else
					{
						// camera is moving on path, not followinig driver
						camDC->flags |= 0x2000;
					}

					// if driver quadblock is wall, therefore need to improvise?
					if ((camDC->flags & 0x2000) != 0)
					{
						FUN_80035684(gGT, i);
						camDC->flags |= 0x4000;
					}
				}
			}

			if ((camDC->flags & 0x5000) == 0x1000)
			{
				// param1 is PTR_DAT_8008d2ac
				// i is screen ID (0, 1, 2, 3)
				FUN_80035684(gGT, i);
			}

			if
			(
				(
					// if camera is following driver "normally"
					(camDC->cameraMode == 0) &&
					// and not wall
					((camDC->flags & 0x2000) != 0)
				) &&
				(
					(
						// quadblock under driver
						driver->underDriver != NULL &&

						(
							// driver -> quadblock -> ptr_add_tex
							(pvs = driver->underDriver->pvs, pvs != 0 &&

							(visSrc = pvs->visInstSrc[i], visSrc != 0))
						)
					)
				)
			)
			{
				// CameraDC 0x28
				// which instances are visible
				camDC->visInstSrc[i] = visSrc;
			}

			visSrc = camDC->visOVertSrc[i];

			// if no animated vertices
			if ((level->configFlags & 4) == 0)
			{

				if (gGT->visMem1->visOVertSrc[i] == visSrc)
				{
					if (gGT->visMem1->visOVertSrc[i] == NULL) goto LAB_80035ce0;
				}

				// if change since last frame
				else
				{
					gGT->visMem1->visOVertSrc[i] = visSrc;
					dest = gGT->visMem1->visOVertList[i];

					if ((visSrc & 1) == 0) goto LAB_80035ce0;
LAB_80035c98:
					// copy until nullptr
					FUN_80021da0(dest, visSrc & 0xfffffffc);
				}
			}
		
			// if animated lev vertices
			else
			{
				visSrc = camDC->visSCVertSrc[i];

				// CameraDC 0x30
				if (gGT->visMem1->visSCVertSrc[i] == visSrc)
				{
					if (gGT->visMem1->visSCVertSrc[i] != 0) continue;
				}

				// if change since previous frame
				else
				{
					gGT->visMem1->visSCVertSrc[i] = visSrc;

					if ((visSrc & 1) != 0)
					{
						dest = gGT->visMem1->visSCVertList[i];
						goto LAB_80035c98;
					}
				}
LAB_80035ce0:
				memcpy
				(
					dest,
					// camDC offset 0x2c or 0x30
					// unk size
				);
			}
		}
	}
}