#ifndef BITPACK_H
#define BITPACK_H

void strip(char []);
long pack(char *);
void unpack(char [], long);
void packarr(char *, char *);
void unpackarr(char *, char *);
void display_ascii(char);
void display_byte(char);
void display_word(long);

#endif
