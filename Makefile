CC = gcc
CFLAGS = -O2 -std=c89 -pedantic -Werror
LFLAGS = -s
OBJS = obj/bitpack.o obj/charvec.o obj/main.o
HDRS = src/bitpack.h src/charvec.h
BIN = bitpack

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)

obj/charvec.o: src/charvec.c src/charvec.h
	$(CC) -c $< $(CFLAGS) -o $@

obj/bitpack.o: src/bitpack.c src/bitpack.h
	$(CC) -c $< $(CFLAGS) -o $@

obj/main.o: src/main.c src/charvec.h src/bitpack.h
	$(CC) -c $< $(CFLAGS) -o $@

.PHONY : clean
clean:
	$(RM) $(OBJS)
