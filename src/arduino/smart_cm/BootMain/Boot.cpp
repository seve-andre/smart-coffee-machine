#include "BootMain.h"
#include "Arduino.h"
#include "Boot.h"

Boot::Boot() { 
    this->timePauseBoot = 2000;
    this->n_thea = 5;
    this->n_coffee = 5;
    this->n_chocolate = 5;
    this->isWelcomeMessageShow = true;
    this->isReadyMessageShow = true;
    this->initializationStatus = false;
}
  
void Boot::showWelcomeMessage() {
    //Da cambiare con stampa su LCD
    if (isWelcomeMessageShow) {
      isWelcomeMessageShow = false;
      Serial.println("Welcome to Smart Caffee Machine");
    }
    
    pauseBoot();
}
      
//vai in pausa dopo timePauseBoot (s)
void Boot::pauseBoot() {
  static unsigned long tPauseBoot, dt; 

  dt = millis() - tPauseBoot;

  //scatta l'interrupt
  if (dt >= timePauseBoot) {
    if (this->isReadyMessageShow) {
      isReadyMessageShow = false;
      initializationStatus = true;
      readyState = 1;
    }
  }
}

void Boot::initialization() {
  isReadyMessageShow = true;
  
  showWelcomeMessage();
  pauseBoot();
}

bool Boot::isInitializationComplete() {
  return this->initializationStatus;
}
