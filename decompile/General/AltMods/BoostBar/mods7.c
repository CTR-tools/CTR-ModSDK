void uibb_entryHook()
{
	data.hud_2P_P1[8].y -= 6;
	data.hud_2P_P2[8].y -= 6;
	data.hud_4P_P1[8].y -= 6;
	data.hud_4P_P2[8].y -= 6;
	data.hud_4P_P3[8].y -= 6;
	data.hud_4P_P4[8].y -= 6;

	// lapcount that draws above bootbar
	data.hud_2P_P1[1].y -= 6;
	data.hud_2P_P2[1].y -= 6;
	data.hud_4P_P1[1].y -= 6;
	data.hud_4P_P2[1].y -= 6;
	data.hud_4P_P3[1].y -= 6;
	data.hud_4P_P4[1].y -= 6;
}