#ifndef __DRINK_MAKER__
#define __DRINK_MAKER__

#include "Drink.h"

class DrinkMaker {
  private:
    
  public:
    DrinkMaker();
    void startTimerServo();
    void simulateServo();
    void prepareDrink(Drink::Type drinkType);
    static void nextWorkingState();
};

#endif
