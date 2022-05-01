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
bool activeServoCoffeeMachine;
unsigned long tServoCoffeeMachine;

CoffeeMachine::CoffeeMachine() {
  drinkFactory = new DrinkFactory();
  machineState = MachineState::WORKING;
  menuSelector = new MenuSelector();
  workingState = WorkingState::MENU_SELECTION;
  //myServo = new ServoMotorImpl(3);
  activeServoCoffeeMachine = false;
  tServoCoffeeMachine = millis();
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
    break;
    case TAKE_DRINK:
      //DrinkPrinter::
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

////Da capire perchè se inserito in un altra classe il timer si incasina e non va
//void CoffeeMachine::doMake() {
//  moveServoTo180CoffeeMachine();
//  //stopServo();
//  timerServoCoffeeMachine();
//}
//
//void CoffeeMachine::moveServoTo180CoffeeMachine() {
//  if (pos < 180 && activeServoCoffeeMachine) {
//    activeServoCoffeeMachine = false;                       // tell servo to go to position in variable 'pos'
//    
//    noInterrupts();
//    pos += 3;
//    interrupts();
//    
//    myServo->setPosition(pos);
//    Serial.println(pos);
//    delay(15);                                // waits 90ms for the servo to reach the position
//  } else if(pos >= 180) {
//    CoffeeMachine::goToState(WorkingState::TAKE_DRINK);
//    //DrinkFactory::printReadyDrink();
//  }
//}
//
////Timer per tick di Servo
//void CoffeeMachine::timerServoCoffeeMachine() {  
//  //Interrupt
//  if ((millis() - tServoCoffeeMachine) >= 165) {
//      Serial.println("active servo");
//      tServoCoffeeMachine = millis();
//      activeServoCoffeeMachine = true;
//  }
//}
