#ifndef __BOOT__
#define __BOOT__

#include "State.h"

class Boot {
  
  public:
    void showWelcomeMessage() {
        //Da cambiare con stampa su LCD
        Serial.println("Welcome to Smart Caffee Machine");
    }
}; 

#endif
