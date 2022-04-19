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

bool Sonar::isDrinkTaken() {
  return (getDistance() >= MAX_DISTANCE);

//  if (d < MAX_DISTANCE) {
//      return true; 
//  } else if (d >= MAX_DISTANCE) {
//    return NO_OBJ_DETECTED;
//  }
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

    Serial.println(d);
    delay(50);

    if (d < 0.04 || d > 1.0) {
      d = 0.00;
    }
    
    return d;
}
