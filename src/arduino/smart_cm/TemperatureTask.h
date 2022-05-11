#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "Task.h"
#include "ServoMotorImpl.h"
#include "ServoMotor.h"
#include "CoffeeMachine.h"

extern ServoMotorImpl* myServo;

class TemperatureTask : public Task {
  public:
    TemperatureTask();
    void moveServo();
    void stopServo();
    void tick();
    void checkTimeTimeout();
    void interruptTimerSelfTest();
    bool isTemperatureInRange();

  private:
    CoffeeMachine* coffeeMachine;
};

#endif
