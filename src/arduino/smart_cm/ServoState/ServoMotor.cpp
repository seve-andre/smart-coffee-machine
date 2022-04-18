#include "ServoMotor.h"
#include "Arduino.h"

ServoMotor::ServoMotor(unsigned int pin) {
  this->servoMotor.attach(pin);  // attaches the servo on pin 9 to the servo object
  beginningDrinkOut();
}

void ServoMotor::beginningDrinkOut() {
  this->stateProduct = PRODUCT_NOT_READY;
  this->startServoTo180 = false;
  this->servoMotor.write(0);
}

//Simulate the drink out
void ServoMotor::prepareDrink() {
  if (!startServoTo180) {
    moveServoTo180();
  } else if (!startServoTo0) {
    moveServoTo0();
  }
}

// goes from 0 degrees to 180 degrees
void ServoMotor::moveServoTo180() {
  startServoTo180 = true;

  for (pos = 0; pos <= 180; pos += 3) { 
    servoMotor.write(pos);                 // tell servo to go to position in variable 'pos'
    delay(75);                          // waits 90ms for the servo to reach the position
  }
  
  startServoTo0 = false; 
}

// goes from 180 degrees to 0 degrees
void ServoMotor::moveServoTo0() {
  startServoTo0 = true;

  for (pos = 180; pos >= 0; pos -= 3) { 
    servoMotor.write(pos);                 // tell servo to go to position in variable 'pos'
    delay(75);                          // waits 15ms for the servo to reach the position
  }
  
  servoMotor.write(1); 
  stateProduct = PRODUCT_READY;
  Serial.println("The XXX is ready");
}
