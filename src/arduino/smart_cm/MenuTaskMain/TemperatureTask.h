#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "Task.h"
#include "servo_motor_impl.h"
#include "servo_motor.h"


class TemperatureTask : public Task {
  public:
    TemperatureTask();
    void moveServo();
    void stopServo();
    void tick();
    void checkTimeTimeout();
    bool checkTemperatureRange();

    ServoMotorImpl* myServo;
};

#endif
