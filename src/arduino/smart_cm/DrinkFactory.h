#ifndef __DRINK_FACTORY__
#define __DRINK_FACTORY__

#include "Drink.h"

class DrinkFactory {
  public:
    DrinkFactory();
    void initializeServoTimer();
    void makeDrink(Drink::Type drinkType);
    void drinkMakingMessage(Drink::Type drinkType);
    void drinkReadyMessage(Drink::Type drinkType);
    void restartServoTimerStop();
    void resetServoTo0();
    void detachServo();

  private:
    char* drinkFromType(Drink::Type drinkType);
    bool isFirstInitializationServoTimer;
};

#endif
