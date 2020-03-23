#include "base.h"

using namespace tetris;
Base::Base() {
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      matrix[(i*width)+j] = ' ';
    }
  }
}

bool Base::add (Block& blk) {
  for(int r =0; r < blk.lines(); r++){
    for (int i = 0; i < blk.columns(); i++) {
      if ((matrix[width * (blk.posY() + r - 1) + i + blk.posX() - 1] == 'x' &&
        blk.getElements()[(blk.columns() * r) + i] == 'x')) {
        mergeBlock(blk);
        return true;
      }
    }
  }
  if (((blk.posY() + blk.lines()) > height+1)) {
    mergeBlock(blk);
    return true;    
  }
  return false;
}

void Base::mergeBlock(Block& blk) {
  for(int r = 0; r < blk.lines(); r++) {
    for(int l = 0; l < blk.columns(); l++){
      if((r + blk.posY()-2) >= 0 && matrix[(width * (r + blk.posY()-2)) + (l + blk.posX()-1)] == ' ')
        matrix[(width * (r + blk.posY()-2)) + (l + blk.posX()-1)] = blk.getElements()[blk.columns()*r + l];
    }
  }
  int elem=0;
  for (int h = 0; h < height; h++){
    for(int w = 0; w < width; w++) {
      if(matrix[width*h + w] == 'x')
        elem++;
    }
    if (elem == width) {
      for(int w = 0; w < width; w++)  {
        matrix[width*h + w] = 'o';
      }
    }
    elem = 0;
  }
}


const int Base::clean() {
  int cleaned = 0;
  for (int h = 0; h < height; h++){
    if (matrix[width * h] == 'o'){
      cleaned++;
      for (int k = h; k > 0; k--)
        for (int w = 0; w < width; w++)
          matrix[width * k + w] = matrix[(width * (k - 1)) + w];
      for (int w = 0; w < width; w++)
        matrix[w] = ' ';
    }
  }
  return cleaned;
}