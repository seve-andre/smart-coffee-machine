#include "Drink.h"

class Tea: public Drink {
  public:
    void printDrink() {
      printMessage("tea");
    }
};
