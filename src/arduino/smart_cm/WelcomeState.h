#ifndef __WELCOME_STATE__
#define __WELCOME_STATE__

#include "BeverageStore.h"
#include <LiquidCrystal_I2C.h>

class WelcomeState {
  public:
    WelcomeState();
    void welcomeMessage();
    void timerWelcomeFinished();

  private:
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
};

#endif
