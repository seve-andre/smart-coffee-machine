#include "DrinkMaker.h"
#include "Arduino.h"
#include "CoffeeMachine.h"

unsigned long Tmaking;
bool TmakingStarted;

DrinkMaker::DrinkMaker() {
  TmakingStarted = false;
}

void DrinkMaker::prepareDrink(Drink::Type drinkType) {
  startTimerServo();
  simulateServo();
}


//inserire logica del Servo
void DrinkMaker::simulateServo() {  
  //Interrupt
  if ((millis() - Tmaking) >= 10000) {
      Tmaking = millis();
      //lcd.setCursor(1,0);
      //lcd.clear();
      Serial.println("Drink Ready");
      CoffeeMachine::goToState(WorkingState::TAKE_DRINK);
  }
}

void DrinkMaker::startTimerServo() {
  if (!TmakingStarted) {
    TmakingStarted = true;
    Tmaking = millis();
  }
}
