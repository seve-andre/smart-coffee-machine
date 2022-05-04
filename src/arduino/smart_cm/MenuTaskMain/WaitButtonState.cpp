#include "WaitButtonState.h"

WaitButtonState::WaitButtonState() {}

void WaitButtonState::initButtonsWait() {
  btnUp = new ButtonImpl(4);
  btnDown = new ButtonImpl(5);
}

void WaitButtonState::checkButtonsInput() {
  delay(50);
  
  if (btnUp->isPressed() || btnDown->isPressed()) {
   CoffeeMachine::goToWorkingState(MENU_SELECTION);
  }
}
