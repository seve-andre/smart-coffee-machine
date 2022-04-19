#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

#include <Servo.h>

class ServoMotor {
  public:
    ServoMotor(unsigned int pin);
    void beginningDrinkOut();
    void prepareDrink(unsigned int n_drink);
    void moveServoTo180(); // goes from 0 degrees to 180 degrees
    void moveServoTo0(); // goes from 0 degrees to 180 degrees
    void printMessageDrinkReady(unsigned int n_drink);
    
  private:
    Servo servoMotor;
    enum {PRODUCT_NOT_READY, PRODUCT_READY} stateProduct;

    unsigned int n_drink;
    int pos;
    bool startServoTo180;
    bool startServoTo0;
};

#endif
