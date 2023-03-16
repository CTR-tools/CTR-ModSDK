// MixRNG_Scramble
void FUN_8003ea28(void)

{
  // random algorithm for seemingly-random numbers
  DAT_8008d424 = DAT_8008d424 * 0x6255 + 0x3619 & 0xffff;
  return;
}


// MixRNG_Particles
// gets number between zero and param_1
int FUN_8003ea6c(int param_1)

{
  uint uVar1;

  uVar1 = FUN_8006c684(PTR_DAT_8008d2ac + 0x252c);
  return (int)((uVar1 & 0xffff) * param_1) >> 0x10;
}


// MixRNG_GetValue
uint FUN_8003eaac(int param_1)

{
  return param_1 * 0x6255 + 0x3619U & 0xffff;
}