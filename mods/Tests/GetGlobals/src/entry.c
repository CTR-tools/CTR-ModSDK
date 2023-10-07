#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	printf(".matArr0D =\n");
	printf("{\n");
	for(int i = 0; i < 4; i++)
	{
	printf("   [%d] =\n", i);
	printf("   {\n");
	printf("      .m =\n");
	printf("      {\n");
	printf("         {%d,%d,%d},\n", data.matArr0D[i].m[0][0], data.matArr0D[i].m[0][1], data.matArr0D[i].m[0][2]);
	printf("         {%d,%d,%d},\n", data.matArr0D[i].m[1][0], data.matArr0D[i].m[1][1], data.matArr0D[i].m[1][2]);
	printf("         {%d,%d,%d},\n", data.matArr0D[i].m[2][0], data.matArr0D[i].m[2][1], data.matArr0D[i].m[2][2]);
	printf("      },\n");
	printf("      .extraShort = %d, // Sneaky ND trick\n", data.matArr0D[i].m[2][3]);
	printf("      .t = {%d,%d,%d}\n", data.matArr0D[i].t[0], data.matArr0D[i].t[1], data.matArr0D[i].t[2]);
	printf("   },\n");
	}
	printf("},\n");
	printf(".matArr0E =\n");
	printf("{\n");
	for(int i = 0; i < 4; i++)
	{
	printf("   [%d] =\n", i);
	printf("   {\n");
	printf("      .m =\n");
	printf("      {\n");
	printf("         {%d,%d,%d},\n", data.matArr0E[i].m[0][0], data.matArr0E[i].m[0][1], data.matArr0E[i].m[0][2]);
	printf("         {%d,%d,%d},\n", data.matArr0E[i].m[1][0], data.matArr0E[i].m[1][1], data.matArr0E[i].m[1][2]);
	printf("         {%d,%d,%d},\n", data.matArr0E[i].m[2][0], data.matArr0E[i].m[2][1], data.matArr0E[i].m[2][2]);
	printf("      },\n");
	printf("      .extraShort = %d, // Sneaky ND trick\n", data.matArr0E[i].m[2][3]);
	printf("      .t = {%d,%d,%d}\n", data.matArr0E[i].t[0], data.matArr0E[i].t[1], data.matArr0E[i].t[2]);
	printf("   },\n");
	}
	printf("},\n");
	printf(".matArr0F =\n");
	printf("{\n");
	for(int i = 0; i < 4; i++)
	{
	printf("   [%d] =\n", i);
	printf("   {\n");
	printf("      .m =\n");
	printf("      {\n");
	printf("         {%d,%d,%d},\n", data.matArr0F[i].m[0][0], data.matArr0F[i].m[0][1], data.matArr0F[i].m[0][2]);
	printf("         {%d,%d,%d},\n", data.matArr0F[i].m[1][0], data.matArr0F[i].m[1][1], data.matArr0F[i].m[1][2]);
	printf("         {%d,%d,%d},\n", data.matArr0F[i].m[2][0], data.matArr0F[i].m[2][1], data.matArr0F[i].m[2][2]);
	printf("      },\n");
	printf("      .extraShort = %d, // Sneaky ND trick\n", data.matArr0F[i].m[2][3]);
	printf("      .t = {%d,%d,%d}\n", data.matArr0F[i].t[0], data.matArr0F[i].t[1], data.matArr0F[i].t[2]);
	printf("   },\n");
	}
	printf("},\n");
	printf(".matArr10 =\n");
	printf("{\n");
	for(int i = 0; i < 4; i++)
	{
	printf("   [%d] =\n", i);
	printf("   {\n");
	printf("      .m =\n");
	printf("      {\n");
	printf("         {%d,%d,%d},\n", data.matArr10[i].m[0][0], data.matArr10[i].m[0][1], data.matArr10[i].m[0][2]);
	printf("         {%d,%d,%d},\n", data.matArr10[i].m[1][0], data.matArr10[i].m[1][1], data.matArr10[i].m[1][2]);
	printf("         {%d,%d,%d},\n", data.matArr10[i].m[2][0], data.matArr10[i].m[2][1], data.matArr10[i].m[2][2]);
	printf("      },\n");
	printf("      .extraShort = %d, // Sneaky ND trick\n", data.matArr10[i].m[2][3]);
	printf("      .t = {%d,%d,%d}\n", data.matArr10[i].t[0], data.matArr10[i].t[1], data.matArr10[i].t[2]);
	printf("   },\n");
	}
	printf("},\n");
	printf(".matArr11 =\n");
	printf("{\n");
	for(int i = 0; i < 4; i++)
	{
	printf("   [%d] =\n", i);
	printf("   {\n");
	printf("      .m =\n");
	printf("      {\n");
	printf("         {%d,%d,%d},\n", data.matArr11[i].m[0][0], data.matArr11[i].m[0][1], data.matArr11[i].m[0][2]);
	printf("         {%d,%d,%d},\n", data.matArr11[i].m[1][0], data.matArr11[i].m[1][1], data.matArr11[i].m[1][2]);
	printf("         {%d,%d,%d},\n", data.matArr11[i].m[2][0], data.matArr11[i].m[2][1], data.matArr11[i].m[2][2]);
	printf("      },\n");
	printf("      .extraShort = %d, // Sneaky ND trick\n", data.matArr11[i].m[2][3]);
	printf("      .t = {%d,%d,%d}\n", data.matArr11[i].t[0], data.matArr11[i].t[1], data.matArr11[i].t[2]);
	printf("   },\n");
	}
	printf("},\n");
	printf(".matArr12 =\n");
	printf("{\n");
	for(int i = 0; i < 4; i++)
	{
	printf("   [%d] =\n", i);
	printf("   {\n");
	printf("      .m =\n");
	printf("      {\n");
	printf("         {%d,%d,%d},\n", data.matArr12[i].m[0][0], data.matArr12[i].m[0][1], data.matArr12[i].m[0][2]);
	printf("         {%d,%d,%d},\n", data.matArr12[i].m[1][0], data.matArr12[i].m[1][1], data.matArr12[i].m[1][2]);
	printf("         {%d,%d,%d},\n", data.matArr12[i].m[2][0], data.matArr12[i].m[2][1], data.matArr12[i].m[2][2]);
	printf("      },\n");
	printf("      .extraShort = %d, // Sneaky ND trick\n", data.matArr12[i].m[2][3]);
	printf("      .t = {%d,%d,%d}\n", data.matArr12[i].t[0], data.matArr12[i].t[1], data.matArr12[i].t[2]);
	printf("   },\n");
	}
	printf("},\n");
	printf(".matArr13 =\n");
	printf("{\n");
	for(int i = 0; i < 4; i++)
	{
	printf("   [%d] =\n", i);
	printf("   {\n");
	printf("      .m =\n");
	printf("      {\n");
	printf("         {%d,%d,%d},\n", data.matArr13[i].m[0][0], data.matArr13[i].m[0][1], data.matArr13[i].m[0][2]);
	printf("         {%d,%d,%d},\n", data.matArr13[i].m[1][0], data.matArr13[i].m[1][1], data.matArr13[i].m[1][2]);
	printf("         {%d,%d,%d},\n", data.matArr13[i].m[2][0], data.matArr13[i].m[2][1], data.matArr13[i].m[2][2]);
	printf("      },\n");
	printf("      .extraShort = %d, // Sneaky ND trick\n", data.matArr13[i].m[2][3]);
	printf("      .t = {%d,%d,%d}\n", data.matArr13[i].t[0], data.matArr13[i].t[1], data.matArr13[i].t[2]);
	printf("   },\n");
	}
	printf("},\n");
	
	printf("\n");
	printf("\n");
	printf("\n");
}