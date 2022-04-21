#include "Sonar.h"

Sonar* proximitySensor;

const int triggerPort = 10;
const int echoPort = 11;
unsigned long Ttimeout;

void setup() {
  Ttimeout = millis();
  Serial.begin(9600);
  proximitySensor = new Sonar(echoPort, triggerPort);
}

void loop() {
  Serial.println(proximitySensor->getDistance());    
  // Serial.println(String("dist: ") + d+ "|");
  timeTimeout();
}

void timeTimeout() {
  static unsigned long dt;

  dt = millis() - Ttimeout;

  //Interrupt
  if (dt >= 5000 || proximitySensor->isDrinkTaken()) {
      Serial.println("machine goes on");
      Ttimeout = millis();
  }
}
