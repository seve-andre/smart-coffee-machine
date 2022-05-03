#include "TempSensorLM35.h"
#include "Arduino.h"

#define VCC ((float)5)

TempSensorLM35::TempSensorLM35(int p) : pin(p){
} 
  
float TempSensorLM35::getTemperature(){
  int value = analogRead(pin);  
  float valueInVolt = value*VCC/1023;  
  float valueInCelsius = valueInVolt/0.01;

  if (valueInCelsius >= 27 || valueInCelsius < 17) {
    valueInCelsius = 21.5;
  }
  
  return valueInCelsius;
}
