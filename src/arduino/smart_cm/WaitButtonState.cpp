#include "WaitButtonState.h"

WaitButtonState::WaitButtonState() {
  btnUp = new ButtonImpl(4);
  btnDown = new ButtonImpl(5);
}

void WaitButtonState::resetFirstTime() {
  this->firstTime = true;
}

void WaitButtonState::initButtonsWait() {
  if (firstTime) {
    btnUp = new ButtonImpl(4);
    btnDown = new ButtonImpl(5);
    firstTime = false;
  }
}

void WaitButtonState::checkButtonsInput() {
  delay(50);
  
  if (btnUp->isPressed() || btnDown->isPressed()) {
   CoffeeMachine::goToWorkingState(MENU_SELECTION);
  }
}
