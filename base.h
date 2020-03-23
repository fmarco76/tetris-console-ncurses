#ifndef TETRIS_BASE
#define TETRIS_BASE

#include "blocks.h"

namespace tetris
{
  const int width = 21;
  const int height = 20;
  class Base {
    private:
      char matrix[height * width];
      void mergeBlock(Block&);
    public:
      Base();
      ~Base() {};
      bool add (Block&);
      const char* getBaseElements() {return matrix; };
      const int getWidth() { return width; }
      const int getHeight() { return height; }
      const int clean();
  };
}

#endif