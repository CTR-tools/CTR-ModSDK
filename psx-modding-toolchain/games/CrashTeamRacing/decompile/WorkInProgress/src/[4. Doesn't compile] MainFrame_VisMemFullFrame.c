#include <common.h>

void DECOMP_MainFrame_VisMemFullFrame(struct GameTracker* gGT, struct Level* level)
{
	void* ptr_add_tex;
	void* unk20;
	void* iVar3;
	u_int uVar4;
	void* uVar5;
	struct cameraDC* cameraDC;
	int iVar7;
	struct Driver* driver;
	int i;

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
		for(i = 0; i < numPlyrCurrGame; i++)
		{
			// CameraDC
			cameraDC = gGT->cameraDC[i];

			// pointer to structure of each player
			driver = gGT->drivers[i];

			// CameraDC 0x20 (vismem->0x40)
			unk20 = cameraDC->unk20;

			// remove flag 0x4000
			cameraDC->flags &= 0xffffbfff;

			// if camera can't figure out what to draw on it's own,
			// if not following warpball path like track select videos,
			if (unk20 == 0)
			{
				if
				(
					(
						// driver -> quadblock under driver
						(driver->underDriver != 0) &&

						// quadblock -> ptr_add_tex
						(ptr_add_tex = driver->underDriver->ptr_add_tex, ptr_add_tex != 0)
					) &&

					// pull vismem data from quadblock + 0x44
					(unk20 = ptr_add_tex->0x0, unk20 != 0)
				)
				{
					// if cameraDC->0x20 is nullptr,
					// grab from quadblock->0x440->0x0
					
					// VisMem 0x40-0x4F
					gGT->visMem1->array4[i] = unk20;

					// quadblock -> ptr_add_tex -> 0x0
					uVar5 = driver->underDriver->ptr_add_tex->0x0;

					if ((uVar5 & 1) == 0) goto LAB_80035900;
LAB_800358e0:
					// copy until nullptr
					FUN_80021da0
					(
						// VisMem 0x0-0xF
						gGT->visMem1->VisDataLeaf_Bit_Visibility[i],
						uVar5 & 0xfffffffc
					);
				}
			}

			// if camera can figure out what to draw on it's own,
			// if following warpball path like track select videos,
			else
			{
				// VisMem 0x40-0x4F
				iVar3 = gGT->visMem1;

				// if this changed from previous frame
				if (iVar3->array4[i] != unk20)
				{
					iVar3->array4[i] = unk20;

					// CameraDC 0x20
					uVar5 = cameraDC->unk20;

					// if size is not specified
					if ((uVar5 & 1) != 0) goto LAB_800358e0;
LAB_80035900:

					// called VISMEM in prototypes
					memcpy
					(
						// destination
						// VisMem 0x0-0xF
						gGT->visMem1->VisDataLeaf_Bit_Visibility[i],

						// source
						uVar5,

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

			// CameraDC 0x24
			unk20 = cameraDC->unk24;

			// if camera can't figure out what to draw on it's own,
			// if not following warpball path like track select videos,
			if (unk20 == 0)
			{
				if
				(
					(
						// driver -> quadblock under driver
						(driver->underDriver != 0) &&

						(
							// quadblock -> ptr_add_tex
							unk20 = driver->underDriver->ptr_add_tex,
							unk20 != 0
						)
					) &&

					(unk20 = unk20->0x4, unk20 != 0)
				)
				{
					// if camDC->0x24 is nullptr,
					// take from quadblock->0x44->0x4
					
					// VisMem 0x50-0x5F
					gGT->visMem1->array5[i] = unk20;

					// quadblock -> ptr_add_tex -> 0x4
					uVar5 = driver->underDriver->ptr_add_tex->0x4;

					if ((uVar5 & 1) == 0)
					{
						// called VISMEM in prototypes
						memcpy
						(
							// VisMem 0x0-0xF
							gGT->visMem1->VisDataLeaf_Bit_Visibility[i],
							uVar5,
							// unk size
						);
					}
					else 
					{
						// VisMem 0x10-0x1F
						// copy until nullptr
						FUN_80021da0
						(
							gGT->visMem1->QuadBlock_Bit_Visibility[i],
							uVar5 & 0xfffffffc
						);
					}
				}
			}

			// if camera can figure out what to draw on it's own,
			// if following warpball path like track select videos,
			else
			{
				// VisMem 0x50-0x5F
				iVar3 = gGT->visMem1;

				// if this changed from the previous frame
				if ((void*)((int)iVar3->0x50[i]) != unk20)
				{
					(void*)((int)iVar3->0x50[i]) = unk20;

					// CameraDC 0x24
					if ((cameraDC->unk24 & 1) == 0)
					{
						memcpy
						(
							// VisMem 0x10-0x1F
							gGT->visMem1->QuadBlock_Bit_Visibility[i]
					
							cameraDC->unk24,
							// unk size
						);
					}

					else
					{
						// copy until nullptr
						FUN_80021da0
						(

							// VisMem 0x10-0x1F
							gGT->visMem1->QuadBlock_Bit_Visibility[i],

							// CameraDC 0x24
							cameraDC->unk24 & 0xfffffffc
						);
					}

					// quadblock under driver
					unk20 = driver->underDriver;

					if
					(
						// if no quadblock exists, or quadblock -> ptr_add_tex does not exist
						((unk20 == 0) || (ptr_add_tex = unk20->ptr_add_tex, ptr_add_tex == 0)) ||
						(
							// data from quadblock -> ptr_add_tex is invalid
							(
								ptr_add_tex->0x0 == 0 ||
								
								(
									(
										(ptr_add_tex->0x4 == 0 || (ptr_add_tex->0x8 == 0)) ||

										// LEV -> mesh_info -> ptrQuadBlockArray
										(unk20 = (unk20 - gGT->level1->ptr_mesh_info->ptrQuadBlockArray) * -0x1642c859,

										// VisMem 0x10-0x1F
										(*(u_int* )((unk20 >> 7) * 4 + gGT->visMem1->QuadBlock_Bit_Visibility[i]) &
										1 << (unk20 >> 2 & 0x1fU)) != 0)
									)
								)
							)
						)
					)
					{
						uVar5 = cameraDC->flags & 0xffffdfff;
					}

					else
					{
						// camera is moving on path, not followinig driver
						uVar5 = cameraDC->flags | 0x2000;
					}

					cameraDC->flags = uVar5;

					// if driver quadblock is wall, therefore need to improvise?
					if ((cameraDC->flags & 0x2000) != 0)
					{
						// param1 is PTR_DAT_8008d2ac
						// i is screen ID (0, 1, 2, 3)
						FUN_80035684(gGT, i);
						cameraDC->flags = cameraDC->flags | 0x4000;
					}
				}
			}

			if ((cameraDC->flags & 0x5000) == 0x1000)
			{
				// param1 is PTR_DAT_8008d2ac
				// i is screen ID (0, 1, 2, 3)
				FUN_80035684(gGT, i);
			}

			if
			(
				(
					// if camera is following driver "normally"
					(cameraDC->cameraMode == 0) &&
					// and not wall
					((cameraDC->flags & 0x2000) != 0)
				) &&
				(
					(
						// quadblock under driver
						driver->underDriver != 0 &&

						(
							// driver -> quadblock -> ptr_add_tex
							(unk20 = driver->underDriver->ptr_add_tex, unk20 != 0 &&

							(unk20 = unk20->0x8, unk20 != 0))
						)
					)
				)
			)
			{
				// quadblock->0x44->0x8
		
				// CameraDC 0x28
				// which instances are visible
				cameraDC->unk28 = unk20;
			}
		
			// if no animated vertices
			if ((level->configFlags & 4) == 0)
			{
				// VisMem 0x60-0x6F
				unk20 = gGT->visMem1;
				driver = unk20->0x60[i];

				// CameraDC 0x2C
				if (driver == cameraDC->unk2c)
				{
					if (driver == 0) goto LAB_80035ce0;
				}

				// if change since last frame
				else
				{
					// camera 0x2C
					unk20->0x60[i] = cameraDC->unk2c;

					uVar5 = cameraDC->unk2c;

					if ((uVar5 & 1) == 0) goto LAB_80035ce0;

					// VisMem 0x20-0x2F (visOVertList)
					uVar4 = gGT->visMem1->Water_Bit_Visibility[i];
LAB_80035c98:
					// copy until nullptr
					FUN_80021da0(uVar4, uVar5 & 0xfffffffc);
				}
			}
		
			// if animated lev vertices
			else
			{
				// VisMem 0x0-0xF
				unk20 = gGT->visMem1->VisDataLeaf_Bit_Visibility[i];
				driver = unk20->0x70;

				// CameraDC 0x30
				if (driver == cameraDC->unk30)
				{
					if (driver != 0) continue;
				}

				// if change since previous frame
				else
				{
					// VisMem + playerIndex*4 + 0x70 = CameraDC 0x30
					unk20->0x70[playerIndex] = cameraDC->unk30;
					uVar5 = cameraDC->unk30;

					if ((uVar5 & 1) != 0)
					{
						// VisMem 0x30-0x3F
						uVar4 = gGT->visMem1->AnimatedVertex_Bit_Visibility[i];
						goto LAB_80035c98;
					}
				}
LAB_80035ce0:
				memcpy
				(
					uVar4,
					// camDC offset 0x2c or 0x30
					// unk size
				);
			}
		}
	}
	return;
}