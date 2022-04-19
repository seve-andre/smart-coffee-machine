#include "ServoMotor.h"

ServoMotor* myservo;

/*
 * If/when the making process starts, a proper message "making a XXX…" is displayed 
 * (XXX = "coffee", "tea", "chocolate").  The making process of a product  is simulated 
 * by means of the motor M, rotating from 0 (beginning of the process) to 180 (end of the process, product ready). 
 * The making process takes Tmaking seconds to complete. 
 * When the process has completed, a message "The XXX is ready." is displayed.
*/

void setup() {
  Serial.begin(9600);

}

void loop() {
  myservo->prepareDrink(1);
}
