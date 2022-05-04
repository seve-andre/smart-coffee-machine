#include "CoffeeMachine.h"
#include "WorkingState.h"
#include "Arduino.h"
#include "MenuSelector.h"
#include "WaitButtonState.h"
#include "WorkingState.h"
#include "ReadyState.h"
#include "WelcomeState.h"
#include "DrinkFactory.h"
#include "DetectDrinkTakenTask.h"
#include "Scheduler.h"
#include "servo_motor_impl.h"

#include <avr/sleep.h>

MachineState machineState;
MenuSelector* menuSelector;
WorkingState workingState;
DrinkFactory* drinkFactory;
WelcomeState* welcomeState;
ReadyState* readyState;
WaitButtonState* waitButtonState;

int pos = 0;
bool activeServoCoffeeMachine;
unsigned long tServoCoffeeMachine;

CoffeeMachine::CoffeeMachine() {
  welcomeState = new WelcomeState();
  readyState = new ReadyState();
  waitButtonState = new WaitButtonState();
  
  drinkFactory = new DrinkFactory();
  machineState = MachineState::WORKING;
  menuSelector = new MenuSelector();
  workingState = WorkingState::WELCOME;
  activeServoCoffeeMachine = false;
  tServoCoffeeMachine = millis();
}

void CoffeeMachine::startWorking() {
  switch (workingState) {
    case WELCOME:
      Serial.println("WELCOME");
      welcomeState->welcomeMessage();
      welcomeState->timerWelcomeFinished();
    break;
    case READY:
      //Serial.println("Ready");
      readyState->readyMessage();
    break;
    case WAIT_FOR_BUTTON_INPUT:
      waitButtonState->initButtonsWait();
      waitButtonState->checkButtonsInput();
      menuSelector->restartTimerIdle();
    break;
    case MENU_SELECTION:
      //Serial.println("Menu Selection");
      menuSelector->printSelection();
      menuSelector->returnToReadyState();
      drinkFactory->restartServoTimerStop();
    break;
    case MAKE_DRINK:
      //Serial.println("MAKE_DRINK");
      drinkFactory->drinkMakingMessage(menuSelector->getSelected());
      drinkFactory->initializeServoTimer();
      drinkFactory->makeDrink(menuSelector->getSelected());
    break;
    case TAKE_DRINK:
      drinkFactory->drinkReadyMessage(menuSelector->getSelected());
      // Inserito il drinkMessage in MAKE_DRINK perchè altrimenti interferisce sui valori di Sonar,
      // Da capire perchè Sonar non funziona all'avvio
      isSonarActive = true;
    break;
    case DRINK_TAKEN:
      isSonarActive = false;
      drinkFactory->resetServoTo0();
      workingState = MENU_SELECTION;
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
    case SLEEP:
    break;
    case ASSISTANCE:
      Serial.println("IN ASSISTANCE");
    break;
    case SELF_TEST:
      //Serial.println("Self Test case");
      //CoffeeMachine::goToState(MENU_SELECTION);
    break;
  }
}

void CoffeeMachine::resetServo() {
  drinkFactory->resetServoTo0();
}

void CoffeeMachine::goToWorkingState(WorkingState newState) {
  workingState = newState;
}

void CoffeeMachine::goToMachineState(MachineState newMachineState) {
  machineState = newMachineState;
}

WorkingState CoffeeMachine::getState() {
  return workingState;
}

void CoffeeMachine::goToSleep() {
  Serial.println("SLEEP_MODE_ON");
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
}

void CoffeeMachine::reactivateArduino() {
  sleep_disable();
  Serial.println("SLEEP_MODE_OFF");
}

void CoffeeMachine::doSelfTest() {
  
}
