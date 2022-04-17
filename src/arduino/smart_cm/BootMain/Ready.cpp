#include "Arduino.h"
#include "Ready.h"
#include "BootMain.h"

Ready::Ready() {
  this-> isFirstReady = true;
}
  
void Ready::showReadyMessage() {
  if (isFirstReady) {
    isFirstReady = false;
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Ready");
  }
}

void Ready::resetIsFirstReady() {
  this->isFirstReady = true;
}
