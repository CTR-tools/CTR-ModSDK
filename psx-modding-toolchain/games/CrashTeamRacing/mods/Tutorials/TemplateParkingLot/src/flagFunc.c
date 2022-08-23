#include <common.h>

void CheckeredFlag_SetFullyOnScreen();
void CheckeredFlag_SetCanDraw(int enable);

// replace call to FullyOffScreen in main(), with this
void MyFlagFunc()
{
	// draw flag when loading, so screen isn't just frozen
	CheckeredFlag_SetFullyOnScreen();

	// without this, Sep3 wont work
	CheckeredFlag_SetCanDraw(1);
}