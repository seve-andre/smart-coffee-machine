#ifndef __DRINK_FACTORY__
#define __DRINK_FACTORY__

#include "Drink.h"

class DrinkFactory {
  public:
    DrinkFactory();
    void initializeServoTimer();
    void makeDrink(Drink::Type drinkType);
    //Drink* printReadyDrink();

  private:
    bool isFirstInitializationServoTimer;
};

#endif
