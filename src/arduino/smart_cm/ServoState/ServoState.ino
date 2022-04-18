#include <Servo.h>

Servo myservo;

int pos;
enum { PRODUCT_NOT_READY, PRODUCT_READY} stateProduct;
bool startServoTo180;
bool finishServoTo180;
bool startServoTo0;
bool finishServoTo0;

/*
 * If/when the making process starts, a proper message "making a XXX…" is displayed 
 * (XXX = "coffee", "tea", "chocolate").  The making process of a product  is simulated 
 * by means of the motor M, rotating from 0 (beginning of the process) to 180 (end of the process, product ready). 
 * The making process takes Tmaking seconds to complete. 
 * When the process has completed, a message "The XXX is ready." is displayed.
*/

void setup() {
  Serial.begin(9600);

  stateProduct = PRODUCT_NOT_READY;
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  startServoTo180 = false;
  myservo.write(0);
}

void loop() {
  moveServo();
}

void moveServo() {
  if (!startServoTo180) {
    moveServoTo180();
  } else if (!startServoTo0) {
    moveServoTo0();
  }
}

// goes from 0 degrees to 180 degrees
void moveServoTo180() {
  startServoTo180 = true;

  for (pos = 0; pos <= 180; pos += 3) { 
    // in steps of 1 degree
    myservo.write(pos);                 // tell servo to go to position in variable 'pos'
    delay(90);                          // waits 15ms for the servo to reach the position
  }
  
  startServoTo0 = false;
  myservo.write(180);   
}

// goes from 180 degrees to 0 degrees
void moveServoTo0() {
  startServoTo0 = true;

  for (pos = 180; pos >= 0; pos -= 3) { 
    // in steps of 1 degree
    myservo.write(pos);                 // tell servo to go to position in variable 'pos'
    delay(90);                          // waits 15ms for the servo to reach the position
  }
  
  myservo.write(1); 
  stateProduct = PRODUCT_READY;   
}
