#include <common.h>

void MEMCARD_StringSet(char *dstString, int slotIdx, char *srcString)

{
  MEMCARD_StringInit(slotIdx, dstString);

  int i = 0;
  while (dstString[i] != '\0')
  {
    i++;
  }

  // copy string from src to dst
  for (int j = 0; (srcString[j] != '\0' && i < 63); j++)
  {
    dstString[i] = srcString[j];
    i++;
  }
  dstString[i] = '\0';
  return;
}
