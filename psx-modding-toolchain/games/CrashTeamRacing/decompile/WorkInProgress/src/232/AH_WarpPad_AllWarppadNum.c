#include <common.h>

void DECOMP_AH_WarpPad_AllWarppadNum(void)
{
  int digit1s;
  struct WarpPad* warpPadObj;
  struct Instance* warpPadInst;
  struct Thread* warpPadThread;
  
  // loop through all warppad threads in thread bucket
  for (warpPadThread = &sdata->gGT->threadBuckets[5]; warpPadThread != 0; warpPadThread = warpPadThread->siblingThread)
  {
	// thread -> object
    warpPadObj = warpPadThread->object;
	
	// 01s digit
	// obj -> WarpnumInst1
    warpPadInst = warpPadObj->inst[1];

    digit1s = warpPadObj->digit1s;
	
    if (
			(
				// if instance is valid
				(warpPadInst != 0) && 
				
				// 01s digit, number of item required to open warppad
				(digit1s != 0)
			) && 
			
			// DCxDemo says:
			// 1 to 8 is taken from mpk i guess, 0, 9 and X are seprate models
			(digit1s != 9)
    )
		
	{
	  // update instance data, depending on digit,
	  // pull directly from the header, dont use distance for LOD
	  
	  // warppadObj -> inst -> xxx
	  // warppadObj -> inst -> model -> header[digit] -> xxx
		
	  // xxx = ptrCommandList
      warpPadInst->idpp->ptrCommandList = warpPadInst->model->headers[digit1s].ptrCommandList;
	  
	  // xxx = ptrColors
	  warpPadInst->idpp->ptrColorLayout = warpPadInst->model->headers[digit1s].ptrColors;
      
	  // xxx = ptrTexLayout
	  warpPadInst->idpp->ptrTexLayout = warpPadInst->model->headers[digit1s].ptrTexLayout;
      
	  // xxx = ptrVertexData
	  warpPadInst->idpp->unkc0[0] = warpPadInst->model->headers[digit1s].ptrVertexData;
    }
    
	// 10s digit
	// obj -> WarpnumInst2
	warpPadInst = warpPadObj->inst[2];
    
	if (
			// if instance is valid
			(warpPadInst != 0) && 
			
			// if 10s digit is not zero
			(warpPadObj->digit10s != 0)
		) 
	{
	  // update instance data, depending on digit,
	  // pull directly from the header, dont use distance for LOD
		
	  // can only ever be '1', hard-coded to header[1]
		
	  // warppadObj -> inst -> xxx
	  // warppadObj -> inst -> model -> header[1] -> xxx
		
	  // xxx = ptrCommandList
      warpPadInst->idpp->ptrCommandList = warpPadInst->model->headers[1].ptrCommandList;
	  
	  // xxx = ptrColors
      warpPadInst->idpp->ptrColorLayout = warpPadInst->model->headers[1].ptrColors;
		   
	  // xxx = ptrTexLayout
      warpPadInst->idpp->ptrTexLayout = warpPadInst->model->headers[1].ptrTexLayout;
		   
	  // xxx = ptrVertexLayout
      warpPadInst->idpp->unkc0[0] = warpPadInst->model->headers[1].ptrVertexData;
    }
  }
  return;
}