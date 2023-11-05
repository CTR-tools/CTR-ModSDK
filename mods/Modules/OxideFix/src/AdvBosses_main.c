#include <common.h>

void CS_Garage_Init();

void AdvBosses_HookGarageUI()
{
	int buttonTap;

	// does not work in sep3,
	// works in all other builds
	#define CharID *(char*)(CS_Garage_Init + 0x80)

	// if Crash selected
	if(sdata->advCharSelectIndex_curr == 0)
	{
		// button
		buttonTap = sdata->gGamepads->
						gamepad[0].buttonsTapped;

		// left
		if((buttonTap & BTN_L1) == BTN_L1)
		{
			// decrease
			CharID = (CharID - 1) & 0xf;
		}

		// right
		else if((buttonTap & BTN_R1) == BTN_R1)
		{
			// increase
			CharID = (CharID + 1) & 0xf;
		}

		DecalFont_DrawLine
		(
			"PRESS L1 OR R1 TO SWAP",

			0x100,					// midpoint
			0xc8,					// near bottom
			FONT_SMALL,				// small text
			(JUSTIFY_CENTER | ORANGE)	// center
		);
	}
}