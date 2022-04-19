#include "Sonar.h"

Sonar* proximitySensor;

const int triggerPort = 11;
const int echoPort = 10;

void setup() {
  Serial.begin(9600);
  proximitySensor = new Sonar(echoPort, triggerPort, 20);
}

void loop() {
  Serial.println(proximitySensor->getDistance());
}
