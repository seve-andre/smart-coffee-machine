#include "DetectDrinkTakenTask.h"
#include "Sonar.h"
#include "Arduino.h"
#include "WorkingState.h"
#include "CoffeeMachine.h"

extern bool isSonarActive = false;
bool firstTime = true;

DetectDrinkTakenTask::DetectDrinkTakenTask() {
  this->proximitySensor = new Sonar();
}

void DetectDrinkTakenTask::tick() {
  if (isSonarActive) {
    if (firstTime) {
      this->proximitySensor->initializeTimer();
      firstTime = false;
    }

    if (proximitySensor->isDrinkTaken()) {
      Serial.println("DRINK_TAKEN");
      CoffeeMachine::resetServo();
      CoffeeMachine::goToWorkingState(WorkingState::DRINK_TAKEN);
      isSonarActive = false;
    } else {
      Serial.println(proximitySensor->getDistance());
    }
    checkTimeTimeout();
  }
}

void DetectDrinkTakenTask::checkTimeTimeout() {
  proximitySensor->timeTimeout();
}
