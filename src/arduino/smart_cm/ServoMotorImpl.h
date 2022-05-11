#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "ServoMotor.h"
#include "Arduino.h"
#include "ServoTimer2.h"

class ServoMotorImpl: public ServoMotor {

public:
  ServoMotorImpl(unsigned int pin);
  void startServoMakeDrink();
  void startServoSelfTest();
  void resetServo();
  
  void stopServo();
  void timerServo();
  void stopServoMakeDrink();
  void restartTimerStop();
  void stopServoSelfTest();
  void timerServoMakeDrink();
  void timerServoSelfTest();
  void startServoTimers();
  
  void setPosition(int angle);
  void moveServoTo0();
  void moveServoTo0MakeDrink();
  void moveServoTo0SelfTest();
  bool isServoFinish();
  void off();
  void resetPosition();
  
private:
  void on();
  void moveServoTo180();
  void moveServoTo180MakeDrink();
  void moveServoTo180SelfTest();
  unsigned int pin;
  unsigned int pos; 
  bool startServoTo180MakeDrink;
  bool startServoTo180SelfTest;
  bool servoFinish;
  ServoTimer2 motor;
};

#endif
