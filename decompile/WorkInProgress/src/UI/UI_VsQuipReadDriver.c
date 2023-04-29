#include <common.h>

u_int DECOMP_UI_VsQuipReadDriver(struct Driver * d, int offset, int size) {
  if (size == 2) {
    // return a short
    short* p = (short*)(d + offset);
    return *p;
  } else if (size == 1) {
    // return a char
    char* p = (char*)(d + offset);
    return *p;
  } else if (size == 4) {
    // return an int
    int* p = (int*)(d + offset);
    return *p;
  }
  return 0;
}
