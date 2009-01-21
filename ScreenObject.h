#ifndef __SCREENOBJECT
#define __SCREENOBJECT
#include <ncurses.h>

class ScreenObject {
  friend class ScreenContext;

public:
  ScreenObject(int x, int y, int sizeX, int sizeY, int v = 0);
  ~ScreenObject();
  void setX(int x) { m_x = x; }
  void setY(int y) { m_y = y; }
  void setAngle(int v) { m_angle = v; }
  void setCenter(int x, int y) { m_centerX = x; m_centerY = y; }
  int getX() { return m_x; }
  int getY() { return m_y; }
  int getAngle() { return m_angle; }


protected:
  ScreenObject() {}
  void setArea(int x, int y, int sizeX, int sizeY, int v = 0, int centerX = 0, int centerY = 0);
  int m_x;
  int m_y;
  int m_sizeX;
  int m_sizeY;
  int m_centerX;
  int m_centerY;
  int m_id;
  int m_angle;
  chtype** m_data;

};

#endif
