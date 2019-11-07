CC = gcc
CFLAGS = -std=c89 -pedantic -Werror
LFLAGS =
OBJS = obj/bitpack.o obj/charvec.o obj/main.o
HDRS = src/bitpack.h src/charvec.h
BIN = bitpack

obj/%.o: src/%.c $(HDRS)
	$(CC) -c $< $(CFLAGS) -o $@

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)

.PHONY : clean
clean:
	$(RM) $(OBJS)
