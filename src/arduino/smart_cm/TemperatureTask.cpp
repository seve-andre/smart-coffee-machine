#include "TemperatureTask.h"
#include "TempSensorImpl.h"

TempSensor* tempSensor;

unsigned long tSelfTest;
bool startSelfTest = true;

ServoMotorImpl* myServo;

TemperatureTask::TemperatureTask() {
  tempSensor = new TempSensorLM35(0);
  tSelfTest = millis();
  startSelfTest = true;
  coffeeMachine = new CoffeeMachine();
  myServo = new ServoMotorImpl(3);
}

void TemperatureTask::moveServo() {
  myServo->startServoSelfTest();
}

void TemperatureTask::tick() {
  this->interruptTimerSelfTest();

  WorkingState currentState = coffeeMachine->getState();
  MachineState machineState = coffeeMachine->getMachineState();
  
  if (
    (currentState == READY || currentState == WAIT_FOR_BUTTON_INPUT)
    && machineState == WORKING
  ) {
    startSelfTest = true;
  } else {
    tSelfTest = millis();
    startSelfTest = false;
  }

  if (startSelfTest) {
    moveServo();
  }
}

void TemperatureTask::interruptTimerSelfTest() {
  //Interrupt
  if ((millis() - tSelfTest) >= 180000) {
    Serial.println("DO Temperature check");
    Serial.println(tempSensor->getTemperature());
    tSelfTest = millis();
    if (!isTemperatureInRange()) {
      CoffeeMachine::goToMachineState(SELF_TEST);
    }
  }
}

bool TemperatureTask::isTemperatureInRange() {
  float temp = tempSensor->getTemperature();
  
  return (temp >= 17.0 && temp <= 24.0);
}
