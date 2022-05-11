#ifndef __BEVERAGE_STORE__
#define __BEVERAGE_STORE__

#include "Drink.h"

class BeverageStore {
  public:
    BeverageStore();
    BeverageStore(unsigned int n_coffee, unsigned int n_tea, unsigned int n_chocolate);
    void reduceQuantity(Drink::Type drinkType);
    unsigned int getQuantity(Drink::Type drinkType);
    void refill();

  private:
    unsigned int n_coffee;
    unsigned int n_tea;
    unsigned int n_chocolate;
};

#endif
