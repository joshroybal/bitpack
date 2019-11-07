#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitpack.h"
#include "charvec.h"

int main(int argc, char *argv[])
{
   int i, j, n;
   unsigned char byte;
   unsigned long word;
   char buf[256];
   struct character_vector text;
   struct seven_bit_ascii *textpack;
	FILE *fp;
   
   create(&text);
   fp = fopen(argv[1], "r");
   while ( fgets(buf, sizeof(buf)-1, fp) ) {
      n = strlen(buf);
      for (i = 0; i < n; ++i)
         if (isascii(buf[i]))
            append(&text, buf[i]);
   }
   fclose(fp);
   /* teletype(&text); */
   n = strlen(text.buf);
   textpack = (struct seven_bit_ascii *) malloc(n * sizeof(struct seven_bit_ascii));
   /* write chars to bit fields */
   for (i = 0; i < n; ++i)
      textpack[i].ascii = text.buf[i];

   destroy(&text);
   
   /* convert word-by-word */
   fp = fopen("dump.dat", "wb");
   for (i = 0; i < n; i += 8) {
      word = 0L;;
      for (j = 0; j < 8; ++j) {
         byte = textpack[i+j].ascii << 1;
         memcpy(&word, &byte, 1);
         word <<= 7;
      }
      word >>= 8;
      fwrite(&word, 7, 1, fp);
   }
   fclose(fp);
   
   free(textpack);

   fp = fopen("dump.dat", "rb");
   while ( fread(&word, 7, 1, fp) ) {
      word <<= 8;
      for (i = 0; i < 8; ++i) {
         byte = word >> 7*(8-i);
         if (byte == 0)
            break;
         putchar(byte >> 1);
      }
   }
   fclose(fp);

   return(0);
}
