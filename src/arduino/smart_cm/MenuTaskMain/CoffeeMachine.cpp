#include "CoffeeMachine.h"
#include "WorkingState.h"
#include "Arduino.h"
#include "MenuSelector.h"
#include "WorkingState.h"
#include "DrinkFactory.h"
#include "DetectDrinkTakenTask.h"
#include "Scheduler.h"
#include "servo_motor_impl.h"

MachineState machineState;
MenuSelector* menuSelector;
WorkingState workingState;
DrinkFactory* drinkFactory;

int pos = 0;
bool activeServoCoffeeMachine;
unsigned long tServoCoffeeMachine;

CoffeeMachine::CoffeeMachine() {
  drinkFactory = new DrinkFactory();
  machineState = MachineState::WORKING;
  menuSelector = new MenuSelector();
  workingState = WorkingState::MENU_SELECTION;
  activeServoCoffeeMachine = false;
  tServoCoffeeMachine = millis();
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
      menuSelector->returnToReadyState();
    break;
    case MAKE_DRINK:
      drinkFactory->drinkMakingMessage(menuSelector->getSelected());
      drinkFactory->initializeServoTimer();
      drinkFactory->makeDrink(menuSelector->getSelected());
    break;
    case TAKE_DRINK:
      drinkFactory->drinkReadyMessage(menuSelector->getSelected());
      isSonarActive = true;
    break;
    case DRINK_TAKED:
      Serial.println("user takes the drink");
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
