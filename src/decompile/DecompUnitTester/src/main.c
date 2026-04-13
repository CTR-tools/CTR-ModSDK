#include <common.h>
#include "math.h"
#include "../../../../../tools/nugget/common/macros/gte.h"

// MIPS Instructions
#define J(addr) ((((unsigned int) addr & 0xFFFFFF) >> 2) | 0x08000000)
#define JR_RA 0x03E00008
#define NOP   0x00000000

// Functions
void DECOMP_CTR_CycleTex_LEV(struct AnimTex* animtex, int timer);
void CTR_CycleTex_LEV(struct AnimTex* animtex, int timer);
void MainFrame_GameLogic();

typedef void (*func)(struct AnimTex* animtex, int timer);
func newFunc = (func) &DECOMP_CTR_CycleTex_LEV;
func oldFunc = (func) &CTR_CycleTex_LEV;

unsigned int * hookAddress = (unsigned int *) (&MainFrame_GameLogic - 8);
unsigned int instructions[4];

unsigned int * ram = (unsigned int *) 0x80010000;
unsigned int * ram_4mb = (unsigned int *) 0x80410000;
unsigned int * ram_6mb = (unsigned int *) 0x80610000;
const unsigned int ramSize = (0x1FF800 - 0x10000) / 4;
unsigned int * scratchpad = (unsigned int *) 0x1F800000;
unsigned int * scratchpadBackup_4mb = (unsigned int *) 0x80400000;
unsigned int * scratchpadBackup_6mb = (unsigned int *) 0x80600000;
const unsigned int scratchpadSize = 0x400 / 4;
unsigned int * gteBackup_4mb = (unsigned int *) 0x80408000;
unsigned int * gteBackup_6mb = (unsigned int *) 0x80608000;
const unsigned int gteSize = 64;
unsigned int hits = 0;
unsigned int total = 0;

/*
	The credit for the first two functions goes to Nicolas Noble,
	author of the openbios project. I'm calling these functions to
	disable interrupts, so that the PSX RAM is guaranteed to not change
	during all our function calls.
	https://github.com/grumpycoders/pcsx-redux/blob/main/src/mips/common/syscalls/syscalls.h#L39-L57
*/
static __attribute__((always_inline)) int enterCriticalSection() {
	register int n asm("a0") = 1;
	register int r asm("v0");
	__asm__ volatile("syscall\n"
					 : "=r"(n), "=r"(r)
					 : "r"(n)
					 : "at", "v1", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9",
					   "memory");
	return r;
}

static __attribute__((always_inline)) void leaveCriticalSection() {
	register int n asm("a0") = 2;
	__asm__ volatile("syscall\n"
					 : "=r"(n)
					 : "r"(n)
					 : "at", "v0", "v1", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9",
					   "memory");
}

void memCopy(unsigned int * dest, unsigned int * src, unsigned int size)
{
	for (unsigned int i = 0; i < size; i++)
		dest[i] = src[i];
}

int isEqual(unsigned int * dest, unsigned int * src, unsigned int size)
{
	int ret = 1;
	for (unsigned int i = 0; i < size; i++)
	{
		if (dest[i] != src[i])
		{
			printf("Diff at %x\n", &dest[i]);
			ret = 0;
		}
	}
	return ret;
}

// The Tester() function takes the same signature as the function you're decompiling
void Tester(struct AnimTex* animtex, int timer)
{
	enterCriticalSection();
	// Backup the program state before calling the decomp function
	memCopy(ram_4mb, ram, ramSize);
	memCopy(scratchpadBackup_4mb, scratchpad, scratchpadSize);
	gte_saveContext(gteBackup_4mb);
	// Call the decomp function
	newFunc(animtex, timer);
	// Backup result of decomp function
	memCopy(ram_6mb, ram, ramSize);
	memCopy(scratchpadBackup_6mb, scratchpad, scratchpadSize);
	gte_saveContext(gteBackup_6mb);
	// Load state
	memCopy(ram, ram_4mb, ramSize);
	memCopy(scratchpad, scratchpadBackup_4mb, scratchpadSize);
	gte_loadContext(gteBackup_4mb);
	// Call the original function
	func ogFunc = (func) &instructions[0];
	ogFunc(animtex, timer);
	gte_saveContext(gteBackup_4mb);
	total++;
	// Comparing the results of the original function and the decomp function
	if ((isEqual(gteBackup_4mb, gteBackup_6mb, gteSize)) &&
        (isEqual(scratchpad, scratchpadBackup_6mb, scratchpadSize)) &&
        (isEqual(ram, ram_6mb, ramSize))) {
        hits++;
    }
	printf("Hits/totals: %d/%d\n", hits, total);
	leaveCriticalSection();
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