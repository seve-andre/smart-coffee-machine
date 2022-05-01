#ifndef __DRINK__
#define __DRINK__

#include "Arduino.h"

class Drink {
  public:
    Drink(int id) {
      this->id = id;
    };
    enum Type {
      Tea,
      Coffee,
      Chocolate
    };
    int getId();

  private:
    int id;
};

#endif
