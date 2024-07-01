extern int currCam;

static void SetNextCamera(bool increase)
{
	int driverCount = octr->NumDrivers;
	while (true)
	{
		currCam = increase ? (currCam + 1) % driverCount : (currCam + driverCount - 1) % driverCount;
		if (octr->nameBuffer[currCam][0])
		{
			sdata->gGT->cameraDC[0].driverToFollow = sdata->gGT->drivers[currCam];
			return;
		}
	}
}

void EndOfRace_Camera()
{
    const char s_switchCam[] = "Press R1 or L1 to change the camera";
	DECOMP_DecalFont_DrawLine(s_switchCam, 0x100, 5, FONT_SMALL, JUSTIFY_CENTER | ORANGE);

	struct GamepadBuffer * pad = &sdata->gGamepads->gamepad[0];
	if (pad->buttonsTapped & BTN_R1) { SetNextCamera(true); }
	if (pad->buttonsTapped & BTN_L1) { SetNextCamera(false); }
}