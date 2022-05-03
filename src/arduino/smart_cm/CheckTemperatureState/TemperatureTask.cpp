#include "TemperatureTask.h"
#include "TempSensorImpl.h"

TempSensor* tempSensor;
ServoMotorImpl* myServo;

TemperatureTask::TemperatureTask() {
  tempSensor = new TempSensorLM35(0);
  myServo = new ServoMotorImpl(3);
}

void TemperatureTask::moveServo() {
  myServo->startServo();
}

void TemperatureTask::tick() {  
  Serial.println(tempSensor->getTemperature());
  moveServo();
  
  if (!isTemperatureInRange()) {
    Serial.println("cambio stato");
  }
}

bool TemperatureTask::isTemperatureInRange() {
  float temp = tempSensor->getTemperature();
  Serial.println(temp);
  
  return (temp > 17.0 && temp < 24.0);
}
