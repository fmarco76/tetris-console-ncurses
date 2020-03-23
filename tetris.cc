#define COLOR_GAME 1
#define COLOR_EXTERNAL 2

#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <chrono>
#include "blocks.h"
#include "base.h"

using namespace tetris;

const int KEY_ESC = 27;
const int KEY_SPACE = ' ';
const int KEY_MENTER = 10;


std::mutex mtx;
Base bs;
Block blk;
WINDOW *gameP;
int points;

WINDOW *createNewWin(int height, int width, int starty, int startx) {
  WINDOW *local_win;
  local_win = newwin(height,width,starty,startx);
  wbkgdset(local_win, COLOR_PAIR(COLOR_GAME));
  wrefresh(local_win);
  return local_win;
}

void colorCombinations(){
  init_color(COLOR_BLACK, 0, 0, 0);
  init_pair(COLOR_GAME, COLOR_RED, COLOR_BLACK);
  init_pair(COLOR_EXTERNAL, COLOR_RED, COLOR_BLACK);

}

void moveBlockDown() {
  mtx.lock();
  blk.moveDown();
  if (bs.add(blk)) {
//      printw(" the position is x=%d, y=%d  ", blk.posX(),blk.posY());
    blk = Block(static_cast<enum Shapes>((int) rand()%7));
    if (bs.add(blk)) {
      mvwprintw(gameP, 10, 7, "Game Over!!");
      wrefresh(gameP);
      timeout(500000);
      getch();
      delwin(gameP);
      endwin();
      exit(0);
    }
//      blk = Block(static_cast<enum Shapes>((int) 0));
  }
  const char *m = bs.getBaseElements();
  for(int bh=0; bh<bs.getHeight(); bh++){
    for(int bw=0; bw<bs.getWidth(); bw++){
      mvwaddch(gameP, bh+1, bw+1, m[(bh*bs.getWidth()) + bw]);
    }
  }
  char *e = blk.getElements(); 
  for(int r=0; r<blk.lines(); r++){
    for(int c=0; c<blk.columns(); c++){
      if (e[r*blk.columns() + c] == 'x')
        mvwaddch(gameP, r + blk.posY(), c + blk.posX(), e[r*blk.columns() + c]);
    }
  }
  wrefresh(gameP);
  mtx.unlock();

}

void goDown() {
  while(1) {
    moveBlockDown();
    std::this_thread::sleep_for (std::chrono::milliseconds(500 - ((points/5) * 10)));

  }
}

void complete() {
  delwin(gameP);
  endwin();
  exit(0);
}


int main() {
  int row, col;
  points = 0;
  srand(time(NULL));
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, row, col);
  mvprintw(row/2,col/2-10, "This is my tetris game");
  attron(A_UNDERLINE);
  start_color();
  colorCombinations();
  gameP = createNewWin(bs.getHeight() + 2, bs.getWidth() + 2, 5, 25);
  box(gameP, 0, 0);
  attron(COLOR_PAIR(1));
  mvprintw(0,col/2-10, "Tetris like experimental game by");
  attron(A_BOLD);
  mvprintw(1,col/2 + 8, "Marco Fargetta");
  attroff(A_BOLD);
  mvprintw(row/2+2,col/2-10, "Press enter to start");
  refresh();
  wrefresh(gameP);
  nodelay(gameP, true);
  timeout(500);
  int c = getch();
  while (c != KEY_MENTER) {
    c=getch();
    if(c==KEY_ESC){
      complete();
    }
  }
  blk = Block(static_cast<enum Shapes>((int) rand()%7));
//  Block blk = Block(static_cast<enum Shapes>((int) 0));
  curs_set(0);
  refresh();
  std::thread first (goDown);
  while(1){
    c = getch();
    werase(gameP);
    points += bs.clean();
    mvprintw(row/2+4,col/2-10, "Completed lines: %d", points);
    box(gameP, 0, 0);
    attron(COLOR_PAIR(1));
    switch(c){
    case KEY_DOWN:
      moveBlockDown();
      break;
    case KEY_LEFT:
      if(blk.posX()>1){
        blk.moveLeft();
      }
      break;
    case KEY_RIGHT:
      if((blk.posX() + blk.columns()) <= bs.getWidth()){
        blk.moveRight();
      }
      break;
    case KEY_SPACE:
    case KEY_UP:
      mtx.lock();
      blk.rotate();
      while (blk.columns() + blk.posX() > bs.getWidth() + 1) {
        blk.moveLeft();
      }
      mtx.unlock();
      break;
    case KEY_ESC:
      complete();
    default: ;
    }
    const char *m = bs.getBaseElements();
    for(int bh=0; bh<bs.getHeight(); bh++){
      for(int bw=0; bw<bs.getWidth(); bw++){
        mvwaddch(gameP, bh+1, bw+1, m[(bh*bs.getWidth()) + bw]);
      }
    }
    char *e = blk.getElements(); 
    for(int r=0; r<blk.lines(); r++){
      for(int c=0; c<blk.columns(); c++){
        if (e[r*blk.columns() + c] == 'x')
          mvwaddch(gameP, r + blk.posY(), c + blk.posX(), e[r*blk.columns() + c]);
      }
    }
    wrefresh(gameP);
  }
}
