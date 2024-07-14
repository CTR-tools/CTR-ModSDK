#include "app.h"

int main(int argc, char* argv[])
{
  App app;
  app.Init();
  try { app.Run(); }
  catch (...) {};
  app.Close();
  return 0;
}
