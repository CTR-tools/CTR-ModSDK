u_int FUN_8005fb4c(struct Driver* driver)
{
	int iVar1;
	u_int uVar2;
	u_int uVar3;
	u_int uVar4;
	u_int uVar5;
	short speedApprox;

	// speed
	speedApprox = driver->speedApprox;

	// erase accel X,Y
	driver->accelXYZ[0] = 0;
	driver->accelXYZ[1] = 0;
	
	if (speedApprox < 0) speedApprox = -speedApprox;

	// low speed (useless? shoould just be '= 0;')
	uVar2 = (speedApprox < 0x301);

	// erase accel Z
	driver->accelXYZ[2] = 0;

	if
	(
		// high speed
		(speedApprox >= 0x301) &&

		(
			// high speed
			uVar2 = 1,

			// if not crashing
			driver->kartState != 1
		)
	)
	{
		// check if driver is in warppad
		uVar2 = driver->actionsFlagSet & 0x4000;

		if
		(
			// if driver is not being warped
			(uVar2 == 0) &&
			(
				(
					(
						// if driver is on quadblock
						uVar2 = driver->actionsFlagSet & 1,

						driver->unknownCollision == 0 &&

						// if driver is on quadblock
						(uVar2 != 0)
					)
					&&
					(
						// driver -> terrain meta -> ???
						// 0x100 for everything except:
						// 0x000 for "ice" and "none" (mid-air)
						uVar2 = driver->terrainMeta1->const_0x100,

						// not on ice, not mid-air
						uVar2 != 0
					)
				)
			)
		)
		{

			uVar4 = (int)driver->unknownDimension2Curr - (int)driver->unknownDImension2Prev;

			// kart angle cap from 'straight to camera'
			uVar3 = (u_int)driver->unk457;

			if ((int)uVar3 < (int)uVar4)
			{
				uVar4 = uVar3;
			}
			if ((int)uVar4 < (int)-uVar3)
			{
				uVar4 = -uVar3;
			}

			// approximate trigonometry
			iVar1 = Data.trigApprox[(uVar4 & 0x3ff)];

			if ((uVar4 & 0x400) == 0)
			{
				iVar1 = iVar1 << 0x10;
			}
			iVar1 = iVar1 >> 0x10;
			if ((uVar4 & 0x800) != 0)
			{
				iVar1 = -iVar1;
			}

			// before this function is called, there is always
			// gte_SetRotMatrix, AxisAngle, driver -> 0x310

			uVar2 = ((int)(uVar2 * -8000) >> 8) * iVar1 >> 0xc & 0xffff;
			gte_ldVXY0(uVar2);
			gte_ldVZ0(0);
			gte_rtv0();
		
			// new acceleration vector
		
			uVar5 = gte_stMAC1();
			driver->accelXYZ[0] = (short)uVar5;
			uVar5 = gte_stMAC2();
			driver->accelXYZ[1] = (short)uVar5;
			uVar5 = gte_stMAC3();
			driver->accelXYZ[2] = (short)uVar5;
		}
	}

	// does not really "return" anything, it just
	// sees something in r2 and assumes. Stupid ghidra
	return uVar2;
}