#include "Sonar.h"

Sonar* proximitySensor;

const int triggerPort = 11;
const int echoPort = 10;

void setup() {
  Serial.begin(9600);
  proximitySensor = new Sonar(echoPort, triggerPort);
}

void loop() {
  Serial.println(proximitySensor->getDistance());
}
