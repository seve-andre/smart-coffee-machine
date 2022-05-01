#include "DrinkFactory.h"
#include "Drink.h"
#include "Tea.cpp"
#include "Coffee.cpp"
#include "Chocolate.cpp"
#include "servo_motor_impl.h"

ServoMotorImpl* myServo;
Drink* drinkElement;

DrinkFactory::DrinkFactory() {
  myServo = new ServoMotorImpl(3);
  isFirstInitializationServoTimer = false;
}

void DrinkFactory::makeDrink(Drink::Type drinkType) {   
  myServo->startServo();
 
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
    myServo->startServoTimers();
  }
}

////////////////////////////////////////////////
//
//void DrinkPrinter::drinkMakingMessage(Drink::Type drinkType) {
//  char drinkMessage[100] = { drinkFromType(drinkType) };
//  Lcd::getInstance()->print((String("making a ") + drinkMessage + String("...")).c_str ());
//}
//
//void DrinkPrinter::drinkReadyMessage(Drink::Type drinkType) {
//  char drinkMessage[100] = { drinkFromType(drinkType) };
//  Lcd::getInstance()->print((String("The ") + drinkMessage + String(" is ready.")).c_str ());
//}
//
//char* DrinkPrinter::drinkFromType(Drink::Type drinkType) {
//  char drinkMessage[10];
//  
//  switch (drinkType) {
//    case Drink::Coffee:
//      strcpy(drinkMessage, "Coffee");
//    break;
//    
//    case Drink::Tea:
//      strcpy(drinkMessage, "Tea");
//    break;
//    
//    case Drink::Chocolate:
//      strcpy(drinkMessage, "Chocolate");
//    break;
//  }
//
//  return drinkMessage;
//}
