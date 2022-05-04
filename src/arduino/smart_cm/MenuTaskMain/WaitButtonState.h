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

  private:
    ButtonImpl* btnUp;
    ButtonImpl* btnDown;
    ButtonImpl* btnMake;
};

#endif
