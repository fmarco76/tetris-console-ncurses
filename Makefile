UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CC=g++
	#CFLAGS=-I.
	LIBS=-lncurses -lpthread
endif
ifeq ($(UNAME_S),Darwin)
	CCC=clang -std=c++11 -stdlib=libc++
  #CCFLAGS += -D OSX
	LIBS=-lncurses -lpthread -lstdc++
endif

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
 