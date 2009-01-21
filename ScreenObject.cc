#include "ScreenObject.h"
#include <ncurses.h>

ScreenObject::ScreenObject(int x, int y, int sizeX, int sizeY, int v) {
  setArea(x, y, sizeX, sizeY, v);
}

void ScreenObject::setArea(int startX, int startY, int sizeX, int sizeY, int v, int centerX, int centerY) {
  // Allokera m_data
  m_data = new chtype*[sizeY];
  for (int y = 0; y < sizeY; y++) {
    m_data[y] = new chtype[sizeX];
    for (int x = 0; x < sizeX; x++)
      m_data[y][x] = 0;
  }

  // Fixa fina medlemsvariabler
  m_x = startX;
  m_y = startY;
  m_sizeX = sizeX;
  m_sizeY = sizeY;
  m_angle = v;
  m_centerX = centerX;
  m_centerY = centerY;
}

ScreenObject::~ScreenObject() {
  // Deallokera m_data
  for (int y = 0; y < m_sizeY; y++)
    delete[] m_data[y];
  delete[] m_data;
}
