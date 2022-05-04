#include "ServoMotorImpl.h"
#include "Arduino.h"
#include "DrinkFactory.h"
#include "ServoTimer2.h"
#include "CoffeeMachine.h"
#include "Sonar.h"

bool activeServo;
unsigned int contCycle;
unsigned int n_drink;
unsigned long tStop;
unsigned long tServo;

ServoMotorImpl::ServoMotorImpl(unsigned int pin){
  this->pin = pin;  
  pos = 0;
  this->on();  // attaches the servo on pin 3 to the servo object
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

void ServoMotorImpl::restartTimerStop() {
  tStop = millis();
}

// Simulate the drink out
void ServoMotorImpl::startServoMakeDrink() {
  moveServoTo180MakeDrink();
  stopServoMakeDrink();
  timerServoMakeDrink();
}


// goes from 0 degrees to 180 degrees
void ServoMotorImpl::moveServoTo180MakeDrink() {
  if (pos < 180 && activeServo) {
    activeServo = false;                       // tell servo to go to position in variable 'pos'
    
    noInterrupts();
    pos += 4;
    interrupts();
    
    this->setPosition(pos);
    Serial.println(pos);
    //delay(15);                                // waits 90ms for the servo to reach the position
  } else if (pos >= 180) {
    startServoTo180MakeDrink = false;
  }
}

void ServoMotorImpl::startServoTimers() {
  tServo = millis();
  tStop = millis();
}

void ServoMotorImpl::resetServo() {
   moveServoTo0MakeDrink();
}

// goes from 180 degrees to 0 degrees
void ServoMotorImpl::moveServoTo0MakeDrink() {
  pos = 0;
  this->setPosition(pos);
  delay(1000);
}

bool ServoMotorImpl::isServoFinish() {
  return servoFinish;
}

//Timer per fine rotazione a 180° di Servo
void ServoMotorImpl::stopServoMakeDrink() {  
  //Interrupt
  if ((millis() - tStop) >= 10000) {
    tStop = millis();
    Serial.println("Tempo Finito");
    // init sonar timer
    // Sonar::initializeTimer();
    CoffeeMachine::goToWorkingState(WorkingState::TAKE_DRINK);
  }
}

//Timer per tick di Servo
void ServoMotorImpl::timerServoMakeDrink() {
  //Interrupt
  if ((millis() - tServo) >= 150) {
      Serial.println("active servo");
      tServo = millis();
      activeServo = true;
  }
}

//SELF-TEST
//Simulate the drink out
void ServoMotorImpl::startServoSelfTest() {

  if (startServoTo180SelfTest) {
    moveServoTo180SelfTest();
  } else {
    moveServoTo0SelfTest();
  }
  
  stopServoSelfTest();
  timerServoSelfTest();
}

// goes from 180 degrees to 0 degrees
void ServoMotorImpl::moveServoTo180SelfTest() {  
  if (pos < 180 && activeServo) {
    activeServo = false;                       // tell servo to go to position in variable 'pos'
    
    noInterrupts();
    pos += 6;
    interrupts();
    
    this->setPosition(pos);
    Serial.println(pos);
    //delay(15);                                // waits 90ms for the servo to reach the position
  } else if (pos > 180) {
    servoFinish = true;
    Serial.println("Servo is done");
    //this->off();
  }
}

// goes from 180 degrees to 0 degrees
void ServoMotorImpl::moveServoTo0SelfTest() {  
  if (pos > 0 && activeServo) {
    activeServo = false;                       // tell servo to go to position in variable 'pos'
    
    noInterrupts();
    pos -= 6;
    interrupts();
    
    this->setPosition(pos);
    Serial.println(pos);
    //delay(15);                                // waits 90ms for the servo to reach the position
  } else if (pos <= 0) {
    servoFinish = true;
    Serial.println("Servo is done");
    this->off();
  }
}


//Timer per fine rotazione a 180° di Servo
void ServoMotorImpl::stopServoSelfTest() {  
  //Interrupt
  if ((millis() - tStop) >= 180000) {
    tStop = millis();
  }
}

//Timer per tick di Servo
void ServoMotorImpl::timerServoSelfTest() {  
  //Interrupt
  if ((millis() - tServo) >= 3050) {
    Serial.println("active servo");
    tServo = millis();
    activeServo = true;
  }
}
