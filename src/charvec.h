#ifndef CHARVEC_H
#define CHARVEC_H

struct character_vector {
   char *buf;
   int curr_siz;
   int max_siz;
};

void create(struct character_vector *);
void append(struct character_vector *, char);
void destroy(struct character_vector *);
void teletype(struct character_vector *);

#endif
