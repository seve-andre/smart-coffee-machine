#include "TemperatureTask.h"
#include "TempSensorImpl.h"

TempSensor* tempSensor;

TemperatureTask::TemperatureTask() {
  tempSensor = new TempSensorLM35(0);
  myServo = new ServoMotorImpl(3);
}

void TemperatureTask::moveServo() {
  myServo->startServo();
}

void TemperatureTask::tick() {
  if (!myServo->isServoFinish()) {
    moveServo();
  } else {
    if (checkTemperatureRange()) {
      //Serial.println("cambio stato");
      //lcd.print("Assistance Required");
    }
  }
}

bool TemperatureTask::checkTemperatureRange() {
  return (tempSensor->getTemperature() < 17.0 || tempSensor->getTemperature() >= 24.0);
}
