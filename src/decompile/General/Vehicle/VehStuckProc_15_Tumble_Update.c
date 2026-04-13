#include <common.h>

void DECOMP_VehStuckProc_Tumble_Update(struct Thread *thread, struct Driver *driver)
{
	if (driver->NoInputTimer != 0) return;

	driver->matrixArray = 0;
	driver->matrixIndex = 0;
	DECOMP_VehPhysProc_Driving_Init(thread, driver);
}