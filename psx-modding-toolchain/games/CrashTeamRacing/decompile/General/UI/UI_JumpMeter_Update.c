#include <common.h>

void Voiceline_RequestPlay(u_int, u_int, u_int);
void Turbo_Increment(struct Driver * , int, u_int, int);
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
      else {

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

         //if Jump meter < 0x5A0
         if (d->jumpMeter < 0x5a0) {
            //if Jump meter < 0x3C0
            if (d->jumpMeter < 0x3c0) {
               //if Jump meter > 0x27F
               if (0x27f < d->jumpMeter) {
                  // Turbo_Increment
                  // add one second reserves
                  Turbo_Increment(d, 0x3c0, 2, 0);
               }
            }

            //if Jump meter >= 0x3C0
            else {
               // Turbo_Increment
               // add one second reserves, plus speed
               Turbo_Increment(d, 0x3c0, 2, 0x80);
            }
         }

         //if Jump meter >= 0x5A0
         else {
            // Turbo_Increment
            // add one second reserves, plus speed
            Turbo_Increment(d, 0x3c0, 2, 0x100);
         }
      }
   }

   //if player is in the air
   else {
      //if (0x3FC of player struct > 0x480) and Jump meter < 0x481
      if ((0x480 < d->jump_LandingBoost) && (d->jumpMeter < 0x481)) {
         //Jump meter related operation

         // Make driver talk
         Voiceline_RequestPlay(7, data.characterIDs[d->driverID], 0x10);
      }

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