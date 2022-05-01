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
      drinkElement = new Tea();
      break;
    case Drink::Type::Coffee:
      drinkElement = new Coffee();
      break;
    case Drink::Type::Chocolate:
      drinkElement = new Chocolate();
      break;
  }
}

void DrinkFactory::initializeServoTimer() {
  if (!isFirstInitializationServoTimer) {
    isFirstInitializationServoTimer = true;
    myServo->startServoTimer();
  }
}
