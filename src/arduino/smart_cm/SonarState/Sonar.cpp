#include "Sonar.h"
#include "Arduino.h"

Sonar::Sonar(int echoPort, int trigPort) {
  this->echoPort = echoPort;
  this->trigPort = trigPort;
  
  pinMode(trigPort, OUTPUT);
  pinMode(echoPort, INPUT);  
}

float Sonar::getSoundSpeed() {
  return 331.5 + 0.6*temperature;   
}

float Sonar::getDistance() {
    digitalWrite(trigPort,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPort,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPort,LOW);
    
    long tUS = pulseInLong(echoPort, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*getSoundSpeed();
    
    if (d < MAX_DISTANCE) {
      return OBJ_DETECTED; 
    } else if (d >= MAX_DISTANCE) {
      return NO_OBJ_DETECTED;
    }
}
