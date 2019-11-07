#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charvec.h"

void create(struct character_vector *v)
{
   v->buf = (char *) malloc(2 * sizeof(char));
   v->buf[0] = '\0';
   v->curr_siz = 0;
   v->max_siz = 2;
}

void append(struct character_vector *v, char c)
{
   ++(v->curr_siz);
   if (v->curr_siz+1 > v->max_siz) {
      v->max_siz *= 2;
      v->buf = (char *) realloc(v->buf, (v->max_siz+1) * sizeof(char));
   }
   v->buf[(v->curr_siz)-1] = c;
   v->buf[v->curr_siz] = '\0';
}

void destroy(struct character_vector *v)
{
   free(v->buf);
   v->curr_siz = 0;
   v->max_siz = 0;
}

void teletype(struct character_vector *v)
{
   puts(v->buf);
}
