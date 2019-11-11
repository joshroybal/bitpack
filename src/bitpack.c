#include <stdio.h>
#include <string.h>
#include "bitpack.h"

long pack(char *block)
{
   int i, n = strlen(block);
   long word = 0L, work = 0L;

   if (n > 8)
      n = 8;
   for (i = 0; i < n; ++i) {
      work = block[i];
      work <<= i*7;
      word ^= work;
   }
   return(word);
}

void unpack(char bytes[], long word)
{
   int i;

   memset(bytes, '\0', 9);
   for (i = 0; i < 8; ++i) {
      bytes[i] = word & 0x7f;
      word >>= 7;
   }
}
