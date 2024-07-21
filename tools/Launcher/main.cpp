#include "app.h"

int main(int argc, char* argv[])
{
  App app;
  app.Init();
#ifdef _DEBUG
  app.Run();
#else
  try { app.Run(); }
  catch (...) {};
#endif
  app.Close();
  return 0;
}
