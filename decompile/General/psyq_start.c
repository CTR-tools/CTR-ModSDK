#include <common.h>

void start()
{
	int* i;
		
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
		
		// clear $sp region
		for(
				i = 0x807ff800; 
				i < 0x807fff00; 
				i += 4
			)
		{
			i[0] = 0;
			i[1] = 0;
			i[2] = 0;
			i[3] = 0;
		}
	}
	
	// initialize $gp
	sdata = &sdata_static;
	
#ifdef USE_RAMEX
	void startSP();
	startSP();
#endif
		
	u_int DECOMP_main();
	DECOMP_main();
}

#ifdef USE_RAMEX
void startSP()
{
	// initialize $sp
	//register int sp asm("sp");
	//sp = 0x807ffffc;
	
	// I can't believe this compiler wont
	// just listen to me and set the register
	asm(
		".set noreorder\n"
		"lui $29, 0x807F\n"
		"ori $29, $29, 0xFFFc");
}
#endif