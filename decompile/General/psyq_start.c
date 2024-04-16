#include <common.h>

void start()
{
	int* i;
	int sp asm("$sp");
	
	// will always initialize to zero, part of OG EXE file
	#define BoolBootedBefore *(int*)0x8008c050
	
	if(BoolBootedBefore != 0)
	{
		// insert debug stuff here
	}
	
	// first boot
	else
	{
		// clear BSS region
		for(
				i = 0x8008d668; 
				i < 0x8009f6f8; 
				i += 4
			)
		{
			i[0] = 0;
			i[1] = 0;
			i[2] = 0;
			i[3] = 0;
		}
		
		*(int*)0x8009f6f8 = 0;
		*(int*)0x8009f6fc = 0;
	}
	
	// initialize $gp
	sdata = &sdata_static;
	
	// initialize $sp
	sp = 0x807ffffc;
	
	u_int DECOMP_main();
	DECOMP_main();
}