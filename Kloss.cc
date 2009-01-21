#include "ScreenContext.h"
#include "Kloss.h"
#include <time.h>
#include <stdlib.h>

Kloss::Kloss(ScreenContext* scr) : m_scr(scr) {
  // Slumpa fram typ
  srand(time(NULL));
  m_typ = (Klosstyp)(rand() % 7);

  // Fyll m_data med något vettigt
  switch (m_typ) {
  case fyrkant:
    setArea(m_scr->getWidth() / 2 - 2, 0, 4, 2);
    m_data[0][0] = '[' | COLOR_PAIR(7);
    m_data[0][1] = ']' | COLOR_PAIR(7);
    m_data[0][2] = '[' | COLOR_PAIR(7);
    m_data[0][3] = ']' | COLOR_PAIR(7);
    m_data[1][0] = '[' | COLOR_PAIR(7);
    m_data[1][1] = ']' | COLOR_PAIR(7);
    m_data[1][2] = '[' | COLOR_PAIR(7);
    m_data[1][3] = ']' | COLOR_PAIR(7);
    break;

  case pinne:
    setArea(m_scr->getWidth() / 2 - 1, 0, 2, 4, 0, 0, 2);
    m_data[0][0] = '[' | COLOR_PAIR(1);
    m_data[0][1] = ']' | COLOR_PAIR(1);
    m_data[1][0] = '[' | COLOR_PAIR(1);
    m_data[1][1] = ']' | COLOR_PAIR(1);
    m_data[2][0] = '[' | COLOR_PAIR(1);
    m_data[2][1] = ']' | COLOR_PAIR(1);
    m_data[3][0] = '[' | COLOR_PAIR(1);
    m_data[3][1] = ']' | COLOR_PAIR(1);
    break;

  case zL:
    setArea(m_scr->getWidth() / 2 - 3, 0, 6, 2);
    m_data[0][0] = '[' | COLOR_PAIR(2);
    m_data[0][1] = ']' | COLOR_PAIR(2);
    m_data[0][2] = '[' | COLOR_PAIR(2);
    m_data[0][3] = ']' | COLOR_PAIR(2);
    m_data[0][4] = 0;
    m_data[0][5] = 0;
    m_data[1][0] = 0;
    m_data[1][1] = 0;
    m_data[1][2] = '[' | COLOR_PAIR(2);
    m_data[1][3] = ']' | COLOR_PAIR(2);
    m_data[1][4] = '[' | COLOR_PAIR(2);
    m_data[1][5] = ']' | COLOR_PAIR(2);
    break;

  case zR:
    setArea(m_scr->getWidth() / 2 - 3, 0, 6, 2);
    m_data[0][0] = 0;
    m_data[0][1] = 0;
    m_data[0][2] = '[' | COLOR_PAIR(3);
    m_data[0][3] = ']' | COLOR_PAIR(3);
    m_data[0][4] = '[' | COLOR_PAIR(3);
    m_data[0][5] = ']' | COLOR_PAIR(3);
    m_data[1][0] = '[' | COLOR_PAIR(3);
    m_data[1][1] = ']' | COLOR_PAIR(3);
    m_data[1][2] = '[' | COLOR_PAIR(3);
    m_data[1][3] = ']' | COLOR_PAIR(3);
    m_data[1][4] = 0;
    m_data[1][5] = 0;
    break;

  case lL:
    setArea(m_scr->getWidth() / 2 - 3, 0, 6, 2);
    m_data[0][0] = 0;
    m_data[0][1] = 0;
    m_data[0][2] = 0;
    m_data[0][3] = 0;
    m_data[0][4] = '[' | COLOR_PAIR(4);
    m_data[0][5] = ']' | COLOR_PAIR(4);
    m_data[1][0] = '[' | COLOR_PAIR(4);
    m_data[1][1] = ']' | COLOR_PAIR(4);
    m_data[1][2] = '[' | COLOR_PAIR(4);
    m_data[1][3] = ']' | COLOR_PAIR(4);
    m_data[1][4] = '[' | COLOR_PAIR(4);
    m_data[1][5] = ']' | COLOR_PAIR(4);
    break;

  case lR:
    setArea(m_scr->getWidth() / 2 - 3, 0, 6, 2);
    m_data[0][0] = '[' | COLOR_PAIR(5);
    m_data[0][1] = ']' | COLOR_PAIR(5);
    m_data[0][2] = 0;
    m_data[0][3] = 0;
    m_data[0][4] = 0;
    m_data[0][5] = 0;
    m_data[1][0] = '[' | COLOR_PAIR(5);
    m_data[1][1] = ']' | COLOR_PAIR(5);
    m_data[1][2] = '[' | COLOR_PAIR(5);
    m_data[1][3] = ']' | COLOR_PAIR(5);
    m_data[1][4] = '[' | COLOR_PAIR(5);
    m_data[1][5] = ']' | COLOR_PAIR(5);
    break;

 case t:
    setArea(m_scr->getWidth() / 2 - 3, 0, 6, 2);
    m_data[0][0] = 0;
    m_data[0][1] = 0;
    m_data[0][2] = '[' | COLOR_PAIR(6);
    m_data[0][3] = ']' | COLOR_PAIR(6);
    m_data[0][4] = 0;
    m_data[0][5] = 0;
    m_data[1][0] = '[' | COLOR_PAIR(6);
    m_data[1][1] = ']' | COLOR_PAIR(6);
    m_data[1][2] = '[' | COLOR_PAIR(6);
    m_data[1][3] = ']' | COLOR_PAIR(6);
    m_data[1][4] = '[' | COLOR_PAIR(6);
    m_data[1][5] = ']' | COLOR_PAIR(6);
    break;
  }
  // Fixa fin X-pos
  calcX();
}

void Kloss::activate() {
  // Tryck upp på skärmen
  m_scr->add(this);
}

void Kloss::advance() {
  // Flytta ner
  setY(getY() + 1);
  m_scr->redraw();
}

void Kloss::moveL() {
  // Flytta vänster
  setX(getX() - 2);
  m_scr->redraw();
}

void Kloss::moveR() {
  // Flytta höger
  setX(getX () + 2);
  m_scr->redraw();
}

int Kloss::calcX() {
  // Räkna ut en lämplig X-position
  int x = m_scr->getWidth() / 2 - m_sizeX / 2;

  if (x%2 != 0)
    x++;

  setX(x);

  return x;
}

void Kloss::rotate() {
  // Rotera 90 grader
  m_angle += 90;
  if (m_angle >= 360)
    m_angle = 0;

  m_scr->redraw();
}
