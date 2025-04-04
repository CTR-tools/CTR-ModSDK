
// Timer_Init
void FUN_8004b31c(void)

{
  EnterCriticalSection();
  StopRCnt(0xf2000001);
  SetRCnt(0xf2000001,0xffff,0x2000);
  StartRCnt(0xf2000001);
  ExitCriticalSection();
  return;
}


// Timer_Destroy
void FUN_8004b370(void)

{
  EnterCriticalSection();
  StopRCnt(0xf2000001);
  ExitCriticalSection();
  return;
}


// Timer_GetTime_Total
// not milliseconds
int FUN_8004b3a4(void)

{
  long lVar1;
  int iVar2;

  // current system timer,
  // updated on every vsync
  iVar2 = DAT_8008d988;

  // time past since vsync
  lVar1 = GetRCnt(0xf2000001);

  // This does nothing
  if (lVar1 < 100)
  {
    iVar2 = DAT_8008d988;
  }

  // 0x147e = 5246
  // (timeAtVsync + timeSinceVsync) / 5
  return ((iVar2 + lVar1) * 1000) / 0x147e;
}


// Timer_GetTime_Elapsed
// Usage: elapsed(frameStart, &frameStart)
// will overwrite new frameStart, and return
// elapsed time since previous frameStart 
int FUN_8004b41c(int param_1,int *param_2)

{
  int iVar1;

  // Timer_GetTime_Total
  iVar1 = FUN_8004b3a4();

  // if pointer exists, write to it
  if (param_2 != (int *)0x0) {
    *param_2 = iVar1;
  }

  // impossible?
  if (iVar1 < param_1) {
    iVar1 = iVar1 + 0xc7e18;
  }

  // sysclock current, minus
  // sysclock previous, equals
  // elapsed time
  return iVar1 - param_1;
}
