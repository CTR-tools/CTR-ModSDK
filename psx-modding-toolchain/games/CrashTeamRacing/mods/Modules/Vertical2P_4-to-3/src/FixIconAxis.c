#include <common.h>

void DecalHUD_DrawPolyGT4(int param_1,u_int param_2,int param_3,int param_4,u_int *param_5,u_int param_6,
                 u_int param_7,u_int param_8,u_int param_9,u_char param_10,short param_11);

void FixIconAxis(int param_1,u_int param_2,int param_3,int param_4,u_int *param_5,u_int param_6,
                 u_int param_7,u_int param_8,u_int param_9,u_char param_10,short param_11)
{
	// swap X to Y
	param_3 = (param_2 * 0xd8) / 0x200;

	// set X to midpoint,
	// minus 8 pixels for centering
	param_2 = 0xF4;

	DecalHUD_DrawPolyGT4(
			param_1, param_2, param_3, param_4,
			param_5, param_6, param_7, param_8,
			param_9, param_10, param_11);
}