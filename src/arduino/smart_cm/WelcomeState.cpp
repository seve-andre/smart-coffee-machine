#include "CoffeeMachine.h"
#include "WelcomeState.h"
#include "Lcd.h"

#define TIME_WELCOME 2000

unsigned long tWelcome;
bool tWelcomeStarted;

WelcomeState::WelcomeState() {
  tWelcomeStarted = false;
}

void WelcomeState::welcomeMessage() {
  if (!tWelcomeStarted) {
    tWelcomeStarted = true;
    Lcd::getInstance()->clear();
    Lcd::getInstance()->print("Welcome to the Smart Coffee Machine");
    Serial.println("Welcome to the Smart Coffee Machine");
    tWelcome = millis();
  }

  timerWelcomeFinished();
}

void WelcomeState::timerWelcomeFinished() {
  if ((millis() - tWelcome) >= TIME_WELCOME) {
    CoffeeMachine::goToWorkingState(READY);
  }
}
