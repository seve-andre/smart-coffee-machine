#include "Sonar.h"
#include "Arduino.h"

Sonar::Sonar(int echoPort, int trigPort, long maxTime) {
  this->echoPort = echoPort;
  this->trigPort = trigPort;
  this->timeOut = maxTime;
  
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

    if (d >= 0.05 && d < 0.41) {
      return d; 
    }    
    else if (d <= 0.04 || d > 1.0) {
      return OBJ_CLOSE;
    } else if (d > 0.41) {
      return NO_OBJ_DETECTED;
    }
}
