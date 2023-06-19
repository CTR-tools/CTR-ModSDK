#include <common.h>

extern RECT r;
u_int metaPhysID = 0;

void heyguys(struct GameTracker* gGT)
{
	MainFreeze_SafeAdvDestroy(); // probably mandatory

	RECT glowingcursor; // exactly what the name says
	char metaPhys[] = "         "; // dummy string space to be used later
	char metaPhysIDString[] = "     ";
	char* driverClassString[4] =
	{
		"BALANCED",
		"ACCELERATION",
		"SPEED",
		"TURN",
		//"UNLIMITED"
	};
	u_int buttonsTapped = sdata->gGamepads->gamepad[0].buttonsTapped;
	int* driverClass = &data.MetaDataCharacters[data.characterIDs[0]].engineID;

	if (buttonsTapped & BTN_L1) metaPhysID = (metaPhysID + 64) % 65;
	if (buttonsTapped & BTN_R1) metaPhysID = (metaPhysID + 1) % 65;

	if (buttonsTapped & (BTN_L2 | BTN_R2))
	{
		if (buttonsTapped & BTN_L2) *driverClass = (*driverClass + 3) % 4;
		if (buttonsTapped & BTN_R2) *driverClass = (*driverClass + 1) % 4;
		VehInit_SetConsts(sdata->gameTracker.drivers[0]);
	}

	sprintf(metaPhys, "%d\n", data.metaPhys[metaPhysID].value[*driverClass]); // right here, in fact!
	sprintf(metaPhysIDString, "%d\n", metaPhysID);

	DecalFont_DrawLine(driverClassString[*driverClass], SCREEN_WIDTH/2, SCREEN_HEIGHT/4, FONT_BIG, (CENTER_TEXT | ORANGE)); // draw current metaPhys value
	u_int metaPhysColor = ORANGE;
	if
	(
		metaPhysID == 9 || metaPhysID == 11 || metaPhysID == 12 || metaPhysID == 18 ||
		metaPhysID == 20 || metaPhysID == 21 || metaPhysID == 22 || metaPhysID == 42 || metaPhysID == 61
	) metaPhysColor = BLUE;
	DecalFont_DrawLine(metaPhysIDString, SCREEN_WIDTH/2, SCREEN_HEIGHT/3, FONT_BIG, (CENTER_TEXT | metaPhysColor));
	DecalFont_DrawLine(metaPhys, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, FONT_BIG, (CENTER_TEXT | metaPhysColor)); // draw current metaPhys value

	// draw glowing cursor
	glowingcursor.x = 40;
	glowingcursor.w = 40;
	glowingcursor.y = 128;
	glowingcursor.h = 50;
	CTR_Box_DrawClearBox(&glowingcursor, &sdata->menuRowHighlight_Normal, 1, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);

	MENUBOX_DrawInnerRect(&r, 4, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour); // draw the actual menubox background
}