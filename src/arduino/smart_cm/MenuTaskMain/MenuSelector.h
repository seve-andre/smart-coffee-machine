#ifndef __MENU_SELECTOR__
#define __MENU_SELECTOR__

#include "Drink.h"
#include "ButtonImpl.h"

class MenuSelector {
  public:
    MenuSelector();
    Drink::Type getSelected();
    void moveNext();
    void movePrev();
    void printSelection();
    void returnToReadyState();
    void restartTimerIdle();
    void refill();

  private:
    bool drinksAvailable();
  
    ButtonImpl* btnUp;
    ButtonImpl* btnDown;
    ButtonImpl* btnMake;
    const unsigned int maxNSelection = 2;
    unsigned int currentSelection;
};

#endif
