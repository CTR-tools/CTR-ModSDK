#include <common.h>

// replace call to FullyOffScreen in main(), with this
void MyFlagFunc()
{
	// draw flag when loading, so screen isn't just frozen
	RaceFlag_SetFullyOnScreen();

	// without this, Sep3 wont work
	RaceFlag_SetCanDraw(1);
}