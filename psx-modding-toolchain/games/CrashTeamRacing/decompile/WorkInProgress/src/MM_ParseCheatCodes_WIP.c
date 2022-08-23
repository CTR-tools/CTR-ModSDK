#include "../../../common.h"

void MM_ParseCheatCodes()
{
	int loopIndex;
	int arrayIndex;
	int iVar3;
	u_int *puVar4;
	bool cheatEntered;
	int *cheatPointer;
	
	// If you are "holding" L1 + R1 at the same time
	if
	(
		((sdata.PtrGamepadSystem->controller[0].buttonsHeldCurrFrame & 0xc00) == 0xc00) &&
		(
			arrayIndex = 9, 
		
			// if you are "tapping" something other than L1 or R1
			sdata.PtrGamepadSystem->controller[0].buttonsTapped != 0
		)
	) 
	{
		// for int i = 9; i < 0; i--
		do 
		{
			// reduce index you are reading from
			loopIndex = arrayIndex--;
		
			// DAT_800b4d04 holds the array of button pressed
			// that are used to determine if cheat codes are entered
		
			// move each byte in an array, by one index
			(&DAT_800b4d04)[arrayIndex] = (&DAT_800b4d04)[loopIndex];
		
			// reduce index you are writing to
			arrayIndex = loopIndex;
		
		} while (0 < loopIndex);
	
		// 800b48e4 is Pointer to array of "Cheats"
	
		// Each "Cheat" is 48 (0x30) bytes large
		// First 4-bytes, length of cheat
		// Then an array of button inputs for the cheat, 4 bytes per button input
		// Then a bunch of zeros
		// Last 4 bytes are the address of the function that the cheat calls
	
		// First cheat is SOAR for Spyro
		// Next cheat is SEEDS for Wumpa, etc
	
		cheatPointer = &DAT_800b48e4;
	
		// save the button you tapped into the array
		DAT_800b4d04 = sdata.PtrGamepadSystem->controller[0].buttonsTapped;
	
		// offset of bytes into array of cheats
		// (cheat index * 0x30)
		arrayIndex = 0;
	
		// loop through all 48-byte cheats, first cheat starts at 0x800b48e4,
		// you'll know you're done when you reach 0x800b4d04, where user input is stored
	
		// for cheatPointer = 0x800b48e4; cheatPointer < 800b4d04; cheatPointer += 12*4 (48 bytes)
		do 
		{
			// get the length of the cheat that you "might" have entered
			loopIndex = *cheatPointer + -1;
		
			// by default, assume you entered a valid cheat
			cheatEntered = true;
		
			// if the cheat has a valid length
			if (-1 < loopIndex) 
			{
				// number of bytes in cheat (cheat length * 4)
				// plus the cheat index * 0x30
				iVar3 = loopIndex * 4 + arrayIndex;
		
				// pointer to start of button array that User entered
				puVar4 = &DAT_800b4d04;
		
				// check to see if the array of cheat buttons in this 0x30 cheat buffer
				// matches the array of cheat buttons that the player entered with L1 + R1
				do 
				{
					// If you failed to enter this cheat,
					// end this iteration of the loop
					if (!cheatEntered) goto LAB_800acfc4;
			
					// 0x800B48E8 is the pointer to array of 48-byte cheats, plus 4,
					// so this is the pointer to the array of buttons in the first cheat
		
					// If the button you entered does NOT match the button in the cheat array
		
													// 0x800B48E8
					if ((*puVar4 & *(u_int *)(iVar3 + -0x7ff4b718)) == 0) 
					{
						// you failed to enter this particular cheat
						cheatEntered = false;
					}
			
					// check the next button in the cheat
					iVar3 = iVar3 + -4;
			
					// decrease length
					loopIndex = loopIndex + -1;
			
					// check the next button you pressed
					puVar4 = puVar4 + 1;
			
				} while (-1 < loopIndex);
		
			}
		
			if
			(
				// If all the buttons in this cheat were pressed
				(cheatEntered) && 
			
				// If this cheat code's function pointer is not nullptr
				((code *)cheatPointer[0xb] != (code *)0x0)
			) 
			{
				// execute the cheat code function
				(*(code *)cheatPointer[0xb])();
			}
		
LAB_800acfc4:

			// Increment pointer by 12 ints, which is 48 bytes
			cheatPointer = cheatPointer + 0xc;
		
			// increment address by 0x30 (48) bytes
			arrayIndex = arrayIndex + 0x30;
		
			// Loop through all cheats to see if 
			// you entered any of them correctly
		
		} while (cheatPointer < &DAT_800b4d04);
	}
	return;
}