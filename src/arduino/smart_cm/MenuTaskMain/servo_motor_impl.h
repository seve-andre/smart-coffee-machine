#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "servo_motor.h"
#include <arduino.h>
#include "ServoTimer2.h"

class ServoMotorImpl: public ServoMotor {

public:
  ServoMotorImpl(unsigned int pin);
  void startServo();
  void resetServo();
  void stopServo();
  void timerServo();    
  void startServoTimers();
  void setPosition(int angle);
  
private:
  void on();
  void off();
  void moveServoTo180();
  void moveServoTo0();
  unsigned int pin;
  unsigned int pos; 
  ServoTimer2 motor;
};

#endif
