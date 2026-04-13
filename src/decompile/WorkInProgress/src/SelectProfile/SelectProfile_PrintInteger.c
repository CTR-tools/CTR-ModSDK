#include <common.h>

void SelectProfile_PrintInteger(int integer,short posX,short posY,short fmt,u_short flags)
{
  char *format;
  char string [64];
  
  if (fmt == 1) {
    format = sdata.stringFormat1[0];
  }
  else {
    format = sdata.stringFormat2[0];
  }
  sprintf(string,format,integer);
  DecalFont_DrawLine(string,posX,posY,1,flags);
}

