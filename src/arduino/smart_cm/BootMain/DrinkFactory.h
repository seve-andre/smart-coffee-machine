#ifndef __DRINK_FACTORY__
#define __DRINK_FACTORY__

#include "Drink.h"

class DrinkFactory {
  public:
    static Drink* makeDrink(Drink::Type drinkType);
};

#endif
