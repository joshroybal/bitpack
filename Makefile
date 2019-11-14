CC = gcc
CFLAGS = -O2 -std=c89 -pedantic -Werror
LFLAGS = -s
OBJS = obj/bitpack.o obj/main.o
HDRS = src/bitpack.h
BIN = bitpack

obj/%.o: src/%.c $(HDRS)
	$(CC) -c $< $(CFLAGS) -o $@

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)

.PHONY : clean
clean:
	$(RM) $(OBJS)
