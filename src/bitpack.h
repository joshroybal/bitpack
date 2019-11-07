#ifndef BITPACK_H
#define BITPACK_H

struct seven_bit_ascii {
   int ascii : 7;
};

void display_ascii(char);
void display_byte(char);
void display_word(long);

#endif
