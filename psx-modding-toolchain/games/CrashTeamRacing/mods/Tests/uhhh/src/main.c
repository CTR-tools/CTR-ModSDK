#include <common.h>

// MIPS Instructions
#define J(addr) ((((unsigned int) addr & 0xFFFFFF) >> 2) | 0x08000000)
#define JR_RA 0x03E00008
#define NOP   0x00000000

void COLL_Instance(short* param_1, u_char* param_2);
void GameplayUpdateLoop();
typedef void (*func)(short* param_1, u_char* param_2);
func oldFunc = (func) &COLL_Instance;

unsigned int * hookAddress = (unsigned int *) (&GameplayUpdateLoop - 8);

unsigned int instructions[4];

// The Tester() function takes the same signature as the function you're decompiling
void Tester(short* param_1, u_char* param_2)
{
	if (param_2[1] == 4) 
 	{  
		printf("1f80014a: %x\n", param_1[0x21]);

		//*(byte **)(param_1 + 0x24) = param_2;
	
		// 1f80014a
   		//param_1[0x21] = param_1[0x21] + 1;
  	}

	// Call the original function
	func ogFunc = (func) &instructions[0];
	ogFunc(param_1, param_2);
}

void InstallHook()
{
	unsigned int * oldFuncAddr = (unsigned int *) oldFunc;
	instructions[0] = oldFuncAddr[0];
	instructions[1] = oldFuncAddr[1];
	instructions[2] = J(&oldFuncAddr[2]);
	instructions[3] = NOP;

	oldFuncAddr[0] = J(&Tester);
	oldFuncAddr[1] = NOP;

	*hookAddress = JR_RA;
}