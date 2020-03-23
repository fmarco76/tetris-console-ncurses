#ifndef TETRIS_BLOCKS
#define TETRIS_BLOCKS

namespace tetris
{
  enum class Shapes { Square, Lshape, bLshape, Tshape, Zshape, bZshape, Ishape };
  class Block {
    private:
      int pX = 0;
      int pY = 0;
      int iRow = 0;
      int iCol = 0;
      enum Shapes shp;
      char *elem;
    public:
      Block();
      Block(enum Shapes, int x = 10, int y = 0);
      Block(const Block&);
      ~Block();
      Block& operator=(const Block&);

      char * getElements() { return elem; };
      const int lines() { return iRow; };
      const int columns()  { return iCol; };
      const int posX() { return pX; };
      const int posY() { return pY; };

      void rotate();
      void moveDown();
      void moveLeft();
      void moveRight();
  };
}

#endif