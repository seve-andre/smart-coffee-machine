#include "CoffeeMachine.h"
#include "WorkingState.h"
#include "Arduino.h"
#include "MenuSelector.h"
#include "WaitButtonState.h"
#include "ReadyState.h"
#include "WelcomeState.h"
#include "DrinkFactory.h"
#include "DetectDrinkTakenTask.h"
#include "Scheduler.h"
#include "ServoMotorImpl.h"
#include "TemperatureTask.h"
#include "Lcd.h"

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

bool firstTimeAssistance = true;
bool firstTimeSelfTest = true;

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
      Serial.println("idle");
      welcomeState->welcomeMessage();
      welcomeState->timerWelcomeFinished();
    break;
    case READY:
      Serial.println("idle");
      waitButtonState->resetFirstTime();
      readyState->readyMessage();
    break;
    case WAIT_FOR_BUTTON_INPUT:
      Serial.println("idle");
      waitButtonState->initButtonsWait();
      waitButtonState->checkButtonsInput();
      menuSelector->restartTimerIdle();
    break;
    case MENU_SELECTION:
      myServo->resetPosition();
      Serial.println("working");
      //Serial.println("Menu Selection");
      menuSelector->printSelection();
      menuSelector->returnToReadyState();
      drinkFactory->restartServoTimerStop();
    break;
    case MAKE_DRINK:
      Serial.println("working");
      //Serial.println("MAKE_DRINK");
      drinkFactory->drinkMakingMessage(menuSelector->getSelected());
      drinkFactory->initializeServoTimer();
      drinkFactory->makeDrink(menuSelector->getSelected());
    break;
    case TAKE_DRINK:
      Serial.println("working");
      drinkFactory->drinkReadyMessage(menuSelector->getSelected());
      // Inserito il drinkMessage in MAKE_DRINK perchè altrimenti interferisce sui valori di Sonar,
      // Da capire perchè Sonar non funziona all'avvio
      isSonarActive = true;
    break;
    case DRINK_TAKEN:
      Serial.println("working");
      isSonarActive = false;
      firstTime = true;
      drinkFactory->resetServoTo0();
      workingState = READY;
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
      Lcd::getInstance()->print("Assistance required");
      if (firstTimeAssistance) {
        Serial.println("assistance");
        firstTimeAssistance = false;  
      }

      if (Serial.available() > 0) {
        String msg = Serial.readString();
        if (msg == "Refill\n") {
          menuSelector->refill();
          machineState = WORKING;
          workingState = READY;
          firstTimeAssistance = true;
        }
      }
    break;
    case SELF_TEST:
      Lcd::getInstance()->print("Assistance required");
      if (firstTimeSelfTest) {
        Serial.println("self test");
        firstTimeSelfTest = false;
      }

      if (Serial.available() > 0) {
        String msg = Serial.readString();
        if (msg == "Recover\n") {
          machineState = WORKING;
          workingState = READY;
          firstTimeSelfTest = true;
        }
      }
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

MachineState CoffeeMachine::getMachineState() {
  return machineState;
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
