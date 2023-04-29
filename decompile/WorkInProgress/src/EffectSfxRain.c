// called "EffectSfx" for no good reason,
// but is related to rain sounds, no proof of name

// this func handle rain on tiger temple and cortex castle
void EffectSfxRain_MakeSound(struct GameTracker *gGT) {
  int i, lev;
  unsigned int rained;

  rained = 0;
  lev = gGT->levelID;

  // if you are not in
  if (
    // Tiger Temple
    (lev != 4) 
    // Cortex Castle
    && (lev != 10)) {
    return;
  }

  // if numPlyrCurrGame is not zero
  if (gGT->numPlyrCurrGame) {
    for (i = 0; i < gGT->numPlyrCurrGame; i++) {
      rained |= gGT->rainBuffer[i];
    }
  } else {
    return;
  }

  // if at least one is rained on
  if (rained) {
    // if there is no rain
    if (gGT->rainVariable == 0) {
      // now there is rain
      gGT->rainVariable = OtherFX_Play(0x82, 0);
    }
  }
  // if nobody is rained on
  else {
    // if it's raining
    if (gGT->rainVariable != 0) {
      OtherFX_Stop1();
      // no more rain
      gGT->rainVariable = 0;
    }
  }
  return;
}

void EffectSfxRain_Reset(struct gameTracker *gGT) {
  gGT->rainVariable = 0;
  return;
}
