#include <common.h>

int DECOMP_VehCalc_MapToRange(
	int val, 
	int oldMin, int oldMax, 
	int newMin, int newMax)
{
	if (val <= oldMin)
		return newMin;
	
	if (val >= oldMax)
		return newMax;
	
	return 
	(
		newMin +
		(
			// distFromBottom * newRange
			(val - oldMin) * (newMax - newMin)
		) 
		
		// divide by oldRange
		/ (oldMax - oldMin)
		
	);
}