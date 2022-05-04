#include "ReadyState.h"
#include "ButtonImpl.h"
#include "CoffeeMachine.h"
#include "Lcd.h"
#include "Arduino.h"

ReadyState::ReadyState() {}

void ReadyState::initButtonsReady() {
}

void ReadyState::readyMessage() {
  Lcd::getInstance()->clear();
  Lcd::getInstance()->print("Ready");
  Serial.println("Ready");
  CoffeeMachine::goToWorkingState(WAIT_FOR_BUTTON_INPUT);
}
