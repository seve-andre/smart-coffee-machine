#ifndef __WAIT_BUTTON_STATE__
#define __WAIT_BUTTON_STATE__

#include "CoffeeMachine.h"
#include "ButtonImpl.h"
#include "WorkingState.h"
#include "Arduino.h"

class WaitButtonState {
  public:
    WaitButtonState();
    void initButtonsWait();
    void checkButtonsInput();
    void resetFirstTime();

  private:
    ButtonImpl* btnUp;
    ButtonImpl* btnDown;
    bool firstTime;
};

#endif
