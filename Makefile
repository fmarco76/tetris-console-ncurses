CC=g++
#CFLAGS=-I.
LIBS=-lncurses -lpthread

OBJ= \
	blocks.o \
	base.o \
    tetris.o

all: tetris

tetris: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

%(OBJ): %.cc %.h
	$(CC) -c $@ $< $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(OBJ)  tetris
 