#include "servo_motor_impl.h"
#include "Arduino.h"
#include "DrinkFactory.h"
#include "ServoTimer2.h"
#include "CoffeeMachine.h"

bool activeServo;
unsigned int contCycle;
unsigned int n_drink;
unsigned long tStop;
unsigned long tServo;

ServoMotorImpl::ServoMotorImpl(unsigned int pin){
  this->pin = pin;  
  pos = 0;
  this->on();  // attaches the servo on pin 3 to the servo object
  //tStop = millis();
  activeServo = false;
} 

void ServoMotorImpl::on(){
  motor.attach(pin);    
}

void ServoMotorImpl::setPosition(int angle){
  // 750 -> 0, 2250 -> 180 
  // 750 + angle*(2250-750)/180
  float coeff = (2250.0-750.0)/180;
  this->motor.write(750 + angle*coeff);
}

void ServoMotorImpl::off(){
  motor.detach();    
}

//-----------------------------------------------

//Simulate the drink out
void ServoMotorImpl::startServo() {
  moveServoTo180();
  stopServo();
  timerServo();
}

// goes from 0 degrees to 180 degrees
void ServoMotorImpl::moveServoTo180() {
  if (pos < 180 && activeServo) {
    activeServo = false;                       // tell servo to go to position in variable 'pos'
    noInterrupts();
    pos += 3;
    this->setPosition(pos);
    interrupts();
    Serial.println(pos);
    delay(25);                                // waits 90ms for the servo to reach the position
  }
}

void ServoMotorImpl::startServoTimers() {
  tServo = millis();
  tStop = millis();
}

void ServoMotorImpl::resetServo() {
   moveServoTo0();
}

// goes from 180 degrees to 0 degrees
void ServoMotorImpl::moveServoTo0() {
  pos = 0;
  this->setPosition(pos);
  delay(1000);
  this->off();
}

//Timer per fine rotazione a 180° di Servo
void ServoMotorImpl::stopServo() {  
  //Interrupt
  if ((millis() - tStop) >= 10000) {
    tStop = millis();
    Serial.println("Tempo Finito");
    CoffeeMachine::goToState(WorkingState::TAKE_DRINK);
    //drinkFactory->drinkReadyMessage(menuSelector->getSelected());
  }
}

//Timer per tick di Servo
void ServoMotorImpl::timerServo() {  
  //Interrupt
  if ((millis() - tServo) >= 150) {
      Serial.println("active servo");
      tServo = millis();
      activeServo = true;
  }
}
