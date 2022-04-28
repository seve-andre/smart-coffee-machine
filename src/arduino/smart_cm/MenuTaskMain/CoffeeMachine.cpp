#include "CoffeeMachine.h"
#include "WorkingState.h"
#include "Arduino.h"

CoffeeMachine::CoffeeMachine() {
  machineState = IDLE;
}

void CoffeeMachine::startWorking() {
  switch (workingState) {
    case WELCOME:
      Serial.println("Welcome");
      workingState=READY;
    break;
    case READY:
    break;
    case READY_STAND_BY:
    break;
    case MENU_SELECTION:
    break;
    case MAKE_DRINK:
    break;
    case TAKE_DRINK:
    break;
  }
}

void doState() {
  switch (machineState) {
    case IDLE:
    break;
    case WORKING:
    break;
    case SELF_TEST:
    break;
    case SLEEP:
    break;
  }
}

void setMachineState(MachineState newState) {
  machineState = newState;
}

void CoffeeMachine::goToSleep() {
  
}
void CoffeeMachine::doSelfTest() {
  
}
