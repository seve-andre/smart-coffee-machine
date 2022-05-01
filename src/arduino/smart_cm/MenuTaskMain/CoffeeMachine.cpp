#include "CoffeeMachine.h"
#include "WorkingState.h"
#include "Arduino.h"
#include "MenuSelector.h"
#include "WorkingState.h"
#include "DrinkFactory.h"
#include "servo_motor_impl.h"

MachineState machineState;
MenuSelector* menuSelector;
WorkingState workingState;
//ServoMotorImpl* myServo;
DrinkFactory* drinkFactory;
int pos = 0;

CoffeeMachine::CoffeeMachine() {
  drinkFactory = new DrinkFactory();
  machineState = MachineState::WORKING;
  menuSelector = new MenuSelector();
  workingState = WorkingState::MENU_SELECTION;
  //myServo = new ServoMotorImpl(3);
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
      //Serial.println("Make Drink");
      drinkFactory->initializeServoTimer();
      drinkFactory->makeDrink(menuSelector->getSelected());
      //myServo->setPosition(180);
      //myServo->setPosition(0);
      //myServo->startServo();
      //myServo->setPosition(pos);
      //pos+=3;

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
