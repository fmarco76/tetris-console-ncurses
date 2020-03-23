#include "blocks.h"
#include <cstring>
using namespace tetris;

Block::Block(enum Shapes shape, int x, int y):
  pX(x), pY(y)
{
  shp = shape;
  switch(shape) {
  case Shapes::Square:
    elem = new char[4]{'x', 'x', 'x', 'x'};
    iRow = 2;
    iCol = 2;
    break;
  case Shapes::Lshape:
    elem = new char[6]{'x', ' ', 'x', ' ', 'x', 'x'};
    iRow = 3;
    iCol = 2;
    break;
  case Shapes::bLshape:
    elem = new char[6]{' ', 'x', ' ', 'x', 'x', 'x'};
    iRow = 3;
    iCol = 2;
    break;
  case Shapes::Tshape:
    elem = new char[6]{'x', ' ', 'x', 'x', 'x', ' '};
    iRow = 3;
    iCol = 2;
    break;
  case Shapes::Zshape:
    elem = new char[6]{'x', ' ', 'x', 'x', ' ', 'x'};
    iRow = 3;
    iCol = 2;
    break;
  case Shapes::bZshape:
    elem = new char[6]{' ', 'x', 'x', 'x', 'x', ' '};
    iRow = 3;
    iCol = 2;
    break;
  case Shapes::Ishape:
    elem = new char[4]{'x', 'x', 'x', 'x'};
    iRow = 4;
    iCol = 1;
    break;
  }
}

Block::Block(const Block& blk) {
  shp = blk.shp;
  pX = blk.pX;
  pY = blk.pY;
  iRow = blk.iRow;
  iCol = blk.iCol;
  elem = new char[iRow*iCol];
  strncpy(elem, blk.elem, iRow*iCol);
}


Block::~Block() {
  delete[] elem;
}

Block::Block() {
}

Block& Block::operator=(const Block& blk) {
  delete[] elem;
  shp = blk.shp;
  pX = blk.pX;
  pY = blk.pY;
  iRow = blk.iRow;
  iCol = blk.iCol;
  elem = new char[iRow*iCol];
  strncpy(elem, blk.elem, iRow*iCol);
  return *this;
}

void Block::rotate() {
  int tmp = iRow;
  iRow = iCol;
  iCol = tmp;
  switch(shp) {
  case Shapes::Lshape:
  case Shapes::bLshape:
  case Shapes::Tshape:
  case Shapes::Zshape:
  case Shapes::bZshape:
    char *tElem = new char[6];  
    if (tmp == 3) {
      tElem[0] = elem[1];
      tElem[1] = elem[3];
      tElem[2] = elem[5];
      tElem[3] = elem[0];
      tElem[4] = elem[2];
      tElem[5] = elem[4];
    }
    else {
      tElem[0] = elem[2];
      tElem[1] = elem[5];
      tElem[2] = elem[1];
      tElem[3] = elem[4];
      tElem[4] = elem[0];
      tElem[5] = elem[3];
    }
    delete[] elem;
    elem = tElem;
    break;
  }

}

void Block::moveDown() {
  pY++;
}

void Block::moveLeft() {
  pX--;
}

void Block::moveRight() {
  pX++;
}
