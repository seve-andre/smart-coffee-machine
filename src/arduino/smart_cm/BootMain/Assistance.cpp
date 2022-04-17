#include "Assistance.h"
#include "BootMain.h"

Assistance::Assistance() {
  this-> isAssistanceRequiredPrint = false;
  this-> isAssistanceTriggered = false;
}

void Assistance::assistanceRequired() { 
  if (!isAssistanceRequiredPrint) {
    isAssistanceTriggered = true;
    isAssistanceRequiredPrint = true;
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Assistance Required");
  }
}

bool Assistance::getAssistanceStatus() {
  return this->isAssistanceTriggered;
}
