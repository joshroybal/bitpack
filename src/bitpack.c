#include <stdio.h>
#include "bitpack.h"

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
      printf("%x", b);           /* print display bit */
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
      printf("%x", b);           /* print display bit */
      if (count % 4 == 0)
         putchar(' ');				/* blank spaces after every 4th digit */
      mask >>= 1;
   }
}
