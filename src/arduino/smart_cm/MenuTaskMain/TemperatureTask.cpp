#include "TemperatureTask.h"
#include "TempSensorImpl.h"
#include "CoffeeMachine.h"

TempSensor* tempSensor;

unsigned long tSelfTest;
bool startSelfTest = true;

TemperatureTask::TemperatureTask() {
  tempSensor = new TempSensorLM35(0);
  //myServo = new ServoMotorImpl(3);
  tSelfTest = millis();
  startSelfTest = true;
}

void TemperatureTask::moveServo() {
  //myServo->startServoSelfTest();
}

void TemperatureTask::tick() {
//  startSelfTest = true;
//  
//  if (startSelfTest) {

  Serial.println(tempSensor->getTemperature());
  moveServo();
  
  if (!isTemperatureInRange()) {
    //CoffeeMachine::goToState(SELF_TEST);
  }
}

bool TemperatureTask::isTemperatureInRange() {
  float temp = tempSensor->getTemperature();
  //Serial.println(temp);
  
  return (temp > 17.0 && temp < 24.0);
}

void interruptTimerSelfTest() {
  //Interrupt
  if ((millis() - tSelfTest) >= 180000) {
    Serial.println("DO Temperature check");
    tSelfTest = millis();
    startSelfTest = true;
  }
}
