#include <common.h>

int DECOMP_VehCalc_SteerAccel(
	int param_1, int param_2, int param_3, 
	int param_4, int param_5, int param_6)
{
  // Crash Bandicoot:
  // param_2: 0x4	SteerAccel_Stage2_FirstFrame
  // param_3: 0x8	SteerAccel_Stage2_FrameLength
  // param_4: 0x40	SteerAccel_Stage4_FirstFrame
  // param_5: 0x800	SteerAccel_Stage1_MinSteer
  // param_6: 0xC00	SteerAccel_Stage1_MaxSteer
	
  // Steering Stage 1,
  // if first 4 frames of steering
  // increase steer acceleration as time passes
  if (param_1 < param_2) 
  {
	// map "frame" from [0,4] -> [0x800,0xC00]

    param_6 = DECOMP_VehCalc_MapToRange(param_1, 0,param_2, param_5,param_6);
  }
  
  else 
  {
	// Steering Stage 3
	// frames 12+
	// decrease steer acceleration as time passes
    if (param_2 + param_3 < param_1) 
	{
	  // map "frame" from [12,64] -> [0xC00,0]

      param_6 = DECOMP_VehCalc_MapToRange(param_1, param_2 + param_3,param_4, param_6,0);
    }
  }
  
  // Steering Stage 2,
  // next 0x8 frames (frame 4 to 12)
  // max steer accel of 0xC00
  return param_6;
  
  // Steering Stage 4,
  // part of Stage 3's mapping,
  // for all steering after frame 64,
  // steer acceleration is zero, so 
  // angular velocity is constant
}