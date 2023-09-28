#include <common.h>

void RunEntryHook()
{
	int num = 10;
	while(num < 0x10)
	{
		printf("[%d] =\n", num);
		printf("{\n");
		printf("	.index =\n"); 
		printf("	{\n");
		
		printf("%d, %d, %d, %d,\n%d, %d, %d, %d,\n%d, %d, %d, %d,\n%d, %d, %d, %d,\n%d, 0, %d, 0, %d, 0\n",
			10+19*num+0,
			10+19*num+1,
			10+19*num+2,
			10+19*num+3,
			10+19*num+4,
			10+19*num+5,
			10+19*num+6,
			10+19*num+7,
			10+19*num+8,
			10+19*num+9,
			10+19*num+10,
			10+19*num+11,
			10+19*num+12,
			10+19*num+13,
			10+19*num+14,
			10+19*num+15,
			10+19*num+16,
			10+19*num+17,
			10+19*num+18);
		
		printf("	},\n");
		printf("	\n");
		printf("	.voiceSet =\n");
		printf("	{\n");
		printf("		{&data.voiceData[%d].index[0], 2},\n", num);
		printf("		{&data.voiceData[%d].index[2], 2},\n", num);
		printf("		{&data.voiceData[%d].index[4], 2},\n", num);
		printf("		{&data.voiceData[%d].index[6], 2},\n", num);
		printf("		{&data.voiceData[%d].index[8], 2},\n", num);
		printf("		{&data.voiceData[%d].index[10], 2},\n", num);
		printf("		{&data.voiceData[%d].index[12], 2},\n", num);
		printf("		{&data.voiceData[%d].index[14], 2},\n", num);
		printf("		{&data.voiceData[%d].index[16], 1},\n", num);
		printf("		{&data.voiceData[%d].index[18], 1},\n", num);
		printf("		{&data.voiceData[%d].index[20], 1},\n", num);
		printf("	}\n");
		printf("},\n");
		num++;
	}
}