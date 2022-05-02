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
  void moveServoTo0();
  bool isServoFinish();
  
private:
  void on();
  void off();
  void moveServoTo180();
  unsigned int pin;
  unsigned int pos; 
  bool startServoTo180;
  bool servoFinish;
  ServoTimer2 motor;
};

#endif
