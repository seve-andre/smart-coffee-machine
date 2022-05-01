#ifndef __DRINK__
#define __DRINK__

#include "Arduino.h"

class Drink {
  public:
    enum Type {
      Tea,
      Coffee,
      Chocolate
    };
    virtual void printDrink() = 0;
    void prepareDrink();
    void printDrinkReady() {
      Type typeDrink;
      
      switch(typeDrink) {
      case Type::Tea:
        Serial.println("The Coffee is ready");
      break;

      case Coffee:
        Serial.println("The Tea is ready");
      break;

      case Chocolate:
        Serial.println("The Chocolate is ready");
      break;
      }   
    };

  protected:
    void printMessage(char msg) {
        //lcd.print("making a " + msg + "...");
    };

    private:
      unsigned int quantity;
};

#endif
