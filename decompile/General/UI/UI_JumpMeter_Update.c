#include <common.h>

void DECOMP_UI_JumpMeter_Update(struct Driver * d) {

   //if player is not in the air
   if ((d->actionsFlagSet & 0x80000) == 0) {
      //if, in previous frame? player was not in the air either
      if ((d->actionsFlagSetPrevFrame & 0x80000) == 0) {
         //if Jump meter Timer is done
         if (d->jumpMeterTimer == 0) {
            //reset Jump meter
            d->jumpMeter = 0;
         }
         //if Jump meter Timer is not done
         else {
            //reduce Jump meter Timer by ~32ms
            d->jumpMeterTimer -= sdata->gGT->elapsedTimeMS;
            //if Jump meter Timer goes negative
            if (d->jumpMeterTimer < 0) {
               //prevent Jump meter Timer from going negative
               d->jumpMeterTimer = 0;
            }
         }
      }
      //if, in previous frame? player was in the air
      else 
	  {

         // if jump is high enough to be significant
         if (0x150 < d->jumpMeter) {
            // keep track of all jumps
            d->timeSpentJumping += d->jumpMeter;
         }

         // if highest jump is less than current jump
         if (d->highestJump < d->jumpMeter) {
            // save highest jump
            d->highestJump = d->jumpMeter;
         }

         if (d->jumpMeter >= 640) 
		 {
            int param = 0;
			if (d->jumpMeter >= 960) param = 0x80;
			if (d->jumpMeter >= 1440) param = 0x100;

			// add one second reserves
			DECOMP_VehFire_Increment(d, 960, POWER_SLIDE_HANG_TIME, param);
         }
      }
   }

   //if player is in the air
   else 
   {
	  #ifndef REBUILD_PS1
      if ((0x480 < d->jump_LandingBoost) && (d->jumpMeter < 0x481)) 
	  {
         // Make driver talk
         Voiceline_RequestPlay(7, data.characterIDs[d->driverID], 0x10);
      }
	  #endif

      //Jump meter = 0x3FC
      d->jumpMeter = d->jump_LandingBoost;

      //if Jump meter > 0x960
      if (0x960 < d->jump_LandingBoost) {
         //prevent Jump meter from going over 0x960
         d->jumpMeter = 0x960;
      }
      //keep Jump meter Timer at 0x5A0.
      d->jumpMeterTimer = 0x5a0;
   }
   return;
}