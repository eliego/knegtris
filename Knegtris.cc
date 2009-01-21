#include <iostream>
#include <ncurses.h>
#include "Exception.h"
#include "ScreenContext.h"
#include "Kloss.h"

int main() {
  char com;
  initscr();
  start_color();
  init_pair(1,COLOR_CYAN,COLOR_CYAN);
  init_pair(2,COLOR_BLUE,COLOR_BLUE);
  init_pair(3,COLOR_GREEN,COLOR_GREEN);
  init_pair(4,COLOR_RED,COLOR_RED);
  init_pair(5,COLOR_MAGENTA,COLOR_MAGENTA);
  init_pair(6,COLOR_YELLOW,COLOR_YELLOW);
  init_pair(7,COLOR_WHITE,COLOR_WHITE);
  try {
    ScreenContext* scr = new ScreenContext(0, 0, 22, 25);
    Kloss* grej = new Kloss(scr);
    grej->activate();
    while ((com = getchar()) != 'q')
      switch (com) {
      case 's':
	grej->advance();
	break;
      case 'a':
	grej->moveL();
	break;
      case 'd':
	grej->moveR();
      break;
      case 'w':
	grej->rotate();
	break;
      }
    delete scr;
    endwin();
  } catch (Exception ex) {
    endwin();
    std::cout << ex.getMess();
  }
  //      endwin();
  return 0;
}
