#include "DetectDrinkTakenTask.h"
#include "Sonar.h"
#include "Arduino.h"
#include "WorkingState.h"
#include "CoffeeMachine.h"

extern bool isSonarActive = false;

DetectDrinkTakenTask::DetectDrinkTakenTask() {
  this->proximitySensor = new Sonar();
  this->proximitySensor->initializeTimer();
}

void DetectDrinkTakenTask::tick() {
  if (isSonarActive) {
    if (proximitySensor->isDrinkTaken()) {
      Serial.println("DRINK_TAKED");
      CoffeeMachine::resetServo();
      CoffeeMachine::goToState(WorkingState::DRINK_TAKED);
      isSonarActive = false;
    } else {
      //Serial.println("DRINK_NOT_TAKED");
      Serial.println(proximitySensor->getDistance());
    }
    checkTimeTimeout();
  }
}

void DetectDrinkTakenTask::checkTimeTimeout() {
  proximitySensor->timeTimeout();
}
