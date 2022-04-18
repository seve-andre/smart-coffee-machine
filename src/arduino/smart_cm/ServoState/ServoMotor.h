#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

#include <Servo.h>

class ServoMotor {
  public:
    ServoMotor(unsigned int pin);
    void beginningDrinkOut();
    void prepareDrink();
    void moveServoTo180(); // goes from 0 degrees to 180 degrees
    void moveServoTo0(); // goes from 0 degrees to 180 degrees
    
  private:
    Servo servoMotor;
    enum { PRODUCT_NOT_READY, PRODUCT_READY} stateProduct;
    
    int pos;
    bool startServoTo180;
    bool startServoTo0;
};

#endif
