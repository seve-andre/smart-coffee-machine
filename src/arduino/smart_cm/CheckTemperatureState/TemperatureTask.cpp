#include "TemperatureTask.h"

TemperatureTask::TemperatureTask() {
  myServo = new ServoMotorImpl(3);
}

void TemperatureTask::moveServo() {
  myServo->startServo();
}

void TemperatureTask::tick() {
  moveServo();
}
