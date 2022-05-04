#include "DrinkFactory.h"
#include "Drink.h"
#include "Tea.cpp"
#include "Coffee.cpp"
#include "Chocolate.cpp"
#include "Lcd.h"
#include "servo_motor_impl.h"

ServoMotorImpl* myServo;
Drink* drinkElement;
char drinkMessage[10];

DrinkFactory::DrinkFactory() {
  myServo = new ServoMotorImpl(3);
  isFirstInitializationServoTimer = false;
}

void DrinkFactory::makeDrink(Drink::Type drinkType) {
  myServo->startServoMakeDrink();
 
  switch(drinkType) {
    case Drink::Type::Tea:
      drinkElement = new Tea(0);
      break;
    case Drink::Type::Coffee:
      drinkElement = new Coffee(1);
      break;
    case Drink::Type::Chocolate:
      drinkElement = new Chocolate(2);
      break;
  }
}

void DrinkFactory::initializeServoTimer() {
  if (!isFirstInitializationServoTimer) {
    isFirstInitializationServoTimer = true;
    myServo->startServoMakeDrink();
  }
}

void DrinkFactory::resetServoTo0() {
  myServo->resetServo();
}

void DrinkFactory::restartServoTimerStop() {
  myServo->restartTimerStop();
}

////////////////////////////////////////////////
//

void DrinkFactory::drinkMakingMessage(Drink::Type drinkType) {
  char drinkMessage[100];

  switch (drinkType) {
    case Drink::Coffee:
      strcpy(drinkMessage, "Coffee");
    break;
    
    case Drink::Tea:
      strcpy(drinkMessage, "Tea");
    break;
    
    case Drink::Chocolate:
      strcpy(drinkMessage, "Chocolate");
    break;
  }
  
  Lcd::getInstance()->print((String("making a ") + drinkMessage + String("...")).c_str ());
}

void DrinkFactory::drinkReadyMessage(Drink::Type drinkType) {
  char drinkMessage[100];

  switch (drinkType) {
    case Drink::Coffee:
      strcpy(drinkMessage, "Coffee");
    break;
    
    case Drink::Tea:
      strcpy(drinkMessage, "Tea");
    break;
    
    case Drink::Chocolate:
      strcpy(drinkMessage, "Chocolate");
    break;
  }
  
  Lcd::getInstance()->print((String("The ") + (String) drinkMessage + String(" is ready.")).c_str ());
  Serial.println(drinkMessage);
}

void DrinkFactory::detachServo() {
  myServo->off();
}


char* DrinkFactory::drinkFromType(Drink::Type drinkType) {
  switch (drinkType) {
    case Drink::Coffee:
      return "Coffee";
    break;
    
    case Drink::Tea:
      return "Tea";
    break;
    
    case Drink::Chocolate:
      return "Chocolate";
    break;
  }

  return drinkMessage;
}
