#include "Pot.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin){
  this->pin = pin;
} 
  
unsigned int Potentiometer::getValue(){
  float val = analogRead(pin);
  return (unsigned int) map(val, 0, 1023, 0, 5);
}
