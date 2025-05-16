CC ?= clang
CFLAGS ?= -O0 -std=c11 -Wall -Wextra -Wno-sign-compare -Wshadow
LDLIBS ?= -lm

.PHONY: all
all: notes synthesize

notes: helpers.c helpers.h notes.c wav.c wav.h cs50.c
	$(CC) $(CFLAGS) -o notes helpers.c notes.c wav.c cs50.c $(LDLIBS)

synthesize: synthesize.c wav.c wav.h helpers.c helpers.h cs50.c
	$(CC) $(CFLAGS) -o synthesize helpers.c synthesize.c wav.c cs50.c $(LDLIBS)

debug: CFLAGS += -g
debug: synthesize

.PHONY: clean
clean:
	rm -f notes synthesize *.wav
