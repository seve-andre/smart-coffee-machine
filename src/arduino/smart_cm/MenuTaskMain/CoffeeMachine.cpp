#include "CoffeeMachine.h"
#include "WorkingState.h"
#include "Arduino.h"
#include "MenuSelector.h"
#include "WorkingState.h"
#include "DrinkMaker.h"

MachineState machineState;
MenuSelector* menuSelector;
DrinkMaker* drinkMake;
WorkingState workingState;

CoffeeMachine::CoffeeMachine() {
  machineState = MachineState::WORKING;
  menuSelector = new MenuSelector();
  drinkMake = new DrinkMaker();
  workingState = WorkingState::MENU_SELECTION;
}

void CoffeeMachine::startWorking() {
  switch (workingState) {
    case WELCOME:
    break;
    case READY:
      Serial.println("in ready");
    break;
    case WAIT_FOR_BUTTON_INPUT:
    break;
    case MENU_SELECTION:
      menuSelector->printSelection();
      menuSelector->returnToReadyState();
    break;
    case MAKE_DRINK:
      drinkMake->prepareDrink(menuSelector->getSelected());
    break;
    case TAKE_DRINK:
      Serial.println("Take Drink");
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

void CoffeeMachine::goToState(WorkingState newState) {
  workingState = newState;
}

void CoffeeMachine::goToSleep() {
  
}
void CoffeeMachine::doSelfTest() {
  
}
