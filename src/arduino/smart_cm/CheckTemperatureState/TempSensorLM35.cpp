#include "TempSensorLM35.h"
#include "Arduino.h"

#define VCC ((float)5)

TempSensorLM35::TempSensorLM35(int p) : pin(p){
} 
  
float TempSensorLM35::getTemperature(){
  int value = analogRead(pin);

  //modifica grezza per far stare la temperature nel range
  value -= 5;
  
  float valueInVolt = value*VCC/1023;  
  float valueInCelsius = valueInVolt/0.01;
  return valueInCelsius;
}
