#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitpack.h"
#include "charvec.h"

int main(int argc, char *argv[])
{
   int i, n, blksiz;
   long word = 0L;
   char buf[256], bytes[9];
   struct character_vector text;
	FILE *fp;
  
   if (argc < 4) {
      fprintf(stderr, "Usage: %s pack|unpack infile outfile\n", argv[0]);
      return(1);
   }
   if (strcmp(argv[1], "pack") != 0 && strcmp(argv[1], "unpack") != 0) {
      fprintf(stderr, "Usage: %s pack|unpack infile outfile\n", argv[0]);
      return(1);      
   }
   
   if (strcmp(argv[1], "pack") == 0) {
      if ( (fp = fopen(argv[2], "r")) == (FILE *) NULL ) {
         fprintf(stderr, "error opening file %s\n", argv[2]);
         return(1);
      }
      create(&text);
      while ( fgets(buf, sizeof(buf)-1, fp) ) {
         n = strlen(buf);
         for (i = 0; i < n; ++i)
            if (isascii(buf[i]))
               append(&text, buf[i]);
      }
      fclose(fp);
      n = text.curr_siz;
      memset(bytes, '\n', 9);
      /* write blocks of packed bits to file */
      if ( (fp = fopen(argv[3], "wb")) == (FILE *) NULL ) {
         fprintf(stderr, "error opening file %s\n", argv[3]);
         destroy(&text);
         return(1);
      }      
      for (i = 0; i < n; i += 8) {
         strncpy(bytes, text.buf + i, 8);
         word = pack(bytes);
         blksiz = (strlen(bytes) < 7) ? strlen(bytes) : 7;
         fwrite(&word, blksiz, 1, fp);
      }
      fclose(fp);
      destroy(&text);
      printf("%s packed into %s\n", argv[2], argv[3]);
   }
   else {
      /* convert packed ascii back to byte sized chars */
      if ( (fp = fopen(argv[2], "rb")) == (FILE *) NULL ) {
         fprintf(stderr, "error opening file %s\n", argv[2]);
         return(1);
      }
      create(&text);
      blksiz = fread(&word, 1, 7, fp);
      while ( blksiz > 0 )  {
         unpack(bytes, word);
         for (i = 0; i < strlen(bytes); ++i) {
            append(&text, bytes[i]);
         }
         word = 0L;
         blksiz = fread(&word, 1, 7, fp);
      }
      fclose(fp);
      if ( (fp = fopen(argv[3], "wb")) == (FILE *) NULL ) {
         fprintf(stderr, "error opening file %s\n", argv[3]);
         destroy(&text);
         return(1);
      }      
      fwrite(text.buf, text.curr_siz, 1, fp);
      fclose(fp);
      destroy(&text);
      printf("%s unpacked from %s\n", argv[3], argv[2]);
   }

   return(0);
}
