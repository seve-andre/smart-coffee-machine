#ifndef __MENU_SELECTOR__
#define __MENU_SELECTOR__

#include <LiquidCrystal_I2C.h>
#include "Drink.h"


class MenuSelector {
  public:
    MenuSelector();
    void moveNext();
    void movePrev();
    void printSelection();
    void returnToReadyState();
    Drink::Type getSelected();

  private:
    const unsigned int maxNSelection = 2;
    unsigned int currentSelection;
};

#endif
