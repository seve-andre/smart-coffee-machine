#include "CoffeeMachine.h"
#include "WorkingState.h"
#include "Arduino.h"
#include "MenuSelector.h"

MachineState machineState;
MenuSelector* menuSelector;

CoffeeMachine::CoffeeMachine() {
  machineState = MachineState::WORKING;
  menuSelector = new MenuSelector();
  workingState = MENU_SELECTION;
}

void CoffeeMachine::startWorking() {
  switch (workingState) {
    case WELCOME:
    break;
    case READY:
    break;
    case WAIT_FOR_BUTTON_INPUT:
    break;
    case MENU_SELECTION:
      menuSelector->printSelection();
    break;
    case MAKE_DRINK:
      Serial.println("preparo drink");
    break;
    case TAKE_DRINK:
    break;
  }
}

void CoffeeMachine::doState() {
  switch (machineState) {
    case IDLE:
    break;
    case WORKING:
      this->startWorking();
    break;
    case SELF_TEST:
    break;
    case SLEEP:
    break;
  }
}

void CoffeeMachine::nextWorkingState() {
  workingState = MAKE_DRINK;
}

void CoffeeMachine::goToSleep() {
  
}
void CoffeeMachine::doSelfTest() {
  
}
