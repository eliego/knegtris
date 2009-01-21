#include "ScreenContext.h"
#include "ScreenObject.h"
#include "Exception.h"
#include <map>
#include <ncurses.h>
#include <fstream>

#include <math.h>



using namespace std;

void ScreenContext::setArea(int startx, int starty, int sizeX, int sizeY) {
  // Kolla så att värdena inte går utanför skärmen
  if (startx + sizeX > COLS || starty + sizeY > LINES || startx < 0 || starty < 0 || sizeX < 0 || sizeY < 0)
    throw InvalidValues("Values exceed drawable screen, or is less than 0");

  // Skapa fönster
  m_screen = newwin(sizeY + 2, sizeX + 2, starty, startx);
  box(m_screen, 0, 0);
  wrefresh(m_screen);


  // Initiera datavektor
  m_data = new chtype*[sizeY];
  for (int y = 0; y < sizeY; y++) {
    m_data[y] = new chtype[sizeX];
    for (int x = 0; x < sizeX; x++)
      m_data[y][x] = 0;
  }

  // Spara medlemsvariablar
  m_x = startx;
  m_y = starty;
  m_sizeX = sizeX;
  m_sizeY = sizeY;
}

void ScreenContext::add(ScreenObject* obj) {
  // Lägg till objektet och rita skärmen
  m_objects[++m_counter] = obj;
  obj->m_id = m_counter;

  redraw();
}

void ScreenContext::del(int id) {
  // Ta bort objektet och rita skärmen
  m_objects.erase(m_objects.find(id));

  redraw();
}

void ScreenContext::redraw() {

  std::ofstream fil("knegtris.out");
  fil <<"m_sizeX is "<<m_sizeX<<std::endl;
  fil <<"m_sizeY is "<<m_sizeY<<std::endl;


  // Börja med att uppdatera m_data

  // Loppa igenom alla objekt
  map<int, ScreenObject*>::iterator obj;
  for (obj = m_objects.begin(); obj != m_objects.end(); obj++) {

    // Kolla så att objektet inte ligger utanför ramarna
    if (obj->second->m_x < 0 || obj->second->m_y < 0 || obj->second->m_x + obj->second->m_sizeX > m_sizeX || obj->second->m_y + obj->second->m_sizeY > m_sizeY || obj->second->m_angle > 360 || obj->second->m_angle < 0)
	throw InvalidPosition("Object is outside the screen!");

    int y2, x2;

    // Loopa igenom objektets koordinater
    for (int y = 0; y < obj->second->m_sizeY; y++)
      for (int x = 0; x < obj->second->m_sizeX; x++) {
	// Skall aktuell position ritas ut?
	if (obj->second->m_data[y][x] != 0) {
	  // Ja det skall den, kolla om den ska roteras och hur mycket
	  if (obj->second->m_angle != 0 && obj->second->m_angle != 360) {
	    if (obj->second->m_angle == 90) {
	      x2 = y;
	      y2 = x;
	    } else if (obj->second->m_angle == 180) {
	      x2 = obj->second->m_sizeX - x;
	      y2 = obj->second->m_sizeY - y;
	    } else if (obj->second->m_angle == 270) {
	      x2 = obj->second->m_sizeY - y;
	      y2 = obj->second->m_sizeX - x;
	    } else {
	      // Ja det ska vi, räkna
	      //	      x2 = cos(obj->second->m_angle) * (x - obj->second->m_centerX);
	      //x2 -= sin(obj->second->m_angle) * (y - obj->second->m_centerY);
	      //x2 += obj->second->m_centerX;
	      //y2 = sin(obj->second->m_angle) * (x - obj->second->m_centerX);
	      //y2 += cos(obj->second->m_angle) * (y - obj->second->m_centerY);
	      //y2 += obj->second->m_centerY;
	    }
	  } else { // Nej, det skall den inte
	    x2 = x;
	    y2 = y;
	  }
	  // Kolla nu om positionen är ockuperad
	  if (m_data[y2 + obj->second->m_y][x2 + obj->second->m_x] == 0) 
	    // Nej det är den inte, kolla en gång till för säkehets skull och rita
	    if (y2 + obj->second->m_y >= m_sizeY - 1)
	      fil <<"GURGEL"<<std::endl;
	    else {
	      fil <<"Writing "<<x2+obj->second->m_x<<":"<<y2+obj->second->m_y<<":"<<m_sizeY<<std::endl;
	      m_data[y2 + obj->second->m_y][x2 + obj->second->m_x] = obj->second->m_data[y][x]; }
	  else
	    // Jepp det är den, kasta
	    throw Collision("Collision between objects!");
	}
      }
  }
  
  // Okej, uppdatera nu skärmen
  
  // Loopa igenom alla koordinater
  for (int y = 0; y < m_sizeY; y++)
    for (int x = 0; x < m_sizeX; x++) {
      // Skriv ut och töm!
      if (m_data[y][x] != 0)
	mvwaddch(m_screen, y + 1, x + 1, m_data[y][x]);
      else
	mvwaddch(m_screen, y + 1, x + 1, ' ');
      m_data[y][x] = 0;
    }
  
  // Rita om vår ruta
  wrefresh(m_screen);
}

ScreenContext::ScreenContext() : m_screen(0), m_counter(0) {
  // Initiera area
  setArea(0, 0, COLS, LINES);
}

ScreenContext::ScreenContext(int startX, int startY, int sizeX, int sizeY) : m_screen(0), m_counter(0) {
  // Initiera area
  setArea(startX, startY, sizeX, sizeY);
}

ScreenContext::~ScreenContext() {
  // Ta bort fönster
  wborder(m_screen, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(m_screen);
  delwin(m_screen);

  // Ta bort m_data
  for (int y = 0; y < m_sizeY; y++)
    delete[] m_data[y];
  delete[] *m_data;
}
