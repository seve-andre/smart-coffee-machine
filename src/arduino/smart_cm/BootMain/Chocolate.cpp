#include "Drink.h"

class Chocolate: public Drink {
  public:
    void printDrink() {
      printMessage("chocolate");
    }
};
