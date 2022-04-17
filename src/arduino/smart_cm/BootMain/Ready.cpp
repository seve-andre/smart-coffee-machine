#include "Arduino.h"
#include "Ready.h"

Ready::Ready() {
  this-> isFirstReady = true;
}
  
void Ready::showReadyMessage() {
  if (isFirstReady) {
    isFirstReady = false;
    //Da cambiare con stampa su LCD
    Serial.println("Machine Ready");
  }
}

void Ready::resetIsFirstReady() {
  this->isFirstReady = true;
}
