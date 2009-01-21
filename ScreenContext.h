#ifndef __SCREENCONTEXT
#define __SCREENCONTEXT
#include "ScreenObject.h"
#include <map>
#include <ncurses.h>

// Representation of the screen
class ScreenContext {
public:
  ScreenContext();
  ScreenContext(int startX, int startY, int sizeX, int sizeY);
  ~ScreenContext();
  void add(ScreenObject* obj);
  void del(int id);
  void redraw();
  int getWidth() { return m_sizeX; }
  int getHeight() { return m_sizeY; }

private:
  WINDOW* m_screen;
  int m_counter;
  int m_x;
  int m_y;
  int m_sizeX;
  int m_sizeY;
  chtype** m_data;
  std::map<int,ScreenObject*> m_objects;
  void setArea(int arg1, int arg2, int arg3, int arg4);
};


#endif
