UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CXX=g++
	#CXXFLAGS=-I.
endif
ifeq ($(UNAME_S),Darwin)
	CXX=clang++
  CXXFLAGS += -D OSX -std=c++14
endif

LIBS=-lncurses -lpthread

OBJ= \
	blocks.o \
	base.o \
    tetris.o

all: tetris

tetris: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

%(OBJ): %.cc %.h
	$(CXX) -c $< $(CXXFLAGS)


.PHONY: clean

clean:
	rm -f $(OBJ)  tetris
 
