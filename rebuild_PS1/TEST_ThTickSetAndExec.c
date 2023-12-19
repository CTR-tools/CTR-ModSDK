#include <common.h>

// Note: Unlike the original game, this TEST version
// can not force the previous function to "return", so
// always put a "return" after calling TEST_ThTickSetAndExec
void TEST_ThTickSetAndExec(struct Thread* t, void (*funcThTick)(struct Thread* self))
{
	t->funcThTick = funcThTick;
	funcThTick(t);
}