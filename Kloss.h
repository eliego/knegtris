#include "ScreenContext.h"
#include "ScreenObject.h"

enum Klosstyp { fyrkant, pinne, zR, zL, lL, lR, t };

class Kloss : public ScreenObject {
public:
  Kloss(ScreenContext* scr);
  void advance();
  void moveR();
  void moveL();
  void activate();
  void rotate();

private:
  int calcX();
  Klosstyp m_typ;
  ScreenContext* m_scr;
};
