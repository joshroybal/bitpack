#include <stdio.h>
#include <string.h>
#include "bitpack.h"

/* replace any non-ascii chars, nulls or dels in read block with spaces */
void strip(char ascii[])
{
   int i;

   for (i = 0; i < strlen(ascii); ++i)
      if ( ascii[i] < 00 || ascii[i] > 0177 ) /* 00 = 0x0, 0177 = 0x7f */
         ascii[i] = ' ';
}

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
   for (i = 0; i < 8; ++i)
      bytes[i] = (word >> i*7) & 0x7f;
}

void packarr(char *dst, char *src)
{
   int i;
   long word;
   char bytes[9];

   strip(src);
   memset(dst, '\0', 71);
   for (i = 0; i < 10; ++i) {
      memset(bytes, '\0', sizeof(bytes));
      memcpy(bytes, src + i*8, sizeof(bytes)-1);
      word = pack(bytes);
      memcpy(dst + i*7, &word, 7);
   }
}

void unpackarr(char *dst, char *src)
{
   int i;
   long word;
   char bytes[9];
   
   memset(dst, '\0', 81);
   for (i = 0; i < 10; ++i) {
      word = 0L;
      memcpy(&word, src + i*7, 7);
      unpack(bytes, word);
      memcpy(dst + i*8, bytes, 8);
   }
}

/* output the bit pattern */
void display_ascii(char a)
{
   int count, nbits;
   char b, m, mask;

   /* determine the word size in bits and set the initial mask */
   nbits = 7;
   m = 0x1 << (nbits - 1);       /* place 1 in leftmost position */

   mask = m;
   for (count = 1; count <= nbits; count++) {
      b = (a & mask) ? 1 : 0;    /* set display bit on or off */
      printf("%x", b);           /* print display bit */
      if (count % 7 == 0)
         putchar(' ');				/* blank spaces after every 4th digit */
      mask >>= 1;
   }
}

/* output the bit pattern */
void display_byte(char a)
{
   int count, nbits;
   char b;
   unsigned char m, mask;

   /* determine the word size in bits and set the initial mask */
   nbits = 8 * sizeof(char);
   m = 0x1 << (nbits - 1);       /* place 1 in leftmost position */

   mask = m;
   for (count = 1; count <= nbits; count++) {
      b = (a & mask) ? 1 : 0;    /* set display bit on or off */
      printf("%x", b);          /* print display bit */
      if (count % 4 == 0)
         putchar(' ');				/* blank spaces after every 4th digit */
      mask >>= 1;
   }
}

/* output the bit pattern */
void display_word(long a)
{
   int count, nbits;
   long b;
   unsigned long m, mask;

   /* determine the word size in bits and set the initial mask */
   nbits = 8 * sizeof(long);
   m = 0x1L << (nbits - 1);       /* place 1 in leftmost position */

   mask = m;
   for (count = 1; count <= nbits; count++) {
      b = (a & mask) ? 1 : 0;    /* set display bit on or off */
      printf("%lx", b);          /* print display bit */
      if (count % 4 == 0)
         putchar(' ');				/* blank spaces after every 4th digit */
      mask >>= 1;
   }
}
