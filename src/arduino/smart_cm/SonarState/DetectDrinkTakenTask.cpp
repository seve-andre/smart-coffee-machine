#include "DetectDrinkTakenTask.h"
#include "Sonar.h"
#include "Arduino.h"

DetectDrinkTakenTask::DetectDrinkTakenTask() {
  this->proximitySensor = new Sonar();
  this->proximitySensor->initializeTimer();
}

void DetectDrinkTakenTask::tick() {
  if (proximitySensor->isDrinkTaken()) {
    Serial.println("DRINK_TAKED");
  } else {
    Serial.println("DRINK_NOT_TAKED");
  }
  checkTimeTimeout();
}

void DetectDrinkTakenTask::checkTimeTimeout() {
  proximitySensor->timeTimeout();
}
